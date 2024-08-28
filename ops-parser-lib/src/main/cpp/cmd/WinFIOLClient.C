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

#include "WinFIOLClient.H"
#include <algorithm>
#include <string>
#include <sstream>
#include <memory>
#include <trace.H>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>

std::condition_variable condvar_;
std::mutex mutex_;
typedef std::lock_guard<std::mutex> lock;
typedef std::unique_lock<std::mutex> ulock;

//**********************************************************************
static std::string trace ="WinFIOLClient";
//**********************************************************************

WinFIOLClient::WinFIOLClient():
  clientId(""),
  wfdriver(NULL),
  neName(""),
  isOrdered(true),
  isRspEnded(false),
  nodeRespHeader(""),
  enmUser(""),
  isAploc(false),
  currentPrompt(""),
  neId(""),
  bcCluster("__BC"),
  cpCluster("__CP"),
  dualAPG("_1"),
  neHeader("NE="),
  orderedCount(0),
  expectedResponse(0),
  systemRestarted(false),
  connectionInterrupted(false),
  autoConfirm(true),
  autoConfirmSent(false),
  autoConfirmReq(false),
  adNode(false),
  exitDone(false),
  autoConfirmPrompt(false),
  loggedOff(false)
{
  // Default constructor
}

WinFIOLClient::WinFIOLClient(WinFIOLDriver *wfd,std::string current_Prompt):
  clientId(""),
  wfdriver(wfd),
  neName(""),
  isOrdered(true),
  isRspEnded(false),
  nodeRespHeader(""),
  enmUser(""),
  isAploc(false),
  currentPrompt(current_Prompt),
  neId(""),
  bcCluster("__BC"),
  cpCluster("__CP"),
  dualAPG("_1"),
  neHeader("NE="),
  orderedCount(0),
  expectedResponse(0),
  systemRestarted(false),
  connectionInterrupted(false),
  autoConfirm(true),
  autoConfirmSent(false),
  autoConfirmReq(false),
  adNode(false),
  exitDone(false),
  autoConfirmPrompt(false),
  loggedOff(false)
{
     //  constructor with single Parameter ,New change is done
    initiatePrompts();
    initiateHeaders();
    initiateCharacters();
}

WinFIOLClient::WinFIOLClient(std::shared_ptr<Channel> winfiolChannel,
                             std::string clientName):
  clientId(clientName),
  neName(""),
  isOrdered(true),
  isRspEnded(false),
  nodeRespHeader(""),
  enmUser(""),
  isAploc(false),
  currentPrompt(""),
  neId(""),
  bcCluster("__BC"),
  cpCluster("__CP"),
  dualAPG("_1"),
  neHeader("NE="),
  orderedCount(0),
  expectedResponse(0),
  systemRestarted(false),
  connectionInterrupted(false),
  autoConfirm(true),
  autoConfirmSent(false),
  autoConfirmReq(false),
  adNode(false),
  exitDone(false),
  wfdriver(NULL),
  autoConfirmPrompt(false),
  loggedOff(false)
{
    TRACE_IN(trace, WinFIOLClient, "Constructor WinFIOLClient");
    wfSessionId = getWfSessionId();
    wfdriver = new WinFIOLDriver(winfiolChannel, clientName, wfSessionId);

    initiatePrompts();
    initiateHeaders();
    initiateCharacters();
    openlog("DDCDATA[OPS]", LOG_ODELAY, LOG_LOCAL2);
    TRACE_OUT(trace, WinFIOLClient, "WinFIOL Session Id: " <<wfSessionId );
}

bool WinFIOLClient::isResponseEnded() {
    return isRspEnded;
}

bool WinFIOLClient::isAdNode() {
    return adNode;
}

std::string WinFIOLClient::createSessionAsync() {
    TRACE_IN(trace, createSessionAsync, "");
    TRACE_OUT(trace, createSessionAsync, "");
    return wfdriver->createSessionAsync();
}

int WinFIOLClient::terminateSession() {
    TRACE_IN(trace, terminateSession, "");
    //syslog(LOG_INFO, getSyslogMessage("OPS_WinFIOL_Session", "Disconnected", "").c_str());
    clearVariables();
    TRACE_OUT(trace, terminateSession, "");
    return wfdriver->terminateSession();
}

WinFIOLClient::~WinFIOLClient () {
    TRACE_IN(trace, ~WinFIOLClient, "Destructor WinFIOLClient" );
    if(wfdriver){
        delete wfdriver;
        wfdriver = NULL;
    }

    TRACE_OUT(trace, ~WinFIOLClient, "" );
}

int WinFIOLClient::disconnect() {
    TRACE_IN(trace, disconnect, "");
    TRACE_INFO(trace, disconnect, "Disconnect requested");
    int retryCount = 0;

    while(!exitDone && (retryCount < DISCONNECT_RETRY_COUNT)) {
       if (currentPrompt.compare(APLOC_PROMPT) == 0) {
           TRACE_FLOW(trace,disconnect, "APLOC prompt, sending exit");
           sendData("exit");
       }
       else if (currentPrompt.compare(MML_PROMPT) == 0) {
           TRACE_FLOW(trace,disconnect, "MML prompt, sending exit;");
           sendData("exit;");
       }
       else if (currentPrompt.find(CONFIGURE_PROMPT) == 0) {
           TRACE_FLOW(trace,disconnect, "configure prompt, sending end");
           sendData("end");
       }
       else {
           TRACE_FLOW(trace, disconnect, "Prompt other than APLOC,MML and CONFIGURE: " << currentPrompt);
           terminateSession();
           break;
       }
       retryCount++;
       sleep(1);
    }

    if (DISCONNECT_RETRY_COUNT == retryCount) {
        TRACE_ERROR(trace, disconnect, "Normal disconnection timed out");
        terminateSession();
    }

    exitDone = false;
    TRACE_OUT(trace, disconnect, "");
    return 0;
}

