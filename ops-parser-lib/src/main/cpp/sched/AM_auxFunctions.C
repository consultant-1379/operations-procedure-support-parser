//**********************************************************************

// NAME
//		AM_auxFunctions.C

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


#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

#include <errno.h>
#include <stdio.h>

#include <CHA_Trace.H>
#include <AM_Order.H>
#include <AM_auxFunctions.H>
#include <sys/types.h>
#include <sys/stat.h>
#include <rw/cstring.h>
#include <strstream>
#include <nl_types.h>
#include <locale.h>

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"AM_auxFunctions", (char*)"C");

const int AM_DB_MAX_STRING_LENGTH = 4080;



//*****************************************************************************

//-----------------------------------------------------------------------------
// This function transforms the data contained in the specified
// structure into one string where every data is separated by
// the character "#".
//-----------------------------------------------------------------------------

void
AM_auxFunctions::structToString (AM_OrderData *orderData, char *resultString)
{
  //TRACE_IN(trace, structToString, "");

    char text[15];

    strcpy( resultString, ltoa(orderData->orderKey,text) );
    strcat(resultString, "#");
    strcat( resultString, itoa(orderData->orderType,text) );
    strcat(resultString, "#");

    if ( isFoundHashMarkCrypt(orderData->filename, resultString) == 0 )
        strcat (resultString, orderData->filename);
	if (strcmp(orderData->filename, "") != 0)
		strcat(resultString, "#");
	else
		strcat(resultString, " #");

    if ( isFoundHashMarkCrypt(orderData->userId, resultString) == 0 )
        strcat (resultString, orderData->userId);
	if (strcmp(orderData->userId, "") != 0)
		strcat(resultString, "#");
	else
		strcat(resultString, " #");

    strcat( resultString, itoa(orderData->status,text) );
    strcat(resultString, "#");

    strcat( resultString, ltoa(orderData->startTime,text) );
    strcat(resultString, "#");

    strcat( resultString, itoa(orderData->interval.intervalBase,text) );
    strcat(resultString, "#");

    strcat( resultString, itoa(orderData->interval.split,text) );
    strcat(resultString, "#");

    if ( isFoundHashMarkCrypt(orderData->host, resultString) == 0 )
        strcat( resultString, orderData->host );
	if (strcmp(orderData->host, "") != 0)
		strcat( resultString, "#" );
	else
		strcat(resultString, " #");

    strcat( resultString, itoa(orderData->tasId,text) );
    strcat( resultString, "#" );

    strcat( resultString, ltoa(orderData->timestamp,text) );
    strcat( resultString, "#" );

	// MML file - CFI
    if (orderData->orderType == 0)
    {
        if ( isFoundHashMarkCrypt(orderData->networkElement, resultString) == 0 )
            strcat (resultString, orderData->networkElement);
		if (strcmp(orderData->networkElement, "") != 0)
			strcat(resultString, "#");
		else
			strcat(resultString, " #");

        if ( isFoundHashMarkCrypt(orderData->outputDest, resultString) == 0 )
	    strcat (resultString, orderData->outputDest);
		if (strcmp(orderData->outputDest, "") != 0)
			strcat(resultString, "#");
		else
			strcat(resultString, " #");


        if ( isFoundHashMarkCrypt(orderData->mailAddress, resultString) == 0 )
	    strcat (resultString, orderData->mailAddress);
		if (strcmp(orderData->mailAddress, "") != 0)
			strcat(resultString, "#");
		else
			strcat(resultString, " #");

	strcat( resultString, ltoa(orderData->funcBusyInterval,text) );
        strcat(resultString, "#");

	strcat( resultString, itoa(orderData->stopContNA,text) );
	strcat(resultString, "#");

	strcat( resultString, itoa(orderData->stopContPE,text) );
	strcat(resultString, "#");

	strcat( resultString, itoa(orderData->mailError,text) );
	strcat(resultString, "#");

	strcat( resultString, itoa(orderData->mailResult,text) );
	strcat(resultString, "#");

	strcat(resultString, itoa(orderData->synchro, text) );
	strcat(resultString, "#");

    }

	// System command file or EME script
    if (orderData->orderType == 1 || orderData->orderType == 3)
    {

	strcat( resultString, itoa(orderData->outMsgMail,text) );
	strcat(resultString, "#");

	if ( isFoundHashMarkCrypt(orderData->parameters, resultString) == 0 )
	    strcat (resultString, orderData->parameters);
	if (strcmp(orderData->parameters, "") != 0)
	  strcat(resultString, "#");
	else
	  strcat(resultString, " #");
    }

	// MML file - OPS
    if (orderData->orderType == 2)
    {
    	strcat(resultString, " #");

        if ( isFoundHashMarkCrypt(orderData->networkElement, resultString) == 0 )
            strcat (resultString, orderData->networkElement);
	if (strcmp(orderData->networkElement, "") != 0)
		strcat(resultString, "#");
	else
		strcat(resultString, " #");

        if ( isFoundHashMarkCrypt(orderData->mailAddress, resultString) == 0 )
	    strcat (resultString, orderData->mailAddress);
	if (strcmp(orderData->mailAddress, "") != 0)
		strcat(resultString, "#");
	else
		strcat(resultString, " #");

        if ( isFoundHashMarkCrypt(orderData->OZTLabel, resultString) == 0 )
	    strcat( resultString, orderData->OZTLabel );
	if (strcmp(orderData->OZTLabel, "") != 0)
		strcat( resultString, "#" );
	else
		strcat(resultString, " #");

	if(orderData->OZTDisplayOn) {
		if (isFoundHashMarkCrypt(orderData->OZTDisplay, resultString) == 0 )
			strcat( resultString, orderData->OZTDisplay );
		if (strcmp(orderData->OZTDisplay, "") != 0)
			strcat( resultString, "#" );
		else
			strcat(resultString, " #");
	} else
		strcat(resultString, " #");

 	if ( orderData->mailOutputDest != NULL ) {
		if (isFoundHashMarkCrypt(orderData->mailOutputDest, resultString) == 0 )
			strcat(resultString, orderData->mailOutputDest);

		if (strcmp(orderData->mailOutputDest, "") != 0)
			strcat(resultString, "#");
		else
			strcat(resultString, " #");
	} else {
		strcat(resultString, " #");
	}

	if ( orderData->fileOutputDest != NULL ) {
        	if (isFoundHashMarkCrypt(orderData->fileOutputDest, resultString) == 0 )
			strcat(resultString, orderData->fileOutputDest);
		if (strcmp(orderData->fileOutputDest, "") != 0)
			strcat(resultString, "#");
		else
			strcat(resultString, " #");
	} else {
			strcat(resultString, " #");
	}

	if ( orderData->printOutputDest != NULL ) {
        	if (isFoundHashMarkCrypt(orderData->printOutputDest, resultString) == 0 )
			strcat(resultString, orderData->printOutputDest );
		if (strcmp(orderData->printOutputDest, "") != 0)
			strcat(resultString, "#");
		else
			strcat(resultString, " #");
	} else {
			strcat(resultString, " #");
	}
    }

    strcat(resultString, ";");

	//TRACE_OUT(trace, structToString, resultString);
}

