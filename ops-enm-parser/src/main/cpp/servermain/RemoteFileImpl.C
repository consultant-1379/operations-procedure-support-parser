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

#include "RemoteFileImpl.H"

#include <trace.H>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <rw/tvslist.h>

static std::string trace ="RemoteFileImpl";

RemoteFileImpl::RemoteFileImpl():MAX_DIRECTORY_LEN(255){}
RemoteFileImpl::~RemoteFileImpl(){}

char* RemoteFileImpl::GetHomeDir(const char* sUser)
throw (CORBA::SystemException){
//--------------------------------------------------------------------------
// Fully described in RemoteFileImpl.H
//--------------------------------------------------------------------------
  TRACE_IN(trace, GetHomeDir, "User:" << sUser);
  RWCString sHomeDir;
  if (strcmp(sUser, "") != 0) {
    sHomeDir = getpwnam(sUser)->pw_dir;
  } else {
    sHomeDir = getpwuid(geteuid())->pw_dir;;
  }
  TRACE_OUT(trace, GetHomeDir, "HomeDir: " << sHomeDir);
  return CORBA::string_dup(sHomeDir.data());  //Skall vara CORBA::string_dup
}


CORBA::Boolean RemoteFileImpl::IsNormal(const char* sPath)
throw (CORBA::SystemException){
//--------------------------------------------------------------------------
// Fully described in RemoteFileImpl.H
//--------------------------------------------------------------------------
  TRACE_IN(trace, IsNormal, "Dir:" << sPath);
  struct stat rFileStat;
  CORBA::Boolean b = (stat(sPath, &rFileStat) == 0 && S_ISREG(rFileStat.st_mode));
  RWCString s = (b)? "JA":"NEJ";
  TRACE_OUT(trace, IsNormal, sPath << "IsNormal?: " << s);
  return b;
}

CORBA::Boolean RemoteFileImpl::IsDirectory(const char* sPath)
throw (CORBA::SystemException){
//--------------------------------------------------------------------------
// Fully described in RemoteFileImpl.H
//--------------------------------------------------------------------------
  TRACE_IN(trace, IsDirectory, "Dir:" << sPath);
  struct stat rFileStat;
  CORBA::Boolean b = (stat(sPath, &rFileStat) == 0 && S_ISDIR(rFileStat.st_mode));
 TRACE_OUT(trace, IsDirectory, sPath << "IsDir?:" << b);
  return b;
}

CORBA::Boolean RemoteFileImpl::CanRead(const char* sPath)
                                       throw (CORBA::SystemException){
//--------------------------------------------------------------------------
// Fully described in RemoteFileImpl.H
//--------------------------------------------------------------------------
   TRACE_IN(trace, CanRead, "File: \"" << sPath << "\"");
    CORBA::Boolean rc = access(sPath, R_OK) == 0;
    TRACE_OUT(trace, CanRead, "returns: " << rc);
    return rc;
}

CORBA::Boolean RemoteFileImpl::CanWrite(const char* sPath)
                                        throw (CORBA::SystemException){
//--------------------------------------------------------------------------
// Fully described in RemoteFileImpl.H
//--------------------------------------------------------------------------
    return (access(sPath, W_OK) == 0);
}

CORBA::Boolean RemoteFileImpl::Exists(const char* sPath)
                                      throw (CORBA::SystemException){
//--------------------------------------------------------------------------
// Fully described in RemoteFileImpl.H
//--------------------------------------------------------------------------
    return (access(sPath, F_OK) == 0);
}

char* RemoteFileImpl::CreateFolder(const char* sDir)
                                   throw (CORBA::SystemException,
                                          OPS::FileViewException){
//--------------------------------------------------------------------------
// Fully described in RemoteFileImpl.H
//--------------------------------------------------------------------------
    RWCString sPath("");
    if(sDir != NULL){
	sPath = (RWCString)sDir + "/Untitled";
	if(mkdir(sPath, S_IRWXU) != 0) {
        //  TRACE_FLOW(trace, CreateFolder, "Failed to create folder: " << strerror(errno));
          if (errno == EEXIST) {
            throw OPS::FileViewException(OPS::ALREADY_EXIST);
          } else {
            throw OPS::FileViewException(OPS::NO_PERMISSION);
          }
        }
    }
    return CORBA::string_dup(sPath);;
}


