//**********************************************************************

// NAME
//		AM_OrderStorage.C

// COPYRIGHT
// COPYRIGHT Ericsson Hewlett-Packard AB 1999
//
// The Copyright to the computer program(s) herein is the
// property of Ericsson Hewlett-Packard Telecommunications AB, Sweden.
// The program(s) may be used and/or copied with the
// written permission from Ericsson Hewlett-Packard Telecommunications AB
// or in accordance with the terms and conditions stipulated
// in the agreement/contract under which the program(s)
// have been supplied.
//

// DOCUMENT NO
//	190 55-CXC 134 998

// AUTHOR
// 	1992-05-29 by EME/TY/O Ricardo Cordon itsrcma@madrid.ericsson.se

//**********************************************************************

//#include <ndbm.h>
#include <sys/file.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

//#include <cap_ter.H>
#include <AM_OrderStorage.H>
#include <AM_auxFunctions.H>
#include <CHA_Trace.H>

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"AM_OrderStorage", (char*)"C");

//*****************************************************************************
//#if defined __hpux || defined SunOS5
/*This fix for TMOS/HP is recorded in prima as C++.89  */

#define LOCK_SH 1
#define LOCK_EX 2
#define LOCK_NB 4
#define LOCK_UN 8

int flock (int fd, int operation)
{
   struct flock fl;

   switch (operation & ~LOCK_NB){
   case LOCK_SH:
	fl.l_type = F_RDLCK;
	break;
   case LOCK_EX:
   	fl.l_type = F_WRLCK;
   	break;
  default:
    	fl.l_type = F_UNLCK;
	break;
  }
  fl.l_whence = SEEK_SET;
  fl.l_start = fl.l_len = 0L;

  return fcntl (fd, (operation & LOCK_NB) ? F_SETLK : F_SETLKW, &fl );
};
//#endif

//*****************************************************************************

const char  AM_DB_NAME[]      = "am_base";
const char  AM_DB_SUFFIX[]    = ".pag";
const char  AM_DB_MAP_FILE[]  = "cha_order_storage";
const char  AM_DB_WORKING_DIR[] = "AM_dir";


//*****************************************************************************
//TORF-241666
//#if defined __hpux || defined SunOS5
//This fix for TMOS/HP is recorded in PRIMA as C++.1
// include for close
#include <unistd.h>
//#else
//This fix for TMOS/HP is recorded in PRIMA as C++.90
//EXTERN_FUNCTION (int close, (int));
//#endif


//*****************************************************************************

AM_OrderStorage::AM_OrderStorage()
{
    firstKey = NULL;
    currentKey = NULL;
    //pdbInstance = NULL;
    lockFile = 0;
}

//*****************************************************************************

AM_OrderStorage::~AM_OrderStorage()
{
    if (firstKey != NULL )
    {
        delete firstKey;
        firstKey = NULL;
    }
    currentKey = NULL;
   /* if (pdbInstance != NULL)
    {
        delete pdbInstance;
        pdbInstance = NULL;
    }*/
}

//*****************************************************************************

//----------------------------------------------------------------------------
// The reserved key with value "1" will contain in every moment the last key
// assigned. This function begins at this value and increases it consecutively
// until it is found a value that is not a key in the data base.
//----------------------------------------------------------------------------

