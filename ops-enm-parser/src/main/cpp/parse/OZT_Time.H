// RCS revision handling
// $Id: OZT_Time.H,v 21.0 1996/08/23 12:43:15 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_Time - Data type for time
// .LIBRARY CHOZTBIN
// .PAGENAME OZT_Time
// .LEFT_FOOTER Ericsson HP

// .COPYRIGHT
//	COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB, Sweden 1994.
// 	All rights reserved.
//
//	The Copyright to the computer program(s) herein is the
//	property of Ericsson Hewlett-Packard Telecommunications AB,
//	Sweden. The program(s) may be used and/or copied only with the
//	written permission from Ericsson Hewlett-Packard
//	Telecommunications AB or in accordance with the terms and
//	conditions stipulated in the agreement/contract under which
//	the program(s) have been supplied.

// .DESCRIPTION 
// 	Data type for time used in CHOZTBIN.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	190 89-CAA 134 2016

// AUTHOR 
// 	1995-03-09 by Nelson Cheng (epanyc@epanyc.ericsson.se)

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_Time.H,v $
// 	Revision 21.0  1996/08/23 12:43:15  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 07:57:48  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:22:30  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:21:52  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:02:22  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:57:31  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:03:00  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:17:26  17:17:26  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.0  1995/10/07 12:01:40  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:09:40  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:25:21  09:25:21  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:02:39  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.1  95/07/05  09:14:57  09:14:57  epanyc (Nelson Cheng VK/EHS/PXE)
//      comment added
//      
//      Revision 9.0  1995/06/29  14:38:15  cmcha
//      Made release EC2_OZ, J Grape (EHSGRAP).
//
//      Revision 8.1  95/06/28  14:31:45  14:31:45  epanyc (Nelson Cheng VK/EHS/PXE)
//      various improvements made
//      
//      Revision 8.0  95/06/07  17:09:28  17:09:28  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 7.2  95/06/07  11:59:33  11:59:33  epanyc (Nelson Cheng VK/EHS/PXE)
//      significant changes to the class
//      
//      Revision 7.1  1995/06/01  13:43:07  epanyc
//      save before not relying on RWTime.
//
//      Revision 7.0  1995/04/16  12:16:38  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.0  95/03/17  20:05:43  20:05:43  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 5.0  95/03/16  20:31:27  20:31:27  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 1.1  95/03/09  08:50:20  08:50:20  epanyc (Nelson Cheng VK/EHS/PXE)
//      Initial revision
//      
//
//	RELEASE REVISION HISTORY
//
//	REV NO	DATE		NAME			DESCRIPTION
//	B_POINT 1996-08-23      J Grape (EHSGRAP)       RCS rev 21.0
//	EC8_OZ  1996-07-10      David Terry epa.epadmt  RCS rev 20.0
//	POW_TB611996-03-19      J Sandquist (ehsjasa)   RCS rev 19.0
//	EC7_OZ  1996-03-01      J Sandquist (ehsjasa)   RCS rev 18.0
//	EC6_OZ  1996-01-17      J Sandquist (ehsjasa)   RCS rev 17.0
//	POW_TB411996-01-08      J Sandquist (ehsjasa)   RCS rev 16.0
//	TB53_OZ 1995-11-29      J Grape (EHSGRAP)       RCS rev 15.0
//	POW_TB3 1995-11-20      J Sandquist (EHSJASA)   RCS rev 14.0
//	PRE_XM221995-10-07      J Sandquist (EHSJASA)   RCS rev 13.0
//	EC5_OZ  1995-09-22      J Sandquist (EHSJASA)   RCS rev 12.0
//	EC4_OZ  1995-09-14      J Sandquist (EHSJASA)   RCS rev 11.0
//	EC3_OZ  1995-08-02      J Sandquist (EHSJASA)   RCS rev 10.0
//	EC2_OZ  1995-06-29      J Grape (EHSGRAP)       RCS rev 9.0
//	TB5_2_OZ1995-06-07      J Grape (EHSGRAP)       RCS rev 8.0
//	TB5_1_OZ1995-04-16      J Grape (EHSGRAP)       RCS rev 7.0
//	TB51_OZ 1995-03-17      ehscama                 RCS rev 6.0
//	TB5_OZ  1995-03-16      ehscama                 RCS rev 5.0
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	<link information: libraries needed and order>

// .SEE ALSO 
// 	<Related classes, (abstract) baseclasses, friend classes, ...>

//*****************************************************************************


#ifndef OZT_TIME_H
#define OZT_TIME_H

#include <rw/cstring.h>
#include <time.h>

class OZT_Time {
public:
    OZT_Time();
    // Description
    //     Default constructor. Construct an OZT_Time object
    //     with the current local time.

    OZT_Time(const OZT_Time &t);
    // Description
    //     Copy constructor.

    OZT_Time(time_t t);
    // Description
    //     Constructor by no. of seconds since the Epoch.


