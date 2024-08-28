// RCS handling
// $Id: CHA_DelRespReceiver.C,v 22.0.1.1 1995/09/10 21:26:46 etosad Exp $

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
//      1994-04-08 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// REVISION
//	XM2S1
//	1995-09-07

// CHANGES
//      RCS revision history
//      $Log: CHA_DelRespReceiver.C,v $
//      Revision 22.0.1.1  1995/09/10 21:26:46  etosad
//      A lot of changes!
//
//      Revision 23.0  1995/09/07  17:38:55  ehscama
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:42:22  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.1  95/07/03  10:58:37  10:58:37  ehsgrap (Jan Grape (9 9073) VK/EHS/PXE)
//      Removed some trace that was no good in a polling event loop
//
//      Revision 21.0  1995/06/29  09:37:45  cmcha
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:30:42  08:30:42  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:50:05  10:50:05  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:02:19  20:02:19  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:00:37  14:00:37  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  12:55:32  12:55:32  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  14:56:34  14:56:34  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:30:19  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  13:59:20  13:59:20  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 12.0  95/02/06  16:09:53  16:09:53  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:42:13  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  08:59:32  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:25:38  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:45:17  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:19:51  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:47:44  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:40:33  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:33:31  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:47:06  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  07:57:38  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.8  1994/06/10  16:52:57  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.7  1994/05/26  14:31:01  ehsgrap
//      getResponseBuffer() returns retCode
//
//      Revision 1.6  1994/05/18  09:10:32  xkknicl
//      Basic tested version
//
//      Revision 1.5  1994/05/16  14:43:55  xkknicl
//      Methods has been moved to a baseclass CHA_SpDelReceiver
//
//      Revision 1.4  1994/05/11  11:12:21  xkknicl
//      *** empty log message ***
//
//      Revision 1.3  1994/05/06  15:39:04  ehsgrap
//      Removed "apa" and "kaka" as parameters to new resp buffer.
//
//      Revision 1.2  1994/04/22  13:34:28  ehsgrap
//      Created local trace block.
//
//       Revision 1.1  1994/04/12  16:19:23  ehsgrap
//      Initial revision.
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


#include <CHA_Trace.H>
#include <CHA_LibGlobals.H>
#include <CHA_LibNLS.H>
#include <CHA_DelRespReceiver.H>
#include <CHA_DelRespBuffer.H>

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_DelRespReceiver", (char*)"C");

//**********************************************************************

CHA_DelRespReceiver::CHA_DelRespReceiver(CHA_IPCSupervisor* pSup,
					 const RWCString& appN)
:CHA_SpDelReceiver(pSup, appN)/*,
 delResponse()*/
{
    // empty
}


//**********************************************************************


CHA_DelRespReceiver::~CHA_DelRespReceiver()
{
    // empty
}

//**********************************************************************

int CHA_DelRespReceiver::receiveResponse()
{
    //return association.Receive_delayed_resp(&delResponse,&command);
}


//**********************************************************************


CHA_ResponseBuffer* CHA_DelRespReceiver::createBuffer(
                                                    const char* bufferString,
                                                    const char* theCommand,
						    const char* theEsName,
							  int   devId)
{
    return new CHA_DelRespBuffer(RWCString(bufferString),RWCString(theCommand),RWCString(theEsName),devId);
}


//**********************************************************************


CHA_ResponseBuffer* CHA_DelRespReceiver::createBuffer(
                                                    const char* bufferString,
                                                    const char* theCommand,
						    const char* theEsName)
{
    return new CHA_DelRespBuffer(bufferString,theCommand,theEsName);
}


//**********************************************************************

CHA_ResponseBuffer* CHA_DelRespReceiver::createAccumulatedBuffer()
{
    return new CHA_DelRespBuffer(*buffer);
}


//**********************************************************************


int CHA_DelRespReceiver::getResponseBuffer(RWCString& bufferStr)
{
    int retCode;
    const char* respStr;

   /* while((retCode = delResponse.Get_buffer(respStr,0)) > 0)
    {
	bufferStr += respStr;
    }
    //TRACE_FLOW(trace, getResponseBuffer, bufferStr);
    return retCode;*/
}


//**********************************************************************

int CHA_DelRespReceiver::completeResponse()
{
   // return delResponse.Is_response_complete();
}

//**********************************************************************

int CHA_DelRespReceiver::interruptResponse()
{
   // return delResponse.Interrupt_response();
}

//**********************************************************************
