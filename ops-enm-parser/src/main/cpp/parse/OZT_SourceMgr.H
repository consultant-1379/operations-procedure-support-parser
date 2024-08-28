// RCS revision handling
// $Id: OZT_SourceMgr.H,v 21.0 1996/08/23 12:43:11 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_SourceMgr - Source Manager of the Ozterm Interpreter
// .LIBRARY CHOZTBIN
// .PAGENAME OZT_SourceMgr
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
// 	The OZT_SourceMgr is the central focus of the whole command file
//      interpreter. It provides the main interface for user interface code
//      to control the interpreter.
//      Data structures are maintained by source manager that keep track
//      of the current status of execution, such as call stack.
//      Most of the run-time support objects are created within this class
//      except those user interface objects, such as I/O window. Those
//      objects need the X Frame for construction but OZT_SourceMgr is
//      independent from the UI.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	190 89-CAA 134 2016

// AUTHOR 
// 	1994-10-10 by EPA/T/EN Nelson Cheng (epanyc@epa.ericsson.se)

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_SourceMgr.H,v $
// 	Revision 21.0  1996/08/23 12:43:11  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 07:57:46  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.1  1996/04/10 15:32:05  emejerf
// 	Fixed HA11662 and 11668.
// 	Now step() function receives the number of open files.
//
// 	Revision 19.0  1996/03/19 07:22:29  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:21:49  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:02:17  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.1  1996/01/16 12:44:03  ehsjasa
// 	Added two private variables to support the changes in the implementation file.
//
// 	Revision 16.0  1996/01/08 18:57:29  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:02:58  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:17:24  17:17:24  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.1  1995/11/16 16:15:40  epanyc
// 	getInterpreter() added
//
//      Revision 13.0  1995/10/07  12:01:37  ehsjasa
//      Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:09:38  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:25:19  09:25:19  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:02:35  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.1  95/07/05  09:14:38  09:14:38  epanyc (Nelson Cheng VK/EHS/PXE)
//      comment added
//      
//      Revision 9.0  1995/06/29  14:38:13  cmcha
//      Made release EC2_OZ, J Grape (EHSGRAP).
//
//      Revision 8.1  95/06/19  16:14:47  16:14:47  epanyc (Nelson Cheng VK/EHS/PXE)
//      OZT_Indicator added
//      .,
//      
//      Revision 8.0  1995/06/07  17:09:26  cmcha
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//
//      Revision 7.2  95/05/29  13:37:47  13:37:47  epanyc (Nelson Cheng VK/EHS/PXE)
//      file logger used
//      
//      Revision 7.1  1995/05/24  08:10:22  epanyc
//      make use of logger classes now
//
//      Revision 7.0  1995/04/16  12:16:36  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.0  95/03/17  20:05:41  20:05:41  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 5.0  95/03/16  20:31:25  20:31:25  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 4.4  95/03/15  20:12:30  20:12:30  epanyc (Nelson Cheng VK/EHS/PXE)
//      catfile stuff removed
//      
//      Revision 4.3  1995/03/06  15:26:11  epanyc
//      findFileByForLoopIdx() added
//
//      Revision 4.2  1995/03/06  09:10:03  epanyc
//      pushFile changed
//
//      Revision 4.1  1995/03/02  21:25:03  epanyc
//      comment window added and a new setCurrPos function added
//
//      Revision 4.0  1995/02/23  21:46:12  cmcha
//      Made release TB4, J Grape (EHSGRAP).
//
//      Revision 3.0  95/02/06  20:58:00  20:58:00  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 2.11  95/01/31  10:26:26  10:26:26  epanyc (Nelson Cheng VK/EHS/PXE)
//      prompt object added
//      
//      Revision 2.10  1995/01/26  17:09:08  epanyc
//      nothing changed
//
//      Revision 2.9  1995/01/26  13:16:44  epanyc
//      fileviewer added
//
//      Revision 2.8  95/01/20  10:55:56  10:55:56  epanyc (Nelson Cheng VK/EHS/PXE)
//      getCurrSourceInfo method added
//      
//      Revision 2.7  1995/01/18  12:55:06  epanyc
//      file browser added
//
//      Revision 2.6  95/01/16  08:25:05  08:25:05  epanyc (Nelson Cheng VK/EHS/PXE)
//      inkeyPopup added
//      
//      Revision 2.5  1995/01/09  12:48:10  epanyc
//      input popup added
//
//      Revision 2.4  1994/12/22  15:53:10  epanyc
//      timeOrder stuff added
//
//      Revision 2.3  1994/12/21  16:14:14  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 2.0  94/12/21  13:52:18  13:52:18  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//      
//      Revision 1.15  1994/12/21  11:59:29  epanyc
//      a tick function is added.
//
//      Revision 1.14  1994/12/19  16:16:37  epanyc
//      *** empty log message ***
//
//      Revision 1.13  1994/12/08  08:39:19  epanyc
//      check in before removing conditional comiplation stuff.
//
//      Revision 1.12  1994/12/02  14:03:27  epanyc
//      io window added
//
//      Revision 1.11  94/11/30  13:54:10  13:54:10  epanyc (Nelson Cheng VK/EHS/PXE)
//      chdHandler added
//      
//      Revision 1.10  94/11/25  10:17:56  10:17:56  epanyc (Nelson Cheng VK/EHS/PXE)
//      check in for the 1st delivery
//      
//      Revision 1.9  1994/11/16  10:29:41  epanyc
//
//      Revision 1.8  1994/11/02  12:38:24  epanyc
//      *** empty log message ***
//
//      Revision 1.7  94/10/28  13:03:19  13:03:19  epanyc (Nelson Cheng VK/EHS/PXE)
//      check in for Neil to compile
//      
//      Revision 1.6  1994/10/17  10:15:47  epanyc
//      step(filename, line) added and trace macros added
//
//      Revision 1.5  1994/10/12  16:35:59  epanyc
//      SUCCESS becomes NO_PROBLEM
//
//      Revision 1.4  1994/10/12  14:34:05  epanyc
//      *** empty log message ***
//
//      Revision 1.3  1994/10/10  15:46:18  epanyc
//      interrupt() added
//
//      Revision 1.2  1994/10/10  15:07:54  epanyc
//      getCmdRspBuf() added
//
//      Revision 1.1  1994/10/05  13:22:39  cmcha
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

