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

#ifndef OZT_CMD_SENDER_H
#define OZT_CMD_SENDER_H

#include <CHA_ModelClient.H>
#include <CHA_IPCSupervisor.H>
#include <CHA_CommandSender.H>
#include <CHA_SpontSubscriber.H>
#include <CHA_SpontRepReceiver.H>
#include <OZT_EventHandler.H>
#include <OZT_Value.H>
#include <OZT_ErrHandling.H>
#include <OZT_RspReceiver.H>
#include <OZT_CmdRspBuf.H>
#include <rw/tvordvec.h>
#include <rw/tvslist.h>
#include <rw/defs.h>
#include <rw/cstring.h>
class OZT_CmdSender: public CHA_ModelClient {
public:
    enum State {IDLE,
		CONNECTION_LOST,
                CONFIRM_PENDING,
                LOGGING_ON,
                WAIT_IMM_RSP,
                WAIT_DEL_RSP,
                FUNBUSY_WAIT,
                WAIT_IMM_RSP_CONFIRMED,
                FUNBUSY_WAIT_CONFIRMED};


    OZT_CmdSender(OZT_CmdRspBuf &theCmdRspBuf);
    OZT_CmdSender(CHA_CommandSender *cms,OZT_CmdRspBuf &theCmdRspBuf,OZT_EventHandler *ozt_evt);
    // Description
    //     Constructor.
    // Parameter
    //     theCmdRspBuf    IN: Reference to a command response buffer.
    //                         This class needs to trigger the buffer
    //                         for changing the "mark" when a new command
    //                         is sent.

    ~OZT_CmdSender();
    // Description
    //     Destructor.

    RWBoolean constructOK() const;
    // Description
    //     Tells if the construction was successful. Possible problems
    //     include IPC init failure or memory allocation failure.
    // Return value
    //     TRUE if successful otherwise FALSE is returned.

    State getState() const;
    // Description
    //     Get the current state of this object.
    // Return value
    //     The state.

    long getPid() const;
    // Description
    //     Get OPS parser process id.
    // Return value
    //     The PID.

    OZT_Result sendCmd(const RWCString &currFileName,
                       const RWCString &cmdText,
                       RWBoolean markBuf);
    // Description
    //     Initiate a command sending operation.
    // Parameter
    //     currFileName    IN: the full path name of the command file that
    //                         contains cmdText.
    //                         The file name is needed for selecting the
    //                         authority profile for command checking.
    //     cmdText         IN: the command string e.g. "CACLP;"
    //     markBuf         IN: If true, mark the buffer before sending the
    //                         command. For @SEND, this parameter should be
    //                         false.
    //

    OZT_Result maidenConfirm(const RWCString &theConfirmStr);
    // Description
    //     To confirm the pending command.
    // Parameter
    //     theConfirmStr   IN: the character string used to confirm a command
    //                         For AXE, it is ";". For others, nobody know.

    CHA_CommandSender& getCHACmdSender();
    // Description
    //     Get hold of the CHA_CommandSender object that is maintained
    //     inside OZT_CmdSender.
    // Return value
    //     A reference to the CHA_CommandSender object.

    CHA_SpontSubscriber& getSpontSubscriber();
    // Description
    //     Get hold of the CHA_SpontSubscriber object that is maintained
    //     inside OZT_CmdSender.
    // Return value
    //     A reference to the CHA_SpontSubscriber object.

    CHA_Connection& getConnectionObject();
    // Description
    //     Get hold of the CHA_Connection object that is maintained
    //     inside OZT_CmdSender.
    // Return value
    //     A reference to the CHA_Connection object.

    OZT_CmdRspBuf& getCmdRspBuf();
    // Description
    //     Get hold of the command response buffer that was passed
    //     to the constructor.
    // Return value
    //     A reference to the OZT_CmdRspBuf object.

    RWCString getExchangeHeader();
    // Description
    //     get the exchange header for the NE.
    // Return value
    //     The exchange header.

    RWCString  getIoType(const RWCString &neName);
    // Description
    //     get the IO type for the NE.
    // Return value
    //     The IO type.

