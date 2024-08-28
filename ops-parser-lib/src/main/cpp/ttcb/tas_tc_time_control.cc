//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/tas_tc_time_control.cc @@/main/3 2000-04-16.12:00 EHS

/*
 *--------------------------------------------------------------------------
 *
 * Name         tas_tc_time_control.cc
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
 * Document no  28/19055-CAA 134 420
 *
 * Rev-state    C
 *
 * Original     1990-04-02 by TX/HJL Anders Olander
 *
 * Description  These objects are peep-holes into the activation queue,
 *              and its main job is to decide if the local crontab list
 *              or some remote list should be used, and create an
 *              apropriate objetct (Local or Remote).
 *
 * Revision     B 1992-02-18 by TM/HJG Gunni Kallander
 * Description  time_control.H changed to tas_tc_time_control.hh
 *              time_control changed to TAS_TC_time_control
 *
 * Revision     C 1993-07-08 by JV/PBJ Erika Biesse
 * Description  Method for asking if the crontabfile has changed since
 *              last accessed by this object.
 *
 *-------------------------------------------------------------------------
 */

//#include <colme.C>
//#include <colme_CXA_101_005.C>
//Anders Berglund VK/EHS/PBO 950919

/*#include <libc.h>*/
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <tcparam.hh>
#include <tas_tc_string_array.hh>
#include <tctrl_local.hh>
#include <tctrl_remote.hh>
#include <current.hh>
#include <cegrow.hh>
#include <CHA_Trace.H>

#include <tas_tc_time_control.hh>

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"TAS_TC_time_control", (char*)"C");

/***************************************************
 * Constructor. Checks if running on the time
 * control server or not. When running on server
 * class Local will be used, otherwise class Remote.
 * The functionallity of Local is a subset of the
 * functinallity of the Remote class.
 */
TAS_TC_time_control::TAS_TC_time_control() {
	local = new Local;
	remote = (Remote *)0;
	return;
}


/****************************************************
 * Destructor
 */
TAS_TC_time_control::~TAS_TC_time_control() {
	delete remote, remote = (Remote *)0;
	delete local, local = (Local *)0;
}


/***************************************************
 * Returns an error code
 */
int TAS_TC_time_control::get_error_code() {
         if (remote)
                  return remote->get_error_code();
         else if (local)
                  return local->get_error_code();
         return -3;
}


/**************************************************
 * Add a Command Request Entry
 * Returns 0 on success, negative on failure.
 */
int TAS_TC_time_control::add(TAS_TC_com_entry ce) {
	if (remote)
		return remote->add(&ce);
	else if (local)
		return local->add(&ce);
	return -3;
}
int TAS_TC_time_control::add(TAS_TC_com_entry *ce) {
	if (remote)
		return remote->add(ce);
	else if (local)
		return local->add(ce);
	return -3;
}


/**************************************************
 * Remove a Command Request Entry
 * Returns 0 on success, negative on failure.
 */
int TAS_TC_time_control::remove(TAS_TC_com_entry ce) {

  int result = -3;

  //TRACE_IN(trace, remove, "remote=" << remote);

  if (remote) {
    result = remote->remove(&ce);
    //TRACE_FLOW(trace, remove, "result: " << result);
  }
  else if (local) {
    result = local->remove(&ce);
    //TRACE_FLOW(trace, remove, "result: " << result);
  }
  else {
    //TRACE_FLOW(trace, remove, "result: " << result);
  }

  //TRACE_RETURN(trace, remove, "");
  return result;
}


/**************************************************
 * List Command Request Entries
 * Returns non-null on success, and null on failure.
 */
TAS_TC_com_entry *TAS_TC_time_control::list(char *User) {
	GrowCEArray cea;
	TAS_TC_com_entry ce, *cep;
	int count;
	if (!remote && !local) return (TAS_TC_com_entry *)0;
	if (remote ? remote->liststart(User) : local->liststart(User))
		return (TAS_TC_com_entry *)0;

        count = 0;
        if (remote)
            ce = remote->listentry();
        else
            ce = local->listentry();
        while (ce) {
           cea.set(count++, ce);
           if (remote)
               ce = remote->listentry();
           else
               ce = local->listentry();
        }

//	for (count = 0;
//	 ce = (remote ? remote->listentry() : local->listentry());
//	 cea.set(count++, ce));

        cep = new TAS_TC_com_entry[++count];
        while (count--)
            cep[count] = cea.get(count);

//	for (cep = new TAS_TC_com_entry[++count]; count--; cep[count] = cea.get(count));

	return cep;
}


/************************************************
 * List users utilizing time control facilities.
 * Returns non-null on success, and null on failure.
 */
char **TAS_TC_time_control::users() {
	TAS_TC_string_array ca;
	char *ue;
	if (!remote && !local)
		return (char **)0;
	while (ue = (remote ? remote->userentry() : local->userentry()))
		ca.add(ue);
	return ca.build();
}

/************************************************
 * Answers the question if the crontab-file has been
 * modified since last accessed from this object.
 * Returns 1 if true, 0 if false, and negative on failure.
 */
int TAS_TC_time_control::is_cron_changed() {
	if (remote)
		return remote->is_cron_changed();
	else if (local)
		return local->is_cron_changed();
	return -3;
}

/************************************************
 * Checks if the id for a TAS_TC_com_entry is present in the crontab file
 * Returns 1 if true, 0 if false, and negative on failure.
 */
int TAS_TC_time_control::is_scheduled(int Idty, const char* user) {
	if (remote)
		return remote->is_scheduled(Idty);
	else if (local)
		return local->is_scheduled(Idty, user);
	return -3;
}

/************************************************
 * Checks if a TAS_TC_com_entry is present in the crontab file
 * Returns 1 if true, 0 if false, and negative on failure.
 */
int TAS_TC_time_control::is_scheduled( TAS_TC_com_entry ce) {
	if (remote)
		return remote->is_scheduled(ce);
	else if (local)
		return local->is_scheduled(ce);
	return -3;
}

/************************************************
 * Checks if server name is among aliases
 */
int TAS_TC_time_control::among_aliases(char* server) {

  struct hostent *hostent_p;

  hostent_p = gethostent();

  int i=0;
  while(hostent_p->h_aliases[i] != NULL) {
    if(strcmp(server, hostent_p->h_aliases[i]) == 0) {
      return 1;
    }
    i++;
  }

  return 0;
}



