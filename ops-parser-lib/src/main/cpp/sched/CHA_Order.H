// RCS handling
// $Id: CHA_Order.H,v 24.0 1995/11/28 16:58:46 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_Order - A superclass for orders 
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_Order.H 

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
// 	CHA_Order.
//	A superclass for the information held about orders and the common
//      functionality for these.
//      The class is intended as a superclass for other more specialized
//      orders. All functionality demanded by the specializations must be
//      defined in this class, otherwise it is not possible to use
//      this class instead of a specialization when defining an arbitary
//      order.
//      Some methodes are pure virtual, while others return nonsens values.
//      Each methode denotes how it should be treated when specializing.
//      The reason for having two different approches are that some
//      methodes must be implemented in subclasses (pure virtual), while
//      other methodes will only be applicable to some subclasses, hence
//      nonsens values for all other subclasses.
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
//      $Log: CHA_Order.H,v $
//      Revision 24.0  1995/11/28 16:58:46  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:46:57  17:46:57  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:48:26  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:45:35  09:45:35  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:36:52  08:36:52  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:56:15  10:56:15  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.1  95/03/23  19:27:51  19:27:51  ehscama (Martin Carlsson VK/EHS/PXE)
//      Removed superflous "," from the enum definitions to remove warnings.
//      
//      Revision 18.0  1995/03/17  20:08:49  cmcha
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:10:21  14:10:21  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:03:06  13:03:06  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:07:57  15:07:57  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:36:55  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.7  95/02/21  15:19:30  15:19:30  qhskred (Krister Eklund VK/EHS/PXE)
//      Changed CHA_OrderState to confirm to status as defined in AM_Order.H
//      
//      Revision 13.6  1995/02/16  15:58:38  qhskred
//      Added support for CHA_OztCmdFileOrder
//
//      Revision 13.5  1995/02/15  14:09:19  cmcha
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 9.1  95/02/08  12:53:12  12:53:12  qhsmosc (Marie Moschna VK/EHS/PXE)
//      rewrite after TAS change
//      
//      Revision 9.0  1994/10/24  21:33:01  cmcha
//      Made release E, ehscama.
//
//      Revision 8.3  1994/10/24  19:03:15  ehscama
//      Made operator< and operator== const.
//
//      Revision 8.2  1994/10/20  14:45:34  qhsmosc
//      Changed order of items in enum CHA_OrderState
//
//      Revision 8.1  1994/10/13  19:34:09  ehsgrap
//      Increased const corectness.
//
//      Revision 8.0  1994/10/05  08:53:31  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.1  1994/09/28  12:49:55  qhsmosc
//      Added enum for error codes
//
//      Revision 7.0  1994/09/22  13:25:49  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.1  1994/09/15  14:31:34  qhsmosc
//      Sort implemented
//
//      Revision 6.0  1994/08/30  17:53:00  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:49:56  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.3  1994/08/16  06:53:13  qhsmosc
//      Before freeze, testing remaining
//
//      Revision 4.2  1994/08/09  12:52:26  qhsmosc
//      A little more cleaning up
//
//      Revision 4.1  1994/08/09  12:50:40  qhsmosc
//      Back to hierarchy
//
//      Revision 1.2  1994/07/12  06:47:33  qhsmosc
//      Preliminary tests OK
//
//      Revision 1.1  1994/07/05  07:16:56  qhsmosc
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
//	E       1994-10-24      ehscama                 RCS rev 9.0
//	D       1994-10-05      EHSCAMA                 RCS rev 8.0
//	R1C     1994-09-22      J Grape (EHSGRAP)       RCS rev 7.0
//	R1B     1994-08-30      J Grape (EHSGRAP)       RCS rev 6.0
//	R1A     1994-08-16      J Grape (EHSGRAP)       RCS rev 5.0

// .SEE ALSO 
//      <Related classes, (abstract) baseclasses, friend classes, ...>

//**********************************************************************

#ifndef CHA_ORDER_H
#define CHA_ORDER_H

/*/extern "C"
{
#include <cap_ipc.h>
}*/

//#include <rw/tvordvec.h>
#include <rw/tpsrtvec.h>
#include <rw/cstring.h>
#include <rw/tools/datetime.h>
#include "CHA_ExecOrderInterval.H"
#include "CHA_RoutingCase.H"

// forward declarations
class CHA_Converter;

enum CHA_OrderState
{
    CHA_ORDER_ACTIVE    = 1,
    CHA_ORDER_CANCELLED = 2,
    CHA_ORDER_IDLE      = 3,
    CHA_ORDER_SCHEDULED = 4,
    CHA_ORDER_COMPLETED = 5
};

enum CHA_Answer
{
    CHA_OK,
    CHA_NOK,
    CHA_NOT_APPLICABLE
};

enum CHA_OrderKind
{
    CHA_ORDKIND_CMDFILE    = 0,
    CHA_ORDKIND_SYSCMDFILE = 1,
    CHA_ORDKIND_OZTCMDFILE = 2
};

enum CHA_SortOrder
{
    CHA_SORT_ORDERNR,
    CHA_SORT_FILENAME,
    CHA_SORT_TYPE,
    CHA_SORT_ES,
    CHA_SORT_STARTTIME,
    CHA_SORT_STATUS,
    CHA_SORT_FILENAMEES,
    CHA_SORT_DONTCHANGE
};

enum CHA_Resp
{
    CHA_SYNCHRON,
    CHA_ASYNCHRON,
    CHA_RESP_NONE
};

