// RCS handling
// $Id: CHA_DayCategory.H,v 24.0 1995/11/28 17:00:28 ehsgrap Rel $

//**********************************************************************
// 
// .NAME CHA_DayCategory - Definition of a DayCategory and it's hash function
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_DayCategory.H 

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
//      Enumeration denoting which day categories are legal in the system. The
//      enumeration is to be used as a hashed set.
//      To do a hashed set you have to have a hash function. In this include
//      file there is very simple  hash function that can be used when 
//	declaring the hashed set.
//      Added enumerations are used by executable orders to describe
//      their schedules to Crontab. These enumerations do not have to be
//      used in a hashed tabel, thus does not have a hash function.

// DOCUMENT NO
//      190 89-CAA 134 1521

// AUTHOR 
//      1994-05-12 by EHS / Marie Moschna (qhsmosc@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_DayCategory.H,v $
//      Revision 24.0  1995/11/28 17:00:28  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:49:21  17:49:21  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:50:05  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:47:36  09:47:36  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:38:48  08:38:48  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:58:10  10:58:10  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:10:58  20:10:58  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:13:08  14:13:08  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:05:13  13:05:13  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:11:55  15:11:55  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:38:46  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:12:11  14:12:11  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:22:36  16:22:36  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:54:13  cmcha
//      Made release PREIT, N L�nninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:08:13  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:35:03  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:56:06  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:27:55  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:55:00  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:53:26  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:45:14  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.1  1994/07/05  12:10:15  qhsmosc
//      Added information for executable orders
//
//      Revision 3.0  1994/06/23  08:00:05  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:01:25  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.2  1994/06/10  16:52:41  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.1  1994/05/17  13:51:30  qhsmosc
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

// .SEE ALSO 
//      

//**********************************************************************

#ifndef CHA_DAYCATEGORY_H
#define CHA_DAYCATEGORY_H

enum CHA_DayCategory {
    CHA_DAYCAT_SUNDAY,
    CHA_DAYCAT_MONDAY,
    CHA_DAYCAT_TUESDAY,
    CHA_DAYCAT_WEDNESDAY,
    CHA_DAYCAT_THURSDAY,
    CHA_DAYCAT_FRIDAY,
    CHA_DAYCAT_SATURDAY,
    CHA_DAYCAT_WEEK_DAY,
    CHA_DAYCAT_BEFORE_HOLIDAY,
    CHA_DAYCAT_HOLIDAY
};

enum CHA_DayOfWeek {
    CHA_DAYWEEK_SUNDAY,
    CHA_DAYWEEK_MONDAY,
    CHA_DAYWEEK_TUESDAY,
    CHA_DAYWEEK_WEDNESDAY,
    CHA_DAYWEEK_THURSDAY,
    CHA_DAYWEEK_FRIDAY,
    CHA_DAYWEEK_SATURDAY,
    CHA_DAYWEEK_NONE
};

enum CHA_RepPeriod 
{ 
    CHA_REPPER_HOURLY, 
    CHA_REPPER_DAILY, 
    CHA_REPPER_WEEKLY, 
    CHA_REPPER_MONTHLY, 
    CHA_REPPER_ANNUALLY, 
    CHA_REPPER_NONE
};

//inline unsigned int hashDayCategory(const CHA_DayCategory& d) {return d;};

//inline unsigned int hashDayCategory(CHA_DayCategory& d, myHash, std::equal_to<CHA_DayCategory>) {return d;};
//inline unsigned int hashDayCategory(CHA_DayCategory& d, myHashDayCategory, std::equal_to<int>) {return d;};
// Description:
//     Hash function used by RWTValHashSet.
// Parameter:
//     d       Day category
// Return value:
//     An unsigned with hash value for inparameter.

#endif
