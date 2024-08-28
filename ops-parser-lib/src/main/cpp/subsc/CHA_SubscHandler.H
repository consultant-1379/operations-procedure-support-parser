// RCS handling
// $Id: CHA_SubscHandler.H,v 24.0 1995/11/28 17:00:44 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_SubscHandler - All that is needed to handle subscriptions 
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_SubscHandler.H 

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
//      The handler is used to instansiate all objects that are needed to
//      maintain subscriptions for spontaneous reports. On request the
//      handler can give references to it's member classes.

// DOCUMENT NO
//      190 89-CAA 134 1521

// AUTHOR 
//      1994-05-17 by EHS Marie Moschna (qhsmosc@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_SubscHandler.H,v $
//      Revision 24.0  1995/11/28 17:00:44  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:49:46  17:49:46  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:50:36  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:48:02  09:48:02  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:39:05  08:39:05  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.1  95/04/24  12:44:21  12:44:21  ehsgrap (Jan Grape (9 9073) VK/EHS/PXE)
//      Changed define of _H to CHA_SUBSCHANDLER_H
//      
//      Revision 19.0  1995/04/13  10:58:38  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:11:18  20:11:18  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:13:34  14:13:34  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:05:34  13:05:34  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:12:32  15:12:32  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:39:03  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:12:32  14:12:32  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:23:14  16:23:14  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:54:41  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:08:39  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:35:26  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:56:44  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:28:22  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:55:28  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:54:07  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:45:46  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  08:00:38  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:01:53  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.3  1994/06/10  16:56:59  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.2  1994/05/17  14:42:35  qhsmosc
//      Removed heritage to ModelClient
//
//      Revision 1.1  1994/05/17  13:16:42  qhsmosc
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
//      CHA_SubscList
//      CHA_SpontRepReceiver

//**********************************************************************

#ifndef CHA_SUBSCHANDLER_H
#define CHA_SUBSCHANDLER_H

#include <CHA_SubscList.H>
#include <CHA_SpontRepReceiver.H>
#include <CHA_RoutingHandler.H>
#include <rw/cstring.h>

class CHA_SubscHandler
{
public:

    CHA_SubscHandler(CHA_IPCSupervisor* pSuper,
		     CHA_RoutingHandler* pHandler,
		     RWCString applName);
    // Description:
    //   Constructor.
    // Parameters:
    //    pSuper     IN: an IPC Supervisor
    //    pHandler   IN: a Routing Handler
    //    applName   IN: the name of the calling application
    

    virtual ~CHA_SubscHandler();
    // Description:
    //   Destructor.Will remove itself as a dependent of the
    //              Sub Process supervisor.

    
    CHA_SubscList* getSubscList();
    // Description:
    //   Returns a pointer to a SubscList Object.
    

    CHA_SpontRepReceiver* getReceiver();
    // Description:
    //   Returns a pointer to a Receiver Object.

    
private:

    CHA_SubscList subscList;                     // CHA_SubscList object
    CHA_SpontRepReceiver spontRepReceiver;       // CHA_SpontRepReceiver object

};

#endif
