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


#include <time.h>
#include <fstream>
#include <rw/rwfile.h>
#include <rw/ctoken.h>
#include <rw/tvordvec.h>
#include <rw/cstring.h>
#include <OZT_Mail.H>
#include <OZT_EventHandler.H>
#include <CHA_Pipe.H>


//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_Mail";


//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_Mail.C,v 21.0 1996/08/23 12:44:15 ehsgrap Rel $";


//*****************************************************************************

extern OZT_EventHandler* ozt_evHandlerPtr;

//*****************************************************************************


OZT_Mail::OZT_Mail()
{
    TRACE_IN(trace, OZT_Mail, "");

    TRACE_OUT(trace, OZT_Mail, "");
}

//*****************************************************************************

OZT_Mail::~OZT_Mail()
{
}

//*****************************************************************************
OZT_Result OZT_Mail::sendFile(const RWCString& mailSubject,
			      const RWCString& filePath,
			      const RWCString& mailAddress ){
  
  OZT_Result result( OZT_Result::NO_PROBLEM );
  TRACE_IN(trace, sendFile, "file :" << filePath << ", mailAddress :" << mailAddress);
  
  ifstream file( filePath.data() );

  if( file.fail() ){
    result = OZT_Result( OZT_Result::MAIL_FILE_NOT_FOUND );
  }
  else {
  
    RWCString message;
    message.readFile( file );
    
    result = sendMail(mailSubject, message, mailAddress);
    
  }

  TRACE_RETURN( trace, sendFile, result );
  return result; 
}
//*****************************************************************************

OZT_Result OZT_Mail::sendMail(const RWCString& mailText, 
                             const RWCString& mailAddress) 
{
    TRACE_IN(trace, sendMail, "mailText :" << mailText
                           << ", mailAddress :" << mailAddress);

    return sendMail(RWCString(), mailText, mailAddress);
}

//*****************************************************************************

OZT_Result OZT_Mail::sendMail(const RWCString& mailText, 
                             const RWTValOrderedVector<RWCString>& mailAddresses)
{
    TRACE_IN(trace, sendMail, "mailText :" << mailText);

    return sendMail(RWCString(), mailText, mailAddresses);
}

//*****************************************************************************

OZT_Result OZT_Mail::sendMail(const RWCString& mailSubject,
                             const RWCString& mailText, 
                             const RWCString& mailAddress) 
{
    TRACE_IN(trace, sendMail, "mailSubject :" << mailSubject
                          << " ,mailAddress :" << mailAddress);

    if (mailAddress.isNull())
    {
        TRACE_OUT(trace, sendMail, "mail address not specified");
        return OZT_Result( OZT_Result::MAIL_SENDING_FAILED );
    }

    RWCString command;
    RWCString subject;
    
    if (!mailSubject.isNull())
    {
        RWCTokenizer next(mailSubject);
        RWCString token;
        while (!(token=next()).isNull())
            subject = subject + "_" + token;

        subject = subject.remove(0, 1);
        subject = " -s " + subject + " ";
    }
    else
    {
        subject = " ";
    }

    // get smtp server (lvsrouter entry from /ericsson/tor/data/global.properties)
    RWCString smtpAddr = getenv("OPS_SMTP_SERVER");
    smtpAddr = (RWCString)" -S " + (RWCString)"smtp=" + smtpAddr;
    
    command = "mailx" + smtpAddr + subject + mailAddress;

    TRACE_FLOW(trace, sendMail, "command :" << command);
 
    CHA_Pipe mail(command);

    if (mail.status() != CHA_Pipe::OKAY)
    {
        TRACE_OUT(trace, sendMail, "Cannot fork a mail process");
        return OZT_Result( OZT_Result::MAIL_SENDING_FAILED );
    }
    int parentToChild = (int) (mail.getSendDescriptor());
    write(parentToChild, mailText, strlen(mailText));

    mail.closeSending();

    ozt_evHandlerPtr->setSigChdTrigger((void *)this, mail.pid());
 
    TRACE_OUT(trace, sendMail, "OK");
    return OZT_Result( OZT_Result::NO_PROBLEM );
}

//*****************************************************************************

OZT_Result OZT_Mail::sendMail(const RWCString& mailSubject,
                             const RWCString& mailText, 
                             const RWTValOrderedVector<RWCString>& mailAddresses)
{ 
    TRACE_IN(trace, sendMail, "mailSubject :" << mailSubject);

    if (mailAddresses.isEmpty())
    {
        TRACE_OUT(trace, sendMail, "mail addresses not specified");
	
        return OZT_Result( OZT_Result::MAIL_SENDING_FAILED );
    }
 
    RWCString command; 
    RWCString subject;

    if (!mailSubject.isNull())
    {
        RWCTokenizer next(mailSubject);
        RWCString token;
        while (!(token=next()).isNull())
            subject = subject + "_" + token;
 
        subject = subject.remove(0, 1);
        subject = " -s " + subject + " ";
    }
    else
    {
        subject = " ";
    }

    // get smtp server (lvsrouter entry from /ericsson/tor/data/global.properties)
    RWCString smtpAddr = getenv("OPS_SMTP_SERVER");
    smtpAddr = (RWCString)" -S " + (RWCString)"smtp=" + smtpAddr + " ";

    command = "mailx" + smtpAddr + subject;

    for (size_t i=0; i<mailAddresses.entries(); i++)
    {
         command = command.append(" ");
         command = command.append(mailAddresses[i]);
    }

    TRACE_FLOW(trace, sendMail, "command :" << command);
 
    CHA_Pipe mail(command); 
 
    if (mail.status() != CHA_Pipe::OKAY) 
    { 
        TRACE_OUT(trace, sendMail, "Cannot fork a mail process"); 
        return OZT_Result( OZT_Result::MAIL_SENDING_FAILED );
    } 
    int parentToChild = (int) (mail.getSendDescriptor());
    write(parentToChild, mailText, strlen(mailText));

    mail.closeSending(); 
    ozt_evHandlerPtr->setSigChdTrigger((void *)this, mail.pid());
 
    TRACE_OUT(trace, sendMail, "OK");
    return OZT_Result( OZT_Result::NO_PROBLEM );
}
