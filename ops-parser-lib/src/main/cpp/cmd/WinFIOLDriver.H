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

#ifndef OPSWinFIOLDriver_H
#define OPSWinFIOLDriver_H

#include <grpcpp/grpcpp.h>
#include <grpcpp/client_context.h>
#include <chrono>
#include "proto/winfiolAxeMed.grpc.pb.h"

const int timeOut = 300; //seconds
const int responseTimeOut = 1800; //seconds

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientReader;
//using grpc::ClientAsyncReader; // TODO: Trying to get async stream working
//using grpc::CompletionQueue;
using winfiolAxeMed::WinFIOLAxeMediation;

using winfiolAxeMed::GenericRequest;
using winfiolAxeMed::GenericResponse;
using winfiolAxeMed::ConnectRequest;
using winfiolAxeMed::CommandRequest;
using winfiolAxeMed::CommandResponse;
using winfiolAxeMed::StreamMessage;
using winfiolAxeMed::SessionRequest;
using winfiolAxeMed::TerminalActionRequest;

class DataStream;

 /**
  * The WinFIOLDriver class, used for interaction with Winfiol Server API
  */
class WinFIOLDriver {
public:
    friend class DataStream;

    enum ctrlChr {RELEASE_CHAR = 1,
                  CONNECT_CHAR};

   WinFIOLDriver(std::string wfSession);
 /**
  * The WinFIOLDriver Constructor
  * @param channel
  *               GRPC channel created between Winfiol client and server.
  * @param clientName
  *               Name of client communicationg with server.
  */
    WinFIOLDriver(std::shared_ptr<Channel> winfiolChannel, std::string clientName, std::string wfSession);

 /**
  * The WinFIOLDriver Destructor
  */
   virtual ~WinFIOLDriver (); // New change done

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

    virtual Status connect(std::string neId, ConnectRequest::ApNodeSide nodeSide, 
                           ConnectRequest::ApNode node);

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
    virtual void sendData (std::string cmd/*, int readResp = 1*/);

    virtual bool readData(std::string &response);

  /**
   * This function initializes clientReader stream message.
   */
    //virtual std::unique_ptr<ClientAsyncReader<StreamMessage> > initStream (ClientContext& ctx, grpc::CompletionQueue& _queue, void *_tag); // TODO: Trying to get async stream working
    virtual std::unique_ptr<ClientReader<StreamMessage> > initStream (ClientContext& ctx);

  /**
   * This function sets the response stream.
   */
    virtual void setStream (DataStream* stream) { if (cmdResponse != NULL) delete cmdResponse; cmdResponse = stream; }

 /**
  * Send control character on Node.
  * true = ctrl+d (RELEASE)
  * false = ctrl+m (CONNECT)
  */
    virtual Status sendControlChar(int ctrlChar, int readResp = 0);

  /**
   * ENM User Name
   */
    virtual void setEnmUser(std::string enmU);

    /**
     Set deadline
    */
    virtual void setTimeout(ClientContext* ctx, int value);


private:

    std::unique_ptr<WinFIOLAxeMediation::Stub> stub;
    DataStream* cmdResponse;
    std::string sessionId;
    std::string clientId;
    std::string wfSessionId;
    std::string enmUser;
    //void* tag;             // TODO: Trying to get async stream working
    //CompletionQueue queue;
};

 /**
  * The DataStream class, perform read and write operation on the stream
  */
class DataStream {
    friend class WinFIOLDriver;
public:
    DataStream(WinFIOLDriver* client);
    bool read(std::string& response);
private:
    ClientContext ctx;
    //void* tag; // TODO: Trying to get async stream working
    //CompletionQueue queue;
public:
    //std::unique_ptr<ClientAsyncReader<StreamMessage> > dstream; // TODO: Trying to get async stream working
    std::unique_ptr<ClientReader<StreamMessage> > dstream;
};

#endif // OPSWinFIOLDriver_H
