// RCS revision handling
// $Id: SRMForwarder.C,v 24.2 1996/07/16 16:04:25 emejome Exp $

//**********************************************************************

// COPYRIGHT
//      COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1994
//
//      The Copyright to the computer program(s) herein is the
//      property of Ericsson Hewlett-Packard Telecommunications AB,
//      Sweden.  The program(s) may be used and/or copied with the
//      written permission from Ericsson Hewlett-Packard
//      Telecommunications AB or in accordance with the terms and
//      condition>`s stipulated in the agreement/contract under which
//      the program(s) have been supplied.

// DOCUMENT NO
//	190 89 - CAA 134 1064

// AUTHOR
//      1993-09-24 by EHS/PBU Dan Andersson (ehsdana@ehs.ericsson.se)

// REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	TB53_OZ 1995-11-28      J Grape (EHSGRAP)       RCS rev 24.0
//	XM2S1   1995-09-07      ehscama                 RCS rev 23.0
//	EC2_OZ  1995-08-01      Jan Sandquist (EHSJAASA)RCS rev 22.0
//	EC1_OZ  1995-06-29      J Grape (EHSGRAP)       RCS rev 21.0
//	TB5_2_OZ1995-06-08      J Grape (ehsgrap)       RCS rev 20.0
//	TB5_1_OZ1995-04-13      J Grape (EHSGRAP)       RCS rev 19.0
//	TB51_OZ 1995-03-17      ehscama                 RCS rev 18.0
//	TB5_OZ  1995-03-16      ehscama                 RCS rev 17.0
//	TB6_B1C_B1995-03-10      N.Lanninge (XKKNICL)    RCS rev 16.0
//	TB6_B1C 1995-03-09      N.Lanninge (XKKNICL)    RCS rev 15.0
//	TB4_OZ  1995-02-25      J Grape (EHSGRAP)       RCS rev 14.0
//	CHUI_TB61995-02-15      N.Lanninge (XKKNICL)    RCS rev 13.5
//	TB3     1995-02-06      J Grape (EHSGRAP)       RCS rev 12.0
//	PREIT   1995-01-18      N L\ufffdnninge (XKKNICL)    RCS rev 11.0
//	TB2     1994-12-22      J Grape (EHSGRAP)       RCS rev 10.0
//	E       1994-10-24      ehscama                 RCS rev 9.0
//	D       1994-10-05      EHSCAMA                 RCS rev 8.0
//	R1C     1994-09-22      J Grape (EHSGRAP)       RCS rev 7.0
//	R1B     1994-08-30      J Grape (EHSGRAP)       RCS rev 6.0
//      A 	931120	D. Andersson

// SEE ALSO
//

//**********************************************************************


#include <string.h>
#include <SRMForwarder.H>
/* TORF-241666
#include <nlsCHA.H>
#include <cap_trc.h>
#include <cap_pdb.H>
#include <cap_pdb_parameter.H> */
#include <CHA_Trace.H>

// Trace definitions:
static const char *const ESS_CHGI_TRC_IN          = "IN";
static const char *const ESS_CHGI_TRC_FLOW        = "FLOW";
static const char *const ESS_CHGI_TRC_OUT         = "OUT";
static const char *const ESS_CHGI_TRC_RETURN      = "return value";

// Definition for errors

const int       NLSSEVEREPDBERROR = 606;
const int       NLSIRCPDBTYPEERROR = 607;
const int       NLSIRCPDBFIELDERROR = 608;

// Definition of CAP Trace blocks:
/* TORF-241666
ESS_CHGI_Gateway_info
CAP_TRC_trace ESS_CHGI_Gateway_info_trc_msg =
CAP_TRC_DEF((char*)"ESS_CHGI_Gateway_info_msg",
		(char*)"C35,C8,C20");
CAP_TRC_trace ESS_CHGI_Gateway_info_trc_cont =
CAP_TRC_DEF((char*)"ESS_CHGI_Gateway_info_cont",
		(char*)"C35,C8,C10,C10,C10,C10,C10,i,C10,i");

CAP_TRC_trace ESS_CHGI_Gateway_info_trc_str =
CAP_TRC_DEF((char*)"ESS_CHGI_Gateway_info_str",
		(char*)"C35,C8,C20,C20");
ESS_CHGI_Gateway_characteristics
CAP_TRC_trace ESS_CHGI_Gateway_characteristics_trc_int =
CAP_TRC_DEF((char*)"ESS_CHGI_Gateway_info_int",
		(char*)"C35,C8,C20,i");
CAP_TRC_trace ESS_CHGI_Gateway_characteristics_trc_str =
CAP_TRC_DEF((char*)"ESS_CHGI_Gateway_info_str",
		(char*)"C35,C8,C20,C20");
CAP_TRC_trace ESS_CHGI_Gateway_characteristics_trc_msg =
CAP_TRC_DEF((char*)"ESS_CHGI_Gateway_characteristics_msg",
		(char*)"C35,C8,C20");

static CAP_TRC_trace trace = CAP_TRC_DEF( (char*)"SRMForwarder", (char*)"C");
*/

