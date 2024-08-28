// RCS revision handling
// $Id: OZT_FileBrowser.H,v 21.0 1996/08/23 12:46:36 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_FileBrowser - Popup window containing a file browser
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
// 	Creates a popup window containing a file browser.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	%EriDoc_no:%

// AUTHOR 
// 	94/12/12 by ETL/XV/B  Neil Harding

// .REVISION <for public API>
//	<Revision state>
//	<Revision date>	  	

// .REVISION <for internal header files>
//	%EriDoc_rev:%
//	%EriDoc_date:%  	

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_FileBrowser.H,v $
// 	Revision 21.0  1996/08/23 12:46:36  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 08:00:50  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:23:54  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:25:04  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:06:41  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:59:37  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:04:48  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.1  95/11/28  14:51:43  14:51:43  epanyc (Nelson Cheng VK/EHS/PXE)
//      a variable is added to avoid re-read directory all the time
//      
//      Revision 14.0  1995/11/20  17:20:35  ehsjasa
//      Made release POW_TB3, J Sandquist (EHSJASA).
//
// 	Revision 13.0  1995/10/07 12:03:55  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:12:57  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:27:35  09:27:35  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:06:14  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:41:25  14:41:25  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.0  95/06/07  17:12:50  17:12:50  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 7.1  95/05/18  11:07:18  11:07:18  etlnei (Neil Harding VK/EHS/PXE)
//      *** empty log message ***
//      
//      Revision 7.0  1995/04/16  12:19:15  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.0  95/03/17  20:08:22  20:08:22  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 5.0  95/03/16  20:33:37  20:33:37  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 4.2  95/03/15  20:19:33  20:19:33  epanyc (Nelson Cheng VK/EHS/PXE)
//      setMessage() added
//      
//      Revision 4.1  1995/03/01  12:10:39  etlnei
//      checked in while I go to England
//
//      Revision 4.0  1995/02/23  21:48:03  cmcha
//      Made release TB4, J Grape (EHSGRAP).
//
//      Revision 3.2  95/02/23  08:49:02  08:49:02  epanyc (Nelson Cheng VK/EHS/PXE)
//      a client parameter is added to the constructor
//      
//      Revision 3.1  1995/02/21  12:00:09  epanyc
//      #include "OZT_CDFFrame.H" is removed
//
//      Revision 3.0  1995/02/06  21:01:53  cmcha
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 2.10  95/02/05  15:07:48  15:07:48  ehsgrap (Jan Grape (9 9073) VK/EHS/PXE)
//      Replaced UIC_NoBtnsFileBrowser with UIC_FileBrowser.
//      
//      Revision 2.9  1995/02/03  15:29:17  etlnei
//      removed doneNotify()
//
//      Revision 2.8  1995/02/03  14:19:36  etlnei
//      second happy test release
//
//      Revision 2.7  1995/01/31  11:44:58  etlnei
//      checked in for Nelson to compile
//
//      Revision 2.6  1995/01/26  09:55:40  etlnei
//      checked in for Eric to compile
//
//      Revision 2.5  1995/01/16  10:13:25  etlnei
//      *** empty log message ***
//
//      Revision 2.4  1995/01/09  11:49:21  etlnei
//      part way through adding a starting path
//
//      Revision 2.3  1994/12/21  16:16:16  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 2.0  94/12/21  13:54:54  13:54:54  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//      
//      Revision 1.2  1994/12/12  12:28:14  epanyc
//      comment style changed for RCS
//
//      Revision 1.1  94/12/12  11:15:57  11:15:57  etlnei (Neil Harding VK/EHS/PXE)
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
//	TB2     1994-12-21      J Grape (EHSGRAP)       RCS rev 2.0
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	<link information: libraries needed and order>

// .SEE ALSO 
// 	<Related classes, (abstract) baseclasses, friend classes, ...>

//*****************************************************************************


#ifndef OZT_FILEBROWSER_H 
#define OZT_FILEBROWSER_H

#include <CHA_OZTInfo.H>
#include <UIC_Button.H>
#include <UIC_ItemRow.H>
#include <UIC_Menu.H>
#include <UIC_MenuItem.H>
#include <UIC_Message.H>
#include <UIC_FileBrowser.H>
#include <UIC_Panel.H>
#include <UIC_Popup.H>
#include "OZT_CDFDef.H"


typedef int (*OZT_IntCallback)(UIC_Window *);

class  OZT_FileBrowser : public UIC_Popup
{

public:

    OZT_FileBrowser(const int nls_index,
                    UIC_Window& window,
                    UIC_Window* client,
                    const int nls_button,
                    OZT_IntCallback callback,
                    RWCString path,
                    RWBoolean msg = FALSE);
    // Description:
    //     Constructor. Constructs a window containing a file browser 
    // Parameters:
    //     nls_index       NLS string for the popup window title
    //     window          parent window
    //     client          client to be passed when the callback is called
    //     nls_button      NLS string for the button
    //     callback        callback routine for when a file is entered
    //     path            The initial directory path
    //     msg             True if a message is to be displayed in the browser


    ~OZT_FileBrowser();
    // Description:
    //     Destructor.


    UIC_FileBrowser* get_FileBrowser(void);
    // Description:
    //     Get a pointer to the UIC_FileBrowser object used
    // Return Value:
    //     The pointer to the UIC_FileBrowser used.

    void setMessage(const RWCString &msg);
    // Description:
    //     set the message in the browser.
    
protected:

private:
    CHA_OZTInfo            ozt_info;

    UIC_Window            *myClient;
    UIC_Button             apply_button;
    UIC_Button             goto_button;
    UIC_ItemRow            button_row;
    UIC_Menu               goto_menu;
    UIC_MenuItem           central_mi;
    UIC_MenuItem           private_mi;
    UIC_Message            theMessage;
    UIC_FileBrowser        browser;
    UIC_Panel              browser_panel;
    OZT_IntCallback        button_callback;
    RWBoolean              msgAllowed;
    RWBoolean              needToReadDir;

    static void   a_apply(UIC_Window* win, UIC_PanelItem* pi);
    static void   a_central(UIC_Window *win, UIC_MenuItem *mi);
    static void   a_private(UIC_Window *win, UIC_MenuItem *mi);

    void          do_apply(void);
    void          do_central(void);
    void          do_private(void);
    void          showNotify(void);

};

#endif
