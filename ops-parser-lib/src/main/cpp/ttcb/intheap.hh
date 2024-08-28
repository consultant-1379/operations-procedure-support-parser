#ifndef INTHEAP_H
#define INTHEAP_H
//Sorce Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/intheap.hh @@/main/1 2000-03-10.17:23 EHS

/*
 *--------------------------------------------------------------------------
 *
 * Name         intheap.hh
 *
 * *******************************************************************
 * * COPYRIGHT (c) 1990 Ericsson Telecom AB, Sweden.                 *
 * *                   All rights reserved                           *
 * *                                                                 *
 * * The copyright to the computer program(s) herein is the property *
 * * of Ericsson Telecom AB, Sweden. The programs may be used or     *
 * * copied only with the written permission of Ericsson Telecom AB. *
 * *******************************************************************
 *
 * Product      System          TMOS
 *              Subsystem       TAP
 *              Function block  TTCB 
 *              Software unit   TTCLIB
 *              
 * Document no  17/19055-CAA 134 420
 *
 * Rev-state    A
 *
 * Original     1990-03-27 by TX/HJL Anders Olander
 *
 * Description  Provides a simple int heap.
 *        
 * Revision     <rev> <yyyy-mm-dd> by <dep> <name>
 * Description  <description-of-the-revision>
 *
 *-------------------------------------------------------------------------
 */


#include <intgrow.hh>

class Heap {
public:
	Heap() {_size = 0; state = GOOD;}

	int add(int value);
	int get();

	int size() {return _size;}

private:
	GrowArray list;
	int _size; // Initial _ avoids name conflict with method size()
	enum {BAD = -1, GOOD} state;
};

#endif

