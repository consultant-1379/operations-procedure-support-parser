// RCS handling
// $Id: CHA_FileTarget.H,v 24.0 1995/11/28 16:57:47 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_FileTarget - sends responses to a specific file
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_FileTarget.H

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
//      CHA_FileTarget is a routing target for responses routed to
//      file. A file target observes one or more response receivers
//      and sends a prinout to a specific file for every response it
//      receives.
//
//      A CHA_FileTarget only handles one file so if routing
//      is set up to more than one file there will have to be
//      multiple file targets. Instantiation and control is usually
//      done by a CHA_FileRouter.

// .SECTION ERROR HANDLING
//      Errors are reported to the global CHA_ErrorReporter instance. 

// DOCUMENT NO
//      190 89-CAA 134 1519

// AUTHOR 
//      1994-05-03 by EHS/PXE Nicolas L�nninge (xkknicl@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_FileTarget.H,v $
//      Revision 24.0  1995/11/28 16:57:47  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:45:20  17:45:20  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:47:07  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:43:48  09:43:48  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:35:43  08:35:43  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:55:03  10:55:03  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:07:26  20:07:26  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:08:11  14:08:11  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:01:43  13:01:43  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:05:31  15:05:31  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:35:44  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:06:46  14:06:46  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:18:21  16:18:21  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:48:45  cmcha
//      Made release PREIT, N L�nninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:04:52  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:31:22  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:51:08  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:24:17  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:51:26  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:47:23  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:39:52  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:56:01  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  07:58:46  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.2  1994/06/10  16:54:25  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.1  1994/05/04  13:27:38  xkknicl
//      Initial version
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
//	PREIT   1995-01-18      N L�nninge (XKKNICL)    RCS rev 11.0
//	TB2     1994-12-22      J Grape (EHSGRAP)       RCS rev 10.0
//	E       1994-10-24      ehscama                 RCS rev 9.0
//	D       1994-10-05      EHSCAMA                 RCS rev 8.0
//	R1C     1994-09-22      J Grape (EHSGRAP)       RCS rev 7.0
//	R1B     1994-08-30      J Grape (EHSGRAP)       RCS rev 6.0
//	R1A     1994-08-16      J Grape (EHSGRAP)       RCS rev 5.0
//	P1C     1994-07-18      J Grape (EHSGRAP)       RCS rev 4.0
//	P1B     1994-06-23      J Grape (EHSGRAP)       RCS rev 3.0
//	P1A     1994-06-12      J Grape (EHSGRAP)       RCS rev 2.0

// .SEE ALSO 
//      CHA_RoutingTarget, CHA_FileRouter

//**********************************************************************

#ifndef CHA_FILETARGET_H
#define CHA_FILETARGET_H

#include <CHA_RoutingTarget.H>
#include <CHA_NLSCatalog.H>


class CHA_FileTarget : public CHA_RoutingTarget
{
    
public:

    CHA_FileTarget(const RWCString& file);
    // Description:
    //     Constructor.
    // Parameters:
    //     file		the filename to send responses to

    virtual ~CHA_FileTarget();
    // Description:
    //     Destructor.

protected:

    virtual void doRouting(const CHA_ResponseBuffer* pResponse);
    // Description:
    //     Implements the actual routing, i.e. sending the output to
    //     file. Activated by the superclass.
    // Parameters:
    //     response	the response to route

private:

    RWCString fileName;		// Name of the File
    CHA_NLSCatalog nlsCat;
};

#endif
