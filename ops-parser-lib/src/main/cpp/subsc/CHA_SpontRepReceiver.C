// RCS handling
// $Id: CHA_SpontRepReceiver.C,v 22.0.1.1 1995/09/10 21:39:42 etosad Exp $

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
//      $Log: CHA_SpontRepReceiver.C,v $
//      Revision 22.0.1.1  1995/09/10 21:39:42  etosad
//      A lot of changes!
//
//      Revision 23.0  1995/09/07  17:50:15  ehscama
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:50:54  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.1  95/07/03  11:00:04  11:00:04  ehsgrap (Jan Grape (9 9073) VK/EHS/PXE)
//      Removed some trace that was no good in a polling event loop
//      
//      Revision 21.0  1995/06/29  09:48:33  cmcha
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:39:40  08:39:40  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:59:02  10:59:02  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:11:41  20:11:41  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:13:58  14:13:58  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:05:58  13:05:58  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:13:21  15:13:21  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:39:23  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:13:01  14:13:01  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:23:48  16:23:48  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:55:12  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.1  1995/01/10  16:08:50  xkknicl
//      added applicationName when creating a CHA_SpontRepBuffer
//
//      Revision 10.0  1994/12/22  09:09:10  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:35:54  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:57:19  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:28:59  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:55:56  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:54:47  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:46:20  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  08:01:15  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:02:23  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.3  1994/05/26  14:28:55  ehsgrap
//      getResponseBuffer() returns retCode
//
//      Revision 1.2  1994/05/18  09:08:36  xkknicl
//      Basic tested version
//
//      Revision 1.1  1994/05/16  14:40:31  xkknicl
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


#include <CHA_Trace.H>
#include <CHA_LibGlobals.H>
#include <CHA_LibNLS.H>
#include <CHA_SpontRepReceiver.H>
#include <CHA_SpontRepBuffer.H>

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_SpontRepReceiver", (char*)"C");

//**********************************************************************


CHA_SpontRepReceiver::CHA_SpontRepReceiver(CHA_IPCSupervisor* pSup,
					   const RWCString& appN)
:CHA_SpDelReceiver(pSup, appN),
 //spontReport(),
 applicationName(appN)
{
    // empty
}


//**********************************************************************


CHA_SpontRepReceiver::~CHA_SpontRepReceiver()
{
    // empty
}


//**********************************************************************

int CHA_SpontRepReceiver::receiveResponse()
{
   // return association.Receive_sp_rep(&spontReport,0);
}
   

//**********************************************************************


CHA_ResponseBuffer* CHA_SpontRepReceiver::createBuffer(
                                                    const char* bufferString,
                                                    const char* theCommand,
						    const char* theEsName)
{
    long int reportId;
    
    // The report ID should be fetched from EAC via the method
    // Get_int_criteria, this is however not working today.
    // This error in EAC will be corrected in the future.
    // In this class report ID is set to 0 for now.
    
    //reportId = spontReport.Get_int_criteria();
    reportId = 0;
    return new CHA_SpontRepBuffer(bufferString,theCommand,theEsName,reportId,applicationName);
}


//**********************************************************************


CHA_ResponseBuffer* CHA_SpontRepReceiver::createBuffer(
                                                    const char* bufferString,
                                                    const char* theCommand,
						    const char* theEsName,
							  int   devId)
{

    long int reportId;
    
    // The report ID should be fetched from EAC via the method
    // Get_int_criteria, this is however not working today.
    // This error in EAC will be corrected in the future.
    // In this class report ID is set to 0 for now.
    
    // is report ID and device ID the same?
    //reportId = spontReport.Get_int_criteria();
    reportId = 0;


    // A constructor for the buffer also taking devId as an argument 
    // should be called here.
    ////////////////////////////////////////////////////////////////
    return new
CHA_SpontRepBuffer(bufferString,theCommand,theEsName,reportId,applicationName);
}


//**********************************************************************

CHA_ResponseBuffer* CHA_SpontRepReceiver::createAccumulatedBuffer()
{
    long int reportId;
    
    // The report ID should be fetched from EAC via the method
    // Get_int_criteria, this is however not working today.
    // This error in EAC will be corrected in the future.
    // In this class report ID is set to 0 for now.
    
    //reportId = spontReport.Get_int_criteria();
    reportId = 0;
    return new CHA_SpontRepBuffer(*buffer,reportId);
}


//**********************************************************************


int CHA_SpontRepReceiver::getResponseBuffer(RWCString& bufferStr)
{
    int retCode;
    const char* respStr;
    
   /* while((retCode=spontReport.Get_buffer(respStr,0)) >0)
    {
	bufferStr += respStr;
    }
    //TRACE_FLOW(trace,getResponseBuffer,bufferStr);
    return retCode;*/
}


//**********************************************************************

int CHA_SpontRepReceiver::completeResponse()
{
    //return spontReport.Is_response_complete();
}

//**********************************************************************

int CHA_SpontRepReceiver::interruptResponse()
{
   // return spontReport.Interrupt_response();
}

//**********************************************************************