//****************************************************************************

//---------------------------------------------------------------------------
// This function checks if a file exists, has read permission and it is
// accesible.
//---------------------------------------------------------------------------

int AM_auxFunctions::checkFileRead(const char *fileName)
{
	//TRACE_IN(trace, checkFileRead, "");

    //char *completeFileName = new char[strlen(directory) + strlen(fileName) +2];
    //sprintf(completeFileName, "%s/%s", directory, fileName);
    int checkResult = 0;

    struct stat sbuf;

    stat(fileName,&sbuf);
    if ((sbuf.st_mode & S_IFMT) == S_IFDIR)
    {
	return 3;
    }

    if ( access (fileName, R_OK) != 0 )
    {
	switch (errno)
	{
	    case ENOENT:
		checkResult = 1;
		break;
	    case EACCES:
		checkResult = 2;
		break;
	    default:
		checkResult = 3;
		break;
	}
    }
    //delete []completeFileName;

	//TRACE_RETURN(trace, checkFileRead, checkResult);

    return checkResult;
}

//****************************************************************************

//---------------------------------------------------------------------------
// This function checks if a file exists, has read and execute permission
// and it is accesible.
//---------------------------------------------------------------------------

int AM_auxFunctions::checkFileExecute(const char *directory,
						const char *fileName)
{
	//TRACE_IN(trace, checkFileExecute, "");

    char *completeFileName = new char[strlen(directory) + strlen(fileName) +2];
    sprintf(completeFileName, "%s/%s", directory, fileName);
    int checkResult = 0;

    if ( ( access(completeFileName, X_OK) != 0) &&  (errno == EACCES) )
	checkResult = 4;

    if ( access (completeFileName, R_OK) != 0 )
    {
	switch (errno)
	{
	    case ENOENT:
		checkResult = 1;
		break;
	    case EACCES:
		checkResult = 2;
		break;
	    default:
		checkResult = 3;
		break;
	}
    }

    delete []completeFileName;

	//TRACE_RETURN(trace, checkFileExecute, checkResult);

    return checkResult;
}

