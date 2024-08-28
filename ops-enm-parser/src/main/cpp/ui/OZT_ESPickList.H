// RCS revision handling
// $Id: OZT_ESPickList.H,v 21.0 1996/09/25 14:38:47 epannh Exp $

//*****************************************************************************
// 
// .NAME
//  	OZT_ESPickList - External System pick list
// .LIBRARY 3C++
// .PAGENAME <CLASSNAME>
// .HEADER  <SSN><API>/<FBN> 
// .LEFT_FOOTER Ericsson HP
// .INCLUDE <filename>

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
// 	Creates a popup window containing a list of all available external
//      systems (network elements) where each one can be selected.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	%EriDoc_no:%

// AUTHOR 
// 	1996/09/19  by EPA/T/N  Ha Nguyen

// .REVISION <for public API>
//	<Revision state>
//	<Revision date>	  	

// .REVISION <for internal header files>
//	%EriDoc_rev:%
//	%EriDoc_date:%  	

// CHANGES
// 	RCS REVISION HISTORY
//
//
//	RELEASE REVISION HISTORY
//
//	REV NO	DATE		NAME			DESCRIPTION
//	PA1     1996-09-19      H. Nguyen (EPANNH)      Created
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	<link information: libraries needed and order>

// .SEE ALSO 
// 	<Related classes, (abstract) baseclasses, friend classes, ...>

//*****************************************************************************


#ifndef OZT_ESPICKLIST_H 
#define OZT_ESPICKLIST_H

#include <UIC_MOPickListField.H>
#include <CHA_EsList.H>
#include "OZT_CDFDef.H"

typedef int (*C_TEXTFIELD_CB) (UIC_Window* win, UIC_PanelItem* pi);

class  OZT_ESPickList : public UIC_MOPickListField
{

public:

    OZT_ESPickList(const int      nls_index,
                   UIC_Window&    window,
                   int            charLen,
                   int            storedLen = -1,
                   bool           entered = FALSE,
                   C_TEXTFIELD_CB callBackFunc = 0,
                   const char*    defaultLabel = 0);
    // Description:
    //     Create a picklist containing a list of available External
    //     Systems.
    // Parameters:
    //     nls_index       NLS index for the field label.
    //     window          parent window for the picklist popup.
    //     charLen         length in characters of the field.
    //     storedLen       number of characters stored. If -1 the value of
    //                     charLen will be used.
    //     centered        TRUE if field shouls be centered in panel.
    //     callBackFunc    Call back function to call when text has been
    //                     entered into the field.
    //     defaultLabel    Default text to use if NLS label is not found.


    ~OZT_ESPickList();
    // Description:
    //     Destructor.

    RWCString getESName(void);
    // Description:
    //     Get the ES name that is in the textfield
    // Return Value
    //     The string

    void fillESList(CHA_EsList::NeSource source = CHA_EsList::IMHAPI);
    // Description:
    //     Fills the list with all the available external system names

  void showESList(void);
  // Description:
  //     Show the pick list popup.
    
protected:

private:

    CHA_EsList       esList;
};

#endif
