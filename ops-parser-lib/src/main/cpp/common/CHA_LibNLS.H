// RCS handling
// $Id: CHA_LibNLS.H,v 24.1 1996/05/13 09:21:34 emermge Exp $

//**********************************************************************
// 
// .NAME    CHA_LibNLS.H
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_LibNLS.H

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
//      This file contains NLS constants (indices) referring to texts
//      in the NLS catalog.

// DOCUMENT NO
//      190 89-CAA 134 1515

// AUTHOR 
//      1994-02-18 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_LibNLS.H,v $
//      Revision 24.1  1996/05/13 09:21:34  emermge
//      Add the NLS_CMD_NOAUTH code for chlcmd.
//
//      Revision 24.0  1995/11/28 16:54:50  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:40:55  17:40:55  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:43:43  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:39:31  09:39:31  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:32:21  08:32:21  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.1  95/04/24  11:07:51  11:07:51  ehsgrap (Jan Grape (9 9073) VK/EHS/PXE)
//      Added message for break delayed not supported.
//      
//      Revision 19.0  1995/04/13  10:51:37  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:03:52  20:03:52  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:02:17  14:02:17  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  12:57:46  12:57:46  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  14:59:29  14:59:29  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:32:43  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:01:50  14:01:50  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:12:54  16:12:54  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:44:32  cmcha
//      Made release PREIT, N L�nninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:01:22  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:28:10  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:47:36  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:21:58  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:49:13  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:43:35  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:36:25  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.1  1994/07/18  11:40:21  ehsgrap
//      Added some messges for chlcmdf.
//
//      Revision 3.0  1994/06/23  07:50:45  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:03:37  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.14  1994/06/10  16:54:48  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.13  1994/06/08  13:22:29  ehsgrap
//      Added NLS codes for chlscmdf (CHA_SubProcSupervisor)
//
//      Revision 1.12  1994/05/10  12:37:43  ehsgrap
//      Corrected numbering.
//
//      Revision 1.11  1994/05/10  12:18:18  ehsgrap
//      Added some codes for del subscr. in chlcmd.
//
//      Revision 1.10  1994/05/03  11:01:44  xkknicl
//      More chlroute messages
//
//      Revision 1.9  1994/04/29  14:46:30  xkknicl
//      Addded more NLS codes for Command Files
//
//      Revision 1.8  1994/04/29  08:19:06  ehsgrap
//      chlroute messages
//
//      Revision 1.7  1994/04/26  14:48:39  ehsgrap
//      Added some nls codes for chlroute.
//
//      Revision 1.6  1994/04/21  10:15:04  xkknicl
//      Added NLS codes for chlcmdf
//
//      Revision 1.5  1994/04/12  16:24:25  ehsgrap
//      Belive it or not! More constans for chlcmd.
//
//      Revision 1.4  1994/04/06  10:28:39  ehsgrap
//      Even more constants for chlcmd
//
//      Revision 1.3  1994/03/23  13:24:37  ehsgrap
//      Added some constants for chlcmd
//
//      Revision 1.2  1994/03/22  14:16:55  ehsgrap
//      Added some NLS codes for chlcmd.
//
//      Revision 1.1  1994/02/18  12:48:41  ehsgrap
//      Initial version.
//
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION
//	TB53_OZ 1995-11-28      J Grape (EHSGRAP)       RCS rev 24.0
//	XM2S1   1995-09-07      ehscama                 RCS rev 23.0
//	EC2_OZ  1995-08-01      Jan Sandquist (EHSJAASA)RCS rev 22.0
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
//	PREIT   1995-01-18      N L�nninge (XKKNICL)    RCS rev 11.0
//	TB2     1994-12-22      J Grape (EHSGRAP)       RCS rev 10.0
//	E       1994-10-24      ehscama                 RCS rev 9.0
//	D       1994-10-05      EHSCAMA                 RCS rev 8.0
//	R1C     1994-09-22      J Grape (EHSGRAP)       RCS rev 7.0
//	R1B     1994-08-30      J Grape (EHSGRAP)       RCS rev 6.0
//	R1A     1994-08-16      J Grape (EHSGRAP)       RCS rev 5.0
//	P1C     1994-07-18      J Grape (EHSGRAP)       RCS rev 4.0
//	P1B     1994-06-23      J Grape (EHSGRAP)       RCS rev 3.0
//	P1A     1994-06-12      J Grape (EHSGRAP)       RCS rev 2.0

