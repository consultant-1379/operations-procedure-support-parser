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


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <strstream>
#include <ctype.h>
#include <rw/ctoken.h>
#include "OZT_Value.H"
#include "OZT_Misc.H"
#include "OZT_ErrHandling.H"
#include <rw/tools/regex.h>


//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_Value";;
//static CAP_TRC_trace trace = CAP_TRC_DEF(((char*)"OZT_Value"), ((char*)"C"));

//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_Value.C,v 21.0 1996/08/23 12:45:00 ehsgrap Rel $";


//*****************************************************************************

OZT_Value::OZT_Value()
    : RWCString()
{
    // Nothing to code, simply use the constructor from the parent
  unvisibleChars = 0;
}

//************************************************************

OZT_Value::OZT_Value(const OZT_Value &v)
    : RWCString(v)
{
    // copy constructor, nothing to do, simply use the parent constructor
  unvisibleChars = v.unvisibleChars;
}

//************************************************************

OZT_Value::OZT_Value(const char* s)
    : RWCString(s)
{
    // Nothing to code, simply use the constructor from the parent
  unvisibleChars = 0;
}

//************************************************************

OZT_Value::OZT_Value(const RWCString &s)
    : RWCString(s)
{
    // Nothing to code, simply use the constructor from the parent
  unvisibleChars = 0;
}

//************************************************************

OZT_Value::OZT_Value(const RWCSubString &s)
    : RWCString(s)
{
    // Nothing to code, simply use the constructor from the parent
  unvisibleChars = 0;
}

//************************************************************

OZT_Value::OZT_Value(char c)
    : RWCString(c)
{
    // Nothing to code, simply use the constructor from the parent
  unvisibleChars = 0;
}

//************************************************************

OZT_Value::OZT_Value(CORBA::Long i)
{
    char str[256];  // should be more than enough

    sprintf(str, "%ld", i);
    *this = OZT_Value((char *)str);
    unvisibleChars = 0;
}

OZT_Value::OZT_Value(long i)
{
    char str[256];  // should be more than enough

    sprintf(str, "%ld", i);
    *this = OZT_Value((char *)str);
    unvisibleChars = 0;
}


//************************************************************

OZT_Value::~OZT_Value()
{
}

//************************************************************

long OZT_Value::toLong(OZT_Result& res) const
{
     long   v;
     size_t len;
     static RWTRegex<char> rexp("^[+-]?[0-9]+$");

     //
     //   validate the value before conversion
     //
     if (rexp.index(*this, &len) == RW_NPOS)
     {
          res.code = OZT_Result::INVALID_VALUE;
          return 0;
     }

     v = atol(data());
     res.code = OZT_Result::NO_PROBLEM;
     return v;
}

//************************************************************

int OZT_Value::toInt(OZT_Result& res) const
{
     int   v;
     size_t len;
     static RWTRegex<char>      rexp("^[+-]?[0-9]+$");

     //
     //   validate the value before conversion
     //
     if (rexp.index(*this, &len) == RW_NPOS)
     {
          res.code = OZT_Result::INVALID_VALUE;
          return 0;
     }

     v = atoi(data());
     res.code = OZT_Result::NO_PROBLEM;
     return v;
}

//***********************************************************
RWBoolean OZT_Value::toBoolean(OZT_Result& res)const
{
  long v;
  
  v = toLong(res);
  if (res.code != OZT_Result::NO_PROBLEM)
    return FALSE;

  if( v == 1L )
    return TRUE;
  else if( v == 0L )
    return FALSE;
  else{
    res = OZT_Result(OZT_Result::INVALID_VALUE);
    return FALSE;
  }
}

//***********************************************************

OZT_Value OZT_Value::toHex(OZT_Result& res) const
{
    long       v;
    strstream  resultS;
    OZT_Value  result;

    v = this->toLong(res);
    if (res.code != OZT_Result::NO_PROBLEM)
        return OZT_Value();

    resultS << hex << v << ends;

    res = OZT_Result(OZT_Result::NO_PROBLEM);
    result = resultS.str();
    delete [] resultS.str();
    result.toUpper();

    return result;
}

