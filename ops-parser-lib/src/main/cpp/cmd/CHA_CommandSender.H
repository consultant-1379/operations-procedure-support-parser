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

#ifndef CHA_COMMANDSENDER_H
#define CHA_COMMANDSENDER_H


#include <CHA_Model.H>
#include <CHA_ModelClient.H>
#include <CHA_PromptString.H>
#include <CHA_CommandHistory.H>
#include <CHA_Connection.H>
#include <CHA_DeviceModeProps.H>
#include <CHA_ImmRespReceiver.H>
#include <CHA_DelRespHandler.H>
#include <CHA_DelSubscriber.H>
#include <CHA_RoutingHandler.H>
#include <OZT_ErrHandling.H>
#include <WinFIOLClient.H>
#define WFST_CONNECTED  4 //Node connected
/* #include <eac_cri_association.H>
#include <eac_cri_command.H>
#include <eac_cri_im_resp.H>
#include <eac_cri_delayed_resp.H> */


class CHA_CommandSender : public CHA_Model, public CHA_ModelClient
{

public:

    // send states
    enum State {NOTCON,
		IDLE,
		WAITING,
		CONFIRM,
		RECEIVING};

    // return codes
    enum ReturnCode {OKAY,
		     BUSY,
		     FAILED,
		     NOCONNECTION,
                     DISCON_FAILED};

    // command results
    enum CmdResult {EXECUTED,
                    NOT_ACCEPTED,
                    PARTLY_EXECUTED,
                    INCOMPLETE,
                    FUNCTION_BUSY,
                    NOT_AUTHORIZED,
                    UNKNOWN,
                    ORDERED};

    CHA_CommandSender(): immReceiver(NULL, this),
       pPrompt(NULL),
       pIpcSupervisor(NULL),
       wfClient(NULL){}

    CHA_CommandSender(CHA_IPCSupervisor* pSup,
		      const RWCString& applicationName,
		      CHA_RoutingHandler* pRtHandler = NULL);
    // Description:
    //     Constructor.
    // Parameters:
    //     pSup			IN: the supervisor that calls all its
    //                          clients when there is something in the
    //                          IPC que.
    //     applicationName	IN: the name of this application.
    //     pRtHandler		IN: the routing handler, if it exsts

    virtual ~CHA_CommandSender();
    // Description:
    //     Destructor.
    //     

    CHA_PromptString* getPromptObject();
    // Description:
    //     To get hold of the CHA_PromptString object.
    // Return values:
    //     A pointer to the prompt string object.

    CHA_DeviceModeProps* getDevModePropsObject();
    // Description:
    //     To get hold of the CHA_DeviceModeProps object.
    // Return values:
    //     A pointer to the props object.

    CHA_CommandHistory* getCommandHistoryObject();
    // Description:
    //     To get hold of the CHA_CommandHistory object.
    // Return values:
    //     A pointer to the history list.

    CHA_Connection* getConnectionObject();
    // Description:
    //     To get hold of the CHA_Connection object.
    // Return values:
    //     A ponter to the connection object.

    CHA_ImmRespReceiver* getImmReceiverObject();
    // Description:
    //     To get hold of the CHA_ImmRespReceiver object.
    // Return values:
    //     A ponter to the receiver.

    CHA_DelRespHandler* getDelReceiverObject();
    // Description:
    //     To get hold of the CHA_DelRespHandler object.
    // Return values:
    //     A ponter to the receiver.

    State getState() const;
    // Description:
    //     To examine the state of the command sender.
    // Return values:
    //     NOTCON	not connected to an ES
    //     IDLE		ready for commands
    //     WAITING	processing a command
    //     CONFIRM	expecting confirmation from
    //                  the main program
    //     RECEIVING	processing a command

