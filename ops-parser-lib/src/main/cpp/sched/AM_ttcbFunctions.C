//**********************************************************************

// NAME
//		AM_ttcbFunctions.C

// COPYRIGHT
// COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1999
//
// The Copyright to the computer program(s) herein is the
// property of Ericsson Hewlett-Packard Telecommunications AB, Sweden.
// The program(s) may be used and/or copied with the
// written permission from Ericsson Hewlett-Packard telecommunications AB
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



#include <AM_Order.H>
#include <AM_OrderStorage.H>

#include <tas_tc_time_control.hh>

#include <stdio.h>

#include <ctype.h>


//#include <cap_ter.H>
#include <time.h>
#include <stdlib.h>
#include <unistd.h> // gethostname on HP
#include <AM_ttcbFunctions.H>
#include <AM_auxFunctions.H>
#include <CHA_Trace.H>

char* CHA_AM_DISPLAYHOST;

//*****************************************************************************

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"AM_ttcbFunctions",(char*)"C");

//*****************************************************************************

static const char* AM_ADD_STRING = "/emt_ttcuip -a -h";
static const char* AM_REMOVE_STRING = "/emt_ttcuip -r -h";

const int MAXHOSTNAMELEN = 64;
const int AM_ADD = 0;
const int AM_REMOVE = 1;

// The time in seconond before T when the order that sets up the T order
// executes!
const int AM_BEFORE_T = 120;

char* TTC_SERVER = NULL;
char* CHA_HOSTNAME = NULL;
char* ttcuchHost = NULL;
//*****************************************************************************
extern const char *Get_host();

//*****************************************************************************

int 	buildCommandLine(AM_OrderData*, char *&);
int	buildTtcuipString(AM_OrderData*, char*, int, char *&, int check = 0);
int	buildComEntry(char*,TAS_TC_com_entry*&,AM_OrderData*,int interval = 0);
int     buildRemoveEntry(char*, AM_OrderData*,TAS_TC_com_entry*&);
void    getHostNames();
int isEmpty(const char *ptr);
int checkLength(const char *word);

//*****************************************************************************

int
AM_ttcbFunctions::initOrder(AM_OrderData * data,TAS_TC_time_control * & tc)
{
	//TRACE_IN(trace, initOrder, "");

    int result;
    int tasId;
    TAS_TC_com_entry*	orderEntry = NULL;


    if (CHA_HOSTNAME == NULL)
	getHostNames();


    char*	commandLine = NULL;
    result = buildCommandLine(data, commandLine);

	//TRACE_FLOW(trace, initOrder, "Built commandLine: " << commandLine);

    if (result != AM_OK)
    {
	delete [] commandLine; commandLine = NULL;
        if (result == AM_ERROR)
	    return AM_ERROR;
        else
	    if (result == AM_NO_MEMORY)
		return AM_NO_MEMORY;
            else
            {
            	// Unexpected return value.
	        return AM_ERROR;
       	    }
    }

    //-------------------------------------------------------------------------
    // case of single execution
    //-------------------------------------------------------------------------

    if (data->interval.intervalBase == AM_NONE)
    {
	result = buildComEntry(commandLine,orderEntry,data);

   	if (result != AM_OK)
    	{
	    delete [] commandLine; commandLine = NULL;
      if (result == AM_ERROR)
        return AM_ERROR;
      else
        if (result == AM_NO_MEMORY)
          return AM_NO_MEMORY;
        else
        {
           	    // Unexpected return value.
	        return AM_ERROR;
        }
      }
	delete [] commandLine;
	commandLine = NULL;

	tc->add(orderEntry);
	tasId = orderEntry->Get_id();
	data->tasId=tasId;
	delete orderEntry;
	orderEntry = NULL;

        switch(tc->get_error_code())
	{
	case 0:
	    break;
	case 3:
	    return AM_JOBEXISTS;
	case 5:
	    return AM_TIMEERR;
	default:
	    return AM_ERROR;
	}
    }// End of if single execution

    //-------------------------------------------------------------------------
    // case of periodic execution
    //-------------------------------------------------------------------------
    else
    {
	char*	ttcuchLine = NULL;
        result = buildTtcuipString(data, commandLine, AM_ADD, ttcuchLine);
        if ( result != AM_OK)
        {
	    delete [] commandLine; commandLine = NULL;
            if (result != AM_NO_MEMORY)
            {
                 // Unexpected return value.
                 return AM_ERROR;
             }
             else return AM_NO_MEMORY;
    	}
	delete [] commandLine; commandLine = NULL;

	result = buildComEntry(ttcuchLine,orderEntry,data, 1);

   	if (result != AM_OK)
    	{
	    delete [] ttcuchLine; ttcuchLine = NULL;
            if (result == AM_ERROR)
		return AM_ERROR;
            else
		if (result == AM_NO_MEMORY)
			return AM_NO_MEMORY;
        	else
        	{
            	    // Unexpected return value.
	            return AM_ERROR;
        	}
      	}
	delete [] ttcuchLine;
	ttcuchLine = NULL;

	tc->add(orderEntry);
	tasId = orderEntry->Get_id();
	data->tasId=tasId;
	delete orderEntry; orderEntry = NULL;
	switch(tc->get_error_code())
	{
	case 0:
	    break;
	case 3:
	    return AM_JOBEXISTS;
	case 5:
	    return AM_TIMEERR;
	default:
	    return AM_ERROR;
	}
    }// end of else: periodic execution

	//TRACE_RETURN(trace, initOrder, "AM_OK");

    return AM_OK;
}