// Record structure in PDB map:
static const char *const ESERCF_info             = "MGW_info";
static const char *const ESERCF_info_server_def  = "MGW_info_server_def";
static const char *const ESERCF_info_time_def    = "MGW_info_time_def";
static const char *const ESERCF_info_retries_def = "MGW_info_retries_def";
static const char *const SERVER_MAP              = "MGW_Gateway_info";
static const char *const ES_NAME                 = "ES_name";
static const char *const ES_TYPE                 = "ES_type";
static const char *const NOF_RETRIES             = "nof_retries";
static const char *const TIME_BETW_RETRIES       = "time_betw_retries";
static const char *const SERV_NAME               = "serv_name";
static const char *const TEXT1                   = "text1";
static const char *const TEXT2                   = "text2";
static const int         NO_OF_ELEMENTS          = 7;
static const int         ES_NAME_NO              = 0;
static const int         ES_TYPE_NO              = 1;
static const int         NOF_RETRIES_NO          = 2;
static const int         TIME_BETW_RETRIES_NO    = 3;
static const int         SERV_NAME_NO            = 4;
static const int         TEXT1_NO                = 5;
static const int         TEXT2_NO                = 6;
const char       *tmp_strings[] = {"ES_name",
                                   "ES_type",
                                   "nof_retries",
                                   "time_betw_retries",
                                   "serv_name",
                                   "text1",
                                   "text2"};
static const char *const NE                      = "NE";
static const char *const OS                      = "OS";


//*****************************************************************************
// Methods for class ESS_CHGI_Gateway_characteristics.
//*****************************************************************************

ESS_CHGI_Gateway_characteristics::
ESS_CHGI_Gateway_characteristics(int retr,
				 int time,
				 RWCString server,
				 RWCString text1_param,
				 RWCString text2_param)
{
    // Trace the entering of the method.
	//TORF-241666
   /* if (/CAP_TRC_ON(ESS_CHGI_Gateway_characteristics_trc_msg))
        CAP_TRC_event(&ESS_CHGI_Gateway_characteristics_trc_msg,
                      "ESS_CHGI_Gateway_characteristics",
		      ESS_CHGI_TRC_IN, "Enter method");*/

    nof_retries = retr;
    time_betw_retries = time;
    server_name = server;
  /*   if (server != 0)
    {
        server_name = new char [strlen(server)+1];
	strcpy (server_name, server);
    }
    else
    server_name = 0; */

    text1 = text1_param;
/*     if (text1_param != 0)
    {
	text1 = new char [strlen(text1_param)+1];
	strcpy (text1, text1_param);
    }
    else
	text1 = 0; */

    text2 = text2_param;
/*     if (text2_param != 0)
    {
	text2 = new char [strlen(text2_param)+1];
	strcpy (text2, text2_param);
    }
    else
	text2 = 0; */

    // Trace the return of the method.
   /* if (CAP_TRC_ON(ESS_CHGI_Gateway_characteristics_trc_msg))
        CAP_TRC_event(&ESS_CHGI_Gateway_characteristics_trc_msg,
                      "ESS_CHGI_Gateway_characteristics",
		      ESS_CHGI_TRC_OUT,
		      "Exit method");*/
}

