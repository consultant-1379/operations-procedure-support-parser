
// RCS handling
// $Id: CHA_SubscInterval.H,v 24.0 1995/11/28 17:00:46 ehsgrap Rel $

//**********************************************************************
// 
// .NAME CHA_SubscInterval - the Interval for a subscription.
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_SubscInterval.H 

// .COPYRIGHT
//      COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1994
//
//      The Copyright to the computer program(s) herein is the
//      property of Ericsson Hewlett-Packard Telecommunications AB,
//      Sweden.  The program(s) may be used and/or copied with the
//      written permission from Ericsson Hewlett-Packard
//      Telecommunications AB or in accordance with the terms and
//      conditions stipulated in the agreement/contract under which
//      the program(s) have been supplied.


// .DESCRIPTION 
//      The interval for a subscription.

// DOCUMENT NO
//      190 89-CAA 134 1521

// AUTHOR 
//      1994-04-28 by EHS / Marie Moschna (qhsmosc@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_SubscInterval.H,v $
//      Revision 24.0  1995/11/28 17:00:46  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:49:49  17:49:49  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:50:38  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:48:05  09:48:05  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:39:07  08:39:07  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:58:42  10:58:42  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:11:20  20:11:20  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:13:37  14:13:37  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:05:37  13:05:37  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:12:37  15:12:37  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:39:05  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:12:35  14:12:35  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:23:19  16:23:19  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:54:44  cmcha
//      Made release PREIT, N L\ufffdnninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:08:43  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:35:29  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:56:49  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:28:26  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:55:30  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:54:11  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:45:50  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  08:00:42  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:01:57  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.7  1994/06/10  16:57:02  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.6  1994/05/17  13:13:52  qhsmosc
//      Move definition of day categories to an own file
//
//      Revision 1.5  1994/05/13  09:51:44  qhsmosc
//      Final version
//
//      Revision 1.4  1994/05/06  06:49:06  qhsmosc
//      Compilable version
//
//      Revision 1.3  1994/04/26  08:00:00  qhsmosc
//      First test version
//
//      Revision 1.2  1994/04/05  13:11:34  ehscama
//      Corrected CHA_TimeInterval, should be CHA_TimeSchedule.
//
//      Revision 1.1  1994/04/05  13:05:55  ehscama
//      Changed name from CHA_SubscriptionSchedule to CHA_SubscInterval.
//
//      Revision 1.1  1994/02/22  15:45:51  ehscama
//      Initial revision.
//
//      Revision 1.1  1994/02/22  15:45:51  ehscama
//      Initial revision.
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

// .SEE ALSO 
//      CHA_TimeSchedule
//      CHA_DayCategory

//**********************************************************************

#ifndef CHA_SUBSCINTERVAL_H
#define CHA_SUBSCINTERVAL_H

#include <CHA_DayCategory.H>
#include <CHA_TimeSchedule.H>
#include <rw/tvhset.h>


class CHA_SubscInterval
{

public:
    CHA_SubscInterval();
    // Description:
    //     Default constructor.
    
    CHA_SubscInterval(const CHA_SubscInterval& other);
    // Description:
    //     Copy constructor.
    // Parameters:
    //     other        original CHA_SubscInterval
    
    ~CHA_SubscInterval();
    // Description:
    //     Default constructor.



    //virtual void setDayCategory(const RWTValHashSet<CHA_DayCategory>& d);
    virtual void setDayCategory(const RWTValHashSet<CHA_DayCategory, std::hash<int>, std::equal_to<int> >& d);
    // Description:
    //     Set the day category set.
    // Parameters:
    //     d                    The day category set
    
   // virtual const RWTValHashSet<CHA_DayCategory>& getDayCategory() const;
    virtual const RWTValHashSet<CHA_DayCategory, std::hash<int>, std::equal_to<int> >& getDayCategory() const;
    // Description:
    //     Get the day category set.
    // Return value:
    //     A CHA_DayCategorySet containing the set day categories.

    virtual void setDailyStartTime(const RWDateTime& t);
    // Description:
    //     Set the daily start time.
    // Parameters:
    //     t                    The daily start time
    
    virtual const RWDateTime getDailyStartTime() const;
    // Description:
    //     Get the daily start time.
    // Return value:
    //     A RWCTime with the daily start time.
    
    virtual void setDailyEndTime(const RWDateTime& t);
    // Description:
    //     Set the daily end time
    // Parameters:
    //     t                    The daily end time
    
    virtual const RWDateTime getDailyEndTime() const;
    // Description:
    //     Get the daily end time
    // Return value:
    //     A RWCTime with the daily end time.
    
    virtual void setStartTimeInterval(const RWDateTime& t);
    // Description:
    //     Set the start time and the start date.
    // Parameters:
    //     t                    The start time
    
    virtual const RWDateTime getStartTimeInterval() const;
    // Description:
    //     Get the start time and start date.
    // Return value:
    //     A RWCTime with the start time.
    
    virtual void setEndTimeInterval(const RWDateTime& t);
    // Description:
    //     Set the end time and end date.
    // Parameters:
    //     t                    The end time
    
    virtual const RWDateTime getEndTimeInterval() const;
    // Description:
    //     Get the daily end time and end date.
    // Return value:
    //     A RWCTime with the end time.
    
    virtual void setStartDateDefined(const RWBoolean& u);
    // Description:
    //     Set the flag which tells if the start date for the time interval
    //     is set or not.
    // Parameters:
    //     t                    The flag, TRUE or FALSE
    
    virtual const RWBoolean isStartDateDefined() const;
    // Description:
    //     Get the flag which tells if the start date for the time interval
    //     is set or not.
    // Return value:
    //     A RWBoolean set to TRUE or FALSE.

    virtual void setEndDateDefined(const RWBoolean& u);
    // Description:
    //     Set the flag which tells if the end date for the time interval
    //     is set or not.
    // Parameters:
    //     t                    The flag, TRUE or FALSE
    
    virtual const RWBoolean isEndDateDefined() const;
    // Description:
    //     Get the flag which tells if the end date for the time interval
    //     is set or not.
    // Return value:
    //     A RWBoolean set to TRUE or FALSE.
    
    virtual CHA_SubscInterval& operator=(const CHA_SubscInterval& s);
    // Description:
    //     Assignment operator.
    // Return value:
    //     A reference to a subscInterval.

    virtual RWBoolean operator==(const CHA_SubscInterval& schedule) const;
    // Description:
    //     Equality operator.
    // Return value:
    //     True or false depending on the result of the comparison.


private:

    CHA_TimeSchedule   timeInterval;  // Start/stop time with dates
    CHA_TimeSchedule   timeEveryDay;  // Start/stop time for every DayCategory
    //RWTValHashSet<CHA_DayCategory> days;
    RWTValHashSet<CHA_DayCategory, std::hash<int>, std::equal_to<int> > days;
    RWBoolean startDateDefined;
    RWBoolean endDateDefined;
  
};

#endif
