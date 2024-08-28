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

#ifndef OZT_CMD_RSP_BUF_H
#define OZT_CMD_RSP_BUF_H

#include <rw/cstring.h>
#include <rw/tvordvec.h>
#include <CHA_LogSource.H>
// HE87081 & HE93921
#include <rw/tvslist.h>
#include <OZT_Value.H>
// END HE87081 & HE93921
#include <vector>
#include <string>

class OZT_CmdRspBuf: public CHA_LogSource {
public:
     OZT_CmdRspBuf();
     //  Description
     //      Constructor.

     OZT_CmdRspBuf(std::vector<std::string> rspBuf);
     // Description
     //      Parameterized constructor for UT

     virtual ~OZT_CmdRspBuf();
     //  Description
     //      Destructor.

     void markBeginOfRsp();
     //  Description
     //      This function should be called if the beginning of a new 
     //      response is coming. It resets the mark to the beginning
     //      of the buffer.

     RWCString reply(const size_t lineIndex) const;
     //  Description
     //      Return the line in the buffer relative to the "mark".
     //  Parameter
     //      lineIndex        IN:the line number of the line to be 
     //                          retrieved, relative to the mark.
     //  Return value
     //      The content of the line retrieved. No trailiing
     //      newline character is included.

     size_t replyLen() const;
     //  Description
     //      Returns the number of lines in the buffer from the mark.
     //  Return value
     //      The number of lines from the mark.

     void markLine();
     //  Description
     //      Move the mark to the end of the buffer.
   
     void markLine(const long &offset);
     //  Description
     //      Move the mark by an offset. The offset can be positive
     //      or negative. The mark cannot be moved prior to the 
     //      beginning of the current response.
     //  Parameter
     //      offset      IN: the offset to be moved.

     void markSearchBackPoint();
     //  Description
     //      To be called to mark the range of the buffer for searching 
     //      backward for @WAITFOR and @WAITREPLY.

     RWBoolean find(const RWCString &str, int startMark = -1) const;
     //  Description
     //      Find "str" from the search back point set previously. 
     //      To be used for @WAITFOR and @WAITREPLY.
     //  Parameter
     //      str         IN: the string to be searched.
     //  Return Value
     //      TRUE        if the string is found from the search back
     //                  point onwards.
     //      FALSE       if the string is not found from the search back
     //                  point onwards.

     void markEndOfRsp();
     //  Description
     //      This function should be called if the end of a response
     //      is met. It is for the purpose of @WAITREPLY.

     RWBoolean isRspEnded() const;
     //  Description
     //      Test if there is a complete response in the buffer. It is
     //      for the purpose of @WAITREPLY.
     //  Return value
     //      TRUE        A complete response is contained in the buffer.
     //      FALSE       No complete response is contained in the buffer.

  RWBoolean getFormatFlag() const;

     RWCString getUpdateText() const;
     //  Description
     //      Retrieve the new text appended to the buffer. This function
     //      is to be called by model client within the updateFrom call.
     //  Return value
     //      The new text just appended to the buffer
     
     void append(const RWCString &text, RWBoolean toFormat = FALSE);
     //  Description
     //      Append text to the buffer. After the text is added, all
     //      model clients are notified in order for them to get the
     //      new text added.
     //  Parameter
     //      text               IN: the new text to be appened.

     size_t scan(const RWCString &key, const size_t &startLine, 
		 size_t &pos) const;
     size_t scan(const RWCString &key, size_t &pos) const;
     size_t scan(const RWCString &key) const;
     size_t scanLastReply(const RWCString &key);
     // HE87081 & HE93921
	 void scanForFailStrings(RWTValSlist<RWCString> extraFailStrings, OZT_Result& result, long);
     // END HE87081 & HE93921
	 
     //  Description
     //      These functions are for the @SCAN command. It searches 
     //      the buffer for the string "key".
     //  Parameter
     //      key                IN: the string to be found
     //      startLine          IN: the start line number for searching
     //                             the "key". Note that it is an absolute 
     //                             number from the beginning of the current
     //                             response, not a relative number from the
     //                             mark.
     //      pos                OUT: the position of "key"within the 
     //                              line found.
     //  Return value
     //      The line number from the mark where the "key" is found. 0
     //      is returned if there is no match.

     void clrScr();
     //  Description
     //      When called, this class informs all clients to clear
     //      the corresponding user interface object that represents
     //      the buffer.

     RWBoolean toClearScr();
     //  Description
     //      For clients to query about whether the corresponding
     //      user interface object should clear its area.

  long getMark();
  long getStoreSize();
  std::string getLastText();
  void updateStore();
  void MarksetterTest(std::vector<std::string> TestStrings) {
    store = TestStrings;
    mark = 0;
  }

private:
     std::vector<std::string>  store;
     RWCString toBeUpdateText;
     size_t    endOfLastReply;
     size_t    mark;
     size_t    searchBackPoint;
     RWBoolean rspEnded;
     RWBoolean scrToBeCleared;
     RWBoolean toBeFormatted;
};

#endif
