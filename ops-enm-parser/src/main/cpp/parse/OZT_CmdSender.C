/*------------------------------------------------------------------------------
 *******************************************************************************
 * COPYRIGHT Ericsson 2018
 *
 * The copyright to the computer program(s) herein is the property of
 * Ericsson Inc. The programs may be used and/or copied only with written
 * permission from Ericsson Inc. or in accordance with the terms and
 * conditions stipulated in the agreement/contract under which the
 * program(s) have been supplied.
 *******************************************************************************
 *----------------------------------------------------------------------------*/
//TORF-241666

#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fstream>
#include <strstream>
#include <time.h>
#include <OZT_CmdSender.H>
#include <CHA_OZTInfo.H>
#include <OZT_EventHandler.H>
#include <OZT_RunTimeNLS.H>
#include <OZT_Misc.H>
#include <trace.H>
#include <CHA_SeqDelRespReceiver.H>
#include <rw/tools/regex.h>


//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_CmdSender";
//static CAP_TRC_trace trace = CAP_TRC_DEF((char *)"OZT_CmdSender", (char *)"C");


//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_CmdSender.C,v 21.0 1996/08/23 12:43:42 ehsgrap Rel $";


//*****************************************************************************

extern RWCString ozt_applName;
extern CHA_OZTInfo ozt_info;
extern OZT_EventHandler* ozt_evHandlerPtr;

//*****************************************************************************

// Initialize the static data member
#if TPF >= 400
OZT_CmdSender* OZT_CmdSender::thisPointer = 0;
#endif

//*****************************************************************************

long OZT_CmdSender::defaultFBAttempts;    // default No. of attempts
long OZT_CmdSender::defaultFBInterval;    // default retry interval

//*****************************************************************************

OZT_CmdSender::OZT_CmdSender(OZT_CmdRspBuf& theCmdRspBuf)
    : cmdRspBuf(theCmdRspBuf),
      useDeviceMode(FALSE),
      autoConfirm(TRUE),
      orderedOn(TRUE),
      reportIsOn(FALSE),
      lastSentCmd(RWCString()),
      okReply(RWCString()),
      failReply(RWCString()),
      RFlag(FALSE),
      ZFlag(FALSE),
      storedFileName(RWCString()),
      curFile(RWCString()),
      interruptPending(FALSE),
      isOnDisconnectSetFlag(FALSE),
      clientQuitFlag(FALSE),
      iOSuperTimerValue(3),
      onDisconnectLabel(RWCString())

{
    TRACE_IN(trace, OZT_CmdSender, "");
    //
    // make a unique name for this instance of the application
    //
    strstream tempName;
    pid =  getpid();
    tempName << ozt_applName << pid << ends;
    RWCString uniqueName(tempName.str());
    delete tempName.str();

    //
    // initialise CAP_IPC
    //
    TRACE_FLOW(trace, OZT_CmdSender, "PROCESS NAME = " << uniqueName);
    TRACE_FLOW(trace, OZT_CmdSender, "PROCESS ID = " << pid);

#if TPF >= 400
    thisPointer = this;
   // IPC_register_input_handler((IPC_input_handler_type)setInputHandler);
#endif
/*
    if (IPC_init((char*)(uniqueName.data()),
		 Install_handler, Remove_handler) != 0)
    {
        TRACE_OUT(trace, OZT_CmdSender, "init IPC fails!");

        int errcode = IPC_get_error_code();
        char* errmsg = IPC_get_error_msg();
        cerr << "IPC init failed with error code " << errcode << endl;
        cerr << "Error message: " << errmsg << endl;
        delete [] errmsg;

        constructSucceed = FALSE;
        return;
    }
*/
    //
    // Create CHALIB objects
    //
    pIOSuper         = new CHA_IPCSupervisor;
    pRoutingHandler  = new CHA_RoutingHandler;
    pCmdSender       = new CHA_CommandSender(pIOSuper,
					     uniqueName.data(),
					     pRoutingHandler);
    pSpontReceiver   = new CHA_SpontRepReceiver(pIOSuper, uniqueName.data());
    pSpontSubscriber = new CHA_SpontSubscriber(NULL, uniqueName.data(), FALSE);
    if ((pIOSuper == 0) || (pCmdSender == 0))
    {
        TRACE_OUT(trace, OZT_CmdSender, "CHALIB object creation fails!");
        constructSucceed = FALSE;
        return;
    }

#if ! ( TPF >= 400 )
    ozt_evHandlerPtr->setIOTrigger((void*)this,
				   OZT_CmdSender::tickCallBack,
				   IPC_get_socket());
#endif

    /*ozt_evHandlerPtr->setTickTrigger((void*)this,
				     OZT_CmdSender::tickCallBack);*/

    // get these from the routing handler stuff
    pDelReceiver  = pRoutingHandler->getRoutingCase(CHA_RT_DELAYED)->getResponseReceiver();
    pImmReceiver  = pRoutingHandler->getRoutingCase(CHA_RT_IMMEDIATE)->getResponseReceiver();
    pConnection   = pCmdSender->getConnectionObject();
    pPromptString = pCmdSender->getPromptObject();
    pRspReceiver  = new OZT_RspReceiver(&cmdRspBuf,
                                        pImmReceiver,
                                        pDelReceiver,
                                        pSpontReceiver);
    if (pRspReceiver == 0)
    {
        TRACE_OUT(trace, OZT_CmdSender, "Memory allocation problem!");
        constructSucceed = FALSE;
        return;
    }
    pDelReceiver->addDependent(this);
    pCmdSender->addDependent(this);

    //
    //  initialise FUNCTION BUSY retries default
    //
    int tempAttempts = 0;
    int tempInterval = 0;

    ozt_info.getAttemptsAndIntvl(tempAttempts, tempInterval);
    defaultFBAttempts = (long)tempAttempts;
    defaultFBInterval = (long)tempInterval;
    if (defaultFBAttempts < 1) defaultFBAttempts = 1;
    if (defaultFBInterval < 1) defaultFBInterval = 1;
    (void)setFunBusyParam(OZT_Value((long)defaultFBAttempts),
                          OZT_Value((long)defaultFBInterval));

    changeState(IDLE);
    constructSucceed = TRUE;

#ifdef OZT_PROTOTYPE
    theDCConfirmFunc = 0;
#endif

    TRACE_OUT(trace, OZT_CmdSender, "Construct okay!");
}

OZT_CmdSender::OZT_CmdSender(CHA_CommandSender *cms,OZT_CmdRspBuf& theCmdRspBuf,OZT_EventHandler *ozt_evthdlr)
    : cmdRspBuf(theCmdRspBuf),
      useDeviceMode(FALSE),
      autoConfirm(TRUE),
      orderedOn(TRUE),
      reportIsOn(FALSE),
      lastSentCmd(RWCString()),
      okReply(RWCString()),
      failReply(RWCString()),
      RFlag(FALSE),
      ZFlag(FALSE),
      storedFileName(RWCString()),
      curFile(RWCString()),
      interruptPending(FALSE),
      isOnDisconnectSetFlag(FALSE),
      clientQuitFlag(FALSE),
      iOSuperTimerValue(3),
      pCmdSender(cms),
      onDisconnectLabel(RWCString())

{
    TRACE_IN(trace, OZT_CmdSender, "");
    //
    // make a unique name for this instance of the application
    //
    strstream tempName;
    pid =  getpid();
    tempName << ozt_applName << pid << ends;
    RWCString uniqueName(tempName.str());
    delete tempName.str();
    ozt_evHandlerPtr = ozt_evthdlr ;
    //
    // initialise CAP_IPC
    //
    TRACE_FLOW(trace, OZT_CmdSender, "PROCESS NAME = " << uniqueName);
    TRACE_FLOW(trace, OZT_CmdSender, "PROCESS ID = " << pid);

#if TPF >= 400
    thisPointer = this;
   // IPC_register_input_handler((IPC_input_handler_type)setInputHandler);
#endif
/*
    if (IPC_init((char*)(uniqueName.data()),
		 Install_handler, Remove_handler) != 0)
    {
        TRACE_OUT(trace, OZT_CmdSender, "init IPC fails!");

        int errcode = IPC_get_error_code();
        char* errmsg = IPC_get_error_msg();
        cerr << "IPC init failed with error code " << errcode << endl;
        cerr << "Error message: " << errmsg << endl;
        delete [] errmsg;

        constructSucceed = FALSE;
        return;
    }
*/
    //
    // Create CHALIB objects
    //
    pIOSuper         = new CHA_IPCSupervisor;
    pRoutingHandler  = new CHA_RoutingHandler;
 /*   pCmdSender       = new CHA_CommandSender(pIOSuper,
					     uniqueName.data(),
					     pRoutingHandler);*/
    pSpontReceiver   = new CHA_SpontRepReceiver(pIOSuper, uniqueName.data());
    pSpontSubscriber = new CHA_SpontSubscriber(NULL, uniqueName.data(), FALSE);
    if ((pIOSuper == 0) || (pCmdSender == 0))
    {
        TRACE_OUT(trace, OZT_CmdSender, "CHALIB object creation fails!");
        constructSucceed = FALSE;
        return;
    }

#if ! ( TPF >= 400 )
    ozt_evHandlerPtr->setIOTrigger((void*)this,
				   OZT_CmdSender::tickCallBack,
				   IPC_get_socket());
#endif

    /*ozt_evHandlerPtr->setTickTrigger((void*)this,
				     OZT_CmdSender::tickCallBack);*/

    // get these from the routing handler stuff
    pDelReceiver  = pRoutingHandler->getRoutingCase(CHA_RT_DELAYED)->getResponseReceiver();
    pImmReceiver  = pRoutingHandler->getRoutingCase(CHA_RT_IMMEDIATE)->getResponseReceiver();
    pConnection   = pCmdSender->getConnectionObject();
    pPromptString = pCmdSender->getPromptObject();
    pRspReceiver  = new OZT_RspReceiver(&cmdRspBuf,
                                        pImmReceiver,
                                        pDelReceiver,
                                        pSpontReceiver);
    if (pRspReceiver == 0)
    {
        TRACE_OUT(trace, OZT_CmdSender, "Memory allocation problem!");
        constructSucceed = FALSE;
        return;
    }
    pDelReceiver->addDependent(this);
    pCmdSender->addDependent(this);

    //
    //  initialise FUNCTION BUSY retries default
    //
    int tempAttempts = 0;
    int tempInterval = 0;
   

    ozt_info.getAttemptsAndIntvl(tempAttempts, tempInterval);
    defaultFBAttempts = (long)tempAttempts;
    defaultFBInterval = (long)tempInterval;
    if (defaultFBAttempts < 1) defaultFBAttempts = 1;
    if (defaultFBInterval < 1) defaultFBInterval = 1;
    (void)setFunBusyParam(OZT_Value((long)defaultFBAttempts),
                          OZT_Value((long)defaultFBInterval));

    changeState(CONFIRM_PENDING);
    constructSucceed = TRUE;

#ifdef OZT_PROTOTYPE
    theDCConfirmFunc = 1;
#endif

    TRACE_OUT(trace, OZT_CmdSender, "Construct okay!");
}



