// RCS handling
// $Id: CHA_IPCSupervisor.H,v 22.0.1.1 1996/01/05 14:18:24 ehsphad Exp $

//**********************************************************************
// 
// .NAME    CHA_IPCSupervisor - checks the IPC que
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_IPCSupervisor.H

// .COPYRIGHT
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
//      The class CHA_IPCSupervisor checks the IPC que for new
//      input. If messages have arrived on CAP-IPC all its
//      CHA_ModelClients are notified about the event. An IPC supervisor
//      never reads input from the IPC que, it just detects it.
//
//      The CHA_IPCSupervisor requires CAP-IPC to be initiated before
//      instantiation.

// DOCUMENT NO
//	190 89-CAA 134 1517

// AUTHOR 
// 	1994-02-24 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
// 	RCS revision history
//      $Log: CHA_IPCSupervisor.H,v $
//      Revision 22.0.1.1  1996/01/05 14:18:24  ehsphad
//      Changed all RWModel to CHA_Model.
//
//      Revision 24.0  1995/11/28 16:53:23  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:38:27  17:38:27  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:41:50  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:37:27  09:37:27  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:30:22  08:30:22  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:49:41  10:49:41  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:01:59  20:01:59  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:00:03  14:00:03  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  12:54:36  12:54:36  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  14:55:44  14:55:44  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:29:41  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  13:58:38  13:58:38  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:08:47  16:08:47  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:41:39  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  08:59:01  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:24:54  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:44:42  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:19:27  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:47:15  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:39:47  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:32:47  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:46:06  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  07:57:01  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.3  1994/06/10  16:54:44  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.2  1994/04/07  12:48:13  ehsgrap
//      changed checkIPCQue()
//
//      Revision 1.1  1994/03/31  13:36:20  ehsgrap
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
// 	CHA_IOSupervisor

//**********************************************************************

#ifndef CHA_IPCSUPERVISOR_H
#define CHA_IPCSUPERVISOR_H

#include <CHA_IOSupervisor.H>
#//include <cap_talk.H>


class CHA_IPCSupervisor : public CHA_IOSupervisor
{
public:
    CHA_IPCSupervisor(CHA_Model* pModel = NULL);
    // Description:
    //     Constructor. If the CHA_IPC_Supervisor is to be trigged by
    //     a model object a pointer to it can be provided. Otherwise
    //     the CAP-IPC que will not be checked unless the method
    //     checkIPCQue is called.
    // Parameters:
    //     pModel		IN: a pointer to a CHA_Model

    virtual ~CHA_IPCSupervisor();
    // Description:
    //     Destructor.
    
    virtual void updateFrom(CHA_Model* model, void* pData);
    // Description:
    //     The method called by the trigger object to initiate a
    //     check. Calls checkIPCQue().
    // Parameters:
    //     model		IN: a pointer to the calling object, not used
    //     pData		IN: not used

    virtual void detachFrom(CHA_Model* model);
    // Description:
    //     The method called by the trigger object if it dies.
    // Parameters:
    //     model		IN: a pointer to the calling object

    CHA_Model*  getTrigger(void);
    // Description:
    //     Returns the a Trigger (CHA_Model*), or NULL if not set.

    void checkIPCQue();
    // Description:
    //     Checks the CAP-IPC que. If th size of the que is > 0 all
    //     clients of this model are notified. It is then up to the
    //     notified objects (usually some kind of response receivers)
    //     to read out what's theirs from the que.

private:
    CHA_Model* pTrigger;
    //CAP_Talk talker;
};

#endif
