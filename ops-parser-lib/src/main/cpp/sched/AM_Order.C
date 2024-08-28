//******************************************************************************
//
// NAME
//		AM_Order

// COPYRIGHT
// COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB, Sweden 1999.
//
// The Copyright to the computer program(s) herein is the
// property of Ericsson Hewlett-Packard Telecommunications AB, Sweden.
// The program(s) may be used and/or copied with the 
// written permission from Ericsson Hewlett-Packard Telecommunications AB
// or in accordance with the terms and conditions stipulated
// in the agreement/contract under which the program(s) have been supplied.

// DOCUMENT NO
//	190 55 - CXC 134 998 

// AUTHOR 
// 	1992-05-29 by EME/TY/O Ricardo Cordon itsrcma@madrid.ericsson.se

// SEE ALSO

//*****************************************************************************

#include <string.h>
#include <iostream>
#include <AM_Order.H>
#include <AM_auxFunctions.H>

//*****************************************************************************

int
structCopy (AM_OrderData * in, AM_OrderData * out);

//*****************************************************************************

AM_Order::AM_Order()
{
    orderData.orderKey = AM_NOT_DEFINED;
    orderData.orderType = AM_NOT_DEFINED;
    orderData.filename = NULL;
    orderData.networkElement = NULL;
    orderData.userId = NULL;
    orderData.status = AM_IDLE;
	orderData.outputDest = NULL;
    orderData.immRouting = NULL;
    orderData.delRouting = NULL;
	orderData.mailOutputDest = NULL;
	orderData.fileOutputDest = NULL;
	orderData.printOutputDest = NULL;
    orderData.startTime = 0;
    orderData.interval.intervalBase = AM_NONE;
    orderData.interval.split = AM_NOT_DEFINED;
    orderData.mailAddress = NULL;
    orderData.funcBusyInterval = 0;
    orderData.stopContNA = AM_NOT_DEFINED;
    orderData.stopContPE = AM_NOT_DEFINED;
    orderData.mailError = AM_NOT_DEFINED;
    orderData.mailResult = AM_NOT_DEFINED;
	orderData.synchro = AM_NOT_DEFINED;
    orderData.outMsgMail = AM_NOT_DEFINED;
    orderData.parameters = NULL;
    orderData.host  = NULL;
    orderData.OZTLabel = NULL;
    orderData.OZTDisplay = NULL;    
    orderData.tasId = 0;
    orderData.OZTDisplayOn = FALSE;    
    orderData.timestamp = 0;
}

//*****************************************************************************

AM_Order::~AM_Order()
{
    AM_auxFunctions::deleteStrings(&orderData);
}

//*****************************************************************************