    CmdResult getLastCmdResult() const;
    // Description:
    //	   This method returns the result of the last command sent to
    //     EA. When sending a command using the sendCommand() method
    //     it is not known upon return wether the command was accepted
    //     by the external system or not. However, when the
    //     CHA_CommandSender object becomes IDLE again the
    //     information is available and can be aquired using this
    //     method.
    // Return values:
    //     EXECUTED
    //         The command was executed without problems and without
    //         any delayed response pending.
    //
    //     UNKNOWN
    //         Initial return value before any command has been
    //         sent. Can also be set when something has gone wrong and
    //         no other result code fits.
    //
    //     ORDERED
    //         The command sent has been ordered to be executed, i.e. the
    //         command will be executed at a later stage. A delayed
    //         response usually follows after this immediate response type.
    //
    //     NOT_ACCEPTED
    //         The command was not accepted due to syntax error, that the
    //         command was unknown to the ES or the connection to the
    //         ES was lost.
    //
    //     NOT_AUTHORIZED
    //         The command was not accepted because the user was not
    //         authorized to send it.
    //
    //     PARTLY_EXECUTED
    //         The command was not fully correct but some parts have been
    //         executed.
    //
    //     INCOMPLETE
    //         The command has not been executed due to more parameters are 
    //         expected.
    //
    //     FUNCTION_BUSY
    //         This is received when the ES cannot process the command
    //         due to a busy situation.

    void setLogInfo(const RWCString& info);
    // Description:
    //     Sets a string to be logged in EA with every command
    //     sent. Once the string is set it will be used for every
    //     command sent from then on. To stop setting the log info the
    //     unsetLogInfo() method must be used.
    // Parameters:
    //     info		the string to associated in the log with
    //                  commands sent.

    void addLogInfo(const RWCString& info);
    // Description:
    //     Adds a string to be logged in EA with every command
    //     sent. If a string has been added before it just adds this string
    //     Otherwise the logstring is set to string.
    //     Once the string is set it will be used for every
    //     command sent from then on. To stop setting the log info the
    //     unsetLogInfo() method must be used.
    // Parameters:
    //     info		the string to associated in the log with
    //                  commands sent.

    void addLogInfoFirst(const RWCString& info);
    // Description:
    //	   Adds a string to be logged in EA with every command
    //     sent. If a string already has been added, the new string
    //     will be added before the existing one.
    //     Once the string is set it will be used for every
    //     command sent from then on. To stop setting the log info the
    //     unsetLogInfo() method must be used.
    // Parameters:
    //     info		the string to be associated in the log with
    //                  commands sent

    void unsetLogInfo();
    // Description:
    //     To stop setting the log info string associated with every
    //     commad sent. 

    RWCString getLogInfo() const;
    // Description:
    //     Returns the log info string associated with every command
    //     sent. If the log info is not set, an empty string is
    //     returned. 

    void setAutoConfirm(RWBoolean confirm);
    // Description:
    //    Sets the confirmatiopn mode to true or false 
    //    based on comand set @A+ or @A- respectively.
 
    ReturnCode sendCommand(RWCString cmd, const RWCString& pmt, 
			   const RWCString& logInfo);
    // Description:
    //     Same as the usual sendCommand() method (see below), but
    //     with an extra parameter to temporarily set the log info
    //     string durin sending of one command.
    //
    //     Can be used to temporarily extend the default log info
    //     string like this: 
    //
    //     myCmdSender.sendCommand("CACLP;",
    //                             myCmdSender.getPromptObject->getPrompt(),
    //                             myCmdSender.getLogInfo() + " YOW!!");

    virtual ReturnCode sendCommand(RWCString cmd, const RWCString& pmt);
    // Description:
    //     To send a comand to the connected ES. It will be echoed as
    //     an immediate response.
    // Parameters:
    //     cmd				IN: the command to send.
    //     pmt				IN: a prompt to echo with the
    //                                  command 
    // Return values:
    //     OK			all went as expected
    //     BUSY			failed, already processing a command
    //     FAILED		failed to send command
    //     NOCONNECTION		failed, not connected to an ES

    ReturnCode confirmCommand(RWBoolean confirmed);
    // Description:
    //     To confirm a command when the state is CONFIRM. 
    // Parameters:
    //     confirmed			IN: true if the command is confirmed
    // Return values:
    //     OK			all went as expected
    //     FAILED		failed to confirm command, skipped

