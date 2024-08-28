
#ifndef TCPARAM_H
#define TCPARAM_H

/*
 *--------------------------------------------------------------------------
 *
 * Name         tcparam.H
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
 *		Software unit	TTCLIB
 *              
 * Document no  31/19055-CAA 134 420
 *
 * Rev-state    A
 *
 * Original     1990-04-25 by TX/HJL Anders Olander
 *
 * Description  General macro definitions, needed in tc functions.
 *        
 * Revision     <rev> <yyyy-mm-dd> by <dep> <name>
 * Description  <Description-of-the-revision>
 *
 *-------------------------------------------------------------------------
 */

// Max user name length, specified in passwd(5).
#define MAXUSERNAMELEN 8
#define MAXINTLEN 10

// Crontab files directory, specified in crontab(5).

/* This code was modified for TMOS/HP. The reason is described in HPUX.24 */
#ifdef __hpux
#define CRONTABLIB "/usr/spool/cron/crontabs/"
#else
#define CRONTABLIB "/var/spool/cron/crontabs/"
#endif

// Lock file name. File placed in user's home directory.
#define TC_LOCK_FILE "/.ttc_lock"

// Name of environmental varible specifing name of time control server.
#define TTCB_SERVER_ENV "TTC_SERVER"

// Prefix needed when executing outside any login-shell
#define SETENV "source .login ; "

// Suffix needed to hide different shell behaviour
#define EXIT0 " ; exit 0"

#endif






