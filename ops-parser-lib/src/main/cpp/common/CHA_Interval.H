// RCS handling
// $Id: CHA_Interval.H,v 24.0 1995/11/28 16:54:47 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_Interval - an integer interval e.g. 1-25
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_Interval.H

// .COPYRIGHT
//      COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1994
//
//      The Copyright to the computer program(s) herein is the
//      property of Ericsson Hewlett-Packard Telecommunications AB,
//      Sweden.  The program(s) may be used and/or copied with the
//      written permission from Ericsson Hewlett-Packard
//      Telecommunications AB or in accordance with the terms and
//      conditions stipulated in the agreement/contract under which
//      the program(s) have been supplied.

// .DESCRIPTION 
//	This class models an integer interval and provides operations
//      for the interval. An interval can be created either by giving
//      lower and upper bound in integer format, or by giving a string
//      representing the interval. The interval string format is "xx-yy"
//	where xx is the lower bound and yy is the upper bound. The
//      syntax of this string is checked and an error will result in
//	the empty interval. A function for checking the syntax of an
//      interval string is also provided. An empty interval is a
//	correct interval.

// DOCUMENT NO
//      190 89-CAA 134 1515

// AUTHOR 
//      1995-06-14 by EHS/PXE Johan Dykström (qhsjody@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_Interval.H,v $
//      Revision 24.0  1995/11/28 16:54:47  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:40:50  17:40:50  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:43:39  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:39:26  09:39:26  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 1.3  95/06/22  11:39:50  11:39:50  qhsjody (Johan Dykstrom VK/EHS/PXE)
//      Added removeInterval.
//      
//      Revision 1.2  1995/06/19  09:16:54  qhsjody
//      Changes after code review.
//
//      Revision 1.1  1995/06/16  12:39:14  qhsjody
//      Initial revision
//
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	TB53_OZ 1995-11-28      J Grape (EHSGRAP)       RCS rev 24.0
//	XM2S1   1995-09-07      ehscama                 RCS rev 23.0
//	EC2_OZ  1995-08-01      Jan Sandquist (EHSJAASA)RCS rev 22.0
//	EC1_OZ  1995-06-29      J Grape (EHSGRAP)       RCS rev 21.0

// .SEE ALSO 
//      

//**********************************************************************

#ifndef CHA_INTERVAL_H
#define CHA_INTERVAL_H

#include	<rw/cstring.h>

//**********************************************************************

class CHA_Interval
{

public:

    CHA_Interval();
    // Description:
    //     Default constructor.

    CHA_Interval(const CHA_Interval& old);
    // Description:
    //     Copy constructor.
    // Parameters:
    //     old		    IN: interval to copy

    CHA_Interval(const RWCString& iv);
    // Description:
    //     Constructor.
    // Parameters:
    //     iv		    IN: interval in text form

    CHA_Interval(int lower, int upper);
    // Description:
    //     Constructor.
    // Parameters:
    //     lower	    IN: lower bound of interval
    //     upper 	    IN: upper bound of interval

    virtual ~CHA_Interval();
    // Description:
    //     Destructor.
    
    virtual CHA_Interval& operator =(const CHA_Interval& old);
    // Description:
    //     Assignment operator.
    // Parameters:
    //     old		    IN: interval to copy

    virtual operator RWCString() const;
    // Description:
    //     Type cast operator. Type casts the interval to a string of 
    //	   format "xx-yy".
    // Return value::
    //     A string representing the interval.

    virtual void getBounds(int& lower, int& upper) const;
    // Description:
    //     To get the lower and upper bounds of the interval. If the
    //     lower bound > upper bound, the interval is the empty interval.
    // Parameters:
    //     lower	    OUT: lower bound of interval
    //     upper	    OUT: upper bound of interval
    
    virtual int getLower() const;
    // Description:
    //     To get the lower bound of the interval.
    // Return value:
    //     The lower bound of the interval.

    virtual int getUpper() const;
    // Description:
    //     To get the upper bound of the interval.
    // Return value:
    //     The upper bound of the interval.

    virtual int length() const;
    // Description:
    //     To get the length of the interval. The length is defined as
    //	   upper bound - lower bound + 1. If the length is 0, the 
    //     interval is the empty interval.
    // Return value:
    //     The length of the interval.

    virtual RWBoolean isEmpty() const;
    // Description:
    //     To check if the interval is empty, that is 
    //     lower bound > upper bound.
    // Return value:
    //     TRUE             The interval is empty.
    //     FALSE            The interval is not empty.

    virtual RWBoolean contains(int i) const;
    // Description:
    //     To check if integer i is in the interval.
    // Parameters:
    //     i		    IN: the integer to check
    // Return value:
    //     TRUE		    i is in the interval.
    //     FALSE	    i is not in the interval.

