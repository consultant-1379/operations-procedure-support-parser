// RCS revision handling
// $Id: OZT_CDFDef.H,v 21.0 1996/08/23 12:46:12 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_CDFDef - Various definitions for the developer GUI
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
// 	Contains a number of definitions used within files choztui
//      such as window sizes, directory names, etc.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	%EriDoc_no:%

// AUTHOR 
// 	1994/10/06  by ETL/XN/DSN  etlnei

// .REVISION <for public API>
//	<Revision state>
//	<Revision date>	  	

// .REVISION <for internal header files>
//	%EriDoc_rev:%
//	%EriDoc_date:%  	

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_CDFDef.H,v $
// 	Revision 21.0  1996/08/23 12:46:12  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 08:00:34  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:23:45  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:24:46  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:06:19  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:59:24  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:04:38  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.2  95/11/28  14:49:53  14:49:53  epanyc (Nelson Cheng VK/EHS/PXE)
//      a few constants are added
//      
//      Revision 14.1  95/11/24  14:01:40  14:01:40  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Increased RESP_PANE_EDIT_SIZE from 2 to 3 million characters.
//      
// 	Revision 14.0  1995/11/20 17:20:20  ehsjasa
// 	Made release POW_TB3, J Sandquist (EHSJASA).
//
// 	Revision 13.2  1995/11/18 14:17:40  ehsjasa
// 	Increased the width of the ES list.
//
// 	Revision 13.1  1995/11/03 14:37:20  epanyc
// 	new constants added for frame height
//
//      Revision 13.0  1995/10/07  12:03:43  ehsjasa
//      Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:12:42  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:27:24  09:27:24  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:05:58  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:41:13  14:41:13  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.0  95/06/07  17:12:39  17:12:39  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 7.1  95/05/18  11:07:18  11:07:18  etlnei (Neil Harding VK/EHS/PXE)
//      checged the width of the comment window
//      
//      Revision 7.0  1995/04/16  12:19:04  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.3  95/04/13  08:18:50  08:18:50  etlnei (Neil Harding VK/EHS/PXE)
//      checked in for TB5.1
//      
//      Revision 6.2  1995/04/04  11:12:57  etlnei
//      checked in for happy test release
//
//      Revision 6.1  1995/03/24  15:43:21  etlnei
//      checked in to use some new UIC stuff
//
//      Revision 6.0  1995/03/17  20:08:11  cmcha
//      Made release TB51_OZ, ehscama.
//
//      Revision 5.0  95/03/16  20:33:26  20:33:26  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 4.2  95/03/14  14:21:20  14:21:20  etlnei (Neil Harding VK/EHS/PXE)
//      checked in to synchronize files with everyone else
//      
//      Revision 4.1  1995/03/09  09:25:06  etlnei
//      checked in for other people to compile
//
//      Revision 4.0  1995/02/23  21:47:54  cmcha
//      Made release TB4, J Grape (EHSGRAP).
//
//      Revision 3.1  95/02/21  09:27:21  09:27:21  etlnei (Neil Harding VK/EHS/PXE)
//      Changes made after hearing comments from Telstra
//      
//      Revision 3.0  1995/02/06  21:01:25  cmcha
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 2.6  95/01/31  11:44:58  11:44:58  etlnei (Neil Harding VK/EHS/PXE)
//      checked in for Nelson to compile
//      
//      Revision 2.5  1995/01/26  09:55:40  etlnei
//      checked in for Eric to compile
//
//      Revision 2.4  1995/01/09  11:49:21  etlnei
//      added props window stuff
//
//      Revision 2.3  1994/12/21  16:15:58  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 2.0  94/12/21  13:54:42  13:54:42  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//      
//      Revision 1.11  1994/12/16  13:38:52  etlnei
//      added text lengths for InputWin
//
//      Revision 1.10  1994/12/13  11:20:23  etlnei
//      checking in everything because OXT_ESBrowser is new
//
//      Revision 1.9  1994/12/12  11:15:57  etlnei
//      checked in for nelson to compile
//
//      Revision 1.8  1994/12/06  11:39:48  etlnei
//      checked in for Janne to compile
//
//      Revision 1.7  1994/12/02  10:35:25  etlnei
//      version uised for "happy testing"
//
//      Revision 1.6  1994/11/17  08:41:56  etlnei
//      now handles multiple files
//
//      Revision 1.5  1994/11/03  10:15:33  etlnei
//      checked in for Janne to compile
//
//      Revision 1.4  94/10/28  11:20:38  11:20:38  etlnei (Neil Harding VK/EHS/PXE)
//      *** empty log message ***
//      
//      Revision 1.3  94/10/13  13:05:48  13:05:48  etlnei (Neil Harding VK/EHS/PXE)
//      more bits done
//      
//      Revision 1.2  94/10/07  19:45:59  19:45:59  etlnei (Neil Harding VK/EHS/PXE)
//      corrected errors
//      
//      Revision 1.1  1994/10/06  14:34:41  etlnei
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


