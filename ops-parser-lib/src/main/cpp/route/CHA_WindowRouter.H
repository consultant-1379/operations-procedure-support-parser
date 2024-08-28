// RCS handling
// $Id: CHA_WindowRouter.H,v 24.0 1995/11/28 16:57:59 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_WindowRouter - routes responses to window
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_WindowRouter.H

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
//      A CHA_WindowRouter is a specialized CHA_DestinationRouter that
//      set up response routes to window.
//
//      When routing to a new window is setup a CHA_WindowTarget is
//      created. The window target can be observed by the UI
//      (preferably a window widget) in order to get responses to
//      display. The window target collects responses from several
//      response receivers and supplies them to the UI.
//
//      Unlike the default behavior of a router the CHA_WindowRouter
//      doesn't destroy routing targets that are not currently used,
//      i.e. a window target will not be destryed once created just
//      because no responses are routed to it. However all window
//      targets will be destroyed in the destructor of the
//      CHA_WindowRouter. 

// DOCUMENT NO
//      190 89-CAA 134 1519

// AUTHOR 
//      1994-05-10 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_WindowRouter.H,v $
//      Revision 24.0  1995/11/28 16:57:59  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:45:39  17:45:39  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:47:21  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:44:14  09:44:14  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:35:57  08:35:57  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:55:18  10:55:18  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:07:43  20:07:43  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:08:32  14:08:32  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:02:01  13:02:01  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:06:02  15:06:02  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:35:59  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:07:27  14:07:27  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:18:50  16:18:50  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:49:50  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:05:11  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:31:43  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:51:42  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:24:38  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:51:49  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:47:57  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:40:23  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:56:40  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  07:59:13  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.2  1994/06/10  16:57:26  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.1  1994/05/18  08:31:21  ehsgrap
//      Initial version.
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
//      CHA_DestinationRouter, CHA_WindowTarget, CHA_ResponseReceiver

//**********************************************************************

#ifndef CHA_WINDOWROUTER_H
#define CHA_WINDOWROUTER_H


#include <CHA_DestinationRouter.H>
#include <CHA_WindowTarget.H>


class CHA_WindowRouter : public CHA_DestinationRouter
{
public:
    CHA_WindowRouter(CHA_RoutingHandler* pRtHandler);
    // Description:
    //     Constructor.
    // Parameters:
    //     pRtHandler	a pointer to a routing handler

    CHA_WindowTarget* getTarget(const RWCString& windowName);
    // Description:
    //     To get the routing target that handles routing to specified
    //     window name.
    //
    //     If no routing target exists for the window name give it is
    //     created.
    // Parameters:
    //     windowName	the name of the window (a.k.a. the address, in
    //                  other routers).
    // Return value:
    //     A pointer to a valid CHA_WindowTarget object that can be
    //     observed by the UI for text to display. If the creation of
    //     the window target fails NULL is returned.

protected:
    
    virtual CHA_RoutingTarget* newRoutingTarget(const RWCString& addr);
    // Description:
    //     It's required by CHA_DestinationRouter that this method is
    //     implemented. It returns a pointer to a window routing target.
    // Return value:
    //     A pointer to a newly created CHA_WindowTarget object
    //     disguised as a CHA_RoutingTarget pointer. CHA_RoutingTarget
    //     is a super classs of CHA_WindowTarget.

    virtual void removeRoute(CHA_ResponseReceiver* pRespRcvr,
			     RWCString addr);
    // Description:
    //     Overloading of corresponding function in super class.
    //
    //     Disconnects a routing target from a response receiver
    //     without deleting it.
    // Parameters:
    //     pRespRcvr	The response receiver.
    //     addr		The address that the routing target was
    //                  routing to.
};

#endif
