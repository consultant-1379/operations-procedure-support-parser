// RCS handling
// $Id: CHA_DelSubscriber.C,v 22.0.1.6 1996/01/05 14:13:10 ehsphad Exp $

//**********************************************************************

// COPYRIGHT
//      COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1994
//
//      The Copyright to the computer program(s) herein is the
//      property of Ericsson Hewlett-Packard Telecommunications AB,
//      Sweden.  The program(s) may be used and/or copied with the
//      written permission from Ericsson Hewlett-Packard
//      Telecommunications AB or in accordance with the terms and
//      conditions stipulated in the agreement/contract under which
//      the program(s) have been supplied.

// DOCUMENT NO
//	190 89-CAA 134 1517

// AUTHOR
//      1994-05-02 by EHS/PXE jan Grape (ehsgrap@ehs.ericsson.se)

// REVISION
//	EC2_OZ
//	1995-08-01

// CHANGES
//      RCS revision history
//      $Log: CHA_DelSubscriber.C,v $
//      Revision 22.0.1.6  1996/01/05 14:13:10  ehsphad
//      Changed all RWModel to CHA_Model.
//
//      Revision 22.0.1.5  1995/10/05 09:51:46  ehscama
//      Changed behaviour for subscriptions, keep old subscription
//      when changing association + name change of variables.
//
//      Revision 22.0.1.4  1995/09/16  19:20:27  etosad
//      /
//
//      Revision 22.0.1.3  1995/09/16  17:10:07  etosad
//      *** empty log message ***
//
//      Revision 22.0.1.2  1995/09/10  21:27:37  etosad
//      A lot of changes!
//
//      Revision 22.0.1.1  1995/09/07  07:06:22  etosad
//      A lot of changes!
//
//      Revision 22.0  1995/08/01  20:42:24  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:37:47  09:37:47  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:30:44  08:30:44  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:50:08  10:50:08  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.1  95/04/10  14:13:24  14:13:24  ehsgrap (Jan Grape (9 9073) VK/EHS/PXE)
//      Added some trace.
//
//      Revision 18.0  1995/03/17  20:02:21  cmcha
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:00:39  14:00:39  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  12:55:47  12:55:47  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  14:56:39  14:56:39  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:30:23  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  13:59:23  13:59:23  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 12.0  95/02/06  16:10:01  16:10:01  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:42:19  cmcha
//      Made release PREIT, N L�nninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  08:59:34  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.1  1994/12/08  10:27:12  ehsgrap
//      Replaced OK with OKAY
//
//      Revision 9.0  1994/10/24  21:25:42  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:45:21  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:19:57  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:47:48  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:40:39  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.2  1994/08/16  06:18:07  ehsgrap
//      Added some trace
//
//      Revision 4.1  1994/07/21  17:10:08  ehsgrap
//      Added some trace
//
//      Revision 4.0  1994/07/18  13:33:36  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:47:11  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  07:57:42  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.3  1994/05/18  09:30:55  ehsgrap
//      Added handling of device mode and routing cases.
//
//      Revision 1.2  1994/04/22  13:34:31  ehsgrap
//      Created local trace block.
//
//      Revision 1.1  1994/04/12  16:20:19  ehsgrap
//      Initial revision. No dev mode, no routing case.
//
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	EC2_OZ  1995-08-01      Jan Sandquist (EHSJAASA)RCS rev 22.0
//	EC1_OZ  1995-06-29      J Grape (EHSGRAP)       RCS rev 21.0
//	TB5_2_OZ1995-06-08      J Grape (ehsgrap)       RCS rev 20.0
//	TB5_1_OZ1995-04-13      J Grape (EHSGRAP)       RCS rev 19.0
//	TB51_OZ 1995-03-17      ehscama                 RCS rev 18.0
//	TB5_OZ  1995-03-16      ehscama                 RCS rev 17.0
//	TB6_B1C_B1995-03-10      N.Lanninge (XKKNICL)    RCS rev 16.0
//	TB6_B1C 1995-03-09      N.Lanninge (XKKNICL)    RCS rev 15.0
//	TB4_OZ  1995-02-25      J Grape (EHSGRAP)       RCS rev 14.0
//	CHUI_TB61995-02-15      N.Lanninge (XKKNICL)    RCS rev 13.5
//	TB3     1995-02-06      J Grape (EHSGRAP)       RCS rev 12.0
//	PREIT   1995-01-18      N L�nninge (XKKNICL)    RCS rev 11.0
//	TB2     1994-12-22      J Grape (EHSGRAP)       RCS rev 10.0
//	E       1994-10-24      ehscama                 RCS rev 9.0
//	D       1994-10-05      EHSCAMA                 RCS rev 8.0
//	R1C     1994-09-22      J Grape (EHSGRAP)       RCS rev 7.0
//	R1B     1994-08-30      J Grape (EHSGRAP)       RCS rev 6.0
//	R1A     1994-08-16      J Grape (EHSGRAP)       RCS rev 5.0
//	P1C     1994-07-18      J Grape (EHSGRAP)       RCS rev 4.0
//	P1B     1994-06-23      J Grape (EHSGRAP)       RCS rev 3.0
//	P1A     1994-06-12      J Grape (EHSGRAP)       RCS rev 2.0

