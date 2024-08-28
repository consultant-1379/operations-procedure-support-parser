// RCS handling
// $Id: CHA_Trace.H,v 24.0 1995/11/28 16:55:14 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_Trace.H
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_Trace.H

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
//      Macros for utilizing CAP-trace.

// DOCUMENT NO
//      190 89-CAA 134 1515

// AUTHOR 
//      1994-02-17 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_Trace.H,v $
//      Revision 24.0  1995/11/28 16:55:14  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:41:34  17:41:34  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:44:17  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:40:05  09:40:05  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:32:46  08:32:46  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:52:09  10:52:09  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:04:24  20:04:24  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:02:51  14:02:51  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  12:58:17  12:58:17  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:00:23  15:00:23  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:33:10  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:02:43  14:02:43  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:13:36  16:13:36  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:45:16  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:01:56  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:28:41  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:48:11  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:22:31  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:49:37  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:44:33  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.1  1994/07/21  17:07:40  ehsgrap
//      Added NOTRACE condition/macro
//
//      Revision 4.0  1994/07/18  13:37:10  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:51:55  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:04:11  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.3  1994/05/31  08:46:18  ehsgrap
//      sun and hp seems to be able to use the same macro definitions now
//
//      Revision 1.2  1994/02/22  10:20:27  ehsgrap
//      Corrections for first compilation.
//
//      Revision 1.1  1994/02/17  15:21:53  ehsgrap
//      Initial version, basically a copy from CFHPRIM
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
//	PREIT   1995-01-18      N Länninge (XKKNICL)    RCS rev 11.0
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
//      trace_utility(1)

//**********************************************************************

#ifndef CHA_TRACE_H
#define CHA_TRACE_H

#include <iostream>
#include <strstream>
//#include <cap_trc.h>

#ifndef NOTRACE

#define TRACE_IN( trbl, method, param_list )               \
if(CAP_TRC_ON(trbl))                                       \
{                                                          \
    ostrstream oss;                                        \
    oss << " -> " << #method << "(" << param_list << ")" << ends;     \
    char *s = oss.str();                                   \
    CAP_TRC_event(&trbl, s);                               \
    delete [] s;                                              \
}

#define TRACE_FLOW( trbl, method, free_text )              \
if(CAP_TRC_ON(trbl))                                       \
{                                                          \
    ostrstream oss;                                        \
    oss << " -- " << #method << ": " << free_text << ends;            \
    char *s = oss.str();                                   \
    CAP_TRC_event(&trbl, s);                               \
    delete [] s;                                              \
}

#define TRACE_OUT( trbl, method, out_param )               \
if(CAP_TRC_ON(trbl))                                       \
{                                                          \
    ostrstream oss;                                        \
    oss << " <- " << #method << "(" << out_param << ")" << ends;      \
    char *s = oss.str();                                   \
    CAP_TRC_event(&trbl, s);                               \
    delete [] s;                                              \
}

#define TRACE_RETURN( trbl, method, result )               \
if(CAP_TRC_ON(trbl))                                       \
{                                                          \
    ostrstream oss;                                        \
    oss << " <- " << #method << " = " << result << ends;              \
    char *s = oss.str();                                   \
    CAP_TRC_event(&trbl, s);                               \
    delete [] s;                                              \
}


#else

#define TRACE_IN( trbl, method, param_list )               
#define TRACE_FLOW( trbl, method, free_text )              
#define TRACE_OUT( trbl, method, out_param )               
#define TRACE_RETURN( trbl, method, result )               

#endif

#endif
