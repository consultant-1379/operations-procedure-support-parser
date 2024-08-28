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


#ifndef CHA_CONNECTION_H
#define CHA_CONNECTION_H


#include <CHA_Model.H>
#include <CHA_ModelClient.H>
#include <CHA_NLSCatalog.H>
#include <CHA_UserInfo.H>
#include <OPSLogger.H>
#include <WinFIOLClient.H>
//#include <CHA_Properties.H>
//#include <eac_cri_connection.H>

#define MAX_CONNECT_ATTEMPT 2
// WinFIOL server address for HA
std::string const WINFIOL_SERVER = "winfiol-axemed-service:8085";

// forward declarations
class CHA_CommandSender;
class CHA_IPCSupervisor;
class CHA_PromptString;


class CHA_Connection : public CHA_Model, public CHA_ModelClient
{

    friend class CHA_PromptString;

public:

    // return codes
    enum ReturnCode {OKAY,
		     ES_FAILED_DISCON,
		     ES_NOREACH,
		     ES_UNKNOWN,
		     ES_IS_EXCLUSIVE,
		     ES_NOAUTH,
		     ES_FAILED_CON,
                     ES_INVALID_NEID,
                     ES_INVALID_SESSIONID,
                     ES_INVALID_ENMUID,
                     ES_COULD_NOT_CONNECT_TO_ES,
                     ES_INCORRECT_SIDE,
                     ES_INCORRECT_CP,
                     ES_SIDE_NOT_ALLOWED,
                     ES_UNREASONABLE_VALUE};
    
    CHA_Connection(): pIpcSupervisor(NULL){}

    CHA_Connection(WinFIOLClient* winF, CHA_CommandSender* cmdS);
    
    CHA_Connection(CHA_IPCSupervisor* pSup,
		   CHA_CommandSender* cmdS,
		   const RWCString& appN);
    // Description:
    //     Constructor.
    // Parameters:
    //     pSup			IN: an IPC supervisor
    //     cmdS			IN: the parent CHA_CommandSender
    //     appN			IN: the name of the application

    virtual ~CHA_Connection();
    // Description:
    //     Destructor.

    WinFIOLClient*  getConnection() ;
    // Description:
    //     To get hold of the WinFIOLClient object.
    // Return values:
    //     A pointer to the WinFIOLClient object.

    int getConnectionStatus();
    // Description:
    //     Returns the value of
    //     EAC_CRI_Connection::Get_connection_status(). 
    // Return values:
    //     See the manual for EAC_CRI_Connection.

    int getConnectionMode();
    // Description:
    //     Returns the value of
    //     EAC_CRI_Connection::Get_connection_mode(). 
    // Return values:
    //     See the manual for EAC_CRI_Connection.

    int getAssocID();
    // Description:
    //     Returns the value of
    //     EAC_CRI_Connection::Get_current_assoc_id();
    // Return values:
    //     See the manual for EAC_CRI_Connection.

    ReturnCode connect(const RWCString& es ,/*EAC_CRI_Access_Mode accessMode = EAC_CRI_SHARED,*/ RWBoolean displayMessage = TRUE);
    // Description:
    //     Connect to an external system. Will communicate this event
    //     to the parent command sender object.
    // Parameters:
    //     es			IN: the name of the external system 
    //     displayMessage	IN: display a message to the user
    // Return values:
    //     OK			connection succeeded
    //     ES_FAILED_DISCON	disconnection failed (if already connected)
    //     ES_NOREACH		external system  not reachable
    //     ES_UNKNOWN		unknown external system
    //     ES_IS_EXCLUSIVE	external system is in exclusive use
    //     ES_NOAUTH		not authorized to connect to external system
    //     ES_FAILED_CON	other kind of failure

    ReturnCode reconnect(RWBoolean displayMessage = TRUE);
    // Description:
    //     To resume a connection to the last ES that was connected
    //     to. Will communicate this event to the command sender.
    // Parameters:
    //     displayMessage	IN: display a message to the user
    // Return values:
    //     OK		connection succeeded
    //     ES_FAILED_DISCON	disconnection failed (if already connected)
    //     ES_NOREACH		external system  not reachable
    //     ES_UNKNOWN		unknown external system
    //     ES_IS_EXCLUSIVE	external system is in exclusive use
    //     ES_NOAUTH		not authorized to connect to external system
    //     ES_FAILED_CON	other kind of failure

    ReturnCode disconnect(RWBoolean displayMessage = TRUE);
    // Description:
    //     Disconnect from current ES. This event will be communicated
    //     to the command sender. 
    // Parameters:
    //     displayMessage	IN: display a message to the user
    // Return values:
    //     OK		disconnection succeeded
    //     ES_FAILED_DISCON	disconnection failed (if already connected)

    RWBoolean useUpperCase() const;
    // Description:
    //     To find out id commands have to be in upper case for this
    //     ES. Presently the only systems known that requires commands
    //     in upper case are AXE and S12.
    // Return values:
    //     TRUE			use upper case for commands to be sent
    //     FALSE		uupercase is not known to be required

    RWCString getEsName() const;
    // Description:
    //     To get hold of the name of the connected ES.
    // Return values:
    //     A string containing the ES name.

    void setSmoUser(std::string smoUser);
    // Description
    //     Will set the SMO user that will send MML commands.
    // Parameter
    //     smoUser      IN: name of the SMO user.

    RWCString getEsType() const;
    // Description:
    //     To examine the ES type.
    // Return values:
    //     A string representing the ES type, e.g. "AXE" or "S12".
    
