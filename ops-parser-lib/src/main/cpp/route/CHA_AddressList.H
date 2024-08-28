// RCS handling
// $Id: CHA_AddressList.H,v 24.0 1995/11/28 16:57:42 ehsgrap Rel $

//**********************************************************************
// 
// .NAME    CHA_AddressList - a list of destination addresses
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE CHA_AddressList.H

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
//      This is a list of addresses (strings) used for storing routing
//      information. It is also a model that can de observed by model
//      clients for changes in the information.

// DOCUMENT NO
//      190 89-CAA 134 1519

// AUTHOR 
//      1994-04-16 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION
//	TB53_OZ
//	1995-11-28

// CHANGES
//      RCS revision history
//      $Log: CHA_AddressList.H,v $
//      Revision 24.0  1995/11/28 16:57:42  ehsgrap
//      Made release TB53_OZ, J Grape (EHSGRAP).
//
//      Revision 23.1  95/10/09  15:41:49  15:41:49  ehsgrap (Jan Grape (9 9073) VK/EHS/VE)
//      *** empty log message ***
//      
//      Revision 23.0  1995/09/07 17:45:10  ehscama
//      Made release XM2S1, ehscama.
//
//      Revision 22.0  1995/08/01  20:47:01  cmcha
//      Made release EC2_OZ, Jan Sandquist (EHSJAASA).
//
//      Revision 21.0  95/06/29  09:43:39  09:43:39  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release EC1_OZ, J Grape (EHSGRAP).
//      
//      Revision 20.0  95/06/08  08:35:37  08:35:37  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_2_OZ, J Grape (ehsgrap).
//      
//      Revision 19.0  95/04/13  10:54:56  10:54:56  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_1_OZ, J Grape (EHSGRAP).
//      
//      Revision 18.0  95/03/17  20:07:18  20:07:18  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB51_OZ, ehscama.
//      
//      Revision 17.0  95/03/16  14:07:52  14:07:52  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB5_OZ, ehscama.
//      
//      Revision 16.0  95/03/10  13:01:36  13:01:36  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C_B, N.Lanninge (XKKNICL).
//      
//      Revision 15.0  95/03/09  15:05:19  15:05:19  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB6_B1C, N.Lanninge (XKKNICL).
//      
//      Revision 14.0  1995/02/25  16:35:38  cmcha
//      Made release TB4_OZ, J Grape (EHSGRAP).
//
//      Revision 13.5  95/02/15  14:06:33  14:06:33  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release CHUI_TB6, N.Lanninge (XKKNICL).
//      
//      Revision 12.0  95/02/06  16:18:10  16:18:10  cmcha (*CHA conf. and dev. EHS/PXE)
//      Made release TB3, J Grape (EHSGRAP).
//      
//      Revision 11.0  1995/01/18  14:48:35  cmcha
//      Made release PREIT, N Länninge (XKKNICL).
//
//      Revision 10.0  1994/12/22  09:04:45  cmcha
//      Made release TB2, J Grape (EHSGRAP).
//
//      Revision 9.0  1994/10/24  21:31:10  cmcha
//      Made release E, ehscama.
//
//      Revision 8.0  1994/10/05  08:50:44  cmcha
//      Made release D, EHSCAMA.
//
//      Revision 7.0  1994/09/22  13:24:09  cmcha
//      Made release R1C, J Grape (EHSGRAP).
//
//      Revision 6.0  1994/08/30  17:51:17  cmcha
//      Made release R1B, J Grape (EHSGRAP).
//
//      Revision 5.0  1994/08/16  07:47:08  cmcha
//      Made release R1A, J Grape (EHSGRAP).
//
//      Revision 4.0  1994/07/18  13:39:40  cmcha
//      Made release P1C, J Grape (EHSGRAP).
//
//      Revision 3.0  1994/06/23  07:55:38  cmcha
//      Made release P1B, J Grape (EHSGRAP).
//
//      Revision 2.0  1994/06/12  07:58:33  cmcha
//      Made release P1A, J Grape (EHSGRAP).
//
//      Revision 1.4  1994/06/10  16:52:05  ehsgrap
//      Fixed doc. nr, creation date, header information and
//      changed #include "..." to #include <...> for a great
//      number of files.
//
//      Revision 1.3  1994/06/01  11:59:43  ehsgrap
//      Made operator== a friend.
//
//      Revision 1.2  1994/05/18  09:34:44  ehsgrap
//      Dunno...
//
//      Revision 1.1  1994/04/25  10:59:11  cmcha
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
//      CHA_RoutingCase, CHA_Model

//**********************************************************************

#ifndef CHA_ADDRESSLIST_H
#define CHA_ADDRESSLIST_H

#include <CHA_Model.H>
#include <CHA_LibGlobals.H>

#include <rw/cstring.h>
#include <rw/tvdlist.h>

class CHA_RoutingCase;

class CHA_AddressList : public CHA_Model
{
    friend class CHA_RoutingCase;
    friend RWBoolean operator==(const CHA_AddressList& a1,
				const CHA_AddressList& a2);
public:

    // events
    enum Event {ADDEDITEM,
		REMOVEDITEM,
		NOTHING};
    
    CHA_AddressList();
    // Description:
    //     Constructor. The list is empty from the beginning.

    CHA_AddressList(const CHA_AddressList& other);
    // Description:
    //     Copy constructor.
    // Parameters:
    //     other	the list to copy
    
    virtual CHA_AddressList& operator=(const CHA_AddressList& other);
    // Description:
    //     Assignment operator.
    // Parameters:
    //     other	the list to copy

