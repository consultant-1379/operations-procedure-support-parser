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

#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_LibNLS.H>
#include <CHA_CommandSender.H>
#include <CHA_UserInfo.H>
#include <tauchl_t.H>
#include <CHA_LibNLS.H>
#include <CHA_SeqDelRespReceiver.H>
#include <trace.H>

//**********************************************************************

static std::string trace ="CHA_CommandSender";


//**********************************************************************


CHA_CommandSender::CHA_CommandSender(CHA_IPCSupervisor* pSup,
				     const RWCString& applicationName,
				     CHA_RoutingHandler* pRtHandler)
: changeAssocId(FALSE),
  isSubscribing(FALSE),
  devModeProps(),
  sendState(NOTCON),
  lastCmdResult(UNKNOWN),
  pIpcSupervisor(pSup),
  commandHistory(),
  immReceiver(pSup, this),
  pPrompt(NULL),
  delHandler(pSup, applicationName, pRtHandler),
  delSubscriber(applicationName, pRtHandler, pSup->getTrigger(), &devModeProps),
  connSupervisor(pSup, this, applicationName),
  nlsCat(CHA_LibNLSCatalog),
  logInfoString(""),
  logInfoChanged(FALSE),
  isAPMode(FALSE),
  wfClient(NULL)
{
     TRACE_IN(trace, CHA_CommandSender, "");
    
     /* create dynamic objects
     pAssociation = new EAC_CRI_Association(connSupervisor.getConnection());
     pCommand = new EAC_CRI_Command();
     pImmResp = new EAC_CRI_Im_Resp();
     pReadBreakAssociation =
	           new EAC_CRI_Association(connSupervisor.getConnection());
     pReadBreakResp = new EAC_CRI_Delayed_Resp();


    register dependencies

    if(pIpcSupervisor != NULL)
    pIpcSupervisor->addDependent(this);*/

    immReceiver.addDependent(this);


    if(pRtHandler != NULL)
    {
	pRtHandler->setRespReceiver(CHA_RT_IMMEDIATE, &immReceiver);
    }

    pPrompt = new CHA_PromptString(this, pIpcSupervisor);
    TRACE_OUT(trace, CHA_CommandSender, "");
}


//**********************************************************************


CHA_CommandSender::~CHA_CommandSender()
{
    // remove dependencies from model objects
    if(pIpcSupervisor != NULL)
	pIpcSupervisor->removeDependent(this);

    immReceiver.removeDependent(this);

    /* delete dynamic objects
    delete pAssociation;
    delete pImmResp;
    delete pCommand;
    delete pReadBreakAssociation;
    delete pReadBreakResp;*/
    if (pPrompt != NULL)
    delete pPrompt; 
}


//**********************************************************************


CHA_PromptString* CHA_CommandSender::getPromptObject()
{
    return pPrompt;
}


//**********************************************************************


CHA_DeviceModeProps* CHA_CommandSender::getDevModePropsObject()
{
    return &devModeProps;
}


//**********************************************************************


CHA_ImmRespReceiver* CHA_CommandSender::getImmReceiverObject()
{
    return &immReceiver;
}


//**********************************************************************


CHA_DelRespHandler* CHA_CommandSender::getDelReceiverObject()
{
    return &delHandler;
}


//**********************************************************************


CHA_CommandSender::State CHA_CommandSender::getState() const
{
    return sendState;
}


//**********************************************************************


CHA_CommandSender::CmdResult CHA_CommandSender::getLastCmdResult() const
{
    TRACE_RETURN(trace, getLastCmdResult, lastCmdResult);
    return lastCmdResult;
}


//**********************************************************************


CHA_CommandHistory* CHA_CommandSender::getCommandHistoryObject()
{
    return &commandHistory;
}


//**********************************************************************


CHA_Connection* CHA_CommandSender::getConnectionObject()
{
    return &connSupervisor;
}


//**********************************************************************

