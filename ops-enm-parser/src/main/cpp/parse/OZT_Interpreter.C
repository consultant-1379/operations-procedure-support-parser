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

#include <rw/cstring.h>
#include <iostream>
#include <OZT_Interpreter.H>
#include <OZT_IOW.H>
#include <OZT_Misc.H>
#include <OZT_CmdSender.H>  // Really necessary? Only references to it below...
#include <OZT_RspCatcher.H> // ...so it should suffice with...
#include <OZT_Pipe.H>       // ...some...
#include <OZT_Clock.H>      // ... forward...
#include <OZT_VarStore.H>   // ...declarations, shouldn't it?
#include "y.tab.h"
#include "OZT_CDFDef.H"
#include <rw/tools/regex.h>


//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_Interpreter";

//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_Interpreter.C,v 21.0 1996/08/23 12:44:13 ehsgrap Rel $";


//*****************************************************************************
//  Declaration of a number of functions found in the lex & yacc files
//*****************************************************************************

extern void ozt_initTokenizer(OZT_Interpreter* wrapper);
extern void ozt_initParser(OZT_SourceMgr*        theSourceMgr,
                           OZT_Interpreter*      wrapper,
                           OZT_VarStore*         theVarStore,
                           OZT_CmdRspBuf*        theCmdRspBuf,
                           OZT_CmdSender*        theCmdSender,
                           OZT_FileMgr*          fMgr,
                           CHA_FileLogger*       theFileLogger,
                           CHA_MailLogger*       theMailLogger,
                           CHA_PrinterLogger*    thePrinterLogger,
                           OZT_RspCatcher*       theRspCatcher,
                           OZT_Clock*            theClock,
                           OZT_Pipe*             theChdHandler,
			   OZT_TimeOrderHandler* theTimeOrdHandler,
                           OZT_CommentWinModel*  theCommentWinModel,
                           OZT_IOW*              theIOWin,
                           OZT_InputPopup*       theInputPopup,
                           OZT_InputPopup*       theInkeyPopup,
                           OZT_FileSelectPopup*  theFSelectPopup,
                           OZT_FileViewerPopup*  theFViewerPopup,
                           OZT_PromptNotice*     thePromptNotice,
                           OZT_ChildHandler*     theChildHandler);
extern void ozt_terminateParser();
extern int  yyparse();


//*****************************************************************************

OZT_Interpreter::OZT_Interpreter(OZT_SourceMgr*        theSourceMgr,
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
                                 OZT_ChildHandler*     theChildHandler)
: 
    pIOWin(theIOWinPtr),
    pInputPopup(theInputPopup),
    pInkeyPopup(theInkeyPopup),
    pFSelectPopup(theFSelectPopup),
    pFViewerPopup(theFViewerPopup),
    varstore(theVarStore),
    cmdSender(theCmdSender),
    rspCatcher(theRspCatcher),
    chdHandler(theChdHandler),
    clock(theClock),
    theState(IDLE),
    isAloneCommand_( FALSE )
{
    TRACE_IN(trace, OZT_Interpreter, "");

    ozt_initTokenizer(this);

    ozt_initParser(theSourceMgr,
                   this,
                   &theVarStore,
                   &theCmdRspBuf,
                   &theCmdSender,
                   &theFileMgr,
                   &theFileLogger,
                   &theMailLogger,
                   &thePrinterLogger,
                   &theRspCatcher,
                   &theClock,
                   &theChdHandler,
		   &theTimeOrdHandler,
                   &theCommentWinModel,
                   pIOWin,
                   pInputPopup,
                   pInkeyPopup,
                   pFSelectPopup,
                   pFViewerPopup,
                   thePromptNotice,
                   theChildHandler);

    TRACE_OUT(trace, OZT_Interpreter, "");
}

//*****************************************************************************

OZT_Interpreter::~OZT_Interpreter()
{
    ozt_terminateParser();
}

//*****************************************************************************

OZT_Result OZT_Interpreter::interpret(const RWCString &theCurrFile,
                                      RWCString &cmdText,
                                      OZT_Flow  &flow_info,
                                      int file_count)
{
    TRACE_IN(trace, interpret, "fileName :" << theCurrFile <<
	     ", cmdText :" << cmdText);

    //
    //  set the state to BUSY, so that this function is not reentrant
    //  (just to be safe :-))
    //
    if (theState == BUSY)
    {
        TRACE_RETURN(trace, interpret, "BUSY");
        return OZT_Result(OZT_Result::BUSY); 
    }
    theState = BUSY;

    //
    //  setup a member variable pointer to point to the current file name 
    //  for this command, some ozterm script command need to know the current
    //  file name
    //
    if( theCurrFile != "" )
      currFileName = theCurrFile;
    else
      isAloneCommand_ = TRUE;
    
    //
    //  Var substitution here
    //
    
    cmdText = varSubst(cmdText);
    cmdText = trim(cmdText);
    
    if (cmdText.length() == 0){
      //
      //  In case the line is actually empty after substitution
      //
      set_result(OZT_Result::NO_PROBLEM);
      set_flow_info(OZT_Flow::NORMAL);
    }  
    else if (isScriptCmd(cmdText)) {
      //
      //  the command is a script command
      //
      TRACE_FLOW(trace, interpret, "processing script command");
      
      //
      //  Setting up buffers for yyparse()
      //

      cmdText.append('\n');  // add a end of text marker
      buf   = &cmdText;
      index = 0;
      index_bound = cmdText.length();
      lookahead_buf.clear();
      
      //
      //  Calling yyparse()
      //
      TRACE_FLOW(trace, interpret, "calling yyparse()");
      yyparse();

      if ((file_count >= MAX_OPEN_FILES) && 
	  (flow.code == OZT_Flow::INCLUDE)){
	  set_result(OZT_Result::INCLUDE_NOT_EXECUTED);
      }    
    }
    else {
      //
      //  The command is a host command 
      //
      TRACE_FLOW(trace, interpret, "processing host command");
      set_result(cmdSender.sendCmd(theCurrFile, cmdText, TRUE));
      set_flow_info(OZT_Flow::NORMAL);
    }
    
    flow_info = flow;   // flow were set by yyparse or sendHostCmd
    
    TRACE_RETURN(trace, interpret, "result : " << result << ", flow : " << flow_info);
    theState = IDLE;
    isAloneCommand_ = FALSE;
    return result;
}

