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

#include <OZT_SourceInfo.H>
#include <OZT_Misc.H>
#include <iostream>
#include <fstream>
#include <errno.h>
#include <rw/ctoken.h>
#include <rw/tools/regex.h>
 
//*****************************************************************************

// trace
#include <trace.H>
static std::string trace ="OZT_SourceInfo";

//*****************************************************************************

// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_SourceInfo.C,v 21.0 1996/08/23 12:44:43 ehsgrap Rel $";


//*****************************************************************************
OZT_IfStackFrame::OZT_IfStackFrame(const LineNo ifLineNo, const LineNo elseLineNo, const LineNo endifLineNo){
  
  TRACE_IN(trace, OZT_IfStackFrame, "ifLineNo:" << ifLineNo << " elseLineNo:" << elseLineNo << " endifLineNo:" << endifLineNo );

  ifLineNo_ = ifLineNo;
  elseLineNo_ = elseLineNo;
  endifLineNo_ = endifLineNo;

  TRACE_OUT(trace, OZT_IfStackFrame, "");
}

//*****************************************************************************
OZT_IfStackFrame::~OZT_IfStackFrame(){
}

//*****************************************************************************
FlowFrameType OZT_IfStackFrame::type() const
{
    return OZT_IF;
}

//*****************************************************************************
RWBoolean OZT_IfStackFrame::operator==(const OZT_FlowStackFrame &sf) const
{
    if (sf.type() != OZT_IF) return FALSE;

    OZT_IfStackFrame *temp = (OZT_IfStackFrame *)(&sf);

    if  ((temp->ifLineNo_ == ifLineNo_) 
	 && (temp->elseLineNo_ == elseLineNo_)
	 && (temp->endifLineNo_ == endifLineNo_))
        return TRUE;
    else
        return FALSE;
}
//*****************************************************************************

OZT_SwitchStackFrame::OZT_SwitchStackFrame(const LineNo    line)
{
     OZT_SwitchStackFrame::endswitchLineNo_ = line;
}

//*****************************************************************************
OZT_SwitchStackFrame::~OZT_SwitchStackFrame()
{
    TRACE_IN(trace, ~OZT_SwitchStackFrame, "");
    TRACE_OUT(trace, ~OZT_SwitchStackFrame, "");	
}

//*****************************************************************************
FlowFrameType OZT_SwitchStackFrame::type() const
{
    return OZT_SWITCH;
}

//*****************************************************************************
RWBoolean OZT_SwitchStackFrame::operator==(const OZT_FlowStackFrame &sf) const
{
  if (sf.type() != OZT_SWITCH) return FALSE;
  
  OZT_SwitchStackFrame *temp = (OZT_SwitchStackFrame *)(&sf);
  
  if( temp->endswitchLineNo_ == endswitchLineNo_ ) 
    return TRUE;
  else
    return FALSE;
}

//*****************************************************************************
OZT_GosubStackFrame::OZT_GosubStackFrame(const LineNo    line, 
                                         const RWBoolean skipElse)
{
    OZT_GosubStackFrame::lineNo       = line;
    OZT_GosubStackFrame::skipElseFlag = skipElse; 
}

//*****************************************************************************

OZT_GosubStackFrame::~OZT_GosubStackFrame()
{
    TRACE_IN(trace, ~OZT_GosubStackFrame, "");
    TRACE_OUT(trace, ~OZT_GosubStackFrame, "");
}

//*****************************************************************************

FlowFrameType OZT_GosubStackFrame::type() const
{
    return OZT_GOSUB;
}


//*****************************************************************************
RWBoolean OZT_GosubStackFrame::operator==(const OZT_FlowStackFrame &sf) const
{
    if (sf.type() != OZT_GOSUB) return FALSE;

    OZT_GosubStackFrame *temp = (OZT_GosubStackFrame *)(&sf);

    if  ((temp->lineNo == lineNo) && (temp->skipElseFlag == skipElseFlag))
        return TRUE;
    else
        return FALSE;
}
//*****************************************************************************

OZT_ForLoopStackFrame::OZT_ForLoopStackFrame(const RWCString &var,
                                             const LineNo     start,
					     const LineNo nextLine,
                                             const OZT_Value &last)
{
    OZT_ForLoopStackFrame::varName   = var;
    OZT_ForLoopStackFrame::startLine = start;
    OZT_ForLoopStackFrame::lastValue = last;
    OZT_ForLoopStackFrame::lineWithNext = nextLine;
}

//*****************************************************************************

OZT_ForLoopStackFrame::~OZT_ForLoopStackFrame()
{
    TRACE_IN(trace, ~OZT_ForLoopStackFrame, "");
    TRACE_OUT(trace, ~OZT_ForLoopStackFrame, "");
}

//*****************************************************************************

FlowFrameType OZT_ForLoopStackFrame::type() const
{
    return OZT_FOR_LOOP;
}

//*****************************************************************************

RWBoolean OZT_ForLoopStackFrame::operator==(const OZT_FlowStackFrame &sf) const
{
    if (sf.type() != OZT_FOR_LOOP) return FALSE;

    OZT_ForLoopStackFrame *temp = (OZT_ForLoopStackFrame *)(&sf);

    if  ((temp->varName == varName) &&
         (temp->startLine == startLine) &&
	 (temp->lineWithNext == lineWithNext) &&
         (temp->lastValue == lastValue))
        return TRUE;
    else
        return FALSE;
}

//*****************************************************************************
//
//  Pre-cond : filename not NULL
//
//  Post-cond : 
//
//  stat == NO_PROBLEM (currLine == the first non-commentry line of the first
//                                  command)
//
//  stat == HIT_EOF    (The file contains no executable lines, this object
//                      should not be used anymore)
//
//  stat == any other values (This object should not be used anymore)
//
OZT_SourceInfo::OZT_SourceInfo(OZT_VarStore& theVarStore, 
			       const RWTValOrderedVector<RWCString>& lines)
: labelTbl(),
  varStore(theVarStore),
  isManualCommands(TRUE)
 {
   TRACE_IN(trace, OZT_SourceInfo, "commaandWindow commands");
   OZT_SourceInfo::filename = "";
   
   load( lines );

   if (stat.code != OZT_Result::NO_PROBLEM) {
     TRACE_OUT(trace, OZT_SourceInfo, "stat set to" << stat);
     return;
   }
   //
   //   advance to the first non-commentry line (if any)
   //
   
   TRACE_FLOW(trace, OZT_SourceInfo, "about to skip commentry lines");
   
   currLine = 0;

   skipCommentryLines();
   
   if (currLine < text.entries())
     stat = OZT_Result(OZT_Result::NO_PROBLEM);
   else {
     currLine = -1;
     stat = OZT_Result(OZT_Result::HIT_EOF);
   }   
   TRACE_OUT(trace, OZT_SourceInfo, "stat set to" << stat);
}


OZT_SourceInfo::OZT_SourceInfo(const RWCString& fileName, 
                               OZT_VarStore& theVarStore)
: labelTbl(),
  varStore(theVarStore),
  isManualCommands(FALSE)
{
    TRACE_IN(trace, OZT_SourceInfo, fileName);

    OZT_SourceInfo::filename      = fileName;
    load();  // read the file in and build the label table

    if (stat.code != OZT_Result::NO_PROBLEM) 
    {
        TRACE_OUT(trace, OZT_SourceInfo, "stat set to" << stat);
        return;
    }
    //
    //   advance to the first non-commentry line (if any)
    //

    TRACE_FLOW(trace, OZT_SourceInfo, "about to skip commentry lines");

    currLine = 0;
    skipCommentryLines();
    if (currLine < text.entries())
        stat = OZT_Result(OZT_Result::NO_PROBLEM);
    else {
        currLine = -1;
        stat = OZT_Result(OZT_Result::HIT_EOF);
    }
    TRACE_OUT(trace, OZT_SourceInfo, "stat set to" << stat);
}
//*****************************************************************************
void OZT_SourceInfo::reset() {
  
  TRACE_IN(trace, reset, "");

  labelTbl.clear();
  flowStack.clearAndDestroy();
  
  TRACE_OUT(trace, reset, "");
}
//*****************************************************************************
void OZT_SourceInfo::emptyFlowStack() { 
  TRACE_IN(trace, emptyFlowStack, "");
  flowStack.clearAndDestroy(); 
  TRACE_OUT(trace, emptyFlowStack, "");
}
//*****************************************************************************

