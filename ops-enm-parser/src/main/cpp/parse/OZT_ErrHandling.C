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

#include <OZT_ErrHandling.H>
#include <OZT_SourceMgr.H>
#include <OZT_Misc.H>
#include <CHA_NLSCatalog.H>
#include <CHA_UserInfo.H>
#include <rw/cstring.h>
#include <strstream>
#include <nl_types.h>


//*****************************************************************************


// trace

#include <trace.H>
static std::string trace ="OZT_ErrHandling";

//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_ErrHandling.C,v 21.0 1996/08/23 12:43:57 ehsgrap Rel $";


//*****************************************************************************
//
//  NLS Message Number
//

static CHA_NLSCatalog nlsFile("/opt/ops/ops_parser/etc/nls/OZT_ErrMsg.cat");

static int NLS_UNDEFINED  = 1;
static int NLS_NO_PROBLEM = 2;
static int NLS_SYNTAX_ERR = 3;
static int NLS_INVALID_VALUE = 4;
static int NLS_DIVISION_BY_ZERO = 5;
static int NLS_VARIABLE = 6;
static int NLS_NOT_DEFINED = 7;
static int NLS_INVALID_LINE_NO = 8;
static int NLS_HIT_EOF = 9;
static int NLS_LABEL = 10;
static int NLS_NOT_FOUND = 11;
static int NLS_RETURN_WITHOUT_GOSUB = 12;
static int NLS_NO_MATCHING_NEXT = 13;
static int NLS_NEXT_WITHOUT_MATCHING_FOR = 14;
static int NLS_FILE_OPEN_ERR = 15;
static int NLS_INTERNAL_ERR = 16;
static int NLS_NOT_IMPLEMENTED = 17;
static int NLS_FILE_NOT_LOADED = 18;
static int NLS_CYCLIC_INCLUDE_ERR = 19;
static int NLS_MEM_ALLOC_ERR = 20;
static int NLS_PROGRAM_TERMINATED = 21;
static int NLS_QUIT = 22;
static int NLS_PAUSE = 23;
static int NLS_STOP = 24;
static int NLS_FILE_HALTED = 25;
static int NLS_NO_FILE_LOADED = 26;
static int NLS_INVALID_LABEL = 27;
static int NLS_DUPLICATE_LABELS = 28;
static int NLS_FAILED = 29;
static int NLS_BUSY = 30;
static int NLS_NO_CONNECTION = 31;
static int NLS_INTERRUPTED = 32;
static int NLS_NO_EXECUTABLE_CODE = 33;
static int NLS_PROGRAM_MODIFIED = 34;
static int NLS_NO_UI_SUPPORTED = 35;
static int NLS_INHIBIT = 36;
static int NLS_CONFIRM_FAIL = 37;
static int NLS_TIME_EXPIRED = 38;
static int NLS_CONNECTION_LOST = 39;
static int NLS_NOT_ACCEPTED = 40;
static int NLS_PARTLY_EXECUTED = 41;
static int NLS_INCOMPLETE_COMMAND = 42;
static int NLS_FUNBUSY = 43;
static int NLS_REPLY_CHECK_FAIL = 45;
static int NLS_MISSING_PARAMETERS = 46;
static int NLS_EXECUTE_ERR = 47;
static int NLS_PATH_IS_DIR = 48;
static int NLS_FILE_OP_ERR = 49;
static int NLS_ES_FAILED_DISCON = 50;
static int NLS_ES_NOREACH = 51;
static int NLS_ES_UNKNOWN = 52;
static int NLS_ES_IS_EXCLUSIVE = 53;
static int NLS_ES_NOAUTH = 54;
static int NLS_ES_FAILED_CON = 55;
static int NLS_NOT_AUTHORIZED = 56;
static int NLS_SEND_FAILED = 57;
static int NLS_CENTRALDIR_NOT_DEFINED = 58;
static int NLS_PRIVATEDIR_NOT_DEFINED = 59;
static int NLS_SAVEDIR_NOT_DEFINED = 60;
static int NLS_ELSE_WITHOUT_IF = 61;
static int NLS_ITERATED_ON_SAME_VAR = 62;
static int NLS_PRINTER_LIST_UPDATE_ERR = 63;
static int NLS_NO_SUCH_PRINTER = 64;
static int NLS_DF_READING_ERR = 65;
static int NLS_FILE_LOGGING_ERR = 66;
static int NLS_DISPLAY_NOT_AVAILABLE = 67;
static int NLS_ENDIF_WITHOUT_IF = 68;
static int NLS_NO_MATCHING_ENDIF = 69;
static int NLS_COMMAND_NOT_SUPPORTED_AS_MENTRY = 70;
static int NLS_MAIL_SENDING_FAILED = 71;
static int NLS_MAIL_FILE_NOT_FOUND = 72;
static int NLS_BREAK_WITHOUT_FOR = 73;
static int NLS_DIALOG_TIMEOUT = 74;
static int NLS_NO_MATCHING_ENDSWITCH = 75;
static int NLS_CASE_WITHOUT_MATCHING_SWITCH = 76;
static int NLS_DEFAULT_WITHOUT_MATCHING_SWITCH = 77;
static int NLS_ENDSWITCH_WITHOUT_MATCHING_SWITCH = 78;
static int NLS_MAA_NOT_REACHABLE = 79;
static int NLS_DELAY_RESPONSE_NOT_RECEIVED = 80;
// WP118
static int NLS_INVALID_CHILD_SESSION_ID = 81;
static int NLS_CHILD_VARIABLE_NOT_SUBSCRIBED = 82;
static int NLS_CHILD_NOT_SUPPORTED = 83;
// END WP118
static int NLS_INVALID_NEID = 84;
static int NLS_INVALID_SESSIONID = 85;
static int NLS_INVALID_ENMUID = 86;
static int NLS_SIDE_INCORRECT = 88;
static int NLS_CP_INCORRECT = 89;
static int NLS_NOT_ALLOWED_SIDE = 90;
static int NLS_VALUE_UNREASONABLE = 91;


