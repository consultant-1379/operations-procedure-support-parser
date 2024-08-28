//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/current.cc @@/main/1 2000-03-10.17:23 EHS

/*
 *--------------------------------------------------------------------------
 *
 * Name         current.C
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
 * Document no  12/19055-CAA 134 420
 *
 * Rev-state    C
 *
 * Original     1990-05-16 by TX/HJL Anders Olander
 *
 * Description  Providing some data about the current environment
 *        
 * Revision     B 1992-01-10 by TM/HJM Anders Olander
 * Description  Allow an offset that is added to the current time.
 *
 * Revision	C 1994-06-28 by EHS/PBJ Gunni Kallander
 * Description  SunOS5:          Sysinfo used instead of gethostname
 *
 *-------------------------------------------------------------------------
 */

#include <time.h>
#include <sys/param.h>

#ifdef __hpux
#include <sys/unistd.h>
#endif

#ifdef SunOS4
#include <sysent.h>
#endif

#if !(SunOS4 || __hpux)           // SunOS5
//#include <sys/systeminfo>
#endif

#include <current.hh>
#include <unistd.h>
Current::Current(unsigned long Offset) {

	offset = Offset;
	curr_time.tm_mday = 0; // Just to make sure ...
	curr_host[0] = '\0';
}


void Current::Init_time() {
	long raw_time;

	// If set, tm_mday of a struct tm, is never zero.
	if (curr_time.tm_mday) return; // Already initialized

	// Time of instance declaration is used.
        raw_time = time((long)0) + offset;
        curr_time = *(localtime(&raw_time));

 	return;
}

int Current::minute() {
	Init_time();
	return curr_time.tm_min; // 0 - 59
}

int Current::hour() {
	Init_time();
	return curr_time.tm_hour; // 0 - 23
}

int Current::day_of_month() {
	Init_time();
	return curr_time.tm_mday; // 1 - 31
}

int Current::day_of_year() {
	Init_time();
	return curr_time.tm_yday + 1; // 1 - 366
}

int Current::day_of_week() {
	Init_time();
	return curr_time.tm_wday; /* 0 - 6,
		see defines in com_entry.H */
}

int Current::month() {
	Init_time();
	return curr_time.tm_mon + 1; // 1 - 12
}

int Current::year() {
	Init_time();
	return curr_time.tm_year + 1900; // 1970 - ...
}



const char *Current::host() {
	// The sysinfo call is only issued at first call to host(). 
#if SunOS4 || __hpux
	if (!curr_host[0] && gethostname (curr_host, MAXHOSTNAMELEN)) 
#else
	if (!curr_host[0] /*&& (sysinfo(SI_HOSTNAME, curr_host, MAXHOSTNAMELEN) == -1)*/) 
#endif
        {
		curr_host[0] = '\0';
	}

	return curr_host;
}


