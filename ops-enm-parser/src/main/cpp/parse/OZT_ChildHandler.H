// RCS revision handling
// $Id: OZT_ChildHandler.H,v 21.0 1996/08/23 12:41:07 ehsgrap Rel $

//*****************************************************************************


#ifndef OZT_ChildHandler_H
#define OZT_ChildHandler_H

#include <OZT_Value.H>
#include <OZT_ErrHandling.H>
#include <rw/defs.h>
#include <rw/cstring.h>
#include <rw/tvordvec.h>
#include "OPSS.H"

class OZT_ChildHandler {
public:
    /**
     * Constructor
     *
     */
    OZT_ChildHandler(OPS::ServerRouterListener* listener);


    /**
     * Destructor
     *
     */
    ~OZT_ChildHandler();

    OZT_Result createChildSession(const OZT_Value &scriptName);
    OZT_Result createChildSession(const OZT_Value &scriptName,
                                  RWTValOrderedVector<OZT_Value> &variableNames);
    OZT_Result performCreateChildSession(const OZT_Value &scriptName,
                                         OPS::stringList* varNames);
                                 
    OZT_Result startChildSession(const OZT_Value &sessionId);
    OZT_Result startChildSession(const OZT_Value &sessionId,
                                 RWTValOrderedVector<OZT_Value> &variablePairs);
    OZT_Result performStartChildSession(const OZT_Value &childSessionId,
                                        OPS::stringList* varNames,
                                        OPS::stringList* varValues);
                                 
    OZT_Result checkChildSession(const OZT_Value &sessionId);
                                 
    OZT_Result terminateChildSession(const OZT_Value &sessionId);
                                 
    OZT_Result readVariable(const OZT_Value &sessionId, const OZT_Value &variableName);
    
private:
    OZT_ChildHandler(){};

    OPS::ServerRouterListener_ptr listener_;
};


#endif
