// RCS handling
// $Id: CHA_ExecOrderList.H,v 24.0 1995/11/28 16:58:42 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_ExecOrderList - A list of orders 
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_ExecOrderList.H 

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
// 	CHA_ExecOrderList.
//	A class for maintaining a list of orders.
//      At construction all made orders are fetched from database.
//      The application program can add, delete and change orders.
//      Each operation effects the database directly.

// .SECTION ERROR HANDLING
//      <General rules for error handling>

// DOCUMENT NO
//      190 89-CAA 134 1516

// AUTHOR 
//      1994-06-10 by EHS/ Marie Moschna (qhsmosc@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_ExecOrderList.H,v $
//      Removed CHA_SysCmdFileOrder and CHA_CmdFileOrder, A Ahlström (EHSANAH).
//
//      Revision 24.0  1995/11/28 16:58:42  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:46:52  17:46:52  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.1  1995/08/25  09:57:34  qhsiabr
//      Added getOrderState.
//
//      Revision 22.0  1995/08/01  20:48:22  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:45:31  09:45:31  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:36:48  08:36:48  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:56:11  10:56:11  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:08:44  20:08:44  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:10:15  14:10:15  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:03:01  13:03:01  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:07:49  15:07:49  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:36:51  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.6  95/02/16  15:54:31  15:54:31  qhskred (Krister Eklund VK/EHS/PXE)
//      Added #include <CHA_OztCmdFileOrder.H>
//      
//      Revision 13.5  1995/02/15  14:09:13  cmcha
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 12.0  95/02/06  16:20:08  16:20:08  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:51:38  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:06:21  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:32:55  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:53:23  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:25:45  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.1  1994/09/15  14:33:50  qhsmosc
//      Sort implemented
//
//      Revision 6.0  1994/08/30  17:52:53  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:49:48  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.1  1994/08/09  13:18:28  qhsmosc
//      Back to hierarchy
//
//      Revision 1.1  1994/07/05  07:16:25  qhsmosc
//      Compilable
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

// .SEE ALSO 
//      CHA_OrderList           base class
//      CHA_OztCmdFileOrder     

//**********************************************************************

#ifndef CHA_EXECORDERLIST_H
#define CHA_EXECORDERLIST_H
/*
extern "C"
{
#include <cap_ipc.h>
}*/

#include <CHA_OrderList.H>
#include <CHA_Order.H>
#include <CHA_OztCmdFileOrder.H>
#include <CHA_Converter.H>
#include <rw/tpsrtvec.h>
#include <rw/cstring.h>

class CHA_ExecOrderList : public CHA_OrderList
{
public:

    CHA_ExecOrderList();
    //  Description:
    //    Default constructor.
    
    virtual ~CHA_ExecOrderList();
    //  Description:
    //    Default destructor.

    virtual int createList(CHA_SortOrder so);
    //  Description:
    //    The routine fetches all information stored in the database and
    //    inserts the found information in the orderlist.
    // Parameters:
    //     so        how the orders should be presented
    //  Return value:
    //     A value < 0 indicates that an error has occured.

    virtual int updateList();
    //  Description:
    //    The routine clears the orderlist and fetches the information
    //    from the database. To be used when somebody else has altered the
    //    information in the database, e.g. many users use the same user id.
    //  Return value:
    //     A value < 0 indicates that an error has occured.

    virtual int addOrder (CHA_Order * s);
    //  Description:
    //    Adds a new order both to the list and to the database.
    //  Parameters:
    //    s          Order to be inserted
    //  Return value:
    //     A value < 0 indicates that an error has occured.

    virtual int removeOrder (const long orderId);
    //  Description:
    //    Removes a order both from the list and the database.
    //  Parameters:
    //    orderIdd     Identity of the order to be removed
    //  Return value:
    //     A value < 0 indicates that an error has occured.

    virtual int changeOrder (const long orderId);
    //  Description:
    //    Changes a order in the database.
    //  Parameters:
    //    orderId     Identity of order to be changed
    //  Return value:
    //     A value < 0 indicates that an error has occured.

    virtual int changeOrder (CHA_Order* order);
    //  Description:
    //    Changes a order in the database. The pointer must not be deleted by
    //    the calling program. When the list is emptied or if remove is called
    //    the pointer will be deleted.
    //  Parameters:
    //    order       New information to be inserted in old order
    //  Return value:
    //     A value < 0 indicates that an error has occured.

    virtual int activateOrder (const long orderId);
    //  Description:
    //    Makes a order in the database active.
    //  Parameters:
    //    orderId     Identity of order to be activated
    // Return value:
    //     A value < 0 indicates that an error has occured.

    virtual int suspendOrder (const long orderId);
    //  Description:
    //    Makes a order in the database deactivated.
    //  Parameters:
    //    orderId     Identity of order to be suspended
    // Return value:
    //     A value < 0 indicates that an error has occured.

    virtual const CHA_OrderState getOrderState (const long orderId);
    //  Description:
    //    Returns a state of the order.
    //  Parameters:
    //    orderId     Identity of order to be suspended
    // Return value:
    //     A value < 0 indicates that an error has occured.

protected:

private:

};

#endif