// .SEE ALSO 
//      CHA_NLSCatalog

//**********************************************************************

#ifndef CHA_LIBNLS_H
#define CHA_LIBNLS_H


// Declare all NLS indices as "const int". Use numbers from 10000 and up.
// For every CAA (code module) begin on a new 100.

// chlcmd
const int NLS_COMMAND_NOAUTH		= 10000;
const int NLS_COMMAND_REJECTED		= 10001;
const int NLS_CONFIRMFAILED		= 10002;
const int NLS_DEVID_CHANGE_LATER	= 10003;
const int NLS_IMMREC_FAILED		= 10004;
const int NLS_IMMREC_TIMEOUT		= 10005;
const int NLS_IMMRESP_INTR		= 10006;
const int NLS_IMMRESP_INTR_FAILED	= 10007;
const int NLS_IMMRESP_NOTRECEIVING	= 10008;
const int NLS_SENDFAILED		= 10009;
const int NLS_SENDFAILED_NOCONNECTION	= 10010;
const int NLS_ES_LINKFAIL		= 10011;
const int NLS_ES_TIMEOUT		= 10012;
const int NLS_ES_DISCON			= 10013;
const int NLS_ES_CON			= 10014;
const int NLS_ES_RECON			= 10015;
const int NLS_ES_FAILED_DISCON		= 10016;
const int NLS_ES_NOREACH		= 10017;
const int NLS_ES_UNKNOWN		= 10018;
const int NLS_ES_IS_EXCLUSIVE		= 10019;
const int NLS_ES_NOAUTH			= 10020;
const int NLS_ES_FAILED_CON		= 10021;
const int NLS_DELREC_FAILED		= 10022;
const int NLS_DELREC_TIMEOUT		= 10023;
const int NLS_DELRESP_INTR_FAILED	= 10024;
const int NLS_DELRESP_NOTRECEIVING	= 10025;
const int NLS_DELSUB_PRLG_FAIL		= 10026;
const int NLS_DELSUB_DMTFAIL		= 10027;
const int NLS_F_DELSUB_FAILED		= 10028;
const int NLS_M_DELSUB_FAILED		= 10029;
const int NLS_P_DELSUB_FAILED		= 10030;
const int NLS_DELSUB_FAILED		= 10031;
const int NLS_DELRESP_NOTSUPPORTED	= 10032;
const int NLS_CMD_NOAUTH		= 10033;
const int NLS_ES_DISCON_CSL     = 10034;
const int SUCCESS     = 10035;

// chlcmdf
const int NLS_CMDFILE_STARTMESSAGE_1    = 10100;
const int NLS_CMDFILE_STARTMESSAGE_2    = 10101;
const int NLS_CMDFILE_NOT_STARTED       = 10102;
const int NLS_CMDFILE_SEND_FAILED       = 10103;
const int NLS_CMDFILE_NOIMMBREAK	= 10104;
const int NLS_CMDFILE_NODELBREAK	= 10105;

// chlroute
const int NLS_ROUTE_UNABLE		= 10200;
const int NLS_ROUTE_NORCVR		= 10201;
const int NLS_UNROUTE_UNABLE		= 10203;
const int NLS_MTARGET_FAILED		= 10204;
const int NLS_FTARGET_FAILED            = 10205;
const int NLS_PTARGET_FAILED            = 10206;

// chlscmdf
const int NLS_SPS_NOPIPE		= 10300;
const int NLS_SPS_NOFORK		= 10301;
const int NLS_SPS_NONONBLK		= 10302;
const int NLS_SPS_READERR		= 10303;
const int NLS_SPS_WRITEERR		= 10304;

#endif
