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


#include "OpsParserOrbHandler.H"
#include <trace.H>

//USE_STD_NS

static std::string trace ="OpsParserOrbHandler";

typedef std::list<std::string> PropertiesList;


const RWCString OPS_ENABLE_LOCATOR = "-Dvbroker.agent.enableLocator=false";
const RWCString OPS_NAME_SERVICE_START = "-DORBInitRef NameService=iioploc://";
const RWCString OPS_NAME_SERVICE_END = "/NameService";

const RWCString OPS_SERVER = "ops_server"; //Check the same name in ops-server module

OpsParserOrbHandler* OpsParserOrbHandler::orbHdlRef = NULL;

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
OpsParserOrbHandler::OpsParserOrbHandler(){
}

//--------------------------------------------------------------------------------
OpsParserOrbHandler::OpsParserOrbHandler(RWCString _sessionId, RWCString _parserName, RWCString _serverSuffix): 
serverRLRef(NULL),
serverLRef_v(NULL), 
parserLRef(NULL){

  TRACE_IN(trace, OpsParserOrbHandler, " ");
  sSessionId = _sessionId;
  parserName = _parserName;
  TRACE_FLOW(trace, OpsParserOrbHandler, "parserName =  " << parserName);
  serverSuffix = _serverSuffix;
  if (serverSuffix == "NO_SUFFIX")serverName = OPS_SERVER;
  else serverName = OPS_SERVER + serverSuffix;
  TRACE_FLOW(trace, OpsParserOrbHandler, "serverName =  " << serverName);
}
//--------------------------------------------------------------------------------

OpsParserOrbHandler::~OpsParserOrbHandler(){
  if( serverRLRef != OPS::ServerRouterListener::_nil() )
  {
  CORBA::release(serverRLRef);
    serverRLRef = OPS::ServerRouterListener::_nil();
  }
  if(parserLRef)
  {
  delete parserLRef;
    parserLRef = NULL;
  }
}

//--------------------------------------------------------------------------------
OpsParserOrbHandler* OpsParserOrbHandler::getInstance(RWCString _sessionId,  RWCString _parserName, RWCString _serverSuffix){
  TRACE_IN(trace, getInstance, " ");
  if (orbHdlRef == NULL) orbHdlRef = new OpsParserOrbHandler(_sessionId, _parserName, _serverSuffix);
  TRACE_OUT(trace, getInstance, " ");
  return orbHdlRef;
}

//--------------------------------------------------------------------------------
OpsParserOrbHandler* OpsParserOrbHandler::getInstance(){
  TRACE_IN(trace, getInstance, " ");
  if (orbHdlRef == NULL) orbHdlRef = new OpsParserOrbHandler();
  TRACE_OUT(trace, getInstance, " ");
  return orbHdlRef;
}

//--------------------------------------------------------------------------------
OpsParserListenerImpl*  OpsParserOrbHandler::getParserListenerRef(){
  TRACE_IN(trace, getParserListenerRef, " ");
  TRACE_OUT(trace, getParserListenerRef, " ");
  return parserLRef;
}

