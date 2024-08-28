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

#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_DeviceModeProps.H>
#include <trace.H>

static std::string trace ="CHA_DeviceModeProps";

//**********************************************************************


CHA_DeviceModeProps::CHA_DeviceModeProps()
: lastEvent(MODE_OFF),
  devModeOn(FALSE),
  reqDeviceIdValid(FALSE),
  reqDeviceId(-1),
  usedDeviceIdValid(FALSE),
  usedDeviceId(-1),
  waitingTimeValid(FALSE),
  waitingTime(CHA_DEVMODEPROPS_MINIMUM_WAITING_TIME)
{
    TRACE_IN(trace, CHA_DeviceModeProps, "");
    // empty
}


//**********************************************************************


CHA_DeviceModeProps::~CHA_DeviceModeProps()
{
    // empty
}


//**********************************************************************


void CHA_DeviceModeProps::setModeOff()
{
    TRACE_IN(trace, setModeOff, "");

    devModeOn 		= FALSE;
    reqDeviceIdValid	= FALSE;
    reqDeviceId		= -1;
    waitingTimeValid 	= FALSE;
    waitingTime 	= CHA_DEVMODEPROPS_MINIMUM_WAITING_TIME;

    announceEvent(MODE_OFF);
}


//**********************************************************************


void CHA_DeviceModeProps::setModeOff(const long int wTime)
{
    TRACE_IN(trace, setModeOff, wTime);

    devModeOn 		= FALSE;
    reqDeviceIdValid	= FALSE;
    reqDeviceId		= -1;
    waitingTimeValid 	= TRUE;

    if (wTime > CHA_DEVMODEPROPS_MINIMUM_WAITING_TIME)
        waitingTime 	= wTime;
    else
        waitingTime = CHA_DEVMODEPROPS_MINIMUM_WAITING_TIME;


    announceEvent(MODE_OFF_TIME);
}


//**********************************************************************


void CHA_DeviceModeProps::setModeOff(const RWDateTime& eTime)
{
    TRACE_IN(trace, setModeOff, eTime);

    devModeOn 		= FALSE;
    reqDeviceIdValid	= FALSE;
    reqDeviceId		= -1;
    waitingTimeValid 	= TRUE;

    RWDateTime rightNow;
    if ( (( eTime.milliSeconds()/1000 ) - ( rightNow.milliSeconds()/1000 ) ) >
	 (CHA_DEVMODEPROPS_MINIMUM_WAITING_TIME) )
        waitingTime = ( eTime.milliSeconds()/1000 ) - ( rightNow.milliSeconds()/1000 );
    else
        waitingTime = CHA_DEVMODEPROPS_MINIMUM_WAITING_TIME;

    announceEvent(MODE_OFF_TIME);
}


//**********************************************************************


void CHA_DeviceModeProps::setModeOn()
{
    TRACE_IN(trace, setModeOn, "");

    devModeOn 		= TRUE;
    reqDeviceIdValid	= FALSE;
    reqDeviceId		= -1;
    waitingTimeValid 	= FALSE;
    waitingTime = CHA_DEVMODEPROPS_MINIMUM_DM_WAITING_TIME;

    announceEvent(MODE_ON);
}


//**********************************************************************


void CHA_DeviceModeProps::setModeOn(int devId)
{
    TRACE_IN(trace, setModeOn, devId);

    devModeOn 			= TRUE;

    if (devId != -1) {
        reqDeviceIdValid	= TRUE;
        reqDeviceId		= devId;
    }
    else {
        reqDeviceIdValid	= FALSE;
        reqDeviceId		= -1;
    }

    waitingTimeValid 		= FALSE;
    waitingTime 		= CHA_DEVMODEPROPS_MINIMUM_DM_WAITING_TIME;

    announceEvent(MODE_ON_ID);
}


//**********************************************************************


void CHA_DeviceModeProps::setModeOn(int devId, const long int wTime)
{
    TRACE_IN(trace, setModeOn, devId << ", " << wTime);

    devModeOn 			= TRUE;

    if (devId != -1) {
        reqDeviceIdValid	= TRUE;
        reqDeviceId		= devId;
    }
    else {
        reqDeviceIdValid	= FALSE;
        reqDeviceId		= -1;
    }

    waitingTimeValid  		= TRUE;

    if (wTime > CHA_DEVMODEPROPS_MINIMUM_DM_WAITING_TIME)
        waitingTime = wTime;
    else
        waitingTime = CHA_DEVMODEPROPS_MINIMUM_DM_WAITING_TIME;

    announceEvent(MODE_ON_ID_TIME);
}


//**********************************************************************


void CHA_DeviceModeProps::setModeOn(int devId, const RWDateTime& eTime)
{
    TRACE_IN(trace, setModeOn, devId << ", " << eTime);

    devModeOn 			= TRUE;

    if (devId != -1) {
        reqDeviceIdValid	= TRUE;
        reqDeviceId		= devId;
    }
    else {
        reqDeviceIdValid	= FALSE;
        reqDeviceId		= -1;
    }

    waitingTimeValid  		= TRUE;

    RWDateTime rightNow;
    if ( (( eTime.milliSeconds()/1000 ) - ( rightNow.milliSeconds()/1000 ) ) >
    	 (CHA_DEVMODEPROPS_MINIMUM_DM_WAITING_TIME) )
            waitingTime = ( eTime.milliSeconds()/1000 ) - ( rightNow.milliSeconds()/1000 );
    else
        waitingTime = CHA_DEVMODEPROPS_MINIMUM_DM_WAITING_TIME;

    announceEvent(MODE_ON_ID_TIME);
}


//**********************************************************************


