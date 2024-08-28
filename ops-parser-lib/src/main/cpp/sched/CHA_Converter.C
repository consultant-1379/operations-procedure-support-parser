// RCS handling
// $Id: CHA_Converter.C,v 24.3 1996/07/30 09:44:31 emejome Exp $

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
//      $Log: CHA_Converter.C,v $
//      Revision   2000/03/02 09:44:31  ehsanah
//      Remove CHA_CmdFileOrder and CHA_SysCmdFileOrder
//
//      Revision 24.3  1996/07/30 09:44:31  emejome
//      ::storeOrder does now warn when a modified order is scheduled too close to the present time.
//
//      Revision 24.2  1996/03/06 14:45:03  ehsjasa
//      Using CHA_UserInfo to get the login name instead of reading an
//      environment variable ($USER or $LOGNAME).
//
//      Revision 24.1  1996/01/11 11:50:11  qhssian
//      Changed fetchOrder return-value to TIMEERR
//
//      Revision 24.0  1995/11/28  16:59:18  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.1  95/10/04  18:05:03  18:05:03  qhsalte (Orjan Altebro)
//      Changes for Solaris2, CHWCH_XM22
//
//      Revision 23.0  1995/09/07  17:47:29  ehscama
//      Made release XM2S1, ehscama.
//
//      Revision 22.4  1995/08/30  15:58:45  ehscama
//      Merged in changes between 16.0 and 16.0.1.2.
//
//      Revision 22.3  1995/08/30  15:14:44  ehscama
//      Added init of OZT attributes in sysCmdFileToOrderData.
//
//      Revision 22.2  1995/08/15  10:44:52  qhsjody
//      Changed some ifdef's.
//
//      Revision 22.1  1995/08/14  10:22:03  qhsiabr
//      Added initialization of the OZT members to cmdFileToOrderData.
//
//      Revision 22.0  1995/08/01  20:48:49  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 20.2  95/07/07  14:11:07  14:11:07  ehscama (Martin Carlsson VK/EHS/PXE)
//      *** empty log message ***
//
//      Revision 20.1  95/06/16  13:14:17  13:14:17  ehsphad (Pierre Hagnestrand VK/EHS/PXE)
//      Added display for both gui and nui in OZTOrders. To differ the two
//      kinds a new method isDisplayOn used.
//
//      Revision 20.0  1995/06/08  08:37:28  cmcha
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.3  95/06/07  13:07:56  13:07:56  epanyc (Nelson Cheng VK/EHS/PXE)
//      start time implementation changed
//
//      Revision 19.2  1995/06/01  12:37:54  ehsphad
//      Added routing possebilitys for ozterm orders . CCR 11
//
//      Revision 19.1  1995/05/31  15:00:47  ehscama
//      Changed definition of CHA_EXECUTABLE_PATH for TPF 400.
//
//      Revision 19.0  1995/04/13  10:56:40  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.2  95/04/03  13:16:49  13:16:49  epatse (Eric Tse VK/EHS/PXE)
//      The return code "CHA_AM_JOBEXISTS" is added for the function storeOrder().
//
//      Revision 18.1  1995/03/23  19:40:55  ehscama
//      Changed to mktime for SunOS5.
//
//      Revision 18.0  1995/03/17  20:09:18  cmcha
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.1  95/03/17  15:41:16  15:41:16  ehsphad (Pierre Hagnestrand VK/EHS/PXE)
//      Added ELBArId for OZT and cmd file converters.
//
//      Revision 17.0  1995/03/16  14:10:56  cmcha
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0.1.2  1995/08/16  09:42:24  ehscama
//      Introduced a static time control object.
//      Added check if order is already in crontab when activating it.
//      This solves TRs EE51210 and EE3395 and EE50884.
//
//      Revision 16.0.1.1  1995/08/01  14:57:45  ehscama
//      Forced check in by EHSPHAD, author EHSCAMA
//
//      Revision 16.0  95/03/10  13:03:36  13:03:36  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  15:08:51  15:08:51  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.1  1995/02/27  13:36:37  epatse
//      fixed memory leak
//
//      Revision 14.0  1995/02/25  16:37:19  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.7  95/02/17  11:43:39  11:43:39  qhskred (Krister Eklund VK/EHS/PXE)
//      More changes due to ordertype CHA_ORDKIND_OZTCMDFILE
//
//      Revision 13.6  1995/02/16  16:03:31  qhskred
//      Added support for CHA_OztCmdFileOrder
//
//      Revision 13.5  1995/02/15  14:10:16  cmcha
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	TB53_OZ 1995-11-28      J Grape (EHSGRAP)       RCS rev 24.0
//	XM2S1   1995-09-07      ehscama                 RCS rev 23.0
//	EC2_OZ  1995-08-01      Jan Sandquist (EHSJAASA)RCS rev 22.0
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
//      CHA_Order		user
//      CHA_SysCmdFileOrder     user
//      CHA_CmdFileOrder        user
//      CHA_ExecOrderList       user

//**********************************************************************

#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_Converter.H>
//#include <sysent.h>
#include <time.h>
#include <rw/cstring.h>
#include <rw/tools/datetime.h>
#include <stdlib.h>
//TORF-241666
//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_Converter", (char*)"C");

/* This is moved to CHA_LibGlobals
// Constants needed by old GUI-code that has been copied (or just used)
#if TPF >= 400
const char* CHA_EXECUTABLE_PATH = "/opt/tmos/bin";
#else
const char* CHA_EXECUTABLE_PATH = "/usr/local/tmos/bin";
#endif
*/
// char* CHA_SYSCMDFILE = "/users/tmosadm/common_files/appl/cha_syscmdfile";
char* CHA_SYSCMDFILE = NULL;
//const char* CHA_SYSADM = "tmosadm";

static TAS_TCCH_time_control* tc_base = NULL;

// Member functions, constructors, destructors, operators


//**********************************************************************


CHA_Converter::CHA_Converter()
:keyList(NULL),
 userInfo()
{
    //TRACE_IN(trace, CHA_Converter, "");

    if (CHA_SYSCMDFILE == NULL)
    {
	CHA_SYSCMDFILE = getenv("CHA_SYSCMDFILE");
    }
};

//**********************************************************************

CHA_Converter::~CHA_Converter()
{
    // Empty
};

//**********************************************************************

void CHA_Converter::constructTimeControl()
{
    if (tc_base == NULL)
      tc_base = new TAS_TCCH_time_control();
}

//**********************************************************************

void CHA_Converter::destructTimeControl()
{
    if (tc_base != NULL)
	delete tc_base;
}

//**********************************************************************

