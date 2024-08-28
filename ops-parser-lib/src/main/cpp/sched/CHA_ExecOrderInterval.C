// RCS handling
// $Id: CHA_ExecOrderInterval.C,v 24.0 1995/11/28 16:59:22 ehsgrap Rel $

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
//	190 89-CAA 134 1516

// AUTHOR
//      1994-06-20 by EHS / Marie Moschna (qhsmosc@ehs.ericsson.se)

// REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_ExecOrderInterval.C,v $
//      Revision 24.0  1995/11/28 16:59:22  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:47:34  17:47:34  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//
//      Revision 22.1  1995/08/24  08:55:10  ehscama
//      Changed default time to now!
//
//      Revision 22.0  1995/08/01  20:48:51  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:46:04  09:46:04  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:37:31  08:37:31  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.1  95/06/07  13:08:15  13:08:15  epanyc (Nelson Cheng VK/EHS/PXE)
//      start time implementation changed
//
//      Revision 19.0  1995/04/13  10:56:43  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:09:22  20:09:22  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:11:02  14:11:02  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  13:03:41  13:03:41  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  15:08:56  15:08:56  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:37:22  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:10:20  14:10:20  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 12.0  95/02/06  16:20:30  16:20:30  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:51:55  cmcha
//      Made release PREIT, N L\ufffdnninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:06:34  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:33:24  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:53:56  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:26:05  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.1  1994/09/08  10:38:47  qhsmosc
//      SetDayOfWeek and SetNoOfRepeat altered
//
//      Revision 6.0  1994/08/30  17:53:19  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:50:31  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.1  1994/08/16  06:47:56  qhsmosc
//      No warning on account of == operator
//
//      Revision 4.0  1994/07/18  13:42:42  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 1.2  1994/07/12  06:45:05  qhsmosc
//      Preliminary tests OK
//
//      Revision 1.1  1994/07/05  07:43:50  qhsmosc
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

// SEE ALSO
//      CHA_Order             user

//**********************************************************************

#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
//TORF-241666
//#include <CHA_Order.H>
#include <CHA_ExecOrderInterval.H>
#include <pwd.h>
//#include <sysent.h>

#ifdef sun
#ifdef SunOS5
#include <sys/types.h>
#include <time.h>
#else
#include <sys/types.h>
#include <sys/time.h>
#endif
#endif

#ifdef __hpux
#include <time.h>
#endif


//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_ExecOrderInterval", (char*)"C");

// Member functions, constructors, destructors, operators

//**********************************************************************

CHA_ExecOrderInterval::CHA_ExecOrderInterval()
{
    //TRACE_IN(trace, CHA_ExecOrderInterval, "");

    // RWTime defZeroTime(0,0,0); // default time used to be today at midnight

    // startTime        = defZeroTime;
    startTime        = time(NULL); // default time is NOW!
    startDateDefined = TRUE;
    period           = CHA_REPPER_NONE;
    day              = CHA_DAYWEEK_NONE;
    noOfRepeat       = 0;
};

//**********************************************************************

CHA_ExecOrderInterval::CHA_ExecOrderInterval(const CHA_ExecOrderInterval& interval)
{
    //TRACE_IN(trace, CHA_ExecOrderInterval-Copy, "");

    // Copy constructor

    startTime        = interval.startTime;
    startDateDefined = interval.startDateDefined;
    period           = interval.period;
    day              = interval.day;
    noOfRepeat       = interval.noOfRepeat;
};

//**********************************************************************

CHA_ExecOrderInterval::~CHA_ExecOrderInterval()
{
};

//**********************************************************************

const RWDateTime CHA_ExecOrderInterval::getStartTime() const
{
    //TRACE_IN(trace, getStartTime, "");

    return RWDateTime(rwEpoch + startTime);
};

//**********************************************************************

time_t CHA_ExecOrderInterval::retrieveStartTime() const
{
    //TRACE_IN(trace, getStartTime, "");

    return startTime;
}

//**********************************************************************

void CHA_ExecOrderInterval::setStartTime(const RWDateTime& timeIn)
{
    //TRACE_IN(trace, setStartTime, "");

    startTime = ( timeIn.milliSeconds()/1000 ) - rwEpoch;
};

//**********************************************************************

void CHA_ExecOrderInterval::setStartTime(time_t timeIn)
{
    //TRACE_IN(trace, setStartTime, "");

    startTime = timeIn;
}

//**********************************************************************

const RWBoolean CHA_ExecOrderInterval::isStartDateDefined() const
{
    //TRACE_IN(trace, isStartDateDefined, "");

    return startDateDefined;
};

//**********************************************************************

void CHA_ExecOrderInterval::setStartDateDefined(const RWBoolean& startDateDefIn)
{
    //TRACE_IN(trace, setStartDateDefined, "");

    startDateDefined = startDateDefIn;;
};

//**********************************************************************

const CHA_RepPeriod CHA_ExecOrderInterval::getRepPeriod() const
{
    //TRACE_IN(trace, getRepPeriod, "");

    return period;
};

//**********************************************************************

void CHA_ExecOrderInterval::setRepPeriod(const CHA_RepPeriod& periodIn)
{
    //TRACE_IN(trace, setRepPeriod, "");

    period = periodIn;
};

//**********************************************************************

const CHA_DayOfWeek CHA_ExecOrderInterval::getDayOfWeek() const
{
    //TRACE_IN(trace, getDayOfWeek, "");

    return day;
};

//**********************************************************************

void CHA_ExecOrderInterval::setDayOfWeek(const CHA_DayOfWeek& dayIn)
{
    //TRACE_IN(trace, setDayOfWeek, "");

    day        = dayIn;
    //noOfRepeat = 0;
};

//**********************************************************************

const int CHA_ExecOrderInterval::getNoOfRepeat() const
{
    //TRACE_IN(trace, getNoOfRepeat, "");

    return noOfRepeat;
};

//**********************************************************************

void CHA_ExecOrderInterval::setNoOfRepeat(const int numberIn)
{
    //TRACE_IN(trace, setNoOfRepeat, "");

    noOfRepeat = numberIn;
    //day        = CHA_DAYWEEK_NONE;
};

//**********************************************************************

CHA_ExecOrderInterval& CHA_ExecOrderInterval::operator=
(const CHA_ExecOrderInterval& interval)
{
    //TRACE_IN(trace, operator=, "");

    startTime        = interval.retrieveStartTime();
    startDateDefined = interval.isStartDateDefined();
    period           = interval.getRepPeriod();
    noOfRepeat       = interval.getNoOfRepeat();
    day              = interval.getDayOfWeek();

    return *this;

};

//**********************************************************************

RWBoolean CHA_ExecOrderInterval::operator==(const CHA_ExecOrderInterval& interval)
const
{
    //TRACE_IN(trace, operator==, "");

    if ((startDateDefined == interval.isStartDateDefined()) &&
	((startDateDefined == FALSE) ||
	 (startTime == interval.retrieveStartTime())) &&
	(period == interval.getRepPeriod()) &&
	(noOfRepeat == interval.getNoOfRepeat()) &&
	(day == interval.getDayOfWeek()))
    {
	return TRUE;
    }

    return FALSE;

};
