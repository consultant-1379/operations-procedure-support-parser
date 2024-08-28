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


#include <CHA_FileLogger.H>
#include <OZT_Misc.H>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>


//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="CHA_FileLogger";

//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: CHA_FileLogger.C,v 21.0 1996/08/23 12:40:33 ehsgrap Rel $";


//static unsigned hashString(const RWCString& str) {return str.hash();}

//*****************************************************************************


CHA_FileLogger::CHA_FileLogger(CHA_LogSource &source)
:CHA_Logger(source), logFiles()
{
   TRACE_IN(trace, CHA_FileLogger, "");

   TRACE_OUT(trace, CHA_FileLogger, "");
}

//*****************************************************************************

CHA_FileLogger::~CHA_FileLogger()
{
    closeAllLogs();
}

//*****************************************************************************

RWCString CHA_FileLogger::getLog( const RWCString& fileId) const
{
   TRACE_IN(trace, getLog, "");

    if (isLoggingOn())
    {
      if( fileId == DEFAULT_FILE_ID ) {
       TRACE_RETURN(trace, getLog, defaultFile.name_);
        return defaultFile.name_;
      }
      else {

	LogFile file;
	RWBoolean found = logFiles.findValue( fileId, file );
	
	if( found ) {
	  TRACE_RETURN(trace, getLog,file.name_);
	  return file.name_; 
	}
	else {
	  TRACE_RETURN(trace, getLog, "");
	  return RWCString();
	}
      }
    }
    else
    {
       TRACE_RETURN(trace, getLog, "");
        return RWCString();
    }
}

//*****************************************************************************
void CHA_FileLogger::closeAllLogs() {
 TRACE_IN(trace, closeAllLogs, "");

  if (isLoggingOn()){
 TRACE_FLOW(trace, closeAllLogs, "isLoggingOn() OK");
    if( defaultFile.fd_ != -1 ) {
      //lockf( defaultFile.fd_, F_ULOCK, 0 );
      close( defaultFile.fd_ );
      defaultFile.name_ = RWCString();
      defaultFile.isFirstTime_ = TRUE;
      defaultFile.fd_ = -1;
    }
 RWTValHashMapIterator<RWCString, LogFile, myHash,
                      std::equal_to<RWCString> > next(logFiles);
     

     while ( ++next ){
     TRACE_FLOW(trace, closeAllLogs, " while ( ++next ) OK");
       LogFile lf = next.value();
     
       if( lf.fd_ != -1 ) {
	 //lockf( lf.fd_, F_ULOCK, 0 );
	 close( lf.fd_ );
       }
    }
  }

  // HH80415
  logFiles.clear(); // Remove all logs from the collection
  // END HH80415
  
  TRACE_OUT(trace, closeAllLogs, "");
}   

//*****************************************************************************

void CHA_FileLogger::closeLog( RWCString fileId)
{
 TRACE_IN(trace, closeLog, "id:" << fileId );

  if (isLoggingOn()){
    if( fileId == DEFAULT_FILE_ID ) {
	//ofstream logFile;
	//logFile.attach( defaultFile.fd_ );
	
	//if( !logFile){
	TRACE_RETURN(trace, closeLog, "Internal error");
	//return;
	//}

      //logFile.close();
      if( defaultFile.fd_ != -1 ) {
	//lockf( defaultFile.fd_, F_ULOCK, 0 );
	close( defaultFile.fd_ );
	defaultFile.fd_ = -1;
      }

      defaultFile.name_ = RWCString();
      defaultFile.isFirstTime_ = TRUE; 
    }
    else {
      LogFile file;
      RWBoolean found = logFiles.findValue( fileId, file );
      if( found ) {
	//ofstream logFile;
	//logFile.attach( file.fd_ );

	//if( !logFile ){
	TRACE_RETURN(trace, closeLog, "Internal error");
	//return;
	//}

	//logFile.close();
	//lockf( defaultFile.fd_, F_ULOCK, 0 );
	close( file.fd_ );
	logFiles.remove( fileId );
      }
    }
      
    if( logFiles.entries() == 0 && defaultFile.name_ == "" )
      turnOff();
  }
  
 TRACE_OUT(trace, closeLog, "");
}

