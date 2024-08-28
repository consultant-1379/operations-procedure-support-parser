//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/tctrl_remote.cc @@/main/2 2000-04-03.17:56 EHS
 

/*
 *--------------------------------------------------------------------------
 *
 * Name         tctrl_remote.C
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
 * Document no  26/19055-CAA 134 420
 *
 * Rev-state    D
 *
 * Original     1990-04-09 by TX/HJL Anders Olander
 *
 * Description  Providing the interface between a remote
 *		time control server and its client.
 *        
 * Revision     B 1992-02-27 by TM/HJG Gunni Kallander
 * Description  com_entry changed to tas_tc_com_entry.
 *        
 * Revision     C 1993-07-08 by JV/PBJ Erika Biesse
 * Description  Method for asking if the crontabfile has changed since 
 *              last accessed by this object. New return code in add,
 *		TTCB_REMOTE_TIMELIMIT.
 *
 * Revision	D 1994-06-28 by EHS/PBJ Gunni Kallander
 * Description	SunOS5/HPUX09: waitpid used instead of wait4
 *
 * Revision     E 1998-06-09 by VU Valter Saaristu
 * Description  According to TR HA87548 change fork to fork1.
 *
 *-------------------------------------------------------------------------
 */

// This code was modified for SunOS4. The reason is described in ...
#ifdef SunOS4
#include <sysent.h>
#include <sys/time.h>
#include <sys/resource.h>
#else
#include <unistd.h>
#endif

#include <sys/wait.h>
#include <stdlib.h>
#include <mystring.hh>
#include <unistd.h>
#include <tctrl_local.hh>
#include <current.hh>
#include <tcparam.hh>

#include <tctrl_remote.hh>
#include <stdio.h>

// Allowed values for state:
#define ERROR		(-1)
#define NORMAL		( 0)
#define SERVER		( 1)
#define LISTING		( 2)
#define USERS		( 3)


static const char* TC_SHELL="/emt_ttcshr";

/*******************************************************
 * Constructor. When called with a null argument, the 
 * object will act as remote server. Otherwise a server
 * process will be started on the specified host. 
 */
