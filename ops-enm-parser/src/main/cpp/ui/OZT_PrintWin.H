// RCS revision handling
// $Id: OZT_PrintWin.H,v 21.0 1996/08/23 12:46:45 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_PrintWin - Popup window for sending a file to the printer
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
// 	Creates a popup window containg a file browser and a list of
//      printers. Handles the printing of a file or a portion of a file.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	%EriDoc_no:%

// AUTHOR 
// 	1994-01-23 by ETL/XN/DSN Neil Harding

// .REVISION <for public API>
//	<Revision state>
//	<Revision date>	  	

// .REVISION <for internal header files>
//	%EriDoc_rev:%
//	%EriDoc_date:%  	

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_PrintWin.H,v $
// 	Revision 21.0  1996/08/23 12:46:45  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 08:00:57  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:23:58  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:25:12  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:06:51  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:59:43  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.1  1995/11/30 17:09:49  ehsjasa
// 	Removed a private variable that's not used anymore.
//
// 	Revision 15.0  1995/11/29 02:04:52  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:20:42  17:20:42  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.0  1995/10/07 12:04:01  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:13:06  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:27:42  09:27:42  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:06:21  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:41:34  14:41:34  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.0  95/06/07  17:12:58  17:12:58  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 7.1  95/05/18  11:07:18  11:07:18  etlnei (Neil Harding VK/EHS/PXE)
//      *** empty log message ***
//      
//      Revision 7.0  1995/04/16  12:19:24  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.0  95/03/17  20:08:29  20:08:29  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 5.0  95/03/16  20:33:43  20:33:43  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 4.0  95/02/23  21:48:10  21:48:10  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB4, J Grape (EHSGRAP).
//      
//      Revision 3.1  95/02/21  09:27:21  09:27:21  etlnei (Neil Harding VK/EHS/PXE)
//      Changes made after hearing comments from Telstra
//      
//      Revision 3.0  1995/02/06  21:02:01  cmcha
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 1.4  95/02/03  14:19:36  14:19:36  etlnei (Neil Harding VK/EHS/PXE)
//      second happy test release
//      
//      Revision 1.3  1995/01/31  11:44:58  etlnei
//      checked in for Nelson to compile
//
//      Revision 1.2  1995/01/26  10:43:54  etlnei
//      corrected the wrong comment style
//
//      Revision 1.1  1995/01/26  10:41:24  etlnei
//      Initial revision
//
//      Revision 1.1  1995/01/26  09:55:40  etlnei
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


#ifndef OZT_PRINTWIN_H 
#define OZT_PRINTWIN_H

#include "OZT_CDFFile.H"
#include "OZT_CDFFrame.H"

#include <CHA_PrinterList.H>
#include <UIC_Button.H>
#include <UIC_Choices.H>
#include <UIC_FileBrowser.H>
#include <UIC_Menu.H>
#include <UIC_MenuItem.H>
#include <UIC_Panel.H>
#include <UIC_Popup.H>
#include <UIC_TextField.H>
#include <UIC_Window.H>
#include "OZT_CDFDef.H"

class OZT_CDFFile;
class OZT_CDFFrame;

class  OZT_PrintWin : public UIC_Popup
{

public:

    OZT_PrintWin(const int nls_index, UIC_Window& window);
    // Description:
    //     Constructor. Opens a window for sending files to a printer 
    // Parameters:
    //     nls_index       NLS string for the popup window
    //     window          parent window


    ~OZT_PrintWin();
    // Description:
    //     Destructor.

    
protected:

private:
    CHA_PrinterList  printer_list;

    UIC_Choices      printer_choice;
    UIC_Button       apply_button;
    UIC_FileBrowser  browser;
    UIC_Panel        print_panel;

    UIC_Menu         print_menu;
    UIC_MenuItem     print_file;
    UIC_MenuItem     print_sel;

    static void a_print_file (UIC_Window* wp, UIC_MenuItem* mi);
    static void a_print_sel (UIC_Window* wp, UIC_MenuItem* mi);

    static void a_print_choice(UIC_Window *win, UIC_PanelItem *pi);

    void          do_print_file (void);
    void          do_print_sel (void);

    void          showNotify(void);

    OZT_CDFFrame  *cdf;
};

#endif
