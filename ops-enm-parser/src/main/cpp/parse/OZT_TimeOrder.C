/*------------------------------------------------------------------------------
 *******************************************************************************
 * COPYRIGHT Ericsson 2018
 *
 * The copyright to the computer program(s) herein is the property of
 * Ericsson Inc. The programs may be used and/or copied only with written
 * permission from Ericsson Inc. or in accordance with the terms and
 * conditions stipulated in the agreement/contract under which the
 * program(s) have been supplied.
 *******************************************************************************
 *----------------------------------------------------------------------------*/

#include <rw/rwtime.h>
#include <rw/rwdate.h>
#include <rw/tvordvec.h>
#include <unistd.h>
#include <CHA_UserInfo.H>
#include <OZT_TimeOrder.H>
#include <OZT_Time.H>

//*****************************************************************************


// trace
#include <CHA_Trace.H>
#include <trace.H>
static std::string trace ="OZT_TimeOrder";


//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_TimeOrder.C,v 21.0 1996/08/23 12:44:56 ehsgrap Rel $";


//*****************************************************************************

const RWCString ozt_emptyLabel = RWCString();

//*****************************************************************************

OZT_TimeOrderHandler::OZT_TimeOrderHandler(const RWCString &theDisplayInfo)
:ptheExecOrderList(0),
 displayInfo(theDisplayInfo)
{
   TRACE_IN(trace, OZT_TimeOrderHandler, "");

   TRACE_OUT(trace, OZT_TimeOrderHandler, "");
}

//*****************************************************************************

OZT_TimeOrderHandler::~OZT_TimeOrderHandler()
{
    if (ptheExecOrderList != 0)
    {
        delete ptheExecOrderList;
        ptheExecOrderList = 0;   // no need
    }
}

//*****************************************************************************

OZT_Value  OZT_TimeOrderHandler::setTimeEvent(const RWCString &currFileName,
                                              const RWCString &label,
                                              const RWCString &dateTimeExp,
                                              RWBoolean useDisplay)
{
   /*TRACE_IN(trace, setTimeEvent, "currFileName :" << currFileName <<
                                  ", label :"  << label <<
                                  ", datetime :" << dateTimeExp <<
                                  ", useDisplay :" << useDisplay);*/
   
    CHA_UserInfo userInfo;
    RWCString owner(userInfo.loginName());

    // the extSystem are not needed.
    return setTimeEvent(currFileName, label, dateTimeExp,
                        useDisplay, owner, RWCString());
return OZT_Value(0L);
}


//*****************************************************************************