OPS::stringList* RemoteFileImpl::GetFiles(const char* sDir)
					  throw (CORBA::SystemException,
                                                 OPS::FileViewMsgException) {

//--------------------------------------------------------------------------
// Fully described in RemoteFileImpl.H
//--------------------------------------------------------------------------

//  TRACE_IN(trace, GetFiles, "Dir: " << sDir);
  if(sDir == NULL) sDir = strdup("");
  RWCString sPath = sDir;

  if(sPath[(unsigned)0] != '/'){
    sPath = "/" + sPath;
   TRACE_FLOW(trace, GetFiles, "Changed dir to: " << sDir);
  }

  TRACE_FLOW(trace, GetFiles, "Listing dir: " << sPath);

  RWTValSlist<char*> fList;
  RWTValSlistIterator<char*> fListIterator(fList);

  errno = 0;
  DIR *dirp = opendir(sPath);

  if ( ! dirp ) {
      RWCString errorMsg(sPath);
      errorMsg.append(": ");
      errorMsg.append(strerror(errno));
     TRACE_FLOW(trace, GetFiles, "error: " << errorMsg.data());
      throw OPS::FileViewMsgException(errorMsg.data());
  }

  struct dirent dp;
  struct dirent *res;

  while (1) {

      int rc = readdir_r(dirp, &dp, &res);

      if (rc == 0) {
          if (res != NULL) {
              // Any files/directories starting with "." is filtered out:
              if (dp.d_name[0] == '.') {
                  continue;
              }
              fList.append(CORBA::string_dup(dp.d_name));
          } else {
              // No more files to read.
              break;
          }
      } else {
          break; // READ_ERROR;
      }
  }
  closedir(dirp);

  TRACE_FLOW(trace, GetFiles, fList.entries() << " entries");
  OPS::stringList *aFiles = new OPS::stringList();
  aFiles->length(fList.entries());

  for (int i=0 ; fListIterator() ; i++) {
      (*aFiles)[i] = fListIterator.key();
     TRACE_FLOW(trace, GetFiles, "file[" << i << "]: " << (*aFiles)[i]);
  }

  TRACE_OUT(trace, GetFiles, "");
  return aFiles;
}

OPS::stringList* RemoteFileImpl::GetContent(const char* sPath)
throw (CORBA::SystemException, OPS::FileViewException){
//--------------------------------------------------------------------------
// Fully described in RemoteFileImpl.H
//--------------------------------------------------------------------------
    TRACE_IN(trace, GetContent, "");

    ifstream rFile(sPath, ios::in);
    ifstream rFile2(sPath, ios::in);
    RWCString sALine;
    int nRows = 0;
    OPS::stringList *aFiles = new OPS::stringList();

    //sFile.open(sPath, ios::in);
    if(!rFile.good()) {
    //	TRACE_FLOW(trace, GetContent, "The user has no permissions to read the file");
    	rFile.close();
	rFile2.close();
    	throw OPS::FileViewException(OPS::NO_PERMISSION);
    }

    if(IsNormal(sPath) && rFile && rFile2){
	// Count rows and allocate structure.
	while(sALine.readLine(rFile, FALSE))
	    nRows++;
	aFiles->length(nRows);

	// Fill the structure.
	nRows = 0;
	while(sALine.readLine(rFile2, FALSE)){
	  if(sALine.isNull())
	    sALine = "";
	//  TRACE_FLOW(trace, GetContent, nRows << ":" << sALine);
	  (*aFiles)[nRows++] = CORBA::string_dup(sALine.data());
	}
	rFile.close();
	rFile2.close();
    }
    else{
	aFiles->length(0); // Att testa!
    }

    TRACE_OUT(trace, GetContent, "");
    return aFiles;
}

void RemoteFileImpl::PutContent(const char* sPath,
				const char* theContent)
     throw (CORBA::SystemException, OPS::FileViewException){
//--------------------------------------------------------------------------
// Fully described in RemoteFileImpl.H
//--------------------------------------------------------------------------
   TRACE_IN(trace, PutContent, sPath);
    
    char buf[100];
    int i;
    
    RWCString sBakPath = RWCString(sPath) + ".bak";

    FILE* in = fopen(sPath, "r");
    if(in == NULL) {
    	// The file doesn't exist, don't create an backup.
    	//fclose(in);
    }else {
    	FILE* bakFile = fopen(sBakPath, "w");
    	if(bakFile == 0) {
    	    fclose(in);
    	    throw OPS::FileViewException(OPS::NO_PERMISSION);
    	}
    
    	/* copy the file contents to the backup file */
    	while (i=fread(buf,1,100,in))
       	    if (fwrite(buf,1,i,bakFile)!=i)
            	break;
    
    	fclose(in);
    	fclose(bakFile);
    }

    FILE* orginalFile = fopen(sPath, "w");

    fprintf(orginalFile, "%s", theContent);
    if(fclose(orginalFile) == EOF) {
      throw OPS::FileViewException(OPS::NO_SPACE);
    }

    TRACE_OUT(trace, PutContent, sPath);
}
