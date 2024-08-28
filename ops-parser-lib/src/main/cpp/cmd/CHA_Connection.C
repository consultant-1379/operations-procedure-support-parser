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
#include <trace.H>
#include <CHA_LibNLS.H>
#include <CHA_CommandSender.H>
#include <CHA_IPCSupervisor.H>
#include <CHA_Connection.H>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

static std::string trace ="CHA_Connection";
//**********************************************************************

CHA_Connection::CHA_Connection(WinFIOLClient *winF, CHA_CommandSender *cmdS)
: esName(""),
  esType(""),
  realUid(""),
  upperCaseNeeded(FALSE),
  connected(FALSE),
  pIpcSupervisor(NULL),
  enmUserId(""),
  pImmResp(winF),
  pCommandSender(cmdS)
{
}

CHA_Connection::CHA_Connection(CHA_IPCSupervisor* pSup,
			       CHA_CommandSender* cmdS,
			       const RWCString& appN)
: esName(""),
  esType(""),
  realUid(""),
  upperCaseNeeded(FALSE),
  connected(FALSE),
  pCommandSender(cmdS),
  pIpcSupervisor(pSup),
  nlsCat(CHA_LibNLSCatalog),
  userInfo(),
  enmUserId("")
  /*connection(appN)*/
{
    TRACE_IN(trace, CHA_Connection, "");
    pImmResp = new WinFIOLClient(grpc::CreateChannel(WINFIOL_SERVER, grpc::InsecureChannelCredentials()), appN.std());
        
    if(pIpcSupervisor != NULL)
	pIpcSupervisor->addDependent(this);
}

//**********************************************************************

bool CHA_Connection::isRespEnded() {
    if(pImmResp!=NULL)
    return pImmResp->isResponseEnded();
}
//*********************************************************************


CHA_Connection::~CHA_Connection()
{
    if(connected)
    	pImmResp->disconnect();

    if(pIpcSupervisor != NULL)
	pIpcSupervisor->removeDependent(this);

    if (pImmResp != NULL) {
        delete pImmResp;
        pImmResp = NULL;
    }
}


//*********************************************************************
WinFIOLClient* CHA_Connection::getConnection()
{
    return pImmResp;
}

//*********************************************************************


int CHA_Connection::getConnectionStatus()
{
    TRACE_IN(trace, getConnectionStatus, "");
    return checkConnection();
}


//*********************************************************************


void CHA_Connection::setEnmId(std::string enmId) {
    enmUserId = enmId;
}


//*********************************************************************


int CHA_Connection::getConnectionMode()
{
    TRACE_IN(trace, getConnectionMode, "");

    (void) checkConnection();
    //return connection.Get_connection_mode();
}

//*********************************************************************


CHA_Connection::ReturnCode CHA_Connection::connect(const RWCString& es ,
						/*EAC_CRI_Access_Mode accessMode,*/
						RWBoolean displayMessage)
{
    TRACE_IN(trace, connect, es);

    // save old values in case connect to new ES fails
    RWBoolean wasConnected = connected;
    RWCString oldEsName = esName;
    ReturnCode result = doConnect(es);
     
    switch(result)
    {
    case OKAY:
        pCommandSender->newConnection(pImmResp);
	changed();
	TRACE_RETURN(trace, connect, "OKAY");
	return OKAY;

    default:
	if(wasConnected)
	{
	    esName = oldEsName;		// the ES we actually disconnected from
	    pCommandSender->usrDisConnection(displayMessage == TRUE);
	    changed();			// tell the world about the
					// lost connection
	}
	TRACE_RETURN(trace, connect, "result of doConnect()");
	return result;
    }
}


//*********************************************************************


