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

#ifndef OZT_VALUE_H
#define OZT_VALUE_H

#include <rw/cstring.h>
#include "OZT_ErrHandling.H"
#include <OPSC.H>
#include <stdint.h>
class OZT_Value: public RWCString {
public:
    OZT_Value();
    OZT_Value(const OZT_Value& v);
    OZT_Value(const char* s);
    OZT_Value(const RWCString& s);
    OZT_Value(const RWCSubString& s);
    OZT_Value(char c);
    OZT_Value(CORBA::Long i);
    OZT_Value(long i);
    
    // Description
    //     Constructors in various forms.

    ~OZT_Value();
    // Description
    //     Destructor.

    int toInt(OZT_Result& res) const;
    long toLong(OZT_Result& res) const;
    // Description
    //     Converts to long.

    OZT_Value toHex(OZT_Result& res) const;
    // Description
    //     Converts to a Hex string-like value.
    // Parameter
    //     res     OUT: returns OZT_Result(INVALID_VALUE) if conversion fails

    OZT_Value toHex(OZT_Result& res, const OZT_Value& width) const;
    // Description
    //     Converts to a Hex string-like value with a given width. If
    //     the resulting string is too long, only the least significant
    //     characters are returned.

    OZT_Value toDec(OZT_Result& res) const;
    // Description
    //     Convert a Hex string-like value to a decimal value.

    RWBoolean toBoolean(OZT_Result& res) const;
  // Description
  //     Convert an OZT_Value object to a Boolean

  RWBoolean isHex();

  // Description
  //     Check if the value is a valid Hex number

    OZT_Value copy(const OZT_Value& start,
                   const OZT_Value& len,
                   OZT_Result& result) const;
  // Description
  //     Copy a sub-string from a specified position.

  size_t length() const{
    return RWCString::length() - unvisibleChars;
  }
  
  int unvisibleChars;
};

RWBoolean operator> (const OZT_Value& a, const OZT_Value& b);
RWBoolean operator>=(const OZT_Value& a, const OZT_Value& b);
RWBoolean operator<=(const OZT_Value& a, const OZT_Value& b);
RWBoolean operator< (const OZT_Value& a, const OZT_Value& b);
OZT_Value operator+(const OZT_Value&, const OZT_Value&);
OZT_Value operator+(const char*,      const OZT_Value&);
OZT_Value operator+(const OZT_Value&, const char*     );
// Description
//     Comparison operators

OZT_Value unaryPlus(const OZT_Value& a, OZT_Result& res);
OZT_Value unaryMinus(const OZT_Value& a, OZT_Result& res);
OZT_Value add(const OZT_Value& a, const OZT_Value& b, OZT_Result& res);
OZT_Value sub(const OZT_Value& a, const OZT_Value& b, OZT_Result& res);
OZT_Value mul(const OZT_Value& a, const OZT_Value& b, OZT_Result& res);
OZT_Value div(const OZT_Value& a, const OZT_Value& b, OZT_Result& res);
// Description
//     Numeric operation functions

OZT_Value center(const OZT_Value& text,
		 const OZT_Value& len,
		 OZT_Result& res);
  //Description
  //     Center a  string    

OZT_Value leftJustify(const OZT_Value& text,
		      const OZT_Value& len,
		      OZT_Result& res);
  //Description
  //     Left justify a string
  
OZT_Value rightJustify(const OZT_Value& text,
		       const OZT_Value& len,
		       OZT_Result& res);
  //Description
  //     Right justify a string

#endif