// RCS revision handling
// $Id: OZT_TimeOrder.H,v 21.0 1996/08/23 12:43:18 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_TimeOrderHandler - Interface class for making time event order
// .LIBRARY CHOZTBIN
// .PAGENAME OZT_TimeOrderHandler
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
// 	This class provides an interface for the interpreter to make use
//      of CHALIB features for making time order.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	190 89-CAA 134 2016

// AUTHOR 
// 	1994-12-22 by Nelson Cheng (epanyc@epa.ericsson.se)

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_TimeOrder.H,v $
// 	Revision 21.0  1996/08/23 12:43:18  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 07:57:50  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:22:31  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:21:55  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:02:20  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:57:32  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:03:02  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:17:28  17:17:28  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.0  1995/10/07 12:01:43  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:09:43  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:25:23  09:25:23  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:02:42  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.2  95/07/05  09:15:20  09:15:20  epanyc (Nelson Cheng VK/EHS/PXE)
//      comment added
//      
//      Revision 9.1  1995/06/30  09:34:07  epanyc
//      #include to OZT_TimeUtility removed
//
//      Revision 9.0  95/06/29  14:38:16  14:38:16  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.2  95/06/28  14:32:14  14:32:14  epanyc (Nelson Cheng VK/EHS/PXE)
//      comment added
//      
//      Revision 8.1  1995/06/16  12:10:25  epanyc
//      display supported for @TIMEEVSET
//
//      Revision 8.0  95/06/07  17:09:30  17:09:30  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 7.0  95/04/16  12:16:40  12:16:40  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 6.1  95/04/03  13:26:44  13:26:44  epatse (Eric Tse VK/EHS/PXE)
//      A new parameter "extSystem" is added for the function setTimeEvent().
//      
//      Revision 6.0  1995/03/17  20:05:45  cmcha
//      Made release TB51_OZ, ehscama.
//
//      Revision 5.0  95/03/16  20:31:29  20:31:29  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 4.3  95/03/14  15:32:10  15:32:10  epatse (Eric Tse VK/EHS/PXE)
//      theExecOrderList becomes a pointer ptheExecOrderList
//      
//      Revision 4.2  1995/03/14  15:03:51  epatse
//      check in after some chanegs.
//
//      Revision 4.1  1995/03/02  10:21:33  epatse
//      new function added
//
//      Revision 4.0  1995/02/23  21:46:14  cmcha
//      Made release TB4, J Grape (EHSGRAP).
//
//      Revision 3.1  95/02/23  08:51:15  08:51:15  epatse (Eric Tse VK/EHS/PXE)
//      Change CHA_CmdFileOrder.H to CHA_OztCmdFileOrder.H
//      
//      Revision 3.0  1995/02/06  20:58:06  cmcha
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 1.3  95/01/24  08:34:11  08:34:11  epatse (Eric Tse VK/EHS/PXE)
//      Time Schedule functions implemented
//      
//      Revision 1.2  1995/01/10  15:55:47  epatse
//      *** empty log message ***
//
//      Revision 1.1  1994/12/22  15:54:05  epanyc
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
//	TB4     1995-02-23      J Grape (EHSGRAP)       RCS rev 4.0
//	TB3     1995-02-06      J Grape (EHSGRAP)       RCS rev 3.0
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	<link information: libraries needed and order>

// .SEE ALSO 
// 	<Related classes, (abstract) baseclasses, friend classes, ...>

//*****************************************************************************

#ifndef OZT_TIME_ORDER_H
#define OZT_TIME_ORDER_H


#include <rw/cstring.h>
#include <OZT_Value.H>
/// TODO #include <CHA_OrderList.H>
/// TODO #include <CHA_OztCmdFileOrder.H>
/// TODO #include <CHA_ExecOrderList.H>
/// TODO #include <CHA_ExecOrderInterval.H>
#include <CHA_OrderList.H>
#include <CHA_OztCmdFileOrder.H>
#include <CHA_ExecOrderList.H>
#include <CHA_ExecOrderInterval.H>

extern const RWCString ozt_emptyLabel;

class OZT_TimeOrderHandler
{
public:

    OZT_TimeOrderHandler(const RWCString &theDisplayInfo = (const char*)"");
    // Description
    //     Constructor.
    // Parameter
    //     theDisplayInfo    IN: the name of the display to be used
    //                           for the time order.


    ~OZT_TimeOrderHandler();
    // Description
    //    Destructor.


    OZT_Value setTimeEvent(const RWCString &currFileName,
                           const RWCString &label, 
                           const RWCString &dateTimeExp,
                           RWBoolean useDisplay);
    // Description
    //     set up an order. A default mail is sent to the current user.
    // Parameter
    //     See the overloaded function below
    // Return value
    //     See the overloaded function below.


    OZT_Value setTimeEvent(const RWCString &currFileName,
                           const RWCString &label, 
                           const RWCString &dateTimeExp,
                           RWBoolean useDisplay,
                           const RWCString &mailAddress,
                           const RWCString &extSystem);
    // Description
    //     Set up an order. This function takes more parameters, it is
    //     here in case @TIMEEVSET is modified in the future to take more
    //     parameters.
    // Parameter
    //     currFileName   IN: the name of the file setting up this order.
    //                        (which is also the file to run when the
    //                        event starts.)
    //     label          IN: the label for commencement
    //     dateTimeExp    IN: the time and date for starting the event
    //     useDisplay     IN: use the GUI version if TRUE else the NUI version
    //     mailAddress    IN: a list of user that will receive the exec result 
    //     extSystem      IN: the external system to be connected for the event
    // Return value
    //     OZT_Value(0L)  - Successful
    //     OZT_Value(1L)  - Fails somewhere during making order
    //     OZT_Value(2L)  - The dateTimeExp is already past
    //     OZT_Value(3L)  - Start time too close
    

    void      clearTimeEvent(const RWCString &currFileName, 
                             const RWCString &label = ozt_emptyLabel);
    // Description
    //     Remove orders setup previously.
    // Parameter
    //     currFileName   IN: the name of the command file in the order
    //     label          IN: when used, only the orders that starts on this
    //                        label will be removed.


    RWBoolean eventLoaded(const RWCString &currFileName, 
                          const RWCString &label = ozt_emptyLabel);
    // Description
    //     Check if an event is set up to run a file at a particular label.
    // Parameter
    //     currFileName   IN: the name of the command file to be checked


    RWCString getSched(const RWCString &currFileName);
    // Description
    //     Get the time that the current file has been scheduled to run in AM.
    // Parameter
    //     currFileName   IN: the name of the command file to be checked


    void setDisplay(const RWCString &currentDisplay);
    // Description
    //     Set the display.
    // Parameter
    //     currentDisplay   IN: the current display

private:    
/// TODO    CHA_ExecOrderList     *ptheExecOrderList;
    CHA_ExecOrderList     *ptheExecOrderList;
    RWCString              displayInfo;
};

#endif
