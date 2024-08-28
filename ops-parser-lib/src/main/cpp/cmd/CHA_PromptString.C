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
#include <CHA_Trace.H>
#include <CHA_PromptString.H>
#include <CHA_CommandSender.H>
#include <trace.H>

static std::string trace ="CHA_PromptString";


//**********************************************************************


CHA_PromptString::CHA_PromptString(CHA_CommandSender* pCmdSender,
				   CHA_IPCSupervisor* pIPCSup)
: pIPCSupervisor(pIPCSup),
  pCHAConnection(NULL)
{
    TRACE_IN(trace, CHA_PromptString, "");

    if(pCmdSender != NULL)
    {
	pCHAConnection = pCmdSender->getConnectionObject();
    }

    if(pIPCSupervisor != NULL)
    {
	pIPCSupervisor->addDependent(this);
    }

    currentPrompt = "*";		// the uninitialized prompt
    checkPrompt();			// now initialize it
}


//**********************************************************************


CHA_PromptString::~CHA_PromptString()
{
    if(pIPCSupervisor != NULL)
	pIPCSupervisor->removeDependent(this);
}


//**********************************************************************


const RWCString& CHA_PromptString::getPrompt()
{
    // Check the prompt first, so that the returned prompt is an absolutely
    // fresh one.
    // getPrompt() might be called from somebody whos was called updateFrom()
    // by this object's changed() call, but there is no risk for eternal
    // recusion since checkPrompt() will only cause a changed() if the
    // prompt actually has changed.
    checkPrompt();
    return currentPrompt;
}


//**********************************************************************


void CHA_PromptString::setPrompt(const RWCString& newPrompt)
{
	TRACE_IN(trace, setPrompt, newPrompt);
    // return quickly if this doesn't seem to be a useful prompt
    if((newPrompt == currentPrompt)
       || newPrompt.isNull()
       || !(newPrompt.isAscii()))
    {
   	TRACE_RETURN(trace, setPrompt, "prompt not useful");
	return;
    }

    // actually set the prompt
    TRACE_FLOW(trace, setPrompt, "new! " << newPrompt);
    currentPrompt = newPrompt;
    changed();
	TRACE_RETURN(trace, setPrompt, "");
}


//**********************************************************************


void CHA_PromptString::updateFrom(CHA_Model* p, void* d)
{
    checkPrompt();
}


//**********************************************************************


void CHA_PromptString::detachFrom(CHA_Model* model)
{
    if((CHA_IPCSupervisor*) model == pIPCSupervisor)
    {
	pIPCSupervisor = NULL;
    }
}



//**********************************************************************


void CHA_PromptString::checkPrompt()
{
	TRACE_IN(trace, checkPrompt, "");
    // there is no point doing this if we don't have a connection object
    if(pCHAConnection == NULL)
    {
	TRACE_RETURN(trace, checkPrompt, "no EA connection obj!");
	return;
    }

    // if EA provides a prompt, use it and return
   /* const char* EAPrompt = pCHAConnection->connection.Get_prompt();
    if(EAPrompt != NULL)
    {
	setPrompt(EAPrompt);
	//TRACE_RETURN(trace, checkPrompt, "using EAPrompt");
	return;
    }

    // if not connected, set a disconnect prompt and return
    if(pCHAConnection->connection.Get_connection_status() != EAC_CRI_CS_CONNECTED)
    {
	setPrompt("-");
	//TRACE_RETURN(trace, checkPrompt, "set disconnect prompt '-'");
	return;
    }

    // If connected, but EA doesn't provede a prompt, make one up
    switch(pCHAConnection->connection.Get_connection_mode())
    {
    case EAC_CRI_CM_COMMAND:
    //TRACE_FLOW(trace, checkPrompt, "case EAC_CRI_CM_COMMAND");
	setPrompt("<");
	break;
    case EAC_CRI_CM_CONFIRMATION:
    //TRACE_FLOW(trace, checkPrompt, "case EAC_CRI_CM_CONFIRMATION");
	setPrompt("?");
	break;
    case EAC_CRI_CM_DIALOGUE:
    //TRACE_FLOW(trace, checkPrompt, "case EAC_CRI_CM_DIALOGUE");
	setPrompt(":");
	break;
    case EAC_CRI_CM_NO_CONNECTION:
    //TRACE_FLOW(trace, checkPrompt, "case EAC_CRI_CM_NO_CONNECTION");
	setPrompt("-");
	break;
    default:
        //TRACE_FLOW(trace, checkPrompt, "case default");
	// don't do anything about the prompt, i.e. keep as is
	break;
    }
	//TRACE_RETURN(trace, checkPrompt, "");
*/
}


//**********************************************************************

