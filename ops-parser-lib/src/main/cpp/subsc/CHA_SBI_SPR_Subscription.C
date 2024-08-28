// RCS handling
// $Id: CHA_SBI_SPR_Subscription.C,v 22.0.1.1 1996/03/13 09:43:49 cmcha Exp $

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
//      $Log: CHA_SBI_SPR_Subscription.C,v $
//      Revision 22.0.1.1  1996/03/13 09:43:49  cmcha
//      Brach anch for HpP_UX-EUXPOW
//
//      Revision 24.0  95/11/28  17:00:57  17:00:57  ehsgrap (Jan Grape (9 9073) VK/EHS/VE)
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:50:07  17:50:07  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:50:51  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:48:27  09:48:27  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:39:35  08:39:35  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.2  95/06/02  07:35:43  07:35:43  ehsphad (Pierre Hagnestrand VK/EHS/PXE)
//      Changed making of subscription to not be deleted when eac_sbi_router
//      goes down.
//
//      Revision 19.1  1995/05/18  11:18:18  qhsjody
//      Ported to SunOS5.
//
//      Revision 19.0  1995/04/13  10:58:57  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:11:36  20:11:36  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:13:50  14:13:50  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  13:05:52  13:05:52  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  15:13:07  15:13:07  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:39:18  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:12:54  14:12:54  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 12.0  95/02/06  16:23:41  16:23:41  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:55:02  cmcha
//      Made release PREIT, N L\ufffdnninge (XKKNICL).
//
//      Revision 10.1  1995/01/05  07:29:31  ehsgrap
//      Use of CHA_UserInfo instead of getpwuid(getuid())
//
//      Revision 10.0  1994/12/22  09:09:05  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:35:48  cmcha
//      Made release E, ehscama.
//
//      Revision 8.1  1994/10/13  07:39:32  qhsmosc
//      If endtimelimit is passed the subscription should be suspended even if EA thinks it is PASSIVE_TIME
//
//      Revision 8.0  1994/10/05  08:57:11  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.1  1994/09/26  07:47:13  qhsmosc
//      Added code to save subscription even if reportId isn't specified, see storeReportid.
//
//      Revision 7.0  1994/09/22  13:28:49  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.1  1994/09/21  08:17:40  qhsmosc
//      Added new status CHA_SUBSC_SCHEDULED
//
//      Revision 6.0  1994/08/30  17:55:51  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.1  1994/08/26  09:57:15  qhsmosc
//      Added routing to other OS
//
//      Revision 5.0  1994/08/16  07:54:34  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.1  1994/08/16  07:02:35  qhsmosc
//      Before freeze, routing to other OS must be completed and tested later
//
//      Revision 4.0  1994/07/18  13:46:10  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  08:01:05  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:02:16  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.8  1994/05/31  08:18:02  ehsgrap
//      compilation on sun required sysent.h
//
//      Revision 1.7  1994/05/20  11:31:56  qhsmosc
//      Purify
//
//      Revision 1.6  1994/05/16  08:15:02  qhsmosc
//      Program test done
//
//      Revision 1.5  1994/05/13  09:47:41  qhsmosc
//      Final version
//
//      Revision 1.4  1994/05/06  08:16:04  qhsmosc
//      Routing remains
//
//      Revision 1.3  1994/04/27  08:03:44  qhsmosc
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
// 	EAC_SBI_SPR_Subscription        Information sent to/from database

//**********************************************************************

#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_SBI_SPR_Subscription.H>
#include <CHA_Subsc.H>
#include <CHA_SubscInterval.H>
#include <CHA_RoutingCase.H>
#include <SRMForwarder.H>
#include <CHA_UserInfo.H>
//TORF-241666
//#include <sysent.h>
#include <unistd.h>

//#ifdef SunOS5
#define SUNOS5_CONST const
//#else
//#define SUNOS5_CONST
//#endif

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_SBI_SPR_Subscription", (char*)"C");

// Member functions, constructors, destructors, operators

//**********************************************************************

CHA_SBI_SPR_Subscription::CHA_SBI_SPR_Subscription()
{
    //TRACE_IN(trace, CHA_SBI_SPR_Subscription, "");

    // Just so that EA can recognize this class when receiving spontaneous
    // reports by the EAC_CRI_Sp_Rep class

    //Set_class_name("EAC_SBI_SPR_Subscription");
};

//**********************************************************************

CHA_SBI_SPR_Subscription::~CHA_SBI_SPR_Subscription()
{
};

//**********************************************************************