//**********************************************************************


#include <CHA_DelSubscriber.H>
#include <CHA_Trace.H>
#include <CHA_LibGlobals.H>
#include <CHA_LibNLS.H>

#include <fstream>
#include <sys/stat.h>


/*
extern "C"
{
#include <cap_ipc.h>
}
*/

//**********************************************************************


//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_DelSubscriber", (char*)"C");

// a special subscription id used as return code, real ones are always > 0
const int CHA_DELSUB_NOID    = -20000; // failure, no subsc made
const int CHA_DELSUB_NOSUBSC = -20001; // there are no subscribers

const unsigned long waitingTime = 43200;  // 12 hours
const unsigned long timeToUpdate = 36000; // 10 hours
const unsigned long updateRate = 120; // every 2 mins

//**********************************************************************


CHA_DelSubscriber::CHA_DelSubscriber(const RWCString& 		appN,
				     CHA_RoutingHandler* 	pRtHandler,
				     CHA_Model* 		pTrg,
				     CHA_DeviceModeProps*	pDevModProps)
: applicationName(appN),
//  subscriber(),
//  subscDescr(),
  pRoutingCase(NULL),
  pDeviceModeProps(pDevModProps),
  pTrigger(pTrg),
  usingTrigger(FALSE),
  depOfList(),
  routingCaseHasChanged(TRUE),
  mySubscId(CHA_DELSUB_NOID),
  endTime(),
  prolongLimit(),
  nlsCat(CHA_LibNLSCatalog)
{
  //TRACE_IN(trace, CHA_DelSubscriber,
//	   appN << ", " << pRtHandler << ", " << pTrg << ", " << pDevModProps);

  if(pRtHandler != NULL) {

    // get the routing case and set external/internal routing
    // also observe the address lists for changes
    pRoutingCase = pRtHandler->getRoutingCase(CHA_RT_DELAYED);

    if(pRoutingCase != NULL) {

      //TRACE_FLOW(trace, CHA_DelSubscriber, "using routing case");

      CHA_AddressList* pAddrL;

      pRoutingCase->setExternallyRouted(CHA_DT_FILE, TRUE);
      pAddrL = pRoutingCase->getAddressList(CHA_DT_FILE);
      pAddrL->addDependent(this);
      depOfList.append(pAddrL);

      pRoutingCase->setExternallyRouted(CHA_DT_MAIL, TRUE);
      pAddrL = pRoutingCase->getAddressList(CHA_DT_MAIL);
      pAddrL->addDependent(this);
      depOfList.append(pAddrL);

      pRoutingCase->setExternallyRouted(CHA_DT_PRINTER, TRUE);
      pAddrL = pRoutingCase->getAddressList(CHA_DT_PRINTER);
      pAddrL->addDependent(this);
      depOfList.append(pAddrL);
    }
  }
  else
    pRoutingCase = NULL;


  /*if(subscDescr.Set_subscription_receiver(applicationName) != EAC_SBI_OK)
    {
      //TRACE_FLOW(trace, CHA_DelSubscriber, "Set_subscription_receiver FAILED");
    }
  else
    {
      //TRACE_FLOW(trace, CHA_DelSubscriber, "Set_subscription_receiver set to: " << applicationName << " , OKAY");
    }
*/
  // Let us be tiggered to update subscriptions
  if(pTrigger != NULL)
    pTrigger->addDependent(this);

  RWDateTime timeNow;
  nextUpdate = timeNow;
}