//****************************************************************************

//---------------------------------------------------------------------------
// This function transforms one string containing elements separated
// by the character "#" into one structure of type AM_OrderData
//---------------------------------------------------------------------------


int
AM_auxFunctions::returnError(AM_OrderData *data)
{
    deleteStrings(data);
    return AM_NO_MEMORY;
}


int
AM_auxFunctions::stringToStruct(char *stringData, AM_OrderData *orderData)
{
  //TRACE_IN(trace, stringToStruct, stringData);

  if (orderData == NULL)
    return AM_ILLEGAL_ARGUMENT;

  orderData->orderKey = AM_NOT_DEFINED;
  orderData->orderType = AM_NOT_DEFINED;
  orderData->filename = NULL;
  orderData->networkElement = NULL;
  orderData->userId = NULL;
  orderData->status = AM_IDLE;
  orderData->outputDest = NULL;
  orderData->mailOutputDest = NULL;
  orderData->fileOutputDest = NULL;
  orderData->printOutputDest = NULL;
  orderData->immRouting = NULL;
  orderData->delRouting = NULL;
  orderData->startTime = 0;
  orderData->interval.intervalBase = AM_NONE;
  orderData->interval.split = AM_NOT_DEFINED;
  orderData->mailAddress = NULL;
  orderData->funcBusyInterval = 0;
  orderData->stopContNA = AM_NOT_DEFINED;
  orderData->stopContPE = AM_NOT_DEFINED;
  orderData->mailError = AM_NOT_DEFINED;
  orderData->mailResult = AM_NOT_DEFINED;
  orderData->synchro = FALSE;
  orderData->outMsgMail = AM_NOT_DEFINED;
  orderData->parameters = NULL;
  orderData->host = NULL;
  orderData->tasId = 0;
  orderData->timestamp = 0;
  orderData->OZTLabel = NULL;
  orderData->OZTDisplay = NULL;
  orderData->OZTDisplayOn = FALSE;

  char*	aux;
  aux = strtok(stringData, "#");
  if (aux == NULL)
    return returnError(orderData);
  orderData->orderKey = atol(aux);

  //TRACE_FLOW(trace, retrieveData, "string to struct key: " << orderData->orderKey);

  aux = strtok(NULL, "#");
  if (aux == NULL)
    return returnError(orderData);
  orderData->orderType = atoi(aux);
  //TRACE_FLOW(trace, retrieveData, "string to struct type: " << orderData->orderType);

  aux = strtok(NULL, "#");
  if (aux == NULL)
    return returnError(orderData);
  orderData->filename = new char[strlen(aux)+1];
  if (orderData->filename == NULL )
    return returnError(orderData);
  if (isFoundCryptedHashMarkDecrypt(aux, orderData->filename) == 1)
    ; // Do nothing
  //TRACE_FLOW(trace, retrieveData, "string to struct file: " << orderData->filename);

  aux = strtok(NULL, "#");
  if (aux == NULL)
    return returnError(orderData);
  orderData->userId = new char[strlen(aux)+1];
  if (orderData->userId == NULL )
    return returnError(orderData);
  if (isFoundCryptedHashMarkDecrypt(aux, orderData->userId) == 1)
    ; // Do nothing
  //TRACE_FLOW(trace, retrieveData, "string to struct userId: " << orderData->userId);

  aux = strtok(NULL, "#");
  if (aux == NULL)
    return returnError(orderData);
  orderData->status = atoi(aux);
  //TRACE_FLOW(trace, retrieveData, "string to struct status: " << orderData->status);

  aux = strtok(NULL, "#");
  if (aux == NULL)
    return returnError(orderData);
  orderData->startTime = atol(aux);
  //TRACE_FLOW(trace, retrieveData, "string to struct start: " << orderData->startTime);

  aux = strtok(NULL, "#");
  if (aux == NULL)
    return returnError(orderData);
  orderData->interval.intervalBase = (AM_Interv)atoi(aux);
  //TRACE_FLOW(trace, retrieveData, "string to struct intervalBase: " << orderData->interval.intervalBase);


  aux = strtok(NULL, "#");
  if (aux == NULL)
    return returnError(orderData);
  orderData->interval.split = atoi(aux);
  //TRACE_FLOW(trace, retrieveData, "string to struct interval split: " << orderData->interval.split);


  aux = strtok(NULL, "#");
  if (aux == NULL)
    return returnError(orderData);
  orderData->host = new char[strlen(aux)+1];
  if (orderData->host == NULL )
    return returnError(orderData);
  if (isFoundCryptedHashMarkDecrypt(aux, orderData->host) == 1)
    ; // Do nothing
  //TRACE_FLOW(trace, retrieveData, "string to struct host: " << orderData->host);


  aux = strtok(NULL, "#");
  if (aux == NULL)
    return returnError(orderData);
  orderData->tasId = atoi(aux);
  //TRACE_FLOW(trace, retrieveData, "string to struct tasId: " << orderData->tasId);


  aux = strtok(NULL, "#");
  if (aux == NULL)
    return returnError(orderData);
  orderData->timestamp = atol(aux);
  //TRACE_FLOW(trace, retrieveData, "string to struct timestamp: " << orderData->timestamp);


  if (orderData->orderType == 0) //case of CFI
    {
      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      orderData->networkElement = new char[strlen(aux)+1];
      if (orderData->networkElement == NULL )
	return returnError(orderData);
      if (isFoundCryptedHashMarkDecrypt(aux, orderData->networkElement) == 1)
	; // Do nothing

      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      orderData->outputDest = new char[strlen(aux) + 1];
      if (orderData->outputDest == NULL)
	return returnError(orderData);
      if (isFoundCryptedHashMarkDecrypt(aux, orderData->outputDest) == 1)
	; // Do nothing

      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      orderData->mailAddress = new char[strlen(aux)+1];
      if (orderData->mailAddress == NULL )
	return returnError(orderData);
      if (isFoundCryptedHashMarkDecrypt(aux, orderData->mailAddress) == 1)
	; // Do nothing

      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      orderData->funcBusyInterval = atoi(aux);

      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      orderData->stopContNA = atoi(aux);

      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      orderData->stopContPE = atoi(aux);

      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      orderData->mailError = atoi(aux);

      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      orderData->mailResult = atoi(aux);

      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      orderData->synchro = atoi(aux);

      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
    }
  if (orderData->orderType == 1 || orderData->orderType == 3)
    //case of system command file or EME script
    {
      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      orderData->outMsgMail = atoi(aux);

      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      orderData->parameters = new char[strlen(aux)+1];
      if (orderData->parameters == NULL )
	return returnError(orderData);
      if (isFoundCryptedHashMarkDecrypt(aux, orderData->parameters) == 1)
	; // Do nothing

      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
    }

  if (orderData->orderType == 2) //case of OPS script
    {
      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);

      //TRACE_FLOW(trace, retrieveData, "string to struct ??: --");


      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      orderData->networkElement = new char[strlen(aux)+1];
      if (orderData->networkElement == NULL )
	return returnError(orderData);
      if (isFoundCryptedHashMarkDecrypt(aux, orderData->networkElement) == 1)
	;

      if( strcmp( orderData->networkElement, "0" ) == 0)
	strcpy(orderData->networkElement, "" );

      //TRACE_FLOW(trace, retrieveData, "string to struct NE: " << orderData->networkElement);

      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      orderData->mailAddress = new char[strlen(aux)+1];
      if (orderData->mailAddress == NULL )
	return returnError(orderData);
      if (isFoundCryptedHashMarkDecrypt(aux, orderData->mailAddress) == 1)
	; // Do nothing
      //TRACE_FLOW(trace, retrieveData, "string to struct mailAddress: " << orderData->mailAddress);

      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      orderData->OZTLabel = new char[strlen(aux)+1];
      if (orderData->OZTLabel == NULL )
	return returnError(orderData);
      if (isFoundCryptedHashMarkDecrypt(aux, orderData->OZTLabel) == 1)
	; // Do nothing

      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      orderData->OZTDisplay = new char[strlen(aux)+1];
      if (orderData->OZTDisplay == NULL )
	return returnError(orderData);
      if (isFoundCryptedHashMarkDecrypt(aux, orderData->OZTDisplay) == 1)
	; // Do nothing

      //TRACE_FLOW(trace, retrieveData, "string to struct OZTDisplay: " << orderData->OZTDisplay);
      if (strcmp(orderData->OZTDisplay,"")!=0)
	orderData->OZTDisplayOn = TRUE;

      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      orderData->mailOutputDest = new char[strlen(aux) + 1];
      if (orderData->mailOutputDest == NULL)
	return returnError(orderData);
      if (isFoundCryptedHashMarkDecrypt(aux, orderData->mailOutputDest) == 1)
	; // Do nothing
      //TRACE_FLOW(trace, retrieveData, "string to struct mailOutputDest: " << orderData->mailOutputDest);


      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      orderData->fileOutputDest = new char[strlen(aux) + 1];
      if (orderData->fileOutputDest == NULL)
	return returnError(orderData);
      if (isFoundCryptedHashMarkDecrypt(aux, orderData->fileOutputDest) == 1)
	; // Do nothing
      //TRACE_FLOW(trace, retrieveData, "string to struct fileOutputDest: " << orderData->fileOutputDest);


      aux = strtok(NULL, "#");
      if (aux == NULL)
	return returnError(orderData);
      if (strcmp(aux, ";") != 0 )
	{
	  orderData->printOutputDest = new char[strlen(aux)+1];
	  if (orderData->printOutputDest == NULL )
	    return returnError(orderData);
	  if (isFoundCryptedHashMarkDecrypt(aux, orderData->printOutputDest)
	      == 1)
	    ; // Do nothing
	  //TRACE_FLOW(trace, retrieveData, "string to struct printOutputDest: " << orderData->printOutputDest);

	  aux = strtok(NULL, "#");
	  if (aux == NULL)
	    return returnError(orderData);
	}
      else
	{
	  orderData->printOutputDest = new char[1];
	  strcpy(orderData->printOutputDest, "");
	}
    }

  //TRACE_RETURN(trace, stringToStruct, "");

  if ( strcmp(aux, ";") != 0 )
    return returnError(orderData);
  else
    return AM_OK;
}

