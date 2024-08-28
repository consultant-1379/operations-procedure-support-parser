// ---------------------------------------------------------------------
// 
//  COPYRIGHT EAB Sweden 2005.
//  All rights reserved.
//
//  The Copyright to the computer program(s) herein is the property of
//  EAB.
//  The program(s) may be used and/or copied only with the written
//  permission from EAB Sweden or in accordance with the terms and
//  conditions stipulated in the  agreement/contract under which the
//  program(s) have been supplied.
//
// ---------------------------------------------------------------------
// Handle CORBA related activity for OPS Parser, using VisiBroker C++
// 

#ifndef OPS_PARSER_ORB_HANDLER_H
#define OPS_PARSER_ORB_HANDLER_H

#include <stdlib.h>
#include <iostream>
#include <rw/regexp.h>

#ifndef NONE_CLASH
#define NONE_CLASH
#endif

#include <OPSS.H>
#include <CHA_EsList.H>
#include "OpsParserListenerImpl.H"
#include <corba.h>
#include "CosNaming_c.hh"
#include "CosNamingExt_c.hh"


class OpsParserOrbHandler {
public:

OpsParserOrbHandler(RWCString _sessionId, RWCString _parserName, RWCString _serverSuffix);
OpsParserOrbHandler();

~OpsParserOrbHandler();

static OpsParserOrbHandler* getInstance(RWCString _sessionId, RWCString _parserName, RWCString _serverSuffix);
static OpsParserOrbHandler* getInstance();
OpsParserListenerImpl*  getParserListenerRef();
OPS::ServerRouterListener_ptr getServerRouterRef(int serverRestart = 0);
OPS::ServerListener_var getServerRef();
CORBA::ORB_var getOrb();

private:
  static OpsParserOrbHandler* orbHdlRef;
  CORBA::ORB_var pOrb;
  OPS::ServerListener_var serverLRef_v;
  OPS::ServerRouterListener_ptr serverRLRef;
  OpsParserListenerImpl* parserLRef;
  OPS::ParserListener_var pReference;
  RWCString sSessionId;
  RWCString parserName;
  RWCString serverSuffix;
  RWCString serverName;
};

#endif //OPS_PARSER_ORB_HANDLER_H
