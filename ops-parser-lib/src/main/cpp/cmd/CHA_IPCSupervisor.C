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
#include <trace.H>
#include <CHA_IPCSupervisor.H>


static std::string trace ="CHA_ImmRespReceiver";
//**********************************************************************


CHA_IPCSupervisor::CHA_IPCSupervisor(CHA_Model* pModel)
: pTrigger(pModel)//,
 // talker()
{
    //TRACE_IN(trace, CHA_IPCSupervisor, "pTrigger");

    if(pTrigger != NULL)
	pTrigger->addDependent(this);
}


//**********************************************************************


CHA_IPCSupervisor::~CHA_IPCSupervisor()
{
    if(pTrigger)
	pTrigger->removeDependent(this);
}


//**********************************************************************


void CHA_IPCSupervisor::updateFrom(CHA_Model* model, void* pData)
{
    checkIPCQue();
}


//**********************************************************************


void CHA_IPCSupervisor::detachFrom(CHA_Model* model)
{
    TRACE_IN(trace, detachFrom, "model");

    if(model == pTrigger)
    {
	TRACE_FLOW(trace, detachFrom, "detached");
	pTrigger = NULL;
    }
}


//**********************************************************************

CHA_Model*  CHA_IPCSupervisor::getTrigger(void)
{
  TRACE_IN(trace, getTrigger, "");

  TRACE_RETURN(trace, getTrigger, pTrigger);
  return pTrigger;

}

//**********************************************************************


void CHA_IPCSupervisor::checkIPCQue()
{

  // Read all buffers in the IPC que.
  /*int queLength = talker.Get_no_of_messages();

  for(int i=0; i<queLength; i++)
    {
      changed();
    }*/

  /*
    int queLength = talker.Get_no_of_messages();
    if(queLength > 0)
    {
        // //TRACE_FLOW(trace, checkIPCQue,
	// 	   "IPC-que = " << queLength << ", calling changed()");
 	changed();

	// queLength = talker.Get_no_of_messages();
        // //TRACE_FLOW(trace, checkIPCQue,
	// 	   "IPC-que = " << queLength << ", after changed()");
    }
    */

}


//**********************************************************************