int CHA_SBI_SPR_Subscription::fetch(CHA_Subsc& subsc)
{
   // EAC_SBI_Subscriber subscriber;
    int answer;

    //TRACE_IN(trace, fetch, "");

    // Read the identity for the subscription to fetch.
    long id = subsc.getSubscriptionId();

    // Read the subscription from the subscription database.
/*    if ((answer = subscriber.Get_subscription(this, id)) !=
	EAC_SBI_OK)

    {
        //  Something has gone astray, error handling
	//TRACE_FLOW(trace, SomethingWrongInGetSub, answer);
	return answer;
    };

    // Move found information from "this" to return object

    // Get state
    int state = subscriber.Subscription_status(id);
    if (state == EAC_SBI_ACTIVE)
    {
	subsc.setState(CHA_SUBSC_ACTIVE);
    }
    else if (state == EAC_SBI_PASSIVE_TIME)
    {
	subsc.setState(CHA_SUBSC_SCHEDULED);
    }
    else
    {
	subsc.setState(CHA_SUBSC_SUSPENDED);
    };
*/
    // Move registered report identities and external system
    answer = fetchReportid(subsc);
    if (answer < 0) return answer;

    // Move time and selected days
    answer = fetchTimes(subsc);
    if (answer < 0) return answer;

    // Move routing
    answer = fetchRouting(subsc);
    if (answer < 0) return answer;

    // If PASSIVE_TIME according to EA and time limit is passed the order
    // should be passive
    RWDateTime now;
    //TRACE_FLOW(trace, Now, now);
    //TRACE_FLOW(trace, EndTime, subsc.getInterval().getEndTimeInterval());
    if ((subsc.getState() == CHA_SUBSC_SCHEDULED) &&
	(subsc.getInterval().isEndDateDefined() == TRUE) &&
	(subsc.getInterval().getEndTimeInterval() < now ))
    {
	subsc.setState(CHA_SUBSC_SUSPENDED);
    }

  //  return EAC_SBI_OK;
};

//**********************************************************************

int CHA_SBI_SPR_Subscription::store(CHA_Subsc& subsc, const RWCString applName)
{
   // EAC_SBI_Subscriber subscriber;
    int answer;

    //TRACE_IN(trace, store, "");

    // Read identity for subscription to store.
    long id = subsc.getSubscriptionId();

    // Move information from parameter object to "this"

    // Move registered report identities, subscription name  and external system
    answer = storeReportid(subsc);
    if (answer < 0) return answer;

    // Move set time and selected days
    answer = storeTimes(subsc);
    if (answer < 0) return answer;

    // Move routing
    answer = storeRouting(subsc, applName);
    if (answer < 0) return answer;

    // Store the object in the subscription database
    if (subsc.getSubscriptionId() != 0)
    {
	// Subscription exists, update information
	//id = subscriber.Change_subscription(subsc.getSubscriptionId(), this);
	/*if (id < 1)
	{
	    // error handling
	    //TRACE_FLOW(trace, errorChangeSubsc, id);
	    return id;
	};*/
    }
    else
    {
	// New subscription, set identity
	/*id = subscriber.Initiate_subscription(this);
	if (id < 1)
	{
	    // error handling
	    //TRACE_FLOW(trace, errorInitSubsc, id);
	    return id;
	};*/
	subsc.setSubscriptionId(id);
    };

    // Set state in EA
    int state = subsc.getState();
    if ((state == CHA_SUBSC_ACTIVE) || (state == CHA_SUBSC_SCHEDULED))
    {
	//subscriber.Resume_subscription(id);
    }
    else
    {
	//subscriber.Suspend_subscription(id);
    };

    // Check status decided by EA and change shown status
  /*  int status = subscriber.Subscription_status(subsc.getSubscriptionId());
    if (status == EAC_SBI_ACTIVE)
	subsc.setState(CHA_SUBSC_ACTIVE);
    else if (status == EAC_SBI_PASSIVE_TIME)
	subsc.setState(CHA_SUBSC_SCHEDULED);
    else
	subsc.setState(CHA_SUBSC_SUSPENDED);

    return EAC_SBI_OK;*/
};

//**********************************************************************

