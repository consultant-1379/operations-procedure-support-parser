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

#ifndef CHA_DELRESPHANDLER_H
#define CHA_DELRESPHANDLER_H

#include <CHA_Model.H>
#include <CHA_ModelClient.H>
#include <CHA_RoutingHandler.H>
#include <CHA_SeqDelRespReceiver.H>
#include <CHA_IPCSupervisor.H>
#include <CHA_NLSCatalog.H>

#include <rw/cstring.h>
#include <rw/tpslist.h>

// Sequence delayed response receiver status in CHA
enum CHA_SeqStatus
{
    IDLE=0,
    BUSY
};

// Element of the list 'sequence response receivers'. 
// This list is handled by CHA_DelRespHandler class
class CHA_ElemSeqRespList 
{ 
public :
    CHA_ElemSeqRespList(CHA_SeqDelRespReceiver* pSeqReceiver)
    { 
       pSeqDelRespReceiver = pSeqReceiver;
       isToDelete = FALSE;
       seqStatus = IDLE;
    }
    ~CHA_ElemSeqRespList() {
        if (pSeqDelRespReceiver != NULL) {
            delete pSeqDelRespReceiver;
            pSeqDelRespReceiver = NULL;
        }
    }
    CHA_ElemSeqRespList& operator=(const CHA_ElemSeqRespList& other)
    {
       pSeqDelRespReceiver = other.pSeqDelRespReceiver;
       isToDelete = other.isToDelete;
       seqStatus = other.seqStatus;      
       return *this;
    }
    RWBoolean operator==(const CHA_ElemSeqRespList& other) const
    {

       return((pSeqDelRespReceiver == other.pSeqDelRespReceiver) &&
 	      (isToDelete == other.isToDelete));
    }    
    CHA_SeqDelRespReceiver*   pSeqDelRespReceiver;
    RWBoolean                 isToDelete;
    CHA_SeqStatus	      seqStatus;
    
};


class CHA_DelRespHandler : public CHA_Model, public CHA_ModelClient
{
public:
    CHA_DelRespHandler(){}
    CHA_DelRespHandler(CHA_IPCSupervisor* pSup,
			const RWCString& appN,
			CHA_RoutingHandler* pRtHandler);
    // Description:
    //     Constructor.
    // Parameters:
    //     pSup			IN: the supervisor that calls all its
    //                          clients when there is something in the
    //                          IPC que.
    //     applicationName	IN: the name of this application.
    //     pRtHandler		IN: the routing handler, if it exsts


    virtual ~CHA_DelRespHandler();
    // Description:
    //     Destructor.


    virtual void updateFrom(CHA_Model* model, void* pData);
    // Description:
    //     Implementation of the method inherited from
    //     CHA_ModelClient. Called by CHA_SeqDelRespReceiver class. 
    
    virtual void detachFrom(CHA_Model* model);
    // Description:
    //     Implementation of the method inherited from
    //     CHA_ModelClient.
    

private:


    CHA_ElemSeqRespList* checkElemList(CHA_ElemSeqRespList* pElemInList);
    // Description:
    //     This method checks if an element is in the list.   
    // Parameters:
    //     pElemInList   a pointer to the element to be found
    // Return values:
    //     A pointer to the element found.

    void createIdleReceiver();
    // Description:
    //     This method checks if there is already an IDLE receiver. 
    //     If there is an IDLE receiver use it and remove the rest
    //     of IDLE receivers.  
    //     If there isn't an IDLE receiver create a new one.   


    CHA_IPCSupervisor*                 pIpcSupervisor; 
    RWCString                          applicationName;
    
    RWTPtrSlist<CHA_ElemSeqRespList>   seqRespReceiverList;
    CHA_RoutingHandler*                pRoutingHandler;

};
#endif

