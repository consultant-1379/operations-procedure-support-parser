// RCS revision handling
// $Id: OZT_DCList.H,v 21.0 1996/09/25 14:35:10 epannh Exp $

//*****************************************************************************
//
// .NAME
//      OZT_DCList - show list of dangerous commands for an ES
// .LIBRARY 3C++
// .PAGENAME <CLASSNAME>
// .HEADER  <SSN><API>/<FBN>
// .LEFT_FOOTER Ericsson HP
// .INCLUDE <filename>

// .COPYRIGHT
//      COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB, Sweden 1994.
//      All rights reserved.
//
//      The Copyright to the computer program(s) herein is the
//      property of Ericsson Hewlett-Packard Telecommunications AB,
//      Sweden. The program(s) may be used and/or copied only with the
//      written permission from Ericsson Hewlett-Packard
//      Telecommunications AB or in accordance with the terms and
//      conditions stipulated in the agreement/contract under which
//      the program(s) have been supplied.

// .DESCRIPTION
//      Popup window showing a list of external systems, the commands
//      that are defined as dangerous for each ES and the warning text
//      for each dangerous command.
//
//      If CFD is connected to an ES, only dangerous commands for this
//      ES can be viewed. If CFD is unconnected, the user is allowed to
//      choose an ES to view commands for.

// .ERROR HANDLING
//	Errors can occur when the ES list is updated, when the DC list
//      is updated and when commands and warning texts are printed.
//      In case of error, a message is printed in the window footer.
//
//	Errors can also occur during printing of DC. A message is printed
//	in the window footer in this case too.
//
//      The error handling is specified for each method.
//
//      No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//      %EriDoc_no:%

// AUTHOR
//      1996-09-12 by EPA/T/N Ha Nguyen

// .REVISION <for public API>
//      <Revision state>
//      <Revision date>

// .REVISION <for internal header files>
//      %EriDoc_rev:%
//      %EriDoc_date:%

// CHANGES
//      RCS REVISION HISTORY
//

//      RELEASE REVISION HISTORY
//
//      REV NO  DATE            NAME                    DESCRIPTION
//      PA1     1996-09-12      H. Nguyen (EPANNH)      Created
//      <Rev no>        <Date>          <Name>          <Description>
 
// .LINKAGE
//      <link information: libraries needed and order>
 
// .SEE ALSO
//      <Related classes, (abstract) baseclasses, friend classes, ...>
 
//*****************************************************************************
 
#ifndef OZT_DCLIST_H
#define OZT_DCLIST_H
 
#include "OZT_CDFFrame.H"

#include <CHA_ModelClient.H>
#include <CHA_DCList.H>
#include <CHA_Connection.H>
#include <CHA_PrinterList.H>
#include <CHA_PrinterPipe.H>
#include <CHA_DCEntry.H>

#include <UIC_Popup.H>
#include <UIC_Panel.H>
#include <UIC_List.H>
#include <UIC_Button.H>
#include <UIC_Menu.H>
#include <UIC_MenuItem.H>
#include <UIC_ItemRow.H>
#include <UIC_TextPane.H>
#include <UIC_Message.H>

#define NARROW_LIST_W	250
#define WIDE_LIST_W	525
#define WIDE_LIST_H	200

class OZT_CDFFrame;      // forward declaration

typedef void (*OZT_Callback)(UIC_Window *);

