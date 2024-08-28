/*
 *--------------------------------------------------------------------------
 *
 * Name         tctrl_local.hh
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
 * Document no  23/19055-CAA 134 420
 *
 * Rev-state    D
 *
 * Original     1990-04-02 by TX/HJL Anders Olander
 *
 * Description  "Local" object are peep-holes into the activation queue.
 *              The crontab list on the local machine is used.
 *        
 * Revision     B 1992-02-27 by TM/HJG GUnni Kallander
 * Description  com_entry has been changed to tas_tc_com_entry.
 *
 * Revision     C 1993-07-08 by JV/PBJ Erika Biesse
 * Description  Method for asking if the crontabfile has changed since 
 *              last accessed by this object. New return code in add,
 *		TTCB_LOCAL_TIMELIMIT.
 *
 * Revision	D 1994-06-28 by EHS/PBJ Gunni Kallander
 *
 *
 *-------------------------------------------------------------------------
 */

#ifndef TCTRL_LOCAL_H
#define TCTRL_LOCAL_H

#include <fstream>
#include <sys/types.h>
using namespace std;
#include <tas_tc_com_entry.hh>

class Local {
public:
	Local() {state = 0; status = 0; crontab_last_written = Get_mod_time();}

	int add(TAS_TC_com_entry *);
	int remove(TAS_TC_com_entry *);

	int liststart(char *User = (char *)0);
	TAS_TC_com_entry listentry();

	char *userentry();

        int get_error_code();
	int is_cron_changed();
	int is_scheduled (int id, const char* user = NULL);
	int is_scheduled (TAS_TC_com_entry);

private:
	int state, status;
        pid_t pid;
	/*/std::CrontabFile *ctfp; // Only used for list service */
	std::ifstream istr;
	time_t crontab_last_written;

	time_t Get_mod_time();
	int add_ctf(TAS_TC_com_entry *ce);
	int remove_ctf(TAS_TC_com_entry *ce);

};

// Value for status
#define TTCB_LOCAL_OK		(0)
#define TTCB_LOCAL_INTERNAL	(1)
#define TTCB_LOCAL_AUTHORITY	(2)
#define TTCB_LOCAL_ALREADY_IN_QUEUE	(3)
#define TTCB_LOCAL_NO_JOB	(4)
#define TTCB_LOCAL_TIMELIMIT	(5)
#endif
