// RCS revision handling
// $Id: OZT_CommentWinModel.H,v 21.0 1996/08/23 12:42:22 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_CommentWinModel - Model of the comment window
// .LIBRARY CHOZTBIN
// .PAGENAME OZT_CommentWinModel
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
// 	This class defines the model of the comment window used by
//      the @WINDOW, @COMMENT and @WINDEND commands. User interface
//      can become the client of this model in order to receive notification
//      of any text appended to the window model.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	190 89-CAA 134 2017 Ux

// AUTHOR 
// 	1995-03-02 by Nelson Cheng (epanyc@epa.ericsson.se)


// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_CommentWinModel.H,v $
// 	Revision 21.0  1996/08/23 12:42:22  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 07:57:02  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:22:05  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:20:56  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:01:25  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:56:54  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:02:27  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:16:06  17:16:06  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.0  1995/10/07 12:00:55  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:08:33  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:24:37  09:24:37  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:01:31  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:37:25  14:37:25  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.1  95/06/28  14:29:57  14:29:57  epanyc (Nelson Cheng VK/EHS/PXE)
//      comment added
//      
//      Revision 8.0  1995/06/07  17:08:31  cmcha
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//
//      Revision 7.0  95/04/16  12:15:53  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 6.0  95/03/17  20:04:56  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 5.0  95/03/16  20:30:44  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 1.2  95/03/06  15:25:19  epanyc (Nelson Cheng VK/EHS/PXE)
//      toClear() added
//      
//      Revision 1.1  1995/03/02  21:24:16  epanyc
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
//	TB51_OZ 1995-03-17      ehscama                 RCS rev 6.0
//	TB5_OZ  1995-03-16      ehscama                 RCS rev 5.0
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	CHALIB

// .SEE ALSO 
// 	OZT_CommentWin

//*****************************************************************************


#ifndef OZT_COMMENT_WIN_MODEL_H
#define OZT_COMMENT_WIN_MODEL_H

#include <CHA_Model.H>
#include <rw/cstring.h>

class OZT_CommentWinModel : public CHA_Model
{
public:
    OZT_CommentWinModel();
    // Description
    //     Constructor

    virtual ~OZT_CommentWinModel();
    // Description
    //     Destructor

    void addText(const RWCString &textBlk, RWBoolean format);
    // Description
    //     Add new comment to the comment window.
    // Parameters:
    //     newText        IN: new text appended to this window.
 
    void beActive();
    // Description:
    //     When called, @COMMENT output to the comment window.

    void beInactive();
    // Description:
    //     When called, @COMMENT output does not go to the comment window.

    void clear();
    // Description:
    //     Clear the comment window.

    RWBoolean isActive() const;
    // Description:
    //     Tell if the window is active.

    RWBoolean toClear() const;
    // Description:
    //     Tell if the window should be cleared.

  RWBoolean toFormat() const;

private:
    RWBoolean active;
    RWBoolean toBeCleared;
    RWBoolean toFormat_;
};

#endif