//*****************************************************************************

OZT_CmdSender::~OZT_CmdSender()
{
    if (ozt_evHandlerPtr != NULL) {
        ozt_evHandlerPtr->unsetTickTrigger((void*)this);
#if ! ( TPF >= 400 )
        ozt_evHandlerPtr->unsetIOTrigger((void*)this, IPC_get_socket());
#else
        // IPC_terminate() below implicitly calls setInputHandler().
#endif
        ozt_evHandlerPtr->unsetTimer((void*)this);
    }

    pDelReceiver->removeDependent(this);
    pCmdSender->removeDependent(this);
    delete pRspReceiver;
    delete pSpontReceiver;
    delete pSpontSubscriber;
    delete pCmdSender;
    delete pIOSuper;

    if (pRoutingHandler != NULL) {
        delete pRoutingHandler;
        pRoutingHandler = NULL;
    }

  //  IPC_terminate();
}

//*****************************************************************************

int OZT_CmdSender::timeOutCallBack(void* instance)
{
  TRACE_IN(trace, timeOutCallBack, "");
    ((OZT_CmdSender*)instance)->timeOut();

    return ozt_evHandlerPtr->notify_done();
}

//*****************************************************************************

int OZT_CmdSender::tickCallBack(void* instance)
{
    TRACE_IN(trace, tickCallBack, "");
    ((OZT_CmdSender*)instance)->checkRspArrival();

    return ozt_evHandlerPtr->notify_done();
}

//*****************************************************************************

void OZT_CmdSender::checkRspArrival()
{

  static int counter = 0;

  TRACE_IN(trace, checkRspArrival, "");
  //if (counter == 0)TRACE_FLOW(trace, checkRspArrival, "iOSuperTimerValue = " << iOSuperTimerValue );

  // Added due to improvement to avoid hanging problem
  if (clientQuitFlag)
    {
      interrupt();
    }
  else
    {

#if ! ( TPF >= 400 )
      (void)IPC_asyncio();
#endif
      // Added due to improvement to avoid hanging problem


      if(senderState == WAIT_DEL_RSP)
	{
	  TRACE_FLOW(trace, checkRspArrival, "counter = " << counter );
	  if (counter%10 == 0 && pConnection->getConnectionStatus() == -1/*!= EAC_CRI_CS_CONNECTED*/) // No connection left, stop trying to get DR
	    {
	      interrupt();
	      counter = 0;
	    }

	  else if(counter > connIdleToTimerValue) // No DR has been received during the time connIdleToTimerValue, stop trying to get DR
	    {
	      interruptAtDr();  //Should be an special interrupt, indicating no DR received
	      counter = 0;
	    }
	  else
	    {
	      sleepAWhile();
	      pIOSuper->checkIPCQue();
	      counter += iOSuperTimerValue;
	    }
	}
      else
	{
	  counter = 0;
	  pIOSuper->checkIPCQue();
	}
      pSpontSubscriber->updateFrom(0,0);
      // pConnection->updateFrom(0,0);
    }
}

//*****************************************************************************

RWBoolean OZT_CmdSender::constructOK() const
{
    return constructSucceed;
}


//*****************************************************************************

CHA_CommandSender& OZT_CmdSender::getCHACmdSender()
{
    TRACE_FLOW(trace, getCHACmdSender, "");
    return *pCmdSender;
}

//*****************************************************************************

CHA_Connection& OZT_CmdSender::getConnectionObject()
{
    TRACE_FLOW(trace, getConnectionObject, "");
    return *pConnection;
}

//*****************************************************************************

OZT_CmdRspBuf& OZT_CmdSender::getCmdRspBuf()
{
    TRACE_FLOW(trace, getCmdRspBuf, "");
    return cmdRspBuf;
}

//****************************************************************************

OZT_RspReceiver& OZT_CmdSender::getRspReceiver()
{
    TRACE_FLOW(trace, getRspReceiver, "");
    return *pRspReceiver;
}

//****************************************************************************

CHA_SpontSubscriber& OZT_CmdSender::getSpontSubscriber()
{
    TRACE_FLOW(trace, getSpontSubscriber, "");
    return *pSpontSubscriber;
}

//*****************************************************************************

OZT_CmdSender::State OZT_CmdSender::getState() const
{
    return senderState;
}

//*****************************************************************************

long OZT_CmdSender::getPid() const
{
  TRACE_FLOW(trace, getSpontSubscriber, pid);
  return pid;
}

//****************************************************************************

RWCString OZT_CmdSender::getExchangeHeader()
{
	TRACE_FLOW(trace, getExchangeHeader, "");

	return "";
}
//****************************************************************************

RWCString OZT_CmdSender::getIoType(const RWCString& neName)
{
	TRACE_FLOW(trace, getIoType, "neName: "+neName);

	if (neName.isNull() && pConnection->getConnectionStatus() == -1) {
		return "";
	}
	else {
		return pConnection->getIoType(neName);
	}
}
//****************************************************************************

RWCString OZT_CmdSender::getProtocolType(const RWCString& neName)
{
	TRACE_FLOW(trace, getProtocolType, "neName: "+neName);

	if (neName.isNull()) {
		return "";
	}
	else {
		return pConnection->getProtocolType(neName);
	}
}

//****************************************************************************

void OZT_CmdSender::changeState(const State newState)
{
    TRACE_FLOW(trace, changeState, printState(newState));
    senderState = newState;
    if (newState == WAIT_DEL_RSP)
    {
        CHA_SeqDelRespReceiver::updateOZTWaitDlRsp(1);
    }
    else
    {
        CHA_SeqDelRespReceiver::updateOZTWaitDlRsp(0);
    }

    if(newState == IDLE)
    {
        flushStoredResponses();
    }
}

//****************************************************************************

RWCString OZT_CmdSender::printState(const State theState)
{
    switch(theState)
    {
        case IDLE                   : return "IDLE";
        case LOGGING_ON             : return "LOGGING_ON";
        case WAIT_IMM_RSP           : return "WAIT_IMM_RSP";
        case WAIT_IMM_RSP_CONFIRMED : return "WAIT_IMM_RSP_CONFIRMED";
        case WAIT_DEL_RSP           : return "WAIT_DEL_RSP";
        case FUNBUSY_WAIT           : return "FUNBUSY_WAIT";
        case FUNBUSY_WAIT_CONFIRMED : return "FUNBUSY_WAIT_CONFIRMED";
        case CONFIRM_PENDING        : return "CONFIRM_PENDING";
        case CONNECTION_LOST        : return "CONNECTION_LOST";
        default: return "Unknown state";
    }
}

//****************************************************************************

