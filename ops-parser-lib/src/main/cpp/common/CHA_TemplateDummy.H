// RCS handling
// $Id: CHA_TemplateDummy.H,v 24.0 1995/11/28 16:55:10 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_TemplateDummy - instantiate templates on Sun
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_TemplateDummy.H

// .COPYRIGHT
// 	COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1995
//
// 	The Copyright to the computer program(s) herein is the
// 	property of Ericsson Hewlett-Packard Telecommunications AB,
// 	Sweden.  The program(s) may be used and/or copied with the
// 	written permission from Ericsson Hewlett-Packard
// 	Telecommunications AB or in accordance with the terms and
// 	conditions stipulated in the agreement/contract under which
// 	the program(s) have been supplied.


// .DESCRIPTION 
//      The CHA_TemplateDummy class is used to force the compiler/linker
//	to instansiate templates hidden in the implementation of CHALIB.
//	To solve the problem just include this file in a central file.
//	The problem only occurs with Suns C++ 3.0.1, but it doesn't
//	hurt to include it on HP-UX too.

// DOCUMENT NO
//	190 89-CAA 134 1515

// AUTHOR 
//      1995-01-18 by EHS/PXE Martin Carlsson (ehscama@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
// 	RCS revision history
//      $Log: CHA_TemplateDummy.H,v $
//      Revision 24.0  1995/11/28 16:55:10  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:41:29  17:41:29  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:44:04  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:39:59  09:39:59  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:32:42  08:32:42  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:52:04  10:52:04  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:04:19  20:04:19  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:02:46  14:02:46  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  12:58:13  12:58:13  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:00:14  15:00:14  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:33:06  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:02:39  14:02:39  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:13:29  16:13:29  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 1.2  1995/01/20  14:41:00  ehscama
//      Fixed capital letter on #include and removed unnecessary variables.
//
//      Revision 1.1  1995/01/19  15:34:01  ehscama
//      First version.
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

// .SEE ALSO 
// 	

//**********************************************************************

#ifndef CHA_TEMPLATEDUMMY_H
#define CHA_TEMPLATEDUMMY_H

#include <rw/cstring.h> // RWCString
#include <rw/tpdlist.h> // RWTPtrDlist
#include <rw/tphdict.h> // RWTPtrHashDictionary
#include <rw/tphasht.h> // RWTPtrHashTable
#include <rw/tpsrtvec.h> // RWTPtrSortedVector
#include <rw/tvdlist.h> // RWTValDlist
#include <rw/tvhdict.h> // RWTValHashDictionary
#include <rw/tvhset.h> // RWTValHashSet
#include <rw/tvordvec.h> // RWTValOrderedVector
#include <rw/tvslist.h> // RWTValSlist
#include <rw/tvsrtvec.h> // RWTValSortedVector

#include <CHA_AddressList.H>
#include <CHA_DCEntry.H>
#include <CHA_DayCategory.H>
#include <CHA_IgnoreCaseString.H>
#include <CHA_ImmRespBuffer.H>
#include <CHA_Order.H>
#include <CHA_ReportIdentity.H>
#include <CHA_ResponseReceiver.H>
#include <CHA_RoutingTarget.H>
#include <CHA_Subsc.H>

class CHA_TemplateDummy
{
    void dummy();
    // Description:
    //    Used to force the Compiler/Linker to instansiate templates
    //    hidden in the implementation of CHALIB.
};

unsigned hashRWCString(const RWCString& str) {return str.hash();}

inline void CHA_TemplateDummy::dummy()
{
    RWTPtrDlist<CHA_AddressList> dummy01;
    RWTPtrDlist<CHA_ImmRespBuffer> dummy02;
    RWTPtrDlist<CHA_ResponseReceiver> dummy03;
    RWTPtrHashDictionary<RWCString, CHA_RoutingTarget> dummy04(hashRWCString);
    RWTPtrHashTable<CHA_DCEntry> dummy05(hashCHA_DCEntry); 
    RWTPtrSortedVector<CHA_DCEntry> dummy06;
    RWTPtrSortedVector<CHA_Order> dummy07;
    RWTValDlist<RWCString> dummy08;
    RWTValHashDictionary< RWCString, RWTValVector<RWCString> >	dummy09(hashRWCString);
    RWTValHashSet<CHA_DayCategory> dummy10(hashDayCategory); 
    RWTValOrderedVector<CHA_ReportIdentity> dummy11;
    RWTValOrderedVector<CHA_Subsc> dummy12;
    RWTValOrderedVector<int> dummy13;
    RWTValOrderedVector<long> dummy14;
    RWTValSlist<RWCString> dummy15;
    RWTValSortedVector<CHA_IgnoreCaseString> dummy16;
    RWTValSortedVector<RWCString> dummy17;

    ; // Do nothing
}

#endif
