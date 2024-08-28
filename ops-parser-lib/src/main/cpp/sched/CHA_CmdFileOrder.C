// RCS handling
// $Id: CHA_CmdFileOrder.C,v 24.0 1995/11/28 16:59:15 ehsgrap Rel $

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
//      $Log: CHA_CmdFileOrder.C,v $
//      Revision 24.0  1995/11/28 16:59:15  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:47:24  17:47:24  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:48:45  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:46:00  09:46:00  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:37:21  08:37:21  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:56:36  10:56:36  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:09:14  20:09:14  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:10:48  14:10:48  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  13:03:32  13:03:32  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  15:08:45  15:08:45  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:37:16  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.6  95/02/16  16:01:07  16:01:07  qhskred (Krister Eklund VK/EHS/PXE)
//      Removed OZTLabel, OZTDisplay and ELB
//
//      Revision 13.5  1995/02/15  14:10:04  cmcha
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 9.2  95/02/09  12:15:39  12:15:39  xkknicl (Nicolas Laenninge VK/EHS/PXE)
//      now uses CHA_UserInfo object to retrieve "login name"
//
//      Revision 9.1  1995/02/08  12:48:58  qhsmosc
//      rewrite after TAS change
//
//      Revision 9.0  1994/10/24  21:33:14  cmcha
//      Made release E, ehscama.
//
//      Revision 8.3  1994/10/24  19:16:59  ehscama
//      Added const on operator== and operator<.
//
//      Revision 8.2  1994/10/20  14:47:46  qhsmosc
//      Removed absolute path before comparing names in operator== and operator<
//
//      Revision 8.1  1994/10/13  19:33:30  ehsgrap
//      Increased const corectness.
//
//      Revision 8.0  1994/10/05  08:53:44  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.3  1994/10/04  14:41:32  qhsmosc
//      Backed one version
//
//      Revision 7.1  1994/09/28  12:50:35  qhsmosc
//      Default mailaddress set at construction
//
//      Revision 7.0  1994/09/22  13:25:58  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.2  1994/09/15  14:30:38  qhsmosc
//      Sort implemented
//
//      Revision 6.1  1994/09/08  10:36:26  qhsmosc
//      Preliminary UI tests ready
//
//      Revision 6.0  1994/08/30  17:53:08  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:50:13  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.2  1994/08/16  06:52:13  qhsmosc
//      Before freeze testing remaining
//
//      Revision 4.1  1994/08/10  07:17:26  qhsmosc
//      Bsck to hierarchy
//
//      Revision 1.2  1994/07/12  06:45:29  qhsmosc
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
//      CHA_Order

//**********************************************************************

#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_CmdFileOrder.H>
//#include <sysent.h>

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_CmdFileOrder", (char*)"C");

// Member functions, constructors, destructors, operators

//**********************************************************************

CHA_CmdFileOrder::CHA_CmdFileOrder()
:delayedRouting(CHA_RT_DELAYED),
 immediateRouting(CHA_RT_IMMEDIATE),
 externalSystem(),
 funcBusyRetryPeriod(1),
 stopExecutionAtNotAccep(FALSE),
 stopExecutionAtPartExec(FALSE),
 sendMailForNotAccPartExec(FALSE),
 sendMailForExecutionResult(FALSE),
 mailAddress(),
 delayedResponseReception(CHA_ASYNCHRON),
 userInfo()
{
    //TRACE_IN(trace, CHA_CmdFileOrder, "");

    kind = CHA_ORDKIND_CMDFILE;

    mailAddress = userInfo.loginName();

};

//**********************************************************************

CHA_CmdFileOrder::CHA_CmdFileOrder(const CHA_CmdFileOrder& order)
{
    //TRACE_IN(trace, CHA_CmdFileOrder-Copy, "");

    // Copy constructor

    // Values from superclass
    state = order.state;
    name = order.name;
    orderId = order.orderId;
    kind    = order.kind;

    host    = order.host;

    tasId    = order.tasId;
    timestamp = order.timestamp;

    interval = order.interval;

    // Own values
    delayedRouting = order.delayedRouting;
    immediateRouting = order.immediateRouting;
    externalSystem = order.externalSystem;
    funcBusyRetryPeriod = order.funcBusyRetryPeriod;
    stopExecutionAtNotAccep = order.stopExecutionAtNotAccep;
    stopExecutionAtPartExec = order.stopExecutionAtPartExec;
    sendMailForNotAccPartExec = order.sendMailForNotAccPartExec;
    sendMailForExecutionResult = order.sendMailForExecutionResult;
    mailAddress = order.mailAddress;
    delayedResponseReception = order.delayedResponseReception;
};