OZT_Result OZT_CmdSender::sendCmd(const RWCString& currFileName,
                                  const RWCString& cmdText,
                                  RWBoolean markBuf)
{
    TRACE_IN(trace, sendCmd, currFileName << ", " << cmdText
             << ",at " << printState(senderState));
    if (cmdText.isNull())
    {
        TRACE_RETURN(trace, sendCmd, "NO_PROBLEM");
        return OZT_Result(OZT_Result::NO_PROBLEM);
    }
    OZT_Result result ;

    interruptPending = FALSE;

#ifdef OZT_PROTOTYPE
    //  if the command if not from a file, and if the user
    //  cancel the command, return

    if (currFileName.isNull() && (theDCConfirmFunc != 0)) {
        if (!((*theDCConfirmFunc)(cmdText))) {
            return OZT_Result(OZT_Result::INHIBIT);
        }
    }
#endif

    switch(senderState)
    {
        case IDLE :
            lastSentCmd = cmdText;

           //It's needed to flush the stored del. resp. since a stored del. resp.
           //will be interpreted as the result of the next del. resp. command.
           //A "System restart" will cause an unexpected del. resp.
           flushStoredResponses();

            //
            //  disable the acceptance of delayed response
            //
            changeState(LOGGING_ON);
            result = pRspReceiver->logOn();
            if (result.code != OZT_Result::NO_PROBLEM)
            {
                changeState(IDLE);
                clearScanStr();
                TRACE_RETURN(trace, sendCmd, result.filtered());
                return result.filtered();
            }

            if (markBuf)
                cmdRspBuf.markBeginOfRsp();

            if (!markBuf)
                cmdRspBuf.markSearchBackPoint();

            //
            //  send the command off
            //
          //  selectAuthProf(currFileName);
            result = actualSend(cmdText);

			// Check if we have no connectin, then we
			// should abort.
			if(result.code == OZT_Result::NO_CONNECTION)
			{
			   changeState(IDLE);
			   clearScanStr();
			   return result.filtered();
			}

            if (result.code != OZT_Result::NO_PROBLEM)
            {
                changeState(IDLE);
                clearScanStr();
            }
            else
            {
                //
                //  wait for the response to arrive
                //
                resetFunBusyCounter();
                decFunBusyCounter();
                changeState(WAIT_IMM_RSP);
                pCmdSender->checkIPC();

                CHA_CommandSender::CmdResult lastCmdResult = pCmdSender->getLastCmdResult();

                if (ozt_evHandlerPtr != NULL) {
                    if (lastCmdResult == CHA_CommandSender::EXECUTED) {
                        ozt_evHandlerPtr->setResult(  OZT_Result(OZT_Result::NO_PROBLEM));
                    }
                    else if(lastCmdResult == CHA_CommandSender::NOT_ACCEPTED) {
                        ozt_evHandlerPtr->setResult(  OZT_Result(OZT_Result::NOT_ACCEPTED));
                    }
                    else if(lastCmdResult == CHA_CommandSender::PARTLY_EXECUTED) {
                        ozt_evHandlerPtr->setResult(  OZT_Result(OZT_Result::PARTLY_EXECUTED));
                    }
                    else if(lastCmdResult == CHA_CommandSender::INCOMPLETE) {
                        ozt_evHandlerPtr->setResult(  OZT_Result(OZT_Result::INCOMPLETE_COMMAND));
                    }
                    else if(lastCmdResult == CHA_CommandSender::FUNCTION_BUSY) {
                        ozt_evHandlerPtr->setResult(  OZT_Result(OZT_Result::FUNBUSY));
                    }
                    else {
                        ozt_evHandlerPtr->setResult(  OZT_Result(OZT_Result::NOT_AUTHORIZED));
                    }

                    result = ozt_evHandlerPtr->waitResult();
                    checkReply(cmdText, result);
                }  
                //
                //  If this is not sent by @SEND, set the search back point
                //  so that @WAITFOR, @WAITREPLY do not search beyond this
                //  point.
                //

                if (markBuf) {
                    cmdRspBuf.markSearchBackPoint();
                    if (pConnection != NULL) {
                        if (pConnection->isRespEnded() == true) {
                            cmdRspBuf.markEndOfRsp();
                        }
                    }
                    cmdRspBuf.updateStore();
                }
            }

            //  Log the error if @Z is on
            if (ZFlag && (result.code != OZT_Result::NO_PROBLEM))
                storeZError(cmdText, result);

            TRACE_RETURN(trace, sendCmd, result.filtered());
            return result.filtered();

        case CONFIRM_PENDING :
            result = maidenConfirm(cmdText);
            TRACE_RETURN(trace, sendCmd, result);
            return result;

        default:
            lastSentCmd = RWCString();
            clearScanStr();
            TRACE_RETURN(trace, sendCmd, "INTERNAL_ERR (wrong state)");
            return OZT_Result(OZT_Result::INTERNAL_ERR);
    }
}


//**************************************************************************

void OZT_CmdSender::selectAuthProf(const RWCString& fileName)
{
    TRACE_IN(trace, selectAuthProf, fileName);

    static RWCString  lastFileUsed = RWCString();

    // If the file name used is different this time, select a new profile
    if (fileName != lastFileUsed)
    {
        lastFileUsed = fileName;

        if (fileName.isNull())
            pConnection->useDefaultAuthority();
        else
        {
            TRACE_FLOW(trace, selectAuthProf, "selecting user for auth check");

            RWCString userName = ozt_info.getUsrForAuthCheck(fileName);

            TRACE_FLOW(trace, selectAuthProf, "user to be used :" << userName);
            //
            //  if the user name to be used is different, switch to the new user
            //
            if (pConnection->authorityUsed() != userName)
            {
                TRACE_FLOW(trace, selectAuthProf,
                           "User used is different, switch to " << userName);

                if (pConnection->useAuthorityOf(userName)
                    != CHA_Connection::OKAY)
                {
                    TRACE_FLOW(trace, selectAuthProf,
                               "Cannot switch, go back to default profile");
                    //
                    //  if it is impossible to switch to the new user,
                    //  step back to use the default authority.
                    //
                    pConnection->useDefaultAuthority();  // if this fails too?
                }
            }
        }
    }

    TRACE_OUT(trace, selectAuthProf, "");
}

//**************************************************************************

OZT_Result OZT_CmdSender::actualSend(const RWCString& cmdText)
{
    TRACE_IN(trace, actualSend, cmdText);
    RWCString prompt;
    //
    //  send the command
    //
    if (pPromptString != NULL) {
        if( pPromptString->getPrompt() == "<" || pPromptString->getPrompt() == "cpt<" )
            prompt = pPromptString->getPrompt();
        else
            prompt = "";
    }
 
    switch(pCmdSender->sendCommand(cmdText,prompt))
    {
        case CHA_CommandSender::OKAY   :
            TRACE_RETURN(trace, actualSend, "NO_PROBLEM");
            return OZT_Result(OZT_Result::NO_PROBLEM);

        case CHA_CommandSender::BUSY   :
            TRACE_RETURN(trace, actualSend, "BUSY");
            return OZT_Result(OZT_Result::BUSY);

        case CHA_CommandSender::FAILED :
            TRACE_RETURN(trace, actualSend, "FAILED");
            return OZT_Result(OZT_Result::FAILED);

        case CHA_CommandSender::NOCONNECTION :
            TRACE_RETURN(trace, actualSend, "NOCONNECTION");
            return OZT_Result(OZT_Result::NO_CONNECTION);

        case CHA_CommandSender::DISCON_FAILED :
            TRACE_RETURN(trace, actualSend, "DISCON_FAILED");
            return OZT_Result(OZT_Result::ES_FAILED_DISCON);

        default:
            TRACE_RETURN(trace, actualSend, "INTERNAL_ERR");
            return OZT_Result(OZT_Result::INTERNAL_ERR);
    }
}

//**************************************************************************

void OZT_CmdSender::useStrictDeviceMode()
{
    useDeviceMode = TRUE;
}

//**************************************************************************

void OZT_CmdSender::useNonStrictDeviceMode()
{
    useDeviceMode = FALSE;
}

//**************************************************************************

OZT_Result OZT_CmdSender::connect(const RWCString& neName)
{
    TRACE_IN(trace, connect, neName);

    time_t td = time(0);

    OZT_Result result;

    /*RWCRegexp re("^[ \t]*[Nn][Ee][ \t]*=[ \t]*.*,[ \t]*[Nn][Oo][Dd][Ee][ \t]*=[ \t]*[AaBb]");

    //  Workaround for fixing the comment window TR ***
    // 750 does not fix it...
    // 1000 is close to fix it...
    // Let's make it 1500!
    // Is the CPU performance of any importance?
    // However, it seems that the X load is of importance,
    // so the higher the value the better.
     This fix destroys the client-server solution. Remove it. ehsanah 
    for (int counter = 0; counter < 2500; counter++)
    {
        ozt_evHandlerPtr->dispatchEvents();
    }
   */
    // Disconnect first if we are already connected.  This also
    // print a message in the response window.
   int  status = pConnection->getConnectionStatus();
   if (pConnection->getConnectionStatus() != -1 )////TORF-241666 == EAC_CRI_CS_CONNECTED)
    {
      //if (neName != pConnection->getEsName())
      //{
      	pConnection->disconnect();
      //}
    }
    //EAM can't handle tab or " " as ne name.
    RWTRegex<char> notVisible("^[ \t]*$");
    RWTRegex<char> neNotVisible("^[ \t]*[Nn][Ee][ \t]*[=][ \t]*$");
    if (notVisible.index(neName) != RW_NPOS || neNotVisible.index(neName) != RW_NPOS  ){
    	TRACE_FLOW(trace, connect, "neName is empty!");
     	return OZT_Result(OZT_Result::ES_UNKNOWN);
   }

	// Let's connect then...
    switch(pConnection->connect(neName))
    {
        case CHA_Connection::OKAY :
	     // The prompt srting chould work fine now.
         // Reset prompt on new connection (TPF 4 only; it works OK for TPF 2)
	     //#if TPF >= 400
	     //	    pPromptString->setPrompt(RWCString());
	     //#endif
            // Read extra strings defining failures (Only TPF 2 really...)
            // TPF 4.1 will support this directly
        	extraFailStrings.clear();
            ozt_info.getAdditionalFailStrings(extraFailStrings);
    	    TRACE_FLOW(trace, connect, "read " << extraFailStrings.entries() << " additional fail strings");

    	    cslExemptionsStrings.clear();
            ozt_info.getCslExemptionCommands(cslExemptionsStrings);
    	    TRACE_FLOW(trace, connect, "read " << cslExemptionsStrings.entries() << " csl exemption strings");

            if(useDeviceMode)
            {
                pCmdSender->getDevModePropsObject()->setModeOn(25200);
            }
            else
            {
                pCmdSender->getDevModePropsObject()->setModeOff(25200);
            }

	    // Added due to improvement to avoid hanging problem
	    // Get timer value for conn_idle_to
	    connIdleToTimerValue = pConnection->getEsExtInfo();
	    TRACE_FLOW(trace, connect, "connIdleToTimerValue = " << connIdleToTimerValue);

	    // Write information to the log file /tmp/opsserver.log

	    setConnectionMode(neName);
            result = OZT_Result(OZT_Result::NO_PROBLEM);
            break;

        case CHA_Connection::ES_INVALID_NEID :
            result = OZT_Result(OZT_Result::INVALID_NODE_ID);
            break;

        case CHA_Connection::ES_INVALID_SESSIONID :
            result = OZT_Result(OZT_Result::INVALID_SESSIONID_VAL);
            break;

        case CHA_Connection::ES_INVALID_ENMUID :
            result = OZT_Result(OZT_Result::INVALID_ENMUID_VAL);
            break;

        case CHA_Connection::ES_COULD_NOT_CONNECT_TO_ES :
            result = OZT_Result(OZT_Result::ES_NOREACH);
            break;

       /* case CHA_Connection::ES_FAILED_DISCON :
            result = OZT_Result(OZT_Result::ES_FAILED_DISCON);
            break;

        case CHA_Connection::ES_NOREACH :
            result = OZT_Result(OZT_Result::ES_NOREACH);
            break;

        case CHA_Connection::ES_UNKNOWN :
            result = OZT_Result(OZT_Result::ES_UNKNOWN);
            break;

        case CHA_Connection::ES_IS_EXCLUSIVE :
            result = OZT_Result(OZT_Result::ES_IS_EXCLUSIVE);
            break;

        case CHA_Connection::ES_NOAUTH :
            result = OZT_Result(OZT_Result::ES_NOAUTH);
            break;*/

        case CHA_Connection::ES_FAILED_CON :
            result = OZT_Result(OZT_Result::ES_FAILED_CON);
            break;

        case CHA_Connection::ES_INCORRECT_SIDE :
            result = OZT_Result(OZT_Result::SIDE_INCORRECT);
            break;

        case CHA_Connection::ES_INCORRECT_CP :
            result = OZT_Result(OZT_Result::CP_INCORRECT);
            break;

        case CHA_Connection::ES_SIDE_NOT_ALLOWED :
            result = OZT_Result(OZT_Result::NOT_ALLOWED_SIDE);
            break;

        case CHA_Connection::ES_UNREASONABLE_VALUE :
            result = OZT_Result(OZT_Result::VALUE_UNREASONABLE);
            break;

	default:
            TRACE_RETURN(trace, connect, "INTERNAL_ERR");
            return OZT_Result(OZT_Result::INTERNAL_ERR);
    }


    TRACE_FLOW(trace, connect, result);
    TRACE_RETURN(trace, connect, result.filtered());
    return result.filtered();

}


