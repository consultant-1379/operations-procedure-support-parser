// RCS revision handling
// $Id: OZT_CDFFrame.H,v 21.1 1996/10/08 17:35:36 ememjga Exp $

//*****************************************************************************
// 
// .NAME
//  	OZT_CDFFrame - Create the frame for both command/response and debugger.
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
// 	This is the main class. It creates the frame and all of its
//      components, handles user input, displays program output,
//      loads files and controls file execution.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	%EriDoc_no:%

// AUTHOR 
// 	1994/10/06 by ETL/XV/B Neil Harding

// .REVISION <for public API>
//	<Revision state>
//	<Revision date>	  	

// .REVISION <for internal header files>
//	%EriDoc_rev:%
//	%EriDoc_date:%  	

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_CDFFrame.H,v $
// 	Revision 21.1  1996/10/08 17:35:36  ememjga
// 	Added the view button on the response window, AD48154.
//
// 	Revision 21.0  1996/08/23 12:46:21  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 08:00:39  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.1  1996/06/13 08:25:18  epadmt
// 	Changes for Australia :
// 	Saving of window size.
// 	Renaming of comment win etc.
//
//      Revision 19.0  96/03/19  07:23:48  07:23:48  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB61, J Sandquist (ehsjasa).
//      
// 	Revision 18.4  1996/03/11 12:59:46  ehsjasa
// 	Changed PROTOTYPE to OZT_PROTOTYPE.
//
// 	Revision 18.3  1996/03/11 10:26:00  ehsjasa
// 	Now using two updateFrom() methods.
//
// 	Revision 18.2  1996/03/07 09:21:16  ehsjasa
// 	Removed an unused variable.
//
// 	Revision 18.1  1996/03/01 16:23:36  ehsjasa
// 	Added a parameter to view_file() and sync_file() to control whether
// 	the notice box should be used.
//
// 	Revision 18.0  1996/03/01 12:24:52  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.2  1996/02/19 11:50:19  ehsjasa
// 	Described the CHA_ModelClient, RWModelClient conditionalization and
// 	changed it somewhat to get it properly parsed by SNiFF+.
//
// 	Revision 17.1  1996/01/26 09:51:48  ehsjasa
// 	Cosmetic changes
//
// 	Revision 17.0  1996/01/17 12:06:25  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.1  1996/01/10 09:45:43  ehsjasa
// 	The RWModel* CHA_Model* conditionalization was not properly done. Fixed.
//
// 	Revision 16.0  1996/01/08 18:59:28  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.2  1996/01/08 18:29:03  ehsjasa
// 	Conditionalized whether RWModel* or CHA_Model* should be used
// 	depending on which version of CHALIB was used (TPF 2 o TPF 4).
//
// 	Revision 15.1  1995/12/08 16:07:47  epanyc
// 	Prototype DCHandler stuff added.
//
//      Revision 15.0  1995/11/29  02:04:41  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.2  95/11/28  23:11:19  23:11:19  ehsgrap (Jan Grape (9 9073) VK/EHS/VE)
//      Added #include <rw/rwdate.h> to avoid macro problems.
//      
// 	Revision 14.1  1995/11/28 14:51:05  epanyc
// 	do_debugMode, do_editMode, do_rememberMarks, do_adjustMarks added
//
//      Revision 14.0  1995/11/20  17:20:26  ehsjasa
//      Made release POW_TB3, J Sandquist (EHSJASA).
//
// 	Revision 13.7  1995/11/19 14:50:01  ehsjasa
// 	Changed the return type from 'int' to 'RWBoolean' for a number of methods.
//
// 	Revision 13.6  1995/11/16 16:35:04  epanyc
// 	position() added
//
//      Revision 13.5  1995/11/09  13:15:55  epanyc
//      new functions added for showing current position
//
//      Revision 13.4  1995/11/07  13:05:00  epanyc
//      resize() added
//
//      Revision 13.3  1995/11/03  14:37:49  epanyc
//      new functions added
//
//      Revision 13.2  1995/10/31  08:23:32  epanyc
//      position update added
//
//      Revision 13.1  1995/10/17  17:15:14  ehsjasa
//      Added task ID parameter to constructor.  Added private method
//      do_running_code_refresh() that continuously displays the position
//      marker when running a script if the property is set.
//
// 	Revision 13.0  1995/10/07 12:03:48  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:12:50  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:27:28  09:27:28  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:06:04  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.1  95/07/03  15:50:21  15:50:21  etlnei (Neil Harding VK/EHS/PXE)
//      Only allow breakpoints and tags to be set on lines with commands
//      
//      Revision 9.0  1995/06/29  14:41:18  cmcha
//      Made release EC2_OZ, J Grape (EHSGRAP).
//
//      Revision 8.2  95/06/26  09:40:20  09:40:20  etlnei (Neil Harding VK/EHS/PXE)
//      changed to work with OZT_Indicator instead of OZT_Clock
//      
//      Revision 8.1  1995/06/15  08:24:13  etlnei
//      removed "paused" variable
//
//      Revision 8.0  1995/06/07  17:12:44  cmcha
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//
//      Revision 7.1  95/05/18  11:07:18  11:07:18  etlnei (Neil Harding VK/EHS/PXE)
//      *** empty log message ***
//      
//      Revision 7.0  1995/04/16  12:19:09  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.4  95/04/12  10:29:32  10:29:32  etlnei (Neil Harding VK/EHS/PXE)
//      checked in to recompile with Quantify
//      
//      Revision 6.3  1995/04/04  07:43:41  etlnei
//      added NE id
//
//      Revision 6.2  1995/03/24  15:43:21  etlnei
//      checked in to use some new UIC stuff
//
//      Revision 6.1  1995/03/21  09:17:10  etlnei
//      changed show_position()
//
//      Revision 6.0  1995/03/17  20:08:16  cmcha
//      Made release TB51_OZ, ehscama.
//
//      Revision 5.0  95/03/16  20:33:30  20:33:30  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 4.3  95/03/09  09:25:06  09:25:06  etlnei (Neil Harding VK/EHS/PXE)
//      checked in for other people to compile
//      
//      Revision 4.2  1995/03/02  21:31:52  epanyc
//      a new parameter is added to OZT_MainLoop
//
//      Revision 4.1  1995/03/01  12:10:39  etlnei
//      checked in while I go to England
//
//      Revision 4.0  1995/02/23  21:47:59  cmcha
//      Made release TB4, J Grape (EHSGRAP).
//
//      Revision 3.4  95/02/21  11:59:54  11:59:54  epanyc (Nelson Cheng VK/EHS/PXE)
//      a forward declaration is added
//      
//      Revision 3.3  1995/02/21  09:27:21  etlnei
//      Changes made after hearing comments from Telstra
//
//      Revision 3.2  1995/02/14  09:44:26  ehsenan
//      Added OLDT calls and functions
//
//      Revision 3.1  1995/02/10  11:38:26  etlnei
//      added getFileContents()
//
//      Revision 3.0  1995/02/06  21:01:42  cmcha
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 2.12  95/02/03  14:19:36  14:19:36  etlnei (Neil Harding VK/EHS/PXE)
//      second happy test release
//      
//      Revision 2.11  1995/01/31  11:44:58  etlnei
//      checked in for Nelson to compile
//
//      Revision 2.10  1995/01/27  15:51:50  etlnei
//      added EDITOR enum for frame style
//
//      Revision 2.9  1995/01/27  10:52:46  etlnei
//      checked in for Eric to compile (has extra parameter in constructor)
//
//      Revision 2.8  1995/01/26  14:53:36  etlnei
//      checked in for Nelso to compile
//
//      Revision 2.7  1995/01/26  09:55:40  etlnei
//      checked in for Eric to compile
//
//      Revision 2.6  1995/01/18  13:45:44  etlnei
//      added FileSelector
//
//      Revision 2.5  1995/01/16  10:13:25  etlnei
//      added time_stamp to check for a file being changed by another editor
//
//      Revision 2.4  1995/01/09  11:49:21  etlnei
//      added props window stuff
//
//      Revision 2.3  1994/12/21  16:16:06  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 2.0  94/12/21  13:54:48  13:54:48  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//      
//      Revision 1.12  1994/12/20  10:38:30  etlnei
//      added delay footer message
//
//      Revision 1.11  1994/12/16  13:38:52  etlnei
//      added OZT_InputWin
//
//      Revision 1.10  1994/12/13  11:20:23  etlnei
//      checking in everything because OXT_ESBrowser is new
//
//      Revision 1.9  1994/12/12  11:15:57  etlnei
//      checked in for nelson to compile
//
//      Revision 1.8  1994/12/06  11:39:48  etlnei
//      checked in for Janne to compile
//
//      Revision 1.7  1994/12/02  10:35:25  etlnei
//      version uised for "happy testing"
//
//      Revision 1.6  94/11/17  08:41:56  08:41:56  etlnei (Neil Harding VK/EHS/PXE)
//      now handles multiple files
//      
//      Revision 1.5  1994/11/03  10:15:33  etlnei
//      checked in for Janne to compile
//
//      Revision 1.4  94/10/28  11:21:07  11:21:07  etlnei (Neil Harding VK/EHS/PXE)
//      *** empty log message ***
//      
//      Revision 1.3  94/10/13  13:05:24  13:05:24  etlnei (Neil Harding VK/EHS/PXE)
//      more bits done
//      
//      Revision 1.2  94/10/07  19:46:26  19:46:26  etlnei (Neil Harding VK/EHS/PXE)
//      corrected errors
//      
//      Revision 1.1  1994/10/06  14:14:41  etlnei
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