int CHA_Converter::activate(CHA_Order& order)
{
    int              answer         = 1;
    AM_OrderData*    data;
    AM_OrderStorage  *pOrderStorage = new AM_OrderStorage;
    AM_ttcbFunctions ttcb;

    //TRACE_IN(trace, Activate, "");

    // lock the database 
    /*answer = pOrderStorage->lock();
    if (answer != AM_DB_OK)
    {
	delete pOrderStorage;
	switch(answer)
	{
	    case AM_DB_NO_MEMORY:
		answer = CHA_AM_NO_MEMORY;
		break;
	    default:
		answer = CHA_AM_ERROR;
	}
	return answer;
    };

    // Move information to a format known by Tas

    data = new AM_OrderData;

    switch (order.getOrderKind())
    {
	case CHA_ORDKIND_OZTCMDFILE:
	    answer = oztCmdFileToOrderData(data, (CHA_OztCmdFileOrder*) &order);
	    break;
	default:
	    answer = AM_ERROR;
    };

    if (answer != AM_OK)
    {
	pOrderStorage->unlock();
	delete pOrderStorage;
	AM_auxFunctions::deleteStrings(data);
	delete data; data = 0;
	//TRACE_FLOW(trace, ErrorFileToOrderActivate, answer);
	return answer;
    };

    // Introducing order in crontab but
    // first check if it is already in crontab...

    if (tc_base->is_scheduled(order.getTasId(), userInfo.loginName()) > 0)
    {
	answer = AM_JOBEXISTS;
    }
    else
    {
	answer = ttcb.initOrder(data, tc_base);
    }

    switch(answer)
    {
	case AM_OK:
	    break;
	case AM_JOBEXISTS:
	    // The order already exists in crontab, set the order to active
	    answer = AM_OK;
	    break;
	case AM_TIMEERR:
	    pOrderStorage->unlock();
	    delete pOrderStorage;
	    AM_auxFunctions::deleteStrings(data);
	    delete data; data = 0;
	    //TRACE_FLOW(trace, TooShortTimespanAtActivate, answer);
	    answer = CHA_AM_TIMEERR;
	    break;
	case AM_DB_BAD_ARGUMENT:
	    pOrderStorage->unlock();
	    delete pOrderStorage;
	    AM_auxFunctions::deleteStrings(data);
	    delete data; data = 0;
	    //TRACE_FLOW(trace, IllegalArgumentAtActivate, answer);
	    answer = CHA_AM_ILLEGAL_ARGUMENT;
	    break;
	case AM_DB_NO_MEMORY:
	    pOrderStorage->unlock();
	    delete pOrderStorage;
	    AM_auxFunctions::deleteStrings(data);
	    delete data; data = 0;
	    //TRACE_FLOW(trace, NoMemoryAtActivate, answer);
	    answer = CHA_AM_NO_MEMORY;
	    break;
	default:
	    pOrderStorage->unlock();
	    delete pOrderStorage;
	    AM_auxFunctions::deleteStrings(data);
	    delete data; data = NULL;
	    //TRACE_FLOW(trace, SomethingWrongTTCBInitOrder, answer);
	    answer = CHA_AM_ERROR;
    }

    if (answer != AM_OK)
	return answer;

    // change status to ACTIVE in the ndbm database, and move tasId
    order.setState(CHA_ORDER_SCHEDULED);
    order.setTasId(data->tasId);

    answer = pOrderStorage->setStatus(order.getOrderId(), AM_SCHEDULED);
    if (answer < 0)
    {
	pOrderStorage->unlock();
	delete pOrderStorage;
	AM_auxFunctions::deleteStrings(data);
	delete data; data = NULL;
 	//TRACE_FLOW(trace, SomethingWrongTTCBInitOrderSetStatus, answer);

	switch(answer)
	{
	    case AM_DB_BAD_ARGUMENT:
		answer = CHA_AM_ILLEGAL_ARGUMENT;
		break;
	    case AM_DB_KEY_DOES_NOT_EXIST:
		answer = CHA_AM_KEYNOTFOUND;
		break;
	    case AM_DB_NO_MEMORY:
		answer = CHA_AM_NO_MEMORY;
		break;
	    default:
		answer = CHA_AM_ERROR;
	}

	return answer;
    };

    answer = pOrderStorage->setTasId(order.getOrderId(), data->tasId);
    if (answer < 0)
    {
	pOrderStorage->unlock();
	delete pOrderStorage;
	AM_auxFunctions::deleteStrings(data);
	delete data; data = NULL;
 	//TRACE_FLOW(trace, SomethingWrongTTCBInitOrderSetStatus, answer);

	switch(answer)
	{
	    case AM_DB_BAD_ARGUMENT:
		answer = CHA_AM_ILLEGAL_ARGUMENT;
		break;
	    case AM_DB_KEY_DOES_NOT_EXIST:
		answer = CHA_AM_KEYNOTFOUND;
		break;
	    case AM_DB_NO_MEMORY:
		answer = CHA_AM_NO_MEMORY;
		break;
	    default:
		answer = CHA_AM_ERROR;
	}

	return answer;
    };

    answer = pOrderStorage->unlock();
    delete pOrderStorage;
    AM_auxFunctions::deleteStrings(data);
    delete data; data = 0;
    return answer;*/
};

//**********************************************************************

int CHA_Converter::suspend(CHA_Order& order)
{
    int answer = 1;
    AM_OrderData* data;
    AM_ttcbFunctions ttcb;
    AM_OrderStorage  *pOrderStorage = new AM_OrderStorage;

    //TRACE_IN(trace, Suspend, "");

    // lock the database
   /* answer = pOrderStorage->lock();
    if (answer != AM_DB_OK)
    {
	delete pOrderStorage;
	switch(answer)
	{
	    case AM_DB_NO_MEMORY:
		//TRACE_FLOW(trace, NoMemoryAtSuspend, answer);
		answer = CHA_AM_NO_MEMORY;
		break;
	    default:
		//TRACE_FLOW(trace, SomethingWrongLockAtSuspend, "");
		answer = CHA_AM_ERROR;
	}

	return answer;
    };

    // Move information to a format known by Tas

    data = new AM_OrderData;

    switch (order.getOrderKind())
    {
	case CHA_ORDKIND_OZTCMDFILE:
	    answer = oztCmdFileToOrderData(data, (CHA_OztCmdFileOrder*) &order);
	    break;
	default:
	    answer = AM_ERROR;
    };

    if (answer != AM_OK)
    {
	pOrderStorage->unlock();
	delete pOrderStorage;
	AM_auxFunctions::deleteStrings(data);
	delete data; data = 0;
	//TRACE_FLOW(trace, ErrorFileToOrderActivate, answer);
	return answer;
    };

    // Terminating order in Crontab
    answer = ttcb.terminateOrder(data, tc_base);

    // Informtion used, delete allocated memory
    AM_auxFunctions::deleteStrings(data);
    delete data; data = 0;

    switch(answer)
    {
	case AM_OK:
	    break;
	case AM_JOBNOTEXIST:
	    // Order does not exist in crontab, set the order to cancelled
	    answer = AM_OK;
	    break;
	case AM_DB_BAD_ARGUMENT:
	    pOrderStorage->unlock();
	    delete pOrderStorage;
	    //TRACE_FLOW(trace, IllegalArgumentAtSuspend, answer);
	    answer = CHA_AM_ILLEGAL_ARGUMENT;
	    break;
	case AM_DB_KEY_DOES_NOT_EXIST:
	    pOrderStorage->unlock();
	    delete pOrderStorage;
	    //TRACE_FLOW(trace, KeyDoesNotExistInNDBM, answer);
	    answer = CHA_AM_KEYNOTFOUND;
	    break;
	case AM_DB_NO_MEMORY:
	    pOrderStorage->unlock();
	    delete pOrderStorage;
	    //TRACE_FLOW(trace, NoMemoryAtSuspend, answer);
	    answer = CHA_AM_NO_MEMORY;
	    break;
	default:
	    pOrderStorage->unlock();
	    delete pOrderStorage; pOrderStorage = 0;
	    //TRACE_FLOW(trace, SomethingWrongInCrontab, "");
	    answer = CHA_AM_ERROR;
    }

    if (answer != AM_OK)
	return answer;

    // change status to SUSPENDED in the ndbm database
    order.setState(CHA_ORDER_CANCELLED);

    answer = pOrderStorage->setStatus(order.getOrderId(), AM_CANCELLED);
    if (answer < 0)
    {
	pOrderStorage->unlock();
	delete pOrderStorage;
	switch(answer)
	{
	    case AM_DB_BAD_ARGUMENT:
		answer = CHA_AM_ILLEGAL_ARGUMENT;
		break;
	    case AM_DB_KEY_DOES_NOT_EXIST:
		answer = CHA_AM_KEYNOTFOUND;
		break;
	    case AM_DB_NO_MEMORY:
		//TRACE_FLOW(trace, NoMemoryAtFetch, answer);
		answer = CHA_AM_NO_MEMORY;
		break;
	    default:
		answer = CHA_AM_ERROR;
	}
	return answer;
    };

    answer = pOrderStorage->unlock();
    delete pOrderStorage;
    return answer;*/
};

