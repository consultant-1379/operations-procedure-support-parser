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

#include "WinFIOLDriver.H"
#include <string>
#include <trace.H>
//#include <chrono> // TODO: Trying to get async stream working
#include <boost/algorithm/string.hpp>

//**********************************************************************
static std::string trace ="WinFIOLDriver";
//**********************************************************************

WinFIOLDriver::WinFIOLDriver(std::string wfSession):
  cmdResponse (NULL),
  sessionId(""),
  clientId(""),
  enmUser(""),
  wfSessionId(wfSession)
{

}

WinFIOLDriver::WinFIOLDriver(std::shared_ptr<Channel> winfiolChannel,
                             std::string clientName,
                             std::string wfSession):
  stub(WinFIOLAxeMediation::NewStub(winfiolChannel)),
  cmdResponse (NULL),
  sessionId(""),
  clientId(clientName),
  enmUser(""),
  wfSessionId(wfSession)
{
    TRACE_IN(trace, WinFIOLDriver, "WinFIOLDriver ");

    TRACE_OUT(trace, WinFIOLDriver, "WinFIOLDriver===" <<wfSessionId );
}

std::string WinFIOLDriver::createSessionAsync() {


    TRACE_INFO(trace, createSessionAsync, "Session Id requested to Winfiol" );
    cmdResponse->dstream->WaitForInitialMetadata(); // TODO: Trying to get async stream working
    std::multimap<grpc::string_ref, grpc::string_ref>::const_iterator it =
                cmdResponse->ctx.GetServerInitialMetadata().find(wfSessionId);//create a property file
    if(it != cmdResponse->ctx.GetServerInitialMetadata().end()){
            sessionId= std::string(it->second.begin(), it->second.end());
            TRACE_INFO(trace, createSessionAsync, "Session Id received from Winfiol: "<<sessionId);
    }else{
            TRACE_ERROR(trace, createSessionAsync, "ERROR: No session metadata received! " );
            sessionId="-1";
    }

    return sessionId;
}

int WinFIOLDriver::terminateSession() {
    TRACE_IN(trace, terminateSession, "terminateSession() ");
    ClientContext ctx;
    GenericResponse response;
    GenericRequest request;
    request.set_sessionid(sessionId);
    setTimeout(&ctx,timeOut);
    int retStatus = 1;

    TRACE_INFO(trace, terminateSession, "Requested to terminate session");
    Status status = stub->TerminateSession(&ctx, request, &response);
    if(status.ok()) {
        TRACE_INFO(trace, terminateSession, "Successfully terminated the session:" <<sessionId);
        TRACE_FLOW(trace, terminateSession, "Successfuly terminated the session. " <<status.error_message());
    } else {
        TRACE_ERROR(trace, terminateSession, "Error " << status.error_message());
        retStatus = response.status();
    }

    delete cmdResponse; //Created in WinFIOLClient
    cmdResponse = NULL;

    TRACE_OUT(trace, terminateSession, "terminateSession() done" );
    return retStatus;
}

WinFIOLDriver::~WinFIOLDriver () {
}

Status WinFIOLDriver::connect(std::string neId, ConnectRequest::ApNodeSide nodeSide, ConnectRequest::ApNode node) {
    TRACE_IN(trace, connect, "WinFIOLDriver connect()");
    ClientContext ctx;
    GenericResponse response;
    ConnectRequest request;
    request.set_sessionid(sessionId);
    request.set_neid(neId);
    request.set_nodeside(nodeSide);
    request.set_node(node);
    ctx.AddMetadata(wfSessionId, sessionId);
    setTimeout(&ctx,timeOut);
    TRACE_INFO(trace, connect, "Connect Requested for Node:" << neId << " to WinFIOL with Session ID:"<< sessionId);

    Status status = stub->Connect(&ctx, request, &response);

    TRACE_OUT(trace, connect, "WinFIOLDriver connect()");
    return status;
}

int WinFIOLDriver::getConnectionStatus(){
    TRACE_IN(trace, getConnectionStatus, "WinFIOLDriver getConnectionStatus()");
    int ret = 0;
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext ctx;
    GenericRequest genReq;
    GenericResponse genResp;
    genReq.set_sessionid(sessionId);
    ctx.AddMetadata(wfSessionId, sessionId);
    setTimeout(&ctx,timeOut);
    Status constatus = stub->ConnectionStatus(&ctx, genReq, &genResp);

    if (constatus.ok()) {
        //TRACE_FLOW(trace, WinFIOLDriver, "Successfully fetch status from the node" <<neName <<" Message is =" <<constatus.error_message());
        ret = genResp.status() ;
        TRACE_OUT(trace, getConnectionStatus, "Connection status:" <<genResp.status());
    } else {
        TRACE_INFO(trace, getConnectionStatus, "Failed to fetch the connection status" <<genResp.status() <<" Message is =" <<constatus.error_message());
        terminateSession(); 
        ret = -1;
    }
    return ret;
}

