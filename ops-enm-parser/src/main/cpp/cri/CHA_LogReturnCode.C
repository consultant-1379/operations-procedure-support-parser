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


#include <CHA_LogReturnCode.H>
#include <CHA_NLSCatalog.H>


//*****************************************************************************

// trace

#include <trace.H>
static std::string trace ="CHA_LogReturnCode";

//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: CHA_LogReturnCode.C,v 21.0 1996/08/23 12:40:35 ehsgrap Rel $";


//*****************************************************************************

static CHA_NLSCatalog nlsFile("/opt/ops/ops_parser/etc/nls/CHA_Log.cat");

//
//   General code
//
static int NLS_UNDEFINED = 101;
static int NLS_NO_PROBLEM = 102;
static int NLS_INTERNAL_ERR = 103;

//
//   Mail logging specific
//
static int NLS_NO_MAIL_RECIPIENT_ERR = 201;
static int NLS_MAIL_PROC_INIT_ERR = 202;
static int NLS_MAIL_LOGGING_ERR = 203;

//
//   Printer logging specific
//
static int NLS_INVALID_PRINTER = 301;

//
//   File logging specific
//
static int NLS_INVALID_LOG_FILE = 401;
static int NLS_FILE_LOGGING_ERR = 402;
static int NLS_LOG_ALREADY_OPEN = 403;
static int NLS_LOG_ID_ALREADY_USED=404;

//****************************************************************************

CHA_LogReturnCode::CHA_LogReturnCode()
{
    code = UNDEFINED;
}

//****************************************************************************

CHA_LogReturnCode::CHA_LogReturnCode(const CHA_LogReturnCode &retCode)
{
    code = retCode.code;
    info = retCode.info;
}

//****************************************************************************

CHA_LogReturnCode::CHA_LogReturnCode(const CHA_LogReturnCode::Code c)
{
    code = c;
    info = RWCString();
}

//****************************************************************************

CHA_LogReturnCode::CHA_LogReturnCode(const CHA_LogReturnCode::Code c,
                                           const RWCString &additionalInfo)
{
    code = c;
    info = additionalInfo;
}

//****************************************************************************

CHA_LogReturnCode &CHA_LogReturnCode::operator=(const CHA_LogReturnCode &c)
{
    if (this == &c)
        return *this;

    code = c.code;
    info = c.info;
    return *this;
}

//****************************************************************************

std::ostream& operator<<(std::ostream& s, const CHA_LogReturnCode& retCode)
{
    return s << retCode.toMsg();
}

//****************************************************************************

RWCString CHA_LogReturnCode::toMsg() const
{
    RWCString msg;

    switch(code)
    {
        case CHA_LogReturnCode::UNDEFINED :
             msg = nlsFile.getMessage(NLS_UNDEFINED, 
                                      "Undefined logging return code");
             break;

        case CHA_LogReturnCode::NO_PROBLEM :
             msg = nlsFile.getMessage(NLS_NO_PROBLEM,
                                      "Successful");
             break;

        case CHA_LogReturnCode::INTERNAL_ERR :
             msg = nlsFile.getMessage(NLS_INTERNAL_ERR, 
                          "Internal logging error");
             break;

        case CHA_LogReturnCode::NO_MAIL_RECIPIENT_ERR :
             msg = nlsFile.getMessage(NLS_NO_MAIL_RECIPIENT_ERR,
                          "Logging error (No mail recipients specified)");
             break;             

        case CHA_LogReturnCode::MAIL_PROC_INIT_ERR :
             msg = nlsFile.getMessage(NLS_MAIL_PROC_INIT_ERR,
                          "Logging error (Mail process initialisation failed)");
             break;

        case CHA_LogReturnCode::MAIL_LOGGING_ERR :
             msg = nlsFile.getMessage(NLS_MAIL_LOGGING_ERR,
                          "Mail logging error");
             break;

        case CHA_LogReturnCode::INVALID_PRINTER :
             msg = nlsFile.getMessage(NLS_INVALID_PRINTER,
                          "Logging error (Invalid printer selected)");
             break;

        case CHA_LogReturnCode::INVALID_LOG_FILE :
             msg = nlsFile.getMessage(NLS_INVALID_LOG_FILE,
                          "Logging error (Invalid file name)");
             break;

        case CHA_LogReturnCode::FILE_LOGGING_ERR :
             msg = nlsFile.getMessage(NLS_FILE_LOGGING_ERR,
                                      "File logging error");
             break;
    case CHA_LogReturnCode::LOG_ALREADY_OPEN:
      msg = nlsFile.getMessage(NLS_LOG_ALREADY_OPEN,
			       "Log file already open");
             break;
    case CHA_LogReturnCode::LOG_ID_ALREADY_USED:
      msg = nlsFile.getMessage(NLS_LOG_ID_ALREADY_USED,
			       "Log identification already used");
             break;
    }

    if (!info.isNull())
        msg = msg + " (" + info + ")";

    return msg;
}