//*****************************************************************************

OZT_ErrHandler ozt_errHandler;   // This is the global resource for ozterm

//*****************************************************************************

OZT_Result::OZT_Result()
{
    code     = UNDEFINED;
    info     = RWCString();
    fileName = RWCString();
    lineNo   = 0;

    TRACE_FLOW(trace, OZT_Result, code);
}

OZT_Result::OZT_Result(const CHA_LogReturnCode& c)
{
    if (c.isOkay())
    {
        code = NO_PROBLEM;
        info = RWCString();
        fileName = RWCString();
        lineNo   = 0;
    }
    else
    {
        code = FAILED;
        info = c.toMsg();
        fileName = RWCString();
        lineNo   = 0;
    }
    TRACE_FLOW(trace, OZT_Result, code);
}

OZT_Result::OZT_Result(const OZT_Result& res)
{
    code     = res.code;
    info     = res.info;
    fileName = res.fileName;
    lineNo   = res.lineNo;
    TRACE_FLOW(trace, OZT_Result, code);
}


OZT_Result::OZT_Result(const OZT_Result::Code theCode)
{
    code     = theCode;
    info     = RWCString();
    fileName = RWCString();
    lineNo   = 0;
    TRACE_FLOW(trace, OZT_Result, code);
}



OZT_Result::OZT_Result(const OZT_Result::Code theCode, const RWCString& theInfo)
{
    code     = theCode;
    info     = theInfo;
    fileName = RWCString();
    lineNo   = 0;
    TRACE_FLOW(trace, OZT_Result, code);
}

OZT_Result::OZT_Result(const OZT_Result::Code theCode,
                       const RWCString& theFileName,
                       const LineNo theLineNo)
{
    code     = theCode;
    info     = RWCString();
    fileName = theFileName;
    lineNo   = theLineNo;
    TRACE_FLOW(trace, OZT_Result, code);
}

OZT_Result::OZT_Result(const OZT_Result::Code theCode,
                       const RWCString& theInfo,
                       const RWCString& theFileName,
                       const LineNo theLineNo)
{
    code     = theCode;
    info     = theInfo;
    fileName = theFileName;
    lineNo   = theLineNo;
    TRACE_FLOW(trace, OZT_Result, code);
}