//***********************************************************

OZT_Value OZT_Value::toHex(OZT_Result& res, const OZT_Value& width) const
{
    long       v, len;
    strstream  resultS;
    OZT_Value  result;

    v = this->toLong(res);
    if (res.code != OZT_Result::NO_PROBLEM)
        return OZT_Value();

    len = width.toLong(res);
    if ((res.code != OZT_Result::NO_PROBLEM) || (len <= 0) || (len > 8))
    {
        res = OZT_Result(OZT_Result::INVALID_VALUE);
        return OZT_Value();
    }
       
    if (v < 0)
        resultS.fill('f');  // sign extension
    else
        resultS.fill('0');  // normal padding character

    resultS.width((int)len);
    resultS.precision((int)len);

    resultS << hex << v << ends;

    res = OZT_Result(OZT_Result::NO_PROBLEM);
    result = resultS.str();
    // only return the least significant digits if too long
    if (result.length() > len)
        result = result(result.length() - len, len);
    delete [] resultS.str();
    result.toUpper();

    return result;
}

//************************************************************
RWBoolean OZT_Value::isHex() {
  static RWTRegex<char>  check("^[0-9aAbBcCdDeEfF]+$");
  size_t len;
  if ((length() > 8) || (check.index(*this, &len) == RW_NPOS)){
    return FALSE;
  } 

  return TRUE;
  
}
//*********************************************************

OZT_Value OZT_Value::toDec(OZT_Result& res) const
{
    static RWTRegex<char>  check("^[0-9aAbBcCdDeEfF]+$");
    unsigned long       v;
    size_t len;

    if ((length() > 8) || (check.index(*this, &len) == RW_NPOS))
    {
        res = OZT_Result(OZT_Result::INVALID_VALUE);
        return OZT_Value();
    } 
    res = OZT_Result(OZT_Result::NO_PROBLEM); 
    sscanf(data(), "%x", &v);

    return OZT_Value((int32_t)v);
}

//************************************************************

OZT_Value OZT_Value::copy(const OZT_Value& start,
                          const OZT_Value& len,
                          OZT_Result& result) const
{
     long x, y;
 
     x = start.toLong(result);
     if ((result.code != OZT_Result::NO_PROBLEM) || (x <= 0))
     {
         result = OZT_Result(OZT_Result::INVALID_VALUE);
         return OZT_Value();
     }

     y = len.toLong(result);
     if ((result.code != OZT_Result::NO_PROBLEM) || (y < 0)) 
     {
         result = OZT_Result(OZT_Result::INVALID_VALUE);
         return OZT_Value();
     }

     x--;      // Ozterm starts from 1, but string starts from 0
     if ((length() == 0) || (x >= length()))
     {
         result = OZT_Result(OZT_Result::NO_PROBLEM);
         return OZT_Value();
     }
     else
     {  
         if ((x + y) > length()) y = length() - x;
         result = OZT_Result(OZT_Result::NO_PROBLEM);
         //TORF-241666 return (*this)((unsigned)x, (unsigned)y);
         return OZT_Value((*this)((unsigned)x, (unsigned)y));
     }
}


//************************************************************

RWBoolean operator> (const OZT_Value& a, const OZT_Value& b)
{
    long v1, v2;
    OZT_Result result;

    v1 = a.toLong(result);
    if (result.code != OZT_Result::NO_PROBLEM)
        return (RWCString)a > (RWCString)b;       // use string comparison

    v2 = b.toLong(result);
    if (result.code != OZT_Result::NO_PROBLEM)
        return (RWCString)a > (RWCString)b;       // use string comparison

    return v1 > v2;    // use numeric comparison
}

//************************************************************

RWBoolean operator>=(const OZT_Value& a, const OZT_Value& b)
{
    long v1, v2;
    OZT_Result result;

    v1 = a.toLong(result);
    if (result.code != OZT_Result::NO_PROBLEM)
        return (RWCString)a >= (RWCString)b;       // use string comparison

    v2 = b.toLong(result);
    if (result.code != OZT_Result::NO_PROBLEM)
        return (RWCString)a >= (RWCString)b;       // use string comparison

    return v1 >= v2;    // use numeric comparison
}