//**********************************************************************

int CHA_Converter::fetchOrder(const long orderKey,
			      CHA_Order& orderData)
{
    int    	answer;
    int         statusres;
    AM_OrderStorage * pOrderStorage = new AM_OrderStorage;
    AM_OrderData* data;

    //TRACE_IN(trace, fetchOrder, orderKey);

   /* answer = pOrderStorage->lock();
    if (answer != AM_DB_OK)
    {
      delete pOrderStorage;
      pOrderStorage = 0;
      switch(answer)
      {
        case AM_DB_NO_MEMORY:
          answer = CHA_AM_NO_MEMORY;
          break;
        default:
          answer = CHA_AM_ERROR;
      }
      return answer;
    }

    //TRACE_FLOW(trace, lockedDatabase, "");

    // retrieve order data from the database
    data = AM_auxFunctions::getAM_OrderDataObject();
    answer = pOrderStorage->retrieveData(orderKey, data);

    //TRACE_FLOW(trace, fetchedInfoFromNDBM, answer);

    if (answer != AM_DB_OK)
    {
      pOrderStorage->unlock();
      delete pOrderStorage; pOrderStorage = 0;
      AM_auxFunctions::deleteStrings(data);
      delete data; data = NULL;
      switch(answer)
      {
        case AM_DB_BAD_ARGUMENT:
          answer = CHA_AM_ILLEGAL_ARGUMENT;
          break;
        case AM_DB_NO_MEMORY:
          answer = CHA_AM_NO_MEMORY;
          break;
        case AM_DB_KEY_DOES_NOT_EXIST:
          answer = CHA_AM_KEYNOTFOUND;
          break;
        default:
          answer = CHA_AM_ERROR;
      }
      return answer;
    }

    // Move info to return object

    //TRACE_FLOW(trace, orderType, data->orderType);
    //TRACE_FLOW(trace, nameBefore, data->filename);

    switch (data->orderType)
    {
      case CHA_ORDKIND_OZTCMDFILE:
        answer = orderDataToOztCmdFile(data, (CHA_OztCmdFileOrder*) &orderData);
        break;
      default:
        answer = AM_ERROR;
    }

    if (answer != AM_DB_OK)
    {
      pOrderStorage->unlock();
      delete pOrderStorage; pOrderStorage = 0;
      AM_auxFunctions::deleteStrings(data);
      delete data; data = NULL;
      return CHA_AM_ERROR;
    }

    //TRACE_FLOW(trace, filenameFetchedOrder, data->filename);

    // Set correct status on order

    answer = AM_auxFunctions::checkDate(data->startTime);
    if ( (answer != AM_OK) && (answer != AM_OLD_DATE) )
    {
      pOrderStorage->unlock();
      delete pOrderStorage; pOrderStorage = 0;
      return CHA_AM_ERROR;
    }

    if (data->interval.intervalBase == AM_NONE)
    {
	// Orders that only will execute once
      if ((answer == AM_OLD_DATE) && (data->status != AM_CANCELLED))
      {
	    // Old date and not cancelled => completed
	    data->status = AM_COMPLETED;
	    orderData.setState(CHA_ORDER_COMPLETED);

	    statusres = pOrderStorage->setStatus(data->orderKey, AM_COMPLETED);
	}
	else
	{
	    if (tc_base->is_scheduled(orderData.getTasId(), userInfo.loginName()) > 0)
	    {
		// Exists in crontab => scheduled
		data->status = AM_SCHEDULED;
		orderData.setState(CHA_ORDER_SCHEDULED);

		statusres = pOrderStorage->setStatus
		    (data->orderKey, AM_SCHEDULED);
	    }
	    else
	    {
		// Nonexistent in crontab => cancelled since it's not completed
		data->status = AM_CANCELLED;
		orderData.setState(CHA_ORDER_CANCELLED);

		statusres = pOrderStorage->setStatus
		    (data->orderKey, AM_CANCELLED);
	    }
	}
    }
    else
    {
	// Order with interval, the only kind of order that can be ACTIVE
	if ((answer == AM_OLD_DATE) &&
	    (tc_base->is_scheduled(orderData.getTasId(), userInfo.loginName()) > 0))
	{
	    // Old date and present in crontab, i.e executing => ACTIVE
	    data->status = AM_ACTIVE;
	    orderData.setState(CHA_ORDER_ACTIVE);
	    statusres = pOrderStorage->setStatus(data->orderKey, AM_ACTIVE);
	}
	else
	{
	    if (answer == AM_OLD_DATE)
	    {
		// Old date and not present in crontab => cancelled
		data->status = AM_CANCELLED;
		orderData.setState(CHA_ORDER_CANCELLED);
		statusres = pOrderStorage->setStatus
		    (data->orderKey, AM_CANCELLED);
	    }
	    else
	    {
		int answer2 = AM_auxFunctions::checkDate(data->startTime - 123);
		if ( (answer2 != AM_OK) && (answer2 != AM_OLD_DATE) )
		{
		    pOrderStorage->unlock();
		    delete pOrderStorage; pOrderStorage = 0;
		    return CHA_AM_ERROR;
		}

		if (answer2 == AM_OLD_DATE)
		{
		    // Order is between now and now - 123,
		    // too close in time to update the list
		    pOrderStorage->unlock();
		    delete pOrderStorage; pOrderStorage = 0;
		    AM_auxFunctions::deleteStrings(data);
		    delete data; data = NULL;
		    return CHA_AM_TIMEERR;
		}

		if (tc_base->is_scheduled(orderData.getTasId(), userInfo.loginName()) > 0)
		{
		    // New date and present in crontab => scheduled
		    data->status = AM_SCHEDULED;
		    orderData.setState(CHA_ORDER_SCHEDULED);
		    statusres = pOrderStorage->setStatus
			(data->orderKey, AM_SCHEDULED);
		}
		else
		{
		    // New date and not present in crontab => cancelled
		    data->status = AM_CANCELLED;
		    orderData.setState(CHA_ORDER_CANCELLED);
		    statusres = pOrderStorage->setStatus
			(data->orderKey, AM_CANCELLED);
		}
	    }
	}
    }

    AM_auxFunctions::deleteStrings(data);
    delete data; data = NULL;

    pOrderStorage->unlock();
    delete pOrderStorage; pOrderStorage = 0;

    // Check result of status change in NDBM
    if (statusres < 0)
	return CHA_AM_ERROR;
    else
	return AM_OK;*/
};

//**********************************************************************

