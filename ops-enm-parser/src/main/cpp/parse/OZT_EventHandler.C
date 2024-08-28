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

#include <OZT_EventHandler.H>

//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_EventHandler";


//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_EventHandler.C,v 21.0 1996/08/23 12:44:00 ehsgrap Rel $";


//*****************************************************************************

OZT_EventHandler::OZT_EventHandler()
{
    TRACE_IN(trace, OZT_EventHandler, "");

    TRACE_OUT(trace, OZT_EventHandler, "");
}

//*****************************************************************************

OZT_EventHandler::~OZT_EventHandler()
{
    ioClients.clearAndDestroy();
    chdClients.clearAndDestroy();
    timerClients.clearAndDestroy();
    tickClients.clearAndDestroy();
}

//*****************************************************************************

int OZT_EventHandler::notify_done() const
{
    return 0;
}

//*****************************************************************************

void OZT_EventHandler::startDispatch()
{
    TRACE_IN(trace, startDispatch, "");

    getOut = FALSE;
    while (!getOut)
    {
        sleepAWhile();
        dispatchEvents();
    }

    TRACE_OUT(trace, startDispatch, "");
}

//*****************************************************************************

void OZT_EventHandler::stopDispatch()
{
    TRACE_IN(trace, stopDispatch, "");

    static OZT_Result dummy(OZT_Result::UNDEFINED);

    getOut = TRUE;
    // result = dummy;

    TRACE_OUT(trace, stopDispatch, "");
}

//*****************************************************************************

OZT_Result OZT_EventHandler::waitResult(RWBoolean connCheckFlag)
{
    TRACE_IN(trace, waitResult, "");


    startDispatch();

    TRACE_RETURN(trace, waitResult, result); // result is set by setResult()
    return result;
}

//****************************************************************************

void OZT_EventHandler::setResult(OZT_Result theResult)
{
    TRACE_IN(trace, setResult, theResult);

    getOut = TRUE;
    result = theResult;

    TRACE_OUT(trace, setResult, "");
}

//****************************************************************************

void OZT_EventHandler::sleepAWhile()
{
    struct timeval tv;

    // For tv.tv_usec it has been noticed that a value of 500 works OK
    // on TPF 2 (HP-UX 9), but on TPF 4 (Solaris 2.4) this makes the
    // cha_developer_gui_bin process occupy the CPU at 80-90%.  A
    // value of 1000 works OK in both environments it seems.
    // ==================================================
    // Don't change tv.tv_sec and tv.tv_usec! They are important for
    // fast MML commands e.g. SYCLE.
    tv.tv_sec = 0;
    tv.tv_usec = 1000;
    (void)select(0, 0, 0, 0, &tv);
}

//****************************************************************************

void OZT_EventHandler::dispatchEvents()
{
    getOut = FALSE;
    dispatchIOEvents();
    dispatchTimerEvents();
    dispatchTickEvents();
    dispatchChdEvents();
    removeTrashedClients();
}

//****************************************************************************

void OZT_EventHandler::dispatchIOEvents()
{
    TRACE_IN(trace, dispatchIOEvents, "");

    for (size_t i = 0; i < ioClients.entries(); i++)
    {
        if (getOut) return;
        if (ioClients[i]->isValid())
            ioClients[i]->dispatch();
    }

    TRACE_OUT(trace, dispatchIOEvents, "");
}

//****************************************************************************

void OZT_EventHandler::dispatchChdEvents()
{
    TRACE_IN(trace, dispatchChdEvents, "");

    int tmp;
    int *stat_loc = &tmp;
    	for (size_t i = 0; i < chdClients.entries(); i++)
    	{
    		if (getOut) return;
    		if (chdClients[i]->isValid())
    		{
    			//
    			//  if the wanted child is dead, dispatch the event and
    			//  mark the client record to be trashed.
    			//
    			if (waitpid(chdClients[i]->pid, stat_loc, WNOHANG) == chdClients[i]->pid)
    			{
    				chdClients[i]->dispatchSignalEvent(stat_loc);
    				chdClients[i]->markToTrash();
    			}
    		}
    	}
 
    TRACE_OUT(trace, dispatchChdEvents, "");
}

//****************************************************************************

void OZT_EventHandler::dispatchTickEvents()
{
    TRACE_IN(trace, dispatchTickEvents, "");
    int delay = 0;//false
    for (size_t i = 0; i < tickClients.entries(); i++)
    {
        if (getOut) return;
        if (tickClients[i]->isValid()){

            tickClients[i]->dispatch();
            	delay = 1;//true
        }
    }
    if (delay == 1){
    	//Sleep 0.125 sec. before the timers arechecked again.
        usleep(125000);
    }
    TRACE_OUT(trace, dispatchTickEvents, "");
}

