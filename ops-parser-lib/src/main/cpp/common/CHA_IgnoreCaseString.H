// RCS handling
// $Id: CHA_IgnoreCaseString.H,v 24.0 1995/11/28 16:54:45 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_IgnoreCaseString - A string that ignore case at comparison.
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_IgnoreCaseString.H 

// .COPYRIGHT
//      COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1994
//
//      The Copyright to the computer program(s) herein is the
//      property of Ericsson Hewlett-Packard Telecommunications AB,
//      Sweden.  The program(s) may be used and/or copied with the
//      written permission from Ericsson Hewlett-Packard
//      Telecommunications AB or in accordance with the terms and
//      conditions stipulated in the agreement/contract under which
//      the program(s) have been supplied.

// .DESCRIPTION 
//	The class inherits from RWCString and all functions almost as that class.
//      The only difference is that the comparison methodes of this class are
//      case insensitive. This is done by overloading.
//      The result is that this class has the same interface as RWCString.

// .SECTION ERROR HANDLING

// DOCUMENT NO
//      190 89-CAA 134 1515

// AUTHOR 
//      1994-10-11 by EHS/Marie Moschna (qhsmosc@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28
//      Initial version
//

//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	TB53_OZ 1995-11-28      J Grape (EHSGRAP)       RCS rev 24.0
//	XM2S1   1995-09-07      ehscama                 RCS rev 23.0
//	EC2_OZ  1995-08-01      Jan Sandquist (EHSJAASA)RCS rev 22.0
//	EC1_OZ  1995-06-29      J Grape (EHSGRAP)       RCS rev 21.0
//	TB5_2_OZ1995-06-08      J Grape (ehsgrap)       RCS rev 20.0
//	TB5_1_OZ1995-04-13      J Grape (EHSGRAP)       RCS rev 19.0
//	TB51_OZ 1995-03-17      ehscama                 RCS rev 18.0
//	TB5_OZ  1995-03-16      ehscama                 RCS rev 17.0
//	TB6_B1C_B1995-03-10      N.Lanninge (XKKNICL)    RCS rev 16.0
//	TB6_B1C 1995-03-09      N.Lanninge (XKKNICL)    RCS rev 15.0
//	TB4_OZ  1995-02-25      J Grape (EHSGRAP)       RCS rev 14.0
//	CHUI_TB61995-02-15      N.Lanninge (XKKNICL)    RCS rev 13.5
//	TB3     1995-02-06      J Grape (EHSGRAP)       RCS rev 12.0
//	PREIT   1995-01-18      N Länninge (XKKNICL)    RCS rev 11.0
//	TB2     1994-12-22      J Grape (EHSGRAP)       RCS rev 10.0
//	E       1994-10-24      ehscama                 RCS rev 9.0

// .SEE ALSO 
//      CHA_EsList

//**********************************************************************

#ifndef CHA_IGNORECASESTRING_H
#define CHA_IGNORECASESTRING_H

#include <rw/cstring.h>

#include <rw/cstring.h>
#include <rw/tvsrtvec.h>
#include <CHA_Model.H>


class CHA_IgnoreCaseString : public RWCString
{
  public:

    CHA_IgnoreCaseString();
    CHA_IgnoreCaseString(const RWCString r);
    CHA_IgnoreCaseString(const char* r);
    // Description:
    //     Constructor.

    ~CHA_IgnoreCaseString();
    // Description:
    //     Destructor.

    CHA_IgnoreCaseString& operator=(const char* cs);
    // Description:
    //     Sets self to cs.

    friend RWBoolean operator<(const CHA_IgnoreCaseString& s1, 
			       const CHA_IgnoreCaseString& s2);
    // Description:
    //     Compares s1 with s2.
    // Return value:
    // 	   int                 <, > or = zero, according to comparison method

  private:
};

#endif
