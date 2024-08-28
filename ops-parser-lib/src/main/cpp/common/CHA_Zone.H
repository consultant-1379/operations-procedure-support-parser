// RCS handling
// $Id: CHA_Zone.H,v 24.0 1995/11/28 16:55:17 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_Zone - A time zone descrition that works on Unix
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_Zone.H

// .COPYRIGHT
//      COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1995
//
//      The Copyright to the computer program(s) herein is the
//      property of Ericsson Hewlett-Packard Telecommunications AB,
//      Sweden.  The program(s) may be used and/or copied with the
//      written permission from Ericsson Hewlett-Packard
//      Telecommunications AB or in accordance with the terms and
//      conditions stipulated in the agreement/contract under which
//      the program(s) have been supplied.

// .DESCRIPTION 
//      CHA_Zone implements a time zone description class inheriting
//      from RWZone. This class is intended to replace the default
//      time zone handling of Rogue Wave's Tools.h++ library. 
//
//      Tools.h++ library doesn't make use of the time zone utilities
//      available in the Unix operating system. Instead it uses it's
//      own, incoplete, implementation. Probably to make thing
//      portable to MS DOS or something.
//
//      The CHA_Zone class uses the time zone information available in
//      the unix operating system. This ensures that zone information
//      is correct everywhere in the world where it is supported by
//      the OS.
//
//	Note: The DST difference to standard time is always assumed to 
//	be 1 hour. This holds for all timezones defined on HP-UX at
//	least.
//
//	Of course, something is also lost in doing this.
//      The Unix operating system API does not provide the information
//      of when day light savings time (DST) begins and ends. Thus,
//      you cannot expect sensible values from the methods
//      CHA_Zone::getBeginDaylight() and
//      CHA_Zone::getEndDaylight(). Since these ar declared pure
//      virtual in the base class RWZone they still have to be
//      implemented in CHA_Zone.

// DOCUMENT NO
//      190 89-CAA 134 1515

// AUTHOR 
//      1995-07-03 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_Zone.H,v $
//      Revision 24.0  1995/11/28 16:55:17  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:41:39  17:41:39  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:44:25  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 1.1  95/07/05  07:24:53  07:24:53  ehscama (Martin Carlsson VK/EHS/PXE)
//      First version.
//      
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	TB53_OZ 1995-11-28      J Grape (EHSGRAP)       RCS rev 24.0
//	XM2S1   1995-09-07      ehscama                 RCS rev 23.0
//	EC2_OZ  1995-08-01      Jan Sandquist (EHSJAASA)RCS rev 22.0

// .SEE ALSO 
//      Tools.h++ Reference Manual

//**********************************************************************

#ifndef CHA_ZONE_H
#define CHA_ZONE_H

#include <rw/zone.h>


class CHA_Zone : public RWZone
{
public:

    CHA_Zone();
    virtual ~CHA_Zone();

    virtual int timeZoneOffset() const;
    virtual int altZoneOffset() const;
    virtual RWBoolean daylightObserved() const;
    virtual RWCString timeZoneName() const;
    virtual RWCString altZoneName() const;

    // isDaylight() may use all members of tmbuf except tm_isdst
    //
    // solution:	convert it to a time_t with tm_isdst = -1
    //			convert it back to a tm
    //			investigate tm_isdst
    virtual RWBoolean isDaylight(const struct tm* tmbuf) const;

    // The following functions use the tm_year member of struct tm, and
    //   set all the remaining members.
    virtual void getBeginDaylight(struct tm*) const;
    virtual void getEndDaylight(struct tm*) const;

private:
    int myTimeZoneOffset;
    int myAltZoneOffset;
    int myDaylightObserved;
    RWCString myTimeZoneName;
    RWCString myAltZoneName;
};

#endif
