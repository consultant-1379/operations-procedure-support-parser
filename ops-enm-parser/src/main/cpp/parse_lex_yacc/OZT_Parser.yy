/*------------------------------------------------------------------------------
 *******************************************************************************
 * COPYRIGHT Ericsson 2018
 *
 * The copyright to the computer program(s) herein is the property of
 * Ericsson Inc. The programs may be used and/or copied only with written
 * permission from Ericsson Inc. or in accordance with the terms and
 * conditions stipulated in the agreement/contract under which the
 * program(s) have been supplied.
 *******************************************************************************
 *----------------------------------------------------------------------------*/

%{

#include <CHA_OZTInfo.H>
#include <OZT_Parser.H>
#include <OZT_SourceMgr.H>
#include <OZT_SourceInfo.H>
#include <OZT_Interpreter.H>
#include <OZT_Value.H>
#include <OZT_VarStore.H>
#include <OZT_CmdSender.H>
#include <OZT_RspReceiver.H>
#include <OZT_CmdRspBuf.H>
#include <OZT_FileMgr.H>
#include <CHA_FileLogger.H>
#include <CHA_MailLogger.H>
#include <CHA_PrinterLogger.H>
#include <OZT_RspCatcher.H>
#include <OZT_Clock.H>
#include <OZT_Pipe.H>
#include <OZT_TimeOrder.H>
#include <OZT_Time.H>
#include <OZT_Mail.H>
#include <OZT_CommentWinModel.H>
#include <OZT_EventHandler.H>
#include <OZT_IOW.H>
#include <OZT_Disk.H>
#include <OZT_Misc.H>
#include <OZT_ChildHandler.H>

/// TODO #include <colme.C>  //In Karma
#include <rw/cstring.h>
#include <rw/tpordvec.h>
#include <rw/tvordvec.h>
#include <iostream>
//*****************************************************************************
// trace
#include <trace.H>
//static CAP_TRC_trace trace = CAP_TRC_DEF(((char*)"OZT_Parser"), ((char*)"C"));

//*****************************************************************************

// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "ClearCase: @(#) syn-opsserver/server/parse/src/OZT_Parser.yy @@/main/3 2000-02-25.15:29 EHS";

//*****************************************************************************

//
//   The following variable is used by the yacc
//   and lex generated code to communicate to each other.
//
int                        ozt_sc = SC_NORMAL;
OZT_Value                  ozt_TokenVal;

//
//   The following is used to deal with some silly Ozterm syntax
//
//   e.g. @DRAW(CUP,...)<---- Here, if CUP is defined as a variable, the
//                            value of the variable is used as the value
//                            supplied to DRAW(). If not, it is treated
//                            as the special constant "CUP" instead.
//
enum OZT_Context {OZT_NORM_CTXT,
                  OZT_DRAW_CTXT,
		  OZT_STYLE_CTXT
		 };
static OZT_Context context;
static OZT_Context previous_context;



extern RWCString ozt_schedTime;    // for GETSCHED()
extern RWCString ozt_displayInfo;  // for TIMEEVSET()
extern OZT_EventHandler *ozt_evHandlerPtr;
extern int yylex();

//
//   The following variable is used to deal with @ELSE without @IF or @IFERROR,
//   it is set if the command executed was a @IF or @IFERROR.
//   @ELSE statement is successful if and only if it is set.
//
//   (What a hack! But there is no easy way to solve this problem)
//
static RWBoolean           elseAcceptable = FALSE;

//const long INFINITY = 262143;
//
//   Private Variables used in the parser
//
static OZT_Result          result;
extern CHA_OZTInfo         ozt_info;
#ifdef PGM_VERSION
static OZT_Value           ozt_LangVersion = (char *)PGM_VERSION;
#else
static OZT_Value           ozt_LangVersion = (char *)"No version";
#endif
static OZT_SourceMgr       *pSourceMgr;
static OZT_Interpreter     *interpreter;
static OZT_VarStore        *pVarStore;
static OZT_CmdRspBuf       *pCmdRspBuf;
static OZT_CmdSender       *pCmdSender;
static OZT_RspReceiver     *pRspReceiver;
static OZT_FileMgr         *pFileMgr;
static CHA_FileLogger      *pFileLogger;
static CHA_MailLogger      *pMailLogger;
static CHA_PrinterLogger   *pPrinterLogger;
static OZT_RspCatcher      *pRspCatcher;
static OZT_Clock           *pClock;
static OZT_Pipe            *pChdHandler;
static OZT_TimeOrderHandler *pTimeOrdHandler;
static OZT_CommentWinModel *pCommentWinModel;
static OZT_IOW             *pIOWin;
static OZT_InputPopup      *pInputPopup;
static OZT_InputPopup      *pInkeyPopup;
static OZT_FileSelectPopup *pFSelectPopup;
static OZT_FileViewerPopup *pFViewerPopup;
static OZT_PromptNotice    *pPromptNotice;
static OZT_ChildHandler    *pChildHandler;

void ozt_initParser(OZT_SourceMgr        *theSourceMgr,
                    OZT_Interpreter      *wrapper,
                    OZT_VarStore         *theVarStore,
                    OZT_CmdRspBuf        *theCmdRspBuf,
                    OZT_CmdSender        *theCmdSender,
                    OZT_FileMgr          *theFileMgr,
                    CHA_FileLogger       *theFileLogger,
                    CHA_MailLogger       *theMailLogger,
                    CHA_PrinterLogger    *thePrinterLogger,
                    OZT_RspCatcher       *theRspCatcher,
                    OZT_Clock            *theClock,
                    OZT_Pipe             *theChdHandler,
                    OZT_TimeOrderHandler *theTimeOrdHandler,
                    OZT_CommentWinModel  *theCommentWinModel,
                    OZT_IOW              *theIOWin,
                    OZT_InputPopup       *theInputPopup,
                    OZT_InputPopup       *theInkeyPopup,
                    OZT_FileSelectPopup  *theFSelectPopup,
                    OZT_FileViewerPopup  *theFViewerPopup,
                    OZT_PromptNotice     *thePromptNotice,
                    OZT_ChildHandler     *theChildHandler
		)
{
    //TRACE_IN(trace, ozt_initParser, "");

    pSourceMgr   = theSourceMgr;
    interpreter  = wrapper;
    pVarStore    = theVarStore;
    pCmdSender   = theCmdSender;
    pRspReceiver = &(pCmdSender->getRspReceiver());
    pCmdRspBuf   = theCmdRspBuf;
    pFileMgr     = theFileMgr;
    pFileLogger  = theFileLogger;
    pMailLogger  = theMailLogger;
    pPrinterLogger = thePrinterLogger;
    pRspCatcher  = theRspCatcher;
    pClock       = theClock;
    pChdHandler  = theChdHandler;
    pTimeOrdHandler = theTimeOrdHandler;
    pCommentWinModel = theCommentWinModel;
    pIOWin       = theIOWin;
    pInputPopup  = theInputPopup;
    pInkeyPopup  = theInkeyPopup;
    pFSelectPopup = theFSelectPopup;
    pFViewerPopup = theFViewerPopup;
    pPromptNotice = thePromptNotice;
    pChildHandler = theChildHandler;
/// TODO cmdSender i/f     pAPSender     = &(pCmdSender->getAPSender());
/// TODO    pSessionHandler = &(pCmdSender->getAsyncSessionHandler());

    // remove the rubbish characters in front of CXC
    size_t idx;
    if ((idx = ozt_LangVersion.index("CXC")) != RW_NPOS)
        ozt_LangVersion.remove(0, idx);

    //TRACE_OUT(trace, ozt_initParser, "");
}

// The following function sleepOrNotToSleep() is only used as a
// work-around to fix trouble report HA11628 until the proper fix is
// done in TAS.  The answer to trouble report HA13804 saiys that it
// will be fixed in TPF 4.1, but not in TPF 2.

static void sleepOrNotToSleep()
{
    //TRACE_IN(trace, sleepOrNotToSleep, "");

    static OZT_Time lastTime; // only used by TIMEEVSET
    OZT_Time currentTime;

    // Because of a limitation in TAS we cannnot setup two
    // orders within the same second, so check how long ago we
    // setup the last one.
    //
    // If within two seconds, sleep for a second.
    //
    // I guess there might be a time skew between a client
    // machine and the server machine (where the actual
    // registration is done) so just to be safe two seconds
    // seems to be the minimum interval to check for on the
    // client machine.

    if (currentTime.toSecSinceEpoch() - lastTime.toSecSinceEpoch() < 2)
    {
        //TRACE_FLOW(trace, sleepOrNotToSleep, "sleeping");

        // sleep(1) is no good to use because the actual time can be
        // up to one second less because of the granularity in system
        // timekeeping.  Because of this we use select() instead.

        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        (void)select(0, 0, 0, 0, &tv);
    }

    lastTime = currentTime; // remember the current time until next time

    //TRACE_OUT(trace, sleepOrNotToSleep, "");
}

static void removeGarbage();  // forward declaration

void ozt_terminateParser()
{
   // TRACE_IN(trace, ozt_terminateParser, "");

    removeGarbage();

    //TRACE_OUT(trace, ozt_terminateParser, "");
}

//*****************************************************************************
//
//  Functions and variables that deals with objects created dynamically in
//  the parser.  removeGarbage() is called at the beginning of yyparse() so
//  that all dynamic objects created last time can be cleared.
//

static RWTPtrOrderedVector<OZT_Value> valueGarbageBin;
static RWTValOrderedVector<RWTValOrderedVector<OZT_Value>*> valueListGarbageBin;

static void removeGarbage()
{
    valueGarbageBin.clearAndDestroy();
    while (valueListGarbageBin.entries() != 0)
        delete valueListGarbageBin.removeFirst();
}

static OZT_Value *newValue(const OZT_Value &v)
{
    OZT_Value *temp;

    temp = new OZT_Value(v);
    valueGarbageBin.insert(temp);   // register this object so that it will
    return temp;                    // be deleted later.
}

static RWTValOrderedVector<OZT_Value> *newValueList()
{
    RWTValOrderedVector<OZT_Value> *temp;

    temp = new RWTValOrderedVector<OZT_Value>;
    valueListGarbageBin.insert(temp);          // same here as newValue
    return temp;
}


extern "C" {

int yywrap(void)
{
    return 1;
}

    void yyerror(const char *s)
    {
        removeGarbage();
	if( pSourceMgr->getCurrSourceInfo() != NULL )
		pSourceMgr->getCurrSourceInfo()->reset();
        interpreter->set_result(OZT_Result::SYNTAX_ERR);
    }



}
%}

%start top
%type <vl> opt_exp_list
%type <vl> exp_list
%type <vl> formExpList
%type <vl> formButtonExpList
%type <vl> formExp
%type <vl> formButtonExp
%type <v> c_style_comment
%type <v> exp
%type <v> prefixed_exp
%type <v> simple_exp
%type <v> constant
%type <v> varaccess
%type <v> varname
%type <v> labelname
%type <v> char_constant
%type <v> funcall
%type <v> line
%type <vl> formcontrol
%type <v> charSequence
%type <b> cond_exp
%type <b> simple_cond_exp

%left  DUMMY
%left  '+' '-' '*' '/'
%token OZT_T_ERROR
%token OZT_T_C_STYLE_COMMENT
%token OZT_T_EOLN
%token OZT_T_LABELNAME
%token OZT_T_STRING
%token OZT_T_DEC_CHAR_CONST
%token OZT_T_HEX_CHAR_CONST
%token OZT_T_NUM_CONST

%token OZT_T_A
%token OZT_T_AND
%token OZT_T_AP
%token OZT_T_APSETSIDE
%token OZT_T_C
%token OZT_T_CHDIR
%token OZT_T_CHECK
%token OZT_T_CLOSE
%token OZT_T_CLRSCR
%token OZT_T_COMMENT
%token OZT_T_SETDEVID
%token OZT_T_SETERRORFLAG
%token OZT_T_UNSETDEVID
%token OZT_T_CONNECT
%token OZT_T_DEC
%token OZT_T_DELAY
%token OZT_T_DELAYSEC
%token OZT_T_DEVID
%token OZT_T_DIAGNOSTICS
%token OZT_T_DISCONNECT
%token OZT_T_DRAW
%token OZT_T_E
%token OZT_T_ELSE
%token OZT_T_ENDIF
%token OZT_T_BREAK
%token OZT_T_EOF
%token OZT_T_ERASE
%token OZT_T_EVDELETE
%token OZT_T_EXECUTE
%token OZT_T_FLUSHVAR
%token OZT_T_FOR
%token OZT_T_FORM
%token OZT_T_FUNBUSY
%token OZT_T_G
%token OZT_T_GE
%token OZT_T_GT
%token OZT_T_GETDATE
%token OZT_T_GETEXCHHDR
%token OZT_T_GETIOTYPE
%token OZT_T_GETPROTOCOLTYPE
%token OZT_T_GETPHASE
%token OZT_T_GETPROGRESS
%token OZT_T_GETTOTALCOUNT
%token OZT_T_LABELEXIST
%token OZT_T_GETMARK
%token OZT_T_GETERRORFLAG
%token OZT_T_GETSESSIONID
%token OZT_T_GETDIR
%token OZT_T_GOSUB
%token OZT_T_GOTO
%token OZT_T_ONDISCONNECT
%token OZT_T_ONTIMEOUT
%token OZT_T_H
%token OZT_T_I
%token OZT_T_IF
%token OZT_T_IFERROR
%token OZT_T_INC
%token OZT_T_INCLUDE
%token OZT_T_INKEY
%token OZT_T_INPUT
%token OZT_T_L
%token OZT_T_LE
%token OZT_T_LT
%token OZT_T_LABEL
%token OZT_T_LOG
%token OZT_T_LOGOF
%token OZT_T_LOGON
%token OZT_T_MARK
%token OZT_T_MENU
%token OZT_T_MAIL
%token OZT_T_FILE
%token OZT_T_MKDIR
%token OZT_T_NE
%token OZT_T_NEXT
%token OZT_T_OPENREAD
%token OZT_T_OR
%token OZT_T_ORDERED
%token OZT_T_P
%token OZT_T_PRINTER
%token OZT_T_PROMPT
%token OZT_T_QUIT
%token OZT_T_R
%token OZT_T_READ
%token OZT_T_RENAME
%token OZT_T_REPORT
%token OZT_T_RESET
%token OZT_T_RESTART
%token OZT_T_RETURN
%token OZT_T_RMDIR
%token OZT_T_S
%token OZT_T_SAVEDIR
%token OZT_T_SELFILE
%token OZT_T_SELPRINT
%token OZT_T_SEND
%token OZT_T_SENDAP
%token OZT_T_SET
%token OZT_T_SETPHASE
%token OZT_T_SETPROGRESS
%token OZT_T_SETREPLY
%token OZT_T_SETTOTALCOUNT
%token OZT_T_STEPPROGRESS
%token OZT_T_SPONTREP
%token OZT_T_SPONTREPOFF
%token OZT_T_STOP
%token OZT_T_SWITCH
%token OZT_T_IN
%token OZT_T_CASE
%token OZT_T_DEFAULT
%token OZT_T_ENDSWITCH
%token OZT_T_T
%token OZT_T_TO
%token OZT_T_THEN
%token OZT_T_VIEWFILE
%token OZT_T_W
%token OZT_T_WAITFOR
%token OZT_T_WAITREPLY
%token OZT_T_WINDEND
%token OZT_T_WINDOW
%token OZT_T_WRITE
%token OZT_T_Z

