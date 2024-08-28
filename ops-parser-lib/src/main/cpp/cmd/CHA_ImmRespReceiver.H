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

#ifndef CHA_IMMRESPRECEIVER_H
#define CHA_IMMRESPRECEIVER_H


#include <CHA_ResponseReceiver.H>
#include <CHA_IPCSupervisor.H>
#include <CHA_ImmRespBuffer.H>
#include <CHA_NLSCatalog.H>

#include <rw/cstring.h>
#include <rw/tpdlist.h>

#include <WinFIOLClient.H>
//#include <eac_cri_im_resp.H>
#define RESP_NOT_ACCEPTED "NOT ACCEPTED"
#define RESP_PARTLY_EXECUTED "PARTLY EXECUTED"
#define RESP_INCOMPLETE "INCOMPLETE COMMAND"
#define RESP_FUNCTION_BUSY "FUNCTION BUSY"
#define RESP_SYNTAX_FAULT "SYNTAX FAULT"
#define RESP_CMD_UNKNOWN "COMMAND UNKNOWN"

// forward declaration
class CHA_CommandSender;


class CHA_ImmRespReceiver : public CHA_ResponseReceiver
{

public:

    // states
    enum State {IDLE,
		WAITING,
		RECEIVING};

    // return codes
    enum ReturnCode {OKAY,
                     NOT_ACCEPTED,
                     PARTLY_EXECUTED,
                     INCOMPLETE,
                     FUNCTION_BUSY,
                     NOT_AUTHORIZED,
                     FAILED};
    CHA_ImmRespReceiver():pIpcSupervisor(NULL) {}
    CHA_ImmRespReceiver(CHA_IPCSupervisor* pSup, CHA_CommandSender* pCmdS);
    // Description:
    //     Constructor. Will add itsellf as a dependent of the IPC supervisor.
    // Parameters:
    //     pSup			IN: an IPC supervisor
    //     pCmdS		IN: the command sender that initiates
    //                              response reception
    
    virtual ~CHA_ImmRespReceiver();
    // Description:
    //     Destructor. Will remove itself as dependent of the IPC supervisor.

    virtual void cancelResponse();
    // Description:
    //     If responce reception is in progress a request will be sent to
    //     the external system to cancel the response.

    void fwdResponse(const RWCString& resp, const RWCString& es, int devId);
    // Description:
    //     Will forward the response string "resp" as an immediate response.
    // Parameters:
    //     resp			IN: the response to be forwarded
    //     es			IN: the name of the ES, can be empty
    //     devId		IN: the current device Id

    void fwdResponse(const RWCString& resp, const RWCString& es);
    // Description:
    //     Will forward the response string "resp" as an immediate response.
    // Parameters:
    //     resp			IN: the response to be forwarded
    //     es			IN: the name of the ES, can be empty

    /*ReturnCode newCommand(const RWCString& cmd,
			  const RWCString& pmt,
			  const RWCString& es,
				int	   devId);*/
	ReturnCode newCommand(const RWCString& cmd,
				const RWCString& pmt,
				const RWCString& es,
				/*int	   devId,*/
				WinFIOLClient* wf);
    // Description:
    //     Initiates the reception of a new response by making the
    //     receiver create the first buffer of a response containing
    //     the command string and then start waiting for a
    //     EAC_CRI_Im_Resp object.
    // Parameters:
    //     wf			IN: WinFIOLClient pointer
    // Return values:
    //     OK		indicates success
    //     FAILED 	failure, the receiver was not in correct mode
    ReturnCode newCommand(WinFIOLClient* wf);

    // Description:
    //     Initiates the reception of a new response by making the
    //     receiver create the first buffer of a response containing
    //     the command string and then start waiting for a
    //     EAC_CRI_Im_Resp object.
    // Parameters:
    //     cmd			IN: the command string
    //     pmt			IN: the prompt to be echoed with the command
    //	   es                   IN: the name of the external system
    //     devId		IN: the device Id
    // Return values:
    //     OK		indicates success
    //     FAILED 	failure, the receiver was not in correct mode

