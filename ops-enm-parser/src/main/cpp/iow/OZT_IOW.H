// RCS revision handling
// $Id: OZT_IOW.H,v 21.0 1996/08/23 12:41:07 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_IOW - Input/Output windows for the run-time environment
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
// 	This file defines a number of virtual base class for 
//      run-time related user interface objects.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	190 89-CAA 134 2015

// AUTHOR 
// 	1994-12-08 by Nelson Cheng (epanyc@epa.ericsson.se)

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_IOW.H,v $
// 	Revision 21.0  1996/08/23 12:41:07  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 07:55:50  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:21:29  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:19:44  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 11:59:59  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:56:02  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:01:43  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:14:52  17:14:52  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.0  1995/10/07 11:59:51  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:06:59  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:23:33  09:23:33  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 10:59:31  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.1  95/07/05  09:38:42  09:38:42  epanyc (Nelson Cheng VK/EHS/PXE)
//      comment added
//      
//      Revision 9.0  1995/06/29  14:36:07  cmcha
//      Made release EC2_OZ, J Grape (EHSGRAP).
//
//      Revision 8.1  95/06/28  14:38:02  14:38:02  epanyc (Nelson Cheng VK/EHS/PXE)
//      comment added
//      
//      Revision 8.0  1995/06/07  17:06:52  cmcha
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//
//      Revision 7.0  95/04/16  12:14:36  12:14:36  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 6.0  95/03/17  20:03:28  20:03:28  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 5.0  95/03/16  20:29:31  20:29:31  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 4.1  95/03/02  21:32:43  21:32:43  epanyc (Nelson Cheng VK/EHS/PXE)
//      prompt object changed
//      
//      Revision 4.0  1995/02/23  21:44:13  cmcha
//      Made release TB4, J Grape (EHSGRAP).
//
//      Revision 3.3  95/02/23  14:04:28  14:04:28  epanyc (Nelson Cheng VK/EHS/PXE)
//      getInput changed
//      
//      Revision 3.2  1995/02/23  13:29:17  epanyc
//      prototype changed for selfile
//
//      Revision 3.1  1995/02/20  16:31:01  epanyc
//      getInput changed
//
//      Revision 3.0  1995/02/06  20:56:07  cmcha
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 2.10  95/02/03  13:21:40  13:21:40  epanyc (Nelson Cheng VK/EHS/PXE)
//      default value added
//      
//      Revision 2.9  95/01/31  10:35:39  10:35:39  epanyc (Nelson Cheng VK/EHS/PXE)
//      OZT_Prompt file added
//      
//      Revision 2.8  1995/01/27  13:13:51  epanyc
//      prototype for fileviewer changed
//
//      Revision 2.7  1995/01/26  13:15:07  epanyc
//      file viewer added
//
//      Revision 2.6  1995/01/18  12:53:12  epanyc
//      file browser virtual class added
//
//      Revision 2.5  1995/01/16  08:36:38  epanyc
//      input popup added
//
//      Revision 2.4  95/01/09  12:55:02  12:55:02  epanyc (Nelson Cheng VK/EHS/PXE)
//      virtual base class for input popup created
//      
//      Revision 2.3  1994/12/21  16:01:16  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 2.1  94/12/21  15:15:20  15:15:20  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//      
//      Revision 2.0  94/12/21  13:45:22  13:45:22  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//      
//      Revision 1.1  1994/12/08  10:10:07  epanyc
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
//	TB2     1994-12-21      J Grape (EHSGRAP)       RCS rev 2.3
//	TB2     1994-12-21      J Grape (EHSGRAP)       RCS rev 2.1
//	TB2     1994-12-21      J Grape (EHSGRAP)       RCS rev 2.0
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	<link information: libraries needed and order>

// .SEE ALSO 
// 	<Related classes, (abstract) baseclasses, friend classes, ...>

//*****************************************************************************


#ifndef OZT_IOW_H
#define OZT_IOW_H

#include <OZT_Value.H>
#include <OZT_ErrHandling.H>
#include <rw/defs.h>
#include <rw/cstring.h>
#include <rw/tvordvec.h>

class OZT_IOW {
public:
    static const char *drawCup;
    static const char *drawBox;
    static const char *drawHigh;
    static const char *drawLow;
    static const char *drawInv;
    // Description
    //     A number of contstants to be used by the parser for specifying
    //     CUP, BOX, HIGH, LOW and INV for the @DRAW command.
    //     Refer to the varaccess grammar rule of the parser.

    static const char *styleBold;
    static const char *styleItal;
    static const char *styleUndrln;
    static const char *stylePlain;


