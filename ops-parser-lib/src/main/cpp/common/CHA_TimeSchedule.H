// RCS handling
// $Id: CHA_TimeSchedule.H,v 24.0 1995/11/28 16:55:12 ehsgrap Rel $

//**********************************************************************
// 
// .NAME CHA_TimeSchedule - the base class for time schedules.
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_TimeSchedule.H 

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
//      The base class for time schedules. This class contains a time
//      interval with a start and stop and time. The date can be
//      obtained from the time. 

// DOCUMENT NO
//      190 89-CAA 134 1515

// AUTHOR 
//      1994-02-17 by EHS/PXE Martin Carlsson (ehscama@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_TimeSchedule.H,v $
//      Revision 24.0  1995/11/28 16:55:12  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:41:32  17:41:32  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:44:06  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:40:02  09:40:02  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:32:44  08:32:44  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:52:06  10:52:06  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:04:22  20:04:22  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:02:48  14:02:48  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  12:58:15  12:58:15  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:00:18  15:00:18  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:33:08  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:02:41  14:02:41  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:13:32  16:13:32  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:45:13  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:01:52  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:28:38  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:48:07  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:22:29  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:49:35  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:44:28  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:37:05  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:51:49  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:04:08  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.5  1994/06/09  15:25:36  ehsgrap
//      Made private members protected.
//
//      Revision 1.4  1994/03/04  13:01:20  ehscama
//      Start and stop representation changed to use only RWTime.
//      setStartDate and setStopDate methods are removed.
//
//      Revision 1.3  1994/02/23  09:20:40  ehsgrap
//      Added copy constructor and operator=
//
//      Revision 1.2  1994/02/22  10:16:54  ehsgrap
//      Small corrections for first compilation.
//
//      Revision 1.1  1994/02/22  09:08:37  ehscama
//      Initial revision.
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

// .SEE ALSO 
//      RWDate, RWTime

//**********************************************************************

#ifndef CHA_TIMESCHEDULE_H
#define CHA_TIMESCHEDULE_H

#include <rw/tools/datetime.h>

static const long CHA_DEFAULT_MIN_ADDITION  = 5;
static const long CHA_DEFAULT_HOUR_ADDITION = 24;

class CHA_TimeSchedule
{

public:

    CHA_TimeSchedule(const RWDateTime& t1, const RWDateTime& t2);
    // Description:
    //     Constructor. Construct CHA_TimeSchedule with the
    //     specified start and stop time.
    // Parameters: 
    //     t1                   In: The start time
    //     t2                   In: The stop time
    
    CHA_TimeSchedule();
    // Description:
    //     Default constructor. Default start date and time
    //     is now + CHA_DEFAULT_MIN_ADDITION minutes. Default
    //     stop date and time is now + CHA_DEFAULT_HOUR_ADDITION
    //     hours and DEAFULT_MIN_ADDITION minutes.

    CHA_TimeSchedule(const CHA_TimeSchedule& other);
    // Description:
    //     Copy constructor.
    // Parameters:
    //     other		In: The CHA_TimeSchedule to copy from.

    virtual ~CHA_TimeSchedule();
    // Description:
    //     Destructor.
    
    virtual CHA_TimeSchedule& operator=(const CHA_TimeSchedule& other);
    // Description:
    //     Assignment operator.
    // Parameters:
    //     other		In: The CHA_TimeSchedule to copy from.
    // Return value:
    //     A reference to the object itself.

    virtual RWDateTime getStartDate() const ;
    // Description:
    //     Get the start date.
    // Return value: 
    //     RWDate               The start date.
    
    virtual void setStartTime(const RWDateTime& t);
    // Description:
    //     Set the start time.
    // Parameters: 
    //     t                    In: The start time.
    
    virtual RWDateTime getStartTime() const;
    // Description:
    //     Get the start time.
    // Return value: 
    //     RWTime               The start time.
    
    virtual RWDateTime getStopDate() const;
    // Description:
    //     Get the stop date.
    // Return value: 
    //     RWDate               The stop date.
    
    virtual void setStopTime(const RWDateTime& t);
    // Description:
    //     Set the stop time.
    // Parameters: 
    //     t                    In: The stop time.
    
    virtual RWDateTime getStopTime() const;
    // Description:
    //     Get the stop time.
    // Return value:
    //     RWTime               The stop time.
 
protected:
    RWDateTime startTime;
    RWDateTime stopTime;
    
};

#endif
