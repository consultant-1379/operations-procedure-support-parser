// RCS handling
// $Id: CHA_ExecOrderList.C,v 24.1 1996/04/09 15:54:40 qhssian Exp $

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
//      $Log: CHA_ExecOrderList.C,v $
//      Revision 24.1  1996/04/09 15:54:40  qhssian
//      *** empty log message ***
//
//      Revision 24.0  95/11/28  16:59:24  16:59:24  ehsgrap (Jan Grape (9 9073) VK/EHS/VE)
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:47:37  17:47:37  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//
//      Revision 22.2  1995/08/30  16:00:44  ehscama
//      Merged in changes from 16.0.1.1.
//
//      Revision 22.1  1995/08/25  09:57:05  qhsiabr
//      Added getOrderState.
//
//      Revision 22.0  1995/08/01  20:48:54  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:46:06  09:46:06  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:37:34  08:37:34  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:56:46  10:56:46  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:09:25  20:09:25  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:11:08  14:11:08  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  13:03:43  13:03:43  cmcha (*CHA conf. and dev. EHS/PXE)
//
//      Revision 16.0.1.1  1995/08/16  09:43:48  ehscama
//      Added calls to construct and destruct the time control object
//      in the converter class. See comments in CHA_Converter.
//
//      Revision 16.0  1995/03/10  13:03:43  cmcha
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
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
//      RWTValOrderedVector
//      CHA_SubscList
//      CHA_ExecOrderList
//      CHA_Order

//**********************************************************************

#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_ExecOrderList.H>
#include <pwd.h>
//#include <sysent.h>

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_ExecOrderList", (char*)"C");

// Member functions, constructors, destructors, operators

//**********************************************************************

CHA_ExecOrderList::CHA_ExecOrderList()
{
    ////TRACE_IN(trace, CHA_ExecOrderList, "");

    CHA_Converter::constructTimeControl();

    createList(CHA_SORT_ORDERNR);
};

//**********************************************************************

CHA_ExecOrderList::~CHA_ExecOrderList()
{
    CHA_Converter::destructTimeControl();
    //orderList.clearAndDestroy();
};

//**********************************************************************

int CHA_ExecOrderList::createList(CHA_SortOrder sortOrder)
{
    int            answer = 0;
    CHA_Converter  converter;
    long           ordid = 0;
    CHA_Order*     order = NULL;
    RWBoolean      oldDate = FALSE;
    RWTPtrSortedVector<CHA_Order> newOrderList;


    //TRACE_IN(trace, CreateList, "");

    // Determine the sort order
    //TRACE_FLOW(trace, SetSortOrder, sortOrder);
    if (sortOrder != CHA_SORT_DONTCHANGE)
	CHA_Order::setSortOrder(sortOrder);

    // Fetch information and sort into the list
    ordid = converter.getFirstKey();
    //TRACE_FLOW(trace, ordidatcreate, ordid);

    // For each id read information and append to list
    while ((ordid > 0) && (ordid != AM_DB_KEY_NOT_FOUND))
    {
	switch (converter.fetchKind(ordid))
	{
	    case CHA_ORDKIND_OZTCMDFILE:
		order = new CHA_OztCmdFileOrder();
		break;
	    default:
		answer = AM_ERROR;
	};

        if(answer == 0)
	    answer = order->fetch(ordid);
        if ((answer  == AM_DB_OK) ||
	    (answer == AM_OK) ||
	    (answer == CHA_AM_OLD_DATE))
        {
	    //TRACE_FLOW(trace, OrderToBeInserted, order->getOrderId());
            newOrderList.insert(order);
	    //TRACE_FLOW(trace, OrderInserted,"");
	    if (answer == CHA_AM_OLD_DATE)
		oldDate = TRUE;
        }
	else
	{
	    // Something has gone wrong, error handling
	    if(order != NULL)
		delete order;
	    //TRACE_FLOW(trace, SomethingWrongCreateList, answer);
	    // Destroy created objects, old list remains intact
	    newOrderList.clearAndDestroy();
	    return answer;
	};

        ordid = converter.getNextKey();
    };

    // Everything went according to plan, destroy original list and save
    // new list
    orderList.clearAndDestroy();
    orderList = newOrderList;

    if (orderList.entries() > 0)
    {
	announceEvent(CHA_OrderList::CHANGEDITEM, *orderList.at(0));
    }
    else
    {
        CHA_Order* returOrder = new CHA_Order();
	announceEvent(CHA_OrderList::CHANGEDITEM, *returOrder);
	delete returOrder;
    };

    if (oldDate == TRUE)
	return CHA_AM_OLD_DATE;
    else
	return AM_DB_OK;
};

//**********************************************************************

int CHA_ExecOrderList::updateList()
{
    int answer;

    //TRACE_IN(trace, UpdateList, "");

    answer = createList(CHA_SORT_DONTCHANGE);

    return answer;
};

//**********************************************************************

int CHA_ExecOrderList::addOrder(CHA_Order * order)
{
    int answer;
    //TRACE_IN(trace, AddOrder, "");

    CHA_Order * copyOrder;

    answer = order->store();
    if ((answer != AM_DB_OK) && (answer != AM_OK))
    {
        //  Something has gone astray, error handling
	//TRACE_FLOW(trace, ErrorInAddOrder, answer);
	return answer;
    };

    //TRACE_FLOW(trace, AddOrderAnswer, answer);

    switch (order->getOrderKind())
    {
	case CHA_ORDKIND_OZTCMDFILE:
	    copyOrder = new CHA_OztCmdFileOrder(*(CHA_OztCmdFileOrder*)order);
	    orderList.insert(copyOrder);
	    break;
	default:
	    return AM_ERROR;
    };

    announceEvent(CHA_OrderList::ADDEDITEM, *order);
    return AM_DB_OK;
};

