// RCS handling
// $Id: CHA_RoutingCase.H,v 24.0 1995/11/28 16:57:56 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_RoutingCase - a routing case
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_RoutingCase.H

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
//      A CHA_RoutingCase holds the information about to which
//      destinations a certain response type shall go an wether this
//      routing is supposed to be done by the application or
//      externally.
//
//      Basically a routing case consists of one list of
//      addresses/destinations (a CHA_AddressList) for every
//      destination type (CHA_DestinationType). 

// DOCUMENT NO
//      190 89-CAA 134 1519

// AUTHOR 
//      1994-04-18 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_RoutingCase.H,v $
//      Revision 24.0  1995/11/28 16:57:56  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:45:34  17:45:34  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:47:17  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:44:08  09:44:08  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:35:53  08:35:53  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:55:13  10:55:13  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:07:39  20:07:39  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:08:27  14:08:27  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:01:57  13:01:57  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:05:54  15:05:54  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:35:55  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:07:13  14:07:13  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:18:43  16:18:43  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:49:23  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:05:06  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:31:37  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:51:31  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:24:33  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:51:43  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.1  1994/08/22  10:59:30  ehsgrap
//      Addedd const version of getAddresList
//
//      Revision 5.0  1994/08/16  07:47:48  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:40:14  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:56:28  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  07:59:04  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.3  1994/06/10  16:56:30  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.2  1994/04/26  14:50:27  ehsgrap
//      changed "" to <>
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
//      CHA_RoutingHandler, CHA_AddressList

//**********************************************************************

#ifndef CHA_ROUTINGCASE_H
#define CHA_ROUTINGCASE_H


#include <CHA_LibGlobals.H>
#include <CHA_ResponseReceiver.H>
#include <CHA_AddressList.H>


class CHA_RoutingHandler;


class CHA_RoutingCase
{
    friend class CHA_RoutingHandler;
    
public:

    CHA_RoutingCase(CHA_ResponseType responseType = CHA_RT_UNDEFINED,
		    CHA_ResponseReceiver* responseReceiver = NULL);
    // Description:
    //     Constructor.
    // Parameters:
    //     responseType		The type of response this routing case
    //                          concerns.
    //     responseReceiver	A pointer to the response receiver
    //                          that receives responses of the
    //                          concerned kind. Can be omitted or set
    //                          to NULL if no response receiver is
    //                          availabel (e.g. if all routing is done
    //                          externally ). If a response receiver
    //                          is given the type of responses it
    //                          receives MUST match the given response
    //                          type. 

    CHA_RoutingCase(const CHA_RoutingCase& other);
    // Description:
    //     Copy constructor.
    // Parameters:
    //     other		The routing case to copy.

    virtual CHA_RoutingCase& operator=(const CHA_RoutingCase& other);
    // Description:
    //     Assignment operator.
    // Parameters:
    //     other		The routing case to copy.

    virtual ~CHA_RoutingCase();
    // Description:
    //     Destructor. If a response receiver was given in the
    //     constructor, nothing will happen to it after this. The
    //     response receiver must be deleted outside this class.
    
    virtual CHA_AddressList* getAddressList(CHA_DestinationType destination);
    virtual const CHA_AddressList* getAddressList(CHA_DestinationType destination) const;
    // Description:
    //     To get the list of addresses for a particular destination
    //     type where the responses of this routing case's response
    //     type is routed.
    //
    //     E.g. getAddressList(CHA_DT_MAIL) gives a list of mail
    //     addresses where responses of this routing case's type (e.g.
    //     CHA_RT_IMMEDIATE) is sent.
    // Parameters:
    //     destination		one of the destinations mentioned in
    //                          the enum CHA_DestinationType in the
    //                          file CHA_LibGlobals.H.
    // Return values:
    //     a ponter to a list of destination addresses.

    virtual RWBoolean isExternallyRouted(CHA_DestinationType destination) const;
    // Description:
    //     Tells wether responses to this particular destination type
    //     is routed by another application (externally), e.g. the
    //     subscription mechanism in EA.
    // Parameters:
    //     destination		one of the destinations mentioned in
    //                          the enum CHA_DestinationType in the
    //                          file CHA_LibGlobals.H.
    // Return values:
    //     TRUE			routing is done externally
    //     FALSE		routing shall be done by this application

    virtual void setExternallyRouted(CHA_DestinationType destination,
				     RWBoolean on);
    // Description:
    //     Sets wether responses to this particular destination type
    //     is routed by another application (externally), e.g. the
    //     subscription mechanism in EA.
    // Parameters:
    //     destination		one of the destinations mentioned in
    //                          the enum CHA_DestinationType in the
    //                          file CHA_LibGlobals.H.
    //     on			if TRUE, external routing is assumed.

    virtual CHA_ResponseType getResponseType() const;
    // Description:
    //     To find out which response type this routing case concerns. 
    // Return values:
    //     One of the response types mentioned in the enum
    //     CHA_ResponseType in the file CHA_LibGlobals.H.

    virtual CHA_ResponseReceiver* getResponseReceiver() const;
    // Description:
    //     To get the response receiver that receives responses that
    //     are routed according to this routing case.
    // Return values:
    //     A pointer to a response receiver orn NULL if the receiver
    //     was not given in the constructon.

protected:

    virtual void setResponseType(CHA_ResponseType responseType);
    // Description:
    //     To set the response type this routing case concerns.
    //     Used by the class CHA_RoutingHandler.
    // Parameters:
    //     responseType		One of the response types mentioned in
    //                          the enum CHA_ResponseType in the file
    //                          CHA_LibGlobals.H. 

    virtual void setResponseReceiver(CHA_ResponseReceiver* pReceiver);
    // Description:
    //     To set the response receiver that receives responses that
    //     are routed according to this routing case.
    //     Used by the class CHA_RoutingHandler.
    // Parameters:
    //    pReceiver		a pointer to a CHA_ResponseReceiver

    CHA_ResponseType respType;
    CHA_ResponseReceiver* pRespRcvr;
    CHA_AddressList addresses[CHA_DT_UNDEFINED + 1];
};
 
#endif
