// RCS handling
// $Id: CHA_DeviceModeProps.H,v 22.0.1.1 1995/09/07 07:04:26 etosad Exp $

//**********************************************************************
// 
// .NAME    CHA_DeviceModeProps - container for device mode information
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_DeviceModeProps.H 

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
//      The class CHA_DeviceModeProps contains information about
//      device mode, a mode for the AXE test system and AXE device
//      dependent commands. When device mode is changed, an object
//      of this class is passed to a CHA_CommandSender object.

// DOCUMENT NO
//      190 89-CAA 134 1517

// AUTHOR 
//      1994-03-01 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION
//	EC2_OZ
//	1995-08-01

// CHANGES
//      RCS revision history
//      $Log: CHA_DeviceModeProps.H,v $
//      Revision 22.0.1.1  1995/09/07 07:04:26  etosad
//      A lot of changes. Manu methods in this class should
//      be removed later.
//
//      Revision 22.0  1995/08/01  20:41:48  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:37:25  09:37:25  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:30:20  08:30:20  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:49:38  10:49:38  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:01:57  20:01:57  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:00:00  14:00:00  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  12:54:34  12:54:34  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  14:55:39  14:55:39  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:29:39  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:41:28  14:41:28  cmcha (*CHA conf. and dev. EHS/PXE)
//      *** empty log message ***
//      
//      Revision 12.1  95/02/15  13:56:32  13:56:32  cmcha (*CHA conf. and dev. EHS/PXE)
//      *** empty log message ***
//      
//      Revision 12.0  1995/02/06  16:08:41  cmcha
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:41:36  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  08:58:59  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:24:52  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:44:37  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:19:23  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:47:13  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:39:42  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:32:38  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:45:58  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  07:56:58  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.4  1994/06/10  16:53:41  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.3  1994/05/30  15:18:02  ehsgrap
//      Renamed event enum items to make it compile on Sun.
//
//      Revision 1.2  1994/04/07  13:35:47  ehsgrap
//      Use of enum instead of const int.
//
//      Revision 1.1  1994/03/31  13:36:20  ehsgrap
//      Initial revision
//
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	EC2_OZ  1995-08-01      Jan Sandquist (EHSJAASA)RCS rev 22.0
//	EC1_OZ  1995-06-29      J Grape (EHSGRAP)       RCS rev 21.0
//	TB5_2_OZ1995-06-08      J Grape (ehsgrap)       RCS rev 20.0
//	TB5_1_OZ1995-04-13      J Grape (EHSGRAP)       RCS rev 19.0
//	TB51_OZ 1995-03-17      ehscama                 RCS rev 18.0
//	TB5_OZ  1995-03-16      ehscama                 RCS rev 17.0
//	TB6_B1C_B1995-03-10      N.Lanninge (XKKNICL)    RCS rev 16.0
//	TB6_B1C 1995-03-09      N.Lanninge (XKKNICL)    RCS rev 15.0
//	TB4_OZ  1995-02-25      J Grape (EHSGRAP)       RCS rev 14.0
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
//      CHA_CommandSender

//**********************************************************************

#ifndef CHA_DEVMODEPROPS_H
#define CHA_DEVMODEPROPS_H


#include <CHA_Model.H>

#include <rw/tools/datetime.h>


// Minimum waiting time when device mode is off
const long int CHA_DEVMODEPROPS_MINIMUM_WAITING_TIME = 3600;

// Minimum waiting time when device mode is on
const long int CHA_DEVMODEPROPS_MINIMUM_DM_WAITING_TIME = 3600;

// CHA_DEVMODE_PROLONG_FACTOR is used when finding out
// when it is time for prolonging a subscription.
// The factor is multiplied with waiting time. The result
// is added to "right now" to get the prolonged end time for
// subscriptions. When this time is reached, a new
// subscription may take place. See also method getDmProlongEndTime().
 
const float CHA_DEVMODEPROPS_PROLONG_FACTOR = 0.80;



class CHA_DeviceModeProps : public CHA_Model
{

public:

    // event codes
    enum Event {MODE_OFF,
		MODE_OFF_TIME,
		MODE_ON,
		MODE_ON_OLD,
		MODE_ON_ID,
		MODE_ON_ID_TIME,
		MODE_ON_TIME,
		USING_ID};

    CHA_DeviceModeProps();
    // Description:
    //     Constructor.

    virtual ~CHA_DeviceModeProps();
    // Description:
    //     Destructor.

    void setModeOff();
    // Description:
    //     Sets device mode off. Waiting time is not valid. 
    //     However, waiting time is set to minimum value.

    void setModeOff(const long int wTime);
    // Description:
    //     Sets device mode off with a specified waiting time. 
    // Parameters:
    //     wTime		IN: the waiting time in seconds of the 
    // 				    delayed subscription
    void setModeOff(const RWDateTime& eTime);
    // Description:
    //     Sets device mode off with a specified waiting time. 
    //     waitingTime is set to (eTime - rightNow).
    // Parameters:
    //     eTime		IN: the end time of the delayed subscription

    void setModeOn();
    // Description:
    //     Sets device mode on. Waiting time and device ID are not valid.
    //     However, waiting time is set to minimum value.
    // Parameters:
    //     wTime		IN: the waiting time in seconds of the 
    // 				    delayed subscription

    void setModeOn(int devId);
    // Description:
    //     Sets device mode on with a specified device ID. Waiting time
    //     is not valid. However, waiting time is set to minimum value.
    // Parameters:
    //     devId		IN: the fixed device ID

