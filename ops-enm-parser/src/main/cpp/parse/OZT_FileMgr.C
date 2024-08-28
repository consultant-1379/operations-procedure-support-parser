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


#include "OZT_FileMgr.H"
#include "OZT_Misc.H"
#include <limits.h>
#include <errno.h>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <rw/tools/regex.h>

//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_FileMgr";


//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_FileMgr.C,v 21.0 1996/08/23 12:44:04 ehsgrap Rel $";


//*****************************************************************************


OZT_FileMgr::OZT_FileMgr()
{
    TRACE_IN(trace, OZT_FileMgr, "");

    lastLineIndex = 0;

    TRACE_OUT(trace, OZT_FileMgr, "");
}




OZT_FileMgr::~OZT_FileMgr()
{
    storedFile.close();
}




RWCString OZT_FileMgr::getDir()
{
    RWCString temp(ozt_currDir());

    if (temp[temp.length() - 1] != '/')
        temp.append('/');

    TRACE_FLOW(trace, getDir, temp);
    return temp;
}



OZT_Result OZT_FileMgr::chDir(RWCString dir)
{
    TRACE_IN(trace, chDir, dir);

    OZT_Result res;

    if (chdir(ozt_normalisePath(dir)) == 0)
        res = OZT_Result(OZT_Result::NO_PROBLEM);
    else
        res = OZT_Result(OZT_Result::FAILED, strerror(errno));

    TRACE_RETURN(trace, chDir, res.filtered());
    return res.filtered(); 
}



OZT_Result OZT_FileMgr::rmFile(RWCString fileName)
{
    TRACE_IN(trace, rmFile, fileName);

    struct stat buf;
    OZT_Result  res;

    fileName = ozt_normalisePath(fileName);

    if (storedFileName == fileName)
    {
        storedFileName = RWCString();
        storedFile.close();
    }

    // Get file status
    if (stat(fileName.data(), &buf) == 0)
        // the file exists
    {
        if (S_ISDIR(buf.st_mode))
            // The path points to a directory.
        {
            res = OZT_Result(OZT_Result::PATH_IS_DIR);
        }
        /*
         * This code segment can be uncommented so that only files
         * that the user has write permission on can be removed.
         * That way @ERASE works like "/bin/rm" instead of "/bin/rm -f"
         * which is the current behaviour with the check commented out.
         * To remove a file it is really only necessary to have execute and
         * write permission ON THE DIRECTORY containing the file.

        else if (access(fileName.data(), W_OK) == -1)
            // No write permission on the file
        {
            res = OZT_Result(OZT_Result::FAILED, strerror(errno));
        }
        */
        else if (unlink(fileName.data()) == 0)
            // The file was deleted successfully.
        {
            
            res = OZT_Result(OZT_Result::NO_PROBLEM);
        }
        else
            // Other reason, report it.  We get here if we don't have
            // directory write permission for example in which case
            // the unlink() above failed...
        {
            res = OZT_Result(OZT_Result::FAILED, strerror(errno));
        }
    }
    else if (errno == ENOENT)
        // The file did not exist so, according to the language
        // definition, it's okay.
    {
        res = OZT_Result(OZT_Result::NO_PROBLEM);
    }
    else
        // Whatever the reason, report it.
    {
        res = OZT_Result(OZT_Result::FAILED, strerror(errno));
    }
    
    TRACE_RETURN(trace, rmFile, res.filtered());
    return res.filtered(); 
}

OZT_Result OZT_FileMgr::closeReadFile() {
  TRACE_IN(trace, closeReadFile, "");
  
  if (!storedFileName.isNull() )
    storedFile.close();
  
  storedFileName = RWCString();
  
  return OZT_Result(OZT_Result::NO_PROBLEM);

}

