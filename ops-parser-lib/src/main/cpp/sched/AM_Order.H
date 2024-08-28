//*****************************************************************************
// 
// NAME
//		 AM_Order

// .COPYRIGHT
//  COPYRIGHT Ericsson Hewlett-Packard telecommunications AB 1999
//
// The Copyright to the computer program(s) herein is the
// property of Ericsson Hewlett-Packard Telecommunications AB, Sweden.
// The program(s) may be used and/or copied with the
// written permission from Ericsson Hewlett-Packard Telecommunications AB
// or in accordance with the terms and conditions stipulated
// in the agreement/contract under which the program(s)
// have been supplied.
// 

// .DESCRIPTION 
// 	Class AM_Order is used to specify all the data that defines a time
//	activated order for a command file or a system command file.


// DOCUMENT NO
//	190 55-CXC 134 998

// AUTHOR 
// 	1992-05-29  EME/TY/O Ricardo Cordon itsrcma@madrid.ericsson.se

//*****************************************************************************

#ifndef AM_ORDER_H
#define AM_ORDER_H

#include <CHA_Globals.H>
//#include <eac.H>
#include <time.h>

//Globals
const int AM_NOT_DEFINED = -99;
const int AM_PARAMETERS_MAX_LEN = CHA_PARAMETERS_STORED_LEN;
const int AM_MAX_FILENAME_LEN = CHA_CMD_FILE_NAME_STORED_LEN;
/*/const int AM_MAX_EXTSYSTEM_LEN = EAC_ES_NAME_LEN;*/
const int AM_MAX_USERID_LEN = 255;
const int AM_MAX_ROUTING_LEN = 1000;
const int AM_MAX_MAILADDRESS_LEN = 40;

//Return values
const int AM_OK     =  0;    //The method has been succesfully executed
const int AM_ERROR  = -1;    //Some error has been detected
const int AM_ILLEGAL_ARGUMENT    = -2;
const int AM_NON_PROPER_STATUS   = -3;
const int AM_DATA_BASE_FULL      = -4;
const int AM_KEY_NOT_FOUND       = -5;
const int AM_NO_MEMORY           = -6;
const int AM_DATE_FORMAT_ERR  = -7;
const int AM_TIME_FORMAT_ERR  = -8;
const int AM_MONTH_RANGE_ERR  = -9;
const int AM_DAY_RANGE_ERR    = -10;
const int AM_HOUR_RANGE_ERR   = -11;
const int AM_MINUTE_RANGE_ERR = -12;
const int AM_OLD_DATE = -13;

const int AM_JOBEXISTS = -14;
const int AM_TIMEERR = -15;
const int AM_JOBNOTEXIST = -16;

const int AM_YEAR_RANGE_ERR = -17;

const int AM_NO_EXEC_PATH_ERR = -18;

//For Interval.split when WEEKLY is specified
const int AM_MONDAY     = 1;
const int AM_TUESDAY    = 2;  
const int AM_WEDNESDAY  = 3;
const int AM_THURSDAY   = 4;
const int AM_FRIDAY     = 5;
const int AM_SATURDAY   = 6;
const int AM_SUNDAY     = 0;

//For status of the Order
const int AM_ACTIVE	= 0;
const int AM_CANCELLED 	= 1; 
const int AM_IDLE	= 2;
const int AM_SCHEDULED	= 3;
const int AM_COMPLETED	= 4;

//Maximum value for the key of an Order
const unsigned long AM_ORDER_KEY_MAX_VALUE = 2147483647;
const int AM_KEY_STRING_MAX_LEN = 12;

//This value can not be assigned to an Order. It is reserved for
//internal use. The minimum value for a key is therefore 2.
const int AM_RESERVED_KEY = 1;

// TRUE and FALSE get defined so many times,
// let's not get in the way of other definitions.
#ifndef TRUE
const int TRUE = 1;
#endif
#ifndef FALSE
const int FALSE = 0;
#endif
 
