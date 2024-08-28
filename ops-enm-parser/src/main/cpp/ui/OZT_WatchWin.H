// RCS revision handling
// $Id: OZT_WatchWin.H,v 21.0 1996/08/23 12:46:54 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_WatchWin - Popup containg a list of variables and contents
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
// 	Creates a popup window containing a list of variable names and
//      contents. The list is kept up to date using the model/view
//      architecture.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	%EriDoc_no:%

// AUTHOR 
// 	1994/12/06  by ETL/XN/DSN  etlnei (Neil Harding)

// .REVISION <for public API>
//	<Revision state>
//	<Revision date>	  	

// .REVISION <for internal header files>
//	%EriDoc_rev:%
//	%EriDoc_date:%  	

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_WatchWin.H,v $
// 	Revision 21.0  1996/08/23 12:46:54  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 08:01:05  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:24:03  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:25:21  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:07:03  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:59:49  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.1  1996/01/08 18:29:03  ehsjasa
// 	Conditionalized whether RWModel* or CHA_Model* should be used
// 	depending on which version of CHALIB was used (TPF 2 o TPF 4).
//
// 	Revision 15.0  1995/11/29 02:04:58  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:20:50  17:20:50  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.0  1995/10/07 12:04:09  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:13:18  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:27:50  09:27:50  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:06:31  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:41:42  14:41:42  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.1  95/06/15  08:24:13  08:24:13  etlnei (Neil Harding VK/EHS/PXE)
//      *** empty log message ***
//      
//      Revision 8.0  1995/06/07  17:13:06  cmcha
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//
//      Revision 7.1  95/05/18  11:07:18  11:07:18  etlnei (Neil Harding VK/EHS/PXE)
//      *** empty log message ***
//      
//      Revision 7.0  1995/04/16  12:19:32  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.0  95/03/17  20:08:40  20:08:40  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 5.0  95/03/16  20:33:50  20:33:50  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 4.1  95/03/09  09:25:06  09:25:06  etlnei (Neil Harding VK/EHS/PXE)
//      checked in for other people to compile
//      
//      Revision 4.0  1995/02/23  21:48:15  cmcha
//      Made release TB4, J Grape (EHSGRAP).
//
//      Revision 3.0  95/02/06  21:02:08  21:02:08  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 2.5  95/01/18  13:45:44  13:45:44  etlnei (Neil Harding VK/EHS/PXE)
//      added space tolerance and stuff
//      
//      Revision 2.4  1995/01/16  10:13:25  etlnei
//      *** empty log message ***
//
//      Revision 2.3  1994/12/21  16:16:30  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 2.0  94/12/21  13:55:04  13:55:04  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//      
//      Revision 1.2  1994/12/12  11:15:57  etlnei
//      checked in for nelson to compile
//
//      Revision 1.1  1994/12/06  11:41:18  etlnei
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


#ifndef OZT_WATCHWIN_H 
#define OZT_WATCHWIN_H

#include <rw/cstring.h>
#include "OZT_CDFFrame.H"
#include <UIC_Button.H>
#include <UIC_ItemRow.H>
#include <UIC_Panel.H>
#include <UIC_Popup.H>
#include <UIC_TextField.H>
#include <UIC_List.H>
#include <OZT_VarStore.H>
#include <OZT_SourceMgr.H>
#include <CHA_ModelClient.H>
#include "OZT_CDFDef.H"


class  OZT_WatchWin : public UIC_Popup, public CHA_ModelClient
{

public:

    OZT_WatchWin(const int nls_index, UIC_Window& window, OZT_SourceMgr *smgr);
    // Description:
    //     Constructor. Opens a window containing a list of variables and
    //     their contents 
    // Parameters:
    //     nls_index       NLS string for the popup window
    //     window          parent window
    //     smgr            source manager


    ~OZT_WatchWin();
    // Description:
    //     Destructor.

    
protected:

private:
    OZT_SourceMgr    *source_mgr;

    UIC_Button       add_button;
    UIC_Button       remove_button;
    UIC_ItemRow      watch_row;
    UIC_List         watch_list;
    UIC_Panel        watch_panel;
    UIC_TextField    watch_textfield;

    static void a_watch_add (UIC_Window* wp, UIC_PanelItem* pi);
    static void a_watch_remove (UIC_Window* wp, UIC_PanelItem* pi);
    static void a_list (UIC_Window* wp, UIC_PanelItem* pi, int mode, int);

    void do_watch_add (void);
    void do_watch_remove (void);
    void do_list (UIC_PanelItem* pi, int mode);

#if TPF >= 400  
    void updateFrom(CHA_Model* pModel, void* pData);
#else
    void updateFrom(RWModel* pModel, void* pData);    
#endif

    void detachFrom(CHA_Model* model);
    RWCString list_entry (OZT_VarStore *var_store, RWCString var_in_list);
};

#endif
