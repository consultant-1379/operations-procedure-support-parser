#ifndef FLAGS_H
#define FLAGS_H

//Source Code Contrl System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/flags.hh @@/main/1 2000-03-10.17:23 EHS

/*
 *--------------------------------------------------------------------------
 *
 * Name         flags.H
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
 * Document no  13/19055-CAA 134 420
 *
 * Rev-state    B
 *
 * Original     1990-04-24 by TX/HJL Anders Olander
 *
 * Description  Extarcts the flag arguments from argv.
 *        
 * Revision     B 1994-07-06 by EHS/PBJ Gunni Kallander
 * Description  const char * changed to char
 *
 *-------------------------------------------------------------------------
 */

 
class Flags {
public:
//	Flags(const char *Available, const char **Argv);
        Flags(char *Available, char **Argv);
	~Flags();

	const char *operator &(const char);

private:
	char *available;
//	const char **table;
//	const char **argv;
	char **table;
	char **argv;
};

#endif

