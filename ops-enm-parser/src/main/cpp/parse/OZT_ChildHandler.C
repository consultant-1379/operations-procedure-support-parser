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


#include <OZT_ChildHandler.H>


//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_ChildHandler";



//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_ChildHandler.C,v 21.0 1996/08/23 12:44:08 ehsgrap Rel $";


//*****************************************************************************
OZT_ChildHandler::OZT_ChildHandler(OPS::ServerRouterListener* listener)
: listener_(listener)
{
 TRACE_IN(trace, OZT_ChildHandler, listener);
 TRACE_OUT(trace, OZT_ChildHandler, "");
}



OZT_ChildHandler::~OZT_ChildHandler()
{
}



OZT_Result OZT_ChildHandler::createChildSession(const OZT_Value &scriptName)
{
   TRACE_IN(trace, createChildSession, scriptName);

    OPS::stringList *varNames = new OPS::stringList; 
    // No  var names specified so an empty list will do

    return performCreateChildSession(scriptName, varNames); 
}

OZT_Result OZT_ChildHandler::createChildSession(const OZT_Value &scriptName,
                                                RWTValOrderedVector<OZT_Value> &variableNames)
{
   TRACE_IN(trace, createChildSession, scriptName << "," << "variableNames");

    OZT_Value varName;
    OPS::stringList *varNames = new OPS::stringList;
    while (variableNames.entries() != 0)
    {
      varName = variableNames.removeFirst();
      varNames->length(varNames->length()+1);
      (*varNames)[varNames->length()-1] = varName;
    }

    return performCreateChildSession(scriptName, varNames); 
}

OZT_Result OZT_ChildHandler::performCreateChildSession(const OZT_Value &scriptName,
                                                       OPS::stringList* varNames)
{
   TRACE_IN(trace, performCreateChildSession, scriptName << "," << "variableNames");

    RWCString childSessionId = "0";
    try {
      if (listener_ != NULL) {
        childSessionId = listener_->createChildSession(scriptName, *varNames);
      } else {
        ozt_errHandler.setFlag();
        return OZT_Result(OZT_Result::FAILED, childSessionId);
      }
    }
    catch (const OPS::OPS_Exception& e)
    {
      ozt_errHandler.setFlag();
      if (e.id == OPS::CHILDREN_CAN_NOT_HAVE_CHILDREN) {
        return OZT_Result(OZT_Result::CHILD_NOT_SUPPORTED, childSessionId);
      } else {
        return OZT_Result(OZT_Result::FAILED, childSessionId);
      }
    }

    if (childSessionId == "0") {
      ozt_errHandler.setFlag();
      return OZT_Result(OZT_Result::FAILED, childSessionId);
    } 

    return OZT_Result(OZT_Result::NO_PROBLEM, childSessionId); 
}

OZT_Result OZT_ChildHandler::startChildSession(const OZT_Value &childSessionId)
{
   TRACE_IN(trace, startChildSession, childSessionId << "," << "variablePairs");

    OPS::stringList *varNames = new OPS::stringList;
    OPS::stringList *varValues = new OPS::stringList;
    // No variables specified so empty lists

    return performStartChildSession(childSessionId, varNames, varValues); 
}

OZT_Result OZT_ChildHandler::startChildSession(const OZT_Value &childSessionId,
                                               RWTValOrderedVector<OZT_Value> &variablePairs)
{
   TRACE_IN(trace, startChildSession, childSessionId << "," << "variablePairs");

    OZT_Value varName;
    OZT_Value varValue;
    OPS::stringList *varNames = new OPS::stringList;
    OPS::stringList *varValues = new OPS::stringList;
    while (variablePairs.entries()!=0)
    {
      varName = variablePairs.removeFirst();
      varNames->length(varNames->length()+1);
      (*varNames)[varNames->length()-1] = varName;
      varValue = variablePairs.removeFirst();
      varValues->length(varValues->length()+1);
      (*varValues)[varValues->length()-1] = varValue;
    }

    return performStartChildSession(childSessionId, varNames, varValues); 
}
                                 
