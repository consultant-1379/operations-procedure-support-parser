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

//#include <eac_cli_search.H>
//#include <eac_cli_retrieval.H>

#include <CHA_Trace.H>
#include <CHA_LibGlobals.H>
#include <CHA_LibNLS.H>
#include <CHA_DelRespHandler.H>
#include <CHA_DelRespBuffer.H>
#include <CHA_SeqDelRespReceiver.H>
#include <trace.H>

static std::string trace ="CHA_SeqDelRespReceiver";

//**********************************************************************

CHA_SeqDelRespReceiver::CHA_SeqDelRespReceiver(CHA_IPCSupervisor* pSup,
				               const RWCString& appN)
: pIpcSupervisor(pSup),
  applicationName(appN),
  /*connection(appN),
  association(connection),
  command(),*/
  nlsCat(CHA_LibNLSCatalog),
  receptionState(IDLE),
  cmdString(NULL),
  esName(NULL),
  deviceId(-1)
  //delResponse()
{
    TRACE_IN(trace,CHA_SeqDelRespReceiver,"");
    if(pIpcSupervisor != NULL)
	pIpcSupervisor->addDependent(this);
}


//**********************************************************************


CHA_SeqDelRespReceiver::~CHA_SeqDelRespReceiver()
{
    if(pIpcSupervisor != NULL)
	pIpcSupervisor->removeDependent(this);
}

//**********************************************************************

void CHA_SeqDelRespReceiver::cancelResponse()
{
   TRACE_IN(trace, cancelResponse, "");

    if(receptionState == RECEIVING)
    {
	/*switch(interruptResponse())
	{
	case EAC_CRI_OK:
	    //	    fwdResponse(nlsCat.getMessage(NLS_DELRESP_INTR), "");
	    break;

	case EAC_CRI_ERR_NO_RESPONSE_RECEPTION:
	    errorReporter.message(nlsCat.getMessage(NLS_DELRESP_NOTRECEIVING));
	    break;

	case EAC_CRI_ERR_ES_DONT_SUPPORT_INTERRUPTION:
	    errorReporter.message(nlsCat.getMessage(NLS_DELRESP_NOTSUPPORTED));
	    break;

	case EAC_CRI_ERR_INTERRUPT_FAILED:
	case EAC_CRI_ERR_NO_COMMUNICATION:
	case EAC_CRI_ERROR:
	default:
	    errorReporter.message(nlsCat.getMessage(NLS_DELRESP_INTR_FAILED));
	    break;
	}*/
    }
    else
    {
	errorReporter.message(nlsCat.getMessage(NLS_DELRESP_NOTRECEIVING));
    }

}


//**********************************************************************

int CHA_SeqDelRespReceiver::receiveResponse()
{
   // return association.Receive_delayed_resp(&delResponse,&command);
}


//**********************************************************************

CHA_ResponseBuffer* CHA_SeqDelRespReceiver::createBuffer(
                                                    const char* bufferString,
                                                    const char* theCommand,
						    const char* theEsName,
							  int   devId)
{
    //TORF-241666return new CHA_DelRespBuffer(bufferString,theCommand,theEsName,devId);
    return new CHA_DelRespBuffer(RWCString(bufferString),RWCString(theCommand),RWCString(theEsName),devId);
}


//**********************************************************************

void CHA_SeqDelRespReceiver::updateFrom(CHA_Model* model, void* pData)
{
  TRACE_IN(trace, updateFrom, "");
  //Changed due to DEL RSP problem
  if (orderedFlag == 0) // Ordered is off and all buffer should be store to be used at logOf
    {
      TRACE_FLOW(trace, updateFrom, "orderedFlag  OFF");
      if(receptionState == RECEIVING)
	readBuffers();
      else
	checkNewResponse();
    }
  else
    {
      TRACE_FLOW(trace, updateFrom, "orderedFlag  ON");
      if (sendFlag == 1) // It means that we are waitting for the first time to receive DEL Rsp.
	{
	  TRACE_FLOW(trace, updateFrom, "sendFlag == 1");
	  if (waitDlRspFlag == 1)
	    {
	      updateSendState(0);
	      TRACE_FLOW(trace, updateFrom, "sendFlag is set to 0");
	      TRACE_FLOW(trace, updateFrom, "waitDlRspFlag  TRUE");
	      if(receptionState == RECEIVING)
		readBuffers();
	      else
		checkNewResponse();
	    }
	}
      else
	{
	  TRACE_FLOW(trace, updateFrom, "sendFlag == 0");
	   if(receptionState == RECEIVING)
		readBuffers();
	      else
		checkNewResponse();
	}
    }


}

//**********************************************************************

void CHA_SeqDelRespReceiver::detachFrom(CHA_Model* model)
{
    if(model == (CHA_Model*) pIpcSupervisor)
	pIpcSupervisor = NULL;
}

//**********************************************************************

CHA_ResponseBuffer* CHA_SeqDelRespReceiver::createBuffer(
                                                    const char* bufferString,
                                                    const char* theCommand,
						    const char* theEsName)
{
    return new CHA_DelRespBuffer(bufferString,theCommand,theEsName);
}


//**********************************************************************

CHA_ResponseBuffer* CHA_SeqDelRespReceiver::createAccumulatedBuffer()
{
    return new CHA_DelRespBuffer(*buffer);
}


//**********************************************************************


int CHA_SeqDelRespReceiver::getResponseBuffer(RWCString& bufferStr)
{
    int retCode;
    const char* respStr;

    /*while((retCode = delResponse.Get_buffer(respStr,0)) > 0)
    {
	bufferStr += respStr;
    }
    TRACE_FLOW(trace, getResponseBuffer, bufferStr);*/
    //return retCode;
}


