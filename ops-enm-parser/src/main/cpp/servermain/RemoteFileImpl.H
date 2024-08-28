//*****************************************************************************
//
// NAME
//      RemoteFileView.H
//

// COPYRIGHT
//  COPYRIGHT Ericsson Radio Systems AB 2000, 2001
// 
//  The copyright to the computer program(s) herein is the property
//  of ERICSSON RADIO SYSTEMS  AB, Sweden. The programs may be used
//  and/or copied only with the written permission from ERICSSON
//  RADIO SYSTEMS AB or in accordance with the terms and conditions
//  stipulated in the agreement/contract under which the program(s)
//  have been supplied.

// DESCRIPTION
//   This class implements the FileView interface of the OPS idl
//   interface, which is used for OPS clients to see the file
//   system on the server side.
 
// DOCUMENT NO
//  CXC 172 2483

//**************************************************************************

#ifndef REMOTE_FILE_VIEW_H
#define REMOTE_FILE_VIEW_H

#include "OPSS.H"
#include <iostream>
#include <fstream>
#include <rw/cstring.h>
#include <rw/ctoken.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
 
using namespace std;
class RemoteFileImpl : public virtual POA_OPS::FileView {

public:
    
    RemoteFileImpl();
  // Description: 
  //     The constructor.
   
    ~RemoteFileImpl();
  // Description: 
  //     The constructor.
    
    virtual CORBA::Boolean CanRead(const char* sPath)
                                   throw (CORBA::SystemException);
  // Description: 
  //     ...

    virtual CORBA::Boolean CanWrite(const char* sPath)
                                    throw (CORBA::SystemException);
  // Description: 
  //     ...

    virtual CORBA::Boolean Exists(const char* sPath)
                                  throw (CORBA::SystemException);
  // Description: 
  //     ...

    virtual CORBA::Boolean IsDirectory(const char* sPath)
                                       throw (CORBA::SystemException);
  // Description: 
  //     ...

    CORBA::Boolean IsNormal(const char* sPath)
                            throw (CORBA::SystemException);
  // Description: 
  //     Answers if a given file is a normal file, i.e. not directory, link etc.

    virtual char* GetHomeDir(const char* sUser)
                             throw (CORBA::SystemException);
  // Description:
  //  ...

    virtual OPS::stringList* GetFiles(const char* sDir)
                                      throw (CORBA::SystemException,
                                             OPS::FileViewMsgException);
  // Description:
  //   Returns the files contained in a directory. If bUserFileHiding
  //   is true, files with an initial "." are not returned.

    virtual char* CreateFolder(const char* sDir) 
                               throw (CORBA::SystemException,
                                      OPS::FileViewException);
  // Description:
  //   ...


    virtual OPS::stringList* GetContent(const char* sPath)
            throw (CORBA::SystemException, OPS::FileViewException);
  // Description:
  //   Returns the content of a normal file.

  virtual void PutContent(const char* sPath, 
                          const char* theContent)
    throw (CORBA::SystemException, OPS::FileViewException);
  // Descripiton:
  //   Saves textual content to a given file.

private:
    const int MAX_DIRECTORY_LEN;
    
};

#endif