ESS_CHGI_Gateway_characteristics::~ESS_CHGI_Gateway_characteristics()
{
    // Trace the entering of the method.
  /*  if (CAP_TRC_ON(ESS_CHGI_Gateway_characteristics_trc_msg))
        CAP_TRC_event(&ESS_CHGI_Gateway_characteristics_trc_msg,
                      "~ESS_CHGI_Gateway_characteristics",
		      ESS_CHGI_TRC_IN, "Enter method");*/

/*     if (server_name != 0)
    {
	delete [] server_name;
	server_name = 0;
    }
    if (text1 != 0)
    {
	delete [] text1;
	text1 = 0;
    }
    if (text2 != 0)
    {
	delete [] text2;
	text2 = 0;
    } */

    // Trace the entering of the method.
  /*  if (CAP_TRC_ON(ESS_CHGI_Gateway_characteristics_trc_msg))
        CAP_TRC_event(&ESS_CHGI_Gateway_characteristics_trc_msg,
                      "~ESS_CHGI_Gateway_characteristics",
		      ESS_CHGI_TRC_OUT, "Exit method");*/
}

RWCString ESS_CHGI_Gateway_characteristics::Get_server_name() const
{
    RWCString name;

    // Trace the entering of the method.
 /*   if (CAP_TRC_ON(ESS_CHGI_Gateway_characteristics_trc_msg))
	CAP_TRC_event(&ESS_CHGI_Gateway_characteristics_trc_msg,
		      "Get_server_name", ESS_CHGI_TRC_IN, "Enter method");*/

    name = server_name;
/*     if (server_name != 0)
    {
	name = new char[strlen(server_name)+1];
	if (name != 0)
	    strcpy(name,server_name);
    } */

    // Trace the return of the method.
   /* if (CAP_TRC_ON(ESS_CHGI_Gateway_characteristics_trc_str))
	CAP_TRC_event(&ESS_CHGI_Gateway_characteristics_trc_str,
		      "Get_server_name", ESS_CHGI_TRC_OUT,
		      ESS_CHGI_TRC_RETURN, name.data());*/

    return name;
}

//******************************************************************************
// Methods for class ESS_CHGI_Gateway_info.
//******************************************************************************

ESS_CHGI_Gateway_info::ESS_CHGI_Gateway_info()
: current_ES(0), err_number(0), err_str()
{
    // Trace the entering of the method.
  /*  if (CAP_TRC_ON(ESS_CHGI_Gateway_info_trc_msg))
        CAP_TRC_event(&ESS_CHGI_Gateway_info_trc_msg,
                      "ESS_CHGI_Gateway_info", ESS_CHGI_TRC_IN, "Enter method");

    // Trace the return of the method.
    if (CAP_TRC_ON(ESS_CHGI_Gateway_info_trc_msg))
        CAP_TRC_event(&ESS_CHGI_Gateway_info_trc_msg,
                      "ESS_CHGI_Gateway_info", ESS_CHGI_TRC_OUT,
		      "Exit method");*/
}