    RWCString getIoType(RWCString neName) const;
    // Description:
    //     To examine the IO type of a NE.
    // Parameter
    //     neName      IN: name of the NE.
    // Return values:
    //     A string representing the IO type, e.g. "APG", "IOG" or "".
    
    RWCString getProtocolType(RWCString neName) const;
    // Description:
    //     To examine the protocol type of a NE.
    // Parameter
    //     neName      IN: name of the NE.
    // Return values:
    //     A string representing the protocol type, e.g. "TELNET_APG40", "SSH_APG40",
    //     "MTP_IOG", "V24_IOG", "TELNET_APG30" or "".


   // Added due to improvement to avoid hanging problem
   int getEsExtInfo();
    // Description:
    //     This method provid the caller with the timer value conn_idel_to.
    //     The vale is fetched by using EAC_ESI_Ext_Characteristics::Get_timeout(EAC_ESI_IDLE).
    // Return values:
    //     timer value.



    virtual void updateFrom(CHA_Model* p, void* d);
    // Description:
    //     Used by the CHA_IPCSupervisor.
    //
    //     Not for use in the main program!

    virtual void detachFrom(CHA_Model* model);
    // Description:
    //     Used by the CHA_IPCSupervisor.
    //
    //     Not for use in the main program!
    
    ReturnCode useAuthorityOf(const RWCString& user);
    // Description:
    //     To set the authority profile used when sending commands
    //     over a connection. If connected to an ES a disconnection
    //     will be made and then a reconnection. This explains some of
    //     the possible return codes. When everything goes OK the
    //     application can continue as if the connection never was
    //     down for a brief moment.
    // Paramters:
    //     user		IN: the name of the user who's authority should be used
    // Return values:
    //     OK			the setting of authority succeeded
    //     ES_FAILED_DISCON	disconnection failed (if already connected)
    //     ES_NOREACH		external system  not reachable
    //     ES_UNKNOWN		unknown external system
    //     ES_IS_EXCLUSIVE	external system is in exclusive use
    //     ES_NOAUTH		not authorized to connect to external system
    //     ES_FAILED_CON	other kind of failure

    ReturnCode useDefaultAuthority();
    // Description:
    //     Resets the authority to the default one, usually the user's
    //     own. For return codes, see the useAuthorityOf() method.
    
    RWCString authorityUsed() const;
    // Description:
    //     Returns the user name of the authority profile that is 
    //     currently used.

    RWBoolean uppCaseForNEGet(const RWCString& esType);
    // Description:
    //	   Check if the type of the network element is defined to be "Uppercase -sensitive"
    //     or not. The value is found in the cha_dc_map file. If the file doesn't exist
    //     or the EA type is not specified in the cha_dc_map file,
    //     the default hard-coded way is used. I.e. the AXE and S12 NE will send all 
    //     commands in uppercase..
    //     With uppercase-sensitive means that the commands are sent in 
    //     uppercase!
    //
    // Return value:
    //     Returns TRUE if the commands should be sent in uppercase.
    //     Returns FALSE if the commands should be sent in the exact
    //     same way as they are typed.
    // 
    // Implemented due to TR: HA99448.
    // 

    bool isRespEnded();
    // Description:
    //     Returns whether the response is ended or not

    void setEnmId(std::string enmId);
    // Description:
    //     Set ENM User Name

private:

    int checkConnection();
    // Description:
    //	   Check the connection with EA and calls updates all model clients
    //     if any change has occured.
    // Return value:
    //     Returns the value of EAC_CRI_Connection::Get_connection_status(). 
    //     See the manual for EAC_CRI_Connection.

    ReturnCode doDisconnect(RWBoolean displayMessage, RWBoolean tellCmdSender);
    // Description:
    //     This method does the actual disconnection.
    // Parameters:
    //	   displayMessage	IN: display message to the user
    //     tellCmdSender	IN: tell the command sender about disconnection
    // Return values:
    //     OK		disconnection succeeded
    //     ES_FAILED_DISCON	disconnection failed (if already connected)

    ReturnCode doConnect(const RWCString& es /*/,EAC_CRI_Access_Mode accessMode = EAC_CRI_SHARED*/ );
    
    // Description:
    //     This method does the actual connecting when connect() or
    //     reconnect() is called.
    // Parameters:
    //     es			IN: the name of the ES.
    // Return values:
    //     OK			connection succeeded
    //     ES_FAILED_DISCON	disconnection failed (if already connected)
    //     ES_NOREACH		external system  not reachable
    //     ES_UNKNOWN		unknown external system
    //     ES_IS_EXCLUSIVE	external system is in exclusive use
    //     ES_NOAUTH		not authorized to connect to external system
    //     ES_FAILED_CON	other kind of failure
      
    WinFIOLClient* pImmResp;
    std:: string sessionId;
    
    
    RWCString esName;
    //std::string esName;   
    RWCString esType;
    //RWCString realUid;
    std::string realUid; 
    // Added due to improvement to avoid hanging problem
    int connIdelToTimerValue;

    RWBoolean upperCaseNeeded;
    RWBoolean connected;

    CHA_CommandSender* pCommandSender;
    CHA_IPCSupervisor* pIpcSupervisor;

    CHA_NLSCatalog nlsCat;
    CHA_UserInfo userInfo;

    std::string enmUserId;
    
   // EAC_CRI_Connection connection;
   // WinfiolClient connection;
};

#endif