int CHA_SBI_SPR_Subscription::fetchTimes(CHA_Subsc& subsc)
{
    int criteriaNr = 0;
    int iv, fy, fm, fd, fh, fmi, fs, ty, tm, td, th, tmi, ts;
 //   EAC_SBI_Day_Cat dayCategory;
    int dayCat;
    //RWTValHashSet<CHA_DayCategory> weekdays (hashDayCategory);
    RWTValHashSet<CHA_DayCategory, std::hash<int>, std::equal_to<int> > weekdays;
    CHA_SubscInterval times;
    RWBoolean fdDef, tdDef;

    //TRACE_IN(trace, fetchTimes, "");

    // Move timecriterias to subscInterval

   /* do
    { 
	if ((criteriaNr = Get_time_criteria(criteriaNr, iv, dayCategory,
					    fy, fm, fd, fh,
					    fmi, fs, ty, tm,
					    td, th, tmi, ts)) >= 0)
	{
	    // -1 implies that defaultvalue should be used
	    if (fh == -1) fh = 0;
	    if (fmi == -1) fmi = 0;
	    if (fs == -1) fs = 0;
	    if (th == -1) th = 23;
	    if (tmi == -1) tmi = 59;
	    if (ts == -1) ts = 0;
	    if (fy == -1) {fy = 0; fdDef = FALSE;} else fdDef = TRUE;
	    if (fm == -1) fm = 0;
	    if (fd == -1) fd = 0;
	    if (ty == -1) {ty = 0; tdDef = FALSE;} else tdDef = TRUE;
	    if (tm == -1) tm = 0;
	    if (td == -1) td = 0;

	    if (iv == 0)
	    {
		// Save Daycat and time of day (hour & mins only)
		dayCat = (int) dayCategory;
		if (dayCat > 0)
		{
		    // Convert the bitmap into a RWTValHashSet
		    if (dayCat >= EAC_SBI_HOLIDAY)
		    {
			weekdays.insert(CHA_DAYCAT_HOLIDAY);
			dayCat = dayCat - EAC_SBI_HOLIDAY;
		    };
		    if (dayCat >= EAC_SBI_BEFORE_HOLIDAY)
		    {
			weekdays.insert(CHA_DAYCAT_BEFORE_HOLIDAY);
			dayCat = dayCat - EAC_SBI_BEFORE_HOLIDAY;
		    };
		    if (dayCat >= EAC_SBI_WEEK_DAY)
		    {
			weekdays.insert(CHA_DAYCAT_WEEK_DAY);
			dayCat = dayCat - EAC_SBI_WEEK_DAY;
		    };
		    if (dayCat >= EAC_SBI_SATURDAY)
		    {
			weekdays.insert(CHA_DAYCAT_SATURDAY);
			dayCat = dayCat - EAC_SBI_SATURDAY;
		    };
		    if (dayCat >= EAC_SBI_FRIDAY)
		    {
			weekdays.insert(CHA_DAYCAT_FRIDAY);
			dayCat = dayCat - EAC_SBI_FRIDAY;
		    };
		    if (dayCat >= EAC_SBI_THURSDAY)
		    {
			weekdays.insert(CHA_DAYCAT_THURSDAY);
			dayCat = dayCat - EAC_SBI_THURSDAY;
		    };
		    if (dayCat >= EAC_SBI_WEDNESDAY)
		    {
			weekdays.insert(CHA_DAYCAT_WEDNESDAY);
			dayCat = dayCat - EAC_SBI_WEDNESDAY;
		    };
		    if (dayCat >= EAC_SBI_TUESDAY)
		    {
			weekdays.insert(CHA_DAYCAT_TUESDAY);
			dayCat = dayCat - EAC_SBI_TUESDAY;
		    };
		    if (dayCat >= EAC_SBI_MONDAY)
		    {
			weekdays.insert(CHA_DAYCAT_MONDAY);
			dayCat = dayCat - EAC_SBI_MONDAY;
		    };
		    if (dayCat >= EAC_SBI_SUNDAY)
		    {
			weekdays.insert(CHA_DAYCAT_SUNDAY);
			dayCat = dayCat - EAC_SBI_SUNDAY;
		    };

		    times.setDayCategory(weekdays);
		};

		RWTime dailyStartTime(fh, fmi, fs);
		RWTime dailyEndTime(th, tmi, ts);

		times.setDailyStartTime(dailyStartTime);
		times.setDailyEndTime(dailyEndTime);
	    }
	    else
	    {
		// Get time interval with date and time
		RWDate startDate(fd, fm, fy);
		RWTime startTime(startDate, fh, fmi, fs);
		RWDate endDate(td, tm, ty);
		RWTime endTime(endDate, th, tmi, ts);

		times.setStartTimeInterval(startTime);
		times.setEndTimeInterval(endTime);
		times.setStartDateDefined(fdDef);
		times.setEndDateDefined(tdDef);
	    };
	};
    } while (criteriaNr > 0);

    subsc.setInterval(times);

    return EAC_SBI_OK;*/
};

//**********************************************************************

