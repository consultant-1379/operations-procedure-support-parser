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
//#include <CHA_Trace.H>
#include <CHA_IgnoreCaseString.H>

#include <trace.H>
static std::string trace ="CHA_IgnoreCaseString";


//**********************************************************************

CHA_IgnoreCaseString::CHA_IgnoreCaseString():
RWCString()
{
    TRACE_IN(trace, CHA_IgnoreCaseString, "");
};

//**********************************************************************

CHA_IgnoreCaseString::CHA_IgnoreCaseString(const RWCString r):
RWCString(r) 
{
    TRACE_IN(trace, CHA_IgnoreCaseString, r);
};

//**********************************************************************

CHA_IgnoreCaseString::CHA_IgnoreCaseString(const char* r):
RWCString(r) 
{
    TRACE_IN(trace, CHA_IgnoreCaseString, r);
};

//**********************************************************************

CHA_IgnoreCaseString::~CHA_IgnoreCaseString()
{
};

//**********************************************************************

CHA_IgnoreCaseString& CHA_IgnoreCaseString::operator=(const char* cs)
{
    TRACE_IN(trace, operator=, cs);
    return (CHA_IgnoreCaseString&)replace(0,length(),cs,strlen(cs));
};

//**********************************************************************

RWBoolean operator<(const CHA_IgnoreCaseString& s1, 
		    const CHA_IgnoreCaseString& s2)
{ 
    TRACE_IN(trace, operator<, s1 << "//" << s2);
    return s1.compareTo(s2, (RWCString::ignoreCase))<0;
};
