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


#include <CHA_UserInfo.H>
#include <unistd.h>


//**********************************************************************

#include <trace.H>
static std::string trace ="CHA_UserInfo";


RWBoolean CHA_UserInfo::isInitialized = FALSE;
RWCString CHA_UserInfo::myLoginName = RWCString();
RWCString CHA_UserInfo::myFullName = RWCString();
uid_t CHA_UserInfo::myUserID = 0;
gid_t CHA_UserInfo::myGroupID = 0;
RWCString CHA_UserInfo::myHomeDir = RWCString();
RWCString CHA_UserInfo::myLoginShell = RWCString();


//**********************************************************************


CHA_UserInfo::CHA_UserInfo()
{
    TRACE_IN(trace, CHA_UserInfo, "");

    if(!isInitialized)
    {
	TRACE_FLOW(trace, CHA_UserInfo, "initializing static members");
        passwd pwdStruct = *getpwuid(getuid());
        ///	passwd pwdStruct = *getpwnam("tmosadm");
	myLoginName = pwdStruct.pw_name;
	myFullName = pwdStruct.pw_gecos;
	myUserID = pwdStruct.pw_uid;
	myGroupID = pwdStruct.pw_gid;
	myHomeDir = pwdStruct.pw_dir;
	myLoginShell = pwdStruct.pw_shell;

	isInitialized = TRUE;
    }
}


//**********************************************************************


CHA_UserInfo::~CHA_UserInfo()
{
    // nothing
}


//**********************************************************************


RWCString CHA_UserInfo::loginName() const
{
    TRACE_RETURN(trace, loginName, myLoginName);
    return myLoginName;
}


//**********************************************************************


RWCString CHA_UserInfo::fullName() const
{
    TRACE_RETURN(trace, fullName, myFullName);
    return myFullName;
}


//**********************************************************************


uid_t CHA_UserInfo::userID() const
{
    TRACE_RETURN(trace, userID, myUserID);
    return myUserID;
}


//**********************************************************************


gid_t CHA_UserInfo::groupID() const
{
    TRACE_RETURN(trace, groupID, myGroupID);
    return myGroupID;
}


//**********************************************************************


RWCString CHA_UserInfo::homeDir() const
{
    TRACE_RETURN(trace, homeDir, myHomeDir);
    return myHomeDir;
}


//**********************************************************************


RWCString CHA_UserInfo::loginShell() const
{
    TRACE_RETURN(trace, loginShell, myLoginShell);
    return myLoginShell;
}


//**********************************************************************