//****************************************************************************

void OZT_EventHandler::dispatchTimerEvents()
{
    TRACE_IN(trace, dispatchTimerEvents, "");
    int delay = 0; //false
    for (size_t i = 0; i < timerClients.entries(); i++)
    {
        if (getOut) return;
        if (timerClients[i]->isValid())
        {

            if (timerClients[i]->isExpired())
            {
                //
                // timer expires, dispatch the event
                // and mark the client record to be trashed
                //
                timerClients[i]->dispatch();
                timerClients[i]->markToTrash();
            }else{
        		delay = 1; //true
           }


        }
    }

    if (delay == 1){
       //Sleep 0.125 sec. before the timers are checked again.
       usleep(125000);
    }

    TRACE_OUT(trace, dispatchTimerEvents, "");
}

//************************************************************************

void OZT_EventHandler::removeTrashedClients()
{
    TRACE_IN(trace, removeTrashedClients, "");

    register int i;

    for (i = ioClients.entries() - 1; i >= 0; i--)
        if (ioClients[i]->toBeTrashed())
            delete ioClients.removeAt(i);

    for (i = timerClients.entries() - 1; i >= 0; i--)
        if (timerClients[i]->toBeTrashed())
            delete timerClients.removeAt(i);

    for (i = tickClients.entries() - 1; i >= 0; i--)
        if (tickClients[i]->toBeTrashed())
            delete tickClients.removeAt(i);

    for (i = chdClients.entries() - 1; i >= 0; i--)
        if (chdClients[i]->toBeTrashed())
            delete chdClients.removeAt(i);

    TRACE_OUT(trace, removeTrashedClients, "");
}

//************************************************************************

void OZT_EventHandler::setIOTrigger(void *instance, int (*func)(void *), int fd)
{
    TRACE_IN(trace, setIOTrigger, "");

    		OZT_IOClient *client = new OZT_IOClient(instance, func, fd);
 
    		ioClients.append(client);

    TRACE_OUT(trace, setIOTrigger, "");
}

//************************************************************************

void OZT_EventHandler::unsetIOTrigger(void *instance, int)
{
    TRACE_IN(trace, unsetIOTrigger, "");

    	for (size_t i = 0; i < ioClients.entries(); i++)
    	{
    		if (ioClients[i]->getInstance() == instance)
    			ioClients[i]->markToTrash();
    	}

    TRACE_OUT(trace, unsetIOTrigger, "");
}

//************************************************************************

void OZT_EventHandler::setSigChdTrigger(void *instance,
                                        pid_t pid,
                                        int (*func)(void *,pid_t,int *))
{
    TRACE_IN(trace, setSigChdTrigger, "");

    OZT_ChdClient *client;

    if (func == 0) {
        client = new OZT_ChdClient(instance, defaultSigChdCallBack, pid);
    } else {
        client = new OZT_ChdClient(instance, func, pid);
    }

    chdClients.append(client);

    TRACE_OUT(trace, setSigChdTrigger, "");
}


//*************************************************************************

void OZT_EventHandler::unsetSigChdTrigger(void *instance, pid_t pid)
{
    TRACE_IN(trace, unsetSigChdTrigger, "");

    	for (size_t i = 0; i < chdClients.entries(); i++)
    	{
    		if (chdClients[i]->getInstance() == instance)
    			chdClients[i]->markToTrash();
    	}

    TRACE_OUT(trace, unsetSigChdTrigger, "");
}

//*************************************************************************

void OZT_EventHandler::setTimer(void *instance, int (*func)(void *), long secs)
{
    TRACE_IN(trace, setTimer, secs);

    		OZT_TimerClient *client = new OZT_TimerClient(instance, func, secs);
    		timerClients.append(client);

    TRACE_OUT(trace, setTimer, "");
}

//*************************************************************************

void OZT_EventHandler::unsetTimer(void *instance)
{
    TRACE_IN(trace, unsetTimer, "");

    	for (size_t i = 0; i < timerClients.entries(); i++)
    	{
    		if (timerClients[i]->getInstance() == instance)
    			timerClients[i]->markToTrash();
    	}

    TRACE_OUT(trace, unsetTimer, "");
}

//*************************************************************************

