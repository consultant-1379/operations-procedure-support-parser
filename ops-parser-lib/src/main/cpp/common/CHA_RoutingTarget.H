// RCS handling
// $Id: CHA_RoutingTarget.H,v 22.0.1.1 1996/01/05 14:09:50 ehsphad Exp $

//**********************************************************************
// 
// .NAME CHA_RoutingTarget - routes responses to a specific destination
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_RoutingTarget.H

// .COPYRIGHT
// 	COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1994
//
// 	The Copyright to the computer program(s) herein is the
// 	property of Ericsson Hewlett-Packard Telecommunications AB,
// 	Sweden.  The program(s) may be used and/or copied with the
// 	written permission from Ericsson Hewlett-Packard
// 	Telecommunications AB or in accordance with the terms and
// 	conditions stipulated in the agreement/contract under which
// 	the program(s) have been supplied.


// .DESCRIPTION 
//      The CHA_RoutingTarget class is a base class for all routing
//      targets, i.e. destinations where responses can go. A routing
//      target should observe all response receivers that it is
//      supposed to receive responses from. When a new response buffer
//      is available the response receiver will then notify the
//      routing target.
// 
//      The main purpose of this class is to provide a unified
//      interface to the CHA_Routing class and other's who maintain
//      several routing targets.
//
//      The actual response reception and routing must be taken care
//      of in a subclass.

// .SECTION ERROR HANDLING
//      When an error occurs a message should be is sent to the
//      CHA_ErrorReporter instance, but that is pretty much up to the
//      implementing sub class.

// DOCUMENT NO
//	190 89-CAA 134 1515

// AUTHOR 
// 	1994-02-16 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
// 	RCS revision history
//      $Log: CHA_RoutingTarget.H,v $
//      Revision 22.0.1.1  1996/01/05 14:09:50  ehsphad
//      Changed all RWModel to CHA_Model.
//
//      Revision 24.0  1995/11/28 16:55:08  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:41:27  17:41:27  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:44:02  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:39:56  09:39:56  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:32:40  08:32:40  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:52:02  10:52:02  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:04:17  20:04:17  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:02:44  14:02:44  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  12:58:11  12:58:11  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:00:10  15:00:10  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:33:04  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:02:36  14:02:36  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:13:24  16:13:24  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:45:06  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:01:49  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:28:35  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:48:03  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:22:26  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:49:32  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:44:22  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:37:01  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:51:40  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:04:04  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.7  1994/06/01  12:02:00  ehsgrap
//      Use of RWTPtrDlist intead of RWTValDlist
//
//      Revision 1.6  1994/05/10  14:26:52  ehsgrap
//      Spelling correction.
//
//      Revision 1.5  1994/04/21  14:06:13  ehsgrap
//      Added list of response receiver pointers.
//
//      Revision 1.4  1994/04/11  13:42:19  ehsgrap
//      Moved the empty impl of detachFrom from .H to .C
//
//      Revision 1.3  1994/02/28  17:59:10  ehsgrap
//      Use of CHA_Model[Client]
//
//      Revision 1.2  1994/02/22  10:22:39  ehsgrap
//      Corrections for first compilation.
//
//      Revision 1.1  1994/02/14  08:41:37  cmcha
//      Initial revision
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
// 	CHA_ResponseReceiver, CHA_ResponseBuffer

//**********************************************************************

#ifndef CHA_ROUTINGTARGET_H
#define CHA_ROUTINGTARGET_H

#include <CHA_ModelClient.H>
#include <CHA_ResponseReceiver.H>
#include <CHA_ResponseBuffer.H>

#include <rw/tpdlist.h>

class CHA_RoutingTarget : public CHA_ModelClient
{
public:
    CHA_RoutingTarget();
    // Description:
    //     Constructor.

    virtual ~CHA_RoutingTarget();
    // Description:
    //     Destructor.

    virtual void route(CHA_ResponseReceiver* respRcvr);
    // Description:
    //     This will make the routing target route responses from the
    //     supplied response receiver.
    // Parameters:
    //     respRcvr		the response receiver to receive
    //				responses from

    virtual void dontRoute(CHA_ResponseReceiver* respRcvr);
    // Description:
    //     This will make the routing target stop routing responses
    //     from the supplied response receiver. If th response receiver
    //     is unknown to the routing target (i.e. not in the list)
    //     nothing will happen.
    // Parameters:
    //     respRcvr		the response receiver to receive
    //				responses from

    virtual size_t nrOfReceivers() const;
    // Description:
    //     To find out how many response receivers the routing target
    //     is receiving from.
    // Return value:
    //     The number of receivers, >= 0.

    virtual void updateFrom(CHA_Model* p, void* d);
    // Description:
    //     The implementation of the update method inherited from
    //     CHA_ModelClient. This method calls doRouting when a complete
    //     response is available. It is expected that this method is
    //     called from a CHA_ResponseReceiver object.
    //
    //     If there is a possibility that this is not the case
    //     (e.g. in a subclass of this class that observes other
    //     CHA_Model objects as well) this method has to be overloaded
    //     in that sub class.
    // Parameters:
    //     p			a pointer to a CHA_ResponseReceiver
    //                          casted to a CHA_Model pointer
    //
    //     d                    a pointer to a CHA_ResponseBuffer
    //                          casted to a void pointer

    virtual void detachFrom(CHA_Model* model);
    // Description:
    //     The implementation of the detach method inherited from
    //     CHA_ModelClient. Is empty.
    // Parameters:
    //     model		a pointer to the calling model, which
    //				in this case is supposed to be a
    //				CHA_ResponseReceiver.

protected:
    virtual void doRouting(const CHA_ResponseBuffer* response) = 0;
    // Description:
    //     Implements the actual routing, i.e. writing to a file or a
    //     window, sending output to mail or a printer or where ever
    //     the response is supposed to go.
    // Parameters:
    //     response		the response to route

    RWTPtrDlist<CHA_ResponseReceiver> depOfList; // list of receiver ptrs
};

#endif
