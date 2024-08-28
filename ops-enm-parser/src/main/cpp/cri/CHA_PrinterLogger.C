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


#include <CHA_PrinterLogger.H>


//*****************************************************************************

// trace
#include <trace.H>
static std::string trace ="CHA_PrinterLogger";

//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: CHA_PrinterLogger.C,v 21.0 1996/08/23 12:40:44 ehsgrap Rel $";


//*****************************************************************************


CHA_PrinterLogger::CHA_PrinterLogger(CHA_LogSource &source,
                                     CHA_EventHandler *cleaner)
: CHA_LoggerPipe(source, cleaner)
{
    TRACE_IN(trace, CHA_PrinerLogger, "");

    TRACE_OUT(trace, CHA_PrinerLogger, "");
}

//*****************************************************************************

CHA_PrinterLogger::~CHA_PrinterLogger()
{
    (void)off();
}

//*****************************************************************************

CHA_LogReturnCode CHA_PrinterLogger::setPrinter(const RWCString &printer)
{
    TRACE_IN(trace, setPrinter, printer);

    if (printer.isNull())
    {
        TRACE_RETURN(trace, setPrinter, "Invalid printer");
        return CHA_LogReturnCode(CHA_LogReturnCode::INVALID_PRINTER);
    }

    if (printerList.update() != CHA_PrinterList::OKAY)
    {
        TRACE_RETURN(trace, setPrinter, "CHA_PrinterList update failed");
        return CHA_LogReturnCode(CHA_LogReturnCode::INTERNAL_ERR,
                                 "Printer list update failed");
    }

    if (!printerList.contains(printer))
    {
        TRACE_RETURN(trace, setPrinter, "Invalid printer");
        return CHA_LogReturnCode(CHA_LogReturnCode::INVALID_PRINTER);
    }

    currPrinter = printer;

    // if logging is already on, turn it off and on again to switch printer

    CHA_LogReturnCode result(CHA_LogReturnCode::NO_PROBLEM);

    if (isLoggingOn())
    {
        result = off();
        if (result.isOkay())
            result = on();
    }

    TRACE_RETURN(trace, setPrinter, result);
    return result;
}

//*****************************************************************************

RWCString CHA_PrinterLogger::getPrinter()
{
    TRACE_IN(trace, getPrinter, "");

    if (currPrinter.isNull())
    {
        printerList.update();
        currPrinter = printerList.defaultName();
    }

    TRACE_RETURN(trace, getPrinter, currPrinter);
    return currPrinter;
}

//*****************************************************************************

CHA_LogReturnCode CHA_PrinterLogger::on()
{
    TRACE_IN(trace, on, "");

    RWCString command;

    RWCString printerToUse = getPrinter();

    if (printerToUse.isNull() || !printerList.contains(printerToUse))
    {
        TRACE_RETURN(trace, on, "Invalid printer");
        return CHA_LogReturnCode(CHA_LogReturnCode::INVALID_PRINTER);
    }

#ifdef __hpux
        command = RWCString("lp -sd ") + printerToUse;
#endif
#ifdef sun
        command = RWCString("lpr -P ") + printerToUse;
#endif

    CHA_LogReturnCode result(CHA_LogReturnCode::NO_PROBLEM);

    if (!isLoggingOn())
    {
        setCmdStr(command);
        CHA_LogReturnCode result = turnOn();
        if (result.isOkay())
	    isFirstTime = TRUE;
    }

    TRACE_RETURN(trace, on, result);
    return result;
}

//*****************************************************************************

CHA_LogReturnCode CHA_PrinterLogger::off()
{
    TRACE_IN(trace, off, "");

    CHA_LogReturnCode result = turnOff();

    TRACE_OUT(trace, off, result);
    return result;
}
