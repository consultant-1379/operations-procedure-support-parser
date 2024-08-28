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
#include <CHA_DelRespHandler.H>
#include <trace.H>

static std::string trace ="CHA_DelRespHandler";

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_DelRespHandler", (char*)"C");

//*********************************************************************

CHA_DelRespHandler::CHA_DelRespHandler(CHA_IPCSupervisor* pSup,
				       const RWCString& appN,
				       CHA_RoutingHandler* pRtHandler)
: pIpcSupervisor(pSup)
{
     TRACE_IN(trace, CHA_DelRespHandler, "");

     CHA_ElemSeqRespList* pAuxElemSeq;
     CHA_SeqDelRespReceiver* pAuxSeqReceiver = new CHA_SeqDelRespReceiver(pSup,appN);

     pAuxElemSeq = new CHA_ElemSeqRespList(pAuxSeqReceiver);

     TRACE_FLOW (trace,CHA_DelRespHandle,"Insert the receiver in the list");

     seqRespReceiverList.append(pAuxElemSeq);

     if(pAuxElemSeq->pSeqDelRespReceiver != NULL)
	pAuxElemSeq->pSeqDelRespReceiver->addDependent(this);

     if(pRtHandler != NULL)
        pRtHandler->setRespReceiver(CHA_RT_DELAYED,
      	                            pAuxElemSeq->pSeqDelRespReceiver);

     pRoutingHandler = pRtHandler;
     TRACE_OUT (trace,CHA_DelRespHandler,"");
}


//**********************************************************************


CHA_DelRespHandler::~CHA_DelRespHandler()
{
     CHA_ElemSeqRespList* pAuxElemSeq;

     const int entries = seqRespReceiverList.entries();
     TRACE_FLOW(trace,CHA_DelRespHandler,entries);
     for(int i = 0; i < entries; i++)
     {
        pAuxElemSeq= seqRespReceiverList.get();
	pAuxElemSeq->pSeqDelRespReceiver->removeDependent(this);
        delete pAuxElemSeq;
        pAuxElemSeq = NULL;
     }
}

//**********************************************************************

void CHA_DelRespHandler::updateFrom(CHA_Model* model, void* pData)
{
   TRACE_IN(trace, updateFrom, "");

   CHA_ElemSeqRespList* pAuxElemSeq;
   CHA_ElemSeqRespList* pAux;

   pAux = new CHA_ElemSeqRespList((CHA_SeqDelRespReceiver*) model);
   pAuxElemSeq = checkElemList(pAux);
   if(pAuxElemSeq != NULL)
   {
       if ((pAuxElemSeq->pSeqDelRespReceiver->isCompleteResponse())&&
           (pAuxElemSeq->pSeqDelRespReceiver->isLastInSequence()))
       {
           TRACE_FLOW(trace, updateFrom, "Response is completed");
           pAuxElemSeq->seqStatus = IDLE;
           pAuxElemSeq->isToDelete = TRUE;
       }
       else
       {
           TRACE_FLOW(trace, updateFrom, "Response is uncompleted");
           pAuxElemSeq->seqStatus = BUSY;
           pAuxElemSeq->isToDelete =FALSE;
           createIdleReceiver();
       }
  }
  delete pAux;
  TRACE_OUT(trace, updateFrom, "");
}

//**********************************************************************

void CHA_DelRespHandler::detachFrom(CHA_Model* model)
{
}

//**********************************************************************

CHA_ElemSeqRespList* CHA_DelRespHandler::checkElemList(CHA_ElemSeqRespList* pElemInList)
{
   TRACE_IN(trace, checkElemList, "");

   CHA_ElemSeqRespList* pAux;
   int                  entries = seqRespReceiverList.entries();
   RWBoolean            isElemFind = FALSE;

   while((entries > 0) && !(isElemFind))
   {
       entries--;
       pAux = seqRespReceiverList[entries];
       if ((pElemInList->pSeqDelRespReceiver) == (pAux->pSeqDelRespReceiver))
          isElemFind = TRUE;
   }
   if (isElemFind)
   {
      TRACE_OUT(trace, checkElemList, "Element exits");
      return pAux;
   }
   else
   {
      TRACE_OUT(trace, checkElemList, "NULL");
      return NULL;
   }

}

//**********************************************************************

void CHA_DelRespHandler::createIdleReceiver()
{
   TRACE_IN(trace, createIdleReceiver, "");

   CHA_ElemSeqRespList* pAux;
   int                  entries = seqRespReceiverList.entries();
   RWBoolean            isElemIdle = FALSE;

   // Check if there is an IDLE receiver already created . If it is already created, reuse it
   while((entries > 0) && !(isElemIdle))
   {
       entries--;
       pAux = seqRespReceiverList[entries];
       if ((pAux->seqStatus) == IDLE)
       {
          TRACE_FLOW(trace, createIdleReceiver, "IDLE receiver");
          isElemIdle = TRUE;
          pAux->isToDelete = FALSE;
       }
   }

   if (isElemIdle)
   {
       // Remove all the rest of idle receivers
       while((entries > 0))
       {
           entries--;
           pAux = seqRespReceiverList[entries];
           if ((pAux->isToDelete) == TRUE)
           {
               TRACE_FLOW(trace, createIdleReceiver, "Delete a receiver");
               seqRespReceiverList.remove(pAux);
               entries--;
           }
        }
   }
   else
   {
       // Create a new receiver
       TRACE_FLOW(trace, createIdleReceiver, "Create a new receiver");
       pAux = new CHA_ElemSeqRespList(new CHA_SeqDelRespReceiver(pIpcSupervisor,
                                                                 applicationName));
       seqRespReceiverList.append(pAux);
       if(pRoutingHandler != NULL)
          pRoutingHandler->setRespReceiver(CHA_RT_DELAYED,
      	                                   pAux->pSeqDelRespReceiver);
   }

   TRACE_OUT(trace, createIdleReceiver, "");
}

//**********************************************************************
