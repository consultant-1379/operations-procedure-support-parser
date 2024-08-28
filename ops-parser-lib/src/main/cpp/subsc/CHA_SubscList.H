// RCS handling
// $Id: CHA_SubscList.H,v 24.0 1995/11/28 17:00:48 ehsgrap Rel $

//**********************************************************************
// 
// .NAME CHA_SubscList - Handling a list of subscriptions 
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_SubscList.H 

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
// 	CHA_SubscList.
//	A class for maintaining a list of subscriptions to spontaneous
//      reports.
//      At construction all made subscriptions are fetched from database.
//      The application program can add, delete and change subscriptions.
//      Each operation effects the database directly.
//      At destruction the list is removed and all subscriptions to process
//      must be deactivated.

// .SECTION ERROR HANDLING
//	Whenever an error occurs in the database access, the routine involved
//      returns the errorcode comming from EA.
//      If the type of error is important consult EA's manual.
//      Otherwise all returncodes less than 0 are errorcodes and
//      all returncodes > 0 are ok.

// DOCUMENT NO
//	190 89-CAA 134 1521

// AUTHOR 
// 	1994-04-15 by EHS / Marie Moschna (qhsmosc@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
// 	RCS revision history
// 	$Log: CHA_SubscList.H,v $
// 	Revision 24.0  1995/11/28 17:00:48  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:49:52  17:49:52  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:50:41  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:48:09  09:48:09  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:39:09  08:39:09  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:58:45  10:58:45  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:11:23  20:11:23  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:13:39  14:13:39  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:05:39  13:05:39  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:12:41  15:12:41  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:39:07  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:12:38  14:12:38  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:23:22  16:23:22  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:54:48  cmcha
//      Made release PREIT, N L\ufffdnninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:08:46  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:35:32  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:56:53  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:28:30  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:55:35  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:54:17  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:45:54  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  08:00:46  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.1  1994/06/22  12:56:38  qhsmosc
//      Altered after preliminary UI-tests
//
//      Revision 2.0  1994/06/12  08:02:00  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.5  1994/06/10  16:57:05  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.4  1994/05/13  09:52:00  qhsmosc
//      Final version
//
//      Revision 1.3  1994/05/06  08:09:39  qhsmosc
//      Routing remains
//
//      Revision 1.2  1994/04/26  08:00:00  qhsmosc
//      First test version
//
//      Revision 1.1  1994/04/13  13:13:48  qhsmosc
//      Initial revision
//
//
//	Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	TB53_OZ 1995-11-28      J Grape (EHSGRAP)       RCS rev 24.0
//	XM2S1   1995-09-07      ehscama                 RCS rev 23.0
//	EC2_OZ  1995-08-01      Jan Sandquist (EHSJAASA)RCS rev 22.0
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
//	PREIT   1995-01-18      N L\ufffdnninge (XKKNICL)    RCS rev 11.0
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
// 	RWTValOrderedVector
// 	CHA_Subsc

//**********************************************************************

#ifndef CHA_SUBSCLIST_H
#define CHA_SUBSCLIST_H
//TORF-241666
/*
extern "C"
{
#include <cap_ipc.h>
}

*/
#include <CHA_Subsc.H>
/*
#include <eac_sbi_subscriber.H>
#include <eac_sbi_spr_subscription.H> */
#include <rw/tvordvec.h>
#include <rw/cstring.h>

class CHA_SubscList : public CHA_Model
{
public:

    // events
    enum Event {ADDEDITEM,
		REMOVEDITEM,
		CHANGEDITEM,
		NOTHING};

    CHA_SubscList(const RWCString& s);
    //  Description:
    //    Default constructor.
    //  Parameter:
    //    s          String containing the name of the application
    
    virtual ~CHA_SubscList();
    //  Description:
    //    Default destructor.

    virtual CHA_Subsc& operator()(size_t i);
    virtual CHA_Subsc operator()(size_t i) const;
    //  Description:
    //    Returns the i'th value in the vector.
    //    The first can be used as an l-value, the second can not.
    //  Parameter:
    //    i          Index, must be between zero and number of elements

    virtual size_t entries() const;
    //  Description:
    //    Returns the number of items currently in the collection.

    virtual RWBoolean isEmpty() const;
    //  Description:
    //    Returns TRUE if there are no items in the collection,
    //    otherwise FALSE is returned.

