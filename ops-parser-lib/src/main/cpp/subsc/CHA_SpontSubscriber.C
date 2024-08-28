// RCS handling
// $Id: CHA_SpontSubscriber.C,v 22.0.1.1 1996/01/05 15:00:58 ehsphad Exp $

//**********************************************************************

// COPYRIGHT
//      COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1994
//
//      The Copyright to the computer program(s) herein is the
//      property of Ericsson Hewlett-Packard Telecommunications AB,
//      Sweden.  The program(s) may be used and/or copied with the
//      written permission from Ericsson Hewlett-Packard
//      Telecommunications AB or in accordance with the terms and
//      conditions stipulated in the agreement/contract under which
//      the program(s) have been supplied.

// DOCUMENT NO
//	190 89-CAA 134 1521

// AUTHOR
//      1995-05-23 by EHS/PXE Johan Dykstr\ufffdm (qhsjody@ehs.ericsson.se)

// REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_SpontSubscriber.C,v $
//      Revision 22.0.1.1  1996/01/05 15:00:58  ehsphad
//      Changed all RWModel to CHA_Model.
//
//      Revision 24.0  1995/11/28 17:01:03  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.1  95/09/21  14:53:46  14:53:46  qhsjody (Johan Dykstrom VK/EHS/PXE)
//      Change after review. New subscriptions are created before old are deleted.
//
//      Revision 23.0  1995/09/07  17:50:18  ehscama
//      Made release XM2S1, ehscama.
//
//      Revision 22.1  1995/08/02  11:13:33  qhsjody
//      Added operator == in CHA_SSEntry.
//
//      Revision 22.0  1995/08/01  20:50:57  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.1  95/07/03  10:59:31  10:59:31  ehsgrap (Jan Grape (9 9073) VK/EHS/PXE)
//      Removed some trace that was no good in a polling event loop
//
//      Revision 21.0  1995/06/29  09:48:36  cmcha
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 1.5  95/06/22  11:41:48  11:41:48  qhsjody (Johan Dykstrom VK/EHS/PXE)
//      Changes after code review. Changed interval handling.
//
//      Revision 1.4  1995/06/14  12:42:11  qhsjody
//      First working version.
//
//      Revision 1.3  1995/06/09  14:24:37  qhsjody
//      Subscription partly implemented.
//
//      Revision 1.2  1995/06/07  14:11:57  qhsjody
//      List and string handling ready.
//
//      Revision 1.1  1995/05/23  16:14:40  qhsjody
//      Initial revision.
//
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	TB53_OZ 1995-11-28      J Grape (EHSGRAP)       RCS rev 24.0
//	XM2S1   1995-09-07      ehscama                 RCS rev 23.0
//	EC2_OZ  1995-08-01      Jan Sandquist (EHSJAASA)RCS rev 22.0
//	EC1_OZ  1995-06-29      J Grape (EHSGRAP)       RCS rev 21.0

//**********************************************************************

#include <CHA_SpontSubscriber.H>
#include <CHA_Trace.H>

/*TORF-241666
 #include <eac_sbi_subscriber.H>
#include <eac_sbi_spr_subscription.H> */

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_SpontSubscriber", (char*)"C");

//**********************************************************************
// CHA_SSEntry is used to store data for one subscription. Only used
// in this class.
//**********************************************************************

CHA_SSEntry::CHA_SSEntry(const RWCString& es, const RWCString& rid, long sid)
: esName(es), reportID(rid), subscID(sid)
{ }

CHA_SSEntry::CHA_SSEntry(const CHA_SSEntry& old)
: esName(old.esName), reportID(old.reportID), subscID(old.subscID)
{ }

CHA_SSEntry& CHA_SSEntry::operator =(const CHA_SSEntry& old)
{
    esName = old.esName;
    reportID = old.reportID;
    subscID = old.subscID;
    return *this;
}

int CHA_SSEntry::operator ==(const CHA_SSEntry& other)
{
    return ((esName == other.esName) &&
	    (reportID == other.reportID) &&
	    (subscID == other.subscID));
}

