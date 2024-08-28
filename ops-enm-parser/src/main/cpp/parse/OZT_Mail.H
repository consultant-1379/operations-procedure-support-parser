// RCS revision handling
// $Id: OZT_Mail.H,v 21.0 1996/08/23 12:42:50 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_Mail - Mail sender 
// .LIBRARY CHOZTBIN
// .PAGENAME OZT_Mail
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
// 	This class provides a number of functions for sending mail
//      to a list of specified users.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	190 89-CAA 134 2016

// AUTHOR 
// 	1995-01-24 by Eric Tse (epatse@epa.ericsson.se)

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_Mail.H,v $
// 	Revision 21.0  1996/08/23 12:42:50  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 07:57:29  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:22:19  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:21:23  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:01:57  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:57:14  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:02:46  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:17:05  17:17:05  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.1  1995/10/31 17:06:46  ehsjasa
// 	Some unnecessary include directives removed or replaced with forward
// 	declarations.
//
// 	Revision 13.0  1995/10/07 12:01:19  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:09:04  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:25:01  09:25:01  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:02:09  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.1  95/07/05  09:11:58  09:11:58  epanyc (Nelson Cheng VK/EHS/PXE)
//      comment added
//      
//      Revision 9.0  1995/06/29  14:37:52  cmcha
//      Made release EC2_OZ, J Grape (EHSGRAP).
//
//      Revision 8.0  95/06/07  17:09:03  17:09:03  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 7.1  95/06/07  11:59:01  11:59:01  epanyc (Nelson Cheng VK/EHS/PXE)
//      removal of a function
//      
//      Revision 7.0  1995/04/16  12:16:16  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.4  95/03/28  11:22:11  11:22:11  epatse (Eric Tse VK/EHS/PXE)
//      The functions setContent(), getContent(), sendFile() and some sendMail()
//      functions associated with the member variable "content" are all removed.
//      The member variable "content" is removed.
//      
//      Revision 6.3  1995/03/24  16:43:09  epanyc
//      sigchld catcher added
//
//      Revision 6.2  1995/03/23  10:03:04  epatse
//      The member variable "subject" is removed.
//
//      Revision 6.1  1995/03/21  14:52:35  epatse
//      Another 2 sendMail() functions are added.
//
//      Revision 4.0  95/02/23  21:45:52  21:45:52  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB4, J Grape (EHSGRAP).
//      
//      Revision 3.1  95/02/21  13:48:06  13:48:06  epatse (Eric Tse VK/EHS/PXE)
//      check in for epanyc
//      
//      Revision 3.0  1995/02/06  20:57:27  cmcha
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 1.3  95/01/27  16:22:18  16:22:18  epatse (Eric Tse VK/EHS/PXE)
//      *** empty log message ***
//      
//      Revision 1.2  1995/01/24  11:27:33  epanyc
//      template added
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
//	TB4     1995-02-23      J Grape (EHSGRAP)       RCS rev 4.0
//	TB3     1995-02-06      J Grape (EHSGRAP)       RCS rev 3.0
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	<link information: libraries needed and order>

// .SEE ALSO 
// 	<Related classes, (abstract) baseclasses, friend classes, ...>

//*****************************************************************************

#ifndef OZT_MAIL_H
#define OZT_MAIL_H

#include <rw/defs.h>
#include <OZT_ErrHandling.H>
// Forward declarations
template <class TP, class A> class RWTValOrderedVector;
class RWCString;

//*****************************************************************************

class OZT_Mail {
    
public:
    OZT_Mail();
    // Description
    //     Constructor

    ~OZT_Mail();
    // Description
    //     Destructor

    OZT_Result sendMail(const RWCString& mailSubject,
                       const RWCString& mailText,
                       const RWCString& mailAddress);
    //
    // Description:
    //    This function will send the contains in mailText
    //    to the user with address of mailAddress.
    // Parameters:
    //    mailSubject    The subject of the mail.
    //    mailText       The contents of the mail.
    //    mailAddess     The mailing address of the receiver.
    // 

    OZT_Result sendFile(const RWCString& mailSubject,
			const RWCString& filePath,
			const RWCString& mailAddress );
//
    // Description:
    //    This function will send the context of the
    //    specified file
    //    to the user with address of mailAddress.
    // Parameters:
    //    mailSubject    The subject of the mail.
    //    filePath       The file to be sent
    //    mailAddess     The mailing address of the receiver.

    OZT_Result sendMail(const RWCString& mailSubject,
			const RWCString& mailText,
			const RWTValOrderedVector<RWCString>& mailAddresses);
    //
    // Description:
    //    This function will send the contains in mailText
    //    to the users with addresses of mailAddresses.
    // Parameters:
    //    mailSubject    The subject of the mail.
    //    mailText       The contents of the mail.
    //    mailAddesses   The mailing addresses of the receivers.
    // 

    OZT_Result sendMail(const RWCString& mailText,
			const RWCString& mailAddress);
    //
    // Description:
    //    This function will send the contains in mailText
    //    to the user with address of mailAddress.
    // Parameters:
    //    mailText       The contents of the mail.
    //    mailAddess     The mailing address of the receiver.
    // 

    OZT_Result sendMail(const RWCString& mailText,
			const RWTValOrderedVector<RWCString>& mailAddresses);
    //
    // Description:
    //    This function will send the contains in mailText
    //    to the users with addresses of mailAddresses.
    // Parameters:
    //    mailText       The contents of the mail.
    //    mailAddesses   The mailing addresses of the receivers.
    // 
};

#endif
