// RCS handling
// $Id: CHA_ReportIdentity.C,v 24.0 1995/11/28 17:00:55 ehsgrap Rel $

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
//	190 89-CAA 134 1521

// AUTHOR
//      1994-04-20 by EHS / Marie Moschna (qhsmosc@ehs.ericsson.se)

// REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_ReportIdentity.C,v $
//      Revision 24.0  1995/11/28 17:00:55  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:50:04  17:50:04  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:50:48  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:48:24  09:48:24  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//
//      Revision 20.0  95/06/08  08:39:32  08:39:32  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//
//      Revision 19.0  95/04/13  10:58:55  10:58:55  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:11:33  20:11:33  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 17.0  95/03/16  14:13:48  14:13:48  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 16.0  95/03/10  13:05:50  13:05:50  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//
//      Revision 15.0  95/03/09  15:13:02  15:13:02  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//
//      Revision 14.0  1995/02/25  16:39:16  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:12:51  14:12:51  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//
//      Revision 12.0  95/02/06  16:23:37  16:23:37  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 11.0  1995/01/18  14:54:58  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:09:02  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:35:44  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:57:06  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:28:45  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:55:47  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:54:30  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:46:05  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  08:01:00  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:02:11  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.3  1994/05/13  09:46:56  qhsmosc
//      Final version
//
//      Revision 1.2  1994/05/06  06:48:32  qhsmosc
//      Compilable version
//
//      Revision 1.1  1994/04/26  07:40:47  qhsmosc
//      Initial revision
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

// SEE ALSO
//

//**********************************************************************

#include <CHA_LibGlobals.H>
#include <CHA_Trace.H>
#include <CHA_ReportIdentity.H>

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"CHA_ReportIdentity", (char*)"C");

// Member functions, constructors, destructors, operators

//**********************************************************************

CHA_ReportIdentity::CHA_ReportIdentity()
{
    //TRACE_IN(trace, CHA_ReportIdentity, "");
    type = NO_VALUE;
};

//**********************************************************************

CHA_ReportIdentity::CHA_ReportIdentity(const CHA_ReportIdentity& reportId)
{
    //TRACE_IN(trace, CHA_ReportIdentity, "");

    // Copy constructor

    low         = reportId.low;
    high        = reportId.high;
    stringValue = reportId.stringValue;
    type        = reportId.type;
};

//**********************************************************************

CHA_ReportIdentity::~CHA_ReportIdentity()
{
};

//**********************************************************************

void CHA_ReportIdentity::setLow(const long lowIn)
{
    //TRACE_IN(trace, setLow, "");

    low = lowIn;
};

//**********************************************************************

const long CHA_ReportIdentity::getLow() const
{
  //TRACE_IN(trace, getLow, "");

  return low;
};

//**********************************************************************

void CHA_ReportIdentity::setHigh(const long highIn)
{
    //TRACE_IN(trace, setHigh, "");

    high = highIn;
};

//**********************************************************************

const long CHA_ReportIdentity::getHigh() const
{
  //TRACE_IN(trace, getHigh, "");

  return high;
};

//**********************************************************************

void CHA_ReportIdentity::setString(const RWCString stringIn)
{
    //TRACE_IN(trace, setString, "");

    stringValue = stringIn;
};

//**********************************************************************

const RWCString& CHA_ReportIdentity::getString() const
{
  //TRACE_IN(trace, getString, "");

  return stringValue;
};

//**********************************************************************

void CHA_ReportIdentity::setCriteriaType(const criteriaType critType)
{
    //TRACE_IN(trace, setCriteriaType, "");

    type = critType;
};

//**********************************************************************

const criteriaType&
CHA_ReportIdentity::getCriteriaType() const
{
  //TRACE_IN(trace, getCriteriaType, "");

  return type;
};

//**********************************************************************

CHA_ReportIdentity& CHA_ReportIdentity::operator=(
    const CHA_ReportIdentity& reportId)
{
    //TRACE_IN(trace, operator=, "");

    low = reportId.low;
    high = reportId.high;
    stringValue = reportId.stringValue;
    type = reportId.type;

    return *this;
};

//**********************************************************************

int CHA_ReportIdentity::operator==(const CHA_ReportIdentity& reportId) const
{
    int evalEquality = 0;

    //TRACE_IN(trace, operator==, "");

    evalEquality = (low == reportId.getLow());
    if (evalEquality != 0)
	return evalEquality;

    evalEquality = (high == reportId.getHigh());
    if (evalEquality != 0)
	return evalEquality;

    evalEquality = (stringValue == reportId.getString());
    if (evalEquality != 0)
	return evalEquality;

    return evalEquality;
};


