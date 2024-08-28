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


#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_LibNLS.H>
#include <CHA_ImmRespReceiver.H>
#include <CHA_CommandSender.H>
#include <CHA_SeqDelRespReceiver.H>
#include <trace.H>
#include <boost/algorithm/string.hpp>
#include <pthread.h>

static std::string trace ="CHA_ImmRespReceiver";
//**********************************************************************


CHA_ImmRespReceiver::CHA_ImmRespReceiver(CHA_IPCSupervisor* pSup,
					 CHA_CommandSender* pCmdS)
: pIpcSupervisor(pSup),
  pCommandSender(pCmdS),
  //pImmResp(NULL),
  wfClient(NULL),
  receptionState(IDLE),
  esName(),
  command(),
  deviceId(-1),
  responseQue(),
  nlsCat(CHA_LibNLSCatalog),
  pendingCancel(FALSE),
  isAPMode(FALSE),
  cmdRespCode(OKAY),
  isDoneProcessing(TRUE)
{
    TRACE_IN(trace, CHA_ImmRespReceiver, "");

    if(pIpcSupervisor != NULL)
	pIpcSupervisor->addDependent(this);

    createDetachedReadThread();
}


//**********************************************************************


CHA_ImmRespReceiver::~CHA_ImmRespReceiver()
{
    if(pIpcSupervisor != NULL)
	pIpcSupervisor->removeDependent(this);

    while(!responseQue.isEmpty())
    {
	buffer = responseQue.get();
	delete buffer;
    }
}


//**********************************************************************


void CHA_ImmRespReceiver::cancelResponse()
{
    TRACE_IN(trace, cancelResponse, "");

    switch(receptionState)
    {
	case RECEIVING:
	    pendingCancel = FALSE;
	    /*switch(pImmResp->Interrupt_response())
	    {
		case EAC_CRI_OK:
		    fwdResponse(nlsCat.getMessage(NLS_IMMRESP_INTR), "");
		   break;

		case EAC_CRI_ERR_NO_RESPONSE_RECEPTION:
		    errorReporter.message(nlsCat.getMessage(NLS_IMMRESP_NOTRECEIVING));
		    break;

		case EAC_CRI_ERR_INTERRUPT_FAILED:
		case EAC_CRI_ERR_ES_DONT_SUPPORT_INTERRUPTION:
		case EAC_CRI_ERR_NO_COMMUNICATION:
		case EAC_CRI_ERROR:
		default:
		    errorReporter.message(nlsCat.getMessage(NLS_IMMRESP_INTR_FAILED));
		    break;
	    }*/

	    // check once more for buffers
	    readBuffers(TRUE);
	    break;

	case WAITING:
	    pendingCancel = TRUE;
	    break;

	default:
	    errorReporter.message(nlsCat.getMessage(NLS_IMMRESP_NOTRECEIVING));
	    break;
    }
}


//**********************************************************************


void CHA_ImmRespReceiver::fwdResponse(const RWCString& resp,
				      const RWCString& es,
				      	    int	       devId)
{
    TRACE_IN(trace, fwdResponse, resp);

    CHA_ImmRespBuffer* response = new CHA_ImmRespBuffer(resp, "", es, devId);

    if(receptionState == IDLE)
    {
	if(buffer != NULL)
	    delete buffer;
	buffer = response;

	if(accumulatedResp != NULL)
	    delete accumulatedResp;
	accumulatedResp = new CHA_ImmRespBuffer(*buffer);

	responseComplete = TRUE;
	newResponse = TRUE;
	changed(buffer);
	newResponse = FALSE;
    }
    else
    {
	responseQue.append(response);
    }
    TRACE_OUT(trace, fwdResponse, "");
}


//**********************************************************************


void CHA_ImmRespReceiver::fwdResponse(const RWCString& resp,
				      const RWCString& es)
{
    TRACE_IN(trace, fwdResponse, resp);

    CHA_ImmRespBuffer* response = new CHA_ImmRespBuffer(resp, "", es);

    if(receptionState == IDLE)
    {
	if(buffer != NULL)
	    delete buffer;
	buffer = response;

	if(accumulatedResp != NULL)
	    delete accumulatedResp;
	accumulatedResp = new CHA_ImmRespBuffer(*buffer);

	responseComplete = TRUE;
	newResponse = TRUE;
	changed(buffer);
	newResponse = FALSE;
    }
    else
    {
	responseQue.append(response);
    }
}


