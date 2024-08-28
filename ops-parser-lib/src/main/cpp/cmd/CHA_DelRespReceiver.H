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

#ifndef CHA_DELRESPRECEIVER_H
#define CHA_DELRESPRECEIVER_H

#include <CHA_SpDelReceiver.H>
#include <CHA_NLSCatalog.H>

//#include <eac_cri_delayed_resp.H>

class CHA_DelRespReceiver : public CHA_SpDelReceiver
{

public:
    CHA_DelRespReceiver(){} 
    CHA_DelRespReceiver(CHA_IPCSupervisor* pSup,
			const RWCString& appN);
    // Description:
    //     Constructor.

    virtual ~CHA_DelRespReceiver();
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
    //     Implementation of the method inherited from
    //     CHA_SpDelReceiver

    virtual CHA_ResponseBuffer* createBuffer(const char* bufferString,
					     const char* command,
					     const char* esName);
    // Description:
    //     Implementation of the method inherited from
    //     CHA_SpDelReceiver 

    virtual CHA_ResponseBuffer* createAccumulatedBuffer();
    // Description:
    //     Implementation of the method inherited from
    //     CHA_SpDelReceiver 

    virtual int getResponseBuffer(RWCString& bufferStr);
    // Description:
    //     Implementation of the method inherited from
    //     CHA_SpDelReceiver
    
    virtual int completeResponse();
    // Description:
    //     Implementation of the method inherited from
    //     CHA_SpDelReceiver 
        
    virtual int interruptResponse();
    // Description:
    //     Implementation of the method inherited from
    //     CHA_SpDelReceiver 
    
private:
    
   // EAC_CRI_Delayed_Resp delResponse;
};

#endif