int CHA_SBI_SPR_Subscription::fetchReportid(CHA_Subsc& subsc)
{
    int criteriaNr = 0;
    int critType;
    long low;
    long high;
    RWTValOrderedVector<CHA_ReportIdentity> repIdList;
    CHA_ReportIdentity repId;
    const char* ES_Name;
    const char* name;
    const char* spontId;

    //TRACE_IN(trace, fetchReportid, "");

    do
    {
	CHA_ReportIdentity repId;

	criteriaNr = Get_criteria_and_name(criteriaNr,
					   ES_Name,
					   critType,
					   low,
					   high,
					   spontId,
					   name);
	subsc.setExternalSystem(ES_Name);
	subsc.setName(name);

	/*switch (critType)
	{
	case EAC_SBI_NO_VALUE:
	    // No value returned
	    repId.setCriteriaType(NO_VALUE);
	    break;
	case EAC_SBI_LOW_ONLY:
	    // Only lower limit returned
	    repId.setLow(low);
	    repId.setCriteriaType(LOW_ONLY);
	    break;
	case EAC_SBI_RANGE:
	    // Interval returned
	    repId.setLow(low);
	    repId.setHigh(high);
	    repId.setCriteriaType(RANGE);
	    break;
	case EAC_SBI_STRING:
	    // String returned
	    repId.setString(spontId);
	    repId.setCriteriaType(STRING);
	    break;
	};
	repIdList.insert(repId);
*/
    } while (criteriaNr > 0);

    subsc.setReportIdentity(repIdList);

   // return EAC_SBI_OK;
};

//**********************************************************************

int CHA_SBI_SPR_Subscription::fetchRouting(CHA_Subsc& subsc)
{
    RWBoolean        window = FALSE;
    int receiverNr = 0;
    SUNOS5_CONST char* applName;
    SUNOS5_CONST char* userId;
    SUNOS5_CONST char* devName;
    SUNOS5_CONST char* nodeName;
  //  EAC_SBI_Dev_Type devType;
    unsigned int normalDelete, defaultSub;
    int prevReceiverNr;

    //TRACE_IN(trace, fetchRouting, "");

    // Move routing information to routingCase

    do
    {
        // Save previous receiver number before fetching a new
	prevReceiverNr = receiverNr;
	/*if ((receiverNr = Get_subscription_receiver(receiverNr,
						    applName,
						    userId,
						    devType,
						    devName,
						    nodeName,
						    normalDelete,
						    defaultSub)) >= 0)
	{
	    switch (devType)
	    {
	    case EAC_SBI_Unspecified:
		// Window process
		subsc.getRoutingCase().getAddressList(CHA_DT_WINDOW)
		    ->append(devName);
		window = TRUE;
		break;
	    case EAC_SBI_Printer:
		// Address to printer returned
		subsc.getRoutingCase().getAddressList(CHA_DT_PRINTER)
		    ->append(devName);
		break;
	    case EAC_SBI_Mail_Box:
		// Address to mail box returned
		subsc.getRoutingCase().getAddressList(CHA_DT_MAIL)
		    ->append(devName);
		break;
	    case EAC_SBI_File:
		// Address to file returned
		subsc.getRoutingCase().getAddressList(CHA_DT_FILE)
		    ->append(devName);
		break;
	    case EAC_SBI_File_Append:
		// Address to file returned
		subsc.getRoutingCase().getAddressList(CHA_DT_FILE)
		    ->append(devName);
		break;
	    case EAC_SBI_External_System:
		// Address to other OS returned

		// Check that the receiver in the subscription db
		// matches the one in ESS PDB map.
		// If they don't match, change the receiver process
		// name in subscription db.
		{
		    SUNOS5_CONST char* dummyApplName;
		    SUNOS5_CONST char* dummyUser;
		    SUNOS5_CONST char* forwarderProcess;
		    SUNOS5_CONST char* forwarderHost;
		    SUNOS5_CONST char* dummyNode;
		    EAC_SBI_Subscriber         subscriber;
		    EAC_SBI_Notification_Receiver dummyNotiRec;
		    unsigned int dummyNormDel, dummyDefSub;
		    if (Get_subscription_receiver(prevReceiverNr,
						  dummyApplName,
						  dummyUser,
						  forwarderProcess,
						  forwarderHost,
						  dummyNode,
						  dummyNotiRec,
						  dummyNormDel,
						  dummyDefSub) >= 0)
		    {
			SRMForwarder forw;
			const char * currentForwProc =
			    forw.getServerName(devName);
			if (currentForwProc)
			{
			    subsc.getRoutingCase().getAddressList(CHA_DT_OS)
				->append(devName);

			    // Get state
			    int state = subsc.getState();
			    if (state == CHA_SUBSC_ACTIVE)
			    {
				state = EAC_SBI_ACTIVE;
			    }
			    else
			    {
				state = EAC_SBI_PASSIVE;
			    };
			    if (strcmp(forwarderProcess, currentForwProc))
				(void) subscriber.Change_receiver
				    (subsc.getSubscriptionId(),
				     state,
				     (const char *) forwarderProcess,
				     currentForwProc,
				     forwarderHost,
				     forwarderHost,
				     (const char *) 0,
				     (const char *) 0,
				     devName);
			}
			else
			{
			    // The OS (devName) isn't any longer defined
			    // in the ESS_CHGI map, and/or PDB err.
			    // Delete the receiver.
			    (void) subscriber.Change_receiver
				(subsc.getSubscriptionId(),
				 EAC_SBI_DELETED,
				 (const char *) forwarderProcess,
				 (const char *) forwarderProcess,
				 forwarderHost,
				 forwarderHost,
				 (const char *) 0,
				 (const char *) 0,
				 devName);
			    if (forw.getErrNumber() > 0)
			    {
				// Error in reading map
				//TRACE_FLOW(trace, "SomethingWrongOS",
					   forw.getErrNumber());
				//TRACE_FLOW(trace, "SomethingWrongOS	", devName);
			    }
			}
		    }
		}
		break;
	    default:
		// Something strange is returned
		//TRACE_FLOW(trace, "SomeStrangeRoutingType", devType);
		//TRACE_FLOW(trace, "SomeStrangeRoutingName", devName);
		break;
	    };

	};*/
    } while (receiverNr > 0);

    if (window == TRUE)
    {
 	// Change the the receiving process to the current one
 	SUNOS5_CONST char * applicationName;
 	SUNOS5_CONST char * user_id;
 	SUNOS5_CONST char * oldProcessName;
 	SUNOS5_CONST char * oldHostName;
	SUNOS5_CONST char * oldNodeName;
 	//EAC_SBI_Subscriber subscrib;
 	//EAC_SBI_Notification_Receiver notificationReceiver;
 	unsigned int normal_delete, default_sub;

 	/*if (Get_subscription_receiver(0,
 				      applicationName,
 				      user_id,
 				      oldProcessName,
 				      oldHostName,
 				      oldNodeName,
				      notificationReceiver,
 				      normal_delete,
 				      default_sub) >= 0)
 	{
 	    char hostName[EAC_HOST_NAME_LEN + 1];
	    RWCString processName = IPC_get_procname();

	    //TRACE_FLOW(trace, applName, applName);
	    //TRACE_FLOW(trace, processName, processName);
 	    if (gethostname(hostName,
 			    EAC_HOST_NAME_LEN + 1) == 0)
 	    {
		subscrib.Change_receiver(subsc.getSubscriptionId(),
 				         EAC_SBI_ACTIVE,
 					 oldProcessName,
					 processName.data(),
					 oldHostName,
 					 hostName);
 	    };
 	};
    };
    return EAC_SBI_OK;*/
}
}

