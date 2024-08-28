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

#include <CHA_Trace.H>
#include <CHA_LibGlobals.H>
#include <CHA_LibNLS.H>
#include <CHA_SpDelReceiver.H>
#include <trace.H>
static std::string trace ="CHA_SpDelReceiver";


//**********************************************************************


CHA_SpDelReceiver::CHA_SpDelReceiver(CHA_IPCSupervisor* pSup,
				     const RWCString& appN)
: pIpcSupervisor(pSup),
  applicationName(appN),
 // connection(appN),
 // association(connection),
 // command(),
  nlsCat(CHA_LibNLSCatalog),
  receptionState(IDLE),
  cmdString(NULL),
  esName(NULL),
  deviceId(-1)
{
    if(pIpcSupervisor != NULL)
	pIpcSupervisor->addDependent(this);
}


//**********************************************************************


CHA_SpDelReceiver::~CHA_SpDelReceiver()
{
    if(pIpcSupervisor != NULL)
	pIpcSupervisor->removeDependent(this);
}


//**********************************************************************


void CHA_SpDelReceiver::cancelResponse()
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


void CHA_SpDelReceiver::updateFrom(CHA_Model* model, void* pData)
{
    TRACE_IN(trace, updateFrom, "");
    if(receptionState == RECEIVING)
	readBuffers();
    else
	checkNewResponse();
}


//**********************************************************************


void CHA_SpDelReceiver::detachFrom(CHA_Model* model)
{
    if(model == (CHA_Model*) pIpcSupervisor)
	pIpcSupervisor = NULL;
}


//**********************************************************************


void CHA_SpDelReceiver::checkNewResponse()
{
   // EAC_CLI_Command cmd;
    //EAC_CLI_Search  search;
    char*           tmpStr = NULL;

    TRACE_IN(trace, checkNewResponse, "");

  /*  switch(receiveResponse())
    {
   // case EAC_CRI_OK:
    case EAC_CRI_ALREADY_RECEIVED:
        {
	    //TRACE_FLOW(trace, checkNewResponse, "new response.");
	    receptionState = RECEIVING;
	    responseComplete = FALSE;
	    newResponse = TRUE;

	    if(buffer != NULL)
		delete buffer;

	    cmd.Reset_search_criteria();

	    esName = NULL;
	    esName = connection.Get_es_name();
	    if(esName == NULL)
		esName = "";   // Can`t send NULL pointer to createBuffer

	    deviceId = association.Get_assoc_id();

	    cmd.Set_association_id(deviceId);

	    cmdString = NULL;

	    if(search.Set_search(cmd) != EAC_CLI_SUCCEED)
	    {
		// Couldn't set search criteria
		cmdString = NULL;
	    }

	    while(search.Get_result(cmd) != EAC_CLI_LOG_EXHAUSTED)
	    {
		// Search until there is no more hits
		if(tmpStr != NULL) delete [] tmpStr;
		cmdString = cmd.Return_command_string();
		tmpStr = new char[strlen(cmdString)+1];
		strcpy(tmpStr,cmdString);
		cmdString = tmpStr;
	    }

	    if(cmdString == NULL)
		cmdString = ""; // Can`t send NULL pointer to createBuffer

	    if (deviceId > 0)
	        buffer = createBuffer(" ", cmdString, esName, deviceId);
	    else
		buffer = createBuffer(" ", cmdString, esName);

	    if(accumulatedResp != NULL)
		delete accumulatedResp;
	    accumulatedResp = createAccumulatedBuffer();
	    readBuffers();

	    if(tmpStr != NULL) delete [] tmpStr;
	}
	break;
    default:			// otherwise just skip it
	// //TRACE_FLOW(trace, checkNewResponse, "no buffers from EA");
	break;
    }*/
}


//**********************************************************************


void CHA_SpDelReceiver::readBuffers()
{
    // read all available buffers into bufferStr
    RWCString bufferStr;
    int retCode = getResponseBuffer(bufferStr);

    TRACE_FLOW(trace,readBuffers,bufferStr);
    // check if the response is complete, can also happen due to an error
    if(completeResponse())
    {
	TRACE_FLOW(trace, readBuffers, "Response. complete");

	responseComplete = TRUE;

	if(buffer != NULL)
	    delete buffer;

	if (deviceId > 0)
	    buffer = createBuffer(bufferStr, cmdString, esName, deviceId);
	else
	    buffer = createBuffer(bufferStr, cmdString, esName);

	accumulatedResp->append(*buffer);

	// notify all ModelClients
	changed(buffer);

	newResponse = FALSE;

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
	    errorReporter.message(nlsCat.getMessage(NLS_DELREC_TIMEOUT));
	    break;
	case EAC_CRI_ES_REQUEST_REFUSAL:
	case EAC_CRI_ERROR:
	    errorReporter.message(nlsCat.getMessage(NLS_DELREC_FAILED));
	    break;
	default:
	    break;		// no error
	}*/

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

	    if (deviceId > 0)
	        buffer = createBuffer(bufferStr, cmdString, esName, deviceId);
	    else
		buffer = createBuffer(bufferStr, cmdString, esName);

	    accumulatedResp->append(*buffer);

	    // notify all ModelClients
	    changed(buffer);
	    newResponse = FALSE; // not new anymore
	}
    }

}


//**********************************************************************


RWBoolean CHA_SpDelReceiver::isLastInSequence() const
{
    /* TRACE_FLOW(trace, isLastInSequence,
	       "connection mode = " << connection.Get_connection_mode());*/

   // return (connection.Get_connection_mode() != EAC_CRI_CM_REPORT);
}


//**********************************************************************