#ifndef OZT_CDFDEF_H 
#define OZT_CDFDEF_H

#include <rw/cstring.h>

#define CDF_INSTANCE 57 /* Need to check that this is OK */
#define PANE_NUMBER 58  /* Need to check that this is OK */

// External System text field
static const int ES_CHARLEN = 16;
static const int ES_STORELEN = 64;

//Filename: text field (main frame and printer popup)
static const int FILE_CHARLEN = 20;
static const int FILE_STORELEN = 256;

//Lines: text field
static const int LINES_CHARLEN = 7;
static const int LINES_STORELEN = 13;

//-----------------------------------------------------------------------------
// Sizes of text panes in debugger mode
//-----------------------------------------------------------------------------

static const int PANES_HEIGHT = 560;  // code pane + resp pane
static const int BASE_FRAME_HEIGHT = PANES_HEIGHT + 100;

static const int BIG_FRAME_HEIGHT = 600;
static const int SMALL_FRAME_HEIGHT = 320;

static const int CODE_PANE_HEIGHT = 400;
static const int CODE_PANE_WIDTH = 740;
static const int CODE_PANE_MARGIN = 60;

static const int RESP_PANE_HEIGHT = 200;
static const int RESP_PANE_MIN_HEIGHT = 68;
static const int RESP_PANE_WIDTH = CODE_PANE_WIDTH;
static const int RESP_PANE_STORED_LEN = 200000;
static const int RESP_PANE_EDIT_SIZE = 3000000;


//-----------------------------------------------------------------------------
// Sizes of text panes in command/response window mode
//-----------------------------------------------------------------------------
static const int RESP_WIN_HEIGHT = 336;
static const int RESP_WIN_WIDTH = CODE_PANE_WIDTH;

//-----------------------------------------------------------------------------
// Current position, breakpoints and tabs
//-----------------------------------------------------------------------------
static const int TAG_X         = CODE_PANE_MARGIN/3;
static const int CURRENT_POS_X = 2*CODE_PANE_MARGIN/3;
static const int BREAKPOINT_X   = 0;

// NLS file name
static const char *const NLS_CAT = "OZT";


//-----------------------------------------------------------------------------
// Name given to file with no name
// A number will be appended to the name to ensure that a unique name is given
//-----------------------------------------------------------------------------
static const char *const UNNAMED_FILE = "Untitled";


//-----------------------------------------------------------------------------
// Upper limits
//-----------------------------------------------------------------------------
static const int MAX_OPEN_FILES = 31; // If this is too high, problems can occur
                                      //(probably run out of file descriptors)
                                      // Changed from 16 to 31 due to TR HI36856
static const int MAX_LINES = 99999;   //Max lines for tags/breakpoints
// 25-04-2002 Value changed from 10000 to 20000 because of TR HD18279
// 17-06-2004 Value changed from 20000 to 99999 because of TR HE29968


//-----------------------------------------------------------------------------
// INPUT popup window
//-----------------------------------------------------------------------------
static const int INPUT_CHARLEN = 32;
static const int INPUT_STORELEN = 255;

//-----------------------------------------------------------------------------
// Status popup window
//-----------------------------------------------------------------------------
static const int DIR_CHARLEN = 48;
static const int DIR_STORELEN = 512;

//-----------------------------------------------------------------------------
// View popup window
//-----------------------------------------------------------------------------
static const int VIEW_CHARLEN = 25;
static const int VIEW_STORELEN = 256;
static const int VIEW_LIST_ROWS = 8;
static const int VIEW_LIST_WIDTH = 250;

//-----------------------------------------------------------------------------
// Watch popup window
//-----------------------------------------------------------------------------
static const int WATCH_CHARLEN = 25;
static const int WATCH_STORELEN = 256;
static const int WATCH_LIST_ROWS = 10;
static const int WATCH_LIST_WIDTH = 250;

//-----------------------------------------------------------------------------
// Print popup window
//-----------------------------------------------------------------------------
// For File textfield values see FILE_CHARLEN and FILE_STORELEN above.
static const int PRINTER_CHARLEN = FILE_CHARLEN;
static const int PRINTER_STORELEN = 256;

//-----------------------------------------------------------------------------
// ES popup window
//-----------------------------------------------------------------------------
static const int ESP_CHARLEN = 25;
static const int ESP_STORELEN = 256;
static const int ESP_LIST_ROWS = 10;
static const int ESP_LIST_WIDTH = 250;

//-----------------------------------------------------------------------------
// Sizes of text panes in CommentWin popup
//-----------------------------------------------------------------------------
static const int COMMENT_WIN_HEIGHT = 115;
static const int COMMENT_WIN_WIDTH = 604;


//-----------------------------------------------------------------------------
// Properties popup window
//-----------------------------------------------------------------------------
static const char *const PROP_RCFILE = ".cha_developerrc"; // Goes in home directory
static const char *const PROP_DEF_RCFILE = "OPS_DEFAULTS"; // Goes in app-defaults
static const char *const PROP_PREFIX = "cha_developer"; //

#endif