//**********************************************************************

CHA_ImmRespReceiver::ReturnCode CHA_ImmRespReceiver::newCommand(WinFIOLClient* wf) {
    wfClient = wf;
    pendingCancel = FALSE;

    if(buffer != NULL)
        delete buffer;
    buffer = new CHA_ImmRespBuffer("", "", "");

    if(accumulatedResp != NULL)
        delete accumulatedResp;
    accumulatedResp = new CHA_ImmRespBuffer(*buffer);

    // notify all ModelClients
    responseComplete = FALSE;
    newResponse = TRUE;
    changed(buffer);
    newResponse = FALSE;

    receptionState = WAITING;
    TRACE_RETURN(trace, newCommand, "OKAY");
    return OKAY;
}

/*CHA_ImmRespReceiver::ReturnCode CHA_ImmRespReceiver::newCommand(const RWCString& cmd,
								const RWCString& pmt,
								const RWCString& es,
								      int	 devId)*/
CHA_ImmRespReceiver::ReturnCode CHA_ImmRespReceiver::newCommand(const RWCString& cmd,
								const RWCString& pmt,
								const RWCString& es,
								/*int	 devId,*/
								WinFIOLClient* wf)
{
	wfClient = wf;
        cmdRespCode = OKAY;
    TRACE_IN(trace, newCommand, cmd);

    // check that we're not out of sync with the command sender
    // this is an error state that is totally unexpected
    if(receptionState != IDLE)
    {
	TRACE_RETURN(trace, newCommand, "FAILED");
	return FAILED;
    }

    command = cmd;
    esName = es;
    //deviceId = devId;
    pendingCancel = FALSE;

    if(buffer != NULL)
	delete buffer;

    //if(wf->isAplocMode())
    /*std::string cmdStr(command);
    if(wfClient->isAplocMode() || boost::iequals(cmdStr, "aploc;"))
    {
        buffer = new CHA_ImmRespBuffer(pmt+"\n", command, esName, deviceId);
    }
    else {
        buffer = new CHA_ImmRespBuffer(pmt+command+"\n", command, esName, deviceId);
    }*/
    buffer = new CHA_ImmRespBuffer(pmt+command+"\n", command, esName, deviceId);

    if(accumulatedResp != NULL)
	delete accumulatedResp;
    accumulatedResp = new CHA_ImmRespBuffer(*buffer);

    // notify all ModelClients
    responseComplete = FALSE;
    newResponse = TRUE;
    changed(buffer);
    newResponse = FALSE;

    receptionState = WAITING;
    TRACE_RETURN(trace, newCommand, "OKAY");
    return OKAY;
}


//**********************************************************************


CHA_ImmRespReceiver::ReturnCode CHA_ImmRespReceiver::newCommand(const RWCString& cmd,
								const RWCString& pmt,
								const RWCString& es)
{
    TRACE_IN(trace, newCommand, cmd);

    // check that we're not out of sync with the command sender
    // this is an error state that is totally unexpected
    if(receptionState != IDLE)
    {
	TRACE_RETURN(trace, newCommand, "FAILED");
	return FAILED;
    }

    command = cmd;
    esName = es;
    pendingCancel = FALSE;

    if(buffer != NULL)
	delete buffer;
    buffer = new CHA_ImmRespBuffer(pmt+command+"\n", command, esName);

    if(accumulatedResp != NULL)
	delete accumulatedResp;
    accumulatedResp = new CHA_ImmRespBuffer(*buffer);

    // notify all ModelClients
    responseComplete = FALSE;
    newResponse = TRUE;
    changed(buffer);
    newResponse = FALSE;

    receptionState = WAITING;
    TRACE_RETURN(trace, newCommand, "OKAY");
    return OKAY;
}


//**********************************************************************