ESS_CHGI_Gateway_info::~ESS_CHGI_Gateway_info()
{
   /*if (CAP_TRC_ON(ESS_CHGI_Gateway_info_trc_msg))
        CAP_TRC_event(&ESS_CHGI_Gateway_info_trc_msg,
                      "~ESS_CHGI_Gateway_info", ESS_CHGI_TRC_IN,
		      "Enter method");
*/
    if (current_ES != 0)
    {
      delete current_ES;
      current_ES = 0;
    }

/*     if (err_str)
	delete [] err_str; */

    // Trace the return of the method.
  /*  if (CAP_TRC_ON(ESS_CHGI_Gateway_info_trc_msg))
        CAP_TRC_event(&ESS_CHGI_Gateway_info_trc_msg,
                      "~ESS_CHGI_Gateway_info", ESS_CHGI_TRC_OUT,
		      "Exit method");*/
}
/*
ESS_CHGI_Gateway_characteristics * ESS_CHGI_Gateway_info
::Get_server_info(const RWCString ES_name)
{
   CAP_PDB pdb;
   CAP_PDB_record *tmp_rec = 0;
   CAP_PDB_list *server_list = 0;

    int found = 0,               // Set to 1 when matching record is found.
	is_error = 0,            // 1 if internal error.
	retr,
	time,
	pdb_error;

    RWCString ES_map_name;
    RWCString servname;
    RWCString text1;
    RWCString text2;
    RWCString pdb_error_str;

    CAP_PDB_int  *pdb_retr = 0,
	*pdb_time = 0;

   CAP_PDB_char *pdb_string = 0;

    // Trace the entering of the method.
    if (CAP_TRC_ON(ESS_CHGI_Gateway_info_trc_msg))
        CAP_TRC_event(&ESS_CHGI_Gateway_info_trc_msg,
                      "Get_server_info", ESS_CHGI_TRC_IN, "Enter method");

    if (current_ES != 0)
	delete current_ES;
    current_ES = NULL;

    if  ((server_list = (CAP_PDB_list *)pdb.get(SERVER_MAP, ESERCF_info)) == 0)
    {
	pdb_error = pdb.get_error();
	pdb_error_str = pdb.get_error_text(pdb_error);
	err_number = NLSSEVEREPDBERROR;
	is_error = 1;
	if (err_str)
	    delete [] err_str;
	err_str = new char[strlen(pdb_error_str) + 1];
	strcpy(err_str, pdb_error_str);
	err_str = pdb_error_str;
	if (pdb_error_str != 0)
	    delete [] pdb_error_str;
    }
    else
    {
	if (server_list->get_type() != CAP_PDB_TYPE_LIST)
	{
	    err_number = NLSIRCPDBTYPEERROR;
	    is_error = 1;
	}
	else
	{
	    while (!found &&
		   (tmp_rec = (CAP_PDB_record*) server_list->get()) != 0 &&
		   !is_error)
	    {
		if (tmp_rec->get_type() != CAP_PDB_TYPE_RECORD)
		{
		    err_number = NLSIRCPDBTYPEERROR;
		    is_error = 1;
		}
		else if (Check_PDB_record(*tmp_rec) == -1)
		{
		    // err_number set by method above.
		    is_error = 1;
		}
		if (!is_error &&
		    (pdb_string = (CAP_PDB_char *)tmp_rec->
		     get(tmp_strings[ES_NAME_NO])) != 0)
		{
		    ES_map_name = pdb_string->get_string();
		    delete pdb_string;
                    // Match is found; read parameters from map.
		    if (strcmp(ES_name, ES_map_name) == 0)
		    if (ES_name == ES_map_name)
		    {
			found = 1;
			if ((pdb_retr = (CAP_PDB_int *)tmp_rec->
			     get(tmp_strings[NOF_RETRIES_NO])) != 0)
			{
			    if (pdb_retr->get(retr) == -1)
			    {
				// Get default.
				if (pdb.get(SERVER_MAP,
					    ESERCF_info_retries_def,
					    retr) == -1)
				{
				    err_number = NLSIRCPDBFIELDERROR;
				    is_error = 1;
				}
			    }
			    delete pdb_retr;
			}

			if ((pdb_time = (CAP_PDB_int *)tmp_rec->
			     get(tmp_strings[TIME_BETW_RETRIES_NO])) != 0)
			{
			    if (pdb_time->get(time) == -1)
			    {
				if (pdb.get(SERVER_MAP,
					    ESERCF_info_time_def,time) == -1)
				{
				    err_number = NLSIRCPDBFIELDERROR;
				    is_error = 1;
				}
			    }
			    delete pdb_time;
			}

			if ((pdb_string = (CAP_PDB_char *)tmp_rec->
			     get(tmp_strings[SERV_NAME_NO])) != 0)
			{
			    if (strcmp(servname = pdb_string->get_string(),
				       "") == 0)
			    {
				delete pdb_string;
				if ((pdb_string = (CAP_PDB_char *)pdb.get
				     (SERVER_MAP, ESERCF_info_server_def)) == 0)
				{
				    err_number = NLSIRCPDBFIELDERROR;
				    is_error = 1;
				}
			    }
			    if (!is_error)
			    {
				delete [] servname;
				servname = pdb_string->get_string();
				delete pdb_string;
				pdb_string = 0;
			    }
			}

			if ((pdb_string = (CAP_PDB_char *)tmp_rec->
			     get(tmp_strings[TEXT1_NO])) != 0)
			{
			    text1 = pdb_string->get_string();
			    delete pdb_string;
			}

			if ((pdb_string = (CAP_PDB_char *)tmp_rec->
			     get(tmp_strings[TEXT2_NO])) != 0)
			{
			    text2 = pdb_string->get_string();
			    delete pdb_string;
			}

			// Trace the content of the record found in PDB map.
		if (CAP_TRC_ON(ESS_CHGI_Gateway_info_trc_cont))
			    CAP_TRC_event(&ESS_CHGI_Gateway_info_trc_cont,
					  "Get_server_info",
					  ESS_CHGI_TRC_FLOW, "ES",
					  ES_map_name.data(),
                                          "Server", servname.data(),
					  "Retries", retr, "Time", time);

			if (!is_error)
			    current_ES =
				new ESS_CHGI_Gateway_characteristics(retr,
								     time,
								     servname,
								     text1,
								     text2);
		    }
		    delete [] ES_map_name;
		}
		if (tmp_rec != 0)
		    delete tmp_rec;
	    }
	}
    }

    Deallocate memory.
    if (server_list != 0)
        delete server_list;
    if (servname != 0)
	delete [] servname;
    if (text1 != 0)
	delete [] text1;
    if (text2 != 0)
	delete [] text2;

    // Trace the return of the method.
    if (CAP_TRC_ON(ESS_CHGI_Gateway_info_trc_msg))
        CAP_TRC_event(&ESS_CHGI_Gateway_info_trc_msg,
                      "Get_server_info", ESS_CHGI_TRC_OUT, "Exit method");

    if (found && !is_error)
	return current_ES;
    else
	return 0;
}*/

