/*------------------------------------------------------------------------------
 *******************************************************************************
 * COPYRIGHT Ericsson 2018
 *
 * The copyright to the computer program(s) herein is the property of
 * Ericsson Inc. The programs may be used and/or copied only with written
 * permission from Ericsson Inc. or in accordance with the terms and
 * conditions stipulated in the agreement/contract under which the
 * program(s) have been supplied.
 *******************************************************************************
 *----------------------------------------------------------------------------*/

#ifndef _tauchl_t_H
#define _tauchl_t_H

//#include <TSSC.H>
//#include <TSS.hh>

#define TAU_AUTHORIZED      1
#define TAU_NOT_FOUND      -1
#define TAU_NOT_AUTHORIZED  0  
#define TAU_SUCCESS         0
#define TAU_FAIL           -2
#define TAUMXL_AO          41
#define TAUMXL_ACT         81
#define TAUMXL_ATYP        21
#define TAUMXL_OPER        21
#define NOT_CREATED       -10



class tauchl_t
{	
	private:	
		int statusFlag_m;
                int resultActivityListIterator_m;
                int resultTargetListIterator_m;
	    /*TSS::Authority_var tss_m;
       	TSSDef::TypedStringList_var resultActivityList_m;
       	TSSDef::TypedStringList_var resultTargetList_m;
		TSSDef::NamedValueList dummyArgs_m;*/

		int check_oper_ne_auth(char * oper, char * ao_name);

  // Description:
  //    Private method used only by tauchl_s. It checks if the operator has  
  //    authority to the specified ne.  
  //    
  // Parameters:
  //    oper :  user id or the operator which uses the tauchl_s class.
  //	ao   :  authority object for which authority should be yield.
  //
  // Return value:
  //    int  :  Returns TAU_AUTHORIZED if the oper is autorized to 
  //            perform activities on the specified ao. 
  //
  //            Returns TAU_NOT_AUTHORIZED if the oper is autorized to 
  //            perform activities on the specified ao. 
  //
  //            Returns TAU_FAIL if information isn't achievable. 
  // 
  // Additional information
  //    -

	int get_num_rows(char *oper, char *ao_name, char *activity, char *activity_type);
  // Description:
  //    Private method used only by tauchl_s. It checks how many commands  
  //    an operator is authorized to perform on the specified ne.  
  //    
  // Parameters:
  //    oper :  user id or the operator which uses the tauchl_s class.
  //	ao   :  authority object for which authority should be yield.
  //	activity   :  activity.
  //	activity_type   :  activity_type.
  //
  // Return value:
  //    int  :  Returns NBR_OF_ROWS or TAU_FAIL if the query fails. 
  //            perform activities on the specified ao. 
  //
  // 
  // Additional information
  //    -


		
        public:
		tauchl_t(){}
		friend class tauchl_s;

		tauchl_t(const char *server_host = 0);
  // Description:
  //    The class constructor. Creates an instance of the tauchl_t
  //    class, establishes contact with the data server and the
  //    authority data base.
  // Parameters:
  //    server_host : Name of the database server for adb. If not given, the
  //		      environment variable ADB_SERVER is used.
  // Return value:
  //    -
  // Additional information
  //    -

		~tauchl_t();
  // Description:
  //    The tauchl_t destructor. Closes the connection with the
  //    server.
  // Parameters:
  //    -
  // Return value:
  //    -
  // Additional information
  //    -


		int get_status();
  // Description:
  //    A method to check if the construction of the class instance
  //    succeeded.
  // Parameters:
  //    -
  // Return value:
  //    (Use of the symbolic names are recommended)
  //   
  //    -2: TAU_FAIL            No contact to authority database
  //     0: TAU_SUCCESS         Succeeded
  // Additional information
  //    -

                int check_activity(char *oper,
                                   char *ao_name,
                                   char *activity,
                                   char *activity_type);
  // Description:
  //    Yields the authority for the caller to perform an activity
  //    on the addressed authority object (AO).
  //
  //    The return parameter refers to the current authority
  //    according to the authority database.
  // Parameters:
  //    oper:	       The operator identification (as given in the
  //		       UNIX etc/passwd file and used for UNIX
  //		       login). No wild cards allowed. Max length of
  //		       string = TAUMXL_OPER
  //     
  //    ao_name:       The name of the authority object (AO) for
  //                   which to check authority. Max length of
  //                   string = TAUMXL_AO
  //     
  //    activity:      The name of the activity that is to be
  //                   performed on the authority object. Max
  //                   length of string = TAUMXL_ACT
  //     
  //    activity_type: The type of activity as defined in the
  //                   authority data base. Max length of string =
  //                   TAUMXL_ATYP
  // Return value:
  //    (Use of the symbolic names are recommended)
  //     
  //    -2: TAU_FAIL           Unable to achieve information
  //    0: TAU_NOT_AUTHORIZED  Operator is not authorized to 
  //                           perform activity.
  //    1: TAU_AUTHORIZED      Operator is authorized to perform
  //                           activity
  // Additional information
  //    Both activity and activity_type must match in the sample
  //    table to return TAU_AUTHORIZED.
                    

