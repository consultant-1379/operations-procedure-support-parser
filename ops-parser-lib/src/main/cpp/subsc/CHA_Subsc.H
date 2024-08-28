// RCS handling
// $Id: CHA_Subsc.H,v 24.0 1995/11/28 17:00:42 ehsgrap Rel $

//**********************************************************************
// 
// .NAME CHA_Subsc - Subscription for spontaneous reports 
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_Subsc.H 

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
//      The class is used to handle a subscription to a spontaneous report.
//      There are routines that accesses the subscription database via the
//      class CHA_SBI_SPR_Subscription, mainly routines for fetching and storing
//      information. There are also routines that directly communicates with
//      subscription database, routines for activating/suspending subscriptions.
//      The operations that only demands an subscription identity are initiated
//      in this class, while the operations that demands more information are
//      initiated via the class CHA_SBI_Subscription.

// .SECTION ERROR HANDLING
//	Whenever an error occurs in the database access, the routine involved
//      returns the errorcode comming from EA.
//      If the type of error is important consult EA's manual.
//      Otherwise all returncodes less than 0 are errorcodes and
//      all returncodes > 0 are ok..

// DOCUMENT NO
//	190 89-CAA 134 1521

// AUTHOR 
// 	1994-04-15 by EHS / Marie Moschna (qhsmosc@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_Subsc.H,v $
//      Revision 24.0  1995/11/28 17:00:42  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:49:43  17:49:43  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:50:34  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:47:58  09:47:58  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:39:03  08:39:03  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:58:35  10:58:35  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:11:15  20:11:15  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:13:32  14:13:32  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:05:32  13:05:32  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:12:27  15:12:27  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:39:01  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:12:29  14:12:29  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:23:08  16:23:08  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:54:38  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:08:35  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:35:22  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:56:38  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:28:19  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.1  1994/09/21  08:18:32  qhsmosc
//      Added new status CHA_SUBSC_SCHEDULED
//
//      Revision 6.0  1994/08/30  17:55:24  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.1  1994/08/26  09:54:27  qhsmosc
//      Added constructor with default routing to window
//
//      Revision 5.0  1994/08/16  07:54:02  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:45:41  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  08:00:34  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:01:49  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.4  1994/05/13  09:51:28  qhsmosc
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
// 	CHA_SubscInterval                Time interval
//      CHA_RoutingCase                  Routing case
//      CHA_SBI_SPR_Subscription         Encapsulation of database access
//      CHA_ReportIdentity               Identity for report subscribed to

//**********************************************************************

#ifndef CHA_SUBSC_H
#define CHA_SUBSC_H

#include <rw/model.h>
//#include <eac_sbi_subscriber.H>
//#include <eac_sbi_spr_subscription.H>
#include <CHA_SBI_SPR_Subscription.H>
#include <CHA_SubscInterval.H>
#include <CHA_ReportIdentity.H>
#include <CHA_RoutingCase.H>
#include <rw/cstring.h>
#include <rw/tvordvec.h>

enum CHA_SubscState
{
    CHA_SUBSC_ACTIVE,
    CHA_SUBSC_SUSPENDED,
    CHA_SUBSC_SCHEDULED
};

class CHA_Subsc
{
public:
    CHA_Subsc();
    // Description:
    //     Default constructor.

    CHA_Subsc(RWCString windowName);
    // Description:
    //     Constructor to be used when a default routing to window is desired.
    // Parameter:
    //     windowName        Routing address to window

    CHA_Subsc(const CHA_Subsc& s);
    // Description:
    //     Constructor to be used at copy.

    //CHA_Subsc(const long sub_id);
    // Description:
    //     Constructor to be used when fetching information from the
    //     subscription database.

    virtual ~CHA_Subsc();
    // Description:
    //     Destructor.
    
    virtual int activate();
    // Description:
    //     Activate the subscription.
    // Return value:
    //     A value < 0 indicates that an error has occured.
    //     Errorcodes from EA are forwarded, for more information see EA.
    
    virtual int suspend();
    // Description:
    //     Suspend the subscription.
    // Return value:
    //     A value < 0 indicates that an error has occured.
    //     Errorcodes from EA are forwarded, for more information see EA.
    
