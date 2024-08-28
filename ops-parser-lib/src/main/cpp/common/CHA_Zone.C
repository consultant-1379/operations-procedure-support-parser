/*------------------------------------------------------------------------------
 ********************************************************************************
 * COPYRIGHT Ericsson 2018
 *
 * The copyright to the computer program(s) herein is the property of
 * Ericsson Inc. The programs may be used and/or copied only with written
 * permission from Ericsson Inc. or in accordance with the terms and
 * conditions stipulated in the agreement/contract under which the
 * program(s) have been supplied.
 ********************************************************************************
 *----------------------------------------------------------------------------*/

#include <time.h>
#include <CHA_Zone.H>


//**********************************************************************


CHA_Zone::CHA_Zone()
{
#if defined SunOS5 || defined __hpux
    // tzset() is only intialized in the constructor.
    // If the timezone setting need to be changed 
    // construct a new zone object.

    tzset();

    // Number of seconds west of UTC/GMT for standard time
    myTimeZoneOffset = timezone;

    // Number of seconds west of UTC/GMT for Daylight Savings Time
    // Should almost(?) always work... All timezones we know of
    // have on hour offset compared to standard time...
    // So probably this code breaks on Western Samoa Islands.
    // The difference is defined in altzone on SunOS5...
#if defined SunOS5
    myAltZoneOffset = altzone;
#else
    myAltZoneOffset = timezone - 3600;
#endif

    // Non zero if this timezone observes DST
    myDaylightObserved = daylight;

    // Name of the standard time zone
    if (tzname[0] != NULL)
    {
	myTimeZoneName = tzname[0];
    }
    else
    {
	myTimeZoneName = "";
    }

    // Name of the alternative time zone
    if (tzname[1] != NULL)
    {
	myAltZoneName = tzname[1];
    }
    else
    {
	myAltZoneName = "";
    }
#endif  // Should be removed...
}


//**********************************************************************


CHA_Zone::~CHA_Zone()
{
    // Empty
}


//**********************************************************************


RWBoolean CHA_Zone::isDaylight(const struct tm* pTm) const
{
    // There may be hidden side effects here since we don't
    // update the timezone setting ourselves but somebody else
    // may have in another part of the program (excerpt from   
    // the HP-UX man page):

    // tzset()
    // Sets the values of the external variables timezone,
    // daylight, and tzname according to the contents of
    // the TZ environment variable (independent of any time
    // value).  The functions localtime(), mktime(),
    // ctime(), nl_ctime(), nl_cxtime(), asctime(),
    // nl_asctime(), nl_ascxtime(), and strftime() (see
    // strftime(3C)) call tzset() and use the values
    // returned in the external variables described below
    // for their operations.  tzset() can also be called
    // directly by the user.

    struct tm myTm = *pTm;

#if defined SunOS5 || defined __hpux
    time_t t = mktime(&myTm);
#else
    time_t t = timelocal(&myTm);
#endif
    myTm = *localtime(&t);

    if (myTm.tm_isdst > 0)
    {
	// DST in effect
	return TRUE;
    }
    else
    {
	// Not in effect or unknown
	return FALSE;
    }
}


//**********************************************************************


int CHA_Zone::timeZoneOffset() const
{
    // Number of seconds west of UTC/GMT

    return myTimeZoneOffset;
}


//**********************************************************************


int CHA_Zone::altZoneOffset() const
{
    // Number of seconds west of UTC/GMT for DST
    // Do we have DST for this timezone at all?

    if (myDaylightObserved != 0)
    {
	return myAltZoneOffset;
    }
    else
    {
	// No DST observed just return standard diff
	return myTimeZoneOffset;
    }
}

//**********************************************************************


RWBoolean CHA_Zone::daylightObserved() const
{
    if (myDaylightObserved != 0)
    {
	return TRUE;
    }
    else 
    {
	return FALSE;
    }
}


//**********************************************************************


RWCString CHA_Zone::timeZoneName() const
{
    return myTimeZoneName;
}


//**********************************************************************


RWCString CHA_Zone::altZoneName() const
{
    return myAltZoneName;
}


//**********************************************************************


void CHA_Zone::getBeginDaylight(struct tm* pTm) const
{
    // tbd
}


//**********************************************************************


void CHA_Zone::getEndDaylight(struct tm* pTm) const
{
    // tbd
}


//**********************************************************************