//**********************************************************************

int CHA_SeqDelRespReceiver::completeResponse()
{
   // return delResponse.Is_response_complete();
}

//**********************************************************************

int CHA_SeqDelRespReceiver::interruptResponse()
{
    //return delResponse.Interrupt_response();
}

//**********************************************************************

void CHA_SeqDelRespReceiver::checkNewResponse()
{
    TRACE_IN(trace, checkNewResponse, "");

   /* switch(receiveResponse())
    {
    case EAC_CRI_OK:
    case EAC_CRI_ALREADY_RECEIVED:
        {
	    //TRACE_FLOW(trace, checkNewResponse, "new response.");
	    receptionState = RECEIVING;
	    responseComplete = FALSE;
	    newResponse = TRUE;

	    if(buffer != NULL)
		delete buffer;

	    esName = NULL;
	    esName = connection.Get_es_name();
	    if(esName == NULL)
		esName = "";   // Can`t send NULL pointer to createBuffer

	    deviceId = association.Get_assoc_id();
	    cmdString = NULL;

	    if(cmdString == NULL)
		cmdString = ""; // Can`t send NULL pointer to createBuffer

	    if (deviceId != -1)
	        buffer = createBuffer(" ", cmdString, esName, deviceId);
	    else
		buffer = createBuffer(" ", cmdString, esName);

	    if(accumulatedResp != NULL)
		delete accumulatedResp;
	    accumulatedResp = createAccumulatedBuffer();
	    readBuffers();
	}
	break;
    default:	*/		// otherwise just skip it
	TRACE_FLOW(trace, checkNewResponse, "no buffers from EA");
	//break;
   // }
}


//**********************************************************************


void CHA_SeqDelRespReceiver::readBuffers()
{
    TRACE_IN(trace,readBuffers, "");
    // read all available buffers into bufferStr
    RWCString bufferStr;
    int retCode = getResponseBuffer(bufferStr);

    TRACE_FLOW(trace,readBuffers,bufferStr);
    // check if the response is complete, can also happen due to an error
   /* if(completeResponse())
    {
	//TRACE_FLOW(trace, readBuffers, "Response. complete");

	responseComplete = TRUE;

	if(buffer != NULL)
	    delete buffer;

	if (deviceId != -1)
	    buffer = createBuffer(bufferStr, cmdString, esName, deviceId);
	else
	    buffer = createBuffer(bufferStr, cmdString, esName);

	accumulatedResp->append(*buffer);

	// notify all ModelClients
	changed(buffer);

	newResponse = FALSE;

	// perhaps some error message should be presented, i.e. the response
	// was actually not complete, but cut off due to an error.
	switch(retCode)
	{
	case EAC_CRI_NO_MORE_BUFS:
	case EAC_CRI_TIMEOUT:
	case EAC_CRI_PMS_MSG_RECEIVED:
	    break;		// no error
	case EAC_CRI_ERR_NO_COMMUNICATION:
	    break;		// handled by conn. supervisor
	case EAC_CRI_ERR_BUFFER_TIMEOUT:
	    errorReporter.message(nlsCat.getMessage(NLS_DELREC_TIMEOUT));
	    break;
	case EAC_CRI_ES_REQUEST_REFUSAL:
	case EAC_CRI_ERROR:
	    errorReporter.message(nlsCat.getMessage(NLS_DELREC_FAILED));
	    break;
	default:
	    break;		// no error
	}

	receptionState = IDLE;
    }
    else
    {
	// The response isn't complete but there are no
	// more buffers for now.

	responseComplete = FALSE;

	// check if we got any buffers
	if(bufferStr.length() > 0)
	{

	    if(buffer != NULL)
		delete buffer;

	    if (deviceId != -1)
	        buffer = createBuffer(bufferStr, cmdString, esName, deviceId);
	    else
		buffer = createBuffer(bufferStr, cmdString, esName);

	    accumulatedResp->append(*buffer);

	    // notify all ModelClients
	    changed(buffer);
	    newResponse = FALSE; // not new anymore
	}
    }*/

}


//**********************************************************************


RWBoolean CHA_SeqDelRespReceiver::isLastInSequence() const
{
    /*//TRACE_FLOW(trace, isLastInSequence,
	       "connection mode = " << connection.Get_connection_mode());

    return (connection.Get_connection_mode() != EAC_CRI_CM_REPORT);*/
}


//**********************************************************************
void CHA_SeqDelRespReceiver::updateOZTWaitDlRsp(int OZTwaitDlRsp)
{
  TRACE_IN(trace,updateOZTWaitDlRsp, OZTwaitDlRsp);
  waitDlRspFlag = OZTwaitDlRsp;
  TRACE_OUT(trace,updateOZTWaitDlRsp, OZTwaitDlRsp);
}

//**********************************************************************
void CHA_SeqDelRespReceiver::updateOrderState(int ordered)
{
  TRACE_IN(trace,updateOrderState, ordered);
  orderedFlag = ordered;
  TRACE_OUT(trace,updateOrderState, ordered);
}

//**********************************************************************
void CHA_SeqDelRespReceiver::updateSendState(int sendState)
{
  TRACE_IN(trace,updateSendState, sendState);
  sendFlag = sendState;
  TRACE_OUT(trace,updateSendState, sendState);
}


int CHA_SeqDelRespReceiver::waitDlRspFlag = 0; // 0 Means WAIT_DEL_RSP not true. 1 means WAIT_DEL_RSP true

int CHA_SeqDelRespReceiver::orderedFlag = 1; // 0 Means ordered off. 1 means ordered on true

int CHA_SeqDelRespReceiver::sendFlag = 0; // 0 Means ordered off. 1 means ordered on true
