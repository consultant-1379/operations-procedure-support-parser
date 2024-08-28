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


#include <sys/wait.h>
#include <CHA_MailLogger.H>
#include <CHA_Pipe.H>


//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="CHA_MailLogger";


//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: CHA_MailLogger.C,v 21.0 1996/08/23 12:40:42 ehsgrap Rel $";


//*****************************************************************************

const RWCString CHA_MailLogger::defaultSubject("Command file execution log");

//*****************************************************************************

CHA_MailLogger::CHA_MailLogger(CHA_LogSource &source,
                               CHA_EventHandler *cleaner)
: CHA_LoggerPipe(source, cleaner)
{
    TRACE_IN(trace, CHA_MailLogger, "");

    TRACE_OUT(trace, CHA_MailLogger, "");
}

//*****************************************************************************

CHA_MailLogger::~CHA_MailLogger()
{
    (void)off();
}

//*****************************************************************************

CHA_LogReturnCode CHA_MailLogger::setRecipients(const RWCString &users,
                                                const RWCString &subjectText)
{
    TRACE_IN(trace, setRecipients, users);

    if (users.isNull())
    {
        TRACE_RETURN(trace, setRecipients, "No Mail recipient error");
        return CHA_LogReturnCode(CHA_LogReturnCode::NO_MAIL_RECIPIENT_ERR);
    }
    // need more validation

    recipients = users;
    subject = subjectText;

    // if logging is already on, turn it off and on again to switch users

    CHA_LogReturnCode result(CHA_LogReturnCode::NO_PROBLEM);

    if (isLoggingOn())
    {
        result = off();
        if (result.isOkay())
            result = on();
    }

    TRACE_RETURN(trace, setRecipients, result);
    return result;
}

//*****************************************************************************

CHA_LogReturnCode CHA_MailLogger::on()
{
    TRACE_IN(trace, on, recipients);

    if (recipients.isNull())
    {
        TRACE_RETURN(trace, on, "No Mail recipient error");
        return CHA_LogReturnCode(CHA_LogReturnCode::NO_MAIL_RECIPIENT_ERR);
    }

    // get smtp server (lvsrouter entry from /ericsson/tor/data/global.properties)
    RWCString smtpAddr = getenv("OPS_SMTP_SERVER");
    smtpAddr = (RWCString)"smtp=" + smtpAddr;

    char * argv[7];
    argv[0] = (char *)"mailx";
    argv[1] = (char *)"-S";
    argv[2] = (char *)(smtpAddr.data());
    argv[3] = (char *)"-s";
    argv[4] = (char *)(subject.data());
    argv[5] = (char *)(recipients.data());
    argv[6] = 0;

    setCmdStr(argv);
    CHA_LogReturnCode result = turnOn();


    TRACE_RETURN(trace, on, result);
    return result;
}

//*****************************************************************************

CHA_LogReturnCode CHA_MailLogger::shutDownPipe()
{
    TRACE_IN(trace, shutDownPipe, "");

    RWCString message;

    if ((pPipe != 0) && (pPipe->status() == CHA_Pipe::OKAY))
        pPipe->closeSending();

    // check if the mail program has anything to say, normally none.
    message.readFile(pPipe->receive());
    delete pPipe;
    pPipe = 0;

    if (!message.isNull())
    {
        TRACE_RETURN(trace, shutDownPipe, message);
        return CHA_LogReturnCode(CHA_LogReturnCode::MAIL_LOGGING_ERR, message);
    }
    else
    {
        TRACE_RETURN(trace, shutDownPipe, "NO_PROBLEM");
        return CHA_LogReturnCode(CHA_LogReturnCode::NO_PROBLEM);
    }
}

//*****************************************************************************

CHA_LogReturnCode CHA_MailLogger::off()
{
    TRACE_IN(trace, off, "");

    CHA_LogReturnCode result = turnOff();

    TRACE_OUT(trace, off, result);
    return result;
}