int WinFIOLClient::connect(std::string poId) {
    TRACE_IN(trace, connect, "Node name: " << poId);

    clearVariables(); //Everything should be cleared when connecting (again)
    orderedCount = 0;
    int ret = 1;
    neName = poId;

    boost::algorithm::trim(neName);

    ConnectRequest::ApNodeSide nodeSide = ConnectRequest::CLUSTER;
    ConnectRequest::ApNode node = ConnectRequest::AP1;

    bladeName = "mml";

    // Vector of string to save tokens
    std::vector <std::string> tokens;

    std::string rightStr = neName;
    while(rightStr.find(",") != std::string::npos) {
        tokens.push_back(rightStr.substr(0, rightStr.find(","))); //NE=
        rightStr = rightStr.substr(rightStr.find(",") + 1, rightStr.length() - rightStr.find(","));
    }
    tokens.push_back(rightStr);

    // Parse connection tokens
    parseConnectTokens(tokens, nodeSide, node);

    TRACE_FLOW(trace, connect, "neId: " << neId.c_str());
    Status status = wfdriver->connect(neId, nodeSide, node);

    if (!status.ok()) {
        TRACE_ERROR(trace, connect, "Failed to connect to Node: " << neName << " with error " << status.error_message());
	this->terminateSession();
        syslog(LOG_INFO, getSyslogMessage("OPS_WinFIOL_Session", "Failed").c_str());
        ret = WF_COULD_NOT_CONNECT_TO_ES;
        adNode = false;
        if (status.error_code() == 3) {
            if (status.error_message().find(INVALID_NEID) != std::string::npos) {
                ret = WF_INVALID_NEID;
            }
            else if (status.error_message().find(INVALID_SESSIONID) != std::string::npos) {
                ret = WF_INVALID_SESSIONID;
            }
            else if (status.error_message().find(INVALID_ENMUID) != std::string::npos) {
                ret = WF_INVALID_ENMUID;
            }
            else {
                ret = WF_COULD_NOT_CONNECT_TO_ES;
            }
        }
    }
    else {
        TRACE_FLOW(trace, connect, "Connection Status: OKAY");
        ret = setConnectionMode(status.error_code());
    }

    TRACE_OUT(trace, connect, "Return value: " << ret);
    return ret;
}

void WinFIOLClient::parseConnectTokens(std::vector<std::string> tokens, 
                                       ConnectRequest::ApNodeSide& nodeSide,
                                       ConnectRequest::ApNode& node) {
    TRACE_IN(trace, parseConnectTokens, "");

    for(int i = 0; i < tokens.size(); i++) {
        TRACE_FLOW(trace, parseConnectTokens, "Value of tokens: "<<tokens[i] );
        std::string tokname = tokens[i];

        if (tokname.find(neHeader) != std::string::npos) {
            if(isBladeCluster(tokname)) {
                setBladeClusterNode(tokname);
            }
            else if (isDualApg(tokname)) { //checking if "_1" is at the end of node name
                size_t pos = neName.find(neHeader);
                int delpos = tokname.rfind(dualAPG);
                neId = tokname.substr(pos+3,  delpos-3);
                nodeSide = ConnectRequest::CLUSTER;
                node = ConnectRequest::AP2;
                isAploc = true;
                TRACE_FLOW(trace, parseConnectTokens, "Node Name for DUAL APG: " << neId );
            }
            else {
                int pos = tokname.find(neHeader);
                neId = tokname.substr(pos+3);
                TRACE_FLOW(trace, parseConnectTokens, "Node Name: "<<neId );
            }
        }
        else if (boost::icontains(tokname, "AD=")) {
            int pos = tokname.find("=");
            bladeName = bladeName + " -d ad-" + tokname.substr(pos + 1);
            adNode = true;
            TRACE_FLOW(trace, parseConnectTokens, "BladeName for AD: " << bladeName );
        }
        else if (boost::icontains(tokname, "CPNAME=")) {
            int pos = tokname.find("=");
            bladeName = bladeName + " -cp " + tokname.substr(pos + 1);
            TRACE_FLOW(trace, parseConnectTokens, "BladeName for CPNAME: " << bladeName );
        }
        else if (boost::iequals(tokname, "SIDE=STANDBY")) {
            bladeName = bladeName + " -s ";
            TRACE_FLOW(trace, parseConnectTokens, "BladeName for SIDE=STANDBY: " << bladeName );
        }
        else if (boost::iequals(tokname, "SIDE=EXECUTIVE")) {
            TRACE_FLOW(trace, parseConnectTokens, "BladeName for SIDE=EXECUTIVE: " << bladeName );
        }
        else if (boost::iequals(tokname, "NODE=B")) {
            nodeSide = ConnectRequest::NODE_B;
            TRACE_FLOW(trace, parseConnectTokens, "Connecting to Node Side B" );
            isAploc = true;
        }
        else if (boost::iequals(tokname, "NODE=A")) {
            nodeSide = ConnectRequest::NODE_A;
            TRACE_FLOW(trace, parseConnectTokens, "Connecting to Node Side A" );
            isAploc = true;
        }
        else if (boost::iequals(tokname, "NODE=C")) {
            TRACE_FLOW(trace, parseConnectTokens, "Connecting to Node Side C" );
            isAploc = true;
        }
        else if (isDualApg(tokname)) { //checking if "_1" is at the end of node name
           size_t pos = tokname.rfind(dualAPG);
           neId = tokname.substr(0,  pos);
           TRACE_FLOW(trace, parseConnectTokens, "Connecting to DUAL APG: " << neId);
           nodeSide = ConnectRequest::CLUSTER;
           node = ConnectRequest::AP2;
           isAploc = true;
        }
        else if (isBladeCluster(tokname)) {
            setBladeClusterNode(tokname);
        }
        else {
            neId = tokname;
        }
    }
    TRACE_OUT(trace, parseConnectTokens, "");
}

