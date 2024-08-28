// RCS revision handling
// $Id: OZT_NEIdentification.H,v 21.0 1996/08/23 12:46:39 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME    OZT_NEIdentification - shows which NE CFD is connected to.
// .LIBRARY
// .HEADER
// .INCLUDE OZT_NEIdentification.H

// .COPYRIGHT
//	COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB, Sweden 1994.
// 	All rights reserved.
//
//	The Copyright to the computer program(s) herein is the
//	property of Ericsson Hewlett-Packard Telecommunications AB,
//	Sweden. The program(s) may be used and/or copied only with the
//	written permission from Ericsson Hewlett-Packard
//	Telecommunications AB or in accordance with the terms and
//	conditions stipulated in the agreement/contract under which
//	the program(s) have been supplied.

// .DESCRIPTION 
// 	This class is for showing connection status. The status is shown
//      using a bitmap and two text labels. The bitmap shows if CFD is
//      connected to a network element or not and the text labels show
//      which NE CFD is connected to. OZTNEIdentification is a view to
//      the connection object and is made aware of state changes in the
//      connection.

// .ERROR HANDLING
//	No error handling in this class.

// DOCUMENT NO
//	

// AUTHOR 
// 	1995-03-21 by EHS/PXE Johan Dykström (qhsjody@ehs.ericsson.se)

// .REVISION
//	B_POINT
//	1996-08-23

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_NEIdentification.H,v $
// 	Revision 21.0  1996/08/23 12:46:39  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 08:00:53  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:23:56  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:25:07  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:06:44  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:59:39  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.1  1996/01/08 18:29:03  ehsjasa
// 	Conditionalized whether RWModel* or CHA_Model* should be used
// 	depending on which version of CHALIB was used (TPF 2 o TPF 4).
//
// 	Revision 15.0  1995/11/29 02:04:49  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:20:37  17:20:37  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.0  1995/10/07 12:03:57  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:13:00  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:27:38  09:27:38  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:06:16  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:41:29  14:41:29  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.0  95/06/07  17:12:54  17:12:54  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 7.0  95/04/16  12:19:19  12:19:19  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 1.1  95/03/27  13:15:43  13:15:43  qhsjody (Johan Dykstrom VK/EHS/PXE)
//      Initial revision
//      
//
//	RELEASE REVISION HISTORY
//
//	REV NO	DATE		NAME			DESCRIPTION
//	B_POINT 1996-08-23      J Grape (EHSGRAP)       RCS rev 21.0
//	EC8_OZ  1996-07-10      David Terry epa.epadmt  RCS rev 20.0
//	POW_TB611996-03-19      J Sandquist (ehsjasa)   RCS rev 19.0
//	EC7_OZ  1996-03-01      J Sandquist (ehsjasa)   RCS rev 18.0
//	EC6_OZ  1996-01-17      J Sandquist (ehsjasa)   RCS rev 17.0
//	POW_TB411996-01-08      J Sandquist (ehsjasa)   RCS rev 16.0
//	TB53_OZ 1995-11-29      J Grape (EHSGRAP)       RCS rev 15.0
//	POW_TB3 1995-11-20      J Sandquist (EHSJASA)   RCS rev 14.0
//	PRE_XM221995-10-07      J Sandquist (EHSJASA)   RCS rev 13.0
//	EC5_OZ  1995-09-22      J Sandquist (EHSJASA)   RCS rev 12.0
//	EC4_OZ  1995-09-14      J Sandquist (EHSJASA)   RCS rev 11.0
//	EC3_OZ  1995-08-02      J Sandquist (EHSJASA)   RCS rev 10.0
//	EC2_OZ  1995-06-29      J Grape (EHSGRAP)       RCS rev 9.0
//	TB5_2_OZ1995-06-07      J Grape (EHSGRAP)       RCS rev 8.0
//	TB5_1_OZ1995-04-16      J Grape (EHSGRAP)       RCS rev 7.0
//

// .SEE ALSO 
// 	UIC_Image, UIC_Message

//*****************************************************************************

#ifndef OZT_NEIDENTIFICATION_H
#define OZT_NEIDENTIFICATION_H

#include	<UIC_ItemRow.H>
#include	<UIC_Image.H>
#include	<UIC_Message.H>
#include	<CHA_ModelClient.H>
#include	<CHA_Connection.H>

//*****************************************************************************

class OZT_NEIdentification : public UIC_ItemRow, public CHA_ModelClient
{

public:

    OZT_NEIdentification();
    // Description:
    //     Constructor.

    ~OZT_NEIdentification();
    // Description:
    //     Destructor.

    void setConnection(CHA_Connection* conn);
    // Description:
    //     
    // Parameters:
    //     conn          IN: A pointer to the CHA_Connection

    void xConstruct(int x, int& ypos, UIC_PanelItem* selfPt);
    // Description:
    //     Creates the XView UIC_PanelItems and positions them properly
    //     in the Panel they belong to.
    // Parameters:
    //     x            IN: the x-coordinate of the UIC_ItemRow
    //     y        IN/OUT: the y-coordinate of the UIC_ItemRow. Will be
    //                      set to the lower left corner of the UIC_ItemRow.
    //     selfPt       IN: Pointer to object which will be used for the SELF
    //                      key. If not set then than <this> will be used.

#if TPF >= 400  
    virtual void updateFrom(CHA_Model* pModel, void* pData);
#else
    virtual void updateFrom(RWModel* pModel, void* pData);
#endif
    // Description:
    //	   To receive updateFrom-calls from the model (CHA_Connection).
    // Parameters:
    //     pModel        IN: the model that called the method
    //     pData        IN: additional info (should not be used)

    void detachFrom(CHA_Model* model);
    // Description:
    //	   To receive detachFrom-calls from the model (CHA_Connection).
    // Parameters:
    //     model        IN: the model that called the method

private:

    UIC_Image       image;              // Image of NE
    UIC_Message     name;               // NE name
    UIC_Message     type;               // NE type
    UIC_ItemRow     messages;           // Row of UIC_Messages

    CHA_Connection* connection;         // Pointer to model

};

#endif
