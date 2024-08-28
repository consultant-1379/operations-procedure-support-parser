// RCS handling
// $Id: CHA_Order.C,v 22.0.1.1 1996/03/13 11:19:36 cmcha Exp $

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
//      $Log: CHA_Order.C,v $
//      Revision 22.0.1.1  1996/03/13 11:19:36  cmcha
//      Branch for POW
//
//      Revision 24.0  95/11/28  16:59:27  16:59:27  ehsgrap (Jan Grape (9 9073) VK/EHS/VE)
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:47:40  17:47:40  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:48:56  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:46:09  09:46:09  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:37:37  08:37:37  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:56:49  10:56:49  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:09:27  20:09:27  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:11:12  14:11:12  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  13:03:46  13:03:46  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  15:09:05  15:09:05  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.1  1995/02/27  13:28:53  epatse
//      fixed memory leak.
//
//      Revision 14.0  1995/02/25  16:37:27  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.6  95/02/16  15:59:20  15:59:20  qhskred (Krister Eklund VK/EHS/PXE)
//      Added support for CHA_OztCmdFileOrder
//
//      Revision 13.5  1995/02/15  14:10:27  cmcha
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 9.2  95/02/08  12:47:46  12:47:46  qhsmosc (Marie Moschna VK/EHS/PXE)
//      rewrite after TAS change
//
//      Revision 9.1  1994/11/15  07:50:34  qhsmosc
//      Added definition of static variable
//
//      Revision 9.0  1994/10/24  21:33:31  cmcha
//      Made release E, ehscama.
//
//      Revision 8.1  1994/10/13  19:34:23  ehsgrap
//      Increased const corectness.
//
//      Revision 8.0  1994/10/05  08:54:03  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:26:13  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.2  1994/09/15  14:33:09  qhsmosc
//      Sort implemented
//
//      Revision 6.1  1994/09/08  10:32:27  qhsmosc
//      Preliminary UI tests ready
//
//      Revision 6.0  1994/08/30  17:53:25  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:50:49  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.2  1994/08/16  06:51:12  qhsmosc
//      Before freeze, testing remaining
//
//      Revision 4.1  1994/08/10  06:55:44  qhsmosc
//      Back to hierarchy
//
//      Revision 1.2  1994/07/12  06:46:35  qhsmosc
//      Preliminary tests OK
//
//      Revision 1.1  1994/07/05  07:43:50  qhsmosc
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
//	E       1994-10-24      ehscama                 RCS rev 9.0
//	D       1994-10-05      EHSCAMA                 RCS rev 8.0
//	R1C     1994-09-22      J Grape (EHSGRAP)       RCS rev 7.0
//	R1B     1994-08-30      J Grape (EHSGRAP)       RCS rev 6.0
//	R1A     1994-08-16      J Grape (EHSGRAP)       RCS rev 5.0

// SEE ALSO
//      CHA_OrderList
//      CHA_CommandFileOrder
//      CHA_SystemFileOrder
//      CHA_Subsc

//**********************************************************************

#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_Order.H>
#include <CHA_Converter.H>
#include <pwd.h>
#include <unistd.h> // gethostname on HP
//#include <sysent.h> // gethostname on SUN

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_Order", (char*)"C");

//const int MAXHOSTNAMELEN = 64;

// Member functions, constructors, destructors, operators

CHA_SortOrder CHA_Order::sortOrder=CHA_SORT_ORDERNR;

//**********************************************************************

CHA_Order::CHA_Order()
:state(CHA_ORDER_SCHEDULED),
 name(),
 orderId(0),
 interval(),
 host(),
 tasId(0),
 timestamp(0,0,0),
 startTime(0,0,0)
{

    ////TRACE_IN(trace, CHA_Order, "");

    char* cha_hostname = NULL;
    cha_hostname = new char[64];
    gethostname(cha_hostname, 64);
    host = cha_hostname;
    delete [] cha_hostname; cha_hostname = NULL;

    ////TRACE_FLOW(trace,CHA_Order,host);
    ////TRACE_RETURN(trace,CHA_Order,"");

};

//**********************************************************************

CHA_Order::CHA_Order(const CHA_Order& order)
{
    ////TRACE_IN(trace, CHA_Order-Copy, "");

    // Copy constructor

    state = order.state;
    name = order.name;
    orderId = order.orderId;
    kind    = order.kind;

    host      = order.host;

    tasId     = order.tasId;
    timestamp = order.timestamp;
    startTime = order.startTime;

    interval = order.interval;
};

//**********************************************************************

CHA_Order::~CHA_Order()
{
};

//**********************************************************************

int CHA_Order::activate()
{
    int  answer;
    CHA_Converter converter;

    //TRACE_IN(trace, Activate, "");

    answer = converter.activate(*this);
    if (answer == AM_DB_OK)
	state = CHA_ORDER_SCHEDULED;

    return answer;
};

//**********************************************************************

int CHA_Order::suspend()
{
    int  answer;
    CHA_Converter converter;

    //TRACE_IN(trace, Suspend, "");

    answer = converter.suspend(*this);
    if (answer == AM_DB_OK)
	state = CHA_ORDER_CANCELLED;

    return answer;
};

//**********************************************************************

int CHA_Order::fetch(const long ordId)
{
    int  answer;
    CHA_Converter converter;

    //TRACE_IN(trace, fetch, ordId);

    orderId = ordId;
    answer = converter.fetchOrder(ordId, *this);
    return answer;
};

//**********************************************************************

int CHA_Order::store()
{
    int  answer;
    CHA_Converter converter;

    //TRACE_IN(trace, store, "");

    answer = converter.storeOrder(*this);
    return answer;
};

//**********************************************************************