int WinFIOLClient::setConnectionMode(int connectionStatus) {
    TRACE_IN(trace, setConnectionMode, "");

    int ret = connectionStatus;
    if ((boost::icontains(neName, "NODE=")) || (isDualApg(neName))) {
        TRACE_FLOW(trace, setConnectionMode, "Connected to AP Mode");
        syslog(LOG_INFO, getSyslogMessage("OPS_WinFIOL_Session", "Connected").c_str());
        sendData(" ");//Adding prompt to output
    }
    else {
        //sendData(bladeName);
        //std::string cmdResponse = getResponsedata();
        std::string cmdResponse = "";
        std::string response = "";
        wfdriver->sendData(bladeName);
        int retryCount = 1;
        std::string read_retry_count = getenv("READ_DATA_RETRY_COUNT");
        int read_data_retry_count = atoi(read_retry_count.c_str());
        while (wfdriver->readData(response)) {
            cmdResponse += response;
            if(gotPrompt(response)) {//only checking response since gotPrompt now removes prompt
                TRACE_FLOW(trace, setConnectionMode, "Data: " << cmdResponse.c_str());
                removeStringFromBuffer(cmdResponse, bladeName); //remove command echo
                removeHeadersFromBuffer(cmdResponse);
                suppressCharacters(cmdResponse);
                break;
            }
            // To handle resdResponse timeout
            if(retryCount == read_data_retry_count){
                int timeout = read_data_retry_count/60;
                TRACE_ERROR(trace, setConnectionMode, "No response received for: "<<timeout<<" minutes.");
                ret = 25; // Random magic number to capture unknown error response
                disconnect();
                break;
            }
            // To make readResponse available if response takes time
            if (!response.empty()) {
                retryCount = 1;
            } else {
                retryCount++;
                sleep(1);
            }
        }

        if(std::find(prompts.begin(), prompts.end(), cmdResponse) != prompts.end()) {
            TRACE_FLOW(trace, setConnectionMode, "Connected to CP Mode!");
            syslog(LOG_INFO, getSyslogMessage("OPS_WinFIOL_Session", "Connected").c_str());
            TRACE_FLOW(trace, setConnectionMode, "cmdResponse:" << cmdResponse.c_str());
            //respString += cmdResponse; //Adding prompt to output
        }
        else if (cmdResponse.find(INCORRECT_SIDE) != std::string::npos) {
            TRACE_ERROR(trace, setConnectionMode, "Connect SIDE is not defined");
            syslog(LOG_ERR, getSyslogMessage("OPS_WinFIOL_Session", "Failed").c_str());
            ret = 6;
            disconnect();
        }
        else if ((cmdResponse.find(INCORRECT_CP) != std::string::npos) || (cmdResponse.find(CPNAME_CPGROUP_NOT_DEFINED) != std::string::npos)) {
            TRACE_ERROR(trace, setConnectionMode, "Illegal CP name, or, CP name or CP group is not defined.");
            syslog(LOG_ERR, getSyslogMessage("OPS_WinFIOL_Session", "Failed").c_str());
            ret = 7;
            disconnect();
        }
        else if (cmdResponse.find(SIDE_NOT_ALLOWED) != std::string::npos) {
            TRACE_ERROR(trace, setConnectionMode, "Connect to SIDE not allowed");
            syslog(LOG_ERR, getSyslogMessage("OPS_WinFIOL_Session", "Failed").c_str());
            ret = 8;
            disconnect();
        }
        else if (boost::icontains(cmdResponse,UNREASONABLE_VALUE)) {
            TRACE_ERROR(trace, setConnectionMode, "Connection unreasonable");
            syslog(LOG_ERR, getSyslogMessage("OPS_WinFIOL_Session", "Failed").c_str());
            ret = 9;
            disconnect();
        }
        else if (cmdResponse.find(AD_DEVICE_BUSY) != std::string::npos) {
            TRACE_ERROR(trace, setConnectionMode, "Connected AD device is busy");
            syslog(LOG_ERR, getSyslogMessage("OPS_WinFIOL_Session", "Failed").c_str());
            ret = 5;
            adNode = false;
            disconnect();
        }
        else {
            TRACE_ERROR(trace, setConnectionMode, "sendBladeName: Unknown error response received");
            syslog(LOG_ERR, getSyslogMessage("OPS_WinFIOL_Session", "Failed").c_str());
            //ret = 25; // Random magic number to capture unknown error response
            //disconnect();
        }
    }

    TRACE_OUT(trace, setConnectionMode, "Return value: " << ret);
    return ret;
}

int WinFIOLClient::getConnectionStatus(){
    TRACE_IN(trace, getConnectionStatus, "");
    TRACE_OUT(trace, getConnectionStatus, "");
    return wfdriver->getConnectionStatus();
}

void WinFIOLClient::logoff(){
    TRACE_IN(trace, logoff, "");
    std::string responseBuffer = "";
    loggedOff = true;
    bool cpMode = false;

    if (getCurrentPrompt().compare(APLOC_PROMPT) == 0) {
        TRACE_FLOW(trace, logoff, "Aploc mode, executing mml to send release/connect character");
        sendData("mml");
        cpMode = true;
    }

    Status status = wfdriver->sendControlChar(RELEASE_CHAR);
    if(expectedResponse > 0) {
        readOrderedAndSpontaneousPrintouts();
    }
    status = wfdriver->sendControlChar(CONNECT_CHAR);
    if(!systemRestarted) {
        readHeader();
    }


    while(!orderedPrintouts.empty()) {
        responseBuffer += orderedPrintouts.front();
        TRACE_FLOW(trace, logoff, "Printout from queue: " << orderedPrintouts.front());
        orderedPrintouts.pop();

        if (orderedCount > 0) { //Fix for TORF-336209
            orderedCount--;
        }
        TRACE_FLOW(trace, logoff, "orderedCount: " << orderedCount);
    }

    if (cpMode) {
        TRACE_FLOW(trace, logoff, "Switch to Aploc mode");
        sendData("aploc;");
        cpMode = false;
    }
    respString += responseBuffer;
    TRACE_OUT(trace, logoff, "");
}

void WinFIOLClient::logon(){ //Not used at the moment. @LOGON does nothing
    TRACE_IN(trace, logon, "");
    loggedOff = false;
    sendControlChar(CONNECT_CHAR);
    TRACE_FLOW(trace, logon, "Sending CONNECT");
    TRACE_OUT(trace, logon, "");
}

