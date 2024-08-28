//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/lock.cc @@/main/2 2000-04-03.17:56 EHS

/*
 *--------------------------------------------------------------------------
 *
 * Name         lock.C
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
 * Document no  10/19055-CAA 134 420
 *
 * Rev-state    A
 *
 * Original     1990-03-28 by TX/HJL Anders Olander
 *
 * Description  Mutual exclusion for crontab file
 *              manipulation.
 *        
 * Revision     <rev> <yyyy-mm-dd> by <dep> <name>
 * Description  <description-of-the-revision>
 *
 *-------------------------------------------------------------------------
 */

#include <pwd.h>

#ifdef __hpux
#include <sys/unistd.h>
#endif

#ifdef SunOS4
#include <sysent.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include <tcparam.hh>

#include <lock.hh>


MutualExclusion::MutualExclusion(const char *User) {
	int retries = 3;
	struct passwd *entry;
	// Get user's pw entry.
	if (!(entry = (User ? getpwnam(User) : getpwuid(getuid())))) {
		errorstate = 1;
		return;
	}

	// Try to open lock file.
	strcat(strcpy(lockfile_path, entry->pw_dir), TC_LOCK_FILE);
	for (;(lock_fd = open(lockfile_path, O_WRONLY|O_SYNC)) == -1; retries--) {
		// It didn't work, it probably doesn't exist.
		if (retries < 1) {
			// Give up.
			errorstate = 1;
			return;
		}

		// Creat the lock file
		lock_fd = open(lockfile_path, O_WRONLY|O_CREAT, 0600);
	    
		if (lock_fd != -1) {
		    fchown( lock_fd, entry->pw_uid, entry->pw_gid );
		    close(lock_fd);
		}
	}

	// Lock
	if (lockf(lock_fd, F_LOCK, 0) == -1) {
		errorstate = 1;
		return;
	}
	errorstate = 0;
	return;
}


MutualExclusion::~MutualExclusion() {
	// Unlock
	lockf(lock_fd, F_ULOCK, 0);
	close(lock_fd);
}