OZT_Result OZT_FileMgr::getFileLength( const RWCString& fileName, long& nrOfLines ) {
    TRACE_IN(trace, getFileLength, fileName);
    
    OZT_Result res;
    ifstream fileStream;
    struct stat buf;
    nrOfLines= 0L;

    //check the name
    if (fileName.isNull()) {
	res = OZT_Result(OZT_Result::FILE_OP_ERR);
	TRACE_RETURN(trace, getFileLength, res.filtered());
	return res.filtered();
    }

    RWCString normalisedName = ozt_normalisePath(fileName);

    //check if the path points to a directory
    if ((stat(fileName.data(), &buf) == 0) && S_ISDIR(buf.st_mode)) {
        res = OZT_Result(OZT_Result::PATH_IS_DIR);
        TRACE_RETURN(trace, getFileLength, res.filtered());
        return res.filtered();
    }

    //open the file
    fileStream.open(fileName.data(), ios::in);
    if (fileStream.fail()) {
	res = OZT_Result(OZT_Result::FILE_OP_ERR, strerror(errno));
	TRACE_RETURN(trace, getFileLength, res.filtered());
	return res.filtered();
    }
 
    //count the lines
    while( !fileStream.eof() ) {
	RWCString line;
	line.readLine( fileStream, FALSE );
	nrOfLines++;
    }
    
    //close the file
    fileStream.close();
    
    //return without problems
    res = OZT_Result(OZT_Result::NO_PROBLEM);
    TRACE_RETURN(trace, getFileLength, res.filtered());
    return res.filtered();
}

OZT_Result OZT_FileMgr::openReadFile(RWCString fileName)
{
    TRACE_IN(trace, openReadFile, fileName);

    OZT_Result  res;
    struct stat buf;

    // Reset the variables used by readLine().
    lastReadLine = RWCString();
    lastLineIndex = 0; //HF52958
    lastReadResult = OZT_Result(OZT_Result::NO_PROBLEM);

    if (fileName.isNull())
    {
    	TRACE_FLOW(trace, RWCString, "stored file - null filename");
      if (!storedFileName.isNull())
	      storedFile.close();
      storedFileName = RWCString();
      return OZT_Result(OZT_Result::FILE_OP_ERR);
    }
    
    fileName = ozt_normalisePath(fileName);
    if ((stat(fileName.data(), &buf) == 0) && S_ISDIR(buf.st_mode)) {
      // the path points to a directory
      res = OZT_Result(OZT_Result::PATH_IS_DIR);
      TRACE_RETURN(trace, openReadFile, res.filtered());
      return res.filtered();
    }
 
    //close previouslly opened file
    if (!storedFileName.isNull()){
      storedFileName = RWCString();
      storedFile.close();
    } 
    
    if( !storedFile.rdbuf()->is_open() ) {
      storedFile.open(fileName.data(), ios::in);
      if (storedFile.fail()) {
        TRACE_FLOW(trace, RWCString, "stored file fail");
        res = OZT_Result(OZT_Result::FAILED, strerror(errno));
      } else {
        TRACE_FLOW(trace, RWCString, "stored file ok");
	      storedFileName = fileName;
	      res = OZT_Result(OZT_Result::NO_PROBLEM);
      }
    }
    else {
      res = OZT_Result(OZT_Result::NO_PROBLEM);
    }

    TRACE_RETURN(trace, openReadFile, res.filtered());
    return res.filtered();
}



OZT_Result OZT_FileMgr::mkDir(RWCString dir)
{
    TRACE_IN(trace, mkDir, dir);

    struct stat buf;
    OZT_Result  res;

    dir = ozt_normalisePath(dir);

    if ((stat(dir.data(), &buf) == 0) && !S_ISDIR(buf.st_mode))
    {
        res = OZT_Result(OZT_Result::FILE_OP_ERR);
    }
    else if (mkdir(dir, 07777) == 0)
        // the directory was created successfully
    {
        res = OZT_Result(OZT_Result::NO_PROBLEM);
    }
    else if (errno == EEXIST)
        // dir already exists
    {
        res = OZT_Result(OZT_Result::NO_PROBLEM);
    }
    else
        // whatever went wrong with mkdir()
    {
        res = OZT_Result(OZT_Result::FAILED, strerror(errno));
    }
    TRACE_RETURN(trace, mkDir, res.filtered());
    return res.filtered();
}