//*****************************************************************************

CHA_LogReturnCode CHA_FileLogger::logOverwrite(RWCString fileName, RWCString fileId)
{
   TRACE_IN(trace, logOverwrite, fileName);

    CHA_LogReturnCode res;

    fileName = trim(fileName);

    if (fileName.isNull()) {
      defaultFile.name_ = RWCString();
      res = CHA_LogReturnCode(CHA_LogReturnCode::INVALID_LOG_FILE);
    }
    else
    {
      //check if file exists
      struct stat buf;
      bool fileExists = false;
      if(stat(fileName.data(), &buf) == 0) {
        fileExists = true;
      }

      if( defaultFile.fd_ != -1 ){
	//flock( defaultFile.fd_, LOCK_UN );
	//lockf( defaultFile.fd_, F_ULOCK, 0 );
	close( defaultFile.fd_ );
	defaultFile.fd_ = -1;
      }

      int fd = open( fileName.data(),
                     O_CREAT | O_WRONLY,
                     S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH );
      //ofstream logFile;
      //logFile.open( fileName, ios::out, defaultLogFilePermission);
      
      if(fd == -1) {
	
	if( fileId == DEFAULT_FILE_ID ) 
	  defaultFile.name_ = RWCString();
	
	res = CHA_LogReturnCode(CHA_LogReturnCode::FILE_LOGGING_ERR,
				strerror(errno));
      }
      else {
        if (!fileExists) {
          //TORF-304533- explicity providing the file permission for "Others".
          if (chmod(fileName.data(), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH )) {
            res = CHA_LogReturnCode(CHA_LogReturnCode::FILE_LOGGING_ERR,
	                             strerror(errno));
            close(fd);
            return res;
          }
        }
 
	res = turnOn();
	if (res.isOkay()) {
	  //lockf( fd, F_LOCK, 0 );
	  if(fileId == DEFAULT_FILE_ID) {
	    defaultFile.name_ = ozt_normalisePath(fileName);
	    defaultFile.isFirstTime_ = TRUE;
	    defaultFile.fd_ = fd;
	  }
	  else {
	    LogFile lf;
	    lf.name_ = ozt_normalisePath(fileName);
	    lf.isFirstTime_ = TRUE;	
	    lf.fd_ = fd;
	    logFiles.insertKeyAndValue( fileId, lf );
	  }
	}
	else
	  close( fd );
      }
    }
    
    TRACE_RETURN(trace, logOverwrite, res);
    return res;
   
}
//*****************************************************************************