//****************************************************************************

//----------------------------------------------------------------------------
// This function deletes all the strings created in AM_OrderData
//----------------------------------------------------------------------------

void
AM_auxFunctions::deleteStrings(AM_OrderData *in_data)
{
	//TRACE_IN(trace, deleteStrings, "");

    if (in_data !=NULL)
    {
        if ( in_data->filename != NULL )
        {
            delete []in_data->filename;
            in_data->filename = NULL;
        }

	if ( in_data->networkElement != NULL )
	{
	    delete []in_data->networkElement;
	    in_data->networkElement = NULL;
	}

	if ( in_data->userId != NULL )
	{
	    delete []in_data->userId;
	    in_data->userId = NULL;
	}

	if (in_data->outputDest != NULL)
	{
		delete []in_data->outputDest;
		in_data->outputDest = NULL;
	}

	if ( in_data->immRouting != NULL )
	{
	    delete []in_data->immRouting;
	    in_data->immRouting = NULL;
	}

	if ( in_data->delRouting != NULL )
	{
	    delete []in_data->delRouting;
	    in_data->delRouting = NULL;
	}

	if ( in_data->mailAddress != NULL )
	{
	    delete []in_data->mailAddress;
	    in_data->mailAddress = NULL;
	}

	if ( in_data->parameters != NULL )
	{
	    delete []in_data->parameters;
	    in_data->parameters = NULL;
	}

	if ( in_data->host != NULL )
	{
	    delete []in_data->host;
	    in_data->host = NULL;
	}

	if ( in_data->OZTLabel != NULL )
	{
	    delete []in_data->OZTLabel;
	    in_data->OZTLabel = NULL;
	}

	if ( in_data->OZTDisplay != NULL )
	{
	    delete []in_data->OZTDisplay;
	    in_data->OZTDisplay = NULL;
	}

	if ( in_data->mailOutputDest != NULL )
	{
	    delete []in_data->mailOutputDest;
	    in_data->mailOutputDest = NULL;
	}

	if ( in_data->fileOutputDest != NULL )
	{
	    delete []in_data->fileOutputDest;
	    in_data->fileOutputDest = NULL;
	}

	if ( in_data->printOutputDest != NULL )
	{
	    delete []in_data->printOutputDest;
	    in_data->printOutputDest = NULL;
	}
    }

	//TRACE_OUT(trace, deleteStrings, "");
}

