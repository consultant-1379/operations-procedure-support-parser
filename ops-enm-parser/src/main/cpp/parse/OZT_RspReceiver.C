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

#include <OZT_RspReceiver.H>
#include <OZT_EventHandler.H>

//*****************************************************************************


// trace
#include <CHA_Trace.H>
#include <trace.H>
static std::string trace ="OZT_RspReceiver";


//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_RspReceiver.C,v 21.0 1996/08/23 12:44:37 ehsgrap Rel $";


//*****************************************************************************

extern OZT_EventHandler *ozt_evHandlerPtr;

//*****************************************************************************

OZT_RspReceiver::OZT_RspReceiver(OZT_CmdRspBuf* _pCmdRspBuf,
                                 CHA_ResponseReceiver* _pImmReceiver,
                                 CHA_ResponseReceiver* _pDelReceiver,
                                 CHA_ResponseReceiver* _pSpontReceiver)
{
    pCmdRspBuf = _pCmdRspBuf;
    pImmReceiver = _pImmReceiver;
    pDelReceiver = _pDelReceiver;
    pSpontReceiver = _pSpontReceiver;
    if( pImmReceiver!=NULL && pDelReceiver!=NULL &&    pSpontReceiver!=NULL  ){ 
    pImmReceiver->addDependent(this);
    pDelReceiver->addDependent(this);
    pSpontReceiver->addDependent(this);}

    receivingDelRsp   = FALSE;
    receivingSpontRsp = FALSE;
    loggingOn         = TRUE;
    tryingToLogOn     = FALSE;
    aCompleteRspStored   = FALSE;
    storedDelRsp      = RWCString();
    storedSpontRsp    = RWCString();
}
OZT_RspReceiver::OZT_RspReceiver(OZT_CmdRspBuf* _pCmdRspBuf,
                                 CHA_ResponseReceiver* _pImmReceiver,
                                 CHA_ResponseReceiver* _pDelReceiver,
                                 CHA_ResponseReceiver* _pSpontReceiver,
                                 RWBoolean _ploggingOn                                    )
{
    pCmdRspBuf = _pCmdRspBuf;
    pImmReceiver = _pImmReceiver;
    pDelReceiver = _pDelReceiver;
    pSpontReceiver = _pSpontReceiver;

        
    if( pImmReceiver!=NULL && pDelReceiver!=NULL &&    pSpontReceiver!=NULL  ) 
   {
    pImmReceiver->addDependent(this);
    pDelReceiver->addDependent(this);
    pSpontReceiver->addDependent(this);
   } 
    receivingDelRsp   = FALSE;
    receivingSpontRsp = FALSE;
    loggingOn         = _ploggingOn;
    tryingToLogOn     = FALSE;
    aCompleteRspStored   = FALSE;
    storedDelRsp      = RWCString("OKAY");
    storedSpontRsp    = RWCString();
}



//*****************************************************************************

OZT_RspReceiver::~OZT_RspReceiver()
{
    if( pImmReceiver!=NULL && pDelReceiver!=NULL &&    pSpontReceiver!=NULL  ){ 
    pImmReceiver->removeDependent(this);
    pDelReceiver->removeDependent(this);
    pSpontReceiver->removeDependent(this);
    }
}

//*****************************************************************************

OZT_Result OZT_RspReceiver::logOn()
{
    TRACE_IN(trace, logOn, "");

    OZT_Result result;

    if (loggingOn)
    {
        TRACE_RETURN(trace, logOn, "NO_PROBLEM");
        return OZT_Result(OZT_Result::NO_PROBLEM);   // already logged on
    }
    
    //
    //  If this object is not in the middle of receiving a delayed or Spont 
    //  response, log on. Otherwise, wait until the response completes.
    //
    if (!receivingSpontRsp && !receivingDelRsp)
    {
        loggingOn = TRUE;
        TRACE_RETURN(trace, logOn, "not busy receiving, NO_PROBLEM");
        return OZT_Result(OZT_Result::NO_PROBLEM);
    }
    else
    {
        tryingToLogOn = TRUE;
        result = ozt_evHandlerPtr->waitResult();
        if (result.code == OZT_Result::NO_PROBLEM)
            loggingOn = TRUE;  // log on successfully (or else interrupted)
        tryingToLogOn = FALSE;

        TRACE_RETURN(trace, logOn, result);
        return result;
    }
}

//*****************************************************************************

RWBoolean OZT_RspReceiver::logOff()
{
    TRACE_IN(trace, logOff, "");
    RWBoolean flushedDelResp = FALSE;

    if (!loggingOn)
    {
        TRACE_OUT(trace, logOff, "already log off");
        return flushedDelResp;
    }
    //
    // flush delayed & spont responses held up due to previously log on
    //
    //The stored spont. resp. should be flushed first.    
    flushStoredSpontResp();
    flushedDelResp = flushStoredDelResp();      

    //
    // Notify OZT_CmdRspBuf that a complete response has just been inserted.
    // OZT_CmdRspBuf will then inform OZT_RspCatcher which needs this info
    // to handle @WAITREPLY.
    //
    if (aCompleteRspStored)
    {
        pCmdRspBuf->markEndOfRsp();
        aCompleteRspStored = FALSE;
    }

    loggingOn = FALSE;

    TRACE_OUT(trace, logOff, "");
    return flushedDelResp;
}

