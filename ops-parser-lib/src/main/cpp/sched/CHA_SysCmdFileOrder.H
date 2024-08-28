// RCS handling
// $Id: CHA_SysCmdFileOrder.H,v 24.0 1995/11/28 16:58:55 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_SysCmdFileOrder - Handles information and functionallity for
//                           system command file orders. 
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_SysCmdFileOrder.H 

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
// 	CHA_SysCmdFileOrder.
//	A class for the specific information held about system command 
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
//      $Log: CHA_SysCmdFileOrder.H,v $
//      Revision 24.0  1995/11/28 16:58:55  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:47:06  17:47:06  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:48:32  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:45:43  09:45:43  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:36:57  08:36:57  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:56:21  10:56:21  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:08:57  20:08:57  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:10:28  14:10:28  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:03:14  13:03:14  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:08:11  15:08:11  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:37:01  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:09:34  14:09:34  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:20:23  16:20:23  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:51:47  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:06:30  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:33:07  cmcha
//      Made release E, ehscama.
//
//      Revision 8.1  1994/10/13  19:32:20  ehsgrap
//      Increased const corectness.
//
//      Revision 8.0  1994/10/05  08:53:38  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.2  1994/10/04  14:46:22  qhsmosc
//      Backed one revision
//
//      Revision 7.0  1994/09/22  13:25:54  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.1  1994/09/15  14:32:50  qhsmosc
//      Sort implemented
//
//      Revision 6.0  1994/08/30  17:53:04  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:50:05  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.1  1994/08/09  13:05:16  qhsmosc
//      Back to hierarchy
//
//      Revision 1.2  1994/07/12  06:48:36  qhsmosc
//      Preliminary tests OK
//
//      Revision 1.1  1994/07/05  07:10:32  qhsmosc
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
//      CHA_Order		Superclass

//**********************************************************************

#ifndef CHA_SYSCMDFILEORDER_H
#define CHA_SYSCMDFILEORDER_H

/*
extern "C"
{
#include <cap_ipc.h>
}
*/
#include <CHA_Order.H>
#include <rw/cstring.h>

class CHA_SysCmdFileOrder : public CHA_Order
{
public:

    CHA_SysCmdFileOrder();
    // Description:
    //     Default constructor.

    CHA_SysCmdFileOrder(const CHA_SysCmdFileOrder& s);
    // Description:
    //     Constructor to be used at copy.

    virtual ~CHA_SysCmdFileOrder();
    // Description:
    //     Destructor.
    
    virtual void setParameterList(const RWCString& p);
    // Description:
    //     Set the parameter list for the system file order.
    // Parameters:
    //     p                    the parameter list
    
    virtual const RWCString& getParameterList() const;
    // Description:
    //     Get the parameter list for the system file order.
    // Return value:
    //     A RWCString with the current parameter list for the
    //     system file order. 
    
    virtual void setMessagesToMail(const RWBoolean p);
    // Description:
    //     Set the messages to mail flag for the system file order.
    // Parameters:
    //     p                    the messages to mail flag
    
    virtual const RWBoolean getMessagesToMail () const;
    // Description:
    //     Get the messages to mail flag for the system file order.
    // Return value:
    //     A CHA_MessToMail with the current flag for messages to mail
    //     for the system file order.
    
    virtual CHA_SysCmdFileOrder& operator=(const CHA_SysCmdFileOrder& s);
    // Description:
    //     Assignmentoperator, required by TOOL
    // Parameter:
    //     s                    the original order

    virtual int operator==(const CHA_Order& s) const;
    //virtual int operator==(const CHA_SysCmdFileOrder& s);
    // Description:
    //     Equallity operator, required by TOOL
    // Parameter:
    //     s                    the order that is to be compared 

    virtual int operator<(const CHA_Order& s) const;
    //virtual int operator<(const CHA_SysCmdFileOrder& s);
    // Description:
    //     Less than operator, required by TOOL
    // Parameter:
    //     s                    the order that is to be compared 

private:
    RWCString             parameterList;
    RWBoolean             messagesToMail;
};

#endif


