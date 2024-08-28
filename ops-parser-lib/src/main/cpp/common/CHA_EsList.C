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
//**********************************************************************
#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_LibNLS.H>
#include <CHA_UserInfo.H>
//TORF-241666
//#include <eac_esi.H>
//#include <eac.H>

#include <CHA_EsList.H>

#include <rw/cstring.h>

#include <trace.H>
static std::string trace ="CHA_EsList";

//**********************************************************************


CHA_EsList::CHA_EsList()
{
    TRACE_IN(trace, CHA_EsList, "");

    // Empty
}


//**********************************************************************


CHA_EsList::~CHA_EsList()
{
    // Empty
}


//**********************************************************************


RWCString CHA_EsList::operator[](size_t i) const
{
    TRACE_IN(trace, operator[], i);

    return myEsList[i];
}


//**********************************************************************


RWBoolean CHA_EsList::contains(const RWCString& name) const
{
    TRACE_IN(trace, contains, name);

    return myEsList.contains(name);
}


//**********************************************************************


size_t CHA_EsList::entries() const
{
    TRACE_IN(trace, entries, "");

    return myEsList.entries();
}


//**********************************************************************


RWCString CHA_EsList::first() const
{
    TRACE_IN(trace, first, "");

    return myEsList.first();
}


//**********************************************************************


size_t CHA_EsList::index(const RWCString& name) const
{
    TRACE_IN(trace, index, name);

    return myEsList.index(name);
}


//**********************************************************************


RWBoolean CHA_EsList::isEmpty() const
{
    TRACE_IN(trace, isEmpty, "");

    return myEsList.isEmpty();
}


//**********************************************************************


RWCString CHA_EsList::last() const
{
    TRACE_IN(trace, last, "");

    return myEsList.last();
}


//**********************************************************************


size_t CHA_EsList::length() const
{
    TRACE_IN(trace, length, "");

    return myEsList.length();
}


//**********************************************************************


size_t CHA_EsList::occurrencesOf(const RWCString& name) const
{
    TRACE_IN(trace, occurrencesOf, name);

    return myEsList.occurrencesOf(name);
}


//**********************************************************************
void CHA_EsList::updateIMHDatabase()
{
}


//**********************************************************************

CHA_EsList::ReturnCode CHA_EsList::update(CHA_EsList::NeSource ne_src)
{
    TRACE_IN(trace, update, "");

    CHA_EsList::ReturnCode returnValue;

    returnValue = updateUsingEA();

    changed();

    TRACE_RETURN(trace, update, returnValue);
    return returnValue;
}


//**********************************************************************


CHA_EsList::ReturnCode CHA_EsList::updateUsingEA()
{
    TRACE_IN(trace, updateUsingEA, "");

    CHA_EsList::ReturnCode returnValue = CHA_EsList::OKAY;

  //  EAC_ESI_Info eacInfo;
 //   char estype[EAC_ES_TYPE_LEN+1];
 //   strcpy(estype,"AXE");
/*
    if( eacInfo.Get_status() != -1  )
      {
	const char* esName =
	  eacInfo.Get_first_ES_name(estype);

	if (esName == NULL)
	  {
	    cerr << "esName NULL string: Get_error:" << eacInfo.Get_error()  << endl;
	    TRACE_FLOW(trace, updateUsingEA, "esName NULL string: Get_error:" << eacInfo.Get_error() );

	    switch (eacInfo.Get_error())
	      {
	      case EAC_ESI_OK:
		returnValue = CHA_EsList::NOT_AUTHORIZED;
		break;
	      case EAC_ESI_PDB_NO_MEMORY:
	      case EAC_ESI_PDB_NOT_EXIST:
	      case EAC_ESI_PDB_ERROR:
	      case EAC_ESI_MEMORY_ERR:
	      case EAC_ESI_MAP_PAR_NO_VAL:
	      case EAC_ESI_PDB_NO_MAP:
	      case EAC_ESI_NULL_POINTER:
	      default:
		returnValue = CHA_EsList::NO_CONTACT_AUTHDB;
		break;
	      }
	  }
	else
	  {
	    myEsList.clear();

	    while(esName != 0)
	      {
	      	TRACE_FLOW(trace, updateUsingEA, "NE found: " << esName);
		myEsList.insert(esName);

		getCpsForES(eacInfo, esName);

		esName = eacInfo.Get_next_ES_name();
	      }
	  }
      }
    else
      {
//	For debugging purposes
	cerr << "no contact with the authority database" << endl;
	TRACE_FLOW(trace, updateUsingEA, "no contact with the authority database");
	returnValue = CHA_EsList::NO_CONTACT_AUTHDB;
      }
    TRACE_RETURN(trace, updateUsingEA, returnValue);
    return returnValue;*/
}

//**********************************************************************
/*
void CHA_EsList::getCpsForES(EAC_ESI_Info& eacInfo, const char* esName)
{
  int noOfCps;

  char** cpNames = eacInfo.Get_CP_names(esName, noOfCps);
  if (cpNames != NULL) {
    for (int i = 0; i < noOfCps; i++) {
      RWCString cpName(esName);
      cpName += "__";
      cpName += cpNames[i];

      TRACE_FLOW(trace, getCpsForES, "CP found: " << cpName);
      myEsList.insert(cpName);
    }
  }
}
*/

//**********************************************************************


CHA_EsList::ReturnCode CHA_EsList::updateUsingIMHAPI()
{

  // NOT USED
  return CHA_EsList::OKAY;
}


//**********************************************************************



