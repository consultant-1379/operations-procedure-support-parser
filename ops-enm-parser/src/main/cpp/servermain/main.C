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

#include <stdlib.h>
#include <iostream>
#include <rw/regexp.h>

#ifndef NONE_CLASH
#define NONE_CLASH
#endif

#include <OPSS.H>
#include <CHA_EsList.H>
#include "OpsParserListenerImpl.H"
#include "OpsParserOrbHandler.H"
#include <corba.h>
#include <syslog.h>

#include <trace.H>

//USE_STD_NS

using namespace std;

static std::string trace = "main";

/**
 * OPS Server main program
 *
 */
int main(int argc, char** argv)
{
  OPSLogger::getInstance().init_logging();
  syslog(LOG_INFO, "Start of script execution");
  TRACE_INFO(trace, main, "Start of script execution");
  RWCString parserName;
  RWCString serverSuffix;
  RWCString sSessionId;
  RWCString userId;
  RWCString pwd;
  OPS::ClientType listenerType;
  OPS::ServerRouterListener_ptr serverRLRef;
  OpsParserListenerImpl* parserLRef;
  OpsParserOrbHandler* orbHdlRef;

  
  try {
    
    // Read in-parameters.
    TRACE_FLOW(trace, main, "number of arguments = " << argc);
    for (int i = 0; i<argc; i++ )
      TRACE_FLOW(trace, main, "argument " << i << ": " << *(argv+i));
    
    if (argc < 3) {
      TRACE_INFO(trace, main, "Failed to start OPS parser, too few arguments.");
      cerr << "ERROR: Failed to start OPS parser, too few arguments." << endl;
      return -1;
    }
    else if (argc > 3)  //Display is included in arg. list.
    {
      parserName = argv[2];
      serverSuffix = argv[3];
    }
    else
    {
      parserName = argv[1];
      serverSuffix = argv[2];
    }
    
    //-----------------------------------------------------------------------------
    // Calculate first session id (string and int)
    //-----------------------------------------------------------------------------
    
    RWCRegexp rSessId("[0-9]+$"); // Name is ending with the sessionId.
    size_t nPos = parserName.index(rSessId);
    sSessionId = parserName(nPos, parserName.length() - nPos);
    TRACE_FLOW(trace, main, "sSessionId   " << sSessionId);
    
    // Start ORB handler
    orbHdlRef = OpsParserOrbHandler::getInstance(sSessionId, parserName, serverSuffix);

    // Get server router ref
    serverRLRef = orbHdlRef->getServerRouterRef();

    // Get Parser listener ref
    parserLRef = orbHdlRef->getParserListenerRef();
    //--------------------------------------------
    // Set the session data in parser listener 
    //--------------------------------------------

    if (serverRLRef != NULL && parserLRef != NULL)
    {
      char* u;
      char* p;
      listenerType = serverRLRef->getClientInfo(sSessionId, u, p);
      userId = u;
      pwd = p;
      parserLRef->setSessionData(serverRLRef,
                             sSessionId,
                             listenerType,
                             userId,
                             pwd);
    }
    else
    {
      TRACE_INFO(trace, main, "Failed to start OPS parser, server router listener not exist: " << sSessionId);
      delete orbHdlRef;
      return -1;
    }


    //--------------------------------------------
    // Activate the orb
    //--------------------------------------------

    TRACE_FLOW(trace, main, "OPS parser is waiting for requests" );
    (orbHdlRef->getOrb())->run();
    parserLRef->cleanup();

  }

  catch(const CORBA::Exception& x) {
      TRACE_INFO(trace, main, "Corba Exception: " << x._name() << endl);
      cerr << "main: Corba Exception: " << x._name() << endl;
      return -1;
  }

  delete orbHdlRef;
  syslog(LOG_INFO, "End of script execution");
  TRACE_INFO(trace, main, "End of script execution");
  return 0;

}
