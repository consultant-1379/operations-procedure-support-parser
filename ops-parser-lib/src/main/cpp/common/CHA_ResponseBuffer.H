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

#ifndef CHA_RESPONSEBUFFER_H
#define CHA_RESPONSEBUFFER_H

#include <CHA_LibGlobals.H>

#include <rw/cstring.h>
#include <rw/tools/datetime.h>

class CHA_ResponseBuffer
{
public:
    CHA_ResponseBuffer(){}
    CHA_ResponseBuffer(const RWCString& respBuf,
		       const RWCString& cmd,
		       const RWCString& syst,
		       const RWDateTime& 	t,
			     int 	devId);
    // Description:
    //     Constructor.
    // Parameters:
    //     respBuf		IN: the response string
    //     cmd                  IN: the command that caused the response
    //     syst                 IN: the system that caused the response
    //     t			IN: the time of response
    //	   devId		IN: the device Id

    CHA_ResponseBuffer(const RWCString& respBuf,
		       const RWCString& cmd,
		       const RWCString& syst,
			     int 	devId);
    // Description:
    //     Constructor.
    // Parameters:
    //     respBuf		IN: the response string
    //     cmd                  IN: the command that caused the response
    //     syst                 IN: the system that caused the response
    //	   devId		IN: the device Id

    CHA_ResponseBuffer(const RWCString& respBuf,
		       const RWCString& cmd,
		       const RWCString& syst,
		       const RWDateTime& 	t);
    // Description:
    //     Constructor.
    // Parameters:
    //     respBuf		IN: the response string
    //     cmd                  IN: the command that caused the response
    //     syst                 IN: the system that caused the response
    //     t			IN: time of response

    CHA_ResponseBuffer(const RWCString& respBuf,
		       const RWCString& cmd,
		       const RWCString& syst);
    // Description:
    //     Constructor.
    // Parameters:
    //     respBuf		IN: the response string
    //     cmd                  IN: the command that caused the response
    //     syst                 IN: the system that caused the response
        
    CHA_ResponseBuffer(      RWBoolean  cmdFileResp,
                       const RWCString& respBuf,
		       const RWCString& cmd,
		       const RWCString& syst);
    // Description:
    //     Constructor.
    // Parameters:
    //     respBuf		IN: the response string
    //     cmd                  IN: the command that caused the response
    //     syst                 IN: the system that caused the response
    //     isCmdFileResp        IN: 
        

    CHA_ResponseBuffer(const RWCString& respBuf);
    // Description:
    //     Constructor.
    // Parameters:
    //     respBuf		IN: the response string

    CHA_ResponseBuffer(const CHA_ResponseBuffer& other);
    // Description:
    //     Copy constructor. Initiates a CHA_ResponseBuffer with the
    //     same value as another response buffer.
    // Parameters:
    //     other		IN: the CHA_ResponseBuffer to copy from

  virtual CHA_ResponseBuffer* copy() const = 0;
    // Description:
    //     Copy method. Return a subclass type of CHA_ResponseBuffer instead
    //     of the superclass itself.
    // Return value:
    //     A reference to the object itself.

    virtual ~CHA_ResponseBuffer();
    // Description:
    //     Destructor.

    virtual CHA_ResponseBuffer& operator=(const CHA_ResponseBuffer& other);
    // Description:
    //     Assignment operator.
    // Parameters:
    //     other		IN: the CHA_ResponseBuffer to copy from
    // Return value:
    //     A reference to the object itself.

  virtual RWBoolean operator==(const CHA_ResponseBuffer& other);
    // Description:
    //     Equality operator.
    // Parameters:
    //     other		IN: the CHA_ResponseBuffer to compare with
    // Return value:
    //     TRUE or FALSE

    virtual RWCString getText() const;
    // Description:
    //     Used in order to acces the response string.
    // Return value:
    //     A RWCString containing the response string.

    virtual RWCString getHeader() const = 0;
    // Description:
    //     This method is used for retrieving a header suitable for
    //     printing. A subclass must overload this method to
    //     return a header, containing important
    //     information about the response, such as command, time, date,
    //     device ID and response type.
    // Return value:
    //     A RWCString containing the header.

    virtual RWCString getOneLineHeader() const = 0;
    //     This method is used for retrieving a one line header suitable for
    //     printing. A subclass must overload this method to
    //     return a header, containing important
    //     information about the response, such as command, time, date,
    //     device ID and response type.
    // Return value:
    //     A RWCString containing the header.

    virtual RWCString getCommand() const;
    // Description:
    //     Get the command that caused the response.
    // Return value:
    //     A RWCString containing the command. If no command is known
    //     the string is empty.

    virtual RWCString getSrcSystem() const;
    // Description:
    //     Get the source system of the response, e.i. the system
    //     that sent the response.
    // Return value:
    //     A RWCString containing the source system. If no source
    //     system is known the string is empty.

    virtual RWDateTime getTime() const;
    // Description:
    //     Get the time of the response.
    // Return value:
    //     A RWTime.

    virtual int getDeviceId() const;
    // Description:
    //     Get the deviceId of the response.
    // Return value:
    //     An int.

     RWBoolean isCmdFileType() const;
    // Description:
    //     
    // Return value:
    //   

    virtual CHA_ResponseType getRespType() const;
    // Description:
    //     Get the response type.
    // Return values:
    //     CHA_RT_UNDEFINED		response type not known
    //     CHA_RT_IMMEDIATE		an immediate response
    //     CHA_RT_DELAYED		a delayed response
    //     CHA_RT_SPONTANEOUS		a spontaneous report
    //     CHA_RT_COMMANDFILE		output from a command file
    //     CHA_RT_SYSCOMMANDFILE	output from a system command file
    //     CHA_RT_LOGSEARCH		the result of a search in the log

  
    virtual void append(const RWCString& resp);
    // Description:
    //     Appends a string to the current response string. Can be
    //     used when several buffers of the same response are
    //     availble. Time, type and origin information is not
    //     changed.
    // Parameters:
    //     string		the response string to append

    virtual void append(const CHA_ResponseBuffer& other);
    // Description:
    //     Appends an other response to the current response. Can be
    //     used when several buffers of the same response are
    //     availble. Time, type and origin information is taken
    //     from the current response.
    // Parameters:
    //     other		the other response to append

protected:

    RWCString response;		// the actual response string
    RWCString srcSyst;		// the source system of the response
    RWCString command;		// the command that caused the response
    CHA_ResponseType type;	// the type of the response
    RWDateTime time;		// the time of response arrival
    int deviceId;		// the device ID of the association
    RWBoolean cmdFileType;      // 
};

#endif