    virtual int createList();
    //  Description:
    //    The routine fetches all information stored in the database and
    //    inserts the found information in the subscriptionlist.
    // Return value:
    //     A value < 0 indicates that an error has occured.
    //     Errorcodes from EA are forwarded, for more information see EA.

    virtual int updateList();
    //  Description:
    //    The routine clears the subscriptionlist and fetches the information
    //    from the subscription database. To be used when somebody else has
    //    altered the information in the subscription database, e.g. many
    //    users use the same user id.
    // Return value:
    //     A value < 0 indicates that an error has occured.
    //     Errorcodes from EA are forwarded, for more information see EA.

    virtual int removeRoutingToWindow();
    //  Description:
    //    The routine deactivates all routing to the screen.
    //    To be used when the user terminates the session.
    // Return value:
    //     A value < 0 indicates that an error has occured.
    //     Errorcodes from EA are forwarded, for more information see EA.

    virtual int addSubscription (CHA_Subsc & s);
    //  Description:
    //    Adds a new subscription both to the list and to the subscription
    //    database.
    //  Parameters:
    //    s          Subscription to be inserted,subscription
    //               identity will be stored in the subscription
    // Return value:
    //     A value < 0 indicates that an error has occured.
    //     Errorcodes from EA are forwarded, for more information see EA.

    virtual int removeSubscription (const long sub_id);
    //  Description:
    //    Removes a subscription both from the list and the subscription
    //    database.
    //  Parameters:
    //    sub_id     Identity of subscription to be removed
    // Return value:
    //     A value < 0 indicates that an error has occured.
    //     Errorcodes from EA are forwarded, for more information see EA.

    virtual int changeSubscription (const CHA_Subsc & s);
    virtual int changeSubscription (const long sub_id);
    //  Description:
    //    Changes a subscription in the subscription database.
    //  Parameters:
    //    s          Subscription that is to be changed
    //    or
    //    sub_id     Identity of subscription to be changed
    // Return value:
    //     A value < 0 indicates that an error has occured.
    //     Errorcodes from EA are forwarded, for more information see EA.

    virtual int activateAll();
    //  Description:
    //    Activates all subscriptions contained in the subscription list.
    // Return value:
    //     A value < 0 indicates that an error has occured.
    //     Errorcodes from EA are forwarded, for more information see EA.

    virtual int activateSubscription (const long sub_id);
    //  Description:
    //    Makes a subscription in the subscription database active.
    //  Parameters:
    //    sub_id     Identity of subscription to be activated
    // Return value:
    //     A value < 0 indicates that an error has occured.
    //     Errorcodes from EA are forwarded, for more information see EA.

    virtual int suspendAll();
    //  Description:
    //    Deactivates all subscriptions contained in the subscription list.
    // Return value:
    //     A value < 0 indicates that an error has occured.
    //     Errorcodes from EA are forwarded, for more information see EA.

    virtual int suspendSubscription (const long sub_id);
    //  Description:
    //    Makes a subscription in the subscription database deactivated.
    //  Parameters:
    //    sub_id     Identity of subscription to be suspended
    // Return value:
    //     A value < 0 indicates that an error has occured.
    //     Errorcodes from EA are forwarded, for more information see EA.

    virtual Event getLastEvent() const;
    // Description:
    //     To find out what caused a updateFrom() call in a client of
    //     this model.
    // Return values:
    //     ADDEDITEM	an subscription was added to the list
    //     REMOVEDITEM	an subscription was removed from the list
    //     NOTHING      nothing has happened

    virtual const CHA_Subsc& getChangedSubsc() const;
    // Description:
    //     To get hold of the new or removed subscription when
    //     getLastEvent() has returned ADDEDITEM or REMOVEDITEM.
    // Return value:
    //     A reference to the changed string.
    
protected:

    virtual void announceEvent(Event evt, const CHA_Subsc& subsc);
    // Description:
    //     Notifies all model clients about an event. During the
    //     notification (the updateFrom() call) a model client can
    //     call getLastEvent() and getChangedAddress() to find out
    //     about the event.
    // Parameters:
    //     evt		the event to announce
    //     subsc	the changed subscription

private:

    RWTValOrderedVector<CHA_Subsc> subscriptionList;
    RWCString processName;
    RWCString applName;
    RWCString user;

    Event lastEvent;
    CHA_Subsc changedSubsc;
};

#endif