void WinFIOLClient::sendControlChar(int ctrlChar, int readResp) {
    TRACE_IN(trace, sendControlChar, "");
    /*if((getCurrentPrompt().compare(MML_PROMPT) != 0) &&
        (getCurrentPrompt().compare(SUBCOMMAND_PROMPT) != 0) &&
        (getCurrentPrompt().compare(PROMPT15) != 0) &&
        (getCurrentPrompt().compare(PROMPT16) != 0)) {
        //Not a prompt to send release/connect here
        TRACE_OUT(trace, sendControlChar, "");
        return;
    }*/
    isRspEnded = false;

    std::string response;
    std::string responseBuffer = "";

    if (ctrlChar == RELEASE_CHAR) {

        Status status = wfdriver->sendControlChar(ctrlChar);
        TRACE_FLOW(trace, sendControlChar, "Sending RELEASE");

        TRACE_FLOW(trace, sendControlChar, "orderedCount1: " << orderedCount);

        if(autoConfirmPrompt) {
            while(wfdriver->readData(response)) {//We get INHIBITED if RELEASE is sent on auto confirm prompt

                if(gotPrompt(response)) {
                    responseBuffer += response;
                    break;
                }
                else {
                    responseBuffer += response;
                }
            }
        } else {

            readOrderedAndSpontaneousPrintouts();

            while((isOrdered || loggedOff) && (orderedCount > 0) && (!orderedPrintouts.empty())) {
                responseBuffer += orderedPrintouts.front();
                TRACE_FLOW(trace, sendControlChar, "Printout from queue: " << orderedPrintouts.front());
                orderedPrintouts.pop();
                orderedCount--;
                TRACE_FLOW(trace, sendControlChar, "orderedCount2: " << orderedCount);
            }

            std::string tmpResponsBuffer = "";

            while ( (isOrdered || loggedOff) && (orderedCount > 0) && wfdriver->readData(response)) {
                TRACE_FLOW(trace, sendControlChar, "Reading data...");
                tmpResponsBuffer += response;
                TRACE_FLOW(trace, sendControlChar, "Data:\n" << response.c_str());

                int begin = 0;
                for (size_t offset = tmpResponsBuffer.find(0x04); offset != std::string::npos;
                        offset = tmpResponsBuffer.find(0x04, offset + 1))
                {

                    std::string printout = tmpResponsBuffer.substr(begin, (offset - begin));
                    begin = offset +1;
                    if((printout.find("TIME OUT") != std::string::npos) && (printout.find("END") == std::string::npos)){
                    //found TIME OUT string without END string in the print out response
                            TRACE_ERROR(trace, sendControlChar, "TIME OUT found!");
                            tmpResponsBuffer.erase(begin, (offset - begin));
                            continue;
                    }
                    else {
                        TRACE_FLOW(trace, sendControlChar, "PRINTOUT found!");
                            orderedCount--;
                            responseBuffer += printout;
                            tmpResponsBuffer.erase(begin, (offset - begin));
                            TRACE_FLOW(trace, sendControlChar, "orderedCount3: " << orderedCount);
                    }
                }
            }
            TRACE_FLOW(trace, sendControlChar, "All ordered printouts found...\n");
        }
    }
    else {
        TRACE_FLOW(trace, sendControlChar, "Sending CONNECT");
        Status status = wfdriver->sendControlChar(ctrlChar);
        while (wfdriver->readData(response)) {

            if(gotPrompt(response)) {
                responseBuffer += response;
                break;
            }
            else {
                responseBuffer += response;
            }
        }
    }

    if(responseBuffer.compare("") != 0) {
        //TRACE_FLOW(trace, sendControlChar, "Adding:" << responseBuffer.c_str());
        respString += responseBuffer;
    }

    isRspEnded = true;
    TRACE_OUT(trace, sendControlChar, "");
}

bool WinFIOLClient::isAplocMode() {// TODO: isAploc used in connect is not used, change connect.
    if(currentPrompt.compare(APLOC_PROMPT) != 0) {
        return false;
    }
    return true;
}

