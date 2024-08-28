#ifndef TAS_TC_TIME_CONTROL_HH
#define TAS_TC_TIME_CONTROL_HH

//**********************************************************************
// 
// .NAME TAS_TC_time_control -  Used to add and remove command requests.
// .LIBRARY 3C++
// .HEADER  TAS TC
// .INCLUDE tas_tc_time_control.hh

// .SECTION COPYRIGHT
//  COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1995
//
// The Copyright to the computer program(s) herein
// is the property of Ericsson Hewlett-Packard Telecom AB, Sweden.
// The program(s) may be used and/or copied with the
// written permission from Ericsson Hewlett-Packard Telecom AB or in
// accordance with the terms and conditions stipulated
// in the agreement/contract under which the program(s)
// have been supplied.
// 

// .SECTION DESCRIPTION 
//      TAS_TC_time_control is used to add and remove command requests.
//      A list if all requests can be retrieved, as well as a list of
//      all possible users.

// .SECTION ERROR HANDLING
//	No error reports are sent to PMS.
//      The return values are described in each method.

// DOCUMENT NO
//	27/19055-CAA 134 420

// AUTHOR 
//      1990-03-28 by TX/HJL Anders Olander

// .SECTION REVISION
//      D
//      1995-05-05

// CHANGES
// 	<Revision history>
// $Log$
//	REV NO	DATE 	   NAME	                  DESCRIPTION
//      B       1992-02-13 TM/HJG Gunni Kallander Make it possible to use
//                                                GENMAN
//      C	1993-07-08 JV/PBJ Erika Biesse 	  Method is_cron_changed added.
//                                                GENMAN
//      D       1995-05-05 PBJ Gunni Kallander	  Hint to use the | operator 
//					          in tas_tc_com_entry for
//					  	  the list command

// .SECTION SEE ALSO 
// 	TAS_TC_com_entry


//**********************************************************************

#include <tas_tc_com_entry.hh>
#include <tctrl_local.hh>
#include <tctrl_remote.hh>

class  TAS_TC_time_control {
       friend class Local;

public:
      
  TAS_TC_time_control ();
  // Description:
  //    Constructor
  // Parameters:
  //    -
  // Return value:
  //    -
  // Additional information
  //    -

  ~TAS_TC_time_control ();
  // Description:  
  //    Destructor
  // Parameters:   
  //    -
  // Return value: 
  //    -
  // Additional information:
  //    -

  int get_error_code();
  // Description:
  //    Returns an error code
  // Parameters:
  //    -
  // Return value:
  //   -3	TTC_SERVER has no value
  //	0	OK
  //	1	Internal Error
  //	2	Authority Error
  //	3	Job already in queue
  //	4	Job does not exists in queue	
  //	5	Job not inserted. Time to execution too short, or passed.	
  // Additional information:
  //    -

  int add (TAS_TC_com_entry);
  int add (TAS_TC_com_entry *);
  // Description:  
  //    Adds another command request to the time queue.
  // Parameters:   
  //    TAS_TC_com_entry        The command request to be added
  // Return value: 
  //    0                       Success
  //    negative                Failure
  // Additional information:
  //    -

  int remove (TAS_TC_com_entry);
  // Description:  
  //    Removes one command request from the queue.
  // Parameters:   
  //    TAS_TC_com_entry        The command request cancelled
  // Return value: 
  //    0                       Success
  //    negative                Failure
  // Additional information:
  //    -

  TAS_TC_com_entry *list(char *User = (char *)0);
  // Description:
  //    Retrives the information belonging to the user stored by the
  //    time control facility.
  // Parameters: 
  //    char *user_name         Name of user, whose entries are subject to
  //                            interest. When no user name is supplied, the
  //                            entries of the effective user will be returned.
  // Return value: 
  //    Array of command 
  //	request entries 	Success
  //    Null pointer            Failure
  // Additional information:
  //    Memory space is allocated dynamically for the null-terminated 
  //    TAS_TC_com_entry array.
  //    The memory should be freed with delete when the array is not needed.
  //
  //	Use the | operator in TAS_TC_com_entry when looping over the array.
  //	The array is always terminated with an TTCB_CE_EMPTY object.	

  char **users ();
  // Description:  
  //    Lists all users utilizing the time control facility.
  // Parameters:   
  //    -
  // Return value: 
  //    String array containing user_names of users
  //    using the control facility                      Success
  //    Null pointer                                    Failure
  // Additional information:
  //    The memory should be freed with delete when the array is not needed.
  //
  //    If other packages use crontab services, users using such packages
  //    might be included as well.
  //
  //    Users that have used the crontab services but don't use them any 
  //    more will be included in the list. 

  int is_cron_changed ();
  // Description:  
  //    Checks if the crontab file of the effective user has been modified 
  //    since last accessed by this instance.
  // Parameters:   
  //    -
  // Return value: 
  //    1                       True
  //    0                       False
  //    negative                Failure
  // Additional information:
  //    -

  int is_scheduled (int id, const char* user);
  // Description:  
  //    Checks if the id for a TAS_TC_com_entry is present in the users 
 // crontab file  
  // Parameters:   
  //    -
  // Return value: 
  //    1                       True
  //    0                       False
  //    negative                Failure
  // Additional information:
  //    -

  int is_scheduled (TAS_TC_com_entry);
  // Description:  
  //    Checks if a TAS_TC_com_entry is present in the crontab file  
  // Parameters:   
  //    -
  // Return value: 
  //    1                       True
  //    0                       False
  //    negative                Failure
  // Additional information:
  //    -


private:   		//N.B. Optional, but a good rule!
  Remote *remote;
  Local *local;

  int among_aliases(char *server);


}; 

#endif 