    void setModeOn(int devId, const long int wtime);
    // Description:
    //     Sets device mode on with a specified device ID and a
    //     specified waiting time.
    // Parameters:
    //     devId		IN: the fixed device ID
    //     wTime		IN: the waiting time in seconds of the 
    // 				    delayed subscription

    void setModeOn(int devId, const RWDateTime& eTime);
    // Description:
    //     Sets device mode on with a specified device ID and a
    //     specified waiting time. waitingTime is set to (eTime - rightNow).
    // Parameters:
    //     devId		IN: the fixed device ID
    //     eTime		IN: the end time of the delayed subscription

    void setModeOn(const long int wtime);
    // Description:
    //     Sets device mode on with a specified waiting time for the
    //     subscription of delayed responses. Device ID is not valid.
    // Parameters:
    //     wTime		IN: the waiting time in seconds of the 
    // 				    delayed subscription

    void setModeOn(const RWDateTime& eTime);
    // Description:
    //     Sets device mode on with a specified waiting time for the
    //     subscription of delayed responses. Device ID is not valid.
    // Parameters:
    //     eTime		IN: the end time of the delayed subscription

//  void setModeOnUsingOldSettings();
    // Description:
    //     Sets device mode on. Use old settings regarding waiting time 
    //     and device ID. This means that waiting time is set if it was set
    //     the last time device mode was turned on. The same goes for
    //     device ID.

    void usingDevId(int devId);
    // Description:
    //     This method is called by the CHA_CommandSender. It sets the used
    //     deviceId to devId. Current settings are used regarding waiting time 
    //     and device mode, but the state of this object is USING_ID. 
    // Parameters:
    //     devId		IN: the fixed device ID

    RWBoolean isDevModeOn() const;
    // Description:
    //     Checks if device mode is turned on.
    // Return value:
    //     Returns TRUE if device mode is on, otherwise FALSE.

    RWBoolean isReqDeviceIdSet() const;
    // Description:
    //     Check if requested device ID is valid.
    // Return value:
    //     TRUE if requested device ID is valid, otherwise FALSE.

    RWBoolean isDeviceIdSet() const;
    // Description:
    //     Check if requested device ID is valid.
    // Return value:
    //     TRUE if requested device ID is valid, otherwise FALSE.

    RWBoolean isUsedDeviceIdSet() const;
    // Description:
    //     Check if used device ID is valid.
    // Return value:
    //     TRUE if used device ID is valid, otherwise FALSE.

    RWBoolean isWaitingTimeSet() const;
    // Description:
    //     Check if waiting time is valid.
    // Return value:
    //     TRUE if waiting time is valid, otherwise FALSE.

    RWBoolean isEndTimeSet() const;
    // Description:
    //     The same as for isWaitingTimeSet().
    // Return value:
    //     TRUE if waiting time is valid, otherwise FALSE.

    long int getWaitingTime() const;
    // Description:
    //     To get the waiting time of the subscription of delayed
    //     responses.
    // Resturn value:
    //     The waiting time in seconds.

    RWDateTime getEndTime() const;
    // Description:
    //     To get the end time of the subscription of delayed
    //     responses. The end time is set to (rightNow + waitingTime).
    // Resturn value:
    //     The waiting time in the form of a RWDateTime object.

    RWDateTime getProlongEndTime() const;
    // Description:
    //     To get the "when to prolong" end time of the subscription 
    //     of delayed responses. This time is set to
    //     (rightNow + CHA_DELSUB_DM_PROLONG_FACTOR*wTime).
    // Resturn value:
    //     The waiting time in the form of a RWDateTime object.

    int getReqDevId() const;
    // Description:
    //     To get the requested device ID. Not valid unless 
    //     isReqDeviceIdSet() returns TRUE.
    // Return value:
    //     Returns the requested device id.

    int getDevId() const;
    // Description:
    //     To get the device ID. Not valid unless isDeviceIdSet()
    //     returns TRUE.
    // Return value:
    //     Returns the device id.

    int getUsedDevId() const;
    // Description:
    //     To get the last used device ID. Not valid unless 
    //     isUsedDeviceIdSet() returns TRUE.
    // Return value:
    //     Returns the last used device id.

    Event getLastEvent();
    // Description:
    //     Can be called by ModelClients to find out why their
    //     updateFrom() method was called. An event code is returned
    //	   which the state of this object.
    // Return values:
    //     OFF	       Device mode was turned off. Device ID
    //		       and waiting time are not valid.
    //
    //     OFF_TIME    Device mode was turned off. Waiting time 
    //                 is valid, device ID is not.
    //
    //     ON          Device mode was turned on. Device ID
    //		       and waiting time are not valid. 
    //
    //     ON_OLD      Device mode was turned on using the
    //                 old settings from the previous time
    //                 device mode was on.
    //
    //     ON_ID       Device mode was turned on. Device ID
    //                 is valid, waiting time is not.
    //
    //     ON_ID_TIME  Device mode was turned on. Device ID
    //                 and waiting time are valid.
    //
    //     ON_TIME     Device mode was turned on. Waiting time 
    //                 is valid, device ID is not. 
    //
    //     USING_ID    The device ID has been updated.

private:
    
    void announceEvent(Event eventCode);
    // Description:
    //     Notifies all model clients about an event.

    
    Event 	lastEvent;

    RWBoolean 	devModeOn;

    RWBoolean 	reqDeviceIdValid;
    int		reqDeviceId;		// The requested device id to use

    RWBoolean 	usedDeviceIdValid;
    int		usedDeviceId;		// The used device id

    RWBoolean 	waitingTimeValid;	
    long int 	waitingTime;		// Waiting time is the time from
					// the subscription of delayed
					// responses starts till it expires.

};

#endif