OZT_Result OZT_FileMgr::rmDir(RWCString dir)
{
    TRACE_IN(trace, rmDir, dir);

    OZT_Result  res;

    dir = ozt_normalisePath(dir);

    /*
     * This code segment can be uncommented so that only files
     * that the user has write permission on can be removed.
     * That way @ERASE works like "/bin/rm" instead of "/bin/rm -f"
     * which is the current behaviour with the check commented out.
     * To remove a directory it must be empty and then it is really
     * only necessary to have execute and write permission ON THE
     * DIRECTORY containing the file.
    
     if (access(dir.data(), W_OK) == -1)
         // no write permission
     {
     res = OZT_Result(OZT_Result::FAILED, strerror(errno));
     }
     else

     */
    
    if (rmdir(dir.data()) == 0)
    {
        res = OZT_Result(OZT_Result::NO_PROBLEM);
    }
    else if (errno == ENOENT)
        // directory did not exist
    {
        res = OZT_Result(OZT_Result::NO_PROBLEM);
    }
    else
        // something else went wrong
    {
        res = OZT_Result(OZT_Result::FAILED, strerror(errno));
    }
    
    TRACE_RETURN(trace, rmDir, res.filtered());
    return res.filtered();
}



OZT_Result OZT_FileMgr::reNameFile(RWCString oldName, 
                                   RWCString newName)
{
    TRACE_IN(trace, reNameFile, oldName << ", " << newName);

    OZT_Result res;
    struct stat oldBuf;
    struct stat newBuf;    

    oldName = ozt_normalisePath(oldName);
    newName = ozt_normalisePath(newName);
    
    // If `oldName' and `newName' both specifies the same type of
    // file, i.e. an ordinary file or a directory, that is fine.
    // Otherwise, if `newName' is a directory and `oldName' is not, we
    // need to append the actual filename part of `oldName' to
    // `newName' for rename() to work.
    if ((stat(oldName.data(), &oldBuf) == 0) &&
        (stat(newName.data(), &newBuf) == 0))
    {
        if ((!S_ISDIR(oldBuf.st_mode)) && S_ISDIR(newBuf.st_mode))
        {
            size_t lastSlash = oldName.last('/');
            
            if (newName[newName.length()-1] != '/')
            {
                newName.append("/");
            }
            
            if (lastSlash == RW_NPOS)
            {
                newName.append(oldName);
            }
            else
            {
                size_t extent = oldName.length() - lastSlash - 1;
                
                newName.append(oldName(lastSlash+1, extent));
            }
        }
    }

    if ((access(newName.data(), W_OK) == -1) && (errno != ENOENT))
        // No write permission on already existing `newName' file.
    {
        res = OZT_Result(OZT_Result::FAILED, strerror(errno));
    }
    else if (rename(oldName.data(), newName.data()) == 0)
        // The file (or directory) was successfully renamed.
    {
        res = OZT_Result(OZT_Result::NO_PROBLEM);
    }
    else
        // Whatever the reason for failure, report it.
    {
        res = OZT_Result(OZT_Result::FAILED, strerror(errno));
    }

    TRACE_RETURN(trace, reNameFile, res.filtered());
    return res.filtered();
}

