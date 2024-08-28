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

#include <OPS_EventHandler.H>
//#include <CHA_Trace.H>

// Static data member initialization
// trace

#include <trace.H>
static std::string trace ="OPS_EventHandler";

#ifdef HPUX10
static pthread_mutexattr_t pthreadMutexAttrInit_ = { 0, 0, 0 };
#endif

//********************************+*****************************************  
OPS_EventHandler::OPS_EventHandler(): 
  _pConnection(NULL),
  clientAlive(TRUE),
  connCheckFlag(TRUE)
{
  TRACE_IN(trace, OPS_EventHandler, "");


  pthread_mutex_init( &eventMutex_, 0 );


#ifdef HPUX10
  pthread_mutex_init( &eventMutex_, pthreadMutexAttrInit_ );
#endif

  TRACE_OUT(trace, OPS_EventHandler, "");
}


//********************************+*****************************************  
OPS_EventHandler::~OPS_EventHandler()
{
  pthread_mutex_destroy( &eventMutex_ );
}

//*****************************************************************************

void OPS_EventHandler::startDispatch()
{
  TRACE_IN(trace, startDispatch, "");

  getOut = FALSE;
  while (!getOut && clientAlive)
  {
    TRACE_IN(trace, startDispatch, "clientAlive = " << clientAlive);
    if (!connCheckFlag) // It's about a delay or delaysec, do not check the connection
      {
	// sleep a while so that it doesn't use up the CPU. Should be longer than 1000 usec here
	sleepAWhile();         
	if (getOut) break;    // in case the gui has set getOut during the sleep
	dispatchEvents();
      }
    else                 // It's about a MML procedure, check the connection
      {
	if (_pConnection != NULL)
	  {
	    //Check the connection status
       int i = _pConnection->getConnectionStatus();
	    //if (i < 0/*!= EAC_CRI_CS_CONNECTED*/)
	    if (i != 4)
	      {
		TRACE_FLOW(trace, startDispatch, "CONNECTION NOT EXIST");
		getOut = TRUE;
	      }
	    else
	      {
		// sleep a while so that it doesn't use up the CPU. Should not be more than 1000 usec here
		sleepAWhile();         
		if (getOut) break;    // in case the gui has set getOut during the sleep
		dispatchEvents();
                getOut = TRUE;    //TORF-241666 : Its a hack
	      }
	  }
	else
	  {
	    TRACE_FLOW(trace, startDispatch, "CONNECTION OBJECT NOT EXIST");
	    getOut = TRUE;
	  }
      }
    
  }

  TRACE_OUT(trace, startDispatch, "");
}

//*****************************************************************************

void OPS_EventHandler::dispatchEvents()
{
  OZT_EventHandler::dispatchEvents();
  dispatchGuiEvents();
  removeTrashedClients();
}

//*****************************************************************************

OZT_Result OPS_EventHandler::waitResult(RWBoolean checkFlag)
{
  TRACE_IN(trace, waitResult, " connCheckFlag = " << checkFlag);

  connCheckFlag = checkFlag;

  startDispatch();

  TRACE_RETURN(trace, waitResult, result);  // result is set via 
  return result;                            // OZT_EventHandler::setResult()
}

//****************************************************************************

void OPS_EventHandler::dispatchGuiEvents()
{
  pthread_mutex_lock(&eventMutex_);
  for (size_t i = 0; i < guiClients.entries(); i++)
  {
    if (getOut) {
      pthread_mutex_unlock(&eventMutex_);
      return;
    }
    TRACE_FLOW(trace, dispatchGuiEvents, "dispatching GUI event " << i);
    if (guiClients[i]->isValid()) {
      guiClients[i]->dispatchGuiEvent();
      guiClients[i]->markToTrash();
    }
  }
  pthread_mutex_unlock(&eventMutex_);
}

//************************************************************************

void OPS_EventHandler::removeTrashedClients()
{
  register int i;

  OZT_EventHandler::removeTrashedClients();

  pthread_mutex_lock(&eventMutex_);
  for (i = guiClients.entries() - 1; i >= 0; i--) {
    if (guiClients[i]->toBeTrashed()) {
      TRACE_FLOW(trace, removeTrashedClients, "Removing client " << i);
      delete guiClients.removeAt(i);
    }
  }
  pthread_mutex_unlock(&eventMutex_);

}

//************************************************************************

void OPS_EventHandler::setGuiTrigger(void *instance,
                                     int (*func)(void *, void *),
                                     void *args,
                                     void (*cleaner)(void *))
{
  TRACE_IN(trace, setGuiTrigger, "");

  OPS_GuiClient *client = new OPS_GuiClient(instance, func, args, cleaner);

  pthread_mutex_lock(&eventMutex_);
  guiClients.append(client);
  pthread_mutex_unlock(&eventMutex_);

  TRACE_OUT(trace, setGuiTrigger, "");
}
 
//************************************************************************
 
void OPS_EventHandler::unsetGuiTrigger(void *instance)
{
  TRACE_IN(trace, unsetGuiTrigger, "");

  pthread_mutex_lock(&eventMutex_);
  for (size_t i = 0; i < guiClients.entries(); i++)
  {
    if (guiClients[i]->getInstance() == instance)
      guiClients[i]->markToTrash();
  }
  pthread_mutex_unlock(&eventMutex_);

  TRACE_OUT(trace, unsetGuiTrigger, "");
}

//***********************************************************************

OPS_GuiClient::OPS_GuiClient(void *theInstance, 
                           int (*theFunc)(void*, void*), 
                           void *theArgs,
                           void (*theCleaner)(void*))
: OZT_Client()
{
  OPS_GuiClient::instance = theInstance;
  OPS_GuiClient::function = theFunc;
  OPS_GuiClient::args     = theArgs;
  OPS_GuiClient::cleaner  = theCleaner;
}

OPS_GuiClient::~OPS_GuiClient()
{
  if (OPS_GuiClient::cleaner != NULL)
    OPS_GuiClient::cleaner(OPS_GuiClient::args);
}

OZT_ClientType OPS_GuiClient::type() const
{
  return OZT_GUI_CLIENT;
}

RWBoolean OPS_GuiClient::operator==(const OZT_Client &client) const
{
  if ((type() == client.type()) && (instance == client.getInstance()))
    return TRUE;
  else
    return FALSE;
}


void OPS_GuiClient::dispatchGuiEvent()
{
  OPS_GuiClient::function(OPS_GuiClient::instance, OPS_GuiClient::args);
}



//***********************************************************************
void OPS_EventHandler::setConnectionRef(CHA_Connection *pConnection)
{
  TRACE_IN(trace, setConnectionRef, "");
  
  _pConnection = pConnection;
   
  TRACE_OUT(trace, setConnectionRef, "");
}

//***********************************************************************
void OPS_EventHandler::clientStatus(RWBoolean statusFlag)
{
  TRACE_IN(trace, clientStatus, "clientAlive = " << statusFlag);
  
  clientAlive = statusFlag;
   
  TRACE_OUT(trace, clientStatus, "");
}