    virtual int fetch(const long s);
    // Description:
    //     Read the order from the order database.
    // Parameters:
    //     s                    subscription identity
    // Return value:
    //     A value < 0 indicates that an error has occured.
    //     Errorcodes from EA are forwarded, for more information see EA.
    
    virtual int store(const RWCString a);
    // Description:
    //     Store the subscription in the subscription database. Used both to
    //     insert a new order in the subscription database and to overwrite
    //     an existing order.
    // Parameter:
    //     a                    the name of the application
    // Return value:
    //     A value < 0 indicates that an error has occured.
    //     Errorcodes from EA are forwarded, for more information see EA.
    
    virtual int remove();
    // Description:
    //     Delete the subscription from the subscription database. 
    // Return value:
    //     A value < 0 indicates that an error has occured.
    //     Errorcodes from EA are forwarded, for more information see EA.
    
    virtual const CHA_SubscState& getState() const;
    // Description:
    //     Get the current state for the subscription.
    // Return value:
    //     A CHA_SubscState with the current state for the
    //     subscription. 

    virtual void setState(CHA_SubscState s);
    // Description:
    //     Set the current state for the subscription. This routine does NOT
    //     effect the value in the subscription databas, to effect it you
    //     should use activate and suspend.
    //     The routine exists to set the value when information is read
    //     from the subscription database.
    // Parameter:
    //     s              A CHA_SubscState with the current state for the
    //                    subscription. 

    virtual void setName(const RWCString& n);
    // Description:
    //     Set the name of the subscription.
    // Parameters:
    //     n                    the name of the subscription
    
    virtual const RWCString& getName() const;
    // Description:
    //     Get the name of the subscription.
    // Return value:
    //     A RWCString with the current name of the subscription. 

    virtual void setInterval(const CHA_SubscInterval& s);
    // Description:
    //     Set the time interval for the subscription.
    // Parameters:
    //     s                    the subscription interval
    
    virtual const CHA_SubscInterval& getInterval() const;
    // Description:
    //     Get the time Interval for the subscription.
    // Return value:
    //     A CHA_SubscInterval with the current interval for the
    //     subscription. 
    
    virtual void setRoutingCase(const CHA_RoutingCase& rc);
    // Description:
    //     Set the routing case for the result of the subscription.
    // Parameters:
    //     rc                   the routing case
    
    virtual CHA_RoutingCase& getRoutingCase();
    virtual const CHA_RoutingCase& getRoutingCase() const;
    // Description:
    //     Get the routing case for the result of the subscription.
    // Return value:
    //     A CHA_RoutingCase with the current routing case for the
    //     execution result of the subscription. 
    
    virtual void setExternalSystem(const RWCString& e);
    // Description:
    //     Set the external system for the subscription.
    // Parameters:
    //     e                    the subscription external system
    
    virtual const RWCString& getExternalSystem() const;
    // Description:
    //     Get the external system for the subscription.
    // Return value:
    //     A RWCString with the current external system for the
    //     subscription. 
    
    virtual void setReportIdentity(
	const RWTValOrderedVector<CHA_ReportIdentity>& r);
    // Description:
    //     Set the report identities for the subscription.
    // Parameters:
    //     r                    the report identities
    
    virtual const RWTValOrderedVector<CHA_ReportIdentity>&
    getReportIdentity() const;
    // Description:
    //     Get the report identity for the subscription.
    // Return value:
    //     A RWCString with the current report identity for the
    //     subscription. 

    virtual void setSubscriptionId(const long& s);
    // Description:
    //     Set the identity of the subscription.
    // Parameters:
    //     s                    the identity
    
    virtual const long getSubscriptionId() const;
    // Description:
    //     Get the identity of the subscription.
    // Return value:
    //     A long with the identity of the subscription. 

    virtual CHA_Subsc& operator=(const CHA_Subsc& s);
    // Description:
    //     Assignmentoperator, required by TOOL
    // Parameter:
    //     s                    the original subscription

    virtual int operator==(const CHA_Subsc& s) const;
    // Description:
    //     Equallity operator, required by TOOL
    // Parameter:
    //     s                    the subscription that is to be compared 

private:
    CHA_SubscState state;
    RWCString name;
    CHA_SubscInterval schedule;
    CHA_RoutingCase resultRouting;
    RWCString externalSystem;
    RWTValOrderedVector<CHA_ReportIdentity> reportIdentity;
    long subscId;
};

#endif

