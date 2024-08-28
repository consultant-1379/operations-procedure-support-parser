// RCS revision handling
// $Id: OZT_SourceInfo.H,v 21.0 1996/08/23 12:43:07 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_SourceInfo - Class about a source file at execution time
// .LIBRARY CHOZTBIN
// .PAGENAME OZT_SourceInfo
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
// 	During execution, the interpreter contains a source info object
//      per command file. This class stores some data structure about
//      the file, such as label tables, source text tables etc.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	190 89-CAA 134 2016

// AUTHOR 
// 	1994-10-05 by Nelson Cheng (epanyc@epa.ericsson.se)

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_SourceInfo.H,v $
// 	Revision 21.0  1996/08/23 12:43:07  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 07:57:42  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.1  1996/05/14 17:33:04  ememjga
// 	Added method lineLabel, AD16693
//
//      Revision 19.0  96/03/19  07:22:27  07:22:27  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB61, J Sandquist (ehsjasa).
//      
// 	Revision 18.0  1996/03/01 12:21:45  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:02:14  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:57:26  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:02:57  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:17:21  17:17:21  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.1  1995/10/23 15:46:13  ehsjasa
// 	Removed uneceserry inclusion of "rw/regexp.h".
//
// 	Revision 13.0  1995/10/07 12:01:35  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:09:35  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:25:16  09:25:16  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:02:31  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.1  95/06/30  15:41:32  15:41:32  epanyc (Nelson Cheng VK/EHS/PXE)
//      isCommentryLine() changed
//      
//      Revision 9.0  1995/06/29  14:38:10  cmcha
//      Made release EC2_OZ, J Grape (EHSGRAP).
//
//      Revision 8.0  95/06/07  17:09:24  17:09:24  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//
//      Revision 7.0  95/04/16  12:16:34  12:16:34  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.2  95/04/04  12:44:33  12:44:33  epanyc (Nelson Cheng VK/EHS/PXE)
//      no changed
//
//      Revision 6.1  1995/03/24  16:44:02  epanyc
//      labelExist() added
//
//      Revision 6.0  1995/03/17  20:05:39  cmcha
//      Made release TB51_OZ, ehscama.
//
//      Revision 5.0  95/03/16  20:31:23  20:31:23  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 4.1  95/03/06  15:25:56  15:25:56  epanyc (Nelson Cheng VK/EHS/PXE)
//      forLoopIndexUsed() added
//
//      Revision 4.0  1995/02/23  21:46:09  cmcha
//      Made release TB4, J Grape (EHSGRAP).
//
//      Revision 3.1  95/02/20  14:30:53  14:30:53  epanyc (Nelson Cheng VK/EHS/PXE)
//      incomplete string on a line is detected
//
//      Revision 3.0  1995/02/06  20:57:57  cmcha
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 2.6  95/01/31  10:31:30  10:31:30  epanyc (Nelson Cheng VK/EHS/PXE)
//      no change
//
//      Revision 2.5  1995/01/26  17:08:55  epanyc
//      isCommentryLine added
//
//      Revision 2.4  1995/01/23  12:42:14  epanyc
//      strip comment changed
//
//      Revision 2.3  1994/12/21  16:14:11  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 2.0  94/12/21  13:52:15  13:52:15  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 1.8  1994/11/16  10:27:40  epanyc
//
//      Revision 1.7  94/11/02  12:38:24  12:38:24  epanyc (Nelson Cheng VK/EHS/PXE)
//      *** empty log message ***
//
//      Revision 1.6  94/10/31  12:01:12  12:01:12  epanyc (Nelson Cheng VK/EHS/PXE)
//      some function prototypes changed
//
//      Revision 1.5  1994/10/31  10:35:53  epanyc
//      check in again for Neil to compile
//
//      Revision 1.4  1994/10/28  13:03:19  epanyc
//      check in for Neil to compile
//
//      Revision 1.3  1994/10/17  10:15:28  epanyc
//      trace macros added
//
//      Revision 1.2  1994/10/12  16:35:56  epanyc
//      SUCCESS becomes NO_PROBLEM
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

