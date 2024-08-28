// RCS revision handling
// $Id: OZT_ViewSelectFile.H,v 21.0 1996/08/23 12:46:52 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_ViewSelectFile - Popup containing a list of loaded files.
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
// 	Creates a popup window to display a list of all the files that
//      have been loaded into the developer. The list is kept up to date
//      by calling fill_list() after a change has been made.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	%EriDoc_no:%

// AUTHOR 
// 	1994/11/03 by ETL/XV/B  Neil Harding

// .REVISION <for public API>
//	<Revision state>
//	<Revision date>	  	

// .REVISION <for internal header files>
//	%EriDoc_rev:%
//	%EriDoc_date:%  	

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_ViewSelectFile.H,v $
// 	Revision 21.0  1996/08/23 12:46:52  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 08:01:03  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:24:01  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:25:18  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:07:00  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:59:47  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:04:56  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:20:48  17:20:48  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.0  1995/10/07 12:04:06  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:13:14  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:27:48  09:27:48  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:06:28  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:41:39  14:41:39  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.0  95/06/07  17:13:04  17:13:04  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 7.1  95/05/18  11:07:18  11:07:18  etlnei (Neil Harding VK/EHS/PXE)
//      *** empty log message ***
//      
//      Revision 7.0  1995/04/16  12:19:30  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.1  95/03/24  15:43:21  15:43:21  etlnei (Neil Harding VK/EHS/PXE)
//      checked in to use some new UIC stuff
//      
//      Revision 6.0  1995/03/17  20:08:37  cmcha
//      Made release TB51_OZ, ehscama.
//
//      Revision 5.0  95/03/16  20:33:49  20:33:49  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 4.1  95/03/01  12:10:39  12:10:39  etlnei (Neil Harding VK/EHS/PXE)
//      checked in while I go to England
//      
//      Revision 4.0  1995/02/23  21:48:13  cmcha
//      Made release TB4, J Grape (EHSGRAP).
//
//      Revision 3.0  95/02/06  21:02:05  21:02:05  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 2.4  95/02/03  14:19:36  14:19:36  etlnei (Neil Harding VK/EHS/PXE)
//      second happy test release
//      
//      Revision 2.3  1994/12/21  16:16:27  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 2.0  94/12/21  13:55:02  13:55:02  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//      
//      Revision 1.3  1994/12/02  10:35:25  etlnei
//      version uised for "happy testing"
//
//      Revision 1.2  94/11/17  08:41:56  08:41:56  etlnei (Neil Harding VK/EHS/PXE)
//      now handles multiple files
//      
//      Revision 1.1  1994/11/03  10:15:33  etlnei
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


#ifndef OZT_VIEWSELECTFILE_H 
#define OZT_VIEWSELECTFILE_H

#include "OZT_CDFFrame.H"
#include <UIC_Button.H>
#include <UIC_Panel.H>
#include <UIC_Popup.H>
#include <UIC_TextField.H>
#include <UIC_List.H>
#include "OZT_CDFDef.H"
#include "OZT_CDFFile.H"

// Forward declaration(s)
class OZT_CDFFile;
class OZT_CDFFrame;


typedef int (*OZT_IntCallback)(UIC_Window *);

class  OZT_ViewSelectFile : public UIC_Popup
{

public:

    OZT_ViewSelectFile(const int nls_index, UIC_Window& window,
                       OZT_IntCallback callback);
    // Description:
    //     Opens a window containing a list of files loaded into the developer 
    // Parameters:
    //     nls_index       NLS string for the popup window
    //     window          parent window
    //     callback        callback routine for when a filename is entered


    ~OZT_ViewSelectFile();
    // Description:
    //     Destructor.

    void fill_list(void);
    // Description:
    //     Fills the list with all the open file names 

    void view_apply(void);
    // Description:
    //     The user has pressed the Apply button.

    RWCString get_value(void);
    // Description:
    //     Get the filename that has been selected.
    // Return Value"
    //     The filename

    
protected:

private:
    OZT_CDFFrame*    cdf;

    UIC_Panel        view_panel;
    UIC_TextField    view_textfield;
    UIC_List         view_list;
    UIC_Button       apply_button;
    OZT_IntCallback  apply_callback;

    RWCString full_name_array[MAX_OPEN_FILES];

    static void a_view_apply (UIC_Window* wp, UIC_PanelItem* pi);
    static void a_list (UIC_Window* wp, UIC_PanelItem* pi, int mode, int);

    void do_list (UIC_PanelItem* pi, int mode);
    void showNotify (void);

};

#endif
