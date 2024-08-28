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


#ifndef CHA_SPDELRECEIVER_H
#define CHA_SPDELRECEIVER_H

#include <CHA_ResponseReceiver.H>
#include <CHA_IPCSupervisor.H>
#include <CHA_NLSCatalog.H>

#include <rw/cstring.h>

//#include <eac_cri_connection.H>
//#include <eac_cri_association.H>
//#include <eac_cri_sp_rep.H>
//#include <eac_cri_command.H>

class CHA_SpDelReceiver : public CHA_ResponseReceiver
{

public:

    
    // states
    enum State {IDLE,
		RECEIVING};
    CHA_SpDelReceiver() {}    
    CHA_SpDelReceiver(CHA_IPCSupervisor* pSup,
			const RWCString& appN);
    // Description:
    //     Constructor.
    // Parameters:
    //     pSup		a pointer to the IPC supervisor.
    //     appN		the name of the application

    virtual ~CHA_SpDelReceiver();
    // Description:
    //     Destructor.

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

    virtual int receiveResponse() = 0;
    // Description:
    //     Start receiving responses through methods
    //     provided by EAC association object.
    //     Method is implemented in subclasses.
    
    virtual CHA_ResponseBuffer* createBuffer(const char* bufferStr,
					     const char* command,
					     const char* esName) = 0;
    // Description:
    //     Creates buffers for responses.
    //     Method is implemented in subclasses.

    virtual CHA_ResponseBuffer* createBuffer(const char* bufferStr,
					     const char* command,
					     const char* esName,
						   int   devId) = 0;
    // Description:
    //     Creates buffers for responses.
    //     Method is implemented in subclasses.
    
    virtual CHA_ResponseBuffer* createAccumulatedBuffer() = 0;
    // Description:
    //     Creates accumulated buffers for responses
    //     Method is implemented in subclasses.
    
    virtual int getResponseBuffer(RWCString& bufferStr) = 0;
    // Description:
    //     Receive responsebuffers from EAC association object.
    //     Method is implemented in subclasses.
    
    virtual int completeResponse() = 0;
    // Description:
    //     Decides if a reponse is complete
    //     trhough methods provided by EAC association object.
    //     Method is implemented in subclasses.
    
    virtual int interruptResponse() = 0;
    // Description:
    //     Interrupt responses trough methods
    //     provided by EAC association object.
    //     Method is implemented in subclasses.
    
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
    
protected:

    // In the constructor the association depends on the connection,
    // thus the connection must be DECLARED before the association,
    // since that will also define the constrution order.

    /*/EAC_CRI_Connection connection;
    EAC_CRI_Association association;
    EAC_CRI_Command command;*/
    
private:

    void checkNewResponse();
    // Description:
    //     Checks for new delayed responses when in IDLE mode.
    
    void readBuffers();
    // Description:
    //     Reads buffers from EA until the response  is complete or no
    //     more buffers are available at the moment.

    CHA_IPCSupervisor* pIpcSupervisor;
    RWCString applicationName;
    
    CHA_NLSCatalog nlsCat;
    State receptionState;

    const char* cmdString;
    const char* esName;
	  int   deviceId;
    
};

#endif



