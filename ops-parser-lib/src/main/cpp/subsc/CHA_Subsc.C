// RCS handling
// $Id: CHA_Subsc.C,v 24.0 1995/11/28 17:01:05 ehsgrap Rel $

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
//      1994-04-20 by EHS / Marie Moschna (qhsmosc@ehs.ericsson.se)

// REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_Subsc.C,v $
//      Revision 24.0  1995/11/28 17:01:05  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:50:21  17:50:21  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:50:59  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:48:39  09:48:39  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:39:43  08:39:43  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:59:04  10:59:04  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:11:44  20:11:44  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:14:04  14:14:04  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  13:06:00  13:06:00  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  15:13:26  15:13:26  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:39:25  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:13:03  14:13:03  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 12.0  95/02/06  16:23:51  16:23:51  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:55:14  cmcha
//      Made release PREIT, N L\ufffdnninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:09:13  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:35:58  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:57:22  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:29:05  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.2  1994/09/21  08:18:00  qhsmosc
//      Added new status CHA_SUBSC_SCHEDULED
//
//      Revision 6.1  1994/09/15  14:35:14  qhsmosc
//      Active at construction
//
//      Revision 6.0  1994/08/30  17:55:59  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.1  1994/08/26  09:55:12  qhsmosc
//      Added constructor with default routing to window
//
//      Revision 5.0  1994/08/16  07:54:54  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:46:24  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  08:01:19  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.1  1994/06/22  12:54:35  qhsmosc
//      Altered after preliminary UI-tests
//
//      Revision 2.0  1994/06/12  08:02:28  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.6  1994/05/20  11:32:27  qhsmosc
//      Purify
//
//      Revision 1.5  1994/05/13  09:49:29  qhsmosc
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
//	TB53_OZ 1995-11-28      J Grape (EHSGRAP)       RCS rev 24.0
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
// 	CHA_SBI_SPR_Subscription        database interface
//      EAC_SBI_Subscription
//      CHA_RoutingCase
//      CHA_SubscInterval



//**********************************************************************

#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_Subsc.H>
//TORF-241666
//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_Subsc", (char*)"C");

// Member functions, constructors, destructors, operators

//**********************************************************************

CHA_Subsc::CHA_Subsc()
:state(CHA_SUBSC_ACTIVE),
 name(),
 resultRouting(CHA_RT_SPONTANEOUS),
 externalSystem(),
 reportIdentity(5),
 subscId(0)

{
    ////TRACE_IN(trace, CHA_Subsc, "");
};

//**********************************************************************

CHA_Subsc::CHA_Subsc(RWCString windowName)
:state(CHA_SUBSC_ACTIVE),
 name(),
 resultRouting(CHA_RT_SPONTANEOUS),
 externalSystem(),
 reportIdentity(5),
 subscId(0)

{
    // Constructor to be used when window should be default routing.

    ////TRACE_IN(trace, CHA_Subsc, "");

    resultRouting.getAddressList(CHA_DT_WINDOW)->append(windowName);

};

//**********************************************************************

CHA_Subsc::CHA_Subsc(const CHA_Subsc& subscription)
{
    ////TRACE_IN(trace, CHA_Subsc-Copy, "");

    // Copy constructor

    state = subscription.state;
    name = subscription.name;
    schedule = subscription.schedule;
    resultRouting = subscription.resultRouting;
    externalSystem = subscription.externalSystem;
    reportIdentity = subscription.reportIdentity;
    subscId = subscription.subscId;
};

//**********************************************************************

CHA_Subsc::~CHA_Subsc()
{
};

//**********************************************************************

int CHA_Subsc::activate()
{
  //  EAC_SBI_Subscriber subscriber;
    int answer;

    ////TRACE_IN(trace, Activate, "");
/*
    if ((answer = subscriber.Resume_subscription(subscId)) != EAC_SBI_OK)
    {
        //  Something has gone astray, error handling
	return answer;
    };

    // Check wether the subscription is waiting or executing
    if (subscriber.Subscription_status(subscId) == EAC_SBI_ACTIVE)
	state = CHA_SUBSC_ACTIVE;
    else
	state = CHA_SUBSC_SCHEDULED;

    return EAC_SBI_OK;*/
};

//**********************************************************************

int CHA_Subsc::suspend()
{
  //  EAC_SBI_Subscriber subscriber;
    int answer;

    ////TRACE_IN(trace, Suspend, "");

   /* if ((answer = subscriber.Suspend_subscription(subscId)) != EAC_SBI_OK)
    {
        //  Something has gone astray, error handling
	return answer;
    };
    
  return EAC_SBI_OK;*/
  state = CHA_SUBSC_SUSPENDED;
};

//**********************************************************************

int CHA_Subsc::fetch(const long subId)
{
    CHA_SBI_SPR_Subscription subs;
    int answer;

    ////TRACE_IN(trace, fetch, "");

    // Save identity for wanted subscription before calling database.
    subscId = subId;

   /* if ((answer = subs.fetch(*this)) != EAC_SBI_OK)
    {
        //  Something has gone astray, error handling
	return answer;
    }
   return EAC_SBI_OK;*/
};