//**********************************************************************

CHA_SpontSubscriber::CHA_SpontSubscriber(CHA_Model* pTrigger,
					 const RWCString& applName,
					 RWBoolean createReceiver,
					 CHA_IPCSupervisor* supervisor,
					 CHA_RoutingHandler* /*pHand*/)
: trigger(pTrigger),
  name(applName),
  receiver(0)
{
    ////TRACE_IN(trace, CHA_SpontSubscriber, name);

    if (trigger)
	trigger->addDependent(this);

    // Should we create a CHA_SpontRepReceiver?
    if (createReceiver)
    {
	////TRACE_FLOW(trace, CHA_SpontSubscriber,
	//	   "Create CHA_SpontRepReceiver");

	receiver = new CHA_SpontRepReceiver(supervisor, name);
    }
}

//**********************************************************************

CHA_SpontSubscriber::~CHA_SpontSubscriber()
{
    (void) unsubscribe();
    if (trigger)
	trigger->removeDependent(this);
    if (receiver)
	delete receiver;
}

//**********************************************************************

CHA_SpontSubscriber::ReturnCode
CHA_SpontSubscriber::subscribe(const RWCString& es,
			       const RWCString& reportIDs)
{
    ////TRACE_IN(trace, subscribe, es << ": '" << reportIDs << "'");
    ReturnCode result = OKAY, tmpResult;
    RWTValDlist<CHA_SSEntry> entriesToBeDeleted;

    // Set prolong time
    prolongLimit = RWDateTime::now() + CHA_SPONSUB_PROLONGE_AFTER;

    // Check if report ID is a string
    if (isIDString(reportIDs))
    {
	////TRACE_FLOW(trace, subscribe, "ID is string");
	RWBoolean foundOldSubsc = FALSE;
	int index = 0;

	// Check for old subscription
	while (!foundOldSubsc &&
	       (index < stringSubsc.entries()))
	{
	    if ((stringSubsc[index].esName == es) &&
		(stringSubsc[index].reportID == reportIDs))
		foundOldSubsc = TRUE;
	    index++;
	}

	// If no old subscription existed
	if (!foundOldSubsc)
	{
	    ////TRACE_FLOW(trace, subscribe, "New subscription");
	    CHA_SSEntry entry(es, reportIDs);

	    // Create subscription
	    result = startSubscription(entry);

	    // Save subscription data
	    stringSubsc.append(entry);
	}
    }

    // Report ID was integer or interval
    else
    {
	////TRACE_FLOW(trace, subscribe, "ID is interval");
	CHA_Interval iv(reportIDs);

	// Turn integer into interval
	if (iv.isEmpty())
	    iv = CHA_Interval(reportIDs + "-" + reportIDs);

	// If interval empty (invalid) do no more
	if (iv.isEmpty())
	    result = INVALID_ID;

	// ID OK
	else
	{
	    ////TRACE_FLOW(trace, subscribe, "ID OK");
	    int index = 0;

	    // Traverse list of intervals and try to concatenate new
	    // interval with as many of the old as possible
	    while (index < intervSubsc.entries())
	    {
		CHA_Interval oldIv(intervSubsc[index].reportID);

		// Is it possible to concatenate the intervals? They must
		// be for the same NE and be adjacent or intersecting.
		if ((intervSubsc[index].esName == es) &&
		    (iv.isAdjacentTo(oldIv) || iv.isIntersecting(oldIv)))
		{
		    ////TRACE_FLOW(trace, subscribe,
			//       "Concat(" << iv << ", " << oldIv << ")");

		    // Move subscription from subscription list to
		    // deletion list
		    entriesToBeDeleted.append(intervSubsc.removeAt(index));

		    // Make new interval
		    iv.concatenate(oldIv);
		    index--;                // Decrease to avoid increase
		}
		index++;
	    }

	    // Start subscription and insert new interval into list
	    tmpResult = insertSubscription(es, iv);
	    if (tmpResult != OKAY)
		result = tmpResult;

	    // Stop all old subscriptions
	    while (!entriesToBeDeleted.isEmpty())
	    {
		tmpResult = stopSubscription(entriesToBeDeleted.get());
		if (tmpResult != OKAY)
		    result = tmpResult;
	    }
	}
    }

    ////TRACE_RETURN(trace, subscribe, result);
    return result;
}