int CHA_Converter::storeOrder(CHA_Order& order)
{
    int answer = 1;
    int status;
    AM_ttcbFunctions ttcb;
    AM_OrderData* data;
    AM_OrderStorage * pOrderStorage = new AM_OrderStorage;

    //TRACE_IN(trace, storeOrder, "");

    // lock the database
/*    answer = pOrderStorage->lock();
    if (answer != AM_DB_OK)
    {
      delete pOrderStorage; pOrderStorage = 0;
      switch(answer)
      {
        case AM_DB_NO_MEMORY:
          answer = CHA_AM_NO_MEMORY;
          break;
        default:
          answer = CHA_AM_ERROR;
      }
      return answer;
    }

    if (order.getOrderId() < 1)
    {
	// New order
	// get a free key in the database
      long res = pOrderStorage->getFreeKey();
      if (res < 1)
      {
        pOrderStorage->unlock();
        delete pOrderStorage; pOrderStorage = 0;
        //TRACE_FLOW(trace, ErrorGettingNewKey, res);

        switch(res)
        {
          case AM_DB_NO_MEMORY:
            res = CHA_AM_NO_MEMORY;
            break;
          case AM_DB_KEY_NOT_FOUND:
            res = CHA_AM_KEYNOTFOUND;
            break;
          default:
            res = CHA_AM_ERROR;
        }
	    return res;
    }

    //TRACE_FLOW(trace, NewKey, res);

    long orderKey = res;

	// set key to the order

	order.setOrderId(orderKey);
	data = new AM_OrderData;

	switch (order.getOrderKind())
	{
	case CHA_ORDKIND_OZTCMDFILE:
	    answer = oztCmdFileToOrderData(data, (CHA_OztCmdFileOrder*) &order);
	    break;
	default:
	    answer = AM_ERROR;
  }

	if (answer != AM_OK)
	{
	    pOrderStorage->unlock();
	    delete pOrderStorage; pOrderStorage=NULL;
      AM_auxFunctions::deleteStrings(data);
	    delete data; data = 0;
	    //TRACE_FLOW(trace, ErrorCmdFileToOrder, answer);
	    // Clear orderid, order could not be stored
	    order.setOrderId(0);
	    return answer;
	}

	//------------------------------------------------------------
	// Introducing order in crontab
	//------------------------------------------------------------
        //TRACE_FLOW(trace,storeOrder,"tasId before initOrder");
        //TRACE_FLOW(trace,storeOrder,data->tasId);

	status = order.getState();
	//TRACE_FLOW(trace, AnswerGetStatus, status);
	if (status < 0)
	{
	    pOrderStorage->unlock();
	    delete pOrderStorage; pOrderStorage = NULL;
      //TRACE_FLOW(trace, ErrorInGetStatusAtInitInTTCB, status);
	    order.setOrderId(0);
	    switch(status)
	    {
		case AM_DB_BAD_ARGUMENT:
		    status = CHA_AM_ILLEGAL_ARGUMENT;
		    break;
		case AM_DB_KEY_DOES_NOT_EXIST:
		    status = CHA_AM_KEYNOTFOUND;
		    break;
		case AM_DB_NO_MEMORY:
		    //TRACE_FLOW(trace, NoMemoryAtFetch, answer);
		    status = CHA_AM_NO_MEMORY;
		    break;
		default:
		    answer = CHA_AM_ERROR;
	    }
	    return status;
	}
	else
	    if ((status == CHA_ORDER_ACTIVE) || (status == CHA_ORDER_SCHEDULED))
	    {
		answer = ttcb.initOrder(data, tc_base);
	    }

        //TRACE_FLOW(trace,storeOrder,data->orderKey);
        //TRACE_FLOW(trace,storeOrder,data->orderType);
        //TRACE_FLOW(trace,storeOrder,data->filename);
        //TRACE_FLOW(trace,storeOrder,data->networkElement);
        //TRACE_FLOW(trace,storeOrder,data->userId);
        //TRACE_FLOW(trace,storeOrder,data->status);
        //TRACE_FLOW(trace,storeOrder,data->outputDest);
        //TRACE_FLOW(trace,storeOrder,data->mailOutputDest);
        //TRACE_FLOW(trace,storeOrder,data->fileOutputDest);
        //TRACE_FLOW(trace,storeOrder,data->printOutputDest);
        //TRACE_FLOW(trace,storeOrder,data->immRouting);
        //TRACE_FLOW(trace,storeOrder,data->delRouting);
        //TRACE_FLOW(trace,storeOrder,data->startTime);
        //TRACE_FLOW(trace,storeOrder,data->interval.intervalBase);
        //TRACE_FLOW(trace,storeOrder,data->interval.split);
        //TRACE_FLOW(trace,storeOrder,data->mailAddress);
        //TRACE_FLOW(trace,storeOrder,data->funcBusyInterval);
        //TRACE_FLOW(trace,storeOrder,data->stopContNA);
        //TRACE_FLOW(trace,storeOrder,data->stopContPE);
        //TRACE_FLOW(trace,storeOrder,data->mailError);
        //TRACE_FLOW(trace,storeOrder,data->mailResult);
        //TRACE_FLOW(trace,storeOrder,data->synchro);
        //TRACE_FLOW(trace,storeOrder,data->outMsgMail);
        //TRACE_FLOW(trace,storeOrder,data->parameters);
        //TRACE_FLOW(trace,storeOrder,data->host);
        //TRACE_FLOW(trace,storeOrder,data->tasId);
        //TRACE_FLOW(trace,storeOrder,data->timestamp);
        //TRACE_FLOW(trace,storeOrder,data->OZTLabel);
        //TRACE_FLOW(trace,storeOrder,data->OZTDisplay);
        //TRACE_FLOW(trace,storeOrder,data->OZTDisplayOn);

	if (answer != AM_OK)
	{
	    pOrderStorage->deleteData(orderKey);
	    pOrderStorage->unlock();
	    AM_auxFunctions::deleteStrings(data);
	    delete data; data = 0;
	    delete pOrderStorage; pOrderStorage = 0;
	    //TRACE_FLOW(trace, ErrorInitOrderInCrontab, answer);
	    // Clear orderid, order could not be stored
	    order.setOrderId(0);
	    switch(answer)
	    {
		case AM_TIMEERR:
		    answer = CHA_AM_TIMEERR;
		    break;
		case AM_DB_BAD_ARGUMENT:
		    answer = CHA_AM_ILLEGAL_ARGUMENT;
		    break;
		case AM_DB_NO_MEMORY:
		    answer = CHA_AM_NO_MEMORY;
		    break;
                case AM_JOBEXISTS:
                    answer = CHA_AM_JOBEXISTS;
                    break;
		default:
		    //TRACE_FLOW(trace, SomethingWrongTTCBInitOrder, answer);
		    answer = CHA_AM_ERROR;
	    }
	    return answer;
	}

	// Move tas id to the order
	order.setTasId(data->tasId);

	// store Order data in the database
	answer = pOrderStorage->storeData(orderKey, data, AM_DB_INSERT);
	if (answer != AM_DB_OK)
	{
	    // Remove order from crontab
	    answer = ttcb.terminateOrder(data, tc_base);

	    pOrderStorage->unlock();
	    AM_auxFunctions::deleteStrings(data);
	    delete data; data = 0;
	    delete pOrderStorage; pOrderStorage = 0;
	    //TRACE_FLOW(trace, ErrorStoreData, answer);

	    // Clear orderid, order could not be stored
	    order.setOrderId(0);

	    switch(answer)
	    {
		case AM_DB_NO_MEMORY:
		    answer = CHA_AM_NO_MEMORY;
		    break;
		case AM_DB_BAD_ARGUMENT:
		    answer = CHA_AM_ILLEGAL_ARGUMENT;
		    break;
		case AM_DB_KEY_DOES_NOT_EXIST:
		    answer = CHA_AM_KEYNOTFOUND;
		    break;
		case AM_DB_KEY_ALREADY_EXISTS:
		    answer = CHA_AM_KEYEXISTS;
		    break;
		default:
		    answer = CHA_AM_ERROR;
	    }
	    return answer;
	}

    }
    else
    {
	// =========================================================
	// Modify old order
	// =========================================================


        //--------------------------------------------------------
        // Terminating order in crontab
        //--------------------------------------------------------

        // retrieve order data to be modified from the database

        AM_OrderData* oldData;

        oldData = AM_auxFunctions::getAM_OrderDataObject();
        answer = pOrderStorage->retrieveData(order.getOrderId(), oldData);

        if (answer != AM_DB_OK)
        {
	    pOrderStorage->unlock();
	    delete pOrderStorage; pOrderStorage = 0;
	    AM_auxFunctions::deleteStrings(oldData);
	    delete oldData; oldData = NULL;
	    //TRACE_FLOW(trace, ModifyOrderCouldNotFetchInfo, answer);
	    switch(answer)
	    {
	        case AM_DB_BAD_ARGUMENT:
		     answer = CHA_AM_ILLEGAL_ARGUMENT;
		     break;
	        case AM_DB_NO_MEMORY:
		     answer = CHA_AM_NO_MEMORY;
		     break;
	        case AM_DB_KEY_DOES_NOT_EXIST:
		     answer = CHA_AM_KEYNOTFOUND;
		     break;
	        default:
		     answer = CHA_AM_ERROR;
	    }
	    return answer;
        }

        //TRACE_FLOW(trace, Terminatingorder, order.getOrderId());

        answer = ttcb.terminateOrder(oldData, tc_base);

	switch(answer)
	{
	    case AM_OK:
		break;
	    case AM_JOBNOTEXIST:
		//TRACE_FLOW(trace, TermOrderErrorNotExistCrontab, "");
		break;
	    default:
		//TRACE_FLOW(trace, TermOrderError, answer);
		switch(answer)
		{
		    case AM_DB_BAD_ARGUMENT:
			answer = CHA_AM_ILLEGAL_ARGUMENT;
			break;
		    case AM_DB_KEY_DOES_NOT_EXIST:
			answer = CHA_AM_KEYNOTFOUND;
			break;
		    case AM_DB_NO_MEMORY:
			answer = CHA_AM_NO_MEMORY;
			break;
		    default:
			answer = CHA_AM_ERROR;
		}
		pOrderStorage->unlock();
		AM_auxFunctions::deleteStrings(oldData);
		delete oldData; oldData = NULL;
		delete pOrderStorage; pOrderStorage = NULL;
		return answer;
	}

        // Fetch new order values

	data = new AM_OrderData;

	switch (order.getOrderKind())
	{
		case CHA_ORDKIND_OZTCMDFILE:
		answer = oztCmdFileToOrderData(data, (CHA_OztCmdFileOrder*) &order);
		break;

		default:
		answer = AM_ERROR;
	}

	if ((answer != AM_OK) && (answer != AM_DB_OK))
	{
	    pOrderStorage->unlock();
	    AM_auxFunctions::deleteStrings(data);
	    delete data; data = NULL;
	    delete pOrderStorage; pOrderStorage = NULL;
	    //TRACE_FLOW(trace, ErrorMovingInfo, answer);

	    // Restore old order in crontab

	    ttcb.initOrder(oldData, tc_base);
	    AM_auxFunctions::deleteStrings(oldData);
	    delete oldData; oldData = 0;

	    return CHA_AM_ERROR;
	};


	//------------------------------------------------------------
	// Introducing order in crontab
	//------------------------------------------------------------

	answer = ttcb.initOrder(data, tc_base);
	//TRACE_FLOW(trace, answerAfterTTCBInitOrderAtModify, answer);

	if (answer != AM_OK)
	{
	    pOrderStorage->unlock();
	    AM_auxFunctions::deleteStrings(data);
	    delete data; data = 0;
	    delete pOrderStorage; pOrderStorage = 0;

	    //TRACE_FLOW(trace, ErrorInitOrderInCrontab, answer);
	    switch(answer)
	    {
		case AM_TIMEERR:
		    answer = CHA_AM_TIMEERR;
		    break;
		case AM_DB_BAD_ARGUMENT:
		    answer = CHA_AM_ILLEGAL_ARGUMENT;
		    break;
		case AM_DB_NO_MEMORY:
		    answer = CHA_AM_NO_MEMORY;
		    break;
                case AM_JOBEXISTS:
                    answer = CHA_AM_JOBEXISTS;
                    break;
		default:
		    //TRACE_FLOW(trace, SomethingWrongTTCBInitOrder, answer);
		    answer = CHA_AM_ERROR;
	    }

	    // Restore old order in crontab

	    ttcb.initOrder(oldData, tc_base);
	    AM_auxFunctions::deleteStrings(oldData);
	    delete oldData; oldData = 0;

	    return answer;
	}


	// Move tas id to order
	order.setTasId(data->tasId);

	// Replace the Order data in the database
	answer = pOrderStorage->storeData(order.getOrderId(),
					  data, AM_DB_REPLACE);
	if (answer != AM_DB_OK)
	{
	    // Remove order from crontab
	    answer = ttcb.terminateOrder(data, tc_base);
	    pOrderStorage->unlock();
	    AM_auxFunctions::deleteStrings(data);
	    delete data; data = NULL;
	    delete pOrderStorage; pOrderStorage = NULL;
	    switch(answer)
	    {
		case AM_DB_NO_MEMORY:
		    answer = CHA_AM_NO_MEMORY;
		    break;
		case AM_DB_BAD_ARGUMENT:
		    answer = CHA_AM_ILLEGAL_ARGUMENT;
		    break;
		case AM_DB_KEY_DOES_NOT_EXIST:
		    answer = CHA_AM_KEYNOTFOUND;
		    break;
		case AM_DB_KEY_ALREADY_EXISTS:
		    answer = CHA_AM_KEYEXISTS;
		    break;
		default:
		    answer = CHA_AM_ERROR;
	    }

	    // Restore old order in crontab

	    ttcb.initOrder(oldData, tc_base);
	    AM_auxFunctions::deleteStrings(oldData);
	    delete oldData; oldData = 0;

	    return answer;
	}

	AM_auxFunctions::deleteStrings(oldData);
	delete oldData; oldData = 0;
    }

    answer = pOrderStorage->unlock();
    if (answer != AM_DB_OK)
	answer = CHA_AM_ERROR;
    else
    	answer = AM_OK;

    AM_auxFunctions::deleteStrings(data);
    delete data; data = 0;

    delete pOrderStorage, pOrderStorage = 0;

    return answer;*/
};