//**********************************************************************

int CHA_Subsc::store(const RWCString applName)
{
    CHA_SBI_SPR_Subscription subs;
    int answer;

    ////TRACE_IN(trace, store, "");

   /* if ((answer = subs.store(*this, applName)) != EAC_SBI_OK)
    {
        //  Something has gone astray, error handling
	return answer;
    };

    return EAC_SBI_OK;*/
};

//**********************************************************************

int CHA_Subsc::remove()
{
   // EAC_SBI_Subscriber subscriber;
    int answer;

    ////TRACE_IN(trace, remove, "");

   /* if ((answer = subscriber.Terminate_subscription(subscId)) != EAC_SBI_OK)
    {
        //  Something has gone astray, error handling
	return answer;
    }
    return EAC_SBI_OK;*/
};

//**********************************************************************

const CHA_SubscState& CHA_Subsc::getState() const
{
    ////TRACE_IN(trace, getState, "");

    return state;
};

//**********************************************************************

void CHA_Subsc::setState(CHA_SubscState stateIn)
{
    ////TRACE_IN(trace, setState, "");

    state = stateIn;
};

//**********************************************************************

void CHA_Subsc::setName(const RWCString& nameIn)
{
    ////TRACE_IN(trace, setName, "");

    name = nameIn;
};

//**********************************************************************

const RWCString& CHA_Subsc::getName() const
{
    ////TRACE_IN(trace, getName, "");

    return name;
};

//**********************************************************************

void CHA_Subsc::setInterval(const CHA_SubscInterval& subscInterval)
{
    ////TRACE_IN(trace, setInterval, "");

    schedule = subscInterval;
};

//**********************************************************************

const CHA_SubscInterval& CHA_Subsc::getInterval() const
{
    ////TRACE_IN(trace, getInterval, "");

    return schedule;
};

//**********************************************************************

void CHA_Subsc::setRoutingCase(const CHA_RoutingCase& routingcase)
{
    ////TRACE_IN(trace, setRoutingCase, "");

    resultRouting = routingcase;
};

//**********************************************************************

CHA_RoutingCase& CHA_Subsc::getRoutingCase()
{
    ////TRACE_IN(trace, getRoutingCase, "");

    return resultRouting;
};

//**********************************************************************

const CHA_RoutingCase& CHA_Subsc::getRoutingCase() const
{
    ////TRACE_IN(trace, getRoutingCase, "");

    return resultRouting;
};

//**********************************************************************

void CHA_Subsc::setExternalSystem(const RWCString& extSyst)
{
    ////TRACE_IN(trace, setExternalSystem, "");

    externalSystem = extSyst;
};

//**********************************************************************

const RWCString& CHA_Subsc::getExternalSystem() const
{
    ////TRACE_IN(trace, getExternalSystem, "");

    return externalSystem;
};


void CHA_Subsc::setReportIdentity(
    const RWTValOrderedVector<CHA_ReportIdentity>& repId)
{
    ////TRACE_IN(trace, setReportIdentity, "");

    reportIdentity = repId;
};

//**********************************************************************

const RWTValOrderedVector<CHA_ReportIdentity>&
CHA_Subsc::getReportIdentity() const
{
    ////TRACE_IN(trace, getReportIdentity, "");

    return reportIdentity;
};

//**********************************************************************

void CHA_Subsc::setSubscriptionId(const long & subId)
{
    ////TRACE_IN(trace, setSubscriptionId, "");

    subscId = subId;
};

//**********************************************************************

const long CHA_Subsc::getSubscriptionId() const
{
    ////TRACE_IN(trace, getSubscriptionId, "");

    return subscId;
};

//**********************************************************************

CHA_Subsc& CHA_Subsc::operator=(const CHA_Subsc& subscription)
{
    ////TRACE_IN(trace, operator=, "");

    state          = subscription.getState();
    schedule       = subscription.schedule;
    resultRouting  = subscription.resultRouting;
    externalSystem = subscription.getExternalSystem();
    reportIdentity = subscription.getReportIdentity();
    subscId        = subscription.getSubscriptionId();
    name           = subscription.getName();

    return *this;

};

//**********************************************************************

int CHA_Subsc::operator==(const CHA_Subsc& subscription) const
{
    int evalEquality = TRUE;

    ////TRACE_IN(trace, operator==, "");

    // Observe that NOT all values contained in a susbcription are
    // tested before two subscriptions are considered equal.
    // It is possible to add more tests, if needed!

    evalEquality = (subscId == subscription.getSubscriptionId());
    if (evalEquality != TRUE)
	return evalEquality;

    evalEquality = (name == subscription.getName());
    if (evalEquality != TRUE)
	return evalEquality;


    // Some testing over all the elements contained in the list
 /*       evalEquality = (reportIdentity == subscription.getReportIdentity());
       if (evalEquality != TRUE)
    	return evalEquality; */

    evalEquality = (state == subscription.getState());
    if (evalEquality != TRUE)
	return evalEquality;

    evalEquality = (externalSystem == subscription.getExternalSystem());
    if (evalEquality != TRUE)
	return evalEquality;

    return evalEquality;
};
