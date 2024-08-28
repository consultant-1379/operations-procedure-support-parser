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

#include <OZT_RspCatcher.H>
#include <OZT_EventHandler.H>


//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_RspCatcher";

//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_RspCatcher.C,v 21.0 1996/08/23 12:44:33 ehsgrap Rel $";


//*****************************************************************************

extern OZT_EventHandler *ozt_evHandlerPtr;

//*****************************************************************************


OZT_RspCatcher::OZT_RspCatcher(OPS::ServerRouterListener_ptr theListener,
                               OZT_CmdRspBuf &theCmdRspBuf,
                               OZT_Indicator &theIndicator,
                               OZT_CmdSender &theCmdSender)
: listener(theListener),
  cmdRspBuf(theCmdRspBuf),
  indicator(theIndicator),
  cmdSender(theCmdSender)
{
    TRACE_IN(trace, OZT_RspCatcher, "");

    okReply = RWCString();
    failReply = RWCString();
    changeState(IDLE);

    TRACE_OUT(trace, OZT_RspCatcher, "");
}


//*****************************************************************************

OZT_RspCatcher::~OZT_RspCatcher()
{
}

//*****************************************************************************

void OZT_RspCatcher::setListener(OPS::ServerRouterListener_ptr theListener) {
    listener = theListener;
}

//*****************************************************************************

OZT_Result OZT_RspCatcher::waitFor(const OZT_Value &str1, 
                                   const OZT_Value &str2,
                                   const RWBoolean indefinite,
                                   const OZT_Value &secs)
{
    TRACE_IN(trace, waitFor, str1 << ", " << str2 << ", " << indefinite
                              << "," << secs);
    OZT_Result result;
    long v;

    // set state as undefined (default state) in case there was an Interrupt earlier in the same session.
    ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::UNDEFINED));
    v = secs.toLong(result);
    if ((result.code != OZT_Result::NO_PROBLEM) || (v < 0))
    {
        TRACE_RETURN(trace, waitFor, "INVALID_VALUE");
        return OZT_Result(OZT_Result::INVALID_VALUE);
    }

    if (str1.isNull() && str2.isNull())
    {
        TRACE_RETURN(trace, waitFor, "INVALID_VALUE");
        return OZT_Result(OZT_Result::INVALID_VALUE);
    }

    if (cmdRspBuf.find(str1) && cmdRspBuf.find(str2))
    {
        TRACE_RETURN(trace, waitFor, "NO_PROBLEM (string has already arrived)");
        return OZT_Result(OZT_Result::NO_PROBLEM);
    }
    else
    {
        bool isIndefinite = false;
        if (!indefinite)
        {
            if (v == 0)  // you can't set 0 secs, so it is set to 1
                v = 1;
        }
        else {
            v = 1;
            isIndefinite = true;
        }

        changeState(WAITFOR);
	RWBoolean flag = TRUE;
        while (v > 0) {

            //check if state is interrupted (for SHIFT+STOP).
            OZT_Result curr_result = ozt_evHandlerPtr->getResult();
            if(curr_result.code == OZT_Result::INTERRUPTED){
               //unset timer on OPS Gui.
               listener->showTimeInfo(-1);
               return OZT_Result(OZT_Result::INTERRUPTED);
            }

            //cmdSender.sendCtrlChar(WinFIOLClient::RELEASE_CHAR, TRUE);
	    //cmdSender.sendCtrlChar(WinFIOLClient::RELEASE_CHAR, flag);
             cmdSender.sendLogoff(flag);

	    flag = FALSE;
            sleep(RESPONSE_CHECK_INTERVAL);
            if (cmdRspBuf.find(str1, 0) && cmdRspBuf.find(str2, 0)) {
                return OZT_Result(OZT_Result::NO_PROBLEM);
            }
            if (isIndefinite == false) {

                v = v - RESPONSE_CHECK_INTERVAL;
                if (v > 60) { 
                    if (v % 5 == 0) {
                        listener->showTimeInfo(v);
                    }
                }
                else if (v > 30 ) { 
                    if (v % 2 == 0) {
                        listener->showTimeInfo(v);
                    }
                }
                else {
                    listener->showTimeInfo(v);
                }
            }
            else {
                listener->showTimeInfo(v++);
            }
        }
        timeOut();
        result = OZT_Result(OZT_Result::TIME_EXPIRED);
        TRACE_RETURN(trace, waitFor, result.filtered());
        return result.filtered();
    }
}

//*****************************************************************************

OZT_RspCatcher::State OZT_RspCatcher::getState() {
  return state;
}

//*****************************************************************************