//*****************************************************************************

int
AM_ttcbFunctions::terminateOrder(AM_OrderData * data,
				 TAS_TC_time_control * & tc)
{
	//TRACE_IN(trace, terminateOrder, "");

    int result;
    TAS_TC_com_entry*	orderEntry = NULL;

    if (CHA_HOSTNAME == NULL)
	getHostNames();


    char*	commandLine = NULL;
    result = buildCommandLine(data, commandLine);

	//TRACE_FLOW(trace, terminateOrder, "commandLine: " << commandLine);

    if (result != AM_OK)
    {
	delete [] commandLine; commandLine = NULL;
        if (result == AM_ERROR)
	    return AM_ERROR;
        else
	    if (result == AM_NO_MEMORY)
		return AM_NO_MEMORY;
            else
            {
            	// Unexpected return value.
	        return AM_ERROR;
       	    }
    }

    //-------------------------------------------------------------------------
    // case of single execution
    //-------------------------------------------------------------------------
    if (data->interval.intervalBase == AM_NONE)
    {
	result = buildComEntry(commandLine,orderEntry,data);

   	if (result != AM_OK)
    	{
	    delete [] commandLine;
	    commandLine = NULL;
            if (result == AM_ERROR)
		return AM_ERROR;
            else
		if (result == AM_NO_MEMORY)
			return AM_NO_MEMORY;
        	else
        	{
            	    // Unexpected return value.
	            return AM_ERROR;
        	}
      	}
	delete [] commandLine;
	commandLine = NULL;

	result = tc->remove(*orderEntry);
	delete orderEntry;
	orderEntry = NULL;
	switch(tc->get_error_code())
	{
	case 0:
	    break;
	case 4:
	    return AM_JOBNOTEXIST;
	default:
	    return AM_ERROR;
	}
    }// End of if single execution

    //-------------------------------------------------------------------------
    // case of periodic execution
    //-------------------------------------------------------------------------
    else
    {
	char*	ttcuchLine = NULL;

	// The AM_BEFORE_T sec correction does NOT solve the problem entirely.
	// There remains a critical period just around T-AM_BEFORE_T to T
        // We are now sure to have 3 seconds during which T-AM_BEFOR_T order
        // is present in crontab file

	result = AM_auxFunctions::checkDate((data->startTime)-AM_BEFORE_T-3);
	//-----------------------------------------------------------------
	// when execution not started yet
	//-----------------------------------------------------------------
	if (result == AM_OK)
	{
            result = buildTtcuipString(data, commandLine, AM_ADD, ttcuchLine);
            if ( result != AM_OK)
            {
	        delete [] commandLine;
		commandLine = NULL;
                if (result != AM_NO_MEMORY)
                {
                    // Unexpected return value.
                    return AM_ERROR;
                }
                else return AM_NO_MEMORY;
	    }
	    delete [] commandLine;
	    commandLine = NULL;

	    result = buildComEntry(ttcuchLine,orderEntry,data, 1);

	    if (result != AM_OK)
    	    {
	        delete [] ttcuchLine;
		ttcuchLine = NULL;
                if (result == AM_ERROR)
		    return AM_ERROR;
                else
		    if (result == AM_NO_MEMORY)
		        return AM_NO_MEMORY;
        	    else
        	    {
            	        // Unexpected return value.
	                return AM_ERROR;
        	    }
      	    }
	    delete [] ttcuchLine;
	    ttcuchLine = NULL;

	    result = tc->remove(*orderEntry);
	    delete orderEntry; orderEntry = NULL;
	    switch(tc->get_error_code())
	    {
	    case 0:
		break;
	    case 4:
		return AM_JOBNOTEXIST;
	    default:
		return AM_ERROR;
	    }
	}

	//-----------------------------------------------------------------
	// when execution already started
	//-----------------------------------------------------------------
	else
	{
	    result = AM_auxFunctions::checkDate(data->startTime);
	    if (result == AM_OK)
		return AM_ERROR;

	    // just testing
	    result = buildRemoveEntry(commandLine, data, orderEntry);

          if ( result != AM_OK)
          {
            delete [] commandLine; commandLine = NULL;
            delete orderEntry; orderEntry = NULL;
            if (result != AM_NO_MEMORY)
            {
                  // Unexpected return value.
              return AM_ERROR;
            }
            else return AM_NO_MEMORY;
    	    }
	    delete [] commandLine; commandLine = NULL;

	    result = tc->remove(*orderEntry);
	    delete orderEntry; orderEntry = NULL;
	    switch(tc->get_error_code())
	    {
	    case 0:
		break;
	    case 4:
		return AM_JOBNOTEXIST;
	    default:
		return AM_ERROR;
	    }
	}

    }// end of else: periodic execution

	//TRACE_RETURN(trace, terminateOrder, "AM_OK");

    return AM_OK;
}

