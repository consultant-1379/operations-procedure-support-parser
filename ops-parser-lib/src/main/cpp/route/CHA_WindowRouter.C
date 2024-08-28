// RCS handling
// $Id: CHA_WindowRouter.C,v 24.0 1995/11/28 16:58:19 ehsgrap Rel $

//**********************************************************************

// COPYRIGHT
//      COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1994
//
//      The Copyright to the computer program(s) herein is the
//      property of Ericsson Hewlett-Packard Telecommunications AB,
//      Sweden.  The program(s) may be used and/or copied with the
//      written permission from Ericsson Hewlett-Packard
//      Telecommunications AB or in accordance with the terms and
//      conditions stipulated in the agreement/contract under which
//      the program(s) have been supplied.

// DOCUMENT NO
//	190 89-CAA 134 1519

// AUTHOR
//      1994-05-10 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_WindowRouter.C,v $
//      Revision 24.0  1995/11/28 16:58:19  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:46:14  17:46:14  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:47:45  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:44:58  09:44:58  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:36:23  08:36:23  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:55:45  10:55:45  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:08:15  20:08:15  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:09:17  14:09:17  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  13:02:31  13:02:31  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  15:06:56  15:06:56  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:36:25  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:08:17  14:08:17  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 12.0  95/02/06  16:19:37  16:19:37  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:51:05  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:05:54  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:32:27  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:52:35  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:25:10  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:52:29  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:49:06  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:41:23  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:57:39  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:00:00  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.2  1994/06/10  16:57:21  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.1  1994/05/18  08:31:04  ehsgrap
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

//**********************************************************************


#include <CHA_WindowRouter.H>
#include <CHA_LibGlobals.H>
#include <CHA_LibNLS.H>
#include <CHA_Trace.H>


//**********************************************************************


//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_WindowRouter", (char*)"C");


//**********************************************************************


CHA_WindowRouter::CHA_WindowRouter(CHA_RoutingHandler* pRtHandler)
: CHA_DestinationRouter(CHA_DT_WINDOW, pRtHandler)
{
    //TRACE_IN(trace, CHA_WindowRouter, pRtHandler);
}


//**********************************************************************


CHA_WindowTarget* CHA_WindowRouter::getTarget(const RWCString& addr)
{
    //TRACE_IN(trace, getTarget, addr);

    // find the routing target for this address
    RWCString tmpAddr = addr;
    CHA_RoutingTarget* pRoutingTarget = targetDict.findValue(&tmpAddr);
    if(pRoutingTarget == NULL)
    {
	//TRACE_FLOW(trace, getTarget, "new routing target");

	pRoutingTarget = newRoutingTarget(addr); // use of virtual function
	targetDict.insertKeyAndValue(new RWCString(addr), pRoutingTarget);
    }

    return (CHA_WindowTarget*) pRoutingTarget;
}


//**********************************************************************


CHA_RoutingTarget* CHA_WindowRouter::newRoutingTarget(const RWCString& addr)
{
    //TRACE_RETURN(trace, newRoutingTarget, addr);
    return new CHA_WindowTarget();
}


//**********************************************************************


void CHA_WindowRouter::removeRoute(CHA_ResponseReceiver* pRespRcvr,
				   RWCString addr)
{
    //TRACE_IN(trace, removeRoute, pRespRcvr << ", " << addr);

    // If no response receiver exists, we don't know what to remove
    if(pRespRcvr == NULL)
    {
	errorReporter.message(nlsCat.getMessage(NLS_UNROUTE_UNABLE)
			      + addr + ". ");
	return;
    }

    // find the routing target for this address
    CHA_RoutingTarget* pRoutingTarget = targetDict.findValue(&addr);
    if(pRoutingTarget != NULL)
    {
	// deactivate the routing
	pRoutingTarget->dontRoute(pRespRcvr);
    }
}


//**********************************************************************

