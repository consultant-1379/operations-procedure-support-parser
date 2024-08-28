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

#ifndef CHA_RESPFWDRECEIVER_H
#define CHA_RESPFWDRECEIVER_H


#include <CHA_ResponseReceiver.H>
#include <CHA_ResponseBuffer.H>
#include <CHA_NLSCatalog.H>

#include <rw/cstring.h>
#include <rw/tpslist.h>


class CHA_ResponseFwdReceiver : public CHA_ResponseReceiver
{

public:
    CHA_ResponseFwdReceiver(){}
    CHA_ResponseFwdReceiver(CHA_ResponseType responseType);
    // Description:
    //     Constructor:  
    // Parameters:
    //	     responseType: the type of response that the recivier will forward
    
    virtual ~CHA_ResponseFwdReceiver();
    // Description:
    //     Destructor. 

    virtual void cancelResponse();
    // Description:
    //     If responce reception is in progress a request will be sent to
    //     the sending response reciever to cancel the response.


    virtual void updateFrom(CHA_Model* model, void* pData);
    // Description:
    //     This method is called by the response reciever and results in
    //     an attempt to read buffers from it.
    // Parameters:
    //     model		a pointer to the response reciever
    //     pData		not used

    virtual void detachFrom(CHA_Model* model);
    // Description:
    //     This method is called by the responsereciever when no more
    //     reception of data is expected.
    // Parameters:
    //     model		a pointer to the response reciever

    virtual const CHA_ResponseBuffer* getBuffer() const;
    // Description:
    //     To get the most recent part of a response.
    // Return value:
    //     A CHA_ResponseBuffer containing the response buffer.

    virtual const CHA_ResponseBuffer* getAccumulatedResponse() const;
    // Description:
    //     To get one buffer containing the concatenation of all
    //     response buffers of a response so far. When
    //     isCompleteResponse() returns TRUE this method will return
    //     the entire response.
    // Return value:
    //     A CHA_ResponseBuffer containing the accumulated responses.

    virtual RWBoolean isCompleteResponse() const;
    // Description:
    //     To find out if the last buffer of a response is available.
    // Return value:
    //     Returns TRUE if the last buffer in a response is available.

    virtual RWBoolean isNewResponse() const;
    // Description:
    //     To find out if the first buffer of a new response has arrived.
    // Return value:
    //     Returns true only when the first buffer of a response has
    //     arrived. When the second buffer has come this method will
    //     return FALSE.

    virtual RWBoolean isLastInSequence() const;
    // Description:
    //     Some response types have sequences of responses that belong
    //     together, e.g. delayed responses from S12. This method will
    //     tell whether a response is last in such a sequence or
    //     not.

private:

    void fwdFromList();
    // Description:
    //     Announces all responses in the list respToFwd that have been
    //     collected during reception of buffers from another
    //     receiver. (Only buffers from one receiver can be announced
    //     at a time).

  CHA_ResponseReceiver* pCurrentRespRcvr;     // a pointer to the
					      // response receiver
					      // that gave the last
					      // non stored response
					      // buffer 


  CHA_ResponseType myResponseType;	      // the response type of this
 					      // forwarder

  RWTPtrSlist<CHA_ResponseBuffer> respToFwd;	      // list of responses
					      // that can't be
					      // forwarded directly
  
};

#endif