//**********************************************************************

int CHA_SBI_SPR_Subscription::storeReportid(const CHA_Subsc subsc)
{
    RWTValOrderedVector<CHA_ReportIdentity> repIdList;
    CHA_ReportIdentity repId;
    int numId;
   /// int r = EAC_SBI_OK;

    //TRACE_IN(trace, storeReportid, "");

    repIdList = subsc.getReportIdentity();
    numId = repIdList.entries();

  /*  for (int i = 0; i < numId; i++)
    {
	repId = repIdList(i);
	switch (repId.getCriteriaType())
	{
	case EAC_SBI_NO_VALUE:
	    // No value returned, use only ordername
	    r = Set_criteria_and_name(subsc.getExternalSystem().data(),
				      subsc.getName().data());
	    break;
	case EAC_SBI_LOW_ONLY:
	    // Only lower limit to be saved
	    r = Set_criteria_and_name(subsc.getExternalSystem().data(),
				      repId.getLow(),
				      subsc.getName().data());
	    break;
	case EAC_SBI_RANGE:
	    // Interval to be saved
	    r = Set_criteria_and_name(subsc.getExternalSystem().data(),
				      repId.getLow(),
				      repId.getHigh(),
				      subsc.getName().data());
	    break;
	case EAC_SBI_STRING:
	    // String to be saved
	    r = Set_criteria_and_name(subsc.getExternalSystem().data(),
				      repId.getString().data(),
				      subsc.getName().data());
	    break;
	};
    };

    if (numId == 0)
	// No reportIds stored, use only ordername
	r = Set_criteria_and_name(subsc.getExternalSystem().data(),
				  subsc.getName().data());


    return r;*/
};

