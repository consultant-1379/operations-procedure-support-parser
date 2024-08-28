// RCS handling
// $Id: CHA_SpontSubscriber.H,v 22.0.1.1 1996/01/05 15:00:58 ehsphad Exp $

//**********************************************************************
// 
// .NAME    CHA_SpontSubscriber - manages spont. report subscriptions
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_SpontSubscriber.H

// .COPYRIGHT
//      COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1995
//
//      The Copyright to the computer program(s) herein is the
//      property of Ericsson Hewlett-Packard Telecommunications AB,
//      Sweden.  The program(s) may be used and/or copied with the
//      written permission from Ericsson Hewlett-Packard
//      Telecommunications AB or in accordance with the terms and
//      conditions stipulated in the agreement/contract under which
//      the program(s) have been supplied.

// .DESCRIPTION 
//	This class handles spontaneus report subscriptions. It is 
//	possible to start and stop subscriptions using this class.
//      A subscription is started by calling method subscribe with
//      an ES name and a report ID string. It is possible to stop
//	a single subscription, all subscriptions for an ES or all
//      subscriptions alltogether. All subscriptions are stopped
//	automatically when the CHA_SpontSubscriber is deleted.
//
//      The report IDs can be either strings, integers or integer
//	intervals. It is also possible to ask the CHA_SpontSubscriber
//	which report IDs that are subscribed for.

// DOCUMENT NO
//      190 89-CAA 134 1521

// AUTHOR 
//      1995-04-24 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_SpontSubscriber.H,v $
//      Revision 22.0.1.1  1996/01/05 15:00:58  ehsphad
//      Changed all RWModel to CHA_Model.
//
//      Revision 24.0  1995/11/28 17:00:41  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:49:40  17:49:40  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.1  1995/08/02  11:13:21  qhsjody
//      Added operator == in CHA_SSEntry.
//
//      Revision 22.0  1995/08/01  20:50:32  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:47:55  09:47:55  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 1.8  95/06/22  11:41:32  11:41:32  qhsjody (Johan Dykstrom VK/EHS/PXE)
//      Changes after code review. Changed interval handling.
//      
//      Revision 1.7  1995/06/15  08:04:07  epanyc
//      *** empty log message ***
//
//      Revision 1.6  95/06/14  12:47:12  12:47:12  qhsjody (Johan Dykstrom VK/EHS/PXE)
//      Added INVALID_ID.
//      
//      Revision 1.5  1995/06/14  12:41:53  qhsjody
//      First working version.
//
//      Revision 1.4  1995/06/09  14:25:08  qhsjody
//      Subscription partly implemented.
//
//      Revision 1.3  1995/06/07  14:12:23  qhsjody
//      List and string handling ready.
//
//      Revision 1.2  1995/05/23  16:14:30  qhsjody
//      Added some attributes.
//
//      Revision 1.1  1995/05/22  07:33:41  ehsgrap
//      Initial revision
//
//
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	TB53_OZ 1995-11-28      J Grape (EHSGRAP)       RCS rev 24.0
//	XM2S1   1995-09-07      ehscama                 RCS rev 23.0
//	EC2_OZ  1995-08-01      Jan Sandquist (EHSJAASA)RCS rev 22.0
//	EC1_OZ  1995-06-29      J Grape (EHSGRAP)       RCS rev 21.0

// .SEE ALSO 
//      CHA_SpontRepReceiver

//**********************************************************************

#ifndef CHA_SPONTSUBSCRIBER_H
#define CHA_SPONTSUBSCRIBER_H

#include <CHA_SpontRepReceiver.H>
#include <CHA_IPCSupervisor.H>
#include <CHA_RoutingHandler.H>
#include <CHA_Interval.H>

#include <rw/tvdlist.h>
#include <rw/cstring.h>
#include <rw/tools/datetime.h>

// Wait for one hour for a spontaneus report in the normal case
const long CHA_SPONSUB_DURATION = 3600;

// Prolonge a subscription when there is 10 minutes left
const long CHA_SPONSUB_PROLONGE_AFTER = CHA_SPONSUB_DURATION - 600;

//**********************************************************************

// CHA_SSEntry is used to store data for one subscription. Only used
// in this class.
class CHA_SSEntry
{
public:
    CHA_SSEntry(const RWCString& es, const RWCString& rid, long sid = -1);
    CHA_SSEntry(const CHA_SSEntry& old);
    CHA_SSEntry& operator =(const CHA_SSEntry& old);
    int operator ==(const CHA_SSEntry& other);

    RWCString esName, reportID;
    long subscID;
};

//**********************************************************************

class CHA_SpontSubscriber : public CHA_ModelClient
{
public:

    enum ReturnCode { OKAY,                // Everything OK
		      INVALID_ID,          // ID format invalid
		      NO_SUBSCRIPTION,     // Subscription did not exist
		      IPC_ERROR,           // Communication error
		      MEMORY_ERROR,        // Out of memory
		      DATABASE_ERROR,      // Database error
		      GENERAL_ERROR };     // Parameter error etc.
    
    CHA_SpontSubscriber(CHA_Model* pTrigger,
			const RWCString& applName,
			RWBoolean createReceiver = FALSE,
			CHA_IPCSupervisor* supervisor = NULL,
			CHA_RoutingHandler* pHandler = NULL);
    // Description:
    //     Constructor.
    // Parameters:
    //      pTrigger	    IN: a trigger for resubscribing to reports
    //      applName   	    IN: the name of the calling application
    //      createReceiver  IN: if a CHA_SpontRepReceiver should be created
    //      supervisor      IN: a CHA_IPCSupervisor for the CHA_SpontRepReceiver,
    //                          must be specified if createReceiver is TRUE.
    //      pHandler   	    IN: a Routing Handler (not used in this version