CHA_LogReturnCode CHA_FileLogger::logAppend( RWCString fileName, RWCString fileId ){

 TRACE_IN(trace, logAppend, fileName);
  
  CHA_LogReturnCode res(CHA_LogReturnCode::NO_PROBLEM);
  
 // fileName = trim(fileName);
  
  //check if the file name is correct
  if (fileName.isNull()) {
    defaultFile.name_ = RWCString();
    res = CHA_LogReturnCode(CHA_LogReturnCode::INVALID_LOG_FILE);
  }
  else {
    //check if file already exists
    struct stat buf;
    bool fileExists = false;
    if(stat(fileName.data(), &buf) == 0) {
      fileExists = true;
    }

    //try to open the file
    int fd = open( fileName.data(),
                   O_CREAT | O_WRONLY | O_APPEND,
                   S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH );

    if (fd == -1) {
      //file cannot be opened
      if( fileId == DEFAULT_FILE_ID ) {
	defaultFile.name_ = RWCString();
      }

      res = CHA_LogReturnCode(CHA_LogReturnCode::FILE_LOGGING_ERR,
			      strerror(errno));
    }
    else {
      if (!fileExists) {
        //TORF-304533- explicity providing the file permission for "Others".
        if (chmod(fileName.data(), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH )) {
          res = CHA_LogReturnCode(CHA_LogReturnCode::FILE_LOGGING_ERR,
                                  strerror(errno));
          close(fd);
          return res;
	}
      }

      //try to turn the logging on
	res = turnOn();
	
	if( res.isOkay() ) {
	  LogFile newLf;
	  newLf.name_ = ozt_normalisePath(fileName);
	  newLf.isFirstTime_ = TRUE;	
	  newLf.fd_ = fd;
	  
	  //check if the specified file has already been opened
	  
          //RWTValHashDictionaryIterator<RWCString,LogFile> next(logFiles);
RWTValHashMapIterator<RWCString, LogFile, myHash,
                      std::equal_to<RWCString> > next(logFiles);
	  
	  while ( ++next ){
	    LogFile lf = next.value();
	    RWCString id = next.key();
	    
	    if( newLf.name_ == lf.name_ && fileId != id ) {
	      close( fd );
	      res = CHA_LogReturnCode(CHA_LogReturnCode::LOG_ALREADY_OPEN, lf.name_ );
	      
	     TRACE_RETURN(trace, logAppend, res);
	      return res;
	    }
	    else if( newLf.name_ == lf.name_ && fileId == id ) {
              close( fd );
              return res;
            }
	  }
	  
	  //check if the specified file is already opened as default file
	  if( defaultFile.name_ == newLf.name_ && fileId != DEFAULT_FILE_ID ) {
	    close( fd );
	    res = CHA_LogReturnCode(CHA_LogReturnCode::LOG_ALREADY_OPEN, newLf.name_ );
	    
	    TRACE_RETURN(trace, logAppend, res);
	    return res;
          }
          else if( defaultFile.name_ == newLf.name_  && fileId == DEFAULT_FILE_ID ) {
            close( fd );
	    return( res );
          }

	  if(fileId == DEFAULT_FILE_ID) {
	    //check if the default file is already open
	    if(defaultFile.fd_ != -1){
	      close(defaultFile.fd_);
	    }
	  
	    defaultFile.name_ = newLf.name_;
	    defaultFile.fd_ = newLf.fd_;
	    defaultFile.isFirstTime_ = newLf.isFirstTime_; 
	  }
	  else {
		
	    //check if the specified log id has been used for the previously opened log files
//HI79116
            LogFile oldLf;
	    if( logFiles.findValue( fileId, oldLf ) ) {
	      //close the old log file
	      close( oldLf.fd_ );
	    }
	    //add the new log file to the map
	    logFiles.insertKeyAndValue( fileId, newLf );     
//END HI79116
	  }
	}
	else 
	  close( fd );
    }
    
    TRACE_RETURN(trace, logAppend, res);
    return res;
  }
}

//*****************************************************************************
void CHA_FileLogger::appendLine( LogFile&  lf, RWBoolean h, const RWCString& text ) {

  TRACE_IN(trace, appendLine, text);
  int result;

  result = lockf( lf.fd_, F_TLOCK, 0 );  //ADDED DUE TO TR HF51253

  if( h && lf.isFirstTime_ ) {
    lf.isFirstTime_ = FALSE;
    RWCString dummy = putHeader() + text;
    result = write( lf.fd_, dummy.data(), dummy.length() );
  }
  else {
    result = write( lf.fd_, text.data(), text.length() );
  }


  lockf( lf.fd_, F_ULOCK, 0 );

  TRACE_OUT(trace, appendLine, result);
}

//*****************************************************************************
void CHA_FileLogger::appendLog(RWBoolean h, const RWCString &newText)
{
    TRACE_FLOW(trace, appendLog, newText);
    char END_OF_TEXT = 0x03;
    RWCString etx(END_OF_TEXT);
    RWCString nxt(newText);
    RWCString empty("");
    size_t size=nxt.index(etx,0,RWCString::exact);
    size_t val=1;
    if(size!=RW_NPOS)
     {
       nxt=nxt.replace(size, val,empty);
     }


    // write to the deafult file
    if (defaultFile.name_ != "" ) {
      appendLine( defaultFile, h, nxt );
    }

    //write to the remaining log files

//    RWTValHashDictionaryIterator<RWCString,LogFile> next(logFiles);
RWTValHashMapIterator<RWCString, LogFile, myHash,
                      std::equal_to<RWCString> > next(logFiles);

    while ( ++next ){
      LogFile lf = next.value();
     
      appendLine( lf, h, nxt );
      
      //logFiles.remove( next.key() );
      //logFiles.insertKeyAndValue( next.key(), lf );
    }
}