    virtual ~CHA_AddressList();
    // Description:
    //     Destructor. All items in the list are destructed.

    virtual void append(const RWCString& addr);
    // Description:
    //     Add an address to the end of the list.
    // Parameters:
    //     addr		a string with the address

    virtual RWBoolean contains(const RWCString& addr) const;
    // Description:
    //     Check if an address already is in the list.
    // Parameters:
    //     addr		the address to compare with
    // Return values:
    //     TRUE		an item in the list is equal to addr
    //     FALSE	there is no item like addr in the list

    virtual size_t entries() const;
    // Description:
    //     Measure the length of the list.
    // Return values:
    //     The length of the list.

    virtual RWBoolean insertAt(size_t i, const RWCString& addr);
    // Description:
    //     Insert a value at a certain position in the list. If
    //     a position outside the list is given, nothing is changed.
    // Parameters:
    //     i		the position in the list
    //     addr		the value to insert at position i
    // Return values:
    //     TRUE		item was inserted at i
    //     FALSE	list is unchanged
    
    virtual RWBoolean isEmpty() const;    
    // Description:
    //     Check if list is empty.
    // Return values:
    //     TRUE		the list is empty
    //     FALSE        the list has one or more entries

    virtual RWBoolean remove(const RWCString& addr);
    // Description:
    //     Remove the first item matching addr.
    // Parameters:
    //     addr		the item to compare with
    // Return values:
    //     TRUE		there was an item matching addr in the list and
    //     		it is now removed.
    //     FALSE	no item matched addr in the list

    virtual RWCString removeAt(size_t i);
    // Description:
    //     Remove an item at a specific position. If a position
    //     outside the list is given an empty address is returned.
    // Parameters:
    //     i 		the position that should be removed
    // Return values:
    //     The removed address or an empty string if the list was empty
    //     or 'i' outside the list.

    virtual RWCString operator[](size_t i) const;
    // Description:
    //     To reference an item in the list.
    // Parameters:
    //     i		the position in the list that is referenced
    // Return values:
    //     A constant string reference to the address, i.e. this
    //     operator can't be used for assignment. If 'i' is outside
    //     the list an empty string will be returned.

    virtual RWBoolean isExternallyRouted() const;
    // Description:
    //     Check if these destinations are routed internally (by the
    //     application) or externally, e.g. by EA's subscription
    //     mechanism. 
    // Return values:
    //     TRUE		routing is done externally
    //     FALSE	routing is done by the application. This is
    //                  the default value and can be changed with the
    //                  setExternallyRouted() method.

    virtual CHA_RoutingCase* getRoutingCase();
    // Description:
    //     Get the routing case this address list belongs to.
    // Return values:
    //     A pointer to the routing case or NULL if no routing case
    //     was set.

    virtual const CHA_RoutingCase* getRoutingCase() const;
    // Description:
    //     To get a 'const' pointer to the routng case this address
    //     list belongs to.
    // Return values:
    //     A pointer to the routing case or NULL if no routing case
    //     was set.

    virtual CHA_DestinationType getDestinationType() const;
    // Description:
    //     To find out the type of destination (e.g. mail, printer, file)
    //     these addresses are for.
    // Return values:
    //     One of the destination types mentioned in the enum
    //     CHA_DestinationType in the file CHA_LibGlobals.H.

    virtual Event getLastEvent() const;
    // Description:
    //     To find out what caused a updateFrom() call in a client of
    //     this model.
    // Return values:
    //     ADDEDITEM	an address was added to the list
    //     REMOVEDITEM	an address was removed from the list
    //     NOTHING      nothing has happened

    virtual const RWCString& getChangedAddress() const;
    // Description:
    //     To get hold of the new or removed address when
    //     getLastEvent() has returned ADDEDITEM or REMOVEDITEM.
    // Return value:
    //     A reference to the changed string.
    
protected:

    virtual void announceEvent(Event evt, const RWCString& addr);
    // Description:
    //     Notifies all model clients about an event. During the
    //     notification (the updateFrom() call) a model client can
    //     call getLastEvent() and getChangedAddress() to find out
    //     about the event.
    // Parameters:
    //     evt		the event to announce
    //     addr		the changed string

    virtual void setExternallyRouted(RWBoolean on);
    // Description:
    //     Set these destinations to routed externally. Affects what
    //     is returned by the isExternallyRouted() method.
    //     Used by the class CHA_RoutingCase.
    // Parameters:
    //     on		a boolean, where TRUE means that routing
    //                  should be done externally and FALSE the
    //                  opposite. 

    virtual void setRoutingCase(CHA_RoutingCase* rtCase);
    // Description:
    //     Set the routing case that this address list belongs to.
    //     Used by the class CHA_RoutingCase.
    // Parameters:
    //     rtCase	a pointer to the routing case, can be NULL if
    //                  this list doesn't belong to any routing case.

    virtual void setDestinationType(CHA_DestinationType dt);
    // Description:
    //     Set the type of destination (e.g. mail, printer, file)
    //     these addresses are for.
    //     Used by the class CHA_RoutingCase.
    // Parameters:
    //     dt		a destination type mentioned in the enum
    //                  CHA_DestinationType in the file
    //                  CHA_LibGlobals.H.

    RWBoolean extRouted;
    CHA_RoutingCase* pRoutingCase;
    CHA_DestinationType destinationType;
    RWTValDlist<RWCString> addresses;
    Event lastEvent;
    RWCString changedAddress;
};

inline RWBoolean operator==(const CHA_AddressList& a1,
			    const CHA_AddressList& a2)
{
    return (&a1 == &a2);	// equality is the same as identity
}

#endif