//**********************************************************************

int CHA_Converter::removeOrder(const long orderId)
{
    int answer = AM_DB_OK;
    AM_ttcbFunctions ttcb;
    AM_OrderData* data;
    AM_OrderStorage * pOrderStorage = new AM_OrderStorage;

    //TRACE_IN(trace, removeOrder, "");

    // lock the database
/*    answer = pOrderStorage->lock();
    if (answer != AM_DB_OK)
    {
	delete pOrderStorage; pOrderStorage = 0;
        //TRACE_FLOW(trace, UnableToLockDbREMOVE, answer);
	switch(answer)
	{
	    case AM_DB_NO_MEMORY:
		answer = CHA_AM_NO_MEMORY;
		break;
	    default:
		answer = CHA_AM_ERROR;
	}
	return answer;
    };

    //--------------------------------------------------------
    // Terminating order in crontab
    //--------------------------------------------------------

    // retrieve order data from the database
    data = AM_auxFunctions::getAM_OrderDataObject();
    answer = pOrderStorage->retrieveData(orderId, data);

    if (answer != AM_DB_OK)
    {
	pOrderStorage->unlock();
	delete pOrderStorage; pOrderStorage = 0;
	AM_auxFunctions::deleteStrings(data);
	delete data; data = NULL;
	//TRACE_FLOW(trace, removeOrderCouldNotFetchInfo, answer);
	switch(answer)
	{
	    case AM_DB_BAD_ARGUMENT:
		answer = CHA_AM_ILLEGAL_ARGUMENT;
		break;
	    case AM_DB_NO_MEMORY:
		answer = CHA_AM_NO_MEMORY;
		break;
	    case AM_DB_KEY_DOES_NOT_EXIST:
		answer = CHA_AM_KEYNOTFOUND;
		break;
	    default:
		answer = CHA_AM_ERROR;
	}
	return answer;
    }

    //TRACE_FLOW(trace, TerminatingorderRemoveOrder, orderId);
    answer = ttcb.terminateOrder(data, tc_base);

    switch(answer)
    {
	case AM_OK:
	    break;
	case AM_JOBNOTEXIST:
	    //TRACE_FLOW(trace, TermOrderErrorNotExistCrontab, "");
	    break;
	default:
	    //TRACE_FLOW(trace, TermOrderError, answer);
	    switch(answer)
	    {
		case AM_DB_BAD_ARGUMENT:
		    answer = CHA_AM_ILLEGAL_ARGUMENT;
		    break;
		case AM_DB_KEY_DOES_NOT_EXIST:
		    answer = CHA_AM_KEYNOTFOUND;
		    break;
		case AM_DB_NO_MEMORY:
		    answer = CHA_AM_NO_MEMORY;
		    break;
		default:
		    answer = CHA_AM_ERROR;
	    }
	    pOrderStorage->unlock();
	    AM_auxFunctions::deleteStrings(data);
	    delete data; data = NULL;
	    delete pOrderStorage; pOrderStorage = NULL;
	    return answer;
    }

    //------------------------------------------------------------
    // Delete Order
    //------------------------------------------------------------
    answer = pOrderStorage->deleteData(orderId);
    if (answer != AM_DB_OK)
    {
	pOrderStorage->unlock();
	AM_auxFunctions::deleteStrings(data);
	delete data; data = NULL;
	delete pOrderStorage; pOrderStorage = 0;
        //TRACE_FLOW(trace, UnableToRemoveData, answer);
	switch(answer)
	{
	    case AM_DB_BAD_ARGUMENT:
		answer = CHA_AM_ILLEGAL_ARGUMENT;
		break;
	    case AM_DB_NO_MEMORY:
		answer = CHA_AM_NO_MEMORY;
		break;
	    case AM_DB_KEY_DOES_NOT_EXIST:
		answer = CHA_AM_KEYNOTFOUND;
		break;
	    default:
		answer = CHA_AM_ERROR;
	}
	return answer;
    };

    // unlock the database
    answer = pOrderStorage->unlock();
    if (answer != AM_DB_OK)
    {
	AM_auxFunctions::deleteStrings(data);
	delete data; data = NULL;
	delete pOrderStorage; pOrderStorage = 0;
        //TRACE_FLOW(trace, UnableToUnlockDbREMOVE, answer);
	return CHA_AM_ERROR;
    };

    AM_auxFunctions::deleteStrings(data);
    delete data; data = NULL;
    delete pOrderStorage;
    pOrderStorage = 0;

    return answer;*/

};

