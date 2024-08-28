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

#include <CHA_OZTInfo.H>
#include <CHA_UserInfo.H>
/* #include <tauchl_t.H>
#include <eac_egi.H>
#include <cap_pdb.H>
#include <CHA_Trace.H>
#include <cap_pdb_parameter.H> */
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <trace.H>
#include <rw/tools/regex.h>
#include <trace.H>
static std::string trace ="CHA_OZTInfo";

// Initialise static variables
RWBoolean CHA_OZTInfo::installed = FALSE;
RWBoolean CHA_OZTInfo::hasCheckedIfInstalled = FALSE;
RWCString CHA_OZTInfo::directory = "";
RWBoolean CHA_OZTInfo::headers = FALSE;
int 	  CHA_OZTInfo::noOfAttempts = 0;
int 	  CHA_OZTInfo::interval = 0;
RWCString CHA_OZTInfo::esListSource = "";
RWCString CHA_OZTInfo::sessionIdFile_ = "";
RWCString CHA_OZTInfo::saveDir_ = "";
RWCString CHA_OZTInfo::privateDir_ = "";

// Name of parameters in the PDB map
/* static const char *const MAP_NAME       = "ops_map";
static const char *const ON_OFF         = "oztermOFF";
static const char *const ATTEMPTS       = "cmdAttempts";
static const char *const INTERVAL       = "cmdInterval";
static const char *const DIRECTORY      = "directory";
static const char *const CMDFILE        = "cmdfile";
static const char *const RESPONSE       = "response";
static const char *const FAIL_STRING    = "failString";
static const char *const TYPE           = "type";
static const char *const STR            = "str";
static const char *const HEADERS_ON     = "headerON";
static const char *const ES_LIST_SOURCE = "esListSource";
static const char *const SESSION_FILE    = "sessionIdFile"; */
static const char *const DEFAULT_SESSION_FILE = "/var/opt/ericsson/nms_ops_server/data/session_id";
static const char *const DEFAULT_CENTRAL_DIR  = "/etc/opt/ericsson/nms_ops_server/scripts";
static const char *const DEFAULT_RESPONSE_DIR  = "/cha/response";
static const char *const DEFAULT_PRIVATE_DIR  = "/cha/cmdfile";
//*****************************************************************************

using namespace std;

CHA_OZTInfo::CHA_OZTInfo()
{
  TRACE_IN(trace, CHA_OZTInfo, "");
  // nothing
}


//*****************************************************************************


CHA_OZTInfo::~CHA_OZTInfo()
{
  // nothing
}


//*****************************************************************************


CHA_OZTInfo::ReturnCode CHA_OZTInfo::getCentralDir(RWCString& retDirectory) const
{
  ReturnCode  rc = NOT_INSTALLED;
  const char  *dir;
  retDirectory = ".";
  
  if(isInstalled()) {
    if ((dir = getenv("OPS_CENTRALDIR")) == NULL) {       // Not set
      retDirectory = DEFAULT_CENTRAL_DIR;
    }else{
      retDirectory = dir;
    }
	rc = OKAY;

    if (retDirectory[retDirectory.length() - 1] != '/'){
      retDirectory.append('/');
    }
    TRACE_RETURN(trace, getCentralDir, rc);
    return rc;
  }
}


//*****************************************************************************
CHA_OZTInfo::ReturnCode CHA_OZTInfo::getAttemptsAndIntvl(int& cmdAttempts,
                                                         int& cmdInterval) const
{
  ReturnCode rc = NOT_INSTALLED;

  if(isInstalled())
  {
    rc = OKAY;
  }
  cmdInterval = interval;
  cmdAttempts = noOfAttempts;

  TRACE_RETURN(trace, getAttemptsAndIntvl, rc);
  return rc;
}


//*****************************************************************************
CHA_OZTInfo::ReturnCode CHA_OZTInfo::getHeadersON(RWBoolean& headersON) const
{
  ReturnCode rc = NOT_INSTALLED;

  if(isInstalled())
  {
    headersON = headers;
    rc = OKAY;
  }

  TRACE_RETURN(trace, getHeadersON, rc);
  return rc;
}

//*****************************************************************************

void CHA_OZTInfo::getAdditionalFailStrings(RWTValSlist<RWCString> &list)
{
  TRACE_IN(trace, getAdditionalFailStrings, "");

  //getEnvStringList("FAILSTRINGS", list);
  list.append("NOT ACCEPTED");

  TRACE_OUT(trace, getAdditionalFailStrings, "");
}

