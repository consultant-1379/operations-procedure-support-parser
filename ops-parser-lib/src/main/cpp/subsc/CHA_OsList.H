// RCS handling
// $Id: CHA_OsList.H,v 24.0 1995/11/28 17:00:32 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_OsList - A list of currently available OS.
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_OsList.H 

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
//      A list of currently available other OS.
//      The list is checked against the current users
//      authority. It is sorted alphabetically.

// .SECTION ERROR HANDLING
//      Error messages are sent to the CHA_ErrorReporter
//      instance. Error events are also notified to all clients of
//      this model object.

// DOCUMENT NO
//      190 89-CAA 134 1515

// AUTHOR 
//      1994-08-11 by EHS/Marie Moschna (qhsmosc@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28
//      RCS revision history
//      $Log: CHA_OsList.H,v $
//      Revision 24.0  1995/11/28 17:00:32  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//       Revision 23.0  95/09/07  17:49:27  17:49:27  ehscama (Martin Carlsson VK/EHS/VE)
//       Made release XM2S1, ehscama.
//       
//       Revision 22.0  1995/08/01  20:50:22  cmcha
//       Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//       Revision 21.0  95/06/29  09:47:42  09:47:42  cmcha (*CHA conf. and dev. EHS/PXE)
//       Made release EC1_OZ, J Grape (EHSGRAP).
//       
//       Revision 20.0  95/06/08  08:38:53  08:38:53  cmcha (*CHA conf. and dev. EHS/PXE)
//       Made release TB5_2_OZ, J Grape (ehsgrap).
//       
//       Revision 19.1  95/04/24  13:04:39  13:04:39  ehsgrap (Jan Grape (9 9073) VK/EHS/PXE)
//       Changed returnCode to ReturnCode for consistency.
//       
//       Revision 19.0  1995/04/13  10:58:17  cmcha
//       Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//       Revision 18.0  95/03/17  20:11:03  20:11:03  cmcha (*CHA conf. and dev. EHS/PXE)
//       Made release TB51_OZ, ehscama.
//       
//       Revision 17.0  95/03/16  14:13:16  14:13:16  cmcha (*CHA conf. and dev. EHS/PXE)
//       Made release TB5_OZ, ehscama.
//       
//       Revision 16.0  95/03/10  13:05:18  13:05:18  cmcha (*CHA conf. and dev. EHS/PXE)
//       Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//       
//       Revision 15.0  95/03/09  15:12:03  15:12:03  cmcha (*CHA conf. and dev. EHS/PXE)
//       Made release TB6_B1C, N.Lanninge (XKKNICL).
//       
//       Revision 14.0  1995/02/25  16:38:50  cmcha
//       Made release TB4_OZ, J Grape (EHSGRAP).
//
//       Revision 13.5  95/02/15  14:12:16  14:12:16  cmcha (*CHA conf. and dev. EHS/PXE)
//       Made release CHUI_TB6, N.Lanninge (XKKNICL).
//       
//       Revision 12.0  95/02/06  16:22:44  16:22:44  cmcha (*CHA conf. and dev. EHS/PXE)
//       Made release TB3, J Grape (EHSGRAP).
//       
//       Revision 11.0  1995/01/18  14:54:21  cmcha
//       Made release PREIT, N Länninge (XKKNICL).
//
//       Revision 10.0  1994/12/22  09:08:18  cmcha
//       Made release TB2, J Grape (EHSGRAP).
//
//       Revision 9.0  1994/10/24  21:35:07  cmcha
//       Made release E, ehscama.
//
//       Revision 8.0  1994/10/05  08:56:14  cmcha
//       Made release D, EHSCAMA.
//
//       Revision 7.0  1994/09/22  13:28:01  cmcha
//       Made release R1C, J Grape (EHSGRAP).
//
//       Revision 6.0  1994/08/30  17:55:08  cmcha
//       Made release R1B, J Grape (EHSGRAP).
//
//       Revision 1.1  1994/08/26  10:13:04  qhsmosc
//       First version
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
//	D       1994-10-05      EHSCAMA                 RCS rev 8.0
//	R1C     1994-09-22      J Grape (EHSGRAP)       RCS rev 7.0
//	R1B     1994-08-30      J Grape (EHSGRAP)       RCS rev 6.0

// .SEE ALSO 
//      CHA_EsList

//**********************************************************************

#ifndef CHA_OSLIST_H
#define CHA_OSLIST_H

#include <rw/cstring.h>
#include <rw/tvsrtvec.h>
#include <CHA_Model.H>
#include <CHA_EsList.H>

class CHA_OsList : public CHA_EsList
{
public:

    CHA_OsList();
    // Description:
    //     Constructor.
    
    virtual ~CHA_OsList();
    // Description:
    //     Destructor.
    
    ReturnCode update();
    // Description:
    //     Updates the list.
    // Return value:
    //     OK			Succesful
    //     NOT_AUTHORIZED	The user is not authorized
    //     NO_CONTACT_AUTHDB 	Problems with authority data base

private:

};

#endif