void WinFIOLClient::sendData (std::string cmd, int readResp) {
    TRACE_IN(trace, sendData, "readResp: " << readResp );

    loggedOff = false; //@LOGOF suspended by MML command. The only way to suspend?
    isRspEnded = false;
    autoConfirmPrompt = false;
    std::string response="";
    std::string commandResponse="";
    std::string commandEcho="";
    std::string tmpCmdStr = cmd+VT100_CARRIAGE_RETURN;
    bool commandEchoRemoved = false;
    bool skipOrderedPrintouts = false;
    bool timeOutFound = false;
    bool promptFound = false;
    bool newCommand = true;

    int retryCount = 1;
    std::string read_retry_count = getenv("READ_DATA_RETRY_COUNT");
    int read_data_retry_count = atoi(read_retry_count.c_str());

    std::string tmpCmd = cmd;
    transform(tmpCmd.begin(), tmpCmd.end(), tmpCmd.begin(), ::toupper);
    std::stringstream confirmCmd;
    confirmCmd << " " << tmpCmd;

    TRACE_FLOW(trace, sendData, "Sending command to winfiol: " << cmd);
    syslog(LOG_INFO, getSyslogMessage("OPS_WinFIOL_Command", "Sent").c_str());

    wfdriver->sendData(cmd);

    if((cmd.rfind("mml", 0) == 0) && (cmd.find("-f") != std::string::npos)) {
        skipOrderedPrintouts = true;
        //Ignoring all ordered responses if a file is directly executed on the node without any OPS interaction.
        //since output will be directly generated on node irrespective of @ordered state
    }

    //receive the command output
    while (wfdriver->readData(response) && (retryCount <= read_data_retry_count)) {
        TRACE_FLOW(trace, sendData, "Response from WinFIOL: "<<response);

        if( (response.find("TIME OUT") != std::string::npos) || (timeOutFound))
        {
            
            if(response.find("END") != std::string::npos)
            {
                timeOutFound = false;
            }
            else
            {
                timeOutFound = true;
            }
            TRACE_FLOW(trace, sendData, "TIME OUT found: "<<std::boolalpha<<timeOutFound);
        }
        if((response.find(ORDERED_PRINTOUT) != std::string::npos) && (!skipOrderedPrintouts) && (newCommand)) { //All ORDERED are counted.
            orderedCount++;
            expectedResponse++;
            TRACE_FLOW(trace, sendData, "Ordered Count incremented : "<< orderedCount);
            newCommand= false;
            TRACE_FLOW(trace, sendData, "case: ORDERED_PRINTOUT, Ordered Count: " << orderedCount);
        }
        
        TRACE_FLOW(trace, sendData, "CurrentPrompt:" << getCurrentPrompt()<<" ConfirmCmd: "<<confirmCmd.str() <<"autoConfirm: "<<std::boolalpha <<autoConfirm);
        if ((getCurrentPrompt().compare(MML_PROMPT) == 0) && (response.rfind(confirmCmd.str()) != std::string::npos)) {
            if(autoConfirm) {
                TRACE_FLOW(trace, sendData, "case: CONFIRMATION_PRINTOUT, Auto confirm enabled");
                autoConfirmReq = true;
 
                // logic to handle prompt with confirmation response
                std::string autoConfResp = response;
                int pos = autoConfResp.rfind(MML_PROMPT);
                if (pos != std::string::npos) {
                    response = autoConfResp.substr(pos);
                    autoConfResp = autoConfResp.substr(0, pos);
                }
                autoConfResp += ";\n";
                lock l(mutex_); // prevents multiple pushes corrupting queue_
                immediatePrintouts.push(autoConfResp);
                condvar_.notify_all();
            } else {//We got auto confirm prompt, but no confirmation is done
                TRACE_FLOW(trace, sendData, "case: CONFIRMATION_PRINTOUT, Manual confirmation required");
                autoConfirmPrompt = true; //anything else then ; at this promp will give INHIBITED
            }
        }
 
        if(response.find("Connection closed") != std::string::npos) { // TODO: Trying to fix "exit from AP-prompt". Is "Connection closed" printed from all nodes?
            this->terminateSession();
            exitDone = true;
            break;
        } else if(response.find("CONNECTION INTERRUPTED") != std::string::npos) {
            commandResponse += response;
            autoConfirmPrompt = false;
            connectionInterrupted = true;
            break;
        } else if(gotPrompt(response)) {
            TRACE_FLOW(trace, sendData, "case: PRINTOUT_WITH_PROMPT cmd:" << cmd);
            promptFound = true;
            if(autoConfirmReq) { 
                autoConfirmSent = true;
                autoConfirmReq = false;
                sendData(";",0);//Send confirm
                autoConfirmSent = false;
            }

            if(!commandEchoRemoved) {
                commandEcho +=response;
                commandResponse += commandEcho;
                removeStringFromBuffer(commandResponse, cmd);//remove command echo
                commandEchoRemoved = true;
            } else {
                commandResponse += response;
            }
            break;
        } else {
            TRACE_FLOW(trace, sendData, "case: PRINTOUT_WITHOUT_PROMPT: readResp: "<< readResp );
            // check if sending new command
            if (0 == readResp) {
                if (!commandEchoRemoved) {
                    commandEcho += response;
                    if (commandEcho.find(tmpCmdStr) != std::string::npos) {
                        TRACE_FLOW(trace, sendData, "Command echo found: " );
                        removeStringFromBuffer(commandEcho, cmd); // remove command echo
                        if(commandEcho.find_first_not_of(" \t\n\v\f\r") != std::string::npos) {
                            TRACE_FLOW(trace, sendData, "Response found with command echo flushed: "<< commandEcho.c_str());
                            lock l(mutex_); // prevents multiple pushes corrupting queue_
                            immediatePrintouts.push(commandEcho);
                            condvar_.notify_all();
                        }
                        commandEchoRemoved = true;
                    }
                } else {
                    if (!autoConfirmReq) {
                        commandEcho = "";
                        TRACE_FLOW(trace, sendData, "Response flushed autoConfirmReq" << autoConfirmReq);
                        lock l(mutex_); // prevents multiple pushes corrupting queue_
                        immediatePrintouts.push(response);
                        condvar_.notify_all();
                    }
                }
            } else {
                commandResponse += response;
            }
        }
        
        // To handle readResponse timeout
        if(retryCount == read_data_retry_count){
            int timeout = read_data_retry_count/60;
            TRACE_ERROR(trace, sendData, "No response received for: "<<timeout<<" minutes.");
        }
        // To make readResponse available if response takes time
        if (!response.empty()) {
            retryCount = 1;
        } else {
            retryCount++;
            sleep(1);
        }
    }

    if (1 == readResp) {
        TRACE_FLOW(trace, sendData, "Remove command from buffer: "<<cmd );
        removeStringFromBuffer(commandResponse, cmd); //remove command echo
    }

    respString += commandResponse;
    TRACE_FLOW(trace, sendData, "Command response from buffer "<<respString );

    if(isOrdered && (orderedCount>0)) { //If ORDERED(ON) all ORDERED printouts are fetched instantly. ORDERED(OFF) will count printouts but not fetch them.
        TRACE_FLOW(trace, sendData, "Number of ORDERED queued: " << orderedCount);
        sendControlChar(RELEASE_CHAR, 0);//Get the ORDERED printouts
        sendControlChar(CONNECT_CHAR, 0);//Get prompt back
    }

    int waitCounter = 0;
    while (!isImmRespEnded()) {
        TRACE_FLOW(trace, sendData, "Waiting for immediate response to end... Max wait time(sec) " <<  waitCounter << " Records to process " << immediatePrintouts.size());
        if (waitCounter > 600) {
            TRACE_ERROR(trace, sendData, "Thread to flush immediate printouts has failed To process: "<< immediatePrintouts.size());
            break;
        }
        sleep(1);
        waitCounter++;
    }

    if((timeOutFound)&&(promptFound)) {
        TRACE_FLOW(trace, sendData, "case NODE_TIMED_OUT: Retrying the command : " << cmd);
        timeOutFound = false;
        promptFound = false;
        sendData(cmd);
    }

    TRACE_OUT(trace, sendData, "");
}

