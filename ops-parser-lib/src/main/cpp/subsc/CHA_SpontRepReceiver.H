// RCS handling
// $Id: CHA_SpontRepReceiver.H,v 22.0.1.1 1995/09/10 21:38:24 etosad Exp $

//**********************************************************************
// 
// .NAME CHA_SpontRepReceiver - receiver of spontaneous reports 
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_SpontRepReceiver.H 
// 
// 	COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1994
//
// 	The Copyright to the computer program(s) herein is the
// 	property of Ericsson Hewlett-Packard Telecommunications AB,
// 	Sweden.  The program(s) may be used and/or copied with the
// 	written permission from Ericsson Hewlett-Packard
// 	Telecommunications AB or in accordance with the terms and
// 	conditions stipulated in the agreement/contract under which
// 	the program(s) have been supplied.


// .DESCRIPTION 
//      A CHA_DelRespReceiver implements methods inherited from the baseclass
//      CHA_SpDelReceiver.All methods concerns the reception of 
//      spontaneous reports.


// .SECTION ERROR HANDLING
//	Error messages are reported to the global error reporter
//      instance.

// DOCUMENT NO
//	190 89-CAA 134 1521

// AUTHOR 
// 	1994-05-10 by EHS/PXE Nicolas Länninge (xkknicl@ehs.ericsson.se)

// .REVISION
//	XM2S1
//	1995-09-07

// CHANGES
// 	RCS revision history
// 	$Log: CHA_SpontRepReceiver.H,v $
// 	Revision 22.0.1.1  1995/09/10 21:38:24  etosad
// 	A lot of changes!
//
//      Revision 23.0  1995/09/07  17:49:37  ehscama
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:50:30  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:47:52  09:47:52  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:39:00  08:39:00  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:58:32  10:58:32  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:11:13  20:11:13  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:13:30  14:13:30  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:05:29  13:05:29  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:12:23  15:12:23  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:38:58  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:12:26  14:12:26  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:23:01  16:23:01  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:54:33  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.1  1995/01/10  16:09:25  xkknicl
//      added private RWCString applicationName
//
//      Revision 10.0  1994/12/22  09:08:30  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:35:20  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:56:33  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:28:17  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:55:21  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:53:58  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:45:37  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  08:00:28  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:01:46  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.5  1994/06/10  16:56:48  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.4  1994/05/26  14:30:07  ehsgrap
//      getResponseBuffer() returns retCode
//
//      Revision 1.3  1994/05/18  09:08:02  xkknicl
//      Basic tested version
//
//      Revision 1.2  1994/05/16  14:41:38  xkknicl
//      Initial Version
//
//     Revision 1.1  1994/04/13  13:13:48  qhsmosc
//     Initial revision
//
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
// 	CHA_SpDelReceiver

//**********************************************************************

#ifndef CHA_SPONTREPRECEIVER_H
#define CHA_SPONTREPRECEIVER_H

#include <CHA_SpDelReceiver.H>
#include <CHA_NLSCatalog.H>

//#include <eac_cri_sp_rep.H>

class CHA_SpontRepReceiver : public CHA_SpDelReceiver
{

public:
    
    CHA_SpontRepReceiver(CHA_IPCSupervisor* pSup,
			 const RWCString& appN);
    // Description:
    //     Constructor.

    virtual ~CHA_SpontRepReceiver();
    // Description:
    //     Destructor.

    virtual int receiveResponse();
    // Description:
    //     Implementation of the method inherited from
    //     CHA_SpDelReceiver 

    virtual CHA_ResponseBuffer* createBuffer(const char* bufferString,
					     const char* command,
					     const char* esName);
    // Description:
    //     Implementation of the method inherited from
    //     CHA_SpDelReceiver 

    virtual CHA_ResponseBuffer* createBuffer(const char* bufferString,
					     const char* command,
					     const char* esName,
						   int   devId);
    // Description:
    //     Implementation of the method inherited from
    //     CHA_SpDelReceiver

    virtual CHA_ResponseBuffer* createAccumulatedBuffer();
    // Description:
    //     Implementation of the method inherited from
    //     CHA_SpDelReceiver
    
    virtual int getResponseBuffer(RWCString& bufferStr);
    // Description:
    //     Implementation of the method inherited from
    //     CHA_SpDelReceiver
    
    virtual int completeResponse();
    // Description:
    //     Implementation of the method inherited from
    //     CHA_SpDelReceiver
    
    virtual int interruptResponse();
    // Description:
    //     Implementation of the method inherited from
    //     CHA_SpDelReceiver
    
private:
    
    /*/EAC_CRI_Sp_Rep spontReport;*/
    RWCString applicationName;
};

#endif