//**********************************************************************


CHA_DelSubscriber::~CHA_DelSubscriber()
{
    while(depOfList.entries() > 0) {
	depOfList.get()->removeDependent(this);
    }

    if(pTrigger != NULL)
      pTrigger->removeDependent(this);

    // Terminate all subscriptions
    while(mySubscriptionList.isEmpty() != TRUE)
      {
	tmpListData = mySubscriptionList.get();
      }
}


//**********************************************************************

CHA_DelSubscriber::ReturnCode CHA_DelSubscriber::startSubscription(
    					/*const EAC_CRI_Association* pAssoc,*/
    					const RWCString&           esName)
{
 // int newAssocId  =  pAssoc->Get_assoc_id();

 /* if (pAssoc != NULL)
    {
      //TRACE_IN(trace, startSubscription,
	//       "assoc=" << newAssocId << ", es=" << esName);

	  // Check if assoc. is already in the sub. list
	  subListData tmpData;
	  tmpData.myAssocId = newAssocId;
	  tmpData.myEsName  = esName;

	  if(mySubscriptionList.contains(&tmpData))
	    {
	      //TRACE_RETURN(trace, startSubscription, "OKAY - Allready subsrcibed to, found in list");
	      return OKAY;
	    }



    }
  else
    {
      //TRACE_RETURN(trace, startSubscription, "FAILED - no EAC_CRI_Association");
      return FAILED;
    }
*/

  // make sure that the subscription description has the correct
  // routing values

  // tell what we subscribe for
 /* subscDescr.Clear_criteria();
  if(subscDescr.Set_criteria(esName, pAssoc->Get_assoc_id()) != EAC_SBI_OK)
    {
      mySubscId = CHA_DELSUB_NOID;
      //TRACE_RETURN(trace, startSubscription, "FAILED - Error in call to  EAC_SBI_DR_Subscription::Set_criteria");
      return FAILED;
    }*/

  // Start the subscription
 /* mySubscId = subscriber.Initiate_subscription(&subscDescr,
					       waitingTime);

  if(!(mySubscId > 0))
    {
	//TRACE_RETURN(trace, startSubscription, "FAILED - Error in call to EAC_SBI_Subscriber::Initiate_subscription");
	return FAILED;
    }
*/

  // Add this new subsription to the subscription list
 /* RWTime tmpTime; // Current time + time to update
  tmpTime += timeToUpdate;

  tmpListData = new subListData(mySubscId,
				newAssocId,
				tmpTime, // current time + seconds to update
				esName);

  mySubscriptionList.append(tmpListData);

  tmpListData = NULL; // set to NULL, so not used incorrectly.



  //TRACE_RETURN(trace, startSubscription, "OKAY");
  return OKAY;*/
}




//**********************************************************************