std::unique_ptr<ClientReader<winfiolAxeMed::StreamMessage>>  WinFIOLDriver::initStream (grpc::ClientContext &ctx) {
//std::unique_ptr<ClientAsyncReader<winfiolAxeMed::StreamMessage>>  WinFIOLDriver::initStream (grpc::ClientContext &ctx, grpc::CompletionQueue &_queue, void *_tag) { // TODO: Trying to get async stream working

    TRACE_IN(trace, initStream, "Initstream");
    SessionRequest sessReq;
    sessReq.set_clientname(clientId);
    sessReq.set_enmuserid(enmUser);
    /*tag = _tag; // TODO: Trying to get async stream working
    std::unique_ptr<ClientAsyncReader<winfiolAxeMed::StreamMessage>> reader = stub->AsyncCreateAsyncSession(&ctx, sessReq, &_queue, &tag);

    //return stub->AsyncCreateAsyncSession(&ctx, sessReq, &_queue, (void*)1);*/
    TRACE_OUT(trace, initStream, "Initstream:user is ===" <<enmUser);
    return stub->CreateAsyncSession(&ctx, sessReq);
}

Status WinFIOLDriver::sendControlChar(int ctrlChar, int readResp) {
    TRACE_IN(trace, sendControlChar, "WinFIOLDriver sendControlChar");
    ClientContext ctx;
    TerminalActionRequest actionReq;
    GenericResponse genResp;
    ctx.AddMetadata(wfSessionId, sessionId);
    setTimeout(&ctx,timeOut);
    actionReq.set_sessionid(sessionId);

    if (ctrlChar == RELEASE_CHAR) {
        actionReq.set_action(TerminalActionRequest::RELEASE);
    } else {
        actionReq.set_action(TerminalActionRequest::CONNECT);
    }

    Status status = stub->ControlNeTerminal(&ctx, actionReq, &genResp);

    TRACE_OUT(trace, sendControlChar, "WinFIOLDriver sendControlChar");
    return status;
}

void WinFIOLDriver::sendData (std::string cmd/*, int readResp*/) {
    TRACE_IN(trace, sendData, "WinFIOLDriver sendData "<<cmd );
    ClientContext ctx;
    CommandResponse cmdResp;
    CommandRequest cmdReq;
    cmdReq.set_sessionid(sessionId);
    cmdReq.set_cmdinput(cmd);
    setTimeout(&ctx,responseTimeOut);

    TRACE_FLOW(trace, sendData, "Sending cmd to winfiol " << cmd);
    stub->SendCommand(&ctx, cmdReq, &cmdResp);
    TRACE_FLOW(trace, sendData, "Sent cmd to winfiol " << cmd);

    TRACE_OUT(trace, sendData, "WinFIOLDriver sendData");
}

bool WinFIOLDriver::readData(std::string &response) {
    TRACE_IN(trace, readData, "WinFIOLDriver readData");
    bool status = cmdResponse->read(response);
    TRACE_OUT(trace, readData, "WinFIOLDriver readData");
    return status;
}

void WinFIOLDriver::setEnmUser(std::string enmU) {
    TRACE_IN(trace, setEnmUser, "WinFIOLDriver setEnmUser enmU: " << enmU.c_str());
    enmUser = enmU;
    TRACE_OUT(trace, setEnmUser, "WinFIOLDriver setEnmUser enmUser: " << enmUser.c_str());
}

void WinFIOLDriver::setTimeout(ClientContext* ctx, int value) {
    TRACE_IN(trace, setTimeout, "WinFIOLDriver setTimeout");
    const auto start_time = std::chrono::system_clock::now();
    const std::chrono::system_clock::time_point deadline = start_time + std::chrono::seconds(value);
    ctx->set_deadline(deadline);
    TRACE_OUT(trace, setTimeout, "WinFIOLDriver setTimeout");
}

DataStream::DataStream(WinFIOLDriver *client)
{
    //tag = (void*)1;
    //dstream  = client->initStream(ctx, queue, tag); // TODO: Trying to get async stream working
    dstream  = client->initStream(ctx);
}

bool DataStream::read(std::string& response) {
    TRACE_IN(trace, DataStream, "DataStream::read");
    StreamMessage resp;
    /*bool ok; // TODO: Trying to get async stream working
    const auto start_time = std::chrono::system_clock::now();
    const std::chrono::system_clock::time_point deadline = start_time + std::chrono::milliseconds(1000);
    bool ret = queue.AsyncNext(&tag, &ok, deadline);
    //TRACE_FLOW(trace, WinFIOLDriver, "DataStream::ok: " << ok);*/
    //dstream->Read(&resp, &tag);
    bool readStatus = dstream->Read(&resp);
    response = resp.message();
    TRACE_OUT(trace, DataStream, "DataStream::read response:\n" << response.c_str());
    return readStatus;
}