//**********************************************************************

int CHA_SBI_SPR_Subscription::storeTimes(const CHA_Subsc subsc)
{
    RWCString startTime;
    RWCString startDate;
    RWCString endTime;
    RWCString endDate;
    int fy, fm, fd, fh, fmi, ty, tm, td, th, tmi;
   // EAC_SBI_Day_Cat dayCategory;
   // int DC = EAC_SBI_DONT_CARE;
    int dayCat = 0;
    int dayCatAlways = 0;
   // int r = EAC_SBI_OK;

    //TRACE_IN(trace, storeTimes, "");

    CHA_SubscInterval schedule = subsc.getInterval();

    if (schedule.isStartDateDefined())
    {
	// A time and date interval is set

	RWDateTime startDate (subsc.getInterval().getStartTimeInterval());
	RWDateTime endDate (subsc.getInterval().getEndTimeInterval());

	// Move information to variables understood by EA

	fy = startDate.year();
	fm = startDate.month();
	fd = startDate.dayOfMonth();
	ty = endDate.year();
	tm = endDate.month();
	td = endDate.dayOfMonth();

	fh = subsc.getInterval().getStartTimeInterval().hour();
	fmi = subsc.getInterval().getStartTimeInterval().minute();
	th = subsc.getInterval().getEndTimeInterval().hour();
	tmi = subsc.getInterval().getEndTimeInterval().minute();

	// Set time criterias

	//r = Set_time_criteria(fy, fm, fd, fh, fmi, DC,
	//		      ty, tm, td, th, tmi, DC);
    };

    // Convert DayCategory into a single value, bitmap
  /*  if (subsc.getInterval().getDayCategory().contains(CHA_DAYCAT_HOLIDAY))
	dayCat = dayCat + EAC_SBI_HOLIDAY;
    if (subsc.getInterval().getDayCategory().contains(CHA_DAYCAT_BEFORE_HOLIDAY))
	dayCat = dayCat + EAC_SBI_BEFORE_HOLIDAY;
    if (subsc.getInterval().getDayCategory().contains(CHA_DAYCAT_WEEK_DAY))
	dayCat = dayCat + EAC_SBI_WEEK_DAY;
    if (subsc.getInterval().getDayCategory().contains(CHA_DAYCAT_SATURDAY))
	dayCat = dayCat + EAC_SBI_SATURDAY;
    if (subsc.getInterval().getDayCategory().contains(CHA_DAYCAT_FRIDAY))
	dayCat = dayCat + EAC_SBI_FRIDAY;
    if (subsc.getInterval().getDayCategory().contains(CHA_DAYCAT_THURSDAY))
	dayCat = dayCat + EAC_SBI_THURSDAY;
    if (subsc.getInterval().getDayCategory().contains(CHA_DAYCAT_WEDNESDAY))
	dayCat = dayCat + EAC_SBI_WEDNESDAY;
    if (subsc.getInterval().getDayCategory().contains(CHA_DAYCAT_TUESDAY))
	dayCat = dayCat + EAC_SBI_TUESDAY;
    if (subsc.getInterval().getDayCategory().contains(CHA_DAYCAT_MONDAY))
	dayCat = dayCat + EAC_SBI_MONDAY;
    if (subsc.getInterval().getDayCategory().contains(CHA_DAYCAT_SUNDAY))
	dayCat = dayCat + EAC_SBI_SUNDAY;

    // dayCatAlways will hold a value used to decide if the day category set
    // puts a constraint on the time criteria

    dayCatAlways = EAC_SBI_SUNDAY + EAC_SBI_MONDAY + EAC_SBI_TUESDAY +
	EAC_SBI_WEDNESDAY + EAC_SBI_THURSDAY + EAC_SBI_FRIDAY + EAC_SBI_SATURDAY;

    dayCategory = (EAC_SBI_Day_Cat)dayCat;

    // Move information about daily times to variables understood by EA

    fh = subsc.getInterval().getDailyStartTime().hour();
    fmi = subsc.getInterval().getDailyStartTime().minute();
    th = subsc.getInterval().getDailyEndTime().hour();
    tmi = subsc.getInterval().getDailyEndTime().minute();

    // Decide if the time criteria should be set or not

    if ((dayCat != dayCatAlways) || (fh != 0) || (fmi != 0) ||
	(th != 23) || (tmi != 59))
    {
	// Set the time criteria

	r = Set_time_criteria(dayCategory,
			      fh, fmi, DC,
			      th, tmi, DC);
    };
    return r;*/
};

