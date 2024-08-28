// RCS revision handling
// $Id: OZT_ESBrowser.H,v 21.0 1996/08/23 12:46:33 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_ESBrowser - External System browser
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
//      systems (network elements).

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	%EriDoc_no:%

// AUTHOR 
// 	1994/12/13  by ETL/XN/DSN  etlnei

// .REVISION <for public API>
//	<Revision state>
//	<Revision date>	  	

// .REVISION <for internal header files>
//	%EriDoc_rev:%
//	%EriDoc_date:%  	

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_ESBrowser.H,v $
// 	Revision 21.0  1996/08/23 12:46:33  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 08:00:48  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:23:53  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:25:02  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:06:38  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:59:35  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:04:46  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:20:33  17:20:33  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.0  1995/10/07 12:03:52  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:12:55  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:27:33  09:27:33  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:06:11  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:41:23  14:41:23  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.0  95/06/07  17:12:48  17:12:48  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 7.1  95/05/18  11:07:18  11:07:18  etlnei (Neil Harding VK/EHS/PXE)
//      *** empty log message ***
//      
//      Revision 7.0  1995/04/16  12:19:13  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.1  95/04/10  14:56:24  14:56:24  etlnei (Neil Harding VK/EHS/PXE)
//      checked in to measure performance
//      
//      Revision 6.0  1995/03/17  20:08:20  cmcha
//      Made release TB51_OZ, ehscama.
//
//      Revision 5.0  95/03/16  20:33:35  20:33:35  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 4.0  95/02/23  21:48:01  21:48:01  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB4, J Grape (EHSGRAP).
//      
//      Revision 3.0  95/02/06  21:01:50  21:01:50  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 2.3  94/12/21  16:16:11  16:16:11  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//      
//      Revision 2.0  94/12/21  13:54:51  13:54:51  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//      
//      Revision 1.1  1994/12/13  11:45:00  etlnei
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
//	TB4     1995-02-23      J Grape (EHSGRAP)       RCS rev 4.0
//	TB3     1995-02-06      J Grape (EHSGRAP)       RCS rev 3.0
//	TB2     1994-12-21      J Grape (EHSGRAP)       RCS rev 2.3
//	TB2     1994-12-21      J Grape (EHSGRAP)       RCS rev 2.0
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	<link information: libraries needed and order>

// .SEE ALSO 
// 	<Related classes, (abstract) baseclasses, friend classes, ...>

//*****************************************************************************


#ifndef OZT_ESLIST_H 
#define OZT_ESLIST_H

#include <UIC_Button.H>
#include <UIC_Panel.H>
#include <UIC_Popup.H>
#include <UIC_TextField.H>
#include <UIC_List.H>
#include <CHA_EsList.H>
#include "OZT_CDFDef.H"


typedef void (*OZT_Callback)(UIC_Window *);

class  OZT_ESBrowser : public UIC_Popup
{

public:

    OZT_ESBrowser(const int nls_index, UIC_Window& window,
                  const int button_index, OZT_Callback callback);
    // Description:
    //     Constructor. Opens a window containing a list of available
    //     External systems.
    // Parameters:
    //     nls_index       NLS string for the popup window
    //     window          parent window
    //     nls_index       NLS string for the button
    //     callback        callback routine for when an ES is entered


    ~OZT_ESBrowser();
    // Description:
    //     Destructor.

    void fill_list(void);
    // Description:
    //     fills the list with all the available external system names

    RWCString get_value(void);
    // Description:
    //     Get the string that is in the textfield
    // Return Value
    //     The string


    
protected:

private:
    CHA_EsList       cha_es_list;

    UIC_Panel        es_panel;
    UIC_TextField    es_textfield;
    UIC_List         es_list;
    UIC_Button       es_button;
    OZT_Callback     button_callback;

    static void a_es_button (UIC_Window* wp, UIC_PanelItem* pi);
    static void a_list (UIC_Window* wp, UIC_PanelItem* pi, int mode, int);

    void do_es_button (void);
    void do_list (UIC_PanelItem* pi, int mode);
    void showNotify(void);

};

#endif
