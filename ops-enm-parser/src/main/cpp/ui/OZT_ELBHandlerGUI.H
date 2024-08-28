// RCS revision handling
// $Id: OZT_ELBHandlerGUI.H,v 21.0 1996/08/23 12:46:31 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME    OZT_ELBHandlerGUI - includes ELB agent in OZT_ELBHandler.
// .LIBRARY
// .HEADER
// .INCLUDE OZT_ELBHandlerGUI.H

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
//	This class is an ELB handler using the ELB agent and is 
//      supposed to be used by programs with a GUI. Apart from the 
//      agent handling nothing is different from OZT_ELBHandler.

// .ERROR HANDLING
//	The method runMode can be used to check for errors. The error
//      text can then be fetched using method getErrorText and
//      displayed in a suitable way.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	

// AUTHOR 
// 	1995-03-13 by EHS/PXE Johan Dykström (qhsjody@ehs.ericsson.se)

// .REVISION
//	B_POINT
//	1996-08-23

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_ELBHandlerGUI.H,v $
// 	Revision 21.0  1996/08/23 12:46:31  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 08:00:46  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:23:52  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:24:59  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:06:35  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:59:33  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:04:44  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:20:30  17:20:30  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.0  1995/10/07 12:03:50  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:12:52  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:27:31  09:27:31  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:06:07  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:41:21  14:41:21  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.0  95/06/07  17:12:46  17:12:46  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 7.0  95/04/16  12:19:11  12:19:11  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 6.0  95/03/17  20:08:18  20:08:18  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 5.0  95/03/16  20:33:33  20:33:33  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 1.1  95/03/15  12:21:51  12:21:51  qhsjody (Johan Dykstrom VK/EHS/PXE)
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

// .SEE ALSO 
// 	OZT_ELBHandler, OZT_ELBErrorTexts

//*****************************************************************************

#ifndef OZT_ELBHANDLERGUI_H
#define OZT_ELBHANDLERGUI_H

#include	<ELB_APP_Agent.H>
#include	<OZT_ELBHandler.H>
#include	<xview/frame.h>

//*****************************************************************************

class OZT_ELBHandlerGUI : public OZT_ELBHandler {

public:

    OZT_ELBHandlerGUI(const RWCString& applName, const RWCString& taskId,
		      RWBoolean doUseELB = TRUE, Frame frame = 0);
    // Description:	
    //     Constructor.
    // Parameters:
    //     applName           IN: the name of the application
    //     taskId             IN: ELB task id
    //     doUseELB           IN: if ELB should be used
    //     frame              IN: a frame for the ELB agent

    virtual ~OZT_ELBHandlerGUI();
    // Description:
    //	   Destructor.

    virtual void addFrame(Frame frame);
    // Description:
    //     To set the base frame for the agent. If the agent already
    //     has a correct frame, the new frame is added to it.
    // Parameters:
    //     frame	      IN: the frame for the agent

    ELBRunMode runMode(RWBoolean recheck = FALSE);
    // Description:
    //     To get the ELB run mode. This method checks that ELB started
    //     OK or if not, if user is allowed to run the application
    //     stand alone.
    // Parameters:
    //     recheck	      IN: if TRUE, everything is rechecked,
    //                            if FALSE, the saved run mode is used
    // Return value:
    //     RUN_WITH_ELB            Everything is OKEY, ELB is used
    //     RUN_STAND_ALONE_OK      ELB not used, user is allowed
    //                             to run without ELB, no error
    //     RUN_STAND_ALONE_ERROR   ELB not started, user is allowed
    //                             to run without ELB, ELB faulty
    //     DONT_RUN                ELB not started, user is not allowed
    //                             to run without ELB, appl. should quit
private:

    ELB_APP_Agent agent_;                   // The ELB agent

};

#endif