    virtual RWBoolean isSubsetTo(const CHA_Interval& iv) const;
    // Description:
    //     To check if this is a subset to interval iv. The empty
    //     interval is a subset to every interval.
    // Parameters:
    //     iv		    IN: the interval to check this against
    // Return value:
    //     TRUE		    this is a subset to iv.
    //     FALSE	    this is not a subset to iv.

    virtual RWBoolean isSupersetTo(const CHA_Interval& iv) const;
    // Description:
    //     To check if this is a superset to interval iv. Every
    //     interval is a superset to the empty interval.
    // Parameters:
    //     iv		    IN: the interval to check this against
    // Return value:
    //     TRUE		    this is a superset to iv.
    //     FALSE	    this is not a superset to iv.

    virtual RWBoolean isAdjacentTo(const CHA_Interval& iv) const;
    // Description:
    //     To check if this is adjacent to interval iv. It does not
    //     matter on which side of iv this is. The empty interval is
    //     adjacent to every interval.
    // Parameters:
    //     iv		    IN: the interval to check this against
    // Return value:
    //     TRUE		    this is adjacent to iv.
    //     FALSE	    this is not adjacent to iv.

    virtual RWBoolean isIntersecting(const CHA_Interval& iv) const;
    // Description:
    //     To check if this is intersecting interval iv. The empty
    //     interval is not intersecting any interval.
    // Parameters:
    //     iv		    IN: the interval to check this against
    // Return value:
    //     TRUE		    this is intersecting iv.
    //     FALSE	    this is not intersecting iv.

    virtual RWBoolean concatenate(const CHA_Interval& iv);
    // Description:
    //     To concatenate two intervals. This operation is only defined
    //     if the intervals are adjacent or intersecting each other. If
    //     the operation is defined, the result is that this is set to
    //     the union of the two intervals, e.g. "1-5" + "3-7" == "1-7".
    //     If the intervals are disjunct and the operation are undefined,
    //     this is not changed. If one of the intervals is empty, the
    //     result is equal to the other interval (might be empty too).
    // Parameters:
    //     iv		    IN: the interval to concatenate with this
    // Return value:
    //     TRUE		    Source intervals OK, operation defined.
    //     FALSE	    Source intervals disjunct, operation 
    //                      undefined, this unchanged.

private:

    void copy(const CHA_Interval& old);
    // Description:
    //     To copy the class attributes.
    // Parameters:
    //     old		    IN: interval to copy

    void clear() { }
    // Description:
    //     To clear dynamically allocated memory.

    virtual RWBoolean extractBounds(const RWCString& iv, 
				    int& lower, int& upper) const;
    // Description:
    //     To convert an interval string into a lower and an upper bound.
    //     The interval string should have the format "xx-yy".
    // Parameters:
    //     iv		    IN: the string to convert
    //     lower	    OUT: lower bound of interval
    //     upper	    OUT: upper bound of interval
    // Return value:
    //     TRUE		    Conversion worked OK. Bounds correct.
    //     FALSE	    Incorrect interval specified. Bounds incorrect.

    friend RWBoolean operator ==(const CHA_Interval& iv1, 
				 const CHA_Interval& iv2);
    // Description:
    //     To compare two intervals for equality.
    // Parameters:
    //     iv1		    IN: interval one
    //     iv2		    IN: interval two
    // Return value:
    //     TRUE		    The intervals are equal.
    //     FALSE	    The intervals are not equal.

    friend RWBoolean operator !=(const CHA_Interval& iv1, 
				 const CHA_Interval& iv2);
    // Description:
    //     To compare two intervals for inequality.
    // Parameters:
    //     iv1		    IN: interval one
    //     iv2		    IN: interval two
    // Return value:
    //     TRUE		    The intervals are not equal.
    //     FALSE	    The intervals are equal.

    int lb, ub;       // Interval bounds

};

// Non-member functions

extern RWBoolean isInterval(const RWCString& iv);
// Description:
//     To check that an interval string has the correct format.
//     The interval string should have the format "xx-yy".
// Parameters:
//     iv		    IN: the interval string to check
// Return value:
//     TRUE		    Interval bounds correct.
//     FALSE	    	    Incorrect interval specified.

RWBoolean removeInterval(const CHA_Interval& op1, const CHA_Interval& op2,
			 CHA_Interval& res1, CHA_Interval& res2);
// Description:
//     To remove one interval from another. The operation op1 - op2 is
//     performed, and the result is assigned to res1 and possibly res2 if
//     the operation results in two non-empty intervals. If op1 is a
//     subset to op2, the result will be the empty interval. If op1 and
//     op2 are disjunct, the result will be op1 unchanged.
// Parameters:
//     op1		    IN: source interval
//     op2		    IN: interval to remove
//     res1		    IN: result interval (might be empty)
//     res2		    IN: second result interval. res2 is only
//                              valid if the function returns TRUE.
// Return value:
//     TRUE		    The operation resulted in two non-empty
//                          intervals.
//     FALSE	    	    The operation resulted in one interval that
//                          might be empty.

#endif
