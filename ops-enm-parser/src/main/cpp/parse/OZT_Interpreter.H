// RCS revision handling
// $Id: OZT_Interpreter.H,v 21.0 1996/08/23 12:42:48 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_Interpreter - Interpreter for command file language
// .LIBRARY CHOZTBIN
// .PAGENAME OZT_Interpreter
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
// 	OZT_Interpreter encapsulates lex & yacc generated code. It provides 
//      the service of interpreter an individual command.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	190 89-CAA 134 2016

// AUTHOR 
// 	94-10-05 by EPA/T/EN Nelson Cheng (epanyc@epa.ericsson.se)

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_Interpreter.H,v $
// 	Revision 21.0  1996/08/23 12:42:48  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 07:57:26  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.1  1996/04/10 15:39:15  emejerf
// 	Fixed HA11662 and 11668.
// 	Now interpret() function receives a new parameter (the
// 	number of the open files).
//
// 	Revision 19.0  1996/03/19 07:22:18  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:21:20  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:01:54  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:57:12  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:02:44  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:17:02  17:17:02  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.1  1995/10/24 16:01:11  ehsjasa
// 	Replaced a whole bunch of include directives with forward
// 	declarations.
//
// 	Revision 13.0  1995/10/07 12:01:17  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:09:01  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:24:59  09:24:59  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:02:06  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:37:48  14:37:48  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.1  95/06/28  14:31:16  14:31:16  epanyc (Nelson Cheng VK/EHS/PXE)
//      comment added
//      
//      Revision 8.0  1995/06/07  17:08:57  cmcha
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//
//      Revision 7.2  95/05/29  13:37:14  epanyc (Nelson Cheng VK/EHS/PXE)
//      file logger used
//      
//      Revision 7.1  1995/05/24  08:09:19  epanyc
//      make use of CHA_MailLogger & CHA_PrinterLogger now
//
//      Revision 7.0  1995/04/16  12:16:12  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.1  95/03/24  16:42:40  epanyc (Nelson Cheng VK/EHS/PXE)
//      new param added to the constructor
//      
//      Revision 6.0  1995/03/17  20:05:16  cmcha
//      Made release TB51_OZ, ehscama.
//
//      Revision 5.0  95/03/16  20:31:02  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 4.2  95/03/15  20:11:45  epanyc (Nelson Cheng VK/EHS/PXE)
//      catfile removed
//      
//      Revision 4.1  1995/03/02  21:24:24  epanyc
//      comment window added
//
//      Revision 4.0  1995/02/23  21:45:48  cmcha
//      Made release TB4, J Grape (EHSGRAP).
//
//      Revision 3.0  95/02/06  20:57:23  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 2.10  95/01/31  10:31:30  epanyc (Nelson Cheng VK/EHS/PXE)
//      prompt object
//
//      Revision 2.9  1995/01/26  13:22:24  epanyc
//      file viewer added
//
//      Revision 2.8  95/01/19  15:58:51  epatse (Eric Tse VK/EHS/PXE)
//      no change
//
//      Revision 2.7  1995/01/18  12:55:25  epanyc
//      file browser added
//
//      Revision 2.6  95/01/16  08:24:23  epanyc (Nelson Cheng VK/EHS/PXE)
//      inkeyPopup added
//
//      Revision 2.5  1995/01/09  12:47:25  epanyc
//      input popup added
//
//      Revision 2.4  1994/12/22  15:53:10  epanyc
//      timeOrder stuff added
//
//      Revision 2.3  1994/12/21  16:07:41  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 2.0  94/12/21  13:51:50  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 1.13  1994/12/19  16:16:37  epanyc
//      *** empty log message ***
//
//      Revision 1.12  1994/12/08  08:39:19  epanyc
//      check in before removing conditional comiplation stuff.
//
//      Revision 1.11  1994/12/02  14:03:10  epanyc
//      io window added
//
//      Revision 1.10  1994/11/30  13:53:49  epanyc
//      chdHandler added
//
//      Revision 1.9  94/11/25  10:17:47  epanyc (Nelson Cheng VK/EHS/PXE)
//      check in for the 1st delivery
//
//      Revision 1.8  1994/11/16  10:26:20  epanyc
//      use cmdSender instead of cmdRspInterface
//
//      Revision 1.7  1994/10/28  13:03:19  epanyc
//      check in for Neil to compile
//
//      Revision 1.6  1994/10/17  10:14:59  epanyc
//      Blocking behavour removed to individual runtime objects
//
//      Revision 1.5  1994/10/14  09:16:51  epanyc
//      This revision is checked in so that the blocking behaviour is removed in
//      the next revision.
//
//      Revision 1.4  1994/10/12  16:35:49  epanyc
//      SUCCESS becomes NO_PROBLEM
//
//      Revision 1.3  1994/10/12  14:33:57  epanyc
//      *** empty log message ***
//
//      Revision 1.2  1994/10/10  15:07:54  epanyc
//      This version uses the immediate and delayed resp receivers directly.
//
//      Revision 1.1  94/10/05  11:14:32    cmcha (*CHA conf. and dev. EHS/PXE)
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

