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
#include <CHA_RoutingTarget.H>

#include <trace.H>
static std::string trace ="CHA_RoutingTarget";

 
//**********************************************************************


CHA_RoutingTarget::CHA_RoutingTarget()
: depOfList()
{
    TRACE_IN(trace, CHA_RoutingTarget, "");
}


//**********************************************************************


CHA_RoutingTarget::~CHA_RoutingTarget()
{
    while(depOfList.entries() > 0)
	depOfList.removeFirst()->removeDependent(this);
}


//**********************************************************************


void CHA_RoutingTarget::route(CHA_ResponseReceiver* respRcvr)
{
    TRACE_IN(trace, route, respRcvr);
	     
    // don't do routing more than once per response receiver
    if(!depOfList.contains(respRcvr))
    {
	respRcvr->addDependent(this);
	depOfList.append(respRcvr);
    }
}


//**********************************************************************


void CHA_RoutingTarget::dontRoute(CHA_ResponseReceiver* respRcvr)
{
    TRACE_IN(trace, dontRoute, respRcvr);
	     
    // only take action if we were routing this receiver
    if(depOfList.remove(respRcvr))
	respRcvr->removeDependent(this);
}


//**********************************************************************


size_t CHA_RoutingTarget::nrOfReceivers() const
{
    TRACE_RETURN(trace, nrOfReceivers, depOfList.entries());
    return depOfList.entries();
}


//**********************************************************************


void CHA_RoutingTarget::updateFrom(CHA_Model* p, void* d)
{
    CHA_ResponseReceiver* respRcvr = (CHA_ResponseReceiver*) p;

    if(respRcvr->isCompleteResponse())
	doRouting(respRcvr->getAccumulatedResponse());

    TRACE_RETURN(trace, updateFrom, "routing done...");
}


//**********************************************************************


void CHA_RoutingTarget::detachFrom(CHA_Model* model)
{
    depOfList.remove((CHA_ResponseReceiver*) model);
}


//**********************************************************************