//****************************************************************************

//----------------------------------------------------------------------------
// Function itoa, that converts integers into strings
//----------------------------------------------------------------------------

char*
AM_auxFunctions::itoa(int x,char *t)
{

	int j=0;
	int k=0;
	char s[15];

	while (x>= 10)
	{
		s[j++] = (char) ((x%10) + 48);
		x = x/10;
	}
	s[j] = (char) (x + 48);
	s[j+1] ='\0';
	for (k=0;j>=0; j--, k++)
	{
		t[k] = s[j];
	}
	t[k] = '\0';
	return(t);
}

//****************************************************************************

//----------------------------------------------------------------------------
// Function ltoa, that converts longs into strings
//----------------------------------------------------------------------------

char*
AM_auxFunctions::ltoa(long x,char *t)
{

	int j=0;
	int k=0;
	char s[15];

	while (x>= 10)
	{
		s[j++] = (char) ((x%10) + 48);
		x = x/10;
	}
	s[j] = (char) (x + 48);
	s[j+1] ='\0';
	for (k=0;j>=0; j--, k++)
	{
		t[k] = s[j];
	}
	t[k] = '\0';
	return(t);
}

//*****************************************************************************

//----------------------------------------------------------------------------
// Function blank, that truncates/fills with blanks the given string
//----------------------------------------------------------------------------

