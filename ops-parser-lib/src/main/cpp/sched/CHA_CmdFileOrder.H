// RCS handling
// $Id: CHA_CmdFileOrder.H,v 24.0 1995/11/28 16:58:36 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_CmdFileOrder - Handles information and functionality for
//                             command file orders. 
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_CmdFileOrder.H 

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
// 	CHA_CmdFileOrder.
//	A class for the specific information held about command 
//      file orders and functionality only applicable for such orders.
//      The application program can add, delete and change orders.

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
//      $Log: CHA_CmdFileOrder.H,v $
//      Revision 24.0  1995/11/28 16:58:36  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:46:41  17:46:41  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:48:03  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:45:24  09:45:24  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:36:42  08:36:42  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:56:05  10:56:05  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:08:36  20:08:36  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:10:03  14:10:03  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:02:54  13:02:54  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:07:37  15:07:37  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:36:45  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:08:51  14:08:51  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.1  95/02/09  12:14:35  12:14:35  xkknicl (Nicolas Laenninge VK/EHS/PXE)
//      added  CHA_UserInfo object
//      
//      Revision 12.0  1995/02/06  16:19:57  cmcha
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:51:25  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:06:13  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:32:45  cmcha
//      Made release E, ehscama.
//
//      Revision 8.1  1994/10/13  19:33:04  ehsgrap
//      Increased const corectness.
//
//      Revision 8.0  1994/10/05  08:53:05  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.2  1994/10/04  14:45:46  qhsmosc
//      Backed one revision
//
//      Revision 7.0  1994/09/22  13:25:35  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.1  1994/09/15  14:32:34  qhsmosc
//      Sort implemented
//
//      Revision 6.0  1994/08/30  17:52:46  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:49:33  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.1  1994/08/10  06:16:04  qhsmosc
//      Back to hierarchy
//
//      Revision 1.2  1994/07/12  06:48:20  qhsmosc
//      Preliminary tests OK
//
//      Revision 1.1  1994/07/05  07:00:53  qhsmosc
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

// .SEE ALSO 
//      CHA_Order		Superclass

//**********************************************************************

#ifndef CHA_CMDFILEORDER_H
#define CHA_CMDFILEORDER_H

/*
extern "C"
{
#include <cap_ipc.h>
}
*/

#include <CHA_Order.H>
#include <CHA_RoutingCase.H>
#include <CHA_UserInfo.H>
#include <rw/cstring.h>

class CHA_CmdFileOrder : public CHA_Order
{
public:

    CHA_CmdFileOrder();
    // Description:
    //     Default constructor.

    CHA_CmdFileOrder(const CHA_CmdFileOrder& s);
    // Description:
    //     Constructor to be used at copy.

    virtual ~CHA_CmdFileOrder();
    // Description:
    //     Destructor.
    
    virtual void setExternalSystem(const RWCString& e);
    // Description:
    //     Set the external system for the command file order.
    // Parameters:
    //     e                    the external system
    
    virtual const RWCString& getExternalSystem() const;
    // Description:
    //     Get the external system for the command file order.
    // Return value:
    //     A RWCString with the current external system for the
    //     command file order. 
    
    virtual void setFuncBusyRetry(const int p);
    // Description:
    //     Set the function busy retry period for the command file order.
    // Parameters:
    //     p                    the function busy retry period
    
    virtual const int getFuncBusyRetry() const;
    // Description:
    //     Get the function busy retry period for the command file order.
    // Return value:
    //     An int with the current function busy retry period for the command
    //     file order.
    
    virtual void setStopExecAtNotAccep(const RWBoolean p);
    // Description:
    //     If TRUE the execution should be stoped when not accepted..
    // Parameters:
    //     p                    TRUE or FALSE
    
    virtual const RWBoolean stopExecAtNotAccep () const;
    // Description:
    //     Check if the execution should be stoped when not accepted.
    // Return value:
    //     True if the execution should be stoped.
    
    virtual void setStopExecAtPartExec(const RWBoolean p);
    // Description:
    //     If TRUE the execution can be stoped when partly executed.
    // Parameters:
    //     p                    TRUE or FALSE
    