/*
int ESS_CHGI_Gateway_info::Check_PDB_record(CAP_PDB_record &pdb_rec)
{
    CAP_PDB_atomic *tmp_atomic =0;

    // Trace the entering of the method.
    if (CAP_TRC_ON(ESS_CHGI_Gateway_info_trc_msg))
	CAP_TRC_event(&ESS_CHGI_Gateway_info_trc_msg,
		      "Check_PDB_record", ESS_CHGI_TRC_IN, "Enter method");

    for (int i = 0 ; i < NO_OF_ELEMENTS; i++)
    {
	tmp_atomic = pdb_rec.get(tmp_strings[i]);
	if ( tmp_atomic == 0)
	{
	    // wrong or missing field
	    err_number = NLSIRCPDBFIELDERROR;
	    return -1;
	}
	else
	{
	    if (((i==ES_NAME_NO) &&
		 (tmp_atomic->get_type() != CAP_PDB_TYPE_STRING)) ||
		((i==ES_TYPE_NO) &&
		 (tmp_atomic->get_type() != CAP_PDB_TYPE_STRING)) ||
		((i==NOF_RETRIES_NO) &&
		 (tmp_atomic->get_type() != CAP_PDB_TYPE_INT))    ||
		((i==TIME_BETW_RETRIES_NO) &&
		 (tmp_atomic->get_type() != CAP_PDB_TYPE_INT))    ||
		((i==SERV_NAME_NO) &&
		 (tmp_atomic->get_type() != CAP_PDB_TYPE_STRING)) ||
		((i==TEXT1_NO) &&
		 (tmp_atomic->get_type() != CAP_PDB_TYPE_STRING)) ||
		((i==TEXT2_NO) &&
		 (tmp_atomic->get_type() != CAP_PDB_TYPE_STRING)))
	    {
		err_number = NLSIRCPDBTYPEERROR;
		if (tmp_atomic != 0)
		    delete tmp_atomic;
		return -1;
	    }
	}
	pdb_rec.reset();
	if (tmp_atomic != 0)
	    delete tmp_atomic;
    }
    // Trace the return of the method.
    if (CAP_TRC_ON(ESS_CHGI_Gateway_info_trc_msg))
	CAP_TRC_event(&ESS_CHGI_Gateway_info_trc_msg,
		      "Check_PDB_record", ESS_CHGI_TRC_OUT, "Exit method");
    return 0;
}
*/
SRMForwarder::SRMForwarder()
: sc(0), s_name()
{
    //TRACE_IN (trace, SRMForwarder, "");

    server_info = new ESS_CHGI_Gateway_info;

    //TRACE_OUT (trace, SRMForwarder, "");
}

SRMForwarder::~SRMForwarder()
{
/*    delete server_info;
   delete [] s_name; */
}

RWCString SRMForwarder::getServerName(const RWCString& os)
{
    //TRACE_IN(trace, getServerName, os);

    s_name = "";
    sc = server_info->Get_server_info(os);

    if (sc)
    {
	const char* tmpStr = sc->Get_server_name();
	if(tmpStr != NULL)
	    s_name = tmpStr;
    }
    else
    {
        //TRACE_FLOW (trace, getServerName, "server_info->Get_server_info Failed!");
        //TRACE_FLOW (trace, SRMForwarder, "Error string: " << server_info->getErrStr());
        //TRACE_FLOW (trace, SRMForwarder, "Error number: " << server_info->getErrNumber());
    }

    //TRACE_OUT(trace, getServerName, "");

    return s_name;
}
