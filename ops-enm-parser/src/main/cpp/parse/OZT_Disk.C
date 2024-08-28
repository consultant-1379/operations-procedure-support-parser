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


#include <OZT_Disk.H>
#include <rw/cstring.h>
#include <rw/ctoken.h>
#include <OZT_Misc.H>
#include <CHA_Pipe.H>
#include <OZT_Value.H>
#include <OZT_EventHandler.H>
#include <boost/filesystem.hpp>

//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_Disk";

//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_Disk.C,v 21.0 1996/08/23 12:43:48 ehsgrap Rel $";

 
//*****************************************************************************

extern OZT_EventHandler *ozt_evHandlerPtr;

//*****************************************************************************

int OZT_Disk::diskFree(OZT_Result& res)
{
    TRACE_IN(trace, diskFree, "");
//     char buf[512];
//     RWCString directory;

//     getcwd(buf, 512);
//     if (buf == NULL)
//     {
//         directory = "."; // will either work or report error later on
//     }
//     else
//     {
//         directory = buf;
//     }

//     return diskFree(directory, res);
    
    return diskFree(".", res);
}

int OZT_Disk::diskFree(const RWCString& fileSys, OZT_Result& res)
{
    TRACE_IN(trace, diskFree, "file system " << fileSys);
    RWCString fileSystem = trim(fileSys);// remove leading/trailing whitespace
    std::string file(fileSystem);

    if (fileSystem.length() == 0)
    {
        // fileSystem is not specified.
        TRACE_INFO(trace, diskFree, "Error, File System not specified");
        res = OZT_Result::MISSING_PARAMETERS;
        return -1;
    }

    if(boost::filesystem::is_directory(file))
    {
        boost::filesystem::space_info si = boost::filesystem::space(file);
        int resultLine = si.available / 1024;
        OZT_Value myDiskSpace = resultLine;
        int diskSpace = (int)(myDiskSpace.toLong(res));
        TRACE_RETURN(trace, diskFree, "diskSpace: " << diskSpace);
        return diskSpace;
    }
    else
    {
        TRACE_INFO(trace, diskFree, "No such file or directory: " << fileSystem);
        res = OZT_Result(OZT_Result::INVALID_VALUE);
        return -1;
    }

}


RWCString OZT_Disk::opsVersion()
{

    RWCString command = "rpm -q ERICopsparser_CXP9042171";

    CHA_Pipe  myPipe(command.data());
    CHA_Pipe::PipeStatus statusOfPipe;
    const char * fail = "-1";
   do {                                   // Wait for child to finished
        statusOfPipe = myPipe.status();    // or error in the pipe
    }while(statusOfPipe == CHA_Pipe::OKAY);
    if ( ( statusOfPipe == CHA_Pipe::NO_CHILD ) || (statusOfPipe == CHA_Pipe::NOFORK) )
    {
        return fail;
    }

    ozt_evHandlerPtr->setSigChdTrigger((void *)356, // arbitrary client
                                        myPipe.pid());

    RWCString version = RWCString();

    char      line[70] = {'\0'};

    int chdToParent = (int) (myPipe.getReceiveDescriptor());

    const int charToRead = 70;
    if (read(chdToParent,line,charToRead) != NULL)
    {
      version = line;
    }
    else
    {
      version = "No Version";
    }

    return version;
}
/*
int OZT_Disk::sigChdCatcher(void *instance, 
                             pid_t)
{
    return ozt_evHandlerPtr->notify_done();
}
*/
