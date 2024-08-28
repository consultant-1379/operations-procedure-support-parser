// RCS handling
// $Id: CHA_WindowTarget.H,v 22.0.1.1 1996/01/05 14:29:26 ehsphad Exp $

//**********************************************************************
// 
// .NAME    CHA_WindowTarget - forwards responses to a window
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_WindowTarget.H

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
//      CHA_WindowTarget is a routing target for responses routed to
//      window. A window target observes one or more response
//      receivers and forwards every response to it's observers,
//      usually a window widget in the UI.
//
//      A CHA_WindowTarget represents one window, so if routing is
//      made to several windows there will be several window targets.
//
//      Every window target is identified through a string that is
//      refered to as it's `address' or window name.

// .SECTION ERROR HANDLING
//      Errors are reported to the global CHA_ErrorReporter instance. 

// DOCUMENT NO
//      190 89-CAA 134 1519

// AUTHOR 
//      1994-05-10 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_WindowTarget.H,v $
//      Revision 22.0.1.1  1996/01/05 14:29:26  ehsphad
//      Changed all RWModel to CHA_Model.
//
//      Revision 24.0  1995/11/28 16:58:00  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:45:42  17:45:42  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:47:23  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:44:17  09:44:17  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:36:00  08:36:00  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:55:20  10:55:20  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:07:46  20:07:46  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:08:35  14:08:35  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:02:04  13:02:04  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:06:07  15:06:07  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:36:01  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:07:36  14:07:36  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:18:54  16:18:54  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:49:55  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:05:14  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:31:47  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:51:45  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:24:41  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:51:53  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:48:03  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:40:28  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.1  1994/07/15  11:39:34  ehsgrap
//      Now handles break response.
//
//      Revision 3.0  1994/06/23  07:56:45  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  07:59:17  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.3  1994/06/10  16:57:35  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.2  1994/06/08  13:44:03  ehsgrap
//      Added Event STORED_REMOVED.
//
//      Revision 1.1  1994/05/18  08:31:40  ehsgrap
//      Initial version.
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

//**********************************************************************

#ifndef CHA_WINDOWTARGET_H
#define CHA_WINDOWTARGET_H

#include <CHA_RoutingTarget.H>
#include <CHA_ResponseBuffer.H>
#include <CHA_ResponseReceiver.H>

#include <rw/tvslist.h>


class CHA_WindowTarget : public CHA_RoutingTarget, public CHA_Model
{
    
public:

    // Possible events
    enum Event {NOTHING,
		NEW_BUFFER,
		NEW_STORED_AVAILABLE,
		STORED_REMOVED};

    CHA_WindowTarget();
    // Description:
    //     Constructor.

    ~CHA_WindowTarget();
    // Description:
    //     Destructor.

    RWBoolean isStoredType(CHA_ResponseType respType) const;
    // Description:
    //     To find out wether a response type is stored or forwarded
    //     directly. 
    // Parameters:
    //     respType	IN: One of the response types mentioned in the
    //                  enum CHA_ResponseType from the file
    //                  CHA_LibGlobals.H
    // Return value:
    //     TRUE		Responses of the given type is stored.
    //     FALSE        The opposite.

    void setTypeStored(CHA_ResponseType respType, RWBoolean on);
    // Description:
    //     Make a certain resposetype a stored type. The default is
    //     that CHA_RT_DELAYED and CHA_RT_SPNTANEOUS are stored.
    // Parameters:
    //     respType	IN: One of the response types mentioned in the
    //                  enum CHA_ResponseType from the file
    //                  CHA_LibGlobals.H
    //
    //     on		IN: TRUE will make the type sored and FALSE
    //                  will make responses forwarded directly.

    size_t availableStored() const;
    // Description:
    //     Count the number of stored responses.
    // Return value:
    //     The number of stored responses.

    RWCString getStoredResponse();
    // Description:
    //     To get the first stored response. The count of stored
    //     responses will be reduced by 1 after this.
    // Return value:
    //     A string containing the response.

