//ClearCase Version Control Information
//ClearCase: @(#) syn-opsserver/opslib/common/src/CHA_OZTInfo.H @@/main/4 2000-05-23.13:26 EHS

// ---------------------------------------------------------------------
//
//  COPYRIGHT EHPT Sweden AB 2000.
//  All rights reserved.
//
//  The Copyright to the computer program(s) herein is the property of
//  EHPT Sweden AB.
//  The program(s) may be used and/or copied only with the written
//  permission from EHPT Sweden AB or in accordance with the terms and
//  conditions stipulated in the  agreement/contract under which the
//  program(s) have been supplied.
//
// ---------------------------------------------------------------------

#ifndef CHA_OZTINFO_H
#define CHA_OZTINFO_H

#include   <rw/cstring.h>
#include   <rw/ctoken.h>
#include   <rw/tvslist.h>

/**
 * This class handles the OPS parameters in the PDB (Parameter Data Base).
 * It also handles some other configuration data.
 *
 * @author 1994-12-27 EHS/PXE Christer Eklund (qhskred@ehs.ericsson.se)
 * @author 2000-03-01 EHS/OX/DF Anders Ahlström
 *
 * @see OtherClass
 */
class  CHA_OZTInfo
{

public:

  /**
   * Return codes
   *
   */
  enum  ReturnCode {
    OKAY,
    NOT_INSTALLED,        // OPS is not installed
    ENV_NOT_SET,          // Environment variable is not set
    ACCESS_ERROR          // Private directory not accessible
  };

  /**
   * Constructor
   *
   */
  CHA_OZTInfo();

  /**
   * Destructor
   *
   */
  virtual ~CHA_OZTInfo();

  /**
   * Get the full path of the central directory where  OPS scripts are stored.
   *
   * @param directory Name of central directory, OUT
   * @return OKAY           Name of directory is returned
   *         NOT_INSTALLED  OPS is not installed (The parameter, directory, is not touched)
   */
  ReturnCode getCentralDir(RWCString& directory) const;

  /**
   * Get no of attempts, and interval, which will be made before a command
   * is considered to have failed.
   *
   * @param cmdAttempts Number of attempts, as defined in the pdb map, OUT
   * @param cmdInterval Interval in seconds,  as defined in the pdb map, OUT
   * @return OKAY           The parameters are returned
   * @return NOT_INSTALLED  OPS is not installed (The parameter is not touched)
   */
  ReturnCode getAttemptsAndIntvl(int& cmdAttempts, int& cmdInterval) const;

  /**
   * This method bla bla
   *
   * @param <para> <Parameter Description, IN/OUT>
   * @return OKAY           The parameters are returned
   * @return NOT_INSTALLED  OPS is not installed (The parameters are not touched)
   */
  ReturnCode getHeadersON(RWBoolean& headersON) const;

  /**
   * Get the content of environment variable CHA_CMDFILE.
   * This is where private command scripts are stored.
   *
   * @param directory Name of private directory, OUT
   * @return OKAY           Name of directory is returned
   * @return ENV_NOT_SET    Environment variable CHA_CMDFILE is not set
   * @return ACCESS_ERROR   Private directory is not accessible
   *            			(The parameter, directory, contains "./" in the
   *        			    error cases)
   */
  ReturnCode getPrivateDir(RWCString& directory) const;

  /**
   * Set the content of environment variable CHA_CMDFILE.
   * This is where private command scripts are stored.
   *
   * @param directory Name of private directory, IN
   */
  static void setPrivateDir(const RWCString& directory);

  /**
   * Get the content of environment variable CHA_RESPONSE. This is where data files
   * used by script should normally store.
   *
   * @param directory Name of the save directory, OUT
   * @return OKAY           Name of directory is returned
   * @return ENV_NOT_SET    Environment variable CHA_RESPONSE is not set
   * @return ACCESS_ERROR   Private directory is not accessible
   *            			(The parameter, directory, contains "./" in the
   *        			    error cases)
   */
  ReturnCode getSaveDir(RWCString& directory) const;