    ReturnCode newCommand(const RWCString& cmd,
			  const RWCString& pmt,
			  const RWCString& es);
    // Description:
    //     Initiates the reception of a new response by making the
    //     receiver create the first buffer of a response containing
    //     the command string and then start waiting for a
    //     EAC_CRI_Im_Resp object.
    // Parameters:
    //     cmd			IN: the command string
    //     pmt			IN: the prompt to be echoed with the command
    //	   es                   IN: the name of the external system
    // Return values:
    //     OK		indicates success
    //     FAILED 	failure, the receiver was not in correct mode

   ReturnCode receiveResponse(WinFIOLClient* pResp);
    // Description:
    //     Will make the receiver start receiving buffers from
    //     pResp. The method newCommand must have been called first.
    // Parameters:
    //     pResp		the EAC_CRI_Im_Resp object to receive
    //                          buffers from
    // Return values:
    //     OK		indicates success
    //     FAILED 	failure, the receiver was not in correct mode

    ReturnCode receiveConfirmResponse(WinFIOLClient* pResp);
    // Description:
    //     Will read buffers from the confirmation
    //     response (pResp). Leaving receiving states unchanged afterwards.
    //     The response buffers will also be flushed. 
    // Parameters:
    //     pResp		the EAC_CRI_Im_Resp object to receive
    //                          buffers from
    // Return values:
    //     OK		indicates success
    //     FAILED 	failure, the receiver was not in correct mode

    void skipResponse();
    // Description:
    //     Will make the receiver stop waiting for input from EA and
    //     move to an idle state. This method is generally called by
    //     the command sender when the connection is lost.

    virtual void updateFrom(CHA_Model* model, void* pData);
    // Description:
    //     This method is called by the IPC supervisor and results in
    //     an attempt to read buffers from the EAC_CRI_Im_Resp object.
    // Parameters:
    //     model		a pointer to the IPC supervisor
    //     pData		not used

    virtual void detachFrom(CHA_Model* model);
    // Description:
    //     This method is called by the IPC supervisor when no more
    //     IPC communication is expected.
    // Parameters:
    //     model		a pointer to the IPC supervisor

    virtual void setApMode(RWBoolean isAPModeIn);
    // Description:
    //     This method is used by CHA_CommandSender to specify whether
    //     or not it is sending APG commands.
    // Parameters:
    //     isAPModeIn   TRUE when in APG mode.

    virtual CHA_ImmRespReceiver::ReturnCode getResponseCode();
    // Description:
    //     This is the mehtod to get response code 
    //     based on response received from Driver

private:

    void readBuffers(RWBoolean notifySender = TRUE, RWBoolean goIdle = TRUE);
    // Description:
    //     Does the actual attempt to read reasponse buffers from EA.
    // Parameters:
    //     notifySender		If TRUE (default) the command sender
    //                          will be notified when a response is
    //                          complete. 

    void flushResponseQue();
    // Description:
    //     Forwards all responses that could not be forwarded directly
    //     when fwdResponse() was called because the receiver was busy
    //     with another response.

    void readPrintouts();
    static void* readPrintoutsThread(void* x);
    void createDetachedReadThread();

    WinFIOLClient* wfClient;
    CHA_IPCSupervisor* pIpcSupervisor;
    CHA_CommandSender* pCommandSender;
    //EAC_CRI_Im_Resp* pImmResp;
    State receptionState;
    RWCString esName;
    RWCString command;
    int deviceId;
    RWTPtrDlist<CHA_ImmRespBuffer> responseQue;
    CHA_NLSCatalog nlsCat;
    RWBoolean pendingCancel;
    RWBoolean isAPMode;
    CHA_ImmRespReceiver::ReturnCode cmdRespCode;
    pthread_t pReadThread;
    pthread_attr_t detachedReadThreadAttr;
    RWBoolean isDoneProcessing;
};

#endif