//**************************************************************************


void OZT_CmdSender::setSmoUser(const char* smoUser)
{
    TRACE_IN(trace, setSmoUser, "");

    pConnection->setSmoUser(smoUser);
}


//**************************************************************************


OZT_Result OZT_CmdSender::disconnect()
{
    TRACE_IN(trace, disconnect, "");

    clearScanStr();
    switch(pConnection->disconnect())
    {
        case CHA_Connection::OKAY :
            TRACE_RETURN(trace, disconnect, "NO_PROBLEM");
            return OZT_Result(OZT_Result::NO_PROBLEM);

        case CHA_Connection::ES_FAILED_DISCON :
            TRACE_RETURN(trace, disconnect, "ES_FAILED_DISCON");
            return OZT_Result(OZT_Result::ES_FAILED_DISCON);

        default:
            TRACE_RETURN(trace, disconnect, "INTERNAL_ERR");
            return OZT_Result(OZT_Result::INTERNAL_ERR);
    }
}


//**************************************************************************


RWCString OZT_CmdSender::getEsName() const
{
    if (pConnection->getConnectionStatus() != -1) /* == EAC_CRI_CS_CONNECTED*/
{
        return pConnection->getEsName();
}
    else
{
        return RWCString();
}
}


//**************************************************************************


RWCString OZT_CmdSender::getEsType() const
{
	if (pConnection->getConnectionStatus()!= -1) /*== EAC_CRI_CS_CONNECTED*/
{
        return pConnection->getEsType();
}
    else
{
        return RWCString();
}
}

//**************************************************************************

void OZT_CmdSender::setOKReply(const RWCString& str)
{
    okReply = str;
}

//**************************************************************************

void OZT_CmdSender::setFailReply(const RWCString& str)
{
    failReply = str;
}

//**************************************************************************

void OZT_CmdSender::checkReply(const RWCString& cmdText, OZT_Result& result)
{
     TRACE_IN(trace, checkReply, result);
    //
    //  Check if the response contains one of the additional fail strings
    //
    cmdRspBuf.scanForFailStrings(extraFailStrings, result, funBusyCounter);

    // HE87081 & HE93921

    TRACE_FLOW(trace, checkReply, "EXTRA FAIL STRINGS");

	for (int i = 0; i < extraFailStrings.entries(); i++)
    {
    	TRACE_FLOW(trace, checkReply, i << " : " << extraFailStrings[i]);
    }

    cmdRspBuf.scanForFailStrings(extraFailStrings, result, funBusyCounter);

    	/*
        for (i = 0; i < extraFailStrings.entries(); i++)
        {
        	// HD81566 Only scan the last reply, otherwise will the @SEND
        	//         command set the error flag if there are earlier errors
        	//	   in the buffer.
            if (cmdRspBuf.scanLastReply(extraFailStrings[i]) != 0)
            {
                result = OZT_Result(OZT_Result::REPLY_CHECK_FAIL,
                                    extraFailStrings[i]);
                break;
            }
        }
        */
    // END HE87081 & HE93921



    //
    //  Toggle the result for the presence of the OK or FAIL string
    //
    if (result.code == OZT_Result::NO_PROBLEM)
    {
        if ((!failReply.isNull()) && (cmdRspBuf.scan(failReply) != 0))
            result = OZT_Result(OZT_Result::REPLY_CHECK_FAIL, failReply);
    }
    else
    {
        if ((!okReply.isNull()) && (cmdRspBuf.scan(okReply) != 0))
            result = OZT_Result(OZT_Result::NO_PROBLEM);
    }

    //
    //  Checking of strings set up by @/w1,...,wn/
    //
    if (result.code == OZT_Result::NO_PROBLEM)
    {
        RWCString failStr;

        if (!mScan(failStr))
        {
            cmdRspBuf.append(RWCString("*** RESPONSE TEST FAILED WITH STRING: ")
                             + failStr + RWCString(" ***\n"));
            if (!RFlag)
                result = OZT_Result(OZT_Result::REPLY_CHECK_FAIL, failStr);
        }
    }
    TRACE_OUT(trace, checkReply, result);
}

//**************************************************************************

void OZT_CmdSender::orderOn()
{
    TRACE_FLOW(trace, orderOn, "");
    //orderedOn = TRUE;
    pConnection->getConnection()->orderedOn();
    // Added due to DEL RSP problem
    CHA_SeqDelRespReceiver::updateOrderState(1);
}

//**************************************************************************

void OZT_CmdSender::orderOff()
{
    TRACE_FLOW(trace, orderOff, "");
    //orderedOn = FALSE;
    pConnection->getConnection()->orderedOff();
    // Added due to DEL RSP problem
    CHA_SeqDelRespReceiver::updateOrderState(0);
}

//**************************************************************************

void OZT_CmdSender::reportOn()
{
    TRACE_FLOW(trace, reportOn, "");
    reportIsOn = TRUE;
}

//**************************************************************************

void OZT_CmdSender::reportOff()
{
    TRACE_FLOW(trace, reportOff, "");
    reportIsOn = FALSE;
}

//**************************************************************************

void OZT_CmdSender::setAutoConfirm(const RWBoolean mode)
{
    TRACE_IN(trace, setAutoConfirm, mode);
    pCmdSender->setAutoConfirm(mode);
    TRACE_OUT(trace, setAutoConfirm, "");
}

//**************************************************************************

RWCString OZT_CmdSender::confirmStr() const
{
    if (getEsType() == "AXE")
        return ";";
    else
        return ";"; // no idea
}

//**************************************************************************


OZT_Result OZT_CmdSender::maidenConfirm(const RWCString& theConfirmStr)
{
    TRACE_IN(trace, maidenConfirm, theConfirmStr);

    OZT_Result result;

    if (theConfirmStr != confirmStr())
    {
        (void)pCmdSender->confirmCommand(FALSE);
        changeState(IDLE);
        clearScanStr();
        TRACE_RETURN(trace, maidenConfirm, "INHIBIT");
        return OZT_Result(OZT_Result::INHIBIT);
    }
    if (pCmdSender->confirmCommand(TRUE) != CHA_CommandSender::OKAY)
    {
        changeState(IDLE);
        clearScanStr();
        TRACE_RETURN(trace, maidenConfirm, "CONFIRM_FAIL");
        return OZT_Result(OZT_Result::CONFIRM_FAIL);
    }

    changeState(WAIT_IMM_RSP_CONFIRMED);
    // Now ";" is displayed when confirmation is required.
    cmdRspBuf.append(RWCString(";"));
    result = ozt_evHandlerPtr->waitResult();
    checkReply(lastSentCmd, result);
    cmdRspBuf.markSearchBackPoint();
    if (ZFlag && (result.code != OZT_Result::NO_PROBLEM))
        storeZError(lastSentCmd, result);

    TRACE_RETURN(trace, maidenConfirm, result.filtered());
    return result.filtered();
}


//*****************************************************************************