CHA_ImmRespReceiver::ReturnCode CHA_ImmRespReceiver::receiveResponse(WinFIOLClient* pResp)
{
    TRACE_IN(trace, receiveResponse, "");

    // check that we're not out of sync with the command sender
    // this is an error state that is totally unexpected
    if(receptionState != WAITING)
    {
	 CHA_SeqDelRespReceiver::updateSendState(0); // Changed due to DEL RSP problem.Indicate that start phase of new sending
     TRACE_FLOW(trace, receiveResponse, "updateSendState 0");
	TRACE_RETURN(trace, receiveResponse, "FAILED");
	return FAILED;
    }

    receptionState = RECEIVING;
    wfClient = pResp;

    if(pendingCancel)
	cancelResponse();
     
    /*std::string responseStr = wfClient->getResponsedata();
    if(responseStr.find(RESP_NOT_ACCEPTED) != std::string::npos) {
        readBuffers(TRUE);
        return NOT_ACCEPTED;
    }
    else if (responseStr.find(RESP_PARTLY_EXECUTED) != std::string::npos) {
        readBuffers(TRUE);
        return PARTLY_EXECUTED;
    }
    else if (responseStr.find(RESP_INCOMPLETE) != std::string::npos) {
        readBuffers(TRUE);
        return INCOMPLETE;
    }
    else if (responseStr.find(RESP_FUNCTION_BUSY) != std::string::npos) {
        readBuffers(TRUE);
        return FUNCTION_BUSY;
    }
    else {
        readBuffers(TRUE);
        TRACE_RETURN(trace, receiveResponse, "OKAY");
        return OKAY;
    }*/

    int counter=0;
     while (!isDoneProcessing && (counter<10)) {
        TRACE_FLOW(trace, receiveResponse, "Waiting for readPrintout thread to finish...");
        usleep(500000); // sleep for 500 msec
        counter++;
    }

    readBuffers(TRUE);
    return cmdRespCode;
}

//**********************************************************************


//CHA_ImmRespReceiver::ReturnCode CHA_ImmRespReceiver::receiveConfirmResponse(EAC_CRI_Im_Resp* pResp)
CHA_ImmRespReceiver::ReturnCode CHA_ImmRespReceiver::receiveConfirmResponse(WinFIOLClient* pResp)
{
    TRACE_IN(trace, receiveConfirmResponse, "");


    RWBoolean tmpResponseComplete = responseComplete;
    RWBoolean tmpNewResponse      = newResponse;
    State tmpReceptionState       = receptionState;

    // check that we're not out of sync with the command sender
    // this is an error state that is totally unexpected
    if(receptionState != WAITING)
    {

	CHA_SeqDelRespReceiver::updateSendState(0); // Changed due to DEL RSP problem.Indicate that start phase of new sending

     TRACE_FLOW(trace, receiveConfirmResponse, "updateSendState 0");
     TRACE_RETURN(trace, receiveConfirmResponse, "FAILED");
     return FAILED;
    }

    wfClient = pResp;

    readBuffers(TRUE, FALSE);

   RWCString str="";
    // Reset (empty) the buffers.
    if(buffer != NULL)
      delete buffer;
    buffer = new CHA_ImmRespBuffer(str, command, esName, deviceId);

    if(accumulatedResp != NULL)
      delete accumulatedResp;
    accumulatedResp = new CHA_ImmRespBuffer(*buffer);

    TRACE_FLOW(trace, receiveConfirmResponse, "Reset receptionState, responseComplete and newResponse after reading the confirm buffer");
    responseComplete = tmpResponseComplete;
    newResponse      = tmpNewResponse;
    receptionState   = tmpReceptionState;

    TRACE_RETURN(trace, receiveConfirmResponse, "OKAY");
    return OKAY;
}


//**********************************************************************


void CHA_ImmRespReceiver::skipResponse()
{
    TRACE_IN(trace, skipResponse, "");

     CHA_SeqDelRespReceiver::updateSendState(0); // Changed due to DEL RSP problem.Indicate that start phase of new sending

     TRACE_FLOW(trace, skipResponse, "updateSendState 0");

    if(receptionState == IDLE)
	return;

    if(receptionState == RECEIVING)
	readBuffers(FALSE);		// read whatever is there

    pendingCancel = FALSE;

    if(receptionState != IDLE)
    {
	responseComplete = TRUE;
	newResponse = FALSE;

	if(buffer != NULL)
	    delete buffer;
        const char* String="";
	if (deviceId > 0)
	    buffer = new CHA_ImmRespBuffer((RWCString)"", command, esName, deviceId);
            //buffer = new CHA_ImmRespBuffer("", command, esName, deviceId);
	else
	    buffer = new CHA_ImmRespBuffer((RWCString)"", command, esName);

	// notify all model clients
	changed(buffer);

	receptionState = IDLE;

	// empty the que of "faked" responses
	flushResponseQue();
    }
}


//**********************************************************************