//**********************************************************************

CHA_SpontSubscriber::ReturnCode CHA_SpontSubscriber::unsubscribe()
{
    ////TRACE_IN(trace, unsubscribe, "");
    ReturnCode result = OKAY, tmpResult;

    // Unsubscribe to all subscriptions in interval list
    for (int i = 0; i < intervSubsc.entries(); i++)
    {
	tmpResult = stopSubscription(intervSubsc[i]);
	if (tmpResult != OKAY)
	    result = tmpResult;
    }
    intervSubsc.clear();

    // Unsubscribe to all subscriptions in string list
    for (int i = 0; i < stringSubsc.entries(); i++)
    {
	tmpResult = stopSubscription(stringSubsc[i]);
	if (tmpResult != OKAY)
	    result = tmpResult;
    }
    stringSubsc.clear();

    ////TRACE_RETURN(trace, unsubscribe, result);
    return result;
}

//**********************************************************************

CHA_SpontSubscriber::ReturnCode
CHA_SpontSubscriber::unsubscribe(const RWCString& es)
{
    ////TRACE_IN(trace, unsubscribe, es);
    ReturnCode result = OKAY, tmpResult;

    // Interval list
    int i = 0;
    while (i < intervSubsc.entries())
    {
	// Unsubscribe to all subscriptions for ES es
	if (intervSubsc[i].esName == es)
	{
	    // Correct ES - stop subscription
	    tmpResult = stopSubscription(intervSubsc[i]);
	    if (tmpResult != OKAY)
		result = tmpResult;
	    intervSubsc.removeAt(i--);       // Decrease to avoid increase
	}
	i++;
    }

    // String list
    i = 0;
    while (i < stringSubsc.entries())
    {
	// Unsubscribe to all subscriptions for ES es
	if (stringSubsc[i].esName == es)
	{
	    // Correct ES - stop subscription
	    tmpResult = stopSubscription(stringSubsc[i]);
	    if (tmpResult != OKAY)
		result = tmpResult;
	    stringSubsc.removeAt(i--);       // Decrease to avoid increase
	}
	i++;
    }

    ////TRACE_RETURN(trace, unsubscribe, result);
    return result;
}

//**********************************************************************

