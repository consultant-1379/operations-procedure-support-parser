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


#include <OZT_Indicator.H>
#include <CHA_LibGlobals.H>
#include <CHA_ErrorReporter.H>


//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_Indicator";


//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_Indicator.C,v 21.0 1996/08/23 12:44:10 ehsgrap Rel $";


//*****************************************************************************


OZT_Indicator::OZT_Indicator()
{
    errorReporter.addDependent(this);
}

OZT_Indicator::~OZT_Indicator()
{
    errorReporter.removeDependent(this);
}

void OZT_Indicator::setMsg(const RWCString &msg)
{
    if (msg != currentMsg)
    {
        currentMsg = msg;
        changed((void *)(&msg));
    }
}

RWCString OZT_Indicator::getMsg() const
{
    return currentMsg;
}

void OZT_Indicator::clearMsg()
{
    setMsg("");
}

#if TPF >= 400  
void OZT_Indicator::updateFrom(CHA_Model* pModel, void* pValue)
#else
void OZT_Indicator::updateFrom(RWModel* pModel, void* pValue)
#endif
{
    if ((CHA_ErrorReporter*)pModel == &errorReporter)
        setMsg(errorReporter.getErrorMessage());
}

void OZT_Indicator::detachFrom(CHA_Model* pModel)
{

}