//
//  When check is off, this function changes an error to non-error and
//  set the error flag.
//
OZT_Result OZT_Result::filtered() const
{
    if ((code == NO_PROBLEM) || ozt_errHandler.isCheckOn())
        return *this;
    else
    {
        ozt_errHandler.setFlag();
        return OZT_Result(OZT_Result::NO_PROBLEM);
    }
}

OZT_Result &OZT_Result::operator=(const OZT_Result& res)
{
    if (this == &res)
        return *this;

    code     = res.code;
    info     = res.info;
    fileName = res.fileName;
    lineNo   = res.lineNo;
    return *this;
}


RWCString OZT_Result::toMsg() const
{
	RWCString str;
   // TRACE_FLOW(trace, OZT_Result, code);
    switch(code)
    {
    case OZT_Result::UNDEFINED :
      return nlsFile.getMessage(NLS_UNDEFINED, "Undefined Error Code");

    case OZT_Result::NO_PROBLEM :
      return nlsFile.getMessage(NLS_NO_PROBLEM, "Successful");


    case OZT_Result::DELAY_RESPONSE_NOT_RECEIVED :
      return nlsFile.getMessage(NLS_DELAY_RESPONSE_NOT_RECEIVED, "Delay Response not received");

    case OZT_Result::SYNTAX_ERR :
      return nlsFile.getMessage(NLS_SYNTAX_ERR, "Syntax Error");

    case OZT_Result::INVALID_VALUE :
             return nlsFile.getMessage(NLS_INVALID_VALUE, "Invalid Parameter");

    case OZT_Result::DIVISION_BY_ZERO :
      return nlsFile.getMessage(NLS_DIVISION_BY_ZERO,
				"Divide By Zero Error");

    case OZT_Result::VAR_UNDEFINED :
      return nlsFile.getMessage(NLS_VARIABLE, "Variable") +
	" \"" + info + "\" " +
	nlsFile.getMessage(NLS_NOT_DEFINED, "Not Defined");

    case OZT_Result::INVALID_LINE_NO :
      return nlsFile.getMessage(NLS_INVALID_LINE_NO,
				"Invalid Line Number");

    case OZT_Result::HIT_EOF :
      return nlsFile.getMessage(NLS_HIT_EOF, "Hit End Of File");

    case OZT_Result::LABEL_NOT_FOUND :
      return nlsFile.getMessage(NLS_LABEL, "Label") +
	" \"" + info + "\" " +
	nlsFile.getMessage(NLS_NOT_FOUND, "Not Found");

    case OZT_Result::RETURN_WITHOUT_GOSUB :
      return nlsFile.getMessage(NLS_RETURN_WITHOUT_GOSUB,
				"Return Without Gosub");

    case OZT_Result::NO_MATCHING_NEXT :
      return nlsFile.getMessage(NLS_NO_MATCHING_NEXT,
				"No Matching @NEXT Statement");
    case OZT_Result::ENDIF_WITHOUT_IF :
             return nlsFile.getMessage(NLS_ENDIF_WITHOUT_IF,
                                       "No Matching @IF Statement");
    case OZT_Result::BREAK_WITHOUT_FOR:
      return nlsFile.getMessage(NLS_BREAK_WITHOUT_FOR,
				"No Matching @FOR statement");
    case OZT_Result::NO_MATCHING_ENDIF :
      return nlsFile.getMessage(NLS_NO_MATCHING_ENDIF,
				"No Matching @ENDIF Statement");

    case OZT_Result::NEXT_WITHOUT_MATCHING_FOR :
      return nlsFile.getMessage(NLS_NEXT_WITHOUT_MATCHING_FOR,
				"No Matching @FOR Statement");

    case OZT_Result::FILE_OPEN_ERR :
      return nlsFile.getMessage(NLS_FILE_OPEN_ERR, "File Open Error")
	+ " (" + info + ")";

    case OZT_Result::INTERNAL_ERR :
      return nlsFile.getMessage(NLS_INTERNAL_ERR, "Internal Error")
	+ " (" + info + ")";

    case OZT_Result::NOT_IMPLEMENTED :
      return nlsFile.getMessage(NLS_NOT_IMPLEMENTED, "Not Implemented");

    case OZT_Result::FILE_NOT_LOADED :
      return nlsFile.getMessage(NLS_FILE_NOT_LOADED, "File Not Loaded");

    case OZT_Result::CYCLIC_INCLUDE_ERR :
      return nlsFile.getMessage(NLS_CYCLIC_INCLUDE_ERR,
				"Cyclic Include Error");

    case OZT_Result::MEM_ALLOC_ERR :
      return nlsFile.getMessage(NLS_MEM_ALLOC_ERR,
				"Memory Allocation Error");

    case OZT_Result::PROGRAM_TERMINATED :
      return nlsFile.getMessage(NLS_PROGRAM_TERMINATED,
				"Normal Program Termination");

    case OZT_Result::PAUSE :
      return nlsFile.getMessage(NLS_PAUSE, "Execution Paused");

    case OZT_Result::QUIT :
      return nlsFile.getMessage(NLS_QUIT, "Quit");

    case OZT_Result::STOP :
      return nlsFile.getMessage(NLS_STOP, "Program Stopped");

    case OZT_Result::FILE_HALTED :
      return nlsFile.getMessage(NLS_FILE_HALTED, "File Halted");

    case OZT_Result::NO_FILE_LOADED :
      return nlsFile.getMessage(NLS_NO_FILE_LOADED, "No File Loaded");

    case OZT_Result::FAILED :
      return info;
      // return nlsFile.getMessage(NLS_FAILED, "Failed") + ": " + info;

    case OZT_Result::BUSY :
      return nlsFile.getMessage(NLS_BUSY, "Busy");

    case OZT_Result::NO_CONNECTION :
      return nlsFile.getMessage(NLS_NO_CONNECTION, "No Connection");

    case OZT_Result::INVALID_LABEL    :
             return nlsFile.getMessage(NLS_INVALID_LABEL,
				       "Invalid Label Name Found in ") +
	       fileName;

    case OZT_Result::DUPLICATE_LABELS :
      return nlsFile.getMessage(NLS_DUPLICATE_LABELS, "Duplicated Label")
	+ " \"" + info + "\" ";

    case OZT_Result::INTERRUPTED :
      return nlsFile.getMessage(NLS_INTERRUPTED, "User interrupted");

    case OZT_Result::PROGRAM_MODIFIED :
      return nlsFile.getMessage(NLS_PROGRAM_MODIFIED,"Program Modified");

    case OZT_Result::NO_UI_SUPPORTED :
      return nlsFile.getMessage(NLS_NO_UI_SUPPORTED,
				"No User Interface Supported");

    case OZT_Result::NO_EXECUTABLE_CODE :
      return nlsFile.getMessage(NLS_NO_EXECUTABLE_CODE,
				"No Executable Code in")
	+ " \"" + info + "\" ";

    case OZT_Result::INHIBIT :
      return nlsFile.getMessage(NLS_INHIBIT, "Confirmation Inhibited");

    case OZT_Result::CONFIRM_FAIL :
      return nlsFile.getMessage(NLS_CONFIRM_FAIL, "Confirmation Failed");

    case OZT_Result::TIME_EXPIRED :
      return nlsFile.getMessage(NLS_TIME_EXPIRED, "Time Out");

    case OZT_Result::CONNECTION_LOST :
      return nlsFile.getMessage(NLS_CONNECTION_LOST, "Connection Lost");

    case OZT_Result::NOT_ACCEPTED :
      return nlsFile.getMessage(NLS_NOT_ACCEPTED, "Not Accepted");

    case OZT_Result::PARTLY_EXECUTED :
      return nlsFile.getMessage(NLS_PARTLY_EXECUTED, "Partly Executed");

    case OZT_Result::INCOMPLETE_COMMAND :
      return nlsFile.getMessage(NLS_INCOMPLETE_COMMAND,
				"Incomplete Command");

    case OZT_Result::FUNBUSY :
      return nlsFile.getMessage(NLS_FUNBUSY, "Function Busy");

    case OZT_Result::REPLY_CHECK_FAIL :
      if (info.isNull())
	return nlsFile.getMessage(NLS_REPLY_CHECK_FAIL,
				  "Reply Check Failed");
      else
	return nlsFile.getMessage(NLS_REPLY_CHECK_FAIL,
				  "Reply Check Failed")
	  + " (\"" + info + "\" found)";

    case OZT_Result::MISSING_PARAMETERS :
      return nlsFile.getMessage(NLS_MISSING_PARAMETERS,
				"Missing Parameter(s)");

    case OZT_Result::EXECUTE_ERR :
      return nlsFile.getMessage(NLS_EXECUTE_ERR,
				"Cannot Execute External Program");

    case OZT_Result::PATH_IS_DIR :
      return nlsFile.getMessage(NLS_PATH_IS_DIR,
				"The path is a directory");

    case OZT_Result::FILE_OP_ERR :
      return nlsFile.getMessage(NLS_FILE_OP_ERR,
				"File operation failed");

    case OZT_Result::ES_FAILED_DISCON :
      return nlsFile.getMessage(NLS_ES_FAILED_DISCON,
				"Disconnection failed");

    case OZT_Result::ES_NOREACH :
      return nlsFile.getMessage(NLS_ES_NOREACH,
				"External system not reachable");

    case OZT_Result::ES_UNKNOWN :
      return nlsFile.getMessage(NLS_ES_UNKNOWN,
				"Unknown external system");

    case OZT_Result::ES_IS_EXCLUSIVE :
      return nlsFile.getMessage(NLS_ES_IS_EXCLUSIVE,
				"External system is in exclusive use");

    case OZT_Result::ES_NOAUTH :
      return nlsFile.getMessage(NLS_ES_NOAUTH,
				"Not authorized to connect to external system");

    case OZT_Result::ES_FAILED_CON :
      return nlsFile.getMessage(NLS_ES_FAILED_CON,
				"Unable to connect to the external system");

    case OZT_Result::NOT_AUTHORIZED :
      return nlsFile.getMessage(NLS_NOT_AUTHORIZED,
				"Not authorized to send the command");

    case OZT_Result::SEND_FAILED :
      return nlsFile.getMessage(NLS_SEND_FAILED,
				"Cannot send the command");

    case OZT_Result::CENTRALDIR_NOT_DEFINED :
      return nlsFile.getMessage(NLS_CENTRALDIR_NOT_DEFINED,
				"Central directory is not defined in the PDB map");

    case OZT_Result::PRIVATEDIR_NOT_DEFINED :
      return nlsFile.getMessage(NLS_PRIVATEDIR_NOT_DEFINED,
				"Private directory is not defined in the environment");

    case OZT_Result::SAVEDIR_NOT_DEFINED :
      return nlsFile.getMessage(NLS_SAVEDIR_NOT_DEFINED,
				"Save directory is not defined in the environment");

    case OZT_Result::ELSE_WITHOUT_IF :
      return nlsFile.getMessage(NLS_ELSE_WITHOUT_IF,
				"No preceding @IF-THEN or @IFERROR-THEN statement");

    case OZT_Result::ITERATED_ON_SAME_VAR :
      return nlsFile.getMessage(NLS_ITERATED_ON_SAME_VAR,
				"Nested for-loop on the same variable");

    case OZT_Result::PRINTER_LIST_UPDATE_ERR :
      return nlsFile.getMessage(NLS_PRINTER_LIST_UPDATE_ERR,
				"Printer list update error");

    case OZT_Result::NO_SUCH_PRINTER :
      return nlsFile.getMessage(NLS_NO_SUCH_PRINTER,
				"Invalid printer");

    case OZT_Result::DF_READING_ERR :
      return nlsFile.getMessage(NLS_DF_READING_ERR,
				"Fail to find the disk space left");

    case OZT_Result::FILE_LOGGING_ERR :
      return nlsFile.getMessage(NLS_FILE_LOGGING_ERR,
				"File logging error") + " (" + info + ")";

    case OZT_Result::DISPLAY_NOT_AVAILABLE :
      return nlsFile.getMessage(NLS_DISPLAY_NOT_AVAILABLE,
				"X display information not available");
    case OZT_Result::COMMAND_NOT_SUPPORTED_AS_MENTRY:
      return nlsFile.getMessage( NLS_COMMAND_NOT_SUPPORTED_AS_MENTRY,
				 "Command not supported in the Manual Entry window" );
    case OZT_Result::MAIL_SENDING_FAILED:
      return nlsFile.getMessage( NLS_MAIL_SENDING_FAILED,
				 "Can't send the mail; check the address" );
    case OZT_Result::MAIL_FILE_NOT_FOUND:
      return nlsFile.getMessage( NLS_MAIL_FILE_NOT_FOUND,
				 "Can't open the file to be sent" );
    case OZT_Result::DIALOG_TIMEOUT:
      return nlsFile.getMessage( NLS_DIALOG_TIMEOUT,
				 "Dialog timeout" );
    case OZT_Result::NO_MATCHING_ENDSWITCH:
      return nlsFile.getMessage( NLS_NO_MATCHING_ENDSWITCH,
				 "No matching @ENDSWITCH command" );
    case OZT_Result::CASE_WITHOUT_MATCHING_SWITCH:
      return nlsFile.getMessage( NLS_CASE_WITHOUT_MATCHING_SWITCH,
				 "@CASE without matching @SWITCH" );
    case OZT_Result::DEFAULT_WITHOUT_MATCHING_SWITCH:
      return nlsFile.getMessage( NLS_DEFAULT_WITHOUT_MATCHING_SWITCH,
				 "@DEFAULT without matching @SWITCH" );
    case OZT_Result::ENDSWITCH_WITHOUT_MATCHING_SWITCH:
      return nlsFile.getMessage( NLS_ENDSWITCH_WITHOUT_MATCHING_SWITCH,
				 "@ENDSWITCH without matching @SWITCH" );
    case OZT_Result::MAA_NOT_REACHABLE:
      return nlsFile.getMessage( NLS_MAA_NOT_REACHABLE,
				 "MAA is not reachable." );
    case OZT_Result::INVALID_NODE_ID:
      return nlsFile.getMessage( NLS_INVALID_NEID,
                                 "Invalid NeID" );

    case OZT_Result::INVALID_SESSIONID_VAL:
      return nlsFile.getMessage( NLS_INVALID_SESSIONID,
                                 "Invalid SessionID" );

    case OZT_Result::INVALID_ENMUID_VAL:
      return nlsFile.getMessage( NLS_INVALID_ENMUID,
                                 "Invalid EnmUID" );

    case OZT_Result::SIDE_INCORRECT:
      return nlsFile.getMessage( NLS_SIDE_INCORRECT,
                                 "Side not defined" );

    case OZT_Result::CP_INCORRECT:
      return nlsFile.getMessage( NLS_CP_INCORRECT,
                                 "Illegal CP" );

    case OZT_Result::NOT_ALLOWED_SIDE:
      return nlsFile.getMessage( NLS_NOT_ALLOWED_SIDE,
                                 "Side not allowed" );

    case OZT_Result::VALUE_UNREASONABLE:
      return nlsFile.getMessage( NLS_VALUE_UNREASONABLE,
                                 "Unreasonable Value" );

// WP118
	  case OZT_Result::INVALID_CHILD_SESSION_ID :
	    return nlsFile.getMessage(NLS_INVALID_CHILD_SESSION_ID, "The specified child session ID is invalid");
	  case OZT_Result::CHILD_VARIABLE_NOT_SUBSCRIBED :
	    return nlsFile.getMessage(NLS_CHILD_VARIABLE_NOT_SUBSCRIBED, "There is no subscription to the variable");
	  case OZT_Result::CHILD_NOT_SUPPORTED :
	    return nlsFile.getMessage(NLS_CHILD_NOT_SUPPORTED, "A child script may not create or access other child scripts");
// END WP118


    default:
      return "OZT_ErrHandling: Unknown Result code";
    }
}

