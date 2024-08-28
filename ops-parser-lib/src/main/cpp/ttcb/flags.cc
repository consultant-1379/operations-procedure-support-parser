//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/flags.cc @@/main/1 2000-03-10.17:23 EHS

/*
 *--------------------------------------------------------------------------
 *
 * Name         flags.C
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
 * Document no  14/19055-CAA 134 420
 *
 * Rev-state    A
 *
 * Original     1990-04-24 by TX/HJL Anders Olander
 *
 * Description  Extracts th flag arguments from argv.
 *        
 * Revision     <rev> <yyyy-mm-dd> by <dep> <name>
 * Description  <description-of-the-revision>
 *
 *-------------------------------------------------------------------------
 */

#include <mystring.hh>

#include <flags.hh>


/**********************************************************
 * Constructor. Copies the argv string, and makes an array
 * where you can use flag character as an index, to find
 * the corresponding flags argument.
 * Inputs: Available - a string containing all allowed flags.
 *	   Argv - the argument vector argv;
 */
Flags::Flags(char *Available, char **Argv) {
	int argc, temp;
	char *farg;

	available = (char *)0;
	table = argv = (char **)0;

	// Copy argv and available
	if (!(available = strdup2(Available))) return;
	for (argc = 0; Argv[argc]; argc++);
	if (!(argv = new char *[argc + 1])) {
		return;
	}
	for (temp = 0; argv[temp] = Argv[temp]; temp++);

	// Make table
	if (!(table = new char *[strlen(Available) + 1])) {
		return;
	}
	for (temp = strlen(Available); table[temp] = 0, temp--;);

	// Work loop
	for (temp = 0; argv[temp]; temp++) {
		if (argv[temp][0] == '-' && 
		    (farg = strchr(available, argv[temp][1]))) {
			if (argv[temp][2] == '\0' &&
			    argv[temp + 1] &&
			    argv[temp + 1][0] != '-')
				table[farg - available] = argv[temp + 1];
			else
				table[farg - available] = argv[temp] + 2;
			argv[temp] = 0;
		}
	}
}


/*******************************************************
 * Destructor
 */
Flags::~Flags() {
	delete available;
	delete argv;
	delete table;
}


/****************************************************
 * Get one flag argument. If flag doesn't exist, null
 * is returned.
 */
const char *Flags::operator &(const char flag) {
	char *curr;
	if (!this || !flag ||
	    !table || !argv || !available)
		return (const char *)0;

	if (curr = strchr(available, flag))
		return table[curr - available];
	else
		return (const char *)0;
}