//--------------------------------------------------------------------------------
OPS::ServerRouterListener_ptr OpsParserOrbHandler::getServerRouterRef(int serverRestart){
  TRACE_IN(trace, getServerRouterRef, " ");
  RWDateTime t;
  unsigned long endTime;
  CORBA::Object_var ns;
  char ns_ior[256];

  char *ns_host = getenv("OPSNameServiceHost");
  char *ns_port = getenv("OPSNameServicePort");
  RWCString nameServiceInitRef = OPS_NAME_SERVICE_START + ns_host + ":" + ns_port  + OPS_NAME_SERVICE_END;
  TRACE_FLOW(trace, getServerRouterRef, "nameServiceInitRef    " << nameServiceInitRef);

  // When this method is called, ref to server objects are NULL
  serverLRef_v = NULL; 
  serverRLRef = NULL;

  if (!serverRestart)
    {
      
      //**************************ORB HANDLING START************************
      static int nArgc = 2;
      static char* aArgv[] = {strdup((const char*)nameServiceInitRef),
			      strdup((const char*)OPS_ENABLE_LOCATOR)}; // What more should be send!?, COMPONENT_NAME should be enough!
    
      try
	{

	  // Initialize the ORB
	  pOrb = CORBA::ORB_init(nArgc, aArgv);
	}
      catch(const CORBA::Exception &e)
	{
	  TRACE_INFO(trace, getServerRouterRef, " CORBA::Exception");
	  CORBA::SystemException* sys_excep;
	  sys_excep =
	    CORBA::SystemException::_downcast((CORBA::Exception*)&e);
	  if(sys_excep != NULL) {
	    TRACE_INFO(trace, getServerRouterRef,  "System Exception occurred:" << endl);
	    cerr << "System Exception occurred:" << endl;
	    TRACE_INFO(trace, getServerRouterRef, "exception name: " << sys_excep->_name() << endl);
	    cerr << "exception name: " << sys_excep->_name() << endl;
	    TRACE_INFO(trace, getServerRouterRef, "minor code: " << sys_excep->minor() << endl);
	    cerr << "minor code: " << sys_excep->minor() << endl;
	    TRACE_INFO(trace, getServerRouterRef, "completion code: " << sys_excep->completed() << endl);
	    cerr << "completion code: " << sys_excep->completed() << endl;
	  }
	  else {
	    TRACE_INFO(trace, getServerRouterRef, "Not a system exception" << endl);
	    cerr << "Not a system exception" << endl;
	    // cerr << e << endl;
	  }
	}
    }//if (!serverRestart)
  //*********************************NS HANDLING START******************************

  if (serverRestart)endTime = (t.milliSeconds()/1000) + OPS::ServerListener::OPS_SERVER_SUPERVISION_TIME; // Parser has got five minutes to find the server after a restart
  else endTime = (t.milliSeconds()/1000 ) + OPS::ServerRouterListener::OPS_STARTING_SUPERVISION_TIME;
  while ((( t.now().milliSeconds()/1000 ) < endTime) && serverLRef_v == NULL){
   try
      {
	// Get a reference to the Naming Service root_context
	sprintf(ns_ior,
		"iioploc://%s:%s/NameService",
		ns_host,
		ns_port);
	ns = pOrb->string_to_object(ns_ior);
	TRACE_FLOW(trace, getServerRouterRef, "NS_ior  " << ns_ior);
	
	CosNaming::NamingContextExt_var rootContext = CosNaming::NamingContextExt::_narrow(ns);
	
	// Locate the server listener through the Naming Service

    CosNaming::Name name (1);
    name.length (1);
    name[0].id = CORBA::string_dup (OPS_SERVER);

	CORBA::Object_var parserObj = rootContext->resolve(name);
	serverLRef_v = OPS::ServerListener::_narrow(parserObj);
      }
    catch(CORBA::Exception& x)
      {
	TRACE_INFO(trace, getServerRouterRef, "Corba Exception: " << x._name() << endl);
      }
    if (serverRestart)sleep(1); 
  }//while (...)
  if (serverLRef_v == NULL) return NULL;

  // Give the client a chance to initiate a server router object 
  //after restart before parser asks for the server router 
  if (serverRestart)sleep(OPS::ServerRouterListener::OPS_STARTING_SUPERVISION_TIME);

  //*********************************NS HANDLING END******************************
  TRACE_FLOW(trace, getServerRouterRef, "NS HANDLING OK, ref to server listener OK ");
  
  if (!serverRestart)
    {
      //****************************ROOT POA , POA and Parser listenr object HANDLING START*****************
      // get a reference to the root POA
      CORBA::Object_var obj = pOrb->resolve_initial_references("RootPOA"); 
      PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(obj);
      
      // My own policies
      CORBA::PolicyList myPolicies;
      myPolicies.length(1);
      myPolicies[(CORBA::ULong)0] = rootPOA->create_lifespan_policy(PortableServer::TRANSIENT);
      
     
      // get the POA manager
      PortableServer::POAManager_var pPoaManager = rootPOA->the_POAManager();
      // create myPOA with my and the security policies
           PortableServer::POA_var myPOA = rootPOA->create_POA("ops_parser_poa", 
							       pPoaManager,
							       myPolicies); 
      //----------------------------
      // Create a new Parser object. 
      //----------------------------
      
      parserLRef = new OpsParserListenerImpl(pOrb);
      PortableServer::ObjectId_var pManagerId = PortableServer::string_to_ObjectId(parserName);
      myPOA->activate_object_with_id(pManagerId, parserLRef);
      pPoaManager->activate();
      pReference = OPS::ParserListener::_narrow(myPOA->id_to_reference(pManagerId));

      //****************************ROOT POA , POA and Parser listenr object HANDLING END*****************
    }//if (!serverRestart)

  //****************************Server Listener HANDLING START*****************
  // Get ref to the server listener object
  //--------------------------------------------
  // and send the parser listener ref to the OPS server
  //--------------------------------------------
  if (serverRestart)endTime = ( t.milliSeconds()/1000 )+ OPS::ServerListener::OPS_SERVER_SUPERVISION_TIME; // Parser has got five minutes to find the server after a restart
  else endTime = ( t.milliSeconds()/1000 )+OPS::ServerRouterListener::OPS_STARTING_SUPERVISION_TIME;
  while ((( t.now().milliSeconds()/1000 ) < endTime) && serverRLRef == NULL){
 try {
   serverRLRef = serverLRef_v->setParserListener(pReference.in(), sSessionId);
 }
 catch(const CORBA::Exception& x) {
   TRACE_INFO(trace, getServerRouterRef, "Corba Exception: " << x._name() << endl);
   return NULL;
 }
  if (serverRestart)sleep(1);
  }// while
  
  TRACE_FLOW(trace, getServerRouterRef, "parser listener ref is sent and ref to server router listener is received" );
  
  //****************************Server Listener ref HANDLING END*****************
  
  TRACE_OUT(trace, getServerRouterRef, " ");
  return serverRLRef;
}

//--------------------------------------------------------------------------------
OPS::ServerListener_var OpsParserOrbHandler::getServerRef(){
  TRACE_IN(trace, getServerRef, " ");
  TRACE_OUT(trace, getServerRef, " ");
  return serverLRef_v;
}

//--------------------------------------------------------------------------------
CORBA::ORB_var OpsParserOrbHandler::getOrb(){
  TRACE_IN(trace, getOrb, " ");
  TRACE_OUT(trace, getOrb, " ");
  return pOrb;
}