std::string WinFIOLClient::getResponsedata() {
    TRACE_IN(trace, getResponsedata, "Response data: " << respString.c_str());
    std::string response = respString;
    removeHeadersFromBuffer(response);
    suppressCharacters(response);
    respString = "";
    TRACE_OUT(trace, getResponsedata, "");
    if(response.find_first_not_of(" \t\n\v\f\r") != std::string::npos) {
        TRACE_FLOW(trace, getResponsedata, "response : " << response);
        return response;
    }
    return respString;
}

bool WinFIOLClient::hasPrintOut()
{
    return !immediatePrintouts.empty();
}

std::deque<RWCString> WinFIOLClient::getImmediatePrintouts() {
    std::queue<std::string> swapper;
    returnQ.clear();
    //Sync block, the wait call will only proceed if the inner lambda expression returns a true i.e []{return !immediatePrintouts.empty();}
    //if it returns false, the wait will release the mutex.
    ulock u(mutex_);

    condvar_.wait(
                u,std::bind(&WinFIOLClient::hasPrintOut, this));
     int fetch = 0;
     int batchSize = 5000;
     if(immediatePrintouts.size() > batchSize) {
     //This client thread exits the moment this queue is empty, so it is important to make sure we fetch only data which can be processed in 50msec
        while(fetch < batchSize) {
            swapper.push(immediatePrintouts.front());
            immediatePrintouts.pop();
            fetch++;
        }
     } else {
        swapper.swap(immediatePrintouts);
     }
     u.unlock();
    // Sync block done
    std::string bigChunk = "";
    int bufCount = 0;
    while(!swapper.empty()) {
        std::string chunk = swapper.front();
        swapper.pop();
        removeHeadersFromBuffer(chunk);
        suppressCharacters(chunk);
        if(bufCount < 9) { //Further reducing the load on processing thread by mergning 10 printouts to one.
            bigChunk += chunk;
            bufCount++;
        } else {
            bigChunk += chunk;
            returnQ.push_back(bigChunk);
            bufCount=0;
            bigChunk="";
        }

    }
        if(bufCount != 0) {
        returnQ.push_back(bigChunk);
        }
        TRACE_FLOW(trace, getImmediatePrintouts, "Processing queue: " << returnQ.size() << "Pending queue: "<<immediatePrintouts.size());
    return returnQ;
}

bool WinFIOLClient::isImmRespEnded() {
    bool bRespEnded = false;

    if (immediatePrintouts.empty() && returnQ.empty()) {
        bRespEnded = true;
        usleep(500000); //wait for response to get flushed on output window for 500ms
    }
    return bRespEnded;
}

std::string WinFIOLClient::getWfSessionId() {
   using boost::property_tree::ptree;
   ptree pt;
   boost::property_tree::ini_parser::read_ini( "/opt/ops/ops_server/etc/ops-config.properties", pt );
   std::string s=pt.get<std::string>("WfSessionId");
   return s;
}

std::string WinFIOLClient::getEnmUser() {
   return enmUser;
}

void WinFIOLClient::setEnmUser(std::string enmU) {
    TRACE_IN(trace, setEnmUser, "Setting Enm User: " << enmU.c_str());
    enmUser = enmU;
    wfdriver->setEnmUser(enmU);
    TRACE_OUT(trace, setEnmUser, "");
}

void WinFIOLClient::orderedOn() {
    isOrdered = true;
}

void WinFIOLClient::orderedOff() {
    isOrdered = false;
}
bool WinFIOLClient::gotPrompt(std::string& data){
    TRACE_IN(trace, gotPrompt, "");
    bool promptFound = false;

    for(int i = 0; i < prompts.size(); i++){
        int found = data.rfind(prompts[i].c_str());
        if(found == -1) {
            continue;
        } else {
            promptFound = true;
            currentPrompt = prompts[i];
            if( (currentPrompt.compare(MML_PROMPT) == 0 ) || (currentPrompt.compare(APLOC_PROMPT) == 0 ) ) {
                 data.erase(found,currentPrompt.length()); //remove the MML prompt
            }
            break;
        }
    }

    if(promptFound && currentPrompt.compare(APLOC_PROMPT) == 0 && strMatch(data.c_str(), CONFIGURE_PROMPT ) ){ //If AP prompt, check if we are in config mode
        currentPrompt = CONFIGURE_PROMPT;
    }
    TRACE_OUT(trace, gotPrompt, "hasPrompt:  " << std::boolalpha << promptFound <<" .Prompt: "<<currentPrompt);

    return promptFound;
}

void WinFIOLClient::initiatePrompts() { //TODO: Could the prompts be configurable?
    TRACE_IN(trace, initiatePrompts, "");
    prompts.push_back(PROMPT15);// "cpt\3<"
    prompts.push_back(APLOC_PROMPT);//"\3>"
    prompts.push_back(MML_PROMPT);//"\3<"
    prompts.push_back(SUBCOMMAND_PROMPT);//"\3:"
    prompts.push_back(PROMPT1);// "\3#"
    prompts.push_back(PROMPT2);// "\3# "
    prompts.push_back(PROMPT16);//"cpt "
    TRACE_OUT(trace, initiatePrompts, "");
}

void WinFIOLClient::initiateHeaders() {
    TRACE_IN(trace, initiateHeaders, "");
    headers.push_back(PATTERN_HEADER_APG40AD);//"* AD-* TIME ?????? ???? *"
    headers.push_back(PATTERN_HEADER_APG40TW);//"* TW-* TIME ?????? ???? *"
    headers.push_back(PATTERN_HEADER_IOG20AT);//"* AT-* TIME ?????? ???? *"
    headers.push_back(PATTERN_HEADER_IOG20NVT);//"* NVT-* TIME ?????? ???? *"
    headers.push_back(PATTERN_SUBHEADER1);//"CLUSTER SESSION - "
    headers.push_back(PATTERN_SUBHEADER2);//"RESTRICTED CP SESSION"
    headers.push_back(PATTERN_SUBHEADER3);//"UNRESTRICTED CP SESSION"
    headers.push_back(PATTERN_SUBHEADER4);//"UNRESTRICTED CP SESSION - *"
    headers.push_back(PATTERN_SUBHEADER5);//"RESTRICTED CP SESSION - *"
    TRACE_OUT(trace, initiateHeaders, "");
}

