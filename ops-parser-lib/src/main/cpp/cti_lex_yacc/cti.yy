%{
//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/cti_lex_yacc/cti.yy @@/main/3 2000-03-10.17:24 EHS

/*--------------------------------------------------------------------------
 *
 * Name         cti.Y
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
 * Document no  08/19055-CAA 134 420
 *
 * Rev-state    A
 *
 * Original     1990-04-06 by TX/HJL Anders Olander
 *
 * Description  Syntax analyse code for reading CrontabFile objects from
 *              files.
 *        
 * Revision     <rev> <yyyy-mm>-dd by <dep> <name>
 * Description  <description-of-the-revision>
 *
 *-------------------------------------------------------------------------
 */


#include <mystring.hh>

// #include <intheap.H>
#include <queuenotail.hh>

//#define yyerror(S)

%}

%nonassoc ASTERISK NUMBER EOL SHELL COMMAND STRING
%nonassoc Y_FLAG I_FLAG M_FLAG H_FLAG C_FLAG
%left COMMA

%union {
	int number;
	Ttc_Queue_no_tail *entry;
	char *string;
}

%type <number> NUMBER
%type <entry> field numberlist
%type <string> COMMAND STRING

%start line

%%

line	: 				{return TTCB_CRT_EOF;}
	| field field field field field shell COMMAND EOL {
					 delete command; command = $7;
					 delete minute; minute = $1;
					 delete hour; hour = $2;
					 delete day; day = $3;
					 delete month; month = $4;
					 delete weekday; weekday = $5;
					 return TTCB_CRT_OK;}
	| error EOL			{yyerrok;
					 return TTCB_CRT_PROBLEMS;}
	;


field	: ASTERISK			{$$ = new Ttc_Queue_no_tail;}
	| numberlist			{$$ = $1;}
	;


numberlist : NUMBER			{$$ = new Ttc_Queue_no_tail;
					 if ($$->add($1)) {
						delete $$;
						$$ = (Ttc_Queue_no_tail *)0;
					 }
					}
	   | numberlist COMMA NUMBER	{if ($1->add($3)) {
						delete $1;
						$$ = (Ttc_Queue_no_tail *)0;
					 } else {
						$$ = $1;
					 }
					}
	   ;

shell	: SHELL flaglist C_FLAG
	;

flaglist:				{year = TCANY;
					 id = 0;
					 delete host; host = (char *)0;}
	| flaglist Y_FLAG NUMBER	{year = $3;}
	| flaglist I_FLAG NUMBER	{id = $3;}
	| flaglist M_FLAG NUMBER
	| flaglist H_FLAG STRING	{host = $3;}
	;

%%
void yyerror(const char *){
    return;
}
