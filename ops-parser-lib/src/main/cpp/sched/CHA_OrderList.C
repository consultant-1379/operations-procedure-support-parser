// RCS handling
// $Id: CHA_OrderList.C,v 24.0 1995/11/28 16:59:30 ehsgrap Rel $

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
//	190 89-CAA 134 1516

// AUTHOR
//      1994-06-20 by EHS / Marie Moschna (qhsmosc@ehs.ericsson.se)

// REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_OrderList.C,v $
//      Revision 24.0  1995/11/28 16:59:30  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:47:43  17:47:43  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:48:58  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:46:11  09:46:11  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:37:39  08:37:39  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:56:52  10:56:52  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:09:30  20:09:30  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:11:15  14:11:15  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  13:03:49  13:03:49  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  15:09:10  15:09:10  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:37:29  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:10:31  14:10:31  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 12.0  95/02/06  16:20:36  16:20:36  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:52:03  cmcha
//      Made release PREIT, N L\ufffdnninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:06:39  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:33:33  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:54:06  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:26:21  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.1  1994/09/08  10:45:07  qhsmosc
//      Removed function UpdateList
//
//      Revision 6.0  1994/08/30  17:53:28  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.1  1994/08/26  10:15:16  qhsmosc
//      Working version
//
//      Revision 5.0  1994/08/16  07:50:55  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.1  1994/08/10  06:43:25  qhsmosc
//      Back to hierarchy
//
//      Revision 1.1  1994/07/05  07:43:50  qhsmosc
//      Initial revision
//
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	TB53_OZ 1995-11-28      J Grape (EHSGRAP)       RCS rev 24.0
//	XM2S1   1995-09-07      ehscama                 RCS rev 23.0
//	EC2_OZ  1995-08-01      Jan Sandquist (EHSJAASA)RCS rev 22.0
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
//	PREIT   1995-01-18      N L\ufffdnninge (XKKNICL)    RCS rev 11.0
//	TB2     1994-12-22      J Grape (EHSGRAP)       RCS rev 10.0
//	E       1994-10-24      ehscama                 RCS rev 9.0
//	D       1994-10-05      EHSCAMA                 RCS rev 8.0
//	R1C     1994-09-22      J Grape (EHSGRAP)       RCS rev 7.0
//	R1B     1994-08-30      J Grape (EHSGRAP)       RCS rev 6.0
//	R1A     1994-08-16      J Grape (EHSGRAP)       RCS rev 5.0

// SEE ALSO
//      RWTValOrderedVector
//      CHA_SubscList
//      CHA_ExecOrderList
//      CHA_Order

//**********************************************************************

#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_OrderList.H>
#include <pwd.h>
//#include <sysent.h>

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_OrderList", (char*)"C");

// Member functions, constructors, destructors, operators

//**********************************************************************

CHA_OrderList::CHA_OrderList()
: lastEvent(CHA_OrderList::NOTHING)
{
    //TRACE_IN(trace, CHA_OrderList, "");
};

//**********************************************************************

CHA_OrderList::~CHA_OrderList()
{
    orderList.clearAndDestroy();
};

//**********************************************************************

CHA_Order* CHA_OrderList::operator()(size_t i)
{
    //TRACE_IN(trace, operator(), "");

    return orderList[i];
};

//**********************************************************************

CHA_Order* CHA_OrderList::operator()(size_t i) const
{
    //TRACE_IN(trace, operator()const, "");

    return orderList[i];
};

//**********************************************************************

size_t CHA_OrderList::entries() const
{
    //TRACE_IN(trace, entries, "");

    return orderList.entries();
};

//**********************************************************************

RWBoolean CHA_OrderList::isEmpty() const
{
    //TRACE_IN(trace, isEmpty, "");

    return orderList.isEmpty();
};


//**********************************************************************

CHA_OrderList::Event CHA_OrderList::getLastEvent() const
{
    //TRACE_IN(trace, getLastEvent, "");

    return lastEvent;
};

//**********************************************************************

const CHA_Order& CHA_OrderList::getChangedOrder() const
{
    //TRACE_IN(trace, getChangedOrder, "");

    return changedOrder;
};

//**********************************************************************

void CHA_OrderList::announceEvent(CHA_OrderList::Event evt,
				  const CHA_Order& Order)
{
    //TRACE_IN(trace, announceEvent, evt << ", " << Order.getOrderId());

    lastEvent = evt;
    changedOrder = Order;
    changed();
};


//**********************************************************************
// Functions that should be defined in subclasses
//**********************************************************************

int CHA_OrderList::CreateList()
{
    return 1;
};
//TORF-241666
/* int CHA_OrderList::UpdateList()
{
   return 1;
}; */

int CHA_OrderList::AddOrder (CHA_Order * s)
{
    return 1;
};

int CHA_OrderList::RemoveOrder (const long orderId)
{
    return 1;
};

int CHA_OrderList::ChangeOrder (const long orderId)
{
    return 1;
};

int CHA_OrderList::ActivateOrder (const long orderId)
{
    return 1;
};

int CHA_OrderList::SuspendOrder (const long orderId)
{
    return 1;
};