void WinFIOLClient::initiateCharacters() {
    TRACE_IN(trace, initiateCharacters, "");
    charactersToSuppress.push_back(VT100_CLEAR_SCREEN_CURSOR_DOWN); //Esc[J
    TRACE_OUT(trace, initiateCharacters, "");
}

void WinFIOLClient::removeHeadersFromBuffer(std::string &buffer){
    TRACE_IN(trace, removeHeadersFromBuffer, "");

    int start = 0;
    int end = 0;

    bool found = false;
    bool headerFound = false;

    while(!found) {
        end = buffer.find("\r", start);

        if(end == -1) {
            break;
        }
        for(int j = 0; j < headers.size(); j++) { //Match against all header types
            if( strMatch( buffer.substr(start, (end-start)).c_str(), headers[j].c_str() ) ){
                TRACE_FLOW(trace, removeHeadersFromBuffer, "Header found: " << buffer.substr(start, (end-start)).c_str());
                buffer.erase(start, ((end-start)+2) ); //Remove header + \r\n
                headerFound = true;
                break;
            }
        }
        if (headerFound) {
            headerFound = false;//search for next header
        } else {
            start = (end + 2);
        }

    }

    TRACE_OUT(trace, removeHeadersFromBuffer, "Buffer:" << buffer.c_str());
}

//-----------------------------------------------------------------
bool rMatch(const char* s, int i, const char* p, int j)
{
   // s = to be tested ,    i = position in s
   // p = pattern to match ,j = position in p
   bool matched;
   int k;
   int sLen = strlen(s);
   int pLen = strlen(p);

   if ( pLen == 0 )
      return true;

   for (;;) {

      if ( i >= sLen && j >= pLen )
         return true;

      else if ( j >= pLen )
         return false;

      else if ( p[j] == '*' ) {
         k = i;
         if ( j >= pLen-1 )
            return true;

         for (;;) {
            matched = rMatch(s,k,p,j+1);
            if ( matched || (k >= sLen) )
               return matched;
            k++;
         }
      }
      else if ( (p[j]=='?' && i<sLen) || (toupper(p[j]) == toupper(s[i])) ) {
         i++;
         j++;
      }
      else
         return false;
   } // for
}


//-----------------------------------------------------------------
bool WinFIOLClient::strMatch(const char* szSource, const char* szPattern)
{
   return rMatch(szSource,0,szPattern,0);
}

void WinFIOLClient::removeStringFromBuffer(std::string &buffer, std::string stringToRemove){
    TRACE_IN(trace, removeStringFromBuffer, "Buffer in:\n" << buffer.c_str() << "stringToRemove:(" << stringToRemove.c_str() << ")");

    washStringFromNewlineCarriageReturn(stringToRemove);

    int start = 0;
    int end = 0;

    bool found = false;
    while(!found) {
        end = buffer.find("\r", start);

        if(end == -1) {
            TRACE_FLOW(trace, removeStringFromBuffer, "String not found!");
            break;
        }
        if ( (buffer.substr(start, (end-start)).compare(stringToRemove) == 0) ) {
            buffer.erase(start, ((end-start)+2) ); //Remove string + \r\n
            found = true;//Not expecting to find the string more than once
        }
        else {
            start = (end + 2);
        }

    }

    TRACE_OUT(trace, removeStringFromBuffer, "Buffer out:\n" << buffer.c_str());
}

std::string WinFIOLClient::getSyslogMessage(std::string messageType, std::string state) {

    TRACE_IN(trace, getSyslogMessage, "getSyslogMessage");

    std::string logMessage = messageType+" {"+ "\\\"state\\\":\\\""+state+"\\\""+",\\\"neId\\\":\\\""+neId+"\\\""+"}";
    std::string command = "logger -p local2.info -t DDCDATA \"" + logMessage + "\"";

    int ret = std::system(command.c_str());
    if(ret != 0) {
        TRACE_FLOW(trace, getSyslogMessage, "Failed to write log message");
    }

    TRACE_OUT(trace, getSyslogMessage, "getSyslogMessage: " << logMessage);
    return logMessage;
}

void WinFIOLClient::washStringFromNewlineCarriageReturn(std::string &str) {
    str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
}

std::string WinFIOLClient::getCurrentPrompt() { //Empty string if no prompt is found yet
    return currentPrompt;
}

void WinFIOLClient::initStream() {
    DataStream* ioStream = new DataStream(wfdriver);
    wfdriver->setStream(ioStream);
}

void WinFIOLClient::readOrderedAndSpontaneousPrintouts() {

    TRACE_IN(trace, readOrderedAndSpontaneousPrintouts, "");
    std::string response;
    std::string buffer;

    bool stopReading = false;
    while(expectedResponse > 0) {
        wfdriver->readData(response);

        TRACE_FLOW(trace, readOrderedAndSpontaneousPrintouts, "Data received from Node: " << response.c_str());

        if(response.find("SYSTEM RESTARTED") != std::string::npos) { //Special handling for SYSTEM RESTARTED
            systemRestarted = true;
            if(response.find(0x04) != std::string::npos){
                buffer += response;
                expectedResponse = 0;
                break;//printout found, break
            }
            else {
                buffer += response;
                stopReading = true;//Stop reading as soon as the (0x04) end of printout is read
            }
        }
        else if(stopReading && response.find(0x04) != std::string::npos) {
            buffer += response;
            expectedResponse = 0;
            break; //Special handling for SYSTEM RESTARTED, printout found
        }
        else {

            size_t pos = response.find(0x04);
            while( pos != std::string::npos)
            {
                expectedResponse--;
                pos =response.find(0x04, pos + 1);
            }
            buffer += response;
            TRACE_FLOW(trace, readOrderedAndSpontaneousPrintouts, "Expected Response count: " << expectedResponse);
        }
    }

    //Go through data and check for ordered and/or spontaneous printouts
    TRACE_FLOW(trace, readOrderedAndSpontaneousPrintouts, "Buffer Size: " << buffer.length());
    int begin = 0;
    for (size_t offset = buffer.find(0x04); offset != std::string::npos;
            offset = buffer.find(0x04, offset + 1))
    {
        TRACE_FLOW(trace, readOrderedAndSpontaneousPrintouts, "Offset: " << offset);
        std::string printout = buffer.substr(begin, (offset - begin));
        begin = offset +1;
        if((printout.find("TIME OUT") != std::string::npos) && (printout.find("END") == std::string::npos)){
        //found TIME OUT string without END string in the print out response
            TRACE_ERROR(trace, readOrderedAndSpontaneousPrintouts, "TIME OUT found!");
            continue;
        }
        else if(printout.find("SYSTEM RESTARTED") != std::string::npos) {
            respString += printout;
            connectionInterrupted = false;
            //sendControlChar(CONNECT_CHAR);
        }
        else {

                orderedPrintouts.push(printout);//Push printouts to a separate fifo queue to be fetched when asked for
        }
    }
    TRACE_OUT(trace, readOrderedAndSpontaneousPrintouts, "Printouts found: " << orderedPrintouts.size() );
}

