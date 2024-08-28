// RCS handling
// $Id: CHA_SubscList.C,v 24.1 1996/03/19 09:49:33 qhssian Exp $

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
//	190 89-CAA 134 1521

// AUTHOR
//      1994-04-28 by EHS / Marie Moschna (qhsmosc@ehs.ericsson.se)

// REVISION
//	XM2S1
//	1995-09-07

// CHANGES
//      RCS revision history
//      $Log: CHA_SubscList.C,v $
//      Revision 24.1  1996/03/19 09:49:33  qhssian
//      Fixed activateSubscription, now calls activate-method.
//
//      Revision 23.0  1995/09/07  17:50:30  ehscama
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:51:05  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:48:50  09:48:50  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:39:49  08:39:49  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:59:12  10:59:12  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:11:52  20:11:52  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:14:16  14:14:16  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  13:06:08  13:06:08  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  15:13:42  15:13:42  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:39:32  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:13:14  14:13:14  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 12.0  95/02/06  16:24:01  16:24:01  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:55:25  cmcha
//      Made release PREIT, N L\ufffdnninge (XKKNICL).
//
//      Revision 10.1  1995/01/05  07:40:09  ehsgrap
//      Use of CHA_UserInfo instead of getpwuid(getuid())
//
//      Revision 10.0  1994/12/22  09:09:21  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:36:06  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:57:33  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:29:20  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:56:11  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.1  1994/08/26  09:56:18  qhsmosc
//      AddSubscription prepends to list instead of appends
//
//      Revision 5.0  1994/08/16  07:55:09  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:46:42  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  08:01:34  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.1  1994/06/22  12:56:02  qhsmosc
//      Altered after preliminary UI-tests
//
//      Revision 2.0  1994/06/12  08:02:40  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.5  1994/05/13  09:50:00  qhsmosc
//      Final version
//
//      Revision 1.4  1994/05/06  08:16:04  qhsmosc
//      Routing remains
//
//      Revision 1.3  1994/04/27  08:05:18  qhsmosc
//      Before new RCS-handling
//
//      Revision 1.2  1994/04/26  08:02:37  qhsmosc
//      First test version
//
//      Revision 1.1  1994/04/13  13:21:15  qhsmosc
//      Initial revision
//
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	XM2S1   1995-09-07      ehscama                 RCS rev 23.0
//	EC2_OZ  1995-08-01      Jan Sandquist (EHSJAASA)RCS rev 22.0
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
//	PREIT   1995-01-18      N L\ufffdnninge (XKKNICL)    RCS rev 11.0
//	TB2     1994-12-22      J Grape (EHSGRAP)       RCS rev 10.0
//	E       1994-10-24      ehscama                 RCS rev 9.0
//	D       1994-10-05      EHSCAMA                 RCS rev 8.0
//	R1C     1994-09-22      J Grape (EHSGRAP)       RCS rev 7.0
//	R1B     1994-08-30      J Grape (EHSGRAP)       RCS rev 6.0
//	R1A     1994-08-16      J Grape (EHSGRAP)       RCS rev 5.0
//	P1C     1994-07-18      J Grape (EHSGRAP)       RCS rev 4.0
//	P1B     1994-06-23      J Grape (EHSGRAP)       RCS rev 3.0
//	P1A     1994-06-12      J Grape (EHSGRAP)       RCS rev 2.0

// SEE ALSO
//      RWTValOrderedVector
//      CHA_Subsc

//**********************************************************************

#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_SubscList.H>
#include <CHA_UserInfo.H>
//TORF-241666
//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_SubscList", (char*)"C");

// Member functions, constructors, destructors, operators

//**********************************************************************

CHA_SubscList::CHA_SubscList(const RWCString & applNameIn)
: lastEvent(CHA_SubscList::NOTHING)
{
    //TRACE_IN(trace, CHA_SubscList, "");

    applName = applNameIn;

    CHA_UserInfo userInfo;
    user = userInfo.loginName();

   // processName = IPC_get_procname();
};

//**********************************************************************

CHA_SubscList::~CHA_SubscList()
{
    subscriptionList.clear();
};

//**********************************************************************

CHA_Subsc& CHA_SubscList::operator()(size_t i)
{
    //TRACE_IN(trace, operator(), "");

    return subscriptionList[i];
};

//**********************************************************************

CHA_Subsc CHA_SubscList::operator()(size_t i) const
{
    //TRACE_IN(trace, operator()const, "");

    return subscriptionList[i];
};

//**********************************************************************

size_t CHA_SubscList::entries() const
{
    //TRACE_IN(trace, entries, "");

    return subscriptionList.entries();
};

