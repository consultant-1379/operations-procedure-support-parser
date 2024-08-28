// RCS revision handling
// $Id: OZT_Flow.H,v 21.0 1996/08/23 12:42:42 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_Flow - Objects of this class are passed from OZT_Interpreter
//                 to OZT_SourceMgr so that the next command can be located.
//
// .LIBRARY CHOZTBIN
// .PAGENAME OZT_Flow
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
// 	When a command file is executed, there are some commands which can
//      divert the flow of control. Examples are @INCLUDE, @GOTO and @GOSUB.
//      It is the purpose of the OZT_SourceMgr to locate the next command.
//      Objects of the OZT_Flow class are passed from the interpreter to the
//      Source Manager so that the next command can be located.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	190 89-CAA 134 2016

// AUTHOR 
// 	1994-10-05 by EPA/T/EN Nelson Cheng (epanyc@epa.ericsson.se)


// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_Flow.H,v $
// 	Revision 21.0  1996/08/23 12:42:42  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 07:57:21  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:22:15  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:21:15  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:01:49  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:57:08  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:02:41  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:16:57  17:16:57  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.0  1995/10/07 12:01:12  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:08:53  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:24:54  09:24:54  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:01:59  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:37:44  14:37:44  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.2  95/06/28  14:30:55  14:30:55  epanyc (Nelson Cheng VK/EHS/PXE)
//      comment added
//      
//      Revision 8.1  1995/06/26  08:53:26  epanyc
//      no change
//
//      Revision 8.0  1995/06/07  17:08:55  cmcha
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//
//      Revision 7.0  95/04/16  12:16:10  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.0  95/03/17  20:05:13  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 5.0  95/03/16  20:31:00  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 4.0  95/02/23  21:45:47  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB4, J Grape (EHSGRAP).
//
//      Revision 3.0  95/02/06  20:57:21  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 2.4  95/01/31  10:31:30  epanyc (Nelson Cheng VK/EHS/PXE)
//      no change
//
//      Revision 2.3  1994/12/21  16:07:38  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 2.0  94/12/21  13:51:47  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 1.5  1994/11/16  10:26:09  epanyc
//
//      Revision 1.4  1994/10/28  13:03:19  epanyc
//      check in for Neil to compile
//
//      Revision 1.3  1994/10/12  16:35:47  epanyc
//      SUCCESS becomes NO_PROBLEM
//
//      Revision 1.2  1994/10/12  14:33:55  epanyc
//      *** empty log message ***
//
//      Revision 1.1  1994/10/05  12:08:42  cmcha
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

#ifndef OZT_FLOW_H
#define OZT_FLOW_H

#include <rw/cstring.h>

class OZT_Flow {
public:

    enum Code {UNDEFINED,
               NORMAL, 
               FOR_SETUP,            // @for i = x to y
               NEXT,                 // @next
               GOTO_LABEL,           // @goto labelx
               GOSUB_LABEL,          // @gosub labelx
               RETURN_FROM_GOSUB,    // @return
               INCLUDE,              // @include filename   or  @I filename
               END_OF_FILE,
               PAUSE,                // @PAUSE   or   @W
               QUIT,                 // @QUIT
               STOP,                 // @stop
               RESTART,              // @restart
               FILE_HALTED,           // !$$$$!
	       IF,
	       ELSE,
	       BREAK,
	       ENDIF,
	       SWITCH,
	       CASE,
	       DEFAULT,
	       ENDSWITCH
    };

    OZT_Flow(const OZT_Flow::Code codeIn   = UNDEFINED,
             const RWCString      &info1In = "",
             const RWCString      &info2In = "",
             const RWCString      &info3In = "");

    Code      code;
    RWBoolean skipElseFlag;
    RWCString info1;
    RWCString info2;
    RWCString info3;

    //*******************************************************************
    //
    //                    info1      info2      info3    skipElseFlag
    // UNDEFINED            -          -          -           -
    // NORMAL               -          -          -           -
    // FOR_SETUP          varname  startvalue  endvalue       -
    // NEXT               varname      -          -           -
    // GOTO_LABEL         label        -          -           -
    // GOSUB_LABEL        label        -          -          used
    // RETURN_FROM_GOSUB    -          -          -           -
    // INCLUDE            filename     -          -          used
    // END_OF_FILE          -          -          -           -
    //
    //*******************************************************************

    OZT_Flow& operator=(const OZT_Flow& f);
    RWCString toMsg() const;

    friend std::ostream& operator<<(std::ostream& os, const OZT_Flow& flow);
};

#endif