int
AM_Order::setOrderData(const char* filename,
			 const char* networkElement,
			 const char* userId,
			 const int   status,    
			 const char* mailOutputDest,    
			 const char* fileOutputDest,
			 const char* printOutputDest,
			 time_t      startTime,    
    		 AM_Interval interval,
			 const char* mailAddress,
			 const unsigned int funcBusyInterval,
			 const int   stopContNA,
  			 const int   stopContPE,
			 const int   mailError,
			 const int   mailResult,
			const int	synchro,
			 const char* host,
			 const int   tasId,
			 time_t      timestamp)
{
    orderData.orderKey = 0;
    orderData.orderType = 0; //MML file - CFI

    if (filename != NULL)
    {
		if (strlen(filename) > AM_MAX_FILENAME_LEN )
			returnFault(AM_ILLEGAL_ARGUMENT);
		orderData.filename = new char [strlen(filename)+1];
		if (orderData.filename != NULL)
			strcpy(orderData.filename, filename);
		else
			returnFault(AM_NO_MEMORY);
    }
    else
		returnFault(AM_ILLEGAL_ARGUMENT);


    if (networkElement != NULL)
    {
		//if (strlen(networkElement) > AM_MAX_EXTSYSTEM_LEN )
		//	returnFault(AM_ILLEGAL_ARGUMENT);
		orderData.networkElement = new char [strlen(networkElement) + 1];
		if (orderData.networkElement != NULL)
			strcpy(orderData.networkElement, networkElement);
		else
			returnFault(AM_NO_MEMORY);
    }
    else
		returnFault(AM_ILLEGAL_ARGUMENT);


    if (userId != NULL)
    {
		if ( strlen(userId) > AM_MAX_USERID_LEN )
			returnFault(AM_ILLEGAL_ARGUMENT);
		orderData.userId = new char [strlen(userId)+1];
		if (orderData.userId != NULL)
			strcpy(orderData.userId, userId);
		else
			returnFault(AM_NO_MEMORY);
	}
    else
		returnFault(AM_ILLEGAL_ARGUMENT);

	char* tmpStr = NULL;
	tmpStr = new char [1000];
// 	strcat(tmpStr, "");
	strcpy(tmpStr, "");
	if (mailOutputDest != NULL)
	{
		if (strcmp(mailOutputDest, "") != 0)
		{
			strcat(tmpStr, "mail:");
			strcat(tmpStr, mailOutputDest);
		}
	}
	if (fileOutputDest != NULL)
	{
		if (strcmp(fileOutputDest, "") != 0)
		{
			if (strcmp(mailOutputDest, "") == 0)
				strcat(tmpStr, "file:");
			else
				strcat(tmpStr, ":file:");
			strcat(tmpStr, fileOutputDest);
		}
	}
	if (printOutputDest != NULL)
	{
		if (strcmp(printOutputDest, "") != 0)
		{
			if (strcmp(mailOutputDest, "") == 0
			 && strcmp(fileOutputDest, "") == 0)
				strcat(tmpStr, "printer:");
			else
				strcat(tmpStr, ":printer:");
			strcat(tmpStr, printOutputDest);
		}
	}
	orderData.outputDest = new char [strlen(tmpStr) + 1];
	if (orderData.outputDest != NULL)
	{
	    strcpy(orderData.outputDest, tmpStr);
	}
	else
	    returnFault(AM_NO_MEMORY);


    if (mailAddress != NULL)
    {
	if (strlen(mailAddress) > AM_MAX_MAILADDRESS_LEN )
	    returnFault(AM_ILLEGAL_ARGUMENT);
	orderData.mailAddress = new char [strlen(mailAddress)+1];
	if (orderData.mailAddress != NULL)
	    strcpy(orderData.mailAddress, mailAddress);
	else
	    returnFault(AM_NO_MEMORY);
    }
    else
	returnFault(AM_ILLEGAL_ARGUMENT);


    switch (interval.intervalBase)
    {
	case AM_NONE:
	    if (interval.split != 1)
		returnFault(AM_ILLEGAL_ARGUMENT);
            break;
    case AM_WEEKLY:
        if ( (interval.split < AM_SUNDAY) ||
		 (interval.split > AM_SATURDAY) )
		returnFault(AM_ILLEGAL_ARGUMENT);
            break;
	case AM_HOURLY:
	case AM_DAILY:
    	case AM_MONTHLY:
    	case AM_ANNUALLY:
            if ( (interval.split < 1) || (interval.split > 12 ) ) 
		returnFault(AM_ILLEGAL_ARGUMENT);
            break;
        default:
	    returnFault(AM_ILLEGAL_ARGUMENT);
    }

    orderData.interval.intervalBase = interval.intervalBase;
    orderData.interval.split = interval.split;
    orderData.startTime = startTime;

    orderData.status = status;
    orderData.funcBusyInterval = funcBusyInterval;
    orderData.stopContNA = stopContNA;
    orderData.stopContPE = stopContPE;
    orderData.mailError = mailError;
    orderData.mailResult = mailResult;
	orderData.synchro = synchro;
    if (host != NULL)
    {
	orderData.host = new char [strlen(host)+1];
	if (orderData.host != NULL)
	    strcpy(orderData.host, host);
	else
	    returnFault(AM_NO_MEMORY);
    }

    orderData.tasId = tasId;
    orderData.timestamp = timestamp;

    if (tmpStr != NULL)
        delete [] tmpStr;
    return AM_OK;
}

