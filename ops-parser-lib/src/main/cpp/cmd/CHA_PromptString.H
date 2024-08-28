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


#ifndef CHA_PROMPTSTRING_H
#define CHA_PROMPTSTRING_H

#include <CHA_Model.H>
#include <CHA_ModelClient.H>
#include <CHA_IPCSupervisor.H>
#include <CHA_Connection.H>

#include <rw/cstring.h>

// forward declarations
class CHA_CommandSender;

class CHA_PromptString : public CHA_Model, public CHA_ModelClient
{

public:
    CHA_PromptString(){}
    CHA_PromptString(CHA_CommandSender* pCmdSender,
		     CHA_IPCSupervisor* pIPCSup);
    // Description:
    //     Constructor. The CHA_CommandSender is used to get hold of
    //     the EAC_CRI_Connection object that is the basis for the 
    //     prompt information.
    //     The CHA_IPCSupervisor is a trigger for checking after new
    //     prompt information.
    
    virtual ~CHA_PromptString();
    // Description:
    //     Destructor.

    const RWCString& getPrompt();
    // Description:
    //     Get the current prompt.
    // Return value
    //     A RWCString containing the prompt.

 
    void checkPrompt();
    // Description.
    //     Checks if there is any prompt information. If so, it calls
    //     setPrompt(). Is called by updateFrom()
    
    virtual void updateFrom(CHA_Model* p, void* d);
    // Description:
    //     To be updated from the CHA_IPCSupervisor.
    //
    //     Not for use in the main program!
    
    virtual void detachFrom(CHA_Model* model);
    // Description:
    //     Used by the CHA_IPCSupervisor when it is destructed.
    //
    //     Not for use in the main program!
    
private:
    
    void setPrompt(const RWCString& p);
    // Description:
    //     To set the current prompt.
    //	   If the prompt is the same as the old one, an empty string 
    //     or contains garbage it's not used.
    //     Is called by checkPromt() and normally not by the application.
 
    RWCString currentPrompt;
    CHA_IPCSupervisor* pIPCSupervisor;
    CHA_Connection* pCHAConnection;
};

#endif
