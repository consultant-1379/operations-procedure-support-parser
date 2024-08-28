//**********************************************************************
// 
// .NAME
//		 AM_OrderStorage

// .COPYRIGHT
//  COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1999
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
// 	Class AM_OrderStorage handles the data base where it is stored all the 
//  information about all orders that are being carried out.
//  In order to store the information, the standard UNIX NDBM hashed key
//  data base library is used. 

// .DOCUMENT NO
//	190 55-CXC 134 998

// AUTHOR 
// 	1992-05-29  EME/TY/O Ricardo Cordon itsrcma@madrid.ericsson.se

// SEE ALSO

//**********************************************************************

#ifndef AM_ORDER_STORAGE_H
#define AM_ORDER_STORAGE_H

#include <AM_Order.H>
#include <time.h>
#include <KeyList.H>
/*/#include <cap_pdb.H>*/

const int AM_DB_MAX_STRING_LENGTH = 4080;

const int AM_DB_INSERT = 0;
const int AM_DB_REPLACE = 1;

const int AM_DB_OK                 =  0;
const int AM_DB_ACCESS_ERROR       = -1;
const int AM_DB_BAD_ARGUMENT       = -2;
const int AM_DB_KEY_NOT_FOUND      = -3;
const int AM_DB_KEY_ALREADY_EXISTS = -4;
const int AM_DB_KEY_DOES_NOT_EXIST = -5;
const int AM_DB_NO_MEMORY          = -6;
// Jesus inicio
const int AM_DB_FILE_CORRUPT       = -7;
// Jesus final



class AM_OrderStorage 
{

public:

    AM_OrderStorage();
	//Description:
	//	Constructor of the AM_OrderStorage class.
	//


    ~AM_OrderStorage();
	//Description:
	//	Destructor of the AM_OrderStorage class.
	//


    long getFreeKey();
	//Description:
    //  This function finds a unique key which has not been assigned
    //  before.
    //
    //Parameters:
    //  -
    //
    //Return value:
    //  > 0   Found key if succesfully executed.
    //  AM_DB_ACCESS_ERROR    Error accesing the NDBM data base.
    //  AM_DB_KEY_NOT_FOUND   There is no a free key in the data base.       


    int storeData (long orderKey, 
                   AM_OrderData* orderData,
                   int flag);
    //Description:
    //  This function stores the data of an order in the data base.
    //
    //Parameters:
    //  orderKey.  IN.
    //  Key under which the data is going to be stored. This key must be
    //  previously found using the getFreeKey method.   
    //
    //  orderData.  IN.
    //  Pointer to a AM_OrderData structure that contains
    //  all the data about the Order.   
    //
    //  flag.  IN.
    //  It can be:
    //     AM_DB_INSERT    insert new entries in the data base. 
    //     AM_DB_REPLACE   replace an already existing entry in the 
    //                      data base.
    //
    //Return value:
    //  AM_DB_OK                  Successfully executed.   
    //  AM_DB_ACCESS_ERROR        Error accesing the NDBM data base.
    //  AM_DB_BAD_ARGUMENT        Any of the parameters of the function has 
    //                             a value not allowed.
    //  AM_DB_KEY_ALREADY_EXISTS  The specified key already existed in the
    //                             data base and the option AM_DB_INSERT
    //                             was specified.
    //  AM_DB_KEY_DOES_NOT_EXISTS In the case AM_DB_REPLACE was given, this
    //                             return value indicates that the specified key
    //                             is not in the data base.
    //
    //Additional information:
    //  In order to store the information, this function transform the
    //  the information contained in the AM_orderData structure
    //  into one string where each field is separated by character "#" and 
    //  finished by the characters "#;".


    int retrieveData(long orderKey,
                    AM_OrderData* orderData);
    //Description:
    //  This function retrieves the data of an Order from the data base.
    //
    //Parameters:
    //  orderKey.  IN
    //  Key under which the data of the Order is stored.
    //
    //  orderData.  IN&OUT.
    //  Pointer to a AM_OrderData structure where the data about
    //  the Order will be returned after the execution of the function.
    //
    //Return value:
    //  AM_DB_OK                  Successfully executed.
    //  AM_DB_ACCESS_ERROR        Error accesing the NDBM data base.
    //  AM_DB_BAD_ARGUMENT        Any of the parameters of the function has 
    //                             a value not allowed.
    //  AM_DB_KEY_DOES_NOT_EXIST  The specified key is not in the data base.     


    int deleteData(long orderKey);
    //Description:
    //  This function deletes one entry in the data base.
    //
    //Parameters:
    //  orderKey.  IN.
    //  Key under which the Order data to be deleted is stored.
    //
    //Return value:
    //  AM_DB_OK                  Successfully executed.   
    //  AM_DB_ACCESS_ERROR        Error accesing the NDBM data base.
    //  AM_DB_BAD_ARGUMENT        Any of the parameters of the function has 
    //                             a value not allowed.
    //  AM_DB_KEY_DOES_NOT_EXIST  The specified key is not in the data base.


    
    int getStatus(long orderKey);
    //Description:
    //  This function gets the status information of an Order whose
    //  information is stored under the specified key.
    //
    //Parameters:
    //  orderKey.  IN.
    //  Key under which the data of the Order is stored.
    //
    //Return value:
    //     > 0                    Found status if succesfully executed.
    //  AM_DB_ACCESS_ERROR        Error accesing the NDBM data base.
    //  AM_DB_BAD_ARGUMENT        Any of the parameters of the function has 
    //                             a value not allowed.
    //  AM_DB_KEY_DOES_NOT_EXIST  The specified key is not in the data base.



