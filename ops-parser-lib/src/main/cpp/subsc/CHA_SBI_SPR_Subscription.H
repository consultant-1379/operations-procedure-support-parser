// RCS handling
// $Id: CHA_SBI_SPR_Subscription.H,v 24.0 1995/11/28 17:00:35 ehsgrap Rel $

//**********************************************************************
// 
// .NAME CHA_SBI_SPR_Subscription - Database calls for spontaneous reports 
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_SBI_SPR_Subscription.H 

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
//      This class provides an interface to the subscription database.
//      It is mainly used for reading and storing information in the
//      database.
//      Before returning read information or storing received information
//      the class converts the information from/to the format used by
//      the subscription database.

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
//      $Log: CHA_SBI_SPR_Subscription.H,v $
//      Revision 24.0  1995/11/28 17:00:35  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:49:32  17:49:32  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:50:26  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:47:48  09:47:48  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:38:56  08:38:56  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:58:27  10:58:27  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:11:08  20:11:08  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:13:24  14:13:24  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:05:24  13:05:24  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:12:12  15:12:12  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:38:54  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:12:21  14:12:21  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:22:53  16:22:53  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:54:27  cmcha
//      Made release PREIT, N L\ufffdnninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:08:25  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:35:14  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:56:24  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:28:08  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:55:14  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:53:41  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:45:27  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  08:00:19  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:01:37  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.4  1994/05/13  09:51:14  qhsmosc
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
// 	CHA_SubscInterval                Time interval
// 	CHA_ReportIdentity               Identity for subscribed report
//      CHA_RoutingCase                  Routing case
//      EAC_SBI_SPR_Subscription         Database calls
//      CHA_Subsc                        Subscription

//**********************************************************************

#ifndef CHA_SBI_SPR_SUBSCRIPTION_H
#define CHA_SBI_SPR_SUBSCRIPTION_H
/*
extern "C"
{
    #include <cap_ipc.h>
};
*/
/* #include <eac_sbi_spr_subscription.H>
#include <eac_sbi_spr_subscription.H>
#include <eac_sbi_subscriber.H> */
#include <rw/cstring.h>

class CHA_Subsc;

class CHA_SBI_SPR_Subscription //: public EAC_SBI_SPR_Subscription
{

public:
    
    CHA_SBI_SPR_Subscription();
    // Description:
    //     Default constructor.

    virtual ~CHA_SBI_SPR_Subscription();
    // Description:
    //     Destructor.

    virtual int fetch(CHA_Subsc& s);
    // Description:
    //     Read the order from the subscription database.
    // Parameters:
    //     s              Subscription where the information is to be held
    
    virtual int store(CHA_Subsc& s, const RWCString a);
    // Description:
    //     Store the subscription in the subscription database. Used both
    //     to insert a new order in the subscription database and to
    //     overwrite an existing order.
    // Parameters:
    //     s              Subscription to store in subscription database
    //     a              the name of the application

private:
    virtual int fetchTimes(CHA_Subsc& s);
    // Description:
    //     Moves the times and daycategories found in the subscription
    //     database to s.
    // Parameters:
    //     s              Subscription where the information is to be held
    
    virtual int fetchRouting(CHA_Subsc& s);
    // Description:
    //     Moves the routing information found in the subscription
    //     database to s.
    // Parameters:
    //     s              Subscription where the information is to be held
    
    virtual int fetchReportid(CHA_Subsc& s);
    // Description:
    //     Moves the reportidentities, name and external system found in
    //     the subscription database to s.
    // Parameters:
    //     s              Subscription where the information is to be held
    
    virtual int storeReportid(const CHA_Subsc subsc);
    // Description:
    //     Moves the reportidentities, name and external system found in
    //     s to this. The information will later be stored in the
    //     subscription database.
    // Parameters:
    //     s              Subscription where the information is held

    virtual int storeTimes(const CHA_Subsc subsc);
    // Description:
    //     Moves the time criterias found in s to this. The information
    //     will later be stored in the subscription database.
    // Parameters:
    //     s              Subscription where the information is held

    virtual int storeRouting(CHA_Subsc subsc,
			     const RWCString a);
    // Description:
    //     Moves the routing information found in s to this. The information
    //     will later be stored in the subscription database.
    // Parameters:
    //     s              Subscription where the information is held.
    //                    The parameter wont be changed, but can not be
    //                    declared CONST while the member function
    //                    getAddressList is not declared CONST!
    //     a              the name of the application

    
    //*************************************************************
    // The following functions are copied from functions used in the
    // GUI. Instead of these, EA's own functions should be used. To
    // accomplish this both these and the functions in the GUI must be
    // altered at the same time, otherwise the two version are not
    // compatible.
    