class OZT_DCList: public UIC_Popup, public CHA_ModelClient
//#if TPF >= 400
//		public CHA_ModelClient, RWModelClient
//#else
//		public CHA_ModelClient
//#endif
{

public:

    OZT_DCList(const int nls_index,
               UIC_Window& window,
               CHA_Connection *connection);
    // Description:	
    //     Constructor.
    // Parameters:
    //     nls_index    IN: index to NLS
    //     window       IN: parent window
    //     connection   IN: ES connection

    virtual ~OZT_DCList();
    // Description:
    //	   Destructor.

    void show(const RWCString& esName);
    // Description:
    //	   Displays the window.
    // Parameters:
    //     esName        IN: the name of the ES CHA is connected to

    virtual void update(const RWCString& esName, RWBoolean connected);
    // Description:
    //	   To update the selection lists with new data when CHA is
    //     connected to an external system.
    // Parameters:
    //     esName        IN: the name of the selected external system
    //     connected     IN: if CHA is connected to an ES

    //void updateFrom(CHA_Model* model, void* esName);
#if TPF >= 400
    void updateFrom(CHA_Model *pModel, void *);
#else
    void updateFrom(RWModel *pModel, void *);
#endif
    // Description:
    //	   To receive updateFrom-calls from the model (CHA_DCList).
    // Parameters:
    //     model        IN: the model that called the method
    //     esName       IN: the name of the ES that CHA connected to

    void detachFrom(CHA_Model* model);
    // Description:
    //	   To receive detachFrom-calls from the model (CHA_DCList).
    // Parameters:
    //     model        IN: the model that called the method

protected:

    virtual void updateESList();
    // Description:
    //	   To update the ES list with new data.

    virtual void updateDCList(const RWCString& esName,
			      RWBoolean connected);
    // Description:
    //	   To update the DC list with new data.
    // Parameters:
    //     esName        IN: the name of the selected external system
    //     connected     IN: if CHA is connected to an ES

    virtual void updateWTList(const RWCString& command);
    // Description:
    //	   To update the WT list with new data.
    // Parameters:
    //     command       IN: command to show warning text for

    void listSelection(UIC_List* list, int operation, int row);
    // Description:
    //	   To handle list selections.
    // Parameters:
    //     list        IN: the list the item belongs to
    //     operation   IN: selection or deselection
    //     row         IN: row number of selected item

    void printSelected();
    // Description:
    //	   To handle a 'print selected' menu selection.

    void printAll();
    // Description:
    //	   To handle a 'print all' menu selection.

private:

    virtual void doPrintCommand(ostream& out,
				const CHA_DCEntry& entry) const;
    // Description:
    //	   Prints a command and warning text on out.
    // Parameters:
    //     out         IN: the stream to print on
    //     entry       IN: the command to print

    virtual void printError(const CHA_PrinterPipe& pPipe);
    // Description:
    //	   Prints a message in footer if a printer error has occurred.
    // Parameters:
    //     pPipe       IN: the printer pipe

    static void a_listselection(UIC_Window* wp, UIC_PanelItem* list,
 			        int operation, int row);
    // Description:
    //	   Callback function that handles a list selection.
    // Parameters:
    //     wp          IN: the window the list is placed in
    //     list        IN: the list the item belongs to
    //     operation   IN: selection or deselection
    //     row         IN: row number of selected item

    static void a_printselected(UIC_Window* wp, UIC_MenuItem* mi);
    // Description:
    //	   Callback function that handles print menu selections.
    // Parameters:
    //     wp        IN: the window the menu is placed in
    //     mi        IN: the menu item that was selected

    static void a_printall(UIC_Window* wp, UIC_MenuItem* mi);
    // Description:
    //	   Callback function that handles print menu selections.
    // Parameters:
    //     wp        IN: the window the menu is placed in
    //     mi        IN: the menu item that was selected


    UIC_MenuItem printSelectedItem;
    UIC_MenuItem printAllItem;
    UIC_Menu printMenu;                  // Print menu in button
    UIC_Button printButton;              // Print button below DC list
    UIC_List guiESList;                  // ES selection list
    UIC_List guiDCList;                  // DC selection list
    UIC_TextPane warningTextList;        // Warning text list
    UIC_Message warningText;             // Warning text list label
    UIC_ItemRow itemRow;                 // Item row in panel
    UIC_Panel DCPanel;                   // Panel in window

    CHA_Connection *pConnect;
    CHA_DCList dcList;             // DC list
    RWCString viewedES;            // The ES which commands are shown

};

#endif