enum CHA_AmError
{
    CHA_AM_OK = 0,
    CHA_AM_ERROR = -1,
    CHA_AM_ILLEGAL_ARGUMENT = -2,
    CHA_AM_DBFULL = -3,
    CHA_AM_KEYEXISTS = -4,
    CHA_AM_KEYNOTFOUND = -5,
    CHA_AM_NO_MEMORY = -6,
    CHA_AM_OLD_DATE = -13,
    CHA_AM_JOBEXISTS = -14,
    CHA_AM_TIMEERR = -15,
    CHA_AM_JOBNOTEXIST = -16
};

class CHA_Order
{
public:

    CHA_Order();
    // Description:
    //     Default constructor.

    CHA_Order(const CHA_Order& s);
    // Description:
    //     Constructor to be used at copy.

    virtual ~CHA_Order();
    // Description:
    //     Destructor.
    
    virtual int activate();
    // Description:
    //     Activate the order.
    // Return value:
    //     A value < 0 indicates that an error has occured.
    
    virtual int suspend();
    // Description:
    //     Suspend the order.
    // Return value:
    //     A value < 0 indicates that an error has occured.
    
    virtual int fetch(const long s);
    // Description:
    //     Read the order from the order database.
    // Parameters:
    //     s                    order identity
    // Return value:
    //     A value < 0 indicates that an error has occured.
    
    virtual int store();
    // Description:
    //     Store the order in the database. Used both to insert a new
    //     order in the database and to overwrite an existing order.
    // Return value:
    //     A value < 0 indicates that an error has occured.
    
    virtual int remove();
    // Description:
    //     Delete the order from the database. 
    // Return value:
    //     A value < 0 indicates that an error has occured.
    
    virtual const CHA_OrderState& getState() const;
    // Description:
    //     Get the current state for the order.
    // Return value:
    //     A CHA_OrderState with the current state for the order. 

    virtual void setState(CHA_OrderState s);
    // Description:
    //     Set the current state for the order. This routine does NOT
    //     effect the value in the databas, to effect it you should
    //     use activate and suspend.
    //     The routine exists to set the value when information is read
    //     from the database.
    // Parameter:
    //     s              A CHA_OrderState with the current state for the
    //                    order. 

    virtual const CHA_OrderKind& getOrderKind() const;
    // Description:
    //     Get the kind of order.
    // Return value:
    //     A CHA_OrderKind with the kind of the order. 

    virtual void setName(const RWCString& n);
    // Description:
    //     Set the name of the order.
    // Parameters:
    //     n                    the name of the order
    
    virtual const RWCString& getName() const;
    // Description:
    //     Get the name of the order.
    // Return value:
    //     A RWCString with the current name of the order. 

    virtual void setOrderId(const long& s);
    // Description:
    //     Set the identity of the order.
    // Parameters:
    //     s                    the identity
    
    virtual const long getOrderId() const;
    // Description:
    //     Get the identity of the order.
    // Return value:
    //     A long with the identity of the order. 

    virtual void setInterval(const CHA_ExecOrderInterval& s);
    // Description:
    //     Set the time interval for the order.
    // Parameters:
    //     s                    the interval for the order
    
    virtual const CHA_ExecOrderInterval& getInterval() const;
    // Description:
    //     Get the time Interval for the order.
    // Return value:
    //     A CHA_SchedInterval with the current interval for the
    //     order. 
    
    virtual void setHost(const RWCString& h);
    // Description:
    //     Set the host parameter of the order.
    // Parameters:
    //     h                    the host of the order
    
    virtual const RWCString& getHost() const;
    // Description:
    //     Get the host parameter of the order.
    // Return value:
    //     A RWCString with the current host parameter of the order. 

    virtual void setTasId(const int t);
    // Description:
    //     Set the crontab identity of the order.
    // Parameters:
    //     t                    the crontab identity of the order
    
    virtual const int getTasId() const;
    // Description:
    //     Get the crontab identity of the order.
    // Return value:
    //     An integer with the current crontab identity of the order. 

    virtual void setTimestamp(const RWDateTime& n);
    // Description:
    //     Set the timestamp of the order.
    // Parameters:
    //     n                    the timestamp of the order
    
    virtual const RWDateTime& getTimestamp() const;
    // Description:
    //     Get the timestamp of the order.
    // Return value:
    //     A RWTime with the current timestamp of the order. 
    
    virtual void setStartTime(const RWDateTime& m);
    // Description:
    //     Set the start time of the order.
    // Parameters:
    //     m                    the start time of the order
    
    virtual const RWDateTime& getStartTime() const;
    // Description:
    //     Get the start time of the order.
    // Return value:
    //     A RWTime with the current start time of the order.

    virtual CHA_Order& operator=(const CHA_Order& s);
    // Description:
    //     Assignmentoperator, required by TOOL
    // Parameter:
    //     s                    the original order

    virtual int operator==(const CHA_Order& s) const;
    // Description:
    //     Equallity operator, required by TOOL
    // Parameter:
    //     s                    the order that is to be compared 

    virtual int operator<(const CHA_Order& s) const;
    // Description:
    //     Less than operator, required by TOOL
    // Parameter:
    //     s                    the order that is to be compared 

    static void setSortOrder(const CHA_SortOrder so);
    // Description:
    //     Sets the parameter used when sorting the orders.
    // Parameter:
    //     so                   the sortorder that is to be used 

    

protected:
    CHA_OrderState    state;
    long              orderId;
    RWCString         name;
    CHA_OrderKind     kind;
    CHA_ExecOrderInterval interval;

    RWCString         host;
    int               tasId;
    RWDateTime            timestamp;
    RWDateTime            startTime;

    static CHA_SortOrder sortOrder;
};

#endif