//**********************************************************************

CHA_CmdFileOrder::~CHA_CmdFileOrder()
{
};

//**********************************************************************

const RWCString& CHA_CmdFileOrder::getExternalSystem() const
{
    //TRACE_IN(trace, getExternalSystem, "");

    return externalSystem;
};

//**********************************************************************

void CHA_CmdFileOrder::setExternalSystem(const RWCString& extSystemIn)
{
    //TRACE_IN(trace, setExternalSystem, "");

    externalSystem = extSystemIn;
};

//**********************************************************************

const RWCString CHA_CmdFileOrder::getMailAddress() const
{
    //TRACE_IN(trace, getMailAddress, "");

    return mailAddress;
};

//**********************************************************************

void CHA_CmdFileOrder::setMailAddress(const RWCString mailAddressIn)
{
    //TRACE_IN(trace, setMailAddress, "");

    mailAddress = mailAddressIn;
};

//**********************************************************************

const int CHA_CmdFileOrder::getFuncBusyRetry() const
{
    //TRACE_IN(trace, getFuncBusyRetry, "");

    return funcBusyRetryPeriod;
};

//**********************************************************************

void CHA_CmdFileOrder::setFuncBusyRetry(const int funcBusyRetryIn)
{
    //TRACE_IN(trace, setFuncBusyRetry, "");

    funcBusyRetryPeriod = funcBusyRetryIn;
};

//**********************************************************************

const RWBoolean CHA_CmdFileOrder::stopExecAtNotAccep() const
{
    //TRACE_IN(trace, getStopExecAtNotAccep, "");

    return stopExecutionAtNotAccep;
};

//**********************************************************************

void CHA_CmdFileOrder::setStopExecAtNotAccep(const RWBoolean stopExecIn)
{
    //TRACE_IN(trace, setStopExecAtNotAccep, "");

    stopExecutionAtNotAccep = stopExecIn;
};

//**********************************************************************

const RWBoolean CHA_CmdFileOrder::stopExecAtPartExec() const
{
    //TRACE_IN(trace, getStopExecAtPartExec, "");

    return stopExecutionAtPartExec;
};

//**********************************************************************

void CHA_CmdFileOrder::setStopExecAtPartExec(const RWBoolean stopExecIn)
{
    //TRACE_IN(trace, setStopExecAtPartExec, "");

    stopExecutionAtPartExec = stopExecIn;
};

//**********************************************************************

const RWBoolean CHA_CmdFileOrder::sendMailForNAPE() const
{
    //TRACE_IN(trace, sendMailForNAPE, "");

    return sendMailForNotAccPartExec;
};

//**********************************************************************

void CHA_CmdFileOrder::setSendMailForNAPE(const RWBoolean sendMailForIn)
{
    //TRACE_IN(trace, setSendMailForNAPE, "");

    sendMailForNotAccPartExec = sendMailForIn;
};

//**********************************************************************

const RWBoolean CHA_CmdFileOrder::sendMailForExecResult() const
{
    //TRACE_IN(trace, sendMailForExecResult, "");

    return sendMailForExecutionResult;
};

//**********************************************************************

void CHA_CmdFileOrder::setSendMailForExecResult(const RWBoolean sendMailForIn)
{
    //TRACE_IN(trace, setSendMailForExecResult, "");

    sendMailForExecutionResult = sendMailForIn;
};

//**********************************************************************

const CHA_Resp CHA_CmdFileOrder::getDelRespRecep() const
{
    //TRACE_IN(trace, getDelRespRecep, "");

    return delayedResponseReception;
};

//**********************************************************************

void CHA_CmdFileOrder::setDelRespRecep(const CHA_Resp delRespRecepIn)
{
    //TRACE_IN(trace, setDelRespRecep, "");

    delayedResponseReception = delRespRecepIn;
};

//**********************************************************************

void CHA_CmdFileOrder::setDelRoutingCase(const CHA_RoutingCase& routingcase)
{
    //TRACE_IN(trace, setDelRoutingCase, "");

    delayedRouting = routingcase;
};

//**********************************************************************

CHA_RoutingCase& CHA_CmdFileOrder::getDelRoutingCase()
{
    //TRACE_IN(trace, getDelRoutingCase, "");

    return delayedRouting;
};

//**********************************************************************

