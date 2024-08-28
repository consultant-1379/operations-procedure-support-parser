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

#include <OZT_Misc.H>
//#include <xview/xview.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <pwd.h>
#include <rw/tools/regex.h>


//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_Misc";

//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_Misc.C,v 21.0 1996/08/23 12:44:19 ehsgrap Rel $";


//*****************************************************************************


RWBoolean isEmptyLine(const char *buf)
{
    while (*buf != '\0') {
        if (!isspace(*buf)) return FALSE;
        buf++;
    }
    return TRUE;
}

//*****************************************************************************

RWCString ozt_currDir()
{
    size_t PATHMAX = 1030;
    static char   buf[1032];
 
    return (char *)getcwd((char *)buf, PATHMAX+1);
}

//*****************************************************************************

RWCString ozt_homeDir(const RWCString &userName)
{
    TRACE_IN(trace, ozt_homeDir, userName);

    struct passwd *entry;

    if (userName.isNull())
        entry = getpwuid(getuid());  // if userName is null, use eff. uid
    else
        entry = getpwnam(userName);

    if (entry == 0)
    {
        TRACE_OUT(trace, ozt_homeDir, "");
        return RWCString();
    }
    else 
    { 
        TRACE_OUT(trace, ozt_homeDir, entry->pw_dir);
        return entry->pw_dir;
    }
}

//*****************************************************************************

RWCString ozt_normalisePath(RWCString path)
{
    TRACE_IN(trace, ozt_normalisePath, path);

    path = trim(path);

    //  if the path starts with '~' or '~user', expand it
    size_t ext;
    static RWTRegex<char> homeChecker("^~[^/]*");

    if (homeChecker.index(path, &ext) != RW_NPOS)
    {
        RWCString home = ozt_homeDir(path(1, ext - 1));
        if (!(home.isNull()))
            path.replace(0, ext, home + "/");
    }

    // if the path doesn't start with a '/', add current working dir to it
    if(path.isNull() || (path[(unsigned)0] != '/'))
    {
	TRACE_FLOW(trace, ozt_normalisePath, "a relative path");
	path = ozt_currDir() + "/" + path;
    }

    // if the path end with .. or ., append a '/' 
    if ((path.index("/..", path.length() - 3) != RW_NPOS) ||
        (path.index("/.", path.length() - 2) != RW_NPOS))
    {
        path.append("/");
    }

    size_t idx;				// index in string
    
    // remove '/./'
    while((idx = path.index("/./")) != RW_NPOS)
	path.remove(idx, 2);
    TRACE_FLOW(trace, ozt_normalisePath, path);

    // replace '//' with '/'
    while((idx = path.index("//")) != RW_NPOS)
	path.replace(idx, 2, "/");
    TRACE_FLOW(trace, ozt_normalisePath, path);

    // when '/../' or trailing '/..' is found remove directory before
    while ((idx = path.index("/../")) != RW_NPOS)
    {
	size_t endIdx = idx + 3;	// last character in pattern
	
	if(idx > 0)
	{
	    idx--;
	    while((idx > 0) && (path[idx] != '/'))
		idx--;
	}

	size_t len = endIdx - idx;
	path.remove(idx, len);
	TRACE_FLOW(trace, ozt_normalisePath, path);
    }

    TRACE_RETURN(trace, ozt_normalisePath, path);
    return path;    
}

//*****************************************************************************

RWCString trim(const RWCString& line)
{
    int i = 0;
    int j = line.length() - 1;
 
    //  trim leading white space
    while (i < line.length()) 
    {
        if (!isspace(line[(unsigned)i]))
            break;
        i++;
    }
    
    //  trim trailing white space
    while (j > i) {
        if (!isspace(line[(unsigned)j]))
            break;
        j--;
    }
    
    if (i > j)
        return RWCString();
    else
        return line(i, j-i+1);
}

//*****************************************************************************

int strToInt(const RWCString &str)
{
    return (int)atoi(str.data());
}
