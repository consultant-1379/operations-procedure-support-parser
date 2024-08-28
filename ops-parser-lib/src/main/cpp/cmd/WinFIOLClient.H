/*------------------------------------------------------------------------------
 *******************************************************************************
 * COPYRIGHT Ericsson 2019
 *
 * The copyright to the computer program(s) herein is the property of
 * Ericsson Inc. The programs may be used and/or copied only with written
 * permission from Ericsson Inc. or in accordance with the terms and
 * conditions stipulated in the agreement/contract under which the
 * program(s) have been supplied.
 *******************************************************************************
 *----------------------------------------------------------------------------*/

#ifndef OPSWINFIOLCLIENT_H
#define OPSWINFIOLCLIENT_H
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <queue>
#include <deque>
#include <unistd.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/client_context.h>
#include <rw/cstring.h>
#include "proto/winfiolAxeMed.grpc.pb.h"
#include "WinFIOLDriver.H"

#define CONNECTION_TIMEOUT 240 //seconds
#define DISCONNECT_RETRY_COUNT 1200 //each try in 1 sec, total 20 min
#define READ_AND_REJECT_RESP 0
#define READ_RESP 2
#define DO_NOT_READ_RESP 3
#define COMMAND_NOT_ACCEPTED "NOT ACCEPTED"
#define NODE_TIMEOUT "TIME OUT"
#define INCORRECT_CP "Illegal"
#define INCORRECT_SIDE "not defined"
#define SIDE_NOT_ALLOWED "not allowed"
#define UNREASONABLE_VALUE "Unreasonable"
#define INVALID_COMMAND "Command not found"
#define INVALID_NEID "Invalid NeID"
#define INVALID_SESSIONID "Invalid SessionID"
#define INVALID_ENMUID "Invalid EnmUID"
#define COMMAND_PARTLY_EXECUTED "PARTLY EXECUTED"
#define COMMAND_FUNCTION_BUSY "FUNCTION BUSY"
#define COMMAND_INCOMPLETE "INCOMPLETE COMMAND"
#define CPNAME_CPGROUP_NOT_DEFINED "CP name or CP group is not defined"
#define END "END\r\n"
#define AD_DEVICE_BUSY "Device is occupied"
#define ORDERED_PRINTOUT "ORDERED\x0D"


//Prompts
#define APLOC_PROMPT "\3>"
#define MML_PROMPT "\3<"
#define CONFIGURE_PROMPT "(config*"
#define SUBCOMMAND_PROMPT "\3:"
#define PROMPT1 "\3#"
#define PROMPT2 "\3# "
//#define PROMPT3 "no)? "
//#define PROMPT4 "\n<"
//#define PROMPT5 "< "
//#define PROMPT6 ">"
//#define PROMPT7 "> "
//#define PROMPT8 ">:"
//#define PROMPT9 ": "
//#define PROMPT10 "?"
//#define PROMPT11 "? "
//#define PROMPT12 "] "
//#define PROMPT13 "]:"
//#define PROMPT14 "\":"
#define PROMPT15 "cpt\3<"
#define PROMPT16 "cpt "
//#define PROMPT17 "No)"
//#define PROMPT18 "No "
//#define PROMPT19 "\"\" "
//#define PROMPT20 " \"\""
//#define PROMPT21 "\n:"
//#define PROMPT22 "ADDR:"
//#define PROMPT23 "name: "
//#define PROMPT24 "name:"
//#define PROMPT25 "word: "
//#define PROMPT26 "word:"

//Headers
#define PATTERN_HEADER_APG40AD  "* AD-* TIME ?????? ????*"
#define PATTERN_HEADER_APG40TW  "* TW-* TIME ?????? ????*"
#define PATTERN_HEADER_IOG20AT  "* AT-* TIME ?????? ????*"
#define PATTERN_HEADER_IOG20NVT "* NVT-* TIME ?????? ????*"
//#define PATTERN_HEADER          "*TIME ?????? ????*"  //[TORF-332885]
#define PATTERN_SUBHEADER1      "CLUSTER SESSION - *"
#define PATTERN_SUBHEADER2      "RESTRICTED CP SESSION"
#define PATTERN_SUBHEADER3      "UNRESTRICTED CP SESSION"
#define PATTERN_SUBHEADER4      "UNRESTRICTED CP SESSION - *"
#define PATTERN_SUBHEADER5      "RESTRICTED CP SESSION - *"

//VT100
//#define VT100_CLEAR_SCREEN_CURSOR_DOWN "\x1B\x5B\x4A" //Esc[J
#define VT100_CLEAR_SCREEN_CURSOR_DOWN   "\x5B\x4A" //[J Esc is missing in the data?!
#define VT100_CARRIAGE_RETURN            "\x0D" //^M (carriage return) removal

 /**
  * The WinFIOLClient class, used for interaction with Winfiol Server API
  */
class WinFIOLClient {
public:

    enum WFReturnCode {
        WF_INVALID_NEID = 2,
        WF_INVALID_SESSIONID,
        WF_INVALID_ENMUID,
        WF_COULD_NOT_CONNECT_TO_ES,
        WF_INCORRECT_SIDE,
        WF_INCORRECT_CP,
        WF_SIDE_NOT_ALLOWED,
        WF_UNREASONABLE_VALUE};

    
    enum ctrlChr {RELEASE_CHAR = 1,
                  CONNECT_CHAR};
   WinFIOLClient();
   WinFIOLClient(WinFIOLDriver *wfd,std::string currentPrompt);

 /**
  * The WinFIOLClient Constructor
  * @param channel
  *               GRPC channel created between Winfiol client and server.
  * @param clientName
  *               Name of client communicationg with server.
  */
    WinFIOLClient(std::shared_ptr<Channel> winfiolChannel, std::string clientName);

 /**
  * The WinFIOLClient Destructor
  */
    virtual  ~WinFIOLClient ();

 /**
  * The createSessionAsync call to create a Asynchronous session with winfiol server
  */
    virtual std::string createSessionAsync();

  /**
   * Terminated the winfiol session.
   */
    virtual int terminateSession();

  /**
   * Connect Function call to server
   * @param poID
   *           poID of the node in the environment.
   */
    virtual int connect(std::string poId);

  /**
   * This function gets the connection status from the server.
   */
    virtual int getConnectionStatus();

  /**
   * sendData Function call to server
   * @param cmd
   *           command to send to the node.
   * @param cmdNo
   *           command number
   */
    virtual void sendData (std::string cmd, int readResp = 1);

  /**
   * This function sets the response stream.
   */
    virtual void initStream ();

  /**
   * Fetch the response Data from the server.
   */
    virtual std::string getResponsedata() ;
 
 /**
  * @ORDERED("ON")
  */
    virtual void orderedOn();

 /**
  * @ORDERED("OFF")
  */
    virtual void orderedOff();

 /**
  *  
  */
    virtual bool isResponseEnded();

 /**
  * Send control character on Node.
  * true = ctrl+d (RELEASE)
  * false = ctrl+m (CONNECT)
  */
    virtual void sendControlChar(int ctrlChar, int readResp = 0);

  /**
   * ENM User Name
   */
    virtual void setEnmUser(std::string enmU);

    virtual bool isAplocMode();

    virtual bool isAdNode();

    virtual int disconnect();

    std::string getCurrentPrompt();

    void setAutoConfirm(bool confirm){autoConfirm = confirm;}
    void logoff();
    void logon();

    virtual std::deque<RWCString> getImmediatePrintouts();
    bool isImmRespEnded();

private:

    std::string getWfSessionId();
    std::string getEnmUser();
    bool gotPrompt(std::string&);
    bool hasPrintOut();
    void initiatePrompts();
    void removeHeadersFromBuffer(std::string &buffer);
    bool strMatch(const char* szSource, const char* szPattern);
    void initiateHeaders();
    void removeStringFromBuffer(std::string &buffer, std::string stringToRemove);
    void washStringFromNewlineCarriageReturn(std::string & str);
    void readOrderedAndSpontaneousPrintouts();
    std::string getSyslogMessage(std::string messageType, std::string state);
    void clearVariables();
    void initiateCharacters();
    void suppressCharacters(std::string& data);
    void parseConnectTokens(std::vector<std::string> tokens,
                            ConnectRequest::ApNodeSide& nodeSide,
                            ConnectRequest::ApNode& node);
    int setConnectionMode(int connectionStatus);
    bool isDualApg(std::string const &fullString);
    bool isBladeCluster(std::string tokname);
    bool setBladeClusterNode(std::string tokname);
    void readHeader();

    //TODO: Alarm recognition if spontaneous printout shall be activated
    //bool isPrintoutAlarm(std::string printout);
    bool isOrdered;
    bool loggedOff;
    std::string clientId;
    std::string neName;
    std::string respString;
    std::string wfSessionId;
    std::string enmUser;
    std::string nodeSide;
    std::string bladeName;
    std::string neId;
    int headerLen;
    bool isRspEnded;
    std::string nodeRespHeader;
    bool autoConfirmPrompt;
    bool isAploc;
    std::vector<std::string> prompts;
    std::string currentPrompt;
    int orderedCount;
    bool adNode;
    bool exitDone;
    std::vector<std::string> headers;
    WinFIOLDriver* wfdriver;
    std::queue<std::string> orderedPrintouts;
    bool connectionInterrupted;
    bool autoConfirm;
    bool autoConfirmSent;
    bool autoConfirmReq;
    std::vector<std::string> charactersToSuppress;
    std::queue<std::string> immediatePrintouts;
    bool orderedFound;
    const std::string bcCluster;
    const std::string cpCluster;
    const std::string dualAPG;
    const std::string neHeader;
    int expectedResponse;
    bool systemRestarted;
    std::deque<RWCString> returnQ;
};

#endif // OPSWINFIOLCLIENT_H