OZT_SourceInfo::~OZT_SourceInfo()
{
    TRACE_IN(trace, ~OZT_SourceInfo, "");

    text.clear();
    labelTbl.clear();
    flowStack.clearAndDestroy();

    TRACE_OUT(trace, ~OZT_SourceInfo, "");
}
//**********************************************************

OZT_Result OZT_SourceInfo::lineLabel(RWCString label,LineNo& line)
{
    TRACE_IN(trace, lineLabel, label);
    LineNo      targetLine;
    OZT_Result  result;

    label.toUpper();
    if (labelTbl.findValue(label, targetLine) == TRUE)
    {
        if (targetLine < 0)
        {
            result = OZT_Result(OZT_Result::DUPLICATE_LABELS, label);
   
        }    
        else
        {
            result = OZT_Result(OZT_Result::NO_PROBLEM);
        }
        line = targetLine;
    }
    else 
        result = OZT_Result(OZT_Result::LABEL_NOT_FOUND,label);

    TRACE_RETURN(trace, lineLabel, result);
    return result;
}



//*****************************************************************************

OZT_Result OZT_SourceInfo::constructStatus()
{
    return stat;
}

//***********************************************************************
//
//  Pre-cond : stat == NO_PROBLEM
//
//  Post-cond : TRUE (currLine set to the first non-commentry line
//                          after lineno)
//
//              or
//
//              FALSE (currLine unchanged)
//
//
RWBoolean OZT_SourceInfo::setLine(const LineNo lineno, RWBoolean skip_comments)
{
    TRACE_IN(trace, setLine, lineno);

    if ((lineno < 0) || (lineno >= text.entries())) 
    {
        TRACE_RETURN(trace, setLine, "FALSE");
        return FALSE;
    }

    currLine = lineno;

    if(skip_comments)
      skipCommentryLines();

    if (currLine >= text.entries())
    {
        currLine = -1;
        TRACE_RETURN(trace, setLine, "FALSE");
        return FALSE;
    }
    else
    {
        TRACE_RETURN(trace, setLine, "TRUE");
        return TRUE;
    }
}

//***********************************************************************
OZT_Result OZT_SourceInfo::ifElseSetup( const OZT_Value& condition ){
  TRACE_IN(trace, ifElseSetup, condition );

  OZT_Result result;
  LineNo tempLineNo = currLine;
  LineNo lineWithElse;
  LineNo lineWithEndif;
  OZT_IfStackFrame* ifs;
  RWBoolean conditionValue;

  conditionValue = condition.toBoolean( result );

  if (result.code != OZT_Result::NO_PROBLEM){
    TRACE_RETURN(trace, ifElseSetup, result);
    return result;
  }

  //find the @ELSE statement and the @ENDIF statement
  result = findElseStatement( currLine + 1, lineWithElse );


  result = findEndifStatement( currLine + 1, lineWithEndif );

  if (result.code != OZT_Result::NO_PROBLEM){
    currLine = tempLineNo;
    TRACE_RETURN(trace, ifElseSetup, "NO_MATCHING_ENDIF");
    return OZT_Result(OZT_Result::NO_MATCHING_ENDIF);
  }
  
  //if the @IF condition is true
  if( conditionValue == TRUE ){
    //   find the first executable line in the if body
    (void)advance();
  }
  //if the @IF condition is false
  else{
    if( lineWithElse != -1 ){
      //@ELSE  was defined, execute the @ELSE statement
      currLine = lineWithElse;
      (void)advance();
    }
    else{
      //@ELSE wasn't defined, contiinue after @ENDIF
      currLine = lineWithEndif - 1;
      (void)advance();
    }
  }

  TRACE_FLOW(trace, ifElseSetup, "lineWithEndif" << lineWithEndif);

  ifs = new OZT_IfStackFrame( tempLineNo, lineWithElse, lineWithEndif );
 
  if( ifs == NULL ){
    currLine = tempLineNo;
    TRACE_RETURN(trace, ifElseSetup, "MEM_ALLOC_ERR");      
    return OZT_Result(OZT_Result::MEM_ALLOC_ERR,
			  "OZT_SourceInfo::ifElseSetup()");
  }

  flowStack.append(ifs);

  TRACE_RETURN(trace, ifElseSetup, "NO_PROBLEM");
  return OZT_Result(OZT_Result::NO_PROBLEM);
}
//***********************************************************************

OZT_Result OZT_SourceInfo::forLoopBreak() {
  LineNo      lineWithNext;
  OZT_Result  result;

  //find the FOR loop flow
  OZT_FlowStackFrame* flow  = findFlow( OZT_FOR_LOOP );
  
  //if the FOR loop flow can't be found, it menas that the @BREAK 
  //has been used withour previouslly defined @FOR
  if( flow == NULL ) {
    TRACE_RETURN(trace, forLoopBreak, "BREAK_WITHOUT_FOR");
    return OZT_Result(OZT_Result::BREAK_WITHOUT_FOR);
  }

  //remove the flow object inside of the for-loop
  while( (flowStack.last()->type() != OZT_FOR_LOOP ) )
    delete flowStack.removeLast();
	
  flowStack.remove( flow );
  delete flow;

  currLine = ((OZT_ForLoopStackFrame*)flow)->lineWithNext;
  result = advance();

  TRACE_RETURN(trace, forLoopBreak, result);
  return result;
  
}
//***********************************************************************
OZT_Result OZT_SourceInfo::elseFound(){
  OZT_Result result;

  OZT_FlowStackFrame* flow  = findFlow( OZT_IF );
  if(flow == NULL ) {
    TRACE_RETURN(trace, elseFound, "ELSE_WITHOUT_IF");
    return OZT_Result(OZT_Result::ELSE_WITHOUT_IF);
  }
  
  //advance after endif
  currLine = ((OZT_IfStackFrame*)(flow))->getLineWithEndif() - 1;
  result = advance();
  TRACE_FLOW(trace, elseFound, "currline:" << currLine);
  
  TRACE_RETURN(trace, elseFound, result);
  return result;
  
}
//***********************************************************************

OZT_Result OZT_SourceInfo::switchSetup( const OZT_Value& varValue ) {
  
  TRACE_IN(trace, switchSetup, varValue);

  LineNo tempLineNo = currLine;
  LineNo lineWithMatchingCase = -1;
  LineNo lineWithEndswitch = -1;
  OZT_Result result;
  OZT_SwitchStackFrame* sfs;
  
      
  result = findMatchingCaseStatement( currLine + 1, varValue, lineWithMatchingCase );
  result = findEndswitchStatement( currLine + 1, lineWithEndswitch );
      
  if (result.code != OZT_Result::NO_PROBLEM){
    currLine = tempLineNo;
    TRACE_RETURN(trace, switchSetup, "NO_MATCHING_ENDSWITCH");
    return OZT_Result(OZT_Result::NO_MATCHING_ENDSWITCH);
  }
      
  if( lineWithMatchingCase == -1 ) {
    //   no matching @CASE or @DEFAULT
    currLine = lineWithEndswitch - 1;
  }
  else {
    currLine = lineWithMatchingCase;
  }

  (void)advance();

  //create the stack object
  sfs = new OZT_SwitchStackFrame( lineWithEndswitch );

  flowStack.append(sfs);  

  TRACE_RETURN(trace, switchSetup, "NO_PROBLEM");

  return OZT_Result(OZT_Result::NO_PROBLEM);
}