#ifndef OZT_SOURCE_INFO_H
#define OZT_SOURCE_INFO_H

#include <OZT_Def.H>
#include <OZT_ErrHandling.H>
#include <OZT_Value.H>
#include <OZT_VarStore.H>

#include <rw/tpordvec.h>
#include <rw/tvordvec.h>
#include <rw/tvhdict.h>
#include <rw/cstring.h>
#include <iostream>


enum FlowFrameType {OZT_GOSUB, OZT_FOR_LOOP, OZT_IF, OZT_SWITCH};

//***************************************************************************

class OZT_FlowStackFrame {
public:
    virtual ~OZT_FlowStackFrame(){};
    virtual FlowFrameType type() const =0; 
    virtual RWBoolean operator==(const OZT_FlowStackFrame &sf)const = 0;
};


//***************************************************************************
class OZT_IfStackFrame: public OZT_FlowStackFrame {
public:
  OZT_IfStackFrame(const LineNo ifLineNo, const LineNo elseLineNo, const LineNo endifLineNo);
  ~OZT_IfStackFrame();
  FlowFrameType type() const;
  RWBoolean operator==(const OZT_FlowStackFrame &sf)const;
  
  LineNo getLineWithEndif(){
    return endifLineNo_;
  }
private:
  LineNo ifLineNo_;
  LineNo elseLineNo_;
  LineNo endifLineNo_;
};

//***************************************************************************

class OZT_GosubStackFrame: public OZT_FlowStackFrame {
public:
    OZT_GosubStackFrame(const LineNo lineNo, const RWBoolean skipElseFlag);
    ~OZT_GosubStackFrame();
    FlowFrameType type() const;
    RWBoolean operator==(const OZT_FlowStackFrame &sf)const;
    LineNo  lineNo;
    RWBoolean skipElseFlag;
};

//***************************************************************************

class OZT_SwitchStackFrame: public OZT_FlowStackFrame {
public:
  OZT_SwitchStackFrame(const LineNo endswitchLineNo);
  ~OZT_SwitchStackFrame();
  FlowFrameType type() const;
  RWBoolean operator==(const OZT_FlowStackFrame &sf)const;

  LineNo getLineWithEndswitch(){
    return endswitchLineNo_;
  }

private:
  LineNo  endswitchLineNo_;
};

//***************************************************************************

class OZT_ForLoopStackFrame: public OZT_FlowStackFrame {
public:
    OZT_ForLoopStackFrame(const RWCString &varName, 
                          const LineNo     startLine,
			  const LineNo lineWithNext,
                          const OZT_Value &lastValue);
    ~OZT_ForLoopStackFrame();
    FlowFrameType type() const;
    RWBoolean operator==(const OZT_FlowStackFrame &sf)const;
    RWCString  varName;
    LineNo     startLine;
    LineNo     lineWithNext;
    OZT_Value  lastValue;
};

//***************************************************************************
// Important: This class needs to maintain an invariant condition in order
//            to function properly. The current position (hold in currLine)
//            must always be on a non-commentry line.
//***************************************************************************

class OZT_SourceInfo {
public:
  OZT_SourceInfo(OZT_VarStore& theVarStore, 
		 const RWTValOrderedVector<RWCString>& lines);

  OZT_SourceInfo(const RWCString& filename, OZT_VarStore &theVarStore);
    // Description
    //     Constructor.
    // Parameters
    //     filename    IN: the name of the command file
    //     theVarStore IN: reference to the variable store (used for var subst)


    ~OZT_SourceInfo();
    // Description
    //     Destructor.
    void emptyFlowStack();
    // Description
    // Empty the flow stack.
  
    void reset();
    // Description
    OZT_Result lineLabel(RWCString label ,LineNo& line);
    // Description 
    //      Returns the status of one label. If the label
    //      exists , the line number is stored in the 
    //      variable line  
    // Parameters
    //      label   IN: label
    //      line   OUT: line, it is the line number where the
    //                  label is declared the first time.
    //                  It is only set when the label is
    //                  declared.
    