CHA_SpontSubscriber::ReturnCode
CHA_SpontSubscriber::unsubscribe(const RWCString& es,
				 const RWCString& reportIDs)
{
    ////TRACE_IN(trace, unsubscribe, es << ": '" << reportIDs << "'");
    ReturnCode result = OKAY, tmpResult;
    RWTValDlist<CHA_SSEntry> entriesToBeDeleted;

    // Check if report ID is a string
    if (isIDString(reportIDs))
    {
	////TRACE_FLOW(trace, unsubscribe, "ID is string");
	int index = 0;

	// Check for old subscription
	while (index < stringSubsc.entries())
	{
	    if ((stringSubsc[index].esName == es) &&
		(stringSubsc[index].reportID == reportIDs))
		break;
	    index++;
	}

	// If old subscription did exist
	if (index < stringSubsc.entries())
	{
	    ////TRACE_FLOW(trace, unsubscribe, "Found subscription");

	    // Stop subscription
	    result = stopSubscription(stringSubsc[index]);

	    // Remove subscription data
	    stringSubsc.removeAt(index);
	}

	// Did not find subscription
	else
	    result = NO_SUBSCRIPTION;
    }

    // Report ID was integer or interval
    else
    {
	////TRACE_FLOW(trace, unsubscribe, "ID is interval");
	CHA_Interval iv(reportIDs);

	// Turn integer into interval
	if (iv.isEmpty())
	    iv = CHA_Interval(reportIDs + "-" + reportIDs);

	// If interval empty (invalid) do no more
	if (iv.isEmpty())
	    result = INVALID_ID;

	// ID OK
	else
	{
	    ////TRACE_FLOW(trace, unsubscribe, "ID OK");
	    RWBoolean intervalFound = FALSE;
	    int index = 0;

	    // Traverse list to find intersecting intervals
	    while (index < intervSubsc.entries())
	    {
		CHA_Interval oldIv(intervSubsc[index].reportID);
		////TRACE_FLOW(trace, unsubscribe,
		//	   "iv " << index << ": " << oldIv);

		if ((intervSubsc[index].esName == es) &&
		    iv.isIntersecting(oldIv))
		{
		    ////TRACE_FLOW(trace, unsubscribe,
			//       iv <<  " intersects " << oldIv);

		    // Move subscription from subscription list to
		    // deletion list
		    entriesToBeDeleted.append(intervSubsc.removeAt(index));

		    CHA_Interval newIv1, newIv2;

		    // Make new interval(s)
		    // Start subscription and insert interval(s) into
		    // list. This won't trouble us, since new
		    // interval(s) are inserted at the same place or
		    // after the old interval.
		    if (removeInterval(oldIv, iv, newIv1, newIv2))
		    {
			// Two intervals were created, insert last iv
			////TRACE_FLOW(trace, unsubscribe, "Two intervals");
			tmpResult = insertSubscription(es, newIv2);
			if (tmpResult != OKAY)
			    result = tmpResult;
		    }

		    // If newIv1 is non-empty, subscribe to it
		    if (!newIv1.isEmpty())
		    {
			// At least one interval left
			////TRACE_FLOW(trace, unsubscribe, "At least one iv");
			tmpResult = insertSubscription(es, newIv1);
			if (tmpResult != OKAY)
			    result = tmpResult;
		    }
		    index--;                // Decrease to avoid increase
		}
		index++;

	    }  // while (index < intervSubsc.entries())

	    // Stop all old subscriptions
	    while (!entriesToBeDeleted.isEmpty())
	    {
		tmpResult = stopSubscription(entriesToBeDeleted.get());
		if (tmpResult != OKAY)
		    result = tmpResult;
	    }
	}
    }

    ////TRACE_RETURN(trace, unsubscribe, result);
    return result;
}

//**********************************************************************

RWTValDlist<RWCString>
CHA_SpontSubscriber::reportIDs(const RWCString& es) const
{
    ////TRACE_IN(trace, reportIDs, es);
    RWTValDlist<RWCString> result;
    int i;

    // Traverse interval list
    for (i = 0; i < intervSubsc.entries(); i++)
    {
	// Copy all IDs for ES es
	if (intervSubsc[i].esName == es)
	    result.append(intervSubsc[i].reportID);
    }

    // Traverse string list
    for (i = 0; i < stringSubsc.entries(); i++)
    {
	// Copy all IDs for ES es
	if (stringSubsc[i].esName == es)
	    result.append(stringSubsc[i].reportID);
    }

    ////TRACE_RETURN(trace, reportIDs, result.entries() << " IDs");
    return result;
}

//**********************************************************************

RWTValDlist<RWCString>
CHA_SpontSubscriber::externalSystems() const
{
    ////TRACE_IN(trace, externalSystems, "");
    RWTValDlist<RWCString> result;
    int i;

    // Traverse interval list
    for (i = 0; i < intervSubsc.entries(); i++)
    {
	// If we have not already copied the ES, copy it
	if (!result.contains(intervSubsc[i].esName))
	    result.append(intervSubsc[i].esName);
    }

    // Traverse string list
    for (i = 0; i < stringSubsc.entries(); i++)
    {
	// If we have not already copied the ES, copy it
	if (!result.contains(stringSubsc[i].esName))
	    result.append(stringSubsc[i].esName);
    }

    ////TRACE_RETURN(trace, externalSystems, result.entries() << " ESs");
    return result;
}