const CHA_RoutingCase& CHA_CmdFileOrder::getDelRoutingCase() const
{
    //TRACE_IN(trace, getDelRoutingCase, "");

    return delayedRouting;
};

//**********************************************************************

void CHA_CmdFileOrder::setImmRoutingCase(const CHA_RoutingCase& routingcase)
{
    //TRACE_IN(trace, setImmRoutingCase, "");

    immediateRouting = routingcase;
};

//**********************************************************************

CHA_RoutingCase& CHA_CmdFileOrder::getImmRoutingCase()
{
    //TRACE_IN(trace, getImmRoutingCase, "");

    return immediateRouting;
};

//**********************************************************************

const CHA_RoutingCase& CHA_CmdFileOrder::getImmRoutingCase() const
{
    //TRACE_IN(trace, getImmRoutingCase, "");

    return immediateRouting;
};

//**********************************************************************

CHA_CmdFileOrder& CHA_CmdFileOrder::operator=(const CHA_CmdFileOrder& order)
{
    //TRACE_IN(trace, operator=, "");

    // Values from superclass
    state                      = order.state;
    name                       = order.name;
    orderId                    = order.orderId;
    kind                       = order.kind;
    interval                   = order.interval;

    host                       = order.getHost();

    tasId                      = order.getTasId();
    timestamp                  = order.getTimestamp();

    // Own values
    delayedRouting             = order.getDelRoutingCase();
    immediateRouting           = order.getImmRoutingCase();
    externalSystem             = order.getExternalSystem();
    funcBusyRetryPeriod        = order.getFuncBusyRetry();
    stopExecutionAtNotAccep    = order.stopExecAtNotAccep();
    stopExecutionAtPartExec    = order.stopExecAtPartExec();
    sendMailForNotAccPartExec  = order.sendMailForNAPE();
    sendMailForExecutionResult = order.sendMailForExecResult();
    mailAddress                = order.getMailAddress();
    delayedResponseReception   = order.getDelRespRecep();

    return *this;
};

//**********************************************************************

//int CHA_CmdFileOrder::operator==(const CHA_CmdFileOrder& order)
int CHA_CmdFileOrder::operator==(const CHA_Order& order) const
{
    //TRACE_IN(trace, operator==, "");

    //TRACE_FLOW(trace, thisName, name);
    //TRACE_FLOW(trace, incommingName, order.getName());

    RWCString myName = name;
    RWCString compareName = order.getName();
    size_t pathLength;

    // Remove paths
    pathLength = myName.last('/');
    if(pathLength != RW_NPOS)
	// Remove path
	myName.remove(0, pathLength + 1);
    pathLength = compareName.last('/');
    if(pathLength != RW_NPOS)
	// Remove path
	compareName.remove(0, pathLength + 1);

    //TRACE_FLOW(trace, thisNameStriped, myName);
    //TRACE_FLOW(trace, incommingNameStriped, compareName);

    switch(sortOrder)
    {
    case CHA_SORT_FILENAME:

	if (myName != compareName)
	{
	    //TRACE_FLOW(trace, ReturningFALSEName, "");
	    return FALSE;
	}
	if (orderId != order.getOrderId())
	{
	    //TRACE_FLOW(trace, ReturningFALSEId, "");
	    return FALSE;
	}
	break;

    case CHA_SORT_TYPE:
	if (kind != order.getOrderKind())
	    return FALSE;
	if (orderId != order.getOrderId())
	    return FALSE;
	break;

    case CHA_SORT_ES:
	if (order.getOrderKind() != kind)
	    // CmdFiles should come before SysCmdFiles and this is a CmdFile
	    return FALSE;
	if (externalSystem != ((CHA_CmdFileOrder*)&order)->getExternalSystem())
	    return FALSE;
	if (orderId != order.getOrderId())
	    return FALSE;
	break;

    case CHA_SORT_STARTTIME:
	if (interval.getStartTime() != order.getInterval().getStartTime())
	    return FALSE;
	if (orderId != order.getOrderId())
	    return FALSE;
	break;

    case CHA_SORT_STATUS:
	if (state != order.getState())
	    return FALSE;
	if (orderId != order.getOrderId())
	    return FALSE;
	break;

    case CHA_SORT_FILENAMEES:
	if (myName != compareName)
	    return FALSE;
	if (order.getOrderKind() != kind)
	    // CmdFiles should come before SysCmdFiles and this is a CmdFile
	    return FALSE;
	if (externalSystem != ((CHA_CmdFileOrder*)&order)->getExternalSystem())
	    return FALSE;
	if (orderId != order.getOrderId())
	    return FALSE;
	break;

    default:
	// Default sorting, at the moment same as CHA_SORT_ORDERNR
	if (orderId != order.getOrderId())
	    return FALSE;
	break;
    }

    //TRACE_FLOW(trace, ReturningTRUE, "");
    return TRUE;
};