//*****************************************************************************

int
AM_Order::returnFault(int errorCode)
{
    AM_auxFunctions::deleteStrings(&orderData);
    return errorCode;
}

 
//*****************************************************************************

// System command file or EME script
int AM_Order::setOrderData (int orderType,
			    const char* filename,
			    const char* userId,
			    const int   status,    
			    time_t      startTime,    
			    AM_Interval interval,
			    const int   outMsgMail,
			    const char* parameters,
			    const char* host,
			    const int   tasId,
			    time_t      timestamp)
{
  orderData.orderKey = 0;
  orderData.orderType = orderType;
  
  if (filename != NULL)
    {
      if ( strlen(filename) > AM_MAX_FILENAME_LEN )
	returnFault(AM_ILLEGAL_ARGUMENT);
      orderData.filename = new char [strlen(filename)+1];
      if (orderData.filename != NULL)
	strcpy(orderData.filename, filename);
      else
	returnFault(AM_NO_MEMORY);
    }
  else
    returnFault(AM_ILLEGAL_ARGUMENT);
  
  
  if (userId != NULL)
    {
      if ( strlen(userId) > AM_MAX_USERID_LEN )
	returnFault(AM_ILLEGAL_ARGUMENT);
	orderData.userId = new char [strlen(userId)+1];
	if (orderData.userId != NULL)
	  strcpy(orderData.userId, userId);
	else
	    returnFault(AM_NO_MEMORY);
    }
  else
    returnFault(AM_ILLEGAL_ARGUMENT);
  
  
  if (parameters != NULL)
    {
      if ( strlen(parameters) > AM_PARAMETERS_MAX_LEN )
	returnFault(AM_ILLEGAL_ARGUMENT);
      orderData.parameters = new char [strlen(parameters)+1];
      if (orderData.parameters != NULL)
	    strcpy(orderData.parameters, parameters);
      else
	returnFault(AM_NO_MEMORY);
    }

    switch (interval.intervalBase)
      {
      case AM_NONE:
	if (interval.split != 1)
		returnFault(AM_ILLEGAL_ARGUMENT);
	break;
      case AM_WEEKLY:
	if ( (interval.split < AM_SUNDAY) ||
	     (interval.split > AM_SATURDAY) )
	  returnFault(AM_ILLEGAL_ARGUMENT);
	break;
      case AM_HOURLY:
      case AM_DAILY:
      case AM_MONTHLY:
      case AM_ANNUALLY:
	if ( (interval.split < 1) || (interval.split > 12 ) ) 
	  returnFault(AM_ILLEGAL_ARGUMENT);
	break;
      default:
	returnFault(AM_ILLEGAL_ARGUMENT);
      }
    
    orderData.interval.intervalBase = interval.intervalBase;
    orderData.interval.split = interval.split;
    orderData.startTime = startTime;
    orderData.status = status;
    orderData.outMsgMail = outMsgMail;
    
    if (host != NULL)
      {
	orderData.host = new char [strlen(host)+1];
	if (orderData.host != NULL)
	  strcpy(orderData.host, host);
	else
	  returnFault(AM_NO_MEMORY);
      }
    
    orderData.tasId = tasId;
    orderData.timestamp = timestamp;
    
    return AM_OK;    
}    