//***********************************************************************

OZT_Result OZT_SourceInfo::caseFound( const OZT_Value& value ) {

  TRACE_IN(trace, caseFound, "");
  
  OZT_Result result;
    
  OZT_FlowStackFrame* flow = findFlow( OZT_SWITCH );
    
  if( flow == NULL ) {
    TRACE_RETURN(trace, caseFound, "CASE_WITHOUT_MATCHING_SWITCH");
    return OZT_Result(OZT_Result::CASE_WITHOUT_MATCHING_SWITCH);
  } 
    
  //advance after @ENDIF
  currLine = ((OZT_SwitchStackFrame*)(flow))->getLineWithEndswitch() - 1;
  
  result = advance();

  TRACE_FLOW(trace, caseFound, "currline:" << currLine);

  TRACE_RETURN(trace, caseFound, result);
  
  return result;
}

 //***********************************************************************

OZT_Result OZT_SourceInfo::defaultFound() {

  TRACE_IN(trace, defaultFound, "");
  
  OZT_Result result;
    
  OZT_FlowStackFrame* flow = findFlow( OZT_SWITCH );
    
  if( flow == NULL ) {
    TRACE_RETURN(trace, defaultFound, "DEFAULT_WITHOUT_MATCHING_SWITCH");
    return OZT_Result(OZT_Result::DEFAULT_WITHOUT_MATCHING_SWITCH);
  } 
    
  //advance after @ENDIF
  currLine = ((OZT_SwitchStackFrame*)(flow))->getLineWithEndswitch() - 1;
  
  result = advance();

  TRACE_FLOW(trace, defaultFound, "currline:" << currLine);

  TRACE_RETURN(trace, defaultFound, result);
  
  return result;
}

//***********************************************************************

OZT_Result OZT_SourceInfo::endswitchFound() {
  TRACE_IN(trace, endswitchFound, "");
  
  OZT_Result result;
    
  OZT_FlowStackFrame* flow = findFlow( OZT_SWITCH );
    
  if( flow == NULL ) {
    TRACE_RETURN(trace, endswitchFound, "ENDSWITCH_WITHOUT_MATCHING_SWITCH");
    return OZT_Result(OZT_Result::ENDSWITCH_WITHOUT_MATCHING_SWITCH);
  } 
    
  //switch statement terminates; remove the flow stack object
  TRACE_FLOW(trace, endswitchFound, "End of switch statement");
  delete (OZT_SwitchStackFrame *)flowStack.remove( flow );

  result = advance();

  TRACE_RETURN(trace, endswitchFound, result);
  return result;
}

//***********************************************************************
OZT_Result OZT_SourceInfo::findMatchingCaseStatement( LineNo startLineNo,
						      OZT_Value varValue,
						      LineNo& resultLineNo ) {
  TRACE_IN(trace, findMatchingCaseStatement, startLineNo << ", " << varValue << ", " << resultLineNo );

  static RWTRegex<char> caseScanner("^[\t ]*@[\t ]*[cC][aA][sS][eE][\t ]+[A-Za-z0-9]+[\t ]*");
  static RWTRegex<char> defaultScanner("^[\t ]*@[\t ]*[dD][eE][fF][aA][uU][lL][tT][\t ]*");


  LineNo tempLineNo = startLineNo;
  LineNo lastLine = text.entries() - 1;
  resultLineNo = -1;
  RWCString tempLine;

  while (tempLineNo <= lastLine){

    tempLine = stripAllComment(text[tempLineNo]);
   
    //check if this is a @CASE statement
    if(caseScanner.index(tempLine) == RW_NPOS){

      //check if this is a @DEFAULT statement
      if(defaultScanner.index(tempLine) == RW_NPOS){
	tempLineNo++;
      }
      else {
	//@DEFAULT statement found, move to it
	resultLineNo = tempLineNo;
	TRACE_RETURN(trace, findMatchingCaseStatement, "NO_PROBLEM:" << "resultLineNo:" << resultLineNo);
	return OZT_Result(OZT_Result::NO_PROBLEM);
      }
    }
    else{
      RWCTokenizer next( tempLine );
      RWCString caseCommand = next();
      RWCString caseValue = next();
      
      //ok, the matching value is found
      if( caseValue == varValue ) {
	resultLineNo = tempLineNo;
	TRACE_RETURN(trace, findMatchingCaseStatement, "NO_PROBLEM:" << "resultLineNo:" << resultLineNo);
	return OZT_Result(OZT_Result::NO_PROBLEM);
      }
      else
	//go to the next line
	tempLineNo++;
    }
  }

  TRACE_RETURN(trace, findMatchingCaseStatement, "HIT_EOF");
  return OZT_Result(OZT_Result::HIT_EOF);
}

//***********************************************************************

OZT_Result OZT_SourceInfo::endifFound(){
  TRACE_IN(trace, endifFound, "");
  OZT_Result result;

  //remove else if it exist
  OZT_FlowStackFrame* flow  = findFlow( OZT_IF );

  if( flow == NULL ){
    TRACE_RETURN(trace, endifFound, "ENDIF_WITHOUT_IF");
    return OZT_Result(OZT_Result::ENDIF_WITHOUT_IF);
  }

  //if statement terminates; remove the flow stack object
  TRACE_FLOW(trace, endifFound, "End of if statement");
  delete (OZT_IfStackFrame *)flowStack.remove( flow );
  result = advance();
  TRACE_RETURN(trace, endifFound, result);
  return result;
}

//***********************************************************************
OZT_Result OZT_SourceInfo::findElseStatement( LineNo startLineNo,
					      LineNo& resultLineNo ) {
  TRACE_IN(trace, findElseStatement, startLineNo );

  static RWTRegex<char> elseScanner("^[\t ]*@[\t ]*[eE][lL][sS][eE][\t ]*$");
  static RWTRegex<char> endifScanner("^[\t ]*@[\t ]*[eE][nN][dD][iI][fF][\t ]*");
  static RWTRegex<char> thenScanner("[tT][hH][eE][nN]$");
  
  LineNo lineWithEndif;
  LineNo tempLineNo = startLineNo;
  LineNo lastLine = text.entries() - 1;
  resultLineNo = -1;
  size_t i;
  RWCString tempLine;
  
  while (tempLineNo <= lastLine){
    tempLine = stripAllComment(text[tempLineNo]);

    //OK, nested @IF found, find where it ends 
    if( thenScanner.index(tempLine) != RW_NPOS ){
      OZT_Result result = findEndifStatement( tempLineNo + 1, lineWithEndif );

      //if endif doesn't exist, return an error
      if (result.code != OZT_Result::NO_PROBLEM){
	TRACE_RETURN(trace, findElseStatement, "NO_MATCHING_ENDIF");
	return OZT_Result(OZT_Result::NO_MATCHING_ENDIF);
      }
      else {
	//increase @IF-statement counter and contuinue searching after the @endif statement
	tempLineNo = lineWithEndif + 1;
      }
    }
    //if the @ELSE statement is found
    else if (elseScanner.index(tempLine) != RW_NPOS){
      	resultLineNo = tempLineNo;
	TRACE_RETURN(trace, findElseStatement, "NO_PROBLEM:" << "resultLineNo:" << resultLineNo);
	return OZT_Result(OZT_Result::NO_PROBLEM);
    }
    //@ENDIF found, on @ELSE statement
    else if( endifScanner.index(tempLine) != RW_NPOS){
      TRACE_RETURN(trace, findElseStatement, "NO_PROBLEM:" << "resultLineNo:" << resultLineNo);
      return OZT_Result(OZT_Result::NO_PROBLEM);
    }
    //.. or go to the next statement
    else
      tempLineNo++;

  } //while

  TRACE_RETURN(trace, findElseStatement, "HIT_EOF");
  return OZT_Result(OZT_Result::HIT_EOF);
}