CHA_Connection::ReturnCode CHA_Connection::reconnect(RWBoolean displayMessage)
{
    TRACE_IN(trace, reconnect, displayMessage);

  //if(pImmResp->getConnectionStatus() > -1)
  if (pImmResp->getConnectionStatus() == 4)
    {
	connected = TRUE;
	TRACE_RETURN(trace, reconnect, "OKAY");
	return OKAY;
    }

    RWBoolean wasConnected = connected;	// remember previous state
    ReturnCode result = doConnect(esName);
    switch(result)
    {
    case OKAY:
	changed();
	TRACE_RETURN(trace, reconnect, "OKAY");
	return OKAY;

    default:
	if(wasConnected)
	    changed();			// tell the world about
					// the lost connection
	TRACE_RETURN(trace, reconnect, "result of doConnect()");
	return result;
    }
}


//*********************************************************************


CHA_Connection::ReturnCode CHA_Connection::disconnect(RWBoolean displayMessage)
{
    TRACE_IN(trace, disconnect, displayMessage);

    return doDisconnect(displayMessage == TRUE, // TRUE == message to user
			TRUE);		  	// TRUE == tell command sender
}


//*********************************************************************


CHA_Connection::ReturnCode CHA_Connection::doDisconnect(RWBoolean displayMessage,
							RWBoolean tellCmdSender)
{
    TRACE_IN(trace, doDisconnect, displayMessage << ", " << tellCmdSender);
   
    // return quickly if we are not connected
    if(!connected)
    {
	TRACE_RETURN(trace,doDisconnect,"OKAY (not connected)");
	return OKAY;
    }

    // try to disconnect twice, sometimes the second time
    // is more successful
    for(int attempts = 0; attempts < 2; attempts++)
    {
           if (pImmResp->disconnect() == 0)
                connected = FALSE;
        	
        if(!connected && tellCmdSender)	{
            pCommandSender->usrDisConnection(displayMessage == TRUE);
    	    changed();
    	    TRACE_RETURN(trace, doDisconnect, "OKAY");
            return OKAY;
    	}
    }

    // if we come here, disconnection failed
    errorReporter.message(nlsCat.getMessage(NLS_ES_FAILED_DISCON)
			  + esName);
    TRACE_RETURN(trace, doDisconnect, "ES_FAILED_DISCON");
    return ES_FAILED_DISCON;
}


//*********************************************************************


RWBoolean CHA_Connection::useUpperCase() const
{
    return upperCaseNeeded;
}


//*********************************************************************


RWCString CHA_Connection::getEsName() const
{
    return esName;
}

//*********************************************************************


void CHA_Connection::setSmoUser(std::string smoUser)
{
    realUid = smoUser;
}


//*********************************************************************


RWCString CHA_Connection::getEsType() const
{
    return esType;
}


//*********************************************************************


RWCString CHA_Connection::getIoType(RWCString neName) const
{
	//TORF-241666
    TRACE_IN(trace, getIoType, "NE name: " << neName);

    //EAC_ESI_Info* pEsInfo = new	EAC_ESI_Info;

    RWCString result = "APG";

  /*  char estype[EAC_ES_TYPE_LEN+1];
     strcpy(estype,"AXE");

     const char **pEsChars = pEsInfo->Get_first_ES_name_and_prot(estype);

    if (pEsChars != NULL)
    	{
		while( (pEsChars != NULL) && (pEsChars[0] != neName) )
		{
			pEsChars = pEsInfo->Get_next_ES_name_and_prot();
		}
		if (pEsChars !=	NULL)
		{
			//TRACE_FLOW(trace, getIoType, "NE found:	" << pEsChars[0]);

			if (strstr(pEsChars[1],	"MTP") != NULL)
			{
				result = "IOG";
			}
			else if	(strstr(pEsChars[1], "V24") != NULL)
			{
				result = "IOG";
			}
			else if	(strstr(pEsChars[1], "APG") != NULL)
			{
				result = "APG";
			}
			else
			{
				result = "";
			}
		}
		else
		{
			result = "";
		}
    }
    else
    {
		//TRACE_FLOW(trace, getIoType, "NULL string: Get_error:" << pEsInfo->Get_error() );
		result = "";
    }

    delete pEsInfo;
*/
    TRACE_OUT(trace, getIoType,	"");

    return result;
}


//*********************************************************************


