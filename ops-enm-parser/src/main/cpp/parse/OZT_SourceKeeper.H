// RCS revision handling
// $Id: OZT_SourceKeeper.H,v 1.0 1996/03/19 07:20:56 ehsjasa Rel $

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
// 	$Log: OZT_SourceKeeper.H,v $
//      Revision 1.1  95/05/24  07:46:20  07:46:20  epanyc (Nelson Cheng VK/EHS/PXE)
//      Initial revision
//      
//
//	RELEASE REVISION HISTORY
//
//	REV NO	DATE		NAME			DESCRIPTION
//	POW_TB611996-03-19      J Sandquist (ehsjasa)   RCS rev 19.0
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	<link information: libraries needed and order>

// .SEE ALSO 
// 	<Related classes, (abstract) baseclasses, friend classes, ...>

//*****************************************************************************


#ifndef OZT_SOURCEKEEPER_H
#define OZT_SOURCEKEEPER_H

#include <OZT_SourceMgr.H>

class OZT_SourceKeeper
{
public:

    static OZT_SourceKeeper* Instance();
    //  Description:
    //      Return a pointer to this object.

    void setSourceMgrPointer (OZT_SourceMgr* p);
    //  Description:
    //      Set the pointer to the OZT_SourceMgr.

    OZT_SourceMgr* getSourceMgrPointer();
    //  Description:
    //      Get the pointer to the OZT_SourceMgr previously set.
    
protected:

    OZT_SourceKeeper();
    //  Description:
    //      Constructor.

private:
    static OZT_SourceKeeper* instance;
    OZT_SourceMgr*    pSourceMgr;

};

#endif