//void CHA_CommandSender::newConnection(RWBoolean displayMessage)
void CHA_CommandSender::newConnection(WinFIOLClient* wf)
{
	wfClient = wf;
    /*TRACE_IN(trace, newConnection, "");

      delete pAssociation;
      pAssociation = new EAC_CRI_Association(connSupervisor.getConnection());

      changeAssocId = FALSE;

    
       If we are in device mode the device id may be set 
       by the user. Then we should use that Id. 
       if (devModeProps.isDevModeOn())
       {
	if(devModeProps.isReqDeviceIdSet())  
	pAssociation->Set_assoc_id(devModeProps.getReqDevId());
       }
      else
       {
	 try to get the assoc id from the conenction object (new API)
	 int associd = connSupervisor.getAssocID();
	 pAssociation->Set_assoc_id(associd);
       }

      tell devModeProps object
      devModeProps.usingDevId(pAssociation->Get_assoc_id());

       If the user has set the log info string,
       we will have to use that as well.

  HE76148
     logInfoString = "OPS";
    if(!logInfoString.isNull())
   HE76148 end
	 pAssociation->Set_log_info(logInfoString.data());
     logInfoChanged = FALSE;

    delete pReadBreakAssociation;
    pReadBreakAssociation =
	new EAC_CRI_Association(connSupervisor.getConnection());

    delete pReadBreakResp;
    pReadBreakResp = new EAC_CRI_Delayed_Resp();

    delete pImmResp;
    pImmResp = new EAC_CRI_Im_Resp();

    immReceiver.skipResponse();	// just in case

    If association is set, start subscription now.
    if (pAssociation->Get_assoc_id() != -1) {
      CHA_DelSubscriber::ReturnCode result;
      result = delSubscriber.startSubscription(pAssociation,
					       connSupervisor.getEsName());
      if ( result != CHA_DelSubscriber::OKAY) {
	errorReporter.message(nlsCat.getMessage(NLS_DELSUB_FAILED));
      }
      else  
	{
	  TRACE_FLOW(trace, newConnection, "subscribed to delayed");
	}
    }*/
    
    if(TRUE)
    {
	immReceiver.fwdResponse("\n*** "
				+ nlsCat.getMessage(NLS_ES_CON)
				+ connSupervisor.getEsName()
				+ " ***\n",
				//+ wfClient->getResponsedata(),//Should contain prompt just after connect
				connSupervisor.getEsName());
				checkIPC(); // fix for HD42973
    }

    TRACE_FLOW(trace, newConnection, "IDLE");
    changeState(IDLE);
    TRACE_OUT(trace, newConnection, "");
}


//**********************************************************************


void CHA_CommandSender::esDisConnection(int connStatus, RWBoolean displayMessage)
{
    TRACE_IN(trace, esDisConnection, "");

    immReceiver.skipResponse();	// if a response was during reception

    RWCString message;
/*
    switch(connStatus)
    {
    case EAC_CRI_CS_LINK_DOWN:
	message = "\n*** "
	          + nlsCat.getMessage(NLS_ES_LINKFAIL)
	          + connSupervisor.getEsName()
		  + " ***\n";
	break;
    case EAC_CRI_CS_SYSTEM_TIMEOUT:
	message = "\n*** "
		  + nlsCat.getMessage(NLS_ES_TIMEOUT)
		  + connSupervisor.getEsName()
		  + " ***\n";
	break;
    case EAC_CRI_ERR_CSL_COMM_FAILURE:
 	message = "\n*** "
		  + nlsCat.getMessage(NLS_ES_DISCON_CSL)
		  + connSupervisor.getEsName()
		  + " ***\n";
    break;
    default:
	message = "\n*** "
		  + nlsCat.getMessage(NLS_ES_DISCON)
		  + connSupervisor.getEsName()
		  + " ***\n";
	break;
    }
*/
    if(displayMessage)
    {
	immReceiver.fwdResponse(message, connSupervisor.getEsName());
    }


    TRACE_FLOW(trace, esDisConnection, "NOTCON");
    changeState(NOTCON);
    TRACE_OUT(trace, esDisConnection, "");
}


//**********************************************************************


void CHA_CommandSender::usrDisConnection(RWBoolean displayMessage)
{
    TRACE_IN(trace, usrDisConnection, "");

    immReceiver.skipResponse();	// if a response was during reception

    if(displayMessage)
    {
	immReceiver.fwdResponse("\n*** "
				+ nlsCat.getMessage(NLS_ES_DISCON)
				+ connSupervisor.getEsName()
				+ " ***\n",
				connSupervisor.getEsName());
    }

    // Stop any subscription, TR HF21010
    delSubscriber.stopAllSubscription();

    TRACE_FLOW(trace, usrDisConnection, "NOTCON");
    changeState(NOTCON);
    TRACE_OUT(trace, usrDisConnection, "");
}



//**********************************************************************


void CHA_CommandSender::setLogInfo(const RWCString& info)
{
    TRACE_IN(trace, setLogInfo, info);
    logInfoString = info;
    logInfoChanged = TRUE;
}

//**********************************************************************


void CHA_CommandSender::addLogInfo(const RWCString& info)
{
    TRACE_IN(trace, addLogInfo, info);
    if (! logInfoChanged)
    {
	logInfoString = info;
	logInfoChanged = TRUE;
    }
    else 
	logInfoString = getLogInfo() + " " + info;
}


//**********************************************************************