CHA_DelSubscriber::ReturnCode CHA_DelSubscriber::prolongSubscription(
    					/*const EAC_CRI_Association* pAssoc,*/
    					const RWCString&           esName)
{

   /* if (pAssoc != NULL) {
        //TRACE_IN(trace, prolongSubscription,
	//     "assoc=" << pAssoc->Get_assoc_id() << ", es=" << esName);
    }
    else {
	//TRACE_IN(trace, prolongSubscription, "");
    }*/

    // don't make any unneccesary subscriptions
    if( (pDeviceModeProps->getWaitingTime()) <= 0 ) {

        mySubscId = CHA_DELSUB_NOID;
	//TRACE_RETURN(trace, startSubscription, "OKAY (no waiting time)");
	return OKAY;
    }

    long oldSubscId = mySubscId;

    // make sure that the subscription description has the correct
    // routing values
    if(routingCaseHasChanged) {

	//subscDescr.Clear_subscription_receiver();

	/*switch(fillInSubscRcvrs(subscDescr)) {
	    case OKAY:
	        routingCaseHasChanged = FALSE;
	        break;
	    case NOSUBSCRIBERS:
	        mySubscId = CHA_DELSUB_NOSUBSC;
		break;
	    case FAILED:
	    default:
	        mySubscId = CHA_DELSUB_NOID;
		return FAILED;*/
	//}
    }

    if(routingCaseIsEmpty)
	mySubscId = CHA_DELSUB_NOSUBSC;


   // if(pAssoc != NULL) {	// assumes that esName also != NULL

	// tell what we subscribe for
	/*subscDescr.Clear_criteria();
	if(subscDescr.Set_criteria(esName, pAssoc->Get_assoc_id()) != EAC_SBI_OK) {
	    mySubscId = CHA_DELSUB_NOID;
	    return FAILED;
	}*/
  //  }


    // Change the subscription
   /* mySubscId = subscriber.Change_subscription(mySubscId,
			    	      	     &subscDescr,
			    	            pDeviceModeProps->getWaitingTime());

    if( (mySubscId > 0) || (mySubscId == CHA_DELSUB_NOSUBSC) ) {

//	// Stop old subscription
//	subscriber.Terminate_subscription(oldSubscId);

	// Calculate the new end time and prolong limit
	endTime 		= pDeviceModeProps->getEndTime();
    	prolongLimit 	= pDeviceModeProps->getProlongEndTime();


	if( (!usingTrigger) && (pTrigger != NULL) ) {

	    //TRACE_FLOW(trace, startSubscription, "attaching to trigger");
	    pTrigger->addDependent(this);
	    usingTrigger = TRUE;
	}

 	//TRACE_RETURN(trace, startSubscription, "OKAY");
	return OKAY;
    }
    else {

	mySubscId = oldSubscId;	// Might as well keep the old one

	//TRACE_RETURN(trace, startSubscription, "FAILED");
	return FAILED;
    }*/


}


//**********************************************************************
/*

void CHA_DelSubscriber::forgetSubscription()
{
    //TRACE_IN(trace, forgetSubscription, "");

    mySubscId = CHA_DELSUB_NOID;

    if( (usingTrigger) && (pTrigger != NULL) ) {

	//TRACE_FLOW(trace, startSubscription, "detaching from trigger");
	pTrigger->removeDependent(this);
	usingTrigger = FALSE;
    }
}
*/
//**********************************************************************
// Added due to change the handlig of start and stop subscription, TR HF21010
void CHA_DelSubscriber::stopAllSubscription()
{
   //TRACE_IN(trace, stopAllSubscription, "");
  // Terminate all subscriptions
  while(mySubscriptionList.isEmpty() != TRUE)
    {
      tmpListData = mySubscriptionList.get();

/*      if( (subscriber.Terminate_subscription(tmpListData->mySubId)) == EAC_SBI_OK)
	{
	  //TRACE_FLOW(trace, CHA_DelSubscriber," Subscription: " << tmpListData->mySubId << " terminated");
	}
      else
	{
	  //TRACE_FLOW(trace, CHA_DelSubscriber," Failed to terminate subscription: " << tmpListData->mySubId);
	}*/
    }
   //TRACE_OUT(trace, stopAllSubscription, "");
}
//**********************************************************************

/*
CHA_DelSubscriber::ReturnCode CHA_DelSubscriber::stopSubscription()
{

  // don't try to stop a subscription that doesn't exist or is forgotten
    if(mySubscId <= 0) {

	//TRACE_RETURN(trace, stopSubscription, "OKAY (no subscription)");
	return OKAY;
    }

    if(subscriber.Terminate_subscription(mySubscId) != EAC_SBI_OK) {

	//TRACE_RETURN(trace, stopSubscription, "FAILED");
	return FAILED;
    }
    else {

	mySubscId = CHA_DELSUB_NOID;
	//TRACE_RETURN(trace, stopSubscription, "OKAY");
	return OKAY;
    }

    if( (usingTrigger) && (pTrigger != NULL) ) {

    //TRACE_FLOW(trace, stopSubscription, "detaching from trigger");
    pTrigger->removeDependent(this);
    usingTrigger = FALSE;
    }
}
*/
//**********************************************************************


