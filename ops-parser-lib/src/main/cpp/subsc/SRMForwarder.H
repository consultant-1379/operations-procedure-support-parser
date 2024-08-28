// RCS revision handling
// $Id: SRMForwarder.H,v 24.1 1996/01/17 16:23:18 ehscama Exp $

//**********************************************************************
// 
// .NAME SRMForwarder
// .INCLUDE SRMForwarder.H

// .COPYRIGHT
//      COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1994
//
//      The Copyright to the computer program(s) herein is the
//      property of Ericsson Hewlett-Packard Telecommunications AB,
//      Sweden.  The program(s) may be used and/or copied with the
//      written permission from Ericsson Hewlett-Packard
//      Telecommunications AB or in accordance with the terms and
//      conditions stipulated in the agreement/contract under which
//      the program(s) have been supplied.

// .DESCRIPTION 
//	This class retrieves information from a PDB map own by ESS-ERCF.
//	The SRMForwarder class provides the Gateway server (ercf) name which 
//	handles an operation system. That is the process which forwards
//	spontaneous reports to an external OS. Used when setting up a subscription
//	receiver.

// .SECTION DOCUMENT NUMBER
// 	190 89-CAA 134 1064

// AUTHOR
//	1993-09-24 JV/PBU Dan Andersson

// REVISION
//	TB53_OZ
//	1995-11-28
// CHANGES

//
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
//	A		1993-09-24	ehsdana         First revision


// SEE ALSO

//****************************************************************************

#ifndef SRMFORWARDER_H
#define SRMFORWARDER_H

#include <rw/cstring.h>
/*TORF-241666
#include <cap_pdb.H>
#include <cap_pdb_parameter.H>*/


class ESS_CHGI_Gateway_characteristics
{
    friend class ESS_CHGI_Gateway_info;
    // Description:
    //    In order for the ESS_CHGI_Gateway_info class to have access
    //    to the constructor of this class.


  public:
    RWCString Get_server_name()const;
    // Description:
    //    Returns the name of the server associated with the specified
    //    ES (NE) name.

  private:
    int nof_retries;
    int time_betw_retries;
    RWCString server_name;
    RWCString text1;
    RWCString text2;

    ESS_CHGI_Gateway_characteristics(int retr, int time, RWCString serv_name, 
                                     RWCString text1_param, 
				     RWCString text2_param);
    // Description:
    //    Constructor. Not available outside this function block.

    virtual ~ESS_CHGI_Gateway_characteristics();
    // Description:
    //    Destructor.

};

class ESS_CHGI_Gateway_info
{
    // Relationships:
    //      Inherits:           None.
    //      Contains:
    //      Uses:               None.
    //
    //      Keys:
    //      The following attributes must receive values
    //      in order to uniquely identify one instance of
    //      the class: 
    //                  NA.

public:
    ESS_CHGI_Gateway_info();
    // Description:
    //    The constructor of the class.
    //     
    // Parameters:
    //
    // Calls:
    //
    //
    // Additional information:
    //  

    virtual ~ESS_CHGI_Gateway_info();
    // Description:
    //  The destructor of the class.
    //
    // Parameters: 
    //  None.
    //
    // Return values:   
    //  None.
    //
    // Calls:
    //  None.

    ESS_CHGI_Gateway_characteristics *Get_server_info(const RWCString name);
    // Description:
    //    Returns a pointer to an ESS_CHGI_Gateway_characteristics object
    //    containing information about the requested ES.
    //    Updates the current_ES pointer.
    //
    //    If the current_ES pointer already points to an object, this
    //    will be deleted before creating a new object.

    int getErrNumber()
    {
	return err_number;
    }

    const RWCString getErrStr()
    {
	return err_str;
    }

private:
    ESS_CHGI_Gateway_characteristics *current_ES; 
    // Description:
    //     Pointer to current ESS_CHGI_Gateway_characteristics object.

   // int Check_PDB_record (CAP_PDB_record &pdb_record);
    // Description:
    //    Returns 0 if the PDB record is OK, -1 otherwise. 

    int err_number;
    RWCString err_str;
};

class SRMForwarder
{
public:
    SRMForwarder();
    // Description:
    // Constructor function.

    virtual ~SRMForwarder();
    // Description:
    // Destructor function.
    
    RWCString getServerName(const RWCString& os);
    // Description:
    // Returns the server name associated with the specified OS or
    // 0 if not found or error.

    int getErrNumber()
    // Description:
    // Returns a nls value if an error was encountered while reading
    // the PDB map.
    {
	return server_info->getErrNumber();
    }

    RWCString getErrStr()
    // Description:
    // Returns a string set when a severe PDB error has occurred.
    {
	return server_info->getErrStr();
    }

private:
    ESS_CHGI_Gateway_info * server_info;
    ESS_CHGI_Gateway_characteristics * sc;
    RWCString s_name; // Retrieved server name
};
#endif