//*****************************************************************************

#if TPF >= 400  
void OZT_RspReceiver::updateFrom(CHA_Model* pModel, void*)
#else
void OZT_RspReceiver::updateFrom(RWModel* pModel, void*)
#endif
{
    TRACE_IN(trace, updateFrom, "");

    if ((CHA_ResponseReceiver*)pModel == pImmReceiver)
    {
        updateFromImmReceiver();
    }
    else if ((CHA_ResponseReceiver*)pModel == pDelReceiver)
    {
        updateFromDelReceiver();
    }
    else if ((CHA_ResponseReceiver*)pModel == pSpontReceiver)
    {
        updateFromSpontReceiver();
    }

    TRACE_OUT(trace, updateFrom, "");
}

//*****************************************************************************

void OZT_RspReceiver::detachFrom(CHA_Model* pModel)
{

}

//*****************************************************************************

void OZT_RspReceiver::updateFromImmReceiver()
{
    TRACE_IN(trace, updateFromImmReceiver, "");

    pCmdRspBuf->append(pImmReceiver->getBuffer()->getText());

    TRACE_OUT(trace, updateFromImmReceiver, "");
}

//*****************************************************************************

void OZT_RspReceiver::updateFromDelReceiver()
{
    //
    //  If logOn, store the buffer, otherwise, output to the regular cmd
    //  rsp buffer.
    //
    TRACE_IN(trace, updateFromDelReceiver, "");

    if (loggingOn)
    {
        storedDelRsp = storedDelRsp + pDelReceiver->getBuffer()->getText();
        if (pDelReceiver->isCompleteResponse())
        {
            aCompleteRspStored = TRUE;
            receivingDelRsp = FALSE;
        }
        else
            receivingDelRsp = TRUE;
    }
    else
    {
        pCmdRspBuf->append(pDelReceiver->getBuffer()->getText());
        if (pDelReceiver->isCompleteResponse())
        {
            pCmdRspBuf->markEndOfRsp();
            receivingDelRsp = FALSE;
            if (tryingToLogOn && !receivingSpontRsp)
                ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::NO_PROBLEM));
        }
        else
            receivingDelRsp = TRUE;
    }

    TRACE_OUT(trace, updateFromDelReceiver, "");
}

//*****************************************************************************

void OZT_RspReceiver::updateFromSpontReceiver()
{
    //
    //  If logOn, store the buffer, otherwise, output to the regular cmd
    //  rsp buffer.
    //
    TRACE_IN(trace, updateFromSpontReceiver, "");

    if (loggingOn)
    {
        storedSpontRsp = storedSpontRsp+ pSpontReceiver->getBuffer()->getText();
        if (pSpontReceiver->isCompleteResponse())
        {
            aCompleteRspStored = TRUE;
            receivingSpontRsp = FALSE;
        }
        else
            receivingSpontRsp = TRUE;
    }
    else
    {
        pCmdRspBuf->append(pSpontReceiver->getBuffer()->getText());
        if (pSpontReceiver->isCompleteResponse())
        {
            pCmdRspBuf->markEndOfRsp();
            receivingSpontRsp = FALSE;
            if (tryingToLogOn && !receivingDelRsp)
                ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::NO_PROBLEM));
        }
        else
            receivingSpontRsp = TRUE;
    }

    TRACE_OUT(trace, updateFromSpontReceiver, "");
}

//*****************************************************************************

void OZT_RspReceiver::interrupt()
{
    if (tryingToLogOn)
    {
        if (receivingDelRsp)
            pDelReceiver->cancelResponse();
        if (receivingSpontRsp)
            pSpontReceiver->cancelResponse();
        ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::INTERRUPTED));
    }
}
//*****************************************************************************
RWBoolean OZT_RspReceiver::flushStoredDelResp()
{   
    TRACE_IN(trace, flushStoredDelResp, "");
    RWBoolean flushedDelRsp = FALSE;
    if (!storedDelRsp.isNull())
    {
        flushedDelRsp = TRUE;    	
        pCmdRspBuf->append(storedDelRsp);
        storedDelRsp = RWCString();
    }
    TRACE_OUT(trace, flushStoredDelResp, "");      
    return flushedDelRsp;
  
}
//*****************************************************************************
void OZT_RspReceiver::flushStoredSpontResp()
{       
    TRACE_IN(trace, flushStoredSpontResp, "");
    if (!storedSpontRsp.isNull())
    {

        TRACE_FLOW(trace, flushStoredSpontResp, "Flush:" + storedSpontRsp);
        pCmdRspBuf->append(storedSpontRsp);
        storedSpontRsp = RWCString();
    }
    TRACE_OUT(trace, flushStoredSpontResp, "");  
}           
