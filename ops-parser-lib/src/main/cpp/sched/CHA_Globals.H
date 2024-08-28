// RCS revision handling
// $Id: CHA_Globals.H,v 24.1 1996/01/17 16:17:45 ehscama Exp $

//**********************************************************************
// 
// .NAME CHA_Globals 
// .INCLUDE CHA_Globals.H 

// .COPYRIGHT
//  COPYRIGHT Ericsson Telecom AB 1993
//
// The Copyright to the computer program(s) herein
// is the property of Ericsson Telecom AB, Sweden.
// The program(s) may be used and/or copied with the
// written permission from Ericsson Telecom AB or in
// accordance with the terms and conditions stipulated
// in the agreement/contract under which the program(s)
// have been supplied.
// 

// .DESCRIPTION 
// 	Global variables for the CHA application

// DOCUMENT NO
//	190 89-CAA 134 056

// AUTHOR 
// 	1992-04-11 TM/JUG AC Coward Olsen  etxacco@juno.ericsson.se

// .REVISION
//	TB53_OZ
//	1995-11-28
// CHANGES

//
//	REV NO	DATE		NAME			DESCRIPTION
//	TB53_OZ 1995-11-28      J Grape (EHSGRAP)       RCS rev 24.0
//	XM2S1   1995-09-07      ehscama                 RCS rev 23.0
//	EC2_OZ  1995-08-01      Jan Sandquist (EHSJAASA)RCS rev 22.0
//	EC1_OZ  1995-06-29      J Grape (EHSGRAP)       RCS rev 21.0
//	TB5_2_OZ1995-06-08      J Grape (ehsgrap)       RCS rev 20.0
//	TB5_1_OZ1995-04-13      J Grape (EHSGRAP)       RCS rev 19.0
//	TB51_OZ 1995-03-17      ehscama                 RCS rev 18.0
//	TB5_OZ  1995-03-16      ehscama                 RCS rev 17.0
//	TB6_B1C_B1995-03-10      N.Lanninge (XKKNICL)    RCS rev 16.0
//	TB6_B1C 1995-03-09      N.Lanninge (XKKNICL)    RCS rev 15.0
//	TB4_OZ  1995-02-25      J Grape (EHSGRAP)       RCS rev 14.0
//	CHUI_TB61995-02-15      N.Lanninge (XKKNICL)    RCS rev 13.5
//	TB3     1995-02-06      J Grape (EHSGRAP)       RCS rev 12.0
//	PREIT   1995-01-18      N Länninge (XKKNICL)    RCS rev 11.0
//	TB2     1994-12-22      J Grape (EHSGRAP)       RCS rev 10.0
//	E       1994-10-24      ehscama                 RCS rev 9.0
//	D       1994-10-05      EHSCAMA                 RCS rev 8.0
//	R1C     1994-09-22      J Grape (EHSGRAP)       RCS rev 7.0
//	R1B     1994-08-30      J Grape (EHSGRAP)       RCS rev 6.0
//	R1A     1994-08-16      J Grape (EHSGRAP)       RCS rev 5.0
//	P1C     1994-07-18      J Grape (EHSGRAP)       RCS rev 4.0
//	B		1993-10-28	C. Nilsson	CHA_TEXT_INPUT_WIDTH and
//							CHA_TEXT_OUTPUT_WIDTH
//                                                      changed
//                                      ehsdana         CHA_OS_NAME_VISIBLE_LEN,
//                                                      CHA_OS_NAME_STORED_LEN,
//                                                      CHA_DATE/TIME_LEN
//							added.
//	A		1993-03-01	C. Nilsson

//**********************************************************************

#ifndef CHA_GLOBALS_H
#define CHA_GLOBALS_H

const int CHA_CMD_FILE_NAME_STORED_LEN=255;	// Max length of command file 
						// name and system command file
//const int CHA_FILE_NAME_STORED_LEN=255;		// Max length of file name
//const int CHA_COMMAND_STORED_LEN=255;		// Max length of command string
const int CHA_PARAMETERS_STORED_LEN=255;	// Max length of parameters
extern const char* CHA_EXECUTABLE_PATH; 
//const char* CHA_EXECUTABLE_PATH="/usr/local/tmos/bin"; 
// The path to the executables


// Ricardo's constants
const int 	LISTROWS=7;	
const int	LISTWIDTH=750;

const int	CFH_MAX_ROUTING_TO_FILE=5;
const int	CFH_MAX_ROUTING_TO_MAIL=5;
const int	CFH_MAX_ROUTING_TO_PRINTER=5;

const int	CHA_MAX_ROUTING_TO_FILE=5;
const int	CHA_MAX_ROUTING_TO_MAIL=5;
const int	CHA_MAX_ROUTING_TO_PRINTER=5;

const int	CHA_MAX_FILENAME_LEN=40;
const int	CHA_MAX_PRINTERNAME_LEN=20;
const int	CHA_MAX_MAILADDRESS_LEN=40;

const int	CFH_FNC_BUSY_INTERVAL_MIN=0;
const int	CFH_FNC_BUSY_INTERVAL_MAX=40;

const int	CFH_REPEAT_FREQ_MIN=1;
const int	CFH_REPEAT_FREQ_MAX=12;

extern char*		CHA_LOGRETRIEVE;
extern char*		CHA_CMDFILE;
extern char*            CHA_SYSCMDFILE;
extern char*		CHA_RESPONSE;
extern char*		CHA_ALPHAFILE;
extern char*		CHA_USER;

extern const char*	CHA_SYSADM;
extern const char*	CHA_HELP_FILE;

const int 	CHA_TIMER_VALUE = 10;
#endif
