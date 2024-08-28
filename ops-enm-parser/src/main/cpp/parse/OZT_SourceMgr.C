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

#include <OZT_SourceMgr.H>
#include <OZT_Misc.H>
#include <OZT_EventHandler.H>
#include <OZT_RunTimeNLS.H>
#include <OZT_SourceKeeper.H>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <ctype.h>


//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_SourceMgr";


//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_SourceMgr.C,v 21.0 1996/08/23 12:44:49 ehsgrap Rel $";


//*****************************************************************************

extern OZT_EventHandler *ozt_evHandlerPtr;
extern RWCString ozt_displayInfo;

//*****************************************************************************


OZT_SourceMgr::OZT_SourceMgr(CORBA::ORB_var pOrb,
			     OPS::ServerRouterListener_ptr theListener,
			     const RWCString & session_id,
			     OZT_IOW *iow, 
                             OZT_InputPopup *inputPopup,
                             OZT_InputPopup *inkeyPopup,
                             OZT_FileSelectPopup *fSelectPopup,
                             OZT_FileViewerPopup *fViewerPopup,
                             OZT_PromptNotice *promptNotice,
                             OZT_ChildHandler *childHandler)
  : sessionId_( session_id),
    pIOWin(iow),
    pInputPopup(inputPopup),
    pInkeyPopup(inkeyPopup),
    pFSelectPopup(fSelectPopup),
    pFViewerPopup(fViewerPopup),
		pChildHandler(childHandler),
		currSource(0),
    cmdRspBuf(),
    cmdSender(cmdRspBuf),
    fileLogger(cmdRspBuf),
    mailLogger(cmdRspBuf, ozt_evHandlerPtr),
    printerLogger(cmdRspBuf, ozt_evHandlerPtr),
    clock(theListener, cmdSender),
    rspCatcher(theListener, cmdRspBuf, indicator, cmdSender),
    chdHandler(cmdRspBuf),
    phase("Phase not set."), // TODO: Use NLS message file.
    progress(0),
    totalCount(0),
    interpreter(this,
		varstore, 
		cmdRspBuf, 
		cmdSender, 
		fMgr, 
		fileLogger,
		mailLogger,
		printerLogger,
		rspCatcher, 
		clock, 
		chdHandler, 
		timeOrdHandler, 
		commentWinModel,
		iow, 
		inputPopup, 
		inkeyPopup,
		fSelectPopup,
		fViewerPopup,
		promptNotice,
		childHandler),
    interrupted(FALSE),
    listener(theListener)
{
    TRACE_IN(trace, OZT_SourceMgr, "");

    OZT_SourceKeeper*  sourceKeeper = OZT_SourceKeeper::Instance();
    sourceKeeper->setSourceMgrPointer(this);

    TRACE_OUT(trace, OZT_SourceMgr, "");
}

//*****************************************************************************

OZT_SourceMgr::~OZT_SourceMgr()
{
    clearAllSourceInfo();
}
//*****************************************************************************

RWCString OZT_SourceMgr::getSessionId(){
  return sessionId_;
}
//*****************************************************************************
RWBoolean OZT_SourceMgr::constructOK() const
{
    return cmdSender.constructOK();
}

//*****************************************************************************

void OZT_SourceMgr::interrupt()
{
    TRACE_IN(trace, interrupt, "");

    // First, get the state of the command sender (is it FUNBUSY?).
    // Need to read it first because interpreter.interrupt() will
    // probably reset it...
    cmdSenderState = cmdSender.getState();
    interrupted = TRUE;
    
    interpreter.interrupt();
    cmdSender.interrupt();

    TRACE_OUT(trace, interrupt, "");
}

//*****************************************************************************

void OZT_SourceMgr::reset(RWBoolean clearSourceInfo)
{
    TRACE_IN(trace, reset, "");

    cmdSender.orderOn();

    cmdSender.reportOff();

    ozt_errHandler.reset();
    varstore.clearAll();
    if(clearSourceInfo) {	
        clearAllSourceInfo();
    }
    printerLogger.off();
    fileLogger.closeAllLogs();
    cmdSender.setFunBusyParam(OZT_Value(OZT_CmdSender::defaultFBAttempts),
                              OZT_Value(OZT_CmdSender::defaultFBInterval));
    cmdSender.setOKReply(RWCString());
    cmdSender.setFailReply(RWCString());
    phase = "Phase not set."; // TODO: Use NLS message file.
    progress = 0;
    totalCount = 0;

    if (pIOWin != 0)
    {
        pIOWin->clrscr();
        pIOWin->close();
    }

    commentWinModel.beInactive();

    TRACE_OUT(trace, reset, "");
}

