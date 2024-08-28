// RCS revision handling
// $Id: OZT_Props.H,v 21.0 1996/08/23 12:46:47 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_Props - Properties window
// .LIBRARY 3C++
// .PAGENAME <CLASSNAME>
// .HEADER  <SSN><API>/<FBN> 
// .LEFT_FOOTER Ericsson HP
// .INCLUDE <filename>

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
// 	Creates a popup window used for setting properties. The properties
//      are managed using the User Interface Components class UIC_PropHandler.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	%EriDoc_no:%

// AUTHOR 
// 	1995-01-04 by ETL/XV/BN Neil Harding

// .REVISION <for public API>
//	<Revision state>
//	<Revision date>	  	

// .REVISION <for internal header files>
//	%EriDoc_rev:%
//	%EriDoc_date:%  	

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_Props.H,v $
// 	Revision 21.0  1996/08/23 12:46:47  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 08:00:59  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:23:59  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:25:14  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:06:54  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:59:44  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:04:54  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:20:44  17:20:44  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.2  1995/11/03 14:39:06  epanyc
// 	window size props added
//
//      Revision 13.1  1995/10/31  08:23:03  epanyc
//      position update choice added
//
//      Revision 13.0  1995/10/07  12:04:03  ehsjasa
//      Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:13:08  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:27:44  09:27:44  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:06:24  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:41:35  14:41:35  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.0  95/06/07  17:13:00  17:13:00  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 7.1  95/05/18  11:07:18  11:07:18  etlnei (Neil Harding VK/EHS/PXE)
//      *** empty log message ***
//      
//      Revision 7.0  1995/04/16  12:19:26  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.0  95/03/17  20:08:31  20:08:31  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 5.0  95/03/16  20:33:45  20:33:45  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 4.0  95/02/23  21:48:11  21:48:11  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB4, J Grape (EHSGRAP).
//      
//      Revision 3.1  95/02/10  11:38:26  11:38:26  etlnei (Neil Harding VK/EHS/PXE)
//      added property for mouse accelerators (tag, breakpoints, set position)
//      
//      Revision 3.0  1995/02/06  21:02:04  cmcha
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 1.2  95/01/16  10:13:25  10:13:25  etlnei (Neil Harding VK/EHS/PXE)
//      made it work
//      
//      Revision 1.1  1995/01/09  11:49:21  etlnei
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


#ifndef OZT_PROPS_H 
#define OZT_PROPS_H

#include "OZT_CDFFrame.H"
#include <CHA_Model.H>
#include <UIC_Button.H>
#include <UIC_Choices.H>
#include <UIC_Panel.H>
#include <UIC_Popup.H>
#include "UIC_PropHandler.H"

typedef void (*OZT_Callback)(UIC_Window *);

class  OZT_Props : public UIC_Popup, public CHA_Model
{

public:

    OZT_Props(const int nls_index, UIC_Window& window);
    // Description:
    //     Constructs a properties window for the Ozterm debugger 
    // Parameters:
    //     nls_index       NLS string for the popup window title
    //     window          parent window

    ~OZT_Props();
    // Description:
    //     Destructor.

    int        codeWinSize(void);
    // Description:
    //     Returns the current property value of the code window size.
    // Return value:
    //   0 - Small
    //   1 - Medium
    //   2 - Large

    int        posUpdate(void);
    // Description:
    //     Returns the current property value of position update.
    // Return value:
    //   0 - Always
    //   1 - Step Only

    int        warnings(void);
    // Description:
    //     Returns the current property value of warnings.
    // Return value:
    //   0 = Always
    //   1 = Never

    int        breakpoints_acc(void);
    // Description:
    //    Returns the current property value of the set breakpoints accelerator.
    // Return value:
    //   0 = accelearator disabled
    //   1 = accelearator enabled

    int        position_acc(void);
    // Description:
    //    Returns the current property value of the set position accelerator.
    // Return value:
    //   0 = accelearator disabled
    //   1 = accelearator enabled

    int        tags_acc(void);
    // Description:
    //    Returns the current property value of the set tags accelerator.
    // Return value:
    //   0 = accelearator disabled
    //   1 = accelearator enabled

protected:

private:
    UIC_Button         apply_button;
    UIC_Button         reset_button;
    UIC_Button         set_button;
    UIC_Choices        codeWinSize_choice;
    UIC_Choices        posUpdate_choice;
    UIC_Choices        accelerator_choice;
    UIC_Choices        warnings_choice;
    UIC_ItemRow        props_button_row;
    UIC_Panel          props_panel;

    UIC_PropHandler    *props_handler;  

    static int a_reset(UIC_Button & button, Update_type type, int changed);
    static int a_set(UIC_Button & button, Update_type type, int changed);

    int        do_set(void);

};

#endif
