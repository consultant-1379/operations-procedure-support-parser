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

#include <OZT_RunTimeNLS.H>
#include <OZT_EventHandler.H>
#include <OZT_InputWin.H>
#include <OZT_CDFDef.H>
#include <stdlib.h>
#include <rw/tools/regex.h>

//*****************************************************************************

// trace
#include <trace.H>
static std::string trace ="OZT_InputWin";

//*****************************************************************************

static const int OZT_MAX_INPUT_LENGTH = 255;

//*****************************************************************************

extern OZT_EventHandler *ozt_evHandlerPtr;

//*****************************************************************************
OZT_InputWin::OZT_InputWin (OPS::ServerRouterListener_ptr listener) :
  listener_(listener),
  nlsFile_(OZT_RUN_TIME_NLS),
  state_(IDLE)
{
  TRACE_IN(trace, OZT_InputWin, "");

  defaultPrompt_ = nlsFile_.getMessage(OZT_NLS_ENTER_PROMPT1);

  timeoutTime_ = -1;

 TRACE_OUT(trace, OZT_InputWin, "");
}

//*****************************************************************************
OZT_InputWin::~OZT_InputWin ()
{
}


//*****************************************************************************
OZT_Result OZT_InputWin::getInput(RWCString promptMsg, 
                                  RWCString defaultVal,
				  RWBoolean toFormat,
                                  RWCString &usrInput)
{
 TRACE_IN(trace, getInput, promptMsg);
  OZT_Result result;
  RWCString inputMessage;

  // set the prompt message
  if (promptMsg.isNull())
    inputMessage = defaultPrompt_;
  else
    inputMessage = promptMsg;

  // set the default value
  if (defaultVal.length() > OZT_MAX_INPUT_LENGTH)
    defaultVal = defaultVal(0, OZT_MAX_INPUT_LENGTH);

  //CORBA::String_var returnString = defaultVal.data();
  state_ = BUSY;

  OPS::StringReturnValue_var returnValue;
  std::string smoUser;

  try
  {
    smoUser = listener_->getSmoUser();
    if(smoUser != "")
    {
      TRACE_FLOW(trace, getInput, "waiting for GUI to launch");
      listener_->setWaitingForUserInput();
      clientType_ = listener_->getClientType("");

      while(clientType_ != OPS::GUI)
      {
        clientType_ = listener_->getClientType("");
        if(clientType_ == OPS::GUI)
        {
          listener_->setWaitingForUserInput();
          break;
        }
        sleep(20); // checking if gui has launched at every 20 seconds 
      }
     }

    TRACE_FLOW(trace, getInput, "Making callback");
      returnValue = listener_->input(inputMessage, 
                                     defaultVal, 
                                     timeoutTime_,
                                     toFormat);
    TRACE_FLOW(trace, getInput, "Callback ok");  
  }
  catch (const OPS::OPS_Client_Exception& ce)
  {
  	if (ce.id == OPS::NOT_ALLOWED_IN_CHILD_SCRIPTS) 
     	{
     		TRACE_FLOW(trace,getInput,"NOT_ALLOWED_IN_CHILD_SCRIPTS");
     		ozt_errHandler.setFlag();
        	return OZT_Result(OZT_Result::NOT_ALLOWED_IN_CHILD_SCRIPTS);
      	}
      	else 
      	{
      		state_ = IDLE;
      	//	TRACE_OUT(trace, getInput, "ui not support");
      		return OZT_Result(OZT_Result::NO_UI_SUPPORTED);
      	}
  }

  state_ = IDLE;

  if (returnValue->ret == OPS::DIALOG_RETURNS_INTERRUPT){
  TRACE_OUT(trace, getInput, "interrupt");
    return OZT_Result(OZT_Result::INTERRUPTED);
  }
  else  if( returnValue->ret == OPS::DIALOG_RETURNS_TIMEOUT ){
   TRACE_OUT(trace, getInput, "timeout");
    return OZT_Result(OZT_Result::DIALOG_TIMEOUT);
  }

  usrInput = RWCString( returnValue->answer);
  if (usrInput.length() > INPUT_STORELEN)
    usrInput = usrInput(0, INPUT_STORELEN);

    // update the session status to server
  listener_->newState(OPS::RUNNING);

 TRACE_OUT(trace, getInput, "NO_PROBLEM");
  return OZT_Result(OZT_Result::NO_PROBLEM);
}

//*****************************************************************************
void OZT_InputWin::interrupt()
{
 TRACE_IN(trace, interrupt, "");

  if (state_ == BUSY)
  {
    ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::INTERRUPTED));
  }

 TRACE_OUT(trace, interrupt, "");
}

//*****************************************************************************

RWCString OZT_InputWin::getTimeoutLabel(){
  return timeoutLabel_;
}

void OZT_InputWin::resetTimeout(){
  timeoutLabel_ = "";
  timeoutTime_ = -1;
}

OZT_Result OZT_InputWin::setTimeout( const OZT_Value& label,
				   const OZT_Value& time,
				   const OZT_Value& unit ) {

  TRACE_IN(trace, setTimeout, label << "," << time << "," << unit );
  OZT_Result res;
  size_t len;
  static RWTRegex<char> rexp("^[+]?[0-9]+$");

  if( rexp.index( time, &len ) == RW_NPOS ) {
    res.code = OZT_Result::INVALID_VALUE;
    return res;
  }

  long t = atol( time.data() );
  
  if( unit == "S" || unit == "s" )
    timeoutTime_ = t;
  else if( unit == "M" || unit == "m" )
    timeoutTime_ = t*60;
  else if( unit == "H" || unit == "h" )
    timeoutTime_ = t*3600;
  else {
    res.code = OZT_Result::INVALID_VALUE;
    return res;
  }


  timeoutLabel_ = label;
  
  res.code = OZT_Result::NO_PROBLEM;
  return res;
}
