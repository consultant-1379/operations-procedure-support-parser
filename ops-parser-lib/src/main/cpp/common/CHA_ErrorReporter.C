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

//#include <CHA_Trace.H>
#include <CHA_ErrorReporter.H>

#include <trace.H>
static std::string trace ="CHA_ErrorReporter";

//**********************************************************************


CHA_ErrorReporter::CHA_ErrorReporter()
: errMsg()
{
    TRACE_IN(trace, CHA_ErrorReporter, "");
}


//**********************************************************************


CHA_ErrorReporter::~CHA_ErrorReporter()
{
}

//**********************************************************************

void CHA_ErrorReporter::message(const char* msg, const cmdErrType type)
{
    TRACE_IN(trace, message, msg);

    errMsg = msg;
    errType = type;
    
    changed();
}

//**********************************************************************

void CHA_ErrorReporter::message(const RWCString& msg, const cmdErrType type)
{
    TRACE_IN(trace, message, type);

    errMsg = msg;
    errType = type;
    
    changed();
}

//**********************************************************************

RWCString CHA_ErrorReporter::getErrorMessage() const
{
    return errMsg;
}

//**********************************************************************

//**********************************************************************

CHA_ErrorReporter::cmdErrType CHA_ErrorReporter::getErrorType() const
{
    return errType;
}
//**********************************************************************