//*****************************************************************************

void CHA_OZTInfo::getCslExemptionCommands(RWTValSlist<RWCString> &list)
{
  TRACE_IN(trace, getCslExemptionCommands, "");

  //getEnvStringList("CSLEXEMPTIONS", list);
  RWCString sEnvString = "exit|mml|PTCOE;";
  RWCString sToken;
  RWCTokenizer theNextToken(sEnvString);
  while(!(sToken = theNextToken("|")).isNull()) {
      list.append(sToken.strip(RWCString::both, ' '));
  }

  TRACE_OUT(trace, getCslExemptionCommands, "");
}

//*****************************************************************************

void CHA_OZTInfo::getEnvStringList(RWCString name, RWTValSlist<RWCString> &list)
{
  TRACE_IN(trace, getEnvStringList, name);
  RWCString sEnvString;
  RWCString sToken;

  if(getenv(name) != NULL){
	sEnvString = getenv(name);
    TRACE_FLOW(trace, getEnvStringList, "found " << sEnvString);
    RWCTokenizer theNextToken(sEnvString);
    while(!(sToken = theNextToken("|")).isNull())
      list.append(sToken.strip(RWCString::both, ' '));
  } else {
	TRACE_FLOW(trace, getEnvStringList, "Environment variable " << name << " is not defined or empty");
  }

  TRACE_OUT(trace, getEnvStringList, "");
}

//*****************************************************************************

CHA_OZTInfo::ReturnCode CHA_OZTInfo::getSessionIdFile( RWCString& sessionIdFile ) const{

  ReturnCode rc = NOT_INSTALLED;
  const char  *dir;
  sessionIdFile = ".";
  
  if(isInstalled()) {
    if ((dir = getenv("OPS_SESSION_FILE")) == NULL) {       // Not set
      sessionIdFile = DEFAULT_SESSION_FILE;
    }

    if(access(dir, R_OK) != 0)
      rc = ACCESS_ERROR;
    else{
      rc = OKAY;
      sessionIdFile = dir;
    }
    TRACE_RETURN(trace, getSessionIdFile, rc);
    return rc;
  }
}
//*****************************************************************************
CHA_OZTInfo::ReturnCode CHA_OZTInfo::getPrivateDir(RWCString& retDirectory) const
{
  TRACE_IN(trace, getPrivateDir, "");

  ReturnCode  rc = NOT_INSTALLED;
  retDirectory = ".";
  const char *subDir;


  if (privateDir_.length() == 0) {       // Not set
    rc = ENV_NOT_SET;
  }
  else if(access(privateDir_.data(), R_OK) != 0){
    rc = ACCESS_ERROR;
  }
  else{
    rc = OKAY;
    retDirectory = privateDir_;
  }

  if(rc != OKAY){

    // Get home directory
    char *homeDir = strcat(getpwuid(getuid())->pw_dir, "/");

    // Get any extension, ~/cha/cmdfile by default
    if((subDir = getenv("OPS_PRIVATEDIR")) == NULL)
      subDir = DEFAULT_PRIVATE_DIR;
      
     retDirectory = strcat(homeDir, subDir);
     normalisePath(retDirectory);
	rc = OKAY;
  }

  if (retDirectory[retDirectory.length() - 1] != '/')
    retDirectory.append('/');

  TRACE_OUT(trace, getPrivateDir, rc);

  return rc;
}



//*****************************************************************************

void CHA_OZTInfo::setPrivateDir(const RWCString& theDirectory)
{
  privateDir_ = theDirectory;
  normalisePath(privateDir_);
}


//*****************************************************************************

CHA_OZTInfo::ReturnCode CHA_OZTInfo::getSaveDir(RWCString& retDirectory) const
{
  TRACE_IN(trace, getSaveDir, "");

  ReturnCode  rc = NOT_INSTALLED;
  retDirectory = ".";
  const char *subDir;


  if (saveDir_.length() == 0) {       // Not set
    rc = ENV_NOT_SET;
  }
  else if(access(saveDir_.data(), R_OK) != 0){
    rc = ACCESS_ERROR;
  }
  else{
    rc = OKAY;
    retDirectory = saveDir_;
  }


  if(rc != OKAY){

    // Get home directory
    char *homeDir = strcat(getpwuid(getuid())->pw_dir, "/");

    // Get any extension, ~/cha/response by default
    if((subDir = getenv("OPS_RESPONSEDIR")) == NULL)
      subDir = DEFAULT_RESPONSE_DIR;

    retDirectory = strcat(homeDir, subDir);
    normalisePath(retDirectory);
	rc = OKAY;
  }

  if (retDirectory[retDirectory.length() - 1] != '/')
    retDirectory.append('/');

  TRACE_OUT(trace, getSaveDir, rc);
  return rc;
}