#ifndef OZT_SOURCE_MGR_H
#define OZT_SOURCE_MGR_H

#include <CHA_Model.H>
#include <OZT_ErrHandling.H>
#include <OZT_SourceInfo.H>
#include <OZT_Flow.H>
#include <OZT_Interpreter.H>
#include <OZT_FileMgr.H>
#include <OZT_Indicator.H>
#include <CHA_FileLogger.H>
#include <CHA_MailLogger.H>
#include <CHA_PrinterLogger.H>
#include <OZT_RspCatcher.H>
#include <OZT_Clock.H>
#include <OZT_CmdSender.H>
#include <OZT_CmdRspBuf.H>
#include <OZT_Pipe.H>
#include <OZT_TimeOrder.H>
#include <OZT_IOW.H>
#include <OZT_CommentWinModel.H>
#include <OZT_ChildHandler.H>
#include <rw/tpordvec.h>
#include <rw/cstring.h>

class OZT_SourceMgr : public CHA_Model {
public:

    OZT_SourceMgr(CORBA::ORB_var pOrb,
		  OPS::ServerRouterListener_ptr theListener,
		  const RWCString& session_id,
		  OZT_IOW *iow = 0, 
                  OZT_InputPopup *inputPopup = 0,
                  OZT_InputPopup *inkeyPopup = 0,
                  OZT_FileSelectPopup *fSelectPopup = 0,
                  OZT_FileViewerPopup *fViewerPopup = 0,
                  OZT_PromptNotice *promptNotice = 0,
                  OZT_ChildHandler *childHandler = 0);
    // Description
    //     Constructor
    // Parameters
    //     iow          IN: pointer to the I/O window used for @DRAW, @FORM etc.
    //     inputPopup   IN: pointer to the input popup used for @INPUT
    //     inkeyPopup   IN: pointer to the input popup used for @INKEY
    //     fselectPopup IN: pointer to the file selector used for SELFILE() 
    //     fViewerPopup IN: pointer to the file viewer used for @VIEWFILE
    //     pomptNotice  IN: pointer to the prompt object used for @PROMPT


    ~OZT_SourceMgr();
    // Description
    //     Destructor


    RWBoolean constructOK() const;
    // Description:
    //    Check if the source manager is constructed properly.
    // 
    

    void  reset(RWBoolean clearSourceInfo = TRUE);
    // Description:
    //    Reset the interpreter.


    OZT_Result update(const RWCString& filename);
    // Description:
    //    Force the source manager to read the file "filename" again.
    //    This will update the line numbers for any label contained
    //    in "filename".
    //    This member function is to be called by the debugger after
    //    the user has modified the file "filename" during controlled
    //    execution (i.e. stepping).
    // Parameter
    //    filename    IN: the file to read again
    // Return value
    //    A result object telling whether the update is successful.