    static const char *timeSec;
    static const char *timeMin;
    static const char *timeHour;

    static const char *padLeft;
    static const char *padRight;
    static const char *padCenter;
    
    static const char* NOVARIABLE;

    virtual void open() = 0;
    // Description
    //     Open the IO window.

    virtual void close() = 0;
    // Description
    //     Close the IO window.

    virtual void clrscr() = 0;
    // Description
    //     Clear the contents of the IO window.

    virtual OZT_Result draw(RWTValOrderedVector<OZT_Value> &spec) = 0;
    // Description
    //     Draw a number of items to the IO window.
    // Parameter
    //     spec    IN: a vector of OZT_Value's that gives
    //                 the specification about the drawing.
    //                 The values are directly obtained from the
    //                 parser. This function performs validation.

    virtual OZT_Result form(RWTValOrderedVector<OZT_Value> &spec,
                            RWTValOrderedVector<RWCString> &ans) = 0;
    // Description
    //     Open a form for user input.
    // Parameter
    //     spec    IN: a vector of OZT_Value's that gives the
    //                 specification about the form. The number of
    //                 items must be in the multiple of four. Each
    //                 lot of four defines an input field.
    //     ans     OUT: a vector of user input value that typed into
    //                  the input fields.

    virtual OZT_Result menu(OZT_Value &selectedValue,
                            const OZT_Value &nLeftChoices,
                            const OZT_Value &nRightChoices) = 0;
    // Description
    //     Open a menu for user input.
    // Parameter
    //     selectedValue   OUT: the number of the choice that the user
    //                          has selected.
    //     nLeftChoices    IN: the number of choices that should be
    //                         on the left side of the menu.
    //     nRightChoices   IN: the number of choices that should be
    //                         on the right side of the menu.

    virtual void interrupt() = 0;
    // Description
    //     To be called in the middle of executing form() or menu(),
    //     this function terminates the input immediately.

    virtual OZT_Result setTimeout( const OZT_Value& label,
				   const OZT_Value& time,
				   const OZT_Value& unit ) = 0;

    virtual RWCString getTimeoutLabel() = 0;
    virtual void resetTimeout() = 0;
};

//**********************************************************************

class OZT_InputPopup {
public:
    virtual OZT_Result getInput(RWCString promptMsg,
                                RWCString defaultValue,
				RWBoolean toFormat,
                                RWCString &usrInput) = 0;
    // Description
    //     Obtain user input by using the popup.
    // Parameter
    //     promptMsg      IN: the prompt message
    //     defaultValue   IN: the default value that should be supplied in
    //                        the input field
    //     usrInput       OUT: the user input value


    virtual void interrupt() = 0;
    // Description
    //     To be called in the middle of getting user input. This
    //     function makes getInput() returns immediately.

  virtual OZT_Result setTimeout( const OZT_Value& label,
				 const OZT_Value& time,
				 const OZT_Value& unit ) = 0;

  virtual RWCString getTimeoutLabel() = 0;
  virtual void resetTimeout() = 0;
};

//**********************************************************************

class OZT_FileSelectPopup {
public:
    virtual OZT_Result selFile(const RWCString &mask,
                               const RWCString &promptMsg,
                               RWCString &usrInput) = 0;
    // Description
    //     Open the file browser and obtain the user input.
    // Parameter
    //     mask         IN: a directory mask for filtering files
    //     promptMsg    IN: a prompt message to be displayed in the file browser
    //     usrInput     OUT: the full path name of the file selected
    //                       by the user.

    virtual void interrupt() = 0;
    // Description
    //     To be called in the middle of getting user input. This
    //     function makes selFile() returns immediately.
};

//**********************************************************************

class OZT_FileViewerPopup {
public:
    virtual OZT_Result view(RWCString fileName) = 0;
    // Description
    //     Open the file viewer and let the user view the content
    //     of a specified file. 
    // Parameter
    //     fileName   IN: the full path name of a specified file

    virtual void interrupt() = 0;
    // Description
    //     To be called in the middle of viewing a file. This function
    //     makes view() returns immediately.
};

//**********************************************************************

class OZT_PromptNotice {
public:
    enum Answer {TO_CONTINUE, TO_STOP, TO_STOP_N_QUIT, TIMEOUT};

  virtual OZT_Result setTimeout( const OZT_Value& label,
				 const OZT_Value& time,
				 const OZT_Value& unit ) = 0;

  virtual RWCString getTimeoutLabel() = 0;
  virtual void resetTimeout() = 0;

  virtual Answer askContinue() = 0;
  // Description
  //     Put up a notice and ask the user whether to continue.
};

#endif