void CHA_ImmRespReceiver::readBuffers(RWBoolean notifySender, RWBoolean goIdle)
{
    TRACE_IN(trace, readBuffers, notifySender);

    // read all available buffers into bufferStr
    RWCString bufferStr = "";
    std::string respStr = wfClient->getResponsedata();

    if (cmdRespCode == NOT_AUTHORIZED) {
        return;
    }

    if (respStr.find(RESP_FUNCTION_BUSY) != std::string::npos) {
        cmdRespCode = FUNCTION_BUSY;
    }

    bufferStr += respStr;
	
	// Check for ORDERED, to enable as quick subscription
	// for delayed as possible.
	// Especially needed towards S12 since EHQ doesn't store
	// delayed for a little while as EHM does.
	/*if(pImmResp->Get_immediate_response_type() == EAC_CRI_IRT_ORDERED)
	  {
	     CHA_SeqDelRespReceiver::updateSendState(1); // Changed due to DEL RSP problem.Indicate that start phase of new sending

	     //TRACE_FLOW(trace, readBuffers, "updateSendState 1");
	    pCommandSender->expectingDelayed();
	  }
	else
	  {*/
	     CHA_SeqDelRespReceiver::updateSendState(0); // Changed due to DEL RSP problem.Indicate that start phase of new sending

	     //TRACE_FLOW(trace, readBuffers, "updateSendState 0");
	/*  }
    }

    // check if the response is complete, can also happen due to an error
    if(pImmResp->Is_response_complete())
    {
	//TRACE_FLOW(trace, readBuffers, "complete response");*/

	responseComplete = TRUE;
	newResponse = FALSE;	// just to be on the safe side

        // HD45123: When running in APG mode (sending commands to the APG) the
        // prompt must be displayed, so that the confirmation requests (which is
        // treated as a prompt) are displayed. The command "alogdeact", which
        // was mentioned in the TR, is one example of such a command.
	    // HD94591: Will also make OPS to accept the prompt ":" with prefix.
	/* const char* prmpt = pImmResp->Get_response_prompt();
        if (prmpt != NULL && (isAPMode || prmpt[strlen(prmpt) - 1] == ':'))
	  {

		//TRACE_FLOW(trace, readBuffers, "prmpt: " << prmpt);
		bufferStr += prmpt;
		bufferStr += "\n";
	  }*/


	if(buffer != NULL)
	    delete buffer;

        // deviceId is not used currently.

        /*if (deviceId > 0)
	   buffer = new CHA_ImmRespBuffer(bufferStr+"\n", command, esName, deviceId);
	else
	    buffer = new CHA_ImmRespBuffer(bufferStr+"\n", command, esName);*/

        if (!bufferStr.compareTo("\n",RWCString::exact) || bufferStr.isNull())
        {
           TRACE_FLOW(trace, readBuffers, "response is null or a  newline");
           buffer = new CHA_ImmRespBuffer(bufferStr, command, esName);
        }
        else {
           buffer = new CHA_ImmRespBuffer(bufferStr+"\n", command, esName);
        }

	accumulatedResp->append(*buffer);


	// notify all ModelClients
	changed(buffer);
        bufferStr = "";

	// perhaps some error message should be presented, i.e. the response
	// was actually not complete, but cut off due to an error.
	/*switch(retCode)
	{
	case EAC_CRI_NO_MORE_BUFS:
	case EAC_CRI_TIMEOUT:
	case EAC_CRI_PMS_MSG_RECEIVED:
	    break;		// no error
	case EAC_CRI_ERR_NO_COMMUNICATION:
	    break;		// handled by conn. supervisor
	case EAC_CRI_ERR_BUFFER_TIMEOUT:
	    errorReporter.message(nlsCat.getMessage(NLS_IMMREC_TIMEOUT));
	    break;
	case EAC_CRI_ES_REQUEST_REFUSAL:
	case EAC_CRI_ERROR:
	    errorReporter.message(nlsCat.getMessage(NLS_IMMREC_FAILED));
	    break;
	default:
	    break;		// no error
	}*/

	// empty the que of "faked" responses
	flushResponseQue();

	if (goIdle == TRUE)
	{
	  receptionState = IDLE;

	  // Notify sender that you now are IDLE

	  if(notifySender)
	  {
	    // notify the command sender
	    /* const char* prompt = pImmResp->Get_response_prompt();
	    if(prompt == NULL)
		prompt = "";
	    pCommandSender->immResponseReceived(prompt);*/
           const char* prompt = "";
            pCommandSender->immResponseReceived(prompt);
	  }
	}

   /* }
    else
    {
	 The response isn't complete but there are no
	 more buffers for now.*/

	// check if we got any buffers
	/*if(bufferStr.length() > 0)
	{
	    if(buffer != NULL)
		delete buffer;

	if (deviceId > 0)
	   buffer = new CHA_ImmRespBuffer(bufferStr, command, esName, deviceId);
	else
	    buffer = new CHA_ImmRespBuffer(bufferStr, command, esName);

	    accumulatedResp->append(*buffer);

	    // notify all ModelClients
	    changed(buffer);
	}*/
    //}
     TRACE_OUT(trace, readBuffers, "");
}