//***********************************************************************
OZT_Result OZT_SourceInfo::findEndifStatement( LineNo startLineNo,
					       LineNo& resultLineNo ) {
  
  static RWTRegex<char> endifScanner("^[\t ]*@[\t ]*[eE][nN][dD][iI][fF][\t ]*");
  static RWTRegex<char> thenScanner("[tT][hH][eE][nN]$");

  TRACE_IN(trace, findEndifStatement, startLineNo );

  LineNo tempLineNo = startLineNo;
  LineNo lastLine = text.entries() - 1;
  resultLineNo = -1;
  RWCString tempLine;
  size_t i;
  int nrIf = 1;

  while (tempLineNo <= lastLine){
    tempLine = stripAllComment(text[tempLineNo]);

    if( thenScanner.index(tempLine) != RW_NPOS ){
      nrIf++;
    }

    if(endifScanner.index(tempLine) == RW_NPOS){
      tempLineNo++;
    }
    else{
      if( nrIf == 1 ){
	resultLineNo = tempLineNo;
	TRACE_RETURN(trace, findEndifStatement, "NO_PROBLEM:" << "resultLineNo:" << resultLineNo);
	return OZT_Result(OZT_Result::NO_PROBLEM);
      }
      else{
	tempLineNo++;
	nrIf--;
      }
    }
  }
  
  TRACE_RETURN(trace, findEndifStatement, "HIT_EOF");
  return OZT_Result(OZT_Result::HIT_EOF);

}

//***********************************************************************
OZT_Result OZT_SourceInfo::findEndswitchStatement( LineNo startLineNo,
						   LineNo& resultLineNo ) {
  
  static RWTRegex<char> endswitchScanner("^[\t ]*@[\t ]*[eE][nN][dD][sS][wW][iI][tT][cC][hH][\t ]*");

  TRACE_IN(trace, findEndswitchStatement, startLineNo );

  LineNo tempLineNo = startLineNo;
  LineNo lastLine = text.entries() - 1;
  resultLineNo = -1;
  RWCString tempLine;
  size_t i;
  int nrIf = 1;

  while (tempLineNo <= lastLine){
    tempLine = stripAllComment(text[tempLineNo]);


    if(endswitchScanner.index(tempLine) == RW_NPOS){
      tempLineNo++;
    }
    else{
      resultLineNo = tempLineNo;
      TRACE_RETURN(trace, findEndswitchStatement, "NO_PROBLEM:" << "resultLineNo:" << resultLineNo);
      return OZT_Result(OZT_Result::NO_PROBLEM);
    }
  }
  
  TRACE_RETURN(trace, findEndswitchStatement, "HIT_EOF");
  return OZT_Result(OZT_Result::HIT_EOF);

}
//*****************************************************************************

OZT_FlowStackFrame* OZT_SourceInfo::findFlow( FlowFrameType type ){
  TRACE_IN(trace, findFlow, type );

  if( flowStack.isEmpty() ){
    TRACE_RETURN(trace, findFlow, "FlowStack empty");
    return NULL;
  }

  TRACE_FLOW(trace, findFlow, "FlowStack length:" << flowStack.length());

  // HE11023
  // for( size_t i = flowStack.length() - 1; i >= 0; i-- ){

  // size_t can not be used as type for the iteration variable
  // here because it is an unsigned type. At the last iteration 
  // when i is 0 and then is decreased by one it turns into a 
  // very large value instead of -1. Thus the i >= 0 condition 
  // is still false and we go into an infinite loop.

  for( int i = flowStack.length() - 1; i >= 0; i-- ){
    TRACE_FLOW(trace, findFlow, "for loop i=" << i);
  // END HE11023
    if( flowStack[i]->type() == type ){
      
      TRACE_RETURN(trace, findFlow, "FlowStack found:" << type);
      return flowStack[i];
    }
    TRACE_FLOW(trace, findFlow, "FlowStack:" << flowStack[i]->type());
  }
  
  TRACE_RETURN(trace, findFlow, "Flow not found");
  return NULL;

}

//***********************************************************************
//
//  Post-cond: NO_PROBLEM  (currLine set to the first non-commentry line
//                          of a command which does not start with @ELSE)
//             or
//
//             HIT_EOF     (currLine unchanged)
//
OZT_Result OZT_SourceInfo::skipElse()
{
    TRACE_IN(trace, skipElse, "");

    static     RWTRegex<char> elseScanner("^[\t ]*@[\t ]*[eE][lL][sS][eE][\t ]+");
    RWCString  textBlk;
    LineNo     tempLineNo = currLine;
    OZT_Result result;

    //
    //  keep skipping commands until hitting one without @ELSE
    //
    while (result = advance(),
           result.code == OZT_Result::NO_PROBLEM)
    {
        getCurrCmdText(textBlk);
        if (elseScanner.index(textBlk) == RW_NPOS)
        {
            // A command which is not an @ELSE is found.
            TRACE_RETURN(trace, skipElse, "NO_PROBLEM");
            return OZT_Result(OZT_Result::NO_PROBLEM);
        }
    }
    currLine = tempLineNo;
    TRACE_RETURN(trace, skipElse, result);
    return result;
}

//*****************************************************************************

RWBoolean OZT_SourceInfo::forLoopIndexUsed(const RWCString &varName) const
{
    for (size_t i = 0; i < flowStack.length(); i++)
    {
         if ((flowStack[i]->type() == OZT_FOR_LOOP) &&
             (((OZT_ForLoopStackFrame *)(flowStack[i]))->varName == varName))
             return TRUE;
    }
    return FALSE;
}


//*************************************************************************
//
//  Pre-cond : currLine = first non-commentry line of the @FOR command
// 
//  Post-cond : INVALID_VALUE (currLine unchanged)
//
//              or
//
//              NO_MATCHING_NEXT (currLine unchanged)
//
//              or
//
//              MEM_ALLOC_ERR (currLine unchanged)
//
//              or
//
//              NO_PROBLEM (currLine set to the first non-commentry line
//                          of the command the ought to be executed,
//                          a flowFrame is pushed)
//
//              or
//
//              HIT_EOF (currLine set to line of the corresponding @NEXT)
//

OZT_Result OZT_SourceInfo::forLoopSetUp(RWCString varName,
                                        const OZT_Value &firstValue,
                                        const OZT_Value &lastValue)
{
    TRACE_IN(trace, forLoopSetUp, varName << ", " << firstValue 
	     << ", " << lastValue);

    OZT_ForLoopStackFrame *sf;
    LineNo      tempLineNo = currLine;
    LineNo      lineWithNext;
    OZT_Result  result;
    long        v;

    //
    //   check if firstValue and lastValue are numeric
    //
    v = firstValue.toLong(result);
    if (result.code != OZT_Result::NO_PROBLEM)
    {
        TRACE_RETURN(trace, forLoopSetUp, result);
        return result;
    }
    v = lastValue.toLong(result);
    if (result.code != OZT_Result::NO_PROBLEM)
    {
        TRACE_RETURN(trace, forLoopSetUp, result);
        return result;
    }

    //
    //
    //   check if there is a matching @NEXT first
    //
    varName.toUpper();
    result = findEndOfForLoop(currLine, varName, lineWithNext);
    if (result.code != OZT_Result::NO_PROBLEM)
    {
        currLine = tempLineNo;
        TRACE_RETURN(trace, forLoopSetUp, "NO_MATCHING_NEXT");
        return OZT_Result(OZT_Result::NO_MATCHING_NEXT);
    }

    //
    //   check if the loop executes at all
    //
    if (firstValue > lastValue)
    {
        //
        //   The loop does not execute, jump to the line that past the @NEXT
        //
        currLine = lineWithNext;
        result   = advance(); 
        TRACE_RETURN(trace, forLoopSetUp, result);
        return result;
    } 

    //
    //   find the first executable line in the loop body
    //
    (void)advance();  // This cannot fail as findEndOfForLoop returns NO_PROBLEM

    //
    //   make a new flow frame
    //
    sf = new OZT_ForLoopStackFrame(varName, currLine, lineWithNext, lastValue);
    if (sf == 0)
    {
        currLine = tempLineNo;
        TRACE_RETURN(trace, forLoopSetUp, "MEM_ALLOC_ERR");
        return OZT_Result(OZT_Result::MEM_ALLOC_ERR
                    , "OZT_SourceInfo::forLoopSetUp()");
    }
    flowStack.append(sf);   // what if this fails

    //
    //   initialise the loop counter variable to firstValue
    //
    varStore.put(varName, firstValue);
    TRACE_RETURN(trace, forLoopSetUp, "NO_PROBLEM");
    return OZT_Result(OZT_Result::NO_PROBLEM);
}