//*****************************************************************************


int
AM_ttcbFunctions::createCEObject(AM_OrderData * data,
				     TAS_TC_com_entry * & orderEntry)
{
	//TRACE_IN(trace, createCEObject, "");

    int result;
    char * commandLine = NULL;

    if (CHA_HOSTNAME == NULL)
	getHostNames();

    result = buildCommandLine(data, commandLine);
    if (result != AM_OK)
    {
	delete [] commandLine;
        if (result != AM_NO_MEMORY)
	    return AM_ERROR;
        else
	    return AM_NO_MEMORY;
    }

    //-------------------------------------------------------------------------
    // case of single execution
    //-------------------------------------------------------------------------
    if (data->interval.intervalBase == AM_NONE)
    {
	result = buildComEntry(commandLine,orderEntry,data);
   	if (result != AM_OK)
    	{
	    delete [] commandLine;
	    if (result != AM_NO_MEMORY)
		return AM_ERROR;
	    else
		return AM_NO_MEMORY;
      	}
	delete [] commandLine;
    }

    //-------------------------------------------------------------------------
    // case of periodic execution
    //-------------------------------------------------------------------------
    else
    {
	char*	ttcuchLine = NULL;

        // Substract AM_BEFORE_T sec. from startTime because order changes
        // Substarct another 3 seconds to have time to process the order
 	result = AM_auxFunctions::checkDate((data->startTime)-AM_BEFORE_T-3);
	if (result == AM_OK)
	{
            // We have 3 seconds during which T-AM_BEFORE_T order is in crontab
	    result = buildTtcuipString(data, commandLine, AM_ADD, ttcuchLine,1);
	    if ( result != AM_OK)
	    {
		delete [] commandLine;
		if (result != AM_NO_MEMORY)
		    return AM_ERROR;
		else
		    return AM_NO_MEMORY;
	    }
	    delete [] commandLine;

	    result = buildComEntry(ttcuchLine,orderEntry,data, 1);
	    if (result != AM_OK)
	    {
		delete [] ttcuchLine;
		if (result != AM_NO_MEMORY)
		    return AM_ERROR;
		else
		    return AM_NO_MEMORY;
	    }
	    delete [] ttcuchLine;
	}
	else
	{
	    result = AM_auxFunctions::checkDate(data->startTime);
	    if (result == AM_OK)
		return AM_OLD_DATE; // Not really, but value will do!

	    result = buildRemoveEntry(commandLine, data, orderEntry);

            if ( result != AM_OK)
            {
	        AM_auxFunctions::deleteStrings(data);
	        delete data; data = NULL;
		delete [] commandLine;
		commandLine = NULL;
		delete orderEntry; orderEntry = NULL;
                if (result != AM_NO_MEMORY)
                {
                    // Unexpected return value.
                    return AM_ERROR;
                }
                else return AM_NO_MEMORY;
    	    }
	    delete [] commandLine;
	}
    }

	//TRACE_OUT(trace, createCEObject, "AM_OK");

    return AM_OK;
}