#ifndef OZT_CDFFRAME_H 
#define OZT_CDFFRAME_H

//********************************************
// Files included to get around macro problems
#undef max // Someone has defined macros named max and min (???!!)
#undef min // which is the names used for a couple of methods in rw.
#include <rw/rwtime.h>
#include <rw/rwdate.h>
#include <CHA_Pipe.H>
//********************************************

#include <CHA_Connection.H>
#include <rw/model.h>
#include "OZT_CDFFile.H"
//#include "OZT_ESBrowser.H"
#include "OZT_CommentWin.H"
#include "OZT_FileSelector.H"
#include "OZT_FileBrowser.H"
#include "OZT_InputWin.H"
#include "OZT_NEIdentification.H"
#include "OZT_PrintWin.H"
#include "OZT_Prompt.H"
#include "OZT_Props.H"
#include "OZT_StatusWin.H"
#include "OZT_FileViewer.H"
#include "OZT_ViewSelectFile.H"
#include "OZT_WatchWin.H"
#include <OZT_Indicator.H>
#include <OZT_SourceMgr.H>
#include <OZT_ErrHandling.H>
#include <OZT_XvIOW.H>
#include <OZT_ESPickList.H>

#ifdef OZT_PROTOTYPE
#include "OZT_CmdEntryPane.H"
#include "OZT_DCHandler.H"
#endif