    RWCString getBuffer();
    // Description:
    //     To get the currently forwarded buffer, i.e. a buffer from a
    //     response type that is not stored. If the buffer is not
    //     retreived during a updateFrom() call in a model client
    //     observing this window target, the buffer may not be valid.
    //
    //     Usually this method is called within a updateFrom() method
    //     when the method getLastEvent() of this calss has returned
    //     NEW_BUFFER. 
    // Return value:
    //     A string containing the buffer.

    const CHA_ResponseBuffer* getRespBuffer();
    // Description:
    //     Get the current buffer. If no buffer exist, NULL is returned.
    // Return value:
    //     CHA_ResponseBuffer* or NULL

    void breakCurrentResponse();
    // Description:
    //     Will send a CHA_ResponseReceiver::cacncelResponse() to the
    //     response receiver that the window target currently is
    //     receiving response buffers from.
    //
    //     This method has no effect on stored responses.


    RWBoolean isCompleteResponse() const;
    // Description:
    //     To find out id the buffer retreived from a getBuffer() call
    //     was the last one in a response.
    // Return value:
    //     TRUE		The buffer was the last one in a response.
    //     FALSE        The buffer was in the beginning or middle of a
    //                  response .
    
    virtual void updateFrom(CHA_Model* p, void* d);
    // Description:
    //     A new implementation of the update method inherited from
    //     CHA_RoutingTarget. It is expected that this method is
    //     called from a CHA_ResponseReceiver object. 
    // Parameters:
    //     p		A pointer to a CHA_ResponseReceiver
    //                  casted to a CHA_Model pointer.
    //
    //     d            A pointer to a CHA_ResponseBuffer
    //                  casted to a void pointer.

    void detachFrom(CHA_Model* p);
    // Description:
    //     A new implementation of the detach method inherited from
    //     CHA_RoutingTarget. It is expected that this method is
    //     called from a CHA_ResponseReceiver object.
    // Parameters:
    //     p		A pointer to a CHA_ResponseReceiver
    //                  casted to a CHA_Model pointer.
    //

    Event getLastEvent();
    // Description:
    //     To find out what caused this object to make a updateFrom()
    //     call to it's observing model client.
    // Return value:
    //     NOTHING		Nothing has happened.
    //     NEW_BUFFER		A new (not stored) buffer is availble.
    //     NEW_STORED_AVAILABLE	A new stored response is available.

protected:
    
    virtual void doRouting(const CHA_ResponseBuffer* response);
    // Description:
    //     This method is empty. It is defined only beacause the
    //     abstract super class CHA_RoutingTarget has declared this
    //     method as pure virtual.
    //
    //     Normally this method is called from the super calss method
    //     updateFrom(), but in this sub class that method is
    //     redefined (over loaded) and the doRouting() method is no
    //     longer needed.
    // Parameters:
    //     response	A pointer to a CHA_ResponseBuffer.

private:

    void fwdFromList();
    // Description:
    //     Announces all responses in the list respToFwd that have been
    //     collected during reception of buffers from another
    //     receiver. (Only buffers from one receiver can be announced
    //     at a time).

    void announceEvent(Event evt);
    // Description:
    //     To announce a new event, i.e. set the lastEvent variable
    //     and called changed().
    // Parameters:
    //     evt		One of the events mentioned in the enum Event. 


    RWBoolean isStored[CHA_RT_UNDEFINED + 1]; // record of which types
					      // that are stored

    RWTValSlist<RWCString> stored;            // list of stored
					      // responses 

    CHA_ResponseReceiver* pCurrentRespRcvr;   // a pointer to the
					      // response receiver
					      // that gave the last
					      // non stored response
					      // buffer 

    const CHA_ResponseBuffer* pRespBuffer;    // a pointer to the last
					      // non stored response
					      // buffer 

    RWTValSlist<RWCString> respToFwd;	      // list of responses
					      // that can't be
					      // forwarded directly

    Event lastEvent;                          // the last event that
					      // occured 
};

#endif
