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


#include <OZT_SourceKeeper.H>
#include <OZT_SourceMgr.H>

//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_SourceKeeper";

//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_SourceKeeper.C,v 1.0 1996/03/19 07:21:14 ehsjasa Rel $";

//*****************************************************************************
OZT_SourceKeeper* OZT_SourceKeeper::instance = 0;


OZT_SourceKeeper::OZT_SourceKeeper()
{
    TRACE_IN(trace, OZT_SourceKeeper, "");


    TRACE_OUT(trace, OZT_SourceKeeper, "");
}

//*************************************************************************

OZT_SourceKeeper* OZT_SourceKeeper::Instance()
{
    TRACE_IN(trace, Instance, "");
   
    if (instance == 0)
    {
        instance = new OZT_SourceKeeper; 
    }
    return instance;

    TRACE_OUT(trace, Instance, "");
}

//*************************************************************************

void OZT_SourceKeeper::setSourceMgrPointer (OZT_SourceMgr* p)
{
    TRACE_IN(trace, setSourceMgrPointer, "");
   
    pSourceMgr = p;

    TRACE_OUT(trace, setSourceMgrPointer, "");
}

//*************************************************************************

OZT_SourceMgr* OZT_SourceKeeper::getSourceMgrPointer ()
{
    TRACE_IN(trace, getSourceMgrPointer, "");
   
    return pSourceMgr;

    TRACE_OUT(trace, getSourceMgrPointer, "");
}
