/*
 *--------------------------------------------------------------------------
 *
 * Name         tctrl_remote.hh
 *
 * *******************************************************************
 * * COPYRIGHT (c) 1990   Ericsson Telecom AB, Sweden.               *
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
 * Document no  25/19055-CAA 134 420
 *
 * Rev-state    C
 *
 * Original     1990-04-02 by TX/HJL Anders Olander
 *
 * Description  Providing the interface between a remote
 *		time control server and its client.
 *        
 * Revision     B by TM/HJG Gunni Kallander
 * Description  com_entry changed to tas_tc_com_entry.
 *
 * Revision     C 1993-07-08 by JV/PBJ Erika Biesse
 * Description  Method for asking if the crontabfile has changed since 
 *              last accessed by this object. New return code in add,
 *		TTCB_REMOTE_TIMELIMIT.
 *
 *-------------------------------------------------------------------------
 */

#ifndef TCTRL_REMOTE_H
#define TCTRL_REMOTE_H
//Source Code Contrl System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/tctrl_remote.hh @@/main/1 2000-03-10.17:23 


#include <fstream>
using namespace std;
#include <tas_tc_com_entry.hh>

class Remote {
public:
	Remote(char *Host);
	~Remote();

	int add(TAS_TC_com_entry *);
	int remove(TAS_TC_com_entry *);

	int liststart(char *User = (char *)0);
	TAS_TC_com_entry listentry();
	char *userentry();
	int is_cron_changed();
	int is_scheduled (int);
	int is_scheduled (TAS_TC_com_entry);

	int accept(std::istream&, std::ostream&);
        int get_error_code();
private:
	TAS_TC_com_entry *set_current_host(TAS_TC_com_entry *);

private:
	int state, status;
        pid_t pidr;
	std::ifstream serverin;
	std::ofstream serverout;
	char *host;
};


// Flag signaling remote server (Compare cti.hh - tc_shell flags)
#define TTCB_TC_SERVER_FLAG		'T'
#define TTCB_TC_FLAG_STRING		"T"
#define TTCB_REMOTE_OK			(0)
#define TTCB_REMOTE_INTERNAL		(1)
#define TTCB_REMOTE_AUTHORITY		(2)
#define TTCB_REMOTE_ALREADY_IN_QUEUE	(3)
#define TTCB_REMOTE_NO_JOB		(4)
#define TTCB_REMOTE_TIMELIMIT		(5)
#endif
