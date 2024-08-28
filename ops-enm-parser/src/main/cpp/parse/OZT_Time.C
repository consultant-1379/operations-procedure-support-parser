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


#include <OZT_Time.H>
#include <OZT_Misc.H>
#include <time.h>
#include <ctype.h>
#include <rw/tools/regex.h>
#include <rw/tools/datetime.h>

//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_Time";

//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_Time.C,v 21.0 1996/08/23 12:44:53 ehsgrap Rel $";


//*****************************************************************************

OZT_Time::OZT_Time()
: valid(TRUE),
  theTime(time(0))
{
    timeBuffer = new struct tm;
}

//*****************************************************************************

OZT_Time::OZT_Time(const OZT_Time &t)
: valid(t.isValid()),
  theTime(t.toSecSinceEpoch())
{
    timeBuffer = new struct tm;
}

//*****************************************************************************

time_t  OZT_Time::toSecSinceEpoch() const
{
    return theTime;
}

//*****************************************************************************

OZT_Time::OZT_Time(time_t t)
{
    valid = TRUE;  // have no choice but TRUE for this constructor
    theTime = t;
    timeBuffer = new struct tm;
}

//*****************************************************************************

OZT_Time::OZT_Time(const RWCString &dateTimeExp)
{
    TRACE_IN(trace, OZT_Time, dateTimeExp);
 
    static RWTRegex<char> check("[^0-9]");
    struct tm tempData;
    timeBuffer = new struct tm;
 
    if ((dateTimeExp.length() < 10) || (check.index(RWCString(dateTimeExp(0,10))) != RW_NPOS) )
    {
        TRACE_OUT(trace, OZT_Time, "invalid date time exp");
        valid = FALSE;
        return;
    }
 
    int year = strToInt(dateTimeExp(0,2));
    if (year < 70)
      year = year + 100;   // 1970 is the cut-off year.
  
    tempData.tm_year  = year;
    tempData.tm_mon   = strToInt(dateTimeExp(2,2)) - 1;
    tempData.tm_mday  = strToInt(dateTimeExp(4,2));
    tempData.tm_hour  = strToInt(dateTimeExp(6,2));
    tempData.tm_min   = strToInt(dateTimeExp(8,2));
    tempData.tm_sec   = 0;
    tempData.tm_isdst = -1;  // let mktime() determine whether daylight
                             // saving should be applied.

    RWDateTime temp(&tempData);  // borrow the range check mechanism from tools.h++

    if ((!temp.isValid()) || (tempData.tm_hour > 23) || (tempData.tm_min > 59))
    {
        TRACE_OUT(trace, OZT_Time, "invalid date-time expression");
        valid = FALSE;
    }
    else
    {
        TRACE_OUT(trace, OZT_Time, "");
        valid = TRUE;
        theTime = mktime(&tempData);
    }
}

//****************************************************************************
 
OZT_Time::~OZT_Time()
{
    if (timeBuffer != NULL)
        delete timeBuffer;
}
 
//****************************************************************************

RWBoolean OZT_Time::isValid() const
{
    return valid;
}

//****************************************************************************
 
OZT_Time &OZT_Time::operator=(const OZT_Time &t)
{
    if (this == &t)
        return *this;
 
    valid = t.isValid();
    theTime = t.toSecSinceEpoch();

    return *this;
}
 
//****************************************************************************

OZT_Time operator+(const OZT_Time &t, time_t secs)
{
    return OZT_Time(t.toSecSinceEpoch() + secs);
}

//****************************************************************************

OZT_Time operator+(time_t secs, const OZT_Time &t)
{
    return OZT_Time(t.toSecSinceEpoch() + secs);
}

//****************************************************************************

long operator-(const OZT_Time &t1, const OZT_Time &t2)
{
    return (long)(t1.toSecSinceEpoch()) - (long)(t2.toSecSinceEpoch());
}

//****************************************************************************

OZT_Time &OZT_Time::operator+=(time_t s)
{
    if (isValid())
       theTime += s;

    return *this;
}

//****************************************************************************

RWBoolean OZT_Time::advance(const RWCString &intervalExp)
{
    int interval;
    char intervalType;

    if (!isValid())
    {
        TRACE_RETURN(trace, advance, "Object not valid");
        return FALSE;
    }
    if (convertInterval(intervalExp, interval, intervalType) == FALSE)
    {
        TRACE_RETURN(trace, advance, "cannot convert interval");
        return FALSE;
    }
    if (interval == 0)
    {
        TRACE_RETURN(trace, advance, "interval == 0");
        return FALSE;
    }
 
    struct tm *pTimeStruct = localtime_r(&theTime, timeBuffer);

    do {
        switch (intervalType)
        {
            case 'M' : pTimeStruct->tm_min += interval;
                       break;
    
            case 'H' : pTimeStruct->tm_hour += interval;
                       break;
    
            case 'D' : pTimeStruct->tm_mday += interval;
                       pTimeStruct->tm_isdst = -1;
                       break;

            case 'W' : pTimeStruct->tm_mday += 7*interval;
                       pTimeStruct->tm_isdst = -1;
                       break;
        }

    } while (OZT_Time(mktime(pTimeStruct)).inHistory());

    theTime = mktime(pTimeStruct);
    return TRUE;
}

//****************************************************************************