//*****************************************************************************


int
buildComEntry(char* commandLine,TAS_TC_com_entry*& orderEntry,
	      AM_OrderData* data,int intervalOn)
{
	//TRACE_IN(trace, buildComEntry, "");

    int 	result;
    struct tm* 	tmp;
    char*       tmpHost = data->host;
    time_t      startTime = data->startTime;
    time_t      tmpTime = startTime-AM_BEFORE_T;

    if (commandLine == NULL)
	return AM_NO_MEMORY;

    tmp = localtime(&startTime);


    // Start the initiation job for periodic jobs AM_BEFORE_T seconds before
    // actual time because TAS can NOT handle this case. tmpHost changed so
    // T-AM_BEFORE_T job runs on TTC_SERVER; minimizes time job is
    // not present in crontab.
    if (intervalOn == 1)
    {
	tmpHost = TTC_SERVER;
	tmp = localtime(&tmpTime);
    }

	//TRACE_FLOW(trace, buildComEntry, "User: " << data->userId);

    orderEntry = new TAS_TC_com_entry(tmpHost,
                                      commandLine,
                                      tmp->tm_year+1900,
                                      tmp->tm_mon+1,
                                      tmp->tm_mday,
                                      tmp->tm_hour,
                                      tmp->tm_min,
				      data->userId,
				      data->tasId);

	//TRACE_RETURN(trace, buildComEntry, "");

    if (orderEntry == NULL)
	return AM_NO_MEMORY;
    else
	return AM_OK;
}

//*****************************************************************************