    virtual ~CHA_SpontSubscriber();
    // Description:
    //     Destructor.

    ReturnCode subscribe(const RWCString& es, const RWCString& reportIDs);
    // Description:
    //      Set up subscription of spontaneus reports from ES es with IDs
    //      reportIDs. reportIDs may be of format "1", "7-23" or "name".
    // Parameters:
    //      es		    IN: the ES to subscribe from
    //      reportIDs	    IN: report IDs to subscribe for
    // Return value:
    //      OKAY	    All subscriptions were set up OKAY.
    //      INVALID_ID	    reportIDs was of invalid format.
    //	    IPC_ERROR       Communication error
    //	    MEMORY_ERROR    Out of memory
    //	    DATABASE_ERROR  Database error
    //	    GENERAL_ERROR   Parameter error etc.

    ReturnCode unsubscribe();
    ReturnCode unsubscribe(const RWCString& es);
    ReturnCode unsubscribe(const RWCString& es, const RWCString& reportIDs);
    // Description:
    //      Remove subscription of spontaneus reports from ES es with IDs
    //      reportIDs. reportIDs may be of format "1", "7-23" or "name".
    //	    If no IDs are given, all subscriptions from the selected ES
    //      are removed. If no ES is given all subscriptions from all
    //      ESs are removed.
    // Parameters:
    //      es		    IN: the ES to unsubscribe from
    //      reportIDs	    IN: report IDs to unsubscribe
    // Return value:
    //      OKAY	      All subscriptions were removed OKAY.
    //      INVALID_ID	      reportIDs was of invalid format.
    //      NO_SUBSCRIPTION   Subscription did not exist.
    //	    IPC_ERROR         Communication error
    //	    MEMORY_ERROR      Out of memory
    //	    GENERAL_ERROR     Parameter error etc.

    RWTValDlist<RWCString> reportIDs(const RWCString& es) const;
    // Description:
    //      To get a list of IDs that are subscribed for from ES es.
    // Parameters:
    //      es		    IN: the ES to get subscribed IDs for
    // Return value:
    //      A list of all IDs subscribed for.

    RWTValDlist<RWCString> externalSystems() const;
    // Description:
    //      To get a list of ESs that have subscriptions.
    // Return value:
    //      A list of all ESs that have subscriptions.

    virtual void updateFrom(CHA_Model* model, void* pData);
    // Description:
    //     This method is called by the CHA_Model when it notifies
    //     it's clients about an event or state change.
    //
    //     This method has to be implemented by the subclasses and
    //     sould never be called explicitly.
    // Parameters:
    //     model		a pointer to the calling model object
    //     pData		a pointer to some data regarding the update

    virtual void detachFrom(CHA_Model* model);
    // Description:
    //     This method is called by the CHA_Model when it no longer
    //     can update it's clients. The most common case is that the
    //     model object is being destructed.
    //
    //     This method has to be implemented by the subclasses and
    //     sould never be called explicitly from anything other than
    //     a CHA_Model object.
    // Parameters:
    //     model		a pointer to the calling model object

    CHA_SpontRepReceiver* getSpontReceiver() const;
    // Description:
    //      To get hold of the spontaneus reports receiver object.
    // Return value:
    //      A pointer to the internal the spontaneus reports receiver.

private:

    RWBoolean isIDString(const RWCString& id) const;
    // Description:
    //      Internal method to check if an ID is a string or an interval.
    // Parameters:
    //      id		    IN: ID to check
    // Return value:
    //      TRUE	    The ID is a string.
    //      FALSE	    The ID is an interval (or integer that can
    //                      be turned into an interval).

    ReturnCode insertSubscription(const RWCString& es, const CHA_Interval& iv);
    // Description:
    //      Internal method to start an interval subscription and insert
    //      it at the right place in the interval subscription list. The
    //      list is sorted after ES name and interval start.
    // Parameters:
    //      es		    IN: ES name
    //      iv		    IN: interval for report ID
    // Return value:
    //      OKAY	    The subscription was started OKAY
    //	    IPC_ERROR       Communication error
    //	    MEMORY_ERROR    Out of memory
    //	    DATABASE_ERROR  Database error
    //	    GENERAL_ERROR   Parameter error etc.

    ReturnCode stopSubscription(const CHA_SSEntry& entry);
    // Description:
    //      Internal method to stop a single subscription.
    // Parameters:
    //      entry	    IN: a CHA_SSEntry containing subscription info
    // Return value:
    //      OKAY	    The subscription was stopped OKAY.
    //	    IPC_ERROR       Communication error
    //	    MEMORY_ERROR    Out of memory
    //	    GENERAL_ERROR   Parameter error etc.

    ReturnCode startSubscription(CHA_SSEntry& entry);
    // Description:
    //      Internal method to start a single subscription. All objects
    //      are constructed and initialized, and the subscription object
    //      is sent to the subscription server.
    // Parameters:
    //      entry	    IN/OUT: a CHA_SSEntry containing subscription info
    // Return value:
    //      OKAY	    The subscription was started OKAY
    //	    IPC_ERROR       Communication error
    //	    MEMORY_ERROR    Out of memory
    //	    DATABASE_ERROR  Database error
    //	    GENERAL_ERROR   Parameter error etc.

    // Subscription data in two lists - one for strings and one for
    // intervals
    RWTValDlist<CHA_SSEntry> stringSubsc;
    RWTValDlist<CHA_SSEntry> intervSubsc;

    CHA_Model* trigger;      // Clock trigger for subscription prolonging
    RWCString name;                                   // Application name

    CHA_SpontRepReceiver* receiver;            // Spont. reports Receiver
    RWDateTime prolongLimit;                  // When to prolong subscription
};

#endif