RWBoolean OZT_Time::regress(const RWCString &intervalExp)
{
    int interval;
    char intervalType;

    if (!isValid())
    {
      TRACE_RETURN(trace, advance, "Object not valid");
        return FALSE;
    }
    if (convertInterval(intervalExp, interval, intervalType) == FALSE)
    {
      TRACE_RETURN(trace, advance, "cannot convert interval");
        return FALSE;
    }
    if (interval == 0)
    {
      TRACE_RETURN(trace, advance, "interval == 0");
        return FALSE;
    }
 
    struct tm *pTimeStruct = localtime_r(&theTime, timeBuffer);

    switch (intervalType)
      {
      case 'M' : pTimeStruct->tm_min -= interval;
	break;
	
      case 'H' : pTimeStruct->tm_hour -= interval;
	break;
	
      case 'D' : pTimeStruct->tm_mday -= interval;
	pTimeStruct->tm_isdst = -1;
	break;
	
      case 'W' : pTimeStruct->tm_mday -= 7*interval;
	pTimeStruct->tm_isdst = -1;
	break;
      }

//		RWTime temp(pTimeStruct);
//    if ( !temp.isValid() ) {
//    	pTimeStruct->tm_hour -= 1;
//    }
      
    theTime = mktime(pTimeStruct);
    return TRUE;
}

//****************************************************************************

RWCString OZT_Time::toString() const
{
    if (isValid())
    {
        char tempBuffer[16];

        // "%y%m%d%H%M%S%a" results in 16 characters including the null char.
        strftime(tempBuffer, 16, "%y%m%d%H%M%S%a", localtime_r(&theTime, timeBuffer));

        RWCString tempStr(tempBuffer);

        tempStr.toUpper();

        return tempStr;
    }
    else
    {
        return "<invalid date>";
    }
}
 
//****************************************************************************
 
RWCString OZT_Time::toString(RWCString &dayOfWeek) const
{
    if (isValid())
    { 
        char tempBuffer[3];

        // "%w" results in 2 characters including the null char, but we need
        // to pass 3 as the maxsize, because otherwise strftime() fails for
        // some reason (i.e. a return value of 0 and indeterminate string
        // contents). On HP-UX 9.03 at least...
        strftime(tempBuffer, 3, "%w", localtime_r(&theTime, timeBuffer));

        dayOfWeek = RWCString(tempBuffer);

        return toString();
    }
    else
    {
        dayOfWeek = RWCString();
        return "<invalid date>";
    }
}

//****************************************************************************
 
RWBoolean OZT_Time::inHistory() const
{
    TRACE_IN(trace, inHistory, toString() << "(current time :" 
	     << OZT_Time().toString() << ")");
    RWBoolean ans;

    if (isValid())
    {
        ans = (*this  <  OZT_Time());
        TRACE_OUT(trace, inHistory, ans);
        return ans;
    }
    else
    {
        TRACE_OUT(trace, inHistory, "Not valid, returns FALSE");
        return FALSE;
    }
}

//****************************************************************************

RWBoolean OZT_Time::convertInterval(const RWCString &intervalExp,
                                    int &interval,
                                    char &intervalType)
{
    RWRegexp   checker("^[0-9][0-9]?[mMhHdDwW]$");
 
    //
    //  check the interval format
    //
    if (intervalExp.index(checker) == RW_NPOS)
        return FALSE;
 
    if (intervalExp.length() == 3)
        interval = (intervalExp[(unsigned)0] - '0') * 10 + (intervalExp[(unsigned)1] - '0');
    else
        interval = (intervalExp[(unsigned)0] - '0');
 
    intervalType = toupper(intervalExp[intervalExp.length() - 1]);
    return TRUE;
}
 
//****************************************************************************

RWBoolean     operator>(const OZT_Time& t1, const OZT_Time& t2)
{
    if (difftime(t1.toSecSinceEpoch(), t2.toSecSinceEpoch()) > 0)
        return TRUE;
    else
        return FALSE;
}

//****************************************************************************

RWBoolean     operator>=(const OZT_Time& t1, const OZT_Time& t2)
{
    if (difftime(t1.toSecSinceEpoch(), t2.toSecSinceEpoch()) >= 0)
        return TRUE;
    else
        return FALSE;
}

//****************************************************************************

RWBoolean     operator==(const OZT_Time& t1, const OZT_Time& t2)
{
    if (difftime(t1.toSecSinceEpoch(), t2.toSecSinceEpoch()) == 0)
        return TRUE;
    else
        return FALSE;
}

//****************************************************************************

RWBoolean     operator!=(const OZT_Time& t1, const OZT_Time& t2)
{
    if (difftime(t1.toSecSinceEpoch(), t2.toSecSinceEpoch()) != 0)
        return TRUE;
    else
        return FALSE;
}

//****************************************************************************

RWBoolean     operator<=(const OZT_Time& t1, const OZT_Time& t2)
{
    if (difftime(t1.toSecSinceEpoch(), t2.toSecSinceEpoch()) <= 0)
        return TRUE;
    else
        return FALSE;
}

//****************************************************************************

RWBoolean     operator<(const OZT_Time& t1, const OZT_Time& t2)
{
    if (difftime(t1.toSecSinceEpoch(), t2.toSecSinceEpoch()) < 0)
        return TRUE;
    else
        return FALSE;
}

//****************************************************************************
