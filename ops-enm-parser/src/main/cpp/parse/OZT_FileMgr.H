// RCS revision handling
// $Id: OZT_FileMgr.H,v 21.0 1996/08/23 12:42:40 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_FileMgr - Class for file system related access
// .LIBRARY CHOZTBIN
// .PAGENAME OZT_FileMgr
// .LEFT_FOOTER Ericsson HP

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
// 	The class OZT_FileMgr provides the implementation of file system
//      related access, such as opening and writing a file.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	190 89-CAA 134 2016

// AUTHOR 
// 	1994-10-12 by Eric Tse (epatse@epa.ericsson.se)

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_FileMgr.H,v $
// 	Revision 21.0  1996/08/23 12:42:40  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 07:57:20  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:22:14  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:21:13  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:01:46  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:57:07  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:02:38  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:16:55  17:16:55  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.1  1995/10/23 15:42:42  ehsjasa
// 	Removed unnecessary inclusion of "rw/tvordvec.h".
//
// 	Revision 13.0  1995/10/07 12:01:10  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.1  1995/10/06 09:14:48  ehsjasa
// 	Added a constant that defines the default permission on the created
// 	file. The value is now -rw-rw-rw- instead of (the library default)
// 	-rw-r--r--.
//
// 	Revision 12.0  1995/09/22 14:08:50  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:24:52  09:24:52  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.2  1995/09/05 13:48:41  ehsjasa
// 	New private attributes `lastReadLine' and `lastReadResult' introduced.
// 	Only used in readLine() and reset in openReadFile(). This fixed
// 	obvious bug in 10.1.
//
// 	Revision 10.1  1995/08/28 07:43:36  ehsjasa
// 	Renamed methods readFile() to readLine() and writeFile() to
// 	writeLine(). Updated the description of readLine() according to the
// 	new treatment of LF, CR, VT, FF...
//
// 	Revision 10.0  1995/08/02 11:01:57  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:37:42  14:37:42  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.1  95/06/28  14:30:45  14:30:45  epanyc (Nelson Cheng VK/EHS/PXE)
//      comment added
//      
//      Revision 8.0  1995/06/07  17:08:52  cmcha
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//
//      Revision 7.0  95/04/16  12:16:08  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 6.0  95/03/17  20:05:11  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 5.0  95/03/16  20:30:58  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 4.0  95/02/23  21:45:45  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB4, J Grape (EHSGRAP).
//      
//      Revision 3.0  95/02/06  20:57:20  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 2.4  95/01/25  13:10:01  epanyc (Nelson Cheng VK/EHS/PXE)
//      prototypes changed
//      
//      Revision 2.3  94/12/21  16:07:35  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//      
//      Revision 2.0  94/12/21  13:51:46  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//      
//      Revision 1.6  1994/11/28  11:09:43  epatse
//      *** empty log message ***
//
//      Revision 1.5  1994/11/16  12:39:17  epatse
//      change reName back to reNameFile.
//
//      Revision 1.4  1994/11/14  09:08:11  epatse
//      Check in for epanyc
//
//      Revision 1.3  1994/10/14  16:15:00  epatse
//      Cap Trace been added
//
//      Revision 1.2  1994/10/12  15:18:47  epatse
//      check in for epanyc 12/10/94
//
//      Revision 1.1  1994/10/12  11:56:56  epatse
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
//	TB53_OZ 1995-11-29      J Grape (EHSGRAP)       RCS rev 15.0
//	POW_TB3 1995-11-20      J Sandquist (EHSJASA)   RCS rev 14.0
//	PRE_XM221995-10-07      J Sandquist (EHSJASA)   RCS rev 13.0
//	EC5_OZ  1995-09-22      J Sandquist (EHSJASA)   RCS rev 12.0
//	EC4_OZ  1995-09-14      J Sandquist (EHSJASA)   RCS rev 11.0
//	EC3_OZ  1995-08-02      J Sandquist (EHSJASA)   RCS rev 10.0
//	EC2_OZ  1995-06-29      J Grape (EHSGRAP)       RCS rev 9.0
//	TB5_2_OZ1995-06-07      J Grape (EHSGRAP)       RCS rev 8.0
//	TB5_1_OZ1995-04-16      J Grape (EHSGRAP)       RCS rev 7.0
//	TB51_OZ 1995-03-17      ehscama                 RCS rev 6.0
//	TB5_OZ  1995-03-16      ehscama                 RCS rev 5.0
//	TB4     1995-02-23      J Grape (EHSGRAP)       RCS rev 4.0
//	TB3     1995-02-06      J Grape (EHSGRAP)       RCS rev 3.0
//	TB2     1994-12-21      J Grape (EHSGRAP)       RCS rev 2.3
//	TB2     1994-12-21      J Grape (EHSGRAP)       RCS rev 2.0
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	tools.h++