    virtual const RWBoolean stopExecAtPartExec () const;
    // Description:
    //     Check if the execution can be stoped when partly executed.
    // Return value:
    //     TRUE if the execution can be stoped.
    
    virtual void setSendMailForNAPE(const RWBoolean p);
    // Description:
    //     TRUE if mail should be sent after NOT ACCEPTED or PARTLY
    //     EXECUTED.
    // Parameters:
    //     p                    TRUE or FALSE
    
    virtual const RWBoolean sendMailForNAPE() const;
    // Description:
    //     Check if mail should be sent after NOT ACCEPTED or PARTLY
    //     EXECUTED.
    // Return value:
    //     TRUE of mail should be sent.
   
    virtual void setSendMailForExecResult(const RWBoolean p);
    // Description:
    //     TRUE if mail with execution result should be sent.
    // Parameters:
    //     p                    TRUE or FALSE
    
    virtual const RWBoolean sendMailForExecResult() const;
    // Description:
    //     Check if mail with execution result should be sent.
    // Return value:
    //     TRUE if mail should be sent.
   
    virtual void setMailAddress(const RWCString p);
    // Description:
    //     Set the mail address for the command file order.
    // Parameters:
    //     p                    the mail address
    
    virtual const RWCString getMailAddress() const;
    // Description:
    //     Get the mail address for the command file order.
    // Return value:
    //     A RWCString with the current mail address for the 
    //     command file order.
   
    virtual void setDelRespRecep(const CHA_Resp p);
    // Description:
    //     Set the delayed response reception for the command file order.
    // Parameters:
    //     p                    the delayed response reception
    
    virtual const CHA_Resp getDelRespRecep() const;
    // Description:
    //     Get the delayed response reception for the command file order.
    // Return value:
    //     A CHA_Resp with the current delayed response reception for the 
    //     command file order.
   
    virtual void setDelRoutingCase(const CHA_RoutingCase& rc);
    // Description:
    //     Set the delayed routing case for the result of the command file order
    // Parameters:
    //     rc                   the routing case
    
    virtual CHA_RoutingCase& getDelRoutingCase();
    virtual const CHA_RoutingCase& getDelRoutingCase() const;
    // Description:
    //     Get the delayed routing case for the result of the command file order
    // Return value:
    //     A CHA_RoutingCase with the current delayed routing case for the
    //     execution result of the command file order 

    virtual void setImmRoutingCase(const CHA_RoutingCase& rc);
    // Description:
    //     Set the immediate routing case for the result of the command file order
    // Parameters:
    //     rc                   the routing case
    
    virtual CHA_RoutingCase& getImmRoutingCase();
    virtual const CHA_RoutingCase& getImmRoutingCase() const;
    // Description:
    //     Get the immediate routing case for the result of the command file order
    // Return value:
    //     A CHA_RoutingCase with the current immediate routing case for the
    //     execution result of the command file order 
    
    virtual CHA_CmdFileOrder& operator=(const CHA_CmdFileOrder& s);
    // Description:
    //     Assignmentoperator, required by TOOL
    // Parameter:
    //     s                    the original order

    virtual int operator==(const CHA_Order& s) const;
    //virtual int operator==(const CHA_CmdFileOrder& s);
    // Description:
    //     Equallity operator, required by TOOL
    // Parameter:
    //     s                    the order that is to be compared 

    virtual int operator<(const CHA_Order& s) const;
    //virtual int operator<(const CHA_CmdFileOrder& s);
    // Description:
    //     Less than operator, required by TOOL
    // Parameter:
    //     s                    the order that is to be compared 

private:
    RWCString             externalSystem;
    int                   funcBusyRetryPeriod;
    RWBoolean             stopExecutionAtNotAccep;
    RWBoolean             stopExecutionAtPartExec;
    RWBoolean             sendMailForNotAccPartExec;
    RWBoolean             sendMailForExecutionResult;
    RWCString             mailAddress;
    CHA_Resp              delayedResponseReception;
    CHA_RoutingCase       delayedRouting;
    CHA_RoutingCase       immediateRouting;
    CHA_UserInfo          userInfo;
};

#endif