  /**
   * Set the content of environment variable CHA_RESPONSE. This is where data files
   * used by script should normally store.
   *
   * @param directory Name of the save directory, IN
   */
  static void setSaveDir(const RWCString& directory);

  /**
   * Get the source for ES lists.
   *
   * @param source Source for ES lists, OUT
   * @return OKAY           Name of source is returned
   * @return NOT_INSTALLED  OPS is not installed. (The parameter, source, is not touched)
   */
  ReturnCode getEsListSource(RWCString& source) const;

  /**
   * Find out if OPS is installed.
   *
   * @return TRUE         OPS is installed.
   * @return FALSE        OPS is not installed.
   */
  static RWBoolean isInstalled();

  /**
   * Find out what operator id should be used for authority checking while executing
   * "scriptName".
   *
   * @param scriptName Path name of the script, IN
   * @return The operator id to be used for authority checking while executing
   * "scriptName". In case of errors, such as the script cannot be accessed, an empty
   * string is returned.
   */
  RWCString getUsrForAuthCheck(const RWCString &scriptName) const;

  /**
   * Retrieve extra failure strings that should be checked
   *
   * @param list the failure strings retrieved from the PDB map, OUT
   */
  void getAdditionalFailStrings(RWTValSlist<RWCString> &list);

  /**
   * If CSL response is found in the immediate answer printout
   * of these commands, it will be ignored (i.e. treated as a regular
   * answer), instead of being treated as Function Busy.
   *
   * @param list the CSL exemptions retrieved from the PDB map, OUT
   */
  void getCslExemptionCommands(RWTValSlist<RWCString> &list);

  /**
   * Fetch a string to be parser as a list of value separated
   * by |, append values to list
   *
   * @param name name of environment variable
   * @param list list to append values to
   */
  void getEnvStringList(RWCString name, RWTValSlist<RWCString> &list);

  ReturnCode getSessionIdFile( RWCString& sessionIdFile ) const;


private:
  /**
   * Given a path name, this function strips the central directory part from the path.
   * If "path" is not prefixed by the central directory, the whole "path" is returned.
   *
   * @param path the full path name of a file, IN
   * @return The stripped path name
   */
  RWCString  stripCentralDir(const RWCString &path) const;

  /**
   * Given a path name, this function return the user name of the file owner.
   *
   * @param path the path name of a file, IN
   * @return The user name of the file owner.
   */
  static RWCString  fileOwnerOf(const RWCString &path);

  /**
   * Find out if command file developer (OPS) is installed. If it is installed,
   * the static attributes (directory, noOfAttempts and interval)
   * are updated with corresponding values from the pdb map.
   *
   * @return TRUE         OPS is installed.
   * @return FALSE        OPS is not installed.
   */
  static RWBoolean  checkIfInstalled();

  /**
   * Trims the leading and trailing space, tabs and newline characters.
   * @param line string to trim, IN
   * @return trimmed string.
   */
  static RWCString  trim(const RWCString& line);

  /**
   * Returns the current directory.
   * @return current directory.
   */
  static RWCString  currDir();

  /**
   * Returns the home directory of the specified user.
   * @param usrName specified user, IN
   * @return user's home directory.
   */
  static RWCString  homeDir(const RWCString &usrName);

  /**
   * Expands the given path into an absolute path.
   * Tilde (~), ".." and "." are removed. If the path is not absolute,
   * It is expanded as if the path is relative to the current directory.
   * @param path the path to expand, IN
   * @return expanded path.
   */
  static void  normalisePath(RWCString& path);

  static RWBoolean   installed;
  static RWBoolean   hasCheckedIfInstalled;
  static RWCString   directory;
  static RWBoolean   headers;
  static int         noOfAttempts;
  static int         interval;
  static RWCString   esListSource;
  static RWCString   privateDir_;
  static RWCString   sessionIdFile_;
  static RWCString   saveDir_;
};

#endif
