#ifndef TAS_TC_STRING_ARRAY_H
#define TAS_TC_STRING_ARRAY_H
//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/tas_tc_string_array.hh @@/main/1 2000-03-10.17:23 EHS
/*
 *--------------------------------------------------------------------------
 *
 * Name         tas_tc_string_array.H
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
 * Document no  19/19055-CAA 134 420
 *
 * Rev-state    A
 *
 * Original     1990-04-02 by TX/HJL Anders Olander
 *
 * Description  Class providing a few methods for composing strings.
 *		For more details, please read tas_tc_string_array.C .
 *        
 * Revision     <rev> <yyyy-mm-dd> by <dep> <name>
 * Description  <description-of-the-revision>
 *
 *-------------------------------------------------------------------------
 */



class TAS_TC_string_array {
public:
	TAS_TC_string_array();
	~TAS_TC_string_array();

	int add(const char *);

	char **build();
	char *catenate();

private:
	void *head;
	void **last;
};

#endif