//*****************************************************************************

#ifndef OZT_FILEMGR_H
#define OZT_FILEMGR_H

#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fstream>
#include <rw/cstring.h>
#include <OZT_ErrHandling.H>

//*****************************************************************************

const RWCString newLine("");
const RWCString append("");
    // Only needed because the compiler reports that that the
    // declaration of writeLine() is too complex otherwise.

const int defaultFilePermission = 0666;
    // Default permission (octal) on the file.  The umask value is
    // then automatically applied to this value at file creation time.

//*****************************************************************************

class OZT_FileMgr {
public:
    OZT_FileMgr();
    // Description
    //     Constructor.

    ~OZT_FileMgr();
    // Description
    //     Destructor.

    RWCString   getDir();
    // Description
    //     Retrieves the current directory.
    // Return value
    //     The current directory in absolute path. The path is always ended
    //     with a slash (/).

    OZT_Result  chDir(RWCString dir);
    // Description
    //     Change the current directory.
    // Parameter
    //     dir    IN: the new directory. Can be an absolute or a relative path.
    //                Tilde (~) is accepted.
    // Return value
    //     A result object telling whether the operation succeeds or not.

    OZT_Result  mkDir(RWCString dir);
    // Description
    //     Make a new directory.
    // Parameter
    //     dir    IN: the directory to be created. Can be an absolute or
    //                a relative path. Tilde (~) is accepted.
    // Return value
    //     A result object telling whether the operation succeeds or not.

    OZT_Result  rmDir(RWCString dir);
    // Description
    //     Remove a directory.
    // Parameter
    //     dir    IN: the directory to be removed. Can be an absolute or
    //                a relative path. Tilde (~) is accepted.
    // Return value
    //     A result object telling whether the operation succeeds or not.

    OZT_Result  rmFile(RWCString fileName);
    // Description
    //     Remove a file.
    // Parameter
    //     fileName  IN: the name of the file to be removed. Can be an
    //                   absolute or a relative path. Tilde (~) is accepted.
    // Return value
    //     A result object telling whether the operation succeeds or not.
 
    OZT_Result  openReadFile(RWCString fileName);
    // Description
    //     Open a file for subsequent reading via OZT_FileMgr::readLine().
    //     This function always closes the previously opened file, if any.
    // Parameter
    //     fileName  IN: the name of the file to be opened for reading. Can
    //                   be an absolute or a relative path. Tilde (~) is
    //                   accepted.
    // Return value
    //     A result object telling whether the operation succeeds or not.

    OZT_Result  closeReadFile();
    // Description
    //     Close the file opened previously via OZT_FileMgr::openReadFile().
    // Return value
    //     A result object telling whether the operation succeeds or not.

    OZT_Result  reNameFile(RWCString oldName, RWCString newName);
    // Description
    //     Rename a file.
    // Parameter
    //     oldName      IN: the path name of the file to be renamed.
    //     newName      IN: the new path name.
    // Return value
    //     A result object telling whether the operation succeeds or not.

  OZT_Result  readLine(RWCString &line);

  OZT_Result getFileLength( const RWCString& fileName, long& nrOfLines );

  RWBoolean read(long linenr );

  OZT_Result readLine( RWCString& line,
		       const RWCString& lineNrStr );
    // Description
    //     Read a line (up to a newline, line feed, form feed,
    //     vertical tab character or EOF) from the file opened
    //     previously by OZT_FileMgr::openReadFile(). The terminating
    //     character is removed from the input stream but not stored in `line'.
    // Parameter
    //     line    OUT: the line read from the file.
    // Return value
    //     A result object telling whether the operation succeeds or not.

    OZT_Result  writeLine(RWCString fileName, 
			  const RWCString& lineNrStr = append,
                          const RWCString &str = newLine);
    // Description
    //     Write a line to a file.
    // Parameter
    //     fileName    IN: the path name of the file to be written.
    //     str         IN: the line to be written to the file.
    // Return value
    //     A result object telling whether the operation succeeds or not.

private:
    long getOffset( const RWCString& fileName,
		    long lineNr );
    
    ifstream   storedFile;	 // file stream for the read file
    RWCString  storedFileName;   // file name for the read file
    long lastLineIndex;

    RWCString  lastReadLine;     // Used by readLine(), reset by openReadFile()
    OZT_Result lastReadResult;   // Used by readLine(), reset by openReadFile()

};

#endif