//*************************************************************************
//
//  Post-cond: NEXT_WITHOUT_MATCHING_FOR (stack top may be removed)
//
//             or
//
//             VAR_UNDEFINED (stack top removed)
// 
//             or
//
//             INVALID_VALUE (stack top removed)
//
//             or
//
//             HIT_EOF (stack top removed, currLine unchanged)
//
//             or
//
//             NO_PROBLEM (stack top may be removed, currLine set to 
//                         the first non-commentry line of the command to
//                         be executed)
//
//             or
//
//             PROGRAM_MODIFIED (stack top removed, currLine unchanged)
//
OZT_Result OZT_SourceInfo::forLoopNext(RWCString varName)
{
    TRACE_IN(trace, forLoopNext, varName);

    OZT_Value  content;
    OZT_Result result;

    varName.toUpper();
    //
    //   check if this is a correct @NEXT var
    //
    if (flowStack.isEmpty() || (flowStack.last()->type() != OZT_FOR_LOOP))
    {
        TRACE_RETURN(trace, forLoopNext, "NEXT_WITHOUT_MATCHING_FOR");
        return OZT_Result(OZT_Result::NEXT_WITHOUT_MATCHING_FOR);
    }

    if (((OZT_ForLoopStackFrame *)(flowStack.last()))->varName != varName)
    {
        delete (OZT_ForLoopStackFrame *)flowStack.removeLast(); 
        TRACE_RETURN(trace, forLoopNext, "NEXT_WITHOUT_MATCHING_FOR");
        return OZT_Result(OZT_Result::NEXT_WITHOUT_MATCHING_FOR);
    }
    
    //
    //  increase the loop counter by 1
    //
    if (!varStore.get(varName, content))
    {
        //  Happens if the variable is flushed
        delete (OZT_ForLoopStackFrame *)flowStack.removeLast();
        TRACE_RETURN(trace, forLoopNext, "VAR <" << varName << "> UNDEFINED");
        return OZT_Result(OZT_Result::VAR_UNDEFINED, varName);
    }
    content = add(content, OZT_Value(1L), result);
    if (result.code != OZT_Result::NO_PROBLEM)
    {
        delete (OZT_ForLoopStackFrame *)flowStack.removeLast();
        TRACE_RETURN(trace, forLoopNext, result);
        return result;
    }
    varStore.put(varName, content);

    //
    //  check to see if the loop terminates
    //
    if (content > ((OZT_ForLoopStackFrame *)(flowStack.last()))->lastValue)
    {
        //
        //  loop terminated, remove flow frame and move on to the next command
        //
        TRACE_FLOW(trace, forLoopNext, "loop on " << varName << " terminated.");
        delete (OZT_ForLoopStackFrame *)flowStack.removeLast(); 
        result = advance();
        TRACE_RETURN(trace, forLoopNext, result);
        return result;
    }
    else
    {
        //
        //  loop not terminated, jump back to the beginning of the loop
        //
        if (setLine(((OZT_ForLoopStackFrame *)(flowStack.last())) ->startLine))
        {
            TRACE_RETURN(trace, forLoopNext, "NO_PROBLEM");
            return OZT_Result(OZT_Result::NO_PROBLEM);
        }
        else
        { 
            delete (OZT_ForLoopStackFrame *)flowStack.removeLast();
            TRACE_RETURN(trace, forLoopNext, "PROGRAM_MODIFIED");
            return OZT_Result(OZT_Result::PROGRAM_MODIFIED);
        }
    } 
}


//***************************************************************************
//  Pre-cond: startLineNo == An executable line which starts searching for 
//                           @NEXT
//
//  Post-cond: NO_PROBLEM (resultLineNo == the line with @next varName)
//
//             or
//             
//             HIT_EOF    (resultLineNo undefined)

OZT_Result OZT_SourceInfo::findEndOfForLoop(const  LineNo startLineNo, 
                                            RWCString varName,
                                            LineNo &resultLineNo)
{
    static RWTRegex<char> nextScanner("^[\t ]*@[\t ]*[nN][eE][xX][tT][\t ]+");

    LineNo    tempLineNo = startLineNo;
    LineNo    lastLine   = text.entries() - 1;
    RWCString tempLine;
    size_t    i;

    varName.toUpper();
    while (tempLineNo <= lastLine)
    {
        tempLine = stripAllComment(text[tempLineNo]);

        //
        //    Check if the line starts with "@NEXT"
        //
        if (nextScanner.index(tempLine, &i) == RW_NPOS)
        {
            tempLineNo++;
            continue;
        }

        //
        //    Trim the line to the part for the potential variable name
        //
        tempLine = trim(tempLine(i, tempLine.length()-i));
        tempLine.toUpper();
        if (tempLine == varName)
        {
             //
             //  yup, got it.
             //
             resultLineNo = tempLineNo;
             return OZT_Result(OZT_Result::NO_PROBLEM);
        }

        tempLineNo++;
    }
    return OZT_Result(OZT_Result::HIT_EOF);
}

//*****************************************************************************

OZT_Result OZT_SourceInfo::labelExist(RWCString label)
{
    TRACE_IN(trace, labelExist, label);

    LineNo targetLine;
    OZT_Result result;

    label.toUpper();
    if (labelTbl.findValue(label, targetLine))
    {
        if (targetLine < 0)
            result = OZT_Result(OZT_Result::DUPLICATE_LABELS, label);
        else
            result = OZT_Result(OZT_Result::NO_PROBLEM);
    }
    else
        result = OZT_Result(OZT_Result::LABEL_NOT_FOUND, label);

    TRACE_RETURN(trace, labelExist, result);
    return result;
}

//**************************************************************************
//
//  Post-cond: NO_PROBLEM      (currLine set to the first non-commentry line
//                              of the matching label)
//             or
//
//             LABEL_NOT_FOUND (currLine unchanged)
//
//             or
//
//             DUPLICATE_LABELS
//
OZT_Result OZT_SourceInfo::gotoLabel(RWCString label)
{
    TRACE_IN(trace, gotoLabel, label);

    LineNo      targetLine;
    OZT_Result  result;

    label.toUpper();
    if (labelTbl.findValue(label, targetLine) == TRUE)
    {
        if (targetLine < 0)
            result = OZT_Result(OZT_Result::DUPLICATE_LABELS, label);
        else
        {
            currLine = targetLine - 1;
            result = OZT_Result(OZT_Result::NO_PROBLEM);
        }
    }
    else 
        result = OZT_Result(OZT_Result::LABEL_NOT_FOUND, label);

    TRACE_RETURN(trace, gotoLabel, result);
    return result;
}