void OZT_EventHandler::setTickTrigger(void *instance, int (*func)(void *))
{
    TRACE_IN(trace, setTickTrigger, "");

    		OZT_TickClient *client = new OZT_TickClient(instance, func);

    		tickClients.append(client);

    TRACE_OUT(trace, setTickTrigger, "");
}

//*************************************************************************

void OZT_EventHandler::unsetTickTrigger(void *instance)
{
    TRACE_IN(trace, unsetTickTrigger, "");

    	for (size_t i = 0; i < tickClients.entries(); i++)
    	{
    		if (tickClients[i]->getInstance() == instance)
    			tickClients[i]->markToTrash();
    	}

    TRACE_OUT(trace, unsetTickTrigger, "");
}

int OZT_EventHandler::defaultSigChdCallBack(void *,pid_t,int *)
{
    TRACE_IN(trace, defaultSigChdCallBack, "");

    return 0;
}

//*************************************************************************
//*************************************************************************


OZT_Client::OZT_Client()
{
    trashed = FALSE;
}

OZT_Client::~OZT_Client()
{

}

void OZT_Client::dispatch()
{
			OZT_Client::func(OZT_Client::instance);
		}

void OZT_Client::markToTrash()
{
    trashed = TRUE;
}

RWBoolean OZT_Client::isValid() const
{
    return !trashed;
}

RWBoolean OZT_Client::toBeTrashed() const
{
    return trashed;
}

void *OZT_Client::getInstance() const
{
    return instance;
}

//***********************************************************************

OZT_IOClient::OZT_IOClient(void *_instance,
                           int (*_func)(void*),
                           int _fd)
{
    OZT_IOClient::instance = _instance;
    OZT_IOClient::func     = _func;
    OZT_IOClient::fd       = _fd;
}

OZT_IOClient::~OZT_IOClient()
{

}

OZT_ClientType OZT_IOClient::type() const
{
    return OZT_IO_CLIENT;
}


RWBoolean OZT_IOClient::operator==(const OZT_Client &client) const
{
    if ((type() == client.type()) && (instance == client.getInstance()))
        return TRUE;
    else
	return FALSE;
}

//***********************************************************************

OZT_TimerClient::OZT_TimerClient(void *_instance,
                                 int (*_func)(void *),
                                 unsigned long secs)
{
    OZT_TimerClient::instance = _instance;
    OZT_TimerClient::func     = _func;
    OZT_TimerClient::timeToExpire = OZT_Time() + (time_t)secs;
}

OZT_TimerClient::~OZT_TimerClient()
{

}

OZT_ClientType OZT_TimerClient::type() const
{
    return OZT_TIMER_CLIENT;
}


RWBoolean OZT_TimerClient::isExpired() const
{
    if (timeToExpire.inHistory())
        return TRUE;
    else
        return FALSE;
}

RWBoolean OZT_TimerClient::operator==(const OZT_Client &client) const
{
    if ((type() == client.type()) && (instance == client.getInstance()))
        return TRUE;
    else
    	
	return FALSE;
}

//***********************************************************************

OZT_TickClient::OZT_TickClient(void *_instance, int (*_func)(void *))
{
    OZT_TickClient::instance = _instance;
    OZT_TickClient::func = _func;
}

OZT_TickClient::~OZT_TickClient()
{

}

OZT_ClientType OZT_TickClient::type() const
{
    return OZT_TICK_CLIENT;
}

RWBoolean OZT_TickClient::operator==(const OZT_Client &client) const
{
    if ((type() == client.type()) && (instance == client.getInstance()))
        return TRUE;
    else
	return FALSE;
}

//***********************************************************************

OZT_ChdClient::OZT_ChdClient(void *_instance,
                             int (*_func)(void *,pid_t,int *),
                             pid_t _pid)
{
    OZT_ChdClient::instance = _instance;
    OZT_ChdClient::function = _func;
    OZT_ChdClient::pid      = _pid;
}

OZT_ChdClient::~OZT_ChdClient()
{

}

OZT_ClientType OZT_ChdClient::type() const
{
    return OZT_CHD_CLIENT;
}

RWBoolean OZT_ChdClient::operator==(const OZT_Client &client) const
{
    if ((type() == client.type()) && (instance == client.getInstance()))
        return TRUE;
    else
	return FALSE;
}

void OZT_ChdClient::dispatchSignalEvent(int *stat)
{
			OZT_ChdClient::function(OZT_ChdClient::instance,OZT_ChdClient::pid,stat);
}
