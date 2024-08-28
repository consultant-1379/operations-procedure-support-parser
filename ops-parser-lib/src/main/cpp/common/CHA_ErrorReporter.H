// RCS handling
// $Id: CHA_ErrorReporter.H,v 24.0 1995/11/28 16:54:40 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_ErrorReporter - receives and forwards internal error messages
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_ErrorReporter.H

// .COPYRIGHT
// 	COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1994
//
// 	The Copyright to the computer program(s) herein is the
// 	property of Ericsson Hewlett-Packard Telecommunications AB,
// 	Sweden.  The program(s) may be used and/or copied with the
// 	written permission from Ericsson Hewlett-Packard
// 	Telecommunications AB or in accordance with the terms and
// 	conditions stipulated in the agreement/contract under which
// 	the program(s) have been supplied.

// .DESCRIPTION
//      A CHA_ErrorReporter acts as a receiver of (textual) error
//      messages from a group of objects. When an error message
//      arrives the observers of this instace (the CHA_ModelClients) are
//      notified so they can read out the new error message, if they
//      want.
//
//      A static object of this class, named errorReporter, is created
//      at the start of the main program. This object is available to
//      the entire application and should be used for error messages
//      by the programmer rather than making new instances.
//
//      Be aware! This class and instance can only be used for
//      receiving and distributing simple error texts (strings) within
//      an application, e.g. from implementation classes to the user
//      interface. For a more complete error reporting facility the
//      standard TMOS error reporting classes should be used instead.

// DOCUMENT NO
//	190 89-CAA 134 1515

// AUTHOR 
// 	1994-02-11 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
// 	RCS revision history
//      $Log: CHA_ErrorReporter.H,v $
//      Revision 24.0  1995/11/28 16:54:40  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:40:38  17:40:38  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:43:32  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:39:15  09:39:15  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:32:12  08:32:12  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:51:26  10:51:26  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:03:39  20:03:39  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:02:03  14:02:03  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  12:57:35  12:57:35  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  14:59:06  14:59:06  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:32:33  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:01:32  14:01:32  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:12:41  16:12:41  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:44:16  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:01:08  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:27:54  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:47:20  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:21:43  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:49:03  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:43:15  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:36:08  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:50:22  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:03:21  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.5  1994/06/10  16:53:50  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.4  1994/04/22  15:48:31  ehsgrap
//      Moved errorReporter instance to CHA_LibGlobals.H,C
//
//      Revision 1.3  1994/02/28  18:01:59  ehsgrap
//      Use of CHA_Model[Client]
//
//      Revision 1.2  1994/02/22  10:20:58  ehsgrap
//      Corrections for fist compilation.
//
//      Revision 1.1  1994/02/14  08:41:30  cmcha
//      Initial revision
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
//     cap_ter(3)

//**********************************************************************

#ifndef CHA_ERRORREPORTER_H
#define CHA_ERRORREPORTER_H

#include <CHA_Model.H>

#include <rw/cstring.h>

class CHA_ErrorReporter : public CHA_Model
{
public:
    	enum cmdErrType
		{
			COMMAND_SENDER_NOT_AUTHORIZED,
			COMMAND_UNKNOWN
		};
		
    
    CHA_ErrorReporter();
    // Description:
    //     Constructor.

    ~CHA_ErrorReporter();
    // Description:
    //     Destructor.
    
    void message(const char* msg, const cmdErrType type = COMMAND_UNKNOWN);
    // Description:
    //     Sets the current error message to be reported to the
    //     observers of the CHA_ErrorReporter instance.
    // Parameters:
    //     msg			IN: a string containg the message
    //	type			IN: an enum containing the error type
    
    void message(const RWCString& msg, const cmdErrType type = COMMAND_UNKNOWN);
    // Description:
    //     Sets the current error message to be reported to the
    //     observers of the CHA_ErrorReporter instance.
    // Parameters:
    //     	msg			IN: a string containg the message
    //		type		IN: an enum containing the error type
    
    RWCString getErrorMessage() const;
    // Description:
    //     Returns the current error message. Should be used by the
    //     observers when they are notified.
    // Return value:
    //     A RWCString containing the current error message.
    
    
	cmdErrType getErrorType() const;
    // Description:
    //     Returns the current error type. Should be used by the
    //     observers when they are notified.
    // Return value:
    //     A cmdErrType containing the current error type.
    


private:
    RWCString errMsg;			 // the current error message
    cmdErrType errType;
};

#endif