//*****************************************************************************

RWCString OZT_Interpreter::varSubst(const RWCString &cmdText)
{
    RWCString  inLine, outLine;
    OZT_Value  expandedText;
    RWCString  varname;
    RWTRegex<char>  scanner( R"(\{[^\{\}]+\})");
    size_t     start;
    size_t     pos;
    size_t     len;

    //
    //  Recursive variable substitution
    // 
    inLine = cmdText;
    for (;;)
    {
        outLine = RWCString();
        start = 0;
        //
        //  Scan through the line for one round of substitution
        //
        while (start < inLine.length())
        {
            pos = scanner.index(inLine, &len, start);
            if (pos == RW_NPOS)
            {
                // no match
                outLine = (RWCString)outLine + (RWCString)inLine(start, inLine.length() - start);
                break;
            }
         
            varname = inLine(pos+1, len-2);
            varname = trim(varname);
            varname.toUpper();
            //
            //  substitute the variable, if possible
            // 
            if (varstore.get(varname, expandedText))
                outLine = (RWCString)outLine + (RWCString)inLine(start, pos - start) 
                          + (RWCString)expandedText;
            else
                outLine = (RWCString)outLine + (RWCString)inLine(start, pos + len - start);
                
            start = pos + len;
        }
        if (inLine == outLine)   // no change is possible
            return outLine;

        inLine = outLine;
    }
    return outLine;
} 

//*****************************************************************************

RWBoolean OZT_Interpreter::isScriptCmd(const RWCString& cmdText)
{
    static RWTRegex<char> scriptCmdChecker("^[\t ]*[@/!]");  // pavn check
    size_t len = cmdText.length();
    if(!scriptCmdChecker.matchAt(cmdText,size_t(0),len))
        return FALSE;
    else
        return TRUE;
}

//*****************************************************************************

void OZT_Interpreter::interrupt()
{
    TRACE_IN(trace, interrupt, "");

    if (theState == BUSY)
    {
        // broadcasts the interrupt to run-time support objects that can block.
        cmdSender.interrupt();
        rspCatcher.interrupt();
        chdHandler.interrupt();
        clock.interrupt();

        if (pIOWin != 0)
            pIOWin->interrupt();

        if (pInputPopup != 0)
            pInputPopup->interrupt();

        if (pInkeyPopup != 0)
            pInkeyPopup->interrupt();

        if (pFSelectPopup != 0)
            pFSelectPopup->interrupt();

        if (pFViewerPopup != 0)
            pFViewerPopup->interrupt();
    }

    TRACE_OUT(trace, interrupt, "");
}

//*****************************************************************************

void OZT_Interpreter::overriden_unput(int c)
{
    lookahead_buf.insert(c);
}

//*****************************************************************************

int OZT_Interpreter::overriden_input()
{
    int a;

    if (!lookahead_buf.isEmpty())
    {
        a = lookahead_buf.last();
        lookahead_buf.removeLast();
    } else if (index < index_bound)
        a = (int)((unsigned char)((*buf)[index++]));
    else
        a = 0;

    return a;
}

//*****************************************************************************

void OZT_Interpreter::set_result(const OZT_Result::Code code)
{
    TRACE_IN(trace, set_result, result);
    OZT_Interpreter::result = OZT_Result(code);
    TRACE_OUT(trace, set_result, result);
}

//*****************************************************************************

void OZT_Interpreter::set_result(const OZT_Result &res)
{
    TRACE_IN(trace, set_result, res);
    OZT_Interpreter::result = res;
    TRACE_OUT(trace, set_result, "");
}

//*****************************************************************************

void OZT_Interpreter::set_flow_info(const OZT_Flow::Code code)
{
  TRACE_IN(trace, set_flow_info, flow);
  OZT_Interpreter::flow = OZT_Flow(code);
  TRACE_OUT(trace, set_flow_info, "");
}

//*****************************************************************************

void OZT_Interpreter::set_flow_info(const OZT_Flow &_flow)
{
    TRACE_IN(trace, set_flow_info, _flow);
    OZT_Interpreter::flow = _flow;

    TRACE_OUT(trace, set_flow_info, "");
}

//*****************************************************************************

void OZT_Interpreter::setSkipElseFlag()
{
    OZT_Interpreter::flow.skipElseFlag = TRUE;
}

//*****************************************************************************

RWCString OZT_Interpreter::getCurrFileName() const
{
    return currFileName;
}
