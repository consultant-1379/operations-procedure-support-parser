// RCS revision handling
// $Id: OZT_Def.H,v 21.0 1996/08/23 12:42:24 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	<ClassName> - <Short description of the class>
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
// 	<General description of the class>

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	%EriDoc_no:%

// AUTHOR 
// 	<Date> by <Dept> <Name>

// .REVISION <for public API>
//	<Revision state>
//	<Revision date>	  	

// .REVISION <for internal header files>
//	%EriDoc_rev:%
//	%EriDoc_date:%  	

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_Def.H,v $
// 	Revision 21.0  1996/08/23 12:42:24  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 07:57:03  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.1  1996/05/15 09:53:35  ememjga
// 	Changed type to allow negative values , AD16693.
//
//      Revision 19.0  96/03/19  07:22:06  07:22:06  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB61, J Sandquist (ehsjasa).
//      
// 	Revision 18.0  1996/03/01 12:20:59  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:01:29  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:56:56  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:02:29  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:16:08  17:16:08  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.0  1995/10/07 12:00:57  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:08:35  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:24:39  09:24:39  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:01:35  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:37:27  14:37:27  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.0  95/06/07  17:08:34  17:08:34  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 7.0  95/04/16  12:15:55  12:15:55  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 6.0  95/03/17  20:04:58  20:04:58  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 5.0  95/03/16  20:30:46  20:30:46  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 4.0  95/02/23  21:45:37  21:45:37  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB4, J Grape (EHSGRAP).
//      
//      Revision 3.0  95/02/06  20:57:13  20:57:13  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 2.3  94/12/21  16:07:25  16:07:25  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//      
//      Revision 2.0  94/12/21  13:51:36  13:51:36  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//      
//      Revision 1.1  1994/11/16  10:25:45  epanyc
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


#ifndef OZT_DEF_H
#define OZT_DEF_H

#include <rw/defs.h>

typedef int LineNo;

#endif