//************************************************************
  
RWBoolean operator<=(const OZT_Value& a, const OZT_Value& b) 
{
    long v1, v2;
    OZT_Result result;

    v1 = a.toLong(result);
    if (result.code != OZT_Result::NO_PROBLEM)
        return (RWCString)a <= (RWCString)b;       // use string comparison

    v2 = b.toLong(result);
    if (result.code != OZT_Result::NO_PROBLEM)
        return (RWCString)a <= (RWCString)b;       // use string comparison

    return v1 <= v2;    // use numeric comparison
}

//************************************************************

RWBoolean operator< (const OZT_Value& a, const OZT_Value& b) 
{
    long v1, v2;
    OZT_Result result;

    v1 = a.toLong(result);
    if (result.code != OZT_Result::NO_PROBLEM)
        return (RWCString)a < (RWCString)b;       // use string comparison

    v2 = b.toLong(result);
    if (result.code != OZT_Result::NO_PROBLEM)
        return (RWCString)a < (RWCString)b;       // use string comparison

    return v1 < v2;    // use numeric comparison
}

OZT_Value operator+(const OZT_Value& a, const OZT_Value& b) {

  RWCString s = ((RWCString)a) + ((RWCString)b);
  
  OZT_Value val(s);
  val.unvisibleChars = a.unvisibleChars + b.unvisibleChars;

  return val;

}

OZT_Value operator+(const char* a, const OZT_Value& b){
  
  RWCString s = a + (( RWCString)b);
  
  OZT_Value val(s);
  val.unvisibleChars = b.unvisibleChars;

  return val;
}

OZT_Value operator+(const OZT_Value& a, const char* b){
  RWCString s = ((RWCString)a) + b;
  
  OZT_Value val(s);
  val.unvisibleChars = a.unvisibleChars;

  return val;
}
//************************************************************

/*
OZT_Value trim(const OZT_Value& v)
{
    register int i = 0;
    register int j = v.length() -1;

    //  trim leading white space
    while (i < v.length()) {
        if ((v[i] != ' ') && (v[i] != '\t'))
            break;
        i++;
    }

    //  trim trailing white space
    while (j > i) {
        if ((v[j] != ' ') && (v[j] != '\t'))
            break;
        j--;
    }

    if (i > j)
        return OZT_Value();
    else
        return v(i, j-i+1);
}

*/

//************************************************************

OZT_Value unaryPlus(const OZT_Value& a, OZT_Result& res)
{
    long v1;
 
    v1 = a.toLong(res);
    if (res.code != OZT_Result::NO_PROBLEM)
        return OZT_Value();
 
    res.code = OZT_Result::NO_PROBLEM;
    return a;
}


//************************************************************

OZT_Value unaryMinus(const OZT_Value& a, OZT_Result& res)
{
    long v;
    strstream buf;
    OZT_Value result;
 
    v = a.toLong(res);
    if (res.code != OZT_Result::NO_PROBLEM)
        return OZT_Value();
 
    buf << -v << ends;
 
    res = OZT_Result(OZT_Result::NO_PROBLEM);
    result = buf.str();
    delete [] buf.str();

    return result;
}


//************************************************************

OZT_Value add(const OZT_Value& a, const OZT_Value& b, OZT_Result& res)
{
    int v1;
    int v2;
    strstream buf;
    OZT_Value result;

    v1 = a.toInt(res);
    if (res.code != OZT_Result::NO_PROBLEM)
        return OZT_Value();

    v2 = b.toInt(res);
    if (res.code != OZT_Result::NO_PROBLEM)
        return OZT_Value();

    buf << v1 + v2 << ends;

    res = OZT_Result(OZT_Result::NO_PROBLEM);
    result = buf.str();
    delete [] buf.str();

    return result;
}


//************************************************************

