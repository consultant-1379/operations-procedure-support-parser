/*
 *--------------------------------------------------------------------------
 *
 * Name         tctrl_local.C
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
 * Document no  24/19055-CAA 134 420
 *
 * Rev-state    E
 *
 * Original     1990-04-17 by TX/HJL Anders Olander
 *
 * Description  "Local" object are peep-holes into the activation queue.
 *              The crontab list on the local machine is used.
 *
 * Revision     B 1992-01-09 by TM/HJM Anders Olander
 * Description  In add, a check is inserted, to verify that the request
 *              will be executed at least once (if it is not removed,
 *              of course).
 *
 * Revision     C 1992-02-27 by TM/HJG Gunni Kallander
 * Description  com_entry changed to tas_tc_com_entry.
 *
 * Revision     D 1993-07-08 by JV/PBJ Erika Biesse
 * Description  Method is_cron_changed() for asking if the crontabfile has
 *              changed since last modified by this instance or since
 *		last time is_cron_changed() was called. New return code in
 *		add, TTCB_LOCAL_TIMELIMIT.
 *
 * Revision	E 1994-06-28 by EHS/PBJ Gunni Kallander
 * Description  SunOS5/HPUX09:  waitpid used instead of wait4
 *              SunOS4:         wait4 and int for process number is still used

 *              Error report AB56048 corrected. is_cron_changed returns 1 if
 *                    crontabfile is physically deleted.
 *
 * Revision     F 1996-11-13 by EHS/VP Anders Berglund
 * Description  Solving TR HA13804 needs higher reolution in the identity.
 *              Some changes are done in the Local::add_ctf-method
 *              The identity is changed from 1/s to 16/s.
 *
 * Revision     G 1998-01-27 by EHS/VS Goran Ihs
 * Description  Correcting TR HA69890 , bog in last correction F
 *              Some changes are done in the Local::add_ctf-method
 *
 * Revision     H 1998-06-09 by VU Valter Saaristu
 * Description  According to TR HA87548 change fork to fork1.
*-------------------------------------------------------------------------

 */

#include <errno.h>
#include <mystring.hh>

#ifdef SunOS4
#include <sysent.h>
#include <sys/time.h>
#include <sys/resource.h>
#else
#include <unistd.h>
#endif

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <values.h>


#include <tcparam.hh>
#include <intheap.hh>
#include <cti.hh>
#include <current.hh>

#include <tctrl_local.hh>

#include <CHA_Trace.H>

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"tctrl_local", (char*)"C");

// Allowed state values:
#define NORMAL	0
#define LISTING 2
#define USERS	3

// This code was modified for TMOS/HP. The reason is described in HPUX.74
#ifdef __hpux
#define LS "/bin/ls"
#else
#define LS "/usr/bin/ls"
#endif

/*****************************************************
 * Return the status code
 */
int Local::get_error_code () {
         return status;
};

/*****************************************************
 * Add one Command Request Entry into the local crontab
 * file. Read through the entries in the crontab file,
 * checking the entry is not already inserted (thus
 * avoiding duplicates), and which id numbers are in
 * use. The id number is determined from the UNIX time. If
 * this time couldn't be fetched, the smallest non-used id
 * number will be used.
 * The ids are important in the shell command. (see
 * ttcb_shell.C)
 * Retruns 0 on success, and -1 on failure.
 */
