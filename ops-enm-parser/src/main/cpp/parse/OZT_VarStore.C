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


#include "OZT_VarStore.H"


//*****************************************************************************

// trace
#include <trace.H>
static std::string trace ="OZT_VarStore";

//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_VarStore.C,v 21.0 1996/08/23 12:45:02 ehsgrap Rel $";


//*****************************************************************************

//static unsigned hashString(const RWCString& str) {return str.hash();}

OZT_VarStore::OZT_VarStore()
  : store()
{
    // No code needed.
}


OZT_VarStore::~OZT_VarStore()
{
    // No code needed.
}


void OZT_VarStore::put(const RWCString &varName, const OZT_Value &content)
{
    RWCString temp = varName; 

    temp.toUpper();
    if(store.contains(temp)) 
      store.remove(temp); // insertKeyAndValue doesn't replace, so remove
                          // the any old value first. 
    store.insertKeyAndValue(temp, content);
    TRACE_FLOW(trace, put, "Variable " << temp << " - value " << content 
                                       << "; number of entries in the store " << entries());
    
    changed((void*)&temp);
}

RWBoolean OZT_VarStore::get(const RWCString &varName, OZT_Value &content)
{
    RWCString temp = varName;

    temp.toUpper();
    TRACE_FLOW(trace, get, "number of entries in the store " << entries());
    return store.findValue(temp, content);
}


RWBoolean OZT_VarStore::contains(const RWCString &varName)
{
    RWCString temp = varName;

    temp.toUpper();
    TRACE_FLOW(trace, contains, "number of entries in the store " << entries());

    return store.contains(temp);
}


RWBoolean OZT_VarStore::flushVar(const RWCString &varName)
{
    RWCString temp = varName;

    temp.toUpper();
    TRACE_FLOW(trace, flushVar, "number of entries in the store " << entries());
    if (store.remove(temp))
    {
        changed((void*)&temp);
        return TRUE;
    }
    else
        return FALSE;
}


void OZT_VarStore::clearAll()
{
    TRACE_FLOW(trace, clearAll, "number of entries in the store " << entries());
  if( store.isEmpty() == FALSE ){
    store.clear();
    RWCString temp;
    changed((void*)&temp);
    //changed();
  }
}


size_t OZT_VarStore::entries()
{
    return store.entries();
}


OZT_Result OZT_VarStore::inc(const RWCString &varName)
{
    RWCString temp = varName;
    OZT_Value  content;
    OZT_Result result;

    temp.toUpper();

    if (!get(temp, content))
        return OZT_Result(OZT_Result::VAR_UNDEFINED, temp);

    content = add(content, OZT_Value(1L), result);
    if (result.code != OZT_Result::NO_PROBLEM)
        return result;

    put(temp, content);
    return OZT_Result(OZT_Result::NO_PROBLEM);
}


OZT_Result OZT_VarStore::dec(const RWCString &varName)
{
    RWCString temp = varName;
    OZT_Value  content;
    OZT_Result result;

    temp.toUpper();
    if (!get(temp, content))
        return OZT_Result(OZT_Result::VAR_UNDEFINED, temp);

    content = sub(content, OZT_Value(1L), result);
    if (result.code != OZT_Result::NO_PROBLEM)
        return result;

    put(temp, content);
    return OZT_Result(OZT_Result::NO_PROBLEM);
}