//**********************************************************************

void CHA_SpontSubscriber::updateFrom(CHA_Model* model, void*)
{
    int i;

    // Prolonge only if time is up
    RWDateTime rightNow;                                 // Current time
    if (rightNow > prolongLimit)
    {
	// Calculate new end time for subscription
	prolongLimit = rightNow + CHA_SPONSUB_PROLONGE_AFTER;

	// Prolong all subscriptions by stopping and starting again
	for (i = 0; i < intervSubsc.entries(); i++)
	{
	    (void) stopSubscription(intervSubsc[i]);
	    (void) startSubscription(intervSubsc[i]);
	}
	for (i = 0; i < stringSubsc.entries(); i++)
	{
	    (void) stopSubscription(stringSubsc[i]);
	    (void) startSubscription(stringSubsc[i]);
	}
    }
}

//**********************************************************************

void CHA_SpontSubscriber::detachFrom(CHA_Model* model)
{
    ////TRACE_IN(trace, detachFrom, long(model));
    if (trigger == model)
	trigger = 0;
}

//**********************************************************************

CHA_SpontRepReceiver* CHA_SpontSubscriber::getSpontReceiver() const
{
    ////TRACE_IN(trace, getSpontReceiver, "");
    return receiver;
}

//**********************************************************************

RWBoolean CHA_SpontSubscriber::isIDString(const RWCString& id) const
{
    ////TRACE_IN(trace, isIDString, id);
    RWBoolean result = TRUE;
    std::istrstream is(id);
    int foo;

    is >> foo;                                    // Try to read integer
    if (is)                        // If we succeeded, id is an interval
	result = FALSE;

    ////TRACE_RETURN(trace, isIDString, result);
    return result;
}

//**********************************************************************

CHA_SpontSubscriber::ReturnCode
CHA_SpontSubscriber::insertSubscription(const RWCString& es,
					const CHA_Interval& iv)
{
    ////TRACE_IN(trace, insertSubscription, "(" << es << ", " << iv << ")");
    ReturnCode result = OKAY;
    int index = 0;

    // Find place to put new interval in list...
    //
    // WHILE
    //   we have not reached end of list
    // AND
    //     es name is greater than es name in list
    //   OR
    //       es name is equal to es name in list
    //     AND
    //       interval is greater than interval in list
    while ((index < intervSubsc.entries()) &&
	   ((es > intervSubsc[index].esName) ||
	    ((es == intervSubsc[index].esName) &&
	     (iv.getLower() > CHA_Interval(
		 intervSubsc[index].reportID).getLower()))))
	index++;

    // Create subscription
    CHA_SSEntry entry(es, iv);
    result = startSubscription(entry);

    // Save subscription data
    ////TRACE_FLOW(trace, insertSubscription, "Adding (" << es << ", " << iv
	//       << ") to list, index: " << index);
    if (index >= intervSubsc.entries())
	intervSubsc.append(entry);
    else
	intervSubsc.insertAt(index, entry);

    ////TRACE_RETURN(trace, insertSubscription, result);
    return result;
}

//**********************************************************************

CHA_SpontSubscriber::ReturnCode
CHA_SpontSubscriber::stopSubscription(const CHA_SSEntry& entry)
{
    ////TRACE_IN(trace, stopSubscription, "(" << entry.esName << ", "
	//     << entry.reportID << ", " << entry.subscID << ")");

   // EAC_SBI_Subscriber subscriber;
    int errorCode;

    // Actually stop subscription
  //  errorCode = subscriber.Terminate_subscription(entry.subscID);

  /*  if (errorCode != EAC_SBI_OK)
    {
	////TRACE_FLOW(trace, stopSubscription,
	//	   "Terminate_subscription failed: " << errorCode);
	switch (errorCode)
	{
	    case EAC_SBI_MEM_ERR:
		////TRACE_RETURN(trace, stopSubscription, "MEMORY_ERROR");
		return MEMORY_ERROR;
	    case EAC_SBI_IPC_ERR:
		////TRACE_RETURN(trace, stopSubscription, "IPC_ERROR");
		return IPC_ERROR;
	    default:
		////TRACE_RETURN(trace, stopSubscription, "GENERAL_ERROR");
		return GENERAL_ERROR;
	}
    }
*/
    ////TRACE_RETURN(trace, stopSubscription,"OKAY");
    return OKAY;
}

