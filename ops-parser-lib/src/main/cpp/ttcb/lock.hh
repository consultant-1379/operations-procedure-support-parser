#ifndef LOCK_H
#define LOCK_H
//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/lock.hh @@/main/1 2000-03-10.17:23 EHS

/*
 *--------------------------------------------------------------------------
 *
 * Name         lock.H
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
 * Document no  09/19055-CAA 134 420
 *
 * Rev-state    A
 *
 * Original     1990-03-28 by TX/HJL Anders Olander
 *
 * Description  Mutual exclusion for crontab file 
 *		manipulation.
 *        
 * Revision     <rev> <yyyy-mm-dd> by <dep> <name>
 * Description  <description-of-the-revision>
 *
 *-------------------------------------------------------------------------
 */

#include <sys/param.h>

class MutualExclusion {
public:
	MutualExclusion(const char *User = (char *)0);
	~MutualExclusion();

	int operator ! () {return errorstate;}
	operator void * () {return (errorstate ? (void *)0 : (void *)(-1));}

private:
	int lock_fd, errorstate;
	char lockfile_path[MAXPATHLEN];
};

#endif