//*****************************************************************************

void CHA_OZTInfo::setSaveDir(const RWCString& theDirectory)
{
  saveDir_ = theDirectory;
  normalisePath(saveDir_);
}


//*****************************************************************************

CHA_OZTInfo::ReturnCode CHA_OZTInfo::getEsListSource(RWCString& retSource) const
{
  ReturnCode rc = NOT_INSTALLED;

  if(isInstalled())
  {
    rc = OKAY;
    retSource = esListSource;
  }

  TRACE_RETURN(trace, getEsListSource, rc);
  return rc;
}


//*****************************************************************************


RWBoolean CHA_OZTInfo::isInstalled()
{
  if(!hasCheckedIfInstalled)
  {
    installed = checkIfInstalled();
  }

  TRACE_RETURN(trace, isInstalled, installed);
  return installed;
}


//*****************************************************************************

RWCString CHA_OZTInfo::getUsrForAuthCheck(const RWCString &scriptName) const
{
  TRACE_IN(trace, getUsrForAuthCheck, scriptName);

  static CHA_UserInfo  userInfo;
  RWCString            procOwner = userInfo.loginName();
  /*
  // declaring `procOwner' as "static RWCString" makes the HP
  // compiler stop with an internal compiler error
  tauchl_t             authCheck;
  static EAC_EGI_Info  eaGeneralInfo;
  static const char*   tmosNode = eaGeneralInfo.Get_TMOS_node();
  char                 scriptNameBuf[1024];

  if (authCheck.get_status() != TAU_SUCCESS)
  {
    //TRACE_RETURN(trace, getUsrForAuthCheck,
     "Error! authority object is not okay, use process owner :"
         << procOwner);
    return procOwner;
  }

  if (tmosNode == 0)
  {
    //TRACE_RETURN(trace, getUsrForAuthCheck,
         "Error! tmosNode is not okay, use process owner :"
         << procOwner);
    return procOwner;
  }

  //TRACE_FLOW(trace, getUsrForAuthCheck, "TMOS node for checking :" <<
             tmosNode);

  // Try the relative path from the central dir
  strcpy((char*)scriptNameBuf, stripCentralDir(scriptName).data());
  //TRACE_FLOW(trace, getUsrForAuthCheck, "Name for checking :" <<
             scriptNameBuf);

  if (authCheck.check_activity((char *)(procOwner.data()),
                               (char *)tmosNode,
                               (char *)scriptNameBuf,
                               "CMD_FILE") == TAU_AUTHORIZED)
  {
    // The script is authorised, use the file owner for authority checking
    //TRACE_RETURN(trace, getUsrForAuthCheck, fileOwnerOf(scriptName));
    return fileOwnerOf(scriptName);
  }

  //  Try again with absolute path
  strcpy((char*)scriptNameBuf, scriptName.data());
  //TRACE_FLOW(trace, getUsrForAuthCheck, "Name for checking :" <<
                                         scriptNameBuf);

  if (authCheck.check_activity((char *)(procOwner.data()),
                               (char *)tmosNode,
                               (char *)scriptNameBuf,
                               "CMD_FILE") == TAU_AUTHORIZED)
  {
    //TRACE_RETURN(trace, getUsrForAuthCheck, fileOwnerOf(scriptName));
    return fileOwnerOf(scriptName);
  }

  //
  // The file name is not defined as an activity in the authdb, so
  // use the process owner for authority check.
  //
  //TRACE_RETURN(trace, getUsrForAuthCheck,
           "Cannot find the name in the authority db, using process owner :"
             << procOwner);
  */
  return procOwner;
}


//*****************************************************************************

RWCString CHA_OZTInfo::stripCentralDir(const RWCString &path) const
{
  RWCString centralDir;

  (void)getCentralDir(centralDir);

  //
  //  if the path name is preceded by the central dir, strip that part
  //  off
  //
  if (path.index(centralDir) == 0)
    return path(centralDir.length(), path.length() - centralDir.length());
  else
    return path;
}

//*****************************************************************************

