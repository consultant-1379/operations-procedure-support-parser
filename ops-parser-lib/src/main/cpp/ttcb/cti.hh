#ifndef CTI_H
#define CTI_H
/*
 *--------------------------------------------------------------------------
 *
 * Name         cti.hh
 *
 * *******************************************************************
 * * COPYRIGHT (c) 1990 Ericsson Telecom AB, Sweden.                 *
 * *                   All rights reserved                           *
 * *                                                                 *
 * * The copyright to the computer program(s) herein is the property *
 * * of Ericsson Telecom AB, Sweden. The programs may be used or     *
 * * copied only with the written permission of Ericsson Telecom AB. *
 * *******************************************************************
 *
 * Product      System          TMOS
 *              Subsystem       TAP
 *              Function block  TTCB 
 *              Software unit   TTCLIB
 *              
 * Document no  05/19055-CAA 134 420
 *
 * Rev-state    C 
 *
 * Original     1990-04-05 by TX/HJL Anders Olander
 *
 * Description  Crontab file interface
 *        
 * Revision     B 1991-07-04 by TM/HJG Peter Hertzman
 * Description  File protection for crontab changed in
 *              SunOS 4.1.1 ( com. to SunOS 4.0.3 ) .
 *
 * Revision     C 1992-02-27 by TM/HJG Gunni Kallander
 * Description  com_entry changed to tas_tc_com_entry.
 *
 *-------------------------------------------------------------------------
 */

#include <fstream>
using namespace std;
#include <tas_tc_com_entry.hh>
#include <lock.hh>
#include <sys/types.h>
 
class CrontabFile {
public:
	CrontabFile(int RdWr)
		{CrontabFile_constructor(RdWr, (char *)0, (char *)0); }

	CrontabFile(int RdWr, const char *Dir, const char *User = (char *)0)
		{CrontabFile_constructor(RdWr, Dir, User) ; }

	~CrontabFile();
	int operator ! ();
	operator void * ();
	CrontabFile& operator << (TAS_TC_com_entry);
	CrontabFile& operator >> (TAS_TC_com_entry&);
	friend char *ttcb_crt_Decode_command(char *);
private:
	// Actual constructor code
	void CrontabFile_constructor(int RdWr, const char *, const char *User = 0 );
private:
	MutualExclusion *mep;
	std::ifstream ctin;
	std::ofstream ctout;
	int status;
	pid_t pidin, pidout ;
	char *user;
};


// Values for status
#define TTCB_CRT_WRITING_IN_PROGRESS	( 1)
#define TTCB_CRT_NOTHING_WRITTEN	( 0)
#define TTCB_CRT_OK			( 0)
#define TTCB_CRT_PROBLEMS		(-1)
#define TTCB_CRT_EOF			(-2)
#define TTCB_CRT_AUTHORITY_ERROR        (-3)
#define TTCB_CRT_PROGRAM_ERROR		(-5)

// tc_shell flags (The same definitions appear in cti.L)
#define TTCB_CRT_FLAGS_STRING		"ihymc"
#define TTCB_CRT_ID_FLAG		'i'
#define TTCB_CRT_HOST_FLAG		'h'
#define TTCB_CRT_YEAR_FLAG		'y'
#define TTCB_CRT_MONTH_FLAG		'm'
#define TTCB_CRT_COMMAND_FLAG		'c'

#endif

