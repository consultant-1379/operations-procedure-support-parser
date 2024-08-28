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

#ifndef CHA_DELSUBSCRIBER_H
#define CHA_DELSUBSCRIBER_H


#include <CHA_ModelClient.H>
#include <CHA_RoutingHandler.H>
#include <CHA_RoutingCase.H>
#include <CHA_DeviceModeProps.H>
#include <CHA_NLSCatalog.H>

#include <rw/cstring.h>
#include <rw/tpdlist.h>
#include <rw/tools/datetime.h>
//#include <eac_cri_association.H>
//#include <eac_sbi_subscriber.H>
//#include <eac_sbi_dr_subscription.H>




class  CHA_DelSubscriber : public CHA_ModelClient
{
public:
    // return codes
    enum ReturnCode {OKAY,
		     FAILED,
		     NOSUBSCRIBERS};

    CHA_DelSubscriber(){ pTrigger = NULL; }
    CHA_DelSubscriber(const RWCString& 		appN,
		      CHA_RoutingHandler* 	pRtHandler,
		      CHA_Model* 		pTrg,
		      CHA_DeviceModeProps*	pDevModProps);
    // Description:
    //     Constructor.
    // Parameters:
    //     appN			the application name
    //	   pRtHandler		a pointer to a routing handler, can be NULL
    //     pTrg			a pointer to a CHAModel object that will call
    //                  	this class' updateFrom() method regulary. Used
    //                  	when checking if a dev mode subscription shall
    //                  	be prolonged.
    //     pDevModProps		a pointer to a CHA_DeviceModeprops object

    virtual ~CHA_DelSubscriber();
    // Description:
    //     Destructor.

    ReturnCode startSubscription(/*/const EAC_CRI_Association* pAssoc,*/
				 const RWCString& 	    esName);
    // Description:
    //     Starts a subscription of delayed responses.
    // Parameters:
    //     pAssoc	a pointer to the assocication obj used for
    //                  command sending
    //     esName	the name of the external system
    // Return values:
    //     OK		the operation was successful
    //     FAILED       the operation failed

    ReturnCode prolongSubscription(/*/const EAC_CRI_Association* pAssoc,*/
				   const RWCString& 	      esName);
    // Description:
    //     Prolongs a subscription of delayed responses.
    // Parameters:
    //     pAssoc	a pointer to the assocication obj used for
    //                  command sending
    //     esName	the name of the external system
    // Return values:
    //     OK		the operation was successful
    //     FAILED       the operation failed

    // Added due TR HF21010
     void stopAllSubscription(); 
    // Description:
    //     Terminates all subscription of delayed responses.

//    void forgetSubscription();
    // Description:
    //     Drops the current subscription. It will not be
    //     terminated directly and will still be active till
    //     it reaches it's time limit.

//    ReturnCode stopSubscription();
    // Description:
    //     Terminates the current subscription of delayed responses.

    virtual void updateFrom(CHA_Model* model, void* pData);
    // Description:
    //     Called by the trigger object (see constructor) in order to
    //     initiate a check if a device mode subscription of delayed
    //     responses shall be prolonged.
    //
    //     Will also be called when routing information is changed in
    //     the delayed response routing case.
    //
    //     Not for use in the main program!

    virtual void detachFrom(CHA_Model* model);
    // Description:
    //     Not for use in the main program!
    
protected:
    
//    long makeDefaultSubscr(const EAC_CRI_Association* pAssoc = NULL,
//			   const char* esName = NULL);
    // Description:
    //     Makes a subscription of delayed responses using the routing
    //     information found in the current delayed routing case. If
    //     no routing case is available (no routing handler was given
    //     in the constructor) a subscription with this process as
    //     receiver will be set up.
    //
    //     This method is called by other meber functions when
    //     subscriptions are made.
    // Parameters:
    //     pAssoc	a pointer to the assocication obj used for
    //                  command sending
    //     esName	the name of the external system
    // Return value:
    //     A subscription ID. Only valid if > 0, otherwise an error
    //     has occured.    

    ReturnCode fillInSubscRcvrs(/*/EAC_SBI_DR_Subscription& subscr*/);
    // Description:
    //     Translates the current routing information (from the
    //     delayed routing case) into a subscription description
    //     handled by EA.
    //
    //     This method is called by the method makeDefaultSubscr()
    //     when subscriptions are made.
    // Parameters:
    //     subscr	a EAC_SBI_DR_Subscription object to fill with
    //                  information. 
    // Return values:
    //     OK			the operation was successful
    //     FAILED       	the operation failed
    //     NOSUBSCRIBERS	routing case was empty, the variable
    //                          routingCaseIsEmpty is set.

private:

     class subListData 
     {
     public:
       
       subListData() {}
       
       subListData(long subId, int assocId, RWDateTime time, RWCString esName)
       {
	 mySubId = subId;
	 myAssocId = assocId;
	 myUpdateTime = time;
	 myEsName = esName;
       }
       
       ~subListData() {}
       
       // Copy const.
       subListData(const subListData& sublistdata)
       {
	 mySubId = sublistdata.mySubId;
	 myAssocId = sublistdata.myAssocId;
	 myUpdateTime = sublistdata.myUpdateTime;
	 myEsName    = sublistdata.myEsName;
       }
       
       // Assignment opr.
       void operator=(const subListData& sublistdata)
       {
	 mySubId = sublistdata.mySubId;
	 myAssocId = sublistdata.myAssocId;
	 myUpdateTime = sublistdata.myUpdateTime; 
	 myEsName = sublistdata.myEsName;   
       }
       
       // Only the assoc of interst for us.
       
       int operator==(const subListData& sublistdata)
       {
	 return((sublistdata.myAssocId == myAssocId) && 
	 	 (sublistdata.myEsName  == myEsName));
       }
       
       long      mySubId;
       int       myAssocId;
       RWCString myEsName;

       RWDateTime myUpdateTime;
       
     };
 
    RWTPtrDlist<subListData> mySubscriptionList;
    subListData* tmpListData;
    RWDateTime       nextUpdate;

    RWCString 			applicationName;

    CHA_RoutingCase* 		pRoutingCase;
    CHA_DeviceModeProps*	pDeviceModeProps;
    
    CHA_Model* 			pTrigger;
    RWBoolean 			usingTrigger;

    RWTPtrDlist<CHA_AddressList> depOfList;

    RWBoolean 			routingCaseHasChanged;
    RWBoolean 			routingCaseIsEmpty;

    long                        mySubscId;	// identity of subscription

    RWDateTime 			endTime;	// end time of limited subsc
    RWDateTime 			prolongLimit;	// the time when to prolonge a
						// device mode subsc

    CHA_NLSCatalog nlsCat;
};


#endif
