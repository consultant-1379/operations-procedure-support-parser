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

#include <OZT_RunTimeNLS.H>


//*****************************************************************************


// trace
#include <trace.H>
//static CAP_TRC_trace trace = CAP_TRC_DEF(((char*)"OZT_RunTimeNLS"), ((char*)"C"));

//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_RunTimeNLS.C,v 21.0 1996/08/23 12:44:39 ehsgrap Rel $";


//*****************************************************************************


//
//  The NLS file name
//
const char *OZT_RUN_TIME_NLS = "/opt/ops/ops_parser/etc/nls/OZT_RunTime.cat";

//
//  The catalog object
//
CHA_NLSCatalog ozt_nlsCatalog(OZT_RUN_TIME_NLS);

//
//  OZT_Clock related messages
//
const int OZT_NLS_TIME_TO_DELAY = 11;
const int OZT_NLS_MINS = 12;
const int OZT_NLS_SECS = 13;

//
//  OZT_FileSelector messages
//
const int OZT_NLS_FILE_SELECTION = 21;
const int OZT_NLS_DIRECTORY = 22;
const int OZT_NLS_FILE = 23;
const int OZT_NLS_SELECT = 24;
const int OZT_NLS_CANCEL = 25;
const int OZT_NLS_GOUPONE = 26;
const int OZT_NLS_SELECT_A_FILE = 27;

//
//  OZT_InputWin messages
//
const int OZT_NLS_INPUT = 31;
const int OZT_NLS_ENTER = 32;
const int OZT_NLS_ENTER_PROMPT1 = 33;
const int OZT_NLS_ENTER_PROMPT2 = 34;

//
//  OZT_FileViewer messages
//
const int OZT_NLS_FILE_VIEWER = 41;

//
//  OZT_XvIOW messages
//
const int OZT_NLS_IOW = 51;

//
//  OZT_Prompt messages
//
const int OZT_NLS_CONTINUE_EXECUTION = 61;
const int OZT_NLS_CONTINUE = 62;
const int OZT_NLS_STOP = 63;
const int OZT_NLS_STOP_N_QUIT = 64;

//
//  Error messages coming from the main program
//
const int OZT_NLS_ELB_TASK_ID_MISSING = 100;
const int OZT_NLS_THE_FILE = 101;
const int OZT_NLS_CANNOT_BE_ACCESSED = 102;
const int OZT_NLS_FAIL_TO_INIT = 103;
const int OZT_NLS_FAIL_TO_EXECUTE = 104;
const int OZT_NLS_CHA_ENV_ERROR = 105;
const int OZT_NLS_NO_SUCH_PRINTER = 106;
const int OZT_NLS_NO_TEXT = 107;
const int OZT_NLS_STEP_CANT_INCLUDE = 108;
const int OZT_NLS_CANT_INCLUDE = 109;
const int OZT_NLS_FILE_OPEN_ERROR = 110;
const int OZT_NLS_CANNOT_SET_USER = 111;
const int OZT_NLS_CANNOT_CD = 112;
const int OZT_NLS_OUT_OF_MEMORY = 113;
const int OZT_NLS_NO_FILE_LOADED = 114;
const int OZT_NLS_MAX_FILES = 115;
const int OZT_NLS_SESSION_READ_ERROR = 116;
const int OZT_WRONG_USER = 117;
const int OZT_NO_PERM_CLIENTCHANGE = 118;
const int OZT_IS_DISCONNECTED = 119;
const int OZT_IS_CONNECTED = 120;
const int OZT_INCORRECT_PWD = 121;

//
//  Startup messages
//
const int OZT_NLS_INITIALISING = 201;
const int OZT_NLS_CHECKING_ELB_AUTH = 202;
const int OZT_NLS_INITIALISING_USER_INTERFACE = 203;
const int OZT_NLS_CONNECTING = 204;
const int OZT_NLS_INITIALISING_CAP_IPC = 205;
const int OZT_NLS_CMD_SENDER_INITIALISED = 206;
const int OZT_NLS_INTERPRETER_INITIALISED = 207;

//
//  Main program messages
//
const int OZT_NLS_STEP_IN_PROGRESS = 301;
const int OZT_NLS_STEP_INTERRUPTED = 302;
const int OZT_NLS_STEP = 303;
const int OZT_NLS_RUNNING_FROM_TOP = 304;
const int OZT_NLS_RUNNING_TAGS = 305;
const int OZT_NLS_NO_TAGS = 306;
const int OZT_NLS_RUNNING = 307;
const int OZT_NLS_RUN_STOP_BREAKPOINT = 308;
const int OZT_NLS_RUN_STOP_INTERRUPT = 309;
const int OZT_NLS_RUN_STOP = 310;
const int OZT_NLS_NOT_UPTODATE = 311;
const int OZT_NLS_INCLUDED_LINES_EXECUTED = 312;

const int OZT_NLS_NO_CHA_DIRECTORIES = 313;
const int OZT_NLS_APCONNECT = 314;