#if TPF >= 400
void OZT_CmdSender::updateFrom(CHA_Model* pModel, void*)
#else
void OZT_CmdSender::updateFrom(RWModel* pModel, void*)
#endif
{
    TRACE_IN(trace, updateFrom, "");

    if ((CHA_CommandSender*)pModel == pCmdSender)
    {
        updateFromCmdSender();
    }
    else if ((CHA_ResponseReceiver*)pModel == pDelReceiver)
    {
        updateFromDelReceiver();
    }

    TRACE_OUT(trace, updateFrom, "");
}

//*****************************************************************************

void OZT_CmdSender::detachFrom(CHA_Model* pModel)
{
    if ((CHA_CommandSender*)pModel == pCmdSender)
    {
        TRACE_FLOW(trace, detachFrom, "pCmdSender");
        return;
    }

    if ((CHA_ResponseReceiver*)pModel == pDelReceiver)
    {
        TRACE_FLOW(trace, detachFrom, "pDelReceiver");
        return;
    }
}

//*****************************************************************************

const char* OZT_CmdSender::chaCommandSenderStateToString(CHA_CommandSender::State state)
{
    switch(state)
    {
    case CHA_CommandSender::NOTCON:
    	return "NOTCON";
    case CHA_CommandSender::IDLE:
    	return "IDLE";
    case CHA_CommandSender::WAITING:
    	return "WAITING";
    case CHA_CommandSender::CONFIRM:
    	return "CONFIRM";
    case CHA_CommandSender::RECEIVING:
    	return "RECEIVING";
    default:
    	return "UNKNOWN";
    }
}

const char* OZT_CmdSender::chaCommandSenderCmdResultToString(CHA_CommandSender::CmdResult cmdResult)
{
    switch(cmdResult)
    {
    case CHA_CommandSender::EXECUTED:
    	return "EXECUTED";
    case CHA_CommandSender::UNKNOWN:
    	return "UNKNOWN";
    case CHA_CommandSender::ORDERED:
    	return "ORDERED";
    case CHA_CommandSender::NOT_ACCEPTED:
    	return "NOT_ACCEPTED";
    case CHA_CommandSender::NOT_AUTHORIZED:
    	return "NOT_AUTHORIZED";
    case CHA_CommandSender::PARTLY_EXECUTED:
    	return "PARTLY_EXECUTED";
    case CHA_CommandSender::INCOMPLETE:
    	return "INCOMPLETE";
    case CHA_CommandSender::FUNCTION_BUSY:
    	return "FUNCTION_BUSY";
    default:
    	return "UNKNOWN";
    }
}

const char* OZT_CmdSender::stateToString(State state)
{
    switch(state)
    {
    case IDLE:
    	return "IDLE";
    case CONNECTION_LOST:
    	return "CONNECTION_LOST";
    case CONFIRM_PENDING:
    	return "CONFIRM_PENDING";
    case LOGGING_ON:
    	return "LOGGING_ON";
    case WAIT_IMM_RSP:
    	return "WAIT_IMM_RSP";
    case WAIT_DEL_RSP:
    	return "WAIT_DEL_RSP";
    case FUNBUSY_WAIT:
    	return "FUNBUSY_WAIT";
    case WAIT_IMM_RSP_CONFIRMED:
    	return "WAIT_IMM_RSP_CONFIRMED";
    case FUNBUSY_WAIT_CONFIRMED:
    	return "FUNBUSY_WAIT_CONFIRMED";
    default:
    	return "UNKNOWN";
    }
}

RWBoolean OZT_CmdSender::isClusterLockResponse()
{

    TRACE_IN(trace, isClusterLockResponse, "");

	size_t dontCare;

	size_t storeSizeT = (size_t) cmdRspBuf.getStoreSize();
	size_t searchStartPos = storeSizeT >= 3 ? storeSizeT - 3 : 0;
	TRACE_FLOW( trace, isClusterLockResponse, "Search starts from line " << searchStartPos );

	size_t pos1 = cmdRspBuf.scan("SESSION LOCKED DURING", searchStartPos, dontCare);
//	size_t pos1 = cmdRspBuf.scan("REMAINING LOCK TIME", searchStartPos, dontCare);
	size_t pos2 = cmdRspBuf.scan("YOU MAY NOW ENTER: APLOC, PTCOI, PTCOE OR EXIT COMMAND", searchStartPos, dontCare);

	RWBoolean result;

	// scan returns 0 when not found :(
	if( ( pos1 == 0 ) || ( pos2 == 0 ) )
	{
		TRACE_FLOW( trace, isClusterLockResponse, "SESSION LOCK printout not found in buffer");
		result = FALSE;
	}
	else if( (pos2 == pos1 + 1) || (pos2 == pos1 + 2) )
	{
		TRACE_FLOW( trace, isClusterLockResponse, "SESSION LOCK printout found in buffer at lines " << pos1 << " and " << pos2 );
		result = TRUE;
	}
	else
	{
		TRACE_FLOW( trace, isClusterLockResponse, "SESSION LOCK printout not found in buffer");
		result = FALSE;
	}

    TRACE_OUT(trace, isClusterLockResponse, "return " << ( result ? "TRUE" : "FALSE" ));
    return result;
}

RWBoolean OZT_CmdSender::isCommandCslExemption()
{
    TRACE_IN(trace, isCommandCslExemption, lastSentCmd);

    RWBoolean foundInList = false;
    int i = 0;

    while(!foundInList && i < cslExemptionsStrings.entries())
    {
    	foundInList = ( !cslExemptionsStrings[i].compareTo(lastSentCmd,RWCString::ignoreCase) );
    	i++;
    }

    TRACE_OUT(trace, isCommandCslExemption, foundInList);
    return foundInList;
}

void OZT_CmdSender::appendToBuffer(const RWCString& text)
{
	cmdRspBuf.append(text);
}

void OZT_CmdSender::appendCslFuncBusyToBuffer()
{
	appendToBuffer(RWCString("NOT ACCEPTED\n"));
	appendToBuffer(RWCString("FUNCTION BUSY - SESSION LOCKED\n"));
}

void OZT_CmdSender::updateFromCmdSender()
{
    TRACE_IN(trace, updateFromCmdSender, "");

    TRACE_FLOW( trace, updateFromCmdSender, "OZT senderState = " << stateToString(senderState));

    CHA_CommandSender::State pCmdSenderState = pCmdSender->getState();
    TRACE_FLOW( trace, updateFromCmdSender, "CHA senderState = " << chaCommandSenderStateToString(pCmdSenderState));

    CHA_CommandSender::CmdResult lastCmdResult = pCmdSender->getLastCmdResult();
    TRACE_FLOW( trace, updateFromCmdSender, "CHA lastCmdResult = " << chaCommandSenderCmdResultToString(lastCmdResult));

    CHA_PromptString* prompt = pCmdSender->getPromptObject();
    TRACE_FLOW( trace, updateFromCmdSender, "Current prompt is " << prompt->getPrompt());

    switch(pCmdSenderState)
    {
        case CHA_CommandSender::CONFIRM :
            confirmReqEvent();
            break;

        case CHA_CommandSender::IDLE :
            if ((senderState != WAIT_IMM_RSP) &&
                (senderState != WAIT_IMM_RSP_CONFIRMED))
            {
                // not waiting for immediate rsp, so finish.
                TRACE_OUT(trace, updateFromCmdSender,"Not waiting for imm rsp");
                return;
            }


            switch(lastCmdResult)
            {
                case CHA_CommandSender::EXECUTED :

                    if(isClusterLockResponse())
                	{
                		TRACE_FLOW(trace, updateFromCmdSender, "Response is CSL");
                    	if(isCommandCslExemption())
                    	{
                    		TRACE_FLOW(trace, updateFromCmdSender, "Command is " << lastSentCmd << ", CSL is ignored");
                    ozt_evHandlerPtr->setResult(
                                                OZT_Result(OZT_Result::NO_PROBLEM));
                    changeState(IDLE);
                    	}
                    	else
                    	{
                    		appendCslFuncBusyToBuffer();
                    		funBusyEvent();
                    	}
                	}
                	else
                	{
						TRACE_FLOW(trace, updateFromCmdSender, "Response is not CSL");
						ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::NO_PROBLEM));
						changeState(IDLE);
                	}
                    break;
                case CHA_CommandSender::UNKNOWN :
                    ozt_evHandlerPtr->setResult(
                                                OZT_Result(OZT_Result::SEND_FAILED));
                    changeState(IDLE);
                    break;

                case CHA_CommandSender::ORDERED :
                    orderedEvent();
                    break;

                case CHA_CommandSender::NOT_ACCEPTED :
                    ozt_evHandlerPtr->setResult(
                                                OZT_Result(OZT_Result::NOT_ACCEPTED));
                    changeState(IDLE);
                    break;

                case CHA_CommandSender::NOT_AUTHORIZED :
                    ozt_evHandlerPtr->setResult(
                                                OZT_Result(OZT_Result::NOT_AUTHORIZED));
                    changeState(IDLE);
                    break;

                case CHA_CommandSender::PARTLY_EXECUTED :
                    ozt_evHandlerPtr->setResult(
                                                OZT_Result(OZT_Result::PARTLY_EXECUTED));
                    changeState(IDLE);
                    break;

                case CHA_CommandSender::INCOMPLETE :
                    ozt_evHandlerPtr->setResult(
                                                OZT_Result(OZT_Result::INCOMPLETE_COMMAND));
                    changeState(IDLE);
                    break;

                case CHA_CommandSender::FUNCTION_BUSY :
                    funBusyEvent();
                    break;

                default:
                    ozt_evHandlerPtr->setResult(
                                                OZT_Result(OZT_Result::INTERNAL_ERR,
                                                           "Unknown return code from CHALIB command sender"));
                    changeState(IDLE);
                    break;
            }
            break;

        case CHA_CommandSender::NOTCON :
            loseConnectionEvent();
            break;

        default: break;
    }

    TRACE_OUT(trace, updateFromCmdSender, "");
}


