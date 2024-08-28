/*------------------------------------------------------------------------------
 ********************************************************************************
 * COPYRIGHT Ericsson 2018
 *
 * The copyright to the computer program(s) herein is the property of
 * Ericsson Inc. The programs may be used and/or copied only with written
 * permission from Ericsson Inc. or in accordance with the terms and
 * conditions stipulated in the agreement/contract under which the
 * program(s) have been supplied.
 ********************************************************************************
 *----------------------------------------------------------------------------*/

#include <CHA_PrinterPipe.H>

//**********************************************************************

#include <trace.H>
static std::string trace ="CHA_PrinterPipe";

//**********************************************************************

CHA_PrinterPipe::CHA_PrinterPipe()
{
    TRACE_IN(trace, CHA_PrinterPipe, "");

    // Get default printer name from printer list
    CHA_PrinterList list;
    list.update();
    RWCString printerName = list.defaultName();

    TRACE_FLOW(trace, CHA_PrinterPipe, printerName);

    createPipe(printerName);
}

//*********************************************************************

CHA_PrinterPipe::CHA_PrinterPipe(const RWCString& printerName)
{
    TRACE_IN(trace, CHA_PrinterPipe, printerName);

    createPipe(printerName);
}

//*********************************************************************

CHA_PrinterPipe::~CHA_PrinterPipe()
{
    pPipe->closeSending();
    pPipe->waitForChild();
    delete pPipe;
}

//*********************************************************************

CHA_PrinterPipe::ReturnCode CHA_PrinterPipe::status() const
{
    TRACE_IN(trace, status, "");
    CHA_PrinterPipe::ReturnCode pipeStatus;
    CHA_PrinterList list;

    // First, check status of pipe
    switch (pPipe->status())
    {
        case CHA_Pipe::OKAY:
	    // If OKAY, check if printer exists
	    list.update();
	    if (list.contains(printerName()))
		pipeStatus = CHA_PrinterPipe::OKAY;
	    else
		pipeStatus = CHA_PrinterPipe::NOPRINTER;
	    break;

	case CHA_Pipe::NOFORK:
	case CHA_Pipe::NO_CHILD:
	    pipeStatus = CHA_PrinterPipe::NOFORK;
	    break;

	case CHA_Pipe::CLOSED:
	case CHA_Pipe::TERMINATED:
	    pipeStatus = CHA_PrinterPipe::CLOSED;
	    break;

	default:
	    pipeStatus = OKAY;
	    break;
    }

    TRACE_RETURN(trace, status, pipeStatus);
    return pipeStatus;
}

//*********************************************************************

RWCString CHA_PrinterPipe::printerName() const
{
    TRACE_RETURN(trace, printer, printer);
    return printer;
}

//*********************************************************************

std::ostream& CHA_PrinterPipe::send()
{
    TRACE_RETURN(trace, send, "");
    return pPipe->send();
}

//*********************************************************************

void CHA_PrinterPipe::createPipe(const RWCString& printerName)
{
    TRACE_IN(trace, createPipe, printerName);
    RWCString command;

    printer = printerName;

#if  defined __hpux || defined SunOS5
    // This fix for TMOS/HP is recorded in PRIMA as HPUX.35
    command = "lp -sd " + printerName;
#else  // defined sun
    command = "lpr -P " + printerName;
#endif

    TRACE_FLOW(trace, createPipe, command);
    pPipe = new CHA_Pipe(command);
}

//*********************************************************************
