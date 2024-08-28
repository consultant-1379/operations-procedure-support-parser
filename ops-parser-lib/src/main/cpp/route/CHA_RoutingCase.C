// RCS handling
// $Id: CHA_RoutingCase.C,v 24.0 1995/11/28 16:58:15 ehsgrap Rel $

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
//      1994-04-18 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_RoutingCase.C,v $
//      Revision 24.0  1995/11/28 16:58:15  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:46:09  17:46:09  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:47:42  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:44:52  09:44:52  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:36:20  08:36:20  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:55:41  10:55:41  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:08:10  20:08:10  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:09:10  14:09:10  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  13:02:26  13:02:26  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  15:06:47  15:06:47  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:36:21  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:08:11  14:08:11  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 12.0  95/02/06  16:19:31  16:19:31  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:51:00  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:05:49  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:32:18  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:52:24  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:25:06  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:52:24  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.1  1994/08/22  10:59:19  ehsgrap
//      Addedd const version of getAddresList
//
//      Revision 5.0  1994/08/16  07:48:57  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:41:12  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:57:30  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  07:59:53  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.3  1994/06/10  16:56:22  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.2  1994/04/26  14:51:00  ehsgrap
//      changed "" to <>
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


#include <CHA_Trace.H>
#include <CHA_RoutingCase.H>


//**********************************************************************


//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_RoutingCase", (char*)"C");


//**********************************************************************


CHA_RoutingCase::CHA_RoutingCase(CHA_ResponseType responseType,
				 CHA_ResponseReceiver* responseReceiver)
: respType(responseType),
  pRespRcvr(responseReceiver)
{
    for(int i = 0; i <= CHA_DT_UNDEFINED; i++)
    {
	addresses[i].setDestinationType((CHA_DestinationType)i);
	addresses[i].setRoutingCase(this);
    }
}


//**********************************************************************


CHA_RoutingCase::CHA_RoutingCase(const CHA_RoutingCase& other)
: respType(other.respType),
  pRespRcvr(other.pRespRcvr)
{
    for(int i = 0; i <= CHA_DT_UNDEFINED; i++)
    {
	addresses[i] = other.addresses[i];
	addresses[i].setRoutingCase(this);
    }
}


//**********************************************************************


CHA_RoutingCase& CHA_RoutingCase::operator=(const CHA_RoutingCase& other)
{
    //TRACE_IN(trace, operator=, "other");

    respType = other.respType;
    pRespRcvr = other.pRespRcvr;
    for(int i = 0; i <= CHA_DT_UNDEFINED; i++)
    {
	addresses[i] = other.addresses[i];
	addresses[i].setRoutingCase(this);
    }

    return *this;
}


//**********************************************************************


CHA_RoutingCase::~CHA_RoutingCase()
{
    // empty
}


//**********************************************************************


CHA_AddressList* CHA_RoutingCase::getAddressList(CHA_DestinationType destination)
{
    return &addresses[destination];
}


//**********************************************************************


const CHA_AddressList* CHA_RoutingCase::getAddressList(CHA_DestinationType destination) const
{
    //TRACE_RETURN(trace, getAddressList, "const version");
    return &addresses[destination];
}


//**********************************************************************


RWBoolean CHA_RoutingCase::isExternallyRouted(CHA_DestinationType destination) const
{
    /*TRACE_RETURN(trace, isExternallyRouted,
		 destination << ": "
		 << addresses[destination].isExternallyRouted());*/
    return addresses[destination].isExternallyRouted();
}


//**********************************************************************


void CHA_RoutingCase::setExternallyRouted(CHA_DestinationType destination,
					  RWBoolean on)
{
    addresses[destination].setExternallyRouted(on);
}


//**********************************************************************


CHA_ResponseType CHA_RoutingCase::getResponseType() const
{
    return respType;
}


//**********************************************************************


CHA_ResponseReceiver* CHA_RoutingCase::getResponseReceiver() const
{
    return pRespRcvr;
}


//**********************************************************************


void CHA_RoutingCase::setResponseType(CHA_ResponseType responseType)
{
    respType = responseType;
}


//**********************************************************************


void CHA_RoutingCase::setResponseReceiver(CHA_ResponseReceiver* pReceiver)
{
    pRespRcvr = pReceiver;
}


//**********************************************************************
