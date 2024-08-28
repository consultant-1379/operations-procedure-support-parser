//**********************************************************************

// NAME
//	AM_ttcbFunctions

// COPYRIGHT
// COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1999
//
// The Copyright to the computer program(s) herein is the
// property of Ericsson Hewlett-Packard Telecommunications AB, Sweden.
// The program(s) may be used and/or copied with the 
// written permission from Ericsson Hewlett-Packard Telecommunications AB
// or in accordance with the terms and conditions stipulated
// in the agreement/contract under which the program(s)
// have been supplied.
// 

// DESCRIPTION

// DOCUMENT NO
//	190 55-CXC 134 998

// AUTHOR 
// 	1992-05-29 by EME/TY/O Ricardo Cordon itsrcma@madrid.ericsson.se

// SEE ALSO

//**********************************************************************

#ifndef AM_TTCBFUNCTIONS_H
#define AM_TTCBFUNCTIONS_H

/// TODO 
/// #include <tas_tc_time_control.hh>
/// #include <tas_tc_com_entry.hh>
#include <tas_tc_time_control.hh>
#include <tas_tc_com_entry.hh>

class TAS_TC_time_control;
class TAS_TC_com_entry;

class AM_OrderStorage;

extern char* CHA_SYSCMDFILE;
extern char* CHA_AM_DISPLAYHOST;

class AM_ttcbFunctions
{
public:

    int initOrder(AM_OrderData *,TAS_TC_time_control * & tc);
    int terminateOrder(AM_OrderData *,TAS_TC_time_control * & tc);
    int createCEObject(AM_OrderData * data,
		       TAS_TC_com_entry * & orderEntry);
    void getTtcuipHost(TAS_TC_com_entry * & crontabEntry);
    char* getOwnHost();
};

#endif
