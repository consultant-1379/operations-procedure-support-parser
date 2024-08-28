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

#ifndef CHA_NLSCATALOG_H
#define CHA_NLSCATALOG_H

#if defined __hpux || defined __linux__
#include <nl_types.h>
#elif defined sun
extern "C"
{
    typedef int nl_catd;
    char* catgets(nl_catd, int, int, const char*);
    nl_catd catopen(const char*, int);
    int catclose(nl_catd);
}
#endif

#include <rw/cstring.h>
#include <CHA_ErrorReporter.H>

class CHA_NLSCatalog
{
public:
    CHA_NLSCatalog(){}
    CHA_NLSCatalog(const char* catName, int catSet = 1);
    // Description:
    //     Constructor. The catalog is not opened at this time.
    // Parameters:
    //     catName       IN: the name of the NLS catalog
    //     catSet        IN: catalog set, default is 1
    
    CHA_NLSCatalog(const RWCString& catName, int catSet = 1);
    // Description:
    //     Constructor. The catalog is not opened at this time.
    // Parameters:
    //     catName       IN: the name of the NLS catalog
    //     catSet        IN: catalog set, default is 1
    
    virtual ~CHA_NLSCatalog();
    // Description:
    //     Destructor.

    virtual void selectSet(int catSet);
    // Description:
    //     Selects another set of the catalog.
    // Parameters:
    //     catSet        IN: the set number

    virtual RWCString getMessage(int nlsIdx) const;
    // Description:
    //     Reads a message from the NLS catalog.
    // Parameters:
    //     nlsIdx        IN: the NLS index, i.e. the message number
    // Return value:
    //     A string containing the NLS message. If the index given is
    //     not in the catalog an empty string is returned. If there
    //     are problems with opening or reading the catalog a
    //     default message is returned.

    virtual RWCString getMessage(int nlsIdx,
				 const char* defaultMsg) const;
    // Description:
    //     Reads a message from the NLS catalog.
    // Parameters:
    //     nlsIdx        IN: the NLS index, i.e. the message number
    //     defaultMsg    IN: the default message to use on failure
    // Return value:
    //     A string containing the NLS message. If the index given is
    //     not in the catalog an empty string is returned. If there
    //     are problems with opening or reading the catalog a
    //     default message is returned.

    virtual RWCString getMessage(int nlsIdx,
				 const RWCString& defaultMsg) const;
    // Description:
    //     Reads a message from the NLS catalog.
    // Parameters:
    //     nlsIdx        IN: the NLS index, i.e. the message number
    //     defaultMsg    IN: the default message to use on failure
    // Return value:
    //     A string containing the NLS message. If the index given is
    //     not in the catalog an empty string is returned. If there
    //     are problems with opening or reading the catalog a
    //     default message is returned.

private:
    RWCString catalogName;	// the name of the catalog
    int currentSet;		// the set used
};

#endif

