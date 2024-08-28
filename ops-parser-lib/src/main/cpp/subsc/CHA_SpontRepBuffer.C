// RCS handling
// $Id: CHA_SpontRepBuffer.C,v 22.0.1.4 1996/07/16 16:04:04 emejome Exp $

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
//      1994-05-10 by EHS/PXE Nicolas Länninge (xkknicl@ehs.ericsson.se)

// REVISION
//	XM2S1
//	1995-09-07

// CHANGES
//      RCS revision history
//      $Log: CHA_SpontRepBuffer.C,v $
//      Revision 22.0.1.4  1996/07/16 16:04:04  emejome
//      Added Trace points.
//
//      Revision 22.0.1.3  1996/01/03 17:11:28  qhsalte
//      Added "ends" in the end of ostrstream variables
//
//      Revision 22.0.1.2  1995/12/21  17:03:54  ehsphad
//      Added copy method.
//
//      Revision 22.0.1.1  1995/09/10 21:39:18  etosad
//      A lot of changes!
//
//      Revision 23.0  1995/09/07  17:50:12  ehscama
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:50:53  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:48:30  09:48:30  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:39:38  08:39:38  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:59:00  10:59:00  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:11:39  20:11:39  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:13:53  14:13:53  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  13:05:55  13:05:55  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  15:13:15  15:13:15  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:39:21  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:12:58  14:12:58  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 12.0  95/02/06  16:23:45  16:23:45  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:55:07  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.1  1995/01/10  16:13:41  xkknicl
//      reading login name from CHA_UserInfo now
//
//      Revision 10.0  1994/12/22  09:09:08  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:35:51  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:57:15  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:28:54  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:55:53  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:54:39  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:46:15  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  08:01:11  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:02:20  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.2  1994/05/18  09:09:37  xkknicl
//      Basic tested version
//
//      Revision 1.1  1994/05/16  15:05:25  xkknicl
//      Initial Version
//
//
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	XM2S1   1995-09-07      ehscama                 RCS rev 23.0
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


#include <CHA_SpontRepBuffer.H>

#include <strstream>
#include <stdlib.h>

#include <CHA_Trace.H>

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_SpontRepBuffer", (char*)"C");


//**********************************************************************


CHA_SpontRepBuffer::CHA_SpontRepBuffer(const RWCString& respBuf,
				     const RWCString& cmd,
				     const RWCString& syst,
				     const long int reportId,
                                     const RWCString& appN)
: CHA_ResponseBuffer(respBuf, cmd, syst),
  userInfo(),
  reportIden(reportId),
  applicationName(appN)
{
    type =  CHA_RT_SPONTANEOUS;
}


//**********************************************************************


CHA_SpontRepBuffer::CHA_SpontRepBuffer(const CHA_ResponseBuffer& other,
				       const long int reportId)
: CHA_ResponseBuffer(other),
  reportIden(reportId)
{
    type =  CHA_RT_SPONTANEOUS;
}


//**********************************************************************


RWCString CHA_SpontRepBuffer::getHeader() const
{
    //TRACE_IN(trace, CHA_SpontRepBuffer, "");

    // ----------------------------------------
    // ES name:        AXE19
    // Report id:      1
    // Time:           Thu Mar  3 10:03:23 1994
    // User:           tmosadm
    // Application:    CHA
    // ----------------------------------------

    std::ostrstream buffer;

  buffer << "----------------------------------------" << std::endl;

    if(srcSyst.length() > 0)
	buffer << "ES name:        " << srcSyst << std::endl;

    buffer << "Report id:      " << reportIden << std::endl;

    buffer << "Time:           " << time.asString("%m/%d/%Y %H:%M:%S") << std::endl
	   << "User:           " << userInfo.loginName() << std::endl;
    buffer << "Application:    " << applicationName << std::endl;

    if(command.length() > 0)
	buffer << "Command:        " << command << std::endl;

    buffer << "----------------------------------------" << std::endl << std::ends;

    //TRACE_FLOW(trace, CHA_SpontRepBuffer, buffer);

    char* bufferStr = buffer.str();
    RWCString hdr(bufferStr);
    delete [] bufferStr;

    //TRACE_OUT(trace, CHA_SpontRepBuffer, "");

    return hdr;
}


//**********************************************************************

CHA_ResponseBuffer* CHA_SpontRepBuffer::copy() const
{
return new CHA_SpontRepBuffer(*this);
}

//**********************************************************************


RWCString CHA_SpontRepBuffer::getOneLineHeader() const
{
    // Should be implemented as in CHA_ImmRespBuffer.C and
    // CHA_DelRespBufer.C
    return RWCString();
}