RWCString CHA_OZTInfo::fileOwnerOf(const RWCString &path)
{
  TRACE_FLOW(trace, fileOwnerOf, path);

  struct stat statBuf;
  struct passwd *pPwdStruct;

  if (stat(path.data(), &statBuf) != 0)
    return "";

  if ((pPwdStruct = getpwuid(statBuf.st_uid)) == 0)
    return "";

  return pPwdStruct->pw_name;
}

//*****************************************************************************

RWBoolean CHA_OZTInfo::checkIfInstalled()
{

  // This function was used to check if pdb maps were installed
  // properly. But those does not exist under CIF.
  char        *str = NULL;
  int         par;
  int         intvls;
  int         att;
  int         head;
  //CAP_PDB     pdb;
  RWBoolean   ret = TRUE;

  /*
  if (pdb.get(MAP_NAME, DIRECTORY, str) != 0)
  {
    // The Directory parameter is not present
    // (The map is considered to be not present)
    ret = FALSE;
  }
  else
  {
    // The map is present
    directory = str;
    if (pdb.get(MAP_NAME, ATTEMPTS, att ) == 0)
      noOfAttempts = att;
    if (pdb.get(MAP_NAME, INTERVAL, intvls ) == 0)
      interval = intvls;
    if (pdb.get(MAP_NAME, HEADERS_ON, head ) == 0)
      headers = head;
    if (pdb.get(MAP_NAME, ES_LIST_SOURCE, str) == 0)
      esListSource = str;
    if (pdb.get(MAP_NAME, SESSION_FILE, str) == 0)
      sessionIdFile_ = str;
    if (pdb.get(MAP_NAME, CMDFILE, str) == 0)
      setPrivateDir(str);
    if (pdb.get(MAP_NAME, RESPONSE, str) == 0)
      setSaveDir(str);

    // Check if the ON_OFF parameter is present and = OFF
    //   (The ON_OFF parameter is intended for testing
    //    purposes and is not documented to the user).

    if (pdb.get(MAP_NAME, ON_OFF, par) == 0)
    {
      // ON_OFF parameter is present
      if(par == 1)
      ret = FALSE;          // OFF is indicated
    }
  }

  if(str != NULL)
    delete str;
  */

  hasCheckedIfInstalled = TRUE;
  TRACE_RETURN(trace, checkIfInstalled, ret);

  return ret;
}

//*****************************************************************************

void CHA_OZTInfo::normalisePath(RWCString& path)
{
    TRACE_IN(trace, normalisePath, path);

    path = trim(path);

    //  if the path starts with '~' or '~user', expand it
    size_t ext;
    static RWTRegex<char> homeChecker("^~[^/]*");

    if (homeChecker.index(path, &ext) != RW_NPOS)
    {
        RWCString home = homeDir(path(1, ext - 1));
        if (!(home.isNull()))
            path.replace(0, ext, home + "/");
    }

    // if the path doesn't start with a '/', add current working dir to it
    if(path.isNull() || (path[(unsigned)0] != '/'))
    {
	TRACE_FLOW(trace, normalisePath, "a relative path");
	path = currDir() + "/" + path;
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
    TRACE_FLOW(trace, normalisePath, path);

    // replace '//' with '/'
    RWCString path1 = path;
    while((idx = path1.index("//")) != RW_NPOS)
	path1.replace(idx, 2, "/");
	path = path1;
    TRACE_FLOW(trace, normalisePath, path);

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
	TRACE_FLOW(trace, normalisePath, path);
    }

    TRACE_RETURN(trace, normalisePath, path);
}

//*****************************************************************************

RWCString CHA_OZTInfo::homeDir(const RWCString &userName)
{
    TRACE_IN(trace, homeDir, userName);

    struct passwd *entry;

    if (userName.isNull())
        entry = getpwuid(getuid());  // if userName is null, use eff. uid
    else
        entry = getpwnam(userName);

    if (entry == 0)
    {
        TRACE_OUT(trace, homeDir, "");
        return RWCString();
    }
    else
    {
        TRACE_OUT(trace, homeDir, entry->pw_dir);
        return entry->pw_dir;
    }
}

//*****************************************************************************

RWCString CHA_OZTInfo::currDir()
{
    size_t PATHMAX = 1030;
    static char   buf[1032];

    return (char *)getcwd((char *)buf, PATHMAX+1);
}

//*****************************************************************************

RWCString CHA_OZTInfo::trim(const RWCString& line)
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
