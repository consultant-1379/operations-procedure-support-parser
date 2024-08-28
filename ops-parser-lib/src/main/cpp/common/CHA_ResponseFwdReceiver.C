/*------------------------------------------------------------------------------
 ********************************************************************************
 * COPYRIGHT Ericsson 2018
 *
 * The copyright to the computer program(s) herein is the property of
 * Ericsson Inc. The programs may be used and/or copied only with written
 * permission from Ericsson Inc. or in accordance with the terms and
 * conditions stipulated in the agreement/contract under which the
 * program(s) have been supplied.
 ********************************************************************************
 *----------------------------------------------------------------------------*/


#include <CHA_LibGlobals.H>
//#include <CHA_Trace.H>
#include <CHA_LibNLS.H>
#include <CHA_ResponseFwdReceiver.H>

#include <trace.H>
static std::string trace ="CHA_ResponseFwdReceiver";

//**********************************************************************


CHA_ResponseFwdReceiver::CHA_ResponseFwdReceiver(CHA_ResponseType respType)
  : pCurrentRespRcvr(NULL),
    myResponseType(respType)
{
    TRACE_IN(trace, CHA_ResponseFwdReceiver, "");
}


//**********************************************************************


CHA_ResponseFwdReceiver::~CHA_ResponseFwdReceiver()
{
    respToFwd.clearAndDestroy();
}


//**********************************************************************


void CHA_ResponseFwdReceiver::cancelResponse()
{
    TRACE_IN(trace, cancelResponse, "");

    if(pCurrentRespRcvr != NULL) pCurrentRespRcvr->cancelResponse();
}


//**********************************************************************


const CHA_ResponseBuffer* CHA_ResponseFwdReceiver::getBuffer() const
{
    
    if (pCurrentRespRcvr != NULL){
      TRACE_RETURN(trace, getBuffer, pCurrentRespRcvr->getBuffer());
      return pCurrentRespRcvr->getBuffer();
    }
    else{
      TRACE_RETURN(trace, getBuffer, buffer);
      return buffer;
    }
};


//**********************************************************************


const CHA_ResponseBuffer* CHA_ResponseFwdReceiver::getAccumulatedResponse() const
{
    if (pCurrentRespRcvr != NULL) {
      TRACE_RETURN(trace, getAccumulatedResponse, pCurrentRespRcvr->getAccumulatedResponse());
      return pCurrentRespRcvr->getAccumulatedResponse();
    }
    else {
      TRACE_RETURN(trace, getAccumulatedResponse, accumulatedResp);
      return accumulatedResp;
    }
};


//**********************************************************************


RWBoolean CHA_ResponseFwdReceiver::isCompleteResponse() const
{
    
    if (pCurrentRespRcvr != NULL){
      TRACE_RETURN(trace, isCompleteResponse, pCurrentRespRcvr->isCompleteResponse() );
      return pCurrentRespRcvr->isCompleteResponse();
    }    
    else {
      TRACE_RETURN(trace, isCompleteResponse, responseComplete);
      return responseComplete;
    }
};


//**********************************************************************


RWBoolean CHA_ResponseFwdReceiver::isNewResponse() const
{
    if (pCurrentRespRcvr != NULL){
      TRACE_RETURN(trace, isNewResponse, newResponse);
      return pCurrentRespRcvr->isNewResponse();
    }
    else{
      TRACE_RETURN(trace, isNewResponse, newResponse);
      return newResponse;
    }
};


//**********************************************************************


RWBoolean CHA_ResponseFwdReceiver::isLastInSequence() const
{
    RWBoolean returnValue = TRUE;

    if (pCurrentRespRcvr != NULL) 
	returnValue = pCurrentRespRcvr->isLastInSequence();
    else
	returnValue = TRUE;

    TRACE_RETURN(trace, isLastInSequence, returnValue);
    return returnValue;
};


//**********************************************************************


void CHA_ResponseFwdReceiver::updateFrom(CHA_Model* model, void* d)
{
  TRACE_IN(trace, updateFrom, model << ", " << d);
    
    // assume that it is a response receiver calling
  CHA_ResponseReceiver* tmpRcvr = (CHA_ResponseReceiver*) model;
  const CHA_ResponseBuffer* tmpBuffer = tmpRcvr->getBuffer();

  TRACE_FLOW(trace, updateFrom, "tmpBuffer=" << tmpBuffer );
  
  if(tmpBuffer->getRespType() == myResponseType)
    {
      if(pCurrentRespRcvr == NULL)
	{
	  TRACE_FLOW(trace, updateFrom, "pCurrentRespRcvr == NULL" );
	  pCurrentRespRcvr=tmpRcvr;
	  changed();
	  if(pCurrentRespRcvr->isCompleteResponse()){
	    fwdFromList();
	  }
	}
      else if(tmpRcvr == pCurrentRespRcvr)
	{
	  //Same receiver as before, just forward the buffer
	  TRACE_FLOW(trace, updateFrom, "Same receiver as before, just forward the buffer" );
	  changed();
	  
	  if(pCurrentRespRcvr->isCompleteResponse()){
	    fwdFromList();
	  }
	}
      else if(tmpRcvr->isCompleteResponse())
	{
	  TRACE_FLOW(trace, updateFrom, " store the buffer temporarily before it gets lost" );
	  // store the buffer temporarily before it gets lost
	  respToFwd.append(tmpRcvr->getAccumulatedResponse()->copy());
	}
    }
    TRACE_OUT(trace, updateFrom, "");

}


//**********************************************************************


void CHA_ResponseFwdReceiver::detachFrom(CHA_Model* model)
{
  if(model == (CHA_Model*)pCurrentRespRcvr)
    pCurrentRespRcvr = NULL;
}

//**********************************************************************

 
void CHA_ResponseFwdReceiver::fwdFromList()
{
    TRACE_IN(trace, fwdFromList, "");
    
    // This is necessary, because we don't have a response receiver
    // for these temporarily stored responses. Also
    // isCompleteResponse() will return always TRUE when this variable
    // is NULL.
    pCurrentRespRcvr = NULL;
          
    // A while loop would probably take more time to execute.
    
    const int entries = respToFwd.entries();

    TRACE_FLOW(trace, fwdFromList, "nr of entries=" << entries);
    
    for(int i = 0; i < entries; i++){
      if(accumulatedResp != NULL)
	delete accumulatedResp;
      
      if(buffer != NULL)
	delete buffer;
      
      accumulatedResp=respToFwd.get();
      buffer= accumulatedResp->copy();
      
      TRACE_FLOW(trace, fwdFromList, "buffer=" << buffer);
      
      responseComplete = TRUE;
      newResponse = TRUE;
      
      changed();
      newResponse = FALSE;
    }
    
    responseComplete = FALSE;
    
    // To be sure that the list is clear
    if( respToFwd.entries() != 0 ){
       
      TRACE_FLOW(trace, fwdFromList, "deleting entries =" << respToFwd.entries() );
      respToFwd.clearAndDestroy();
    }

    TRACE_OUT(trace, fwdFromList, "");

}