//*****************************************************************************

void OZT_SourceMgr::clearAllSourceInfo()
{
    TRACE_IN(trace, clearAllSourceInfo, "");

    sourceStack.clearAndDestroy();
    if (currSource != 0)
    {
         delete currSource;
         currSource = 0;
    }
    changed();

    TRACE_OUT(trace, clearAllSourceInfo, "");
}

//*****************************************************************************

RWBoolean OZT_SourceMgr::isActive() const
{
    if (currSource != 0)
        return TRUE;
    else
        return FALSE;
}

//*****************************************************************************

void OZT_SourceMgr::getCurrPos(RWCString& fileName, 
                               LineNo& lineNo,
                               LineNo& numLines)
{
    if (currSource == 0) 
    {
        fileName = RWCString();
        lineNo   = 0;
        numLines = 0;
        return;
    }
    fileName = currSource->getFileName();
    lineNo   = currSource->getLineNo();
    numLines = currSource->currCmdLength();
}

//*****************************************************************************

OZT_Result OZT_SourceMgr::update(const RWCString& filename)
{
    TRACE_IN(trace, update, filename);

    OZT_SourceInfo *temp;
    OZT_Result      result;

    if ((temp = findByFilename(filename)) != NULL)
    {
        result = temp->update();
        TRACE_RETURN(trace, update, result);
        return result;
    }
    else 
    {
        TRACE_RETURN(trace, update, "FILE_NOT_LOADED");
        result.code = OZT_Result::FILE_NOT_LOADED;
        return result;
    }
}

//*****************************************************************************

OZT_SourceInfo* OZT_SourceMgr::getCurrSourceInfo()
{
    return currSource;
}

//*************************************************************************
//  Pre-cond: sourceStack.entries() != 0
//
//  Post-cond: currSource = old top of sourceStack
//             old top of sourceStack removed
//
void OZT_SourceMgr::popFile()
{
    TRACE_IN(trace, popFile, "");

    if (currSource != 0)
        delete currSource;
    currSource = sourceStack.removeLast();
    changed();

    TRACE_OUT(trace, popFile, "");
}

//*************************************************************************
//  Pre-cond: pSourceInfo != 0 
//
//  Post-cond: currSource == new source info object
//             sourceStack top contains the old currSource
//
void OZT_SourceMgr::pushFile(OZT_SourceInfo *pSourceInfo)
{
    TRACE_IN(trace, pushFile, "");

    if (currSource != 0)
        sourceStack.insert(currSource);  // What if this fails???
    currSource = pSourceInfo;
    changed();
   
    TRACE_OUT(trace, pushFile, "");
}

//*************************************************************************
//
//  Post-cond: 
//
//  NO_PROBLEM          (returns a pointer to the new sourceInfo object)
//
//  CYCLIC_INCLUDE_ERR  (returns 0)
//
//  MEM_ALLOC_ERR       (returns 0)
//
//  any other values    (returns 0)
//
OZT_SourceInfo* OZT_SourceMgr::createSource(const RWCString& fileName,
                                            OZT_Result& result)
{
    TRACE_IN(trace, createSource, fileName);

    OZT_SourceInfo  *tempSource;
    RWCString pathName;

    //
    //  Construct the absolute path if necessary
    //
    pathName = ozt_normalisePath(fileName);

    //
    //   Check if the file is already loaded
    //
    if (findByFilename(pathName) != 0)
    {
        TRACE_OUT(trace, createSource, "CYCLIC_INCLUDE_ERR");
        result = OZT_Result(OZT_Result::CYCLIC_INCLUDE_ERR);
        return 0;
    }

    //
    //   Create the new sourceInfo object
    //
    tempSource = new OZT_SourceInfo(pathName, varstore);
    if (tempSource == 0)
    {
        TRACE_OUT(trace, createSource, "MEM_ALLOC_ERR");
        result = OZT_Result(OZT_Result::MEM_ALLOC_ERR);
        return 0;
    }

    result = tempSource->constructStatus();
    if (result.code != OZT_Result::NO_PROBLEM) 
    {
        delete tempSource;
        TRACE_OUT(trace, createSource, result);
        return 0;
    }
    
    TRACE_OUT(trace, createSource, "NO_PROBLEM");
    return tempSource;
}