    OZT_Result  constructStatus();
    // Description
    //     Returns the status of construction.
    // Return value
    //     A result object


    RWCString   getFileName();
    // Description
    //     Get hold of the file name of this source info object.
    //


    LineNo      getLineNo();
    // Description
    //     Get hold of the current line number.
    // Return value
    //     The current line number.


    LineNo      currCmdLength();
    // Description
    //     Get hold of the current command length. This includes the
    //     commentry lines in between if the command spans line boundaries.
    // Return value
    //     The current command length.


    OZT_Result  update();
    // Description
    //     Forces this object to read the command file again and updates
    //     the label table etc.
    // Return value
    //     A result object about the update.


    RWBoolean   setLine(const LineNo lineNo, RWBoolean skip_comments = TRUE);
    // Description
    //     Set the current position to the specified line. If that line is
    //     a commentry line, the actual position set will be advanced to 
    //     the first non-commentry line follows. However, if there is
    //     no non-commentry line follows, this method will not change
    //     the current position.
    // Parameters
    //     skip_comments IN: if TRUE, then step to next non-comment line.  
    // Return value
    //     TRUE if the current position is changed, otherwise it returns FALSE.


    OZT_Result  advance();
    // Description
    //     Advance the current position to the next command.
    // Return value
    //     OZT_Result(NO_PROBLEM)   if the position is advanced.
    //     OZT_Result(HIT_EOF)      if there is no next command, in this
    //                              case, the current position is not changed.


    OZT_Result  getCurrCmdText(RWCString &buf, char skip_comments = 1);
    // Description
    //     Retrieve a comment-stripped text block for the current command.
    //     If the the command spans multiple line, the string will be
    //     the concatenated string from the multiple lines.
    // Parameter
    //     buf OUT: the command text
    //     skip_comments IN: if TRUE, then step to next non-comment line.
    // Return value
    //     OZT_Result(HIT_EOF)    if there is no command from the current pos.
    //                            Note that this will not normally happen if
    //                            the invariant condition of the class is 
    //                            maintained (see the comment at the front
    //                            of the class description). 
    //     OZT_Result(NO_PROBLEM) if a command is successfully retrieved.


    static RWBoolean  isCommentryLine(RWCString line);
    // Description
    //     Tells if a line is a commentry line only.
    // Parameter
    //     line   IN: the line to be checked.
    // Return value
    //     TRUE if the line is a commentry line only, otherwise FALSE 
    //     is returned.


    //**************************************************
    //  Functions for specific flow control commands
    //**************************************************

    OZT_Result  skipElse();
    // Description
    //     Skips all the following commands that starts with @ELSE. This
    //     member is used for implementating the @IF-THEN, @ELSE and 
    //     @IFERROR commands.
    // Parameter
    //     OZT_Result(HIT_EOF)   if there is no non-@ELSE command follows.
    //                           In this case, the current position is not
    //                           modified.
    //     OZT_Result(NO_PROBLEM) if the position is postioned successfully.


    RWBoolean   forLoopIndexUsed(const RWCString &varName) const;
    // Description
    //     Checks if the specified variable name is used already for
    //     any current for-loops.
    // Parameter
    //     varName   IN: the variable name in question
    // Return value
    //     TRUE if the variable is used, otherwise FALSE is returned.

