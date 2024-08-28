// RCS revision handling
// $Id: OZT_CDFFile.H,v 21.0 1996/08/23 12:46:15 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_CDFFile - Hold information about a file loaded in the debugger
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
// 	Contains all the information specific to a file that has been loaded
//      into the debugger, including name, directory, tag and breakpoint
//      positions. It does not contain the file contents.
//
//      There is one instance of this class for each file loaded.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	%EriDoc_no:%

// AUTHOR 
// 	<Date> by ETL/XV/B Neil Harding

// .REVISION <for public API>
//	<Revision state>
//	<Revision date>	  	

// .REVISION <for internal header files>
//	%EriDoc_rev:%
//	%EriDoc_date:%  	

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_CDFFile.H,v $
// 	Revision 21.0  1996/08/23 12:46:15  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 08:00:36  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:23:47  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:24:49  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:06:22  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:59:26  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:04:39  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.1  95/11/28  14:50:38  14:50:38  epanyc (Nelson Cheng VK/EHS/PXE)
//      a number of methods added for better encapsulation
//      
//      Revision 14.0  1995/11/20  17:20:23  ehsjasa
//      Made release POW_TB3, J Sandquist (EHSJASA).
//
// 	Revision 13.0  1995/10/07 12:03:46  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:12:45  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:27:26  09:27:26  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:06:01  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:41:16  14:41:16  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.0  95/06/07  17:12:41  17:12:41  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 7.1  95/05/18  11:07:18  11:07:18  etlnei (Neil Harding VK/EHS/PXE)
//      added variable to hold the first text marker
//      
//      Revision 7.0  1995/04/16  12:19:06  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.0  95/03/17  20:08:13  20:08:13  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 5.0  95/03/16  20:33:28  20:33:28  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 4.0  95/02/23  21:47:56  21:47:56  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB4, J Grape (EHSGRAP).
//      
//      Revision 3.1  95/02/21  09:27:21  09:27:21  etlnei (Neil Harding VK/EHS/PXE)
//      Changes made after hearing comments from Telstra
//      
//      Revision 3.0  1995/02/06  21:01:32  cmcha
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 2.5  95/01/27  12:27:38  12:27:38  etlnei (Neil Harding VK/EHS/PXE)
//      Changed get_breakpoint to look over multiple lines
//      
//      Revision 2.4  1995/01/16  10:13:25  etlnei
//      added time_stamp to check for a file being changed by another editor
//
//      Revision 2.3  1994/12/21  16:16:01  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 2.0  94/12/21  13:54:45  13:54:45  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//      
//      Revision 1.5  1994/12/02  10:35:25  etlnei
//      version uised for "happy testing"
//
//      Revision 1.4  1994/11/17  08:41:56  etlnei
//      now handles multiple files
//
//      Revision 1.3  1994/11/03  10:15:33  etlnei
//      checked in for Janne to compile
//
//      Revision 1.2  94/10/28  11:21:00  11:21:00  etlnei (Neil Harding VK/EHS/PXE)
//      *** empty log message ***
//      
//      Revision 1.1  94/10/13  13:04:41  13:04:41  etlnei (Neil Harding VK/EHS/PXE)
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
//	<link information: libraries needed and order>

// .SEE ALSO 
// 	<Related classes, (abstract) baseclasses, friend classes, ...>

//*****************************************************************************


#ifndef OZT_CDFFILE_H 
#define OZT_CDFFILE_H

#include "OZT_CDFDef.H"
#include <time.h>
#include <rw/cstring.h>
#include <rw/rwfile.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#undef MIN
#undef MAX


// Member functions, constructors, destructors, operators
class  OZT_CDFFile
{

public:
    
    OZT_CDFFile(RWCString dir_path, RWCString name,
                OZT_CDFFile **file_array, int num_files);
    // Description:
    //     Constructor. 
    //    
    // Parameters:
    //      dir_path          The directory path of the file
    //                        If "" then the current directory will be used
    //      name              The name of the file to hold information about
    //                        If "" then a name will be generated
    //      file_array        Array of open files
    //      num_files         Number of open files


    ~OZT_CDFFile();          
    // Description:
    //     Destructor


    int  get_breakpoint(int start_line, int num_lines);
    // Description:
    //     see if the a breakpoint is contained within a range of lines
    // Parameters
    //     start_line          The first line number in the range
    //     num_lines           The number of lines in the range
    // Return value: 
    //     TRUE = a breakpoint set, FALSE = no breakpoint set   

    RWCString  get_directory(void);
    // Description:
    //     get the directory that this file is in
    // Return value: 
    //     The directory path (this may be "" if using the current directory) 

    RWCString  get_full_name(void);
    // Description:
    //     get full filename including the directory path
    // Return value: 
    //     The full name   

    RWCString get_name(void);
    // Description:
    //     get the filename
    // Return value: 
    //     the filename.   

    int get_next_tag(int line_num);
    // Description:
    //     get the next tagged line number
    // Parameters:
    //     line_num   The current line number
    // Return value: 
    //     the next tagged line number, -1 if no more tags are set 


    int  get_tag(int start_line, int num_lines);
    // Description:
    //     see if the a tag is contained within a range of lines
    // Parameters
    //     start_line          The first line number in the range
    //     num_lines           The number of lines in the range
    // Return value: 
    //     TRUE = a tag set, FALSE = no tag set   


    int  is_changed(void);
    // Description:
    //     See if this file has changed since it was last loaded
    // Return value:
    //     TRUE = has changed
    //     FALSE = not changed

    void set_name(RWCString name);
    // Description:
    //     set the filename. Also sets the directory to the current directory.
    // Parameters: 
    //     name               the filename.   

    void set_breakpoint(int line_num, int   is_breakpoint);
    // Description:
    //     set the breakpoint flag for a line
    // Parameters: 
    //     line_num          the line number
    //     is_breakpoint     TRUE = set breakpoint
    //                       FALSE = clear breakpoint  

    void set_breakpoints(const char data[MAX_LINES]);
    // Description:
    //     Set multiple break points.

    void copy_breakpoints(char data[MAX_LINES]);
    // Description:
    //     Copy the break points info into data.

    void set_tag(int line_num, int   is_tag);
    // Description:
    //     set the tag flag for a line
    // Parameters: 
    //     line_num          the line number
    //     is_tag            TRUE = set tag
    //                       FALSE = clear tag

    void set_tags(const char data[MAX_LINES]);
    // Description:
    //     Set multiple tags.

    void copy_tags(char data[MAX_LINES]);
    // Description:
    //     Copy the tags info into data.

    void clearAllBrkPts();
    // Description:
    //     Remove all the break points set.

    void clearAllTags();
    // Description:
    //     Remove all the tags set.

    void set_time_stamp(void);
    // Description
    //     set the time stamp to the last modified time to record that
    //     the file is up to date at this time.

protected:

private:

    RWCString    directory;        //The name of the directory
    RWCString    filename;         //The name of the file
    char         breakpoint_array[MAX_LINES];  //Breakpoint array
    char         tag_array[MAX_LINES];         //Tag array
    unsigned long time_stamp;		      //Time stamp
};

 
#endif