OZT_Result OZT_SourceMgr::getLabelLine( const RWCString& label, LineNo& line ){
 
  if( currSource != NULL ){
    OZT_Result result;

    result = currSource->lineLabel( label, line );
    TRACE_RETURN(trace, getLabelLine, result);

    return result;
  }
  else {
    TRACE_RETURN(trace, getLabelLine, "FILE_NOT_LOADED");
    OZT_Result result;

    result.code = OZT_Result::FILE_NOT_LOADED;

    return result;
  }
}
//*****************************************************************************

OZT_Result OZT_SourceMgr::setCurrPos(const RWCString &filename,
                                     const RWCString &label,
				     RWBoolean skip_comments)
{
    TRACE_IN(trace, setCurrPos, filename << ", " << label);

    OZT_Result result;

    result = setCurrPos(filename, 0, skip_comments);
    if (result.code == OZT_Result::NO_PROBLEM)
        result =  currSource->gotoLabel(label);

    TRACE_RETURN(trace, setCurrPos, result);
    return result;
}

//*****************************************************************************

void OZT_SourceMgr::setListener(OPS::ServerRouterListener_ptr theListener){
	TRACE_IN(trace, setListener, "");
	
	listener = theListener;
	
    TRACE_OUT(trace, setListener, "");
}

//***************************************************************************
//
//  Post-cond: 
//
//  NO_PROBLEM   (current position set to the first executable line
//                after "line" in "filename")
//
//  other values (nothing changed)
//
OZT_Result OZT_SourceMgr::setCurrPos(const RWCString &filename, 
                                     const LineNo line,
				     RWBoolean skip_comments)
{
    TRACE_IN(trace, setCurrPos, filename << ", " << line);

    OZT_Result result;
    RWCString pathName;
    
    if (line < 0)
    {
        result = OZT_Result(OZT_Result::PROGRAM_TERMINATED);
        TRACE_RETURN(trace, setCurrPos, result.toMsg());
        return result;
    }

    //
    //  need to construct the absolute path
    //
    pathName = ozt_normalisePath(filename);

    OZT_SourceInfo *tempSource = findByFilename(pathName);
   
    if (tempSource == 0)
    {
        //
        //  create the new SourceInfo object, since it has not been loaded
        //
        tempSource = createSource(pathName, result);
        if (result.code != OZT_Result::NO_PROBLEM)
        {
            TRACE_RETURN(trace, setCurrPos, result);
            return result;
        }
           
        //
        //  set the line no.
        //
        if (!tempSource->setLine(line, skip_comments))
        {
            delete tempSource;
            return OZT_Result(OZT_Result::INVALID_LINE_NO);
        }   

        //
        //  pop all the files and set the currSource to the new object
        //
        clearAllSourceInfo();
        pushFile(tempSource);
    }
    else
    {
        //
        //  set the line no.
        //

        if (!tempSource->setLine(line, skip_comments))
        {
            TRACE_RETURN(trace, setCurrPos, "INVALID_LINE_NO");
            return OZT_Result(OZT_Result::INVALID_LINE_NO);
        }

        //
        //  Keep popping the file stack until the file is on the top
        //  (can't fail as findByFilename() said so)
        //
        while (currSource != tempSource)
            popFile();
        assert(currSource != 0); 
    }

    TRACE_RETURN(trace, setCurrPos, "NO_PROBLEM");
    return OZT_Result(OZT_Result::NO_PROBLEM);
}