    OZT_Result ifElseSetup( const OZT_Value& condition );
  // Description
  //    Sets up the IF/THEN/ELSE command; by finding the 
  //    belonging @ELSE and @ENDIF commands. Depending of the condition
  //    the current position is decided:
  //           i) if the condition is "TRUE"; the current position is the
  //              first line after the IF/THEN line
  //          ii) if the condition is "FALSE"; the current position is the first line 
  //              after @ELSE; if the @ELSE command is defined or the first line after @ENDIF
  // Parameter
  //     condition    IN: TRUE/FALSE value
  // Return value
  //     OZT_Result(NO_PROBLEM)
  //         if IF/THEN/ELSE is setup successfully
  //     OZT_Result(NO_MATCHING_ENDIF) 
  //         if there is no matching @ENDIF in the later part of the cmd file
  //     OZT_Result(MEM_ALLOC_ERR)
  //         if memory allocation fails
  //     OZT_Result(ELSE_WITHOUT_IF)
  //         if @ELSE is found without previously defined IF/THEN
  //     OZT_Result(ENDIF_WITHOUT_IF)
  //         if @ENDIF is found without previously defined IF/THEN

  OZT_Result forLoopBreak();
  // Description
  //    TBD
  // Return value
  //    TBD

    OZT_Result elseFound();
  // Description
  //    Check if there is a belonging IF command and advances the flow to the line after
  //    the @ENDIF command
  // Return value
  //     OZT_Result(NO_PROBLEM)
  //         if IF/THEN/ELSE is setup successfully
  //     OZT_Result(ELSE_WITHOUT_IF)
  //         if @ELSE is found without previously defined IF/THEN

    OZT_Result endifFound();
  // Description
  //    Check if there is a belonging IF command and removes the IF flow from the stack
  // Return value
  //     OZT_Result(NO_PROBLEM)
  //         if IF/THEN/ELSE is setup successfully
  //     OZT_Result(ENDIF_WITHOUT_IF)
  //         if @ENDIF is found without previously defined IF/THEN

  OZT_Result switchSetup( const OZT_Value& varValue );
  // Description
  //    Sets up a switch/case/endswitch command
  // Return value
  //     OZT_Result(NO_PROBLEM)
  //         if SWITCH is setup successfully
  //     OZT_Result(NO_MATCHING_ENDSWITCH)
  //         TBD

 OZT_Result caseFound( const OZT_Value& value );
  // Description
  //    Sets up a switch/case/endswitch command
  // Return value
  //     TBD

  OZT_Result defaultFound();
  // Description
  //    Sets up a switch/case/endswitch command
  // Return value
  //     TBD

  OZT_Result endswitchFound();
  // Description
  //    Sets up a switch/case/endswitch command
  // Return value
  //     TBD


  OZT_Result  forLoopSetUp(RWCString varName, 
			   const OZT_Value &firstValue,
			   const OZT_Value &lastValue);
  // Description
    //     Sets up a for-loop. This will makes the source info object
    //     remembers where to return when the for-loop hits the end.
    //     When returned, the current position will be at
    //
    //         i) the first non-commentry line of the loop body, or
    //        ii) the line after the matching @NEXT , or (This can happen
    //            for example "@FOR i = 10 to 1" is executed)
    //       iii) the line at the matching @NEXT. (Similar to (ii) but 
    //            there is no command after the @NEXT.
    // Parameter
    //     varName     IN: the index variable used in the for-loop
    //     firstValue  IN: the start value of the loop index
    //     lastValue   IN: the final value of the loop index
    // Return value
    //     OZT_Result(NO_PROBLEM)
    //         if the for-loop is setup successfully
    //     OZT_Result(INVALID_VALUE)
    //         if the startValue, or lastValue are not numeric
    //     OZT_Result(NO_MATCHING_NEXT) 
    //         if there is no matching @NEXT in the later part of the cmd file
    //     OZT_Result(MEM_ALLOC_ERR)
    //         if memory allocation fails
    //     OZT_Result(HIT_EOF)
    //         for case (iii) described above