int Local::add_ctf(TAS_TC_com_entry *ce) {
	int duplicates = 0;
//	unsigned int no; //no changed from int to unsigned int 961113 ehsanbe
        int no;
        int reply = 0;

	//new variables 961113 ehsanbe
	struct timeval timestruct;
	int sec, usec, steps;

	TAS_TC_com_entry temp;

        status = TTCB_LOCAL_OK;

	//TRACE_FLOW(trace, add_ctf, ce->user);

	CrontabFile ctf(1, CRONTABLIB, ce->user);
	Heap idheap;
        reply = !ctf;
	if (reply == TTCB_CRT_AUTHORITY_ERROR) {
                status = TTCB_LOCAL_AUTHORITY;
		return -1;
        }
        else if (reply != 0) {
                status = TTCB_LOCAL_INTERNAL;
                return -1;
        }
	while (ctf >> temp && temp) {
		if (*ce == temp)
			duplicates = 1;
		if (temp.id > 0)
			idheap.add(temp.id);
		ctf << temp;
	}
	if (duplicates) {
                status = TTCB_LOCAL_ALREADY_IN_QUEUE;
		return -1;
        }

	if (ce->id < 1)
	{

	  //old solution before 961113
	  //time_t *pno = (time_t*)&no;
	  //no = (int)time(pno);

	  //new solution from 961113

	  // <vip> gettimeofday(&timestruct, 0);
	   int sec = timestruct.tv_sec;
	   int usec = timestruct.tv_usec;
	   int steps = 4;

//	   no = (sec << steps) + usec % (int)pow(2,steps);
           no = (sec << steps) + usec % 16;

	//	time_t is a long. long and int is equal in length in our systems
		if (no < 0)
//		for (no = 1; no == idheap.get(); no++);
		  no+=MAXINT;
		ce->id = no;
	}

	ctf << *ce;
	return 0;
}

int Local::add(TAS_TC_com_entry *ce) {
        int reply = 0;
	Current timelimit(180); // Two to three minutes from now

        status = TTCB_LOCAL_OK;

	/* Input argument check has to take place prior to creation
	 * crontab interface instance.
	 */
	if (!*ce) {
                status = TTCB_LOCAL_INTERNAL;
		return -1;
        }
	// Fill in host name if not set
	if (!ce->host) {
		Current current;
		ce->host = strdup2(current.host());
	}

	// Check that the request will be executed
	if (ce->year != TCANY &&
		(ce->year < timelimit.year() || (ce->year == timelimit.year() &&
		(ce->month < timelimit.month() || (ce->month == timelimit.month() &&
		(ce->day < timelimit.day_of_month() ||
			(ce->day == timelimit.day_of_month() &&
		(ce->hour < timelimit.hour() || (ce->hour == timelimit.hour() &&
		(ce->minute < timelimit.minute())))))))))) {
                status = TTCB_LOCAL_TIMELIMIT;
		return -1;
	}

	reply = add_ctf(ce);

	//Set timestamp after modif. of cronfile
	crontab_last_written = Get_mod_time();
	return reply;
}


/*****************************************************
 * Remove one Command Request Entry from the local crontab
 * file. Read through the entries in the crontab file,
 * removing the entry. If it didn't exist the method
 * will return -1 (failure).
 * Retruns 0 on success, and -1 on failure.
 */
int Local::remove_ctf(TAS_TC_com_entry *ce) {

  //TRACE_IN(trace, remove_ctf, "");

	TAS_TC_com_entry temp;
	int count = 0;
        int reply = 0;

        status = TTCB_LOCAL_OK;

	CrontabFile ctf(1, CRONTABLIB, ce->user);
	//TRACE_FLOW(trace, remove_ctf, "Crontab file for user: " << ce->user );
        reply = !ctf;
	if (reply == TTCB_CRT_AUTHORITY_ERROR) {
                status = TTCB_LOCAL_AUTHORITY;
		//TRACE_RETURN(trace, remove_ctf, "result=-1 status=TTCB_LOCAL_AUTHORITY");
		return -1;
        }
        else if (reply != 0) {
                status = TTCB_LOCAL_INTERNAL;
		//TRACE_RETURN(trace, remove_ctf, "result=-1 status=TTCB_LOCAL_INTERNAL");
                return -1;
        }
	while (ctf >> temp && temp) {
	  //TRACE_FLOW(trace, remove_ctf, "Reading com entry: " << temp.Get_command_line() );
		if ((!(ce->id) && *ce == temp )  // id not used. matching of complete record
		|| ((ce->id == temp.id) &&
		    (strcmp(ce->Get_command_line(), temp.Get_command_line()) == 0))) {
			count++;
			//TRACE_FLOW(trace, remove_ctf, "Com entry to be removed : " << ce->Get_command_line() );
		}
		else
			ctf << temp;
	}

	if (count != 1) {
                status = TTCB_LOCAL_NO_JOB;
		//TRACE_RETURN(trace, remove_ctf, "result=-1 status=TTCB_LOCAL_NO_JOB ");
		return -1;
        }
	else
		return 0;
}

