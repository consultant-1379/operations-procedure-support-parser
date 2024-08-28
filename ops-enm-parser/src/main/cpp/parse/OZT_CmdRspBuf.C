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

#include "OZT_CmdRspBuf.H"
#include <OZT_Misc.H>
#include <rw/regexp.h>
#include <rw/cstring.h>
#include <iostream>
#include <stdlib.h>

//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_CmdRspBuf";


//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_CmdRspBuf.C,v 21.0 1996/08/23 12:43:38 ehsgrap Rel $";
long funbusyRetryCnt;


//*****************************************************************************

OZT_CmdRspBuf::OZT_CmdRspBuf()
: toBeUpdateText(RWCString()),
  mark(0),
  searchBackPoint(0),
  endOfLastReply(0),
  rspEnded(FALSE),
  scrToBeCleared(FALSE),
  toBeFormatted(FALSE)
{
    TRACE_IN(trace, OZT_CmdRspBuf, "");

    TRACE_OUT (trace, OZT_CmdRspBuf, "");
}

//*****************************************************************************

OZT_CmdRspBuf::OZT_CmdRspBuf(std::vector<std::string>rspBuf)
: mark(2),
  searchBackPoint(0),
  rspEnded(TRUE)
{
    for (int i=0; i<rspBuf.size(); i++)
    {
        store.push_back(rspBuf[i]);
    }
}

//*****************************************************************************

OZT_CmdRspBuf::~OZT_CmdRspBuf()
{
    store.clear();
}

//*****************************************************************************

void OZT_CmdRspBuf::markBeginOfRsp()
{
    TRACE_IN(trace, markBeginOfRsp, "");

    toBeUpdateText = RWCString();
    toBeFormatted = FALSE;
    //move the mark to the end of buffer
    long delta_mark     = store.size() - mark;
    changed( (void*)&delta_mark );
    searchBackPoint = 0;
    rspEnded = FALSE;
    scrToBeCleared = FALSE;
    store.clear();
    mark = 0;
	// HE87081 & HE93921
	endOfLastReply = 0;
	// END HE87081 & HE93921
	
    TRACE_OUT(trace, markBeginOfRsp, "");
}
//*****************************************************************************
long OZT_CmdRspBuf::getMark() {
  TRACE_IN(trace, getMark, "");
  TRACE_OUT(trace, getMark, mark);

  return mark;
}
//*****************************************************************************

long OZT_CmdRspBuf::getStoreSize()
{
	return store.size();
}

//*****************************************************************************

RWCString OZT_CmdRspBuf::reply(const size_t lineIndex) const
{
    TRACE_IN(trace, reply, lineIndex);

    RWCString tempLine;

    if (store.size() == 0)
    {
        TRACE_RETURN(trace, reply, "");
        return RWCString();
    }

    if ((lineIndex + mark - 1) < 0)
    {
        TRACE_RETURN(trace, reply, "Overflow! return empty string");
        return RWCString();
    }

    if (lineIndex + mark - 1 >= store.size())
    {
        TRACE_RETURN(trace, reply, "");
        return RWCString();
    }

    tempLine = store[lineIndex + mark - 1].c_str();
    while (tempLine[tempLine.length() - 1] == '\n' 
              || tempLine[tempLine.length() - 1] == '\r') {
        tempLine.remove(tempLine.length() - 1);
        if (0 == tempLine.length()) {
            break;
        }
    }
    TRACE_RETURN(trace, reply, tempLine);
    return tempLine;
}

//*****************************************************************************

size_t OZT_CmdRspBuf::replyLen() const
{
    TRACE_FLOW(trace, replyLen, store.size() - mark);
    return store.size() - mark;
}

//*****************************************************************************

void OZT_CmdRspBuf::markLine()
{
    TRACE_IN(trace, markLine, "");
    long oldMark = mark;
TRACE_OUT(trace, markLine, " wa- Old mark is = " << oldMark);
    mark = store.size();
    searchBackPoint = mark;
    rspEnded = FALSE;
    long delta_mark = mark - oldMark;
    changed( (void*)&delta_mark );

    TRACE_OUT(trace, markLine, "new mark = " << mark);
}

//*****************************************************************************