    RWCString  getProtocolType(const RWCString &neName);
    // Description
    //     get the protocol type for the NE.
    // Return value
    //     The protocol type.

  CHA_RoutingHandler* getRoutingHandler() {
    return pRoutingHandler;
  }

  OZT_RspReceiver& getRspReceiver();
  // Description
  //     Get hold of the response receiver object that is maintained
  //     inside OZT_CmdSender.
  // Return value
  //     A reference to the OZT_RspReceiver object.

    void       useStrictDeviceMode();
    // Description
    //     Use "device mode" for future command sending.  The default is
    //     not to use it.

    void       useNonStrictDeviceMode();
    // Description
    //     Do not use strict "device mode" for future command sending.
    //     This is the default.

    OZT_Result connect(const RWCString &neName);
    // Description
    //     Establish a connection with the specified network element.
    // Parameter
    //     neName      IN: name of the network element to be connected.
    // Return value
    //     A result object telling if the connection was successful.

    void setSmoUser(const char* smoUser);
    // Description
    //     Will set the SMO user that will send MML commands.
    // Parameter
    //     smoUser      IN: name of the SMO user.

    OZT_Result disconnect();
    // Description
    //     Disconnects from the currently connected network element
    // Return value
    //     A result object telling if the disconnection was successful.

    RWCString  getEsName() const;
    // Description
    //     Get hold of the name of the currently connected network element.
    // Return value
    //     The name of the network element.

    RWCString  getEsType() const;
    // Description
    //     Get hold of the type of the currently connected network element.
    // Return value
    //     The type of the network element.

    void       reportOn();
    // Description
    //     Turns the @REPORT mode on for S12 communication. When on, the
    //     command sending operation will complete even if only a
    //     REPORT FOLLOWS is seen.

    void       reportOff();
    // Description
    //     Turns the @REPORT mode off for S12 communication. When off, the
    //     command sending operation wait for the LAST REPORT before finishing.

    void       orderOn();
    // Description
    //     Turns the @ORDERED mode on for AXE communication. When on,
    //     the command sending operation will wait for the complete
    //     delayed response before finishing.

    void       orderOff();
    // Description
    //     Turns the @ORDERED mode off for AXE communication. When off,
    //     the command sending operation does not wait for delayed responses.

    void       setOKReply(const RWCString& str);
    // Description
    //     Set the "OK" string for the @SETREPLY command. If a response
    //     received contains the string, the sending operation is considered
    //     to be successful even if it actually failed.
    // Parameter
    //     str     IN: the OK string

    void       setFailReply(const RWCString& str);
    // Description
    //     Set the "FAIL" string for the @SETREPLY command. If a response
    //     received contains the string, the sending operation is considered
    //     to be unsuccessful even if it was actually fine.
    // Parameter
    //     str     IN: the FAIL string

    void       setAutoConfirm(const RWBoolean mode);
    // Description
    //     Turns auto confirm mode on or off. When off, a separate call
    //     to OZT_CmdSender::sendCmd() with a ";" is needed to confirm
    //     the previous command. The default mode is on.
    // Parameter
    //     mode    IN: True if autoconfirm mode is needed.

    OZT_Result setFunBusyParam(const OZT_Value& attempts,
                               const OZT_Value& interval);
    // Description
    //     Set the number of attempts and interval between attempts when
    //     FUNCTION BUSY is encountered.
    // Parameter
    //     attempts    IN: number of attempts (including the initial one)
    //     interval    IN: interval between attempts in seconds

    void       interrupt();
    // Description
    //     Interrupt the command sending operation.

    OZT_Result setScanStr(const RWCString& inStr);
    // Description
    //     Used for setting the parameters in the FIOL @/w1,...,wn/ command.
    //     The strings are compared with the response received due to the
    //     next command to be sent. Note that these scan strings are
    //     cleared every time a command sending operation finishes.
    // Parameter
    //     inStr     IN:the strings specifed in the FIOL command in the form
    //                  "w1,...,wn/".

    void       setR();
    // Description
    //     Used for the @R+ command.

    void       clearR();
    // Description
    //     Used for the @R- command.