//**********************************************************************

int CHA_SBI_SPR_Subscription::storeRouting(CHA_Subsc subsc,
					   const RWCString applName)
{
    int numId;
    int j;
   // int r = EAC_SBI_OK;
    CHA_AddressList* padrList;

    CHA_UserInfo userInfo;
    RWCString user = userInfo.loginName();

    //TRACE_IN(trace, storeRouting(), "");

    padrList = subsc.getRoutingCase().getAddressList(CHA_DT_WINDOW);
    numId = padrList->entries();
    if (numId > 0)
    {
	//r = Set_subscription_receiver(applName.data());
    };

    padrList = subsc.getRoutingCase().getAddressList(CHA_DT_FILE);
    numId = padrList->entries();
    if (numId > 0)
    {
	for (j = 0; j < numId; j++)
	{
	 /*   r = Set_subscription_receiver(applName.data(),
					  user.data(),
					  EAC_SBI_File_Append,
					  (*padrList)[j],
					  (const char*) 0, //node_name default
					  0 ); // normal_delete NOT default*/

// Values for telling the subscription to file to NOT be erased
//  if the router process is going down. See eac_sbi_spr_subscriber
	};
    };

    padrList = subsc.getRoutingCase().getAddressList(CHA_DT_MAIL);
    numId = padrList->entries();
    if (numId > 0)
    {
	for (j = 0; j < numId; j++)
	{
	/*    r = Set_subscription_receiver(applName.data(),
					  user.data(),
					  EAC_SBI_Mail_Box,
					  (*padrList)[j],
					  (const char*) 0, //node_name default
					  0 ); // normal_delete NOT default*/

// Values for telling the subscription to mail to NOT be erased
//  if the router process is going down. See eac_sbi_spr_subscriber
	};
    };

    padrList = subsc.getRoutingCase().getAddressList(CHA_DT_PRINTER);
    numId = padrList->entries();
    if (numId > 0)
    {
	for (j = 0; j < numId; j++)
	{
	/*    r = Set_subscription_receiver(applName.data(),
					  user.data(),
					  EAC_SBI_Printer,
					  (*padrList)[j],
					  (const char*) 0, //node_name default
					  0 ); // normal_delete NOT default*/

// Values for telling the subscription to printer to NOT be erased
//  if the router process is going down. See eac_sbi_spr_subscriber
	};

    };

  /*  {
	SRMForwarder forw;
	const char* proc;

	padrList = subsc.getRoutingCase().getAddressList(CHA_DT_OS);
	numId = padrList->entries();
	if (numId > 0)
	{
	    for (j = 0; j < numId; j++)
	    {
		proc = forw.getServerName((*padrList)[j]);
		if (proc)
		{
		    r = Set_subscription_receiver
			(applName.data(),
			 user.data(),
			 proc,
			 "", // host
			 (const char *) 0,//node
			 (*padrList)[j]);
		};
	    };
	};
    }

    return r;*/
};

//**********************************************************************
//**********************************************
//**********************************************************************

int CHA_SBI_SPR_Subscription::Set_criteria_and_name
(const char* ES_name, const char* orderName)
{
  long  MaxInt = 999;

  //TRACE_IN(trace, Set_criteria_and_name, "");

  /*int r = Set_string_condition(ES_name);
  if (r == EAC_SBI_OK)
    r = Set_string_condition("*");
  if (r == EAC_SBI_OK)
    r = Set_integer_condition(-MaxInt,MaxInt);
  if (r == EAC_SBI_OK)
    r = Set_or_condition(2);
  if (r == EAC_SBI_OK)
    r = Set_string_condition(orderName);
  if (r == EAC_SBI_OK)
    r = Set_comment_condition(1);
  if (r == EAC_SBI_OK)
    r = Set_and_condition(3);
  if (r != EAC_SBI_OK) Error_handler(r); // report to PMS
  return r;*/
}; // end of Set_criteria_and_name


int CHA_SBI_SPR_Subscription::Set_criteria_and_name(const char*  ES_name,
						    long         spont_id,
						    const char* 	orderName)
{

    //TRACE_IN(trace, Set_criteria_and_name, "");

 /* int r = Set_string_condition(ES_name);
  if (r == EAC_SBI_OK)
    r = Set_integer_condition(spont_id);
  if (r == EAC_SBI_OK)
    r = Set_string_condition(orderName);
  if (r == EAC_SBI_OK)
    r = Set_comment_condition(1);
  if (r == EAC_SBI_OK)
    r = Set_and_condition(3);
  if (r != EAC_SBI_OK) Error_handler(r); // report to PMS
  return r;*/
}; // end of Set_criteria_and_name