OZT_Result  OZT_SourceMgr::step(OZT_SourceInfo& source, int file_count, RWBoolean skip_comments ){
 
  TRACE_IN(trace, executeLine, "step 1");
  OZT_Result result;
  OZT_Flow   flow_info;
  RWCString commandLine;
  
  if (currSource != 0              &&
      currSource->getLineNo() < 0  &&
      ! source.isManualCommandEntry())
  {
      // The script is already finished.
      result = OZT_Result(OZT_Result::PROGRAM_TERMINATED);
      TRACE_RETURN(trace, step, result);
      return result;
  }

  char skipComm = skip_comments?1:0;

  result = source.getCurrCmdText( commandLine, skipComm );

  if( result.code == OZT_Result::NO_PROBLEM ){
    if( cmdSender.getState() == OZT_CmdSender::CONNECTION_LOST ) {
      cmdSender.setIdle();
      if( cmdSender.isOnDisconnectSet() ){
	result = advance( OZT_Flow(OZT_Flow::GOTO_LABEL,
				   cmdSender.getOnDisconnectLabel()) );
	TRACE_RETURN(trace, step, result);
	return result;    
      }
    }  
    
    result = interpreter.interpret("",
				   commandLine, 
				   flow_info,
				   file_count);
    // Either the code was executed alright or checking has been
    // turned off by using '@CHECK("OFF)'  
    if (result.code == OZT_Result::NO_PROBLEM){
      // interrupted while FUNCTION BUSY, so don't advance the
      // current position as we might want to resend the MML
      // command
      if(cmdSenderState == OZT_CmdSender::FUNBUSY_WAIT ||
	 cmdSenderState == OZT_CmdSender::FUNBUSY_WAIT_CONFIRMED){
      }
      else {
	result = source.advance();
      }
    }
  }
    
  TRACE_OUT(trace, step, result);
  
  return result;
}

//***************************************************************************
//
//  Pre-cond: OZT_SourceMgr::isActive() gives TRUE
//
//  Post-cond: returns result of the execution
//             current position will be pointing to one of the following:
//
//             - the next command to be executed, or
//             - the command that failed, or
//             - the command that terminated the program.
//

OZT_Result OZT_SourceMgr::step(int file_count, RWBoolean skip_comments)
{
    TRACE_IN(trace, step, "step 2");

    RWCString  buf;
    OZT_Result result;
    OZT_Flow   flow_info;

    assert(isActive());

    // First reset `interrupted' because we just started
    // "stepping". It can only be set as a consequence of the "Stop"executeLine
    // button being pressed and we are interested if it is pressed
    // during the call to interpreter.interpret() below.
    //
    // Ideally, the status object could contain information about the
    // state at interrupt time, maybe?
    
    interrupted = FALSE;
    cmdSenderState = OZT_CmdSender::IDLE; // "reset" it

    if (currSource->getLineNo() < 0) {
        // The script is already finished.
        result = OZT_Result(OZT_Result::PROGRAM_TERMINATED);
        TRACE_RETURN(trace, step, result);
        return result;
    }

    char skipComm = skip_comments?1:0;
        
    currSource->getCurrCmdText(buf, skipComm);
    
    if( cmdSender.getState() == OZT_CmdSender::CONNECTION_LOST ) {
    TRACE_FLOW(trace, step, "Connection was lost");
	  cmdSender.setIdle();
	  if( cmdSender.isOnDisconnectSet() ){
	    result = advance( OZT_Flow(OZT_Flow::GOTO_LABEL,
				 cmdSender.getOnDisconnectLabel()) );
	    TRACE_RETURN(trace, step, result);
	    return result;    
	  }
    }  

    result = interpreter.interpret(currSource->getFileName(),
                                   buf, 
                                   flow_info,file_count);

    if (result.code == OZT_Result::NO_PROBLEM)
    {
        // Either the code was executed alright or checking has been
        // turned off by using '@CHECK("OFF)'
        if (interrupted &&
            (cmdSenderState == OZT_CmdSender::FUNBUSY_WAIT ||
             cmdSenderState == OZT_CmdSender::FUNBUSY_WAIT_CONFIRMED))
        {
            // interrupted while FUNCTION BUSY, so don't advance the
            // current position as we might want to resend the MML
            // command
        }

        else
        {
            result = advance(flow_info);
        }
    }
    
    TRACE_RETURN(trace, step, result);
    return result;
}

//*****************************************************************************

OZT_VarStore& OZT_SourceMgr::getVarStore()
{
    return varstore;
}

//*****************************************************************************

OZT_CmdRspBuf& OZT_SourceMgr::getCmdRspBuf()
{
    return cmdRspBuf;
}

