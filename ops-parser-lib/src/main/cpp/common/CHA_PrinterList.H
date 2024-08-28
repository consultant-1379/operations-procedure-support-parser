// RCS handling
// $Id: CHA_PrinterList.H,v 24.0 1995/11/28 16:55:01 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_PrinterList - A list of currently available printers
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_PrinterList.H 

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
//      A list of currently available printers.
//      It is sorted alphabetically.

// .SECTION ERROR HANDLING
//      Error messages are sent to the CHA_ErrorReporter
//      instance. Error events are also notified to all clients of
//      this model object.

// DOCUMENT NO
//      190 89-CAA 134 1515

// AUTHOR 
//      1994-05-05 by EHS/PXE Nicolas Länninge (xkknicl@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_PrinterList.H,v $
//      Revision 24.0  1995/11/28 16:55:01  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//     Revision 23.0  95/09/07  17:41:11  17:41:11  ehscama (Martin Carlsson VK/EHS/VE)
//     Made release XM2S1, ehscama.
//     
//     Revision 22.0  1995/08/01  20:43:54  cmcha
//     Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//     Revision 21.0  95/06/29  09:39:44  09:39:44  cmcha (*CHA conf. and dev. EHS/PXE)
//     Made release EC1_OZ, J Grape (EHSGRAP).
//     
//     Revision 20.0  95/06/08  08:32:32  08:32:32  cmcha (*CHA conf. and dev. EHS/PXE)
//     Made release TB5_2_OZ, J Grape (ehsgrap).
//     
//     Revision 19.1  95/04/24  13:05:00  13:05:00  ehsgrap (Jan Grape (9 9073) VK/EHS/PXE)
//     Changed returnCode to ReturnCode for consistency.
//     
//     Revision 19.0  1995/04/13  10:51:51  cmcha
//     Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//     Revision 18.0  95/03/17  20:04:06  20:04:06  cmcha (*CHA conf. and dev. EHS/PXE)
//     Made release TB51_OZ, ehscama.
//     
//     Revision 17.0  95/03/16  14:02:33  14:02:33  cmcha (*CHA conf. and dev. EHS/PXE)
//     Made release TB5_OZ, ehscama.
//     
//     Revision 16.1  95/03/14  14:10:56  14:10:56  qhsjody (Johan Dykstrom VK/EHS/PXE)
//     defaultName now returns "" if PRINTER is incorrect.
//     
//     Revision 16.0  1995/03/10  12:57:59  cmcha
//     Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//     Revision 15.0  95/03/09  14:59:54  14:59:54  cmcha (*CHA conf. and dev. EHS/PXE)
//     Made release TB6_B1C, N.Lanninge (XKKNICL).
//     
//     Revision 14.0  1995/02/25  16:32:55  cmcha
//     Made release TB4_OZ, J Grape (EHSGRAP).
//
//     Revision 13.5  95/02/15  14:02:19  14:02:19  cmcha (*CHA conf. and dev. EHS/PXE)
//     Made release CHUI_TB6, N.Lanninge (XKKNICL).
//     
//     Revision 12.0  95/02/06  16:13:13  16:13:13  cmcha (*CHA conf. and dev. EHS/PXE)
//     Made release TB3, J Grape (EHSGRAP).
//     
//     Revision 11.0  1995/01/18  14:44:53  cmcha
//     Made release PREIT, N Länninge (XKKNICL).
//
//     Revision 10.0  1994/12/22  09:01:34  cmcha
//     Made release TB2, J Grape (EHSGRAP).
//
//     Revision 9.2  1994/12/15  16:30:26  epanyc
//     defaultName() added
//
//     Revision 9.1  1994/12/08  10:27:53  ehsgrap
//     Replaced OK with OKAY
//
//     Revision 9.0  1994/10/24  21:28:24  cmcha
//     Made release E, ehscama.
//
//     Revision 8.0  1994/10/05  08:47:52  cmcha
//     Made release D, EHSCAMA.
//
//     Revision 7.0  1994/09/22  13:22:15  cmcha
//     Made release R1C, J Grape (EHSGRAP).
//
//     Revision 6.1  1994/09/21  14:18:21  xkknicl
//     CHA_Pipe.H included
//
//     Revision 6.0  1994/08/30  17:49:26  cmcha
//     Made release R1B, J Grape (EHSGRAP).
//
//     Revision 5.0  1994/08/16  07:44:00  cmcha
//     Made release R1A, J Grape (EHSGRAP).
//
//     Revision 4.0  1994/07/18  13:36:47  cmcha
//     Made release P1C, J Grape (EHSGRAP).
//
//     Revision 3.0  1994/06/23  07:51:10  cmcha
//     Made release P1B, J Grape (EHSGRAP).
//
//     Revision 2.0  1994/06/12  08:03:53  cmcha
//     Made release P1A, J Grape (EHSGRAP).
//
//     Revision 1.1  1994/05/09  11:54:43  xkknicl
//     Initial Revision
//
//
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
//	CHUI_TB61995-02-15      N.Lanninge (XKKNICL)    RCS rev 13.5
//	TB3     1995-02-06      J Grape (EHSGRAP)       RCS rev 12.0
//	PREIT   1995-01-18      N Länninge (XKKNICL)    RCS rev 11.0
//	TB2     1994-12-22      J Grape (EHSGRAP)       RCS rev 10.0
//	E       1994-10-24      ehscama                 RCS rev 9.0
//	D       1994-10-05      EHSCAMA                 RCS rev 8.0
//	R1C     1994-09-22      J Grape (EHSGRAP)       RCS rev 7.0
//	R1B     1994-08-30      J Grape (EHSGRAP)       RCS rev 6.0
//	R1A     1994-08-16      J Grape (EHSGRAP)       RCS rev 5.0
//	P1C     1994-07-18      J Grape (EHSGRAP)       RCS rev 4.0
//	P1B     1994-06-23      J Grape (EHSGRAP)       RCS rev 3.0
//	P1A     1994-06-12      J Grape (EHSGRAP)       RCS rev 2.0