void CHA_CommandSender::addLogInfoFirst(const RWCString& info)
{
    TRACE_IN(trace, addLogInfoFirst, info);

    if (!logInfoChanged)
    {
	logInfoString = info;
	logInfoChanged = TRUE;
    }
    else
	logInfoString = info + " " + getLogInfo();

    TRACE_IN(trace, addLogInfoFirst, info);
}


//**********************************************************************


void CHA_CommandSender::unsetLogInfo()
{
    TRACE_IN(trace, unsetLogInfo, "");
    logInfoString = "";
    logInfoChanged = TRUE;
}


//**********************************************************************


RWCString CHA_CommandSender::getLogInfo() const
{
    TRACE_RETURN(trace, getLogInfo, logInfoString);
    return logInfoString;
}

//**********************************************************************

void CHA_CommandSender::setAutoConfirm(RWBoolean confirm)
{
    TRACE_IN(trace, setAutoConfirm, confirm);
    wfClient->setAutoConfirm(confirm);
    TRACE_OUT(trace, setAutoConfirm, "");
} 
 
//**********************************************************************


CHA_CommandSender::ReturnCode CHA_CommandSender::sendCommand(
					        RWCString cmd,
						const RWCString& pmt,
						const RWCString& logInfo)
{
    TRACE_IN(trace, sendCommand, cmd << ", " << pmt << ", " << logInfo);

    // store the original value of the log string
    RWCString tmpLogInfo = logInfoString;
    
    // set it temporarily to the new value and send the command
    logInfoString = logInfo;
    logInfoChanged = TRUE;
    ReturnCode result = sendCommand(cmd, pmt);

    // restore the old value and return
    logInfoString = tmpLogInfo;
    logInfoChanged = TRUE;

    TRACE_RETURN(trace, sendCommand, "value of prev SendCommand() call");
    return result;
}
    

//**********************************************************************


