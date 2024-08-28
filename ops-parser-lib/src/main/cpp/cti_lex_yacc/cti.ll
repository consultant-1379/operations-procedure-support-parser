%{
//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/cti_lex_yacc/cti.ll @@/main/2 2000-01-04.19:40 EHS

/*--------------------------------------------------------------------------
 *
 * Name         cti.L
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
 * Document no  07/19055-CAA 134 420
 *
 * Rev-state    B
 *
 * Original     1990-04-06 by TX/HJL Anders Olander
 *
 * Description  Lexical analyse code for reading CrontabFile objects
 *              from files.
 *        
 * Revision     B 1992-08-25 by TM/HJG Gunni Kallander
 * Description  Possible to use different signs (-) in the host name.
 *
 *-------------------------------------------------------------------------
 */


/* #include <libc.h> */
#include <stdlib.h>
#include <string.h>

#define CAT	strcat(collected_line, (const char *)yytext);
/* Crontab can't handle more than approx. 950 bytes,
 * so there won't be any problems.
 */

#define yywrap()	1

%}

%start SHF COM HOST

%%

<COM>[^ \'\t\n][^\'\n]*	{CAT; yylval.string = strdup2((const char *)yytext); return COMMAND;}
\*		{CAT; return ASTERISK;}
\,		{CAT; return COMMA;}
[0-9]+		{CAT; yylval.number = atoi((const char *)yytext); return NUMBER;}
\n		{BEGIN 0; return EOL;}
ttcshr		{CAT; BEGIN SHF; return SHELL;}
<SHF>\-i	{CAT; return I_FLAG;}
<SHF>\-y	{CAT; return Y_FLAG;}
<SHF>\-h	{CAT; BEGIN HOST; return H_FLAG;}
<SHF>\-m	{CAT; return M_FLAG;}
<SHF>\-c	{CAT; BEGIN COM; return C_FLAG;}
<HOST>[^ \t\n\#]+	{
		CAT; yylval.string = strdup2((const char *)yytext); BEGIN SHF; return STRING;
		}
.		{CAT;}

