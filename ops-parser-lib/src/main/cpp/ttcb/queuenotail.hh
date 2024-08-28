#ifndef QUEUENOTAIL_HH
#define QUEUENOTAIL_HH
//Source Code COntrol System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/queuenotail.hh @@/main/2 2000-03-10.17:23 EHS

/*
 *--------------------------------------------------------------------------
 *
 * Name         queuenotail.hh
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
 * Product
 *              Software unit   TTCLIB
 *              
 * Document no  51/19055-CAA 134 420
 *
 * Rev-state    A
 *
 * Original     1990-10-24 by TM/HJL Anders Olander
 *
 * Description  Provides a queue with an invisible tail
 *		Compatible with class Heap
 *        
 * Revision     <rev> <yyyy-mm-dd> by <dep> <name>
 * Description  <description-of-the-revision>
 *
 *-------------------------------------------------------------------------
 */


class Ttc_Queue_no_tail {
public:
	Ttc_Queue_no_tail() {_size = 0; head = -1;}

	int add(int value);
	int get() {return head;}

	int size() {return _size;}

private:
	int _size; // Initial _ avoids name conflict with method size()
	int head;
};

#endif