int CHA_Order::remove()
{
    int answer = 1;
    CHA_Converter converter;

    //TRACE_IN(trace, remove, "");

    answer = converter.removeOrder(orderId);
    return answer;
};

//**********************************************************************

const CHA_OrderState& CHA_Order::getState() const
{
    //TRACE_IN(trace, getState, "");

    return state;
};

//**********************************************************************

void CHA_Order::setState(CHA_OrderState stateIn)
{
    //TRACE_IN(trace, setState, stateIn);

    state = stateIn;
};

//**********************************************************************

const CHA_OrderKind& CHA_Order::getOrderKind() const
{
    //TRACE_IN(trace, getOrderKind, "");

    return kind;
};

//**********************************************************************

void CHA_Order::setName(const RWCString& nameIn)
{
    //TRACE_IN(trace, setName, nameIn);

    name = nameIn;
};

//**********************************************************************

const RWCString& CHA_Order::getName() const
{
    //TRACE_IN(trace, getName, "");

    return name;
};

//**********************************************************************

const long CHA_Order::getOrderId() const
{
    //TRACE_IN(trace, getOrderId, "");

    return orderId;
};

//**********************************************************************

void CHA_Order::setOrderId(const long & ordId)
{
    //TRACE_IN(trace, setOrderId, ordId);

    orderId = ordId;
};

//**********************************************************************

void CHA_Order::setHost(const RWCString& hostIn)
{
    //TRACE_IN(trace, setHost, hostIn);

    host = hostIn;
};

//**********************************************************************

const RWCString& CHA_Order::getHost() const
{
    //TRACE_IN(trace, getHost, "");

    return host;
};

//**********************************************************************


void CHA_Order::setTasId(const int tasIdIn)
{
    //TRACE_IN(trace, setTasId, tasIdIn);

    tasId = tasIdIn;
};

//**********************************************************************

const int CHA_Order::getTasId() const
{
    //TRACE_IN(trace, getTasId, "");

    return tasId;
};

//**********************************************************************

void CHA_Order::setTimestamp(const RWDateTime& timestampIn)
{
    //TRACE_IN(trace, setTimestamp, timestampIn);

    timestamp = timestampIn;
};

//**********************************************************************

void CHA_Order::setStartTime(const RWDateTime& startTimeIn)
{
    //TRACE_IN(trace, setStartTime, startTimeIn);

    startTime = startTimeIn;
};

//**********************************************************************

const RWDateTime& CHA_Order::getTimestamp() const
{
    //TRACE_IN(trace, getTimestamp, "");

    return timestamp;
};

//**********************************************************************

const RWDateTime& CHA_Order::getStartTime() const
{
    //TRACE_IN(trace, getStartTime, "");

    return startTime;
};

//**********************************************************************

CHA_Order& CHA_Order::operator=(const CHA_Order& order)
{
    //TRACE_IN(trace, operator=, "");

    state          = order.getState();
    orderId        = order.getOrderId();
    name           = order.getName();
    kind           = order.getOrderKind();

    host           = order.getHost();
    tasId          = order.getTasId();
    timestamp      = order.getTimestamp();
    startTime 	   = order.getStartTime();

    interval       = order.getInterval();

    return *this;

};

//**********************************************************************

int CHA_Order::operator==(const CHA_Order& order) const
{
    //TRACE_IN(trace, operator==, "");

    if (orderId != order.getOrderId())
	return FALSE;

    if (kind != order.getOrderKind())
	return FALSE;

    if (name != order.getName())
	return FALSE;

    if (state != order.getState())
	return FALSE;

    if (host != order.getHost())
	return FALSE;

    if (tasId != order.getTasId())
	return FALSE;

    if (timestamp != order.getTimestamp())
	return FALSE;

    if (startTime != order.getStartTime())
	return FALSE;

    return TRUE;
};

//**********************************************************************

int CHA_Order::operator<(const CHA_Order& order) const
{
    //TRACE_IN(trace, operator<, "");
    //TRACE_FLOW(trace, ThisOrderId, orderId);
    //TRACE_FLOW(trace, OrderIdIn, order.getOrderId());

    if (orderId < order.getOrderId())
	return TRUE;
    else
	if (orderId > order.getOrderId())
	    return FALSE;

    if (kind < order.getOrderKind())
	return TRUE;
    else
	if (kind > order.getOrderKind())
	    return FALSE;

    if (name < order.getName())
	return TRUE;
    else
	if (name > order.getName())
	    return FALSE;

    if (state < order.getState())
	return TRUE;
    else
	if (state > order.getState())
	    return FALSE;

    if (host < order.getHost())
	return TRUE;
    else
	if (host > order.getHost())
	    return FALSE;

    if (tasId < order.getTasId())
	return TRUE;
    else
	if (tasId > order.getTasId())
	    return FALSE;

    if (timestamp < order.getTimestamp())
	return TRUE;
    else
	if (timestamp > order.getTimestamp())
	    return FALSE;

    if (startTime < order.getStartTime())
	return TRUE;
    else
	if (startTime > order.getStartTime())
	    return FALSE;

    return FALSE;

};

//**********************************************************************

void CHA_Order::setSortOrder(const CHA_SortOrder sortOrderIn)
{
    //TRACE_IN(trace, setSortOrder, sortOrderIn);

    sortOrder = sortOrderIn;
};

//**********************************************************************

void CHA_Order::setInterval(const CHA_ExecOrderInterval& s)
{
    //TRACE_IN(trace, setInterval, "");
    interval = s;
};

//**********************************************************************

const CHA_ExecOrderInterval& CHA_Order::getInterval() const
{
    //TRACE_IN(trace, getInterval,"");
    return interval;
};


