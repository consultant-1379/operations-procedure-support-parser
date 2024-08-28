%{
//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/com_entry_lex_yacc/com_entry.yy @@/main/2 2000-01-11.16:47 EHS

/*--------------------------------------------------------------------------
 *
 * Name         com_entry.yy
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
 * Document no  04/19055-CAA 134 420
 *
 * Rev-state    A
 *
 * Original	1990-04-04 by TX/HJL Anders Olander
 *
 * Description  Yacc input for ttcb_ce_yyparse
 *        
 * Revision     <rev> <yyyy-mm>-dd by <dep> <name>
 * Description  <description-of-the-revision>
 *
 *-------------------------------------------------------------------------
 */


//#define yyerror(S)		0
#include <tas_tc_com_entry.hh>

%}

%right DASH
%nonassoc COMMAND ID SNABLE NUMBER COLON STDINTV EVY_WEEK SLASH WEEKDAY BLOCK
%token EOL BAD_CHAR

%union {
	char *string;
	int number;
	enum interv interval;
}

%type <string> COMMAND ID 
%type <number> NUMBER WEEKDAY
%type <interval> STDINTV EVY_WEEK

%start line

%%

line	:				{return TTCB_CE_EMPTY; /* End of input */}
	| user id host date rep com EOL	{return TTCB_CE_OK; /* Normal */}
	| error EOL			{yyerrok; return TTCB_CE_BAD_INPUT_SYNTAX;
						/* Error */}
	;

user	:				{delete user; user = (char *)0;}
	| ID				{delete user; user = $1;}
	;

id	:				{id = 0;}
	| NUMBER			{id = $1;}
	;

host	:				{delete host; host = (char *)0;}
	| SNABLE ID			{delete host; host = $2;}
	;

date	: NUMBER DASH NUMBER DASH NUMBER NUMBER COLON NUMBER {
					year = $1;
					month = $3;
					day = $5;
					hour = $6;
					minute = $8;
					}
	|             NUMBER DASH NUMBER NUMBER COLON NUMBER {
					year = TCANY;
					month = $1;
					day = $3;
					hour = $4;
					minute = $6;
					}
	|                         NUMBER NUMBER COLON NUMBER {
					year = TCANY;
					month = TCANY;
					day = $1;
					hour = $2;
					minute = $4;
					}
	|                                NUMBER COLON NUMBER {
					year = TCANY;
					month = TCANY;
					day = TCANY;
					hour = $1;
					minute = $3;
					}
	|                                             NUMBER {
					year = TCANY;
					month = TCANY;
					day = TCANY;
					hour = TCANY;
					minute = $1;
					}
	;

rep	:				{intervalbase = NONE; split = 1;}
	| STDINTV SLASH NUMBER		{intervalbase = $1; split = $3;}
	| STDINTV			{intervalbase = $1; split = 1;}
	| EVY_WEEK SLASH WEEKDAY	{intervalbase = WEEKLY; split = $3;}
	| EVY_WEEK SLASH NUMBER		{intervalbase = WEEKLY; split = $3;}
	;

com	: BLOCK COMMAND			{delete commandline; commandline = $2;}
	;

%%

void yyerror(const char *){
    return;
}