//*****************************************************************************

void OZT_CmdSender::updateFromDelReceiver()
{
    TRACE_IN(trace, updateFromDelReceiver, "");

    switch(senderState)
    {
        case WAIT_DEL_RSP :
            if (pDelReceiver->isCompleteResponse())
            {
                if (!reportIsOn && !(pDelReceiver->isLastInSequence()))
                {
                    TRACE_OUT(trace, updateFromDelReceiver,
                              "@report is OFF and not LAST REPORT, nothing happen");
                    return;
                }
                ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::NO_PROBLEM));
                changeState(IDLE);
                TRACE_OUT(trace, updateFromDelReceiver,
                          "delayed rsp complete, unBlock.");
                return;
            }
            break;

        default :
            break;
    }
    TRACE_OUT(trace, updateFromDelReceiver, "");
}


//*****************************************************************************

void OZT_CmdSender::confirmReqEvent()
{
    TRACE_IN(trace, confirmReqEvent, "at " << printState(senderState));

    switch(senderState)
    {
        case WAIT_IMM_RSP :
            //
            //  If autoconfirm, confirm. Otherwise, change state.
            //
            if (autoConfirm)
                confirmCmd();
            else
            {
                ozt_evHandlerPtr->setResult(
                                            OZT_Result(OZT_Result::NO_PROBLEM));
                changeState(CONFIRM_PENDING);
            }
            break;

        case WAIT_IMM_RSP_CONFIRMED :
            confirmCmd();
            break;

        default:
            TRACE_FLOW(trace, confirmReqEvent,
                       "confirm requested from NE at an unexpected state");
            break;
    }

    TRACE_OUT(trace, confirmReqEvent, "");
}


//*****************************************************************************

void OZT_CmdSender::confirmCmd()
{
    TRACE_IN(trace, confirmCmd, "");

    if (pCmdSender->confirmCommand(TRUE) != CHA_CommandSender::OKAY)
    {
        ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::CONFIRM_FAIL));
        changeState(IDLE);
        TRACE_OUT(trace, confirmCmd, "fails, unBlock!");
        return;
    }
    else
    {
        TRACE_OUT(trace, confirmCmd, "done.");
        return;
    }
}


//*****************************************************************************

void OZT_CmdSender::orderedEvent()
{
    TRACE_IN(trace, orderedEvent, "at " << printState(senderState));

    switch(senderState)
    {
        case WAIT_IMM_RSP :
        case WAIT_IMM_RSP_CONFIRMED :
            //
            //  For S12
            //
            if (getEsType() == "S12")
            {
                if (!reportIsOn)
                {
                    pRspReceiver->logOff(); // logoff, let the del rsp come thr'
                    if (cmdRspBuf.isRspEnded() &&
                        (cmdRspBuf.scan("LAST REPORT") != 0))
                    {
                        TRACE_FLOW(trace, orderedEvent,
                               "S12 del res already arrived, go to idle");
                        ozt_evHandlerPtr->setResult(
                                           OZT_Result(OZT_Result::NO_PROBLEM));
                        changeState(IDLE);
                    }
                    else
                    {
                        TRACE_FLOW(trace, orderedEvent,
                               "logoff, wait for S12 del rsp");
                        changeState(WAIT_DEL_RSP);
                    }
                }
                else
                {
                    TRACE_FLOW(trace, orderedEvent,
                           "@report(ON), no need to wait for del rsp");
                    ozt_evHandlerPtr->setResult(
                                        OZT_Result(OZT_Result::NO_PROBLEM));
                    changeState(IDLE);
                }

                break;
            }

              //
            // For AXE
            //
            TRACE_FLOW(trace, orderedEvent, "orderedOn = " << orderedOn);
            if (orderedOn)
            {
            	//All stored del. resp. needs to be flushed before the command
            	//is sent if this should work.
                //The flushing should be done in the method sendCmd().
                RWBoolean lastLogOffFlushedDelResp = pRspReceiver->logOff();

                if (lastLogOffFlushedDelResp && cmdRspBuf.isRspEnded())
                {
                     TRACE_FLOW(trace, orderedEvent, "Del res flushed by logOff set state idle");
                     ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::NO_PROBLEM));
                     changeState(IDLE);
                }
                else
                {
                     TRACE_FLOW(trace, orderedEvent, "wait for del rsp");
                     changeState(WAIT_DEL_RSP);
                }
            }
            else
            {
                TRACE_FLOW(trace, orderedEvent, "orderedOff, IDLE");
                ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::NO_PROBLEM));
                changeState(IDLE);
            }
            break;

        default:
            TRACE_FLOW(trace, orderedEvent, "unexpected state!!");
            break;
    }

    TRACE_OUT(trace, orderedEvent, "");
}


//*****************************************************************************

void OZT_CmdSender::funBusyEvent()
{
    TRACE_IN(trace, funBusyEvent, senderState);

    switch(senderState)
    {
        case WAIT_IMM_RSP:
            if (!moreFunBusyRetry())
            {
                TRACE_FLOW(trace, funBusyEvent, "no more retry, unblocks");
                ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::FUNBUSY));
                changeState(IDLE);
            }
            else
            {
                TRACE_FLOW(trace, funBusyEvent, "more retry, set timer");
                decFunBusyCounter();
                sleep(funBusyInterval);
                changeState(FUNBUSY_WAIT);
                timeOut();
                pCmdSender->checkIPC();
            }
            break;

        case WAIT_IMM_RSP_CONFIRMED:
            if (!moreFunBusyRetry())
            {
                TRACE_FLOW(trace, funBusyEvent, "no more retry, unblocks");
                ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::FUNBUSY));
                changeState(IDLE);
            }
            else
            {
                TRACE_FLOW(trace, funBusyEvent, "more retry, set timer");
                decFunBusyCounter();
                sleep(funBusyInterval);
                changeState(FUNBUSY_WAIT);
                timeOut();
                pCmdSender->checkIPC();
            }
            break;

        default:
            TRACE_FLOW(trace, funBusyEvent, "unexpected state!!");
            break;
    }
    TRACE_OUT(trace, funBusyEvent, "");
}


//*****************************************************************************

void OZT_CmdSender::loseConnectionEvent()
{
    TRACE_IN(trace, loseConnectionEvent, "at " << printState(senderState));

    switch(senderState)
    {
        case IDLE:
	  changeState(CONNECTION_LOST);
	  break;

        case LOGGING_ON:
            // far too complicated to change to IDLE here. Let the logon
            // finish, then when a cmd is sent, NO_CONNECTION will be
            // detected anyway.
            break;

        case CONFIRM_PENDING:
	  changeState(CONNECTION_LOST);
	  break;

        case WAIT_DEL_RSP:
        case WAIT_IMM_RSP:
        case WAIT_IMM_RSP_CONFIRMED:
            ozt_evHandlerPtr->setResult(
                                       OZT_Result(OZT_Result::CONNECTION_LOST));
	    changeState(CONNECTION_LOST);
            break;

        case FUNBUSY_WAIT:
        case FUNBUSY_WAIT_CONFIRMED:
            ozt_evHandlerPtr->unsetTimer((void*)this);
            ozt_evHandlerPtr->setResult(
                                        OZT_Result(OZT_Result::CONNECTION_LOST));
	    changeState(CONNECTION_LOST);
            break;
        case CONNECTION_LOST:
	  break;
    }
    //notify all clients thast the connection is lost

    TRACE_OUT(trace, loseConnectionEvent, "");
}

//*****************************************************************************
void OZT_CmdSender::setIdle(){
  changeState(IDLE);
}
//*****************************************************************************

void OZT_CmdSender::timeOut()
{
    TRACE_IN(trace, timeOut, "at " << printState(senderState));

    OZT_Result result;

    switch(senderState)
    {
        case FUNBUSY_WAIT:
            result = actualSend(lastSentCmd);
            if (result.code != OZT_Result::NO_PROBLEM)
            {
                ozt_evHandlerPtr->setResult(result);
                TRACE_OUT(trace, timeOut, "resent last cmd fails");
                changeState(IDLE);
                break;
            }
            changeState(WAIT_IMM_RSP);
            break;

        case FUNBUSY_WAIT_CONFIRMED:
            result = actualSend(lastSentCmd);
            if (result.code != OZT_Result::NO_PROBLEM)
            {
                ozt_evHandlerPtr->setResult(result);
                TRACE_OUT(trace, timeOut, "resent last cmd fails");
                changeState(IDLE);
                break;
            }
            changeState(WAIT_IMM_RSP_CONFIRMED);
            break;

        default:
            TRACE_OUT(trace, timeOut, "at irrelevant state");
            break;
    }
    TRACE_OUT(trace, timeOut, "");
}

//*****************************************************************************

OZT_Result  OZT_CmdSender::setFunBusyParam(const OZT_Value& retry,
                                           const OZT_Value& interval)
{
    TRACE_FLOW(trace, setFunBusyParam, retry << ", " << interval);

    OZT_Result result;
    long retryVal, intervalVal;

    //
    //  convert to long
    //
    retryVal = retry.toLong(result);
    if ((result.code != OZT_Result::NO_PROBLEM) || (retryVal < 0))
        return OZT_Result(OZT_Result::INVALID_VALUE);

    intervalVal = interval.toLong(result);
    if ((result.code != OZT_Result::NO_PROBLEM) || (intervalVal < 0))
        return OZT_Result(OZT_Result::INVALID_VALUE);

    if (retryVal == 0)
    {
        // reset to the default value
        funBusyAttempts  = defaultFBAttempts;
        funBusyInterval  = defaultFBInterval;
    }
    else
        funBusyAttempts = retryVal;

    if (intervalVal == 0)        // adjust the boundary case
        intervalVal = 1;

    funBusyCounter = funBusyAttempts;
    funBusyInterval = intervalVal;

    return OZT_Result(OZT_Result::NO_PROBLEM);
}