int
buildTtcuipString(AM_OrderData* data, char* commandLine,
                  int action, char *& ttcuchLine, int check)
{
  //TRACE_IN(trace, buildTtcuipString, "");

    char 	monthStr[3];
    char 	dayStr[3];
    char 	splitStr[3];
    char 	hourStr[3];
    char 	minuteStr[3];
    struct tm*  tmp=NULL;
    char text[15];
    char* tmpHost = data->host;
    int lengthOfTtcuipHost=0;

    // If this is a check for existence in crontab then use host from
    // crontabentry!

    if (check)
	tmpHost = ttcuchHost;

    if (tmpHost != NULL)
	lengthOfTtcuipHost=strlen(tmpHost);

    if (commandLine == NULL)
        return AM_NO_MEMORY;
    if (data == NULL)
        return AM_NO_MEMORY;

    tmp = localtime(&data->startTime);
    strcpy ( monthStr, AM_auxFunctions::ltoa(tmp->tm_mon,text) );
    strcpy ( dayStr, AM_auxFunctions::ltoa(tmp->tm_mday,text) );
    strcpy ( splitStr, AM_auxFunctions::itoa(data->interval.split,text) );
    strcpy ( hourStr, AM_auxFunctions::ltoa(tmp->tm_hour,text) );
    strcpy ( minuteStr, AM_auxFunctions::ltoa(tmp->tm_min,text) );

    char *am_add_string = new char[strlen(getenv("AM_TTCUIP_EXEC_PATH")) + strlen(AM_ADD_STRING) + 1];

    if (am_add_string == NULL)
        return AM_NO_MEMORY;

    char *am_remove_string = new char[strlen(getenv("AM_TTCUIP_EXEC_PATH")) + strlen(AM_REMOVE_STRING) +1];

    if (am_remove_string == NULL)
    {
      delete [] am_add_string;
      return AM_NO_MEMORY;
    }

    (void) sprintf(am_add_string, "%s%s", getenv("AM_TTCUIP_EXEC_PATH"), AM_ADD_STRING);
    (void) sprintf(am_remove_string, "%s%s", getenv("AM_TTCUIP_EXEC_PATH"), AM_REMOVE_STRING);

    ttcuchLine = new char[ strlen(am_add_string) +
                            lengthOfTtcuipHost +
                            strlen(monthStr) +
                            strlen(dayStr) +
                            strlen(splitStr) +
                            strlen(hourStr) +
                            strlen(minuteStr) +
                            strlen(commandLine) + 30 ];
    if (ttcuchLine == NULL)
    {
      delete [] am_add_string;
      delete [] am_remove_string;

      return AM_NO_MEMORY;
    }

    if (action == AM_ADD)
      strcpy(ttcuchLine, am_add_string);
    if (action == AM_REMOVE)
      strcpy(ttcuchLine, am_remove_string);

    delete [] am_add_string;
    delete [] am_remove_string;

    if (tmpHost != NULL)
      strcat(ttcuchLine, tmpHost);

    switch (data->interval.intervalBase)
    {
        case AM_ANNUALLY:
            strcat(ttcuchLine, " -m");
            strcat(ttcuchLine, monthStr);
        case AM_MONTHLY:
            strcat(ttcuchLine, " -d");
            strcat(ttcuchLine, dayStr);
        case AM_DAILY:
            strcat(ttcuchLine, " -H");
            strcat(ttcuchLine, hourStr);
        case AM_HOURLY:
            strcat(ttcuchLine, " -M");
            strcat(ttcuchLine, minuteStr);
            strcat(ttcuchLine, " -s");
            strcat(ttcuchLine, splitStr);
            break;
        case AM_WEEKLY:
            strcat(ttcuchLine, " -w");
            strcat(ttcuchLine, splitStr);
            strcat(ttcuchLine, " -H");
            strcat(ttcuchLine, hourStr);
            strcat(ttcuchLine, " -M");
            strcat(ttcuchLine, minuteStr);
            break;
        case NONE:
        default:
            delete [] ttcuchLine; ttcuchLine = NULL;
            return AM_ILLEGAL_ARGUMENT;
    }
    strcat(ttcuchLine, " -c");
///    strcat(ttcuchLine, " \"");
    strcat(ttcuchLine, " \'");
    strcat(ttcuchLine, commandLine);
///    strcat(ttcuchLine, "\"");
    strcat(ttcuchLine, "\'");

	//TRACE_RETURN(trace, buildTtcuipString, "");

    return AM_OK;
}


//*****************************************************************************

