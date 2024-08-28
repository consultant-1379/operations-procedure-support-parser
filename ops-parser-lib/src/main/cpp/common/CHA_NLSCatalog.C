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


#include <CHA_NLSCatalog.H>
#include <CHA_ErrorReporter.H>
#include <CHA_LibGlobals.H>
#include <strstream>

//**********************************************************************


static const char* noOpenCat  = "Can't open NLS catalog: ";
static const char* noCloseCat = "Can't close NLS catalog: ";
static const char* getError   = "Get text error, ";

#include <trace.H>
static std::string trace ="CHA_NLSCatalog";


//**********************************************************************


CHA_NLSCatalog::CHA_NLSCatalog(const char* catName, int catSet)
: catalogName(catName),
  currentSet(catSet)
{    
    TRACE_IN(trace, CHA_NLSCatalog, catName << ", " << catSet);
}


//**********************************************************************


CHA_NLSCatalog::CHA_NLSCatalog(const RWCString& catName, int catSet)
: catalogName(catName),
  currentSet(catSet)
{
    TRACE_IN(trace, CHA_NLSCatalog, catName << ", " << catSet);
}


//**********************************************************************


CHA_NLSCatalog::~CHA_NLSCatalog()
{
}


//**********************************************************************


void CHA_NLSCatalog::selectSet(int catSet)
{
    TRACE_IN(trace, selectSet, catSet);
    
    currentSet = catSet;
}


//**********************************************************************


RWCString CHA_NLSCatalog::getMessage(int nlsIdx) const
{
    std::ostrstream buff;
    nl_catd cat = catopen(catalogName, 0);
    if(cat == (nl_catd)-1)
    {
	TRACE_FLOW(trace, getMessage, "can't open " << catalogName);

        errorReporter.message(noOpenCat + catalogName);
        buff << getError << nlsIdx;
        RWCString retVal(buff.str(), buff.pcount());
        delete [] buff.str();
	return retVal;
    }
    else
    {
	RWCString rwcS(catgets(cat, currentSet, nlsIdx, getError));
	if(catclose(cat) == -1)
	    errorReporter.message(noCloseCat + catalogName);

	if(rwcS == getError)
	{
	    buff << getError << nlsIdx;
	    RWCString retVal(buff.str(), buff.pcount());
	    TRACE_RETURN(trace, getMessage, retVal);
            delete [] buff.str();
	    return retVal;
	}
	else
	{
	    return rwcS;
	}
    }
}


//**********************************************************************


RWCString CHA_NLSCatalog::getMessage(int nlsIdx,
				     const char* defaultMsg) const
{
    nl_catd cat = catopen(catalogName, 0);
    if(cat == (nl_catd)-1)
    {
	TRACE_FLOW(trace, getMessage, "can't open " << catalogName);

	errorReporter.message(noOpenCat + catalogName);
	return RWCString(defaultMsg);
    }
    else
    {
	RWCString rwcS(catgets(cat, currentSet, nlsIdx, defaultMsg));
	if(catclose(cat) == -1)
	    errorReporter.message(noCloseCat + catalogName);

	return rwcS;
    }
}


//**********************************************************************


RWCString CHA_NLSCatalog::getMessage(int nlsIdx,
				     const RWCString& defaultMsg) const
{
    nl_catd cat = catopen(catalogName, 0);
    if(cat == (nl_catd)-1)
    {
	TRACE_FLOW(trace, getMessage, "can't open " << catalogName);

	errorReporter.message(noOpenCat + catalogName);
	return defaultMsg;
    }
    else
    {
	RWCString rwcS(catgets(cat, currentSet, nlsIdx, defaultMsg.data()));
	if(catclose(cat) == -1)
	    errorReporter.message(noCloseCat + catalogName);
	return rwcS;
    }
}


//**********************************************************************
