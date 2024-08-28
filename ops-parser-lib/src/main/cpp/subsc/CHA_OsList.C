// RCS handling
// $Id: CHA_OsList.C,v 24.0 1995/11/28 17:00:54 ehsgrap Rel $

//**********************************************************************

// COPYRIGHT
//      COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1994
//
//      The Copyright to the computer program(s) herein is the
//      property of Ericsson Hewlett-Packard Telecommunications AB,
//      Sweden.  The program(s) may be used and/or copied with the
//      written permission from Ericsson Hewlett-Packard
//      Telecommunications AB or in accordance with the terms and
//      conditions stipulated in the agreement/contract under which
//      the program(s) have been supplied.

// DOCUMENT NO
//      190 89-CAA 134 1515

// AUTHOR
//      1994-08-11 by EHS/Marie Moschna (qhsmosc@ehs.ericsson.se)

// REVISION
//	TB53_OZ
//	1995-11-28
//      RCS revision history
//      $Log: CHA_OsList.C,v $
//      Revision 24.0  1995/11/28 17:00:54  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//       Revision 23.0  95/09/07  17:50:01  17:50:01  ehscama (Martin Carlsson VK/EHS/VE)
//       Made release XM2S1, ehscama.
//
//       Revision 22.0  1995/08/01  20:50:46  cmcha
//       Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//       Revision 21.0  95/06/29  09:48:21  09:48:21  cmcha (*CHA conf. and dev. EHS/PXE)
//       Made release EC1_OZ, J Grape (EHSGRAP).
//
//       Revision 20.0  95/06/08  08:39:30  08:39:30  cmcha (*CHA conf. and dev. EHS/PXE)
//       Made release TB5_2_OZ, J Grape (ehsgrap).
//
//       Revision 19.1  95/04/24  13:04:30  13:04:30  ehsgrap (Jan Grape (9 9073) VK/EHS/PXE)
//       *** empty log message ***
//
//       Revision 19.0  1995/04/13  10:58:52  cmcha
//       Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//       Revision 18.1  95/04/10  14:12:25  14:12:25  ehsgrap (Jan Grape (9 9073) VK/EHS/PXE)
//       Removed update call from costructor.
//
//       Revision 18.0  1995/03/17  20:11:31  cmcha
//       Made release TB51_OZ, ehscama.
//
//       Revision 17.0  95/03/16  14:13:46  14:13:46  cmcha (*CHA conf. and dev. EHS/PXE)
//       Made release TB5_OZ, ehscama.
//
//       Revision 16.0  95/03/10  13:05:47  13:05:47  cmcha (*CHA conf. and dev. EHS/PXE)
//       Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//       Revision 15.0  95/03/09  15:12:56  15:12:56  cmcha (*CHA conf. and dev. EHS/PXE)
//       Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//       Revision 14.0  1995/02/25  16:39:14  cmcha
//       Made release TB4_OZ, J Grape (EHSGRAP).
//
//       Revision 13.5  95/02/15  14:12:47  14:12:47  cmcha (*CHA conf. and dev. EHS/PXE)
//       Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//       Revision 12.0  95/02/06  16:23:33  16:23:33  cmcha (*CHA conf. and dev. EHS/PXE)
//       Made release TB3, J Grape (EHSGRAP).
//
//       Revision 11.0  1995/01/18  14:54:56  cmcha
//       Made release PREIT, N L\ufffdnninge (XKKNICL).
//
//       Revision 10.1  1995/01/05  07:29:15  ehsgrap
//       Use of CHA_UserInfo instead of getpwuid(getuid())
//
//       Revision 10.0  1994/12/22  09:09:00  cmcha
//       Made release TB2, J Grape (EHSGRAP).
//
//       Revision 9.1  1994/12/08  10:27:34  ehsgrap
//       Replaced OK with OKAY
//
//       Revision 9.0  1994/10/24  21:35:41  cmcha
//       Made release E, ehscama.
//
//       Revision 8.0  1994/10/05  08:57:03  cmcha
//       Made release D, EHSCAMA.
//
//       Revision 7.0  1994/09/22  13:28:41  cmcha
//       Made release R1C, J Grape (EHSGRAP).
//
//       Revision 6.0  1994/08/30  17:55:44  cmcha
//       Made release R1B, J Grape (EHSGRAP).
//
//       Revision 1.1  1994/08/26  10:12:40  qhsmosc
//       First version
//

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

// SEE ALSO
// 	CHA_EsList

//**********************************************************************


#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_LibNLS.H>
#include <CHA_UserInfo.H>
//TORF-241666
/* #include <eac_esi_auth.H>
#include <sysent.h> */
#include <CHA_OsList.H>
#include <SRMForwarder.H>

//static CAP_TRC_trace trace = CAP_TRC_DEF( (char*)"CHA_OsList", (char*)"C");

//**********************************************************************


CHA_OsList::CHA_OsList()
{
    //TRACE_IN(trace, CHA_OsList, "");

    // Empty
}


//**********************************************************************


CHA_OsList::~CHA_OsList()
{
    // Empty
}


//**********************************************************************


CHA_EsList::ReturnCode CHA_OsList::update()
{
    //TRACE_IN(trace, update, "");

    CHA_EsList::ReturnCode returnValue = CHA_OsList::OKAY;
    CHA_UserInfo userInfo;
    //EAC_ESI_Auth_Info authInfo;
    SRMForwarder forwarder;


    myEsList.clear();
/*
    const char* esName =
	authInfo.Get_first_auth_ES_name(userInfo.loginName().data(),
					CR_CONNECTION);

    if (esName == 0)
    {
	switch (authInfo.Get_error())
	{
	case EAC_ESI_OK:
	    returnValue = CHA_EsList::NOT_AUTHORIZED;
	    break;
	case EAC_ESI_PDB_NO_MEMORY:
	case EAC_ESI_PDB_NOT_EXIST:
	case EAC_ESI_PDB_ERROR:
	case EAC_ESI_MEMORY_ERR:
	case EAC_ESI_MAP_PAR_NO_VAL:
	case EAC_ESI_PDB_NO_MAP:
	case EAC_ESI_NULL_POINTER:
	default:
	    returnValue = CHA_EsList::NO_CONTACT_AUTHDB;
	    break;
	}
    }
    else
    {
	while(esName != 0)
	{
	    // Check that name exists in ESS_CHGI_Gateway

	    RWCString proc;
	    proc = forwarder.getServerName(esName);

            //TRACE_FLOW(trace, esName, esName);
            //TRACE_FLOW(trace, foundProc, proc);

	    if (!proc.isNull())
	    {
		// Name does exist in ESS_CHGI_Gateway

                // Check that the name is not inserted already
		if (!myEsList.contains(esName))
		    myEsList.insert(esName);
	    }

	    esName = authInfo.Get_next_auth_ES_name();
	}
    }

    changed();

    //TRACE_OUT(trace, update, returnValue);

    return returnValue;*/
}
