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

#ifndef OZT_ERRHANDLING_H
#define OZT_ERRHANDLING_H

#include <iostream>
#include <cstring>
#include <nl_types.h>
#include <CHA_LogReturnCode.H>
#include <OZT_Def.H>

using namespace std;
class OZT_SourceMgr;  // forward declaration

//*****************************************************************************
//
//   The following function produce a formatted execution report
//   that you see from mail or from the output of the NUI version.
//

extern RWCString ozt_formatReport(const RWCString &filename,
                                  const RWCString &startLabel,
                                  const RWCString &es,
                                  const RWCString &msg,
                                  OZT_SourceMgr *pSourceMgr = 0);

extern RWCString ozt_formatReport(const RWCString &filename,
                                  const RWCString &startLabel,
                                  const RWCString &es,
				  const RWCString &sessionId,
                                  const RWCString &msg,
                                  OZT_SourceMgr *pSourceMgr = 0);



//*****************************************************************************
//    The following defines the error handler class. A static instance
//    of this class is declared in the corresponding .C file.
//*****************************************************************************

class OZT_ErrHandler {
public:
    OZT_ErrHandler() {errFlag = FALSE; checking = TRUE;}
    void  setFlag() {errFlag = TRUE;}
    void  clearFlag() {errFlag = FALSE;}
    void  checkOn() {checking = TRUE;}
    void  checkOff() {checking = FALSE;}
    void  reset() {errFlag = FALSE; checking = TRUE;}
    RWBoolean  isFlagSet() {return errFlag;}
    RWBoolean  isCheckOn() {return checking;}
    RWBoolean  isCheckOff() {return checking;}

private:
    RWBoolean errFlag;
    RWBoolean checking;
};

extern OZT_ErrHandler ozt_errHandler;

//****************************************************************************

class OZT_Result {
public:
    enum Code {UNDEFINED,

               NO_PROBLEM,
               SYNTAX_ERR,
               INVALID_VALUE,
               DIVISION_BY_ZERO,
               VAR_UNDEFINED,

               INVALID_LINE_NO,
               HIT_EOF,
               LABEL_NOT_FOUND,
               RETURN_WITHOUT_GOSUB,
               NO_MATCHING_NEXT,
               NEXT_WITHOUT_MATCHING_FOR,
	       ENDIF_WITHOUT_IF,
	       NO_MATCHING_ENDIF,
               FILE_OPEN_ERR,
	       BREAK_WITHOUT_FOR,
               INTERNAL_ERR,
               NOT_IMPLEMENTED,

	       NO_MATCHING_ENDSWITCH,
	       CASE_WITHOUT_MATCHING_SWITCH,
	       DEFAULT_WITHOUT_MATCHING_SWITCH,
	       ENDSWITCH_WITHOUT_MATCHING_SWITCH,

               FILE_NOT_LOADED,
               INCLUDE_NOT_EXECUTED,
               CYCLIC_INCLUDE_ERR,
               MEM_ALLOC_ERR,

               PROGRAM_TERMINATED,
               QUIT,
               PAUSE,
               STOP,
               FILE_HALTED,

               NO_FILE_LOADED,

               INVALID_LABEL,
               DUPLICATE_LABELS,

               FAILED,
               BUSY,
               NO_CONNECTION,

               INTERRUPTED,
               NO_EXECUTABLE_CODE,
               PROGRAM_MODIFIED,

               INHIBIT,
               CONFIRM_FAIL,
               TIME_EXPIRED,
               CONNECTION_LOST,
               NOT_ACCEPTED,
               PARTLY_EXECUTED,
               INCOMPLETE_COMMAND,
               FUNBUSY,
               REPLY_CHECK_FAIL,
               MISSING_PARAMETERS,
               EXECUTE_ERR,
               NO_UI_SUPPORTED,

               //
               //   error code related to file system access
               //
               PATH_IS_DIR,
               FILE_OP_ERR,

               //
               //   CHALIB connection return codes
               //
               ES_FAILED_DISCON,
               ES_NOREACH,
               ES_UNKNOWN,
               ES_IS_EXCLUSIVE,
               ES_NOAUTH,
               ES_FAILED_CON,

               //
               //
               NOT_AUTHORIZED,
               SEND_FAILED,

               CENTRALDIR_NOT_DEFINED,
               PRIVATEDIR_NOT_DEFINED,
               SAVEDIR_NOT_DEFINED,

               ELSE_WITHOUT_IF,
               ITERATED_ON_SAME_VAR,
               PRINTER_LIST_UPDATE_ERR,
               NO_SUCH_PRINTER,
               DF_READING_ERR,

               FILE_LOGGING_ERR,
               DISPLAY_NOT_AVAILABLE,

	       // Manual entry errors
	       COMMAND_NOT_SUPPORTED_AS_MENTRY,

	       DIALOG_TIMEOUT,
	       MAIL_SENDING_FAILED,
	       MAIL_FILE_NOT_FOUND,

	       // MAA
	       MAA_NOT_REACHABLE,

	       // Added due improvement of DR handling
	       DELAY_RESPONSE_NOT_RECEIVED,

	       // WP118
	       INVALID_CHILD_SESSION_ID,
	       CHILD_VARIABLE_NOT_SUBSCRIBED,
	       CHILD_NOT_SUPPORTED,
	       NOT_ALLOWED_IN_CHILD_SCRIPTS,
	       INVALID_NODE_ID,
	       INVALID_SESSIONID_VAL,
	       INVALID_ENMUID_VAL,
	       COULD_NOT_CONNECT_TO_EXT_SYSTEM,
               SIDE_INCORRECT,
               CP_INCORRECT,
               NOT_ALLOWED_SIDE,
               VALUE_UNREASONABLE
              };

    OZT_Result();
    OZT_Result(const CHA_LogReturnCode &code);
    OZT_Result(const OZT_Result &res);
    OZT_Result(const OZT_Result::Code);
    OZT_Result(const OZT_Result::Code, const RWCString &info);
    OZT_Result(const OZT_Result::Code,
               const RWCString &fileName, const LineNo lineNo);
    OZT_Result(const OZT_Result::Code, const RWCString &info,
               const RWCString &fileName, const LineNo lineNo);
    // Description
    //     Constructors in various forms.
    // Parameter
    //     code      IN: the result
    //     info      IN: additional information about the result

    OZT_Result filtered() const;
    // Description
    //     This function does nothing if the current instance contains
    //     NO_PROBLEM, or if the CHECK status contained in the error
    //     handler is ON.
    //     Otherwise, the error flag in the error handler is set to
    //     TRUE and the result code is filtered to NO_PROBLEM.

    OZT_Result &operator=(const OZT_Result &res);
    // Description
    //     Assignment operator.

    RWCString  toMsg() const;
    // Description
    //     Return a string representation of the result object.

    friend ostream& operator<<(ostream& s, const OZT_Result& res);
    // Description
    //     Overloaded function for printing a result object to a stream.

    Code       code;
    RWCString  info;
    RWCString  fileName;
    LineNo     lineNo;
};

#endif