//************************************************************************
//
//  Post-cond: NO_PROBLEM   (currLine set to the first non-commentry line
//                           of the label, a stackFrame is added) 
//
//             or
//
//             LABEL_NOT_FOUND (currLine unchanged)
//
//             or
//
//             MEM_ALLOC_ERR   (currLine unchanged)
//
OZT_Result OZT_SourceInfo::gosubLabel(RWCString label, 
                                      const RWBoolean skipElseFlag)
{
    TRACE_IN(trace, gosubLabel, label << ", " << skipElseFlag);

    LineNo      targetLine;
    OZT_Result  result;   
    OZT_GosubStackFrame *sf;
 
    label.toUpper();

    //
    //  push the return line no into the flow stack
    //
    sf = new OZT_GosubStackFrame(currLine, skipElseFlag);
    if (sf == 0)
    {
        TRACE_RETURN(trace, gosubLabel, "MEM_ALLOC_ERR");
        return OZT_Result(OZT_Result::MEM_ALLOC_ERR,
                   "OZT_SourceInfo::gosubLabel()");
    }
    flowStack.append(sf);

    //
    //  jump to the label
    //
    if (labelTbl.findValue(label, targetLine))
    {
        if (targetLine < 0)
        {
            // label found, but duplicated
            delete (OZT_GosubStackFrame *)flowStack.removeLast();
            result = OZT_Result(OZT_Result::DUPLICATE_LABELS, label);
        }
        else
        {
            // label found
            currLine = targetLine - 1; 
            result = OZT_Result(OZT_Result::NO_PROBLEM);
        }
    }     
    else 
    {   
        // label not found
        delete (OZT_GosubStackFrame *)flowStack.removeLast();
        result = OZT_Result(OZT_Result::LABEL_NOT_FOUND, label);
    }     
    TRACE_RETURN(trace, gosubLabel, result);
    return result; 
}


//**************************************************************************
//  Post-cond: RETURN_WITHOUT_GOSUB (flowStack unchanged)
//
//             or
//
//             NO_PROBLEM (flowStack top removed,
//                         currLine set to the first non-commentry
//                         line of the command following the corresponding
//                         gosub, elses skipped if needed)
//
//             or
//
//             HIT_EOF (flowStack top removed,
//                      currLine set to the first non-commentry 
//                      line of the command which contains the corresponding
//                      @gosub)
//
//             or
//
//             PROGRAM_MODIFIED (flowStack top removed, currLine unchanged)
//                               
OZT_Result  OZT_SourceInfo::returnFromGosub()
{
    TRACE_IN(trace, returnFromGosub, "");
    OZT_Result  result; 
    OZT_FlowStackFrame* flow = findFlow( OZT_GOSUB );
    if ( flow == NULL )
    {
        TRACE_RETURN(trace, returnFromGosub, "");
        result = OZT_Result(OZT_Result::RETURN_WITHOUT_GOSUB);
    }
    else
    {  
        OZT_GosubStackFrame *sf = (OZT_GosubStackFrame*)(flow);      
        if (!setLine(sf->lineNo))
        {
            TRACE_RETURN(trace, returnFromGosub, "PROGRAM_MODIFIED");
            result = OZT_Result(OZT_Result::PROGRAM_MODIFIED);
        }
        else 
        {
            if (sf->skipElseFlag == TRUE)
               result = skipElse();
            else
               result = advance();
        }
        //Roll back any IF, FOR or SWITCH states. 
        while( flowStack.last()->type()!= OZT_GOSUB ){	 
            delete flowStack.removeLast();
        }
        //Delete the GOSUB state.
        delete flowStack.removeLast(); 
    } 
    TRACE_RETURN(trace, returnFromGosub, result); 
    return result;
}

//***************************************************************************
//
//  Post-cond:stat changed and
//
//            NO_PROBLEM          (text, labelTbl rebuilt, currLine adjusted)
//
//            or
//
//            NO_EXECUTABLE_CODE  (cannot update, UI must reset the execution)
//
//            or
//
//            FILE_OPEN_ERR       (cannot read the file)
//
//            or
//
//            INTERNAL_ERR        (internal limit reached)
//
OZT_Result OZT_SourceInfo::update()
{
    TRACE_IN(trace, update, "");
    //
    //  reload the file in
    //
    load();
    if (stat.code != OZT_Result::NO_PROBLEM)
    {
        TRACE_RETURN(trace, update, stat);
        return stat;
    }

    //
    //  adjust currLine if necessary so that the invariant is maintained
    //
    if (adjustCurrLine() == TRUE)
    {
        TRACE_RETURN(trace, update, stat);
        return stat;
    }
    else
    {
        TRACE_RETURN(trace, update, "NO_EXECUTABLE_CODE in" << filename);
        stat = OZT_Result(OZT_Result::NO_EXECUTABLE_CODE, filename);
        return stat;
    }
}

void OZT_SourceInfo::load( const RWTValOrderedVector<RWCString>& lines ){

  TRACE_IN(trace, load, "load from string array");
  LineNo     lineCount;

  text.clear();
  lineCount = 0;

  for(int i = 0; i < lines.entries(); i++ ){
    RWCString stripped= lines[i].strip( RWCString::trailing, '\n'); 
    stripped =RWCString( stripped ).strip(  RWCString::trailing, '\r');
    if( stripped != "" ) {
      TRACE_FLOW(trace, load, "Loading:" << RWCString( stripped) );
      text.insert(RWCString( stripped ));
      lineCount++;
      if (text.entries() != lineCount){
	text.clear();
	stat = OZT_Result(OZT_Result::INTERNAL_ERR,"OZT_SourceInfo::load()");
	TRACE_OUT(trace, load, stat);
	return;
      }
    }
  } 
  stat = OZT_Result(OZT_Result::NO_PROBLEM);
  TRACE_OUT(trace, load, "Loaded " << lineCount <<" rows" );
}

//***************************************************************************
//
//  Pre-cond: filename defined
//
//  Post-cond: stat == FILE_OPEN_ERR  (This object should not be used anymore) 
//
//             or
//
//             stat == INTERNAL_ERR (This object should not be used anymore)
//
//             or
//
//             stat == NO_PROBLEM  (text loaded, labelTbl rebuilt)
//
//
void  OZT_SourceInfo::load()
{ 
    TRACE_IN(trace, load, "");

    ifstream   infile;
    RWCString  line;
    LineNo     lineCount;
    OZT_Result result;

    infile.open(filename.data());
    if (!infile)  // something wrong in opening the file
    {
        stat = OZT_Result(OZT_Result::FILE_OPEN_ERR, strerror(errno));
        TRACE_OUT(trace, load, stat);
        return;
    }

    text.clear();
    labelTbl.clear();
    // Should I clear the flow stack as well????
    
    //
    //   Read the file contents into a vector
    //
    lineCount = 0;
    while(line.readLine(infile, FALSE))
    {
    	// HE68730
    	line = trim(line);
    	// END HE68730
        stat = findAndInsertLabel(line, lineCount + 1);
        if (stat.code != OZT_Result::NO_PROBLEM)
        {
            text.clear();
            labelTbl.clear();
            infile.close();
            TRACE_OUT(trace, load, stat);
            return;
        }
        text.insert(line);
        lineCount++;
        if (text.entries() != lineCount)  // check if the insert was ok.
        {
            text.clear();
            labelTbl.clear();
            infile.close();
            stat = OZT_Result(OZT_Result::INTERNAL_ERR,"OZT_SourceInfo::load()");
            TRACE_OUT(trace, load, stat);
            return;
        }
    }

// TR: AE79424 - inserted correction start.

    if (line.length() > 0 ) 
      {
        stat = findAndInsertLabel(line, lineCount + 1);
        if (stat.code != OZT_Result::NO_PROBLEM)
	  {
            text.clear();
            labelTbl.clear();
            infile.close();
            TRACE_OUT(trace, load, stat);
            return;
	  }
        text.insert(line);
        lineCount++;
        if (text.entries() != lineCount)  // check if the insert was ok.
	  {
            text.clear();
            labelTbl.clear();
            infile.close();
            stat = OZT_Result(OZT_Result::INTERNAL_ERR,"OZT_SourceInfo::load()");
            TRACE_OUT(trace, load, stat);
            return;
	  }
      }
    
    // end
    
    infile.close();
    
    stat = OZT_Result(OZT_Result::NO_PROBLEM);
    TRACE_OUT(trace, load, "NO_PROBLEM");
    return;
}