//**********************************************************************

RWBoolean CHA_SubscList::isEmpty() const
{
    //TRACE_IN(trace, isEmpty, "");

    return subscriptionList.isEmpty();
};

//**********************************************************************

int CHA_SubscList::createList()
{
    CHA_SBI_SPR_Subscription   subsckind;
    //EAC_SBI_Subscriber         subscriber;
    long                       subid = 0;
    int                        answer;

    //TRACE_IN(trace, CreateList, "");

   /* while ((subid = subscriber.Get_next_subscription_id( &subsckind,
							 applName,
							 user,
							 subid)) > 0)
    {
        CHA_Subsc* subscrip = new CHA_Subsc();

        if ((answer = subscrip->fetch(subid)) == EAC_SBI_OK)
        {
            subscriptionList.insert(*subscrip);
        }
	else
	{
	    // Something has gone wrong, error handling
	    delete subscrip;
	    return answer;
	};

	delete subscrip;
    };

    // Check to see if anything went wrong
    if (subid < 0) return subid;

    return EAC_SBI_OK;*/
};

//**********************************************************************

int CHA_SubscList::updateList()
{
    int answer;

    //TRACE_IN(trace, UpdateList, "");

    subscriptionList.clear();
    answer = createList();

    if (subscriptionList.entries() > 0)
    {
	announceEvent(CHA_SubscList::CHANGEDITEM, subscriptionList.at(0));
    }
    else
    {
        CHA_Subsc* subscrip = new CHA_Subsc();
	announceEvent(CHA_SubscList::CHANGEDITEM, *subscrip);
	delete subscrip;
    };

    return answer;
};

//**********************************************************************

int CHA_SubscList::removeRoutingToWindow()
{
    CHA_SBI_SPR_Subscription subscription;
   // EAC_SBI_Subscriber subscriber;
    int answer;
    //TRACE_IN(trace, RemoveRoutingToWindow, "");

   /* if ((answer = subscriber.Change_receiver(&subscription,
					     applName,
					     user,
					     EAC_SBI_PASSIVE,
					     processName))
	!= EAC_SBI_OK)
    {
        //  Something has gone astray, error handling
	return answer;
    };
    return EAC_SBI_OK;*/
};

//**********************************************************************

int CHA_SubscList::addSubscription(CHA_Subsc & subscription)
{
    int answer;
    //TRACE_IN(trace, AddSubscription, "");

  /*  if ((answer = subscription.store(applName)) != EAC_SBI_OK)
    {
        //  Something has gone astray, error handling
	return answer;
    };*/

    subscriptionList.prepend(subscription);

    announceEvent(CHA_SubscList::ADDEDITEM, subscription);
   // return EAC_SBI_OK;
};

//**********************************************************************

int CHA_SubscList::removeSubscription(const long subId)
{
    int  index = 0;
    int  size = 0;
    int  answer;
    CHA_Subsc removedSubsc;

    //TRACE_IN(trace, RemoveSubscription, "");

    // Find wanted subscription

    size = subscriptionList.entries();

    while ((index < size) &&
	   ((subscriptionList.at(index).getSubscriptionId()) != subId))
	index++;

    if (index < size)
    {
	/*if ((answer = subscriptionList.at(index).remove()) != EAC_SBI_OK)
	{
	    //  Something has gone astray, error handling
	    return answer;
	};*/
	removedSubsc = subscriptionList.at(index);
	subscriptionList.removeAt(index);
    };
    announceEvent(CHA_SubscList::REMOVEDITEM, removedSubsc);
   // return EAC_SBI_OK;
};

//**********************************************************************

int CHA_SubscList::changeSubscription(const long subId)
{
    int  index = 0;
    int  size = 0;
    int  answer;

    //TRACE_IN(trace, ChangeSubscription(subid), "");

    // Find wanted subscription
    size = subscriptionList.entries();
    while ((index < size) &&
	   ((subscriptionList.at(index).getSubscriptionId()) != subId))
	index++;

    if (index < size)
    {
	/*if ((answer = subscriptionList.at(index).store(applName)) != EAC_SBI_OK)
	{
	    //  Something has gone astray, error handling
	    return answer;
	};*/
    };
    announceEvent(CHA_SubscList::CHANGEDITEM, subscriptionList.at(index));
   // return EAC_SBI_OK;
};

//**********************************************************************

