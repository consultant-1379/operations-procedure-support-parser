// RCS handling
// $Id: CHA_RoutingHandler.H,v 22.0.1.1 1995/12/21 16:46:11 ehsphad Exp $

//**********************************************************************
// 
// .NAME    CHA_RoutingHandler - the general routing service
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_RoutingHandler.H

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
//      A CHA_RoutingHandler provides the routing service. It
//      instantiates one routing case for every response type and one
//      destination handler for every destination type.
//
//      To the outside world the routing handler provides means to get
//      hold of a routing case. That routing case can be read (e.g. by
//      a subscriber) or modified (e.g. by the UI). The destination
//      handlers will then adjust themselves to route according to the
//      routing case.
//
//      Before any real routing can be done all response receivers
//      MUST register themselves with the routing handler, using the
//      method setResponseReceiver(). Otherwise it will be impossible
//      for the routing service to connect routing destination with
//      response receivers.

// DOCUMENT NO
//      190 89-CAA 134 1519

// AUTHOR 
//      1994-04-18 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION
//	XM2S1
//	1995-09-07

// CHANGES
//      RCS revision history
//      $Log: CHA_RoutingHandler.H,v $
//      Revision 22.0.1.1  1995/12/21 16:46:11  ehsphad
//      Added Instance of CHA_ResponseFwdReceiver
//
//      Revision 23.0  1995/09/07 17:45:36  ehscama
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:47:19  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:44:11  09:44:11  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:35:55  08:35:55  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:55:15  10:55:15  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:07:41  20:07:41  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:08:29  14:08:29  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:01:59  13:01:59  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:05:58  15:05:58  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:35:57  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:07:16  14:07:16  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:18:46  16:18:46  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:49:26  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:05:09  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:31:40  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:51:37  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:24:35  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:51:47  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:47:52  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:40:19  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:56:34  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  07:59:08  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.5  1994/06/10  16:56:40  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.4  1994/06/08  13:33:24  ehsgrap
//      Moved some #include statements from .H to .C file.
//
//      Revision 1.3  1994/04/29  08:18:09  ehsgrap
//      Replaced fwd decl of CHA_DestinationRouter with include.
//
//      Revision 1.2  1994/04/26  14:51:36  ehsgrap
//      Added getRouter() method.
//
//      Revision 1.1  1994/04/25  10:59:11  cmcha
//      Initial revision
//
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
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
//      CHA_RoutingCase

//**********************************************************************

#ifndef CHA_ROUTINGHANDLER_H
#define CHA_ROUTINGHANDLER_H


#include <CHA_LibGlobals.H>
#include <CHA_RoutingCase.H>
#include <CHA_ResponseReceiver.H>
#include <CHA_ResponseFwdReceiver.H>
#include <CHA_DestinationRouter.H>
#include <CHA_MailRouter.H>
#include <CHA_PrinterRouter.H>
#include <CHA_FileRouter.H>
#include <CHA_WindowRouter.H>


class CHA_RoutingHandler
{    
public:
    CHA_RoutingHandler();
    // Description:
    //     Constructor.

    ~CHA_RoutingHandler();
    // Description:
    //     Destructor.

    CHA_RoutingCase* getRoutingCase(CHA_ResponseType respType);
    // Description:
    //     To get hold of the routing case for a particular response
    //     type. 
    // Parameters:
    //     respType		One of the response types mentioned in
    //                          the enum CHA_ResponseType in the file
    //                          CHA_LibGlobals.H. 
    // Return values:
    //     A pointer to the routing case.

    CHA_DestinationRouter* getRouter(CHA_DestinationType destType);
    // Description:
    //     To get hold of the router for a particular destination
    //     type. 
    // Parameters:
    //     destType		One of the destination types mentioned in
    //                          the enum CHA_DestinationType in the file
    //                          CHA_LibGlobals.H. 
    // Return values:
    //     A pointer to the routing case.

  void setRespReceiver(CHA_ResponseType responseType,
		       CHA_ResponseReceiver* pReceiver);
  // Description:
  //     To set the response receiver of a particular response type.
  //     Must be set before any real routing can be done by the
  //     routing service.
  // Parameters:
  //     responseType		One of the response types mentioned in
  //                          the enum CHA_ResponseType in the file
  //                          CHA_LibGlobals.H. 
  //     pReceiver		A poiner to the receiver that receives
  //                          responses of the type given.
  
private:
  CHA_RoutingCase routingCase[CHA_RT_UNDEFINED + 1];
  CHA_DestinationRouter* router[CHA_DT_UNDEFINED + 1];
  CHA_ResponseFwdReceiver* receiver[CHA_RT_UNDEFINED + 1];
};

#endif
