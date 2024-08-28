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
 
#ifndef OZT_DISK_H
#define OZT_DISK_H

#include <rw/cstring.h>
#include <OZT_ErrHandling.H>

class OZT_Disk {

public:
    static int    diskFree(const RWCString &fileSys, OZT_Result &res);
    // Description
    //    To find out the space left in kbytes of the specified
    //    filesystem.
    // Parameter
    //    fileSys      IN: the name of a file system or a directory
    //    res          OUT: the result of the execution
    // Return value
    //    The number of kbytes left.

    static int    diskFree(OZT_Result &res);
    // Description
    //    To find out the space left in the file system where the current
    //    directory is in.
    // Parameter
    //    res          OUT: the result of the execution
    // Return value
    //    The number of kbytes left.
   static RWCString   opsVersion();
    // Description
    // To get the OPS rpm version
};

#endif