char*
AM_auxFunctions::blank(char* t, int length)
{
	int  l;
	char* g = new char[length+1];

        if ( t == NULL )
            l = 0;
        else
            l = strlen(t);

	if(l>length)
	{
          strncpy(g,t,length);
	  g[length] = '\0';
	  return g;
	}

        strncpy(g,t,l);
	for(l;l<length;l++)
	{
	  g[l]=' ';
	}
	g[l] = '\0';
	return g;
}

//*****************************************************************************

//----------------------------------------------------------------------------
// Function checkDateTime. It checks the format of date and time
//----------------------------------------------------------------------------

time_t
AM_auxFunctions::checkDateTime(char* date, char* time)
{

	//TRACE_IN(trace, checkDateTime, date << " " << time);

    char 	yearStr[5];
    char  monthStr[3];
    char 	dayStr[3];
    char 	hourStr[3];
    char 	minuteStr[3];
    int 	year, month, day, hour, minute;

    if ( ! ( (strlen(date)==10) && (date[4]=='-') && (date[7]=='-') ) )
	return AM_DATE_FORMAT_ERR;

    if ( ! ( (strlen(time)==5) && (time[2]==':') ) )
	return AM_TIME_FORMAT_ERR;

    strncpy(yearStr, date, 4);
    yearStr[4] = '\0';
    if ( !isdigit(yearStr[0]) || !isdigit(yearStr[1]) ||
	!isdigit(yearStr[2]) || !isdigit(yearStr[3]) )
	return AM_DATE_FORMAT_ERR;
    year = atoi(yearStr);
    // This check is necessary to avoid problems with mktime
    if (year >= 2038)
    	return AM_YEAR_RANGE_ERR;

    monthStr[0] = date[5];
    monthStr[1] = date[6];
    monthStr[2] = '\0';
    if ( !isdigit(monthStr[0]) || !isdigit(monthStr[1]) )
	return AM_DATE_FORMAT_ERR;
    month = atoi(monthStr);

    dayStr[0] = date[8];
    dayStr[1] = date[9];
    dayStr[2] = '\0';
    if ( !isdigit(dayStr[0]) || !isdigit(dayStr[1]) )
	return AM_DATE_FORMAT_ERR;
    day = atoi(dayStr);

    if ( (month > 12) || (month < 1) ) return AM_MONTH_RANGE_ERR;

    if ( (day > 31) || (day < 1) ) return AM_DAY_RANGE_ERR;

    switch (month)
    {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		break;
	case 4:
	case 6:
	case 9:
	case 11:
	    if(day>30) return AM_DAY_RANGE_ERR;
	    break;
	case 2:
	    if (day > 29) return AM_DAY_RANGE_ERR;
    	    if((year%4 == 0) && (year%100 != 0) || (year%400 == 0))
		break;
	    else
		if (day>28) return AM_DAY_RANGE_ERR;
	    break;
	default:
	    break;
    }


    hourStr[0] = time[0];
    hourStr[1] = time[1];
    hourStr[2] = '\0';
    if ( !isdigit(hourStr[0]) || !isdigit(hourStr[1]) )
	return AM_TIME_FORMAT_ERR;
    hour = atoi(hourStr);

    minuteStr[0] = time[3];
    minuteStr[1] = time[4];
    minuteStr[2] = '\0';
    if ( !isdigit(minuteStr[0]) || !isdigit(minuteStr[1]) )
	return AM_TIME_FORMAT_ERR;
    minute = atoi(minuteStr);

    if (hour>23)
	return AM_HOUR_RANGE_ERR;

    if (minute>59)
	return AM_MINUTE_RANGE_ERR;

    //Creating the time structure
    tm 	startDateTime;

    startDateTime.tm_year = (year - 1900);
    startDateTime.tm_mon = (month-1); //January = 0; December = 11;
    startDateTime.tm_mday = day;
    startDateTime.tm_hour = hour;
    startDateTime.tm_min = minute;
    startDateTime.tm_sec = 0;

    startDateTime.tm_isdst = -1;
    int result = checkDate( mktime(&startDateTime) );

	//TRACE_RETURN(trace, checkDateTime, result);

    if (result != AM_OK)
	return result;
    startDateTime.tm_isdst = -1;
    return mktime(&startDateTime);
}