//******************************************************************************
//
//  Pre-cond: currLine >= 0
//
//  Post-cond: FALSE (cannot find a proper line for currLine, currLine unchanged)
//
//             or
//
//             TRUE (currLine sets to a closest non-commentry Line)
//
RWBoolean OZT_SourceInfo::adjustCurrLine()
{
    LineNo tempLineNo = currLine;

    if (text.entries() == 0)
        return FALSE;
 
    skipCommentryLines();
    if (currLine >= text.entries()) {
        currLine = text.entries() - 1;
    }

    for(;;)
    {
        if (!isEmptyLine(stripAllComment(text[currLine])))
            return TRUE;
        if (currLine == 0)
        {
            currLine = tempLineNo;
            return FALSE;
        }
        else
            currLine--;
    }
}


//**************************************************************************
//
//  Pre-cond: currLine >= 0
//
//  Post-cond: currLine advanced to a non-commentry line. (or text.entries())
//             (it may remain unchanged.)
//
void OZT_SourceInfo::skipCommentryLines()
{
  TRACE_IN(trace, skipCommentryLines, "");

  RWCString tempText;

  TRACE_FLOW(trace, skipCommentryLines, "currLine=" << currLine << " text.entries()=" << text.entries());
  
  while (currLine < text.entries())
    {
      tempText = stripAllComment(text[currLine]);
      if (!isEmptyLine(tempText.data()))
	break;
      currLine++;
    }
  TRACE_OUT(trace, skipCommentryLines, "currLine=" << currLine);
}


//**************************************************************************
//  Pre-cond: currLine must be on the first non-commentry line
//            of the command to be skipped.
//
//  Post-cond: NO_PROBLEM returned (currLine set to the first non-commentry 
//                                  line of the next command)
//                 or
//
//             HIT_EOF returned (currLine unchanged).
//
OZT_Result OZT_SourceInfo::advance()
{
    TRACE_IN(trace, advance, "");
    LineNo tempLineNo = currLine;

    currLine += currCmdLength();
    skipCommentryLines();
    if (currLine >= text.entries())
    {
        currLine = -1;
        TRACE_RETURN(trace, advance, "HIT_EOF");
        return OZT_Result(OZT_Result::HIT_EOF);
    }
    else
    {
        TRACE_RETURN(trace, advance, "NO_PROBLEM");
        return OZT_Result(OZT_Result::NO_PROBLEM);
    }
}


//***************************************************************************
//  Pre-cond: currLine must be on the first non-commentry line
//            of the command to be measured.
//
//  Post-cond: returns the number of lines occupied by the command
//
LineNo OZT_SourceInfo::currCmdLength()
{
    LineNo    len;
    RWCString dummy;

    getCurrCmdText(dummy, len);
    return len; 
}


//**************************************************************************
//
// Post-cond: HIT_EOF (textBlk == empty string)
//
//               or
//
//            NO_PROBLEM (textBlk == the block of commands to be retrieved,
//                        currLine advanced to the first non-commentry line
//                        of the command retrieved)
//
//
OZT_Result OZT_SourceInfo::getCurrCmdText(RWCString &textBlk, char skip_comments)
{
    TRACE_IN(trace, getCurrCmdText, "");

    LineNo dummy;
    LineNo tempLineNo = currLine;
 
    if(skip_comments)
      skipCommentryLines();
    TRACE_FLOW(trace, getCurrCmdText, "currLine=" << currLine << " text.entries()=" << text.entries());
    if (currLine >= text.entries())
    {
        currLine = -1;
        TRACE_RETURN(trace, getCurrCmdText, "HIT_EOF");
        return OZT_Result(OZT_Result::HIT_EOF);
    }
    else
    {
        getCurrCmdText(textBlk, dummy);
        TRACE_RETURN(trace, getCurrCmdText, "NO_PROBLEM");
        return OZT_Result(OZT_Result::NO_PROBLEM);
    }
}

//**************************************************************************
//  Pre-cond:  currLine must be set on the first non-commentry line
//             of the command to be retrieved
//
//  Post-cond: textBlk   == the text for the command 
//             cmdLength == no. of lines occupies by the command retrieved
//                          (including empty lines in between, but not those
//                           following)
//
void OZT_SourceInfo::getCurrCmdText(RWCString &textBlk, LineNo &cmdLength)
{
    TRACE_IN(trace, getCurrCmdText, "");

    static RWTRegex<char>  scriptCmdChecker("^[ \t]*[@/!]");
    RWCString tempText;

    if (currLine < 0) {
        // We have already executed the last statement of the script.
        textBlk   = "";
        cmdLength = 0;
        TRACE_OUT(trace, getCurrCmdText, "[" << textBlk << "] (cmdLength = " 
                  << cmdLength << ")");
        return;
    }

    //
    //  composes the command text block
    //
    tempText = stripAllComment(text[currLine]);
    if (scriptCmdChecker.index(tempText) != RW_NPOS)
        composeScriptCmd(textBlk, cmdLength);
    else
        composeHostCmd(textBlk, cmdLength);

    TRACE_OUT(trace, getCurrCmdText, "[" << textBlk << "] (cmdLength = " 
	      << cmdLength << ")");
}


//*****************************************************************************

RWBoolean OZT_SourceInfo::isCommentryLine(RWCString line)
{
    line = trim(line);

    if (line.isNull())
        return TRUE;

    if ((line.length() >= 2) && (line[(unsigned)0] == '@') && (line[(unsigned)1] == '@'))
        return TRUE;

    if (line[(unsigned)0] == '!')
    {
        if ((line.length() >= 6) && (line(0, 6) == "!$$$$!"))
            return FALSE;
        return TRUE;
    } 
    return FALSE;
}
 
//****************************************************************************
//  Pre-cond: currLine must be set on the first non-commentry line
//            of the command to be retrieved.
//
//  Post-cond: returns the joint lines of the command (comment stripped)
//             cmdLength == lines occupied by the command
//
void OZT_SourceInfo::composeScriptCmd(RWCString &textBlk, LineNo &cmdLength)
{
    TRACE_IN(trace, composeScriptCmd, "");

    LineNo tempLineNo = currLine; 
    RWCString tempText;
    
    tempText = stripAllComment(text[tempLineNo]);
    textBlk  = tempText;

    while (toContinue(tempText) && (tempLineNo < text.entries()))
    {
        // joins the next non-terminating lines, empty lines are skipped
        while (tempLineNo++, tempLineNo < text.entries())
        {
	  tempText = stripAllComment(text[tempLineNo]);
            if (!isEmptyLine(tempText))
            {
                textBlk  = textBlk + tempText;
                break;
            }
        } 
    }
    if (tempLineNo >= text.entries())
        cmdLength = tempLineNo - currLine;
    else
        cmdLength = tempLineNo - currLine + 1;

    TRACE_OUT(trace, composeScriptCmd, textBlk << "length = (" 
	     << cmdLength << ")");
}

//*****************************************************************************

RWBoolean OZT_SourceInfo::toContinue(const RWCString &textBlk)
{
  TRACE_IN(trace, toContinue, textBlk);

  static RWTRegex<char>  continueChecker(",[ \t]*$");
  
  size_t pos = continueChecker.index(textBlk);
  char   delimiter;
  
  if (pos == RW_NPOS){
    TRACE_RETURN(trace, toContinue, "FALSE1");
    return FALSE;
  }
  
  for (pos = 0; pos < textBlk.length(); pos++)
    {
      if ((textBlk[pos] == '\"') || (textBlk[pos] == '\''))
        {
	  // find the end of the quoted string
	  
	  delimiter = textBlk[pos++];
	  while ((pos < textBlk.length()) && (textBlk[pos] != delimiter))
	    pos++;
	  
	  if (pos == textBlk.length()){
	    TRACE_RETURN(trace, toContinue, "FALSE2");
	    return FALSE;
	  }
        }
      if ((pos + 1 < textBlk.length()) &&
	  (textBlk[pos] == '/') &&
	  (textBlk[pos + 1] == '*'))
        {
	  pos += 2;
	  while (pos < textBlk.length())
            {
	      if (pos + 1 >= textBlk.length())
		return FALSE;
	      
	      if ((textBlk[pos] == '*') && (textBlk[pos+1] == '/'))
                {
		  pos++;
		  break;
                }
	      pos++;
            }
        }
    }
  TRACE_RETURN(trace, toContinue, "TRUE");
  return TRUE;
}