#ifndef OZT_INTERPRETER_H
#define OZT_INTERPRETER_H

#include <rw/tvordvec.h>
#include <rw/cstring.h>
#include <OZT_ErrHandling.H>
#include <OZT_Flow.H>

//****************************************************************
//  Do not instantiate more than one object of this class, the
//  yacc code cannot handle multiple instances of the interpreter.
//****************************************************************

// Forward Declarations
class CHA_FileLogger;
class CHA_MailLogger;
class CHA_PrinterLogger;
class OZT_ChildHandler;
class OZT_CmdRspBuf;
class OZT_CmdSender;
class OZT_FileMgr;
class OZT_RspCatcher;
class OZT_Clock;
class OZT_Pipe;
class OZT_TimeOrderHandler;
class OZT_CommentWinModel;
class OZT_IOW;
class OZT_SourceMgr;
class OZT_InputPopup;
class OZT_FileSelectPopup;
class OZT_FileViewerPopup;
class OZT_PromptNotice;
class OZT_VarStore;

class OZT_Interpreter {
public:
    enum State {IDLE, BUSY};
    
    OZT_Interpreter(OZT_SourceMgr*        theSourceMgr,
                    OZT_VarStore&         theVarStore,
                    OZT_CmdRspBuf&        theCmdRspBuf,
                    OZT_CmdSender&        theCmdSender,
                    OZT_FileMgr&          theFileMgr,
                    CHA_FileLogger&       theFileLogger,
                    CHA_MailLogger&       theMailLogger,
                    CHA_PrinterLogger&    thePrinterLogger,
                    OZT_RspCatcher&       theRspCatcher,
                    OZT_Clock&            theClock,
                    OZT_Pipe&             theChdHandler,
		    OZT_TimeOrderHandler& theTimeOrdHandler,
                    OZT_CommentWinModel&  theCommentWinModel,
                    OZT_IOW*              theIOWinPtr,
                    OZT_InputPopup*       theInputPopup,
                    OZT_InputPopup*       theInkeyPopup,
                    OZT_FileSelectPopup*  theFSelectPopup,
                    OZT_FileViewerPopup*  theFViewerPopup,
                    OZT_PromptNotice*     thePromptNotice,
                    OZT_ChildHandler*     theChildHandler);
    // Description
    //     Constructor.


    ~OZT_Interpreter();
    // Description
    //     Destructor.


    OZT_Result interpret(const RWCString& theCurrFile,
                         RWCString& cmd_text, 
                         OZT_Flow& flow_info,
                         int file_count);
    // Description
    //     Interpret a command.
    // Parameter
    //     theCurrFile    IN: the path name of the file where "cmd_text"
    //                        is retrieved from. This is needed for choosing
    //                        authority profile for MML checking.
    //     cmd_text       IN: the text block that contains the command.
    //     file_count     IN: the number of open files.
    //     flow_info      OUT: the OZT_Flow object that contains the flow
    //                         control information about where to find the
    //                         next command.
    

    void   interrupt();
    // Description
    //     Interrupt the command that is currently executing.

    //
    //  Callbacks for yyparse(shouldn't be used directly)
    //
    int    overriden_input();
    void   overriden_unput(int c);
    void   set_result(const OZT_Result& result);
    void   set_result(const OZT_Result::Code code);
    void   set_flow_info(const OZT_Flow& flow);
    void   set_flow_info(const OZT_Flow::Code code);
    void   setSkipElseFlag();
    RWCString getCurrFileName() const;
    RWBoolean isAloneCommand()const { return isAloneCommand_; }
private:
    RWBoolean  isScriptCmd(const RWCString& cmdText);
    // Description
    //     Check if the command is a command file primitive or a MML command.

    RWCString  varSubst(const RWCString& cmdText);
    // Description
    //     Expand the string by variable substitution.

    //
    //  private members for holding command text to be parsed
    //
    RWCString           *buf;
    size_t               index;
    size_t               index_bound;
    RWTValOrderedVector<int>  lookahead_buf;

    //
    //  runtime supported objects
    //
    OZT_CmdSender&       cmdSender;
    OZT_VarStore&        varstore;
    OZT_RspCatcher&      rspCatcher;
    OZT_Pipe&            chdHandler;
    OZT_Clock&           clock;
    OZT_IOW*             pIOWin;
    OZT_InputPopup*      pInputPopup;
    OZT_InputPopup*      pInkeyPopup;
    OZT_FileSelectPopup* pFSelectPopup;
    OZT_FileViewerPopup* pFViewerPopup;

    RWCString            currFileName;
    State                theState;
    OZT_Result           result;
    OZT_Flow             flow;
    RWBoolean isAloneCommand_;
};

#endif
