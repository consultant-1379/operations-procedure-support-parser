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
#include <OZT_FileViewer.H>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

//*****************************************************************************

// trace
#include <trace.H>
static std::string trace ="OZT_FileViewer";

//*****************************************************************************

extern OZT_EventHandler *ozt_evHandlerPtr;

//*****************************************************************************

OZT_FileViewer::OZT_FileViewer(OPS::ServerRouterListener_ptr listener)
: state_(IDLE),
  listener_(listener)
{
  TRACE_IN(trace, OZT_FileViewer, "");
  TRACE_OUT(trace, OZT_FileViewer, "");
}

//*****************************************************************************

OZT_FileViewer::~OZT_FileViewer()
{
}

//*****************************************************************************

OZT_Result OZT_FileViewer::view(RWCString fileName)
{
 TRACE_IN(trace, view, fileName);

  int local_errno = 0; // to many lib calls to trust `errno' below
 
  //
  // load the file in
  //
  fileName = ozt_normalisePath(fileName);
  struct stat buf;
  errno = 0; // Reset `errno' prior to opening the file
  if ((stat(fileName.data(), &buf) == -1) || !S_ISREG(buf.st_mode)) {
    return OZT_Result(OZT_Result::FILE_OPEN_ERR, strerror(errno));
  }
  
  TRACE_FLOW(trace, view, "About to load " << fileName);
  state_ = BUSY;

  OPS::DialogReturnValue returnValue;
  try
  {
      returnValue = listener_->viewFile(fileName);
  }
  catch (const OPS::OPS_Client_Exception& ce)
  {
  	if (ce.id == OPS::NOT_ALLOWED_IN_CHILD_SCRIPTS) 
     	{
     		TRACE_FLOW(trace,draw,"draw, NOT_ALLOWED_IN_CHILD_SCRIPTS");
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
  TRACE_FLOW(trace, view, "File loaded");

  if (returnValue == OPS::DIALOG_RETURNS_INTERRUPT)
    return OZT_Result(OZT_Result::INTERRUPTED);

  TRACE_RETURN(trace, view, "NO_PROBLEM");
  return OZT_Result(OZT_Result::NO_PROBLEM);
}


void OZT_FileViewer::interrupt()
{
 TRACE_IN(trace, interrupt, "");

  if (state_ == BUSY)
    ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::INTERRUPTED));

 TRACE_OUT(trace, interrupt, "");
}
