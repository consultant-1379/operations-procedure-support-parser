/*------------------------------------------------------------------------------
 ********************************************************************************
 * COPYRIGHT Ericsson 2018
 *
 * The copyright to the computer program(s) herein is the property of
 * Ericsson Inc. The programs may be used and/or copied only with written
 * permission from Ericsson Inc. or in accordance with the terms and
 * conditions stipulated in the agreement/contract under which the
 * program(s) have been supplied.
 ********************************************************************************
 *----------------------------------------------------------------------------*/


#include <CHA_LibGlobals.H>
//#include <CHA_Trace.H>
#include <CHA_ResponseBuffer.H>

#include <trace.H>
static std::string trace ="CHA_ResponseBuffer";


//**********************************************************************


CHA_ResponseBuffer::CHA_ResponseBuffer(const RWCString& respBuf,
				       const RWCString& cmd,
				       const RWCString& syst,
				       const RWDateTime& 	t,
					     int	devId)
: response(respBuf),
  command(cmd),
  srcSyst(syst),
  time(t),
  deviceId(devId),
  type(CHA_RT_UNDEFINED),
  cmdFileType(FALSE)
{
    TRACE_IN(trace, CHA_ResponseBuffer,
           respBuf << ", " << cmd << ", " << syst << ", " << t <<", " << devId);
         
    TRACE_OUT (trace, CHA_ResponseBuffer, "");
}


//**********************************************************************


CHA_ResponseBuffer::CHA_ResponseBuffer(const RWCString& respBuf,
				       const RWCString& cmd,
				       const RWCString& syst,
					     int	devId)
: response(respBuf),
  command(cmd),
  srcSyst(syst),
  time(),
  deviceId(devId),
  type(CHA_RT_UNDEFINED),
  cmdFileType(FALSE)
{
    TRACE_IN(trace, CHA_ResponseBuffer,
           respBuf << ", " << cmd << ", " << syst << ", " << devId);

    TRACE_OUT (trace, CHA_ResponseBuffer, "");
}


//**********************************************************************


CHA_ResponseBuffer::CHA_ResponseBuffer(const RWCString& respBuf,
				       const RWCString& cmd,
				       const RWCString& syst,
				       const RWDateTime& 	t)
: response(respBuf),
  command(cmd),
  srcSyst(syst),
  time(t),
  deviceId(-1),
  type(CHA_RT_UNDEFINED),
  cmdFileType(FALSE)
{
    TRACE_IN(trace, CHA_ResponseBuffer,
  	     respBuf << ", " << cmd << ", " << syst << ", " << t);
	     
    TRACE_OUT (trace, CHA_ResponseBuffer, "");
}

//**********************************************************************


CHA_ResponseBuffer::CHA_ResponseBuffer(const RWCString& respBuf,
				       const RWCString& cmd,
				       const RWCString& syst)
: response(respBuf),
  command(cmd),
  srcSyst(syst),
  time(),
  deviceId(-1),
  type(CHA_RT_UNDEFINED),
  cmdFileType(FALSE)
{
    TRACE_IN(trace, CHA_ResponseBuffer,
  	     respBuf << ", " << cmd << ", " << syst);

    TRACE_OUT (trace, CHA_ResponseBuffer, "");
}


//**********************************************************************

CHA_ResponseBuffer::CHA_ResponseBuffer(      RWBoolean  cmdFileResp,
				       const RWCString& respBuf,
				       const RWCString& cmd,
				       const RWCString& syst )
: response(respBuf),
  command(cmd),
  srcSyst(syst),
  time(),
  deviceId(-1),
  type(CHA_RT_UNDEFINED),
  cmdFileType(cmdFileResp)
{
    TRACE_IN(trace, CHA_ResponseBuffer,
  	     respBuf << ", " << cmd << ", " << syst << "," << cmdFileResp );

    TRACE_OUT (trace, CHA_ResponseBuffer, "");
}


//**********************************************************************


CHA_ResponseBuffer::CHA_ResponseBuffer(const RWCString& respBuf)
: response(respBuf),
  command(""),
  srcSyst(""),
  time(),
  deviceId(-1),
  type(CHA_RT_UNDEFINED),
  cmdFileType(FALSE)
{
    TRACE_IN(trace, CHA_ResponseBuffer, respBuf);
    
    TRACE_OUT (trace, CHA_ResponseBuffer, "");
}


//**********************************************************************


CHA_ResponseBuffer::CHA_ResponseBuffer(const CHA_ResponseBuffer& other)
: response(other.response),
  srcSyst(other.srcSyst),
  command(other.command),
  type(other.type),
  time(other.time),
  deviceId(other.deviceId),
  cmdFileType(other.cmdFileType)
{
    TRACE_IN(trace, CHA_ResponseBuffer, "CHA_ResponseBuffer& other");

    TRACE_OUT (trace, CHA_ResponseBuffer, "");
}


//**********************************************************************


CHA_ResponseBuffer::~CHA_ResponseBuffer()
{
}


//**********************************************************************


CHA_ResponseBuffer& CHA_ResponseBuffer::operator=(const CHA_ResponseBuffer& other)
{
    TRACE_IN(trace, operator=, "CHA_ResponseBuffer& other");
    response = other.response;
    srcSyst = other.srcSyst;
    command = other.command;
    type = other.type;
    time = other.time;
    deviceId = other.deviceId;
    cmdFileType = other.cmdFileType;

    return *this;
}

//**********************************************************************


RWBoolean CHA_ResponseBuffer::operator==(const CHA_ResponseBuffer& other)
{
  TRACE_RETURN(trace, operator==, "CHA_ResponseBuffer& other");

    return ((response == other.response) &&
	    (srcSyst == other.srcSyst) &&
	    (command == other.command) &&
	    (type == other.type) &&
	    (time == other.time) &&
	    (deviceId == other.deviceId) &&
            (cmdFileType == other.cmdFileType));
}

//**********************************************************************


RWCString CHA_ResponseBuffer::getText() const
{
    TRACE_RETURN(trace, getText, response);

    return response;
}


//**********************************************************************


RWCString CHA_ResponseBuffer::getHeader() const
{
    TRACE_RETURN(trace, getHeader, "");

    return RWCString("");
}


//**********************************************************************


RWCString CHA_ResponseBuffer::getOneLineHeader() const
{
    return RWCString("");
}


//**********************************************************************


RWCString CHA_ResponseBuffer::getCommand() const
{
    TRACE_RETURN(trace, getCommand, command);
    return command;
}


//**********************************************************************


RWCString CHA_ResponseBuffer::getSrcSystem() const
{
    TRACE_RETURN(trace, getSrcSystem, srcSyst);
    return srcSyst;
}


//**********************************************************************


RWDateTime CHA_ResponseBuffer::getTime() const
{
    TRACE_RETURN(trace, getTime, time);
    return time;
}


//**********************************************************************


int CHA_ResponseBuffer::getDeviceId() const
{
  TRACE_RETURN(trace, getDeviceId, deviceId);
  return deviceId;
}


//**********************************************************************


CHA_ResponseType CHA_ResponseBuffer::getRespType() const
{
    TRACE_RETURN(trace, getType, type);
    return type;
}

//**********************************************************************


RWBoolean CHA_ResponseBuffer::isCmdFileType() const
{
    TRACE_RETURN(trace, isCmdFileType, cmdFileType);
    return cmdFileType;
}


//**********************************************************************

void CHA_ResponseBuffer::append(const RWCString& resp)
{
    response += resp;
}


//**********************************************************************


void CHA_ResponseBuffer::append(const CHA_ResponseBuffer& other)
{
    response += other.response;
}


//**********************************************************************
