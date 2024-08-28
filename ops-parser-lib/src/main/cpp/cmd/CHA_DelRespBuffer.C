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


#include <CHA_DelRespBuffer.H>
#include <CHA_UserInfo.H>
#include <strstream>
#include <CHA_Trace.H>
#include <trace.H>

static std::string trace ="CHA_DelRespBuffer";
//**********************************************************************


CHA_DelRespBuffer::CHA_DelRespBuffer(const RWCString& respBuf,
				     const RWCString& cmd,
				     const RWCString& syst,
				     const RWDateTime&    t,
					   int	      devId)
: CHA_ResponseBuffer(respBuf, cmd, syst, t, devId),
  showTime(TRUE),
  showCommand(TRUE),
  showEsName(TRUE),
  showUser(TRUE),
  showDevId(TRUE)
{
    type = CHA_RT_DELAYED;
}


//**********************************************************************


CHA_DelRespBuffer::CHA_DelRespBuffer(const RWCString& respBuf,
				     const RWCString& cmd,
				     const RWCString& syst,
					   int	      devId)
: CHA_ResponseBuffer(respBuf, cmd, syst, devId),
  showTime(TRUE),
  showCommand(TRUE),
  showEsName(TRUE),
  showUser(TRUE),
  showDevId(TRUE)
{
    type = CHA_RT_DELAYED;
}


//**********************************************************************


CHA_DelRespBuffer::CHA_DelRespBuffer(const RWCString& respBuf,
				     const RWCString& cmd,
				     const RWCString& syst)
: CHA_ResponseBuffer(respBuf, cmd, syst),
  showTime(TRUE),
  showCommand(TRUE),
  showEsName(TRUE),
  showUser(TRUE),
  showDevId(FALSE)
{
    type = CHA_RT_DELAYED;
}


//**********************************************************************


CHA_DelRespBuffer::CHA_DelRespBuffer(      RWBoolean  cmdFileResp,
				     const RWCString& respBuf,
				     const RWCString& cmd,
				     const RWCString& syst)
: CHA_ResponseBuffer(cmdFileResp, respBuf, cmd, syst),
  showTime(TRUE),
  showCommand(TRUE),
  showEsName(TRUE),
  showUser(TRUE),
  showDevId(FALSE)
{
    type = CHA_RT_DELAYED;
}


//**********************************************************************

CHA_DelRespBuffer::CHA_DelRespBuffer(const CHA_ResponseBuffer& other)
: CHA_ResponseBuffer(other)
{
    type = CHA_RT_DELAYED;
}


//**********************************************************************


RWCString CHA_DelRespBuffer::getHeader() const
{
    TRACE_IN(trace, CHA_DelRespBuffer, "");

    // ----------------------------------------
    // ES name:        AXE19
    // Time:           Thu Mar  3 10:03:23 1994
    // User:           tmosadm
    // Command:        LABUP;
    // DeviceId:       1234
    // ----------------------------------------

    std::ostrstream buffer;
    CHA_UserInfo userInfo;


    buffer << "----------------------------------------" << "\n";


    if (showEsName) {

	if (srcSyst.length() > 0)
	    buffer << "ES name:        " << srcSyst << "\n";
	else
	    buffer << "ES name:        " << "unknown" << "\n";
    }

    if (showTime) {

            buffer << "Time:           " << time.asString("%m/%d/%Y %H:%M:%S") << "\n";
    }

    if (showUser) {

	    buffer << "User:           " << userInfo.loginName() << "\n";
    }

    if (showCommand) {

	if (command.length() > 0)
	    buffer << "Command:        " << command << "\n";
	else
	    buffer << "Command:        " << "unknown" << "\n";
    }

    if (showDevId) {

	if (deviceId > 0)
            buffer << "Device ID:      " << deviceId << "\n";
	else
	    buffer << "Device ID:      " << "unknown" << "\n";
    }


    buffer << "----------------------------------------" << "\n" << std::ends;

    TRACE_FLOW(trace, CHA_DelRespBuffer,  buffer.str());

    char* bufferStr = buffer.str();
    RWCString hdr(bufferStr);
    delete [] bufferStr;

    TRACE_OUT(trace, CHA_DelRespBuffer,  "");

    return hdr;
}


//**********************************************************************


RWCString CHA_DelRespBuffer::getOneLineHeader() const
{
    // ***   Time: Thu Mar  3 10:03:23 1994   Command: LABUP;   ES name: AXE19
    // User: tmosadm   Device ID: 1234   ***

    std::ostrstream buffer;
    CHA_UserInfo userInfo;

    buffer << "\n***" << flush;


    if (showTime) {

	    buffer << "   Time: " << time.asString("%m/%d/%Y %H:%M:%S") << flush;
    }

    if (showCommand) {

	if (command.length() > 0)
	    buffer << "   Cmd: " << command << flush;
	else
	    buffer << "   Cmd: " << "unknown" << flush;
    }

    if (showEsName) {

	if (srcSyst.length() > 0)
	    buffer << "   ES: " << srcSyst << flush;
	else
	    buffer << "   ES: " << "unknown" << flush;
    }

    if (showUser) {

            buffer << "   Usr: " << userInfo.loginName() << flush;
    }

    if (showDevId) {

	if (deviceId > 0)
            buffer << "   DevID: " << deviceId << flush;
	else
	    buffer << "   DevID: " << "unknown" << flush;
    }


    buffer << "   ***/n" << "\n" << std::ends;

    char* bufferStr = buffer.str();
    RWCString hdr(bufferStr);
    delete [] bufferStr;

    return hdr;
}


//**********************************************************************


void CHA_DelRespBuffer::setLayout(RWBoolean t,
				  RWBoolean cmd,
				  RWBoolean es,
				  RWBoolean usr,
				  RWBoolean devId)
{
    showTime 	= t;
    showCommand = cmd;
    showEsName	= es;
    showUser	= usr;
    showDevId	= devId;
}


//**********************************************************************

CHA_ResponseBuffer* CHA_DelRespBuffer::copy() const
{
return new CHA_DelRespBuffer(*this);
}


//**********************************************************************