OZT_Result OZT_FileMgr::readLine( RWCString& line,
				  const RWCString& lineNrStr ) {
  
  TRACE_IN(trace, readLine, "linenr <" << lineNrStr << ">"); 
  
  OZT_Result result;
  size_t len;
  static RWTRegex<char> rexp("^[+]?[0-9]+$");

  if( rexp.index( lineNrStr, &len ) == RW_NPOS ) {
    result.code = OZT_Result::INVALID_VALUE;
    return result;
  }

  long lineNr = atol( lineNrStr.data() );

  if (lastReadLine.isNull()) {

    if( !read( lineNr ) ) {
       if (storedFile.eof())
	 lastReadResult = OZT_Result(OZT_Result::HIT_EOF);
       else
	 lastReadResult = OZT_Result(OZT_Result::FILE_OP_ERR);
    }
    else {
      // successfully read a line
      
      // RWCString::readLine() has already chopped off the line
      // at the newline, '\n', so we need to add it again for
      // the algorithm below to work properly.  Otherwise, we'd
      // loose an empty line if the line actually read in ends
      // with any of the "newLine" characters defined below
      // (except for '\n' of course).
      
      TRACE_FLOW(trace, readLine, "reading line:" << lineNr );
      lastLineIndex == lineNr;
      
      lastReadLine.append("\n");
      lastReadResult = OZT_Result(OZT_Result::NO_PROBLEM);
    }
  }    

  // Split the last read line at the first RETURN, NEWLINE,
  // FORMFEED, or a vertical tab character encountered.
  static RWTRegex<char> newLine("[\f\n\v]"); // No CR included. No '\v' on p.43-2.
  size_t lineLength;
  
  // lineLength = lastReadLine.index(newLine, &ext);
  lineLength = newLine.index(lastReadLine);
  if (lineLength != RW_NPOS)
    // "newline" found
    {
      line = "";
      line.append(lastReadLine, lineLength); // don't include the "newLine"
      lastReadLine.remove(0, lineLength+1);  // remove the "newLine" too
      result = OZT_Result(OZT_Result::NO_PROBLEM);
    }
  else
        // no "newline" found; ordinary line
    {
      line = lastReadLine;
      lastReadLine = "";
      result = lastReadResult;
    }
  
  TRACE_RETURN(trace, readLine, result.filtered());
  return result.filtered();
  
}

RWBoolean OZT_FileMgr::read(long linenr ) {
  
  TRACE_IN(trace, read, linenr);
  // read a new line from the file
  if( linenr <=  lastLineIndex ) {
    RWCString file = storedFileName;
    closeReadFile();
    openReadFile( file );
    lastLineIndex = 0;
  }
  
  while( lastLineIndex < linenr ){
    if( !lastReadLine.readLine( storedFile, FALSE ) ){
      TRACE_RETURN( trace, read, FALSE );
      return FALSE;
    }
    lastLineIndex++;
  }
    
  TRACE_FLOW( trace, read, "line read:" << lastReadLine );
  TRACE_RETURN( trace, read, TRUE );
  return TRUE;
}

OZT_Result OZT_FileMgr::readLine(RWCString &line){
    
  TRACE_IN(trace, readLine, "line <" << line << ">");
  
  OZT_Result result;
  
  if (lastReadLine.isNull()) {

    // read a new line from the file
      TRACE_IN(trace, readLine, "line <" << line << ">");
      
      if ( !read( lastLineIndex + 1 )) {
	  // something went wrong
	  
	  if (storedFile.eof())
	      lastReadResult = OZT_Result(OZT_Result::HIT_EOF);
	  else
	      lastReadResult = OZT_Result(OZT_Result::FILE_OP_ERR);
      }
      else {
	// successfully read a line
	  // RWCString::readLine() has already chopped off the line
	  // at the newline, '\n', so we need to add it again for
	  // the algorithm below to work properly.  Otherwise, we'd
	  // loose an empty line if the line actually read in ends
	  // with any of the "newLine" characters defined below
	  // (except for '\n' of course).
	  
	  TRACE_IN(trace, readLine, "reading line:" << lastLineIndex );
	  
	  lastReadLine.append("\n");
	  lastReadResult = OZT_Result(OZT_Result::NO_PROBLEM);
        }
  }
  
  // Split the last read line at the first RETURN, NEWLINE,
  // FORMFEED, or a vertical tab character encountered.
  static RWTRegex<char> newLine("[\f\n\v]"); // No CR included. No '\v' on p.43-2.
  size_t lineLength;
  
  lineLength = newLine.index(lastReadLine);
  if (lineLength != RW_NPOS) {
      // "newline" found
    
      line = "";
      line.append(lastReadLine, lineLength); // don't include the "newLine"
      lastReadLine.remove(0, lineLength+1);  // remove the "newLine" too
      result = OZT_Result(OZT_Result::NO_PROBLEM);
  }
  else {
      // no "newline" found; ordinary line
      line = lastReadLine;
      lastReadLine = "";
      result = lastReadResult;
  }
  
  TRACE_RETURN(trace, readLine, result.filtered());
  return result.filtered();
}

//****************************************************************