%token OZT_T_ADVANCE
%token OZT_T_REGRESS
%token OZT_T_CENTRALDIR
%token OZT_T_CONCAT
%token OZT_T_CREATECHILDSESSION
%token OZT_T_STARTCHILDSESSION
%token OZT_T_CHECKCHILDSESSION
%token OZT_T_TERMINATECHILDSESSION
%token OZT_T_READVARIABLE
%token OZT_T_STYLE
%token OZT_T_COPY
%token OZT_T_DECIMAL
%token OZT_T_DISKFREE
%token OZT_T_EVLOADED
%token OZT_T_GETDEST
%token OZT_T_GETFILELENGTH
%token OZT_T_GETLOG
%token OZT_T_GETMODE
%token OZT_T_GETPRINT
%token OZT_T_GETSCHED
%token OZT_T_GETDEVID
%token OZT_T_HEX
%token OZT_T_INHISTORY
%token OZT_T_LENGTH
%token OZT_T_LOWCASE
%token OZT_T_POS
%token OZT_T_PAD
%token OZT_T_PRIVATEDIR
%token OZT_T_REPLY
%token OZT_T_REPLYLEN
%token OZT_T_SCAN
%token OZT_T_TIMEEVSET
%token OZT_T_TRIM
%token OZT_T_UPCASE
%token OZT_T_VAR
%token OZT_T_VAREXIST
%token OZT_T_VERSION
%token OZT_T_FORMFIELD
%token OZT_T_LN
%token OZT_T_FORMCOMBO
%token OZT_T_FORMBUTTON
%token OZT_T_FORMCHECKBOX
%token OZT_T_FORMRADIOBUTTON

%%
/*********************************************/
/*           Rules for commands              */
/*********************************************/
top              : {context = OZT_NORM_CTXT;
                    ozt_sc  = SC_NORMAL;}
                   command
                   {elseAcceptable = FALSE;
                    removeGarbage();}
                 ;

command          : '@' general_script_command
                 | '@' group1_restricted_command
                 | '@' group2_restricted_command
                 | c_style_comment OZT_T_EOLN
                       {
                           pCmdRspBuf->append(*($1));
                           pCmdRspBuf->append("\n");
                           interpreter->set_flow_info(OZT_Flow::NORMAL);
                           interpreter->set_result(OZT_Result::NO_PROBLEM);
                       }
                 | OZT_T_EOF OZT_T_EOLN
                       {
                           interpreter->set_flow_info(OZT_Flow::FILE_HALTED);
                           interpreter->set_result(OZT_Result::NO_PROBLEM);
                       }
                 ;

c_style_comment : OZT_T_C_STYLE_COMMENT
                  {
                      $$ = newValue(ozt_TokenVal);
                  }
                ;

group1_restricted_command :
    OZT_T_LABEL labelname OZT_T_EOLN
        {
		if( interpreter->isAloneCommand() == FALSE ){
           		interpreter->set_flow_info(OZT_Flow::NORMAL);
            		interpreter->set_result(OZT_Result::NO_PROBLEM);
		}
		else {
			interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
			YYERROR;
		}
        }
|   OZT_T_FOR varname '=' exp OZT_T_TO exp OZT_T_EOLN
        {
		if( interpreter->isAloneCommand() == FALSE ){
           		interpreter->set_flow_info(OZT_Flow(OZT_Flow::FOR_SETUP,
            	                                   *($2), *($4), *($6)));
           		interpreter->set_result(OZT_Result::NO_PROBLEM);
		}
		else {
			interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
			YYERROR;
		}
        }
|   OZT_T_NEXT varname OZT_T_EOLN
        {
		if( interpreter->isAloneCommand() == FALSE ){
            		interpreter->set_flow_info(OZT_Flow(OZT_Flow::NEXT, *($2)));
            		interpreter->set_result(OZT_Result::NO_PROBLEM);
		}
		else {
			interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
			YYERROR;
		}
        }
| OZT_T_SWITCH '(' exp ')'  OZT_T_EOLN
	{
		if( interpreter->isAloneCommand() == FALSE ){
			interpreter->set_flow_info(OZT_Flow(OZT_Flow::SWITCH, *($3)));
			//interpreter->set_flow_info(OZT_Flow::NORMAL);
			interpreter->set_result(OZT_Result::NO_PROBLEM);
		}
		else {
			interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
			YYERROR;
		}
	}
| OZT_T_CASE constant OZT_T_EOLN
	{
		if( interpreter->isAloneCommand() == FALSE ){
			interpreter->set_flow_info(OZT_Flow(OZT_Flow::CASE, *($2)));
			//interpreter->set_flow_info(OZT_Flow::NORMAL);
			interpreter->set_result(OZT_Result::NO_PROBLEM);
		}
		else {
			interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
			YYERROR;
		}
	}
| OZT_T_DEFAULT OZT_T_EOLN
	{
		if( interpreter->isAloneCommand() == FALSE ){
			interpreter->set_flow_info(OZT_Flow(OZT_Flow::DEFAULT));
			//interpreter->set_flow_info(OZT_Flow::NORMAL);
			interpreter->set_result(OZT_Result::NO_PROBLEM);
		}
		else {
			interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
			YYERROR;
		}
	}
| OZT_T_ENDSWITCH OZT_T_EOLN
	{
		if( interpreter->isAloneCommand() == FALSE ){
			interpreter->set_flow_info(OZT_Flow(OZT_Flow::ENDSWITCH));
			//interpreter->set_flow_info(OZT_Flow::NORMAL);
			interpreter->set_result(OZT_Result::NO_PROBLEM);
		}
		else {
			interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
			YYERROR;
		}
	}
|   OZT_T_ELSE OZT_T_EOLN
	{
		if( interpreter->isAloneCommand() == FALSE ){
	    		interpreter->set_flow_info( OZT_Flow::ELSE );
	    		interpreter->set_result(OZT_Result::NO_PROBLEM);
		}
		else {
			interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
			YYERROR;
		}
	}
|   OZT_T_ELSE
        {
	   	if( interpreter->isAloneCommand() == FALSE ){
            		if (!elseAcceptable)
            		{
                		interpreter->set_flow_info(OZT_Flow::NORMAL);
                		interpreter->set_result(OZT_Result::ELSE_WITHOUT_IF);
                		YYACCEPT;    // skip the rest of the statement
            		}
		}
		else {
			interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
			YYERROR;
		}
        }
        general_script_command
|   OZT_T_ELSE
        {
		if( interpreter->isAloneCommand() == FALSE ){
            		if (!elseAcceptable)
            		{
                		interpreter->set_flow_info(OZT_Flow::NORMAL);
                		interpreter->set_result(OZT_Result::ELSE_WITHOUT_IF);
                		YYACCEPT;    // skip the rest of the statement
            		}
		}
		else {
			interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
			YYERROR;
		}
        }
        group2_restricted_command
|   OZT_T_ENDIF OZT_T_EOLN
	{
		if( interpreter->isAloneCommand() == FALSE ){
	    		interpreter->set_flow_info( OZT_Flow::ENDIF );
	    		interpreter->set_result(OZT_Result::NO_PROBLEM);
		}
		else {
			interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
			YYERROR;
		}
	}
;

group2_restricted_command :
    OZT_T_IF cond_exp OZT_T_THEN OZT_T_EOLN
	{
	    	if( interpreter->isAloneCommand() == FALSE ){
	    		if( $2 ) {
				interpreter->set_flow_info( OZT_Flow( OZT_Flow::IF,
					    	      OZT_Value( 1L ) ) );
				interpreter->set_result( OZT_Result::NO_PROBLEM );
	    		}
	    		else {
				interpreter->set_flow_info( OZT_Flow( OZT_Flow::IF,
					    	      OZT_Value( 0L ) ) );
				interpreter->set_result( OZT_Result::NO_PROBLEM );
	   		}
	   	}
		else{
			interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
			YYERROR;
		}
	}

|    OZT_T_IF cond_exp OZT_T_THEN
        {
		if( interpreter->isAloneCommand() == FALSE )
		{
            		if (!($2))
            		{
                		interpreter->set_flow_info(OZT_Flow::NORMAL);
                		interpreter->set_result(OZT_Result::NO_PROBLEM);
                		elseAcceptable = TRUE;
                		YYACCEPT;    // skip the execution of the command
            		}
		}
		else{
			interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
			YYERROR;
		}
        }
    general_script_command
        {
            interpreter->setSkipElseFlag();
        }
|   OZT_T_IFERROR OZT_T_THEN OZT_T_EOLN
	{
		if( interpreter->isAloneCommand() == FALSE ){
	    		if (ozt_errHandler.isFlagSet()) {
				interpreter->set_flow_info( OZT_Flow( OZT_Flow::IF,
						    	      OZT_Value( 1L ) ) );
				interpreter->set_result( OZT_Result::NO_PROBLEM );
	    		}
	    		else {
				interpreter->set_flow_info( OZT_Flow( OZT_Flow::IF,
					    	      OZT_Value( 0L ) ) );
				interpreter->set_result( OZT_Result::NO_PROBLEM );
	    		}

			ozt_errHandler.clearFlag();
		}
		else{
			interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
			YYERROR;
		}
	}
|   OZT_T_IFERROR  OZT_T_THEN
        {
		if( interpreter->isAloneCommand() == FALSE ){
            		if (!ozt_errHandler.isFlagSet())
            		{
                		interpreter->set_flow_info(OZT_Flow::NORMAL);
                		interpreter->set_result(OZT_Result::NO_PROBLEM);
                		elseAcceptable = TRUE;
                		YYACCEPT;
            		}
            		ozt_errHandler.clearFlag();
		}
		else {
			interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
			YYERROR;
		}
        }
    general_script_command
        {
            interpreter->setSkipElseFlag();
        }
;

general_script_command   :
  '/' charSequence OZT_T_EOLN
    {
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(pCmdSender->setScanStr(*($2)));
    }
| OZT_T_EOF OZT_T_EOLN
    {
        interpreter->set_flow_info(OZT_Flow::FILE_HALTED);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
    }
|OZT_T_A '+' OZT_T_EOLN
     {
         pCmdSender->setAutoConfirm(TRUE);
         interpreter->set_flow_info(OZT_Flow::NORMAL);
         interpreter->set_result(OZT_Result::NO_PROBLEM);
     }
| OZT_T_A '-' OZT_T_EOLN
     {
         pCmdSender->setAutoConfirm(FALSE);
         interpreter->set_flow_info(OZT_Flow::NORMAL);
         interpreter->set_result(OZT_Result::NO_PROBLEM);
     }
| OZT_T_AP '(' exp ')' OZT_T_EOLN
{
/// TODO i/f change    RWCString sNe = pCmdSender->getRosHandler().GetEsName();
//    OZT_Result result= pAPSender->Connect(sNe);
    if(result.code == OZT_Result::NO_PROBLEM)
    {
	pCmdRspBuf->markBeginOfRsp();
/// TODO	result = pAPSender->SendCommand(*($3));
	result = OZT_Result::NO_PROBLEM;
    }
    interpreter->set_flow_info(OZT_Flow::NORMAL);
    interpreter->set_result(result.filtered());
}

| OZT_T_AP '(' exp ',' exp ')' OZT_T_EOLN
{
/// TODO i/f change    RWCString sNe = pCmdSender->getRosHandler().GetEsName();
//    OZT_Result result = pAPSender->Connect(sNe);
    if(result.code == OZT_Result::NO_PROBLEM)
    {
	pCmdRspBuf->markBeginOfRsp();
/// TODO	result = pAPSender->SendCommand(*($3), TRUE, *($5));
	result = OZT_Result::NO_PROBLEM;
    }
    interpreter->set_flow_info(OZT_Flow::NORMAL);
    interpreter->set_result(result.filtered());
}

| OZT_T_APSETSIDE '(' exp ')' OZT_T_EOLN
{
/// TODO i/f change    RWCString sNe = pCmdSender->getRosHandler().GetEsName();
//    OZT_Result result = pAPSender->ConnectAndCheckSide(sNe, *($3));
    interpreter->set_flow_info(OZT_Flow::NORMAL);
    interpreter->set_result(result.filtered());
}
| OZT_T_C OZT_T_EOLN
    {
        pFileLogger->closeLog();
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
    }
| OZT_T_CHDIR '(' exp ')' OZT_T_EOLN
    {
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(pFileMgr->chDir(*($3)));

    }
| OZT_T_CHECK '(' exp ')' OZT_T_EOLN
    {
        *($3) = trim(*($3));
        ($3)->toUpper();
        if (*($3) == "ON")
        {
            ozt_errHandler.checkOn();
            interpreter->set_flow_info(OZT_Flow::NORMAL);
            interpreter->set_result(OZT_Result::NO_PROBLEM);
        }
        else if (*($3) == "OFF")
        {
            ozt_errHandler.checkOff();
            ozt_errHandler.clearFlag();
            interpreter->set_flow_info(OZT_Flow::NORMAL);
            interpreter->set_result(OZT_Result::NO_PROBLEM);
        }
        else
        {
            interpreter->set_flow_info(OZT_Flow::NORMAL);
            interpreter->set_result(OZT_Result::INVALID_VALUE);
        }
    }