//*****************************************************************************

OZT_Interpreter& OZT_SourceMgr::getInterpreter()
{
    return interpreter;
}

//*****************************************************************************

OZT_CmdSender& OZT_SourceMgr::getCmdSender()
{
    return cmdSender;
}

//*****************************************************************************

OZT_Indicator& OZT_SourceMgr::getIndicator()
{
    return indicator;
}

//*****************************************************************************

CHA_FileLogger& OZT_SourceMgr::getFileLogger()
{
    return fileLogger;
}

//*****************************************************************************

CHA_MailLogger& OZT_SourceMgr::getMailLogger()
{
    return mailLogger;
}

//*****************************************************************************

CHA_PrinterLogger& OZT_SourceMgr::getPrinterLogger()
{
    return printerLogger;
}

//*****************************************************************************

OZT_RspCatcher& OZT_SourceMgr::getRspCatcher(){
  return rspCatcher;
}

//*****************************************************************************

OZT_Clock& OZT_SourceMgr::getClock()
{
    return clock;
}

//*****************************************************************************

OZT_CommentWinModel& OZT_SourceMgr::getCommentWinModel()
{
    return commentWinModel;
}

//*************************************************************************

void OZT_SourceMgr::setPhaseDescription(RWCString _phase){
  TRACE_IN(trace, setPhaseDescription, OZT_SourceMgr::phase);
  OZT_SourceMgr::phase = _phase;
  // Send total progress to client by server router object
  listener->setPhase(OZT_SourceMgr::phase);
  TRACE_OUT(trace, setPhaseDescription, OZT_SourceMgr::phase);
}

//*************************************************************************

RWCString OZT_SourceMgr::getPhaseDescription(){
  TRACE_RETURN(trace, getPhaseDescription, phase);
  return phase;
}
  
  
//*************************************************************************

OZT_Result OZT_SourceMgr::setTotalCount(const OZT_Value& _totalCount){
  
  TRACE_IN(trace, setTotalCount, OZT_SourceMgr::totalCount);

  long cnt;
  OZT_Result result;

  cnt = _totalCount.toLong(result);
  if (result.code != OZT_Result::NO_PROBLEM)
    return OZT_Result(OZT_Result::INVALID_VALUE).filtered();

  OZT_SourceMgr::totalCount = cnt;
  // Send total progress to client by server router object
  listener->setTotalProgress(OZT_SourceMgr::totalCount);

  TRACE_OUT(trace, setTotalCount, OZT_SourceMgr::totalCount);
  return result;
}

//*************************************************************************

long OZT_SourceMgr::getTotalCount(){
  TRACE_RETURN(trace, getTotalCount, totalCount);
  return totalCount;
}

//*************************************************************************

OZT_Result OZT_SourceMgr::setProgress(const OZT_Value& _progress){
  TRACE_IN(trace, setProgress, OZT_SourceMgr::progress);

  long prg;
  OZT_Result result;

  prg = _progress.toLong(result);
  if (result.code != OZT_Result::NO_PROBLEM)
    return OZT_Result(OZT_Result::INVALID_VALUE).filtered();

  OZT_SourceMgr::progress = prg;

  // Send progress to client by server router object
  listener->setProgress(OZT_SourceMgr::progress);

  TRACE_OUT(trace, setProgress, OZT_SourceMgr::progress);
  return result;
}

//*************************************************************************

long OZT_SourceMgr::getProgress(){
  TRACE_RETURN(trace, getProgress, progress);
  return progress;
}

//*************************************************************************

OZT_Result OZT_SourceMgr::stepProgress(const OZT_Value& interval){
  TRACE_IN(trace, stepProgress, OZT_SourceMgr::progress);
  
  long prg;
  OZT_Result result;

  prg = interval.toLong(result);
  if (result.code != OZT_Result::NO_PROBLEM)
    return OZT_Result(OZT_Result::INVALID_VALUE).filtered();

  OZT_SourceMgr::progress += prg;
  // Send progress to client by server router object
  listener->setProgress(OZT_SourceMgr::progress);
  
  TRACE_OUT(trace, stepProgress, OZT_SourceMgr::progress);
  return result;
}
  
