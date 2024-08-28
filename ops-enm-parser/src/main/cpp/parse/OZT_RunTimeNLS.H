// RCS revision handling
// $Id: OZT_RunTimeNLS.H,v 21.0 1996/08/23 12:43:03 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	N.A.
// .LIBRARY CHOZTBIN
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
// 	This file defines a number of constants for NLS messages.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	190 89-CAA 134 2016

// AUTHOR 
// 	1995-01-18 by Nelson Cheng (epanyc@epa.ericsson.se)


// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_RunTimeNLS.H,v $
// 	Revision 21.0  1996/08/23 12:43:03  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 07:57:40  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:22:26  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:21:42  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:02:11  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:57:24  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:02:55  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:17:17  17:17:17  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.0  1995/10/07 12:01:33  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:09:19  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:25:13  09:25:13  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:02:28  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.1  95/07/05  09:14:04  09:14:04  epanyc (Nelson Cheng VK/EHS/PXE)
//      comment added
//      
//      Revision 9.0  1995/06/29  14:38:06  cmcha
//      Made release EC2_OZ, J Grape (EHSGRAP).
//
//      Revision 8.0  95/06/07  17:09:21  17:09:21  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 7.1  95/05/24  08:09:55  08:09:55  epanyc (Nelson Cheng VK/EHS/PXE)
//      no change
//      
//      Revision 7.0  1995/04/16  12:16:30  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.1  95/04/10  14:59:35  14:59:35  epanyc (Nelson Cheng VK/EHS/PXE)
//      startup messages added
//      
//      Revision 6.0  95/03/17  20:05:35  20:05:35  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 5.0  95/03/16  20:31:19  20:31:19  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 4.3  95/03/16  12:29:03  12:29:03  epanyc (Nelson Cheng VK/EHS/PXE)
//      new error code added
//      
//      Revision 4.2  1995/03/09  08:59:46  epanyc
//      new msg added
//
//      Revision 4.1  1995/03/02  21:24:38  epanyc
//      prompt messages changed
//
//      Revision 4.0  1995/02/23  21:46:05  cmcha
//      Made release TB4, J Grape (EHSGRAP).
//
//      Revision 3.0  95/02/06  20:57:44  20:57:44  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 1.5  95/01/31  10:31:30  10:31:30  epanyc (Nelson Cheng VK/EHS/PXE)
//      new codes added
//      
//      Revision 1.4  1995/01/26  13:57:48  epanyc
//      new code added
//
//      Revision 1.3  1995/01/25  13:10:52  epanyc
//      new codes added
//
//      Revision 1.2  1995/01/18  16:58:08  epanyc
//      new mcode defined for file selector
//
//      Revision 1.1  1995/01/18  12:57:49  epanyc
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


#ifndef OZT_RUNTIME_NLS_H
#define OZT_RUNTIME_NLS_H

#include <CHA_NLSCatalog.H>

extern CHA_NLSCatalog  ozt_nlsCatalog;   // name of the catalog object
extern const char * OZT_RUN_TIME_NLS;

//
//  OZT_Clock related stuff
//
extern const int OZT_NLS_TIME_TO_DELAY;
extern const int OZT_NLS_MINS;
extern const int OZT_NLS_SECS;

//
//  OZT_FileSelector related stuff
//
extern const int OZT_NLS_FILE_SELECTION;
extern const int OZT_NLS_DIRECTORY;
extern const int OZT_NLS_FILE;
extern const int OZT_NLS_SELECT;
extern const int OZT_NLS_CANCEL;
extern const int OZT_NLS_GOUPONE;
extern const int OZT_NLS_SELECT_A_FILE;

//
//  OZT_InputWin related stuff
//
extern const int OZT_NLS_INPUT;
extern const int OZT_NLS_ENTER;
extern const int OZT_NLS_ENTER_PROMPT1;
extern const int OZT_NLS_ENTER_PROMPT2;

//
//  OZT_FileViewer related stuff
//
extern const int OZT_NLS_FILE_VIEWER;

//
//  OZT_XvIOW related stuff
//
extern const int OZT_NLS_IOW;

//
//  OZT_Prompt related stuff
//
extern const int OZT_NLS_CONTINUE_EXECUTION;
extern const int OZT_NLS_CONTINUE;
extern const int OZT_NLS_STOP;
extern const int OZT_NLS_STOP_N_QUIT;

//
//  Error messages coming from the main program
//
extern const int OZT_NLS_ELB_TASK_ID_MISSING;
extern const int OZT_NLS_THE_FILE;
extern const int OZT_NLS_CANNOT_BE_ACCESSED;
extern const int OZT_NLS_FAIL_TO_INIT;
extern const int OZT_NLS_FAIL_TO_EXECUTE;
extern const int OZT_NLS_CHA_ENV_ERROR;
extern const int OZT_NLS_NO_SUCH_PRINTER;
extern const int OZT_NLS_NO_TEXT;
extern const int OZT_NLS_STEP_CANT_INCLUDE;
extern const int OZT_NLS_CANT_INCLUDE;
extern const int OZT_NLS_FILE_OPEN_ERROR;
extern const int OZT_NLS_CANNOT_SET_USER;
extern const int OZT_NLS_CANNOT_CD;
extern const int OZT_NLS_OUT_OF_MEMORY;
extern const int OZT_NLS_NO_FILE_LOADED;
extern const int OZT_NLS_MAX_FILES;
extern const int OZT_WRONG_USER;
extern const int OZT_NO_PERM_CLIENTCHANGE;
extern const int OZT_IS_DISCONNECTED;
extern const int OZT_IS_CONNECTED;
extern const int OZT_INCORRECT_PWD;

//
//  Startup messages
//
extern const int OZT_NLS_INITIALISING;
extern const int OZT_NLS_CHECKING_ELB_AUTH;
extern const int OZT_NLS_INITIALISING_USER_INTERFACE;
extern const int OZT_NLS_CONNECTING;
extern const int OZT_NLS_INITIALISING_CAP_IPC;
extern const int OZT_NLS_CMD_SENDER_INITIALISED;
extern const int OZT_NLS_INTERPRETER_INITIALISED;
extern const int OZT_NLS_SESSION_READ_ERROR;
//
//  Main program messages
//
extern const int OZT_NLS_STEP_IN_PROGRESS;
extern const int OZT_NLS_STEP_INTERRUPTED;
extern const int OZT_NLS_STEP;
extern const int OZT_NLS_RUNNING_FROM_TOP;
extern const int OZT_NLS_RUNNING_TAGS;
extern const int OZT_NLS_NO_TAGS;
extern const int OZT_NLS_RUNNING;
extern const int OZT_NLS_RUN_STOP_BREAKPOINT;
extern const int OZT_NLS_RUN_STOP_INTERRUPT;
extern const int OZT_NLS_RUN_STOP;
extern const int OZT_NLS_NOT_UPTODATE;
extern const int OZT_NLS_INCLUDED_LINES_EXECUTED;

extern const int OZT_NLS_NO_CHA_DIRECTORIES;
extern const int OZT_NLS_APCONNECT;

#endif
