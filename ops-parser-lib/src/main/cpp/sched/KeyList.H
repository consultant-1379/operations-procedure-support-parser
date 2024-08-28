//**********************************************************************
// 
// NAME
//		 KeyList 

// .COPYRIGHT
//  COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1999
//
// The Copyright to the computer program(s) herein is the
// property of Ericsson Hewlett-Packard Telecommunications AB, Sweden.
// The program(s) may be used and/or copied with the
// written permission from Ericsson Hewlett-Packard Telecommunications AB
// or in accordance with the terms and conditions stipulated
// in the agreement/contract under which the program(s)
// have been supplied.
// 

// .DESCRIPTION 
// 	This class is used to store the list of keys created after a call to
//  the getFirstKey method in the class AM_OrderStorage (see OrderStorage.hh).

// DOCUMENT NO
//	190 55-CXC 134 998

// AUTHOR 
// 	1992-05-29  EME/TY/O Ricardo Cordon itsrcma@madrid.ericsson.se

// SEE ALSO
//

//**********************************************************************

#ifndef KEY_LIST_H
#define KEY_LIST_H


class KeyList
{
    public:
                      KeyList();
                      ~KeyList();
          void        setKey(long key);
          long        getKey();
          void        linkIn(KeyList* newOne);
          KeyList*    getNext();

    private:
          long       orderKey;
          KeyList *  next;
};

#endif 
