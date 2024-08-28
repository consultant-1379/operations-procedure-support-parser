// RCS handling
// $Id: CHA_SubscInterval.C,v 24.0 1995/11/28 17:01:09 ehsgrap Rel $

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
//      $Log: CHA_SubscInterval.C,v $
//      Revision 24.0  1995/11/28 17:01:09  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:50:26  17:50:26  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:51:03  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:48:46  09:48:46  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:39:47  08:39:47  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:59:09  10:59:09  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:11:49  20:11:49  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:14:13  14:14:13  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  13:06:05  13:06:05  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  15:13:35  15:13:35  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:39:30  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:13:10  14:13:10  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 12.0  95/02/06  16:23:58  16:23:58  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:55:22  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:09:19  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:36:04  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:57:29  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:29:15  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:56:08  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.1  1994/08/26  10:17:37  qhsmosc
//      Fixed equality operator
//
//      Revision 5.0  1994/08/16  07:55:03  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:46:35  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  08:01:29  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.1  1994/06/22  07:31:41  qhsmosc
//      Changed the equality operator
//
//      Revision 2.0  1994/06/12  08:02:35  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.4  1994/05/13  09:49:47  qhsmosc
//      Final version
//
//      Revision 1.3  1994/05/06  06:49:36  qhsmosc
//      Compilable version
//
//      Revision 1.2  1994/04/27  08:05:18  qhsmosc
//      Before new RCS-handling
//
//      Revision 1.1  1994/04/26  07:40:47  qhsmosc
//      Initial revision
//
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	TB53_OZ 1995-11-28      J Grape (EHSGRAP)       RCS rev 24.0
//	XM2S1   1995-09-07      ehscama                 RCS rev 23.0
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
//	PREIT   1995-01-18      N Länninge (XKKNICL)    RCS rev 11.0
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
//      CHA_TimeSchedule
//      CHA_DayCategory

//**********************************************************************

#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_SubscInterval.H>
#include <rw/tools/datetime.h>

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_SubscInterval", (char*)"C");

// Member functions, constructors, destructors, operators

//**********************************************************************

CHA_SubscInterval::CHA_SubscInterval()
: days()
{
    //days = hashDayCategory;
    RWDateTime defZeroTime(0,0,0);
    RWDateTime defNightTime(23,59,59);

    ////TRACE_IN(trace, CHA_SubscInterval, "");
    timeInterval.setStartTime(defZeroTime);
    timeInterval.setStopTime(defNightTime);
    timeEveryDay.setStartTime(defZeroTime);
    timeEveryDay.setStopTime(defNightTime);
    startDateDefined = FALSE;
    endDateDefined = FALSE;
    days.insert(CHA_DAYCAT_SUNDAY);
    days.insert(CHA_DAYCAT_MONDAY);
    days.insert(CHA_DAYCAT_TUESDAY);
    days.insert(CHA_DAYCAT_WEDNESDAY);
    days.insert(CHA_DAYCAT_THURSDAY);
    days.insert(CHA_DAYCAT_FRIDAY);
    days.insert(CHA_DAYCAT_SATURDAY);
};

//**********************************************************************

CHA_SubscInterval::CHA_SubscInterval(const CHA_SubscInterval& schedule)
: days()
{
    ////TRACE_IN(trace, CHA_SubscInterval-Copy, "");

    // Copy constructor

    timeInterval.setStartTime(schedule.getStartTimeInterval());
    timeInterval.setStopTime(schedule.getEndTimeInterval());
    timeEveryDay.setStartTime(schedule.getDailyStartTime());
    timeEveryDay.setStopTime(schedule.getDailyEndTime());
    startDateDefined = schedule.isStartDateDefined();
    endDateDefined = schedule.isEndDateDefined();
    days = schedule.getDayCategory();
};

//**********************************************************************

CHA_SubscInterval::~CHA_SubscInterval()
{
};

//**********************************************************************

void CHA_SubscInterval::setDayCategory(
    const RWTValHashSet<CHA_DayCategory, std::hash<int>, std::equal_to<int> >& dset)
{
    //TRACE_IN(trace, setDayCategory, "");

    days = dset;
};

//**********************************************************************

const RWTValHashSet<CHA_DayCategory, std::hash<int>, std::equal_to<int> >& CHA_SubscInterval::getDayCategory()
    const
{
  //TRACE_IN(trace, getDayCategory, "");

  return days;
};

//**********************************************************************

void CHA_SubscInterval::setDailyStartTime(const RWDateTime& startTime)
{
    //TRACE_IN(trace, setDailyStartTime, "");

    timeEveryDay.setStartTime(startTime);
};

//**********************************************************************

const RWDateTime CHA_SubscInterval::getDailyStartTime() const
{
    //TRACE_IN(trace, getDailyStartTime, "");

    return timeEveryDay.getStartTime();
};

//**********************************************************************

void CHA_SubscInterval::setDailyEndTime(const RWDateTime& endTime)
{
    //TRACE_IN(trace, setDailyEndTime, "");

    timeEveryDay.setStopTime(endTime);
};

//**********************************************************************

const RWDateTime CHA_SubscInterval::getDailyEndTime() const
{
    //TRACE_IN(trace, getDailyEndTime, "");

    return timeEveryDay.getStopTime();
};

//**********************************************************************

