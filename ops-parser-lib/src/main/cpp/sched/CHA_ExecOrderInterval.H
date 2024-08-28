// RCS handling
// $Id: CHA_ExecOrderInterval.H,v 24.0 1995/11/28 16:58:40 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_ExecOrderInterval - Handles the time interval for system 
//                                  file orders and command file orders. 
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_ExecOrderInterval.H 

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
// 	CHA_ExecOrderInterval.
//	The class handles the information about when to execute a command file/
//      system file order.

// .SECTION ERROR HANDLING
//      <General rules for error handling>

// DOCUMENT NO
//      190 89-CAA 134 1516

// AUTHOR 
//      1994-06-10 by EHS/ Marie Moschna (qhsmosc@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_ExecOrderInterval.H,v $
//      Revision 24.0  1995/11/28 16:58:40  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:46:49  17:46:49  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:48:16  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:45:29  09:45:29  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:36:46  08:36:46  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.1  95/06/07  13:07:36  13:07:36  epanyc (Nelson Cheng VK/EHS/PXE)
//      new API added for setting start time
//      
//      Revision 19.0  1995/04/13  10:56:09  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:08:41  20:08:41  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:10:11  14:10:11  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:02:59  13:02:59  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:07:45  15:07:45  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:36:49  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:09:11  14:09:11  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:20:04  16:20:04  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:51:33  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:06:19  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:32:51  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:53:20  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:25:42  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:52:51  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:49:44  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:41:58  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 1.2  1994/07/12  06:48:01  qhsmosc
//      Preliminary tests OK
//
//      Revision 1.1  1994/07/05  07:15:58  qhsmosc
//      Compilable
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

// .SEE ALSO 
//      CHA_DayCategory
//      CHA_SysCmdFileOrder		Uses this class
//      CHA_CmdFileOrder                Uses this class

//**********************************************************************

#ifndef CHA_EXECORDERINTERVAL_H
#define CHA_EXECORDERINTERVAL_H

/*/extern "C"
{
#include <cap_ipc.h>
}*/

#include "CHA_DayCategory.H"
#include <rw/tvhset.h>
#include <rw/tools/datetime.h>
#include <time.h>

class CHA_ExecOrderInterval
{
public:

    CHA_ExecOrderInterval();
    // Description:
    //     Default constructor.

    CHA_ExecOrderInterval(const CHA_ExecOrderInterval& s);
    // Description:
    //     Constructor to be used at copy.

    virtual ~CHA_ExecOrderInterval();
    // Description:
    //     Destructor.
    
    virtual void setRepPeriod(const CHA_RepPeriod& d);
    // Description:
    //     Set the repitition period
    // Parameters:
    //     d                    The repitition period
    
    virtual const CHA_RepPeriod getRepPeriod() const;
    // Description:
    //     Get the repitition period.
    // Return value:
    //     A CHA_RepPeriod with the set repitition period.

    virtual void setStartTime(const RWDateTime& t);
    // Description:
    //     Set the start time and date.
    // Parameters:
    //     t                    The start time
    
    virtual void setStartTime(time_t t);
    // Description:
    //     Set the start time and date.
    // Parameter:
    //     t                    IN: number of seconds since the Epoch.

    virtual const RWDateTime getStartTime() const;
    // Description:
    //     Get the start time and date.
    // Return value:
    //     A RWTime with the start time.
    
    virtual time_t retrieveStartTime() const;
    // Description:
    //     Get the start time and date.
    // Return value:
    //     The start time in terms of number of seconds since the Epoch.

    virtual void setStartDateDefined(const RWBoolean& u);
    // Description:
    //     Set the flag which tells if the start date for the time interval
    //     is set or not.
    // Parameters:
    //     u                    The flag, TRUE or FALSE
    
    virtual const RWBoolean isStartDateDefined() const;
    // Description:
    //     Get the flag which tells if the start date for the time interval
    //     is set or not.
    // Return value:
    //     A RWBoolean set to TRUE or FALSE.

    virtual void setDayOfWeek(const CHA_DayOfWeek& d);
    // Description:
    //     Set the day of week. Can only be used when the repetition
    //     period is WEEKLY.
    // Parameters:
    //     d                    The day of week
    
    virtual const CHA_DayOfWeek getDayOfWeek() const;
    // Description:
    //     Get the day of week, only defined when the repitition period is WEEKLY.
    // Return value:
    //     The day of the week.
    
    virtual void setNoOfRepeat(const int t);
    // Description:
    //     Set the number of repeats per period. Can only be used when the
    //     period is not WEEKLY. 
    // Parameters:
    //     t                    The number of repeats
    
    virtual const int getNoOfRepeat() const;
    // Description:
    //     Get the number of repeats per period. Only defined when the
    //     period is not WEEKLY.
    // Return value:
    //     The number of repeats per period.
    
    virtual CHA_ExecOrderInterval& operator=(const CHA_ExecOrderInterval& s);
    // Description:
    //     Assignment operator.
    // Return value:
    //     A reference to a ExecOrderInterval.

    virtual RWBoolean operator==(const CHA_ExecOrderInterval& schedule) const;
    // Description:
    //     Equality operator.
    // Return value:
    //     True or false depending on the result of the comparison.

private:

//    RWTime               startTime;              // Starttime with date
    time_t               startTime;
    CHA_RepPeriod        period;
    CHA_DayOfWeek        day;                    // Defined if period = WEEKLY
    int                  noOfRepeat;
    RWBoolean            startDateDefined;
};

#endif
