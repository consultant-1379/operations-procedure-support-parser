//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/queuenotail.cc @@/main/1 2000-03-10.17:23 EHS

/*
 *--------------------------------------------------------------------------
 *
 * Name         queuenotail.cc
 *
 * *******************************************************************
 * * COPYRIGHT (c) 1990   Ericsson Telecom AB, Sweden.               *
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
 * Document no  52/19055-CAA 134 420
 *
 * Rev-state    A
 *
 * Original     1990-10-24 by TM/HJL Anders Olander
 *
 * Description  Provides a queue with an invisible tail.
 *        
 * Revision     <rev> <yyyy-mm-dd> by <dep> <name>
 * Description  <description-of-the-revision>
 *
 *-------------------------------------------------------------------------
 */

//#include <colme.C>
//Anders Berglund /VK/EHS/PBO 950918
//#include <colme_CXA_101_005.C>

#include <queuenotail.hh>

/*****************************************************
 * Adds another element to the queue.
 * Returns 0 on success, and -1 on failure.
 */
int Ttc_Queue_no_tail::add(int value) {
	if (_size++==0)
		head = value;
	return 0;
}
