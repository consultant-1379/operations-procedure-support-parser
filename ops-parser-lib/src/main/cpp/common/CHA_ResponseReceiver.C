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
#include <CHA_ResponseReceiver.H>

#include <trace.H>
static std::string trace ="CHA_ResponseReceiver";
 

//**********************************************************************


CHA_ResponseReceiver::CHA_ResponseReceiver()
: buffer(NULL),
  accumulatedResp(NULL),
  responseComplete(FALSE),
  newResponse(FALSE)
{
    TRACE_IN(trace, CHA_ResponseReceiver, "");
};

    
//**********************************************************************

CHA_ResponseReceiver::~CHA_ResponseReceiver()
{
    if(buffer != NULL)
	delete buffer;

    if(accumulatedResp != NULL)
	delete accumulatedResp;
};

//**********************************************************************

void CHA_ResponseReceiver::reset(void)
{
    TRACE_IN(trace, reset, "");

    if(buffer != NULL)
    {
	delete buffer;
	buffer = NULL;
    }

    if(accumulatedResp != NULL)
    {
	delete accumulatedResp;
	accumulatedResp = NULL;
    }
	
    TRACE_OUT(trace, reset, "");
}

//**********************************************************************

const CHA_ResponseBuffer* CHA_ResponseReceiver::getBuffer() const
{
    TRACE_RETURN(trace, getBuffer, " a buffer");
    return buffer;
};


//**********************************************************************


const CHA_ResponseBuffer* CHA_ResponseReceiver::getAccumulatedResponse() const
{
    TRACE_RETURN(trace, getAccumulatedResponse, " a buffer");
    return accumulatedResp;
};


//**********************************************************************


RWBoolean CHA_ResponseReceiver::isCompleteResponse() const
{
    TRACE_RETURN(trace, isCompleteResponse, responseComplete);
    return responseComplete;
};


//**********************************************************************


RWBoolean CHA_ResponseReceiver::isNewResponse() const
{
    TRACE_RETURN(trace, isNewResponse, newResponse);
    return newResponse;
};


//**********************************************************************


RWBoolean CHA_ResponseReceiver::isLastInSequence() const
{
    TRACE_RETURN(trace, isLastInSequence, "TRUE (default value)");
    return TRUE;
};


//**********************************************************************
