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
#include <OZT_InkeyWin.H>
#include <OZT_CDFDef.H>
#include <stdlib.h>
#include <rw/tools/regex.h>

//*****************************************************************************

// trace
#include <trace.H>
static std::string trace ="OZT_InkeyWin";

//*****************************************************************************

static const int OZT_MAX_INPUT_LENGTH = 255;

//*****************************************************************************

extern OZT_EventHandler *ozt_evHandlerPtr;

//*****************************************************************************
OZT_InkeyWin::OZT_InkeyWin (OPS::ServerRouterListener_ptr listener) :
  listener_(listener),
  nlsFile_(OZT_RUN_TIME_NLS),
  state_(IDLE)
{
  TRACE_IN(trace, OZT_InkeyWin, "");

  defaultPrompt1_ = nlsFile_.getMessage(OZT_NLS_ENTER_PROMPT1);

  defaultPrompt2_ = nlsFile_.getMessage(OZT_NLS_ENTER_PROMPT2);

  timeoutTime_ = -1;

  TRACE_OUT(trace, OZT_InkeyWin, "");
}

//*****************************************************************************
OZT_InkeyWin::~OZT_InkeyWin ()
{
}


//*****************************************************************************
OZT_Result OZT_InkeyWin::getInput(RWCString promptMsg, 
                                  RWCString defaultVal,
				  RWBoolean toFormat,
                                  RWCString &usrInput)
{
  TRACE_IN(trace, getInput, promptMsg);
  OZT_Result result;
  RWCString inputMessage;
  OPS::CharReturnValue returnValue;
  std::string smoUser;
  
  // set the prompt message
  if (promptMsg.isNull())
      inputMessage = defaultPrompt1_;
  else if (promptMsg == RWCString( OZT_IOW::NOVARIABLE ) )
      inputMessage = defaultPrompt2_;
  else
      inputMessage = promptMsg;

  char defaultChar;
  if( defaultVal.length() > 0 )
    defaultChar = defaultVal[(unsigned)0];
  else
    defaultChar = ' ';
  state_ = BUSY;

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
      returnValue = listener_->inkey( inputMessage, defaultChar, timeoutTime_, toFormat);
  }
  catch (const OPS::OPS_Client_Exception& ce)
  {
      if (ce.id == OPS::NOT_ALLOWED_IN_CHILD_SCRIPTS) 
     	{
     		TRACE_FLOW(trace,inkey,"NOT_ALLOWED_IN_CHILD_SCRIPTS");
     		ozt_errHandler.setFlag();
        	return OZT_Result(OZT_Result::NOT_ALLOWED_IN_CHILD_SCRIPTS);
      	}
      	else 
      	{	
      		state_ = IDLE;
      		return OZT_Result(OZT_Result::NO_UI_SUPPORTED);
      	}
  }

  state_ = IDLE;

  if (returnValue.ret == OPS::DIALOG_RETURNS_INTERRUPT)
    return OZT_Result(OZT_Result::INTERRUPTED);
  else  if( returnValue.ret == OPS::DIALOG_RETURNS_TIMEOUT )
    return OZT_Result(OZT_Result::DIALOG_TIMEOUT);

  // HG11871: yyparse() can't handle the '\0'-character in a sentence, but an empty
  // string like the case INPUT can be handled. Only problem when using the syntax
  // @COMMENT("Inkey: {var}"). It's no problem with the syntax @COMMENT("Inkey: ", var).
  if ( returnValue.answer == '\0' )
  	usrInput = "";
  else
  	usrInput = returnValue.answer;

    // update the session status to server
  listener_->newState(OPS::RUNNING);

  TRACE_RETURN(trace, getInput, "NO_PROBLEM");
  return OZT_Result(OZT_Result::NO_PROBLEM);
}

//*****************************************************************************
void OZT_InkeyWin::interrupt()
{
  TRACE_IN(trace, interrupt, "");

  if (state_ == BUSY)
  {
    ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::INTERRUPTED));
  }

  TRACE_OUT(trace, interrupt, "");
}

//*****************************************************************************

RWCString OZT_InkeyWin::getTimeoutLabel(){
  return timeoutLabel_;
}

//*****************************************************************************

void OZT_InkeyWin::resetTimeout(){
  timeoutLabel_ = "";
  timeoutTime_ = -1;
}

//*****************************************************************************

OZT_Result OZT_InkeyWin::setTimeout( const OZT_Value& label,
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
