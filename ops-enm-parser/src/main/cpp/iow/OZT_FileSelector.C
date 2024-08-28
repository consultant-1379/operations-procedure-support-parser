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

#include <OZT_EventHandler.H>
#include <OZT_FileSelector.H>
#include <OZT_Misc.H>
#include <iostream>

//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_FileSelector";

//*****************************************************************************

extern OZT_EventHandler *ozt_evHandlerPtr;

//*****************************************************************************

OZT_FileSelector::OZT_FileSelector(OPS::ServerRouterListener_ptr listener)
:
    state_(IDLE),
    listener_(listener)
{
  TRACE_IN(trace, OZT_FileSelector, "");
  TRACE_OUT(trace, OZT_FileSelector, "");
}

//*****************************************************************************
OZT_FileSelector::~OZT_FileSelector()
{
}

//*****************************************************************************
OZT_Result OZT_FileSelector::selFile(const RWCString& mask,
                                     const RWCString& promptMsg,
                                     RWCString& usrInput)
{
  TRACE_IN(trace, selFile, mask << ", " << promptMsg);

  //CORBA::String_var returnString;
  state_ = BUSY;
  //OPS::DialogReturnValue returnValue = listener_->selectFile(mask, promptMsg, returnString);

  OPS::StringReturnValue_var returnValue;
  std::string smoUser;
  try
  {
    smoUser = listener_->getSmoUser();
    if(smoUser != "")
    {
      TRACE_FLOW(trace, selFile, "waiting for GUI to launch");
      listener_->setWaitingForUserInput();
      listenerType_ = listener_->getClientType("");

      while(listenerType_ != OPS::GUI)
      {
        listenerType_ = listener_->getClientType("");
        if(listenerType_ == OPS::GUI)
        {
          listener_->setWaitingForUserInput();
          break;
        }
        sleep(20); // checking if gui has launched at every 20 seconds 
      }
     }
      returnValue =  listener_->selectFile( mask, promptMsg );
  }
  catch (const OPS::OPS_Client_Exception& ce)
  {
      if (ce.id == OPS::NOT_ALLOWED_IN_CHILD_SCRIPTS) 
     	{
     		TRACE_FLOW(trace,selectFile,"NOT_ALLOWED_IN_CHILD_SCRIPTS");
     		ozt_errHandler.setFlag();
        	return OZT_Result(OZT_Result::NOT_ALLOWED_IN_CHILD_SCRIPTS);
      	}
      	else 
      	{ 	
      		TRACE_FLOW(trace,selectFile,"NO_UI_SUPPORTED");
      		state_ = IDLE;
      		return OZT_Result(OZT_Result::NO_UI_SUPPORTED);
      	}
  }

  state_ = IDLE;

  if (returnValue->ret == OPS::DIALOG_RETURNS_INTERRUPT) {
    usrInput = "";
   TRACE_RETURN(trace, selFile, "INTERRUPTED");
    return OZT_Result(OZT_Result::STOP);
  }

  usrInput = ozt_normalisePath((char*)(returnValue->answer));

    // update the session status to server
  listener_->newState(OPS::RUNNING);

 TRACE_RETURN(trace, selFile, "NO_PROBLEM");
  return OZT_Result(OZT_Result::NO_PROBLEM);
}

//*****************************************************************************
void OZT_FileSelector::interrupt()
{
   TRACE_IN(trace, interrupt, "");


    if (state_ == BUSY)
    {
        ozt_evHandlerPtr->setResult(OZT_Result::INTERRUPTED);
    }

  TRACE_OUT(trace, interrupt, "");
}