void CHA_DeviceModeProps::setModeOn(const long int wTime)
{
    TRACE_IN(trace, setModeOn, wTime);

    devModeOn 		= TRUE;
    reqDeviceIdValid 	= FALSE;
    reqDeviceId		= -1;
    waitingTimeValid  	= TRUE;

    if (wTime > CHA_DEVMODEPROPS_MINIMUM_DM_WAITING_TIME)
        waitingTime = wTime;
    else
        waitingTime = CHA_DEVMODEPROPS_MINIMUM_DM_WAITING_TIME;

    announceEvent(MODE_ON_TIME);
}


//**********************************************************************


void CHA_DeviceModeProps::setModeOn(const RWDateTime& eTime)
{
    TRACE_IN(trace, setModeOn, eTime);

    devModeOn 		= TRUE;
    reqDeviceIdValid 	= FALSE;
    reqDeviceId		= -1;
    waitingTimeValid  	= TRUE;

    RWDateTime rightNow;
    if ( (( eTime.milliSeconds()/1000 ) - ( rightNow.milliSeconds()/1000 ) ) >
     	 (CHA_DEVMODEPROPS_MINIMUM_DM_WAITING_TIME) )
             waitingTime = ( eTime.milliSeconds()/1000 ) - ( rightNow.milliSeconds()/1000 );
    else
        waitingTime = CHA_DEVMODEPROPS_MINIMUM_DM_WAITING_TIME;

    announceEvent(MODE_ON_TIME);
}


//**********************************************************************


void CHA_DeviceModeProps::usingDevId(int devId)
{
    TRACE_IN(trace, usingDevId, devId);

    if (devId > 0) {
        usedDeviceIdValid	= TRUE;
        usedDeviceId		= devId;
    }
    else if (devId < -1) {
	// this is a bit EHT specific
	// EHT gives device IDs that consist of a negative number,
	// where only the three last digits are significant to us.
        usedDeviceIdValid	= TRUE;
	usedDeviceId            = (-devId)%1000;
    }
    else {
        usedDeviceIdValid	= FALSE;
        usedDeviceId		= -1;
    }

    announceEvent(USING_ID);
}


//**********************************************************************
////////////////////////////////////////////////////////////////////////
/*
void CHA_DeviceModeProps::setModeOnUsingOldSettings()
{
    //TRACE_IN(trace, setModeOnUsingOldSettings, "");
    devModeOn = TRUE;
    announceEvent(MODE_ON_OLD);
}
*/
////////////////////////////////////////////////////////////////////////
//**********************************************************************


RWBoolean CHA_DeviceModeProps::isDevModeOn() const
{
    TRACE_RETURN(trace, isDevModeOn, devModeOn);
    return devModeOn;
}


//**********************************************************************


RWBoolean CHA_DeviceModeProps::isReqDeviceIdSet() const
{
    TRACE_RETURN(trace, isReqDeviceIdSet, reqDeviceIdValid);
    return reqDeviceIdValid;
}


//**********************************************************************


RWBoolean CHA_DeviceModeProps::isDeviceIdSet() const
{
    TRACE_RETURN(trace, isDeviceIdSet, reqDeviceIdValid);
    return reqDeviceIdValid;
}


//**********************************************************************


RWBoolean CHA_DeviceModeProps::isUsedDeviceIdSet() const
{
    TRACE_RETURN(trace, isUsedDeviceIdSet, usedDeviceIdValid);
    return usedDeviceIdValid;
}


//**********************************************************************

RWBoolean CHA_DeviceModeProps::isWaitingTimeSet() const
{
    TRACE_RETURN(trace, isWaitingTimeSet, waitingTimeValid);
    return waitingTimeValid;
}


//**********************************************************************

RWBoolean CHA_DeviceModeProps::isEndTimeSet() const
{
    TRACE_RETURN(trace, isEndTimeSet, waitingTimeValid);
    return waitingTimeValid;
}


//**********************************************************************


long int CHA_DeviceModeProps::getWaitingTime() const
{
    TRACE_RETURN(trace, getWaitingTime, waitingTime);
    return waitingTime;
}


//**********************************************************************


RWDateTime CHA_DeviceModeProps::getEndTime() const
{
    RWDateTime endTimeRightNow;
    endTimeRightNow.incrementSecond( waitingTime );

    TRACE_RETURN(trace, getEndTime, endTimeRightNow);

    return endTimeRightNow;
}


//**********************************************************************


RWDateTime CHA_DeviceModeProps::getProlongEndTime() const
{
    RWDateTime prolongEndTimeRightNow;
    prolongEndTimeRightNow.incrementSecond(CHA_DEVMODEPROPS_PROLONG_FACTOR*waitingTime);

    TRACE_RETURN(trace, getProlongEndTime, prolongEndTimeRightNow);

    return prolongEndTimeRightNow;
}


//**********************************************************************


int CHA_DeviceModeProps::getReqDevId() const
{
    TRACE_RETURN(trace, getReqDevId, reqDeviceId);
    return reqDeviceId;
}


//**********************************************************************


int CHA_DeviceModeProps::getDevId() const
{
    TRACE_RETURN(trace, getDevId, reqDeviceId);
    return reqDeviceId;
}


//**********************************************************************


int CHA_DeviceModeProps::getUsedDevId() const
{
    TRACE_RETURN(trace, getUsedDevId, usedDeviceId);
    return usedDeviceId;
}


//**********************************************************************


CHA_DeviceModeProps::Event CHA_DeviceModeProps::getLastEvent()
{
    TRACE_RETURN(trace, getLastEvent, lastEvent);
    return lastEvent;
}


//**********************************************************************


void CHA_DeviceModeProps::announceEvent(CHA_DeviceModeProps::Event eventCode)
{
    TRACE_IN(trace, announceEvent, eventCode);

    lastEvent = eventCode;
    changed();
}


//**********************************************************************