enum AM_Interv 
{ 
    AM_HOURLY, 
    AM_DAILY, 
    AM_WEEKLY, 
    AM_MONTHLY, 
    AM_ANNUALLY, 
    AM_NONE
};

struct AM_Interval
{
    enum AM_Interv	intervalBase;
    int 		split;
};

struct AM_OrderData 
{
    long 		orderKey;
    int 		orderType;
    char* 		filename;
    char* 		networkElement;
    char*		userId;
    int			status;
	char*		outputDest;
    char*		immRouting;
    char*		delRouting;
	int			synchro;
    char*		mailOutputDest;
    char*		fileOutputDest;
    char*		printOutputDest;
    time_t 		startTime;
    AM_Interval 	interval;
    char*		mailAddress;
    unsigned int	funcBusyInterval;
    int			stopContNA;
    int			stopContPE;
    int			mailError;
    int			mailResult;
    int			outMsgMail;
    char*		parameters;
    char*       host;
    char*       OZTLabel;
    char*       OZTDisplay;    
    int         tasId;
    int         OZTDisplayOn;    
    time_t      timestamp;
};



class AM_Order
{

    public:

	AM_Order();
	// Description:
	//     Constructor of the Order class.
	//
	// Parameters:
	//	-
	// Return value:
	//	-
	// Additional information:
	//	-


	~AM_Order();
	// Description:
	//	Destructor of the Order class.
	//
	// Parameters:
	//	-
	// Return value:
	//	-
	// Additional information:
	//	-


	int setOrderData(const char* filename,
			   const char*	networkElement,
			   const char* 	userId,
			   const int 	status,    
			   const char* 	mailOutputDest,    
			   const char* 	fileOutputDest,
			   const char* 	printOutputDest,
			   time_t 	startTime,    
    		   AM_Interval  interval,
			   const char* 	errorMailAddress,
			   const unsigned int funcBusyInterval,
			   const int	stopContNA,
  			   const int	stopContPE,
			   const int	mailError,
			   const int	mailResult,
				const int synchro,
			   const char*  host,
			   const int    tasId = 0,
			   time_t       timestamp = 0);
	//Description:
	//	This function defines the data necessary to perform an
	//	Order for a MML file.
	//
	//Parameters:
	//	filename	IN.	User command file name
	//	networkElement	IN.	External System name.
	//	userId		IN.	User identity.
	//	status		IN.	Order Status.
	//	mailOutputDest	IN.	String with mail address for routing
	//				of all responses.
	//	fileOutputDest	IN.	String with file name for routing
	//				of all responses.
	//	printOutputDest	IN.	String with printer name for routing
	//				of all responses.
	//	startTime	IN.	Start Date & Time.
	//	interval	IN.	structure containing information about
	//				repetition frequency.
    //	errorMailAddress     IN.     Mailaddress
	//	funcBusyInterval IN.	Function Busy Retry Period in minutes.
	//	stopContNA	IN.	Flag indicating if execution should
	//				continue (1) or not (0) after NOT ACCEP.
	//	stopContPE	IN.	As above, for PARTLY EXECUTED.
	//	mailError	IN.	Flag indicating if execution error should
	//  			be mailed or not.
	//	mailResult	IN.	Flag for mailing/not mailing the 
	//				Execution Result.
	//	synchro		IN. Flag for asynchron/synchron reception of delayed
	//				responses
        //	host 		IN.	Host 
	//	tasId           IN.     Unique id from tas/Crontab
	//	timestamp	IN.	Time when order was last saved. 
	//
	//Return value:
	//	AM_OK                 No error state
	//	AM_ILLEGAL_ARGUMENT   Any of the aguments is wrong.
    //      AM_NO_MEMORY          Unable to allocate memory.

