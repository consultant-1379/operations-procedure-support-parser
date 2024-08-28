//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/intgrow.cc @@/main/2 2000-04-03.17:56 EHS

/*
 *--------------------------------------------------------------------------
 *
 * Name         intgrow.C
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
 * Document no  16/19055-CAA 134 420
 *
 * Rev-state    A
 *
 * Original     1990-03-27 by TX/HJL Anders Olander
 *
 * Description  Unlimited int array class
 *        
 * Revision     <rev> <yyyy-mm-dd> by <dep> <name>
 * Description  <description-of-the-revision>
 *
 *-------------------------------------------------------------------------
 */

#include <memory.h>

#include <intgrow.hh>


GrowArray::GrowArray(int BaseSize) { /* Allocate <BaseSize> number of elements
					at construction. */
	if (BaseSize < 1 || !(root = new int[size = BaseSize]))
		root = (int *)0; // Failure state
}

GrowArray::~GrowArray() {
	delete []root;
}

/*********************************************
 * Get the value of the element with index <index> in
 * the array. If the value hasn't been set, the
 * default value zero will be returned.
 * Index mustn't be less than zero.
 */
int GrowArray::get(int index) {
	if (!this ||
	    !root ||
	    index < 0 ||
	    index >= size)
		return 0; //Default value
	return root[index];
}

/************************************************
 * Set the value of the element with index <index> in
 * the array. If space hasn't been allocated before,
 * it will be allocated now.
 * Inputs: index (>= 0), value (any int)
 * Returns 0 on success, and -1 on failure.
 */
int GrowArray::set(int index, int value) {
	if (!this ||
	    !root ||
	    index < 0)
		 return -1; // Failure

	if (index >= size) { // Bigger memory space needed?
		int newsize;
		int *newroot;

		// Double the size till it's big enough.
		for (newsize = 2 * size; index >= newsize; newsize *= 2);
		if (!(newroot = new int[newsize]))
			return -1;

		memcpy(newroot, root, size * sizeof(int));
		delete root;
		root = newroot;
		size = newsize;
	}
	root[index] = value;
	return 0;
}