/*
 The old update handler. Keep for now
void CHA_DelSubscriber::updateFrom(CHA_Model* model, void* pData)
{
    // if it was ptrigger that called, assume we shall prolongue a subscription.
    if(model == (CHA_Model*)pTrigger) {

 	// prolonge only if time is up and endTime is not reached
	RWTime rightNow;

	if (rightNow >= endTime) {

	    if( (usingTrigger) && (pTrigger != NULL) ) {

	    	//TRACE_FLOW(trace, updateFrom, "detaching from trigger");
		pTrigger->removeDependent(this);
		usingTrigger = FALSE;
	    }

	    return;
	}

	if(rightNow > prolongLimit) {

	    //TRACE_FLOW(trace, updateFrom, "prolonging dev mode del subscr");

	    startSubscription(NULL, "");

	    if(mySubscId <= 0)
		errorReporter.message(nlsCat.getMessage(NLS_DELSUB_PRLG_FAIL));
	}

	return;

    }
    else {			// The routing case has changed, a new
				// subscription has to be made

	//TRACE_FLOW(trace, updateFrom, "routing case has changed");
	routingCaseHasChanged = TRUE;

	// check subscription

	if(mySubscId > 0)
	{
	    //TRACE_FLOW(trace, updateFrom,
		       "changing delayed subscr");

	    // Get the subscription description
	    EAC_SBI_DR_Subscription* pSubscDescr =
						new EAC_SBI_DR_Subscription();

	    if(subscriber.Get_subscription(pSubscDescr, mySubscId) != EAC_SBI_OK)
	    {
		errorReporter.message(nlsCat.getMessage(NLS_DELSUB_DMTFAIL));
		delete pSubscDescr;
		return;
	    }

	    // Fill in the new routing information
	    pSubscDescr->Clear_subscription_receiver();
	    switch(fillInSubscRcvrs(*pSubscDescr)) {
	        case OKAY:
	            {
		        // Calculate new duration time
		        RWTime rightNow;
		        if(rightNow > endTime) {

			    // "forget" the subscription
			    mySubscId = CHA_DELSUB_NOID;
			    delete pSubscDescr;
			    return;
		        }
		        unsigned long timeDuration =
			      		endTime.seconds()-rightNow.seconds();

		        // change the subscription
		        mySubscId = subscriber.Change_subscription(mySubscId,
						       	         pSubscDescr,
						       	         timeDuration);
		        if(mySubscId <= 0)
			    errorReporter.message(nlsCat
					      .getMessage(NLS_DELSUB_DMTFAIL));
		    }
		    delete pSubscDescr;
		    return;

	        case FAILED:
		   errorReporter.message(nlsCat.getMessage(NLS_DELSUB_DMTFAIL));
		    delete pSubscDescr;
		    return;

	        case NOSUBSCRIBERS:
	        default:
		    subscriber.Terminate_subscription(mySubscId);
		    mySubscId = CHA_DELSUB_NOID;
		    delete pSubscDescr;
		    return;
	    }
	}

    }
}
*/