    time_t getDateTime(long orderKey);
    //Description:
    //  This function gets the start Date&Time information of an Order whose
    //  information is stored under the specified key.
    //
    //Parameters:
    //  orderKey.  IN.
    //  Key under which the data of the Order is stored.
    //
    //Return value:
    //     > 0                    Found date&time if succesfully executed.
    //  AM_DB_ACCESS_ERROR        Error accesing the NDBM data base.
    //  AM_DB_BAD_ARGUMENT        Any of the parameters of the function has 
    //                             a value not allowed.
    //  AM_DB_KEY_DOES_NOT_EXIST  The specified key is not in the data base.



    int setStatus(long orderKey, int status);
    //Description:
    //  This function sets the status information of an Order whose
    //  information is stored under the specified key.
    //
    //Parameters:
    //  orderKey.  IN.
    //  Key under which the data of the Order is stored.
    //
    //  status.  IN.
    //  New value for the status.
    //  
    //Return value:
    //  AM_DB_OK                  Successfully executed.   
    //  AM_DB_ACCESS_ERROR        Error accesing the NDBM data base.
    //  AM_DB_BAD_ARGUMENT        Any of the parameters of the function has 
    //                             a value not allowed.
    //  AM_DB_KEY_DOES_NOT_EXIST  The specified key is not in the data base.
 
    int setTasId (long orderKey, int tasId);
    //Description:
    //  This function sets the tasId information of an Order whose
    //  information is stored under the specified key.
    //
    //Parameters:
    //  orderKey.  IN.
    //  Key under which the data of the Order is stored.
    //
    //  tasId.  IN.
    //  New value for the id from tas.
    //  
    //Return value:
    //  AM_DB_OK                  Successfully executed.   
    //  AM_DB_ACCESS_ERROR        Error accesing the NDBM data base.
    //  AM_DB_BAD_ARGUMENT        Any of the parameters of the function has 
    //                             a value not allowed.
    //  AM_DB_KEY_DOES_NOT_EXIST  The specified key is not in the data base.

    long getFirstKey();
    //Description:
    //  This function is used, together with the getNextKey function, in order
    //  to perform a linear pass through all keys in the data base. Function
    //  getFirstKey returns the first key in the data base. 
    //
    //Parameters:
    //  -
    //
    //Return value:
    //     > 0                     Found key if succesfully executed.
    //  AM_DB_ACCESS_ERROR        Error accesing the NDBM data base.
    //  AM_DB_KEY_NOT_FOUND       There are no keys in the data base, i.e.,
    //                             the data base in empty.
  

    long getNextKey();
    //Description:
    //  This function is used, together with the getFirstKey function, in order
    //  to perform a linear pass through all keys in the data base. Function
    //  getNextKey returns the next key in the data base.
    //
    //Parameters:
    //  -
    //
    //Return values:
    //     > 0                     Found key if succesfully executed.
    //  AM_DB_ACCESS_ERROR        Error accesing the NDBM data base.
    //  AM_DB_KEY_NOT_FOUND       There are no more keys in the data base.
    //                             This return code indicates the end of a 
    //                             linear pass.
    //
    //Additional information:
    //  The keys are returned in an apparently random order but they are really
    //  presented in an order that depends on a hashing function determined
    //  by the NDBM library function.


    int lock();
    //  This function applies an advisory lock on the data base.
    //
    //Parameters:
    //  -
    //
    //Return value:
    //  AM_DB_OK                  Successfully executed.   
    //  AM_DB_ACCESS_ERROR        Error performing the lock.
    
   
    int unlock();
    //  This function removes an advisory lock on the data base.
    //
    //Parameters:
    //  -
    //
    //Return value:
    //  AM_DB_OK                  Successfully executed.   
    //  AM_DB_ACCESS_ERROR        Error performing the lock.


     int getDataBaseFile(char *& dataBaseFile);
      //  This function gets the databasfile name from cha_order_storage.
      //
      //Parameters:
      //  A char pointer which will be sert to the file name
      //
      //Return value:
      //  AM_DB_OK                  Successfully executed.  
      //  AM_DB_NO_MEMORY		  Memory allocation problems
      //  AM_DB_ACCESS_ERROR        Error performing the lock.
      // This has to be public to be used by the chanhe_ndbm 
      // program which was created when the ndbm database got bigger.


private:

    int 	errorResult;
    KeyList* 	firstKey;
    KeyList* 	currentKey;
    /*/CAP_PDB* 	pdbInstance;*/
    int 	lockFile;

//   int getDataBaseFile(char *& dataBaseFile);

};

#endif  
