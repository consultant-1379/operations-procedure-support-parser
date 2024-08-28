
// RCS revision handling
// $Id: CHA_FileLogger.H,v 21.0 1996/08/23 12:40:18 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	<ClassName> - <Short description of the class>
// .LIBRARY 3C++
// .PAGENAME <CLASSNAME>
// .HEADER  <SSN><API>/<FBN> 
// .LEFT_FOOTER Ericsson HP
// .INCLUDE <filename>

// .COPYRIGHT
//	COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB, Sweden 1994.
// 	All rights reserved.
//
//	The Copyright to the computer program(s) herein is the
//	property of Ericsson Hewlett-Packard Telecommunications AB,
//	Sweden. The program(s) may be used and/or copied only with the
//	written permission from Ericsson Hewlett-Packard
//	Telecommunications AB or in accordance with the terms and
//	conditions stipulated in the agreement/contract under which
//	the program(s) have been supplied.

// .DESCRIPTION 
// 	<General description of the class>

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	%EriDoc_no:%

// AUTHOR 
// 	<Date> by <Dept> <Name>

// .REVISION <for public API>
//	<Revision state>
//	<Revision date>	  	

// .REVISION <for internal header files>
//	%EriDoc_rev:%
//	%EriDoc_date:%  	

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: CHA_FileLogger.H,v $
// 	Revision 21.0  1996/08/23 12:40:18  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 07:55:09  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:20:53  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:18:37  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 11:58:37  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:55:23  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.2  1995/12/12 13:18:06  epanyc
// 	logAppend & logOverwrite functions are changed slightly
//
//      Revision 15.1  1995/11/29  02:12:25  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:14:01  17:14:01  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.0  1995/10/07 11:59:05  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.1  1995/10/06 09:13:59  ehsjasa
// 	Added a constant that defines the default permission on the created
// 	log file. The value is now -rw-rw-rw- instead of (the library default)
// 	-rw-r--r--.
//
// 	Revision 12.0  1995/09/22 14:06:02  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:22:46  09:22:46  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 10:58:14  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:35:17  14:35:17  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.0  95/06/07  17:06:08  17:06:08  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 1.1  95/05/24  07:46:20  07:46:20  epanyc (Nelson Cheng VK/EHS/PXE)
//      Initial revision
//      
//
//	RELEASE REVISION HISTORY
//
//	REV NO	DATE		NAME			DESCRIPTION
//	B_POINT 1996-08-23      J Grape (EHSGRAP)       RCS rev 21.0
//	EC8_OZ  1996-07-10      David Terry epa.epadmt  RCS rev 20.0
//	POW_TB611996-03-19      J Sandquist (ehsjasa)   RCS rev 19.0
//	EC7_OZ  1996-03-01      J Sandquist (ehsjasa)   RCS rev 18.0
//	EC6_OZ  1996-01-17      J Sandquist (ehsjasa)   RCS rev 17.0
//	POW_TB411996-01-08      J Sandquist (ehsjasa)   RCS rev 16.0
//	TB53_OZ 1995-11-29      J Grape (EHSGRAP)       RCS rev 15.1
//	POW_TB3 1995-11-20      J Sandquist (EHSJASA)   RCS rev 14.0
//	PRE_XM221995-10-07      J Sandquist (EHSJASA)   RCS rev 13.0
//	EC5_OZ  1995-09-22      J Sandquist (EHSJASA)   RCS rev 12.0
//	EC4_OZ  1995-09-14      J Sandquist (EHSJASA)   RCS rev 11.0
//	EC3_OZ  1995-08-02      J Sandquist (EHSJASA)   RCS rev 10.0
//	EC2_OZ  1995-06-29      J Grape (EHSGRAP)       RCS rev 9.0
//	TB5_2_OZ1995-06-07      J Grape (EHSGRAP)       RCS rev 8.0
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	<link information: libraries needed and order>

// .SEE ALSO 
// 	<Related classes, (abstract) baseclasses, friend classes, ...>

//*****************************************************************************

#ifndef CHA_FILE_LOGGER_H
#define CHA_FILE_LOGGER_H

#include <CHA_Logger.H>
#include <rw/tvhdict.h>
#include <rw/cstring.h>
#include <rw/rwfile.h>
#include <fstream>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>


//*****************************************************************************

const int defaultLogFilePermission = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

//the when trying to open the log with llog number 1,
//default log file should be opened
const RWCString DEFAULT_FILE_ID("1");

    // Default permission (octal) on the log file.  The umask value is
    // then automatically applied to this value at file creation time.

//*****************************************************************************

class LogFile
{
public:
  RWCString name_;
  int fd_;
  RWBoolean isFirstTime_;
  
  LogFile( RWCString name = "", RWBoolean f = TRUE, int fd = -1){
    name_ = name;
    isFirstTime_ = f;
    fd_ = fd;
  }

  LogFile( const LogFile& other ){
    name_ = other.name_;
    fd_ = other.fd_;
    isFirstTime_ = other.isFirstTime_;
  }
  
  LogFile& operator =(const LogFile& other) {
    name_ = other.name_;
    fd_ = other.fd_;
    isFirstTime_ = other.isFirstTime_;
    return *this;
  }

  bool operator == (const LogFile& other) const {
    if( name_ == other.name_
	&& isFirstTime_ == other.isFirstTime_
	&& fd_ == other.fd_ )
      return TRUE;
    else
      return FALSE;
  }
};

class CHA_FileLogger : public CHA_Logger
{
public:
    CHA_FileLogger(CHA_LogSource &source);
    // Description:
    //     Constructor.
    // Parameter:
    //     source       IN: A source object from which the logger retrieves
    //                      new text to be logged.

    ~CHA_FileLogger();
    // Description:
    //     Destructor.

    virtual RWCString getLog(const RWCString& fileId = DEFAULT_FILE_ID ) const;
    // Description:
    //     Get the currently used log file name
    // Return value:
    //     The name of the log file being used. Empty string is returned if
    //     there is no log file, or the previous log file is closed.
 
    virtual void closeLog(RWCString fileId = DEFAULT_FILE_ID);
    // Description:
    //     Close the current log file.
    //

    virtual CHA_LogReturnCode logOverwrite(RWCString fileName, RWCString fileId = DEFAULT_FILE_ID);
    // Description:
    //     This function closes any existing Log file and open
    //     a new one that is specified by the fileName.
    //
 
    virtual CHA_LogReturnCode logAppend(RWCString fileName, RWCString fileId = DEFAULT_FILE_ID);
    // Description:
    //     Similar to logOverwrite(), but the log file is appended instead.
    //

  virtual void closeAllLogs();

  struct myHash{
    unsigned long operator()(const LogFile& x) const
    {return x.name_.hash();}
  };

protected:
  //additional log file

  virtual void appendLog(RWBoolean headersON, const RWCString &newText);

  void appendLine( LogFile&  lf, RWBoolean headersON, const RWCString& text );

  //RWTValHashDictionary<RWCString, LogFile>        logFiles;
  RWTValHashMap<RWCString, LogFile, myHash,
                      std::equal_to<RWCString> > logFiles;
  
  //default log file
  //RWCString  logFileName;
  LogFile defaultFile;
  //fstream    logFile;
};

#endif
