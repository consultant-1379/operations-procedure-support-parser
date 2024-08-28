// RCS handling
// $Id: CHA_ImmRespBuffer.C,v 22.0.1.7 1996/07/16 16:06:03 emejome Exp $

//**********************************************************************

// COPYRIGHT
//      COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1994
//
//      The Copyright to the computer program(s) herein is the
//      property of Ericsson Hewlett-Packard Telecommunications AB,
//      Sweden.  The program(s) may be used and/or copied with the
//      written permission from Ericsson Hewlett-Packard
//      Telecommunications AB or in accordance with the terms and
//      conditions stipulated in the agreement/contract under which
//      the program(s) have been supplied.

// DOCUMENT NO
//	190 89-CAA 134 1517

// AUTHOR
//      1994-03-03 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// REVISION
//	EC2_OZ
//	1995-08-01

// CHANGES
//      RCS revision history
//      $Log: CHA_ImmRespBuffer.C,v $
//      Revision 22.0.1.7  1996/07/16 16:06:03  emejome
//      Added Trace points.
//      pwd
//
//      Revision 22.0.1.6  1996/06/20 08:37:28  emermge
//      Changed "endl;" by "\n;".
//
//      Revision 22.0.1.5  1996/01/03 17:12:55  qhsalte
//      Added "ends" in the end of ostrstream variables
//
//      Revision 22.0.1.4  1995/12/21  14:37:49  ehsphad
//      Added copy method.
//
//      Revision 22.0.1.3  1995/10/04 18:18:56  qhsalte
//      Code correction. Multiple defined hdr
//
//      Revision 22.0.1.2  1995/09/10  21:29:33  etosad
//      A lot of changes!
//
//      Revision 22.0.1.1  1995/09/07  06:41:28  etosad
//      One line header added.
//
//      Revision 22.0  1995/08/01  20:42:31  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:37:53  09:37:53  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:30:51  08:30:51  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:50:14  10:50:14  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:02:27  20:02:27  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:00:46  14:00:46  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  12:56:18  12:56:18  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  14:56:52  14:56:52  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:30:34  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  13:59:33  13:59:33  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 12.0  95/02/06  16:10:22  16:10:22  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:42:28  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.1  1995/01/05  08:16:51  ehsgrap
//      Use of CHA_UserInfo class instead of getpwuid(getuid))
//
//      Revision 10.0  1994/12/22  08:59:47  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:26:12  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:45:34  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:20:05  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:47:56  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:40:56  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:33:52  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:47:29  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  07:57:53  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.3  1994/06/10  16:54:28  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.2  1994/05/31  08:25:07  ehsgrap
//      Added true copy constructor.
//
//      Revision 1.1  1994/03/31  13:36:00  ehsgrap
//      Initial revision
//
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	EC2_OZ  1995-08-01      Jan Sandquist (EHSJAASA)RCS rev 22.0
//	EC1_OZ  1995-06-29      J Grape (EHSGRAP)       RCS rev 21.0
//	TB5_2_OZ1995-06-08      J Grape (ehsgrap)       RCS rev 20.0
//	TB5_1_OZ1995-04-13      J Grape (EHSGRAP)       RCS rev 19.0
//	TB51_OZ 1995-03-17      ehscama                 RCS rev 18.0
//	TB5_OZ  1995-03-16      ehscama                 RCS rev 17.0
//	TB6_B1C_B1995-03-10      N.Lanninge (XKKNICL)    RCS rev 16.0
//	TB6_B1C 1995-03-09      N.Lanninge (XKKNICL)    RCS rev 15.0
//	TB4_OZ  1995-02-25      J Grape (EHSGRAP)       RCS rev 14.0
//	CHUI_TB61995-02-15      N.Lanninge (XKKNICL)    RCS rev 13.5
//	TB3     1995-02-06      J Grape (EHSGRAP)       RCS rev 12.0
//	PREIT   1995-01-18      N Länninge (XKKNICL)    RCS rev 11.0
//	TB2     1994-12-22      J Grape (EHSGRAP)       RCS rev 10.0
//	E       1994-10-24      ehscama                 RCS rev 9.0
//	D       1994-10-05      EHSCAMA                 RCS rev 8.0
//	R1C     1994-09-22      J Grape (EHSGRAP)       RCS rev 7.0
//	R1B     1994-08-30      J Grape (EHSGRAP)       RCS rev 6.0
//	R1A     1994-08-16      J Grape (EHSGRAP)       RCS rev 5.0
//	P1C     1994-07-18      J Grape (EHSGRAP)       RCS rev 4.0
//	P1B     1994-06-23      J Grape (EHSGRAP)       RCS rev 3.0
//	P1A     1994-06-12      J Grape (EHSGRAP)       RCS rev 2.0

//**********************************************************************


#include <CHA_ImmRespBuffer.H>
#include <CHA_UserInfo.H>

#include <strstream>
#include <CHA_Trace.H>


//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_ImmRespBuffer", (char*)"C");


//**********************************************************************


CHA_ImmRespBuffer::CHA_ImmRespBuffer(const RWCString& respBuf,
				     const RWCString& cmd,
				     const RWCString& syst,
				     const RWDateTime& 	t,
					   int	      devId)
: CHA_ResponseBuffer(respBuf, cmd, syst, t, devId),
  showTime(TRUE),
  showCommand(TRUE),
  showEsName(TRUE),
  showUser(TRUE),
  showDevId(TRUE)
{
    type = CHA_RT_IMMEDIATE;
}


//**********************************************************************


CHA_ImmRespBuffer::CHA_ImmRespBuffer(const RWCString& respBuf,
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
    type = CHA_RT_IMMEDIATE;
}


//**********************************************************************


CHA_ImmRespBuffer::CHA_ImmRespBuffer(const RWCString& respBuf,
				     const RWCString& cmd,
				     const RWCString& syst)
: CHA_ResponseBuffer(respBuf, cmd, syst),
  showTime(TRUE),
  showCommand(TRUE),
  showEsName(TRUE),
  showUser(TRUE),
  showDevId(FALSE)
{
    type = CHA_RT_IMMEDIATE;
}


//**********************************************************************


CHA_ImmRespBuffer::CHA_ImmRespBuffer(      RWBoolean  cmdFileResp,
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
    type = CHA_RT_IMMEDIATE;
}



//**********************************************************************

CHA_ImmRespBuffer::CHA_ImmRespBuffer(const CHA_ResponseBuffer& other)
: CHA_ResponseBuffer(other)
{
    type = CHA_RT_IMMEDIATE;
}


//**********************************************************************


CHA_ImmRespBuffer::CHA_ImmRespBuffer(const CHA_ImmRespBuffer& other)
: CHA_ResponseBuffer(other)
{
    type = CHA_RT_IMMEDIATE;
}


//**********************************************************************


RWCString CHA_ImmRespBuffer::getHeader() const
{
    //TRACE_IN(trace, CHA_ImmRespBuffer, "");

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

    //TRACE_FLOW(trace, CHA_ImmRespBuffer, buffer);

    char* bufferStr = buffer.str();
    RWCString hdr(bufferStr);
    delete [] bufferStr;

    //TRACE_OUT(trace, CHA_ImmRespBuffer, "");

    return hdr;
}


//**********************************************************************


RWCString CHA_ImmRespBuffer::getOneLineHeader() const
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


void CHA_ImmRespBuffer::setLayout(RWBoolean t,
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

CHA_ResponseBuffer* CHA_ImmRespBuffer::copy() const
{
return new CHA_ImmRespBuffer(*this);
}


//**********************************************************************
