// RCS revision handling
// $Id: CHA_EventHandler.H,v 21.0 1996/08/23 12:40:16 ehsgrap Rel $

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
// 	$Log: CHA_EventHandler.H,v $
// 	Revision 21.0  1996/08/23 12:40:16  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.1  1996/07/29 12:19:23  emejerf
// 	Changed for fixing EXECUTE() command with the HP-UX10 OS.
// 	Now the setSigChdTrigger() receive a pointer to function
// 	with three parameters instead of one parameter.
//
// 	Revision 20.0  1996/07/10 07:55:07  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:20:51  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:18:34  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 11:58:34  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:55:21  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.1  1995/11/29 02:12:23  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:13:58  17:13:58  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.0  1995/10/07 11:59:03  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:05:59  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:22:44  09:22:44  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 10:58:12  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:35:14  14:35:14  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.0  95/06/07  17:06:06  17:06:06  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 1.1  95/06/07  12:03:12  12:03:12  epanyc (Nelson Cheng VK/EHS/PXE)
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
//	TB53_OZ 1995-11-29      J Grape (EHSGRAP)       RCS rev 15.1
//	POW_TB3 1995-11-20      J Sandquist (EHSJASA)   RCS rev 14.0
//	PRE_XM221995-10-07      J Sandquist (EHSJASA)   RCS rev 13.0
//	EC5_OZ  1995-09-22      J Sandquist (EHSJASA)   RCS rev 12.0
//	EC4_OZ  1995-09-14      J Sandquist (EHSJASA)   RCS rev 11.0
//	EC3_OZ  1995-08-02      J Sandquist (EHSJASA)   RCS rev 10.0
//	EC2_OZ  1995-06-29      J Grape (EHSGRAP)       RCS rev 9.0
//	TB5_2_OZ1995-06-07      J Grape (EHSGRAP)       RCS rev 8.0
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	<link information: libraries needed and order>

// .SEE ALSO 
// 	<Related classes, (abstract) baseclasses, friend classes, ...>

//*****************************************************************************


#ifndef CHA_EVENT_HANDLER_H
#define CHA_EVENT_HANDLER_H

#include <sys/wait.h>

class CHA_EventHandler
{
public:
    virtual void setSigChdTrigger(void *instance, 
                                  pid_t pid,
                                  int (*func)(void *,pid_t,int *) = 0) = 0;

    //  Description:
    //      To register a process so that when the process dies, there
    //      won't be a zombie process left behind.

    virtual void unsetSigChdTrigger(void *instance, pid_t pid) = 0;
    //  Description:
    //      To de-register the process registered previously.

};

#endif
