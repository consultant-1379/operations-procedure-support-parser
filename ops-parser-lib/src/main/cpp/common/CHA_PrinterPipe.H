// RCS handling
// $Id: CHA_PrinterPipe.H,v 24.0 1995/11/28 16:55:03 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_PrinterPipe - class for sending data to a printer.
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_PrinterPipe.H

// .COPYRIGHT
//      COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1994
//
//      The Copyright to the computer program(s) herein is the
//      property of Ericsson Hewlett-Packard Telecommunications AB,
//      Sweden.  The program(s) may be used and/or copied with the
//      written permission from Ericsson Hewlett-Packard
//      Telecommunications AB or in accordance with the terms and
//      conditions stipulated in the agreement/contract under which
//      the program(s) have been supplied.

// .DESCRIPTION 
//      CHA_PrinterPipe is a class for sending data to a printer in a
//      controlled way. It is possible to create a pipe to a special
//	printer or to the user's default printer. The method send 
//	provides a way to send data to the printer in the same way as
//	to a stream.

// .SECTION ERROR HANDLING
//      Error handling is done using the status method.

// DOCUMENT NO
//      190 89-CAA 134 1515

// AUTHOR 
//      1995-01-18 by EHS/PXE Johan Dykström (qhsjody@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_PrinterPipe.H,v $
//      Revision 24.0  1995/11/28 16:55:03  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:41:15  17:41:15  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:43:56  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:39:47  09:39:47  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:32:34  08:32:34  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:51:53  10:51:53  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.1  95/04/10  12:44:49  12:44:49  ehsgrap (Jan Grape (9 9073) VK/EHS/PXE)
//      Changed OKEY to OKAY.
//      
//      Revision 18.0  1995/03/17  20:04:09  cmcha
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:02:36  14:02:36  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  12:58:02  12:58:02  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  14:59:58  14:59:58  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:32:57  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:02:23  14:02:23  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:13:16  16:13:16  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.1  1995/01/18  16:04:00  qhsjody
//      CHA_PrinterList.H is now included in header file.
//
//      Revision 11.0  1995/01/18  14:44:56  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 1.1  1995/01/18  12:35:38  qhsjody
//      Initial revision
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

// .SEE ALSO 
//      CHA_PrinterList

//**********************************************************************

#ifndef CHA_PRINTERPIPE_H
#define CHA_PRINTERPIPE_H

#include <CHA_Pipe.H>
#include <CHA_PrinterList.H>

#include <rw/cstring.h>

class CHA_PrinterPipe
{

public:

    // Return codes
    enum ReturnCode
    {   
        OKAY,             // The pipe is OKAY and the child process started.
	NOFORK,           // The pipe is not OK because the child process
                          // could not start.
        CLOSED,           // The sending part of the pipe is closed,
                          // i.e. it is not possible to send information to
                          // the sub process anymore.
	NOPRINTER         // The pipe is not OK because the printer could
                          // be found.
    };

    CHA_PrinterPipe();
    // Description:
    //     Constructor. Whether the constructor succeeded or not can be
    //     checked with the method status(). Uses default printer name,
    //     i.e. the name that is returned by CHA_PrinterList::defaultName.
    CHA_PrinterPipe(const RWCString& printerName);
    // Description:
    //     Constructor. Whether the constructor succeeded or not can be
    //     checked with the method status().
    // Parameters:
    //     printerName         IN: The printer to use.

    virtual ~CHA_PrinterPipe();
    // Description:
    //     Destructor.

    CHA_PrinterPipe::ReturnCode status() const;
    // Description:
    //     To check the status of the printer pipe object. This method does
    //     not tell if the child process has terminated or not, it
    //     just tells the state of the pipe.
    // Return values:
    //     OKAY                The pipe is OK and the child process started.
    //                         execution.
    //     NOFORK              The pipe is not OK because the child process
    //                         could not start.
    //     CLOSED              The sending part of the pipe is closed,
    //                         i.e. it is not possible to send information to
    //                         the sub process anymore.
    //     NOPRINTER           The pipe is not OK because the printer could
    //                         be found.

    RWCString printerName() const;
    // Description:
    //     To get the name of the printer the pipe is connected to.
    // Return values:
    //     The name of the printer.

    std::ostream& send();
    // Description:
    //     Provides a stream for sending information to the printer.

private:

    void createPipe(const RWCString& printerName);
    //     To create the actual printer pipe. Called from constructor.
    // Parameters:
    //     printerName         IN: The printer to use.

    CHA_Pipe* pPipe;           // The actual pipe
    RWCString printer;         // Name of used printer

};

#endif
