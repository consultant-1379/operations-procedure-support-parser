// RCS revision handling
// $Id: OZT_OutputProps.H,v 21.0 1996/09/25 14:47:49 epannh Exp $

//*****************************************************************************
// 
// .NAME
//  	OZT_OutputProps - Output Properties window
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
// 	Creates a popup window used for setting routing output properties.

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	%EriDoc_no:%

// AUTHOR 
// 	1996-09-04 by EPA/T/N Ha Nguyen

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
//	PA1     1996-09-04      H Nguyen (EPANNH)       Created
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	<link information: libraries needed and order>

// .SEE ALSO 
// 	<Related classes, (abstract) baseclasses, friend classes, ...>

//*****************************************************************************


#ifndef OZT_OUTPUTPROPS_H 
#define OZT_OUTPUTPROPS_H

//***********************************************************
// File included to get around macro problems in OZT_CDFFrame
// because of the forward declaration.
#include <rw/rwtime.h>
#include <rw/rwdate.h>
//***********************************************************

#include <UIC_Button.H>
#include <UIC_Panel.H>
#include <UIC_ItemRow.H>
#include <UIC_Popup.H>
#include <UIC_FieldsOutputDevice.H>
#include <OZT_CDFFrame.H>
#include <CHA_MailLogger.H>
#include <CHA_FileLogger.H>
#include <CHA_PrinterLogger.H>
#include <CHA_PrinterList.H>
#include <rw/cstring.h>
#include <sys/types.h>

class OZT_CDFFrame;

const int FILENAME_VISIBLE_LEN = 30;
const int FILENAME_STORED_LEN = 255;
const int MAIL_ADDR_VISIBLE_LEN = 30;
const int MAIL_ADDR_STORED_LEN = 255;

typedef void (*OZT_Callback)(UIC_Window *);

class  OZT_OutputProps : public UIC_Popup
{

public:

    OZT_OutputProps(const int nls_index, UIC_Window& window);
    // Description:
    //     Constructs a properties window for the Ozterm debugger 
    // Parameters:
    //     nls_index       NLS string for the popup window title
    //     window          parent window

    ~OZT_OutputProps();
    // Description:
    //     Destructor.

    // OPS++
    void updateFileLogger(void);
    // Description:
    //     Update the file destination where results are logged.

    void updatePrinterLogger(void);
    // Description:
    //     Update the printer destination where results are printed to.

    void updateMailLogger(void);
    // Description:
    //     Update the mail destination where results are printed to.
    // OPS++ - End


protected:

private:
    UIC_Button              apply_button;
    UIC_Button              reset_button;
    UIC_ItemRow             button_row;
    UIC_Panel               destination_panel;
    UIC_FieldsOutputDevice  output_device;

    RWBoolean fileDest;
    RWBoolean printerDest;
    RWBoolean mailDest;

    RWCString fileName;
    RWCString printerName;
    RWCString mailAddress;

    OZT_CDFFrame        *cfd;
    CHA_MailLogger      *pMLogger;
    CHA_FileLogger      *pFLogger;
    CHA_PrinterLogger   *pPLogger;
    CHA_PrinterList     printerList;

    struct passwd       *pwdStr;

    void do_apply();
    // Description:
    //     The user has pressed the "Apply" button, the specified Output
    //     destinations will be saved.

    void do_reset();
    // Description:
    //     The user has pressed the "Reset" button, the Output destinations
    //     will be reversed to the destinations last applied.


    static void a_apply(UIC_Window* wp, UIC_PanelItem* pi);
    static void a_reset(UIC_Window* wp, UIC_PanelItem* pi);
};

#endif