long
AM_OrderStorage::getFreeKey()
{
    long   	baseValue;
    char   	counterString[AM_KEY_STRING_MAX_LEN];
    long   	counter;
    char*  	dataBaseFile;
   // DBM*   	db;
    int    	isFound=0;
    //datum  	key, keyValue, content, assignedKey;
    char   	freeKeyString[AM_KEY_STRING_MAX_LEN];
    long   	freeKey;
    char   	reservedKeyString[AM_KEY_STRING_MAX_LEN];
    int    	result;
    char text[15];
    /*result = getDataBaseFile(dataBaseFile);
    if (result == AM_DB_NO_MEMORY)
	return result;
    else
	if (result == AM_DB_ACCESS_ERROR)
	    return result;
	else
	    if (result != AM_DB_OK)
	    {
		// Unexpected result.
    		return AM_DB_ACCESS_ERROR;
	    }

  // db = dbm_open (dataBaseFile, O_RDWR, 0666);
    delete []dataBaseFile;
    dataBaseFile = NULL;*/
   /* if (db == NULL)
    {
	return errorResult = AM_DB_ACCESS_ERROR;
    }
    else
    {
    strcpy(reservedKeyString, AM_auxFunctions::ltoa(AM_RESERVED_KEY,text));
    key.dsize = strlen(reservedKeyString)+1;
    key.dptr = new char [key.dsize];
    if (key.dptr == NULL)
    {
        dbm_close(db);
        return errorResult = AM_DB_NO_MEMORY;
    }
    strcpy(key.dptr, reservedKeyString);
*/
    //----------------------------------------------------------------------
    // In case the reseved key was not already inserted into the data base
    // it is inserted now. If it was already inserted, nothing will happen
    // because the dbm_store system call will return 1 and the initial value
    // for the reserved key will not be inserted.
    //----------------------------------------------------------------------
/*
    keyValue.dsize = strlen(reservedKeyString)+1;
    keyValue.dptr = new char [keyValue.dsize];
    if ( keyValue.dptr == NULL )
    {
        delete []key.dptr;
	key.dptr = NULL;
        dbm_close(db);
        return errorResult = AM_DB_NO_MEMORY;
    }
    strcpy(keyValue.dptr, reservedKeyString);
    result = dbm_store(db, key, keyValue, DBM_INSERT);

    delete []keyValue.dptr;
    keyValue.dptr = NULL;
    if (result < 0)
    {
        delete []key.dptr;
	key.dptr = NULL;
        dbm_close(db);
        return errorResult = AM_DB_ACCESS_ERROR;
    }

*/
    //--------------------------------------------------------------------
    // At this moment the reserved key will contain the last key assigned
    // and it is fetched now.
    //--------------------------------------------------------------------
 /*   content = dbm_fetch(db, key);
    delete []key.dptr;
    key.dptr = NULL;
    if (content.dptr == NULL)
    {
        //The reserved key has not been found. Installation error
        dbm_close(db);
        return errorResult = AM_DB_ACCESS_ERROR;
    }

    baseValue = atol(content.dptr);
    counter = baseValue;
    if (counter >= AM_ORDER_KEY_MAX_VALUE )
        counter = AM_RESERVED_KEY + 1;
    else counter++;
    //to avoid an infinite loop if there are no free key
    while ((!isFound) && (counter != baseValue))
    {
	strcpy(counterString, AM_auxFunctions::ltoa(counter,text));
        key.dptr = new char[strlen (counterString)+1];
        if (key.dptr == NULL)
        {
            dbm_close(db);
            return errorResult = AM_DB_NO_MEMORY;
        }
        strcpy(key.dptr, counterString);
        key.dsize = strlen(counterString) + 1;
        content = dbm_fetch(db, key);
        if ((content.dptr == NULL) && ( !strcmp(key.dptr, "1")));
        {
            //--------------------------------------------------------
            //No entry has been found for that key, therefore the key
            //is free.
            //--------------------------------------------------------
            isFound = 1;
            freeKey = atol(key.dptr);
            strcpy (freeKeyString, key.dptr);
        }
        delete []key.dptr;
	key.dptr = NULL;
        if (counter == AM_ORDER_KEY_MAX_VALUE)
            counter = AM_RESERVED_KEY + 1;
        else counter++;
    }//end of while

    if (!isFound)
    {
        dbm_close(db);
        return errorResult = AM_DB_KEY_NOT_FOUND;
    }
    else
    {
        //-----------------------------------------------------------
        // When the free key has been found, it is stored under the
        // reserved key.
        //-----------------------------------------------------------
        key.dsize = strlen(reservedKeyString)+1;
        key.dptr = new char[key.dsize];
        if (key.dptr == NULL)
        {
            dbm_close(db);
            return errorResult = AM_DB_NO_MEMORY;
        }

        strcpy(key.dptr, reservedKeyString);
        assignedKey.dsize = strlen(freeKeyString) + 1;
        assignedKey.dptr = new char[assignedKey.dsize];
        if (assignedKey.dptr == NULL)
        {
            dbm_close(db);
            delete []key.dptr;
	    key.dptr = NULL;
            return errorResult = AM_DB_NO_MEMORY;
        }
        strcpy(assignedKey.dptr, freeKeyString);

        result = dbm_store(db, key, assignedKey, DBM_REPLACE);
        delete []key.dptr;
	key.dptr = NULL;
        delete []assignedKey.dptr;
	assignedKey.dptr = NULL;
        if (result < 0)
        {
            dbm_close(db);
            return errorResult = AM_DB_ACCESS_ERROR;
        }
        dbm_close(db);
        return freeKey;
    }

    }//end of first else*/
}
/*
//*****************************************************************************

//-------------------------------------------------------------------------
// Function storeData transforms the structure pointed by orderData into one
// string and then stores it in the data base under the specified free key.
//-------------------------------------------------------------------------
int
AM_OrderStorage::storeData (long freeKey,
			    AM_OrderData* orderData,
			    int flag)
{
    char*	dataBaseFile;
    DBM*	db;
    datum       key, content;
    char   	keyString[AM_KEY_STRING_MAX_LEN];
    int    	result;
    char text[15];

    if ( (freeKey <= AM_RESERVED_KEY) || (orderData == NULL) )
	return errorResult = AM_DB_BAD_ARGUMENT;
    if ( (flag != AM_DB_INSERT) && (flag != AM_DB_REPLACE))
	return errorResult = AM_DB_BAD_ARGUMENT;

    result = getDataBaseFile(dataBaseFile);
    if ( result == AM_DB_NO_MEMORY)
	return result;
    else
	if (result == AM_DB_ACCESS_ERROR)
	    return result;
	else
	    if (result != AM_DB_OK)
	    {
	        // Unexpected result.
	        return AM_DB_ACCESS_ERROR;
	    }

    db = dbm_open (dataBaseFile, O_RDWR, 0666);
    delete []dataBaseFile;
    dataBaseFile = NULL;
    if (db == NULL)
    {
        return errorResult = AM_DB_ACCESS_ERROR;
    }
    else
    {
	strcpy(keyString, AM_auxFunctions::ltoa(freeKey,text));
        key.dsize = strlen(keyString)+1;
        key.dptr = new char[key.dsize];
        if ( key.dptr == NULL )
	{
            dbm_close(db);
            return errorResult = AM_DB_NO_MEMORY;
        }
        strcpy(key.dptr, keyString);
        content.dptr = new char[AM_DB_MAX_STRING_LENGTH];
        if ( content.dptr == NULL )
        {
            delete []key.dptr; key.dptr = NULL;
            dbm_close(db);
            return errorResult = AM_DB_NO_MEMORY;
        }
        AM_auxFunctions::structToString(orderData, content.dptr);
        content.dsize = strlen(content.dptr)+1;
        if ( (flag != AM_DB_INSERT) && (flag != AM_DB_REPLACE))
		{
			errorResult = AM_DB_BAD_ARGUMENT;
        }
        else
        {
            if (flag == AM_DB_INSERT)
				flag = DBM_INSERT;
            if (flag == AM_DB_REPLACE)
				flag = DBM_REPLACE;
            result = dbm_store(db, key, content, flag);
            delete []key.dptr;
			key.dptr = NULL;
            delete []content.dptr;
			key.dptr = NULL;
            if (result < 0)
            {
                if ( flag == DBM_INSERT )
                {
                    errorResult = AM_DB_ACCESS_ERROR;
                }
                else
					errorResult = AM_DB_KEY_DOES_NOT_EXIST;
            }
            else
			if (result == 1)
				errorResult = AM_DB_KEY_ALREADY_EXISTS;
        	else
		    if (result == 0)
				errorResult = AM_DB_OK;
			else
			{
				// Unexpected return value.
				errorResult = AM_DB_ACCESS_ERROR;
			}
        }

	dbm_close(db);
        return errorResult;
    }

}//End of storeData method

//*****************************************************************************

// -----------------------------------------------------------------------
// Function retrieveData fetches the data from the database and stores it
// in the structure pointed by orderData.
//------------------------------------------------------------------------

int
AM_OrderStorage::retrieveData(long orderKey,
                                  AM_OrderData* orderData)
{

  //TRACE_IN(trace, retrieveData, orderKey);

    char*	dataBaseFile;
    DBM*  	db;
    datum  	key, content;
    char   	keyString[AM_KEY_STRING_MAX_LEN];
    int    	result;
    char text[15];

    if ( (orderKey <= AM_RESERVED_KEY) ||
         (orderKey > AM_ORDER_KEY_MAX_VALUE) )
	return errorResult = AM_DB_BAD_ARGUMENT;
    if (orderData == NULL)
	return errorResult = AM_DB_BAD_ARGUMENT;

    result = getDataBaseFile(dataBaseFile);
    if (result == AM_DB_NO_MEMORY)
	return result;
    else
	if (result == AM_DB_ACCESS_ERROR)
	    return result;
	else
	    if (result != AM_DB_OK)
	    {
		// Unexpected result.
                return AM_DB_ACCESS_ERROR;
	    }

    db = dbm_open (dataBaseFile, O_RDWR, 0666);
    delete []dataBaseFile;
    dataBaseFile = NULL;
    if (db == NULL)
    {
        return errorResult = AM_DB_ACCESS_ERROR;
    }
    else
    {
	strcpy(keyString, AM_auxFunctions::ltoa (orderKey,text));
	key.dsize = strlen(keyString) + 1;
	key.dptr = new char [key.dsize];
	if ( key.dptr == NULL )
	{
            dbm_close(db);
            return errorResult = AM_DB_NO_MEMORY;
	}
        strcpy(key.dptr, keyString);
	content = dbm_fetch (db, key);
	delete []key.dptr;
	key.dptr = NULL;
	if (content.dptr == NULL)
	{
            dbm_close(db);
            return errorResult = AM_DB_KEY_DOES_NOT_EXIST;
	}

	//TRACE_FLOW(trace, retrieveData, "Converting to struct : " << content.dptr);

        result =AM_auxFunctions::stringToStruct ( content.dptr, orderData);

        if (result == AM_OK)
        {
            dbm_close(db);
	    return errorResult = AM_DB_OK;
	}
        else
	    if (result == AM_NO_MEMORY)
            {
                dbm_close(db);
        	AM_auxFunctions::deleteStrings(orderData);
        	return errorResult = AM_DB_NO_MEMORY;
            }
            else
            {
		// Unexpected return value.
        	AM_auxFunctions::deleteStrings(orderData);
        	dbm_close(db);
		return errorResult = AM_DB_ACCESS_ERROR;
	    }
    }

    //TRACE_OUT(trace, retrieveData, "");
}

//*****************************************************************************

//-------------------------------------------------------------------
// Function deleteData deletes the entry in the data base under the
// specified key.
//-------------------------------------------------------------------

int
AM_OrderStorage::deleteData (long orderKey)
{
    char* 	dataBaseFile;
    DBM *  	db;
    datum  	key;
    char   	keyString[AM_KEY_STRING_MAX_LEN];
    int    	result;
    char text[15];

    if ( (orderKey <= AM_RESERVED_KEY) ||
         (orderKey > AM_ORDER_KEY_MAX_VALUE) )
	return errorResult = AM_DB_BAD_ARGUMENT;

    result = getDataBaseFile(dataBaseFile);
    if (result == AM_DB_NO_MEMORY)
	return result;
    else
	if (result == AM_DB_ACCESS_ERROR)
	    return result;
        else
	    if (result != AM_DB_OK)
	    {
		// Unexpected result.
		return AM_DB_ACCESS_ERROR;
	    }

    db = dbm_open (dataBaseFile, O_RDWR, 0666);
    delete []dataBaseFile;
    dataBaseFile = NULL;
    if (db == NULL)
    {
	return errorResult = AM_DB_ACCESS_ERROR;
    }
    else
    {
	strcpy(keyString, AM_auxFunctions::ltoa (orderKey,text));
        key.dsize = strlen (keyString) + 1;
        key.dptr = new char[key.dsize];
        if ( key.dptr == NULL )
        {
            dbm_close(db);
            return errorResult = AM_DB_NO_MEMORY;
        }
	strcpy(key.dptr, keyString);
   	result = dbm_delete(db, key);
    	delete []key.dptr;
	key.dptr = NULL;
    	if (result < 0)
	    errorResult = AM_DB_KEY_DOES_NOT_EXIST;
	else
	    if (result == 0)
		errorResult = AM_DB_OK;
    	    else
    	    {
        	//Unexpected return value.
        	errorResult = AM_DB_ACCESS_ERROR;
    	    }

    	dbm_close(db);
    	return errorResult;
    }
}

//*****************************************************************************

//----------------------------------------------------------------------------
// Function getStatus gets the status data of an Order whose data is
// stored in the data base.
//----------------------------------------------------------------------------

int
AM_OrderStorage::getStatus(long orderKey)
{
    int 		result;
    int    		status;
    AM_OrderData*	orderData;

    if ( (orderKey < AM_RESERVED_KEY) ||
         (orderKey > AM_ORDER_KEY_MAX_VALUE) )
   	return AM_DB_BAD_ARGUMENT;

//    orderData = new AM_OrderData;
    orderData = AM_auxFunctions::getAM_OrderDataObject();

    if (orderData == NULL)
    {
        return errorResult = AM_DB_NO_MEMORY;
    }
    result = retrieveData(orderKey, orderData);
    if (result != AM_DB_OK)
    {
        switch (result)
        {
            case AM_DB_ACCESS_ERROR:
            case AM_DB_KEY_DOES_NOT_EXIST:
            case AM_DB_NO_MEMORY:
                errorResult = result;
                break;
            default: // Including AM_DB_BAD_ARGUMENT
                //Unexpected returnValue.
                errorResult = AM_DB_ACCESS_ERROR;
                break;
        }
        delete orderData;
	orderData = NULL;
        return errorResult;
    }
    status = orderData->status;
    AM_auxFunctions::deleteStrings(orderData);
    delete orderData;
    orderData = NULL;
    return status;
}

//*****************************************************************************

//----------------------------------------------------------------------------
// Function getDateTime gets the start date&time data of an Order whose data is
// stored in the data base.
//----------------------------------------------------------------------------

time_t
AM_OrderStorage::getDateTime(long orderKey)
{
    int 		result;
    time_t    		dateTime;
    AM_OrderData*	orderData;

    if ( (orderKey < AM_RESERVED_KEY) ||
         (orderKey > AM_ORDER_KEY_MAX_VALUE) )
   	return AM_DB_BAD_ARGUMENT;

//    orderData = new AM_OrderData;
    orderData = AM_auxFunctions::getAM_OrderDataObject();

    if (orderData == NULL)
    {
        return errorResult = AM_DB_NO_MEMORY;
    }
    result = retrieveData(orderKey, orderData);
    if (result != AM_DB_OK)
    {
        switch (result)
        {
            case AM_DB_ACCESS_ERROR:
            case AM_DB_KEY_DOES_NOT_EXIST:
            case AM_DB_NO_MEMORY:
                errorResult = result;
                break;
            default: // Including AM_DB_BAD_ARGUMENT
                //Unexpected returnValue.
                errorResult = AM_DB_ACCESS_ERROR;
                break;
        }
        delete orderData;
	orderData = NULL;
        return errorResult;
    }
    dateTime = orderData->startTime;
    AM_auxFunctions::deleteStrings(orderData);
    delete orderData;
    orderData = NULL;
    return dateTime;
}

//*****************************************************************************

//----------------------------------------------------------------------------
// Function setStatus set the status data of an Order whose data is
// stored in the data base. In order to do it, first the current data is
// retrieved form the data base, then the status field is changed, and finally
// the data is stored once again under the same key (replaced).
//----------------------------------------------------------------------------

int
AM_OrderStorage::setStatus (long orderKey, int status)
{
    AM_OrderData*	orderData;
    int    		result;

    if  ( (orderKey <= AM_RESERVED_KEY) ||
          (orderKey > AM_ORDER_KEY_MAX_VALUE) )
        return errorResult = AM_DB_BAD_ARGUMENT;

    if ((status != AM_ACTIVE) && (status != AM_CANCELLED) &&
	(status != AM_SCHEDULED) && (status != AM_COMPLETED) &&
	(status != AM_IDLE))
    	return errorResult = AM_DB_BAD_ARGUMENT;

//    orderData = new AM_OrderData;
    orderData = AM_auxFunctions::getAM_OrderDataObject();

    if (orderData == NULL)
    {
        return errorResult = AM_DB_NO_MEMORY;
    }
    result = retrieveData(orderKey, orderData);
    if (result != AM_DB_OK)
    {
        switch (result)
        {
            case AM_DB_ACCESS_ERROR:
            case AM_DB_KEY_DOES_NOT_EXIST:
            case AM_DB_NO_MEMORY:
                errorResult = result;
                break;
            default: // Including AM_DB_BAD_ARGUMENT
                //Unexpected returnValue.
                errorResult = AM_DB_ACCESS_ERROR;
                break;
        }
        delete orderData;
	orderData = NULL;
        return errorResult;
    }

    orderData->status = status;
    result = storeData(orderKey, orderData, AM_DB_REPLACE);
    switch (result)
    {
       case AM_DB_OK:
       case AM_DB_ACCESS_ERROR:
       case AM_DB_KEY_DOES_NOT_EXIST:
       case AM_DB_NO_MEMORY:
            errorResult = result;
            break;
       default: // Including AM_DB_BAD_ARGUMENT
            //Unexpected returnValue.
            errorResult = AM_DB_ACCESS_ERROR;
            break;
    }
    AM_auxFunctions::deleteStrings(orderData);
    delete orderData;
    orderData = NULL;
    return errorResult;
}

//*****************************************************************************

//----------------------------------------------------------------------------
// Function setTasId set the tasId of an Order whose data is
// stored in the data base. In order to do it, first the current data is
// retrieved form the data base, then the tasId field is changed, and finally
// the data is stored once again under the same key (replaced).
//----------------------------------------------------------------------------

int
AM_OrderStorage::setTasId (long orderKey, int tasId)
{
    AM_OrderData*	orderData;
    int    		result;

    if  ( (orderKey <= AM_RESERVED_KEY) ||
          (orderKey > AM_ORDER_KEY_MAX_VALUE) )
        return errorResult = AM_DB_BAD_ARGUMENT;

    orderData = AM_auxFunctions::getAM_OrderDataObject();

    if (orderData == NULL)
    {
        return errorResult = AM_DB_NO_MEMORY;
    }
    result = retrieveData(orderKey, orderData);
    if (result != AM_DB_OK)
    {
        switch (result)
        {
            case AM_DB_ACCESS_ERROR:
            case AM_DB_KEY_DOES_NOT_EXIST:
            case AM_DB_NO_MEMORY:
                errorResult = result;
                break;
            default: // Including AM_DB_BAD_ARGUMENT
                //Unexpected returnValue.
                errorResult = AM_DB_ACCESS_ERROR;
                break;
        }
        delete orderData;
	orderData = NULL;
        return errorResult;
    }

    orderData->tasId = tasId;
    result = storeData(orderKey, orderData, AM_DB_REPLACE);
    switch (result)
    {
       case AM_DB_OK:
       case AM_DB_ACCESS_ERROR:
       case AM_DB_KEY_DOES_NOT_EXIST:
       case AM_DB_NO_MEMORY:
            errorResult = result;
            break;
       default: // Including AM_DB_BAD_ARGUMENT
            //Unexpected returnValue.
            errorResult = AM_DB_ACCESS_ERROR;
            break;
    }
    AM_auxFunctions::deleteStrings(orderData);
    delete orderData;
    orderData = NULL;
    return errorResult;
}

//*****************************************************************************

//----------------------------------------------------------------------
// Function getFirstKey build a list with all the keys in the data base
// (except the reserved key), and return the first in the list.
//----------------------------------------------------------------------

long
AM_OrderStorage::getFirstKey()
{
    char*    	dataBaseFile;
    DBM*     	db;
    datum       key;
    KeyList*    newItem;
    int         result;

    result = getDataBaseFile(dataBaseFile);
    if (result == AM_DB_NO_MEMORY)
	return result;
    else
	if (result == AM_DB_ACCESS_ERROR)
	    return result;
	else
	    if (result != AM_DB_OK)
	    {
    	    	// Unexpected result.
    		return AM_DB_ACCESS_ERROR;
	    }

    db = dbm_open (dataBaseFile, O_RDWR, 0666);
    delete []dataBaseFile;
    dataBaseFile = NULL;
    if (db == NULL)
    {
        return errorResult = AM_DB_ACCESS_ERROR;
    }
    else
    {
        // If there exists a list created before, it is deleted.
    	if (firstKey != NULL)
    	{
            delete firstKey;
            firstKey = NULL;
            currentKey = NULL;
        }
        for ( key = dbm_firstkey(db); (key.dptr != NULL) && (key.dsize != 0); key = dbm_nextkey(db) )
    	{
            if ( atol(key.dptr) != AM_RESERVED_KEY )
            {
                if ( firstKey == NULL)
                {
                    firstKey = new KeyList;
                    if (firstKey == NULL )
			return AM_DB_NO_MEMORY;
                    firstKey->setKey( atol(key.dptr) );
                    currentKey = firstKey;
                }
                else
                {
                    newItem = new KeyList;
                    if ( newItem == NULL )
		    	return AM_DB_NO_MEMORY;
                    newItem->setKey( atol(key.dptr) );
                    currentKey->linkIn(newItem);
                    currentKey = newItem;
                }
            }
        }// End of for

	// Jesus inicio
        if ((key.dptr != NULL) && (key.dsize == 0))
        {
            dbm_close (db);
            return errorResult = AM_DB_FILE_CORRUPT;
        }
	// Jesus final

        if ( firstKey == NULL )
        {
            dbm_close (db);
            return errorResult = AM_DB_KEY_NOT_FOUND;
        }
        else
        {
            currentKey = firstKey->getNext();
            errorResult = AM_DB_OK;
            dbm_close(db);
            return firstKey->getKey();
        }
    }
}

//*****************************************************************************

//------------------------------------------------------------------------
// Function getNextKey returns the key of the list created by getFirstKey
// pointed by currentKey. Then the currentKey ponter is moved forward in
// the list in order to return the next key in the following call to this
// method.
//------------------------------------------------------------------------
long
AM_OrderStorage::getNextKey()
{
    long   	returnKey;

    if (currentKey == NULL)
	return errorResult = AM_DB_KEY_NOT_FOUND;
    else
    {
        returnKey = currentKey->getKey();
        currentKey = currentKey->getNext();
        return returnKey;
    }
}

//*****************************************************************************

//-----------------------------------------------------------------------------
// Function lock applies an advisory lock on one of the files of the data base.
// This file is the one with suffix ".pag". The file is open and the file
// descriptor is stored in the private member lockFile in order to unlock
// it later.
//-----------------------------------------------------------------------------

int
AM_OrderStorage::lock()
{
    char* 	dataBaseFile = NULL;
    char*	fileName = NULL;
    int 	result;

    result = getDataBaseFile(dataBaseFile);
    if ( result == AM_DB_NO_MEMORY)
	return result;
    else
	if (result == AM_DB_ACCESS_ERROR)
	    return result;
	else
	    if (result != AM_DB_OK)
	    {
    		// Unexpected result.
    		return AM_DB_ACCESS_ERROR;
	    }

    fileName = new char[strlen (dataBaseFile) +
                     strlen (AM_DB_SUFFIX) + 1];
    if (fileName == NULL)
    {
        delete []dataBaseFile;
        dataBaseFile = NULL;
        return AM_NO_MEMORY;
    }
    strcpy(fileName, dataBaseFile);
    strcat (fileName, AM_DB_SUFFIX);
    delete []dataBaseFile;
    dataBaseFile = NULL;

	lockFile = open(fileName, O_RDWR);

    delete []fileName;
    fileName = NULL;
    if (lockFile < 0)
    {
    	return errorResult = AM_DB_ACCESS_ERROR;
    }
    else
    {
     	result = flock (lockFile, LOCK_EX);
        if ( result < 0 )
        {
	    return errorResult = AM_DB_ACCESS_ERROR;
        }
	else
        {
	    return errorResult = AM_DB_OK;
        }
    }
}

//*****************************************************************************

//-------------------------------------------------------------------------
// Function unlock removes an advisory lock on the file previously locked.
//-------------------------------------------------------------------------

int AM_OrderStorage::unlock()
{
    int result;

    result = flock (lockFile, LOCK_UN);
    if (result < 0)
    {
        return errorResult = AM_DB_ACCESS_ERROR;
    }
    else
    {
        result = close(lockFile);
        if (result < 0)
        {
            return errorResult = AM_DB_ACCESS_ERROR;
        }
        else
            return errorResult = AM_DB_OK;
    }
}

//*****************************************************************************

int
AM_OrderStorage::getDataBaseFile(char *& dataBaseFile)
{
    int    	result;
    char*  	strValue = NULL;

	strValue = getenv("AM_DB_DIR");
    dataBaseFile = new char [strlen(strValue) + strlen(AM_DB_NAME) + 2];
    if (dataBaseFile == NULL)
    {
        return AM_DB_NO_MEMORY;
    }

    strcpy( dataBaseFile, strValue);
    strcat( dataBaseFile, "/");
    strcat( dataBaseFile, AM_DB_NAME);

    return AM_DB_OK;
}
*/
//*****************************************************************************