Remote::Remote(char *Host) {
	int pin[2], pout[2]; // Pipe fd arrays
	
	char *tc_shell = new char[strlen(getenv("AM_TC_SHELL_EXEC_PATH")) + strlen(TC_SHELL) + 1];
	(void) sprintf(tc_shell, "%s%s", getenv("AM_TC_SHELL_EXEC_PATH"), TC_SHELL);
 
	host = strdup2(Host); // Save host name for future comparing
	if (!Host)
		state = SERVER;
	else {
		// Client
		state = NORMAL;
		if (pipe(pin) || pipe(pout)) {
			state = ERROR;
			return;
		}
#if (SunOS4 || __hpux)
		switch (pidr = fork()) {
#else
		switch (pidr = fork()) {
#endif
			case -1:
				state = ERROR;
				return;
			case  0:
				{
				if (close(pin[1]) ||
				    close(pout[0]) ||
				    close(0) ||
				    (dup(pin[0]) == -1) ||
				    close(1) ||
				    (dup(pout[1]) == -1) ||
				    close(pin[0]) ||
				    close(pout[1]))
					_exit(10);
/* This was modified for TMOS/HP, see PRIMA HPUX.22 */
#ifdef __hpux
				execlp("remsh", "remsh", Host, SETENV, tc_shell,
					"-" TTCB_TC_FLAG_STRING, (char *)0);
#else
				execlp("rsh", "rsh", Host, SETENV, tc_shell,
					"-" TTCB_TC_FLAG_STRING, (char *)0);
#endif
				_exit(13);
                                }
		}
		close(pin[0]);
		close(pout[1]);
	/* <vip>	serverout.attach(pin[1]);
		serverin.attach(pout[0]); */
	}
        status = TTCB_REMOTE_OK;
	
	delete [] tc_shell;

	return;
}


/*********************************************************
 * Destructor. 
 */
Remote::~Remote() {
	int fd;
	if (state == SERVER)
		return;
/*<vip>	fd = serverout.rdbuf()->fd(); */
	serverout.close();
	close(fd);

/*<vip>	fd = serverin.rdbuf()->fd(); */
	serverin.close();
	close(fd);

#if SunOS4
        wait4(pidr, (union wait *)0, 0, 0);
#else
	waitpid(pidr, NULL, 0);
#endif
//	return;
}

/*********************************************************
 * Return the status code
 */
int Remote::get_error_code() {
       return status;
}

/*********************************************************
 * Server function. Recieves orders from the client,
 * and sends them to a "Local" object. The results are
 * sent back to the client.
 * Order format (client to server):
 *    Add:			'\' 'a' <command request entry>
 *    Remove:			'\' 'r' <command request entry>
 *    List entries:		'\' 'l' [<user name>] '\n'
 *    List users:		'\' 'u' '\n'
 *    "No order":		'\' 'q' '\n'		(For testing purposes)
 *    Check changed crontab:	'\' 'c' '\n'
 *    Check if job present:	'\' 'i' <id-number> '\n'
 *    Check if job present:	'\' 's' <command request entry> '\n'
 * Response format (server to client):
 *    Error:			'\' 'E' [<number>] '\n'
 *    Add successful:		'\' 'A' '\n'
 *    Remove successful:	'\' 'R' '\n'
 *    List of entries:		'\' 'L' {<command request entry>} '\n'
 *    List of users:		'\' 'U' {<user name> '\n'} '\n'
 *    "No order" successful:	'\' 'Q' '\n'
 *    Check changed crontab:	'\' 'C' <1 or 0> '\n'
 *    Check if job present:	'\' 'I' <1 or 0> '\n'
 *    Check if job present:	'\' 'S' <1 or 0> '\n'
 *
 * Returns 0 on success, and -1 on failure.
 */
int Remote::accept(std::istream& in, std::ostream& out) {
	Local local;
	TAS_TC_com_entry ce;
	int ret, idty;
	char buffer[MAXINTLEN + 1 + 1], c, *user;
	if (!this || state != SERVER) return -1;
	while (in.clear(), in >> c) {
		if (c != '\\') continue; // Look for next back-slash
		switch (in >> c, c) {
			case 'a': // add
				if (!(in >> ce)) {
					out << "\\E9\n" << std::flush;
					break;
				}
				if (local.add(&ce)) {
					out << "\\E";
					out << local.get_error_code();
					out << "\n" << std::flush;
				}
				else out << "\\A" << ce.id << "\n" << std::flush;
				break;

			case 'c': // check
				if ((ret = local.is_cron_changed()) < 0) {
					out << "\\E3\n" << std::flush;
					break;
				}
				out << "\\C";
				out << ret << "\n" << std::flush;
				break;

			case 'r': // remove
				if (!(in >> ce)) {
					out << "\\E9\n" << std::flush;
					break;
				}
				if (local.remove(&ce)) {
					out << "\\E";
					out << local.get_error_code();
					out << "\n" << std::flush;
				}
				else out << "\\R\n" << std::flush;
				break;

			case 'l': // list
				// Try to read <user name>
				while (in && in.peek() == ' ') in.get();
				*buffer = '\0';
				if (in.getline(buffer, MAXUSERNAMELEN + 1) &&
				    *buffer) user = buffer;
				else user =  (char *)0;

				if (local.liststart(user)) {
					out << "\\E";
                                        out << local.get_error_code();
                                        out << "\n" << std::flush;
					break;
				}
				out << "\\L";
				while (ce = local.listentry()) 
					out << ce;
				out << "\n" << flush;
				break;

			case 'u': //users
				out << "\\U";
				while (user = local.userentry())
					out << user << "\n";
				out << "\n" << flush;
				break;

			case 'i': // check identity
				// Try to read <idty>
				while (in && in.peek() == ' ') in.get();
				*buffer = '\0';
				if (in.getline(buffer, MAXINTLEN + 1) &&
				    *buffer) idty = atoi(buffer);
				else {
					out << "\\E3\n" << flush;
					break;
				}

				if ((ret = local.is_scheduled(idty)) < 0) {
					out << "\\E3\n" << flush;
					break;
				}
				out << "\\I";
				out << ret << "\n" << flush;
				break;

			case 's': // check identity
				if (!(in >> ce)) {
					out << "\\E9\n" << flush;
					break;
				}

				if ((ret = local.is_scheduled(ce)) < 0) {
					out << "\\E3\n" << flush;
					break;
				}
				out << "\\S";
				out << ret << "\n" << flush;
				break;

			case 'q': // No operation
				out << "\\Q\n" << flush;
				break;

			default: // Bad command
				out << "\\E4\n" << flush;
				break;
		}
	}
	return 0;
}


/*****************************************************
 * Read response message (initial back-slash only). Format
 * described at accept().
 * Return 0 on success, and -1 on failure, that is no
 * back-slash was found.
 */
static int Find_next_message(istream& in) {
	in.clear(in.rdstate() & ~ios::failbit);
	while (!in.eof() && in.get() != '\\');
	if (in.eof()) return -1;
	else return 0;
}


/*****************************************************
 * Set host to current host, if host hasn't been specified
 * by the application.
 * Comment: If it is a time control command the host could
 *		have been left out, but it yields surprising
 *		functinallity. (Code commented out)
 * Return the modified Command Request Entry.
 */
TAS_TC_com_entry *Remote::set_current_host(TAS_TC_com_entry *ce) {
	Current current;
	if (!ce->host
		/* && strncmp(ce.commandline, TTCUIP, strlen(TTCUIP)) */ ) {
		ce->host = strdup2(current.host());
	}
	return ce;
}


/******************************************************
 * Send a add request to the remote server. Check
 * the response to see if the request was satisfied.
 * Returns 0 on success, and -1 on add failure and
 * -2 on other failures.
 */
int Remote::add(TAS_TC_com_entry *ce) {
	char reply, buffer[MAXINTLEN + 1 + 1];

        status = TTCB_REMOTE_OK;

	if (!this || state != NORMAL || !*ce) {
		status = TTCB_REMOTE_INTERNAL;	
		return -2;
	}
	if (!(serverout << "\\a" << *(set_current_host(ce)) << flush)) {
		status = TTCB_REMOTE_INTERNAL;
		return -1;
	}
	if (Find_next_message(serverin)) {
		status = TTCB_REMOTE_INTERNAL;
		return -2;
	}
	switch (serverin.get()) {
		case 'A': if (serverin.getline(buffer, MAXINTLEN + 1) &&
				*buffer) {
				    ce->id = atoi(buffer);
				    return 0;
                          } else {
				    status = TTCB_REMOTE_INTERNAL;
				    return -1;
                          } 

                case 'E': reply = serverin.get();
                          switch (reply) {
				case '1': status = TTCB_REMOTE_INTERNAL;
					  return -1;
				case '2': status = TTCB_REMOTE_AUTHORITY;
					  return -1;
				case '3': status = TTCB_REMOTE_ALREADY_IN_QUEUE;
					  return -1;
				case '5': status = TTCB_REMOTE_TIMELIMIT;
					  return -1;
				default: status = TTCB_REMOTE_INTERNAL;
					  return -1;
			  }
		default: return -2;
	}
}


/******************************************************
 * Send a remove request to the remote server. Check
 * the response to see if the request was satisfied.
 * Returns 0 on success, and -1 on remove failure and
 * -2 on other failures.
 */
int Remote::remove(TAS_TC_com_entry *ce) {
        char reply;

	status = TTCB_REMOTE_OK;

	if (!this || state != NORMAL || !*ce) {
		status = TTCB_REMOTE_INTERNAL;
		return -2;
	}
	if (!(serverout << "\\r" << *(set_current_host(ce)) << flush)) {
		status = TTCB_REMOTE_INTERNAL;
		return -1;
	}
	if (Find_next_message(serverin)) {
		status = TTCB_REMOTE_INTERNAL;
		return -2;
	}
	switch (serverin.get()) {
		case 'R': return 0;
                case 'E': reply = serverin.get();
                          switch (reply) {
				case '1': status = TTCB_REMOTE_INTERNAL;
                           		  return -1;
                		case '2': status = TTCB_REMOTE_AUTHORITY;
                          		  return -1;
                		case '4': status = TTCB_REMOTE_NO_JOB;
                           		  return -1;
 				default: status = TTCB_REMOTE_INTERNAL;
                                         return -1;
                          }
		default: return -2;
	}
}


/******************************************************
 * Send a entry list request to the remote server. Check if the
 * response to see if the request will be satisfied.
 * Returns 0 on success, and -1 on request failure and
 * -1 on other failures.
 */
int Remote::liststart(char *User) {
        char reply;
	if (!this || state != NORMAL)
		return -1;
	if (!(serverout << "\\l" << (User ? User : "") << "\n" << flush)) 
		return -1;
	if (Find_next_message(serverin)) return -2;
	switch (serverin.get()) {
		case 'L':
			state = LISTING;
			return 0;
		case 'E': reply = serverin.get();
                          switch (reply) {
                                  case '2' : status = TTCB_REMOTE_AUTHORITY;
                                             return -1;
                                  default  : status = TTCB_REMOTE_INTERNAL;
                                             return -1;
                          }
		default: return -2;
	}
}


/*********************************************************
 * Return next Command Request Entry form listing.
 */
TAS_TC_com_entry Remote::listentry() {
	TAS_TC_com_entry ce;
	Current current;

	if (this && state == LISTING) {
		serverin >> ce;
		if (!ce) state = NORMAL;
		else if (!ce.host)
			// Map server requests
			ce.host = strdup2(host);
		else if (!strcmp(ce.host, current.host())) {
			// Map requests at current host
			delete ce.host;
			ce.host = (char *)0;
		}
	}
	return ce;
}


/************************************************************
 * Get one name of a user utilizing the remote server crontab.
 * When all names have been retrieved, null will be returned
 * once. Next call will restart the retrieving.
 * Returns non-null on success, and null on failure.
 */
char *Remote::userentry() {
	static char buffer[MAXUSERNAMELEN + 2]; 
					 /* 1 extra for terminating '\0' and
					  * 1 extra due to bug in getline
					  */
	if (!this) return (char *)0;

	switch (state) {
		case NORMAL:
			if (!(serverout << "\\u\n" << flush)) return (char *)0;
			if (Find_next_message(serverin)) return (char *)0;
			switch (serverin.get()) {
				case 'U':
					state = USERS;
					break;
				case 'E':
				default:
					return (char *)0;
			}
		case USERS:
			if (!serverin.getline(buffer, MAXUSERNAMELEN + 1) ||
			    !*buffer) {
				state = NORMAL;
				return (char *)0;
			}
			return buffer;
		default:
			return (char *)0;
	}
}



/******************************************************
 * Answers the question if the crontab-file has been 
 * modified since last accessed from this object.
 * Returns 1 if true, 0 if false, and negative on failure.
 */
int Remote::is_cron_changed() {
	if (!this)
		return -1;
	char reply;

	if (!(serverout << "\\c" << "\n" << flush)) 
		return -1;
	if (Find_next_message(serverin)) return -1;
	switch (serverin.get()) {
                case 'C': reply = serverin.get();
                          switch (reply) {
				case '0': return 0;
                		case '1': return 1;
 				default:  return -1;
                          }
		case 'E': return -1;
		default: return -1;
	}
}

/************************************************
 * Checks if the id for a TAS_TC_com_entry is present in the crontab file  
 * Returns 1 if true, 0 if false, and negative on failure.
 */
int Remote::is_scheduled( int Idty ) {
	if (!this)
		return -1;
        if (Idty < 1) 
		return 0;
	char reply;

	if (!(serverout << "\\i" << Idty << "\n" << flush)) 
		return -1;
	if (Find_next_message(serverin)) return -1;
	switch (serverin.get()) {
                case 'I': reply = serverin.get();
                          switch (reply) {
				case '0': return 0;
                		case '1': return 1;
 				default:  return -1;
                          }
		case 'E': return -1;
		default: return -1;
	}
}

/************************************************
 * Checks if a TAS_TC_com_entry is present in the crontab file  
 * Returns 1 if true, 0 if false, and negative on failure.
 */
int Remote::is_scheduled( TAS_TC_com_entry ce) {
        char reply;

	status = TTCB_REMOTE_OK;

	if (!this || state != NORMAL || !ce) {
		status = TTCB_REMOTE_INTERNAL;
		return -2;
	}
	if (!(serverout << "\\s" << *(set_current_host(&ce)) << flush)) {
		status = TTCB_REMOTE_INTERNAL;
		return -1;
	}
	if (Find_next_message(serverin)) {
		status = TTCB_REMOTE_INTERNAL;
		return -2;
	}
	switch (serverin.get()) {
		case 'S': return 0;
                case 'E': reply = serverin.get();
                          switch (reply) {
				case '0': return 0;
                		case '1': return 1;
 				default:  return -1;
                          }
		default: return -2;
	}
}