// .SEE ALSO 
//      <Related classes, (abstract) baseclasses, friend classes, ...>

//**********************************************************************

#ifndef CHA_PRINTERLIST_H
#define CHA_PRINTERLIST_H

#include <rw/cstring.h>
#include <rw/tvsrtvec.h>
#include <CHA_NLSCatalog.H>
#include <CHA_Model.H>
#include <CHA_Pipe.H>

class CHA_PrinterList : public CHA_Model
{
public:

    enum ReturnCode {
	OKAY,
	NO_PRINTERS_AVAILABLE
    };
	
    CHA_PrinterList();
    // Description:
    //     Constructor.
    
    virtual ~CHA_PrinterList();
    // Description:
    //     Destructor.
    
    RWCString operator[](size_t i) const;
    // Description:
    //     Returns the entry at position i.
    // Parameters:
    //     i			IN: the index
    // Return value:
    //     RWCString	        the item
    
    RWBoolean contains(const RWCString& name) const;
    // Description:
    //     Returns true if the list contains the name of
    //     the printer in question.
    // Parameters:
    //     name			IN: the name of the Printer
    // Return value:
    //     TRUE			list contains name
    //     FALSE		list does not contain name

    RWCString defaultName() const;
    // Description:
    //     Returns the default printer name based on the environment
    //     variable $PRINTER. If the environment variable is not
    //     defined or the variable defines an invalid printer, a null 
    //     string is returned.
    // Return value:
    //     RWCString            the name of the default printer

    size_t entries() const;
    // Description:
    //     Returns the number of entries in the list.
    // Return value:
    //     size_t	        the number of entries

    RWCString first() const;
    // Description:
    //     Returns the first entry in the list.
    // Return value:
    //     RWCString	        the item

    virtual size_t index(const RWCString& name) const;
    // Description:
    //     Returns the index for an entry in the list.
    // Parameters:
    //     name			the name of the Printer

    RWBoolean isEmpty() const;
    // Description:
    //     Returns true if the list is empty.
    // Return value:
    //     TRUE			list is empty
    //     FALSE		list is not empty

    RWCString last() const;
    // Description:
    //     Returns the last entry in the list.
    // Return value:
    //     RWCString	        the item

    size_t length() const;
    // Description:
    //     Returns the number of entries in the list.
    // Return value:
    //     size_t	        the length

    virtual size_t occurrencesOf(const RWCString& name) const;
    // Description:
    //     Returns the number occurences of the name.
    // Parameters:
    //     name			IN: the name of the Printer

    ReturnCode update();
    // Description:
    //     Updates the list.
    // Return value:
    //     OK			 Successful
    //     NO_PRINTERS_AVAILABLE No printers available
    

private:

    RWTValSortedVector<RWCString> myPrinterList;
    				// the list of printer names
    CHA_NLSCatalog nlsCat;

};

#endif