| OZT_T_CLOSE OZT_T_EOLN
    {
        pFileLogger->closeLog();
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
    }
| OZT_T_CLOSE '(' exp ')'  OZT_T_EOLN
    {
        pFileLogger->closeLog(*($3));
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
    }
| OZT_T_CLRSCR OZT_T_EOLN
    {
        pCommentWinModel->clear();
        if (pIOWin != 0)
            pIOWin->clrscr();
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
    }
| OZT_T_COMMENT OZT_T_EOLN
    {
        if (pCommentWinModel->isActive())
            pCommentWinModel->addText("\n", FALSE);
        else
            pCmdRspBuf->append("\n");
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
    }
| OZT_T_SETDEVID '(' exp ')' OZT_T_EOLN
{
	//Check the device id format
	OZT_Value val( *($3) );

	//if( val.isHex() )
	//val = val.toDec( result );

	int id = (int)val.toLong( result );

	if( result.code != OZT_Result::NO_PROBLEM || id < 0 || id > 2147483632 ) {
		 // 2147483632 = 0x7FFFFFF0 max value for dev id
		interpreter->set_result(OZT_Result::INVALID_VALUE);
		YYERROR;
	}

	//Set the new device id
	pCmdSender->getCHACmdSender().getDevModePropsObject()->setModeOn( id ); //MAGA not supported (yet?)
}
| OZT_T_SETDEVID '(' ')' OZT_T_EOLN
{
	//Check the device id format

	//Set the new device id
	pCmdSender->getCHACmdSender().getDevModePropsObject()->setModeOn(); //MAGA not supported (yet?)
}
| OZT_T_SETDEVID OZT_T_EOLN
{

	//Set the new deviceE id
	pCmdSender->getCHACmdSender().getDevModePropsObject()->setModeOn(); //MAGA not supported (yet?)
}
| OZT_T_SETERRORFLAG OZT_T_EOLN
{
	ozt_errHandler.setFlag();
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
}

| OZT_T_SETERRORFLAG '(' ')' OZT_T_EOLN
{
	ozt_errHandler.setFlag();
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
}
| OZT_T_SETERRORFLAG '(' exp  ')' OZT_T_EOLN
{
	*($3) = trim(*($3));
        ($3)->toUpper();
        if (*($3) == "ON")
        {
            ozt_errHandler.setFlag();
            interpreter->set_flow_info(OZT_Flow::NORMAL);
            interpreter->set_result(OZT_Result::NO_PROBLEM);
        }
        else if (*($3) == "OFF")
        {
            ozt_errHandler.clearFlag();
            interpreter->set_flow_info(OZT_Flow::NORMAL);
            interpreter->set_result(OZT_Result::NO_PROBLEM);
        }
        else
        {
            interpreter->set_flow_info(OZT_Flow::NORMAL);
            interpreter->set_result(OZT_Result::INVALID_VALUE);
        }
}
| OZT_T_UNSETDEVID  OZT_T_EOLN
{
	pCmdSender->getCHACmdSender().getDevModePropsObject()->setModeOff();
}
| OZT_T_UNSETDEVID '(' ')' OZT_T_EOLN
{
	pCmdSender->getCHACmdSender().getDevModePropsObject()->setModeOff();
}
| OZT_T_COMMENT '(' opt_exp_list ')' OZT_T_EOLN
    {
        // loop through the list to print each expression.
        if (pCommentWinModel->isActive())
        {
            while (($3)->entries() != 0)
            {
		RWBoolean toFormat;

		OZT_Value v = ($3)->first();

		if( v.unvisibleChars > 0 )
			toFormat = TRUE;
		else
			toFormat = FALSE;

                pCommentWinModel->addText(v, toFormat);
                // pCmdRspBuf->append(($3)->first()); // *** TR AB91263 test
                ($3)->removeFirst();
            }
            pCommentWinModel->addText("\n", FALSE);
            // pCmdRspBuf->append("\n"); // *** TR AB91263 test
        }
        else
        {
            while (($3)->entries() != 0)
            {
		RWBoolean toFormat;

		OZT_Value v = ($3)->first();

		if( v.unvisibleChars > 0 )
			toFormat = TRUE;
		else
			toFormat = FALSE;

                pCmdRspBuf->append(v, toFormat);
                ($3)->removeFirst();
            }
            pCmdRspBuf->append("\n");
        }
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
    }
|   OZT_T_BREAK OZT_T_EOLN
	{
		if( interpreter->isAloneCommand() == FALSE )
		{
			interpreter->set_flow_info( OZT_Flow(OZT_Flow::BREAK ) );
			interpreter->set_result(OZT_Result::NO_PROBLEM);
		}
		else
		{
			interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
			YYERROR;
		}
	}
| OZT_T_CONNECT '(' exp ')' OZT_T_EOLN
    {
        interpreter->set_result(pCmdSender->connect(*($3)));
        interpreter->set_flow_info(OZT_Flow::NORMAL);
    }
| OZT_T_CONNECT '(' exp ',' exp ')' OZT_T_EOLN
    {
/// TODO
/*	if( *($5) == "SB" ) {
        	interpreter->set_result(pCmdSender->connect(*($3), TRUE));
		interpreter->set_flow_info(OZT_Flow::NORMAL);
	}
	else if( *($5) == "EX" ) {
		interpreter->set_result(pCmdSender->connect(*($3)));
		interpreter->set_flow_info(OZT_Flow::NORMAL);
	}
	else {
		interpreter->set_result(OZT_Result::SYNTAX_ERR);
		YYERROR;
	}
*/
    }
| OZT_T_CONNECT '(' exp ',' OZT_T_DEVID '=' exp ')' OZT_T_EOLN
    {
/// TODO
/*        interpreter->set_result(pCmdSender->connect(*($3), FALSE, *($7)));
        interpreter->set_flow_info(OZT_Flow::NORMAL);
*/
    }
| OZT_T_CONNECT '(' exp ',' exp ',' OZT_T_DEVID '=' exp ')' OZT_T_EOLN
    {
/// TODO
/*	if( *($5) == "SB" ) {
        	interpreter->set_result(pCmdSender->connect(*($3), TRUE, *($9)));
		interpreter->set_flow_info(OZT_Flow::NORMAL);
	}
	else if( *($5) == "EX" ) {
		interpreter->set_result(pCmdSender->connect(*($3), FALSE, *($9)));
		interpreter->set_flow_info(OZT_Flow::NORMAL);
	}
	else {
		interpreter->set_result(OZT_Result::SYNTAX_ERR);
		YYERROR;
	}
*/
    }
| OZT_T_DEC '(' varname ')' OZT_T_EOLN
    {
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(pVarStore->dec(*($3)));
    }
| OZT_T_DELAY '(' exp ')' OZT_T_EOLN
    {
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(pClock->delay(*($3)));
    }
| OZT_T_DELAYSEC '(' exp ')' OZT_T_EOLN
    {
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(pClock->delaySec(*($3)));
    }