//*****************************************************************************

int CHA_Converter::oztCmdFileToOrderData(AM_OrderData *orderData,
				         CHA_OztCmdFileOrder *inOrder)
{
    RWCString immRouting;

    //TRACE_IN(trace, oztCmdFileToOrderData, "");

    // Initialize values in orderData

    orderData->orderKey = AM_NOT_DEFINED;
    orderData->orderType = AM_NOT_DEFINED;
    orderData->filename = NULL;
    orderData->networkElement = NULL;
    orderData->userId = NULL;
    orderData->status = AM_IDLE;
    orderData->outputDest = NULL;
    orderData->mailOutputDest = NULL;
    orderData->fileOutputDest = NULL;
    orderData->printOutputDest = NULL;
    orderData->immRouting = NULL;
    orderData->delRouting = NULL;
    orderData->startTime = 0;
    orderData->interval.intervalBase = AM_NONE;
    orderData->interval.split = AM_NOT_DEFINED;
    orderData->mailAddress = NULL;
    orderData->funcBusyInterval = 0;
    orderData->stopContNA = AM_NOT_DEFINED;
    orderData->stopContPE = AM_NOT_DEFINED;
    orderData->mailError = AM_NOT_DEFINED;
    orderData->mailResult = AM_NOT_DEFINED;
    orderData->synchro = FALSE;
    orderData->outMsgMail = AM_NOT_DEFINED;
    orderData->parameters = NULL;
    orderData->host = NULL;
    orderData->tasId = 0;
    orderData->timestamp = 0;
    orderData->OZTLabel = NULL;
    orderData->OZTDisplay = NULL;
    orderData->OZTDisplayOn = FALSE;

    // Move values from CmdFileOrder

    orderData->orderKey    = inOrder->getOrderId();
    orderData->orderType   = CHA_ORDKIND_OZTCMDFILE;

    orderData->filename = new char [strlen(inOrder->getName().data())+1];
    if (orderData->filename != NULL)
	strcpy(orderData->filename, inOrder->getName().data());

    RWCString user = userInfo.loginName();
    orderData->userId = new char [strlen(user.data())+1];
    if (orderData->userId != NULL)
	strcpy(orderData->userId, user.data());

   switch(inOrder->getState())
    {
	case CHA_ORDER_CANCELLED:
	    orderData->status = AM_CANCELLED;
	    break;
	case CHA_ORDER_COMPLETED:
	    orderData->status = AM_COMPLETED;
	    break;
	case CHA_ORDER_ACTIVE:
	    orderData->status = AM_ACTIVE;
	    break;
	case CHA_ORDER_IDLE:
	    orderData->status = AM_IDLE;
	    break;
	case CHA_ORDER_SCHEDULED:
	    orderData->status = AM_SCHEDULED;
	    break;
    };

    orderData->networkElement = new char
	[strlen(inOrder->getExternalSystem().data())+1];
    if (orderData->networkElement != NULL)
	strcpy(orderData->networkElement, inOrder->getExternalSystem().data());

    if (!inOrder->getExitMessageMailAddress().isNull())
    {
	orderData->mailAddress =
	    new char [inOrder->getExitMessageMailAddress().length()+1];
	if (orderData->mailAddress != NULL)
	    strcpy(orderData->mailAddress,
		   inOrder->getExitMessageMailAddress().data());
    }
    else
    {
	orderData->mailAddress =
	    new char [2];
	if (orderData->mailAddress != NULL)
	    strcpy(orderData->mailAddress, " ");
    }

    // Move values from interval

    if (inOrder->getInterval().getRepPeriod() == CHA_REPPER_HOURLY)
	orderData->interval.intervalBase = AM_HOURLY;
    if (inOrder->getInterval().getRepPeriod() == CHA_REPPER_DAILY)
	orderData->interval.intervalBase = AM_DAILY;
    if (inOrder->getInterval().getRepPeriod() == CHA_REPPER_WEEKLY)
	orderData->interval.intervalBase = AM_WEEKLY;
    if (inOrder->getInterval().getRepPeriod() == CHA_REPPER_MONTHLY)
	orderData->interval.intervalBase = AM_MONTHLY;
    if (inOrder->getInterval().getRepPeriod() == CHA_REPPER_ANNUALLY)
	orderData->interval.intervalBase = AM_ANNUALLY;
    if (inOrder->getInterval().getRepPeriod() == CHA_REPPER_NONE)
	orderData->interval.intervalBase = AM_NONE;

    if (inOrder->getInterval().getRepPeriod() == CHA_REPPER_WEEKLY)
    {
	if (inOrder->getInterval().getDayOfWeek() == CHA_DAYWEEK_SUNDAY)
	    orderData->interval.split = AM_SUNDAY;
	if (inOrder->getInterval().getDayOfWeek() == CHA_DAYWEEK_MONDAY)
	    orderData->interval.split = AM_MONDAY;
	if (inOrder->getInterval().getDayOfWeek() == CHA_DAYWEEK_TUESDAY)
	    orderData->interval.split = AM_TUESDAY;
	if (inOrder->getInterval().getDayOfWeek() == CHA_DAYWEEK_WEDNESDAY)
	    orderData->interval.split = AM_WEDNESDAY;
	if (inOrder->getInterval().getDayOfWeek() == CHA_DAYWEEK_THURSDAY)
	    orderData->interval.split = AM_THURSDAY;
	if (inOrder->getInterval().getDayOfWeek() == CHA_DAYWEEK_FRIDAY)
	    orderData->interval.split = AM_FRIDAY;
	if (inOrder->getInterval().getDayOfWeek() == CHA_DAYWEEK_SATURDAY)
	    orderData->interval.split = AM_SATURDAY;
    }
    else
    {
	orderData->interval.split = inOrder->getInterval().getNoOfRepeat();
    };

    if (inOrder->getInterval().isStartDateDefined() == TRUE)
    {
	orderData->startTime = inOrder->getInterval().retrieveStartTime();

/*
	//Creating the time structure
	tm 	startDateTime;

	inOrder->getInterval().getStartTime().extract(&startDateTime);

#if defined __hpux || defined SunOS5
	startDateTime.tm_isdst = -1;
	orderData->startTime = mktime(&startDateTime);
#else
	//THIS fix for TMOS/HP is recorded in PRIMA as C++.82
	orderData->startTime = timelocal(&startDateTime);
#endif
*/
    };
    if (!inOrder->getHost().isNull())
    {
	orderData->host =
	    new char [inOrder->getHost().length() +1];
	if (orderData->host != NULL)
	    strcpy(orderData->host, inOrder->getHost().data());
    }
    else
    {
	orderData->host =
	    new char [2];
	if (orderData->host != NULL)
	    strcpy(orderData->host, " ");
    }

      if (!inOrder->getStartLabel().isNull())
      {
  	orderData->OZTLabel =
  	    new char [inOrder->getStartLabel().length() +1];
  	if (orderData->OZTLabel != NULL)
  	    strcpy(orderData->OZTLabel, inOrder->getStartLabel().data());
      }
      else
      {
  	orderData->OZTLabel =
  	    new char [2];
  	if (orderData->OZTLabel != NULL)
  	    strcpy(orderData->OZTLabel, " ");
      }


      if (!inOrder->getDisplayName().isNull())
      {
  	orderData->OZTDisplay =
  	    new char [inOrder->getDisplayName().length() +1];
  	if (orderData->OZTDisplay != NULL)
  	    strcpy(orderData->OZTDisplay, inOrder->getDisplayName().data());
      }
      else
      {
  	orderData->OZTDisplay =
  	    new char [2];
  	if (orderData->OZTDisplay != NULL)
  	    strcpy(orderData->OZTDisplay, " ");
      }


     if (!inOrder->getOutputMailaddress().isNull())
      {
	immRouting += ":mail:";
	immRouting += inOrder->getOutputMailaddress().data();
      }
     if (!inOrder->getOutputFile().isNull())
      {
	immRouting += ":file:";
	immRouting += inOrder->getOutputMailaddress().data();
      }
     if (!inOrder->getOutputPrinter().isNull())
      {
	immRouting += ":printer:";
	immRouting += inOrder->getOutputMailaddress().data();
      }

     if (!immRouting.isNull())
     {
	 orderData->immRouting =
	     new char [immRouting.length() +1];
	 if (orderData->immRouting != NULL)
	     strcpy(orderData->immRouting, immRouting.data());
     }
     else
     {
	 orderData->immRouting =
	     new char [2];
	 if (orderData->immRouting != NULL)
	     strcpy(orderData->immRouting, " ");
     }

    orderData->OZTDisplayOn = inOrder->isDisplayOn();

    //TRACE_FLOW(trace, oztCmdFileToOrderData, orderData->tasId);
    orderData->tasId   = inOrder->getTasId();
    //TRACE_FLOW(trace, oztCmdFileToOrderData, orderData->tasId);
    //Creating the time structure
    tm 	timestamp;

    inOrder->getTimestamp().extract(&timestamp);

#if defined __hpux || defined SunOS5
    timestamp.tm_isdst = -1;
    orderData->timestamp = mktime(&timestamp);
#else
    //THIS fix for TMOS/HP is recorded in PRIMA as C++.82
    orderData->timestamp = timelocal(&timestamp);
#endif

    return AM_OK;
};