    OZT_Result setZ(const RWCString& inFileName, const RWCString& curFileName);
    // Description
    //     Used for the @Z command.

    void       clearZ();
    // Description
    //     Used for the @Z- command.

    void       setIdle();

#if TPF >= 400
    virtual void updateFrom(CHA_Model* pModel, void*);
#else
    virtual void updateFrom(RWModel* pModel, void*);
#endif
    // Description
    //     To be called by the models of OZT_CmdSender, not for public
    //     uses.

    void       detachFrom(CHA_Model* pModel);
    // Description
    //     To be called by the models of OZT_CmdSender, not for public
    //     uses.

    RWCString  printState(const State theState);
    // Description
    //     For diagnostics purpose. This function convert a enum state as
    //     a string.
  void totalInterrupt();   // Added due to improvement to avoid hanging problem
    // Description
    //     Interrupt all command sending operation.Used only when clien has quit

  void setSessionId(RWCString sessionId);
    // Description
    //     Set the session id, received from ParserImp.
    //     sessionId      IN: Id of the ops session, used for printout in opsserver.log only.


  void setOnDisconnectLabel( RWCString label ){

    onDisconnectLabel = label;
    isOnDisconnectSetFlag = TRUE;
  }

  void resetOnDisconnectLabel(){

    onDisconnectLabel = "";
    isOnDisconnectSetFlag = FALSE;
  }

  RWBoolean isOnDisconnectSet() {
    return isOnDisconnectSetFlag;
  }

  RWCString getOnDisconnectLabel() {
    return onDisconnectLabel;
  }

  void  cancelResponses();

  void callConnect();
  // Description
    //     This function is called to send CONNECT Control Character


  void callRelease();
  // Description
    //     This function is called to send RELEASE Control Character

  OZT_Result sendCtrlChar(int ctrlChar, RWBoolean markBuf);
  // Description
    //     This is the OZT side implementation for sending Control Characters

  OZT_Result sendLogoff(RWBoolean markBuf);
  //Used in @waitfor just for checking if printout has arrived
  
  void logOff(RWBoolean bTermination);
  // Description
  // This is the OZT side implementation for @LOGOF command

#ifdef OZT_PROTOTYPE
    RWBoolean (*theDCConfirmFunc)(RWCString);
    void setDCConfirmFunc(RWBoolean (*f)(RWCString)) {theDCConfirmFunc = f;}
#endif

    static long defaultFBAttempts;   // default number of function busy attempts
    static long defaultFBInterval;   // default retry interval for fun busy

private:

    static int tickCallBack(void *instance);
    // Description
    //     This function is called periodically in order to do a polling
    //     to the IPC queue. The constructor installs this callback via
    //     OZT_EventHandler.
    // Parameter
    //     instance    IN: pointer to the OZT_CmdSender instance

    static int timeOutCallBack(void *instance);
    // Description
    //     This function is called when a function busy retry is time-out.
    // Parameter
    //     instance    IN: pointer to the OZT_CmdSender instance

    void       checkRspArrival();
    // Description
    //     Non-static member function called by tickCallBack().

    void       timeOut();
    // Description
    //     Non-static member function called by timeOutCallBack().

  void sleepAWhile();     // Added due to improvement to avoid hanging problem
    // Description
    // Non-static member function called by  tickCallBack().

  void       interruptAtDr();   // Added due to improvement to avoid hanging problem
    // Description
    //     Interrupt the command sending operation at waiting for Delay Response du to timeout.
    //     The timeout value is based on connIdleToTimerValue.

  void setConnectionMode(const RWCString& neName);
    // Description
    // Set the apmode state.


#if TPF >= 400
    // TPF4 IPC stuff
    // void (*inputProc)(void);
    static OZT_CmdSender* thisPointer;
    static void setInputHandler(int fd, RWBoolean flag);
#endif