int Local::remove(TAS_TC_com_entry *ce) {

  //TRACE_IN(trace, remove, "");

        int reply = 0;

        status = TTCB_LOCAL_OK;

	/* Input argument check has to take place prior to creation
	 * crontab interface instance.
	 */
	if (!*ce) {
                status = TTCB_LOCAL_INTERNAL;
		//TRACE_RETURN(trace, remove, "result=-1 status=TTCB_LOCAL_INTERNAL" << reply);

		return -1;
        }
	// Fill in host name if not set
	if (!ce->host) {
		Current current;
		ce->host = strdup2(current.host());
	}

	reply = remove_ctf(ce);

	//Set timestamp after modif. of cronfile
	crontab_last_written = Get_mod_time();

	//TRACE_RETURN(trace, remove, "result=" << reply);

	return reply;

}


/******************************************************
 * Start listing of entries in local crontab file.
 * Start the Crontab File Interface with reading only
 * and change to state to LISTING.
 * Returns 0 on success, and -1 on failure.
 */
int Local::liststart(char *User) {
        int reply = 0;

	if (!this ||
	    state != NORMAL)
		return -1;
	//<vip>ctfp = new CrontabFile(0, CRONTABLIB, User);
      /*  if (!ctfp) {
              return -1;
        };

        reply = !*ctfp;
        if (reply == TTCB_CRT_AUTHORITY_ERROR) {
            status = TTCB_LOCAL_AUTHORITY;
            return -1;
        }
        else if (reply != 0) {
                 status = TTCB_LOCAL_INTERNAL;
                 return -1;
        };*/

	state = LISTING;
	return 0;
}


/***************************************************
 * Return next entry in listing.
 */
TAS_TC_com_entry Local::listentry() {
	TAS_TC_com_entry ce;
	Current current;
	if (!this ||
	    state != LISTING)
		return ce;

	/**ctfp >> ce;

	if (!ce) {
		state = NORMAL;
		delete ctfp;
	}*/
	return ce;
}


/*************************************************
 * Initiate user listing, forks and starts the
 * ls command.
 * Also fills in child process id.
 * Returns 0 on success, and -1 on failure.
 */
