// RCS revision handling
// $Id: OZT_NLS.H,v 21.1 1996/10/08 17:29:31 ememjga Exp $

//*****************************************************************************
// 
// .NAME
//  	OZT_NLS - NLS message numbers
// .LIBRARY 3C++
// .PAGENAME <CLASSNAME>
// .HEADER  <SSN><API>/<FBN> 
// .LEFT_FOOTER Ericsson HP
// .INCLUDE <filename>

// .COPYRIGHT
//	COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB, Sweden 1994.
// 	All rights reserved.
//
//	The Copyright to the computer program(s) herein is the
//	property of Ericsson Hewlett-Packard Telecommunications AB,
//	Sweden. The program(s) may be used and/or copied only with the
//	written permission from Ericsson Hewlett-Packard
//	Telecommunications AB or in accordance with the terms and
//	conditions stipulated in the agreement/contract under which
//	the program(s) have been supplied.

// .DESCRIPTION 
// 	NLS message numbers

// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	%EriDoc_no:%

// AUTHOR 
// 	1994/10/06 by ETL/XN/DSN etlnei

// .REVISION <for public API>
//	<Revision state>
//	<Revision date>	  	

// .REVISION <for internal header files>
//	%EriDoc_rev:%
//	%EriDoc_date:%  	

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_NLS.H,v $
// 	Revision 21.1  1996/10/08 17:29:31  ememjga
// 	Included the constant NLSVIEWRESP, AD48154.
//
// 	Revision 21.0  1996/08/23 12:46:42  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 08:00:55  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.1  1996/04/10 15:45:10  emejerf
// 	Fixed HA11662 and 11668.
// 	Added a few constants to deal with the INCLUDE_NOT_EXECUTED
// 	return value.
//
// 	Revision 19.0  1996/03/19 07:23:57  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.1  1996/03/11 13:06:32  ehsjasa
// 	Changed PROTOTYPE to OZT_PROTOTYPE.
//
// 	Revision 18.0  1996/03/01 12:25:09  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:06:48  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:59:41  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:04:50  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:20:40  17:20:40  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.5  1995/11/16 16:33:50  epanyc
// 	A few prototype related constants defined
//
//      Revision 13.4  1995/11/09  13:16:25  epanyc
//      new message added
//
//      Revision 13.3  1995/11/03  14:38:27  epanyc
//      new messages added
//
//      Revision 13.2  1995/10/31  08:23:17  epanyc
//      position choice messages added
//
//      Revision 13.1  1995/10/17  18:56:17  ehsjasa
//      Added NLSELBTASKID.
//
// 	Revision 13.0  1995/10/07 12:03:59  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:13:03  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:27:40  09:27:40  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:06:19  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.0  95/06/29  14:41:32  14:41:32  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC2_OZ, J Grape (EHSGRAP).
//      
//      Revision 8.0  95/06/07  17:12:56  17:12:56  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//      
//      Revision 7.1  95/05/18  11:07:18  11:07:18  etlnei (Neil Harding VK/EHS/PXE)
//      *** empty log message ***
//      
//      Revision 7.0  1995/04/16  12:19:22  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.1  95/04/04  11:12:57  11:12:57  etlnei (Neil Harding VK/EHS/PXE)
//      checked in for happy test release
//      
//      Revision 6.0  1995/03/17  20:08:27  cmcha
//      Made release TB51_OZ, ehscama.
//
//      Revision 5.0  95/03/16  20:33:41  20:33:41  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 4.3  95/03/10  14:24:59  14:24:59  ehsenan (Lars Enander VK/EHS/PXE)
//      Added OLDT codes
//      
//      Revision 4.2  1995/03/09  09:25:06  etlnei
//      checked in for other people to compile
//
//      Revision 4.1  1995/03/01  12:10:39  etlnei
//      checked in while I go to England
//
//      Revision 4.0  1995/02/23  21:48:08  cmcha
//      Made release TB4, J Grape (EHSGRAP).
//
//      Revision 3.4  95/02/23  08:48:03  08:48:03  epanyc (Nelson Cheng VK/EHS/PXE)
//      NLSSELECTFILE added
//      
//      Revision 3.3  1995/02/21  09:27:21  etlnei
//      Changes made after hearing comments from Telstra
//
//      Revision 3.2  1995/02/10  17:35:41  ehsenan
//      Added OLDT messages
//
//      Revision 3.1  1995/02/10  11:38:26  etlnei
//      more stuff added
//
//      Revision 3.0  1995/02/06  21:01:59  cmcha
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 2.8  95/02/06  15:01:31  15:01:31  etlnei (Neil Harding VK/EHS/PXE)
//      added File does not exist message
//      
//      Revision 2.7  1995/02/03  14:19:36  etlnei
//      second happy test release
//
//      Revision 2.6  1995/01/26  09:55:40  etlnei
//      checked in for Eric to compile
//
//      Revision 2.5  1995/01/16  10:13:25  etlnei
//      added NLS strings for props window
//
//      Revision 2.4  1995/01/09  11:49:21  etlnei
//      part way through adding a starting path
//
//      Revision 2.3  1994/12/21  16:16:23  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 2.0  94/12/21  13:54:59  13:54:59  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//      
//      Revision 1.9  1994/12/16  13:38:52  etlnei
//      added nls messages for InputWin
//
//      Revision 1.8  1994/12/13  11:20:23  etlnei
//      checking in everything because OXT_ESBrowser is new
//
//      Revision 1.7  1994/12/12  11:15:57  etlnei
//      checked in for nelson to compile
//
//      Revision 1.6  1994/12/06  11:39:48  etlnei
//      checked in for Janne to compile
//
//      Revision 1.5  1994/12/02  10:35:25  etlnei
//      version uised for "happy testing"
//
//      Revision 1.4  1994/11/03  10:15:33  etlnei
//      checked in for Janne to compile
//
//      Revision 1.3  94/10/28  11:21:13  11:21:13  etlnei (Neil Harding VK/EHS/PXE)
//      *** empty log message ***
//      
//      Revision 1.2  94/10/07  19:46:43  19:46:43  etlnei (Neil Harding VK/EHS/PXE)
//      corrected errors
//      
//      Revision 1.1  1994/10/06  14:14:52  etlnei
//      Initial revision
//
//
//	RELEASE REVISION HISTORY
//
//	REV NO	DATE		NAME			DESCRIPTION
//	B_POINT 1996-08-23      J Grape (EHSGRAP)       RCS rev 21.0
//	EC8_OZ  1996-07-10      David Terry epa.epadmt  RCS rev 20.0
//	POW_TB611996-03-19      J Sandquist (ehsjasa)   RCS rev 19.0
//	EC7_OZ  1996-03-01      J Sandquist (ehsjasa)   RCS rev 18.0
//	EC6_OZ  1996-01-17      J Sandquist (ehsjasa)   RCS rev 17.0
//	POW_TB411996-01-08      J Sandquist (ehsjasa)   RCS rev 16.0
//	TB53_OZ 1995-11-29      J Grape (EHSGRAP)       RCS rev 15.0
//	POW_TB3 1995-11-20      J Sandquist (EHSJASA)   RCS rev 14.0
//	PRE_XM221995-10-07      J Sandquist (EHSJASA)   RCS rev 13.0
//	EC5_OZ  1995-09-22      J Sandquist (EHSJASA)   RCS rev 12.0
//	EC4_OZ  1995-09-14      J Sandquist (EHSJASA)   RCS rev 11.0
//	EC3_OZ  1995-08-02      J Sandquist (EHSJASA)   RCS rev 10.0
//	EC2_OZ  1995-06-29      J Grape (EHSGRAP)       RCS rev 9.0
//	TB5_2_OZ1995-06-07      J Grape (EHSGRAP)       RCS rev 8.0
//	TB5_1_OZ1995-04-16      J Grape (EHSGRAP)       RCS rev 7.0
//	TB51_OZ 1995-03-17      ehscama                 RCS rev 6.0
//	TB5_OZ  1995-03-16      ehscama                 RCS rev 5.0
//	TB4     1995-02-23      J Grape (EHSGRAP)       RCS rev 4.0
//	TB3     1995-02-06      J Grape (EHSGRAP)       RCS rev 3.0
//	TB2     1994-12-21      J Grape (EHSGRAP)       RCS rev 2.3
//	TB2     1994-12-21      J Grape (EHSGRAP)       RCS rev 2.0
//	<Rev no> 	<Date>		<Name>		<Description>

