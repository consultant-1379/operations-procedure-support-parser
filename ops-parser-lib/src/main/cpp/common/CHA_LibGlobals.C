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

//#include <cap_trc.h>
#include <rw/cstring.h>
#include <rw/tools/datetime.h>

#include <CHA_ErrorReporter.H>

// character constants
const char* CHA_LibNLSCatalog = "/opt/ops/ops_parser/etc/nls/CHA_LibNLS.cat";

// the global error reporter instance
CHA_ErrorReporter errorReporter;


// Constants needed by old GUI-code that has been copied (or just used)
#if TPF >= 400
const char* CHA_EXECUTABLE_PATH = "/opt/tmos/bin";
#else
const char* CHA_EXECUTABLE_PATH = "/usr/local/tmos/bin";
#endif


// Functions used to convert date and time from RWTime
// to strings in the formats used by EAI. For explanations of
// the format directives see the manual pages for strftime (3C).

// "%Y-%m-%d", that is "yyyy-mm-dd"

RWCString CHA_EADateFormat(const RWDateTime& t)
{
    const RWCString dash("-");
    
    return (t.asString('Y') + dash + t.asString('m') + dash + t.asString('d'));
}

// "%H:%M:%S", that is "hh:mm:ss"

RWCString CHA_EATimeFormat(const RWDateTime& t)
{
    const RWCString colon(":");
    
    return t.asString('H') + colon + t.asString('M') + colon + t.asString('S');
}
