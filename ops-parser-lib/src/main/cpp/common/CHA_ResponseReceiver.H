// RCS handling
// $Id: CHA_ResponseReceiver.H,v 22.0.1.3 1996/10/29 22:48:30 ehsgrap Exp $

//**********************************************************************
// 
// .NAME    CHA_ResponseReceiver - receives and forwards responses
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_ResponseReceiver.H

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
//      The class CHA_ResponseReceiver is a base class for all objects
//      that receives responses from outside and forwards them to the
//      routing targets.

//      A response receiver is observed by its routing targets and
//      shall notify them when a new response buffer has arrived. In
//      the notification message a pointer to the most recent buffer
//      is availabe. A response receiver is observing a
//      CHA_IOSupervisor that will tell the receiver when there is
//      something to get on its input channel. Typically a response
//      receiver should work with only one response at a time
//      (containing of several buffers).

//      The main purpose of this class is to provide a unified
//      interface towards the routing targets.

// .SECTION ERROR HANDLING
//      When an error occurs a message should be is sent to the
//      CHA_ErrorReporter instance, but that is up to the implementing
//      sub class.

// DOCUMENT NO
//	190 89-CAA 134 1515

// AUTHOR 
// 	1994-02-15 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION
//	XM2S1
//	1995-09-07

// CHANGES
// 	RCS revision history
//      $Log: CHA_ResponseReceiver.H,v $
//      Revision 22.0.1.3  1996/10/29 22:48:30  ehsgrap
//      Added isLastInSequence() method.
//
//      Revision 22.0.1.2  1996/07/23 09:26:06  emejome
//      Added method reset().
//
//      Revision 22.0.1.1  1995/09/10 21:32:21  etosad
//      A lot of changes!
//
//      Revision 23.0  1995/09/07  17:41:23  ehscama
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:44:00  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:39:53  09:39:53  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:32:38  08:32:38  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:51:59  10:51:59  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:04:14  20:04:14  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:02:41  14:02:41  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  12:58:08  12:58:08  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:00:06  15:00:06  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:33:02  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:02:30  14:02:30  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:13:21  16:13:21  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:45:02  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:01:44  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:28:30  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:48:00  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:22:23  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:49:30  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:44:15  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:36:57  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:51:28  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:04:00  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.5  1994/06/01  12:00:21  ehsgrap
//      Introduced the friend operator==
//
//      Revision 1.4  1994/03/08  16:18:04  ehsgrap
//      fixed spelling miss
//
//      Revision 1.3  1994/02/28  18:00:14  ehsgrap
//      Use of CHA_Model[Client]
//
//      Revision 1.2  1994/02/22  10:22:24  ehsgrap
//      Corrections for first compilation.
//
//      Revision 1.1  1994/02/14  08:41:36  cmcha
//      Initial revision
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
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
// 	CHA_ResponseBuffer, CHA_RoutingTarget

//**********************************************************************

#ifndef CHA_RESPONSERECEIVER_H
#define CHA_RESPONSERECEIVER_H

#include <CHA_Model.H>
#include <CHA_ModelClient.H>
#include <CHA_ResponseBuffer.H>

class CHA_ResponseReceiver : public CHA_Model, public CHA_ModelClient
{
    friend RWBoolean operator==(const CHA_ResponseReceiver& r1,
				const CHA_ResponseReceiver& r2);
public:
    CHA_ResponseReceiver();
    // Description:
    //     Constructor.
    
    virtual ~CHA_ResponseReceiver();
    // Description:
    //     Destructor.
    
    void reset(void);
    // Description:
    //	Resets the result buffers.
    
    virtual const CHA_ResponseBuffer* getBuffer() const;
    // Description:
    //     To get the most recent part of a response.
    // Return value:
    //     A CHA_ResponseBuffer containing the response buffer.

    virtual const CHA_ResponseBuffer* getAccumulatedResponse() const;
    // Description:
    //     To get one buffer containing the concatenation of all
    //     response buffers of a response so far. When
    //     isCompleteResponse() returns TRUE this method will return
    //     the entire response.
    // Return value:
    //     A CHA_ResponseBuffer containing the accumulated responses.

    virtual RWBoolean isCompleteResponse() const;
    // Description:
    //     To find out if the last buffer of a response is available.
    // Return value:
    //     Returns TRUE if the last buffer in a response is available.

    virtual RWBoolean isNewResponse() const;
    // Description:
    //     To find out if the first buffer of a new response has arrived.
    // Return value:
    //     Returns true only when the first buffer of a response has
    //     arrived. When the second buffer has come this method will
    //     return FALSE.

    virtual RWBoolean isLastInSequence() const;
    // Description:
    //     Some response types have sequences of responses that belong
    //     together, e.g. delayed responses from S12. This method will
    //     tell whether a response is last in such a sequence or
    //     not. The default return value is TRUE always, so if
    //     something else is required the method has to be overloaded
    //     in a subclass.

    virtual void cancelResponse() = 0;    
    // Description:
    //     This method will make the response receiver stop receiving
    //     buffers of the current response. When the cancel actually
    //     takes place the response receiver will to the outside world
    //     act like the response is complete,
    //     i.e. isCompleteResponse() will return TRUE. This means that
    //     the routing targets do not have to specifically track a
    //     cancelResponse() call.    

protected:
    CHA_ResponseBuffer* buffer;          // the current response buffer
    CHA_ResponseBuffer* accumulatedResp; // concatenation of all buffers so far
    RWBoolean responseComplete;		 // if last buff of a resp has arrived
    RWBoolean newResponse;		 // if first buff of a resp has arrived
private:
};


inline RWBoolean operator==(const CHA_ResponseReceiver& r1,
			    const CHA_ResponseReceiver& r2)
{
    return (&r1 == &r2);	// equality is the same as identity
}

#endif
