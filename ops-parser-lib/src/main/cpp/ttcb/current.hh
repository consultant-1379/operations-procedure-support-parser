#ifndef CURRENT_H
#define CURRENT_H
//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/current.hh @@/main/1 2000-03-10.17:23 EHS

/*
 *--------------------------------------------------------------------------
 *
 * Name         current.H
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
 * Document no  11/19055-CAA 134 420
 *
 * Rev-state    C
 *
 * Original     1990-03-28 by TX/HJL Anders Olander
 *
 * Description  Providing some data about the current environment
 *        
 * Revision     B 1992-01-10 by TM/HJM Anders Olander
 * Description  Allow an offset when constructing a "Current" object.
 *
 * Revision     C 1994-07-03 by EHS/PBJ Gunni Kallander
 * Description  netdb.h included
 *
 *-------------------------------------------------------------------------
 */

#include <time.h>
#include <sys/param.h>
#include <netdb.h>

class Current {
public:
	Current(unsigned long Offset = 0 /* seconds */);

	int minute();
	int hour();
	int day_of_month();
	int day_of_year();
	int day_of_week();
	int month();
	int year();

	const char *host();

protected:
	void Init_time();

private:
	struct tm curr_time;
	unsigned long offset;
	char curr_host[MAXHOSTNAMELEN];
};

#endif

