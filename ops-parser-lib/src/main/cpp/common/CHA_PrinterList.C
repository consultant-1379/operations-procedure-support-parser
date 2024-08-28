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

#include <CHA_LibGlobals.H>
//#include <CHA_Trace.H>
#include <CHA_LibNLS.H>
//#include <sysent.h>
#include <stdio.h>
#include <stdlib.h>
#include <CHA_PrinterList.H>

#include <trace.H>
static std::string trace ="CHA_PrinterList";

//**********************************************************************


CHA_PrinterList::CHA_PrinterList()
: nlsCat(CHA_LibNLSCatalog)
{
    TRACE_IN(trace, CHA_PrinterList, "");
    
    // Empty
}


//**********************************************************************


CHA_PrinterList::~CHA_PrinterList()
{
    // Empty
}


//**********************************************************************


RWCString CHA_PrinterList::operator[](size_t i) const
{
    TRACE_IN(trace, operator[], i);

    return myPrinterList[i];
}


//**********************************************************************


RWBoolean CHA_PrinterList::contains(const RWCString& name) const
{
    TRACE_IN(trace, contains, name);
    
    return myPrinterList.contains(name);
}


//**********************************************************************


size_t CHA_PrinterList::entries() const
{
    TRACE_IN(trace, entries, "");
    
    return myPrinterList.entries();
}


//**********************************************************************

RWCString CHA_PrinterList::defaultName() const
{
    TRACE_IN(trace, defaultName, "");

    char *s;

    if (((s = getenv("PRINTER")) != 0) && contains(s))
        return s;
    else 
	return "";
}

//**********************************************************************


RWCString CHA_PrinterList::first() const
{
    TRACE_IN(trace, first, "");
    
    return myPrinterList.first();
}


//**********************************************************************


size_t CHA_PrinterList::index(const RWCString& name) const
{
    TRACE_IN(trace, index, name);
    
    return myPrinterList.index(name);
}


//**********************************************************************


RWBoolean CHA_PrinterList::isEmpty() const
{
    TRACE_IN(trace, isEmpty, "");
    
    return myPrinterList.isEmpty();
}


//**********************************************************************


RWCString CHA_PrinterList::last() const
{
    TRACE_IN(trace, last, "");
    
    return myPrinterList.last();
}


//**********************************************************************


size_t CHA_PrinterList::length() const
{
    TRACE_IN(trace, length, "");
    
    return myPrinterList.length();
}


//**********************************************************************


size_t CHA_PrinterList::occurrencesOf(const RWCString& name) const
{
    TRACE_IN(trace, occurrencesOf, name);
    
    return myPrinterList.occurrencesOf(name);
}


//**********************************************************************


CHA_PrinterList::ReturnCode CHA_PrinterList::update()
{
    TRACE_IN(trace, update, "");
    
    CHA_PrinterList::ReturnCode returnValue = CHA_PrinterList::OKAY;
    myPrinterList.clear();

#if defined __hpux || defined SunOS5
    RWCString command = "lpstat -a";
#else  // defined sun
    RWCString command = "lpstat -p";
#endif  

    CHA_Pipe printerPipe(command);

    // return if pipe not ok
    if(printerPipe.status() != CHA_Pipe::OKAY && printerPipe.status() != CHA_Pipe::TERMINATED )
    {
	errorReporter.message(nlsCat.getMessage(NLS_PTARGET_FAILED));
	returnValue = CHA_PrinterList::NO_PRINTERS_AVAILABLE;
        return returnValue;
    }

    char line[200 + 1];
    RWBoolean isPrintersAvailable = FALSE;
    while (!printerPipe.receive().getline(line, 200).fail())
    {
          TRACE_FLOW(trace, CHA_PrinterList, "reading lines ");

          isPrintersAvailable = TRUE;
	  RWCString rad = line;

          TRACE_FLOW(trace, CHA_PrinterList, rad);

#if defined __hpux || defined SunOS5
          // Check if row contains "accepting requests"
          if(rad.contains("accepting requests",RWCString::ignoreCase)
	     && !rad.contains("not accepting requests",RWCString::ignoreCase))
	  {
	     // First word in string is a name of an enabled printer.
	     myPrinterList.insert(rad.remove(rad.first(' ')));
	  }	
#else  // defined sun
	  // Search for a ":", which follows after a printer name
	  if ( rad.first(':') != RW_NPOS)
	  {
	      RWCString newprinter = rad.remove(rad.first(':'));

	      // A printer name has been found, now check if the printer
	      // is enabled.
	      // First ignore next row, concerning queuing
	      printerPipe.receive().getline(line,200);

	      // Check if printer is enabled
	      printerPipe.receive().getline(line,200);

	      RWCString checkrow = line;

	      // *** shouldn't this be "queuing is enabled"? /EHSGRAP
	      if ( checkrow.contains("printing is enabled",
				        RWCString::ignoreCase))
	      {
		  // A enabled printer has been found
		  myPrinterList.insert(newprinter);
	      }
          }		
#endif	  
    } // end of while()...


    // wait for the child process to die
    printerPipe.closeSending();
    printerPipe.waitForChild();

    if (!isPrintersAvailable)
    {
	returnValue = CHA_PrinterList::NO_PRINTERS_AVAILABLE;
    }
    else
    {
        changed();
    }
 
    TRACE_RETURN(trace, update, returnValue);
    return returnValue;
}