//*****************************************************************************

void  OZT_CmdSender::resetFunBusyCounter()
{
    TRACE_FLOW(trace, resetFunBusyCounter, "");
    funBusyCounter = funBusyAttempts;
}

//*****************************************************************************

void  OZT_CmdSender::decFunBusyCounter()
{
    TRACE_FLOW(trace, decFunBusyCounter, "");
    funBusyCounter--;
}

//*****************************************************************************

RWBoolean  OZT_CmdSender::moreFunBusyRetry() const
{
    return funBusyCounter > 0;
}

//*****************************************************************************

void OZT_CmdSender::interrupt()
{
   TRACE_IN(trace, interrupt, "at " << printState(senderState));

    switch(senderState)
    {
        case LOGGING_ON :
            pRspReceiver->interrupt();
            break;

        case WAIT_IMM_RSP :
        case WAIT_IMM_RSP_CONFIRMED :
            if (interruptPending)
            {
	      TRACE_FLOW(trace, interrupt, "if (interruptPending)");
                //
                // here, a disconnect and reconnect is tried in order to
                // give the user back the control
                //
	          if (!clientQuitFlag)
		    {
		      pImmReceiver->cancelResponse();
		      pConnection->disconnect(FALSE);
		      pConnection->reconnect(FALSE);
		    }

                ozt_evHandlerPtr->setResult(OZT_Result::INTERRUPTED);
		changeState(IDLE);
            }
            else
            {
	        TRACE_FLOW(trace, interrupt, "else")
                pImmReceiver->cancelResponse();
                interruptPending = TRUE;
            }

	    break;
        case WAIT_DEL_RSP :
            pDelReceiver->cancelResponse();
            ozt_evHandlerPtr->setResult(OZT_Result::NO_PROBLEM);
	    //ozt_evHandlerPtr->setResult(OZT_Result::DELAY_RESPONSE_NOT_RECEIVED);
            changeState(IDLE);
            break;

        case FUNBUSY_WAIT :
        case FUNBUSY_WAIT_CONFIRMED :
            ozt_evHandlerPtr->unsetTimer((void*)this);
            ozt_evHandlerPtr->setResult(OZT_Result::INTERRUPTED);
            changeState(IDLE);
            break;

        case CONFIRM_PENDING :
            (void)pCmdSender->confirmCommand(FALSE);
            changeState(IDLE);
            break;

        default :
            break;
    }

    TRACE_OUT(trace, interrupt, "");
}

//*****************************************************************************

void OZT_CmdSender::setR()
{
    RFlag = TRUE;
}

//*****************************************************************************

void OZT_CmdSender::clearR()
{
    RFlag = FALSE;
}

//*****************************************************************************

OZT_Result OZT_CmdSender::setZ(const RWCString& inFileName,
                               const RWCString& curFileName)
{
    TRACE_IN(trace, setZ, "inFileName : " << inFileName << ", curFileName : "
             << curFileName);

    if (inFileName == "-")
    {
        ozt_errHandler.checkOn();
        clearZ();
        return OZT_Result(OZT_Result::NO_PROBLEM);
    }

    OZT_Result result;
    curFile = curFileName;
    result = updateFileName(inFileName);

    if (result.code == OZT_Result::NO_PROBLEM)
        ZFlag = TRUE;

    ozt_errHandler.checkOff();

    TRACE_OUT(trace, setZ, "storedFileName : " << storedFileName<< ", result : "
              << result);

    return result;
}

//*****************************************************************************

void OZT_CmdSender::clearZ()
{
    TRACE_IN(trace, clearZ, "");

    ZFlag = FALSE;

    TRACE_OUT(trace, clearZ, "");
}

//*****************************************************************************

OZT_Result OZT_CmdSender::setScanStr(const RWCString& inStr)
{
    TRACE_IN(trace, setScanStr, "inStr <"<< inStr <<  ">");

    size_t start = 0;
    size_t pos;
    RWCString myStr;

    // remove the "/"
    if (inStr.isNull() || inStr(inStr.length() - 1) != '/')
    {
        TRACE_OUT(trace, setScanStr, "Syntax error");
        return OZT_Result(OZT_Result::SYNTAX_ERR);
    }
    myStr = inStr(0, inStr.length() - 1);
    TRACE_FLOW(trace, setScanStr, "myStr <" << myStr << ">");

    myStr = trim(myStr);
    if (myStr.isNull())
    {
        TRACE_OUT(trace, setScanStr, "Missing parameter(s)");
        return OZT_Result(OZT_Result::MISSING_PARAMETERS);
    }

    while(start < myStr.length())
    {
        if ((pos = myStr.index(",", start)) != RW_NPOS)
        {
            keys.append(trim(myStr(start, pos - start)));
            start = pos + 1;
        }
        else
            // The last one not ending with ","
        {
            keys.append(trim(myStr(start, myStr.length() - start)));
            break;
        }
    }
    TRACE_OUT(trace, setScanStr, "NO_PROBLEM");
    return OZT_Result(OZT_Result::NO_PROBLEM);
}

//*****************************************************************************

RWBoolean OZT_CmdSender::mScan(RWCString& failStr)
{
    TRACE_IN(trace, mScan, "")

        size_t index=1,
        lastIndex=0;
    size_t pos=0,
        lastPos=0;

    if (keys.isEmpty())
    {
        TRACE_OUT(trace, mScan, "NO_PROBLEM (empty string)");
        return TRUE;
    }

    for (int i=0; i<keys.entries(); i++)
    {
        if (((index = cmdRspBuf.scan(keys[i], index - 1, pos)) == 0) ||
            ((pos <= lastPos) && (index == lastIndex)))
        {
            failStr = keys[i];
            TRACE_OUT(trace, mScan, "Fail at keys[" <<  i << "]:" << keys[i]
                      <<", lastPos: "<<lastPos<<", pos: "<<pos<<", lastIndex: "
                      <<lastIndex<<", index: "<<index);
	    clearScanStr();
            return FALSE;
        }
        else
        {
            lastPos = pos;
            lastIndex = index;
        }
    }
    // reset the mark back to original position

    clearScanStr();
    failStr = RWCString();
    TRACE_OUT(trace, mScan, "");
    return TRUE;
}

//*****************************************************************************

void OZT_CmdSender::clearScanStr()
{
    TRACE_IN(trace, clearScanStr, "")

        keys.clear();

    TRACE_OUT(trace, clearScanStr, "");
}

//*****************************************************************************

void OZT_CmdSender::storeZError (const RWCString& cmdText,
                                 const OZT_Result& result)
{
    TRACE_IN(trace, storeZError, "cmdText :" << cmdText << ", result :"<<result);
    
    fstream f;
    f.open(storedFileName.data(), ios::out | ios::app);
    if (f.is_open()) {
        f << cmdText << endl << result << endl;
        if (f.bad())    //bad() function will check for badbit
        {
            TRACE_FLOW(trace, storeZError, "Write failed");
        }
        f.close();
    }
    else {
        TRACE_FLOW(trace, storeZError, "Failed to open file: " << storedFileName.data());
    }

    TRACE_OUT(trace, storeZError, "");
}

//*****************************************************************************

OZT_Result OZT_CmdSender::updateFileName(const RWCString& inFileName)
{
    TRACE_IN(trace, updateFileName, "inFileName : " << inFileName);

    RWCString   resultFileName = inFileName;
    OZT_Result  result;
    struct stat buf;
    int         status = 0;

    // stat() the file
    status = stat(resultFileName.data(), &buf);
    if ( (status == -1) && (errno != ENOENT) )
        // file error, except for non-existing file
    {
        result = OZT_Result(OZT_Result::FILE_OPEN_ERR, strerror(errno));

        TRACE_OUT(trace, resultFileName, "resultFileName : " <<
                  resultFileName << ", result : " << result);

        return result;
    }
    else if (status == 0)
        // if file existed, add the extension for resultFileName
    {
        resultFileName = ozt_normalisePath(resultFileName);
        getNextFileName(resultFileName);
    }

    // check if data can be appended to the file `resultFileName'
    fstream f;
    f.open(resultFileName.data(), ios::app);
    if (f)
    {
        result = OZT_Result(OZT_Result::NO_PROBLEM);
        storedFileName = resultFileName;
    }
    else
        result = OZT_Result(OZT_Result::FILE_OPEN_ERR, strerror(errno));

    f.close();

    TRACE_OUT(trace, updateFileName, "storedFileName : " << storedFileName <<
              ", result : " << result);
    return result;
}

//*****************************************************************************

void OZT_CmdSender::getNextFileName(RWCString& inFileName)
{
    TRACE_IN(trace, getNextFileName, "inFileName :" << inFileName);

    int d;
    struct stat buf;
    char   period = '.';
    size_t matchPos = 0, len=0;
    RWCString extension;

    inFileName = inFileName + ".1";
    // keep looping and adding the digit in extension until file not exist.
    // matchPos cannot be RW_NPOS at this point.
    matchPos = inFileName.last(period);

    while (stat(inFileName.data(), &buf) == 0)
    {
	matchPos++;
	len = inFileName.length()-matchPos;
        extension = inFileName(matchPos, len);
        d = (int)atoi(extension.data());
        d++;

        strstream s;
        s << d << ends;
        extension = s.str();
        delete s.str();
	--matchPos;

        inFileName.replace(matchPos+1,
                           inFileName.length()-matchPos+1,
                           RWCString(extension));
    }

    TRACE_OUT(trace, getNextFileName, "inFileName : " << inFileName);
}