    //
    OZT_Result actualSend(const RWCString &cmdText);
    RWCString  confirmStr() const;
    void       confirmCmd();
    void       selectAuthProf(const RWCString &currFileName);
    const char* 		chaCommandSenderStateToString(CHA_CommandSender::State state);
    const char* 		chaCommandSenderCmdResultToString(CHA_CommandSender::CmdResult cmdResult);
    const char* 		stateToString(State state);
    RWBoolean isClusterLockResponse();
    RWBoolean isCommandCslExemption();
    void      appendToBuffer(const RWCString& text);
    void 	   appendCslFuncBusyToBuffer();
    void       updateFromCmdSender();
    void       updateFromDelReceiver();
    void       changeState(const State newState);
    void       confirmReqEvent();
    void       orderedEvent();
    void       funBusyEvent();
    void       loseConnectionEvent();
    void       checkReply(const RWCString &cmdText, OZT_Result &result);

    //
    //  Member functions that deal with function busy
    //
    void       resetFunBusyCounter();
    void       decFunBusyCounter();
    RWBoolean  moreFunBusyRetry() const;


    RWBoolean  mScan(RWCString &failStr);
    // Description
    //     Used for scanning the command response buffer for the
    //     strings specified previously by OZT_CmdSender::setScanStr().
    // Parameter
    //     failStr   OUT:the string that fail to be found
    // Return value
    //     TRUE  if all strings are found in the response buffer.
    //
    //  Member function for the ZFlag
    //

    void       clearScanStr();
    // Description
    //     Used for clearing the strings specified previously by
    //     OZT_CmdSender::setScanStr().

    RWBoolean  getZ();
    // Description
    //     Tells if the @Z command is in effect.
    // Return value
    //     TRUE if and only if the @Z command is in effect.

    void       storeZError(const RWCString &cmdText, const OZT_Result &result);
    // Description
    //     To be called if @Z is in effect. When a command sending
    //     fails, it logs the command that failed together with a
    //     reason in the file specified previously by the @Z command.
    // Parameter
    //     cmdText  IN: the command string that failed
    //     result   IN: the result code which tells what has gone wrong

    RWCString  getCmdStr();
    // Description
    //     Get hold of the last command string that tried to send.
    // Return value
    //     The command string.

    // The following two functions are for picking the right filename for @Z.
    OZT_Result updateFileName(const RWCString &inFileName);
    void       getNextFileName(RWCString &inFileName);

    //
    void flushStoredResponses();
    // Description
    //     Flush the stored spontaneous responses and if ordered is OFF the
    //     stored delayed responses are also flushed.

    RWBoolean             useDeviceMode;
    OZT_CmdRspBuf         &cmdRspBuf;
    OZT_RspReceiver       *pRspReceiver;
    CHA_PromptString      *pPromptString;
    CHA_Connection        *pConnection;
    CHA_IPCSupervisor     *pIOSuper;
    CHA_CommandSender     *pCmdSender;
    CHA_SpontSubscriber   *pSpontSubscriber;
    CHA_RoutingHandler    *pRoutingHandler;
    CHA_ResponseReceiver  *pSpontReceiver;
    CHA_ResponseReceiver  *pImmReceiver;
    CHA_ResponseReceiver  *pDelReceiver;

    RWBoolean              autoConfirm;
    State                  senderState;
    RWBoolean              orderedOn;
    RWBoolean              reportIsOn;
    long                   funBusyAttempts;
    long                   funBusyInterval;
    long                   funBusyCounter;
    RWCString              lastSentCmd;
    RWCString              okReply;
    RWCString              failReply;
    RWBoolean              constructSucceed;
    RWBoolean              interruptPending;

    RWTValOrderedVector<RWCString> keys;
    RWTValSlist<RWCString> extraFailStrings;
    RWTValSlist<RWCString> cslExemptionsStrings;

    RWBoolean              RFlag;

    // for ZFlag
    RWBoolean              ZFlag;
    RWCString              storedFileName; // For the ZFlag
    RWCString              curFile;
    RWCString              onDisconnectLabel;
    RWBoolean              isOnDisconnectSetFlag;

    int connIdleToTimerValue;     // Added due to improvement to avoid hanging problem
    int iOSuperTimerValue;        // Added due to improvement to avoid hanging problem
    int clientQuitFlag;           // Added due to improvement to avoid hanging problem
    RWCString sessionId_;         // Write information into opsserver.log

    long pid;                       // OPS parser process id
};

#endif