int
buildCommandLine(AM_OrderData* data, char *& commandLine)
{
  //TRACE_IN(trace, buildCommandLine, "");

  char text[15];
  if (data->orderType == 0) { //case of MML file - cfi

    if(getenv("AM_CFI_EXEC_PATH") != NULL) {

      commandLine = new char[strlen(getenv("AM_CFI_EXEC_PATH")) +
			    strlen(data->filename) +
			    strlen(data->networkElement) +
			    strlen(AM_auxFunctions::ltoa(data->funcBusyInterval,text)) +
			    strlen(data->outputDest) +
			    strlen(data->mailAddress)*2 + 130 ];

      strcpy(commandLine, getenv("AM_CFI_EXEC_PATH"));
      strcat(commandLine, "/cfi ");

      // busy retry period
      strcat(commandLine, " -b ");
      strcat(commandLine,
	     AM_auxFunctions::ltoa(data->funcBusyInterval,text));

      // routing of all responses
      if (data->outputDest != NULL)
	{
	  if (strcmp(data->outputDest, "") != 0) {
	    strcat(commandLine, " -a ");
	    strcat(commandLine, data->outputDest);
	  }
	}

      // continue even if command is not accepted
      if (data->stopContNA == 0)
	strcat(commandLine, " -n ");

      // continue even when command is partly executed
      if (data->stopContPE == 1)
	strcat(commandLine, " -p ");

      // send mail on error
      if (data->mailError == 1)
	{
	  strcat(commandLine, " -e ");
	  strcat(commandLine, data->mailAddress);
	}

      // send mail about execution result
      if (data->mailResult == 1)
	{
	  strcat(commandLine, " -r ");
	  strcat(commandLine, data->mailAddress);
	}

      // If true the reception of shall be synchronous
      if (data->synchro == 1)
	{
	  strcat(commandLine, " -d synchro ");
	}

      strcat(commandLine, " -N ");
      strcat(commandLine, data->networkElement);

      strcat(commandLine, " -F ");
      strcat(commandLine, data->filename);
      strcat(commandLine, " ");

      // make sure that the commandLine is executed in a Bourne shell
      // and that stdout and stderr is redirected to /dev/null

      char *help = strdup(commandLine);
      sprintf(commandLine,"echo \"%s > /dev/null 2>&1\" | sh ",help);
      delete [] help; help = NULL;

    }
    else {
      return AM_NO_EXEC_PATH_ERR;
    }

  }
  else if (data->orderType == 1)//case of system command file - CFH
    {

      commandLine = new char[strlen(data->filename) +
			    strlen(data->parameters) + 40 ];

      //strcpy(commandLine,"/");
      strcpy(commandLine, data->filename);

      if (strcmp(data->parameters, "") != 0 )
	{
	  strcat(commandLine, " ");
	  strcat(commandLine, data->parameters);
	}

      if (data->outMsgMail == 0) // redirect stdout & stderr to /dev/null
	{
	  // redirect stdout & stderr to /dev/null and make sure that
	  // the command line is executed in Bourne shell

// 	  char *help = strdup(commandLine);
	  char* help = new char[strlen(commandLine) + 1];
	  strcpy(help, commandLine);
	  sprintf(commandLine,"echo \"%s > /dev/null 2>&1\" | sh ",help);
 	  delete [] help; help = NULL;
	}
      else
        {
	  // redirect only stderr to /dev/null and make sure that Bourne shell
	  // is used
// 	  char *help = strdup(commandLine);
	  char* help = new char[strlen(commandLine) + 1];
	  strcpy(help, commandLine);
	  sprintf(commandLine,"echo \"%s 2> /dev/null\" | sh ",help);
 	  delete [] help; help = NULL;
	}

    }
  else if (data->orderType == 2) { //case of OPS script - OPS

    if(getenv("AM_OPS_EXEC_PATH") != NULL && getenv("AM_OPS_NUI") != NULL) {
      commandLine = new char[strlen(getenv("AM_OPS_EXEC_PATH"))+ 1 + strlen(getenv("AM_OPS_NUI")) +
			    checkLength(data->filename) +
			    checkLength(data->networkElement) +
			    checkLength(data->OZTDisplay) +
			    checkLength(data->OZTLabel) +
			    checkLength(data->mailAddress) +
			    checkLength(data->mailOutputDest) +
			    checkLength(data->fileOutputDest) +
			    checkLength(data->printOutputDest) + 170 ];
      // Actual length of all hardcoded strings is 143 in this implementation.

      if (data->OZTDisplayOn) {
      	strcpy(commandLine, "env DISPLAY=");
      	strcat(commandLine, data->OZTDisplay);
	strcat(commandLine, " ");
	strcat(commandLine, getenv("AM_OPS_EXEC_PATH"));
      	strcat(commandLine,"/");
      } else {
      	strcpy(commandLine, getenv("AM_OPS_EXEC_PATH"));
      	strcat(commandLine,"/");
      }

      if (data->OZTDisplayOn)
	strcat(commandLine, getenv("AM_OPS_GUI"));
      else
	strcat(commandLine, getenv("AM_OPS_NUI"));

      if (data->OZTDisplayOn)
	  strcat(commandLine, " -mode run");

      if (!(isEmpty(data->mailAddress)))
	{
	  strcat(commandLine, " -mail ");
	  strcat(commandLine, data->mailAddress);
	}

      char startTime[33];

      strcat(commandLine, " -file ");
      strcat(commandLine, data->filename);
      if (!( isEmpty(data->networkElement)))
	{
	  strcat(commandLine, " -es ");
	  strcat(commandLine, data->networkElement);
	}
      if (!(isEmpty(data->OZTLabel)))
	{
	  strcat(commandLine, " -startlabel ");
	  strcat(commandLine, data->OZTLabel);
	}

      if (!(isEmpty(data->mailOutputDest)))
	{
	  strcat(commandLine, " -routemail ");
	  strcat(commandLine, data->mailOutputDest);
	}

      if (!(isEmpty(data->fileOutputDest)))
	{
	  strcat(commandLine, " -routefile ");
	  strcat(commandLine, data->fileOutputDest);
	}

      if (!(isEmpty(data->printOutputDest)))
	{
	  strcat(commandLine, " -routeprinter ");
	  strcat(commandLine, data->printOutputDest);
	}

      // make sure that the commandLine is executed in a Bourne shell
      // and that stdout and stderr is redirected to /dev/null

      char *help = strdup(commandLine);
      sprintf(commandLine,"echo \"%s > /dev/null 2>&1\" | sh ",help);
      delete [] help; help = NULL;
    }
    else {
      return AM_NO_EXEC_PATH_ERR;
    }

  }
  else if (data->orderType == 3) { // EME script - EME

    if(getenv("AM_EME_EXEC_PATH") != NULL) {

      commandLine = new char[strlen(getenv("AM_EME_EXEC_PATH")) + 8 +
			    strlen(data->filename) +
			    strlen(data->parameters) + 40 +
                            strlen(data->userId) + 4 + /*e-mail*/
                            strlen(data->userId) + 4]; /*user*/
      strcpy(commandLine, getenv("AM_EME_EXEC_PATH"));
      strcat(commandLine,"/eme -F ");
      strcat(commandLine, data->filename);

      if( data->outMsgMail !=  0 ) {
	if (strcmp(data->userId, "") != 0 ) {
	  strcat( commandLine, " -r " );
	  strcat(commandLine, data->userId );
	}
      }

      strcat(commandLine, " -u ");
      strcat(commandLine, data->userId);

      if (strcmp(data->parameters, "") != 0 )
	{
	  strcat(commandLine, " ");
	  strcat(commandLine, data->parameters);
	}

      if (data->outMsgMail == 0)
	{
	  // redirect stdout & stderr to /dev/null and make sure that
	  // the command line is executed in Bourne shell

	  char *help = strdup(commandLine);
	  sprintf(commandLine,
		  "echo \"%s > /dev/null 2>&1\" | sh ",help);
	  delete [] help; help = NULL;
	}
      else
	{
	  // redirect only stderr to /dev/null and make sure that
	  // Bourne shell is used
	  char *help = strdup(commandLine);
	  sprintf(commandLine,"echo \"%s 2> /dev/null\" | sh ",help);
	  delete [] help; help = NULL;
	}
    }
    else {
      return AM_NO_EXEC_PATH_ERR;
    }
  }

  //TRACE_RETURN(trace, buildCommandLine, "AM_OK");

  return AM_OK;
}