void CHA_DelSubscriber::updateFrom(CHA_Model* model, void* pData)
{
  //TRACE_IN(trace, updateFrom, model);

  // if it was ptrigger that called.
  if(model == (CHA_Model*)pTrigger)
    {
      RWDateTime rightNow;
      if(nextUpdate < rightNow)  //  Check if it's time to update the subscriptions
	{
	  nextUpdate.incrementSecond( updateRate ); // Set next time to check for updates
	  //TRACE_FLOW(trace, updateFrom, "Time is now: " << " " << rightNow);

	  if(mySubscriptionList.isEmpty() != TRUE)
	    {
	      //TRACE_FLOW(trace, updateFrom, "Number of subsriptions in the list: " << mySubscriptionList.entries());
	      //TRACE_FLOW(trace, updateFrom, "Next time for update is: "  << (mySubscriptionList.first())->myUpdateTime);
	    }
	  else
	    {
	      //TRACE_FLOW(trace, updateFrom, "The subscription list is empty");
	    }


	  // Check if we shall prolonge a subscription.
	  if(mySubscriptionList.isEmpty() != TRUE) // If empty list do nothing
	    {
	      while(rightNow > (mySubscriptionList.first())->myUpdateTime) // Update all subsr. which
		{                                                          // are due in time
		  // Update the subscription

		  // Get the subsription data from the list
		  tmpListData = mySubscriptionList.get();

		  /*TRACE_FLOW(trace, updateFrom, "Update subsription: mySubId=" << tmpListData->mySubId
			     << " myAssocId=" << tmpListData->myAssocId
			     << " myUpdateTime=" << tmpListData->myUpdateTime);*/


		  // Get the subscription description from the subscriber
		 /* EAC_SBI_DR_Subscription* pSubscDescr = new EAC_SBI_DR_Subscription(); // Creates an empty

		  if(subscriber.Get_subscription(pSubscDescr, tmpListData->mySubId) != EAC_SBI_OK)
		    {
		      //TRACE_FLOW(trace, updateFrom, "Error in call to EAC_SBI_Subscriber::Get_subscription");
		      if(tmpListData) delete tmpListData; // No point keeping it.
		      tmpListData = NULL;
		      delete pSubscDescr;
		      return;
		    }

		  // Prolong the subsription
		  tmpListData->mySubId = subscriber.Change_subscription(tmpListData->mySubId,
									pSubscDescr,
									waitingTime);


		  if(!(tmpListData->mySubId > 0))
		    {
		      //TRACE_FLOW(trace, updateFrom, "Error in call to EAC_SBI_Subscriber::Change_subscription");
		      if(tmpListData) delete tmpListData; // No point keeping it.
		      tmpListData = NULL;
		      delete pSubscDescr;
		      return;
		    }
*/

		 // delete pSubscDescr;

		  // Everything went well, put the subsr. data last in the subscription list
		  tmpListData->myUpdateTime = rightNow;
		  tmpListData->myUpdateTime.incrementSecond( timeToUpdate );

		  mySubscriptionList.append(tmpListData);

		  /*TRACE_FLOW(trace, updateFrom, "Subsription updated, new values: mySubId=" << tmpListData->mySubId
			     << " myAssocId=" << tmpListData->myAssocId
			     << " myUpdateTime=" << tmpListData->myUpdateTime);*/

		  tmpListData = NULL; // set to NULL, so not uesed incorrectly.

		} // while
	    } // if list empty

	} // If time to update
    }

  //TRACE_OUT(trace, updateFrom, model);
}


//**********************************************************************


void CHA_DelSubscriber::detachFrom(CHA_Model* model)
{
    //TRACE_IN(trace, detachFrom, model);

    if((CHA_Model*) model == pTrigger) {

	pTrigger = NULL;
	usingTrigger = FALSE;
    }
    else {
	//if(depOfList.remove((CHA_AddressList*) model) == NULL)
	    //TRACE_FLOW(trace, detachFrom, "could not remove from list");
    }
}


//**********************************************************************


