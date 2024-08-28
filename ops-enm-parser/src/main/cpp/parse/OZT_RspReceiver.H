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

#ifndef OZT_RSP_RECEIVER_H
#define OZT_RSP_RECEIVER_H

#include <OZT_CmdRspBuf.H>
#include <OZT_ErrHandling.H>
#include <CHA_ModelClient.H>
#include <CHA_SpontRepReceiver.H>
#include <CHA_ResponseReceiver.H>
#include <rw/defs.h>
#include <rw/cstring.h>

class OZT_RspReceiver: public CHA_ModelClient {
public:
    OZT_RspReceiver(OZT_CmdRspBuf* pCmdRspBuf,
                    CHA_ResponseReceiver* pImmReceiver,
                    CHA_ResponseReceiver* pDelReceiver,
                    CHA_ResponseReceiver* pSpontReceiver);
    // Description
    //     Constructor
    // Parameters
    //     pCmdRspBuf    IN: command response buffer
    //     pImmReceiver  IN: immediate response receiver
    //     pDelReceiver  IN: delayed response receiver
    //     pSpontReceiver IN: spontaneous report receiver
     OZT_RspReceiver(OZT_CmdRspBuf* pCmdRspBuf,
                    CHA_ResponseReceiver* pImmReceiver,
                    CHA_ResponseReceiver* pDelReceiver,
                    CHA_ResponseReceiver* pSpontReceiver,
                    RWBoolean             loggingOn
    
                    );   


    ~OZT_RspReceiver();
    // Description
    //     Destructor


    OZT_Result logOn();  // effectively making delayed response to be stored
    //  Description:
    //      For compatibility reason, this command effectively diables the
    //      reception of delayed or spontaneous responses by storing them 
    //      temporarily instead of delivering the response to the regular 
    //      command response buffer that is visible to the command file.
    //  Return values:
    //      TRUE    logOn is successful
    //      FALSE   logOn was interrupted by the user while this object was
    //              waiting for the end of a delayed response to complete.


    RWBoolean logOff();
    //  Description: 
    //      Enable the reception of delayed or spontaneour responses, if 
    //      there is any delayed or spontaneous response stored already, those 
    //      response will be flushed to the regular command response buffer 
    //      first. 
    //  Return values: 
    //      TRUE A delayed response is flushed 
    //      FALSE No delayed response is flushed


    void interrupt();
    //  Description:
    //      Interrupt. Only applicable when logOn() is executing.

#if TPF >= 400  
    virtual void updateFrom(CHA_Model* pModel, void*);
#else
    virtual void updateFrom(RWModel* pModel, void*);
#endif
    // Description
    //     

    virtual void detachFrom(CHA_Model* pModel);
    // Description
    //     
    RWBoolean flushStoredDelResp();
    //  Description: 
    //      Print all stored del. resp. and clear the buffer. 
    //      If a stored del. resp. is flushed the result is TRUE.
    
    void flushStoredSpontResp();
    //  Description: 
    //      Print all stored spont. resp. and clear the buffer.      

private:
    void updateFromImmReceiver();
    void updateFromDelReceiver();
    void updateFromSpontReceiver();

    OZT_CmdRspBuf        *pCmdRspBuf;
    CHA_ResponseReceiver *pImmReceiver;
    CHA_ResponseReceiver *pDelReceiver;
    CHA_ResponseReceiver *pSpontReceiver;

    RWBoolean             aCompleteRspStored;
    RWBoolean             tryingToLogOn;
    RWBoolean             receivingDelRsp;
    RWBoolean             receivingSpontRsp;
    RWBoolean             loggingOn;
    RWCString             storedDelRsp;
    RWCString             storedSpontRsp;
};

#endif
