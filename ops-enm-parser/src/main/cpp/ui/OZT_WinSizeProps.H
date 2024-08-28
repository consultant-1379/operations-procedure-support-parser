// RCS revision handling
// $Id: OZT_WinSizeProps.H,v 21.0 1996/08/23 12:46:56 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_WinSizeProps - access to X windows type properties file for CFD.
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

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	%EriDoc_no:%

// AUTHOR 
// 	1996-06-12 by EPA/T/EN David Terry

// .REVISION <for public API>
//	<Revision state>
//	<Revision date>	  	

// .REVISION <for internal header files>
//	%EriDoc_rev:%
//	%EriDoc_date:%  	

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_WinSizeProps.H,v $
// 	Revision 21.0  1996/08/23 12:46:56  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 08:01:07  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 1.1  1996/06/12 14:29:25  epadmt
// 	Initial revision
//
//
//	RELEASE REVISION HISTORY
//
//	REV NO	DATE		NAME			DESCRIPTION
//	B_POINT 1996-08-23      J Grape (EHSGRAP)       RCS rev 21.0
//	EC8_OZ  1996-07-10      David Terry epa.epadmt  RCS rev 20.0
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	<link information: libraries needed and order>

// .SEE ALSO 
// 	<Related classes, (abstract) baseclasses, friend classes, ...>

//*****************************************************************************


#ifndef OZT_WINSIZEPROPS_H 
#define OZT_WINSIZEPROPS_H

#include <tuib/Ui_prop.hh>
#include <rw/cstring.h>

#include <OZT_CDFDef.H>


class  OZT_WinSizeProps
{

public:

    OZT_WinSizeProps();
    // Description:
    //	   constructor
    // Parameters:

    ~OZT_WinSizeProps();
    // Description:
    //     Destructor.

    int getSize(RWCString winlabel, int defValue = 0);
    void setSize(RWCString winlabel, int size);
    void save();

protected:
    Ui_prop * props;
private:
};

#endif
