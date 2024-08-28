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

#include <CHA_Interval.H>
#include <CHA_Trace.H>

#include <strstream>

#include <trace.H>
static std::string trace ="CHA_Interval";

//**********************************************************************

CHA_Interval::CHA_Interval()
: lb(1),
  ub(0)                                   // "1-0" is the empty interval
{
    // Default constructor - make an empty interval.
    TRACE_IN(trace, CHA_Interval, "DC - empty interval");
}

//**********************************************************************

CHA_Interval::CHA_Interval(const CHA_Interval& old)
{
    TRACE_IN(trace, CHA_Interval, "CC: " << old.lb << "-" << old.ub);
    copy(old);
}

//**********************************************************************

CHA_Interval::CHA_Interval(const RWCString& iv)
{
    TRACE_IN(trace, CHA_Interval, iv);

    // Extract interval bounds. If anything goes wrong, we should cast
    // an exeption...
    if (extractBounds(iv, lb, ub))
    {
	TRACE_FLOW(trace, CHA_Interval, "Bounds OK: " << lb << "-" << ub);
    }
    else
    {
	TRACE_FLOW(trace, CHA_Interval,
		   "Bounds incorrect -> empty interval.");
	lb = 1;
	ub = 0;                           // "1-0" is the empty interval
    }
}

//**********************************************************************

CHA_Interval::CHA_Interval(int lower, int upper)
: lb(lower),
  ub(upper)
{
    TRACE_IN(trace, CHA_Interval, lower << "-" << upper);

    if (lb > ub)
    {
	TRACE_FLOW(trace, CHA_Interval,
		   "Bounds incorrect -> empty interval.");
	lb = 1;
	ub = 0;                           // "1-0" is the empty interval
    }
}

//**********************************************************************

CHA_Interval::~CHA_Interval()
{
    clear();
}

//**********************************************************************

CHA_Interval& CHA_Interval::operator =(const CHA_Interval& old)
{
    TRACE_IN(trace, operator =, old.lb << "-" << old.ub);

    // Protect from self assignment
    if (&old != this)
    {
	clear();
	copy(old);
    }
    else
	TRACE_FLOW(trace, operator =, "Self assignment!!!");

    return *this;
}

//**********************************************************************

CHA_Interval::operator RWCString() const
{
    TRACE_IN(trace, RWCString, lb << "-" << ub);
    RWCString result;
    std::ostrstream os;

    // Convert interval to a string on format "xx-yy"
    if (isEmpty())
	os << "empty" << std::ends;
    else
	os << lb << "-" << ub << std::ends;
    result = os.str();
    delete [] os.str();

    TRACE_RETURN(trace, RWCString, result);
    return result;
}

//**********************************************************************

void CHA_Interval::getBounds(int& lower, int& upper) const
{
    lower = lb;
    upper = ub;
    TRACE_RETURN(trace, getBounds, lb << "-" << ub);
}

//**********************************************************************

int CHA_Interval::getLower() const
{
    TRACE_RETURN(trace, getLower, lb);
    return lb;
}

//**********************************************************************

int CHA_Interval::getUpper() const
{
    TRACE_RETURN(trace, getUpper, ub);
    return ub;
}

//**********************************************************************

int CHA_Interval::length() const
{
    int result = (ub - lb + 1);
    TRACE_RETURN(trace, length, result);
    return result;
}

//**********************************************************************

RWBoolean CHA_Interval::isEmpty() const
{
    RWBoolean result = (lb > ub);
    TRACE_RETURN(trace, isEmpty, result);
    return result;
}

//**********************************************************************

RWBoolean CHA_Interval::contains(int i) const
{
    RWBoolean result = !isEmpty() && (i >= lb) && (i <= ub);
    TRACE_RETURN(trace, contains, result);
    return result;
}

//**********************************************************************

RWBoolean CHA_Interval::isSubsetTo(const CHA_Interval& iv) const
{
    RWBoolean result = isEmpty() ||
	(!iv.isEmpty() && (lb >= iv.lb) && (ub <= iv.ub));
    TRACE_RETURN(trace, isSubsetTo, result);
    return result;
}

//**********************************************************************

RWBoolean CHA_Interval::isSupersetTo(const CHA_Interval& iv) const
{
    RWBoolean result = iv.isEmpty() ||
	(!isEmpty() && (lb <= iv.lb) && (ub >= iv.ub));
    TRACE_RETURN(trace, isSupersetTo, result);
    return result;
}

//**********************************************************************

RWBoolean CHA_Interval::isAdjacentTo(const CHA_Interval& iv) const
{
    RWBoolean result = isEmpty() || iv.isEmpty() ||
	(ub == iv.lb - 1) || (lb == iv.ub + 1);
    TRACE_RETURN(trace, isAdjacentTo, result);
    return result;
}

//**********************************************************************

RWBoolean CHA_Interval::isIntersecting(const CHA_Interval& iv) const
{
    RWBoolean result = !isEmpty() && !iv.isEmpty() &&
	(isSubsetTo(iv) || isSupersetTo(iv) ||
	((lb < iv.lb) && (ub >= iv.lb) && (ub < iv.ub)) ||
	((ub > iv.ub) && (lb <= iv.ub) && (lb > iv.lb)));
    TRACE_RETURN(trace, isIntersecting, result);
    return result;
}

