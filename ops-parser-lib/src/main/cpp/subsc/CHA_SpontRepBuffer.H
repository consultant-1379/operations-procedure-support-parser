// RCS handling
// $Id: CHA_SpontRepBuffer.H,v 22.0.1.2 1995/12/21 17:01:47 ehsphad Exp $

//**********************************************************************
// 
// .NAME    CHA_SpontRepBuffer - response buffer for spontaneous reports
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_SpontRepBuffer.H
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
//      The CHA_SpontRepBuffer class is a container for spontaneous reports.

// DOCUMENT NO
//      190 89-CAA 134 1517

// AUTHOR 
//      1994-05-10 by EHS/PXE Nicolas Länninge (xkknicl@ehs.ericsson.se)

// .REVISION
//	XM2S1
//	1995-09-07

// CHANGES
//      RCS revision history
//      $Log: CHA_SpontRepBuffer.H,v $
//      Revision 22.0.1.2  1995/12/21 17:01:47  ehsphad
//      Added copy method.
//
//      Revision 22.0.1.1  1995/09/10 21:38:00  etosad
//      A lot of changes!
//
//      Revision 23.0  1995/09/07  17:49:35  ehscama
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:50:28  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:47:50  09:47:50  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:38:59  08:38:59  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:58:30  10:58:30  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:11:10  20:11:10  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:13:27  14:13:27  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:05:27  13:05:27  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:12:18  15:12:18  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:38:56  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:12:24  14:12:24  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:22:56  16:22:56  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:54:30  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.1  1995/01/10  16:10:59  xkknicl
//      added CHA_UserInfo object + new parameter to constructor , application name
//
//      Revision 10.0  1994/12/22  09:08:28  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:35:17  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:56:29  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:28:13  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:55:17  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:53:50  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:45:33  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  08:00:24  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:01:42  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.2  1994/05/18  09:09:17  xkknicl
//      Basic tested version
//
//      Revision 1.1  1994/05/16  15:04:56  xkknicl
//      Initial Version
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

// .SEE ALSO 
//      CHA_ResponseBuffer

//**********************************************************************

#ifndef CHA_SPONTREPBUFFER_H
#define CHA_SPONTREPBUFFER_H

#include <CHA_ResponseBuffer.H>
#include <CHA_UserInfo.H>
#include <rw/cstring.h>


class CHA_SpontRepBuffer : public CHA_ResponseBuffer
{
    
public:
    
    CHA_SpontRepBuffer(const RWCString& respBuf,
		      const RWCString& cmd,
		      const RWCString& syst,
		      const long int reportId,
                      const RWCString& appN);
    // Description:
    //     Constructor.
    // Parameters:
    //     respBuff		IN: the response string
    //     cmd			IN: the command that caused the response
    //     syst			IN: the system that caused the response
    //     reportId             IN: the report id for the subscription.

    CHA_SpontRepBuffer(const CHA_ResponseBuffer& other,
		       const long int reportId);
    // Description:
    //     Copy constructor.
    // Parameters:
    //     other		IN: the response buffer to copy
    //     reportId             IN: the report id for the subscription.
    
  virtual CHA_ResponseBuffer*  copy() const;
    // Description:
    //     Returns a copy of the calling buffer.


    virtual RWCString getHeader() const;
    // Description:
    //     Returns a header suitable for printing.

    virtual RWCString getOneLineHeader() const;
    // Description:
    //     Returns a one line header suitable for printing.

private:
    long int reportIden;

    RWCString applicationName;

    CHA_UserInfo userInfo;
};

#endif