// .LINKAGE
//	<link information: libraries needed and order>

// .SEE ALSO 
// 	<Related classes, (abstract) baseclasses, friend classes, ...>

//*****************************************************************************


#ifndef OZT_NLS_H 
#define OZT_NLS_H

static const int NLSCDF = 1;
static const int NLSRESP = 2;
static const int NLSBREAKPOINT = 3;
static const int NLSCONNECT = 4;
static const int NLSDEBUGGER = 5;
static const int NLSDISCONNECT = 6;
static const int NLSEDIT = 7;
static const int NLSES = 8;
static const int NLSFILE = 9;
static const int NLSPAUSE = 10;
static const int NLSPROPS = 11;
static const int NLSRUN = 12;
static const int NLSSETPOS = 13;
static const int NLSSTEP = 14;
static const int NLSSTOPDEBUG = 15;
static const int NLSTAG = 16;
static const int NLSVIEW = 17;
static const int NLSMODE = 18;
static const int NLSMESSAGE = 19;
static const int NLSTCONNECTED = 20;
static const int NLSTES = 21;
static const int NLSTFILE = 22;
static const int NLSMICREATEF = 23;
static const int NLSMEDIT = 24;
static const int NLSMDEBUG = 25;
static const int NLSRESPWIN = 26;
static const int NLSMIADDB = 27;
static const int NLSMICLEARB = 28;
static const int NLSMICLEARALLB = 29;
static const int NLSMITOGGLEB = 30;
static const int NLSMIAGAINE = 31;
static const int NLSMICOPYE = 32;
static const int NLSMICUTE = 33;
static const int NLSFIND = 34;
static const int NLSMIPASTEE = 35;
static const int NLSMIUNDOE = 36;
static const int NLSMICLOSEF = 37;
static const int NLSMICLOSEALLF = 38;
static const int NLSMILOADF = 39;
static const int NLSMISAVEF = 40;
static const int NLSMISAVEASF = 41;
static const int NLSMIADDT = 42;
static const int NLSMICLEART = 43;
static const int NLSMICLEARALLT = 44;
static const int NLSMITOGGLET = 45;
static const int NLSMIFILEV = 46;
static const int NLSMIIOWINV = 47;
static const int NLSMIWATCHWINV = 48;
static const int NLSSTOPRESP = 49;
static const int NLSMICURRENTRUN = 50;
static const int NLSMISTARTRUN = 51;
static const int NLSMITAGGEDRUN = 52;
static const int NLSCONTINUE = 53;
static const int NLSVIEWLISTP = 54;
static const int NLSAPPLY = 55;
static const int NLSFILESELECTION = 56;
static const int NLSVIEWPOPUP = 57;
static const int NLSMIONLYSETPOSS = 58;
static const int NLSMIRUNSETPOSS = 59;
static const int NLSMISAVEALLF = 60;
static const int NLSQUITNOTICE = 61;
static const int NLSCANCELNOQUIT = 62;
static const int NLSDISCARDQUIT = 63;
static const int NLSDISCARDEDITS = 64;
static const int NLSSAVEEDITS = 65;
static const int NLSRESETPOS = 66;
static const int NLSCANCEL = 67;
static const int NLSHASBEEN = 68;
static const int NLSCONTAINSPOS = 69;
static const int NLSWATCHWIN = 70;
static const int NLSVARCONTENTS = 71;
static const int NLSADD = 72;
static const int NLSREMOVE = 73;
static const int NLSVARNAME = 74;
static const int NLSLOADFILE = 75;
static const int NLSLOAD = 76;
static const int NLSTDIRECTORY = 77;
static const int NLSGOUPONE = 78;
static const int NLSSAVEFILE = 79;
static const int NLSSAVE = 80;
static const int NLSEXTERNALSYSTEM = 81;
static const int NLSINSERT = 82;
static const int NLSEXT = 83;
static const int NLSCANTCONNECT = 84;
static const int NLSENTER = 85;
static const int NLSINKEYTITLE = 86;
static const int NLSINPUTTITLE = 87;
static const int NLSINKEYMESSAGE = 88;
static const int NLSINPUTMESSAGE = 89;
static const int NLSPROPSTITLE = 90;
static const int NLSRESET = 91;
static const int NLSSET = 92;
static const int NLSWARNINGS = 93;
static const int NLSALWAYS = 94;
static const int NLSNEVER = 95;
static const int NLSNOTUPTODATE = 96;
static const int NLSLOADTHENCONT = 97;
static const int NLSPRINTWINTITLE = 98;
static const int NLSFILENAME = 99;
static const int NLSPRINTER = 100;
static const int NLSPRINTAPPLY = 101;
static const int NLSMIPRINTF = 102;
static const int NLSGOTO = 103;
static const int NLSCENTRAL = 104;
static const int NLSPRIVATE = 105;
static const int NLSSELECTION = 106;
static const int NLSFILENOTEXIST = 107;
static const int NLSQUIT = 108;
static const int NLSACCELERATOR = 109;
static const int NLSPOSITION = 110;
static const int NLSNOPRINTER = 111;
static const int NLSNOSELECTION = 112;
static const int NLSDISCARDINFO = 113;
static const int NLSBREAKORTAG = 114;
static const int NLSINFONOTICE = 115;
static const int NLSDEBUGGERFULL = 116;
static const int NLSFILEOPENERROR = 117;
static const int NLSSELECTFILE = 118;
static const int NLSRESETVAR = 119;
static const int NLSFILENOTLOADED = 120;
static const int NLSCOMMENTTITLE = 121;
static const int NLSCOMMENTWIN = 122;
static const int NLSSTATUSWINV = 123;
static const int NLSSTATUSTITLE = 124;
static const int NLSCURRENTDIR = 125;
static const int NLSUPDATE = 126;
static const int NLSVIEWAPPLY = 127;
static const int NLSPOSUPDATE = 128;
static const int NLSSTEPONLY = 129;
static const int NLSCODEWINSIZE = 130;
static const int NLSSMALL = 131;
static const int NLSMEDIUM = 132;
static const int NLSLARGE = 133;
static const int NLSCURRENTPOS = 134;
static const int NLSCANTINCLUDE = 135;
static const int NLSOK = 136;
static const int NLSSTEPCANTINCLUDE = 137;
static const int NLSVIEWRESP = 138;