OZT_Value sub(const OZT_Value& a, const OZT_Value& b, OZT_Result& res)
{
    int v1;
    int v2;
    strstream buf;
    OZT_Value result;
 
    v1 = a.toInt(res);
    if (res.code != OZT_Result::NO_PROBLEM)
        return OZT_Value(); 
 
    v2 = b.toInt(res);
    if (res.code != OZT_Result::NO_PROBLEM)
        return OZT_Value(); 
 
    buf << v1 - v2 << ends;
 
    res = OZT_Result(OZT_Result::NO_PROBLEM); 
    result = buf.str();
    delete [] buf.str();

    return result;
}


//************************************************************

OZT_Value mul(const OZT_Value& a, const OZT_Value& b, OZT_Result& res)
{
    long v1;
    long v2;
    strstream buf;
    OZT_Value result;
 
    v1 = a.toLong(res);
    if (res.code != OZT_Result::NO_PROBLEM)
        return OZT_Value(); 
 
    v2 = b.toLong(res);
    if (res.code != OZT_Result::NO_PROBLEM)
        return OZT_Value(); 
 
    buf << v1 * v2 << ends;
 
    res = OZT_Result(OZT_Result::NO_PROBLEM); 
    result = buf.str();
    delete [] buf.str();

    return result;
}


//************************************************************

OZT_Value div(const OZT_Value& a, const OZT_Value& b, OZT_Result& res)
{
    long v1;
    long v2;
    strstream buf;
    OZT_Value result;
 
    v1 = a.toLong(res);
    if (res.code != OZT_Result::NO_PROBLEM)
        return OZT_Value(); 
 
    v2 = b.toLong(res);
    if (res.code != OZT_Result::NO_PROBLEM)
        return OZT_Value(); 

    if (v2 == 0)
    {
        res.code = OZT_Result::DIVISION_BY_ZERO;
        return OZT_Value();
    }
 
    buf << v1 / v2 << ends;
 
    res = OZT_Result(OZT_Result::NO_PROBLEM); 
    result = buf.str();
    delete [] buf.str();

    return result;
}

//************************************************************

OZT_Value leftJustify(const OZT_Value& text,
		      const OZT_Value& len,
		      OZT_Result& res) {

  res = OZT_Result(OZT_Result::NO_PROBLEM);
  OZT_Value result(text);
  long l = len.toLong(res);

  if (res.code != OZT_Result::NO_PROBLEM)
    return OZT_Value();
  
  if( text.length() >= l ){
    result.resize( l );
    return result;
  }
  else {
    result = OZT_Value( text );
    long empty =  l - text.length();
    
    for( long count = 0; count < empty; count++ ) 
      result.append( " " );

    return result;
  }
}

//************************************************************

OZT_Value rightJustify(const OZT_Value& text,
		       const OZT_Value& len,
		       OZT_Result& res){

  res = OZT_Result(OZT_Result::NO_PROBLEM);
  OZT_Value result( text);
  long l = len.toLong(res);

  if (res.code != OZT_Result::NO_PROBLEM)
    return OZT_Value();

   if( text.length() >= l ){
    result.resize( l );
    return result;
   }
   else {
     result = OZT_Value( text );
     long empty =  l - text.length();
     
     for( long count = 0; count < empty; count++ ) 
       result.insert(0, " " );
     
     return result;
   }    
}

//************************************************************

OZT_Value center(const OZT_Value& text,
		 const OZT_Value& len,
		 OZT_Result& res) {
  res = OZT_Result(OZT_Result::NO_PROBLEM);
  OZT_Value result( text );
 
  long l = len.toLong(res);
  
  if (res.code != OZT_Result::NO_PROBLEM)
    return OZT_Value();

  if( text.length() >= l ){
    result.resize( l );
    return result;
  }
  else {
    result = OZT_Value( text );
    long empty =  l - text.length();
    long emptyBegin = empty / 2;
    long emptyEnd = empty - emptyBegin;

    long count;
    for( count = 0; count < emptyBegin; count++ ) 
      result.insert(0, " " );

    for( count = 0; count < emptyEnd; count++ ) 
      result.append(  " " );
  }

  return result;
}
