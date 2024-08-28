// RCS handling
// $Id: CHA_DestinationRouter.C,v 22.0.1.1 1996/01/05 14:29:26 ehsphad Exp $

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
//      1994-04-19 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_DestinationRouter.C,v $
//      Revision 22.0.1.1  1996/01/05 14:29:26  ehsphad
//      Changed all RWModel to CHA_Model.
//
//      Revision 24.0  1995/11/28 16:58:04  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:45:50  17:45:50  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:47:28  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:44:27  09:44:27  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:36:05  08:36:05  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:55:25  10:55:25  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:07:52  20:07:52  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:08:43  14:08:43  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  13:02:09  13:02:09  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  15:06:17  15:06:17  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:36:07  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:07:46  14:07:46  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 12.0  95/02/06  16:19:04  16:19:04  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:50:07  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:05:22  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:31:55  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:51:53  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:24:47  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:52:02  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:48:16  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:40:38  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:56:57  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  07:59:26  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.3  1994/05/10  12:33:51  ehsgrap
//      Changed a bit in the error messages.
//
//      Revision 1.2  1994/04/29  08:16:17  ehsgrap
//      Checks isExternallyRouted().
//
//      Revision 1.1  1994/04/25  10:58:50  cmcha
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

//**********************************************************************


#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_DestinationRouter.H>
#include <CHA_LibNLS.H>
#include <CHA_RoutingCase.H>
#include <CHA_RoutingHandler.H>


//**********************************************************************


//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_DestinationRouter", (char*)"C");


//**********************************************************************


/*static unsigned CHA_DestinationRouterHashFunction(const RWCString& s)
{
    return s.hash();
}*/

//**********************************************************************


CHA_DestinationRouter::CHA_DestinationRouter(CHA_DestinationType destType,
					     CHA_RoutingHandler* pHandler)
: destinationType(destType),
  pRoutingHandler(pHandler),
  targetDict(),
  nlsCat(CHA_LibNLSCatalog)
{
    ////TRACE_IN(trace, CHA_DestinationRouter, destType << ", pHandler");
    if(pHandler == NULL)
    {
	////TRACE_RETURN(trace, CHA_DestinationRouter, "no handler");
	return;
    }

    // Observe all address lists for this destination
    for(int respType = 0; respType <= CHA_RT_UNDEFINED; respType++)
    {
	CHA_RoutingCase* pRtCase =
	    pRoutingHandler->getRoutingCase((CHA_ResponseType)respType);
	if(pRtCase != NULL)
	{
	    pAddresses[respType] = pRtCase->getAddressList(destinationType);
	    if(pAddresses[respType] != NULL)
	    {
		pAddresses[respType]->addDependent(this);

		if(pRtCase->isExternallyRouted(destinationType) == FALSE)
		{
		    // Create routing targets for addresses already in the
		    // lists. There will be no loop if entries() returns 0.
		    for(int i = 0; i < pAddresses[respType]->entries(); i++)
		    {
			setupRoute(pRtCase->getResponseReceiver(),
				   (*pAddresses[respType])[i]);
		    }
		}
	    }
	}
	else
	    pAddresses[respType] = NULL;
    }
}


//**********************************************************************


CHA_DestinationRouter::~CHA_DestinationRouter()
{
    // remove dependency from all address lists != NULL
    for(int respType = 0; respType <= CHA_RT_UNDEFINED; respType++)
    {
	if(pAddresses[respType] != NULL)
	    pAddresses[respType]->removeDependent(this);
    }

    // delete all routing targets and addresses
    targetDict.clearAndDestroy();
}


//**********************************************************************


void CHA_DestinationRouter::updateFrom(CHA_Model* p, void* d)
{
    ////TRACE_IN(trace, updateFrom, p);

    // This assumes that the caller really is a CHA_AddressList.
    // If it isn't there is some major troubble somewhere.
    CHA_AddressList* pAddrList = (CHA_AddressList*) p;

    // Return quickly if routing is done externally (e.g. by EA)
    if(pAddrList->isExternallyRouted() == TRUE)
    {
	////TRACE_RETURN(trace, updateFrom, "externally routed, no action");
	return;
    }

    CHA_RoutingCase* pRoutingCase = pAddrList->getRoutingCase();
    CHA_ResponseReceiver* pRespRcvr = NULL;
    if(pRoutingCase != NULL)
	pRespRcvr = pRoutingCase->getResponseReceiver();

    // if there is no response receiver routing isn't possible
    if(pRespRcvr == NULL)
    {
	////TRACE_RETURN(trace, updateFrom, "no response receiver to route from!");
	return;
    }

    switch(pAddrList->getLastEvent())
    {
    case CHA_AddressList::ADDEDITEM:
	setupRoute(pRespRcvr, pAddrList->getChangedAddress());
	break;
    case CHA_AddressList::REMOVEDITEM:
	removeRoute(pRespRcvr, pAddrList->getChangedAddress());
	break;
    case CHA_AddressList::NOTHING:
    default:
	break;
    }
}


//**********************************************************************


void CHA_DestinationRouter::detachFrom(CHA_Model* model)
{
    // return quickly if no model is given
    if(model == NULL)
	return;

    // find the address list that it concerns and set it to NULL
    for(int respType = 0; respType <= CHA_RT_UNDEFINED; respType++)
    {
	if(pAddresses[respType] == (CHA_AddressList*) model)
	{
	    if(pAddresses[respType]->isExternallyRouted() == FALSE)
	    {
		// remove all routings from this address list

		// first get the response receiver for this response type
		CHA_ResponseReceiver* pRespRcvr = NULL;
		CHA_RoutingCase* pRoutingCase =
		    pAddresses[respType]->getRoutingCase();
		if(pRoutingCase != NULL)
		    pRespRcvr = pRoutingCase->getResponseReceiver();

		// then remove all routes
		if(pRespRcvr != NULL)
		{
		    for(int i = 0; i < pAddresses[respType]->entries(); i++)
			removeRoute(pRespRcvr, (*pAddresses[respType])[i]);
		}
	    }
	    pAddresses[respType] = NULL;
	    break;		// skip looping
	}
    }
}


//**********************************************************************


void CHA_DestinationRouter::setupRoute(CHA_ResponseReceiver* pRespRcvr,
				       RWCString addr)
{
    ////TRACE_IN(trace, setupRoute, pRespRcvr << ", " << addr);

    // If no response receiver exists, skip it
    if(pRespRcvr == NULL)
    {
	errorReporter.message(nlsCat.getMessage(NLS_ROUTE_UNABLE)
			      + addr + ". ");
	return;
    }

    // check if we have to create a routing target for this address
    CHA_RoutingTarget* pRoutingTarget = targetDict.findValue(&addr);
    if(pRoutingTarget == NULL)
    {
	////TRACE_FLOW(trace, setupRoute, "new routing target");

	pRoutingTarget = newRoutingTarget(addr); // use of virtual function
	targetDict.insertKeyAndValue(new RWCString(addr), pRoutingTarget);
    }

    // activate the actual routing
    pRoutingTarget->route(pRespRcvr);
}


//**********************************************************************


void CHA_DestinationRouter::removeRoute(CHA_ResponseReceiver* pRespRcvr,
					RWCString addr)
{
    ////TRACE_IN(trace, removeRoute, pRespRcvr << ", " << addr);

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

	// remove the routing target if necessary
	if(pRoutingTarget->nrOfReceivers() == 0)
	{
	    RWCString* pAddress = targetDict.remove(&addr);
	    delete pAddress;
	    delete pRoutingTarget;
	}
    }
}


//**********************************************************************
