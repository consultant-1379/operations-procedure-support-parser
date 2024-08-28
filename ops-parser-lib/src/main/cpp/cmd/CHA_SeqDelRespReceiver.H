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


#ifndef CHA_SEQDELRESPRECEIVER_H
#define CHA_SEQDELRESPRECEIVER_H


#include <CHA_ResponseReceiver.H>
#include <CHA_IPCSupervisor.H>
#include <CHA_NLSCatalog.H>

#include <rw/cstring.h>

//#include <eac_cri_connection.H>
//#include <eac_cri_association.H>
//#include <eac_cri_sp_rep.H>
//#include <eac_cri_command.H>
//#include <eac_cri_delayed_resp.H>

class CHA_SeqDelRespReceiver : public CHA_ResponseReceiver
{

public:

    // receiver states
    enum State {IDLE,
		RECEIVING};
    CHA_SeqDelRespReceiver(){}		
    CHA_SeqDelRespReceiver(CHA_IPCSupervisor* pSup,
			   const RWCString& appN);
    // Description:
    //     Constructor.
    // Parameters:
    //     pSup			IN: the supervisor that calls all its
    //                          clients when there is something in the
    //                          IPC que.
    //     applicationName	IN: the name of this application.

    virtual ~CHA_SeqDelRespReceiver();
    // Description:
    //     Destructor.

    virtual int receiveResponse();
    // Description:
    //     Implementation of the method inherited from 
    //     CHA_SpDelReceiver

    virtual CHA_ResponseBuffer* createBuffer(const char* bufferString,
					     const char* command,
					     const char* esName,
						   int   devId);
    // Description:
    // 	    Create buffer for responses
    
    virtual CHA_ResponseBuffer* createBuffer(const char* bufferString,
					     const char* command,
					     const char* esName);
    // Description:
    // 	   Create buffer for responses

    virtual CHA_ResponseBuffer* createAccumulatedBuffer();
    // Description:
    //     Creates accumulated buffers for responses
 
    virtual int getResponseBuffer(RWCString& bufferStr);
    // Description:
    //     Receive responsebuffers from EAC association object.
    
    virtual int completeResponse();
    // Description:
    //     Decides if a reponse is complete
    //     trhough methods provided by EAC association object.
        
    virtual int interruptResponse();
    // Description:
    //     Interrupt responses trough methods
    //     provided by EAC association object.

    virtual void cancelResponse();
    // Description:
    //     Implementation of the method inherited from
    //     CHA_ResponseReceiver 

    virtual void updateFrom(CHA_Model* model, void* pData);
    // Description:
    //     Implementation of the method inherited from
    //     CHA_ModelClient. Will call either checkNewResponse() or
    //     readBuffers() depending on the reception mode.

    virtual void detachFrom(CHA_Model* model);
    // Description:
    //     Implementation of the method inherited from
    //     CHA_ModelClient.

    virtual RWBoolean isLastInSequence() const;
    // Description:
    //     Returns TRUE if the response currently received is the
    //     last one in a sequence of delayed responses. For AXE this
    //     always TRUE, since you only get one delayed response per
    //     command. However, for S12 this is FALSE when the response
    //     signals RESULT FOLLOWS or REPORT FOLLOWS and becomes TRUE
    //     when the response signals LAST REPORT.
    //
    //     This method probably only gives reliable results just after
    //     a complete delayed response has been received.
  static void updateOZTWaitDlRsp(int OZTwaitDlRsp);
  static void updateOrderState(int ordered);
  static void updateSendState(int sendState);
  static  int waitDlRspFlag;
  static  int orderedFlag;
  static  int sendFlag;
    
protected:

    // In the constructor the association depends on the connection,
    // thus the connection must be DECLARED before the association,
    // since that will also define the constrution order.

  //  EAC_CRI_Connection connection;
  //  EAC_CRI_Association association;
  //  EAC_CRI_Command command;
      
private:

    void checkNewResponse();
    // Description:
    //     Checks for new delayed responses when in IDLE mode.
    
    void readBuffers();
    // Description:
    //     Reads buffers from EA until the response  is complete or no
    //     more buffers are available at the moment.

  //  EAC_CRI_Delayed_Resp delResponse;

    CHA_IPCSupervisor* pIpcSupervisor;
    RWCString applicationName;
    
    CHA_NLSCatalog nlsCat;
    State receptionState;

    const char* cmdString;
    const char* esName;
	  int   deviceId;
 

};

#endif

