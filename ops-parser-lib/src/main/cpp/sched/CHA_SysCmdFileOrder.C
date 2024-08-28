// RCS handling
// $Id: CHA_SysCmdFileOrder.C,v 24.0 1995/11/28 16:59:34 ehsgrap Rel $

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
//      $Log: CHA_SysCmdFileOrder.C,v $
//      Revision 24.0  1995/11/28 16:59:34  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:47:49  17:47:49  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:49:02  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:46:16  09:46:16  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:37:43  08:37:43  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:56:56  10:56:56  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:09:34  20:09:34  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:11:24  14:11:24  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  13:03:54  13:03:54  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  15:09:20  15:09:20  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:37:33  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.6  95/02/16  16:02:51  16:02:51  qhskred (Krister Eklund VK/EHS/PXE)
//      Removed OZTLabel, OZTDisplay and ELB
//
//      Revision 13.5  1995/02/15  14:10:34  cmcha
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 9.1  95/02/08  12:52:26  12:52:26  qhsmosc (Marie Moschna VK/EHS/PXE)
//      rewrite after TAS change
//
//      Revision 9.0  1994/10/24  21:33:36  cmcha
//      Made release E, ehscama.
//
//      Revision 8.3  1994/10/24  19:13:51  ehscama
//      Added const on operator= and operator<.
//
//      Revision 8.2  1994/10/20  14:47:05  qhsmosc
//      Removed path when comparing names in operator== and operator<
//
//      Revision 8.1  1994/10/13  19:32:38  ehsgrap
//      Increased const corectness.
//
//      Revision 8.0  1994/10/05  08:54:09  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.2  1994/10/04  14:43:10  qhsmosc
//      Backed one revision
//
//      Revision 7.0  1994/09/22  13:26:23  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.1  1994/09/15  14:31:04  qhsmosc
//      Sort implemented
//
//      Revision 6.0  1994/08/30  17:53:30  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:51:01  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.2  1994/08/16  06:52:43  qhsmosc
//      Before freeze, testing remaining
//
//      Revision 4.1  1994/08/10  07:24:59  qhsmosc
//      Back to hierarchy
//
//      Revision 1.2  1994/07/12  06:45:48  qhsmosc
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
#include <CHA_SysCmdFileOrder.H>
#include <pwd.h>
//#include <sysent.h>

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_SysCmdFileOrder", (char*)"C");

// Member functions, constructors, destructors, operators

//**********************************************************************

CHA_SysCmdFileOrder::CHA_SysCmdFileOrder()
:parameterList(),
 messagesToMail(FALSE)
{
    //TRACE_IN(trace, CHA_SysCmdFileOrder, "");

    kind = CHA_ORDKIND_SYSCMDFILE;

};

//**********************************************************************

CHA_SysCmdFileOrder::CHA_SysCmdFileOrder(const CHA_SysCmdFileOrder& order)
{
    //TRACE_IN(trace, CHA_SysCmdFileOrder-Copy, "");

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
    parameterList  = order.parameterList;
    messagesToMail = order.messagesToMail;
};

//**********************************************************************

CHA_SysCmdFileOrder::~CHA_SysCmdFileOrder()
{
};

//**********************************************************************

const RWCString& CHA_SysCmdFileOrder::getParameterList() const
{
    //TRACE_IN(trace, getParameterList, "");

    return parameterList;
};

//**********************************************************************

void CHA_SysCmdFileOrder::setParameterList(const RWCString& pListIn)
{
    //TRACE_IN(trace, setParameterList, "");

    parameterList = pListIn;
};

//**********************************************************************

const RWBoolean CHA_SysCmdFileOrder::getMessagesToMail() const
{
    //TRACE_IN(trace, getMessagesToMail, "");

    return messagesToMail;
};

//**********************************************************************

void CHA_SysCmdFileOrder::setMessagesToMail(const RWBoolean messToMailIn)
{
    //TRACE_IN(trace, setMessagesToMail, "");

    messagesToMail = messToMailIn;;
};

//**********************************************************************

CHA_SysCmdFileOrder& CHA_SysCmdFileOrder::operator=(
    const CHA_SysCmdFileOrder& order)
{
    //TRACE_IN(trace, operator=, "");

    state          = order.getState();
    orderId        = order.getOrderId();
    name           = order.getName();
    kind           = order.getOrderKind();

    host           = order.getHost();

    tasId          = order.getTasId();
    timestamp      = order.getTimestamp();

    interval       = order.getInterval();

    messagesToMail = order.getMessagesToMail();
    parameterList  = order.getParameterList();

    return *this;
};

//**********************************************************************

//int CHA_SysCmdFileOrder::operator==(const CHA_SysCmdFileOrder& order)
int CHA_SysCmdFileOrder::operator==(const CHA_Order& order) const
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
	    //TRACE_FLOW(trace, returningFALSEName, "");
	    return FALSE;
	}
	if (orderId != order.getOrderId())
	{
	    //TRACE_FLOW(trace, returningFALSEId, "");
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
	    // CmdFiles should come before SysCmdFiles and this is a SysCmdFile
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
	    // CmdFiles should come before SysCmdFiles and this is a SysCmdFile
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

//int CHA_SysCmdFileOrder::operator<(const CHA_SysCmdFileOrder& order)
int CHA_SysCmdFileOrder::operator<(const CHA_Order& order) const
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
	    // CmdFiles should come before SysCmdFiles and this is a SysCmdFile
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
	    if (interval.getStartTime() > order.getInterval().getStartTime())
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
	    // CmdFiles should come before SysCmdFiles and this is a SysCmdFile
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

    //TRACE_FLOW(trace, ReturningFALSE, "");
    return FALSE;
};