//**********************************************************************

//int CHA_CmdFileOrder::operator<(const CHA_CmdFileOrder& order)
int CHA_CmdFileOrder::operator<(const CHA_Order& order) const
{
    //TRACE_IN(trace, operator<, "");

    //TRACE_FLOW(trace, SortOrder, sortOrder);
    //TRACE_FLOW(trace, thisName, name);
    //TRACE_FLOW(trace, incommingName, order.getName());

    RWCString myName = name;
    RWCString compareName = order.getName();
    size_t pathLength;

    // Remove paths
    pathLength = myName.last('/');
    if(pathLength != RW_NPOS)
	// Remove path
	myName.remove(0, pathLength + 1);
    pathLength = compareName.last('/');
    if(pathLength != RW_NPOS)
	// Remove path
	compareName.remove(0, pathLength + 1);

    //TRACE_FLOW(trace, thisNameStriped, myName);
    //TRACE_FLOW(trace, incommingNameStriped, compareName);

    switch(sortOrder)
    {
    case CHA_SORT_FILENAME:
	if (myName < compareName)
	{
	    //TRACE_FLOW(trace, ReturningTRUEName, "");
	    return TRUE;
	}
	else
	    if (myName > compareName)
	    {
		//TRACE_FLOW(trace, ReturningFALSEName, "");
		return FALSE;
	    }
	if (orderId < order.getOrderId())
	{
	    //TRACE_FLOW(trace, ReturningTRUEId, "");
	    return TRUE;
	}
	else
	    if (orderId > order.getOrderId())
	    {
		//TRACE_FLOW(trace, ReturningFALSEId, "");
		return FALSE;
	    }
	break;

    case CHA_SORT_TYPE:
	if (kind < order.getOrderKind())
	    return TRUE;
	else
	    if (kind > order.getOrderKind())
		return FALSE;
	if (orderId < order.getOrderId())
	    return TRUE;
	else
	    if (orderId > order.getOrderId())
		return FALSE;
	break;

    case CHA_SORT_ES:
	if (order.getOrderKind() != kind)
	    // CmdFiles should come before SysCmdFiles and this is a CmdFile
	    return TRUE;
	if (externalSystem < ((CHA_CmdFileOrder*)&order)->getExternalSystem())
	    return TRUE;
	else
	    if (externalSystem >
		((CHA_CmdFileOrder*)&order)->getExternalSystem())
		return FALSE;
	if (orderId < order.getOrderId())
	    return TRUE;
	else
	    if (orderId > order.getOrderId())
		return FALSE;
	break;

    case CHA_SORT_STARTTIME:
	if (interval.getStartTime() < order.getInterval().getStartTime())
	    return TRUE;
	else
	    if (interval.getStartTime() >
		order.getInterval().getStartTime())
		return FALSE;
	if (orderId < order.getOrderId())
	    return TRUE;
	else
	    if (orderId > order.getOrderId())
		return FALSE;
	break;

    case CHA_SORT_STATUS:
	if (state < order.getState())
	    return TRUE;
	else
	    if (state > order.getState())
		return FALSE;
	if (orderId < order.getOrderId())
	    return TRUE;
	else
	    if (orderId > order.getOrderId())
		return FALSE;
	break;

    case CHA_SORT_FILENAMEES:
	if (myName < compareName)
	    return TRUE;
	else
	    if (myName > compareName)
		return FALSE;
	if (order.getOrderKind() != kind)
	    // CmdFiles should come before SysCmdFiles and this is a CmdFile
	    return TRUE;
	if (externalSystem < ((CHA_CmdFileOrder*)&order)->getExternalSystem())
	    return TRUE;
	else
	    if (externalSystem >
		((CHA_CmdFileOrder*)&order)->getExternalSystem())
		return FALSE;
	if (orderId < order.getOrderId())
	    return TRUE;
	else
	    if (orderId > order.getOrderId())
		return FALSE;
	break;

    default:
	// Default sorting, at the moment same as CHA_SORT_ORDERNR
	if (orderId < order.getOrderId())
	    return TRUE;
	else
	    if (orderId > order.getOrderId())
		return FALSE;
	break;
    }

    //TRACE_FLOW(trace, ReturningFALSELast, "");
    return FALSE;
};


