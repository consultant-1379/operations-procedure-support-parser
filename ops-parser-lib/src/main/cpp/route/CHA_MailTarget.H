// RCS handling
// $Id: CHA_MailTarget.H,v 24.0 1995/11/28 16:57:51 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_MailTarget - sends responses to a mail address
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_MailTarget.H

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
//      CHA_MailTarget is a routing target for responses routed to
//      mail. A mail target observes one or more response receivers
//      and sends a mail to it's mail address for every response it
//      receives.
//
//      A CHA_MailTarget only handles one mail address so if routing
//      is set up to more than one mail recipient ther will have to be
//      multiple mail targets. Instantiation and control is usually
//      done by a CHA_MailRouter.

// .SECTION ERROR HANDLING
//      Errors are reported to the globar CHA_ErrorReporter instance. 

// DOCUMENT NO
//      190 89-CAA 134 1519

// AUTHOR 
//      1994-04-27 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_MailTarget.H,v $
//      Revision 24.0  1995/11/28 16:57:51  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:45:26  17:45:26  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:47:11  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:43:55  09:43:55  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:35:47  08:35:47  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:55:07  10:55:07  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:07:31  20:07:31  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:08:17  14:08:17  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:01:48  13:01:48  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:05:40  15:05:40  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:35:48  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:06:52  14:06:52  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:18:31  16:18:31  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:48:51  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:04:58  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:31:28  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:51:16  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:24:25  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:51:33  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:47:34  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:40:01  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:56:12  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.1  1994/06/21  12:59:10  ehsgrap
//      Added an #include
//
//      Revision 2.0  1994/06/12  07:58:53  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.2  1994/06/10  16:55:25  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.1  1994/04/29  06:54:23  ehsgrap
//      Initial revision
//
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
//	R1A     1994-08-16      J Grape (EHSGRAP)       RCS rev 5.0
//	P1C     1994-07-18      J Grape (EHSGRAP)       RCS rev 4.0
//	P1B     1994-06-23      J Grape (EHSGRAP)       RCS rev 3.0
//	P1A     1994-06-12      J Grape (EHSGRAP)       RCS rev 2.0

// .SEE ALSO 
//      CHA_RoutingTarget, CHA_MailRouter

//**********************************************************************

#ifndef CHA_MAILTARGET_H
#define CHA_MAILTARGET_H

#include <CHA_RoutingTarget.H>
#include <CHA_NLSCatalog.H>
#include <CHA_Pipe.H>


class CHA_MailTarget : public CHA_RoutingTarget
{
    
public:

    CHA_MailTarget(const RWCString& addr);
    // Description:
    //     Constructor.
    // Parameters:
    //     addr		the mail address to send responses to

    virtual ~CHA_MailTarget();
    // Description:
    //     Destructor.

protected:

    virtual void doRouting(const CHA_ResponseBuffer* pResponse);
    // Description:
    //     Implements the actual routing, i.e. sending the output to
    //     mail. Activated by the superclass.
    // Parameters:
    //     response	the response to route

private:

    RWCString address;		// the mail address
    CHA_NLSCatalog nlsCat;
};

#endif