//*****************************************************************************

RWBoolean OZT_CmdSender::getZ()
{
    TRACE_IN(trace, getZ, "");

    TRACE_OUT(trace, getZ, ZFlag);

    return ZFlag;
}

//*****************************************************************************

RWCString OZT_CmdSender::getCmdStr()
{
    TRACE_IN(trace, getCmdStr, "");

    TRACE_OUT(trace, getCmdStr, "CommandStr :" << lastSentCmd);

    return lastSentCmd;
}

//*****************************************************************************

void OZT_CmdSender::cancelResponses() {
  pSpontReceiver->cancelResponse();
  pImmReceiver->cancelResponse();
  pDelReceiver->cancelResponse();
}

//*****************************************************************************
// Added due to improvement to avoid hanging problem
void OZT_CmdSender::sleepAWhile()
{
  struct timeval tv;
  tv.tv_sec = iOSuperTimerValue;
  tv.tv_usec = 0;
  (void)select(0, 0, 0, 0, &tv);

}

//*****************************************************************************
// Added due to improvement to avoid hanging problem
void OZT_CmdSender::interruptAtDr()
{
   TRACE_IN(trace, interruptAtDr, "");
   pDelReceiver->cancelResponse();
   ozt_evHandlerPtr->setResult(OZT_Result::DELAY_RESPONSE_NOT_RECEIVED);
   changeState(IDLE);
   TRACE_OUT(trace, interruptAtDr, "");
}

//*****************************************************************************
// Added due to improvement to avoid hanging problem
void OZT_CmdSender::totalInterrupt()
{
  TRACE_IN(trace, totalInterrupt, "at " << printState(senderState));

    clientQuitFlag = TRUE;

    TRACE_OUT(trace, totalInterrupt, "");
}

//*****************************************************************************
// Added due to improvement information in opsserver.log file
void OZT_CmdSender::setSessionId(RWCString sessionId)
{
  TRACE_IN(trace,setSessionId , "");

    sessionId_ = sessionId;

    TRACE_OUT(trace, setSessionId, "");
}

//*****************************************************************************

#if TPF >= 400

void OZT_CmdSender::setInputHandler(int fd, RWBoolean opened)
{
    // There can be several consecutive calls to this function with
    // opened == TRUE and then there are several consecutive calls
    // with opened == FALSE. E.g. a number of file descriptors seems
    // to be opened by CAP-IPC and then they are closed when calling
    // IPC_terminate().

    if (opened)
    {
        // New socket connected.  Register the callback function with
        // the event handler.
	ozt_evHandlerPtr->setIOTrigger(thisPointer,
				       OZT_CmdSender::tickCallBack,
				       fd);
    }
    else
    {
        // Socket closed, so remove the registration.
	ozt_evHandlerPtr->unsetIOTrigger(thisPointer, fd);
    }
}
#endif
//*****************************************************************************
void OZT_CmdSender::setConnectionMode(const RWCString& neName)
{
    //AP-mode should always be set if the connection string contains NODE=A,B or C. e.g.  "NE=xxx,NODE=[AaBbCc]"

    //For all other connection strings containing the separator "," MML mode should be used e.g.
    //"NE=xxx,CP=xxx" , NE=xxx,CPNAME=xxx, NE=xxx,SIDE=x.

    //The name of the second APG should always and with "_1" e.g. "NE=xxx_1" and "xxx_1". this name convection is not reserved
    //for the second APG so it's not enough to check this.
    //Do the check anyway since we don't want to call the function "getProtocolTyp()" if it's not needed.

    //The ap-mode is only valid for APG40 and APG43 nodes some we check the node type using the function "getProtocolTyp()".

    //Like I stated before the "_1" in not reserved for the second APG so we need to check the prompt to determine if we are in AP-mode
    // or not.

    //(It would probably be enough to only check for NODE, APG and the PROMPT but this would require lot of testing towards different types of nodes.)


    TRACE_IN(trace,setConnectionMode , neName);
    RWTRegex<char> nodeInNeName("^[ \t]*[Nn][Ee][ \t]*=[ \t]*.*,[ \t]*[Nn][Oo][Dd][Ee][ \t]*=[ \t]*[AaBbCc]");
    RWTRegex<char> apg("[Aa][Pp][Gg][4][03]");
    RWTRegex<char> underscoreAtEndOfNeName("_1[ \t]*$");
    RWTRegex<char> apPrompt("[>]");
    RWTRegex<char> separator("[,]");
    RWBoolean apMode = FALSE;
    if (nodeInNeName.index(neName) != RW_NPOS)
    {
    	TRACE_FLOW(trace, connect, "Connection string contains NODE=[ABC], Connection string: " + neName);
        TRACE_FLOW(trace, connect, "Changing AP mode to true");
        apMode = TRUE;
    }
    else if (separator.index(neName) == RW_NPOS)
    {
         TRACE_FLOW(trace, connect, "Connection string don't contains \",\", Connection string:" + neName);
    }
     getCHACmdSender().setApMode(apMode);
     TRACE_OUT(trace, setConnectionMode, neName);
}

//*****************************************************************************
void OZT_CmdSender::flushStoredResponses()
{
    TRACE_IN(trace, flushStoredResponses, "");
    pRspReceiver->flushStoredSpontResp();
    if(orderedOn)
    {
        pRspReceiver->flushStoredDelResp();
    }
    TRACE_OUT(trace, flushStoredResponses, "");
}
//*****************************************************************************

void OZT_CmdSender::callRelease() {
    sendCtrlChar(WinFIOLClient::RELEASE_CHAR, FALSE);
}
//*****************************************************************************

void OZT_CmdSender::callConnect() {
    sendCtrlChar(WinFIOLClient::CONNECT_CHAR, FALSE);
}

//*****************************************************************************

void OZT_CmdSender::logOff(RWBoolean bTermination) {
    TRACE_IN(trace, logOff, "");

    // Send command logOff
    if (pCmdSender != NULL)
        pCmdSender->logOffHandler(bTermination);

    // mark end of response if delayed command response is finished 
    if (pConnection->isRespEnded() == true) {
        cmdRspBuf.markEndOfRsp();
    }

    TRACE_OUT(trace, logOff, "");
}

//*****************************************************************************
OZT_Result OZT_CmdSender::sendLogoff(RWBoolean markBuf) {
    OZT_Result result;
    flushStoredResponses();
    changeState(LOGGING_ON);
    result = pRspReceiver->logOn();
    if (result.code != OZT_Result::NO_PROBLEM) {
        changeState(IDLE);
        clearScanStr();
        return result.filtered();
    }

    if (pConnection->getConnectionStatus() == 4){
		//pCmdSender->sendControlCharacter(ctrlChar);
        pCmdSender->sendLogoff();
        }

    if(result.code == OZT_Result::NO_CONNECTION) {
        changeState(IDLE);
        clearScanStr();
        return result.filtered();
    }

    if (markBuf) {
        cmdRspBuf.markBeginOfRsp();
    }
    if (!markBuf) {
        cmdRspBuf.markSearchBackPoint();
    }

    if (result.code != OZT_Result::NO_PROBLEM) {
        changeState(IDLE);
        clearScanStr();
    }
    else {
        //
        //  wait for the response to arrive
        //
        resetFunBusyCounter();
        decFunBusyCounter();
        changeState(WAIT_IMM_RSP);
        pCmdSender->checkIPC();

        //
        //  If this is not sent by @SEND, set the search back point
        //  so that @WAITFOR, @WAITREPLY do not search beyond this
        //  point.
        //

        if (markBuf) {
            cmdRspBuf.markSearchBackPoint();
            if (pConnection->isRespEnded() == true) {
                cmdRspBuf.markEndOfRsp();
            }
        }
    }
    changeState(IDLE);
    TRACE_RETURN(trace, sendLogoff, result.filtered());
    return result.filtered();
}

//*****************************************************************************

OZT_Result OZT_CmdSender::sendCtrlChar(int ctrlChar, RWBoolean markBuf) {
    OZT_Result result;
    flushStoredResponses();
    changeState(LOGGING_ON);
    result = pRspReceiver->logOn();
    if (result.code != OZT_Result::NO_PROBLEM) {
        changeState(IDLE);
        clearScanStr();
        return result.filtered();
    }

    if (pConnection->getConnectionStatus() == 4)
        pCmdSender->sendControlCharacter(ctrlChar);

    if(result.code == OZT_Result::NO_CONNECTION) {
        changeState(IDLE);
        clearScanStr();
        return result.filtered();
    }

    if (markBuf) {
        cmdRspBuf.markBeginOfRsp();
    }
    if (!markBuf) {
        cmdRspBuf.markSearchBackPoint();
    }

    if (result.code != OZT_Result::NO_PROBLEM) {
        changeState(IDLE);
        clearScanStr();
    }
    else {
	//
        //  wait for the response to arrive
        //
        resetFunBusyCounter();
        decFunBusyCounter();
        changeState(WAIT_IMM_RSP);
        pCmdSender->checkIPC();

        //
        //  If this is not sent by @SEND, set the search back point
        //  so that @WAITFOR, @WAITREPLY do not search beyond this
        //  point.
        //

	if (markBuf) {
            cmdRspBuf.markSearchBackPoint();
            if(pConnection!=NULL) {
                if (pConnection->isRespEnded() == true) {
                    cmdRspBuf.markEndOfRsp();
                }
            }
        }
    }
    changeState(IDLE);
    TRACE_RETURN(trace, sendCmd, result.filtered());
    return result.filtered();

}
//*****************************************************************************

