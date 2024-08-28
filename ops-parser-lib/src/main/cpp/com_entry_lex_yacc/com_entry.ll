%{
//Source Code Control System revision handling, optional
//SCCS:%W% %E% EHS
 
/*--------------------------------------------------------------------------
 *
 * Name         com_entry.ll
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
 * Document no  03/19055-CAA 134 420
 *
 * Rev-state    B
 *
 * Original     1990-04-04 by TX/HJL Anders Olander
 *
 * Name         ttcb_ce_yylex
 * Description  lexical analyzer. Compare syntax in << ComEntry.
 *        
 * Revision     B 1992-09-11 by TM/HJG Gunni Kallander
 * Description  Possible to use - sign in the host name
 *
 *-------------------------------------------------------------------------
 */

#ifdef SunOS4
#include <sysent.h>
#else
#include <stdlib.h>
#endif

#define yywrap()	1

/* %e ...  are optimizations */
%}

%e  200
%p  900
%n  150
%k  250
%a 2300
%o 4000

%start COM HOST

%%

<COM>.*			{BEGIN 0;
			 yylval.string = strdup2((const char *)yytext);
			 return COMMAND;}
\@			{BEGIN HOST; return SNABLE;}
\-			{return DASH;}
\:			{return COLON;}
A[A-Za-z]* 		{yylval.interval = ANNUALLY; return STDINTV;}
M[Oo][Nn][Tt][A-Za-z]*	{yylval.interval = MONTHLY; return STDINTV;}
D[A-Za-z]*		{yylval.interval = DAILY; return STDINTV;}
H[A-Za-z]*		{yylval.interval = HOURLY; return STDINTV;}
W[Ee][Ee][A-Za-z]*	{yylval.interval = WEEKLY; return EVY_WEEK;}
\/			{return SLASH;}
S[Uu][A-Za-z]* 		{yylval.number = SUN; return WEEKDAY;}
M[Oo][Nn][Dd]?[A-Za-z]*	{yylval.number = MON; return WEEKDAY;}
T[Uu][A-Za-z]*		{yylval.number = TUE; return WEEKDAY;}
W[Ee][Dd][A-Za-z]*	{yylval.number = WED; return WEEKDAY;}
T[Hh][A-Za-z]*		{yylval.number = THU; return WEEKDAY;}
F[A-Za-z]*		{yylval.number = FRI; return WEEKDAY;}
S[Aa][A-Za-z]*		{yylval.number = SAT; return WEEKDAY;}
\#\ *			{BEGIN COM; return BLOCK;}
[0-9]+			{yylval.number = atoi((const char *)yytext); return NUMBER;}
<HOST>[^ \t\n\#]+	{yylval.string = strdup2((const char *)yytext);
				BEGIN 0; return ID;}
[A-Za-z0-9_]+		{yylval.string = strdup2((const char *)yytext); return ID;}
[ \t]			;
\n			{return EOL;}
.			{return BAD_CHAR;}