//**********************************************************************

RWBoolean CHA_Interval::concatenate(const CHA_Interval& iv)
{
    TRACE_IN(trace, concatenate, lb << "-" << ub
	     << " and " << iv.lb << "-" << iv.ub);
    RWBoolean result = isAdjacentTo(iv) || isIntersecting(iv);

    // If operation is defined
    if (result)
    {
	// If this is empty, result is iv
	if (isEmpty())
	{
	    lb = iv.lb;
	    ub = iv.ub;
	}

	// If iv is empty, result is this, otherwise, check bounds
	else if (!iv.isEmpty())
	{
	    if (iv.lb < lb)
		lb = iv.lb;
	    if (iv.ub > ub)
		ub = iv.ub;
	}
	TRACE_FLOW(trace, concatenate, "Result: " << lb << "-" << ub);
    }

    TRACE_RETURN(trace, concatenate, result);
    return result;
}

//**********************************************************************

void CHA_Interval::copy(const CHA_Interval& old)
{
    TRACE_IN(trace, copy, old.lb << "-" << old.ub);
    lb = old.lb;
    ub = old.ub;
}

//**********************************************************************

RWBoolean CHA_Interval::extractBounds(const RWCString& iv,
				      int& lower, int& upper) const
{
    TRACE_IN(trace, extractBounds, iv);
    RWBoolean result = TRUE;
    std::istrstream is(iv);
    char foo;

    // Read lower bound
    is >> lower;
    is >> std::skipws;                                          // Eat whitespace
    result = (!is.fail()) && (is.eof() == 0);
    TRACE_FLOW(trace, extractBounds, "lower: " << lower
	       << ", stream: " << is.str() << ", eof: " << is.eof());

    // Read delimiter
    if (result)
    {
	is >> foo;
	is >> std::skipws;                                      // Eat whitespace
	result = (is.str() != 0) && (is.eof() == 0);
	TRACE_FLOW(trace, extractBounds, "foo: " << foo
		   << ", stream: " << is.str() << ", eof: " << is.eof());
    }

    // Read upper bound
    if (result)
    {
	is >> upper;
	result = (is.str() != 0);                  // Don't mind about eof now
	TRACE_FLOW(trace, extractBounds, "upper: " << upper
		   << ", stream: " << is.str()<< ", eof: " << is.eof());
    }

    // Check that upper bound >= lower bound
    if (result)
	result = (upper >= lower);

    TRACE_RETURN(trace, extractBounds, result);
    return result;
}

//**********************************************************************

RWBoolean operator ==(const CHA_Interval& iv1, const CHA_Interval& iv2)
{
    RWBoolean result = (iv1.lb == iv2.lb) &&
	               (iv1.ub == iv2.ub);

    TRACE_RETURN(trace, operator ==, result);
    return result;
}

//**********************************************************************

RWBoolean operator !=(const CHA_Interval& iv1, const CHA_Interval& iv2)
{
    TRACE_RETURN(trace, operator !=, !(iv1 == iv2));
    return !(iv1 == iv2);
}

//**********************************************************************
// Non-member functions
//**********************************************************************

RWBoolean isInterval(const RWCString& iv)
{
    TRACE_IN(trace, isInterval, iv);
    CHA_Interval tmpIv(iv);
    RWBoolean result = !tmpIv.isEmpty();

    TRACE_RETURN(trace, isInterval, result);
    return result;
}

//**********************************************************************

RWBoolean removeInterval(const CHA_Interval& op1, const CHA_Interval& op2,
			 CHA_Interval& res1, CHA_Interval& res2)
{
    TRACE_IN(trace, removeInterval, op1 << " - " << op2);
    RWBoolean result = FALSE;

    // Check if the intervals are disjunct
    if (!op1.isIntersecting(op2))
    {
	TRACE_FLOW(trace, removeInterval, "Intervals disjunct");
	res1 = op1;
    }

    // Check if op1 is a subset to op2
    else if (op1.isSubsetTo(op2))
    {
	TRACE_FLOW(trace, removeInterval, op1 << " is subset to " << op2);
	res1 = CHA_Interval();
    }

    // Check if op1 is a true superset to op2, that is if the result will
    // consist of two intervals.
    else if ((op1.getLower() < op2.getLower()) &&
	     (op1.getUpper() > op2.getUpper()))
    {
	TRACE_FLOW(trace, removeInterval,
		   op1 << " is true superset to " << op2);

	res1 = CHA_Interval(op1.getLower(), op2.getLower() - 1);
	res2 = CHA_Interval(op2.getUpper() + 1, op1.getUpper());
	result = TRUE;
    }

    // Normal case - the result will only be one interval
    else
    {
	TRACE_FLOW(trace, removeInterval, "Normal case - one interval");

	// If op2 starts to the left of op1
	if (op2.getLower() < op1.getLower())
	    res1 = CHA_Interval(op2.getUpper() + 1, op1.getUpper());
	else
	    res1 = CHA_Interval(op1.getLower(), op2.getLower() - 1);
    }

    // Do correct trace
    if (result)
    {
	TRACE_RETURN(trace, removeInterval, res1 << " and " << res2);
    }
    else
    {
	TRACE_RETURN(trace, removeInterval, res1);
    }
    return result;
}

//**********************************************************************