int CHA_SBI_SPR_Subscription::Set_criteria_and_name(const char*  ES_name,
						    long         spont_low,
						    long         spont_high,
						    const char* orderName)
{

    //TRACE_IN(trace, Set_criteria_and_name, "");

 /* int r = Set_string_condition(ES_name);
  if (r == EAC_SBI_OK)
    r = Set_integer_condition(spont_low,spont_high);
  if (r == EAC_SBI_OK)
    r = Set_string_condition(orderName);
  if (r == EAC_SBI_OK)
    r = Set_comment_condition(1);
  if (r == EAC_SBI_OK)
    r = Set_and_condition(3);
  if (r != EAC_SBI_OK) Error_handler(r); // report to PMS
  return r;*/
}; // end of Set_criteria_and_name


int CHA_SBI_SPR_Subscription::Set_criteria_and_name(const char* ES_name,
						    const char* spont_id,
						    const char* 	orderName)
{

  //TRACE_IN(trace, Set_criteria_and_name, "");

 /* int r = Set_string_condition(ES_name);
  if (r == EAC_SBI_OK)
    r = Set_string_condition(spont_id);
  if (r == EAC_SBI_OK)
    r = Set_string_condition(orderName);
  if (r == EAC_SBI_OK)
    r = Set_comment_condition(1);
  if (r == EAC_SBI_OK)
    r = Set_and_condition(3);
  if (r != EAC_SBI_OK) Error_handler(r); // report to PMS
  return r;*/
}; // end of Set_criteria_and_name


int CHA_SBI_SPR_Subscription::Get_criteria_and_name(int 		criteria_nr,
						    const char*  &ES_name,
						    int          &type_of_criteria,
						    long         &spont_low,
						    long         &spont_high,
						    const char*  &spont_id,
						    const char* 	&orderName)
    const
{

    //TRACE_IN(trace, Get_criteria_and_name, "");

    ES_name = 0;
  //  type_of_criteria = EAC_SBI_NO_VALUE;
    spont_id = 0;
    spont_low = 0;
    spont_high = 0;
    orderName = 0;

   /* int r = Check_condition(criteria_nr,
			    "A2C1SS,A3C1SSS,A3C1SRS,A3C1SIS,A3C1SO2RSS");
    switch (r)
    {
    case 0:   // AND(orderName,ES_name)
	orderName = Get_leaf_stg_element(criteria_nr,0);
	ES_name = Get_leaf_stg_element(criteria_nr,1);
	break;
    case 1:   // AND(orderName,spont_id,ES_name)
	orderName = Get_leaf_stg_element(criteria_nr,0);
	spont_id = Get_leaf_stg_element(criteria_nr,1);
	ES_name = Get_leaf_stg_element(criteria_nr,2);
	r = 0;
	type_of_criteria = EAC_SBI_STRING;
	break;
    case 2:   // AND(orderName,spont-low-spont_high,ES_name)
	orderName = Get_leaf_stg_element(criteria_nr,0);
	spont_low = Get_leaf_int_element(criteria_nr,1);
	spont_high = Get_leaf_int_element(criteria_nr,1,1);
	ES_name = Get_leaf_stg_element(criteria_nr,2);
	r = 0;
	type_of_criteria = EAC_SBI_RANGE;
	break;
    case 3:   // AND(orderName,spont_low,ES_name)
	orderName = Get_leaf_stg_element(criteria_nr,0);
	spont_low = Get_leaf_int_element(criteria_nr,1);
	ES_name = Get_leaf_stg_element(criteria_nr,2);
	r = 0;
	type_of_criteria = EAC_SBI_LOW_ONLY;
	break;
    case 4:   // AND(OR(orderName,spont_low-spont_high,spont_id),ES_name)
	orderName = Get_leaf_stg_element(criteria_nr,0);
	spont_low = Get_leaf_int_element(criteria_nr,1);
	spont_high = Get_leaf_int_element(criteria_nr,1,1);
	spont_id = Get_leaf_stg_element(criteria_nr,2);
	ES_name = Get_leaf_stg_element(criteria_nr,3);
	r = 0;
	type_of_criteria = EAC_SBI_DEFAULT;
	break;
    default:  // Error
	r = -1;
	break;
    }; // end switch

    if (r == 0)
    {
	criteria_nr++;
	r = Get_ptr_to_criteria(criteria_nr);
	if (r < 0) r = 0; // Last criteria found
	else r = criteria_nr; // next criteria to read
    }

    return r;*/

}; // end of Get_criteria_and_name