//*****************************************************************************
int
AM_Order::setOrderData ( const char* filename,
			 const char* networkElement,
			 const char* userId,
			 const int   status,    
			 time_t      startTime,    
    			 AM_Interval interval,
			 const char* mailAddress,
			 const char* host,
                         const char* OZTLabel,
                         const char* OZTDisplay,
			 const char* mailOutputDest,
			 const char* fileOutputDest,
			 const char* printOutputDest,
			 const int   tasId,
			 const int   OZTDisplayOn,
			 time_t      timestamp)
{
    orderData.orderKey = 0;
    orderData.orderType = 2; //OPS script - OPS
 
    if (filename != NULL)
    {
	if ( strlen(filename) > AM_MAX_FILENAME_LEN )
	    returnFault(AM_ILLEGAL_ARGUMENT);
	orderData.filename = new char [strlen(filename)+1];
	if (orderData.filename != NULL)
	    strcpy(orderData.filename, filename);
	else
	    returnFault(AM_NO_MEMORY);
    }
    else
	returnFault(AM_ILLEGAL_ARGUMENT);
 
 
    if (networkElement != NULL)
    {
	//if ( strlen(networkElement) > AM_MAX_EXTSYSTEM_LEN )
	//    returnFault(AM_ILLEGAL_ARGUMENT);
	orderData.networkElement = new char [strlen(networkElement)+1];
	if (orderData.networkElement != NULL)
	    strcpy(orderData.networkElement, networkElement);
	else
	    returnFault(AM_NO_MEMORY);
    }
    else
	returnFault(AM_ILLEGAL_ARGUMENT);
 
 
    if (userId != NULL)
    {
	if ( strlen(userId) > AM_MAX_USERID_LEN )
	    returnFault(AM_ILLEGAL_ARGUMENT);
	orderData.userId = new char [strlen(userId)+1];
	if (orderData.userId != NULL)
	    strcpy(orderData.userId, userId);
	else
	    returnFault(AM_NO_MEMORY);
    }
    else
	returnFault(AM_ILLEGAL_ARGUMENT);
 
    
    if (mailAddress != NULL)
    {
	if ( strlen(mailAddress) > AM_MAX_MAILADDRESS_LEN )
	    returnFault(AM_ILLEGAL_ARGUMENT);
	orderData.mailAddress = new char [strlen(mailAddress)+1];
	if (orderData.mailAddress != NULL)
	    strcpy(orderData.mailAddress, mailAddress);
	else
	    returnFault(AM_NO_MEMORY);
    }
    else
	returnFault(AM_ILLEGAL_ARGUMENT);
 
 
    switch (interval.intervalBase)
    {
	case AM_NONE:
	    if (interval.split != 1)
		returnFault(AM_ILLEGAL_ARGUMENT);
            break;
        case AM_WEEKLY:
            if ( (interval.split < AM_SUNDAY) ||
		 (interval.split > AM_SATURDAY) )
		returnFault(AM_ILLEGAL_ARGUMENT);
            break;
	case AM_HOURLY:
	case AM_DAILY:
    	case AM_MONTHLY:
    	case AM_ANNUALLY:
            if ( (interval.split < 1) || (interval.split > 12 ) ) 
		returnFault(AM_ILLEGAL_ARGUMENT);
            break;
        default:
	    returnFault(AM_ILLEGAL_ARGUMENT);
    }
 
    orderData.interval.intervalBase = interval.intervalBase;
    orderData.interval.split = interval.split;
    orderData.startTime = startTime;
 
    orderData.status = status;
 
    if (host != NULL)
    {
	orderData.host = new char [strlen(host)+1];
	if (orderData.host != NULL)
	    strcpy(orderData.host, host);
	else
	    returnFault(AM_NO_MEMORY);
    }
 
    if (OZTLabel != NULL)
    {
	orderData.OZTLabel = new char [strlen(OZTLabel)+1];
	if (orderData.OZTLabel != NULL)
	    strcpy(orderData.OZTLabel, OZTLabel);
	else
	    returnFault(AM_NO_MEMORY);
    }
 
    if (OZTDisplay != NULL)
    {
	orderData.OZTDisplay = new char [strlen(OZTDisplay)+1];
	if (orderData.OZTDisplay != NULL)
	    strcpy(orderData.OZTDisplay, OZTDisplay);
	else
	    returnFault(AM_NO_MEMORY);
    }
 
    if (mailOutputDest != NULL)
    {
		if (strlen(mailOutputDest) > AM_MAX_ROUTING_LEN )
			returnFault(AM_ILLEGAL_ARGUMENT);
		orderData.mailOutputDest = new char [strlen(mailOutputDest) + 1];
		if (orderData.mailOutputDest != NULL)
			strcpy(orderData.mailOutputDest, mailOutputDest);
		else
			returnFault(AM_NO_MEMORY);
	}
    else
		returnFault(AM_ILLEGAL_ARGUMENT);

    if (fileOutputDest != NULL)
    {
		if (strlen(fileOutputDest) > AM_MAX_ROUTING_LEN )
			returnFault(AM_ILLEGAL_ARGUMENT);
		orderData.fileOutputDest = new char [strlen(fileOutputDest) + 1];
		if (orderData.fileOutputDest != NULL)
			strcpy(orderData.fileOutputDest, fileOutputDest);
		else
			returnFault(AM_NO_MEMORY);
    }
    else
		returnFault(AM_ILLEGAL_ARGUMENT);

    if (printOutputDest != NULL)
    {
		if (strlen(printOutputDest) > AM_MAX_ROUTING_LEN )
			returnFault(AM_ILLEGAL_ARGUMENT);
		orderData.printOutputDest = new char [strlen(printOutputDest) + 1];
		if (orderData.printOutputDest != NULL)
			strcpy(orderData.printOutputDest, printOutputDest);
		else
			returnFault(AM_NO_MEMORY);
    }
    else
		returnFault(AM_ILLEGAL_ARGUMENT);
 
    orderData.tasId = tasId;
    orderData.timestamp = timestamp;
    orderData.OZTDisplayOn =  OZTDisplayOn;
 
    return AM_OK;
}