OZT_Result OZT_ChildHandler::performStartChildSession(const OZT_Value &childSessionId,
                                                      OPS::stringList* varNames,
                                                      OPS::stringList* varValues)
{
   TRACE_IN(trace, performStartChildSession, childSessionId << "," << "variablePairs");

    RWCString result = "0";
    try {
      if (listener_ != NULL) {
        result = listener_->startChildSession(childSessionId, *varNames, *varValues);
      } else {
        ozt_errHandler.setFlag();
        return OZT_Result(OZT_Result::FAILED, result);
      }
    }
    catch (const OPS::OPS_Exception& e)
    {
      ozt_errHandler.setFlag();
      if (e.id == OPS::CHILDREN_CAN_NOT_HAVE_CHILDREN) {
        return OZT_Result(OZT_Result::CHILD_NOT_SUPPORTED, childSessionId);
      } else if (e.id == OPS::INVALID_CHILD_SESSION_ID) {
        return OZT_Result(OZT_Result::INVALID_CHILD_SESSION_ID, result);
      } else if (e.id == OPS::VARIABLE_NOT_SUBSCRIBED) {
        return OZT_Result(OZT_Result::CHILD_VARIABLE_NOT_SUBSCRIBED, result);
      } else {
        return OZT_Result(OZT_Result::FAILED, result);
      }
    }

    if (result == "0") {
      ozt_errHandler.setFlag();
      return OZT_Result(OZT_Result::FAILED, result);
    } 

    return OZT_Result(OZT_Result::NO_PROBLEM, result); 
}

OZT_Result OZT_ChildHandler::checkChildSession(const OZT_Value &sessionId)
{
   TRACE_IN(trace, checkCildSession, sessionId);

    RWCString result = "";
    try {
      if (listener_ != NULL) {
        result = listener_->checkChildSession(sessionId);
      } else {
        ozt_errHandler.setFlag();
        return OZT_Result(OZT_Result::FAILED, result);
      }
    }
    catch (const OPS::OPS_Exception& e)
    {
      ozt_errHandler.setFlag();
      if (e.id == OPS::CHILDREN_CAN_NOT_HAVE_CHILDREN) {
        return OZT_Result(OZT_Result::CHILD_NOT_SUPPORTED, sessionId);
      } else if (e.id == OPS::INVALID_CHILD_SESSION_ID) {
        return OZT_Result(OZT_Result::INVALID_CHILD_SESSION_ID, result);
      } else {
        return OZT_Result(OZT_Result::FAILED, result);
      }
    }

    return OZT_Result(OZT_Result::NO_PROBLEM, result); 
}
                                 
OZT_Result OZT_ChildHandler::terminateChildSession(const OZT_Value &sessionId)
{
   TRACE_IN(trace, terminateChildSession, sessionId);

    RWCString result = "0";
    try {
      if (listener_ != NULL) {
        result = listener_->terminateChildSession(sessionId);
      } else {
        ozt_errHandler.setFlag();
        return OZT_Result(OZT_Result::FAILED, result);
      }
    }
    catch (const OPS::OPS_Exception& e)
    {
      ozt_errHandler.setFlag();
      if (e.id == OPS::CHILDREN_CAN_NOT_HAVE_CHILDREN) {
        return OZT_Result(OZT_Result::CHILD_NOT_SUPPORTED, sessionId);
      } else if (e.id == OPS::INVALID_CHILD_SESSION_ID) {
        return OZT_Result(OZT_Result::INVALID_CHILD_SESSION_ID, result);
      } else {
        return OZT_Result(OZT_Result::FAILED, result);
      }
    }

    if (result == "0") {
      ozt_errHandler.setFlag();
      return OZT_Result(OZT_Result::FAILED, result);
    } 

    return OZT_Result(OZT_Result::NO_PROBLEM, result); 
}
                                 
OZT_Result OZT_ChildHandler::readVariable(const OZT_Value &sessionId, const OZT_Value &variableName)
{
   TRACE_IN(trace, readVariable, sessionId + ", " + variableName);

    RWCString result = "";
    try {
      if (listener_ != NULL) {
        result = listener_->readChildSessionVariable(sessionId, variableName);
      } else {
        ozt_errHandler.setFlag();
        return OZT_Result(OZT_Result::FAILED, result);
      }
    }
    catch (const OPS::OPS_Exception& e)
    {
      ozt_errHandler.setFlag();
      if (e.id == OPS::CHILDREN_CAN_NOT_HAVE_CHILDREN) {
        return OZT_Result(OZT_Result::CHILD_NOT_SUPPORTED, sessionId);
      } else if (e.id == OPS::INVALID_CHILD_SESSION_ID) {
        return OZT_Result(OZT_Result::INVALID_CHILD_SESSION_ID, result);
      } else if (e.id == OPS::VARIABLE_NOT_SUBSCRIBED) {
        return OZT_Result(OZT_Result::CHILD_VARIABLE_NOT_SUBSCRIBED, result);
      } else {
        return OZT_Result(OZT_Result::FAILED, result);
      }
    }

    return OZT_Result(OZT_Result::NO_PROBLEM, result); 
}
                                 
