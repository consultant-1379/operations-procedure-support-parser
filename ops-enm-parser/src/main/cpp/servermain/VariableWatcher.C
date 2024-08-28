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

#include "VariableWatcher.H"

//#include <CHA_Trace.H>

// #include "OPS_c.H"

// Static data member initialization
// trace
#include <trace.H>
static std::string trace ="VariableWatcher";

/**
 * Constructors 
 */
VariableWatcher::VariableWatcher (OZT_SourceMgr *smgr, OPS::ServerRouterListener *listener)
{
  TRACE_IN(trace, VariableWatcher, "");

  sourceMgr_ = smgr;
  listener_ = listener;

  TRACE_OUT(trace, VariableWatcher, "");
}


/**
 * Destructor
 */
VariableWatcher::~VariableWatcher ()
{
}

//*****************************************************************************

void VariableWatcher::setListener(OPS::ServerRouterListener_ptr listener){
	TRACE_IN(trace, setListener, "");
	
	listener_ = listener;
	
    TRACE_OUT(trace, setListener, "");
}

//*****************************************************************************

void
VariableWatcher::detachFrom(CHA_Model *model)
{
  TRACE_IN(trace, detachFrom, "");
  TRACE_OUT(trace, detachFrom, "");
}


//*****************************************************************************

void
VariableWatcher::updateFrom(CHA_Model* pModel, void* pData)
{
  TRACE_IN(trace, updateFrom, pData);
  
  if( pData != NULL ) {
    TRACE_FLOW(trace, updateFrom, "pData ok");
    RWCString     *varName  = (RWCString    *)pData;
    listener_->variableChanged(varName->data());
	
    }
  else {
    TRACE_FLOW(trace, updateFrom, "pData = NULL");
    listener_->variableChanged("");
  }

  TRACE_OUT(trace, updateFrom, "");
}