//*****************************************************************************

//----------------------------------------------------------------------------
// Function checkDate. It checks if date&time are valid (future)
//----------------------------------------------------------------------------


int
AM_auxFunctions::checkDate(time_t dateTime)
{
	//TRACE_IN(trace, checkDate, "");

    struct timeval *tp;
    struct timezone *tzp;
    int	 result;

    tp = new struct timeval;
    if (tp == NULL)
        return AM_NO_MEMORY;

    tzp = new struct timezone;
    if (tzp == NULL)
    {
        delete tp;
        return AM_NO_MEMORY;
    }

    if (gettimeofday(tp,tzp) == -1)
    {
        //Unix error. Report error.
       delete tp;
       delete tzp;
       return AM_ERROR;
    }

    if (dateTime <= tp->tv_sec)
	result = AM_OLD_DATE;
    else result = AM_OK;

    if (tp != NULL)
	delete tp;
    if (tzp != NULL)
	delete tzp;

	//TRACE_RETURN(trace, checkDate, result);

    return result;
}

//*****************************************************************************

//----------------------------------------------------------------------------
// Function timeToString, that Convers the time_t seconds in string with
// the following format: YYYY-MM-DD HH:MM
//----------------------------------------------------------------------------

char*
AM_auxFunctions::timeToString(time_t datetime)
{
	//TRACE_IN(trace, timeToString, "");

    tm* date;
    int year = 1900;
    int month = 1;
    int day = 0;
    int hour = 0;
    int minutes = 0;
    char text[15];

    char* dateString = new char[18];

    if(datetime == 0)
    {
	strcpy(dateString,"********** ***** "); //17 blanks
	return dateString;
    }

    date = localtime(&datetime);

    year = year + (date->tm_year);
    strcpy(dateString, itoa(year,text));
    strcat(dateString,"-");

    month = month + (date->tm_mon);
    if(month<10)
	strcat(dateString, "0");
    strcat(dateString, itoa(month,text));
    strcat(dateString,"-");

    day = date->tm_mday;
    if(day<10)
	strcat(dateString, "0");
    strcat(dateString, itoa(day,text));
    strcat(dateString," ");

    hour = date->tm_hour;
    if(hour<10)
	strcat(dateString, "0");
    strcat(dateString, itoa(hour,text));
    strcat(dateString,":");

    minutes = date->tm_min;
    if(minutes<10)
	strcat(dateString, "0");
    strcat(dateString, itoa(minutes,text));
    strcat(dateString," ");

	//TRACE_RETURN(trace, timeToString, dateString);

    return dateString;
}

char* AM_auxFunctions::timeToTimeString(time_t datetime)
{
	//TRACE_IN(trace, timeToTimeString, "");

    tm* date;
    int hour = 0;
    int minutes = 0;
    char* timeString;
    char text[15];

    if (datetime == 0)
    {
		return NULL;
    }

    // Initialize text
    memset( text, '\0', 15 );

    timeString = new char[7];
    // Initialize timeString
    memset( timeString, '\0', 7 );

    date = localtime(&datetime);

    hour = date->tm_hour;
    if(hour<10) {
	strcpy(timeString, "0");
    }

    strcat(timeString, itoa(hour,text));
    strcat(timeString,":");

    minutes = date->tm_min;
    if(minutes<10)
	strcat(timeString, "0");

    strcat(timeString, itoa(minutes,text));
    strcat(timeString," ");

    //TRACE_RETURN(trace, timeToTimeString, timeString);

    return timeString;
}

