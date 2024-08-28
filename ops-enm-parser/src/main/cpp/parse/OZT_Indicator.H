// RCS revision handling
// $Id: OZT_Indicator.H,v 21.0 1996/08/23 12:42:44 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_Indicator - Model for run-time progress indicator
// .LIBRARY CHOZTBIN
// .PAGENAME OZT_Indicator
// .LEFT_FOOTER Ericsson HP

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
// 	OZT_Indicator acts as a model for showing the progress of 
//      some long duration commands such as @DELAY

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	190 89-CAA 134 2016

// AUTHOR 
// 	1995-06-19 by Nelson Cheng (epanyc@epa.ericsson.se)

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_Indicator.H,v $
// 	Revision 21.0  1996/08/23 12:42:44  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 07:57:23  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:22:16  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:21:17  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:01:52  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:57:10  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.1  1996/01/08 18:29:03  ehsjasa
// 	Conditionalized whether RWModel* or CHA_Model* should be used
// 	depending on which version of CHALIB was used (TPF 2 o TPF 4).
//
// 	Revision 15.0  1995/11/29 02:02:42  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:16:59  17:16:59  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.1  1995/11/16 16:15:01  epanyc
// 	new functions are added for fixing the TR about left over messages
//
//      Revision 13.0  1995/10/07  12:01:15  ehsjasa
//      Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:08:59  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:24:56  09:24:56  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:02:02  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:37:46  14:37:46  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 1.2  95/06/28  14:31:06  14:31:06  epanyc (Nelson Cheng VK/EHS/PXE)
//      comment added
//      
//      Revision 1.1  1995/06/19  16:14:17  epanyc
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
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	<link information: libraries needed and order>

// .SEE ALSO 
// 	<Related classes, (abstract) baseclasses, friend classes, ...>

//*****************************************************************************


#ifndef OZT_INDICATOR_H
#define OZT_INDICATOR_H

#include <CHA_Model.H>
#include <CHA_ModelClient.H>
#include <rw/cstring.h>


class OZT_Indicator: public CHA_Model, public CHA_ModelClient {
public:
    OZT_Indicator();
    // Description:
    //    Constructor

    virtual ~OZT_Indicator();
    // Description:
    //    Destructor

    void setMsg(const RWCString &msg);
    // Description:
    //    Set the current message to msg

    RWCString getMsg() const;
    // Description:
    //    Get the current message shown

    void clearMsg();
    // Description:
    //    Clear the current message

#if TPF >= 400  
    virtual void updateFrom(CHA_Model* pModel, void*);
#else
    virtual void updateFrom(RWModel* pModel, void*);
#endif
    //  Description:
    //       

    void detachFrom(CHA_Model* pModel);
    // Description
    //    Receive detach message from it model

protected:
    RWCString  currentMsg;
};

#endif