OZT_Value  OZT_TimeOrderHandler::setTimeEvent(const RWCString &currFileName,
                                              const RWCString &label,
                                              const RWCString &dateTimeExp,
                                              RWBoolean useDisplay,
                                              const RWCString &mailAddress,
                                              const RWCString &extSystem)
{

   /*TRACE_IN(trace, setTimeEvent, "currFileName :" << currFileName <<
                                  ", label :"  << label <<
                                  ", datetime :" << dateTimeExp <<
                                  ", useDisplay :" << useDisplay <<
                                  ", mailAddress :" << mailAddress <<
                                  ", extSystem :" << extSystem);*/
   
    CHA_ExecOrderInterval interval;

    OZT_Time t(dateTimeExp);

    /*TRACE_FLOW(trace, setTimeEvent, "dateTimeExp : " << dateTimeExp << endl << 
                                    "t.tostring(): " << t.toString() << endl <<
                                    "Epoch sec   : " << t.toSecSinceEpoch());*/
    
    if (t.inHistory())
    {
         /*TRACE_RETURN(trace, setTimeEvent, "current time :"
                                          <<  OZT_Time().toString()
                                          << ", set time : "
                                          << t.toString() 
                                          << "3: Start time has elasped");*/
       
       return OZT_Value(2L);
    }

    CHA_OztCmdFileOrder *pOztCmdOrder;
    pOztCmdOrder = new CHA_OztCmdFileOrder;

    interval.setStartTime(t.toSecSinceEpoch());
//    interval.setStartDateDefined(TRUE);
//    interval.setDayOfWeek(CHA_DAYWEEK_NONE);
//    interval.setRepPeriod(CHA_REPPER_NONE);
//    pOztCmdOrder->setFuncBusyRetry(1);

    pOztCmdOrder->setInterval(interval);
    pOztCmdOrder->setName(currFileName);
    pOztCmdOrder->setStartLabel(label);

    if (!displayInfo.isNull())
        pOztCmdOrder->setDisplayName(displayInfo);

    if (useDisplay)
        pOztCmdOrder->setDisplayOn(TRUE);
    else
        pOztCmdOrder->setDisplayOn(FALSE);

    if (!mailAddress.isNull())
        pOztCmdOrder->setExitMessageMailAddress(mailAddress);
    else 
        pOztCmdOrder->setExitMessageMailAddress(RWCString());

    if (!extSystem.isNull()) 
        pOztCmdOrder->setExternalSystem(extSystem);
    else
        pOztCmdOrder->setExternalSystem(" ");  //**** Have to set this ****

    int orderRtnCode;

    // only create when needed....
    if (ptheExecOrderList == 0)
        ptheExecOrderList = new CHA_ExecOrderList;
 
    // add an order (no need to update the list here)
    if ((orderRtnCode=ptheExecOrderList->addOrder((CHA_Order *)pOztCmdOrder))
        < 0) 
    {
        TRACE_FLOW(trace, setTimeEvent, "orderRtnCode :" << orderRtnCode);
        delete pOztCmdOrder; pOztCmdOrder = 0;
        if (orderRtnCode == CHA_AM_TIMEERR)
        {
	   TRACE_RETURN(trace, setTimeEvent, 
	     "Start time too close to present time");
						
            return OZT_Value(3L);
        }

        TRACE_RETURN(trace, setTimeEvent, "addOrder failed");
        return OZT_Value(1L);
    }

    delete pOztCmdOrder; pOztCmdOrder = 0;

    TRACE_RETURN(trace, setTimeEvent, "0");

    return OZT_Value(0L);
}

//*****************************************************************************

void OZT_TimeOrderHandler::clearTimeEvent(const RWCString &currFileName,
                                          const RWCString &label)
{

/*TRACE_IN(trace, clearTimeEvent,"currFileName :" << currFileName <<
                                    ", label :" << label);
*/
    size_t            entries;
    CHA_OztCmdFileOrder *pOztCmdOrder;

    TRACE_FLOW(trace, clearTimeEvent,">>>>> before updatelist >>>>");

    // only create when needed...
    if (ptheExecOrderList == 0)
        ptheExecOrderList = new CHA_ExecOrderList;
    else
        ptheExecOrderList->updateList();

    TRACE_FLOW(trace, clearTimeEvent,"<<<<< after updatelist <<<<<");

    if ((entries = ptheExecOrderList->entries()) == 0)
    {
        TRACE_OUT(trace, clearTimeEvent, "");
        return;
    }

    RWTValOrderedVector<long> tobeDelete;

    //
    // mark the relevant orders to be removed
    //
    for (size_t i=0; i<entries; i++)
    {
        if ((* ptheExecOrderList)(i)->getOrderKind() == CHA_ORDKIND_OZTCMDFILE)
        {
            pOztCmdOrder = (CHA_OztCmdFileOrder *)(* ptheExecOrderList)(i);

            // If the order is for this file and the label matches, delete it
            if ((pOztCmdOrder->getName() == currFileName) &&
                ((label.isNull() || (pOztCmdOrder->getStartLabel() == label))))
            {
                tobeDelete.insert((long)pOztCmdOrder->getOrderId());
            }
        }
    }

    //
    // delete the orders found
    //
    for (size_t j=0; j<tobeDelete.entries(); j++)
    {
        TRACE_FLOW(trace,clearTimeEvent,"item order id :"<<tobeDelete[j]);

        if (ptheExecOrderList->removeOrder((long)tobeDelete[j]) < 0)
        {
            TRACE_OUT(trace, clearTimeEvent, "order cannot be removed");
            return;
        }
    }

    TRACE_OUT(trace, clearTimeEvent, "");

}                                      

