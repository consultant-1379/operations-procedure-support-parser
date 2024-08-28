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
#include <OZT_Prompt.H>
#include <stdlib.h>
#include <rw/tools/regex.h>
//*****************************************************************************

// trace
#include <trace.H>
static std::string trace ="OZT_Prompt";

//*****************************************************************************

OZT_Prompt::OZT_Prompt(OPS::ServerRouterListener_ptr listener)
:
  listener_(listener),
  nlsFile_(OZT_RUN_TIME_NLS)
{
    TRACE_IN(trace, OZT_Prompt, "");

  timeoutTime_ = -1;

    TRACE_OUT(trace, OZT_Prompt, "");
}

OZT_Prompt::~OZT_Prompt()
{
}

OZT_Prompt::Answer OZT_Prompt::askContinue()
{
    TRACE_IN(trace, askContinue, "");

    Answer ans;

    ans = (Answer)listener_->prompt(nlsFile_.getMessage(OZT_NLS_CONTINUE_EXECUTION,
                                                        "Do you want to continue ?"),
				    timeoutTime_);

    TRACE_RETURN(trace, askContinue, ans);
    return ans;
}

//*****************************************************************************

RWCString OZT_Prompt::getTimeoutLabel(){
  return timeoutLabel_;
}

//*****************************************************************************

void OZT_Prompt::resetTimeout(){
  timeoutLabel_ = "";
  timeoutTime_ = -1;
}

//*****************************************************************************

OZT_Result OZT_Prompt::setTimeout( const OZT_Value& label,
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