RWCString CHA_Connection::getProtocolType(RWCString neName) const
{
   
	//TORF-241666
    /*TRACE_IN(trace, getProtocolType, "NE name: " << neName);

      EAC_ESI_Info* pEsInfo = new	EAC_ESI_Info;

      RWCString result = "";

      char estype[EAC_ES_TYPE_LEN+1];
      strcpy(estype,"AXE");

      const char **pEsChars = pEsInfo->Get_first_ES_name_and_prot(estype);

      if (pEsChars != NULL)
    	{
		while( (pEsChars != NULL) && (pEsChars[0] != neName) )
		{
			pEsChars = pEsInfo->Get_next_ES_name_and_prot();
		}
		if (pEsChars !=	NULL)
		{
			//TRACE_FLOW(trace, getProtocolType, "NE found: "	<< pEsChars[0]);

			if (strstr(pEsChars[1],	"MTP") != NULL)
			{
				result = "MTP_IOG";
			}
			else if	(strstr(pEsChars[1], "V24") != NULL)
			{
				result = "V24_IOG";
			}
			else
			{
				result = pEsChars[1];
			}
		}
		else
		{
			result = "";
		}
    }
    else
    {
		//TRACE_FLOW(trace, getProtocolType, "NULL string: Get_error:" <<	pEsInfo->Get_error() );
		result = "";
    }

    delete pEsInfo;

    TRACE_OUT(trace, getProtocolType, "");

    return result;*/
}


//*********************************************************************


void CHA_Connection::updateFrom(CHA_Model* p, void* d)
{
    (void) checkConnection();
}


//*********************************************************************


void CHA_Connection::detachFrom(CHA_Model* model)
{
    if(model == (CHA_Model*)pIpcSupervisor)
	pIpcSupervisor = NULL;
}


//*********************************************************************


int CHA_Connection::checkConnection()
{
    // return quickly if we don't think we are connected anyway
    if(!connected)
     return -1 ; //EAC_CRI_CS_DISCONNECTED; //TORF-241666

    // get the actual connection status
	
    int connStatus = pImmResp->getConnectionStatus();
     
    // check if we have become unexpectedly disconnected
    //if(connStatus == -1)
    if (connStatus != 4)
    {
	connected = FALSE;
	TRACE_FLOW(trace, checkConnection, "connected= " << connected);

	pCommandSender->esDisConnection(connStatus);
	changed();
    }
    return connStatus; 
}