  int setOrderData (int orderType,
		    const char* 	filename,
		    const char* 	userId,
		    const int 	status,    
		    time_t 	startTime,    
		    AM_Interval  interval,
		    const int	outMsgMail,
		    const char*  parameters,
		    const char*  host,
		    const int    tasId = 0,
		    time_t       timestamp = 0);
	//Description:
	//	This function defines the data necessary to perform an
	//	order for a system command file or an EME script
	// 
	//Parameters:
	//	orderType	IN:	Type of order, 2=CFH or 3=EME
	//	filename	IN.	User command file name.
	//	userId		IN.	User identity.
	//	status		IN.	Order Status.
	//	startTime	IN.	Start Date & Time.
	//	interval	IN.	structure containing information about
	//				repetition frequency.
	//	outMsgMail	IN.	Flag for mailing the output messages.
	//	parameters	IN.	Parameters for the Syst. Cmd. File
        //	host 		IN.	Host 
	//	tasId           IN.     Unique id from tas/Crontab
	//	timestamp	IN.	Time when order was last saved. 
	//
	//Return value:
	//	AM_OK                 No error state.
	//	AM_ILLEGAL_ARGUMENT   Any of the aguments is wrong.
        //      AM_NO_MEMORY          Unable to allocate memory.

 
	int setOrderData ( const char* 	filename,
			   const char* 	extSystem,
			   const char* 	userId,
			   const int 	status,    
			   time_t 	startTime,    
    			   AM_Interval  interval,
			   const char* 	mailAddress,
			   const char*  host,
			   const char*  OZTLabel,
			   const char*  OZTDisplay,
			   const char* 	mailOutputDest,    
			   const char* 	fileOutputDest,
			   const char* 	printOutputDest,
			   const int    tasId = 0,
               const int    OZTDisplayOn = FALSE,
			   time_t       timestamp = 0);
	//Description:
	//	This function defines the data necessary to perform an
	//	Order for a command file when OZTerm is installed
	//
	//Parameters:
	//	filename	IN.	User command file name
	//	extSystem	IN.	External System name.
	//	userId		IN.	User identity.
	//	status		IN.	Order Status.
	//	startTime	IN.	Start Date & Time.
	//	interval	IN.	structure containing information about
	//				repetition frequency.
        //	mailAddress     IN.     Mailaddress
        //	host 		IN.	Host 
	//	OZTLabel        IN.     Label used by OZterm to jump to in a
   	//				oz-command file.
	//	OZTDisplay      IN.     Display name to be used to open OZTerm
        //                              gui.
	//	mailOutputDest	IN.	String with mail address for routing
	//				of all responses.
	//	fileOutputDest	IN.	String with file name for routing
	//				of all responses.
	//	printOutputDest	IN.	String with printer name for routing
	//				of all responses.
	//	tasId           IN.     Unique id from tas/Crontab
	//	timestamp	IN.	Time when order was last saved. 
	//	OZTDisplayOn    IN.     If the display is on the OZtermscript
   	//			       uses the OZTDisplay for graphical output.
   		//	timestamp	IN.	Time when order was last saved. 
	//
	//Return value:
	//	AM_OK                 No error state
	//	AM_ILLEGAL_ARGUMENT   Any of the aguments is wrong.
        //      AM_NO_MEMORY          Unable to allocate memory.

			
	int getOrderData(AM_OrderData *& orderData);
	// Description:
	//	Retrieves all data related to an Order object.
	//
	// Parameters:
        //      orderData     OUT:	Pointer to an AM_OrderData structure.
	//
	// Return values:
	//	AM_OK            No error
        //      AM_NO_MEMORY     Unable to allocate memory.	



        int setKey(long orderKey);
        //Description:
        //      This function sets the value of a key of an Order.
        //
        //Parameters:
        //      orderKey     IN:
        //      Value to give to the key of the order.
        //
        //Return values:
	//	AM_OK                 No error state
	//	AM_ILLEGAL_ARGUMENT   Any of the aguments is wrong
        
        

      

private:

	AM_OrderData 	orderData; // data related to the Order

	int returnFault(int errorCode);



};

#endif  