  OZT_Result getLabelLine( const RWCString& label, LineNo& line );

  OZT_Result setCurrPos(const RWCString &filename, const LineNo line=0, RWBoolean skip_comments = TRUE);
    // Description:
    //    The source manager maintains internally a stack of opened files.
    //    When this member function is called, the source manager pops
    //    all the files until the file "filename" is encountered. If no
    //    file is left on the file stack, the file "filename" is opened.
    //
    //    If successful, the current position will be adjusted to the first 
    //    non-commentry line following "line". Otherwise, the state of the
    //    interpreter is not modified.
    // Parameters
    //    filename      IN: the file name to set
    //    line          IN: the line number to set
    //    skip_comments IN: if TRUE, then step to next non-comment line
    // Return Values:    
    //    An OZT_Result object which contains the result of the 
    //    command just executed.
    //

    OZT_Result setCurrPos(const RWCString &filename, const RWCString &label, RWBoolean skip_comments = TRUE);
    // Description
    //    Similar to the other overloaded setCurrPos() except that
    //    a label is specified instead of line no.
    // Parameters
    //    filename      IN: the file name to set
    //    label         IN: the label in the file to set
    //    skip_comments IN: if TRUE, then step to next non-comment line

   OZT_Result  step( OZT_SourceInfo& source, int file_count,RWBoolean skip_comments = TRUE );
    // Description
    //   TBD
    // Parameters
    //   TBD

    OZT_Result step(int file_count, RWBoolean skip_comments = TRUE);
    // Description:
    //    This function may only be called when isActive() returns TRUE.
    //    For xview version, this function may only be called when the
    //    xview notifier is not running as this function may call
    //    notify_start() from xview.
    //
    //    This function executes one command from the current position.
    //    On return, the current position will be set to one of the
    //    following positions:
    //
    //    - the next command to be executed, or
    //    - the commands that fails, or
    //    - the command that stops the program 
    //
    // Parameters
    //    file_count	IN: the number of open files
    //    skip_comments IN: if TRUE, then step to next non-comment line
    //
    // Return Values:
    //     An OZT_Result object which contains the result of the
    //     command just executed.
    //


    void  getCurrPos(RWCString &filename, LineNo &line, LineNo &numLines); 
    // Description:
    //    To query the current position of the source manager. The current
    //    position is returned via "filename" and "line". "numLines" is
    //    the total number of lines occupied by the command including 
    //    empty or commentry lines embedded in the middle of the command.
    //    If there is no file currently opened by the source manager, an 
    //    empty string is returned via "filename", "line" and numLines
    //    will be undefined.  
    // Parameters
    //    filename    OUT: the file where the current position is in
    //    line        OUT: the line number where the current position is in
    //    numLines    OUT: number of lines occupied by the command


    void  interrupt();
    // Description:
    //    To interrupt the execution of the current command.
    // 


    OZT_SourceInfo *getCurrSourceInfo();
    // Description:
    //    To get hold of a pointer to the OZT_SourceInfo object on the
    //    top of the file stack. If there is no such object, a null
    //    pointer is returned.

    OZT_VarStore  &getVarStore();
    // Description:
    //    To get hold of the variable store that is maintained by the 
    //    source manager. The variable store is a model leg of the
    //    controller-model-view architecture. 


    OZT_CmdRspBuf  &getCmdRspBuf();
    // Description:
    //    To get hold of the command & response buffer that is maintained
    //    by the source manager. The command & response buffer is a
    //    model leg of the controller-model-view architecture.

    OZT_Interpreter &getInterpreter();
    // Description:
    //    To get hold of the interpreter object that is maintained by the
    //    source manager. 


    OZT_CmdSender  &getCmdSender();
    // Description:
    //    Ignore this function for the moment.


    CHA_FileLogger &getFileLogger();
    // Description:
    //    To get hold of the file logger object that is maintained
    //    by the source manager.


    CHA_MailLogger &getMailLogger();
    // Description:
    //    To get hold of the mail logger object that is maintained
    //    by the source manager.

    OZT_RspCatcher &getRspCatcher();
  // Description:
  //   To get hold of the response catcher object that is maintained 
  //   by source manager.

    CHA_PrinterLogger &getPrinterLogger();
    // Description:
    //    To get hold of the printer logger object that is maintained
    //    by the source manager.


    OZT_Clock  &getClock();
    // Description:
    //    To get hold of the clock used for time delay commands. The clock
    //    is a model leg of the controller-model-view architecture. The
    //    user interface can make itself a client of the clock so that
    //    information about the delay clock can be displayed.