//***************************************************************************
//  precondition: currLine must be the first non-commentry line of the
//                command to be composed.
//  Note: currLine is not modified
//
void OZT_SourceInfo::composeHostCmd(RWCString &textBlk, LineNo &cmdLength)
{
    TRACE_IN(trace, composeHostCmd, "");

    static RWTRegex<char>  continueChecker("[&-,][ \t]*$");
    LineNo tempLineNo = currLine;
    RWCString tempText;
    
    tempText = trim(stripCommentOnMML(text[tempLineNo]));
    textBlk  = tempText;
    while ((continueChecker.index(tempText) != RW_NPOS) &&
           (tempLineNo < text.entries()) && (tempText[tempText.length()-1] != '*' ))
    {
        // joins all the non-terminating lines, empty lines are skipped
        while (tempLineNo++, tempLineNo < text.entries())
        {   
            tempText = trim(stripCommentOnMML(text[tempLineNo]));
            if (!isEmptyLine(tempText))
            {
                textBlk  = textBlk + tempText;
                break;
            }
        }   
    }    
    if (tempLineNo >= text.entries())
        cmdLength = tempLineNo - currLine;
    else
        cmdLength = tempLineNo - currLine + 1;

    TRACE_OUT(trace, composeHostCmd, textBlk << "length = (" 
                                                 << cmdLength << ")");
}

//*****************************************************************************

RWCString OZT_SourceInfo::stripCommentOnMML(const RWCString &line)
{
    static RWTRegex<char> checker("^[\t ]*!");
    static RWTRegex<char> checker2("^[\t ]*!$$$$!");

    RWCString resultString = RWCString();
    char delimiter;
    register size_t index = 0;
    register size_t lineIndex = 0;
    register size_t lineLength = line.length();

    //
    //  If the line starts with a (!) but not a !$$$$!, return empty line.
    //
    if ((checker.index(line) != RW_NPOS) && (checker2.index(line) == RW_NPOS))
    {
        return RWCString();
    }
    
    for(lineIndex = 0; lineIndex < lineLength; lineIndex++) 
    {
        switch (line[lineIndex]) 
        {
            case '\"' : // start of a string, skip to the other quote
            case '\'' : delimiter = line[lineIndex];
                        resultString.append(delimiter);
                        lineIndex++;
                        while (lineIndex < lineLength)
                        {
                            resultString.append(line[lineIndex]);
                            if (line[lineIndex] == delimiter)
                                break;
                            else
                                lineIndex++;
                        }            
                        break;

            case '@' : if ((lineIndex + 1 < line.length()) &&
                           (line[lineIndex + 1] == '@'))
                       {
                           // The rest of the line is skipped
                           TRACE_RETURN(trace, stripCommentOnMML, resultString);
                           return resultString;
                       } 
                       resultString.append("@");
                       break;

            default :  resultString.append(line[lineIndex]);
                       break;
        }
    }
    return resultString;
}


//*****************************************************************************
//
// This function strip off all the Ozterm style comments.
//
RWCString OZT_SourceInfo::stripAllComment(const RWCString &sourceLine)
{
    RWCString destLine(' ', sourceLine.length()); 
    register size_t index = 0;
    register size_t sourceIdx = 0;
    register size_t destIdx = 0;
    register size_t sourceLength = sourceLine.length();
    char delimiter;

    while (sourceIdx < sourceLength)
    {
        switch (sourceLine[sourceIdx]) 
        {
            case '\"' : // start of a string, skip to the other quote
            case '\'' : delimiter = sourceLine[sourceIdx++];
                        destLine[destIdx++] = delimiter;
                        while (sourceIdx < sourceLength)
                        {
                            destLine[destIdx++] = sourceLine[sourceIdx++];
                            if (sourceLine[sourceIdx - 1] == delimiter)
                                break;
                        }
                        break;

            case '/'  : destLine[destIdx++] = '/';
                        sourceIdx++;
                        if ((sourceIdx < sourceLength) && 
                            (sourceLine[sourceIdx] == '*'))
                        {
                            // start of a c-style comment, skip to the end
                            destLine[destIdx++] = sourceLine[sourceIdx++];
                            while (sourceIdx < sourceLength)
                            {
                                if ((sourceIdx + 1 < sourceLength) &&
                                    (sourceLine[sourceIdx] == '*') &&
                                    (sourceLine[sourceIdx+1] == '/'))
                                {
                                    destLine[destIdx++]=sourceLine[sourceIdx++];
                                    destLine[destIdx++]=sourceLine[sourceIdx++];
                                    break;
                                }
                                else
                                    destLine[destIdx++]=sourceLine[sourceIdx++];
                            }
                        } 
                        break;

            case '!'  : index = sourceLine.index("!$$$$!", sourceIdx);
                        if ((index == RW_NPOS) || (index != sourceIdx)) 
                            return destLine(0, destIdx);  // skip the rest
                        destLine.replace(destIdx, 6, "!$$$$!");
                        destIdx += 6;
                        sourceIdx += 6;
                        break;

            case '@' : sourceIdx++;
                       if ((sourceIdx < sourceLength) &&
                           (sourceLine[sourceIdx] == '@'))
                           return destLine(0, destIdx);  // skip the rest
                       else
                           destLine[destIdx++] = '@';
                       break;

            default :  destLine[destIdx++] = sourceLine[sourceIdx++];
                       break;
        }
    }
    return destLine(0, destIdx);
}

//*****************************************************************************

RWCString OZT_SourceInfo::getFileName()
{
    return filename;
}

//*****************************************************************************

LineNo  OZT_SourceInfo::getLineNo()
{
    return currLine;
}

//***********************************************************************
//
//
OZT_Result OZT_SourceInfo::findAndInsertLabel(RWCString line, LineNo lineno)
{

    static RWTRegex<char> label_reg_exp("^[\t ]*@[\t ]*LABEL[\t ]+[^\t ]");
    static RWTRegex<char> trim_reg_exp("^[^\t ]*");
 
    size_t     i;
    size_t     labelLength;
    int    value;

    line.toUpper();
    line = trim(stripAllComment(line));

    //
    //    if the line doesn't look like containing a label, simply return
    //
    if (label_reg_exp.index(line, &i) == RW_NPOS)
        return OZT_Result(OZT_Result::NO_PROBLEM);

    //
    //    Trim the line to the part for the potential label
    //
    trim_reg_exp.index(line, &labelLength, i - 1);
    line = line(i - 1, labelLength);

    //
    //    if the same label is already found in the file, insert -line no to signify
    //    the problem, otherwise insert the line no. 
    //
    if (labelTbl.findValue(line,value))
    {   
        if (value > 0)
        labelTbl.insertKeyAndValue(line, -value);
        // When a label is defined more than one time  
        // keeps the line number of the first definition
    }    
    else
        labelTbl.insertKeyAndValue(line, lineno);

    return OZT_Result(OZT_Result::NO_PROBLEM);
}

//*****************************************************************************

RWBoolean OZT_SourceInfo::isManualCommandEntry() {
    return isManualCommands;
}

//*****************************************************************************

RWBoolean   operator==(const OZT_SourceInfo& a, const OZT_SourceInfo& b)
{
    return a.filename == b.filename;
}

//*****************************************************************************

//unsigned OZT_SourceInfo::hashString(const RWCString& str) {return str.hash();}

//*****************************************************************************
