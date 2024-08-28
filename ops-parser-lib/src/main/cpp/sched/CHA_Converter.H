// RCS handling
// $Id: CHA_Converter.H,v 24.0 1995/11/28 16:58:38 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_Converter - Handles the database interface for system
//                          command file orders and command file orders.
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_Converter.H 

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
// 	CHA_Converter.
//	A class for the database interface for system command file orders
//      and command file orders. 
//      The class provides methodes for accessing nbdm and TAS (Crontab),
//      and to keep the information consistent between the two.
//      The class does not contain any variables only methodes.

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
//      $Log: CHA_Converter.H,v $
//      Revision   2000/03/02 16:58:38  ehsanah
//      Remove CHA_CmdFileOrder and CHA_SysCmdFileOrder
//
//      Revision 24.0  1995/11/28 16:58:38  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:46:46  17:46:46  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.1  1995/08/30  16:03:32  ehscama
//      Merged in changes from 16.0.1.2.
//
//      Revision 22.0  1995/08/01  20:48:05  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.1  95/07/13  20:45:06  20:45:06  ehscama (Martin Carlsson VK/EHS/PXE)
//      *** empty log message ***
//      
//      Revision 21.0  95/06/29  09:45:26  09:45:26  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:36:44  08:36:44  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:56:07  10:56:07  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.1  95/04/12  16:19:59  16:19:59  ehscama (Martin Carlsson VK/EHS/PXE)
//      Uses the old TAS TTCB names for TPF 4.0.x.
//      
//      Revision 18.0  1995/03/17  20:08:39  cmcha
//      Made release TB51_OZ, ehscama.
//
//      Revision 16.0.1.2  1995/08/16  09:37:36  ehscama
//      Introduced static methods for constructing and destructing
//      the time control object. This solves TRs EE51210 and EE33958.
//
//      Revision 16.0.1.1  1995/08/01  14:57:45  ehscama
//      Forced check in by EHSPHAD, author EHSCAMA
//
//      Revision 17.0  95/03/16  14:10:07  14:10:07  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:02:56  13:02:56  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
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
//      CHA_Order		user
//      CHA_OztCmdFileOrder     user

//**********************************************************************

#ifndef CHA_CONVERTER_H
#define CHA_CONVERTER_H
/*
extern "C"
{
#include <cap_ipc.h>
}
*/
#include <CHA_Order.H>
#include <CHA_OztCmdFileOrder.H>
#include <CHA_RoutingCase.H>
#include <CHA_ExecOrderInterval.H>
#include <CHA_UserInfo.H>

/// TODO 
///#if TPF >= 400
///#include <tas_tc_time_control.hh>
///#include <tas_tc_com_entry.hh>
#define TAS_TCCH_time_control TAS_TC_time_control
///#define TAS_TCCH_com_entry TAS_TC_com_entry
///#else
///#include <tas_tcch_time_control.hh>
///#include <tas_tcch_com_entry.hh>
///#endif

#include <AM_Order.H>
#include <AM_OrderStorage.H>
#include <AM_auxFunctions.H>
#include <AM_ttcbFunctions.H>
#include <rw/cstring.h>
#include <rw/ctoken.h>
#include <rw/rstream.h>
#include <rw/tvordvec.h>

class CHA_Converter
{
public:

    CHA_Converter();
    // Description:
    //     Default constructor.

    virtual ~CHA_Converter();
    // Description:
    //     Destructor.

    static void constructTimeControl();
    // Description:
    //     Construct the singleton time control object
    //     used by the converter. This object is very costly to 
    //     construct and there should only be one.

    static void destructTimeControl();
    // Description:
    //     Destruct the time control object.
    
    virtual int activate(CHA_Order& order);
    // Description:
    //     Activate the order.
    // Parameter:
    //     order      Order to activate
    // Return value:
    //     A value < 0 indicates that an error has occured.
    
    virtual int suspend(CHA_Order& order);
    // Description:
    //     Suspend the order.
    // Parameter:
    //     Order to suspend
    // Return value:
    //     A value < 0 indicates that an error has occured.
    
    virtual int fetchOrder(const long ordId, CHA_Order& s);
    // Description:
    //     Read the order from the order database.
    //     Checks if the order in ndbm really should be CANCELLED. If the
    //	   order can`t be found in Crontab, the orderstatus is changed to
    //     CANCELLED.
    // Parameters:
    //     ordId                key to search with
    //     s                    where to put found information
    // Return value:
    //     A value < 0 indicates that an error has occured.
    
    virtual int storeOrder(CHA_Order& s);
    // Description:
    //     Store the order in the databases. Used both
    //     to insert a new order in the database and to
    //     overwrite an existing order.
    // Parameters:
    //     s              Order that is to be stored
    
    virtual int removeOrder(const long ordId);
    // Description:
    //     Remove order from ndbm.
    // Parameter:
    //     ordId         Identity of the order 
    // Return value:
    //     A value < 0 indicates that an error has occured.

    virtual long getFirstKey();
    // Description:
    //     Reads the database and creates an internal list of keys
    //     to all orders contained in the database.
    // Return value:
    //     A long with the first found key.

    virtual long getNextKey();
    // Description:
    //     Reads the internal list of keys, returns the first key pointed to
    //     in this list and advances the pointer.
    // Return value:
    //     The key pointed to in the internal list of order keys.
    
    virtual int fetchKind(const long ordId);
    // Description:
    //     Reads the order denoted by ordId and returns the order type
    // Parameter:
    //     ordId           Identity for the order that is to be type checked
    // Return value:
    //     enum CHA_OrderKind   if OK
    //     enum CHA_AmError	if error
    
private:

    virtual int oztCmdFileToOrderData(AM_OrderData *orderData, 
				         CHA_OztCmdFileOrder *inOrder);
    // Description:
    //     Moves information stored in a ozt command file object to
    //     an orderdata object.
    // Parameter:
    //     ordData         where to put the information
    //     inOrd           original information
    // Return value:
    //     Error code, < 0 indicates that an error has occured.

    virtual int orderDataToOztCmdFile(AM_OrderData *orderData, 
				      CHA_OztCmdFileOrder *inOrder);
    // Description:
    //     Moves information stored in an ozt orderdata object to a 
    //     command file object.
    // Parameter:
    //     ordData         original information
    //     inOrd           where to put the information
    // Return value:
    //     Error code, < 0 indicates that an error has occured.

    virtual long checkKey(long orderKey);
    // Description:
    //     Also checks if the order belongs to the current user.
    // Parameter:
    //     orderkey         Order that shall be checked
    // Return value:
    //     if < 0    errorcode, some error has occured 
    //     if = 0    ok, but belonging to another user
    //     if > 0    keyvalue ok and belonging to current user

    RWTValOrderedVector<long> keyList;
    int curKey;
    CHA_UserInfo userInfo;
};

#endif