void CHA_SubscInterval::setStartTimeInterval(const RWDateTime& startTime)
{
    //TRACE_IN(trace, setStartTimeInterval, "");

    timeInterval.setStartTime(startTime);
};

//**********************************************************************

const RWDateTime CHA_SubscInterval::getStartTimeInterval() const
{
    //TRACE_IN(trace, getStartTimeInterval, "");

    return timeInterval.getStartTime();
};

//**********************************************************************

void CHA_SubscInterval::setEndTimeInterval(const RWDateTime& endTime)
{
    //TRACE_IN(trace, setEndTimeInterval, "");

    timeInterval.setStopTime(endTime);
};

//**********************************************************************

const RWDateTime CHA_SubscInterval::getEndTimeInterval() const
{
    //TRACE_IN(trace, getEndTimeInterval, "");

    return timeInterval.getStopTime();
};

//**********************************************************************

void CHA_SubscInterval::setStartDateDefined(const RWBoolean& dateFlag)
{
    //TRACE_IN(trace, setStartDateDefined, "");

    startDateDefined = dateFlag;
};

//**********************************************************************

const RWBoolean CHA_SubscInterval::isStartDateDefined() const
{
    //TRACE_IN(trace, getStartDateDefined, "");

    return startDateDefined;
};

//**********************************************************************

void CHA_SubscInterval::setEndDateDefined(const RWBoolean& dateFlag)
{
    //TRACE_IN(trace, setEndDateDefined, "");

    endDateDefined = dateFlag;
};

//**********************************************************************

const RWBoolean CHA_SubscInterval::isEndDateDefined() const
{
    //TRACE_IN(trace, getEndDateDefined, "");

    return endDateDefined;
};

//**********************************************************************

CHA_SubscInterval& CHA_SubscInterval::operator=(const CHA_SubscInterval& schedule)
{
    //TRACE_IN(trace, operator=, "");

    timeInterval.setStartTime(schedule.getStartTimeInterval());
    timeInterval.setStopTime(schedule.getEndTimeInterval());
    timeEveryDay.setStartTime(schedule.getDailyStartTime());
    timeEveryDay.setStopTime(schedule.getDailyEndTime());

    startDateDefined = schedule.isStartDateDefined();
    endDateDefined = schedule.isEndDateDefined();

    days = schedule.getDayCategory();

    //TRACE_FLOW(trace, operator=Finished, "");

    return *this;
};

//**********************************************************************

RWBoolean CHA_SubscInterval::operator==(const CHA_SubscInterval& schedule) const
{
    //TRACE_IN(trace, operator==, "");

    // Test if start and stop times are equal

    if ((schedule.isStartDateDefined() == startDateDefined) &&
	(schedule.isEndDateDefined() == endDateDefined) &&
	((schedule.isStartDateDefined() == FALSE) ||
	 (timeInterval.getStartTime() == schedule.getStartTimeInterval())) &&
	((schedule.isEndDateDefined() == FALSE) ||
	 (timeInterval.getStopTime() == schedule.getEndTimeInterval())) &&
	(timeEveryDay.getStartTime().hour() ==
	 schedule.getDailyStartTime().hour()) &&
	(timeEveryDay.getStartTime().minute() ==
	 schedule.getDailyStartTime().minute()) &&
	(timeEveryDay.getStopTime().hour() ==
	 schedule.getDailyEndTime().hour()) &&
	(timeEveryDay.getStopTime().minute() ==
	 schedule.getDailyEndTime().minute()))
    {
    	// Times are equal, test if the day categories are the same

	if ((days.entries() == schedule.getDayCategory().entries()) &&
	    (days.contains(CHA_DAYCAT_SUNDAY) ==
	     schedule.getDayCategory().contains(CHA_DAYCAT_SUNDAY)) &&
	    (days.contains(CHA_DAYCAT_MONDAY) ==
	     schedule.getDayCategory().contains(CHA_DAYCAT_MONDAY)) &&
	    (days.contains(CHA_DAYCAT_TUESDAY) ==
	     schedule.getDayCategory().contains(CHA_DAYCAT_TUESDAY)) &&
	    (days.contains(CHA_DAYCAT_WEDNESDAY) ==
	     schedule.getDayCategory().contains(CHA_DAYCAT_WEDNESDAY)) &&
	    (days.contains(CHA_DAYCAT_THURSDAY) ==
	     schedule.getDayCategory().contains(CHA_DAYCAT_THURSDAY)) &&
	    (days.contains(CHA_DAYCAT_FRIDAY) ==
	     schedule.getDayCategory().contains(CHA_DAYCAT_FRIDAY)) &&
	    (days.contains(CHA_DAYCAT_SATURDAY) ==
	     schedule.getDayCategory().contains(CHA_DAYCAT_SATURDAY)) &&
	    (days.contains(CHA_DAYCAT_WEEK_DAY) ==
	     schedule.getDayCategory().contains(CHA_DAYCAT_WEEK_DAY)) &&
	    (days.contains(CHA_DAYCAT_BEFORE_HOLIDAY) ==
	     schedule.getDayCategory().contains(CHA_DAYCAT_BEFORE_HOLIDAY)) &&
	    (days.contains(CHA_DAYCAT_HOLIDAY) ==
	     schedule.getDayCategory().contains(CHA_DAYCAT_HOLIDAY)))
	{
	    return TRUE;
	}
	else
	    return FALSE;
    }
    else
	return FALSE;
};


