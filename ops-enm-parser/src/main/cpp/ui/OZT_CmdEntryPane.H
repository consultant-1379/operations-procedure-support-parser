// RCS revision handling
// $Id: OZT_CmdEntryPane.H,v 21.0 1996/08/23 12:46:25 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	<ClassName> - <Short description of the class>
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
// 	<General description of the class>

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	%EriDoc_no:%

// AUTHOR 
// 	<Date> by <Dept> <Name>

// .REVISION <for public API>
//	<Revision state>
//	<Revision date>	  	

// .REVISION <for internal header files>
//	%EriDoc_rev:%
//	%EriDoc_date:%  	

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_CmdEntryPane.H,v $
// 	Revision 21.0  1996/08/23 12:46:25  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 08:00:42  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:23:49  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.1  1996/03/11 12:59:22  ehsjasa
// 	Changed PROTOTYPE to OZT_PROTOTYPE.
//
// 	Revision 18.0  1996/03/01 12:24:55  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:06:28  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:59:30  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.1  1995/12/08 16:08:30  epanyc
// 	getSelectedText() function added
//
//      Revision 15.0  95/11/29  02:04:43  02:04:43  ehsgrap (Jan Grape (9 9073) VK/EHS/VE)
//      Made release TB53_OZ, J Grape (EHSGRAP).
//      
//      Revision 14.0  95/11/20  17:20:28  17:20:28  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 1.1  1995/11/16 16:36:40  epanyc
// 	Initial revision
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
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	<link information: libraries needed and order>

// .SEE ALSO 
// 	<Related classes, (abstract) baseclasses, friend classes, ...>

//*****************************************************************************


#ifndef OZT_CMD_ENTRY_PANE_H
#define OZT_CMD_ENTRY_PANE_H

#ifdef OZT_PROTOTYPE

#include <OZT_ErrHandling.H>
#include <OZT_Interpreter.H>
#include <OZT_Indicator.H>
#include <OZT_CmdSender.H>
#include <UIC_TextPane.H>
#include <rw/defs.h>

class OZT_CDFFrame; // forward declaration

class  OZT_CmdEntryPane : public UIC_TextPane
{
public:

    OZT_CmdEntryPane(OZT_CDFFrame *mainFrame);
    // Description:
    //     Constructor.

    void doExecute();
    // Description:
    //     Execute the command at the current line in the pane.

    RWBoolean isReturnPressed();
    // Description:
    //     Check if the user has just pressed a return.

    void enable();
    // Description:
    //     Enable the entry pane so that the user can enter commands.
    
    void disable();
    // Description:
    //     Disable the entry pane so that the user cannot enter commands.

    RWCString getSelectedText();
    // Description:
    //     Get the selected text in the pane.

protected:
    void doInit();
    // Description:
    //     Initialise some internal variables that cannot be initialised
    //     in the constructor.

    OZT_Result doConfirmation(const RWCString &theCmd);
    // Description:
    //     Confirm with the user if the command should be sent or inhibited

    OZT_CDFFrame    *pParentFrame;
    OZT_CmdSender   *pSender;
    OZT_Indicator   *pIndicator;
    OZT_Interpreter *pInterpreter;

private:

    void returnIsPressed();

    static void aReturnPressed(UIC_Window *, UIC_Pane *, int theChar);


    RWBoolean returnPressed;
};
#endif

#endif
