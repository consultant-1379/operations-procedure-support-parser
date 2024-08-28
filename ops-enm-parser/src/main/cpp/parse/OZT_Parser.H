// RCS revision handling
// $Id: OZT_Parser.H,v 21.0 1996/08/23 12:42:54 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	N.A
// .LIBRARY CHOZTBIN
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
// 	This file is the bridge between the lex and yacc generated code.
//      This file should not be included in any other C++ files.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	190 89-CAA 134 2016

// AUTHOR 
// 	1994-10-04 by EPA/T/EN Nelson Cheng (epanyc@epa.ericsson.se)

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_Parser.H,v $
// 	Revision 21.0  1996/08/23 12:42:54  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 07:57:32  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:22:21  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:21:29  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:02:02  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:57:18  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:02:49  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:17:09  17:17:09  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.1  1995/10/23 15:44:43  ehsjasa
// 	Removed unnecessary inclusions of "rw/tvordvec.h" (forward declaration
// 	used instead) and excessive inclusion "rw/tpordvec.h".
//
// 	Revision 13.0  1995/10/07 12:01:23  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:09:09  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:25:05  09:25:05  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:02:16  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.1  95/07/05  09:12:46  09:12:46  epanyc (Nelson Cheng VK/EHS/PXE)
//      comment added
//      
//      Revision 9.0  1995/06/29  14:37:56  cmcha
//      Made release EC2_OZ, J Grape (EHSGRAP).
//
//      Revision 8.1  95/06/28  14:31:30  14:31:30  epanyc (Nelson Cheng VK/EHS/PXE)
//      comment added
//
//      Revision 8.0  1995/06/07  17:09:08  cmcha
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//
//      Revision 7.0  95/04/16  12:16:20  12:16:20  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.0  95/03/17  20:05:24  20:05:24  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 5.0  95/03/16  20:31:10  20:31:10  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 4.1  95/03/15  20:12:02  20:12:02  epanyc (Nelson Cheng VK/EHS/PXE)
//      SC_SKIP removed
//
//      Revision 4.0  1995/02/23  21:45:56  cmcha
//      Made release TB4, J Grape (EHSGRAP).
//
//      Revision 3.0  95/02/06  20:57:30  20:57:30  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 2.5  95/01/31  10:31:30  10:31:30  epanyc (Nelson Cheng VK/EHS/PXE)
//      prompt object added
//
//      Revision 2.4  1995/01/16  08:24:47  epanyc
//      skip start condition added
//
//      Revision 2.3  1994/12/21  16:07:48  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 2.0  94/12/21  13:52:00  13:52:00  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 1.5  1994/12/12  13:36:25  epanyc
//      a pointer implementation is used for return types
//
//      Revision 1.4  94/11/25  10:17:51  10:17:51  epanyc (Nelson Cheng VK/EHS/PXE)
//      check in for the 1st delivery
//
//      Revision 1.3  94/10/18  12:24:58  12:24:58  epanyc (Nelson Cheng VK/EHS/PXE)
//      boolean type added
//
//      Revision 1.2  1994/10/12  16:35:54  epanyc
//      SUCCESS becomes NO_PROBLEM
//
//      Revision 1.1  1994/10/05  11:21:52  cmcha
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

#ifndef OZT_PARSER_H
#define OZT_PARSER_H

#include <OZT_Value.H>
#include<rw/tvordvec.h>

//template <class TP> class RWTValOrderedVector; // forward declaration

//
//   Start conditions in lex
//
enum {SC_NORMAL = 1, SC_CMD, SC_LABEL, SC_CHAR_SEQ};

//
//   Return types of grammar rules
//
typedef union {
    RWTValOrderedVector<OZT_Value>* vl;
    OZT_Value* v;
    RWBoolean b;
} YYSTYPE;

extern int       ozt_sc;   /* start condition */
extern OZT_Value ozt_TokenVal;
#endif