//**********************************************************************

CHA_SpontSubscriber::ReturnCode
CHA_SpontSubscriber::startSubscription(CHA_SSEntry& entry)
{
    ////TRACE_IN(trace, startSubscription,
	//     "(" << entry.esName << ", " << entry.reportID << ")");
  //  EAC_SBI_Subscriber subscriber;
  // EAC_SBI_SPR_Subscription subscription;
    long errorCode;

 //   subscription.Clear_criteria();

    // Set ES and ID for subscription. This is done in different ways
    // for strings and intervals. Check if ID is a string.
    if (isIDString(entry.reportID))
    {
	////TRACE_FLOW(trace, startSubscription, "ID is string");
	//errorCode = subscription.Set_criteria(entry.esName,
	//				      entry.reportID);
    }

    // ID is an interval
    else
    {
	////TRACE_FLOW(trace, startSubscription, "ID is interval");
	CHA_Interval iv(entry.reportID);
	//errorCode = subscription.Set_criteria(entry.esName,
	//				      iv.getLower(),
	//				      iv.getUpper());
    }

    // Any errors during Set_criteria?
 /*   if (errorCode != EAC_SBI_OK)
    {
	////TRACE_FLOW(trace, startSubscription,
	//	   "Set_criteria failed: " << errorCode);

	// Translate error
	switch (errorCode)
	{
	    case EAC_SBI_MEM_ERR:
		////TRACE_RETURN(trace, startSubscription, "MEMORY_ERROR");
		return MEMORY_ERROR;
	    default:
		////TRACE_RETURN(trace, startSubscription, "GENERAL_ERROR");
		return GENERAL_ERROR;
	}
    }*/

    // We do not need to call this method... do we?
    // Set receiver for spontaneus reports, should automaticly be
    // set to current application
 /*   if ((errorCode = subscription.Set_subscription_receiver(name))
        != EAC_SBI_OK)
    {
	////TRACE_FLOW(trace, startSubscription,
		//   "Set_subscription_receiver failed: " << errorCode);

	// Translate error
	switch (errorCode)
	{
	    case EAC_SBI_MEM_ERR:
		////TRACE_RETURN(trace, startSubscription, "MEMORY_ERROR");
		return MEMORY_ERROR;
	    default:
		////TRACE_RETURN(trace, startSubscription, "GENERAL_ERROR");
		return GENERAL_ERROR;
	}
    }
*/
    // Initiate subscription by sending it to the subscription server
 /*   if ((errorCode = subscriber.Initiate_subscription(&subscription,
					 CHA_SPONSUB_DURATION)) <= 0)
    {
	////TRACE_FLOW(trace, startSubscription,
		//   "Initiate_subscription failed: " << errorCode);

	// Translate error
	switch (errorCode)
	{
	    case -3:
		////TRACE_RETURN(trace, startSubscription, "MEMORY_ERROR");
		return MEMORY_ERROR;
	    case -4:
		////TRACE_RETURN(trace, startSubscription, "IPC_ERROR");
		return IPC_ERROR;
	    case -5:
		////TRACE_RETURN(trace, startSubscription, "DATABASE_ERROR");
		return DATABASE_ERROR;
	    default:
		////TRACE_RETURN(trace, startSubscription, "GENERAL_ERROR");
		return GENERAL_ERROR;
	}
    }
*/
    // Save subscription ID for stopSubscription
    entry.subscID = errorCode;

    ////TRACE_RETURN(trace, startSubscription,"OKAY, id = " << errorCode);
    return OKAY;
}

//**********************************************************************