OZT_Result OZT_FileMgr::writeLine(RWCString fileName,
				  const RWCString& lineNrStr,
                                  const RWCString &str)
{
    TRACE_IN(trace, writeLine, fileName << ", < " << str << ">");

  OZT_Result res;
  size_t len;
  long offset = -1;
  fstream wFile;
  RWCString stringToWrite;
  int desc = -1;

  stringToWrite = str;

  //add the new line character at the end
  stringToWrite.append("\n" );
  
  //normalise the file path

  fileName = ozt_normalisePath(fileName);
  static RWTRegex<char>      rexp("^[+]?[0-9]+$");

  //check if file already exists
  struct stat buf;
  bool fileExists = false;
  if(stat(fileName.data(), &buf) == 0) {
      fileExists = true;
  }

  //if the line number is defined...
  if( lineNrStr != "" ) {
    //check if the line number string contains only numbers
    if( rexp.index( lineNrStr, &len ) == RW_NPOS ) {
      res.code = OZT_Result::INVALID_VALUE;
      return res.filtered();
    }
    //convert to long
    long lineNr =  atol( lineNrStr.data() );
    
    //calculate where to write
    offset = getOffset( fileName, lineNr );

    //the offset is not OK; probably the line number is to high ( there is no so manny lines in the file )
    if( offset == -1 ) {
      res.code = OZT_Result::INVALID_VALUE;
      return res.filtered();
    }
    // open the file (create if it doesn't exist)
    desc = open( fileName.data(),
                 O_WRONLY | O_CREAT,
                 S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH );
    
    if( desc == -1 ){
      res = OZT_Result(OZT_Result::FAILED, strerror(errno));
      TRACE_RETURN(trace, writeLine, res.filtered());
      return res.filtered();
    }

    //seek to the offset position
    off_t newOffset = lseek( desc, offset, SEEK_SET );
    
    if( newOffset ==  (off_t)-1 ) {
      res = OZT_Result(OZT_Result::FAILED, strerror(errno));
      TRACE_RETURN(trace, writeLine, res.filtered());
      close(desc);
      return res.filtered();
    }
  }
  else {
    //open the file for appending
    desc = open( fileName.data(),
                 O_WRONLY | O_APPEND | O_CREAT,
                 S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH );
    
    if( desc == -1 ){
      res = OZT_Result(OZT_Result::FAILED, strerror(errno));
      TRACE_RETURN(trace, writeLine, res.filtered());
      return res.filtered();
    }
  }

  if (!fileExists) {
    //TORF-304533- explicity providing the file Read permission to "Others".
    if( chmod(fileName.data(), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)) {
      res = OZT_Result(OZT_Result::FAILED, strerror(errno));
      TRACE_RETURN(trace, writeLine, res.filtered());
      close (desc);
      return res.filtered();
    }
  }

  //write the string
  int nrBytes = write( desc, stringToWrite.data(), stringToWrite.length() );

  //close the file
  close( desc );
  
  if( nrBytes == -1 ) {
    res = OZT_Result(OZT_Result::FAILED, strerror(errno));
    TRACE_RETURN(trace, writeLine, res.filtered());
    return res.filtered();
  }
    
  TRACE_RETURN(trace, writeLine, "NO_PROBLEM");
  return OZT_Result(OZT_Result::NO_PROBLEM); 
}

//****************************************************************

long OZT_FileMgr::getOffset( const RWCString& fileName,
			     long lineNr ) {

  long offset = 0;
  RWCString currLine;
  RWCString lineToReplace;

  ifstream wFile;

  //open the file
  wFile.open(fileName.data(), ios::in);
  //the file probably doesn't exist; write in the begining
  if( wFile.fail() )
    return offset;

  //read the lines
  for( long i = 1; i < lineNr; i++ ) {
    if( !currLine.readLine( wFile, FALSE ) ) {
      wFile.close();
      return -1;
    }
    //add to the offset
    offset += currLine.length();
    
    //new line char
    offset += 1;
  }
 
  //close the file
  wFile.close();

  return offset;

  TRACE_RETURN(trace, writeLine, "NO_PROBLEM");
}