    virtual int Set_criteria_and_name(const char* ES_name,
				      long        spont_id,
				      const char* order_name);

    virtual int Set_criteria_and_name(const char* ES_name,
				      long        spont_low,
				      long        spont_high,
				      const char* order_name);
    
    virtual int Set_criteria_and_name(const char* ES_name,
				      const char* spont_id,
				      const char* order_name);
    // Description:
    //   Insert a subscription criteria. Spontaneous reports from 
    //   specified ES are subscribed to.
    //   It is possible to specify more than one criteria in each
    //   subscription.
    //   These criterias are combined using an invisible OR operator.
    // Parameters:
    //   ES_name:IN                  ES name (* and ? may be used)
    //                               An ES name may not exceed
    //                               EAC_ES_NAME_LEN chars.
    //   spont_id:IN                 An identification for the
    //                               spontaneous report. 
    //                               May be an integer value or a string
    //                               less than EAC_SBI_MAX_FILE_NAME chars.
    //                               * and ? may be used in the string.
    //   spont_low:IN                Lower limit when subscribing to a
    //                               sequence of spontaneous report
    //                               identities.
    //   spont_high:IN               Upper limit when subscribing to a
    //                               sequence of spontaneous report
    //                               identities.
    // Return value:
    //   EAC_SBI_OK                  Subscription inserted
    //   EAC_SBI_MEM_ERR             Out of memory
    //   EAC_SBI_ERR                 Error detected
    // Additional information:
    //   The tmos_error report object is initiated and sent to PMS
    //   if an error is detected.
    virtual int Set_criteria_and_name(const char* ES_name, const char* order_name);
    // Description:
    //   This format is useful for default-subscriptions. 
    //   That is when an application wants to subscribe to every
    //   spontaneous report not subscribed to by any other application.
    //   It is possible to specify more than one criteria in each
    //   subscription.
    //   These criterias are combined using an invisible OR operator.
    // Parameters:
    //   ES_name:IN                  ES name (* and ? may be used)
    //                               An ES name may not exceed
    //                               EAC_ES_NAME_LEN chars.
    //                               The subscription is valid for any
    //                               spontaneous report.
    // Return value:
    //   EAC_SBI_OK                  Subscription inserted
    //   EAC_SBI_MEM_ERR             Out of memory
    //   EAC_SBI_ERR                 Error detected
    // Additional information:
    //   The tmos_error report object is initiated and sent to PMS
    //   if an error is detected.
    
    
    virtual int Get_criteria_and_name(int          criteria_nr,
				      const char*  &ES_name,
				      int          &type_of_criteria,
				      long         &spont_low,
				      long         &spont_high,
				      const char*  &spont_id,
				      const char*  &order_name)const;
    // Description:
    //   Reads subscription information for specified criteria.
    //   Errors are indicated in the return-code but the error-report
    //   object is not initiated.
    //   The pointers delivered as out-parameters, points to variables
    //   in the object and shall not be deleted by the caller. They are
    //   deleted by the object when the object is deleted.
    // Parameters:
    //   criteria_nr:IN              criteria number for subscription
    //                               criteria to be read.
    //                               0 is the first criteria.
    //   ES_name:OUT                 External System name.
    //                               An ES name does not exceed
    //                               EAC_ES_NAME_LEN chars.
    //   type_of_criteria:OUT        Defines type of criteria returned.
    //                               Following values are used;
    //                               EAC_SBI_NO_VALUE ; no parameters returned
    //                               EAC_SBI_LOW_ONLY ; spont_low returned
    //                               EAC_SBI_RANGE    ; spont_low and 
    //                                                  spont_high returned
    //                               EAC_SBI_STRING   ; spont_id returned
    //   spont_low:OUT               Identification for spontaneous reports.
    //                               Lower limit.
    //   spont_high:OUT              Identification for spontaneous reports.
    //                               Upper limit.
    //   spont_ch_id:OUT             Identification for spontaneous report.
    //                               Does not exceed EAC_SBI_MAX_FILE_NAME
    //                               chars. May be 0.
    // Return value:
    //   >0                          Subscription information read and
    //                               returned.  Returned value indicates
    //                               next criteria to be read.
    //   =0                          Last subscription information read
    //                               and returned.
    //   -1                          Specified subscription criteria does
    //                               not exist.
    //   -2                          The type of criteria does not match 
    //                               parameter list.
    //                               Probably due to program error.
    // Additional_information:
    //   The tmos_error-report object is not initiated.

};

#endif