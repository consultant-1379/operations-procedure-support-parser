//**********************************************************************

// NAME
//		KeyList.C

// COPYRIGHT
// COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1999
//
// The Copyright to the computer program(s) herein is the
// property of Ericsson Hewlett-Packard Telecommunications AB, Sweden.
// The program(s) may be used and/or copied with the 
// written permission from Ericsson Hewlett-Packard telecommunications AB
// or in accordance with the terms and conditions stipulated
// in the agreement/contract under which the program(s)
// have been supplied.
// 

// DOCUMENT NO
//	190 55-CXC 134 998

// AUTHOR 
// 	1992-05-29 by EME/TY/O Ricardo Cordon itsrcma@madrid.ericsson.se

// SEE ALSO

//**********************************************************************

#include <KeyList.H>
#include <string.h>

KeyList::KeyList()
{
    orderKey = 0;
    next = NULL;
}

KeyList::~KeyList()
{
    if (next) delete next;
    next = NULL;
}

void KeyList::setKey(long key)
{
    orderKey = key;
}

long KeyList::getKey()
{
    return orderKey;
}

void KeyList::linkIn(KeyList* newOne)
{
    next = newOne;    
}

KeyList* KeyList::getNext()
{
    return next;
}