#include <UIC_BaseFrame.H>
#include <UIC_Button.H>
#include <UIC_Choices.H>
#include <UIC_DropTarget.H>
#include <UIC_ItemRow.H>
#include <UIC_Message.H>
#include <UIC_Menu.H>
#include <UIC_MenuItem.H>
#include <UIC_Notice.H>
#include <UIC_Panel.H>
#include <UIC_TextField.H>
#include <UIC_TextPane.H>
#include <rw/cstring.h>
#include <xview/scrollbar.h>
#include <xview/font.h>
#include <xview/notice.h>
#include <OLDT_Handler.H>

enum Frame_style {RESP_WIN, DEBUGGER, EDITOR};

        
// Forward declaration(s)
class OZT_CDFFile;
class OZT_Indicator;
//class OZT_ESBrowser;
class OZT_FileBrowser;
class OZT_FileSelector;
class OZT_InputWin;
class OZT_PrintWin;
class OZT_Props;
class OZT_ViewSelectFile;
class OZT_WatchWin;




// Member functions, constructors, destructors, operators
//
// In CHALIB for TPF 4, CHA_ModelClient no longer inherits from
// RWModelClient, so we need to inherit from both to properly interact
// with the OLDT stuff.

class  OZT_CDFFrame : public UIC_BaseFrame,
#if TPF >= 400
                      public CHA_ModelClient,
                      public RWModelClient