                int exec_list(char *oper,
                              char *ao_name,
                              char *activity,
                              char *activity_type);
                        
  // Description:
  //    Use to list activities.
  //    See below

  //              int exec_list(char *oper,
  //                            char *ao_name);

  // Description:
  //    Use to list Authority Objects.
  //    
  //    Prepares a list (of desired format) for the operator.
  //    
  //    The format of the list depends of the input parameter
  //    structure. There are the following overlayed calls:
  //    
  //    - list activities
  //    - list authority objects
  //    
  //    The result list refers to the current authority profile.
  // Parameters:
  //    Note: 'Wild cards' are explained in section additional
  //    information below.
  //    
  //    oper:	       The operator identification (as given in the
  //                   UNIX etc/passwd file and used for UNIX login).
  //                   No wild cards allowed. Max length of string =
  //                   TAUMXL_OPER
  //    
  //    ao_name:       The name of the authority object that is
  //                   addressed. May contain wildcard character(s).
  //                   Max length of string = TAUMXL_AO
  //    
  //    activity:      The name of the activity that is to be
  //                   performed on the authority object. 
  //                   activity may contain wildcard character(s).
  //                   Max length of string = TAUMXL_ACT
  //    
  //    activity_type: The type of activity as defined in the
  //                   authority data base.
  //                   activity_type may contain wildcard
  //                   character(s). Max length of string =
  //                   TAUMXL_ATYP
  // Return value:
  //    (Use of the symbolic names are recommended)
  //        
  //    -2: TAU_FAIL            No contact to authority database.
  //    =0:                     No rows was found for this search.
  //    =1:                     One or more rows are put in the
  //                            result list.     
  // Additional information
  //    Note that the listing contains the current authority
  //    profile, irrespective of other living tauchl_s objects.
  //    
  //    Wild card rules:
  //    '%' means any string of zero or more characters.
  //    '_' means any single character.
           


                int next_from_list(char *ao_name,
                                   char *activity,
                                   char *activity_type,
                                   char *stop_time);

  // Description:
  //    Use after list activities.
  //    See below

  //              int next_from_list(char *ao_name,
  //                                 char *stop_time);

  // Description:
  //    Use after list Authority Objects
  //
  // Parameters:
  //    ao_name:       Pointer to the string in which to store the
  //                   authority object.
  //                   Length of string should be >= TAUMXL_AO and
  //                   string space must be allocated by application.
  //
  //    activity:      Pointer to the string in which to put the
  //                   activity string.
  //                   Length of string should be >= TAUMXL_ACT and
  //                   string space must be allocated by application.
  //
  //    activity_type: Pointer to the string in which to put the
  //                   activity_type.
  //                   Length of string should be >= TAUMXL_ATYP and
  //                   string space must be allocated by application.
  //
  //    stop_time:     Pointer to the string in which to put the time
  //                   of day when the authority (concerning the
  //                   accessed row) expires. The result may contain
  //                   values from '00:00' to '24:00' meaning
  //                   corresponding time of the day.
  //                   Value '24:00' indicates that no limits in time
  //                   within the current day_and_night has been
  //                   defined in the authority database. In this
  //                   case authority may or may not continue the
  //                   next day_and_night.
  //                   Length of string should be >= 6 and string
  //                   space must be allocated by application.
  // 
  // Return value:
  //    (Use of the symbolic names are recommended)
  //     
  //    -3: TAU_BIND            Parameter structure does not match
  //                            previous exec_list call.
  //    -2: TAU_FAIL            No contact to authority database
  //    -1: TAU_NOT_FOUND       No more elements in list
  //     0: TAU_SUCCESS         Succeeded
  //           
  // Additional information
  //    -
  //
  //		char *errormsgs(int* number, int* severity);

  // Description:
  //    Returns a pointer to the error message generated from the 
  //    Database Server, or if the database isn't opened, the database 
  //    class error message. It also returns information about the number
  //    and severity of the error. 
  // Parameters:
  //    number:        A pointer to an integer where the Database Server
  //                   error number is stored.
  //    severity:      A pointer to an integer where the Database Server
  //                   severity level is stored.
  // Return value:
  //    char *         Error message.
  //                   If no message is available, null, (char *)0 is
  //                   returned.
  // Additional information
  //    If a problem generates severity levels above 16, they should be
  //    reported.


};

#endif
