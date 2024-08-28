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

#include <iostream>
#include <ostream>
#include "OZT_Flow.H"

//*****************************************************************************


// trace

#include <trace.H>
static std::string trace ="OZT_Flow";

//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_Flow.C,v 21.0 1996/08/23 12:44:06 ehsgrap Rel $";


//*****************************************************************************

OZT_Flow::OZT_Flow(const OZT_Flow::Code codeIn,
                   const RWCString      &info1In,
                   const RWCString      &info2In,
                   const RWCString      &info3In)
{
    code         = codeIn;
    skipElseFlag = FALSE;
    info1        = info1In;
    info2        = info2In;
    info3        = info3In;
}

OZT_Flow& OZT_Flow::operator=(const OZT_Flow& f)
{
    if (this != &f) {
        code         = f.code;
        skipElseFlag = f.skipElseFlag;
        info1        = f.info1;
        info2        = f.info2;
        info3        = f.info3;
    }
    return *this;
}

RWCString OZT_Flow::toMsg() const
{
    switch(code) 
    {
        case OZT_Flow::UNDEFINED : 
             return "UNDEFINED"; 

        case OZT_Flow::NORMAL    : 
             return "NORMAL";

        case OZT_Flow::FOR_SETUP : 
             return RWCString("FOR_SETUP(") + info1 + RWCString(", ") + info2 
                     + RWCString(", ") + info3 + RWCString(")");

        case OZT_Flow::NEXT : 
             return RWCString("NEXT(") + info1 + RWCString(")");

        case OZT_Flow::GOTO_LABEL: 
             return RWCString("GOTO(") + info1 + RWCString(")");

        case OZT_Flow::GOSUB_LABEL: 
             return RWCString("GOSUB(") + info1 
                    + (skipElseFlag? RWCString(", skipElse)") : RWCString(")"));

        case OZT_Flow::RETURN_FROM_GOSUB:
             return "RETURN_FROM_GOSUB";

        case OZT_Flow::INCLUDE:
             return RWCString("INCLUDE(") + info1
                    + (skipElseFlag? RWCString(", skipElse)") : RWCString(")"));

        case OZT_Flow::END_OF_FILE:
             return "END_OF_FILE";

        case OZT_Flow::PAUSE:
             return "PAUSE";

        case OZT_Flow::QUIT:
             return "QUIT";

        case OZT_Flow::STOP:
             return "STOP";

        case OZT_Flow::IF:
	     return "IF";

        case OZT_Flow::ELSE:
	     return "ELSE";

        case OZT_Flow::ENDIF:
             return "ENDIF";

        case OZT_Flow::RESTART:
             return "RESTART";

        case OZT_Flow::FILE_HALTED:
             return "FILE_HALTED";
    case OZT_Flow::SWITCH:
      return "SWITCH";
    case OZT_Flow::CASE:
      return "CASE";
    case OZT_Flow::DEFAULT:
      return "DEFAULT";
    case OZT_Flow::ENDSWITCH:
      return "ENDSWITCH";
        default:
             return "Unknown flow value";
    }
}


std::ostream& operator<<(std::ostream& os, const OZT_Flow& flow) 
{
    return os << flow.toMsg();
}