//*****************************************************************************

RWBoolean OZT_TimeOrderHandler::eventLoaded(const RWCString &currFileName, 
                                            const RWCString &label)
{

   TRACE_IN(trace, eventLoaded, "currFileName :" << currFileName <<
     ", label :" << label);
   

    CHA_OztCmdFileOrder *pOztCmdOrder;
    size_t entries;

 TRACE_FLOW(trace, clearTimeEvent,">>>>> before updatelist >>>>");

    // only create when needed....
    if (ptheExecOrderList == 0)
        ptheExecOrderList = new CHA_ExecOrderList;
    else
        ptheExecOrderList->updateList();

  TRACE_FLOW(trace, clearTimeEvent,"<<<<< after updatelist <<<<<");

    if((entries=ptheExecOrderList->entries()) == 0)
    {
        TRACE_RETURN(trace, eventLoaded, "FALSE");
        return FALSE;
    }

    for (size_t i=0; i<entries; i++)
    {
        if ((* ptheExecOrderList)(i)->getOrderKind() == CHA_ORDKIND_OZTCMDFILE)
        {
            pOztCmdOrder = (CHA_OztCmdFileOrder *)(* ptheExecOrderList)(i);
 
            if ((pOztCmdOrder->getName() == currFileName) &&
                (pOztCmdOrder->getState() == CHA_ORDER_SCHEDULED) &&
                ((label.isNull() ||  (pOztCmdOrder->getStartLabel() == label))))
            {
                TRACE_RETURN(trace, eventLoaded, "TRUE");
                return TRUE;
            }
        }
    }
    
  TRACE_RETURN(trace, eventLoaded, "FALSE");

    return FALSE;
}

//*****************************************************************************

RWCString OZT_TimeOrderHandler::getSched(const RWCString &currFileName)
{

   TRACE_IN(trace, getSched, "currFileName :" << currFileName );

   CHA_OztCmdFileOrder *pOztCmdOrder;
   size_t entries;

   TRACE_FLOW(trace, clearTimeEvent,">>>>> before updatelist >>>>");

   // only create when needed....
   if (ptheExecOrderList == 0) {
    	TRACE_FLOW(trace, getSched,"ptheExecOrderList == 0");
        ptheExecOrderList = new CHA_ExecOrderList;
   }else {
    	TRACE_FLOW(trace, getSched,"ptheExecOrderList != 0");
        ptheExecOrderList->updateList();
   }

   TRACE_FLOW(trace, clearTimeEvent,"<<<<< after updatelist <<<<<");

   if((entries=ptheExecOrderList->entries()) == 0)
   {
        TRACE_RETURN(trace, getSched, "Scheduled file doesn't exists");
        return "0";
   }

   for (size_t i=0; i<entries; i++)
   {
       	if ((* ptheExecOrderList)(i)->getOrderKind() == CHA_ORDKIND_OZTCMDFILE)
        {
            pOztCmdOrder = (CHA_OztCmdFileOrder *)(* ptheExecOrderList)(i);
 
            if ((pOztCmdOrder->getName() == currFileName) &&
                (pOztCmdOrder->getState() == CHA_ORDER_SCHEDULED))
            {	
            	RWCString startDateAndTime = ((pOztCmdOrder->getStartTime()).asString('y') +
            				      (pOztCmdOrder->getStartTime()).asString('m') +
            				      (pOztCmdOrder->getStartTime()).asString('d') +
            				      (pOztCmdOrder->getStartTime()).asString('H') +
            				      (pOztCmdOrder->getStartTime()).asString('M'));
            	
                TRACE_RETURN(trace, getSched, "Scheduled file exists: " << startDateAndTime);
                return startDateAndTime;
            }
        }
   }
    
   TRACE_RETURN(trace, getSched, "Scheduled file doesn't exists");

   return "0";
}

//*****************************************************************************

void OZT_TimeOrderHandler::setDisplay(const RWCString &currentDisplay)
{
   TRACE_IN(trace, setDisplay, "currentDisplay :" << currentDisplay );
   displayInfo = currentDisplay;
}