    virtual void updateFrom(CHA_Model* p, void* d);
    // Description:
    //     Called By the CHA_IPCSupervisor and CHA_DeviceModeProps.
    //
    //     Not for use in the main program!

    virtual void detachFrom(CHA_Model* model);
    // Description:
    //     Called By the CHA_IPCSupervisor object and the
    //     CHA_DeviceModeProps object.
    //
    //     Not for use in the main program!

    void immResponseReceived(const RWCString& newPrompt);
    // Description:
    //     Called by the CHA_ImmRespReceiver object when an immediate 
    //     response is complete.
    //
    //     Not for use in the main program!
    // Parameters:
    //     newPrompt			IN: prompt provided by EA.

    void expectingDelayed();
    // Description:
    //     Called by the CHA_ImmRespReceiver and by the CHA_CommandSender
    //     itself when the status ORDERED has been received.
    //
    //     This method will start a subscription for a delayed response,
    //     if needed.

    //void newConnection(RWBoolean displayMessage = TRUE);
    void newConnection(WinFIOLClient* wf);
    // Description:
    //     Called by the CHA_Connection object when a new connwction
    //     is established.
    //
    //     Not for use in the main program!
    //
    // Parameters:
    //     displayMessage		IN: decides if a message is forwarded

    void esDisConnection(int connStatus, RWBoolean displayMessage = TRUE);
    // Description:
    //     Called by the CHA_Connection object when the connection is
    //     lost. 
    //
    //     Not for use in the main program! 
    //
    // Parameters:
    //     displayMessage		IN: decides if a message is forwarded

    virtual void usrDisConnection(RWBoolean displayMessage = TRUE);
    // Description:
    //     Called by the CHA_Connection object when the connection is
    //     closed by the user. 
    //
    //     Not for use in the main program!
    //
    // Parameters:
    //     displayMessage		IN: decides if a message is forwarded

       
    void setApMode(RWBoolean isAPModeIn);
    // Description:
    //     This method is used by OZT_CmdSender due to HD53923 to specify 
    //     whether or not it is sending APG commands, i.e. turn case 
    //     convesion on or of.
    // Parameters:
    //     isAPModeIn   TRUE when in APG mode.
    void checkIPC();

    OZT_Result sendLogoff();
    //Used only in @waitfor

    //void sendControlCharacter(int ctrlChr);
    OZT_Result sendControlCharacter(int ctrlChr);
    // Description:
    //     This is CHA side implementation for sending Control Characters.
    //     This method calls WinFIOLClient method for sending Control Characters to ES.
    // Parameters:
    //     ctrlChr      1 for RELEASE; 2 for CONNECT Control Character.

    void logOffHandler(RWBoolean bTermination);
    // Description:
    //     This is CHA side implementation for logOff command.

private:
    //TORF-241666
   // void checkIPC();
    // Description:
    //     Called by updateFrom() to check for incomming first buffer.

    void changeState(State newState);
    // Description:
    //     To change state and update model clients.
    // Parameters:
    //     newState			IN: the new state.

    WinFIOLClient* wfClient;
    RWBoolean changeAssocId;
    RWBoolean isSubscribing;
    RWBoolean isAPMode;

    CHA_DeviceModeProps devModeProps;

    State sendState;

    CmdResult lastCmdResult;

    CHA_IPCSupervisor* pIpcSupervisor;
  
    CHA_CommandHistory commandHistory;
    CHA_ImmRespReceiver immReceiver;
    CHA_DelRespHandler delHandler;
    CHA_DelSubscriber delSubscriber;
    CHA_Connection connSupervisor;

    CHA_PromptString* pPrompt; // need to construct this after the others
    
    CHA_NLSCatalog nlsCat;

    RWCString logInfoString;
    RWBoolean logInfoChanged;

    /*/EAC_CRI_Association* pAssociation;
    EAC_CRI_Command* pCommand;
    EAC_CRI_Im_Resp* pImmResp;
    EAC_CRI_Association* pReadBreakAssociation;
    EAC_CRI_Delayed_Resp* pReadBreakResp;*/
};

#endif