#ifdef OZT_PROTOTYPE
static const int NLS_CMD_INPUT_AREA = 200;
static const int NLS_CONFIRM = 210;
static const int NLS_INHIBIT = 211;
static const int NLS_DOCUMENTATION = 212;
static const int NLS_CONFIRM_REQ_MSG1 = 213;
static const int NLS_CONFIRM_REQ_MSG2 = 214;
static const int NLS_CONFIRM_REQ_MSG3 = 215;
#endif

// ELB Integration messages 1000-1100

static const int NLSELBTASKID = 1006;  // same code as in CHA

// OLDT Integration messages 1151-1200

static const int NLSOLDTBOOKNOTFOUND     = 1151;
static const int NLSOLDTINVALIDNENAME    = 1152;
static const int NLSOLDTINVALIDSTRING    = 1153;
static const int NLSOLDTSERVERERROR      = 1154;
static const int NLSOLDTSERVERSTARTING   = 1155;
static const int NLSOLDTSERVERRETRIEVING = 1156;
static const int NLSOLDTSERVERBUSY       = 1157;
static const int NLSOLDTSERVERDISPLAYED  = 1158;
static const int NLSOLDTUNABLETOOPENDB   = 1159;
static const int NLSOLDTUNKNOWNERROR     = 1160;
static const int NLSOLDTRETURNEDOK       = 1161;
static const int NLSOLDTISINSTALLED      = 1162;
static const int NLSOLDTINVALIDSUBJECT   = 1163;
static const int NLSOLDTCURRENTNETYPE    = 1164;
static const int NLSOLDTCANNOTFINDNEINFO = 1165;
static const int NLSOLDTOUTOFMEMORY      = 1166;

// OLDT Buttons
static const int NLSOLDTDOCMENUTITLE     = 1167;
static const int NLSOLDTCODTITLE         = 1168;
static const int NLSOLDTPODTITLE         = 1169;
static const int NLSOLDTOPITITLE         = 1170;
static const int NLSOLDTAITITLE          = 1171;
static const int NLSOLDTMLIBTITLE        = 1172;

// New errorcodes in OLDT
const int       NLSOLDTTTERROR          = 1178;
const int       NLSOLDTEOLMERROR        = 1179;
const int       NLSOLDTINVALIDDN        = 1180;
const int       NLSOLDTSYNTAXERROR      = 1181;
const int       NLSOLDTINVALIDNEASTYPE  = 1182; 

#endif