//*****************************************************************************

int
AM_Order::getOrderData (AM_OrderData *& outData )
{
 
//    outData = new AM_OrderData;
    outData = AM_auxFunctions::getAM_OrderDataObject();

    if (outData == NULL) 
        return AM_NO_MEMORY;

    int result = structCopy(&orderData, outData);
    if (result != AM_OK)
    {
        AM_auxFunctions::deleteStrings(outData);
        delete outData; outData = NULL;
        if (result == AM_NO_MEMORY)
 	    return AM_NO_MEMORY;
	else
        {
       	    //Unexpected return value.
            return AM_ERROR;
        }
    }
    return AM_OK;
}

//*****************************************************************************

int
AM_Order::setKey(long orderKey)
{
    if ( (orderKey <= AM_RESERVED_KEY) || (orderKey > AM_ORDER_KEY_MAX_VALUE) )
	return AM_ILLEGAL_ARGUMENT; 
    orderData.orderKey = orderKey;
    return AM_OK;
}

//*****************************************************************************

int
structCopy (AM_OrderData * in, AM_OrderData * out)
{

    if  (in->filename == NULL)
	out->filename = NULL;
    else
    {
	out->filename = new char[strlen (in->filename)+1];
	if (out->filename == NULL)
	    return AM_NO_MEMORY;
        else
	    strcpy(out->filename, in->filename);
    }

    if  (in->networkElement == NULL)
	out->networkElement = NULL;
    else
    {
	out->networkElement = new char[strlen (in->networkElement)+1];
	if (out->networkElement == NULL)
	    return AM_NO_MEMORY;
        else
	    strcpy(out->networkElement, in->networkElement);
    }

    if  (in->userId == NULL)
	out->userId = NULL;
    else
    {
	out->userId = new char[strlen (in->userId)+1];
	if (out->userId == NULL)
	    return AM_NO_MEMORY;
        else
	    strcpy(out->userId, in->userId);
    }

    if  (in->outputDest == NULL)
	out->outputDest = NULL;
    else
    {
	out->outputDest = new char[strlen (in->outputDest)+1];
	if (out->outputDest == NULL)
	    return AM_NO_MEMORY;
        else
	    strcpy(out->outputDest, in->outputDest);
    }

    if  (in->mailOutputDest == NULL)
		out->mailOutputDest = NULL;
    else
    {
		out->mailOutputDest = new char[strlen (in->mailOutputDest) + 1];
		if (out->mailOutputDest == NULL)
			return AM_NO_MEMORY;
        else
			strcpy(out->mailOutputDest, in->mailOutputDest);
    }

    if  (in->fileOutputDest == NULL)
		out->fileOutputDest = NULL;
    else
    {
		out->fileOutputDest = new char[strlen (in->fileOutputDest) + 1];
		if (out->fileOutputDest == NULL)
			return AM_NO_MEMORY;
		else
			strcpy(out->fileOutputDest, in->fileOutputDest);
    }

    if  (in->printOutputDest == NULL)
		out->printOutputDest = NULL;
    else
    {
		out->printOutputDest = new char[strlen (in->printOutputDest) + 1];
		if (out->printOutputDest == NULL)
			return AM_NO_MEMORY;
        else
			strcpy(out->printOutputDest, in->printOutputDest);
    }

    if  (in->immRouting == NULL)
		out->immRouting = NULL;
    else
    {
		out->immRouting = new char[strlen (in->immRouting)+1];
		if (out->immRouting == NULL)
			return AM_NO_MEMORY;
        else
			strcpy(out->immRouting, in->immRouting);
    }

    if  (in->delRouting == NULL)
	out->delRouting = NULL;
    else
    {
	out->delRouting = new char[strlen (in->delRouting)+1];
	if (out->delRouting == NULL)
	    return AM_NO_MEMORY;
        else
	    strcpy(out->delRouting, in->delRouting);
    }

    if  (in->mailAddress == NULL)
	out->mailAddress = NULL;
    else
    {
	out->mailAddress = new char[strlen (in->mailAddress)+1];
	if (out->mailAddress == NULL)
	    return AM_NO_MEMORY;
        else
	    strcpy(out->mailAddress, in->mailAddress);
    }

    if  (in->parameters == NULL)
	out->parameters = NULL;
    else
    {
	out->parameters = new char[strlen (in->parameters)+1];
	if (out->parameters == NULL)
	    return AM_NO_MEMORY;
        else
	    strcpy(out->parameters, in->parameters);
    }

    if  (in->host == NULL)
	out->host = NULL;
    else
    {
	out->host = new char[strlen (in->host)+1];
	if (out->host == NULL)
	    return AM_NO_MEMORY;
        else
	    strcpy(out->host, in->host);
    }

    if  (in->OZTLabel == NULL)
	out->OZTLabel = NULL;
    else
    {
	out->OZTLabel = new char[strlen (in->OZTLabel)+1];
	if (out->OZTLabel == NULL)
	    return AM_NO_MEMORY;
        else
	    strcpy(out->OZTLabel, in->OZTLabel);
    }

    if  (in->OZTDisplay == NULL)
	out->OZTDisplay = NULL;
    else
    {
	out->OZTDisplay = new char[strlen (in->OZTDisplay)+1];
	if (out->OZTDisplay == NULL)
	    return AM_NO_MEMORY;
        else
	    strcpy(out->OZTDisplay, in->OZTDisplay);
    }

    out->orderKey = in->orderKey;
    out->orderType = in->orderType;
    out->status = in->status;
    out->startTime = in->startTime;
    out->interval.intervalBase = in->interval.intervalBase;
    out->interval.split = in->interval.split;
    out->funcBusyInterval = in->funcBusyInterval;
    out->stopContNA = in->stopContNA;
    out->stopContPE = in->stopContPE;
    out->mailError = in->mailError;
    out->mailResult = in->mailResult;
	out->synchro = in->synchro;
    out->outMsgMail = in->outMsgMail;
    out->tasId = in->tasId;
    out->timestamp = in->timestamp;
    out->OZTDisplayOn = in->OZTDisplayOn;

    return AM_OK;
}