int CHA_SubscList::changeSubscription(const CHA_Subsc& subscription)
{
    int  index = 0;
    int  size = 0;
    int  answer;
    long subId = 0;

    //TRACE_IN(trace, ChangeSubscription(subscription), "");

    // Find wanted subscription
    size = subscriptionList.entries();
    subId = subscription.getSubscriptionId();
    while ((index < size) &&
	   ((subscriptionList.at(index).getSubscriptionId()) != subId))
	index++;

    if (index >=  size)
    {
	// Subscription does not exist error handling

        return -1;
    };

    // Move sent information till old subscription

    subscriptionList.at(index) = subscription;

   /* if ((answer = subscriptionList.at(index).store(applName)) != EAC_SBI_OK)
    {
	//  Something has gone astray, error handling
	return answer;
    };*/
    announceEvent(CHA_SubscList::CHANGEDITEM, subscriptionList.at(index));
   // return EAC_SBI_OK;
};
//**********************************************************************

int CHA_SubscList::activateAll()
{
   // EAC_SBI_Subscriber         subscriber;
    int                        size = 0;
    int                        answer;

    //TRACE_IN(trace, ActivateAll, "");

   /* if ((answer = subscriber.Resume_subscription(applName,
						 user)) != EAC_SBI_OK)
    {
        //  Something has gone astray, error handling
	//TRACE_FLOW(trace, CouldnotActivateAll, answer);
	return answer;
    };*/

    // Change state for all subscriptions to active
    size = subscriptionList.entries();
    for (int i = 0; i < size; i++)
	subscriptionList.at(i).setState(CHA_SUBSC_ACTIVE);

  //  return EAC_SBI_OK;
};

//**********************************************************************

int CHA_SubscList::activateSubscription(const long subId)
{
   // EAC_SBI_Subscriber    subscriber;
    int  answer;
    int  size;
    int index = 0;

    //TRACE_IN(trace, ActivateSubscription, subId);

  /*  if ((answer = subscriber.Resume_subscription(subId)) != EAC_SBI_OK)
    {
	//  Something has gone astray, error handling
	//TRACE_FLOW(trace, CouldnotActivate, answer);
	return answer;
    };*/

    // Find wanted subscription
    size = subscriptionList.entries();
    while ((index < size) &&
	   ((subscriptionList.at(index).getSubscriptionId()) != subId))
	index++;

    subscriptionList.at(index).activate();

    announceEvent(CHA_SubscList::CHANGEDITEM, subscriptionList.at(index));
   // return EAC_SBI_OK;
};

//**********************************************************************

int CHA_SubscList::suspendAll()
{
    int                        answer;
    int                        size = 0;
   // EAC_SBI_Subscriber         subscriber;

    //TRACE_IN(trace, SuspendAll, "");

  /*  if ((answer = subscriber.Suspend_subscription(applName,
						  user)) != EAC_SBI_OK)
    {
        //  Something has gone astray, error handling
	//TRACE_FLOW(trace, CouldnotSuspendAll, answer);
	return answer;
    };*/

    // Change state for all subscriptions to suspended
    size = subscriptionList.entries();
    for (int i = 0; i < size; i++)
	subscriptionList.at(i).setState(CHA_SUBSC_SUSPENDED);

  //  return EAC_SBI_OK;
};

//**********************************************************************

int CHA_SubscList::suspendSubscription(const long subId)
{
    int                        answer;
    int                        size;
    int                        index = 0;
 //  EAC_SBI_Subscriber         subscriber;

    //TRACE_IN(trace, SuspendSubscription, subId);

  /*  if ((answer = subscriber.Suspend_subscription(subId)) != EAC_SBI_OK)
    {
        //  Something has gone astray, error handling
	//TRACE_FLOW(trace, CouldnotSuspend, answer);
	return answer;
    };*/

    // Find wanted subscription
    size = subscriptionList.entries();
    while ((index < size) &&
	   ((subscriptionList.at(index).getSubscriptionId()) != subId))
	index++;

    subscriptionList.at(index).setState(CHA_SUBSC_SUSPENDED);

    announceEvent(CHA_SubscList::CHANGEDITEM, subscriptionList.at(index));
    //return EAC_SBI_OK;
};

//**********************************************************************

CHA_SubscList::Event CHA_SubscList::getLastEvent() const
{
    //TRACE_IN(trace, getLastEvent, "");

    return lastEvent;
};

//**********************************************************************

const CHA_Subsc& CHA_SubscList::getChangedSubsc() const
{
    //TRACE_IN(trace, getChangedSubsc, "");

    return changedSubsc;
};

//**********************************************************************

void CHA_SubscList::announceEvent(CHA_SubscList::Event evt,
				  const CHA_Subsc& subsc)
{
    //TRACE_IN(trace, announceEvent, evt << ", " << subsc.getSubscriptionId());

    lastEvent = evt;
    changedSubsc = subsc;
    changed();
};
