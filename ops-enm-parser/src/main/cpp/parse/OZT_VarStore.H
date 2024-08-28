// RCS revision handling
// $Id: OZT_VarStore.H,v 21.0 1996/08/23 12:43:28 ehsgrap Rel $

//*****************************************************************************
// 
// .NAME
//  	OZT_VarStore - Store for variables in command files
// .LIBRARY CHOZTBIN
// .PAGENAME OZT_VarStore
// .LEFT_FOOTER Ericsson HP

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
// 	An OZT_VarStore object maintains a table of variables and their
//      contents. This class inherits from CHA_Model class so that any
//      changes to the variable store will result in an updateFrom call
//      to each of its model clients. 
//
//      The second parameter supplied to the updateFrom call is a pointer 
//      to a RWCString which contains the name of the variable changed.
//      If the whole variable store is cleared, the second parameter to
//      the updateFrom call will be a null pointer.


// .ERROR HANDLING
//	The error handling is specified for each method.
//
//	No methods initiate or send  PMS error reports unless specified.

// DOCUMENT NO
//	190 89-CAA 134 2016

// AUTHOR 
// 	1994-10-31 by EPA/T/EN Nelson Cheng

// CHANGES
// 	RCS REVISION HISTORY
//
// 	$Log: OZT_VarStore.H,v $
// 	Revision 21.0  1996/08/23 12:43:28  ehsgrap
// 	Made release B_POINT, J Grape (EHSGRAP).
//
// 	Revision 20.0  1996/07/10 07:57:54  epadmt
// 	Made release EC8_OZ, David Terry epa.epadmt.
//
// 	Revision 19.0  1996/03/19 07:22:34  ehsjasa
// 	Made release POW_TB61, J Sandquist (ehsjasa).
//
// 	Revision 18.0  1996/03/01 12:22:01  ehsjasa
// 	Made release EC7_OZ, J Sandquist (ehsjasa).
//
// 	Revision 17.0  1996/01/17 12:02:27  ehsjasa
// 	Made release EC6_OZ, J Sandquist (ehsjasa).
//
// 	Revision 16.0  1996/01/08 18:57:36  ehsjasa
// 	Made release POW_TB41, J Sandquist (ehsjasa).
//
// 	Revision 15.0  1995/11/29 02:03:05  ehsgrap
// 	Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 14.0  95/11/20  17:17:33  17:17:33  ehsjasa (Jan Sandquist VK/EHS/VE)
//      Made release POW_TB3, J Sandquist (EHSJASA).
//      
// 	Revision 13.0  1995/10/07 12:01:47  ehsjasa
// 	Made release PRE_XM22, J Sandquist (EHSJASA).
//
// 	Revision 12.0  1995/09/22 14:09:49  cmcha
// 	Made release EC5_OZ, J Sandquist (EHSJASA).
//
//      Revision 11.0  95/09/14  09:25:27  09:25:27  ehsjasa (Jan Sandquist VK/EHS/PXE)
//      Made release EC4_OZ, J Sandquist (EHSJASA).
//      
// 	Revision 10.0  1995/08/02 11:02:49  cmcha
// 	Made release EC3_OZ, J Sandquist (EHSJASA).
//
//      Revision 9.1  95/06/30  14:03:47  14:03:47  epanyc (Nelson Cheng VK/EHS/PXE)
//      header filled
//      
//      Revision 9.0  1995/06/29  14:38:24  cmcha
//      Made release EC2_OZ, J Grape (EHSGRAP).
//
//      Revision 8.0  95/06/07  17:09:38  17:09:38  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (EHSGRAP).
//
//      Revision 7.0  95/04/16  12:16:48  12:16:48  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//
//      Revision 6.0  95/03/17  20:05:54  20:05:54  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//
//      Revision 5.0  95/03/16  20:31:37  20:31:37  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//
//      Revision 4.0  95/02/23  21:46:21  21:46:21  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB4, J Grape (EHSGRAP).
//
//      Revision 3.0  95/02/06  20:58:30  20:58:30  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//
//      Revision 2.4  95/01/31  10:31:30  10:31:30  epanyc (Nelson Cheng VK/EHS/PXE)
//      no change
//
//      Revision 2.3  1994/12/21  16:14:20  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 2.0  94/12/21  13:52:27  13:52:27  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 1.4  1994/11/16  10:30:21  epanyc
//
//      Revision 1.3  94/11/02  12:38:24  12:38:24  epanyc (Nelson Cheng VK/EHS/PXE)
//      *** empty log message ***
//
//      Revision 1.2  1994/10/12  16:36:03  epanyc
//      SUCCESS becomes NO_PROBLEM
//
//      Revision 1.1  1994/10/05  13:22:39  cmcha
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
#ifndef OZT_VARSTORE_H
#define OZT_VARSTORE_H

#include <CHA_Model.H>
#include <rw/tvhdict.h>
#include <rw/cstring.h>
#include <OZT_Value.H>

class OZT_VarStore: public CHA_Model {
public:
    OZT_VarStore();
    // Description
    //     Constructor.


    ~OZT_VarStore();
    // Description
    //     Destructor.


    void put(const RWCString &varName, const OZT_Value &content);
    // Description:
    //     Insert the pair ("varName", "content") into the store
    // Parameters:
    //     varName                 IN: the name of the variable to be inserted
    //     content                 IN: the content of "varName" to be inserted


    RWBoolean  get(const RWCString &varName, OZT_Value &content);
    // Description:
    //     Retrieve the content of "varName"
    // Parameters:
    //     varName                 IN: the name of the variable to be retrieved
    //     content                 OUT: the content of the variable
    // Return values:
    //     TRUE                    if "varName" is in the store
    //     FALSE                   if "varName" is not in the store, "content"
    //                             remains unchanged in this case.


    RWBoolean  contains(const RWCString &varName);
    // Description:
    //     Test if "varName" is in the store
    // Parameter:
    //     varName                 IN: the name of the variable to be found
    // Returns:
    //     TRUE                    if "varName" is in the store
    //     FALSE                   if "varName" is not in the store


    RWBoolean flushVar(const RWCString &varName);
    // Description:
    //    Clear the content of "varName" as if it is not defined
    // Parameter:
    //    varName                  IN: the name of the variable to be cleared
    // Returns:
    //    TRUE                     if "varName" is in the store when this 
    //                             function is called
    //    FALSE                    if "varName" is not in the store


    void  clearAll();
    // Description:
    //     Clear all the variables in the store
   

    size_t entries();
    // Description:
    //     returns the number of variables defined in the store


    OZT_Result  inc(const RWCString &varName); 
    // Description: 
    //     increase the content of "varName" by 1 
    // Returns:   
    //     NO_PROBLEM              if this operation is successful 
    //     UNDEFINED_VAR           if "varName" is not defined 
    //     INVALID_VALUE           if the content of "varName" is not numeric 
   

    OZT_Result  dec(const RWCString &varName);
    // Description:
    //     decrease the content of "varName" by 1
    // Returns:   
    //     NO_PROBLEM              if this operation is successful
    //     UNDEFINED_VAR           if "varName" is not defined
    //     INVALID_VALUE           if the content of "varName" is not numeric

  struct myHash{
    unsigned long operator()(const RWCString& x) const
    {return x.hash();}
    //{return x.length()  * (long)x(0);}
  };

private:

  //RWTValHashDictionary<RWCString, OZT_Value> store;
RWTValHashMap<RWCString, OZT_Value, myHash,
                      std::equal_to<RWCString> > store;
};

#endif