char* AM_auxFunctions::timeToDateString(time_t datetime)
{
	//TRACE_IN(trace, timeToDateString, "");

    tm* date;
    int year = 1900;
    int month = 1;
    int day = 0;
    char* dateString;
    char text[15];

    if (datetime == 0)
    {
		return NULL;
    }

    // Initialize text
    memset( text, '\0', 15 );

    dateString = new char[12];
    // Initialize timeString
    memset( dateString, '\0', 12 );

    date = localtime(&datetime);

    year = year + (date->tm_year);
    strcpy(dateString, itoa(year,text));
    strcat(dateString,"-");

    month = month + (date->tm_mon);
    if(month<10)
	strcat(dateString, "0");
    strcat(dateString, itoa(month,text));
    strcat(dateString,"-");

    day = date->tm_mday;
    if(day<10)
	strcat(dateString, "0");
    strcat(dateString, itoa(day,text));
    strcat(dateString," ");

	//TRACE_RETURN(trace, timeToDateString, dateString);

    return dateString;
}

//*****************************************************************************
AM_OrderData*
AM_auxFunctions::getAM_OrderDataObject()
{
	//TRACE_IN(trace, getAM_OrderDataObject, "");

    AM_OrderData *orderData;

    orderData = new AM_OrderData;

    orderData->orderKey = AM_NOT_DEFINED;
    orderData->orderType = AM_NOT_DEFINED;
    orderData->filename = NULL;
    orderData->networkElement = NULL;
    orderData->userId = NULL;
    orderData->status = AM_IDLE;
    orderData->outputDest = NULL;
    orderData->mailOutputDest = NULL;
    orderData->fileOutputDest = NULL;
    orderData->printOutputDest = NULL;
    orderData->immRouting = NULL;
    orderData->delRouting = NULL;
    orderData->startTime = 0;
    orderData->interval.intervalBase = AM_NONE;
    orderData->interval.split = AM_NOT_DEFINED;
    orderData->mailAddress = NULL;
    orderData->funcBusyInterval = 0;
    orderData->stopContNA = AM_NOT_DEFINED;
    orderData->stopContPE = AM_NOT_DEFINED;
    orderData->mailError = AM_NOT_DEFINED;
    orderData->mailResult = AM_NOT_DEFINED;
	orderData->synchro = AM_NOT_DEFINED;
    orderData->outMsgMail = AM_NOT_DEFINED;
    orderData->parameters = NULL;
    orderData->host = NULL;
    orderData->tasId = 0;
    orderData->timestamp = 0;
    orderData->OZTLabel = NULL;
    orderData->OZTDisplay = NULL;
    orderData->OZTDisplayOn = FALSE;

	//TRACE_RETURN(trace, getAM_OrderDataObject, "");

    return orderData;
}

//*****************************************************************************

int AM_auxFunctions::isFoundHashMarkCrypt(const char* s, char* result)
{
	//TRACE_IN(trace, isFoundHashMarkCrypt, s);

    if ( strchr(s, '#') != NULL ) // Hash mark found in s.
    {
        char* alias = new char[3];
	strcpy(alias, "%&");
	char* tmpStr = new char[2*strlen(s) + 1];
	strcpy(tmpStr, "");
	int index = 0;
	int lenTmpStr = strlen(s);

	while ( index < lenTmpStr )
	{
	  if ( (s)[index] == '#' )
	      strcat(tmpStr, alias);
	  else
	      strncat(tmpStr, &((s)[index]), 1);
	  index++;
	}
	strcat(result, tmpStr);
	delete []tmpStr;
	delete []alias;

	return 1;
    }
    else
        return 0;
}

//*****************************************************************************

int AM_auxFunctions::isFoundCryptedHashMarkDecrypt(const char* s, char* result)
{
	//TRACE_IN(trace, isFoundCryptedHashMarkDecrypted, "");

    int foundHashMark = 0;
    int index         = 0;
    int lenS         = strlen(s);
    char* tempStr  = new char[strlen(s) + 1];
    strcpy(tempStr, "");
    while ( index < lenS )
    {
        if ( s[index] == '%' )
	{
	    if ( s[++index] == '&' )
	    {
	        foundHashMark = 1;
		index++;
		strcat(tempStr, "#");
	    }
	}
	else
	    strncat(tempStr, &s[index], 1);
	if ( !foundHashMark )
	    index++;
	foundHashMark = 0;
    }
	if (strcmp(tempStr, " ") == 0)
	  strcpy(tempStr, "");

    strcpy(result, tempStr);
    delete []tempStr;

	//TRACE_RETURN(trace, isFoundCryptedHashMarkDecrypted, "");

    return foundHashMark;
}




