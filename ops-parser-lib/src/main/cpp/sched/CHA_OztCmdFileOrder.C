// RCS handling
// $Id: CHA_OztCmdFileOrder.C,v 24.2 1996/01/17 16:53:16 ehscama Exp $

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
//      1995-02-15  EHS/PXE Christer Eklund (qhskred@ehs.ericsson.se)

// REVISION
//	TB53_OZ
//	1995-11-28
// CHANGES
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
//

// SEE ALSO
//      CHA_Order

//**********************************************************************

#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_OztCmdFileOrder.H>
//#include <sysent.h>

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_OztCmdFileOrder", (char*)"C");

// Member functions, constructors, destructors, operators

//**********************************************************************

CHA_OztCmdFileOrder::CHA_OztCmdFileOrder()
:
 externalSystem(),
 exitMailAddress(),
 OZTLabel(),
 OZTDisplay(),
 OZTDisplayOn(FALSE),
 outputMailAddress(),
 outputFile(),
// outputFile(),
 userInfo()
{

    //TRACE_IN(trace, CHA_OztCmdFileOrder, "");

    kind = CHA_ORDKIND_OZTCMDFILE;

    exitMailAddress = userInfo.loginName();

};

//**********************************************************************

CHA_OztCmdFileOrder::CHA_OztCmdFileOrder(const CHA_OztCmdFileOrder& order)
{
    //TRACE_IN(trace, CHA_OztCmdFileOrder-Copy, "");

    // Copy constructor

    // Values from superclass
    state   = order.state;
    name    = order.name;
    orderId = order.orderId;
    kind    = order.kind;

    host    = order.host;

    tasId    = order.tasId;
    timestamp = order.timestamp;

    interval = order.interval;

    // Own values
    OZTLabel = order.OZTLabel;
    OZTDisplay = order.OZTDisplay;
    OZTDisplayOn = order.OZTDisplayOn;
    outputMailAddress = order.outputMailAddress;
    outputFile = order.outputFile;
    outputPrinter = order.outputPrinter;

    externalSystem = order.externalSystem;
    exitMailAddress = order.exitMailAddress;
};

//**********************************************************************

CHA_OztCmdFileOrder::~CHA_OztCmdFileOrder()
{
};

//**********************************************************************

const RWCString& CHA_OztCmdFileOrder::getExternalSystem() const
{
    //TRACE_IN(trace, getExternalSystem, "");

    return externalSystem;
};

//**********************************************************************

void CHA_OztCmdFileOrder::setExternalSystem(const RWCString& extSystemIn)
{
    //TRACE_IN(trace, setExternalSystem, "");

    externalSystem = extSystemIn;
};

//**********************************************************************

const RWCString CHA_OztCmdFileOrder::getExitMessageMailAddress() const
{
    //TRACE_IN(trace, getExitMessageMailAddress, "");

    return exitMailAddress;
};

//**********************************************************************

void CHA_OztCmdFileOrder::setExitMessageMailAddress(const RWCString mailAddressIn)
{
    //TRACE_IN(trace, setExitMessageMailAddress, "");

    exitMailAddress = mailAddressIn;
};

//**********************************************************************

void CHA_OztCmdFileOrder::setStartLabel(const RWCString& OZTLabelIn)
{
    //TRACE_IN(trace, setStartLabel, OZTLabelIn);

    OZTLabel = OZTLabelIn;
};

//**********************************************************************

const RWCString& CHA_OztCmdFileOrder::getStartLabel() const
{
    //TRACE_IN(trace, getStartLabel, "");

    return OZTLabel;
};

//**********************************************************************


void CHA_OztCmdFileOrder::setDisplayName(const RWCString& OZTDisplayIn)
{
    //TRACE_IN(trace, setDisplayName, OZTDisplayIn);

    OZTDisplay = OZTDisplayIn;
};

//**********************************************************************

const RWCString& CHA_OztCmdFileOrder::getDisplayName() const
{
    //TRACE_IN(trace, getDisplayName, "");

    return OZTDisplay;
};

//**********************************************************************

void CHA_OztCmdFileOrder::setDisplayOn(RWBoolean OZTDisplayOnIn)
{
    //TRACE_IN(trace, setDisplayOn, OZTDisplayOnIn);

    OZTDisplayOn = OZTDisplayOnIn;
};

//**********************************************************************

const RWBoolean CHA_OztCmdFileOrder::isDisplayOn() const
{
    //TRACE_IN(trace, isDisplayOn, "");

    return OZTDisplayOn;
};

//**********************************************************************

void CHA_OztCmdFileOrder::setOutputMailaddress(const RWCString& outputMailIn)
{
    //TRACE_IN(trace, setOutputMailaddress, outputMailIn);

    outputMailAddress = outputMailIn;
};

//**********************************************************************

const RWCString& CHA_OztCmdFileOrder::getOutputMailaddress() const
{
    //TRACE_IN(trace, getOutputMailaddress, "");

    return outputMailAddress;
};
//**********************************************************************
void CHA_OztCmdFileOrder::setOutputFile(const RWCString& outputFileIn)
{
    //TRACE_IN(trace, setOutputFile, outputFileIn);

    outputFile = outputFileIn;
};

//**********************************************************************

const RWCString& CHA_OztCmdFileOrder::getOutputFile() const
{
    //TRACE_IN(trace, getOutputFile, "");

    return outputFile;
};

//**********************************************************************
void CHA_OztCmdFileOrder::setOutputPrinter(const RWCString& outputPrinterIn)
{
    //TRACE_IN(trace, setOutputPrinter, outputPrinterIn);

    outputPrinter = outputPrinterIn;
};

//**********************************************************************

const RWCString& CHA_OztCmdFileOrder::getOutputPrinter() const
{
    //TRACE_IN(trace, getOutputPrinter, "");

    return outputPrinter;
};

//**********************************************************************

CHA_OztCmdFileOrder& CHA_OztCmdFileOrder::operator=(const CHA_OztCmdFileOrder& order)
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
    externalSystem             = order.getExternalSystem();
    exitMailAddress            = order.getExitMessageMailAddress();

    OZTLabel                   = order.getStartLabel();
    OZTDisplay                 = order.getDisplayName();
    OZTDisplayOn               = order.isDisplayOn();
    outputMailAddress          = order.getOutputMailaddress();
    outputFile                 = order.getOutputFile();
    outputPrinter              = order.getOutputPrinter();

    return *this;
};

//**********************************************************************

//int CHA_OztCmdFileOrder::operator==(const CHA_OztCmdFileOrder& order)
int CHA_OztCmdFileOrder::operator==(const CHA_Order& order) const
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
	if (externalSystem != ((CHA_OztCmdFileOrder*)&order)->getExternalSystem())
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
	if (externalSystem != ((CHA_OztCmdFileOrder*)&order)->getExternalSystem())
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

//int CHA_OztCmdFileOrder::operator<(const CHA_OztCmdFileOrder& order)
int CHA_OztCmdFileOrder::operator<(const CHA_Order& order) const
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
	if (externalSystem < ((CHA_OztCmdFileOrder*)&order)->getExternalSystem())
	    return TRUE;
	else
	    if (externalSystem >
		((CHA_OztCmdFileOrder*)&order)->getExternalSystem())
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
	if (externalSystem < ((CHA_OztCmdFileOrder*)&order)->getExternalSystem())
	    return TRUE;
	else
	    if (externalSystem >
		((CHA_OztCmdFileOrder*)&order)->getExternalSystem())
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


