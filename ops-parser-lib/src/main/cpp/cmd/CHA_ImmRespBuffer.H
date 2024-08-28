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

#ifndef CHA_IMMRESPBUFFER_H
#define CHA_IMMRESPBUFFER_H


#include <CHA_ResponseBuffer.H>
#include <rw/cstring.h>
#include <rw/tools/datetime.h>



class CHA_ImmRespBuffer : public CHA_ResponseBuffer
{

    friend RWBoolean operator==(const CHA_ImmRespBuffer& b1,
				const CHA_ImmRespBuffer& b2);
    
public:
    CHA_ImmRespBuffer(){}    
    CHA_ImmRespBuffer(const RWCString& respBuf,
		      const RWCString& cmd,
		      const RWCString& syst,
		      const RWDateTime&    t,
			    int	       devId);

    // Description:
    //     Constructor.
    // Parameters:
    //     respBuff		IN: the response string
    //     cmd			IN: the command that caused the response
    //     syst			IN: the system that caused the response
    //	   t			IN: the time of the arrival of the response
    //	   devId	 	IN: the device ID

    CHA_ImmRespBuffer(const RWCString& respBuf,
		      const RWCString& cmd,
		      const RWCString& syst,
			    int	       devId);

    // Description:
    //     Constructor.
    // Parameters:
    //     respBuff		IN: the response string
    //     cmd			IN: the command that caused the response
    //     syst			IN: the system that caused the response
    //	   devId	 	IN: the device ID

    CHA_ImmRespBuffer(const RWCString& respBuf,
		      const RWCString& cmd,
		      const RWCString& syst);

    // Description:
    //     Constructor.
    // Parameters:
    //     respBuff		IN: the response string
    //     cmd			IN: the command that caused the response
    //     syst			IN: the system that caused the response

    CHA_ImmRespBuffer(      RWBoolean cmdFileResp,
		      const RWCString& respBuf,
		      const RWCString& cmd,
		      const RWCString& syst);

    // Description:
    //     Constructor.
    // Parameters:
    //     cmdFileResp          IN: 
    //     respBuff		IN: the response string
    //     cmd			IN: the command that caused the response
    //     syst			IN: the system that caused the response


    CHA_ImmRespBuffer(const CHA_ResponseBuffer& other);
    // Description:
    //     Sort of copy constructor.
    // Parameters:
    //     other		IN: the response buffer to copy
    
    CHA_ImmRespBuffer(const CHA_ImmRespBuffer& other);
    // Description:
    //     True copy constructor.
    // Parameters:
    //     other		IN: the response buffer to copy

    virtual CHA_ResponseBuffer*  copy() const;
    // Description:
    //     Returns a copy of the calling buffer.

    
    virtual RWCString getHeader() const;
    // Description:
    //     Returns a header suitable for printing.

    virtual RWCString getOneLineHeader() const;
    // Description:
    //     Returns a one line header suitable for printing.

    void setLayout(RWBoolean t, 
		   RWBoolean cmd, 
		   RWBoolean es, 
		   RWBoolean usr,
		   RWBoolean devId);
    // Description:
    //     Sets layout choiches.


private:

    RWBoolean	showTime;
    RWBoolean	showCommand;
    RWBoolean	showEsName;
    RWBoolean	showUser;
    RWBoolean	showDevId;

};

inline RWBoolean operator==(const CHA_ImmRespBuffer& b1,
			    const CHA_ImmRespBuffer& b2)
{
    return (&b1 == &b2);	// equality is the same as identity
}

#endif