CHA_CommandSender::ReturnCode CHA_CommandSender::sendCommand(
							RWCString cmd,
							const RWCString& pmt)
{
    TRACE_IN(trace, sendCommand, cmd << ", " << pmt);

    // check if we can send a command
   
    //sendState=IDLE; //Need to be removed .Added for testing to call sendCmd directly>
    switch(sendState)
    {
    case IDLE:
	break;			// don't exit, continue below
    case NOTCON:
	TRACE_RETURN(trace, sendCommand, "NOCONNECTION");
	return NOCONNECTION;
    case WAITING: break;
    case CONFIRM:
    case RECEIVING:
    default:
	TRACE_RETURN(trace, sendCommand, "BUSY");
	return BUSY;
    }

    // check the connection
    if (connSupervisor.getConnectionStatus() != WFST_CONNECTED)
    {
	//errorReporter.message(nlsCat.getMessage(NLS_SENDFAILED_NOCONNECTION));
	TRACE_RETURN(trace, sendCommand, "NOCONNECTION");
	return NOCONNECTION;
    }

    // For APG40 don't transform to uppercase at AP prompt, i.e. between
    // APLOC and EXIT (but APG40 wants EXIT to be in uppercase for some reason)

    if(isAPMode && cmd.contains("EXIT", RWCString::ignoreCase)) {
        isAPMode = FALSE;
        // HD45123: See description in CHA_ImmRespReceiver.C
        immReceiver.setApMode(isAPMode);
    }

    // this check is removed due to HD53923
    // check if upper case is needed, this convertion should really be in EA
    if(connSupervisor.useUpperCase() && !isAPMode)
    {
      TRACE_FLOW(trace, sendCommand, "converting command " << cmd <<" to upper case");
      cmd.toUpper();
	  } 
	  else
	  {
	    TRACE_FLOW(trace, sendCommand, "no convesion of command " << cmd <<" to upper case");
	  }

    // If APLOC following commands shall not be translated to uppercase.
    if(!isAPMode && cmd.contains("APLOC", RWCString::ignoreCase)) {
        isAPMode = TRUE;
        // HD45123: See description in CHA_ImmRespReceiver.C
        immReceiver.setApMode(isAPMode);
    }

    TRACE_FLOW(trace, sendCommand, ",isAPMode:" << isAPMode);

    /* check if we shall use a new association, i.e. when delayed 
    response is expected

    if(changeAssocId) {

	delete pAssociation;
	pAssociation = new EAC_CRI_Association(connSupervisor.getConnection());
	//TRACE_FLOW(trace, sendCommand, "new association");

	changeAssocId = FALSE;
	isSubscribing = FALSE;

	// If the user has set the log info string we will have to use
	// that as well.
	if(!logInfoString.isNull())
	{
	    char c = ' ';
	    logInfoString = logInfoString.strip(RWCString::both, c);
	   // pAssociation->Set_log_info(logInfoString.data());
	}

	logInfoChanged = FALSE;

    }*/

    // If we are in device mode the device id may be set 
    // by the user. Then we have to use that Id.              
    if(devModeProps.isDevModeOn()) {
	if(devModeProps.isReqDeviceIdSet())
	{
	  //  pAssociation->Set_assoc_id(devModeProps.getReqDevId());
	}
	else
	{
	   // pAssociation->Set_assoc_id(devModeProps.getUsedDevId());
	}
    }

    // tell devModeProps object
    //devModeProps.usingDevId(pAssociation->Get_assoc_id());

    // If the log info string was changed, then set the new value
    if(logInfoChanged)
    {
	char c = ' ';
	logInfoString = logInfoString.strip(RWCString::both, c);
	//pAssociation->Set_log_info(logInfoString.data());
	logInfoChanged = FALSE;
    }

    TRACE_FLOW(trace, sendCommand, "Actually sending: " << cmd);

    // set the command string in our command object
    /*  if(pCommand->Set_cmd_str(cmd.data()) != EAC_CRI_OK)
    {
	errorReporter.message(nlsCat.getMessage(NLS_SENDFAILED));
	//TRACE_RETURN(trace, sendCommand, "FAILED");
	return FAILED;
    }*/

    // put the command in the history and make a response

    commandHistory.append(cmd);
    std::string cmdString( cmd );
    
	if(immReceiver.newCommand(cmd, pmt, connSupervisor.getEsName(), 
			      wfClient)
       != CHA_ImmRespReceiver::OKAY)
    {
	TRACE_FLOW(trace,sendCommand, "immReceiver NOT OK!"); 
		immReceiver.skipResponse();
		immReceiver.newCommand(cmd, pmt, connSupervisor.getEsName(),
		 wfClient);
    }

    // MML "exit;" command handling 

    if((wfClient->getCurrentPrompt().compare(MML_PROMPT) == 0) 
        && (cmd.contains("EXIT;", RWCString::ignoreCase)))
    {
        if(!connSupervisor.disconnect())
            return NOCONNECTION;
        else 
            return DISCON_FAILED;
    }

  /*  if(immReceiver.newCommand(cmd, pmt, connSupervisor.getEsName(), 
			      pAssociation->Get_assoc_id())
       != CHA_ImmRespReceiver::OKAY)
    {
	//TRACE_FLOW(trace,sendCommand, "immReceiver NOT OK!"); 
	immReceiver.skipResponse();
	immReceiver.newCommand(cmd, pmt, connSupervisor.getEsName(),
			       pAssociation->Get_assoc_id());
    }*/
 
    // send the command
    //TRACE_FLOW(trace, sendCommand, 
	//       "Sending command: " << cmd << " with assoc=" << pAssociation->Get_assoc_id() << " isAPMode=" << isAPMode);
    wfClient->sendData(cmdString,0);
    
    changeState(WAITING);
    TRACE_RETURN(trace, sendCommand, "OKAY");
    CHA_SeqDelRespReceiver::updateSendState(1); // Changed due to DEL RSP problem.Indicate that start phase of new sending
    TRACE_FLOW(trace, sendCommand, "sendFlag is set to 1");
    return OKAY;
    
  /*  switch(pAssociation->Send_command(pCommand))
    {
    case EAC_CRI_OK:
    case EAC_CRI_COMMAND_QUEUED:
	// no subscription for delayed made yet
	//TRACE_FLOW(trace, sendCommand, "WAITING");
	changeState(WAITING);
	//TRACE_RETURN(trace, sendCommand, "OKAY");
	CHA_SeqDelRespReceiver::updateSendState(1); // Changed due to DEL RSP problem.Indicate that start phase of new sending
	 //TRACE_FLOW(trace, sendCommand, "sendFlag is set to 1");
	return OKAY;
    case EAC_CRI_ERR_NO_COMMUNICATION:
	errorReporter.message(nlsCat.getMessage(NLS_SENDFAILED_NOCONNECTION));
	//TRACE_FLOW(trace, sendCommand, "NOTCON");
	changeState(NOTCON);
	immReceiver.skipResponse();
	//TRACE_RETURN(trace, sendCommand, "NOCONNECTION");
	return NOCONNECTION;
    case EAC_CRI_ERROR:
    default:
	errorReporter.message(nlsCat.getMessage(NLS_SENDFAILED));
	//TRACE_RETURN(trace, sendCommand, "FAILED");
	return FAILED;
    }*/
}

//*****************************************************************************
OZT_Result CHA_CommandSender::sendLogoff() {

    if (wfClient != NULL && wfClient->getConnectionStatus() == 4) {
        immReceiver.newCommand(wfClient);

        wfClient->logoff();
        changeState(WAITING);
        CHA_SeqDelRespReceiver::updateSendState(1);
        return OZT_Result(OZT_Result::NO_PROBLEM);
    }
    else {
	    //return;
	    return OZT_Result(OZT_Result::NO_CONNECTION);
    }
}

