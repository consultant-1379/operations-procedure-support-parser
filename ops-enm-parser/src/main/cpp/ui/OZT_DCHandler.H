#ifdef OZT_PROTOTYPE

// RCS revision handling
// $Id: OZT_DCHandler.H,v 21.0 1996/08/23 12:46:28 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	<ClassName> - <Short description of the class>
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
// 	<General description of the class>

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	%EriDoc_no:%

// AUTHOR 
// 	<Date> by <Dept> <Name>

// .REVISION <for public API>
//	<Revision state>
//	<Revision date>	  	

// .REVISION <for internal header files>
//	%EriDoc_rev:%
//	%EriDoc_date:%  	

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_DCHandler.H,v $
// 	Revision 21.0  1996/08/23 12:46:28  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 08:00:45  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:23:51  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.2  1996/03/11 13:05:09  ehsjasa
// 	Changed PROTOTYPE to OZT_PROTOTYPE.
//
// 	Revision 18.1  1996/03/11 12:38:03  ehsjasa
// 	Two updateFrom() methods needed with the CHALIB for TPF 4.
//
// 	Revision 18.0  1996/03/01 12:24:57  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:06:31  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:59:32  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 1.2  1996/01/08 18:29:03  ehsjasa
// 	Conditionalized whether RWModel* or CHA_Model* should be used
// 	depending on which version of CHALIB was used (TPF 2 o TPF 4).
//
// 	Revision 1.1  1995/12/08 16:09:42  epanyc
// 	Initial revision
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
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	<link information: libraries needed and order>

// .SEE ALSO 
// 	<Related classes, (abstract) baseclasses, friend classes, ...>

//*****************************************************************************


#ifndef OZT_DC_HANDLER_H
#define OZT_DC_HANDLER_H

#include <CHA_ModelClient.H>
#include <CHA_DCList.H>
#include <CHA_DCCommandParser.H>
#include <CHA_Connection.H>
#include <OLDT_Handler.H>
#include <rw/cstring.h>

class OZT_CDFFrame;  // forward declaration

class OZT_DCHandler:
#if TPF >= 400
                      public CHA_ModelClient,
                      public RWModelClient
#else
                      public CHA_ModelClient
#endif

{
public:
    OZT_DCHandler(OZT_CDFFrame* mainFrame,
                  CHA_Connection* connection);

    virtual ~OZT_DCHandler();

    // The change in CHALIB for TPF 4, where CHA_Model no longer
    // inherits from RWmodel causes us to declare/use two
    // updateFrom() methods.
    void updateFrom(CHA_Model* pModel, void* pData); // for CHA
    void updateFrom(RWModel* pModel, void* pData);   // for OLDT

    void detachFrom(CHA_Model* pModel);

    RWBoolean checkProceed(RWCString cmd);


    static RWBoolean proceed(RWCString cmd);

    static OZT_DCHandler* theInstance;

private:

    enum {CONFIRM, INHIBIT, DOC};
    enum State {IDLE, WAIT_FOR_DOC};

    int getUsrChoice(const CHA_DCEntry &entry, 
                     RWBoolean beep,
                     RWBoolean showDocButton);
    void fetchDoc(const RWCString &cmd);
    void updateDCList();

    OZT_CDFFrame*       pParentFrame;
    CHA_DCList          dcList;
    CHA_DCCommandParser dcParser;
    CHA_Connection*     pConnection;
    OLDT_Handler*       pOLDTHandler;
    State               myState;

    RWCString connectedES;
    RWCString currentES;
};

#endif

#endif