    OZT_Indicator &getIndicator();
    // Description:
    //    To get hold of the indicator model from the source manager. This
    //    model provides the client information about the progress of certain
    //    commands.


    OZT_CommentWinModel &getCommentWinModel();
    // Description:
    //    To get hold of the comment window model object. The comment window
    //    model is a model leg of the controller-model-view architecture.

  void setPhaseDescription(RWCString _phase);
  // Description:
  //      Setting the phase variable. See @SETPHASE.

  RWCString getPhaseDescription();
  // Description:
  //      Getting the phase set @SETPHASE, see setPhase()

  OZT_Result setTotalCount(const OZT_Value& _totalCount);
  // Description:
  //      Setting the totalcount variable. See @TOTALCOUNT

  long getTotalCount();
  // Description:
  //      Getting the totalcount variable. See @TOTALCOUNT

  OZT_Result setProgress(const OZT_Value& _progress);
  // Description:
  //      Setting the progress variable. See @PROGRESS

  long getProgress();
  // Description:
  //      Getting the progress variable. See @PROGRESS

  OZT_Result stepProgress(const OZT_Value& interval = "1");
  // Description:
  //      Setting the progress variable. See @PROGRESS

    RWBoolean  isActive() const;
    // Description:
    //    Check if the source manager has opened any command file.
    // Return values:
    //    TRUE     yes
    //    FALSE    no   


    static int tick(void *instance);
    // Description:
    //     This callBack will be called every fixed time interval in order
    //     to check the IPC queue.

  RWCString getSessionId();


  void setListener(OPS::ServerRouterListener_ptr listener);
  // Description
  //     Used to set the listener pointer to the correct GUI when a GUI
  //     takes over a session previously owned by a crashed GUI.

private:

    void                 clearAllSourceInfo();
    // Description
    //     Remove all source info objects.

    void                 popFile();
    // Description
    //     Remove the current source info with the most recently pushed file.

    void                 pushFile(OZT_SourceInfo *pSourceInfo);
    // Description
    //     Push the current source info object onto the stack and make 
    //     "pSourceInfo" the current one.

    OZT_Result           advance(OZT_Flow flow);
    // Description
    //     Advance the current position according the "flow".

    OZT_SourceInfo      *findByFilename(const RWCString& filename);
    // Description
    //     Find the source info object with the filename. Null is returned
    //     if there is none.
    
    OZT_SourceInfo      *createSource(const RWCString& fileName,
                                      OZT_Result& result);
    // Description
    //     Create a source info object for the file "fileName".

    RWCString            findFileByForLoopIdx(const RWCString &varname) const;
    // Description
    //     Find the file that is currently loaded and which has a pending
    //     for-loop on the specified variable "varname".

    //
    //  Stack of source info objects
    //
    RWTPtrOrderedVector<OZT_SourceInfo>  sourceStack;  
    OZT_SourceInfo      *currSource;

    //
    //   runtime support objects
    //
    OZT_VarStore         varstore;
    OZT_Indicator        indicator;
    OZT_CmdRspBuf        cmdRspBuf;
    OZT_CmdSender        cmdSender;
    OZT_FileMgr          fMgr;
    CHA_FileLogger       fileLogger;
    CHA_MailLogger       mailLogger;
    CHA_PrinterLogger    printerLogger;
    OZT_Clock            clock;
    OZT_RspCatcher       rspCatcher;
    OZT_Pipe             chdHandler;
    OZT_TimeOrderHandler timeOrdHandler;
    OZT_CommentWinModel  commentWinModel;
    OZT_IOW             *pIOWin;
    OZT_InputPopup      *pInputPopup;
    OZT_InputPopup      *pInkeyPopup;
    OZT_FileSelectPopup *pFSelectPopup;
    OZT_FileViewerPopup *pFViewerPopup;
    OZT_ChildHandler    *pChildHandler;

    OZT_Interpreter      interpreter;
    RWCString sessionId_;
    RWCString              phase;
    long                 progress;
    long                 totalCount; // target for progress
    RWBoolean            interrupted;
    // The member variable `interrupted' is used as a flag to avoid
    // the current position marker to be moved past the line where the
    // "Stop" button was pressed.

    OZT_CmdSender::State cmdSenderState;
    // Need to save the state of the command sender for a while when
    // the execution was interrupted. To handle FUNBUSY "correct"...
    
    OPS::ServerRouterListener_ptr listener;  //Refernase to the server rouiter object
                                             //To be used for sending progress, phase and total.
};

#endif