    OZT_Time(const RWCString &dateTimeExp);
    // Description
    //     Construct an OZT_Time object with the specified time.
    // Parameter
    //     dateTimeExp        IN: date-time expression with the format
    //                            YYMMDDHHMM. If the expression is
    //                            longer than 10-chars, the rest of the
    //                            string is ignored.

    virtual ~OZT_Time();
    // Description
    //     Destructor


    time_t toSecSinceEpoch() const;
    // Description
    //     Return the no. of seconds since the Epoch.

    RWBoolean isValid() const;
    // Description
    //     Test if the instance represents a valid time
    // Return value
    //     TRUE               if the object represents a valid time
    //     FALSE              if the object does not represents a valid time

    RWBoolean advance(const RWCString &intervalExp);
    // Description
    //     Increase the time of the current instance repeatedly by
    //     the amount specified in "intervalExp" until the resultant
    //     time is not in the past.
    //     The unit of increment can be a week, a day, an hour or a minute.
    //     If the unit of increment is a week or a day, no daylight saving
    //     adjustment will be applied if the time before and after
    //     increment falls respectively inside and outside of daylight 
    //     saving adjustment boundary, or vice versa.
    //      
    // Parameter
    //     intervalExp       IN: in the format of nnx, where nn is in the
    //                           range of 1-99, and x can be W, D, H or M 
    //                           which represents week, day, hour or minute 
    //                           respectively. 
    // Return value
    //     TRUE              if the advance operation is successful
    //     FALSE             if the advance operation fails

RWBoolean regress(const RWCString &intervalExp);
    // Description
    //     Decrease the time of the current instance repeatedly by
    //     the amount specified in "intervalExp" until the resultant
    //     time is not in the past.
    //     The unit of increment can be a week, a day, an hour or a minute.
    //     If the unit of increment is a week or a day, no daylight saving
    //     adjustment will be applied if the time before and after
    //     increment falls respectively inside and outside of daylight 
    //     saving adjustment boundary, or vice versa.
    //      
    // Parameter
    //     intervalExp       IN: in the format of nnx, where nn is in the
    //                           range of 1-99, and x can be W, D, H or M 
    //                           which represents week, day, hour or minute 
    //                           respectively. 
    // Return value
    //     TRUE              if the regress operation is successful
    //     FALSE             if the regress operation fails


    RWCString toString() const;
    // Description
    //     Returns a string of the format YYMMDDHHMMSSDDD
    //     
    // Return value
    //     A string represents the time of this instance where
    //     YY - Year
    //     MM - Month (01-12)
    //     DD - Day of the month
    //     HH - Hour (00-23)
    //     MM - Minute (00-59)
    //     SS - Second (00-59)
    //     DDD - Day of the week (MON, TUE, ...)
    //
    //     If the object represents an invalid time, an empty string is
    //     returned.

    RWCString toString(RWCString &dayOfWeek) const;
    // Description
    //     Returns a string of the format YYMMDDHHMMSSDDD, and the day of the
    //     week.
    // Parameter
    //     dayOfWeek         OUT: The day of the week, such as MON, TUE etc.
    //                            If the object represents an invalid time,
    //                            an empty string is returned.
    // Return value
    //     See the other overloaded member function toString().

    RWBoolean inHistory() const;
    // Description
    //     Test if this instance represents a time that has already
    //     past.
    //     Note that this function should only be applied when the instance 
    //     represents a valid time.
    // Parameter
    //     TRUE             if the time is passed.
    //     FALSE            if the time is not in the past.

    OZT_Time &operator=(const OZT_Time &t);
    // Description
    //     Assignment operator.

    OZT_Time& operator+=(time_t s);
    // Description
    //     Increment the time by "s" number of seconds

    friend OZT_Time operator+(const OZT_Time &t, time_t secs);
    friend OZT_Time operator+(time_t secs, const OZT_Time &t);
    friend long operator-(const OZT_Time &t1, const OZT_Time &t2);
    // Description
    //     Arithmetic operators.

    friend RWBoolean operator>(const OZT_Time& t1, const OZT_Time& t2);
    friend RWBoolean operator>=(const OZT_Time& t1, const OZT_Time& t2);
    friend RWBoolean operator==(const OZT_Time& t1, const OZT_Time& t2);
    friend RWBoolean operator!=(const OZT_Time& t1, const OZT_Time& t2);
    friend RWBoolean operator<=(const OZT_Time& t1, const OZT_Time& t2);
    friend RWBoolean operator<(const OZT_Time& t1, const OZT_Time& t2);
    // Description
    //     Comparison operators.

protected:
    static RWBoolean convertInterval(const RWCString &intervalExp,
                                     int &interval,
                                     char &intervalType);

private:

    time_t    theTime;
    struct tm *timeBuffer;
    RWBoolean valid;
};


#endif