//*****************************************************************************
int
buildRemoveEntry(char *commandLine, AM_OrderData *data,
		     TAS_TC_com_entry*& orderEntry)
{
	//TRACE_IN(trace, buildRemoveEntry, "");

    int 	result;
    struct tm* 	tmp;

    char *tmpHost = CHA_HOSTNAME;

    if (commandLine == NULL)
	return AM_NO_MEMORY;

    tmp = localtime(&data->startTime);

    int interval = data->interval.intervalBase;

    switch(interval)
    {
    case AM_HOURLY: orderEntry = new TAS_TC_com_entry(data->host,
	                                              commandLine,
						      TCANY,
						      TCANY,
						      TCANY,
						      TCANY,
						      tmp->tm_min,
						      data->userId,
						      0,
						      (interv)data->interval.intervalBase,
						      data->interval.split
						      );
		    break;
    case AM_DAILY: orderEntry = new TAS_TC_com_entry(data->host,
						     commandLine,
						     TCANY,
						     TCANY,
						     TCANY,
						     tmp->tm_hour,
						     tmp->tm_min,
						     data->userId,
						     0,
						     (interv)data->interval.intervalBase,
						     data->interval.split
						     );


		    break;

    case AM_WEEKLY: orderEntry = new TAS_TC_com_entry(data->host,
						      commandLine,
						      TCANY,
						      TCANY,
						      TCANY,
						      tmp->tm_hour,
						      tmp->tm_min,
						      data->userId,
						      0,
						      (interv)data->interval.intervalBase,
						      data->interval.split
						      );


		    break;

    case AM_MONTHLY: orderEntry = new TAS_TC_com_entry(data->host,
						       commandLine,
						       TCANY,
						       TCANY,
						       tmp->tm_mday,
						       tmp->tm_hour,
						       tmp->tm_min,
						       data->userId,
						       0,
						       (interv)data->interval.intervalBase,
						       data->interval.split
						       );

		    break;

    case AM_ANNUALLY: orderEntry = new TAS_TC_com_entry(data->host,
							commandLine,
							TCANY,
							tmp->tm_mon,
							tmp->tm_mday,
							tmp->tm_hour,
							tmp->tm_min,
							data->userId,
							0,
							(interv)data->interval.intervalBase,
							data->interval.split
							);

		    break;

    default:  // should not be the case
		    return AM_ERROR;
    }

    if (orderEntry == NULL)
    {
	return AM_NO_MEMORY;
    }
    if (result = !orderEntry)
    {
	delete orderEntry; orderEntry = NULL;
	if (result == TTCB_CE_OUT_OF_MEMORY)
	    return AM_NO_MEMORY;
        else
        {
            // Error when creating the orderEntry object
            return AM_ERROR;
        }
    }

	//TRACE_RETURN(trace, buildRemoveEntry, "");

    return AM_OK;

}