//**********************************************************************

int CHA_ExecOrderList::removeOrder(const long ordId)
{
    int  index = 0;
    int  size = 0;
    int  answer;
    CHA_Order* removedOrder;

    //TRACE_IN(trace, RemoveOrder, ordId);

    // Find wanted order

    size = orderList.entries();

    while ((index < size) &&
	   ((orderList.at(index)->getOrderId()) != ordId))
      index++;

    if (index < size)
    {
      answer = orderList.at(index)->remove();
      if ((answer != AM_DB_OK) && (answer != AM_OK))
      {
        //  Something has gone astray, error handling
        //TRACE_FLOW(trace, ErrorInRemoveOrder, answer);
        return answer;
      }
      removedOrder = orderList.at(index);
      orderList.removeAt(index);
      announceEvent(CHA_ExecOrderList::REMOVEDITEM, *removedOrder);
      delete removedOrder; removedOrder = 0;
    }

    return AM_DB_OK;
};

//**********************************************************************

int CHA_ExecOrderList::changeOrder(const long ordId)
{
    int  index = 0;
    int  size = 0;
    int  answer;


    //TRACE_IN(trace, ChangeOrder(ordid), ordId);

    // Find wanted order
    size = orderList.entries();
    while ((index < size) &&
	   ((orderList.at(index)->getOrderId()) != ordId))
	index++;

    if (index < size)
    {
	answer = orderList.at(index)->store();
	if ((answer != AM_DB_OK) && (answer != AM_OK))
	{
	    //  Something has gone astray, error handling
	    //TRACE_FLOW(trace, ErrorInChangeOrder, answer);
	    return answer;
	};
    }
    else
    {
	// Order does not exist error handling
	//TRACE_FLOW(trace, OrderCouldNotBeFound, "");
        return -1;
    };

    announceEvent(CHA_ExecOrderList::CHANGEDITEM, *orderList.at(index));
    return AM_DB_OK;
};

//**********************************************************************

int CHA_ExecOrderList::changeOrder(CHA_Order* order)
{
    int  index = 0;
    int  size = 0;
    int  answer;
    long ordId = 0;

    //TRACE_IN(trace, ChangeOrder(order), "");

    // Find wanted order
    size = orderList.entries();
    ordId = order->getOrderId();
    while ((index < size) &&
	   ((orderList.at(index)->getOrderId()) != ordId))
	index++;

    if (index >=  size)
    {
	// Order does not exist error handling
	//TRACE_FLOW(trace, OrderCouldNotBeFound, "");
        return -1;
    };

	CHA_OztCmdFileOrder &oldOrder = (CHA_OztCmdFileOrder &)
	                                  *(orderList.at(index));
	oldOrder = *(CHA_OztCmdFileOrder*) order;

    answer = orderList.at(index)->store();

    if ((answer != AM_DB_OK) && (answer != AM_OK))
    {
	//  Something has gone astray, error handling
	//TRACE_FLOW(trace, ErrorInChangeWholeOrderStore, answer);
	return answer;
    };

    announceEvent(CHA_ExecOrderList::CHANGEDITEM, *orderList.at(index));
    return AM_DB_OK;
};

//**********************************************************************

int CHA_ExecOrderList::activateOrder(const long ordId)
{
    int  size;
    int index = 0;
    int answer = 0;

    //TRACE_IN(trace, ActivateOrder, ordId);

    // Find wanted order
    size = orderList.entries();
    while ((index < size) &&
	   ((orderList.at(index)->getOrderId()) != ordId))
	index++;

    answer = orderList.at(index)->activate();
    if (answer == AM_DB_OK)
       orderList.at(index)->setState(CHA_ORDER_ACTIVE);

    announceEvent(CHA_OrderList::CHANGEDITEM, *orderList.at(index));
    return answer;
};

//**********************************************************************

int CHA_ExecOrderList::suspendOrder(const long ordId)
{
    int  size;
    int index = 0;
    int answer = 0;

    //TRACE_IN(trace, SuspendOrder, ordId);

    // Find wanted order
    size = orderList.entries();
    while ((index < size) &&
	   ((orderList.at(index)->getOrderId()) != ordId))
	index++;

    answer =  orderList.at(index)->suspend();
    if (answer == AM_DB_OK)
       orderList.at(index)->setState(CHA_ORDER_CANCELLED);

    announceEvent(CHA_OrderList::CHANGEDITEM, *orderList.at(index));
    return answer;
};

//**********************************************************************

const CHA_OrderState CHA_ExecOrderList::getOrderState (const long ordId)
{
    int  size;
    int index = 0;
    CHA_OrderState orderState;

    //TRACE_IN(trace, getOrderState, ordId);

    // Find wanted order
    size = orderList.entries();
    while ((index < size) &&
	   ((orderList.at(index)->getOrderId()) != ordId))
	index++;

    orderState = orderList.at(index)->getState();
    return orderState;
};

//**********************************************************************