//**********************************************************************

//void CHA_CommandSender::sendControlCharacter(int ctrlChr) {
OZT_Result CHA_CommandSender::sendControlCharacter(int ctrlChr) {
    //if(wfClient != NULL && wfClient->getConnectionStatus() != -1) {
    if (wfClient != NULL && wfClient->getConnectionStatus() == 4) {
    immReceiver.newCommand(wfClient);

    if (WinFIOLClient::RELEASE_CHAR == ctrlChr) {
        wfClient->sendControlChar(ctrlChr, DO_NOT_READ_RESP);
    }
    else {
        wfClient->sendControlChar(ctrlChr, 0);
    }
    changeState(WAITING);
    CHA_SeqDelRespReceiver::updateSendState(1);
    return OZT_Result(OZT_Result::NO_PROBLEM);
    }
    else {
	    //return;
	    return OZT_Result(OZT_Result::NO_CONNECTION);
    }
}


//**********************************************************************


void CHA_CommandSender::logOffHandler(RWBoolean bTermination) {
    TRACE_IN(trace, logOffHandler, "");

    if (wfClient != NULL && wfClient->getConnectionStatus() == 4) {

        wfClient->logoff();
        
        // Flush responses to output window
        immReceiver.newCommand(wfClient);
        changeState(WAITING);
        immReceiver.receiveResponse(wfClient);

    } else {
        TRACE_FLOW(trace, logOffHandler, "No Connection exists with WinFIOL");
    }

    TRACE_OUT(trace, logOffHandler, "");
}


//**********************************************************************


void CHA_CommandSender::immResponseReceived(const RWCString& newPrompt)
{
    // This method finishes up sending of a command. After this the
    // state of the command sender will be IDLE.
    
    TRACE_IN(trace, immResponseReceived, newPrompt);

    switch (immReceiver.getResponseCode())
    {
        case EXECUTED:
            lastCmdResult = EXECUTED;
            break;
        case FUNCTION_BUSY:
            lastCmdResult = FUNCTION_BUSY;
            break;
        case NOT_AUTHORIZED:
            lastCmdResult = NOT_AUTHORIZED;
            break;
        default:
            lastCmdResult = UNKNOWN;
    }

    /* start a subscription for delayed, if needed
    switch(pImmResp->Get_immediate_response_type())
    {
	// The command sent has been ordered to be executed, i.e. the
	// command will be executed at a later stage. A delayed
	// response usually follows after this immediate response type.
	case EAC_CRI_IRT_ORDERED:
	    lastCmdResult = ORDERED;
	    changeAssocId = TRUE;
	    break;

        // The command parameters have been analysed by the ES and are
        // found to be correct. The command has been executed as
        // indicated and has changed some data in the ES.
    	case EAC_CRI_IRT_EXECUTED:
	// The command sent was correct and has generated an answer
	// response, i.e. a list of ES data.
	case EAC_CRI_IRT_ANSWER_RESPONSE:
	    lastCmdResult = EXECUTED;
	    break;

	// The command was not accepted due to syntax error or that the
	// command was unknown to the ES.
	case EAC_CRI_IRT_NOT_ACCEPTED:
	    lastCmdResult = NOT_ACCEPTED;
	    break;

	// The command was not fully correct but some parts have been
	// executed.
	case EAC_CRI_IRT_PARTLY_EXECUTED:
	    lastCmdResult = PARTLY_EXECUTED;
	    break;

	// The command has not been executed due to more parameters are 
	// expected.
	case EAC_CRI_IRT_INCOMPLETE_COMMAND:
	    lastCmdResult = INCOMPLETE;
	    break;

	// This is received when the ES cannot process the command
	// due to a busy situation.
	case EAC_CRI_IRT_FUNCTION_BUSY:
	    lastCmdResult = FUNCTION_BUSY;
	    break;

	// The immediate response type is unknown or not determined yet.
	// TR: HB36647 (Acc to Stefan Wikstrom it should be treated as executed)
	case EAC_CRI_IRT_UNKNOWN:
		lastCmdResult = EXECUTED;
		break;
	default:
	    lastCmdResult = UNKNOWN;  
	    break;
    }

    // Now device ID should be set. Start subscription
    if (pAssociation->Get_assoc_id() != -1) {

        CHA_DelSubscriber::ReturnCode result;

	if (!isSubscribing)
	    result = delSubscriber.startSubscription(pAssociation,
					     connSupervisor.getEsName());
	else
            result = delSubscriber.prolongSubscription(pAssociation,
					     connSupervisor.getEsName());

        if ( result != CHA_DelSubscriber::OKAY)
            errorReporter.message(nlsCat.getMessage(NLS_DELREC_FAILED));
        else {
	    isSubscribing = TRUE;
	    //TRACE_FLOW(trace, immResponseReceived, "subscribed to delayed");
	}
	
    }	
*/

    // tell devModeProps object
   // devModeProps.usingDevId(pAssociation->Get_assoc_id());

    // 
    pPrompt->checkPrompt();

    if( pPrompt->getPrompt() == ":" ){
      immReceiver.fwdResponse("\n" + 
    			      pPrompt->getPrompt(),
    			      connSupervisor.getEsName());
    }

    /*HD94591: Will make OPS to accept a prompt with prefix. 
    Before they wasn't shown in the OPS GUI.
    RWCString thePrompt = pPrompt->getPrompt();
    if( thePrompt[strlen(thePrompt) - 1] == ':' ){
    	immReceiver.fwdResponse("\n" + 
    			      thePrompt,
    			      connSupervisor.getEsName());
			      }*/

    TRACE_FLOW(trace, immResponseReceived, "IDLE");
    changeState(IDLE);
    TRACE_OUT(trace, immResponseReceived, "");
}


