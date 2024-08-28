// RCS handling
// $Id: CHA_ReportIdentity.H,v 24.0 1995/11/28 17:00:34 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_ReportIdentity - Reportidentities subscribed for 
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_ReportIdentity.H 

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
//      This class is used to keep track of which reportidentities that are
//      subscribed for.
//      Each instance of the class can either hold an interval, a single
//      value or a string value. These values are combined with an OR-operator
//      by EA to select the spontaneous reports which the user wants to see.
//      Intervals are defined with low and high, string values with string and
//      single values with low.

// DOCUMENT NO
//      190 89-CAA 134 1521

// AUTHOR 
//      1994-04-20 by EHS / Marie Moschna (qhsmosc@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_ReportIdentity.H,v $
//      Revision 24.0  1995/11/28 17:00:34  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.0  95/09/07  17:49:30  17:49:30  ehscama (Martin Carlsson VK/EHS/VE)
//      Made release XM2S1, ehscama.
//      
//      Revision 22.0  1995/08/01  20:50:24  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:47:45  09:47:45  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:38:54  08:38:54  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.1  95/05/18  09:37:58  09:37:58  qhsjody (Johan Dykstrom VK/EHS/PXE)
//      Fixed bug in enum criteriaType.
//      
//      Revision 19.0  1995/04/13  10:58:23  cmcha
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 18.0  95/03/17  20:11:05  20:11:05  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:13:20  14:13:20  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:05:21  13:05:21  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:12:07  15:12:07  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:38:52  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:12:18  14:12:18  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:22:50  16:22:50  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:54:24  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:08:20  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:35:11  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:56:18  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:28:04  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:55:11  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:53:35  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:45:23  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  08:00:15  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  08:01:34  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.3  1994/06/10  16:56:08  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.2  1994/05/06  06:48:03  qhsmosc
//      Compilable version
//
//      Revision 1.1  1994/04/26  08:00:00  qhsmosc
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

// .SEE ALSO 
//      CHA_Subsc

//**********************************************************************

#ifndef CHA_REPORTIDENTITY_H
#define CHA_REPORTIDENTITY_H

#include <rw/cstring.h>

enum criteriaType {
    NO_VALUE,
    LOW_ONLY,
    RANGE,
    STRING
};

class  CHA_ReportIdentity
{
public:
    
    CHA_ReportIdentity();
    // Description:
    //     Default constructor. 

    CHA_ReportIdentity(const CHA_ReportIdentity& ri);
    // Description:
    //     Copy constructor. 
    // Parameters: 
    //     ri                    Original report identity 

    virtual ~CHA_ReportIdentity();
    // Description:
    //     Default destructor. 

    virtual void setLow(const long low);
    // Description:
    //     Set lower limit in interval or single value.
    // Parameters: 
    //     low                   Lower limit or single value. 

    virtual void setHigh(const long high);
    // Description:
    //     Set upper limit in interval.
    // Parameters: 
    //     low                   Upper limit. 

    virtual void setString(const RWCString s);
    // Description:
    //     Set string.
    // Parameters: 
    //     s                     String value. 

    virtual void setCriteriaType(const criteriaType c);
    // Description:
    //     Set description of criteriatype stored.
    // Parameters:
    //     enum indicating criteria type.
	
    virtual const long getLow() const;
    // Description:
    //     Get lower limit or single value.
    // Return value: 
    //     Lower limit or single value. 

    virtual const long getHigh() const;
    // Description:
    //     Get upper limit.
    // Return value: 
    //     Upper limit. 

    virtual const RWCString& getString() const;
    // Description:
    //     Get string description.
    // Return value:
    //     String value.

    virtual const criteriaType& getCriteriaType() const;
    // Description:
    //     Get description of criteriatype stored.
    // Return value:
    //     enum indicating criteria type.
	
    virtual CHA_ReportIdentity& operator=(const CHA_ReportIdentity& r);
    // Description:
    //     Assignmentoperator, required by TOOL.
    // Parameter:
    //     r                    The original report identity
    // Return value:
    //     Reference to self.

    virtual int operator==(const CHA_ReportIdentity& ri) const;
    // Description:
    //     Equality operator, required by TOOL.
    // Parameter:
    //     ri                   the report identity that is to be compared
    // Return value:
    //     integer     defined in the same manner as the default operator ==
    
private:                
    long low;                  // Lower limit or if single value
    long high;                 // Upper limit
    RWCString stringValue;     // Wanted reportidentity described as a string.
    criteriaType type;         // Type of criteria 
};

#endif