| OZT_T_DIAGNOSTICS OZT_T_EOLN
    {
	if( interpreter->isAloneCommand() == FALSE ){
        	while(1);
        	interpreter->set_flow_info(OZT_Flow::NORMAL);
        	interpreter->set_result(OZT_Result(OZT_Result::NO_PROBLEM));
    	}
	else {
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
    }
| OZT_T_DISCONNECT OZT_T_EOLN
    {
        interpreter->set_result(pCmdSender->disconnect());
        interpreter->set_flow_info(OZT_Flow::NORMAL);
    }
| OZT_T_DRAW '(' {previous_context = context; context = OZT_DRAW_CTXT;} exp_list {context = previous_context;}
             ')' OZT_T_EOLN
    {
	if( interpreter->isAloneCommand() == FALSE ){

        	if (pIOWin == 0)
        	{
            		interpreter->set_flow_info(OZT_Flow::NORMAL);
	    		interpreter->set_result(OZT_Result::NO_UI_SUPPORTED);
        	}
        	else
        	{
            		interpreter->set_result(pIOWin->draw(*($4)));
            		interpreter->set_flow_info(OZT_Flow::NORMAL);
        	}
	}
	else {
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
    }
| OZT_T_E OZT_T_EOLN
    {
        pCmdRspBuf->markSearchBackPoint();
        pCmdSender->logOff(false); // OPS Implementation of logOff
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
    }
| OZT_T_ERASE '(' exp ')' OZT_T_EOLN
    {
    	// HD88797: Close the log before the erase.
  	// HE12695: Only close the log if the log should be erased.
  	if( *($3) == pFileLogger->getLog() ){
    		pFileLogger->closeLog();
    	}
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(pFileMgr->rmFile(*($3)));
    }
| OZT_T_EVDELETE OZT_T_EOLN
    {
        RWBoolean toFormat;
        OZT_Value v = "@EVDELETE, Command not supported in ENM";
        pCmdRspBuf->append(v, toFormat);
        pCmdRspBuf->append("\n");
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
    }
| OZT_T_EVDELETE '(' ')' OZT_T_EOLN
    {
        RWBoolean toFormat;
        OZT_Value v = "@EVDELETE, Command not supported in ENM";
        pCmdRspBuf->append(v, toFormat);
        pCmdRspBuf->append("\n");
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
    }
| OZT_T_EVDELETE '(' exp ')' OZT_T_EOLN
    {
        RWBoolean toFormat;
        OZT_Value v = "@EVDELETE, Command not supported in ENM";
        pCmdRspBuf->append(v, toFormat);
	pCmdRspBuf->append("\n");
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
    }
| OZT_T_EXECUTE '(' exp ')' OZT_T_EOLN
    {
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        result = pChdHandler->execute(*($3));
        interpreter->set_result(result.filtered());
    }
| OZT_T_FLUSHVAR '(' varname ')' OZT_T_EOLN
    {
        (void)(pVarStore->flushVar(*($3)));
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
    }
| OZT_T_FORM '(' formExpList ')' OZT_T_EOLN
    {
	if( interpreter->isAloneCommand() == FALSE ){

        	if (pIOWin == 0)
        	{
            		interpreter->set_flow_info(OZT_Flow::NORMAL);
            		interpreter->set_result(OZT_Result::NO_UI_SUPPORTED);
        	}
        	else
        	{
           	 	RWTValOrderedVector<RWCString> answers;

           		interpreter->set_flow_info(OZT_Flow::NORMAL);
            		result = pIOWin->form(*($3), answers);
            		if (result.code == OZT_Result::NO_PROBLEM) {
				RWBoolean toJump = FALSE;
				RWCString label;
                		while (answers.entries() != 0)
                		{
					RWCString type = answers.removeFirst();
					if( type == "VAR" ||
			    		    type == "CHECKBOX" ||
			    		    type == "RADIO" ||
			    		    type == "COMBO" ) {
                    				// check the form input into the corresponding variables
                    				// Cannot do it in method call since HP aCC the
						//    reverses argument order
                    				RWCString name = answers.removeFirst();
                    				RWCString value = answers.removeFirst();
                    				pVarStore->put(name, value);
					}
					else if( type == "BUTTON" ) {
			     			toJump = TRUE;
						label = answers.removeFirst();
					}
                		}

				if( toJump == TRUE ) {
					interpreter->set_flow_info(OZT_Flow(OZT_Flow::GOTO_LABEL, label));
				}
				interpreter->set_result(result);
	    		}
			else if( result.code ==OZT_Result::DIALOG_TIMEOUT ) {
				RWCString label = pIOWin->getTimeoutLabel();

				interpreter->set_flow_info( OZT_Flow( OZT_Flow::GOTO_LABEL,
								    	      label ) );
				interpreter->set_result(OZT_Result::NO_PROBLEM);
			}
			else {
				interpreter->set_result(result);
				interpreter->set_flow_info(OZT_Flow::NORMAL);
			}

		}
	}
	else {
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
    }
| OZT_T_FUNBUSY '(' exp ')' OZT_T_EOLN
    {
	if( interpreter->isAloneCommand() == FALSE ){
        	interpreter->set_flow_info(OZT_Flow::NORMAL);
        	interpreter->set_result(
            		pCmdSender->setFunBusyParam(*($3), OZT_Value(OZT_CmdSender::defaultFBInterval)));
	}
	else {
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
    }
| OZT_T_FUNBUSY '(' exp ',' exp ')' OZT_T_EOLN
    {
	if( interpreter->isAloneCommand() == FALSE ){
        	interpreter->set_flow_info(OZT_Flow::NORMAL);
        	interpreter->set_result(pCmdSender->setFunBusyParam(*($3), *($5)));
    	}
	else {
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
    }
| OZT_T_G '+' OZT_T_EOLN
    {
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
    }
| OZT_T_G '-' OZT_T_EOLN
    {
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
    }
| OZT_T_GOSUB labelname OZT_T_EOLN
    {
	if( interpreter->isAloneCommand() == FALSE ){
       		interpreter->set_flow_info(OZT_Flow(OZT_Flow::GOSUB_LABEL, *($2)));
       		interpreter->set_result(OZT_Result::NO_PROBLEM);
	}
	else {
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
    }
| OZT_T_GOTO labelname OZT_T_EOLN
    {
	if( interpreter->isAloneCommand() == FALSE ){
        	interpreter->set_flow_info(OZT_Flow(OZT_Flow::GOTO_LABEL, *($2)));
        	interpreter->set_result(OZT_Result::NO_PROBLEM);
	}
	else {
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
    }
| OZT_T_ONDISCONNECT '(' exp ')' OZT_T_EOLN
    {
	OZT_SourceInfo* source = pSourceMgr->getCurrSourceInfo();

	if( source == NULL ) {
		interpreter->set_result( OZT_Result::FILE_NOT_LOADED );
		YYERROR;
	}

	result = pSourceMgr->getCurrSourceInfo()->labelExist(*($3));

	if (result.code != OZT_Result::NO_PROBLEM) {
              interpreter->set_result(result);
              YYERROR;
        }

	pCmdSender->setOnDisconnectLabel(  *($3) );

        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
    }
| OZT_T_ONTIMEOUT '(' exp ',' exp ',' exp  ')' OZT_T_EOLN
    {
	if( pIOWin == 0 )
	{
		interpreter->set_flow_info( OZT_Flow::NORMAL );
		interpreter->set_result( OZT_Result::NO_UI_SUPPORTED );
	}
	else
	{
		OZT_SourceInfo* source = pSourceMgr->getCurrSourceInfo();

		if( source == NULL ) {
			interpreter->set_result( OZT_Result::FILE_NOT_LOADED );
			YYERROR;
		}

		result = pSourceMgr->getCurrSourceInfo()->labelExist( *($3) );
		if( result.code != OZT_Result::NO_PROBLEM ){
			interpreter->set_result( result );
			YYERROR;
		}

		pIOWin->setTimeout(  *($3), *($5), *($7) );
		pInputPopup->setTimeout(  *($3), *($5), *($7) );
		pInkeyPopup->setTimeout(  *($3), *($5), *($7) );
		pPromptNotice->setTimeout(  *($3), *($5), *($7) );

		interpreter->set_flow_info( OZT_Flow::NORMAL );
		interpreter->set_result( OZT_Result::NO_PROBLEM );
	}
    }
| OZT_T_H charSequence OZT_T_EOLN
    {
        RWBoolean toFormat;
        OZT_Value v = "@H, Command not supported in ENM";
        pCmdRspBuf->append(v, toFormat);
        pCmdRspBuf->append("\n");
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
    }
| OZT_T_I charSequence OZT_T_EOLN
    {
         interpreter->set_flow_info(OZT_Flow(OZT_Flow::INCLUDE, *($2)));
         interpreter->set_result(OZT_Result::NO_PROBLEM);
    }
| OZT_T_INC '(' varname ')' OZT_T_EOLN
     {
         interpreter->set_flow_info(OZT_Flow::NORMAL);
         interpreter->set_result(pVarStore->inc(*($3)));
     }
| OZT_T_INCLUDE '(' exp ')' OZT_T_EOLN
     {
	if( interpreter->isAloneCommand() == FALSE ){
         	interpreter->set_flow_info(OZT_Flow(OZT_Flow::INCLUDE, *($3)));
         	interpreter->set_result(OZT_Result::NO_PROBLEM);
	}
	else{
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
     }
| OZT_T_INKEY OZT_T_EOLN
     {
	if( interpreter->isAloneCommand() == FALSE ){
         	if (pInkeyPopup == 0)
         	{
             		interpreter->set_flow_info(OZT_Flow::NORMAL);
             		interpreter->set_result(OZT_Result::NO_UI_SUPPORTED);
         	}
         	else
         	{
             		RWCString temp;

			result = pInkeyPopup->getInput( RWCString( OZT_IOW::NOVARIABLE ),"",FALSE,temp);

			if( result.code == OZT_Result::DIALOG_TIMEOUT) {
				RWCString label = pInkeyPopup->getTimeoutLabel();

				interpreter->set_flow_info( OZT_Flow( OZT_Flow::GOTO_LABEL,
								    	      label ) );
				interpreter->set_result(OZT_Result::NO_PROBLEM);

			}
			else {
             			interpreter->set_flow_info(OZT_Flow::NORMAL);
             			interpreter->set_result( result );
			}
         	}
	}
	else{
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
     }
| OZT_T_INKEY '(' ')' OZT_T_EOLN
     {
	if( interpreter->isAloneCommand() == FALSE ){

	        if (pInkeyPopup == 0)
        	{
             		interpreter->set_flow_info(OZT_Flow::NORMAL);
             		interpreter->set_result(OZT_Result::NO_UI_SUPPORTED);
          	}
         	else
         	{
             		RWCString temp;

			result = pInkeyPopup->getInput( RWCString( OZT_IOW::NOVARIABLE ),"",FALSE,temp);

			if( result.code == OZT_Result::DIALOG_TIMEOUT) {
				RWCString label = pInkeyPopup->getTimeoutLabel();

				interpreter->set_flow_info( OZT_Flow( OZT_Flow::GOTO_LABEL,
								    	      label ) );
				interpreter->set_result(OZT_Result::NO_PROBLEM);

			}
			else {
             			interpreter->set_flow_info(OZT_Flow::NORMAL);
             			interpreter->set_result( result );
			}
         	}
	}
	else{
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
     }
| OZT_T_INKEY '(' varname ')' OZT_T_EOLN
     {
	if( interpreter->isAloneCommand() == FALSE ){
         	if (pInkeyPopup == 0)
         	{
             		interpreter->set_flow_info(OZT_Flow::NORMAL);
             		interpreter->set_result(OZT_Result::NO_UI_SUPPORTED);
         	}
         	else
         	{
	             	RWCString temp;

			result = pInkeyPopup->getInput("","",FALSE,temp);

			if( result.code == OZT_Result::DIALOG_TIMEOUT) {
				RWCString label = pInkeyPopup->getTimeoutLabel();

				interpreter->set_flow_info( OZT_Flow( OZT_Flow::GOTO_LABEL,
								    	      label ) );
				interpreter->set_result(OZT_Result::NO_PROBLEM);

			}
			else if (result.code == OZT_Result::NO_PROBLEM) {
                 		pVarStore->put(*($3), temp);
				interpreter->set_flow_info(OZT_Flow::NORMAL);
             			interpreter->set_result(result);
			}
			else {
             			interpreter->set_flow_info(OZT_Flow::NORMAL);
             			interpreter->set_result( result );
			}
         	}
	}
	else{
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
     }
| OZT_T_INKEY '(' varname ',' exp_list ')' OZT_T_EOLN
     {
	if( interpreter->isAloneCommand() == FALSE ){
         	if (pInkeyPopup == 0)
         	{
             		interpreter->set_flow_info(OZT_Flow::NORMAL);
             		interpreter->set_result(OZT_Result::NO_UI_SUPPORTED);
         	}
         	else
         	{
             		RWCString tempInput;
			RWBoolean toFormat = FALSE;
             		RWCString tempPrompt = RWCString();

             		while (($5)->entries() != 0)
             		{
				OZT_Value v = ($5)->first();

				//Check if the text is "styled"
				if( (toFormat == FALSE) && v.unvisibleChars > 0 )
					toFormat = TRUE;

                 		tempPrompt = (RWCString)tempPrompt + (RWCString)v;

                 		($5)->removeFirst();
             		}

            		 result = pInkeyPopup->getInput(tempPrompt,"", toFormat, tempInput);
             		if (result.code == OZT_Result::NO_PROBLEM) {
                 		pVarStore->put(*($3), tempInput);
             			interpreter->set_flow_info(OZT_Flow::NORMAL);
             			interpreter->set_result(result);
			}
			else if( result.code == OZT_Result::DIALOG_TIMEOUT) {
				RWCString label = pInkeyPopup->getTimeoutLabel();

				interpreter->set_flow_info( OZT_Flow( OZT_Flow::GOTO_LABEL,
								      label ) );
				interpreter->set_result(OZT_Result::NO_PROBLEM);
			}
			else {
				interpreter->set_flow_info(OZT_Flow::NORMAL);
             			interpreter->set_result(result);
			}
         	}
	}
	else{
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
     }
| OZT_T_INPUT '(' varname ')' OZT_T_EOLN
     {
	if( interpreter->isAloneCommand() == FALSE ){
         	if (pInputPopup == 0)
         	{
             		interpreter->set_flow_info(OZT_Flow::NORMAL);
             		interpreter->set_result(OZT_Result::NO_UI_SUPPORTED);
         	}
         	else
         	{
             		RWCString tempInput;
             		OZT_Value defaultVal;

             		// get the default value if any
             		if (pVarStore->contains(*($3)))
                 		pVarStore->get(*($3), defaultVal);
             		else
                 		defaultVal = RWCString();

             		result = pInputPopup->getInput("", defaultVal, FALSE,tempInput);
             		if (result.code == OZT_Result::NO_PROBLEM){
                 		pVarStore->put(*($3), tempInput);
				interpreter->set_result(result);
				interpreter->set_flow_info(OZT_Flow::NORMAL);
			}
			else if( result.code ==OZT_Result::DIALOG_TIMEOUT ) {
				RWCString label = pInputPopup->getTimeoutLabel();

				interpreter->set_flow_info( OZT_Flow( OZT_Flow::GOTO_LABEL,
								    	      label ) );
				interpreter->set_result(OZT_Result::NO_PROBLEM);
			}
			else {
				interpreter->set_result(result);
				interpreter->set_flow_info(OZT_Flow::NORMAL);
			}
         	}
	}
	else{
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
     }
| OZT_T_INPUT '(' varname ',' exp_list ')' OZT_T_EOLN
     {
	if( interpreter->isAloneCommand() == FALSE ){
         	if (pInputPopup == 0)
         	{
             		interpreter->set_flow_info(OZT_Flow::NORMAL);
             		interpreter->set_result(OZT_Result::NO_UI_SUPPORTED);
         	}
         	else
         	{
             		RWCString tempInput;
             		OZT_Value defaultVal;

             		// get the default value if any
             		if (pVarStore->contains(*($3)))
                 		pVarStore->get(*($3), defaultVal);
             		else
                 		defaultVal = RWCString();

             		RWCString tempPrompt = RWCString();
			RWBoolean toFormat = FALSE;

             		while (($5)->entries() != 0)
             		{
				OZT_Value v = ($5)->first();

				//Check if the text is "styled"
				if( ( toFormat == FALSE ) && ( v.unvisibleChars > 0 ) )
					toFormat = TRUE;

                 		tempPrompt = (RWCString)tempPrompt + (RWCString)v;

                 		($5)->removeFirst();
             		}
             		result = pInputPopup->getInput(tempPrompt, defaultVal, toFormat, tempInput );
	             	if (result.code == OZT_Result::NO_PROBLEM) {
        	        	pVarStore->put(*($3), tempInput);
				interpreter->set_result(result);
				interpreter->set_flow_info(OZT_Flow::NORMAL);
			}
             		else if( result.code ==OZT_Result::DIALOG_TIMEOUT ) {
				RWCString label = pInputPopup->getTimeoutLabel();

				interpreter->set_flow_info( OZT_Flow( OZT_Flow::GOTO_LABEL,
								    	      label ) );
				interpreter->set_result(OZT_Result::NO_PROBLEM);

			}
			else {
				interpreter->set_result(result);
				interpreter->set_flow_info(OZT_Flow::NORMAL);
			}
         	}
	}
	else{
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
     }
| OZT_T_L charSequence OZT_T_EOLN
     {
         interpreter->set_flow_info(OZT_Flow::NORMAL);
         result = OZT_Result(pFileLogger->logOverwrite(
                                             ozt_normalisePath(*($2))));
         interpreter->set_result(result.filtered());
     }
| OZT_T_LOG '(' exp ')' OZT_T_EOLN
     {
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        result = OZT_Result(pFileLogger->logAppend(ozt_normalisePath(*($3))));

	interpreter->set_result(result.filtered());
     }
| OZT_T_LOG '(' exp ',' exp ')' OZT_T_EOLN
     {
        interpreter->set_flow_info(OZT_Flow::NORMAL);
	result = OZT_Result(pFileLogger->logAppend(ozt_normalisePath(*($3)),*($5)));

        interpreter->set_result(result.filtered());
     }
| OZT_T_LOGOF OZT_T_EOLN
     {
         pCmdRspBuf->markSearchBackPoint();
         pCmdSender->logOff(false); // OPS Implementation of logOff
         interpreter->set_flow_info(OZT_Flow::NORMAL);
         interpreter->set_result(OZT_Result::NO_PROBLEM);
     }
| OZT_T_LOGON OZT_T_EOLN
     {
         pRspReceiver->logOn();
         interpreter->set_flow_info(OZT_Flow::NORMAL);
         interpreter->set_result(OZT_Result::NO_PROBLEM);
     }
| OZT_T_MARK OZT_T_EOLN
     {
         pCmdRspBuf->markLine();
         interpreter->set_flow_info(OZT_Flow::NORMAL);
         interpreter->set_result(OZT_Result::NO_PROBLEM);
     }
| OZT_T_MARK '(' ')' OZT_T_EOLN
     {
         pCmdRspBuf->markLine();
         interpreter->set_flow_info(OZT_Flow::NORMAL);
         interpreter->set_result(OZT_Result::NO_PROBLEM);
     }
| OZT_T_MARK '(' exp ')' OZT_T_EOLN
     {
         long v;

         v = ($3)->toLong(result);
         if (result.code != OZT_Result::NO_PROBLEM)
         {
             interpreter->set_flow_info(OZT_Flow::NORMAL);
             interpreter->set_result(result);
         }
         else
         {
             pCmdRspBuf->markLine(v);
             interpreter->set_flow_info(OZT_Flow::NORMAL);
             interpreter->set_result(OZT_Result::NO_PROBLEM);
         }
     }
| OZT_T_MAIL '(' exp ',' exp ',' exp ')' OZT_T_EOLN
{
	RWCString address = *($3);
	RWCString subject = *($5);
	RWCString message = *($7);

	OZT_Mail myMail;

	result = myMail.sendMail( subject, message, address );

        interpreter->set_flow_info(OZT_Flow::NORMAL);
	interpreter->set_result( result.filtered() );
}

| OZT_T_MAIL '(' exp ',' exp ',' OZT_T_FILE '(' exp ')' ')' OZT_T_EOLN
{
	RWCString address = *($3);

	RWCString subject = *($5);
	RWCString file = *($9);

	OZT_Mail myMail;

	result = myMail.sendFile( subject, file, address );

        interpreter->set_flow_info(OZT_Flow::NORMAL);
	interpreter->set_result( result.filtered() );
}

| OZT_T_MENU '(' varname ',' exp ',' exp ')' OZT_T_EOLN
     {
	if( interpreter->isAloneCommand() == FALSE ){
        	if (pIOWin == 0)
         	{
             		interpreter->set_flow_info(OZT_Flow::NORMAL);
             		interpreter->set_result(OZT_Result::NO_UI_SUPPORTED);
         	}
         	else
         	{
             		OZT_Value ans;

             		result = pIOWin->menu(ans, *($5), *($7));

			if (result.code == OZT_Result::NO_PROBLEM){
                 		pVarStore->put(*($3), ans);
				interpreter->set_flow_info(OZT_Flow::NORMAL);
				interpreter->set_result(result);
			}
			else if( result.code == OZT_Result::DIALOG_TIMEOUT ) {
				RWCString label = pIOWin->getTimeoutLabel();

				interpreter->set_flow_info( OZT_Flow( OZT_Flow::GOTO_LABEL,
								    	      label ) );
				interpreter->set_result(OZT_Result::NO_PROBLEM);

			}
			else {
				interpreter->set_flow_info(OZT_Flow::NORMAL);
				interpreter->set_result(result);
			}
         	}
	}
	else{
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
     }
| OZT_T_MENU '(' varname ',' exp ',' exp ',' exp_list ')' OZT_T_EOLN
     {
	if( interpreter->isAloneCommand() == FALSE ){
         	if (pIOWin == 0)
         	{
             		interpreter->set_flow_info(OZT_Flow::NORMAL);
             		interpreter->set_result(OZT_Result::NO_UI_SUPPORTED);
         	}
         	else
         	{
             		OZT_Value ans;

             		result = pIOWin->menu(ans, *($5), *($7));

             		if (result.code == OZT_Result::NO_PROBLEM){
                 		pVarStore->put(*($3), ans);
				interpreter->set_flow_info(OZT_Flow::NORMAL);
				interpreter->set_result(result);
			}
			else if( result.code == OZT_Result::DIALOG_TIMEOUT ) {
				RWCString label = pIOWin->getTimeoutLabel();

				interpreter->set_flow_info( OZT_Flow( OZT_Flow::GOTO_LABEL,
								    	      label ) );
				interpreter->set_result(OZT_Result::NO_PROBLEM);

			}
			else {
				interpreter->set_flow_info(OZT_Flow::NORMAL);
				interpreter->set_result(result);
			}
         	}
	}
	else{
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
     }
| OZT_T_MKDIR '(' exp ')' OZT_T_EOLN
     {
         interpreter->set_flow_info(OZT_Flow::NORMAL);
         interpreter->set_result(pFileMgr->mkDir(*($3)));
     }
| OZT_T_OPENREAD '(' exp ')' OZT_T_EOLN
     {
         interpreter->set_flow_info(OZT_Flow::NORMAL);
         interpreter->set_result(pFileMgr->openReadFile(*($3)));
     }
| OZT_T_ORDERED '(' exp ')' OZT_T_EOLN
     {
         *($3) = trim(*($3));
         ($3)->toUpper();
         if (*($3) == "ON")
         {
             pCmdSender->orderOn();
             interpreter->set_flow_info(OZT_Flow::NORMAL);
             interpreter->set_result(OZT_Result::NO_PROBLEM);
         }
         else if (*($3) == "OFF")
         {
             pCmdSender->orderOff();
             interpreter->set_flow_info(OZT_Flow::NORMAL);
             interpreter->set_result(OZT_Result::NO_PROBLEM);
         }
         else
         {
             interpreter->set_flow_info(OZT_Flow::NORMAL);
             interpreter->set_result(OZT_Result::INVALID_VALUE);
         }
     }
| OZT_T_P '+' OZT_T_EOLN
{
       RWBoolean toFormat;
       OZT_Value v = "@P, Command not supported in ENM";
       pCmdRspBuf->append(v, toFormat);
       pCmdRspBuf->append("\n");
       interpreter->set_flow_info(OZT_Flow::NORMAL);
       interpreter->set_result(OZT_Result::NO_PROBLEM);
     }
| OZT_T_P '-' OZT_T_EOLN
{
       RWBoolean toFormat;
       OZT_Value v = "@P, Command not supported in ENM";
       pCmdRspBuf->append(v, toFormat);
       pCmdRspBuf->append("\n");
       interpreter->set_flow_info(OZT_Flow::NORMAL);
       interpreter->set_result(OZT_Result::NO_PROBLEM);
     }
| OZT_T_PRINTER '(' exp ')' OZT_T_EOLN
     {
       RWBoolean toFormat;
       OZT_Value v = "@PRINTER, Command not supported in ENM";
       pCmdRspBuf->append(v, toFormat);
       pCmdRspBuf->append("\n");
       interpreter->set_flow_info(OZT_Flow::NORMAL);
       interpreter->set_result(OZT_Result::NO_PROBLEM);
     }
| OZT_T_PROMPT OZT_T_EOLN
     {
	RWCString label;

	if( interpreter->isAloneCommand() == FALSE ){
         	if (pPromptNotice == 0)
         	{
             		interpreter->set_flow_info(OZT_Flow::NORMAL);
             		interpreter->set_result(OZT_Result::NO_UI_SUPPORTED);
             		YYERROR;
         	}
         	interpreter->set_flow_info(OZT_Flow::NORMAL);
                try
                {
   		   switch (pPromptNotice->askContinue())
   		   {
   			   case OZT_PromptNotice::TO_CONTINUE :
   				   interpreter->set_result(OZT_Result::NO_PROBLEM);
   				   break;
   			   case OZT_PromptNotice::TO_STOP :
   				   if( pCmdSender->isOnDisconnectSet() )
   					   pCmdSender->resetOnDisconnectLabel();
   				   interpreter->set_result(OZT_Result::STOP);
   				   break;
   			   case OZT_PromptNotice::TO_STOP_N_QUIT :
   				   if( pCmdSender->isOnDisconnectSet() )
   					   pCmdSender->resetOnDisconnectLabel();

   				   interpreter->set_result(OZT_Result::QUIT);
   				   break;
   			   case OZT_PromptNotice::TIMEOUT:
   				   label = pPromptNotice->getTimeoutLabel();

   				   interpreter->set_flow_info( OZT_Flow( OZT_Flow::GOTO_LABEL,
   									 label ) );

   				   interpreter->set_result(OZT_Result::NO_PROBLEM);
   				   break;

   			   default:
   				   interpreter->set_result(OZT_Result(OZT_Result::INTERNAL_ERR,
   						       "Invalid prompt return value"));
   				   break;
   		   }


                }
                catch (const OPS::OPS_Client_Exception& ce)
                {
                   interpreter->set_result(OZT_Result::NO_UI_SUPPORTED);
                   YYERROR;
                }
	}
	else{
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
     }
| OZT_T_QUIT OZT_T_EOLN
     {
	if( interpreter->isAloneCommand() == FALSE ){
		if( pCmdSender->isOnDisconnectSet() )
			pCmdSender->resetOnDisconnectLabel();

                ozt_errHandler.clearFlag();

        	interpreter->set_flow_info(OZT_Flow::NORMAL);
        	interpreter->set_result(OZT_Result::QUIT);
	}
	else {
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
     }
| OZT_T_R '+' OZT_T_EOLN
     {
         pCmdSender->setR();
         interpreter->set_flow_info(OZT_Flow::NORMAL);
         interpreter->set_result(OZT_Result::NO_PROBLEM);
     }
| OZT_T_R '-' OZT_T_EOLN
     {
         pCmdSender->clearR();
         interpreter->set_flow_info(OZT_Flow::NORMAL);
         interpreter->set_result(OZT_Result::NO_PROBLEM);
     }
| OZT_T_READ '(' varname ')' OZT_T_EOLN
      {
          OZT_Value tempValue;

          interpreter->set_flow_info(OZT_Flow::NORMAL);

	  OZT_Result res = pFileMgr->readLine(tempValue);

	  if( res.code !=  OZT_Result::NO_PROBLEM )
		ozt_errHandler.setFlag();

          interpreter->set_result( res );

          pVarStore->put(*($3), tempValue);
      }
| OZT_T_READ '(' varname ',' line  ')' OZT_T_EOLN
      {
          OZT_Value tempValue;

          interpreter->set_flow_info(OZT_Flow::NORMAL);

  	  OZT_Result res = pFileMgr->readLine(tempValue, *($5));

	  if( res.code !=  OZT_Result::NO_PROBLEM )
		ozt_errHandler.setFlag();

          interpreter->set_result( res );

          pVarStore->put(*($3), tempValue);
      }
| OZT_T_RENAME '(' exp ',' exp ')' OZT_T_EOLN
      {
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(pFileMgr->reNameFile(*($3), *($5)));
      }
| OZT_T_REPORT '(' exp ')' OZT_T_EOLN
{
        RWBoolean toFormat;
        OZT_Value v = "@REPORT, Command not supported in ENM";
        pCmdRspBuf->append(v, toFormat);
        pCmdRspBuf->append("\n");
        interpreter->set_flow_info(OZT_Flow::NORMAL);
        interpreter->set_result(OZT_Result::NO_PROBLEM);
     }
| OZT_T_RESET OZT_T_EOLN
      {
	//pSourceMgr->getVarStore().clearAll();
	pSourceMgr->reset(0);

	if(pIOWin != 0)        pIOWin->resetTimeout();
	if(pInkeyPopup != 0)   pInkeyPopup->resetTimeout();
	if(pInputPopup != 0)   pInputPopup->resetTimeout();
	if(pPromptNotice != 0) pPromptNotice->resetTimeout();

	pSourceMgr->getIndicator().clearMsg();
        interpreter->set_flow_info(OZT_Flow::NORMAL);
	interpreter->set_result(OZT_Result::NO_PROBLEM);
      }
| OZT_T_RESTART OZT_T_EOLN
      {
	if( interpreter->isAloneCommand() == FALSE ){
          	interpreter->set_flow_info(OZT_Flow::RESTART);
          	interpreter->set_result(OZT_Result::NO_PROBLEM);
	}
	else{
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
      }
| OZT_T_RETURN OZT_T_EOLN
      {
	if( interpreter->isAloneCommand() == FALSE ){
          	interpreter->set_flow_info(OZT_Flow::RETURN_FROM_GOSUB);
          	interpreter->set_result(OZT_Result::NO_PROBLEM);
	}
	else{
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
      }
| OZT_T_RMDIR '(' exp ')' OZT_T_EOLN
      {
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(pFileMgr->rmDir(*($3)));
      }
| OZT_T_S OZT_T_EOLN
      {
          pRspReceiver->logOn();
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(OZT_Result::NO_PROBLEM);
      }
| OZT_T_SELPRINT '(' exp ')' OZT_T_EOLN
      {
          RWBoolean toFormat;
          OZT_Value v = "@SELPRINT, Command not supported in ENM";
          pCmdRspBuf->append(v, toFormat);
          pCmdRspBuf->append("\n");
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(OZT_Result::NO_PROBLEM);
      }
| OZT_T_SEND '(' exp_list ')' OZT_T_EOLN
      {
          // loop through the list to concatenate all expressions.
          RWCString temp;
          while (($3)->entries() != 0)
          {
              temp = (RWCString)temp + (RWCString)(($3)->first());
              ($3)->removeFirst();
          }
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(pCmdSender->sendCmd(
                                  interpreter->getCurrFileName(),temp, FALSE));
      }
| OZT_T_SENDAP '(' exp ')' OZT_T_EOLN
      {
/// TODO i/f change	  RWCString sNe = pCmdSender->getRosHandler().GetEsName();
//	  OZT_Result result = pAPSender->Connect(sNe);
	  if(result.code == OZT_Result::NO_PROBLEM)
          {
	      pCmdRspBuf->markSearchBackPoint();
/// TODO	      result = pAPSender->SendCommand(*($3));
	result = OZT_Result::NO_PROBLEM;
          }
	  interpreter->set_flow_info(OZT_Flow::NORMAL);
	  interpreter->set_result(result.filtered());
      }
| OZT_T_SENDAP '(' exp ',' exp ')' OZT_T_EOLN
      {
/// TODO i/f change	  RWCString sNe = pCmdSender->getRosHandler().GetEsName();
//	  OZT_Result result = pAPSender->Connect(sNe);
	  if(result.code == OZT_Result::NO_PROBLEM)
          {
	      pCmdRspBuf->markSearchBackPoint();
/// TODO	      result = pAPSender->SendCommand(*($3), TRUE, *($5));
	result = OZT_Result::NO_PROBLEM;
          }
	  interpreter->set_flow_info(OZT_Flow::NORMAL);
	  interpreter->set_result(result.filtered());
      }
| OZT_T_SET  varname '=' exp OZT_T_EOLN
      {
          pVarStore->put(*($2), *($4));
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(OZT_Result::NO_PROBLEM);
      }
| OZT_T_SETPHASE '(' exp ')' OZT_T_EOLN
	{
		pSourceMgr->setPhaseDescription(*($3));
		interpreter->set_flow_info(OZT_Flow::NORMAL);
          	interpreter->set_result(OZT_Result::NO_PROBLEM);
	}
| OZT_T_SETPROGRESS '(' exp ')' OZT_T_EOLN
	{
		interpreter->set_result(pSourceMgr->setProgress(*($3)));
		interpreter->set_flow_info(OZT_Flow::NORMAL);
	}

| OZT_T_SETTOTALCOUNT '(' exp ')' OZT_T_EOLN
	{
		interpreter->set_result(pSourceMgr->setTotalCount(*($3)));
		interpreter->set_flow_info(OZT_Flow::NORMAL);
	}

| OZT_T_SETREPLY '(' exp ',' exp  ')' OZT_T_EOLN
      {
          *($3) = trim(*($3));
          ($3)->toUpper();
          if (*($3) == "OK")
          {
              pCmdSender->setOKReply(*($5));
              pRspCatcher->setOKReply(*($5));
              interpreter->set_flow_info(OZT_Flow::NORMAL);
              interpreter->set_result(OZT_Result::NO_PROBLEM);
          }
          else if (*($3) == "FAIL")
          {
              pCmdSender->setFailReply(*($5));
              pRspCatcher->setFailReply(*($5));
              interpreter->set_flow_info(OZT_Flow::NORMAL);
              interpreter->set_result(OZT_Result::NO_PROBLEM);
          }
          else
          {
              interpreter->set_flow_info(OZT_Flow::NORMAL);
              interpreter->set_result(OZT_Result::INVALID_VALUE);
          }
      }
| OZT_T_SPONTREP '(' varname ',' exp ',' exp_list ')' OZT_T_EOLN
      {
	  RWBoolean toFormat;
	  OZT_Value v = "@SPONTREP, Command not supported in ENM";
	  pCmdRspBuf->append(v, toFormat);
	  pCmdRspBuf->append("\n");
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(OZT_Result::NO_PROBLEM);
      }
| OZT_T_SPONTREPOFF OZT_T_EOLN
      {
          RWBoolean toFormat;
          OZT_Value v = "@SPONTREPOFF, Command not supported in ENM";
          pCmdRspBuf->append(v, toFormat);
          pCmdRspBuf->append("\n");
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(OZT_Result::NO_PROBLEM);
      }
| OZT_T_SPONTREPOFF '(' ')' OZT_T_EOLN
      {
          RWBoolean toFormat;
          OZT_Value v = "@SPONTREPOFF, Command not supported in ENM";
          pCmdRspBuf->append(v, toFormat);
          pCmdRspBuf->append("\n");
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(OZT_Result::NO_PROBLEM);
      }
| OZT_T_SPONTREPOFF '(' exp ')' OZT_T_EOLN
      {
          RWBoolean toFormat;
          OZT_Value v = "@SPONTREPOFF, Command not supported in ENM";
          pCmdRspBuf->append(v, toFormat);
          pCmdRspBuf->append("\n");
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(OZT_Result::NO_PROBLEM);
      }
| OZT_T_SPONTREPOFF '(' exp ',' exp_list ')' OZT_T_EOLN
      {
          RWBoolean toFormat;
          OZT_Value v = "@SPONTREPOFF, Command not supported in ENM";
          pCmdRspBuf->append(v, toFormat);
          pCmdRspBuf->append("\n");
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(OZT_Result::NO_PROBLEM);
      }
| OZT_T_STEPPROGRESS OZT_T_EOLN
	{
		interpreter->set_result(pSourceMgr->stepProgress());
		interpreter->set_flow_info(OZT_Flow::NORMAL);
	}

| OZT_T_STEPPROGRESS '(' exp ')' OZT_T_EOLN
	{
		interpreter->set_result(pSourceMgr->stepProgress(*($3)));
		interpreter->set_flow_info(OZT_Flow::NORMAL);
	}

| OZT_T_STOP OZT_T_EOLN
      {
	if( interpreter->isAloneCommand() == FALSE ){
		if( pCmdSender->isOnDisconnectSet() )
			pCmdSender->resetOnDisconnectLabel();

                ozt_errHandler.clearFlag();

		interpreter->set_flow_info(OZT_Flow::NORMAL);
        	interpreter->set_result(OZT_Result::STOP);
	}
	else{
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
      }
| OZT_T_T exp OZT_T_EOLN
      {
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(pClock->delaySec(*($2)));
      }
| OZT_T_VIEWFILE '(' exp ')' OZT_T_EOLN
      {
          if (pFViewerPopup == 0)
          {
              interpreter->set_flow_info(OZT_Flow::NORMAL);
              interpreter->set_result(OZT_Result::NO_UI_SUPPORTED);
          }
          else
          {
              interpreter->set_flow_info(OZT_Flow::NORMAL);
              result = pFViewerPopup->view(*($3));
              interpreter->set_result(result.filtered());
          }
      }
| OZT_T_W OZT_T_EOLN
      {
	if( interpreter->isAloneCommand() == FALSE ){
         	if (pPromptNotice == 0)
         	{
             		interpreter->set_flow_info(OZT_Flow::NORMAL);
             		interpreter->set_result(OZT_Result::NO_UI_SUPPORTED);
             		YYERROR;
         	}
         	interpreter->set_flow_info(OZT_Flow::NORMAL);
         	switch (pPromptNotice->askContinue())
         	{
             		case OZT_PromptNotice::TO_CONTINUE :
                 		interpreter->set_result(OZT_Result::NO_PROBLEM);
                 		break;
             		case OZT_PromptNotice::TO_STOP :
                 		interpreter->set_result(OZT_Result::STOP);
                 		break;
             		case OZT_PromptNotice::TO_STOP_N_QUIT :
                 		interpreter->set_result(OZT_Result::QUIT);
                 		break;
             		default:
                 		interpreter->set_result(OZT_Result(OZT_Result::INTERNAL_ERR,
                                           			"Invalid prompt return value"));
                 		break;
         	}
	}
	else {
		interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
		YYERROR;
	}
      }
| OZT_T_WAITFOR '(' exp ')' OZT_T_EOLN
      {
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(pRspCatcher->waitFor(*($3),"", TRUE, OZT_Value(0L)));
      }
| OZT_T_WAITFOR '(' exp ',' exp ')' OZT_T_EOLN
      {
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(pRspCatcher->waitFor(*($3), "", FALSE, *($5)));
      }
| OZT_T_WAITFOR '(' exp ',' exp ',' exp ')' OZT_T_EOLN
      {
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(pRspCatcher->waitFor(*($3), *($5), FALSE, *($7)));
      }
| OZT_T_WAITREPLY OZT_T_EOLN
      {
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(pRspCatcher->waitReply(TRUE, OZT_Value(0L)));
      }
| OZT_T_WAITREPLY '(' exp ')' OZT_T_EOLN
      {
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(pRspCatcher->waitReply(FALSE, *($3)));
      }
| OZT_T_WINDEND OZT_T_EOLN
      {
          pCommentWinModel->beInactive();
          if (pIOWin != 0)
              pIOWin->close();
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(OZT_Result::NO_PROBLEM);
      }
| OZT_T_WINDOW OZT_T_EOLN
      {
          pCommentWinModel->beActive();
          pCommentWinModel->clear();
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(OZT_Result::NO_PROBLEM);
      }
| OZT_T_WRITE '(' exp ')' OZT_T_EOLN
      {
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(pFileMgr->writeLine(*($3)));
      }

| OZT_T_WRITE '(' exp ',' line ')' OZT_T_EOLN
      {
	  interpreter->set_flow_info(OZT_Flow::NORMAL);
	  interpreter->set_result(pFileMgr->writeLine(*($3), *($5)));

      }
| OZT_T_WRITE '(' exp ',' line ','  exp_list ')' OZT_T_EOLN
      {
	  // concatenate the strings first
          RWCString tempStr = RWCString();
          while (($7)->entries() != 0)
          {
               tempStr = (RWCString)tempStr + (RWCString)(($7)->first());
               ($7)->removeFirst();
          }
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(pFileMgr->writeLine(*($3), *($5), tempStr));
      }
| OZT_T_WRITE '(' exp ',' exp_list ')' OZT_T_EOLN
      {
          // concatenate the strings first
          RWCString tempStr = RWCString();
          while (($5)->entries() != 0)
          {
               tempStr = (RWCString)tempStr + (RWCString)(($5)->first());
               ($5)->removeFirst();
          }
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(pFileMgr->writeLine(*($3), "", tempStr));
      }
| OZT_T_Z charSequence OZT_T_EOLN
      {
          RWCString curFile = interpreter->getCurrFileName();
          interpreter->set_flow_info(OZT_Flow::NORMAL);
          interpreter->set_result(pCmdSender->setZ(*($2), curFile));
      }
;

charSequence     : {ozt_sc = SC_CHAR_SEQ;} OZT_T_STRING
                   {$$ = newValue(ozt_TokenVal); ozt_sc = SC_NORMAL;}
                 ;

labelname        : {ozt_sc = SC_LABEL;} OZT_T_LABELNAME
		   {$$ = newValue(ozt_TokenVal); ozt_sc = SC_NORMAL;}
                 ;

/*********************************************/
/*           Rules for expression            */
/*********************************************/

opt_exp_list     : exp_list { $$ = $1; }
                 | {$$ = newValueList();}
                 ;

cond_exp         : simple_cond_exp
                      {
                          $$ = $1;
                      }
                 | cond_exp OZT_T_AND simple_cond_exp
                      {
                          $$ = ($1 && $3);
                      }
                 | cond_exp OZT_T_OR  simple_cond_exp
                      {
                          $$ = ($1 || $3);
                      }
                 ;

simple_cond_exp  : exp  OZT_T_LT  exp
                      {
			  OZT_Result tmp1, tmp2;
			  long arg1 = ($1)->toLong(tmp1);
			  long arg2 = ($3)->toLong(tmp2);
			  if ((tmp1.code == OZT_Result::NO_PROBLEM) &&
                              (tmp2.code == OZT_Result::NO_PROBLEM))
				$$ = arg1 < arg2;
			  else
                              $$ = (*($1) < *($3));
                      }
                 | exp  OZT_T_LE  exp
                      {
			  OZT_Result tmp1, tmp2;
			  long arg1 = ($1)->toLong(tmp1);
			  long arg2 = ($3)->toLong(tmp2);
			  if ((tmp1.code == OZT_Result::NO_PROBLEM) &&
                              (tmp2.code == OZT_Result::NO_PROBLEM))
				$$ = arg1 <= arg2;
			  else
                              $$ = (*($1) <= *($3));
                      }
                 | exp  '='   exp
                      {
			  OZT_Result tmp1, tmp2;
			  long arg1 = ($1)->toLong(tmp1);
			  long arg2 = ($3)->toLong(tmp2);
			  if ((tmp1.code == OZT_Result::NO_PROBLEM) &&
                              (tmp2.code == OZT_Result::NO_PROBLEM))
				$$ = arg1 == arg2;
			  else
                              $$ = (*($1) == *($3));
                      }
                 | exp  OZT_T_NE  exp
                      {
			  OZT_Result tmp1, tmp2;
			  long arg1 = ($1)->toLong(tmp1);
			  long arg2 = ($3)->toLong(tmp2);
			  if ((tmp1.code == OZT_Result::NO_PROBLEM) &&
                              (tmp2.code == OZT_Result::NO_PROBLEM))
				$$ = arg1 != arg2;
			  else
                              $$ = (*($1) != *($3));
                      }
                 | exp  OZT_T_GE  exp
                      {
			  OZT_Result tmp1, tmp2;
			  long arg1 = ($1)->toLong(tmp1);
			  long arg2 = ($3)->toLong(tmp2);
			  if ((tmp1.code == OZT_Result::NO_PROBLEM) &&
                              (tmp2.code == OZT_Result::NO_PROBLEM))
				$$ = arg1 >= arg2;
			  else
                              $$ = (*($1) >= *($3));
                      }
                 | exp  OZT_T_GT  exp
                      {
			  OZT_Result tmp1, tmp2;
			  long arg1 = ($1)->toLong(tmp1);
			  long arg2 = ($3)->toLong(tmp2);
			  if ((tmp1.code == OZT_Result::NO_PROBLEM) &&
                              (tmp2.code == OZT_Result::NO_PROBLEM))
				$$ = arg1 > arg2;
			  else
                              $$ = (*($1) > *($3));
                      }
                 | '(' cond_exp ')'
                      {
                          $$ = $2;
                      }
                 ;

formExpList      : formExpList ',' formExp
                   {
			// get the control type
			OZT_Value type = ($3)->removeFirst();

			if( type == OZT_Value( "VAR" ) ) {
				($1)->insert( type );
                       		($1)->insert(($3)->removeFirst()); // X
                       		($1)->insert(($3)->removeFirst()); // Y
                       		($1)->insert(($3)->removeFirst()); // length
                       		($1)->insert(($3)->removeFirst()); // varname
				($1)->insert(($3)->removeFirst()); // default
                       		$$ = $1;
			}
			else if( type == OZT_Value( "CHECKBOX" ) ) {
				($1)->insert( type );
				($1)->insert(($3)->removeFirst()); //X
				($1)->insert(($3)->removeFirst()); //Y
				($1)->insert(($3)->removeFirst()); //title
				($1)->insert(($3)->removeFirst()); //variable name
				($1)->insert(($3)->removeFirst()); //default
				$$ = $1;
			}
			else if( type == OZT_Value( "BUTTON" ) ) {
				($1)->insert( type );
				($1)->insert(($3)->removeFirst()); //X
				($1)->insert(($3)->removeFirst()); //Y
				($1)->insert(($3)->removeFirst()); //title
				($1)->insert(($3)->removeFirst()); //label
				$$ = $1;
			}
			else if( type == OZT_Value( "RADIO" ) ) {
				($1)->insert( type );
				($1)->insert(($3)->removeFirst()); //variable name
				($1)->insert(($3)->removeFirst()); //default

				while( ($3)->entries() > 1 ) {
					($1)->insert(($3)->removeFirst()); // X
					($1)->insert(($3)->removeFirst()); // Y
					($1)->insert(($3)->removeFirst()); // Title
				}
				($1)->insert(($3)->removeFirst()); // "ENDRADIO"
			}
			else if( type == OZT_Value( "COMBO" ) ) {
				($1)->insert( type );
				($1)->insert(($3)->removeFirst()); // X
				($1)->insert(($3)->removeFirst()); // Y
				($1)->insert(($3)->removeFirst()); // variable name
				($1)->insert(($3)->removeFirst()); // default
				($1)->insert(($3)->removeFirst()); // option source -  file/specified options

				while( ($3)->entries() > 1 ) {
					($1)->insert(($3)->removeFirst()); // combo options
				}
				($1)->insert(($3)->removeFirst()); // "ENDCOMBO"
			}
                   }
                 | formExp
                   {
                       $$ = $1;
                   }
                 ;

formButtonExp          : exp ',' exp ',' exp
                   {
                       $$ = newValueList();
                       ($$)->insert(*($1));
                       ($$)->insert(*($3));
                       ($$)->insert(*($5));
		   }
                 ;

formButtonExpList      : formButtonExpList ',' formButtonExp
                   {
                   	($1)->insert(($3)->removeFirst()); // X
                       	($1)->insert(($3)->removeFirst()); // Y
                       	($1)->insert(($3)->removeFirst()); // title
			$$ = $1;
                   }
                 | formButtonExp
                   {
                       $$ = $1;
                   }
                 ;

formExp          : exp ',' exp ',' exp ',' varname
                   {
                       $$ = newValueList();
		       ($$)->insert( OZT_Value( "VAR" ) );
                       ($$)->insert(*($1));
                       ($$)->insert(*($3));
                       ($$)->insert(*($5));
                       ($$)->insert(*($7));
                       //  get the value of the variable as the default value
                       if (pVarStore->contains(*($7)))
                       {
                           OZT_Value temp;

                           pVarStore->get(*($7), temp);
                           ($$)->insert(temp);
                       }
                       else
                       {
                           ($$)->insert("");
                       }
                   }
		   | formcontrol
		   {
			$$ = $1;
		   }
                 ;



exp_list         : exp_list ',' exp
                      {
                          $1->insert(*($3));
                          $$ = $1;
                      }
                 | exp
                      {
                          $$ = newValueList();
                          $$->insert(*($1));
                      }
                 ;


exp              : prefixed_exp {$$ = $1;}
                 | exp '+' exp
                      {
                          $$ = newValue(add(*($1), *($3), result));
                          if (result.code != OZT_Result::NO_PROBLEM)
                          {
                              interpreter->set_result(result);
                              YYERROR;
                          }
                      }
                 | exp '-' exp
                      {
                          $$ = newValue(sub(*($1), *($3), result));
                          if (result.code != OZT_Result::NO_PROBLEM)
                          {
                              interpreter->set_result(result);
                              YYERROR;
                          }
                      }
                 | exp '*' exp
                      {
                          $$ = newValue(mul(*($1), *($3), result));
                          if (result.code != OZT_Result::NO_PROBLEM)
                          {
                              interpreter->set_result(result);
                              YYERROR;
                          }
                      }
                 | exp '/' exp
                      {
                          $$ = newValue(div(*($1), *($3), result));
                          if (result.code != OZT_Result::NO_PROBLEM)
                          {
                              interpreter->set_result(result);
                              YYERROR;
                          }
                      }
                 ;

prefixed_exp     : '+' simple_exp %prec DUMMY
                      {

                          $$ = newValue(unaryPlus(*($2), result));
                          if (result.code != OZT_Result::NO_PROBLEM)
                          {
                              interpreter->set_result(result);
                              YYERROR;
                          }
                      }
                 | '-' simple_exp %prec DUMMY
                      {
                          $$ = newValue(unaryMinus(*($2), result));
                          if (result.code != OZT_Result::NO_PROBLEM)
                          {
                              interpreter->set_result(result);
                              YYERROR;
                          }
                      }
                 | simple_exp  {$$ = $1;}
                 ;

simple_exp       : constant    {$$ = $1;}
                 | funcall     {$$ = $1;}
                 | '(' exp ')' {$$ = $2;}
                 | varaccess   {$$ = $1;}
                 ;

varaccess        : varname
                   {
                       if (pVarStore->contains(*($1)))
                       {
                           OZT_Value temp;

                           pVarStore->get(*($1), temp);
                           $$ = newValue(temp);
                       }
                       else {
                           switch(context)
                           {
                               case OZT_NORM_CTXT :
                                    interpreter->set_result(
                                        OZT_Result(OZT_Result::VAR_UNDEFINED
                                                   , *($1)));
                                    YYERROR;

                               case OZT_DRAW_CTXT :
                                    if (*($1) == "BOX")
                                        $$ = newValue(OZT_IOW::drawBox);
                                    else if (*($1) == "CUP")
                                        $$ = newValue(OZT_IOW::drawCup);
                                    else if (*($1) == "HIGH")
                                        $$ = newValue(OZT_IOW::drawHigh);
                                    else if (*($1) == "INV")
                                        $$ = newValue(OZT_IOW::drawInv);
                                    else if (*($1) == "LOW")
                                        $$ = newValue(OZT_IOW::drawLow);
                                    else
                                    {
                                        interpreter->set_result(
                                            OZT_Result(OZT_Result::VAR_UNDEFINED
                                                       , *($1)));
                                        YYERROR;
                                    }
                                    break;
				case OZT_STYLE_CTXT:
				    if( *($1) == "BOLD" )
					$$ = newValue(OZT_IOW::styleBold );
				    else if( *($1) == "UNDERLINE" )
					$$ = newValue(OZT_IOW::styleUndrln );
				    else if( *($1) == "ITALIC" )
					$$ = newValue(OZT_IOW::styleItal );
				    else if( *($1) == "PLAIN" )
					$$ = newValue(OZT_IOW::stylePlain );
				    else {
					interpreter->set_result( OZT_Result( OZT_Result::VAR_UNDEFINED, *($1)));
					YYERROR;
				    }
				    break;
				   }
				}
                           };

constant         : OZT_T_STRING         { $$ = newValue(ozt_TokenVal); }
                 | char_constant    { $$ = $1; }
                 | OZT_T_NUM_CONST      { $$ = newValue(ozt_TokenVal); }
                 ;

char_constant    : OZT_T_DEC_CHAR_CONST { $$ = newValue(ozt_TokenVal); }
                 | OZT_T_HEX_CHAR_CONST { $$ = newValue(ozt_TokenVal); }
                 ;

/*******************************************************************/
/*           Rules forfield definition in the FORM command         */
/*******************************************************************/

line             : OZT_T_LN '(' exp ')'
		   {
			OZT_Result res;
			long l = ($3)->toLong( res );

			if (res.code != OZT_Result::NO_PROBLEM)
          		{
              			interpreter->set_result(res);
              			YYERROR;
          		}
          		if( l <=  0 )
          		{
              			interpreter->set_result(OZT_Result::INVALID_VALUE);
              			YYERROR;
          		}
			else
			{
				$$ = newValue( *($3) );
			}
		   }
formcontrol	 : OZT_T_FORMFIELD '(' exp ',' exp ',' exp ',' varname ')'
		   {
			$$ = newValueList();
			($$)->insert( OZT_Value( "VAR" ) );
			($$)->insert( *($3) ); // X coordinate
			($$)->insert( *($5) ); // Y coordinate
			($$)->insert( *($7) ); // length
			($$)->insert( *($9) ); // variable name

			//get the valueof the variable as the default
			if( pVarStore->contains( *($9) ) )
			{
				OZT_Value temp;
				pVarStore->get( *($9), temp );
				($$)->insert(temp);
			}
			else
			{
				($$)->insert("");
			}
		}
		|
		OZT_T_FORMBUTTON '(' exp ',' exp ',' exp ',' exp ')'
		{
			//check if the specified label exist
			result = pSourceMgr->getCurrSourceInfo()->labelExist(*($9));
			if( result.code != OZT_Result::NO_PROBLEM )
			{
				interpreter->set_result( result );
				YYERROR;
			}

			$$ = newValueList();
			($$)->insert( OZT_Value( "BUTTON" ) );	//type
			($$)->insert( *($3) ); // X coordinate
			($$)->insert( *($5) ); // Y coordinate
			($$)->insert( *($7) ); // title
			($$)->insert( *($9) ); // label
		}
		|
		OZT_T_FORMCHECKBOX '(' exp ',' exp ',' exp ',' varname ')'
		{
			$$ = newValueList();
			($$)->insert( OZT_Value( "CHECKBOX" ) );
			($$)->insert( *($3) ); // X coordinate
			($$)->insert( *($5) ); // Y coordinate
			($$)->insert( *($7) ); // title
			($$)->insert( *($9) ); // variable name

			//get the valueof the variable as the default
			if( pVarStore->contains( *($9) ) )
			{
				OZT_Value temp;
				pVarStore->get( *($9), temp );
				($$)->insert(temp);
			}
			else
			{
				($$)->insert("");
			}
		}
		|
		OZT_T_FORMRADIOBUTTON '(' formButtonExpList ',' varname ')'
		{
			$$ = newValueList();
			($$)->insert( OZT_Value( "RADIO" ) );
			($$)->insert( *($5) ); // variable name

			//get the value of the variable as the default
			if( pVarStore->contains( *($5) ) )
			{
				OZT_Value temp;
				pVarStore->get( *($5), temp );
				($$)->insert(temp); //default value

			}
			else
			{
				($$)->insert(""); //default value
			}

			if( ($3)->entries() < 3 ) {
				// incorrect number of parameters
				interpreter->set_result(OZT_Result::SYNTAX_ERR);
              			YYERROR;
			}
			else {
				while( ($3)->entries() > 0 ) {
					($$)->insert( OZT_Value( ($3)->removeFirst() ) ); // X
					($$)->insert( OZT_Value( ($3)->removeFirst() ) ); // Y
					($$)->insert( OZT_Value( ($3)->removeFirst() ) ); // Title
				}
			}
			($$)->insert( OZT_Value( "ENDRADIO" ) );

		}
		|
		OZT_T_FORMCOMBO '(' exp ',' exp ',' varname ',' exp_list ')'
		{
			$$ = newValueList();
			($$)->insert( OZT_Value( "COMBO" ) );
			($$)->insert( *($3) ); // X coordinate
			($$)->insert( *($5) ); // Y coordinate
			($$)->insert( *($7) ); // variable name

			//get the value of the variable as the default
			if( pVarStore->contains( *($7) ) )
			{
				OZT_Value temp;
				pVarStore->get( *($7), temp );
				($$)->insert(temp); //default value
			}
			else
			{
				($$)->insert(""); //default value
			}

			if( ($9)->entries() == 1 ) {
				// only the file name is specified
				($$)->insert( OZT_Value( "FILE" ) );
				($$)->insert( OZT_Value( ($9)->removeFirst() ) );
				($$)->insert( OZT_Value( "ENDCOMBO" ) );
			}
			else if( ($9)->entries() > 1 ) {
				//all options are specified
				($$)->insert( OZT_Value( "OPTIONS" ) );
				while( ($9)->entries() > 0 ) {
					($$)->insert( OZT_Value( ($9)->removeFirst() ) );
				}
				($$)->insert( OZT_Value( "ENDCOMBO" ) );
			}
			else {
				// incorrect number of parameters
				interpreter->set_result(OZT_Result::SYNTAX_ERR);
              			YYERROR;
			}
		}
		;

/*********************************************/
/*           Rules for function call         */
/*********************************************/
funcall          :
  OZT_T_ADVANCE '(' exp ',' exp ')'
      {
          OZT_Time theTime(*($3));

          if (!theTime.advance(*($5)))
          {
              interpreter->set_result(OZT_Result::INVALID_VALUE);
              YYERROR;
          }

          $$ = newValue((theTime.toString())(0,10));
      }

| OZT_T_REGRESS '(' exp ',' exp ')'
{
	OZT_Time theTime( *($3) );
	if( !theTime.regress( *($5) ) )
	{
	 	interpreter->set_result(OZT_Result::INVALID_VALUE);
              	YYERROR;
	}

	$$ = newValue((theTime.toString())(0,10));
}
| OZT_T_CENTRALDIR '(' ')'
      {
          RWCString temp;

          if ((ozt_info.getCentralDir(temp) != CHA_OZTInfo::OKAY) ||
              temp.isNull())
          {
              interpreter->set_result(OZT_Result::CENTRALDIR_NOT_DEFINED);
              YYERROR;
          }

          if (temp[temp.length() - 1] != '/')
              temp.append('/');
          $$ = newValue(temp);
      }

| OZT_T_CONCAT '(' exp_list ')'
      {
          if (($3)->entries() < 2)
          {
              interpreter->set_result(OZT_Result::SYNTAX_ERR);
              YYERROR;
          }
          else
          {
              OZT_Value temp;

              while (($3)->entries() != 0)
              {
                  temp = temp + ($3)->first();
                  ($3)->removeFirst();
              }
              $$ = newValue(temp);
          }
      }
| OZT_T_CREATECHILDSESSION '(' exp ')'
      {
          OZT_Result result = pChildHandler->createChildSession(*($3));
          if (result.code == OZT_Result::CHILD_NOT_SUPPORTED)
          {
       	      interpreter->set_result(result);
              YYERROR;
          }
          $$ = newValue(result.info.data());
      }
| OZT_T_CREATECHILDSESSION '(' exp ',' exp_list ')'
      {
          OZT_Result result = pChildHandler->createChildSession(*($3), *($5));
          if (result.code == OZT_Result::CHILD_NOT_SUPPORTED)
          {
       	      interpreter->set_result(result);
              YYERROR;
          }
          $$ = newValue(result.info.data());
      }
| OZT_T_STARTCHILDSESSION '(' exp ')'
      {
          OZT_Result result = pChildHandler->startChildSession(*($3));
          if (result.code == OZT_Result::CHILD_NOT_SUPPORTED)
          {
       	      interpreter->set_result(result);
              YYERROR;
          }
          $$ = newValue(result.info.data());
      }
| OZT_T_STARTCHILDSESSION '(' exp ',' exp_list ')'
      {
          /* Make sure the exp_list consists of PAIRS of variable name & variable value */
          if (($5)->entries() % 2 != 0)
          {
              interpreter->set_result(OZT_Result::SYNTAX_ERR);
              YYERROR;
          }
          else
          {
              OZT_Result result = pChildHandler->startChildSession(*($3), *($5));
              if (result.code == OZT_Result::CHILD_NOT_SUPPORTED)
              {
       	          interpreter->set_result(result);
                  YYERROR;
              }
              $$ = newValue(result.info.data());
          }
      }
| OZT_T_CHECKCHILDSESSION '(' exp ')'
      {
          OZT_Result result = pChildHandler->checkChildSession(*($3));
          if (result.code == OZT_Result::CHILD_NOT_SUPPORTED)
          {
       	      interpreter->set_result(result);
              YYERROR;
          }
          $$ = newValue(result.info.data());
      }
| OZT_T_TERMINATECHILDSESSION '(' exp ')'
      {
          OZT_Result result = pChildHandler->terminateChildSession(*($3));
          if (result.code == OZT_Result::CHILD_NOT_SUPPORTED)
          {
       	      interpreter->set_result(result);
              YYERROR;
          }
          $$ = newValue(result.info.data());
      }
| OZT_T_READVARIABLE '(' exp ',' exp ')'
      {
          OZT_Result result = pChildHandler->readVariable(*($3), *($5));
          if (result.code == OZT_Result::CHILD_NOT_SUPPORTED)
          {
       	      interpreter->set_result(result);
              YYERROR;
          }
          $$ = newValue(result.info.data());
      }
| OZT_T_STYLE '(' { previous_context = context; context = OZT_STYLE_CTXT; } exp { context = previous_context;} ',' exp  ')'
{
	OZT_Value temp;
	if( (*($4) ) == OZT_Value( OZT_IOW::styleBold ) ) {
		temp = "<b>" + *($7) + "</b>";
		temp.unvisibleChars = 7;
		$$ = newValue( temp );
	}
	else if( (*($4) ) == OZT_Value( OZT_IOW::styleItal ) ) {
		temp = "<i>" + *($7) + "</i>";
		temp.unvisibleChars = 7;
		$$ = newValue( temp );
	}
	else if( (*($4) ) == OZT_Value( OZT_IOW::styleUndrln ) ) {
		temp = "<u>" + *($7) + "</u>";
		temp.unvisibleChars = 7;
		$$ = newValue( temp );
	}
	else {
		$$ = newValue( *($7) );
	}
}
| OZT_T_PAD '(' exp ',' exp ',' exp  ')'
{
	OZT_Value val;
	if( (*($7) ) == "L" ) {
		val = leftJustify( *($3), *($5), result );
	}
	else if( (*($7) ) == "R" )  {
		val = rightJustify( *($3), *($5), result );
	}
	else if( (*($7) ) == "C" ) {
		val = center( *($3), *($5), result );
	}
	else {
		interpreter->set_result(OZT_Result::SYNTAX_ERR);
              	YYERROR;
	}

	if (result.code != OZT_Result::NO_PROBLEM)
        {
       		interpreter->set_result(result);
              	YYERROR;
        }
	else
		$$ = newValue( val );
}

| OZT_T_PAD '(' exp ',' exp ')'
{
	OZT_Value val;

	val = leftJustify( *($3), *($5), result );

	if (result.code != OZT_Result::NO_PROBLEM)
        {
       		interpreter->set_result(result);
              	YYERROR;
        }
	else
		$$ = newValue( val );
}

| OZT_T_COPY '(' exp ',' exp ',' exp ')'
      {
          $$ = newValue(($3)->copy(*($5), *($7), result));
          if (result.code != OZT_Result::NO_PROBLEM)
          {
              interpreter->set_result(result);
              YYERROR;
          }
      }

| OZT_T_DECIMAL '(' exp ')'
      {
          $$ = newValue(($3)->toDec(result));
          if (result.code != OZT_Result::NO_PROBLEM)
          {
              interpreter->set_result(result);
              YYERROR;
          }
      }

| OZT_T_DISKFREE '(' ')'
      {
          $$ = newValue(OZT_Value((long)(OZT_Disk::diskFree(result))));
          if (result.code != OZT_Result::NO_PROBLEM)
          {
              interpreter->set_result(result);
              YYERROR;
          }
      }

| OZT_T_DISKFREE '(' exp ')'
      {
          $$ = newValue(OZT_Value((long)(OZT_Disk::diskFree(*($3),result))));
          if (result.code != OZT_Result::NO_PROBLEM)
          {
              interpreter->set_result(result);
              YYERROR;
          }
      }

| OZT_T_EVLOADED '(' ')'
      {
          $$ = newValue("EVLOADED(), Command not Supported in ENM");
      }

| OZT_T_EVLOADED '(' exp ')'
      {
          $$ = newValue("EVLOADED(), Command not Supported in ENM");
      }

| OZT_T_GETDATE '(' ')'
      {
          $$ = newValue(OZT_Time().toString());
      }
| OZT_T_GETEXCHHDR '(' ')'
      {
					$$ = newValue(pCmdSender->getExchangeHeader());
      }
| OZT_T_GETPHASE '(' ')'
      {
          $$ = newValue(pSourceMgr->getPhaseDescription());
      }
| OZT_T_GETPROGRESS '(' ')'
      {
          $$ = newValue(pSourceMgr->getProgress());
      }
| OZT_T_GETIOTYPE '(' exp ')'
    {
        $$ = newValue(pCmdSender->getIoType(*($3)));
    }
| OZT_T_GETPROTOCOLTYPE '(' exp ')'
    {
        $$ = newValue("GETPROTOCOLTYPE(), Command not Supported in ENM");
    }
| OZT_T_GETTOTALCOUNT '(' ')'
      {
          $$ = newValue(pSourceMgr->getTotalCount());
      }
| OZT_T_LABELEXIST '(' exp ')'
	{
		if( interpreter->isAloneCommand() == FALSE ){
			OZT_Result res = pSourceMgr->getCurrSourceInfo()->labelExist(*($3));

			if( res.code == OZT_Result::LABEL_NOT_FOUND )
				$$ = newValue( OZT_Value( 0L ) );
			else if( res.code == OZT_Result::DUPLICATE_LABELS )
				$$ = newValue( OZT_Value( 2L ) );
			else if( res.code == OZT_Result::NO_PROBLEM )
				$$ = newValue( OZT_Value( 1L ) );
		}
		else {
			interpreter->set_result( OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY );
			YYERROR;
		}
	}
| OZT_T_GETMARK '(' ')'
	{
		long mark = pCmdRspBuf->getMark();
		$$ = newValue( OZT_Value( mark ) );
	}
| OZT_T_GETERRORFLAG '(' ')'
	{
		if( ozt_errHandler.isFlagSet() ) {
			$$ = newValue( OZT_Value( 1L ) );
		}
		else {
			$$ = newValue( OZT_Value( 0L ) );
		}
	}
| OZT_T_GETSESSIONID '(' ')'
      {
	RWCString id = pSourceMgr->getSessionId();
	$$ = newValue( id );
      }
| OZT_T_GETDATE '(' varname ')'
      {
          OZT_Time now;
          RWCString dayOfWeek;

          $$ = newValue(now.toString(dayOfWeek));
          pVarStore->put(*($3), dayOfWeek);
      }

| OZT_T_GETDEST '(' ')'
      {
          $$ = newValue(pCmdSender->getEsName());
      }

| OZT_T_GETFILELENGTH '(' exp ')'
      {
	long nrOfLines;

	result = pFileMgr->getFileLength(*($3), nrOfLines);

	if (result.code != OZT_Result::NO_PROBLEM)
        {
              interpreter->set_result(result);
              YYERROR;
        }
	else
	{
		$$ = newValue(nrOfLines);
	}
      }

| OZT_T_GETDIR '(' ')'
      {
          $$ = newValue(pFileMgr->getDir());
      }

| OZT_T_GETLOG '(' ')'
      {
          $$ = newValue(pFileLogger->getLog());
      }
| OZT_T_GETLOG '(' exp ')'
      {
          $$ = newValue(pFileLogger->getLog(*($3)));
      }

| OZT_T_GETMODE '(' ')'
      {
          $$ = newValue(pCmdSender->getEsType());
      }

| OZT_T_GETPRINT '(' ')'
      {
          $$ = newValue("GETPRINT(), Command not Supported in ENM");
      }

| OZT_T_GETSCHED '(' ')'
      {
          $$ = newValue("GETSCHED(), Command not Supported in ENM");
      }

| OZT_T_GETDEVID '(' ')'
      {
/// TODO i/f change        $$ = newValue(pCmdSender->getDeviceId());
	$$ = newValue(OZT_Value((long)-1)); // temporary MAGA, not supported in TMOS version
	//$$ = newValue( OZT_Value ( (long)(pCmdSender->getCHACmdSender().getDevModePropsObject()->getUsedDevId() ) ) );
      }
| OZT_T_HEX '(' exp ')'
      {
          $$ = newValue(($3)->toHex(result));
          if (result.code != OZT_Result::NO_PROBLEM)
          {
              interpreter->set_result(result);
              YYERROR;
          }
      }

| OZT_T_HEX '(' exp ',' exp ')'
      {
          $$ = newValue(($3)->toHex(result, *($5)));
          if (result.code != OZT_Result::NO_PROBLEM)
          {
              interpreter->set_result(result);
              YYERROR;
          }
      }

| OZT_T_INHISTORY '(' exp ')'
      {
        $$ = newValue("INHISTORY(), Command not Supported in ENM");
      }

| OZT_T_LENGTH '(' exp  ')'
      {
          $$ = newValue((long)($3->length()));
      }

| OZT_T_LOWCASE '(' exp ')'
      {
          ($3)->toLower();
          $$ = $3;
      }

| OZT_T_POS '(' exp ',' exp ')'
      {
          size_t pos;

          if (($3)->length() == 0)
              $$ = newValue(0L);
          else
          {
              pos = ($5)->index(*($3), $3->length(), 0, RWCString::exact);
              if (pos == RW_NPOS)
                  $$ = newValue(0L);
              else
                  $$ = newValue((long)(pos + 1));
          }
      }
| OZT_T_PRIVATEDIR '(' ')'
      {
          RWCString temp;

          if ((ozt_info.getPrivateDir(temp) != CHA_OZTInfo::OKAY) ||
              temp.isNull())
          {
              interpreter->set_result(OZT_Result::PRIVATEDIR_NOT_DEFINED);
              YYERROR;
          }

          if (temp[temp.length() - 1] != '/')
              temp.append('/');
          $$ = newValue(temp);
      }

| OZT_T_REPLY '(' exp ')'
      {
          long lineIndex;

          lineIndex = ($3)->toLong(result);
          if (result.code != OZT_Result::NO_PROBLEM)
          {
              interpreter->set_result(result);
              YYERROR;
          }
          if (lineIndex <= 0)
          {
              interpreter->set_result(OZT_Result::INVALID_VALUE);
              YYERROR;
          }
          $$ = newValue(pCmdRspBuf->reply((size_t)lineIndex));
      }

| OZT_T_REPLYLEN '(' ')'
      {
          $$ = newValue((long)(pCmdRspBuf->replyLen()));
      }

| OZT_T_SAVEDIR '(' ')'
      {
          RWCString temp;

          if ((ozt_info.getSaveDir(temp) != CHA_OZTInfo::OKAY) || temp.isNull())
          {
              interpreter->set_result(OZT_Result::SAVEDIR_NOT_DEFINED);
              YYERROR;
          }

          if (temp[temp.length() - 1] != '/')
              temp.append('/');

          $$ = newValue(temp);
      }

| OZT_T_SCAN '(' exp ')'
      {
          $$ = newValue((long)(pCmdRspBuf->scan(*($3))));
      }

| OZT_T_SCAN '(' exp ',' varname ')'
      {
          size_t temp;

          $$ = newValue((long)(pCmdRspBuf->scan(*($3), temp)));
          pVarStore->put(*($5), OZT_Value((long)temp));
      }

| OZT_T_SELFILE '(' exp ')'
      {
          if (pFSelectPopup == 0)
          {
              interpreter->set_flow_info(OZT_Flow::NORMAL);
              interpreter->set_result(OZT_Result::NO_UI_SUPPORTED);
              YYERROR;
          }

          RWCString temp;

          result = pFSelectPopup->selFile(*($3), "", temp);
          if (result.code == OZT_Result::NO_PROBLEM)
              $$ = newValue(temp);
          else
          {
              $$ = newValue("");
              interpreter->set_result(result);
              YYERROR;
          }
      }

| OZT_T_SELFILE '(' exp ',' exp_list ')'
      {
          if (pFSelectPopup == 0)
          {
              interpreter->set_flow_info(OZT_Flow::NORMAL);
              interpreter->set_result(OZT_Result::NO_UI_SUPPORTED);
              YYERROR;
          }
          RWCString prompt;
          RWCString temp;

          // loop through the list to concatenate all part of the prompt
          while (($5)->entries() != 0)
          {
              prompt = (RWCString)prompt + (RWCString)(($5)->first());
              ($5)->removeFirst();
          }
          result = pFSelectPopup->selFile(*($3), prompt, temp);
          if (result.code == OZT_Result::NO_PROBLEM)
              $$ = newValue(temp);
          else
          {
              $$ = newValue("");
              interpreter->set_result(result);
              YYERROR;
          }
      }

| OZT_T_TIMEEVSET '(' exp ',' exp ')'
      {
          $$ = newValue("TIMEEVSET(), Command not Supported in ENM");
      }

| OZT_T_TIMEEVSET '(' exp ',' exp ',' exp ')'
      {
          $$ = newValue("TIMEEVSET(), Command not Supported in ENM");
      }

| OZT_T_TRIM '(' exp ')'
      {
          *($3) = trim(*($3));
          $$ = newValue(*($3));
      }

| OZT_T_UPCASE '(' exp ')'
      {
          ($3)->toUpper();
          $$ = $3;
      }

| OZT_T_VAREXIST '(' varname ')'
      {
          if (pVarStore->contains(*($3)))
              $$ = newValue(1L);
          else
              $$ = newValue(0L);
      }

| OZT_T_VERSION '(' ')'
      {
	  $$ = newValue(OZT_Disk::opsVersion());
      }
;


varname  : OZT_T_VAR          {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_A            {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_AND          {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_C            {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_CHDIR        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_CHECK        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_CLOSE        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_CLRSCR       {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_COMMENT      {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_SETPHASE     {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_SETDEVID     {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_UNSETDEVID   {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_DEVID        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_CONNECT      {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_DEC          {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_DELAY        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_DELAYSEC     {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_DIAGNOSTICS  {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_DISCONNECT   {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_DRAW         {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_E            {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_ELSE         {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_ENDIF        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_FILE         {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_BREAK        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_ERASE        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_EVDELETE     {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_EXECUTE      {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_FLUSHVAR     {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_FOR          {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_FORM         {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_FUNBUSY      {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_G            {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_GOSUB        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_GOTO         {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_ONDISCONNECT {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_H            {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_I            {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_IF           {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_IFERROR      {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_INC          {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_INCLUDE      {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_INKEY        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_INPUT        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_L            {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_LABEL        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_LOG          {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_LOGOF        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_LOGON        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_MARK         {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_MENU         {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_MKDIR        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_NEXT         {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_OPENREAD     {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_OR           {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_ORDERED      {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_P            {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_PRINTER      {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_PROMPT       {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_QUIT         {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_R            {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_READ         {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_RENAME       {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_REPORT       {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
	 | OZT_T_RESET        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_RESTART      {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_RETURN       {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_RMDIR        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_S            {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_SELPRINT     {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_SEND         {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_SET          {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_SETREPLY     {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_STOP         {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_T            {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_THEN         {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_VIEWFILE     {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_W            {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_WAITFOR      {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_WAITREPLY    {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_WINDEND      {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_WINDOW       {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_WRITE        {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         | OZT_T_Z            {ozt_TokenVal.toUpper(); $$ = newValue(ozt_TokenVal);}
         ;








