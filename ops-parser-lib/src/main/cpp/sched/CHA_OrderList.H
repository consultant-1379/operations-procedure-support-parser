// RCS handling
// $Id: CHA_OrderList.H,v 24.0 1995/11/28 16:58:49 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_OrderList - A list of orders 
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_OrderList.H 

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
// 	CHA_OrderList.
//	A class for maintaining a list of subscriptions to orders.
//      The class is intended as a superclass for other more specialized
//      lists. All functionality demanded by specializations must be
//      defined in this class, otherwise it is not possible to use
//      this class instead of a specialization when defining an arbitary
//      list.
//      Some methodes are pure virtual, while others return nonsens values.
//      Each methode denotes how it should be treated when specializing.
//      The reason for having to different approches are that some
//      methodes must be implemented in subclasses (pure virtual), while
//      other methodes will only be applicable to some subclasses, hence
//      nonsens values.

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
//      $Log: CHA_OrderList.H,v $
//      Revision 24.0  1995/11/28 16:58:49  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:47:01  17:47:01  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:48:28  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:45:38  09:45:38  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:36:54  08:36:54  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:56:17  10:56:17  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:08:52  20:08:52  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:10:23  14:10:23  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:03:09  13:03:09  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:08:02  15:08:02  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:36:57  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:09:24  14:09:24  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:20:18  16:20:18  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:51:45  cmcha
//      Made release PREIT, N L\ufffdnninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:06:27  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:33:03  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:53:34  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:25:52  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.2  1994/09/15  14:34:04  qhsmosc
//      Sort implemented
//
//      Revision 6.1  1994/09/08  10:44:25  qhsmosc
//      Commented out function UpdateList
//
//      Revision 6.0  1994/08/30  17:53:02  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.1  1994/08/26  10:14:42  qhsmosc
//      Working version
//
//      Revision 5.0  1994/08/16  07:50:00  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.1  1994/08/10  06:11:00  qhsmosc
//      Back to hierarchy
//
//      Revision 1.1  1994/07/05  07:17:21  qhsmosc
//      Compilable
//
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	TB53_OZ 1995-11-28      J Grape (EHSGRAP)       RCS rev 24.0
//	XM2S1   1995-09-07      ehscama                 RCS rev 23.0
//	EC2_OZ  1995-08-01      Jan Sandquist (EHSJAASA)RCS rev 22.0
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
//	PREIT   1995-01-18      N L\ufffdnninge (XKKNICL)    RCS rev 11.0
//	TB2     1994-12-22      J Grape (EHSGRAP)       RCS rev 10.0
//	E       1994-10-24      ehscama                 RCS rev 9.0
//	D       1994-10-05      EHSCAMA                 RCS rev 8.0
//	R1C     1994-09-22      J Grape (EHSGRAP)       RCS rev 7.0
//	R1B     1994-08-30      J Grape (EHSGRAP)       RCS rev 6.0
//	R1A     1994-08-16      J Grape (EHSGRAP)       RCS rev 5.0

// .SEE ALSO 
//      <Related classes, (abstract) baseclasses, friend classes, ...>

//**********************************************************************

#ifndef CHA_ORDERLIST_H
#define CHA_ORDERLIST_H

/*/extern "C"
{
#include <cap_ipc.h>
}*/

#include <CHA_Order.H>
#include <rw/tpsrtvec.h>
#include <rw/cstring.h>

class CHA_OrderList : public CHA_Model
{
public:

    // events
    enum Event {ADDEDITEM,
		REMOVEDITEM,
		CHANGEDITEM,
		NOTHING};

    CHA_OrderList();
    //  Description:
    //    Default constructor.
    
    virtual ~CHA_OrderList();
    //  Description:
    //    Default destructor.

    virtual CHA_Order* operator()(size_t i);
    virtual CHA_Order* operator()(size_t i) const;
    //  Description:
    //    Returns the i'th value in the vector.
    //    The first can be used as an l-value, the second can not.
    //  Parameter:
    //    i          Index, must be between zero and number of elements

    virtual size_t entries() const;
    //  Description:
    //    Returns the number of items currently in the collection.

    virtual RWBoolean isEmpty() const;
    //  Description:
    //    Returns TRUE if there are no items in the collection,
    //    otherwise FALSE is returned.

    virtual int CreateList();
    //  Description:
    //    The routine fetches all information stored in the database and
    //    inserts the found information in the orderlist.
    //  Return value:
    //     A value < 0 indicates that an error has occured.

    //virtual int UpdateList();
    //  Description:
    //    The routine clears the orderlist and fetches the information
    //    from the database. To be used when somebody else has altered the
    //    information in the database, e.g. many users use the same user id.
    //  Return value:
    //     A value < 0 indicates that an error has occured.

    virtual int AddOrder (CHA_Order * s);
    //  Description:
    //    Adds a new order both to the list and to the database.
    //  Parameters:
    //    s          Order to be inserted
    //  Return value:
    //     A value < 0 indicates that an error has occured.

    virtual int RemoveOrder (const long orderId);
    //  Description:
    //    Removes a order both from the list and the database.
    //  Parameters:
    //    orderIdd     Identity of the order to be removed
    //  Return value:
    //     A value < 0 indicates that an error has occured.

    virtual int ChangeOrder (const long orderId);
    //  Description:
    //    Changes a order in the database.
    //  Parameters:
    //    orderId     Identity of order to be changed
    //  Return value:
    //     A value < 0 indicates that an error has occured.

    virtual int ActivateOrder (const long orderId);
    //  Description:
    //    Makes a order in the database active.
    //  Parameters:
    //    orderId     Identity of order to be activated
    // Return value:
    //     A value < 0 indicates that an error has occured.

    virtual int SuspendOrder (const long orderId);
    //  Description:
    //    Makes a order in the database deactivated.
    //  Parameters:
    //    orderId     Identity of order to be suspended
    // Return value:
    //     A value < 0 indicates that an error has occured.

    virtual Event getLastEvent() const;
    // Description:
    //     To find out what caused a updateFrom() call in a client of
    //     this model.
    // Return values:
    //     ADDEDITEM	an order was added to the list
    //     REMOVEDITEM	an order was removed from the list
    //     CHANGEDITEM	an order in the list was changed
    //     NOTHING      nothing has happened

    virtual const CHA_Order& getChangedOrder() const;
    // Description:
    //     To get hold of the new, removed or changed order when
    //     getLastEvent() has returned ADDEDITEM, REMOVEDITEM or CHANGEDITEM.
    // Return value:
    //     A reference to the changed order.
    
protected:

    virtual void announceEvent(Event evt, const CHA_Order& order);
    // Description:
    //     Notifies all model clients about an event. During the
    //     notification (the updateFrom() call) a model client can
    //     call getLastEvent() and getChangedOrder() to find out
    //     about the event.
    // Parameters:
    //     evt		the event to announce
    //     subsc	the affected order

protected:

     RWTPtrSortedVector<CHA_Order> orderList; 
	 //TORF-241666
  /*   RWCString processName;
    RWCString applName;
    RWCString user; */

    Event lastEvent;
    CHA_Order changedOrder;
};

#endif