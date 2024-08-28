// RCS revision handling
// $Id: CHA_LoggerPipe.H,v 21.0 1996/08/23 12:40:26 ehsgrap Rel $

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
// 	$Log: CHA_LoggerPipe.H,v $
// 	Revision 21.0  1996/08/23 12:40:26  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 07:55:16  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:20:57  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:18:42  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 11:58:40  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:55:30  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.1  1995/11/29 02:12:30  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 15.0  95/11/29  02:01:16  02:01:16  ehsgrap (Jan Grape (9 9073) VK/EHS/VE)
//      Made release TB53_OZ, J Grape (EHSGRAP).
//      
//      Revision 14.0  95/11/20  17:14:09  17:14:09  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.1  1995/10/30 14:30:05  ehsjasa
// 	Forward declarations replacing include directives.
//
// 	Revision 13.0  1995/10/07 11:59:12  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:06:12  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:22:54  09:22:54  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 10:58:26  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:35:25  14:35:25  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.0  95/06/07  17:06:16  17:06:16  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 1.3  95/06/07  12:03:55  12:03:55  epanyc (Nelson Cheng VK/EHS/PXE)
//      memory deallocation problem fixed
//      
//      Revision 1.2  95/05/29  13:31:59  13:31:59  epanyc (Nelson Cheng VK/EHS/PXE)
//      make the pPipe protected
//      
//      Revision 1.1  95/05/24  07:46:20  07:46:20  epanyc (Nelson Cheng VK/EHS/PXE)
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
//	TB53_OZ 1995-11-29      J Grape (EHSGRAP)       RCS rev 15.0
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


#ifndef CHA_LOGGER_PIPE_H
#define CHA_LOGGER_PIPE_H

#include <rw/cstring.h>
#include <CHA_Logger.H>

// Forward declarations
class CHA_EventHandler;
class CHA_Pipe;

class CHA_LoggerPipe : public CHA_Logger
{
public:
    CHA_LoggerPipe(CHA_LogSource& source,
                   CHA_EventHandler* cleaner = 0);

    virtual ~CHA_LoggerPipe();

protected:
    virtual CHA_LogReturnCode turnOn();

    virtual CHA_LogReturnCode turnOff();

    virtual void setCmdStr(const RWCString& str);

    virtual void setCmdStr(char* const argv[]);

    virtual void appendLog(RWBoolean , const RWCString &newText);

    virtual CHA_LogReturnCode setUpPipe();
    // Description:
    //     Set up a pipe to an external program. The protected
    //     member setCmdStr() must be called to set the command string
    //     first before this function can be used.

    virtual CHA_LogReturnCode shutDownPipe();
    // Description:
    //     Bring down the pipe created previously.

    CHA_Pipe* pPipe;
    
protected:
  RWBoolean       isFirstTime;
private:
  CHA_EventHandler* pCleaner;
  char**            pArgv;
  RWCString         cmdString;
  
};

#endif
