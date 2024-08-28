// RCS handling
// $Id: CHA_OztCmdFileOrder.H,v 24.2 1996/01/17 16:53:07 ehscama Exp $

//**********************************************************************
// 
// .NAME    CHA_OztCmdFileOrder - Handles information and functionality for
//                                command file orders to be processed by 
//				  the Command file developer (OZTERM)
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_OztCmdFileOrder.H 

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
// 	CHA_OztCmdFileOrder.
//	A class for the specific information held about command 
//      file orders, to be processed by the Command file developer, 
//	and functionality only applicable for such orders.
//      The application program can add, delete and change orders.

// .SECTION ERROR HANDLING
//      <General rules for error handling>

// DOCUMENT NO
//      190 89-CAA 134 1516

// AUTHOR 
//      1995-02-15  EHS/PXE Christer Eklund (qhskred@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28
// CHANGES
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
//

// .SEE ALSO 
//      CHA_Order		Superclass

//**********************************************************************

#ifndef CHA_OZTCMDFILEORDER_H
#define CHA_OZTCMDFILEORDER_H

/*/extern "C"
{
#include <cap_ipc.h>
}*/

#include <CHA_Order.H>
#include <CHA_UserInfo.H>
#include <rw/cstring.h>

class CHA_OztCmdFileOrder : public CHA_Order
{
public:

    CHA_OztCmdFileOrder();
    // Description:
    //     Default constructor.

    CHA_OztCmdFileOrder(const CHA_OztCmdFileOrder& s);
    // Description:
    //     Constructor to be used at copy.

    virtual ~CHA_OztCmdFileOrder();
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
    
    virtual void setExitMessageMailAddress(const RWCString p);
    // Description:
    //     Set the mail address for exit message of the command file order.
    // Parameters:
    //     p                    the mail address
    
    virtual const RWCString getExitMessageMailAddress() const;
    // Description:
    //     Get the mail address for recieving exit message from the 
    //	   command file order.
    // Return value:
    //     A RWCString with the current mail address for recieving 
    //     exit message from command file order.
   
    virtual void setStartLabel(const RWCString& ol);
    // Description:
    //     Set the startlabel of the order.
    // Parameters:
    //     ol                    the startlabel of the order
    
    virtual const RWCString& getStartLabel() const;
    // Description:
    //     Get the startlabel of the order.
    // Return value:
    //     A RWCString with the current startlabel of the order. 

    virtual void setDisplayName(const RWCString& od);
    // Description:
    //     Set the display of the order.
    // Parameters:
    //     od                    the Display of the order
    
    virtual const RWCString& getDisplayName() const;
    // Description:
    //     Get the display of the order.
    // Return value:
    //     A RWCString with the current display of the order. 
   
    virtual void setDisplayOn(RWBoolean od);
    // Description:
    //     Set the if the order shall run gui or nui.
    // Parameters:
    //     od                    True or False
    
    virtual const RWBoolean isDisplayOn() const;
    // Description:
    //     Checks if display is on or off.
    // Return value:
    //     A RWBoolean with the current status. 

   virtual void setOutputMailaddress(const RWCString& om);
    // Description:
    //     Set the output routing mail address of the order.
    // Parameters:
    //     om                    the output routing mail address of the order

    virtual const RWCString& getOutputMailaddress() const;
    // Description:
    //     Get the output routing mail address of the order.
    // Return value:
    //   A RWCString with the current output routing mail address of the order.

   virtual void setOutputFile(const RWCString& of);
    // Description:
    //     Set the output routing file of the order.
    // Parameters:
    //     of                    the output routing file of the order

    virtual const RWCString& getOutputFile() const;
    // Description:
    //     Get the output routing file of the order.
    // Return value:
    //   A RWCString with the current output routing file of the order.

   virtual void setOutputPrinter(const RWCString& of);
    // Description:
    //     Set the output routing printer of the order.
    // Parameters:
    //     of                    the output routing printer of the order

    virtual const RWCString& getOutputPrinter() const;
    // Description:
    //     Get the output routing printer of the order.
    // Return value:
    //   A RWCString with the current output routing printer of the order.

    virtual CHA_OztCmdFileOrder& operator=(const CHA_OztCmdFileOrder& s);
    // Description:
    //     Assignmentoperator, required by TOOL
    // Parameter:
    //     s                    the original order

    virtual int operator==(const CHA_Order& s) const;
    //virtual int operator==(const CHA_OztCmdFileOrder& s);
    // Description:
    //     Equallity operator, required by TOOL
    // Parameter:
    //     s                    the order that is to be compared 

    virtual int operator<(const CHA_Order& s) const;
    //virtual int operator<(const CHA_OztCmdFileOrder& s);
    // Description:
    //     Less than operator, required by TOOL
    // Parameter:
    //     s                    the order that is to be compared 

private:
    RWCString             externalSystem;
    RWCString             exitMailAddress;
    CHA_UserInfo          userInfo;

    RWCString             OZTLabel;
    RWCString             OZTDisplay;
    RWBoolean             OZTDisplayOn;

    RWCString             outputMailAddress;
    RWCString             outputFile;
    RWCString             outputPrinter;
};

#endif