    OZT_Result  forLoopNext(RWCString varName);
    // Description
    //     Called when "@NEXT var" is executed. The current position
    //     will be set to 
    //
    //         i) the start of the for-loop if the loop has not terminated, or
    //        ii) the line after the @NEXT if the loop terminated, or
    //       iii) no change, if the loop terminates but no command after the
    //            @NEXT. 
    // Parameter
    //     varName   IN: the name of the variable specified in @NEXT.
    // Return value
    //     OZT_Result(NO_PROBLEM)
    //         if the current position is adjusted according to the @NEXT.
    //     OZT_Result(HIT_EOF)
    //         For case (iii) above.
    //     OZT_Result(NEXT_WITHOUT_FOR)
    //         if there was no @for loop setup previously.
    //     OZT_Result(VAR_UNDEFINED)
    //         if the variable is not defined anymore (e.g. by @FLUSHVAR())
    //     OZT_Result(INVALID_VALUE)
    //         if the variable contains a non-numeric value.
    //     OZT_Result(PROGRAM_MODIFIED)
    //         if the current position cannot be set to the beginning
    //         of the loop body due to program update by the user.


    OZT_Result  findEndOfForLoop(const LineNo startLineNo,
                                 RWCString varName,
                                 LineNo &resultLineNo);
    // Description
    //     Find a matching @NEXT from a given position.
    // Parameters
    //     startLineNo    IN: the line from which the search starts.
    //     varName        IN: the variable for the for-loop to be looked for.
    //     resultLineNo   OUT: the line no. where the @NEXT is found.
    // Return value
    //     OZT_Result(NO_PROBLEM)   if the @NEXT is found
    //     OZT_Result(HIT_EOF)      if the @NEXT is not found


    OZT_Result  labelExist(RWCString label);
    // Description
    //     Check if a label is defined in a file
    // Parameter
    //     label   IN: the label in question
    // Return value
    //     OZT_Result(NO_PROBLEM)         if the label is defined
    //     OZT_Result(DUPLICATE_LABELS)   if the label is defined more than once
    //     OZT_Result(LABEL_NOT_FOUND)    if the label is not found


    OZT_Result  gotoLabel(RWCString label);
    // Description
    //     Set the current position to the specified label
    // Parameter
    //     label   IN: the label to jump to
    // Return value
    //     OZT_Result(NO_PROBLEM)         if the goto is successful
    //     OZT_Result(DUPLICATE_LABELS)   if the label is defined more than once
    //     OZT_Result(LABEL_NOT_FOUND)    if the label is not found


    OZT_Result  gosubLabel(RWCString label, const RWBoolean skipElseFlag);
    // Description
    //     Set up a gosub. This makes the object knows where to go back on
    //     return.
    // Parameter
    //     label          IN: the label to jump to
    //     skipElseFlag   IN: specifies if a "skip elses" is needed on return.
    // Return value
    //     OZT_Result(NO_PROBLEM)       if the gosub is successful
    //     OZT_Result(MEM_ALLOC_ERR)    if memory allocation fails
    //     OZT_Result(DUPLICATE_LABLES) if the label is defined multibly
    //     OZT_Result(LABEL_NOT_FOUND)  if the label is not found


    OZT_Result  returnFromGosub();
    // Description
    //     Return from a previous gosub. The current position will be set
    //     to the command after the @GOSUB. If the @GOSUB is inside
    //     a @IF-THEN or @IFERROR-THEN, all elses following will be skipped
    //     too.
    //     If there is no command to set since end of file is reached,
    //     the current position will stay at the @GOSUB and OZT_Result(HIT_EOF)
    //     is returned.
    // Return value
    //     OZT_Result(NO_PROBLEM)
    //         if the return is successful.
    //     OZT_Result(RETURN_WITHOUT_GOSUB)
    //         if there was no corresponding @GOSUB executed.
    //     OZT_Result(HIT_EOF)
    //         Return successful but there is no command after the @GOSUB.
    //     OZT_Result(PROGRAM_MODIFIED)
    //         if the @GOSUB is no longer on the same line. (It means the
    //         program has been modified.)

    RWBoolean isManualCommandEntry();    
  
    friend RWBoolean   operator==(const OZT_SourceInfo&, const OZT_SourceInfo&);
    // Description
    //     Equality operator.

