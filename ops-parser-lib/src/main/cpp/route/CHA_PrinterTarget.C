// RCS handling
// $Id: CHA_PrinterTarget.C,v 24.0 1995/11/28 16:58:14 ehsgrap Rel $

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
//	190 89-CAA 134 1519

// AUTHOR
//      1994-05-03 by EHS/PXE Nicolas Lännnige (xkknicl@ehs.ericsson.se)

// REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_PrinterTarget.C,v $
//      Revision 24.0  1995/11/28 16:58:14  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//     Revision 23.2  95/10/16  12:49:45  12:49:45  ehsgrap (Jan Grape (9 9073) VK/EHS/VE)
//     Changed enum items in CHA_Pipe back to old
//     names to reduce porting.
//
//      Revision 23.1  1995/10/12 15:23:50  ehsgrap
//      Added wait method on CHA_Pipe class to wait for child
//      termination. Also redesigned status method in the same
//      class.
//
//      Revision 23.0  1995/09/07 17:46:06  ehscama
//      Made release XM2S1, ehscama.
//
//     Revision 22.1  1995/08/15  10:44:41  qhsjody
//     Changed some ifdef's.
//
//     Revision 22.0  1995/08/01  20:47:40  cmcha
//     Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//     Revision 21.0  95/06/29  09:44:46  09:44:46  cmcha (*CHA conf. and dev. EHS/PXE)
//     Made release EC1_OZ, J Grape (EHSGRAP).
//
//     Revision 20.0  95/06/08  08:36:18  08:36:18  cmcha (*CHA conf. and dev. EHS/PXE)
//     Made release TB5_2_OZ, J Grape (ehsgrap).
//
//     Revision 19.0  95/04/13  10:55:38  10:55:38  cmcha (*CHA conf. and dev. EHS/PXE)
//     Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//     Revision 18.0  95/03/17  20:08:08  20:08:08  cmcha (*CHA conf. and dev. EHS/PXE)
//     Made release TB51_OZ, ehscama.
//
//     Revision 17.0  95/03/16  14:09:07  14:09:07  cmcha (*CHA conf. and dev. EHS/PXE)
//     Made release TB5_OZ, ehscama.
//
//     Revision 16.0  95/03/10  13:02:23  13:02:23  cmcha (*CHA conf. and dev. EHS/PXE)
//     Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//     Revision 15.0  95/03/09  15:06:43  15:06:43  cmcha (*CHA conf. and dev. EHS/PXE)
//     Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//     Revision 14.0  1995/02/25  16:36:19  cmcha
//     Made release TB4_OZ, J Grape (EHSGRAP).
//
//     Revision 13.5  95/02/15  14:08:07  14:08:07  cmcha (*CHA conf. and dev. EHS/PXE)
//     Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//     Revision 12.0  95/02/06  16:19:28  16:19:28  cmcha (*CHA conf. and dev. EHS/PXE)
//     Made release TB3, J Grape (EHSGRAP).
//
//     Revision 11.0  1995/01/18  14:50:57  cmcha
//     Made release PREIT, N Länninge (XKKNICL).
//
//     Revision 10.0  1994/12/22  09:05:45  cmcha
//     Made release TB2, J Grape (EHSGRAP).
//
//     Revision 9.1  1994/12/08  10:27:57  ehsgrap
//     Replaced OK with OKAY
//
//     Revision 9.0  1994/10/24  21:32:15  cmcha
//     Made release E, ehscama.
//
//     Revision 8.0  1994/10/05  08:52:20  cmcha
//     Made release D, EHSCAMA.
//
//     Revision 7.0  1994/09/22  13:25:03  cmcha
//     Made release R1C, J Grape (EHSGRAP).
//
//     Revision 6.0  1994/08/30  17:52:20  cmcha
//     Made release R1B, J Grape (EHSGRAP).
//
//     Revision 5.0  1994/08/16  07:48:50  cmcha
//     Made release R1A, J Grape (EHSGRAP).
//
//     Revision 4.0  1994/07/18  13:41:06  cmcha
//     Made release P1C, J Grape (EHSGRAP).
//
//     Revision 3.0  1994/06/23  07:57:26  cmcha
//     Made release P1B, J Grape (EHSGRAP).
//
//     Revision 2.1  1994/06/21  13:00:32  ehsgrap
//     Use of CHA_Pipe class instead of popen()
//
//     Revision 2.0  1994/06/12  07:59:49  cmcha
//     Made release P1A, J Grape (EHSGRAP).
//
//     Revision 1.3  1994/06/10  16:55:53  ehsgrap
//     Fixed doc. nr, creation date, header information and
//     changed #include "..." to #include <...> for a great
//     number of files.
//
//     Revision 1.2  1994/05/04  14:29:37  xkknicl
//     Initial version
//
//     Revision 1.1  1994/05/04  14:13:22  xkknicl
//     Initial version
//
//
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	TB53_OZ 1995-11-28      J Grape (EHSGRAP)       RCS rev 24.0
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


#include <CHA_PrinterTarget.H>
#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_LibNLS.H>

#include <rw/cstring.h>
#include <stdio.h>


//**********************************************************************


//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_PrinterTarget", (char*)"C");


//**********************************************************************



CHA_PrinterTarget::CHA_PrinterTarget(const RWCString& printer)
: printerName(printer),
  nlsCat(CHA_LibNLSCatalog)
{
   // //TRACE_IN(trace, CHA_PrinterTarget, printer);
}


//**********************************************************************


CHA_PrinterTarget::~CHA_PrinterTarget()
{
}


//**********************************************************************


void CHA_PrinterTarget::doRouting(const CHA_ResponseBuffer* pResponse)
{
    RWCString command;

 if (!(pResponse->isCmdFileType()))
 {

#if defined __hpux || defined SunOS5
    //This fix for TMOS/HP is recorded in PRIMA as HPUX.35
    command = "lp -sd " + printerName;
    //TRACE_FLOW(trace, doRouting, command);
#elif defined sun
    command = "lpr -P " + printerName;
    //TRACE_FLOW(trace, doRouting, command);
#endif


    // start the printer program and get a pipe connected to it
    CHA_Pipe printerProg(command);

    // return if pipe not ok
    if(printerProg.status() != CHA_Pipe::OKAY)
    {
	errorReporter.message(nlsCat.getMessage(NLS_PTARGET_FAILED)
			      + printerName + ".");
	return;
    }

    // print the buffer to the pipe
    printerProg.send() << pResponse->getHeader() << std::endl
		       << pResponse->getText() << std::endl;

    // close the pipe and we are done
    printerProg.closeSending();
    printerProg.waitForChild();
  }
}


//**********************************************************************