//**********************************************************************


void CHA_CommandSender::expectingDelayed()
{

    TRACE_IN(trace, expectingDelayed, "");
/*
    changeAssocId = TRUE;
    CHA_DelSubscriber::ReturnCode result;
    if (pAssociation->Get_assoc_id() != -1)
        result = delSubscriber.startSubscription(pAssociation,
					     connSupervisor.getEsName());

    if ( result != CHA_DelSubscriber::OKAY) 
        errorReporter.message(nlsCat.getMessage(NLS_DELREC_FAILED));
    else 
	//TRACE_FLOW(trace, immResponseReceived, "subscribed to delayed");	  
*/   
}


//**********************************************************************


CHA_CommandSender::ReturnCode CHA_CommandSender::confirmCommand(RWBoolean confirmed)
{
    TRACE_IN(trace, confirmCommand, confirmed);

    // if we don't need to confirm, return quickly
    if(sendState != CONFIRM)
    {
	TRACE_RETURN(trace, confirmCommand, "OKAY");
	return OKAY;
    }

    int result;
    /*  if(confirmed)
	result = pAssociation->Confirm_command(EAC_CRI_CONFIRM);
    else
	result = pAssociation->Confirm_command(EAC_CRI_INHIBIT);

    switch(result)
    {
    case EAC_CRI_OK:
	//TRACE_FLOW(trace, confirmCommand, "newState");
	changeState(WAITING);
	//TRACE_RETURN(trace, confirmCommand, "OKAY");
	return OKAY;

    case EAC_CRI_ERR_NO_COMMUNICATION:
    case EAC_CRI_ERROR:
    default:
	errorReporter.message(nlsCat.getMessage(NLS_CONFIRMFAILED));	

// I'm not shure it is a good idea to skip response and become idle
// 	immReceiver.skipResponse();
// 	//TRACE_FLOW(trace, confirmCommand, "IDLE");
// 	changeState(IDLE);
*/
	changeState(WAITING);

	TRACE_RETURN(trace, confirmCommand, "FAILED;  ");
	return FAILED;	
  //  }
}


//**********************************************************************


void CHA_CommandSender::updateFrom(CHA_Model* p, void* d)
{
    if(p == (CHA_Model*)pIpcSupervisor)
	checkIPC();
    else {
/*	if ( ((CHA_ResponseReceiver *)p)->isNewResponse())
            // tell devModeProps object
    	   // devModeProps.usingDevId(pAssociation->Get_assoc_id());*/
    }
}


//**********************************************************************


void CHA_CommandSender::detachFrom(CHA_Model* model)
{
    if(model == (CHA_Model*)pIpcSupervisor)
	pIpcSupervisor = NULL;
}


//**********************************************************************