//**********************************************************************


void CHA_ImmRespReceiver::flushResponseQue()
{
    TRACE_IN(trace, flushResponseQue, "");

    while(!responseQue.isEmpty())
    {
	if(buffer != NULL)
	    delete buffer;
	buffer = responseQue.get();

	if(accumulatedResp != NULL)
	    delete accumulatedResp;
	accumulatedResp = new CHA_ImmRespBuffer(*buffer);

	responseComplete = TRUE;
	newResponse = TRUE;
	changed(buffer);
	newResponse = FALSE;
    }
}


//**********************************************************************


void CHA_ImmRespReceiver::updateFrom(CHA_Model* model, void* pData)
{
    // if we're not waiting for IPC, return quickly
    if(receptionState != RECEIVING)
	return;

    readBuffers(TRUE);
}


//**********************************************************************


void CHA_ImmRespReceiver::detachFrom(CHA_Model* model)
{
    if(model == (CHA_Model*) pIpcSupervisor)
	pIpcSupervisor = NULL;
}

void CHA_ImmRespReceiver::setApMode(RWBoolean isAPModeIn)
{
    isAPMode = isAPModeIn;
}

CHA_ImmRespReceiver::ReturnCode CHA_ImmRespReceiver::getResponseCode()
{
    CHA_ImmRespReceiver::ReturnCode tmpRespCode = cmdRespCode;
    cmdRespCode = OKAY;
    return tmpRespCode;
}

//**********************************************************************

void CHA_ImmRespReceiver::readPrintouts()
{
    // code here for reading printouts
    while (1) {
        // check if WfClient is up and initialized
        if (wfClient) {
            isDoneProcessing = TRUE;
            RWCString bufferStr = "";
            std::deque<RWCString> responses = wfClient->getImmediatePrintouts();
            while(!responses.empty()) {
                bufferStr = responses.front();
                responses.pop_front();

                if(bufferStr.length() == 0) {
                    continue;
                } else {
                    isDoneProcessing = FALSE;
                    if (bufferStr.contains(RESP_FUNCTION_BUSY)) {
                        cmdRespCode = FUNCTION_BUSY;
                    } else if (bufferStr.contains(RESP_SYNTAX_FAULT)) {
                         cmdRespCode = NOT_AUTHORIZED;
                         continue;
                    } else if (bufferStr.contains(RESP_CMD_UNKNOWN)) {
                         cmdRespCode = NOT_AUTHORIZED;
                    }

                    if(buffer != NULL)
                        delete buffer;
                    buffer = new CHA_ImmRespBuffer(bufferStr, command, esName);

                    accumulatedResp->append(*buffer);

                    // notify all ModelClients
                    changed(buffer);
                    flushResponseQue();
                }
            }
        } else {
            // wait untill wfClient is up and running
            sleep(1);
        }
    }
}

//**********************************************************************

void* CHA_ImmRespReceiver::readPrintoutsThread(void* x)
{
    ((CHA_ImmRespReceiver*)x)->readPrintouts();
    return NULL;
}

void CHA_ImmRespReceiver::createDetachedReadThread()
{
    TRACE_IN(trace, createDetachedReadThread, "");

    pthread_attr_init(&detachedReadThreadAttr);
    pthread_attr_setdetachstate(&detachedReadThreadAttr,PTHREAD_CREATE_DETACHED);

    if (pthread_create(&pReadThread, &detachedReadThreadAttr, &CHA_ImmRespReceiver::readPrintoutsThread, (void *)this)) {
        TRACE_FLOW(trace, initReadThreadAttr, "Error creating thread");
    }

    TRACE_OUT(trace, createDetachedReadThread, "");
}

//*********************************************************************
