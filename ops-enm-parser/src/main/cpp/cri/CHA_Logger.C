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


#include <CHA_Logger.H>
#include <CHA_LogSource.H>
#include <CHA_OZTInfo.H>
#include <OZT_SourceKeeper.H>
#include <nl_types.h>
#include <CHA_UserInfo.H>

//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="CHA_Logger";

static const char* hyphens   = "----------------------------------------------------\n";
static const char* comFile   = "Command File:\t";
static const char* esName    = "ES Name:\t";
static const char* dateTime  = "Time:\t\t";
static const char* user      = "User:\t\t";
extern CHA_OZTInfo ozt_info;

//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: CHA_Logger.C,v 21.0 1996/08/23 12:40:38 ehsgrap Rel $";


//*****************************************************************************


CHA_Logger::CHA_Logger(CHA_LogSource& source)
:
    pSource(&source),
    loggingOn(FALSE),
    headersON(FALSE)
    //isFirstTime(TRUE)
{
    TRACE_IN(trace, CHA_Logger, "");

    TRACE_OUT(trace, CHA_Logger, "");
}

//*************************************************************************

CHA_Logger::~CHA_Logger()
{
    if (loggingOn)
        turnOff();
}

//*************************************************************************
  
CHA_LogReturnCode CHA_Logger::turnOn()
{
    TRACE_IN(trace, turnOn, "");
 
    if (pSource == 0)
    {
        TRACE_OUT(trace, turnOn, "INTERNAL ERR");
        return CHA_LogReturnCode(CHA_LogReturnCode::INTERNAL_ERR,
                                 "CHA_Logger::turnOn()");
    }
    if (!loggingOn)  // if it is already on, do nothing
    {
        loggingOn = TRUE;
        pSource->addDependent(this);
    }

    TRACE_OUT(trace, turnOn, "NO_PROBLEM");
    return CHA_LogReturnCode(CHA_LogReturnCode::NO_PROBLEM);
}

//*************************************************************************

CHA_LogReturnCode CHA_Logger::turnOff()
{
    TRACE_IN(trace, turnOff, "");

    if (loggingOn && (pSource != 0))
    {
        pSource->removeDependent(this);
        loggingOn = FALSE;
    }

    TRACE_OUT(trace, turnOff, "NO_PROBLEM"); 
    return CHA_LogReturnCode(CHA_LogReturnCode::NO_PROBLEM);
}

//*************************************************************************

#if TPF >= 400  
void CHA_Logger::updateFrom(CHA_Model* pModel, void*)
#else
void CHA_Logger::updateFrom(RWModel* pModel, void*)
#endif
{
    TRACE_IN(trace, updateFrom, "");
 
    if (loggingOn)
    {
        RWCString newText;
 
        if ((CHA_LogSource *)pModel != pSource)
        {
            TRACE_OUT(trace, updateFrom, "Unknown model!");
            return;
        }
 
        newText = pSource->getUpdateText();
        if (!newText.isNull()) 
        {
	    RWCString dummy;
            ozt_info.getHeadersON(headersON);

            /*if (headersON && isFirstTime)
	      {
	      isFirstTime = FALSE;
	      dummy = putHeader() + RWCString(newText);
	      }
	      else
	      {
	      dummy =  RWCString(newText);
	      }*/

            appendLog(headersON, newText);
	}
    }
 
    TRACE_OUT(trace, updateFrom, "");
}
 
//*************************************************************************

void CHA_Logger::detachFrom(CHA_Model* pModel)
{
    TRACE_IN(trace, detachFrom, "");

    if ((CHA_LogSource *)pModel != pSource)
    {
        TRACE_OUT(trace, detachFrom, "Unknown model!");
        return;
    }

    if (loggingOn)
    {
        loggingOn = FALSE;
        pSource = 0;
    }

    TRACE_OUT(trace, detachFrom, "");
}

//*************************************************************************

RWCString CHA_Logger::putHeader()
{
    TRACE_IN(trace, putHeader, "");

    RWCString aux;
    OZT_SourceKeeper*  srcKeeper = OZT_SourceKeeper::Instance();
    time_t td = time(0);
    CHA_UserInfo userInfo;

    aux = RWCString(hyphens) + RWCString(comFile) + 
	  RWCString(srcKeeper->getSourceMgrPointer()->
                    getInterpreter().getCurrFileName()) + 
          RWCString("\n") +
          RWCString(esName) + 
          RWCString(srcKeeper->getSourceMgrPointer()->
                    getCmdSender().getEsName()) + RWCString("\n") +
	  RWCString(dateTime) + RWCString(ctime(&td)) + 
      	  RWCString(user) + RWCString(userInfo.loginName()) +
	  RWCString("\n") + RWCString(hyphens) + RWCString("\n");
    return aux;

    TRACE_OUT(trace, putHeader, "");
}