//*****************************************************************************

int CHA_Converter::orderDataToOztCmdFile(AM_OrderData *orderData,
				      CHA_OztCmdFileOrder *inOrder)
{
    RWCString synchChoice;
    CHA_ExecOrderInterval tmpInterval;

    //TRACE_IN(trace, orderDataToOztCmdFile, "");

    //TRACE_IN(trace, orderkey, orderData->orderKey);
    inOrder->setOrderId(orderData->orderKey);

    //TRACE_IN(trace, filename,orderData->filename);
    inOrder->setName(orderData->filename);

    switch(orderData->status)
    {
	case AM_CANCELLED:
	    inOrder->setState(CHA_ORDER_CANCELLED);
	    break;
	case AM_COMPLETED:
	    inOrder->setState(CHA_ORDER_COMPLETED);
	    break;
	case AM_ACTIVE:
	    inOrder->setState(CHA_ORDER_ACTIVE);
	    break;
	case AM_IDLE:
	    inOrder->setState(CHA_ORDER_IDLE);
	    break;
	case AM_SCHEDULED:
	    inOrder->setState(CHA_ORDER_SCHEDULED);
	    break;
    };

    //TRACE_FLOW(trace, MovedOrderInfo,"");

    inOrder->setExternalSystem(orderData->networkElement);
    inOrder->setExitMessageMailAddress(orderData->mailAddress);

    // Move values to interval

    if (orderData->interval.intervalBase == AM_HOURLY)
	tmpInterval.setRepPeriod(CHA_REPPER_HOURLY);
    if (orderData->interval.intervalBase == AM_DAILY)
	tmpInterval.setRepPeriod(CHA_REPPER_DAILY);
    if (orderData->interval.intervalBase == AM_WEEKLY)
	tmpInterval.setRepPeriod(CHA_REPPER_WEEKLY);
    if (orderData->interval.intervalBase == AM_MONTHLY)
	tmpInterval.setRepPeriod(CHA_REPPER_MONTHLY);
    if (orderData->interval.intervalBase == AM_ANNUALLY)
	tmpInterval.setRepPeriod(CHA_REPPER_ANNUALLY);
    if (orderData->interval.intervalBase == AM_NONE)
	tmpInterval.setRepPeriod(CHA_REPPER_NONE);

    //TRACE_FLOW(trace, StartTimeIn, orderData->startTime);

    if (orderData->startTime != 0)
    {
        tm* tmptime;
        tmptime = localtime(&(orderData->startTime));

	/*
	Changed due to Year 2000 problem.
	// Make date, NB january = 0, december = 11
        RWDate datum((tmptime->tm_mday),
		     (tmptime->tm_mon) + 1,
		     (tmptime->tm_year));
	*/

	// RWDate accepts tm*,i.e. we don't need to extract data for it.
        // This fixes also the problem with the year 2000.
        RWDate datum(tmptime);

        RWDateTime convtime(datum, (tmptime->tm_hour), (tmptime->tm_min), 0);
        tmpInterval.setStartTime(convtime);


        inOrder->setStartTime(convtime);

	tmpInterval.setStartDateDefined(TRUE);

    };

    if (tmpInterval.getRepPeriod() == CHA_REPPER_WEEKLY)
    {
	if (orderData->interval.split == AM_SUNDAY)
	    tmpInterval.setDayOfWeek(CHA_DAYWEEK_SUNDAY);
	if (orderData->interval.split == AM_MONDAY)
	    tmpInterval.setDayOfWeek(CHA_DAYWEEK_MONDAY);
	if (orderData->interval.split == AM_TUESDAY)
	    tmpInterval.setDayOfWeek(CHA_DAYWEEK_TUESDAY);
	if (orderData->interval.split == AM_WEDNESDAY)
	    tmpInterval.setDayOfWeek(CHA_DAYWEEK_WEDNESDAY);
	if (orderData->interval.split == AM_THURSDAY)
	    tmpInterval.setDayOfWeek(CHA_DAYWEEK_THURSDAY);
	if (orderData->interval.split == AM_FRIDAY)
	    tmpInterval.setDayOfWeek(CHA_DAYWEEK_FRIDAY);
	if (orderData->interval.split == AM_SATURDAY)
	    tmpInterval.setDayOfWeek(CHA_DAYWEEK_SATURDAY);
    }
    else
    {
	tmpInterval.setNoOfRepeat(orderData->interval.split);
    };

    inOrder->setInterval(tmpInterval);
    inOrder->setHost(orderData->host);
    inOrder->setStartLabel(orderData->OZTLabel);
    inOrder->setDisplayName(orderData->OZTDisplay);
    inOrder->setDisplayOn(orderData->OZTDisplayOn);

    inOrder->setTasId(orderData->tasId);

    if (orderData->timestamp != 0)
    {
        tm* tmptime2;
        tmptime2 = localtime(&(orderData->timestamp));

	/*
	Changed due to Year 2000 problem.
	// Make date, NB january = 0 .. december = 11
        RWDate datum((tmptime2->tm_mday),
		     (tmptime2->tm_mon) + 1,
		     (tmptime2->tm_year));
	*/

	// RWDate accepts tm*,i.e. we don't need to extract data for it.
        // This fixes also the problem with the year 2000.
        RWDate datum(tmptime2);

        RWDateTime convtime(datum, (tmptime2->tm_hour), (tmptime2->tm_min), 0);
        inOrder->setTimestamp(convtime);
    };

    if(orderData->immRouting !=0 )
    {
	RWCString immRouting = orderData->immRouting;
	RWCTokenizer     nextToken(immRouting);
	RWCString	     subString;
	subString = nextToken(":");

	if ( (!subString.isNull()) && (subString == "mail"))
	{
	    subString = nextToken(":");
	    inOrder->setOutputMailaddress(subString);
	    subString = nextToken(":");
	}

     	if ( (!subString.isNull()) && (subString == "file"))
	{
	    subString = nextToken(":");
	    inOrder->setOutputMailaddress(subString);
	    subString = nextToken(":");
	}
     	if ( (!subString.isNull()) && (subString == "printer"))
	{
	    subString = nextToken(":");
	    inOrder->setOutputMailaddress(subString);
	    subString = nextToken(":");
	}
    }

    return AM_DB_OK;
};