//****************************************************************************

RWCString ozt_formatReport(const  RWCString& filename,
                           const  RWCString& startLabel,
                           const  RWCString& es,
                           const  RWCString& msg,
                           OZT_SourceMgr* pSourceMgr)
{
    extern RWCString ozt_taskid;      // global, declared in the main prog.
    extern RWCString ozt_schedTime;   // same here
    RWCString formatted;
    strstream s;
    CHA_UserInfo userInfo;
    time_t td = time(0);

    s << "------------------------------------------------------\n";
    s << "           Command file execution report              \n";
    s << "------------------------------------------------------\n";
    s << "Date         : " << ctime(&td);
    s << "User         : " << userInfo.loginName()
                           << " (" << userInfo.fullName() << ")" << "\n";

    if (!ozt_taskid.isNull())
        s << "ELB id       : " << ozt_taskid << "\n";

/*  comment this out because it is not correct for repeated orders
    if (ozt_schedTime != "0")
        s << "Scheduled at : " << ozt_schedTime << endl;
*/

    if (!filename.isNull())
        s << "Start file   : " << filename << "\n";

    if (!startLabel.isNull())
        s << "Start label  : " << startLabel << "\n";

    if (!es.isNull())
        s << "Ext System   : " << es << "\n";


    if (pSourceMgr != 0)
    {
        // Format the status of the source manager
        RWCString  extSys;
        RWCString  cmdFile;
        LineNo     lineNo;
        LineNo     dummy;

        pSourceMgr->getCurrPos(cmdFile, lineNo, dummy);
        extSys = pSourceMgr->getCmdSender().getEsName();

        if (!cmdFile.isNull())
            s << "Stopped at   : " << cmdFile << " (line " << lineNo+1
                                   << ")" << "\n";
        if (extSys.isNull())
            s << "ES at exit   : (NONE)" << "\n";
        else
            s << "ES at exit   : " << extSys << "\n";

    }

    s << "Description  : " << msg << "\n";
    s << ends; // better safe than sorry

    formatted = s.str();
    delete [] s.str();

    return formatted;
}