void CHA_CommandSender::checkIPC()
{
    // Check if we got a s.c. "read-break" output from the exchange.
    // A read-break output comes in the form of a delayed response
    // on the current connection and can arrive at any time says
    // the EA man Stefan Wikström  (ehsstwi).
    const char* respStr;
    const char* respPrompt;
    RWCString tmpPrompt(""); 

    TRACE_IN(trace, checkIPC, "");

   /* if ( (connSupervisor.getConnection().Get_connection_mode() != EAC_CRI_CM_NO_CONNECTION ) && 
         (connSupervisor.getConnection().Get_connection_mode() != EAC_CRI_CM_RECEIVING) )
      {
	switch(pReadBreakAssociation->Receive_delayed_resp(pReadBreakResp))
	  {
	  case EAC_CRI_OK:
	  case EAC_CRI_ALREADY_RECEIVED:
	    //TRACE_FLOW(trace, checkIPC, "read break");
	    pReadBreakResp->Get_response(respStr);
	    immReceiver.fwdResponse(respStr, connSupervisor.getEsName(),
				    pAssociation->Get_assoc_id());

 	    // If the association ID is set, this might be the first time
 	    // we get to know about the assoc ID. For EHT, for example, this
 	    // happens right after a connection is made, if header printing 
 	    // is on.
 	    // If we know the association ID we can start a delayed 
 	    // subscription much sooner.
 	    if((pReadBreakAssociation->Get_assoc_id() != -1) 
 	       && (pAssociation->Get_assoc_id() == -1))
	      {
 		pAssociation->Set_assoc_id(pReadBreakAssociation->Get_assoc_id());	
 		devModeProps.usingDevId(pAssociation->Get_assoc_id());

            	CHA_DelSubscriber::ReturnCode result;
            	result = delSubscriber.startSubscription(pAssociation,
							 connSupervisor.getEsName());

            	if(result != CHA_DelSubscriber::OKAY) 
		  errorReporter.message(nlsCat.getMessage(NLS_DELSUB_FAILED));
            	else 
		  //TRACE_FLOW(trace, checkIPC, "subscribed to delayed");
	      }
	    
	    // must always use a "fresh" association for this
	    delete pReadBreakAssociation;
	    pReadBreakAssociation =
	      new EAC_CRI_Association(connSupervisor.getConnection());

	    // The READ BREAK is a delayed response, to know which prompter to
	    // use we get the prompter from the EAC_CRI_Delayed_Resp object using
	    // the new method Get_response_prompt.
	    // respPrompt = pReadBreakResp->Get_response_prompt();
	    // tmpPrompt = respPrompt;
	    // prompt.setPrompt(tmpPrompt);
	    pPrompt->checkPrompt();
	    break;
	  default:			// otherwise just skip it
	    break;
	  }
      }*/

    // if we're not waiting for anything else on CAP-IPC, return quickly
    if(sendState != WAITING)
      {
	TRACE_RETURN(trace, checkIPC, "sendState != WAITING");
	return;
      }
  /*  switch(pAssociation->Receive_im_resp(pImmResp, 0))
    {
    case EAC_CRI_TIMEOUT:	   // nothing yet, return quickly
    case EAC_CRI_PMS_MSG_RECEIVED: // we don't bother about PMS here
      //TRACE_RETURN(trace, checkIPC, "EAC_CRI_TIMEOUT or EAC_CRI_PMS_MSG_RECEIVED");
      return;

    case EAC_CRI_CONFIRM_NEEDED:

      // Needed to read the contense of the received buffers 
      // before asking for confirmation.

      // TA: AE42592. These 3 lines are now moved before the if () statement.
      // The receiveConfirmRespons() calls readbuffer() which sets the state
      // to IDLE for a short while. During this short while, another buffered
      // command was sent to EA and the commands became unsync.
        devModeProps.usingDevId(pAssociation->Get_assoc_id());
	//TRACE_FLOW(trace, checkIPC, "CONFIRM");
	changeState(CONFIRM);*/

/*	if(immReceiver.receiveConfirmResponse(wfClient) != CHA_ImmRespReceiver::OKAY)
	{
	  immReceiver.skipResponse();
	  errorReporter.message(nlsCat.getMessage(NLS_IMMREC_FAILED));
	  //TRACE_FLOW(trace, checkIPC, "Failed to read confirm buffer set state to IDLE");
	  changeState(IDLE);
	}
	
	//TRACE_RETURN(trace, checkIPC, "EAC_CRI_CONFIRM_NEEDED");
	return;

    case EAC_CRI_ALREADY_RECEIVED: // oops, how did this happen?
    case EAC_CRI_OK:
	//TRACE_FLOW(trace, checkIPC, 
		   "RECEIVING, assoc=" << pAssociation->Get_assoc_id());

	// subscribe to delayed, as soon as possible, if needed
	if(pImmResp->Get_immediate_response_type() == EAC_CRI_IRT_ORDERED) {

    	    changeAssocId = TRUE;

            if (pAssociation->Get_assoc_id() != -1) {

            	CHA_DelSubscriber::ReturnCode result;
            	result = delSubscriber.startSubscription(pAssociation,
					     connSupervisor.getEsName());

            	if ( result != CHA_DelSubscriber::OKAY) 
                   errorReporter.message(nlsCat.getMessage(NLS_DELREC_FAILED));
            	else 
	            //TRACE_FLOW(trace, checkIPC, "subscribed to delayed");	
            }	
	
        }*/

	changeState(RECEIVING);	   // this HAS to be before next line

	// tell the receiver to start receiving buffers
	
        switch(immReceiver.receiveResponse(wfClient))
        {
         case EXECUTED:
              errorReporter.message(nlsCat.getMessage(SUCCESS));
              lastCmdResult = EXECUTED;
              return;
         case NOT_ACCEPTED:
              errorReporter.message(nlsCat.getMessage(NLS_IMMREC_FAILED));
              lastCmdResult = NOT_ACCEPTED;
              changeState(IDLE);
              return;
         case PARTLY_EXECUTED:
              errorReporter.message(nlsCat.getMessage(NLS_IMMREC_FAILED));
              lastCmdResult = PARTLY_EXECUTED;
              changeState(IDLE);
              return;
         case INCOMPLETE:
              errorReporter.message(nlsCat.getMessage(NLS_IMMREC_FAILED));
              lastCmdResult = INCOMPLETE;
              changeState(IDLE);
              return;
         case FUNCTION_BUSY:
              errorReporter.message(nlsCat.getMessage(NLS_IMMREC_FAILED));
              lastCmdResult = FUNCTION_BUSY;
              changeState(IDLE);
              return;
         case NOT_AUTHORIZED:
              errorReporter.message(nlsCat.getMessage(NLS_IMMREC_FAILED));
              lastCmdResult = NOT_AUTHORIZED;
              changeState(IDLE);
         default:
              errorReporter.message(nlsCat.getMessage(NLS_IMMREC_FAILED));
              //immReceiver.skipResponse();
              lastCmdResult = UNKNOWN;
              //TRACE_FLOW(trace, checkIPC, "IDLE");
              changeState(IDLE);
              //TRACE_RETURN(trace, checkIPC, "EAC_CRI_ERR_BUFFER_TIMEOUT or EAC_CRI_ERROR or default");
              return;
        }

	//TRACE_RETURN(trace, checkIPC, "EAC_CRI_ALREADY_RECEIVED or EAC_CRI_OK");
   /* case EAC_CRI_ES_REQUEST_REFUSAL: // ES is booting or something
	errorReporter.message(nlsCat.getMessage(NLS_COMMAND_REJECTED)
			      + pCommand->Get_cmd_str());
	immReceiver.skipResponse();
	lastCmdResult = NOT_ACCEPTED;
	//TRACE_FLOW(trace, checkIPC, "IDLE");
	changeState(IDLE);
	//TRACE_RETURN(trace, checkIPC, "EAC_CRI_ES_REQUEST_REFUSAL");
	return;

    case EAC_CRI_ERR_NOT_AUTHORIZED: // user not authorized
	errorReporter.message(nlsCat.getMessage(NLS_CMD_NOAUTH)
			      + pCommand->Get_cmd_str(), CHA_ErrorReporter::COMMAND_SENDER_NOT_AUTHORIZED);
	immReceiver.skipResponse();
	lastCmdResult = NOT_AUTHORIZED;
	//TRACE_FLOW(trace, checkIPC, "IDLE");
	changeState(IDLE);
	//TRACE_RETURN(trace, checkIPC, "EAC_CRI_ERR_NOT_AUTHORIZED");
	return;

    case EAC_CRI_ERR_NO_COMMUNICATION: // the conn.obj will take care of this
	immReceiver.skipResponse();
	//TRACE_FLOW(trace, checkIPC, "NOTCON");
	lastCmdResult = NOT_ACCEPTED;
	changeState(NOTCON);
	//TRACE_RETURN(trace, checkIPC, "EAC_CRI_ERR_NO_COMMUNICATION");
	return;
	
    case EAC_CRI_ERR_BUFFER_TIMEOUT:
    case EAC_CRI_ERROR:
    default:
	errorReporter.message(nlsCat.getMessage(NLS_IMMREC_FAILED));
	immReceiver.skipResponse();
	lastCmdResult = NOT_ACCEPTED;
	//TRACE_FLOW(trace, checkIPC, "IDLE");
	changeState(IDLE);
	//TRACE_RETURN(trace, checkIPC, "EAC_CRI_ERR_BUFFER_TIMEOUT or EAC_CRI_ERROR or default");
	return;
    }*/
}


//**********************************************************************


void CHA_CommandSender::changeState(State newState)
{
    sendState = newState;
    TRACE_FLOW(trace, changeState, "sendState = " << sendState);
    changed();
}


//**********************************************************************

void CHA_CommandSender::setApMode(RWBoolean isAPModeIn)
{
  TRACE_FLOW(trace, setApMode, "Set APMode to:" << isAPModeIn);
  isAPMode = isAPModeIn;
  immReceiver.setApMode(isAPModeIn);
}

//**********************************************************************