#else
                      public CHA_ModelClient
#endif
{
public:
    static const int OZT_NUM_OF_COLS_IN_JA_LOCALE;
    static const int OZT_NUM_OF_ROWS_IN_JA_LOCALE;

    OZT_CDFFrame(Frame_style    which_frame,
                 RWCString      taskID,
                 RWCString      filename,
                 RWBoolean      run,
                 RWBoolean      quit);
    // Description:
    //     Creates the frame which contains all the buttons and panels for
    //     both the Command & Response window, and the debugger. Items specific
    //     to one of these windows are hidden in the other. 
    //     Also creates all the popup windows and the source manager.
    // Parameters: 
    //     Frame_style which_frame      RESP_WIN for command & response window
    //                                  DEBUGGER for debugger window 
    //                                  EDITOR for debugger in edit mode.
    //     RWCString taskID             The task ID (from ELB)
    //     RWCString filename           File to load and run on opening
    //                                  use "" for no file
    //     RWBoolean run                TRUE = start running, FALSE = don't
    //     RWBoolean quit               TRUE = quit at end of run

    virtual ~OZT_CDFFrame();
    // Description:
    //     Destructor. Removes the window and stops running.
    
    OZT_Result   OZT_CDFMainLoop(RWBoolean resetFirst);
    // Description:
    //     Shows the frame and checks for any events to allow the notify
    //     functions to be called. This is the main loop for the developer
    //     and will only return if the frame is quit, or if the developer has
    //     been started with quit = TRUE in the constructor and the run has.
    //     terminated.
    //     
    // Parameter:
    //     resetFirst               TRUE: reset the interpreter on start running
    //                              FALSE: no reset
    // Return value
    //     A result object containing the result of the last operation

    OZT_CDFFile**  getFileArray(void);
    // Description:
    //     Get the file array pointer.
    // Return Value:
    //     Pointer to the OZT_CDFFile array.

    RWCString  getFileContents(int file_number);
    // Description:
    //     Get contents of the textpane holding the file indexed by file_number
    // Parameters
    //     file_number   The file array index
    // Return Value:
    //     the contents

    int  getFileCount(void);
    // Description:
    //     Get the number of files loaded into the debugger.
    // Return Value:
    //     The number of files.

    Frame  getFrame(void);
    // Description:
    //     Get the developer's xview baseframe.
    // Return Value:
    //     The frame

    RWCString  getSelectedText(void);
    // Description:
    //     Get the text that has been highlighted in the edit window.
    // Return Value:
    //     The text or "" if no text selected.

    RWCString  getRespSelectedText(void);
    // Description:
    //     Get the text that has been highlighted in the response window.
    // Return Value:
    //     The text or "" if no text selected.

    OZT_SourceMgr*  getSourceMgr(void);
    // Description:
    //     Get the source manager object.
    // Return Value:
    //     Pointer to the OZT_SourceMgr object.

    RWCString  getViewFileName(void);
    // Description:
    //     Get the full name of the file being viewed
    // Return Value:
    //     the complete file name, with path.

    int  getViewFileNumber(void);
    // Description:
    //     Get the number of the file being viewed
    // Return Value:
    //     the number (index in array)

    RWCString getOLDTSearchString();
    // Description:
    //     Get the text that has been highlighted in the response window
    //     or in the edit window.
    // Return Value:
    //     The text or "" if no text selected.

    void callOLDTwithCOD();
    // Description:
    // Called by AviewMenuCOD() to make the OLDT show a POD

    void callOLDTwithPOD();
    // Description:
    // Called by AviewMenuPOD() to make the OLDT show a POD

    void callOLDTwithAI();
    // Description:
    // Called by AviewMenuAI() to make the OLDT show a AI

    void callOLDTwithMLIB();
    // Description:
    // Called by AviewMenuMLIB() to make the OLDT show the Main Library
    // (collections of Books)

    void OLDTErrorHandler(OLDTReturnCode oldtRC);
    // Description:
    //    Handles different errorCodes sent from OLDT by using the registered
    //    callback AOLDTErrorHandler;

    OLDT_Handler* getOLDTHandler() {return pOLDThandler;}
    // Description:
    //    Get hold of the pointer to the OLDT Handler. Null pointer is
    //    returned if the handler is not constructed.
    //

    void setCFDTitle(const RWCString & es_name, 
                     const RWCString & filename);
       // Description:
       // 	Updates the titles of this and all appropriate
       //	subwindows. Called whenever connected ES or loaded
       //	filename changes.
       // Parameters:
       //	es_name:	IN: Name of the connected ES
       //	filename:	IN: Name of the loaded file.

    void setFooter(int nlsIndex, RWBoolean rightSide = FALSE);
    // Description:
    //	The operation inserts text in the footer of the window (frame)
    // Parameters: 
    //	nlsIndex	IN: The index to the text that will be inserted
    //			    in the footer. If == -1 then the footer will
    //			    be emptied.
    //	rightSide	IN: if FALSE then the text will be 
    //			    on the left side
    //			    of the footer, else on the right side.


    virtual     void resize();
    virtual     void position(bool alsoVertically = FALSE);

protected:

private:
    CHA_EsList::NeSource neSource;

    CHA_Connection*      connection_object;
    OZT_CDFFile*         file_entry[MAX_OPEN_FILES];    //open files array
    OZT_Indicator*       indicator;
    OZT_CmdRspBuf*       cmd_rsp_buf;
    OZT_CommentWin*      comment_win;
    OZT_CommentWinModel* comment_win_model;
    OZT_SourceMgr*       source_mgr;
    //    OZT_ESBrowser*       es_browser;
    OZT_FileBrowser*     load_browser;
    OZT_FileBrowser*     save_browser;
    OZT_FileViewer*      file_viewer;
    OZT_FileSelector*    file_selector;
    OZT_InputWin*        inkey_win;
    OZT_InputWin*        input_win;
    OZT_PrintWin*        print_win;
    OZT_Prompt*          prompt;
    OZT_Props*           props_win;
    OZT_StatusWin*       status_win;
    OZT_XvIOW*           io_win;
    OZT_ViewSelectFile*  select_view;
    OZT_WatchWin*        watch_win;

    RWCString		titleString; // Strings for the window title.
    RWCString		titleFile;
    RWCString      task_id;          // The task ID passed to the constructor

    OLDT_Handler*  pOLDThandler;     // the OLDT_Handler Object    
    RWBoolean      oldtTurnedOn;     // used to decide if OLDT specific 
                                     // code should be executed or not

    int         current_position;    // Program counter, holds current line no.
    int         start_running;       // TRUE when want to start up running
    int         stopped;             // TRUE when stop or pause button pressed
    int         running;             // TRUE when a script is running.
    int         auto_quit;           // TRUE when need to quit when run stops

    Display*    cdf_display;
    Frame       cdf_frame;

    GC		clear_gc;
    GC          draw_gc;
    Window      code_sw[MAX_OPEN_FILES];
    Window      code_xid[MAX_OPEN_FILES];
    Pixmap      breakpoint_image;
    Pixmap      position_image;
    Pixmap      tag_image;

    Frame_style frame_style;

    int         file_count;           // The number of open files
    int	        running_file_number;  // The number of the file with the 
                                      // current_position in it.
    int	        view_file_number;     // The number of the code file viewed

    enum Mode   {EDIT, DEBUG, NONE};
    Mode        mode;

    enum What_to_do {NOTHING, QUIT, STEP, RUN_CONTINUE,
                     RUN_START, RUN_TAGGED, STOP};

    What_to_do action;                // Why xv_main_loop() stopped
 
    OZT_NEIdentification ne_id;
    UIC_Button      breakpoint_button;
    UIC_Button      connect_button;
    UIC_Button      debugger_button;
    UIC_Button      disconnect_button;
    UIC_Button      edit_button;
    //    UIC_Button      es_button;
    OZT_ESPickList  esPickList;
    UIC_Button      file_button;
    UIC_Button      find_button;
    UIC_Button      props_button;
    UIC_Button      quit_button;
    UIC_Button      reset_button;
    UIC_Button      run_button;
    UIC_Button      set_pos_button;
    UIC_Button      step_button;
    UIC_Button      stop_debug_button; //stop button in the debugger
    UIC_Button      stop_resp_button;  //stop button in command + response win
    UIC_Button      tag_button;
    UIC_Button      view_button;
    UIC_Button      view_resp_button;  // response window
    UIC_Button*     pDocButton;        // OLDT button

    UIC_Choices     mode_choice;

    UIC_ItemRow     debug_row;
    UIC_ItemRow     edit_row;
    UIC_ItemRow     es_row;
    UIC_ItemRow     message_row;
    UIC_ItemRow     resp_row;
    UIC_ItemRow     resp_row_sup;     // response window
    UIC_Message     message_message;

    UIC_Menu        breakpoint_menu;
    UIC_Menu        edit_menu;
    UIC_Menu        file_menu;
    UIC_Menu        run_menu;
    UIC_Menu        set_pos_menu;
    UIC_Menu        tag_menu;
    UIC_Menu        view_menu;
    UIC_Menu        view_resp_menu;   // response window
    UIC_Menu*       pDocMenu;          // OLDT menu under pDocButton

    UIC_MenuItem    add_breakpoint;
    UIC_MenuItem    clear_breakpoint;
    UIC_MenuItem    clear_all_breakpoint;
    UIC_MenuItem    close_file;
    UIC_MenuItem    close_all_file;
    UIC_MenuItem    create_file;
    UIC_MenuItem    load_file;
    UIC_MenuItem    save_file;
    UIC_MenuItem    save_all_file;
    UIC_MenuItem    save_as_file;
    UIC_MenuItem    print_file;
    UIC_MenuItem    only_set_pos;
    UIC_MenuItem    run_set_pos;
    UIC_MenuItem    current_run;
    UIC_MenuItem    start_run;
    UIC_MenuItem    tagged_run;
    UIC_MenuItem    add_tag;
    UIC_MenuItem    clear_tag;
    UIC_MenuItem    clear_all_tag;
    UIC_MenuItem    commentwin_view;
    UIC_MenuItem    file_view;
    UIC_MenuItem    iowin_view;
    UIC_MenuItem    statuswin_view;
    UIC_MenuItem    watchwin_view;
    UIC_MenuItem    currentPos_view;
    
    UIC_MenuItem*   pDocCODItem;       // Command description under pDocMenu
    UIC_MenuItem*   pDocPODItem;       // Printout description under pDocMenu
    UIC_MenuItem*   pDocAIItem;        // Application Info under pDocMenu
    UIC_MenuItem*   pDocMLIBItem;      // Main Library under pDocMenu

    UIC_Panel       debug_panel;
    UIC_Panel       edit_panel;
    UIC_Panel       es_panel;
    UIC_Panel       message_panel;
    UIC_Panel       resp_panel;
    UIC_Panel       resp_panel_sup;    // Resp. window
#ifdef OZT_PROTOTYPE
    UIC_Message      cmd_entry_msg;
    UIC_ItemRow      cmd_entry_msg_row;
    UIC_Panel        cmd_entry_msg_panel;
    OZT_CmdEntryPane cmd_entry_pane;
    OZT_DCHandler*   pDCHandler;
#endif

    UIC_TextField   es_text_field;

    UIC_TextPane*   code_textpane[MAX_OPEN_FILES];
    UIC_TextPane    resp_textpane;
    
    static void a_connect(UIC_Window* win, UIC_PanelItem* pi);
    static void a_debugger(UIC_Window* win, UIC_PanelItem* pi);
    static void a_disconnect(UIC_Window* win, UIC_PanelItem* pi);
    static void a_edit(UIC_Window* win, UIC_PanelItem* pi);
    static int  a_es(UIC_Window* win, UIC_PanelItem* pi);
    static void a_file_drop(UIC_Window* win, UIC_PanelItem* pi);
    static void a_find(UIC_Window* win, UIC_PanelItem* pi);
    static void a_mode(UIC_Window* win, UIC_PanelItem* pi);
    static void a_props(UIC_Window* win, UIC_PanelItem* pi);
    static void a_quit(UIC_Window* win, UIC_PanelItem* pi);
    static void a_reset(UIC_Window* win, UIC_PanelItem* pi);
    static void a_set_pos(UIC_Window* win, UIC_PanelItem* pi);
    static void a_step(UIC_Window* win, UIC_PanelItem* pi);
    static void a_stop_debug(UIC_Window* win, UIC_PanelItem* pi);
    static void a_stop_resp(UIC_Window* win, UIC_PanelItem* pi);

    static void a_addbreakpoint(UIC_Window* win, UIC_MenuItem* mi);
    static void a_clearbreakpoint(UIC_Window* win, UIC_MenuItem* mi);
    static void a_clearallbreakpoint(UIC_Window* win, UIC_MenuItem* mi);
    static void a_closefile(UIC_Window* win, UIC_MenuItem* mi);
    static void a_closeallfile(UIC_Window* win, UIC_MenuItem* mi);
    static void a_createfile(UIC_Window* win, UIC_MenuItem* mi);
    static void a_loadfile(UIC_Window* win, UIC_MenuItem* mi);
    static void a_savefile(UIC_Window* win, UIC_MenuItem* mi);
    static void a_saveallfile(UIC_Window* win, UIC_MenuItem* mi);
    static void a_saveasfile(UIC_Window* win, UIC_MenuItem* mi);
    static void a_printfile(UIC_Window* win, UIC_MenuItem* mi);
    static void a_currentrun(UIC_Window* win, UIC_MenuItem* mi);
    static void a_startrun(UIC_Window* win, UIC_MenuItem* mi);
    static void a_taggedrun(UIC_Window* win, UIC_MenuItem* mi);
    static void a_only_set_pos(UIC_Window* win, UIC_MenuItem* mi);
    static void a_run_set_pos(UIC_Window* win, UIC_MenuItem* mi);
    static void a_addtag(UIC_Window* win, UIC_MenuItem* mi);
    static void a_cleartag(UIC_Window* win, UIC_MenuItem* mi);
    static void a_clearalltag(UIC_Window* win, UIC_MenuItem* mi);
    static void a_commentwinview(UIC_Window* win, UIC_MenuItem* mi);
    static void a_currentPosView(UIC_Window* win, UIC_MenuItem* mi);
    static void a_fileview(UIC_Window* win, UIC_MenuItem* mi);
    static void a_iowinview(UIC_Window* win, UIC_MenuItem* mi);
    static void a_statuswinview(UIC_Window* win, UIC_MenuItem* mi);
    static void a_watchwinview(UIC_Window* win, UIC_MenuItem* mi);
    static void a_browser_es(UIC_Window* win);
    static int  a_browser_load(UIC_Window* win);
    static int  a_browser_save(UIC_Window* win);
    static int  a_view_apply(UIC_Window* win);

    // OLDT menu Callbacks
    static void AviewMenuCOD  (UIC_Window* wp, UIC_MenuItem* mi);
    static void AviewMenuPOD  (UIC_Window* wp, UIC_MenuItem* mi);
    static void AviewMenuAI   (UIC_Window* wp, UIC_MenuItem* mi);
    static void AviewMenuMLIB (UIC_Window* wp, UIC_MenuItem* mi);
    
    // OLDT Error Handler callback
    static void AOLDTErrorHandler(void* wp, OLDTReturnCode rc);

    void        do_addbreakpoint(void);
    void        do_clearbreakpoint(void);
    void        do_clearallbreakpoint(void);
    void        do_code_refresh(void);
    void        do_code_sw(Textsw textsw, Attr_avlist attributes);
    void        do_commentwinview(void);
    void        do_currentPosView(void);
    void        do_connect(void);
    void        do_debugger(void);
    void        do_disconnect(void);
    void        do_edit(void);
    void        do_es(void);
    void        do_file_drop(void);
    void        do_fileview(void);
    void        do_find(void);
    void        do_mode(void);
    void        do_debugMode(void);
    void        do_editMode(void);
    void        do_rememberMarks(void);
    void        do_adjustMarks(void);
    void        do_printfile(void);
    void        do_props(void);
    void        do_closefile(void);
    void        do_closeallfile(void);
    void        do_loadfile(void);
    void        do_createfile(void);
    void        do_savefile(void);
    void        do_saveallfile(void);
    void        do_saveasfile(void);
    void        do_quit(void);
    void        do_reset(void);
    void        do_startrun(void);
    void        do_currentrun(void);
    void        do_taggedrun(void);
    void        do_set_pos(void);
    void        do_step(void);
    void        do_stop_debug(void);
    void        do_stop_resp(void);
    void        do_addtag(void);
    void        do_cleartag(void);
    void        do_clearalltag(void);
    void        do_iowinview(void);
    void        do_statuswinview(void);
    void        do_watchwinview(void);
    void        do_browser_es(void);
    RWBoolean   do_browser_load(void);
    RWBoolean   do_browser_save(void);
    RWBoolean   do_view_apply(void);

    void        gc_create(void);
    void        setBusyIcon(void);
    void        setIdleIcon(void);
    static Notify_value  a_code_refresh(Notify_client     client,
                                        Notify_event      event,
                                        Notify_arg        arg,
                                        Notify_event_type type);
    static void mouse_event_proc(Xv_Window window,
                                 Event* event,
                                 Notify_arg arg);
    static void notify_code_sw(Textsw textsw,
                               Attr_avlist attributes);
    static void (*textsw_default_notify)(Textsw textsw,
                                         Attr_avlist attributes);

    RWBoolean   close_a_file(int file_number); // unload a loaded file
    static int  destroy (UIC_Window* bf, BASE_QUIT_STATUS status); //quit frame
    RWBoolean   get_selection(int* first_line, int* last_line); //get highlighted text
    RWBoolean   open_a_file(RWCString dir_path, RWCString name); //load a file into the developer
    void        oldt_create(void); // create the OLDT 

    // The change in CHALIB for TPF 4, where CHA_Model no longer
    // inherits from RWmodel causes us to declare/use two
    // updateFrom() methods.
    void updateFrom(CHA_Model* pModel, void*);  // for CHA stuff
    void updateFrom(RWModel* pModel, void*);    // for OLDT stuff
    virtual void detachFrom(CHA_Model* pModel);
    
    void        display_filename(void); // display the name of the viewed file
    RWCString   get_line(int file, int line);  //Get the contents of a line
    int         get_lines(RWCString filename); // Get the no. of lines in file
    RWBoolean   store_file(int file_number);   // Store a loded file to disk
    RWBoolean   sync_file(int file_number, RWBoolean notice = TRUE);  // Ensure a loaded file is up to date
    OZT_Result  run_loop(RWCString file, RWBoolean tags_only); // Run a file
    void        set_codesw_props(int file_num);  // Ensure a textpane has the right props for its mode
    void        show_position(RWCString filename, int lineNo, int num_lines); // Show the current position.
    RWBoolean   view_file(RWCString filename, RWBoolean notice = TRUE); // View a loaded file.
};

 
#endif