//****************************************************************************

RWCString ozt_formatReport(const  RWCString& filename,
                           const  RWCString& startLabel,
                           const  RWCString& es,
			   const  RWCString &sessionId,
                           const  RWCString& msg,
                           OZT_SourceMgr* pSourceMgr)
{
    extern RWCString ozt_taskid;      // global, declared in the main prog.
    extern RWCString ozt_schedTime;   // same here
    RWCString formatted;
    strstream s;
    CHA_UserInfo userInfo;
    time_t td = time(0);

    s << "------------------------------------------------------\n";
    s << "           Command file execution report              \n";
    s << "------------------------------------------------------\n";
    s << "Date         : " << ctime(&td);
    s << "Session id   : " << sessionId << "\n";
    s << "User         : " << userInfo.loginName()
                           << " (" << userInfo.fullName() << ")" << "\n";

    if (!ozt_taskid.isNull())
        s << "ELB id       : " << ozt_taskid << "\n";

/*  comment this out because it is not correct for repeated orders
    if (ozt_schedTime != "0")
        s << "Scheduled at : " << ozt_schedTime << endl;
*/

    if (!filename.isNull())
        s << "Start file   : " << filename << "\n";

    if (!startLabel.isNull())
        s << "Start label  : " << startLabel << "\n";

    if (!es.isNull())
        s << "Ext System   : " << es << "\n";


    if (pSourceMgr != 0)
    {
        // Format the status of the source manager
        RWCString  extSys;
        RWCString  cmdFile;
        LineNo     lineNo;
        LineNo     dummy;

        pSourceMgr->getCurrPos(cmdFile, lineNo, dummy);
        extSys = pSourceMgr->getCmdSender().getEsName();

        if (!cmdFile.isNull())
            s << "Stopped at   : " << cmdFile << " (line " << lineNo+1
                                   << ")" << "\n";
        if (extSys.isNull())
            s << "ES at exit   : (NONE)" << "\n";
        else
            s << "ES at exit   : " << extSys << "\n";

    }

    s << "Description  : " << msg << "\n";
    s << ends; // better safe than sorry

    formatted = s.str();
    delete [] s.str();

    return formatted;
}
//****************************************************************************

ostream& operator<<(ostream& s, const OZT_Result& res)
{
    return s << res.toMsg();
}
