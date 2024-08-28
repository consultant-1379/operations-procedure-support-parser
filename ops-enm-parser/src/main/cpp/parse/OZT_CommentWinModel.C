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


#include <OZT_CommentWinModel.H>


//*****************************************************************************


// trace

#include <trace.H>
static std::string trace ="OZT_CommentWinModel";
//static CAP_TRC_trace trace = CAP_TRC_DEF(((char*)"OZT_CommentWinModel"), ((char*)"C"));

//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_CommentWinModel.C,v 21.0 1996/08/23 12:43:46 ehsgrap Rel $";


//*****************************************************************************


OZT_CommentWinModel::OZT_CommentWinModel()
: active(FALSE),
  toBeCleared(FALSE),
  toFormat_(FALSE)
{
    TRACE_IN(trace, OZT_CommentWinModel, "");

    TRACE_OUT(trace, OZT_CommentWinModel, "");
}


OZT_CommentWinModel::~OZT_CommentWinModel()
{
}


void OZT_CommentWinModel::addText(const RWCString &textBlk, RWBoolean format)
{
    TRACE_IN(trace, addText, textBlk);

    if (active)
    {
      toFormat_ = format;

      changed((void*)(&textBlk));
      
      //reset the format flag
      toFormat_ = FALSE;
    }

    TRACE_OUT(trace, addText, "");
}

void OZT_CommentWinModel::beActive()
{
    TRACE_IN(trace, beActive, "");

    active = TRUE;
    changed(0);
    
    TRACE_OUT(trace, beActive, "");
}


void OZT_CommentWinModel::beInactive()
{
    TRACE_IN(trace, beInactive, "");

    active = FALSE;
    changed(0);

    TRACE_OUT(trace, beInactive, "");
}


void OZT_CommentWinModel::clear()
{
    TRACE_IN(trace, clear, "");

    toBeCleared = TRUE;
    changed(0);
    toBeCleared = FALSE;

    TRACE_OUT(trace, clear, "");
}


RWBoolean OZT_CommentWinModel::isActive() const
{
    TRACE_IN(trace, isActive, "");

    TRACE_RETURN(trace, isActive, active);
    return active;
}

RWBoolean OZT_CommentWinModel::toClear() const
{
    TRACE_IN(trace, toClear, "");

    TRACE_RETURN(trace, toClear, toBeCleared);
    return toBeCleared;
}

RWBoolean OZT_CommentWinModel::toFormat() const
{
  TRACE_IN(trace, toFormat, "");

  TRACE_RETURN(trace, toFormat, toFormat_);

  return toFormat_;
}
