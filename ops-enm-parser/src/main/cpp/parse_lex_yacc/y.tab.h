/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_OZT_PARSER_TAB_HH_INCLUDED
# define YY_YY_OZT_PARSER_TAB_HH_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DUMMY = 258,
     OZT_T_ERROR = 259,
     OZT_T_C_STYLE_COMMENT = 260,
     OZT_T_EOLN = 261,
     OZT_T_LABELNAME = 262,
     OZT_T_STRING = 263,
     OZT_T_DEC_CHAR_CONST = 264,
     OZT_T_HEX_CHAR_CONST = 265,
     OZT_T_NUM_CONST = 266,
     OZT_T_A = 267,
     OZT_T_AND = 268,
     OZT_T_AP = 269,
     OZT_T_APSETSIDE = 270,
     OZT_T_C = 271,
     OZT_T_CHDIR = 272,
     OZT_T_CHECK = 273,
     OZT_T_CLOSE = 274,
     OZT_T_CLRSCR = 275,
     OZT_T_COMMENT = 276,
     OZT_T_SETDEVID = 277,
     OZT_T_SETERRORFLAG = 278,
     OZT_T_UNSETDEVID = 279,
     OZT_T_CONNECT = 280,
     OZT_T_DEC = 281,
     OZT_T_DELAY = 282,
     OZT_T_DELAYSEC = 283,
     OZT_T_DEVID = 284,
     OZT_T_DIAGNOSTICS = 285,
     OZT_T_DISCONNECT = 286,
     OZT_T_DRAW = 287,
     OZT_T_E = 288,
     OZT_T_ELSE = 289,
     OZT_T_ENDIF = 290,
     OZT_T_BREAK = 291,
     OZT_T_EOF = 292,
     OZT_T_ERASE = 293,
     OZT_T_EVDELETE = 294,
     OZT_T_EXECUTE = 295,
     OZT_T_FLUSHVAR = 296,
     OZT_T_FOR = 297,
     OZT_T_FORM = 298,
     OZT_T_FUNBUSY = 299,
     OZT_T_G = 300,
     OZT_T_GE = 301,
     OZT_T_GT = 302,
     OZT_T_GETDATE = 303,
     OZT_T_GETEXCHHDR = 304,
     OZT_T_GETIOTYPE = 305,
     OZT_T_GETPROTOCOLTYPE = 306,
     OZT_T_GETPHASE = 307,
     OZT_T_GETPROGRESS = 308,
     OZT_T_GETTOTALCOUNT = 309,
     OZT_T_LABELEXIST = 310,
     OZT_T_GETMARK = 311,
     OZT_T_GETERRORFLAG = 312,
     OZT_T_GETSESSIONID = 313,
     OZT_T_GETDIR = 314,
     OZT_T_GOSUB = 315,
     OZT_T_GOTO = 316,
     OZT_T_ONDISCONNECT = 317,
     OZT_T_ONTIMEOUT = 318,
     OZT_T_H = 319,
     OZT_T_I = 320,
     OZT_T_IF = 321,
     OZT_T_IFERROR = 322,
     OZT_T_INC = 323,
     OZT_T_INCLUDE = 324,
     OZT_T_INKEY = 325,
     OZT_T_INPUT = 326,
     OZT_T_L = 327,
     OZT_T_LE = 328,
     OZT_T_LT = 329,
     OZT_T_LABEL = 330,
     OZT_T_LOG = 331,
     OZT_T_LOGOF = 332,
     OZT_T_LOGON = 333,
     OZT_T_MARK = 334,
     OZT_T_MENU = 335,
     OZT_T_MAIL = 336,
     OZT_T_FILE = 337,
     OZT_T_MKDIR = 338,
     OZT_T_NE = 339,
     OZT_T_NEXT = 340,
     OZT_T_OPENREAD = 341,
     OZT_T_OR = 342,
     OZT_T_ORDERED = 343,
     OZT_T_P = 344,
     OZT_T_PRINTER = 345,
     OZT_T_PROMPT = 346,
     OZT_T_QUIT = 347,
     OZT_T_R = 348,
     OZT_T_READ = 349,
     OZT_T_RENAME = 350,
     OZT_T_REPORT = 351,
     OZT_T_RESET = 352,
     OZT_T_RESTART = 353,
     OZT_T_RETURN = 354,
     OZT_T_RMDIR = 355,
     OZT_T_S = 356,
     OZT_T_SAVEDIR = 357,
     OZT_T_SELFILE = 358,
     OZT_T_SELPRINT = 359,
     OZT_T_SEND = 360,
     OZT_T_SENDAP = 361,
     OZT_T_SET = 362,
     OZT_T_SETPHASE = 363,
     OZT_T_SETPROGRESS = 364,
     OZT_T_SETREPLY = 365,
     OZT_T_SETTOTALCOUNT = 366,
     OZT_T_STEPPROGRESS = 367,
     OZT_T_SPONTREP = 368,
     OZT_T_SPONTREPOFF = 369,
     OZT_T_STOP = 370,
     OZT_T_SWITCH = 371,
     OZT_T_IN = 372,
     OZT_T_CASE = 373,
     OZT_T_DEFAULT = 374,
     OZT_T_ENDSWITCH = 375,
     OZT_T_T = 376,
     OZT_T_TO = 377,
     OZT_T_THEN = 378,
     OZT_T_VIEWFILE = 379,
     OZT_T_W = 380,
     OZT_T_WAITFOR = 381,
     OZT_T_WAITREPLY = 382,
     OZT_T_WINDEND = 383,
     OZT_T_WINDOW = 384,
     OZT_T_WRITE = 385,
     OZT_T_Z = 386,
     OZT_T_ADVANCE = 387,
     OZT_T_REGRESS = 388,
     OZT_T_CENTRALDIR = 389,
     OZT_T_CONCAT = 390,
     OZT_T_CREATECHILDSESSION = 391,
     OZT_T_STARTCHILDSESSION = 392,
     OZT_T_CHECKCHILDSESSION = 393,
     OZT_T_TERMINATECHILDSESSION = 394,
     OZT_T_READVARIABLE = 395,
     OZT_T_STYLE = 396,
     OZT_T_COPY = 397,
     OZT_T_DECIMAL = 398,
     OZT_T_DISKFREE = 399,
     OZT_T_EVLOADED = 400,
     OZT_T_GETDEST = 401,
     OZT_T_GETFILELENGTH = 402,
     OZT_T_GETLOG = 403,
     OZT_T_GETMODE = 404,
     OZT_T_GETPRINT = 405,
     OZT_T_GETSCHED = 406,
     OZT_T_GETDEVID = 407,
     OZT_T_HEX = 408,
     OZT_T_INHISTORY = 409,
     OZT_T_LENGTH = 410,
     OZT_T_LOWCASE = 411,
     OZT_T_POS = 412,
     OZT_T_PAD = 413,
     OZT_T_PRIVATEDIR = 414,
     OZT_T_REPLY = 415,
     OZT_T_REPLYLEN = 416,
     OZT_T_SCAN = 417,
     OZT_T_TIMEEVSET = 418,
     OZT_T_TRIM = 419,
     OZT_T_UPCASE = 420,
     OZT_T_VAR = 421,
     OZT_T_VAREXIST = 422,
     OZT_T_VERSION = 423,
     OZT_T_FORMFIELD = 424,
     OZT_T_LN = 425,
     OZT_T_FORMCOMBO = 426,
     OZT_T_FORMBUTTON = 427,
     OZT_T_FORMCHECKBOX = 428,
     OZT_T_FORMRADIOBUTTON = 429
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

//extern YYSTYPE yylval;
extern int yylval;
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_OZT_PARSER_TAB_HH_INCLUDED  */