    static unsigned hashString(const RWCString& str);
    // Description
    //     Required by tools.h++ for hashing purpose.
    
    struct myHash{
    unsigned long operator()(const RWCString& str) const
    {return str.hash();}
  };

private:

  void load( const RWTValOrderedVector<RWCString>& lines );
  // Description
  // TBD

  void       load();
  // Description
  //     Load the file specified in "filename".

    RWBoolean  toContinue(const RWCString &textBlk);
    // Description
    //     Test if the text specified in "textBlk" should continue
    //     for a command file primitive. For a command to continue, 
    //     it must have a comma (,) at the end.

    RWBoolean  adjustCurrLine();
    // Description
    //     Adjust the current line so that it sets on a non-commentry line.
    //     The algorithm tries to find the first line follows, if it fails,
    //     it tries to find the first line prior to the current position.
    // Parameter    
    //     FALSE  if there is no non-commentry line for the current position.
    //     TRUE   if the current position lands on a non-commentry line.

    void       composeScriptCmd(RWCString &textBlk, LineNo &cmdLength);
    // Description
    //     Compose a text block for a command file primitive
    //     from the current position. This function can concatenate 
    //     multiple lines if the command spans line boundary.
    // Parameter
    //     textBlk    OUT: the text block of the command with comment-stripped.
    //     cmdLength  OUT: the number of lines occupied by the command.

    void       composeHostCmd(RWCString &textBlk, LineNo &cmdLength);
    // Description
    //     Compose a text block for a MML command from the current position
    //     This function can concatenate multiple lines if the command spans
    //     line boundary.
    // Parameter
    //     textBlk    OUT: the text block of the MML command with @@ comment
    //                     stripped.
    //     cmdLength  OUT: the number of lines occupied by the command.

    void       getCurrCmdText(RWCString &textBlk, LineNo &cmdLength);
    // Description
    //     Compose a text block for a command from the current position.
    //     This function determines if the command is a MML or not, it then
    //     calls either composeScriptCmd() or composeHostCmd() for putting
    //     the lines together.

    void       skipCommentryLines();
    // Description
    //     Skips to a line which is not a comment.

    OZT_Result findElseStatement( LineNo startLineNo,
				  LineNo& resultLineNo );
  // Description
  //     Finds the belonging ELSE statement

    OZT_Result findEndifStatement( LineNo startLineNo,
				   LineNo& resultLineNo );
  // Description
  //      Finds the belonging ENDIF statement

  OZT_Result findEndswitchStatement( LineNo startLineNo,
				     LineNo& resultLineNo );
  // Description
  //      Finds the belonging ENDSWITCH statement

  OZT_Result findMatchingCaseStatement( LineNo startLineNo,
					OZT_Value varValue,
					LineNo& resultLineNo );
  // Description
  //      Finds the CASE statement that matches the value of the SWITCH variable

  OZT_FlowStackFrame* findFlow( FlowFrameType type );
  // Description
  //      Finds the specified flow

    static RWCString  stripCommentOnMML(const RWCString &line);
    static RWCString  stripAllComment(const RWCString &line);
    // Description
    //     Strips comments from a line.

    OZT_Result findAndInsertLabel(RWCString line, LineNo lineno);
    // Description
    //     Given a line, this function checks if it contains @LABEL xxx, if
    //     yes, this function inside a (label, lineno) pair to the label
    //     table.
    // Parameter
    //     line   IN: the text line to be checked.
    //     lineno IN: the line number of the text.

    OZT_Result                                     stat;
    LineNo                                         currLine;
    RWCString                                      filename;
    RWTValOrderedVector<RWCString>                 text;
   // RWTValHashDictionary<RWCString, LineNo>        labelTbl;
    RWTValHashMap<RWCString, LineNo, myHash,
                      std::equal_to<RWCString> > labelTbl;
    RWTPtrOrderedVector<OZT_FlowStackFrame>        flowStack;
    OZT_VarStore&                                  varStore;
    RWBoolean                                      isManualCommands;
};

#endif
