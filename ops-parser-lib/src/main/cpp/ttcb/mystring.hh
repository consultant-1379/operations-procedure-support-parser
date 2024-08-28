#ifndef MYSTRING_H
#define MYSTRING_H
//Source Code COntrol System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/mystring.hh @@/main/1 2000-03-10.17:23 EHS

/*
 *--------------------------------------------------------------------------
 *
 * Name         mystring.H
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
 * Document no  32/19055-CAA 134 420
 *
 * Rev-state    A
 *
 * Original     1990-04-06 by TX/HJL Anders Olander
 *
 * Description  Useful string function, that are not provided by under-
 *              lying products.
 *        
 * Revision     <rev> <yyyy-mm-dd> by <dep> <name>
 * Description  <description-of-the-revision>
 *
 *-------------------------------------------------------------------------
 */

#include <string.h>

static char *strdup2(const char *s) {
	char *dup_s;
	if (!s || !(dup_s = new char[strlen(s) + 1]))
		return (char *)0;
	return strcpy(dup_s, s);
}

static char *strshl(char *s) {
	char *shifted_s = s;
	while (*s) {
		s[0] = s[1];
		s++;
	}
	return shifted_s;
}
	
#endif