CHA_DelSubscriber::ReturnCode CHA_DelSubscriber::fillInSubscRcvrs(
    /*EAC_SBI_DR_Subscription& subscr*/)
{
    //TRACE_IN(trace, fillInSubscRcvrs, "subscr");

    // if no routing case is available, set a default one and return quickly
    if(pRoutingCase == NULL)
    {
	routingCaseIsEmpty = FALSE;

	// make this process a receiver by default
	/*if(subscr.Set_subscription_receiver(applicationName) != EAC_SBI_OK)
	    return FAILED;
	else
	    return OKAY;*/
    }

    // follow the subscription data in the routing case

    // A flag indicating wether there are any subscribers or not
    RWBoolean subscriberExist = FALSE;

    // A flag indicating wether this process is a subscr rcvr or not
    RWBoolean procIsRcvr = FALSE;

    // A pointer to a list of destination addresses
    CHA_AddressList* pAddrL;

    // set FILE receivers
    pAddrL = pRoutingCase->getAddressList(CHA_DT_FILE);
    if(pAddrL->entries() > 0)
    {
	if(pRoutingCase->isExternallyRouted(CHA_DT_FILE))
	{
	    for(int i = 0; i < pAddrL->entries(); i++)
	    {
		// Create the file and set permissions, so that it is
		// owned by the user and writable by user and group.
                std::ofstream tmpFile((*pAddrL)[i], std::ios::in);
		if (tmpFile)
		{
		    // error, file exists! 
		    // Fail statement when file already exists
		}
		else
		{
		   // tmpFile.close();
		   // tmpFile.open("thefile.txt", std::ios::out);  // OK now
		   //Just a print statement if the file is not present and proceed to next line
		}
		if(tmpFile.good())
		{
		    // Set read/write permission as follows:
		    // rw rw r (user group others)
		    chmod((*pAddrL)[i],
			  S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
		}

		// make the file a receiver of delayed responses
		/*if(subscr.Set_subscription_receiver(applicationName,
						    0,
						    EAC_SBI_File_Append,
						    (*pAddrL)[i])
		   != EAC_SBI_OK)
		{
		    errorReporter.message(
			nlsCat.getMessage(NLS_F_DELSUB_FAILED)
			+ (*pAddrL)[i] + ".");
		}
		else
		    subscriberExist = TRUE; // at least ONE subscr rcvr*/
	    }
	}
	else		// internally routed
	    procIsRcvr = TRUE;
    }

    // set MAIL receivers
    pAddrL = pRoutingCase->getAddressList(CHA_DT_MAIL);
    if(pAddrL->entries() > 0)
    {
	if(pRoutingCase->isExternallyRouted(CHA_DT_MAIL))
	{
	    for(int i = 0; i < pAddrL->entries(); i++)
	    {
		// make the mail address a receiver of delayed responses
		/*if(subscr.Set_subscription_receiver(applicationName,
						    0,
						    EAC_SBI_Mail_Box,
						    (*pAddrL)[i])
		   != EAC_SBI_OK)
		{
		    errorReporter.message(
			nlsCat.getMessage(NLS_M_DELSUB_FAILED)
			+ (*pAddrL)[i] + ".");
		}
		else
		    subscriberExist = TRUE; // at least ONE subscr rcvr*/
	    }
	}
	else		// internally routed
	    procIsRcvr = TRUE;
    }

    // set PRINTER receivers
    pAddrL=pRoutingCase->getAddressList(CHA_DT_PRINTER);
    if(pAddrL->entries() > 0)
    {
	if(pRoutingCase->isExternallyRouted(CHA_DT_PRINTER))
	{
	    for(int i = 0; i < pAddrL->entries(); i++)
	    {
		// make the printer a receiver of delayed responses
		/*if(subscr.Set_subscription_receiver(applicationName,
						    0,
						    EAC_SBI_Printer,
						    (*pAddrL)[i])
		   != EAC_SBI_OK)
		{
		    errorReporter.message(
			nlsCat.getMessage(NLS_P_DELSUB_FAILED)
			+ (*pAddrL)[i] + ".");
		}
		else
		    subscriberExist = TRUE;	// at least ONE subscr rcvr*/
	    }
	}
	else		// internally routed
	    procIsRcvr = TRUE;
    }

    // check for routing to WINDOW, i.e. to this process
    pAddrL=pRoutingCase->getAddressList(CHA_DT_WINDOW);
    if(pAddrL->entries() > 0)
	procIsRcvr = TRUE;

    // set PROCESS receiver
    if(procIsRcvr)
    {
	/*if(subscr.Set_subscription_receiver(applicationName) != EAC_SBI_OK)
	    errorReporter.message(nlsCat.getMessage(NLS_DELSUB_FAILED));
	else
	    subscriberExist = TRUE;	// at least ONE subscr rcvr*/
    }

    if(subscriberExist)
    {
	routingCaseIsEmpty = FALSE;
	return OKAY;
    }
    else
    {
	routingCaseIsEmpty = TRUE;
	return NOSUBSCRIBERS;
    }
}


//**********************************************************************