//*****************************************************************************

long CHA_Converter::getFirstKey()
{
    /*long answer;
    AM_OrderStorage  orderStorage;
    long  key;

    //TRACE_IN(trace, getFirstKey, "");

    if (keyList.entries() > 0)
    {
	keyList.clear();
	curKey = 0;
    };

    key = orderStorage.getFirstKey();

    //TRACE_FLOW(trace, GotFirstKey, key);

    if (key < 0)
    {
	switch(key)
	{
	    case AM_DB_NO_MEMORY:
		return CHA_AM_NO_MEMORY;
	    case AM_DB_KEY_NOT_FOUND:
		return CHA_AM_KEYNOTFOUND;
	    default:
		return CHA_AM_ERROR;
	}
    }

    if ((answer = checkKey(key)) < 0)
	return answer;

    //TRACE_FLOW(trace, AnswerAfterChecked, answer);

    if (answer > 0)
	keyList.insert(key);

    key = orderStorage.getNextKey();

    //TRACE_FLOW(trace, GotNextKey, key);

    while (key > 0)
    {
	if ((answer = checkKey(key)) < 0)
	{
	    curKey = 0;

	    //TRACE_FLOW(trace, somethingWrongInCheckKey, answer);
	    //TRACE_FLOW(trace, getFirstKeyReturningERROR, keyList(0));
	    //TRACE_FLOW(trace, getFirstKeyEntriesInListERROR, keyList.entries());
	    return keyList(0);
	    //return answer;
	};

	//TRACE_FLOW(trace, AnswerAfterCheckedIter, answer);

	// If key belongs to this user insert it in the keylist
	if (answer > 0)
	    keyList.insert(key);

	key = orderStorage.getNextKey();
	//TRACE_FLOW(trace, GotNextKeyIter, key);
    };

    curKey = 0;

    if (keyList.entries() == 0)
    {
    	//TRACE_FLOW(trace, GotNextKeyIter, "KeyList is empty!");
    	return CHA_AM_KEYNOTFOUND;
    }

    //TRACE_FLOW(trace, getFirstKeyReturning, keyList(0));
    //TRACE_FLOW(trace, getFirstKeyEntriesInList, keyList.entries());
    return keyList(0);*/
};

//*****************************************************************************

long CHA_Converter::getNextKey()
{
  /*  curKey = curKey + 1;

    //TRACE_IN(trace, getNextKey, "");

    if (curKey < keyList.entries())
    {
	//TRACE_FLOW(trace, getNextKeyReturning, keyList(curKey));
	return keyList(curKey);
    };

    return CHA_AM_KEYNOTFOUND;*/
};

//*****************************************************************************

int CHA_Converter::fetchKind(const long orderKey)
{
    AM_OrderStorage * pOrderStorage = new AM_OrderStorage;
    AM_OrderData* data;
    int answer;

    //TRACE_IN(trace, fetchKind, "");
/*    answer = pOrderStorage->lock();
    if (answer != AM_DB_OK)
    {
	delete pOrderStorage;
	pOrderStorage = 0;
	switch(answer)
	{
	    case AM_DB_NO_MEMORY:
		answer = CHA_AM_NO_MEMORY;
		break;
	    default:
		answer = CHA_AM_ERROR;
	}
	return answer;
    }

    // retrieve order data from the database
    data = AM_auxFunctions::getAM_OrderDataObject();
    answer = pOrderStorage->retrieveData(orderKey, data);

    if (answer != AM_DB_OK)
    {
	pOrderStorage->unlock();
	delete pOrderStorage; pOrderStorage = 0;
	switch(answer)
	{
	    case AM_DB_BAD_ARGUMENT:
		answer = CHA_AM_ILLEGAL_ARGUMENT;
		break;
	    case AM_DB_NO_MEMORY:
		answer = CHA_AM_NO_MEMORY;
		break;
	    case AM_DB_KEY_DOES_NOT_EXIST:
		answer = CHA_AM_KEYNOTFOUND;
		break;
	    default:
		answer = CHA_AM_ERROR;
	}
	AM_auxFunctions::deleteStrings(data);
	delete data; data = NULL;
	return answer;
    };

    pOrderStorage->unlock();
    delete pOrderStorage; pOrderStorage = 0;
    answer = data->orderType;
    AM_auxFunctions::deleteStrings(data);
    delete data; data = NULL;

    //TRACE_OUT(trace, fetchKind, answer);
    return answer;*/
};

//*****************************************************************************

long CHA_Converter::checkKey(long orderKey)
{
    long answer = 0;
    AM_OrderStorage * pOrderStorage = 0;
    AM_OrderData * data = 0;

    pOrderStorage = new AM_OrderStorage;
/*    int result = pOrderStorage->lock();
    if (result != AM_DB_OK)
    {
	delete pOrderStorage; pOrderStorage = 0;
	//TRACE_FLOW(trace, checkkeyCouldNotLock, result);
	switch(result)
	{
	    case AM_DB_NO_MEMORY:
		result = CHA_AM_NO_MEMORY;
		break;
	    default:
		result = CHA_AM_ERROR;
	}
	return result;
    }

    // retrieve order data from the database
    data = AM_auxFunctions::getAM_OrderDataObject();
    result = pOrderStorage->retrieveData(orderKey, data);

    //TRACE_FLOW(trace, nameForFile, data->filename);

    if (result != AM_DB_OK)
    {
	pOrderStorage->unlock();
	delete pOrderStorage; pOrderStorage = 0;
	//TRACE_FLOW(trace, checkkeyCouldNotFetchInfo, result);
	switch(result)
	{
	    case AM_DB_BAD_ARGUMENT:
		result = CHA_AM_ILLEGAL_ARGUMENT;
		break;
	    case AM_DB_NO_MEMORY:
		result = CHA_AM_NO_MEMORY;
		break;
	    case AM_DB_KEY_DOES_NOT_EXIST:
		result = CHA_AM_KEYNOTFOUND;
		break;
	    default:
		result = CHA_AM_ERROR;
	}
	return result;
    }

    //TRACE_FLOW(trace, userid, data->userId);

    // Only keys for orders belonging to the current user should
    // be inserted in the keylist.

    if (userInfo.loginName() == data->userId)
    {
	// Order created by user
	answer = orderKey;
    };

    AM_auxFunctions::deleteStrings(data);
    delete data;
    pOrderStorage->unlock();
    delete pOrderStorage;
    return answer;*/
};
