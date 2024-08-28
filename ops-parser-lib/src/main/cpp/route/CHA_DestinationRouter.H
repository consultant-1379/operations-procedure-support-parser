// RCS handling
// $Id: CHA_DestinationRouter.H,v 22.0.1.1 1996/01/05 14:29:26 ehsphad Exp $

//**********************************************************************
// 
// .NAME    CHA_DestinationRouter - super class for routers
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_DestinationRouter.H 

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
//      The class CHA_DestinationRouter is a superclass for all
//      routers. A router handles the  routing to a specific
//      destination type (e.g. the mail router takes care of all
//      routing to diffferent mail addresses).

// DOCUMENT NO
//      190 89-CAA 134 1519

// AUTHOR 
//      1994-04-19 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_DestinationRouter.H,v $
//      Revision 22.0.1.1  1996/01/05 14:29:26  ehsphad
//      Changed all RWModel to CHA_Model.
//
//      Revision 24.0  1995/11/28 16:57:44  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:45:14  17:45:14  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:47:03  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:43:42  09:43:42  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:35:39  08:35:39  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:54:58  10:54:58  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:07:21  20:07:21  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:07:58  14:07:58  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:01:38  13:01:38  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:05:23  15:05:23  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:35:40  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:06:40  14:06:40  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:18:14  16:18:14  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:48:40  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:04:47  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:31:14  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:50:51  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:24:12  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:51:19  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:47:13  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:39:44  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:55:47  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  07:58:38  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.4  1994/04/29  07:13:26  ehsgrap
//      Corrected compilation fault.
//
//      Revision 1.3  1994/04/29  07:00:04  ehsgrap
//      Forward declaration of CHA_RoutingHandler.
//
//      Revision 1.2  1994/04/28  07:53:00  ehsgrap
//      Made newRoutinTarget() protected.
//
//      Revision 1.1  1994/04/25  10:59:11  cmcha
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
//      CHA_RoutingTarget, CHA_RoutingHandler

//**********************************************************************

#ifndef CHA_DESTINATIONROUTER_H
#define CHA_DESTINATIONROUTER_H

#include <CHA_LibGlobals.H>
#include <CHA_RoutingTarget.H>
#include <CHA_RoutingTarget.H>
#include <CHA_NLSCatalog.H>
#include <CHA_AddressList.H>

#include <rw/cstring.h>
#include <rw/tphdict.h>



// forward declaration
class CHA_RoutingHandler;


class CHA_DestinationRouter : public CHA_ModelClient
{
    
public:

    CHA_DestinationRouter(CHA_DestinationType destType,
			  CHA_RoutingHandler* pHandler);
    // Description:
    //     Constructor.
    // Parameters:
    //     destType	Describes to what kind of destinations this
    //                  router routes.  
    
    virtual ~CHA_DestinationRouter();
    // Description:
    //     Destructor.
    
    virtual void updateFrom(CHA_Model* p, void* d);
    // Description:
    //     Called by the AddressList class when routing information
    //     has changed.
    //
    //     Not for use in the main program!
    
    virtual void detachFrom(CHA_Model* model);
    // Description:
    //     Called by the AddressList class' destructor.
    //
    //     Not for use in the main program!
struct myHash{
    unsigned long operator()(const RWCString& s) const
    {return s.hash();}
  };
protected:

    virtual CHA_RoutingTarget* newRoutingTarget(const RWCString& addr) = 0;
    // Description:
    //     A pure virtual member function that has to be implemented
    //     in a subclass. The method shall return a pointer to a
    //     suitable routing target, e.g. in a mail router this method
    //     would return a mail target (a sub class of
    //     CHA_RoutingTarget). 
    // Parameters:
    //     addr		The address to route to.
    
    virtual void setupRoute(CHA_ResponseReceiver* respRcvr,
			    RWCString addr);
    // Description:
    //     Connects a routing taget and a response receiver.
    // Parameters:
    //     respRcvr	The response receiver.
    //     addr		The address that the routing target shall
    //                  route to.
    
    virtual void removeRoute(CHA_ResponseReceiver* respRcvr,
			     RWCString addr);
    // Description:
    //     Disconnects a routing target from a response receiver.
    // Parameters:
    //     respRcvr	The response receiver.
    //     addr		The address that the routing target was
    //                  routing to.

    CHA_RoutingHandler* pRoutingHandler;
    CHA_DestinationType destinationType;
    CHA_AddressList* pAddresses[CHA_RT_UNDEFINED + 1];
   // RWTPtrHashDictionary<RWCString, CHA_RoutingTarget> targetDict;
      RWTPtrHashMap<RWCString, CHA_RoutingTarget, myHash, std::equal_to<RWCString> > targetDict;
    CHA_NLSCatalog nlsCat;
};

#endif