void OZT_CmdRspBuf::markLine(const long &offset)
{
    TRACE_IN(trace, markLine, offset);

    long oldMark = mark;
TRACE_OUT(trace, markLine, "Old mark is = " << oldMark);
    if (store.size() == 0)
        mark = 0;
    else if (((long)mark + offset) <= 0)
        mark = 0;
    else if (((long)mark + offset) > store.size())
        mark = store.size();
    else
        mark = (size_t)((long)mark + offset);

    long delta_mark = mark - oldMark;
    changed( (void*)&delta_mark );

    TRACE_OUT(trace, markLine, "new mark = " << mark);
}

//*****************************************************************************

void OZT_CmdRspBuf::markSearchBackPoint()
{
    TRACE_IN(trace, markSearchBackPoint, "");

    searchBackPoint = store.size();
    rspEnded = FALSE;
    changed();

    TRACE_OUT(trace, markSearchBackPoint, "");
}

//*****************************************************************************

RWBoolean OZT_CmdRspBuf::find(const RWCString &str, int startMark) const
{
    TRACE_IN(trace, find, "");
    
    size_t dummy;
    if (startMark == -1) {
        if (str.isNull() || (scan(str, searchBackPoint, dummy) != 0))
        {
            TRACE_RETURN(trace, find, "TRUE");
            return TRUE;
        }
        else
        {
            TRACE_RETURN(trace, find, "FALSE");
            return FALSE;
        }
    }
    else {
        if (str.isNull() || (scan(str, startMark, dummy) != 0)) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
}
//*****************************************************************************

void OZT_CmdRspBuf::markEndOfRsp()
{
    TRACE_IN(trace, markEndOfRsp, "");

    rspEnded = TRUE;
    toBeUpdateText = RWCString();
    toBeFormatted = FALSE;
    changed();

    TRACE_OUT(trace, markEndOfRsp, "");
}

//*****************************************************************************

RWBoolean OZT_CmdRspBuf::isRspEnded() const
{
    return rspEnded;
}

//*****************************************************************************
RWBoolean OZT_CmdRspBuf::getFormatFlag() const
{
  TRACE_IN(trace, getFormatFlag, "");
  TRACE_RETURN(trace, getFormatFlag, toBeFormatted);
  return toBeFormatted;
}
//*****************************************************************************

RWCString OZT_CmdRspBuf::getUpdateText() const
{

  TRACE_IN(trace, getUpdateText, "");
  TRACE_RETURN(trace, getUpdateText, toBeUpdateText);
  return toBeUpdateText;
}

//*****************************************************************************

void OZT_CmdRspBuf::append(const RWCString &chunk, RWBoolean toFormat)
{
  TRACE_IN(trace, append, "string:" << chunk << " To format:" << toFormat);
    // A string that matches the line-boundary characters. For the
    // moment we do not match CR as it is not a "vertical motion
    // character".
    
    const char* newLine = "\n\v\f"; // don't include CR, \r
    size_t start = 0;
    size_t pos;
    std::string newChunk;

    toBeUpdateText = chunk;
    toBeFormatted = toFormat;

    //
    //  In case the last line is not terminated
    //
    if (store.size() != 0)
    {
      newChunk = store.back() + (const char*)chunk;   
      store.pop_back();
    }
    else
    {
      newChunk = chunk;
    }

    while(start < newChunk.length())
    {
        pos = newChunk.find_first_of(newLine, start);
        if (pos != RW_NPOS)
        {
	    store.push_back(newChunk.substr(start, pos - start + 1)); // incl `newLine'
            start = pos + 1;
        } else {
	    store.push_back(newChunk.substr(start, newChunk.length() - start));
            break;
        }
    }
    changed();
    toBeUpdateText = RWCString();  // reset to empty string
    toBeFormatted = FALSE;
    TRACE_OUT(trace, append, "");
}

// HE87081 & HE93921
void OZT_CmdRspBuf::scanForFailStrings(RWTValSlist<RWCString> extraFailStrings, OZT_Result& result, long retry)
{
    TRACE_IN(trace, scanForFailStrings, "");
	long realEndOfLastReply = endOfLastReply;
	size_t i;
	funbusyRetryCnt = retry;
	
	for (i = 0; i < extraFailStrings.entries(); i++)
    {
    	endOfLastReply = realEndOfLastReply;
//    	TRACE_FLOW(trace, scanForFailStrings, ": " << extraFailStrings[i] << " from " << endOfLastReply);
        if (scanLastReply(extraFailStrings[i]) != 0)
        {
            result = OZT_Result(OZT_Result::REPLY_CHECK_FAIL,
                                extraFailStrings[i]);
            break;
        }
    }
    
    TRACE_RETURN(trace, scanForFailStrings, result);
}
// END HE87081 & HE93921



//*****************************************************************************

// HD80040 Only scan the last reply, otherwise will the @SEND
//         command set the error flag if there are earlier errors
//	   in the buffer.
size_t OZT_CmdRspBuf::scanLastReply(const RWCString &key)
{
    TRACE_IN(trace, scanLastReply, key);

    size_t pos;
    size_t result;

    long startOfLastReply = endOfLastReply;
    endOfLastReply = store.size();
    
TRACE_FLOW(trace, scanLastReply, "Scanning for: " << key << " from " << startOfLastReply << " to " << endOfLastReply);
    result = scan(key, startOfLastReply, pos);

    TRACE_RETURN(trace, scanLastReply, result);
    return result;
}

//*****************************************************************************

size_t OZT_CmdRspBuf::scan(const RWCString &key) const
{
    TRACE_IN(trace, scan1, key);

    size_t pos;
    size_t result;

    result = scan(key, pos);

    TRACE_RETURN(trace, scan1, result);
    return result;
}

//*****************************************************************************

size_t OZT_CmdRspBuf::scan(const RWCString &key, size_t &pos) const
{
    TRACE_IN(trace, scan2, key);

    size_t result;
  
    result = scan(key, mark, pos);

    TRACE_RETURN(trace, scan2, result);
    return result;
}

//*****************************************************************************

size_t OZT_CmdRspBuf::scan(const RWCString &key, 
                           const size_t &startLine, size_t &pos) const
{
    TRACE_IN(trace, scan3, key);

    size_t i = startLine;
    
    while (i < store.size())
    {
        if ((pos = store[i].find((const char*)key)) != RW_NPOS)
        {
            pos++;
// HD90814 & HE27512
			size_t pos2=0;
            if ((key == "NOT ACCEPTED") && (scan("FUNCTION BUSY", i, pos2) != 0))
	      	{
				TRACE_FLOW(trace, scan3, "Found NOT ACCEPTED and FUNCTION BUSY");
				pos = 0;
				TRACE_RETURN(trace, scan3, "funbusyRetry Count : " << funbusyRetryCnt);
				return (funbusyRetryCnt > 0) ? 0 : -1;
	      	}
	      	else
	      	{
            	TRACE_RETURN(trace, scan3, i - mark + 1 << ", pos: " << pos);
            	return i - mark + 1;
	      	}
	      	
//            TRACE_RETURN(trace, scan, i - mark + 1 << ", pos: " << pos);
//            return i - mark + 1;
// END HD90814 & HE27512
        }
        else
            i++;
    }

    pos = 0;
    TRACE_RETURN(trace, scan3, 0);
    return 0;
}

//*****************************************************************************

void OZT_CmdRspBuf::clrScr()
{
    TRACE_IN(trace, clrScr, "");

    scrToBeCleared = TRUE;
    toBeUpdateText = RWCString();
    toBeFormatted = FALSE;
    changed();
    scrToBeCleared = FALSE;

    TRACE_OUT(trace, clrScr, "");
}

//*****************************************************************************

RWBoolean OZT_CmdRspBuf::toClearScr()
{
  return scrToBeCleared;
}

//****************************************************************************

std::string OZT_CmdRspBuf::getLastText() {
    if (store.size() == 0) {
        return "";
    }
    if (store.size() == 1) {
        return store[0];
    }
    return store[store.size() - 2].c_str();
}

//****************************************************************************

void OZT_CmdRspBuf::updateStore() {
    // shift each entry to index-1
    for (int i=1;i<store.size();i++) {
        store[i-1] = store[i];
    }

    // shrink the store by 1
    store.pop_back();
}