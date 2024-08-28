//**********************************************************************

// NAME
//		AM_auxFunctions

// COPYRIGHT
// COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1999
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

// SEE ALSO

//**********************************************************************

#ifndef AM_AUXFUNCTIONS_H
#define AM_AUXFUNCTIONS_H

class AM_OrderData;

 
#include <rw/cstring.h> 
 
 
class AM_auxFunctions
{
public:

    static char* itoa(int,char *);
    static char* ltoa(long,char *);
    static char *blank(char *,int);
    static void structToString (AM_OrderData *orderData, char *resultString);
    static int stringToStruct(char *stringData, AM_OrderData *orderData);
    static void	deleteStrings(AM_OrderData *);
    static int returnError(AM_OrderData *data);
    static int	checkDate(time_t dateTime);
    static int	checkFileRead(const char *);
    static int	checkFileExecute(const char *, const char *);
    static time_t checkDateTime(char* date, char* time);
    static char *timeToString(time_t datetime);
	static char* timeToTimeString(time_t datetime);
	static char* timeToDateString(time_t datetime);


 
    static AM_OrderData* getAM_OrderDataObject();
    // Description:
    // This method allocates an AM_OrderData object which must
    // be freed by the caller.

    static int isFoundHashMarkCrypt(const char*, char*);
    // Description:
    // Searches the first argument for the hash mark and crypt it.
    // The result string is return in the second argument.

    static int isFoundCryptedHashMarkDecrypt(const char*, char*);
    // Description:
    // Searches the first argument for the previously crypted hash mark
    // by the previous method and decrypt it. The result string is return
    // in the second argument.

};

#endif