OZT_Result OZT_RspCatcher::waitReply(const RWBoolean indefinite,
                                     const OZT_Value &secs)
{
    TRACE_IN(trace, waitReply, indefinite << "," << secs);

    OZT_Result result;
    long v;

    // set state as undefined (default state) in case there was an Interrupt earlier in the same session.
    ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::UNDEFINED));
    v = secs.toLong(result);
    if ((result.code != OZT_Result::NO_PROBLEM) || (v < 0))
    {
        TRACE_RETURN(trace, waitReply, "INVALID_VALUE");
        return OZT_Result(OZT_Result::INVALID_VALUE);
    }
 
    result = waitReplyCheck();

    //
    //   If the end of reply is not seen yet, starts waiting
    //
    if (result.code == OZT_Result::UNDEFINED)
    {
        bool isIndefinite = false;
        if (!indefinite)
        {
            if (v == 0)  // you can't set 0 secs, so it is set to 1
                v = 1;
        }
        else {
            v = 1;
            isIndefinite = true;
        }

        changeState(WAITREPLY);
	RWBoolean flag = TRUE;
        while (v > 0) {

            //check if state is interrupted (for SHIFT+STOP).
            OZT_Result curr_result = ozt_evHandlerPtr->getResult();
            if(curr_result.code == OZT_Result::INTERRUPTED){
               //unset timer on OPS Gui.
               listener->showTimeInfo(-1);
               return OZT_Result(OZT_Result::INTERRUPTED);
            }

	    flag = FALSE;
            sleep(RESPONSE_CHECK_INTERVAL);
            if (cmdRspBuf.isRspEnded() == TRUE) {
                return OZT_Result(OZT_Result::NO_PROBLEM);
            }
            if (isIndefinite == false) {
                v = v - RESPONSE_CHECK_INTERVAL;
                if (v > 60) {
                    if (v % 5 == 0) {
                        listener->showTimeInfo(v);
                    }
                }
                else if (v > 30 ) {
                    if (v % 2 == 0) {
                        listener->showTimeInfo(v);
                    }
                }
                else {
                    listener->showTimeInfo(v);
                }
            }
            else {
                listener->showTimeInfo(v++);
            }
        }
        timeOut();
        result = OZT_Result(OZT_Result::TIME_EXPIRED);
    }

    TRACE_RETURN(trace, waitReply, result.filtered());
    return result.filtered();
}

//**************************************************************************

OZT_Result OZT_RspCatcher::waitReplyCheck()
{
    if (cmdRspBuf.isRspEnded())
    {
        if (!failReply.isNull()  && cmdRspBuf.find(failReply))
            return OZT_Result(OZT_Result::REPLY_CHECK_FAIL);
        else
            return OZT_Result(OZT_Result::NO_PROBLEM);
    }
    else
    {
        if (!failReply.isNull() && cmdRspBuf.find(failReply))
            return OZT_Result(OZT_Result::REPLY_CHECK_FAIL);

        if (!okReply.isNull() && cmdRspBuf.find(okReply))
            return OZT_Result(OZT_Result::NO_PROBLEM);

        return OZT_Result(OZT_Result::UNDEFINED);  // not known yet
    }
}


//**************************************************************************
 
void OZT_RspCatcher::setOKReply(const RWCString &str)
{
    okReply = str;
}
 
//**************************************************************************
 
void OZT_RspCatcher::setFailReply(const RWCString &str)
{
    failReply = str;
}
 
//*****************************************************************************

void OZT_RspCatcher::detachFrom(CHA_Model *)
{

}

//*****************************************************************************

#if TPF >= 400  
void OZT_RspCatcher::updateFrom(CHA_Model* pModel, void*)
#else
void OZT_RspCatcher::updateFrom(RWModel* pModel, void*)
#endif
{
    TRACE_IN(trace, updateFrom, "at " << printState(state));

    OZT_Result result;

    switch(state)
    {
        case IDLE      : break;

        case WAITFOR   : if (cmdRspBuf.find(expectedStr1) &&
                             cmdRspBuf.find(expectedStr2))
                         {
			   changeState(IDLE);
			   changed();
			   ozt_evHandlerPtr->setResult(
						       OZT_Result(OZT_Result::NO_PROBLEM)); 
                             
                         }
                         break;

        case WAITREPLY : result = waitReplyCheck();
                         if (result.code != OZT_Result::UNDEFINED)
                         {
                             changeState(IDLE);
			     changed();
                             ozt_evHandlerPtr->setResult(result); 
                         }
                         break;
    }

    TRACE_OUT(trace, updateFrom, "");
}


//*****************************************************************************

int OZT_RspCatcher::timeOutCallBack(void *instance)
{
    ((OZT_RspCatcher *)instance)->timeOut();

    return ozt_evHandlerPtr->notify_done();
}

//*****************************************************************************

void OZT_RspCatcher::timeOut()
{
    TRACE_IN(trace, timeOut, "at " << printState(state));

    switch(state)
    {
        case IDLE      : break;

        case WAITFOR   : changeState(IDLE);
			 changed();
			 ozt_evHandlerPtr->setResult(
						     OZT_Result(OZT_Result::TIME_EXPIRED));
                         break;

        case WAITREPLY : changeState(IDLE);
			 changed();
			 ozt_evHandlerPtr->setResult(
						     OZT_Result(OZT_Result::TIME_EXPIRED));
                         break;
    }

    TRACE_OUT(trace, timeOut, "");
}

//*****************************************************************************

void OZT_RspCatcher::interrupt()
{
    TRACE_IN(trace, interrupt, "at " << printState(state));
    switch(state)
    {
        case IDLE      : break;

        case WAITFOR   : changeState(IDLE);
	                 changed();
			 ozt_evHandlerPtr->setResult(
						     OZT_Result(OZT_Result::INTERRUPTED));
                         break;

        case WAITREPLY : changeState(IDLE);
			 changed();
			 ozt_evHandlerPtr->setResult(
						     OZT_Result(OZT_Result::INTERRUPTED));
                         break;
    }

    TRACE_OUT(trace, interrupt, "");
}

//*****************************************************************************
 
void OZT_RspCatcher::changeState(const State newState)
{
    TRACE_FLOW(trace, changeState, printState(newState));
    state = newState;
}
 
//*****************************************************************************

RWCString OZT_RspCatcher::printState(const State theState)
{
    switch(theState)
    {
        case IDLE                   : return "IDLE";
        case WAITFOR                : return "WAITFOR";
        case WAITREPLY              : return "WAITREPLY";
        default: return "Unknown state";
    }
}