//*********************************************************************
CHA_Connection::ReturnCode CHA_Connection::doConnect(const RWCString& es /*, EAC_CRI_Access_Mode accessMode*/)
{
    TRACE_IN(trace, doConnect, es);

    // disconnect if needed
    switch(doDisconnect(FALSE, FALSE))	// no message, don't tell cmdSender
    {
	case OKAY:
	    // continue below
	    break;
	case ES_FAILED_DISCON:
		std::cerr << "ES_FAILED_DISCON" << std::endl;
		break;
	case ES_NOREACH:
		std::cerr << "ES_NOREACH" << std::endl;
		break;
	case ES_UNKNOWN:
		std::cerr << "ES_UNKNOWN" << std::endl;
		break;
	case ES_IS_EXCLUSIVE:
		std::cerr << "ES_IS_EXCLUSIVE" << std::endl;
		break;
	case ES_NOAUTH:
		std::cerr << "ES_NOAUTH" << std::endl;
		break;
	case ES_FAILED_CON:
		std::cerr << "ES_FAILED_CON" << std::endl;
		break;
	default:
		std::cerr << "default" << std::endl;
		break;
	    // return quickly on failure
	    TRACE_RETURN(trace, doConnect, "ES_FAILED_DISCON");
	    return ES_FAILED_DISCON;
    }

    esName = es;
    TRACE_FLOW(trace, doConnect, "REAL_UID    :" << realUid);
    TRACE_FLOW(trace, doConnect, "enmUserId is    :" <<  enmUserId);
    int connectResult;
    std::string esNode( esName );

    if (realUid != "")
       pImmResp->setEnmUser(realUid);
    else
       pImmResp->setEnmUser(enmUserId);

    for (int i = 0; i < MAX_CONNECT_ATTEMPT; i++) {

        pImmResp->initStream();
        sessionId = pImmResp -> createSessionAsync();
        if (sessionId != "-1") {
            break;
        }
        TRACE_FLOW(trace, doConnect, "Connect retry attempt number: "<<i);
    }

    if (sessionId == "-1") {
        errorReporter.message(nlsCat.getMessage(NLS_ES_FAILED_CON)
                              + esName);
        TRACE_RETURN(trace, doConnect, "ES_FAILED_CON");
        return ES_FAILED_CON;       
    }

    connectResult = pImmResp->connect(esNode);
     
    switch(connectResult)
    {
    case 0: 
      connected = TRUE;
      break;
    case 1: 
      errorReporter.message("The Operation was cancelled");
      break;
    case 2:
	TRACE_RETURN(trace, doConnect, "ES_INVALID_NEID");
	return ES_INVALID_NEID;
    case 3:
        TRACE_RETURN(trace, doConnect, "ES_INVALID_SESSIONID");
        return ES_INVALID_SESSIONID;
    case 4:
        return ES_INVALID_ENMUID;
    case 5:
        return ES_COULD_NOT_CONNECT_TO_ES;
    case 6:
        return ES_INCORRECT_SIDE;
    case 7:
        return ES_INCORRECT_CP;
    case 8:
        return ES_SIDE_NOT_ALLOWED;
    case 9:
        return ES_UNREASONABLE_VALUE;
    default:
	errorReporter.message(nlsCat.getMessage(NLS_ES_FAILED_CON)
			      + esName);
	TRACE_RETURN(trace, doConnect, "ES_FAILED_CON");
	return ES_FAILED_CON;
    }
    esType = "AXE";
    TRACE_RETURN(trace, doConnect , connected);
    TRACE_INFO(trace, doConnect, "Node is Connected");
    TRACE_RETURN(trace, doConnect, "OKAY");
    return OKAY;
}


//********************************************************************
CHA_Connection::ReturnCode CHA_Connection::useAuthorityOf(const RWCString& user)
{
    TRACE_IN(trace, useAuthorityOf, user);
    if(!connected)
    {
	// this authority will be used next time a connection is made
	//connection.Set_cmd_auth_user_id(user);
	TRACE_RETURN(trace, useAuthorityOf, "OKAY, not connected");
	return OKAY;
    }
    else
    {
	TRACE_FLOW(trace, useAuthorityOf, "connected");

	// Set the new authority to use
	//connection.Set_cmd_auth_user_id(user);

	// and connect to the same ES again. A disconnection will be
	// made if needed.
	ReturnCode result = doConnect(esName);

	// tell the world if the connection was lost
	if(!connected)
	    changed();

	// return the result of the new conenction attempt
	TRACE_RETURN(trace, useAuthorityOf, "result of doConnect()");
	return result;
    }
}


//**********************************************************************


CHA_Connection::ReturnCode CHA_Connection::useDefaultAuthority()
{
    TRACE_IN(trace, useDefaultAuthority, "");
    return useAuthorityOf(userInfo.loginName());
}


//**********************************************************************


RWCString CHA_Connection::authorityUsed() const
{
   /* const char* username = connection.Get_cmd_auth_user_id();
    if(username != NULL)
    {
	TRACE_RETURN(trace, authorityUsed, username << " (EA)");
	return RWCString(username);
    }
    else
    {
	//TRACE_RETURN(trace, authorityUsed, userInfo.loginName() << " (Def)");
	return userInfo.loginName();
    }*/
}


//**********************************************************************

// Added due to improvement to avoid hanging problem
int CHA_Connection::getEsExtInfo()
{
  TRACE_IN(trace, getEsExtInfo, "");
  TRACE_RETURN(trace, getEsExtInfo, connIdelToTimerValue);
  return connIdelToTimerValue;
}