static int userls(pid_t *pidp, ifstream *strp) {
	int p[2]; // Pipe fd array
	if (pipe(p))
		return -1;
#if (SunOS4 || __hpux)
	switch (*pidp = fork()) {
#else
	switch (*pidp = fork()) {
#endif
		case -1:
			return -1;
		case  0: // Child
			if (close(1) ||
			    (dup(p[1]) == -1) ||
			    close(p[0]) ||
			    close(p[1]))
				_exit(10);

			execlp(LS, "ls", "-1", CRONTABLIB, (char *)0);
			_exit(14);
	}
	close(p[1]);
	//<vip> strp->attach(p[0]);
	return 0;
}


/***************************************************
 * Return next user name
 * Returns non-null on success, and null on end of list
 *	or failure.
 */
static char *usernext(ifstream *strp) {
	static char buffer[MAXUSERNAMELEN + 2];
	if (strp->getline(buffer, MAXUSERNAMELEN + 1))
		return buffer;
	else
		return (char *)0;
}


/**************************************************
 * Close down after user listing.
 * Never fails.
 */
static void userend(pid_t pid, ifstream *strp) {
	int fd;
	//<vip> fd = strp->rdbuf()->fd();
	strp->close();
	close(fd);
#if SunOS4
        wait4 (pid, (union wait*)0, 0, 0);
#else
	waitpid(pid, NULL, 0);
#endif
}


/******************************************************
 * Get one name of a user utilizing crontab. When all
 * user names have been retrieved, null will be returned
 * once. Next call will restart the retrieving.
 * Returns non-null on success, and null on failure.
 */
char *Local::userentry() {
	char *user;
	if (!this) return (char *)0;

	switch (state) {
		case NORMAL:
			if (userls(&pid, &istr))
				return (char *)0;
			state = USERS;
		case USERS:
			if (!(user = usernext(&istr))) {
				userend(pid, &istr);
				state = NORMAL;
			}
			return user;
		default:
			return (char *)0;
	}
}


/******************************************************
 * Get time crontab-file has been last modified
 * Returns time on success, 0 if file deleted, and -1 on failure.
 */
time_t Local::Get_mod_time() {
	if (!this)
		return -1;
	struct stat buf;
	struct passwd *entry;
	char lockfile_path[MAXPATHLEN];

	// Get user's pw entry.
	if (!(entry = getpwuid(getuid()) )) {
		return (time_t)-1;
	}

	// Name of user's crontab file. CRONTABLIB/'user'
	strcat(strcpy(lockfile_path, CRONTABLIB), entry->pw_name);

	if (stat(lockfile_path, &buf) == 0)
		return buf.st_mtime;
        else
           if (errno == ENOENT)
              return (time_t)0;
	else return (time_t)-1;
}

/******************************************************
 * Answers the question if the crontab-file has been
 * modified since last accessed from this object.
 * Returns 1 if true, 0 if false, and negative on failure.
 */
int Local::is_cron_changed() {
	if (!this)
		return -1;
	time_t time;

        switch (time = Get_mod_time()) {

           case -1 : return -1;
           case 0  : if (crontab_last_written !=0)
                     // crontab_... = 0 if crontab does not exist
                     {
                         crontab_last_written = 0;
                         return 1;
                     }
                     else return 0;
           default  : if (time != crontab_last_written) {
                              crontab_last_written = time;
                              return 1;
                     }
                     else return 0;
        }
}

/************************************************
 * Checks if the id for a TAS_TC_com_entry is present in the crontab file
 * Returns 1 if true, 0 if false, and negative on failure.
 */
int Local::is_scheduled(int Idty, const char* user) {
        int reply = 0;
	int duplicates = 0;
	TAS_TC_com_entry temp;

	if (!this)
		return -1;
        status = TTCB_LOCAL_OK;

	/* Input argument check has to take place prior to creation
	 * crontab interface instance.
	 */
	if (Idty < 1) {
                status = TTCB_LOCAL_INTERNAL;
		return -1;
        }

	//TRACE_FLOW(trace, is_scheduled, user);

	CrontabFile ctf(0, NULL, user);
	Heap idheap;
        reply = !ctf;
	if (reply == TTCB_CRT_AUTHORITY_ERROR) {
                status = TTCB_LOCAL_AUTHORITY;
		return -1;
        }
        else if (reply != 0) {
                status = TTCB_LOCAL_INTERNAL;
                return -1;
        }
	while (ctf >> temp && temp) {
		if (temp.id == Idty)
			duplicates = 1;
		ctf << temp;
	}
	if (duplicates) {
                //status = TTCB_LOCAL_ALREADY_IN_QUEUE;
		return 1;
        }

	return 0;
}

/************************************************
 * Checks if a TAS_TC_com_entry is present in the crontab file
 * Returns 1 if true, 0 if false, and negative on failure.
 */
int Local::is_scheduled( TAS_TC_com_entry ce) {
        int reply = 0;
	int duplicates = 0;
	TAS_TC_com_entry temp;

	if (!this)
		return -1;
        status = TTCB_LOCAL_OK;

	/* Input argument check has to take place prior to creation
	 * crontab interface instance.
	 */
	if (!ce) {
                status = TTCB_LOCAL_INTERNAL;
		return -1;
        }

	CrontabFile ctf(0);
	Heap idheap;
        reply = !ctf;
	if (reply == TTCB_CRT_AUTHORITY_ERROR) {
                status = TTCB_LOCAL_AUTHORITY;
		return -1;
        }
        else if (reply != 0) {
                status = TTCB_LOCAL_INTERNAL;
                return -1;
        }
	while (ctf >> temp && temp) {
		if (temp == ce)
			duplicates = 1;
		ctf << temp;
	}
	if (duplicates) {
                //status = TTCB_LOCAL_ALREADY_IN_QUEUE;
		return 1;
        }

	return 0;
}

