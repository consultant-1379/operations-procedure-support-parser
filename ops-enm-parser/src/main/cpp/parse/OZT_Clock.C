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

#include <OZT_Clock.H>
#include <OZT_EventHandler.H>
#include <OZT_RunTimeNLS.H>
#include <CHA_NLSCatalog.H>



//*****************************************************************************


// trace

#include <trace.H>
static std::string trace ="OZT_Clock";
//static CAP_TRC_trace trace = CAP_TRC_DEF(((char*)"OZT_Clock"), ((char*)"C"));


//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_Clock.C,v 21.0 1996/08/23 12:43:32 ehsgrap Rel $";


//*****************************************************************************

extern OZT_EventHandler *ozt_evHandlerPtr;

//*****************************************************************************


OZT_Clock::OZT_Clock(OPS::ServerRouterListener_ptr theListener, OZT_CmdSender &cmdSender)
: state(IDLE),
  listener(theListener),
  commandSender(cmdSender)
{
    TRACE_IN(trace, OZT_Clock, "");

    // read in the nls stuff
    CHA_NLSCatalog catalog(OZT_RUN_TIME_NLS);

    timeToDelayMsg = catalog.getMessage(OZT_NLS_TIME_TO_DELAY,
                                        "Time left for delay:");
    timeToDelayMsg.append(" ");
    minsMsg = catalog.getMessage(OZT_NLS_MINS, "mins");
    secsMsg = catalog.getMessage(OZT_NLS_SECS, "secs");

    TRACE_OUT(trace, OZT_Clock, "");
}

//*****************************************************************************

OZT_Clock::~OZT_Clock()
{
}

//*****************************************************************************

void OZT_Clock::shutdown()
{
    TRACE_IN(trace, shutdown, "");

    if (state == BUSY)
    {
        ozt_evHandlerPtr->setResult(OZT_Result::INTERRUPTED);
        ozt_evHandlerPtr->unsetTickTrigger((void *)this);
    }

    TRACE_OUT(trace, shutdown, "");
}

//*****************************************************************************

OZT_Result OZT_Clock::delay(const OZT_Value &mins)
{
    TRACE_IN(trace, delay, mins);

    long minsV;
    OZT_Result result;

    minsV = mins.toLong(result);
    if (result.code != OZT_Result::NO_PROBLEM)
        return OZT_Result(OZT_Result::INVALID_VALUE);

    if (minsV > 0)
        startDelay(minsV * 60);

    TRACE_OUT(trace, delay, "");
    return OZT_Result(OZT_Result::NO_PROBLEM);
}

//*****************************************************************************

OZT_Result OZT_Clock::delaySec(const OZT_Value &secs)
{
    TRACE_IN(trace, delaySec, secs);

    long secsV;
    OZT_Result result;

    secsV = secs.toLong(result);
    if (result.code != OZT_Result::NO_PROBLEM)
        return OZT_Result(OZT_Result::INVALID_VALUE);

    if (secsV > 0)
        startDelay(secsV);

    TRACE_OUT(trace, delaySec, "");
    return OZT_Result(OZT_Result::NO_PROBLEM);
}

//*****************************************************************************

void OZT_Clock::startDelay(long secs)
{
    TRACE_IN(trace, startDelay, secs);

    OZT_Result dummy;

    originalStartTime = OZT_Time();
    secsForDelay = secs;

    if (secs > 5)
        informClient = TRUE;
    else
        informClient = FALSE;

    state = BUSY;
    while (secs > 0) {
        secs--;
        if (delayInterrupted == TRUE) {  // check for interrupt and break.
           setDelayInterrupt(FALSE);     // set delayInterrupted false for next run in same session.
           break;
        }
        if (secs > 60)
        {
            if (secs % 5 == 0) {
	        if(listener)
                listener->showTimeInfo(secs);
            }
        }
        else if (secs > 30 ) {
            if (secs % 2 == 0) {
                if(listener)
                listener->showTimeInfo(secs);
            }
        }
        else {
	    if(listener)
            listener->showTimeInfo(secs);
        }
        sleep(1);
    }
    state = IDLE;

    TRACE_OUT(trace, startDelay, "");
}

//*****************************************************************************

void OZT_Clock::interrupt()
{
    TRACE_IN(trace, interrupt, "");

    if (state == BUSY)
    {
        setDelayInterrupt(TRUE);
        ozt_evHandlerPtr->setResult(OZT_Result::INTERRUPTED);
	ozt_evHandlerPtr->unsetTickTrigger((void *)this);
        if (clientType == OPS::GUI) listener->showTimeInfo(-1);
    }

    TRACE_OUT(trace, interrupt, "");
}

//*****************************************************************************

void OZT_Clock::setDelayInterrupt(RWBoolean state){
   delayInterrupted = state;
}

//*****************************************************************************

void OZT_Clock::test()
{
     if (state == BUSY) {
         TRACE_FLOW(trace, test, "state: BUSY");
     } else {
         TRACE_FLOW(trace, test, "state: IDLE");
     }

     if (informClient) {
         TRACE_FLOW(trace, test, "informClient : true");
     } else {
         TRACE_FLOW(trace, test, "informClient : false");
     }

}

//*****************************************************************************

void OZT_Clock::setListener(OPS::ServerRouterListener_ptr theListener){
	TRACE_IN(trace, setListener, theListener);

	listener = theListener;

    TRACE_OUT(trace, setListener, "");
}

//*****************************************************************************

void OZT_Clock::setClientType(OPS::ClientType type){
	TRACE_IN(trace, setClientType, "listenerType_ = " << type);

	clientType = type;

	TRACE_OUT(trace, setClientType, "");
}

//*****************************************************************************

void OZT_Clock::aTick()
{
    TRACE_IN(trace, aTick, "");

    static OZT_Time lastTick;
    OZT_Time now;
    long secsLeftForDelay;

    if (state == BUSY)
    {
      // get the number of seconds left for the delay
      secsLeftForDelay = secsForDelay - (now - originalStartTime);

      // if no more seconds left, stops the delay...
      if (secsLeftForDelay <= 0)
	{
	  TRACE_FLOW(trace, aTick, "Time elapsed!");
	  secsLeftForDelay = 0;
	  ozt_evHandlerPtr->setResult(OZT_Result::NO_PROBLEM);
	  if (informClient && clientType == OPS::GUI)
	    listener->showTimeInfo(-1);
        }
      else if (informClient && (now != lastTick) && clientType == OPS::GUI)
        {
	  if (secsLeftForDelay > 60)
	    {
	      if (secsLeftForDelay % 5 == 0)listener->showTimeInfo(secsLeftForDelay);
	    }
	  else if (secsLeftForDelay > 30 )
	    {
	      if (secsLeftForDelay % 2 == 0)listener->showTimeInfo(secsLeftForDelay);
	    }
	  else
	    {
	      listener->showTimeInfo(secsLeftForDelay);
	    }
        }
      lastTick = now;
    }

    TRACE_OUT(trace, aTick, "");
}

//*****************************************************************************

int OZT_Clock::tick(void *instance)
{
  ((OZT_Clock *)instance)->aTick();

  return ozt_evHandlerPtr->notify_done();
}