void WinFIOLClient::clearVariables() {
	//Reset all variables
	isOrdered = true;
	isRspEnded = false;
	nodeRespHeader= "";
	enmUser = "";
	isAploc = false;
	currentPrompt = "";
	neId="";
	orderedCount = 0;
	expectedResponse = 0;
	systemRestarted = false;
	connectionInterrupted = false;
	autoConfirm = true;
	autoConfirmSent = false;
	autoConfirmReq = false;
	adNode = false;
	respString = "";
	autoConfirmPrompt = false;
	loggedOff = false;
	while(!orderedPrintouts.empty()) //Clear queue, start from zero
		orderedPrintouts.pop();
	while(!immediatePrintouts.empty()) //Clear queue, start from zero
		immediatePrintouts.pop();
	while(!returnQ.empty()) //Clear queue, start from zero
    	returnQ.pop_back();
}

void WinFIOLClient::suppressCharacters(std::string& data) {
    TRACE_IN(trace, suppressCharacters, "");

    // erase all ^M characters from response
    boost::erase_all(data, VT100_CARRIAGE_RETURN);

    for(int i = 0; i < charactersToSuppress.size() ;){
        TRACE_FLOW(trace, suppressCharacters, "Characters to search for: " << charactersToSuppress[i].c_str());
        int found = data.find(charactersToSuppress[i].c_str());
        if(found == std::string::npos) {
            i++;
            continue;
        }
        else {
            data.erase(found,charactersToSuppress[i].length()); //remove the characters
        }
    }

    if(data.find("ORDERED") == 0) {
        TRACE_FLOW(trace, suppressCharacters, "Handling extra lines after ORDERED printout");
        int checkEquality = data.compare("ORDERED\n\n"); 

        //logic to suppress newlines after ORDERED printout
        std::string orderedString = "ORDERED";
        int charToRemoveCount = 0;
        int startIndexForOrderedON = data.find("ORDERED\n\n"); //ORDERED printout in case of ORDERED ON
        if(checkEquality==0)
        {
	    data.erase(orderedString.length()+1,orderedString.length()+1);
        }

        if (startIndexForOrderedON != std::string::npos) { //condition for ORDERED ON
            startIndexForOrderedON = startIndexForOrderedON + orderedString.length();

            while (data[startIndexForOrderedON+1] == '\n') {
                charToRemoveCount++;
                startIndexForOrderedON++;
            }
            data.erase((data.find(orderedString)+orderedString.length()+1),charToRemoveCount-1) ;

        } else if (data.find('\n') == 0 && !(isOrdered)) { //condition for ORDERED OFF
            int startIndexForOrderedOFF = data.find('\n');

            if (startIndexForOrderedOFF != std::string::npos) {
                while (data[startIndexForOrderedOFF] == '\n') {
                    charToRemoveCount++;
                    startIndexForOrderedOFF++;
                }
                data.erase(0,charToRemoveCount);
            }
        }
    }

    TRACE_OUT(trace, suppressCharacters, "");
}

bool WinFIOLClient::isDualApg(std::string const &fullString) {
    if (fullString.length() >= dualAPG.length()) {
        return (0 == fullString.compare (fullString.length() - dualAPG.length(), dualAPG.length(), dualAPG));
    } else {
        return false;
    }
}

bool WinFIOLClient::isBladeCluster(std::string tokname) {
    return ((tokname.find(bcCluster) != std::string::npos) || (tokname.find(cpCluster) != std::string::npos));
}

bool WinFIOLClient::setBladeClusterNode(std::string tokname) {
    size_t pos ;
    size_t delpos;
    if (tokname.find(bcCluster) != std::string::npos) {
        delpos = tokname.rfind(bcCluster);
    } else {
        delpos = tokname.rfind(cpCluster);
    }
    if(tokname.find(neHeader) != std::string::npos) {
        pos = tokname.find(neHeader);
        neId = tokname.substr(pos+3, delpos-3);
    } else {
        neId = tokname.substr(0, delpos);
    }
    bladeName = bladeName + " -cp " + tokname.substr(delpos+2);
    TRACE_FLOW(trace, setBladeClusterNode, "Node Name for NE: " << neId);
    TRACE_FLOW(trace, setBladeClusterNode, "BladeName for NE: " << bladeName );
}

void WinFIOLClient::readHeader() {

    TRACE_IN(trace,readHeader, "");
    std::string response = "";

    while (wfdriver->readData(response)) {
        if(gotPrompt(response)) {
            TRACE_FLOW(trace, readHeader, "Found Prompt!");
            orderedPrintouts.push(response);
            break;
        } else {
            orderedPrintouts.push(response);
        }
    }

    TRACE_OUT(trace,readHeader, "");
}

//TODO: Alarm recognition if spontaneous printout shall be activated
/*bool WinFIOLClient::isPrintoutAlarm(std::string printout) {
    TRACE_IN(trace, isPrintoutAlarm, "");
    bool alarm = false;
    //if ( printout.compare(0, 10, "*** ALARM ") == 0) {
    if(printout.find("\n*** ALARM ") != std::string::npos) {
        //ALARM
        TRACE_FLOW(trace, isPrintoutAlarm, "*** ALARM found!");
        alarm = true;
    }
    TRACE_OUT(trace, isPrintoutAlarm, "");
    return alarm;
}*/