//*************************************************************************
//
// Post-cond: returns a pointer to the sourceInfo object that matches
//            the fileName.
//
OZT_SourceInfo* OZT_SourceMgr::findByFilename(const RWCString& filename)
{
    int i = sourceStack.entries() - 1;

    if ((currSource != 0) && (currSource->getFileName() == filename))
        return currSource;

    while (i >= 0) 
    {
        if (sourceStack[i]->getFileName() == filename)
            return sourceStack[i];
        i--;
    }
    return 0;
}

//*****************************************************************************

RWCString OZT_SourceMgr::findFileByForLoopIdx(const RWCString& varname) const
{
    if (!isActive())
        return RWCString();

    if (currSource->forLoopIndexUsed(varname))
        return currSource->getFileName();

    for (size_t i=0; i < sourceStack.length(); i++)
        if (sourceStack[i]->forLoopIndexUsed(varname))
            return sourceStack[i]->getFileName();

    return RWCString();
}

//**************************************************************************
//
// Pre-cond: isActive()
//
// Post-cond:  currSource points to the right sourceInfo
//             the current position of currSource is pointing to one of the
//             following:
//
//             - the next command to be executed, or
//             - the command that fails, or
//             - the command that terminates the program.
//
OZT_Result  OZT_SourceMgr::advance(OZT_Flow flow)
{
    TRACE_IN(trace, advance, flow);

    OZT_Result result;
    OZT_SourceInfo *pTempSourceInfo;
    RWCString tempStr;
    OZT_Value value;
    assert(isActive());

    for(;;) 
      {
        switch(flow.code) 
	  {
	  case OZT_Flow::NORMAL: 
	    if (flow.skipElseFlag == TRUE)
	      result = currSource->skipElse();
	    else
	      result = currSource->advance();
	    if (result.code == OZT_Result::HIT_EOF) 
	      {
		flow = OZT_Flow(OZT_Flow::END_OF_FILE); 
		continue;
	      } 
	    else 
	      {
		TRACE_RETURN(trace, advance, result);
		return result;
	      }
	    
	  case OZT_Flow::FOR_SETUP:
	    tempStr = findFileByForLoopIdx(flow.info1);
	    if (!tempStr.isNull())
	      {
		TRACE_RETURN(trace, advance, "interated on the same var");
		return OZT_Result(OZT_Result::ITERATED_ON_SAME_VAR,
				  (OZT_Value)tempStr);
	      }
	    result = currSource->forLoopSetUp(flow.info1, 
					      (OZT_Value)flow.info2, 
					      (OZT_Value)flow.info3);
	    if (result.code == OZT_Result::HIT_EOF)
	      {
		flow = OZT_Flow(OZT_Flow::END_OF_FILE);
		continue;
	      }
	    else
	      {
		TRACE_RETURN(trace, advance, result);
		return result;
	      }
	    
	  case OZT_Flow::NEXT:
	    result = currSource->forLoopNext(flow.info1);
	    if (result.code == OZT_Result::HIT_EOF)
	      {
		flow = OZT_Flow(OZT_Flow::END_OF_FILE);
		continue;
	      }
	    else
	      {
		TRACE_RETURN(trace, advance, result);
		return result;
	      }
	    
	  case OZT_Flow::GOTO_LABEL : 
	    result = currSource->gotoLabel(flow.info1);
	    TRACE_RETURN(trace, advance, result);
	    return result;
	    
	  case OZT_Flow::GOSUB_LABEL :
	    result = currSource->gosubLabel(flow.info1, flow.skipElseFlag);
	    TRACE_RETURN(trace, advance, result);
	    return result;
	    
	  case OZT_Flow::RETURN_FROM_GOSUB  :
	    result = currSource->returnFromGosub();
	    if (result.code == OZT_Result::HIT_EOF)
	      {
		flow = OZT_Flow(OZT_Flow::END_OF_FILE);
		continue;
	      }
	    else
	      {
		TRACE_RETURN(trace, advance, result);
		return result;
	      }
	    
	  case OZT_Flow::INCLUDE :
	    pTempSourceInfo = createSource(flow.info1, result);
	    if (result.code == OZT_Result::NO_PROBLEM)
	      {
		pushFile(pTempSourceInfo);
		TRACE_RETURN(trace, advance, result);
		return result; 
	      }
	    else if (result.code == OZT_Result::HIT_EOF)
	      {
		//  pushFile(pTempSourceInfo);
		//  flow = OZT_Flow(OZT_Flow::END_OF_FILE);
		//  continue;
		
		flow = OZT_Flow(OZT_Flow::NORMAL); 
		flow.skipElseFlag = TRUE;
		continue;
	      }
	    else
	      {
		// delete pTempSourceInfo;
		if (ozt_errHandler.isCheckOn())
		  {
		    TRACE_RETURN(trace, advance, result);
		    return result;
		  }
		else
		  {
		    ozt_errHandler.setFlag(); 
		    flow = OZT_Flow(OZT_Flow::NORMAL);
		    flow.skipElseFlag = TRUE;
		    continue;
		  }
	      }
	    
	  case OZT_Flow::END_OF_FILE:
	    if (sourceStack.entries() == 0) 
	      {
		TRACE_RETURN(trace, advance, "PROGRAM_TERMINATED");
		return OZT_Result(OZT_Result::PROGRAM_TERMINATED);
	      } 
	    else 
	      {
		popFile();
		flow = OZT_Flow(OZT_Flow::NORMAL); 
		flow.skipElseFlag = TRUE;
		continue;
	      }
	    
	  case OZT_Flow::PAUSE:
	    TRACE_RETURN(trace, advance, "PAUSE");
	    return OZT_Result(OZT_Result::PAUSE);
	    
	  case OZT_Flow::QUIT:
	    TRACE_RETURN(trace, advance, "QUIT");
	    return OZT_Result(OZT_Result::QUIT);
	    
	  case OZT_Flow::STOP:
	    TRACE_RETURN(trace, advance, "STOP");
	    return OZT_Result(OZT_Result::STOP);
	    
	  case OZT_Flow::RESTART:
	    if(currSource != NULL)
	    {
	      currSource->emptyFlowStack();
	    }
	    (void)currSource->setLine(0);
	    TRACE_RETURN(trace, advance, "RESTART");
	    return OZT_Result(OZT_Result::NO_PROBLEM);
	    
	  case OZT_Flow::FILE_HALTED:
	    if (sourceStack.entries() == 0)
	      {
		TRACE_RETURN(trace, advance, "FILE_HALTED");
		return OZT_Result(OZT_Result::FILE_HALTED);
	      } 
	    else 
	      {
		popFile();
		flow = OZT_Flow(OZT_Flow::NORMAL); 
		flow.skipElseFlag = TRUE;
		continue;
	      }
	  case OZT_Flow::IF:
	    result = currSource->ifElseSetup( OZT_Value( flow.info1 ) );
	    return result;
	  case OZT_Flow::ELSE:
	    result = currSource->elseFound();
	    return result;
	  case OZT_Flow::ENDIF:
	    result = currSource->endifFound();
	    if (result.code == OZT_Result::HIT_EOF) 
	      {
		flow = OZT_Flow(OZT_Flow::END_OF_FILE); 
		continue;
	      } 
	    else 
	      {
		TRACE_RETURN(trace, advance, result);
		return result;
	      }
	  case OZT_Flow::BREAK:
	    result = currSource->forLoopBreak();
	    return result;
	  case OZT_Flow::SWITCH:
	      result = currSource->switchSetup(  OZT_Value( flow.info1 ) );
	      return result;
	  case OZT_Flow::CASE:
	    result = currSource->caseFound( OZT_Value( flow.info1 ) );
	    return result;
	  case OZT_Flow::DEFAULT:
	    result = currSource->defaultFound();
	    return result;
	  case OZT_Flow::ENDSWITCH:
	    result = currSource->endswitchFound();
	    if (result.code == OZT_Result::HIT_EOF) 
	      {
		flow = OZT_Flow(OZT_Flow::END_OF_FILE); 
		continue;
	      } 
	    else 
	      {
		TRACE_RETURN(trace, advance, result);
		return result;
	      }
	  case OZT_Flow::UNDEFINED:
	    TRACE_RETURN(trace, advance, "INTERNAL_ERR (undefined flow)");
	    return OZT_Result(OZT_Result::INTERNAL_ERR, "undefined flow");
        }
    }
}