void getHostNames()
{
	//TRACE_IN(trace, getHostNames, "");

  TTC_SERVER = getenv("AM_TTC_SERVER");

  CHA_HOSTNAME = new char [MAXHOSTNAMELEN];
  gethostname(CHA_HOSTNAME, MAXHOSTNAMELEN);
  //TRACE_OUT(trace, getHostNames, endl << "Host names: " << endl <<"TTC_SERVER= " << TTC_SERVER << endl <<"CHA HOST= " << CHA_HOSTNAME << endl);
}

char* AM_ttcbFunctions::getOwnHost()
{
	//TRACE_IN(trace, getOwnHost, "");

    if (CHA_HOSTNAME == NULL)
	getHostNames();

	//TRACE_RETURN(trace, getOwnHost, CHA_HOSTNAME);

    return CHA_HOSTNAME;
}

void
AM_ttcbFunctions::getTtcuipHost(TAS_TC_com_entry*& crontabEntry)
{
	//TRACE_IN(trace, getTtcuipHost, "");

    // To be removed when ID for an order is implemented!

    const char* cmdLine = crontabEntry->Get_command_line();
    char* tmpCmdLine = NULL;
    char* tmpCmdLine1 = NULL;
    char* tmpCmdLine2 = NULL;

    if (ttcuchHost != NULL)
    {
        delete [] ttcuchHost;
        ttcuchHost = NULL;
    }

    tmpCmdLine = new char [strlen(cmdLine)+1];
    strcpy(tmpCmdLine, cmdLine);
    tmpCmdLine1 = strstr(tmpCmdLine, "-h");

    if (tmpCmdLine1 != NULL)
    {
	tmpCmdLine2 = (strtok(tmpCmdLine1, " "));
        ttcuchHost = new char [strlen(tmpCmdLine2)+1];
        strcpy(ttcuchHost, (tmpCmdLine2+2));
    }
    delete [] tmpCmdLine;
    tmpCmdLine = NULL;

	//TRACE_OUT(trace, getTtcuipHost, "");
}


//*****************************************************************************


int isEmpty(const char *ptr)
{
	//TRACE_IN(trace, isEmpty, "");

    int empty = 1;

    if(ptr == 0 || strlen(ptr)== 0)
	return empty;

    while(*ptr && empty)
    {
	empty = isspace(*ptr);
	ptr++;
    }

	//TRACE_RETURN(trace, isEmpty, empty);

    return empty;

}


//*****************************************************************************

int checkLength(const char *word)
{
	//TRACE_IN(trace, checkLength, "");

	int length = 0;

	//TRACE_FLOW(trace, checkLength, word);
	if ( word != NULL ) {
		length = strlen(word);
	}

	//TRACE_RETURN(trace, checkLength, length);

	return length;
}


//*****************************************************************************
