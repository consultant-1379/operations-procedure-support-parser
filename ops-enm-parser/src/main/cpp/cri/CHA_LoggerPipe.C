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


#include <sys/wait.h>
#include <CHA_LoggerPipe.H>
#include <CHA_Pipe.H>
#include <CHA_EventHandler.H> // just a pointer


//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="CHA_LoggerPipe";

//*****************************************************************************
 
 
// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: CHA_LoggerPipe.C,v 21.0 1996/08/23 12:40:40 ehsgrap Rel $";
 
 
//*****************************************************************************

// extern CHA_EventHandler *ozt_evHandlerPtr;

//*****************************************************************************
 
 
CHA_LoggerPipe::CHA_LoggerPipe(CHA_LogSource& source,
                               CHA_EventHandler* cleaner)
: CHA_Logger(source),
  pPipe(0),
  pArgv(0),
  pCleaner(cleaner),
  isFirstTime(TRUE)
{
    TRACE_IN(trace, CHA_LoggerPipe, "");

    TRACE_OUT(trace, CHA_LoggerPipe, "");
}


//*****************************************************************************

CHA_LoggerPipe::~CHA_LoggerPipe()
{
    (void)turnOff();
}

//*****************************************************************************


CHA_LogReturnCode CHA_LoggerPipe::turnOn()
{
    TRACE_IN(trace, turnOn, "");

    CHA_LogReturnCode result(CHA_LogReturnCode::NO_PROBLEM);

    if (!isLoggingOn())  // if it is already on, do nothing
    {
        result = setUpPipe();
        if (result.isOkay())
            result = CHA_Logger::turnOn();
    }

    TRACE_RETURN(trace, turnOn, result);
    return result;
}

//*****************************************************************************


CHA_LogReturnCode CHA_LoggerPipe::turnOff()
{
    TRACE_IN(trace, turnOff, "");

    CHA_LogReturnCode result(CHA_LogReturnCode::NO_PROBLEM);

    if (isLoggingOn())
    {
        result = CHA_Logger::turnOff();
        if (result.isOkay())
            result = shutDownPipe();
    }

    TRACE_RETURN(trace, turnOff, result);
    return result;
}

//*****************************************************************************

void CHA_LoggerPipe::setCmdStr(const RWCString& str)
{
    TRACE_IN(trace, setCmdStr, str);

    cmdString = str;
    pArgv = 0;

    TRACE_OUT(trace, setCmdStr, "");
}

//*****************************************************************************

void CHA_LoggerPipe::setCmdStr(char* const argv[])
{
    cmdString = RWCString();
    pArgv = (char **)argv;
}

//*****************************************************************************

void CHA_LoggerPipe::appendLog(RWBoolean h, const RWCString &newText)
{
    TRACE_IN(trace, appendLog, newText);
    RWCString dummy;

    if ((pPipe != 0) && (pPipe->status() == CHA_Pipe::OKAY))
    {
      if (h && isFirstTime) {
	isFirstTime = FALSE;
	dummy = putHeader() + RWCString(newText);
      }
      else {
	dummy =  RWCString(newText);
      }

    int parentToChild = (int) (pPipe->getSendDescriptor());
    write(parentToChild, dummy, strlen(dummy));

        TRACE_OUT(trace, appendLog, "");
    }
    else{
        TRACE_OUT(trace, appendLog, "Error! pipe failure");
    }
}

//*****************************************************************************


CHA_LogReturnCode CHA_LoggerPipe::setUpPipe()
{
    TRACE_IN(trace, setupPipe, "");

    if (!cmdString.isNull())
        pPipe = new CHA_Pipe(cmdString);
    else if (pArgv != 0)
        pPipe = new CHA_Pipe(pArgv);
    else
    {
        TRACE_RETURN(trace, setUpPipe, "INTERNAL_ERR");
        return CHA_LogReturnCode(CHA_LogReturnCode::INTERNAL_ERR,
                                 "CHA_LoggerPipe::setUpPipe():cmdString err");
    }
 
    if ((pPipe != 0) && (pPipe->status() == CHA_Pipe::OKAY))
    {
        if (pCleaner != 0)
            pCleaner->setSigChdTrigger((void *)this, pPipe->pid());

        TRACE_RETURN(trace, setUpPipe, "NO_PROBLEM");
        return CHA_LogReturnCode(CHA_LogReturnCode::NO_PROBLEM);
    }
    else
    {
        TRACE_RETURN(trace, setUpPipe, "INTERNAL_ERR:pipe err"); 
        return CHA_LogReturnCode(CHA_LogReturnCode::INTERNAL_ERR,
                                 "CHA_LoggerPipe::setUpPipe():pipe err");
    }
}

//*****************************************************************************

CHA_LogReturnCode CHA_LoggerPipe::shutDownPipe()
{
    TRACE_IN(trace, shutDownPipe, "");

    if ((pPipe != 0) && (pPipe->status() == CHA_Pipe::OKAY))
        pPipe->closeSending();

    delete pPipe;
    pPipe = 0;

    TRACE_RETURN(trace, shutDownPipe, "NO_PROBLEM");
    return CHA_LogReturnCode(CHA_LogReturnCode::NO_PROBLEM);
}
