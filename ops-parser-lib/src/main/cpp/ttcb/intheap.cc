//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/intheap.cc @@/main/1 2000-03-10.17:23 EHS

/*
 *--------------------------------------------------------------------------
 *
 * Name         intheap.C
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
 * Product      System          TMOS
 *              Subsystem       TAP
 *              Function block  TTCB 
 *              Software unit   TTCLIB
 *              
 * Document no  18/19055-CAA 134 420
 *
 * Rev-state    A
 *
 * Original     1990-03-27 by TX/HJL Anders Olander
 *
 * Description  Provides a simple uint heap. Algorithm described
 * 		in "Algorithms" by Robert Sedgewick.
 *		(Element with index zero, isn't used.)
 *        
 * Revision     <rev> <yyyy-mm-dd> by <dep> <name>
 * Description  <description-of-the-revision>
 *
 *-------------------------------------------------------------------------
 */

#include <intheap.hh>

/*****************************************************
 * Adds another element to the heap. value >= 0
 * Returns 0 on success, and -1 on failure.
 */
int Heap::add(int value) {
	int place;
	if (!this) return -1;
	if (value < 0 ||
	    state == BAD)
		return -1;

	// Upheap:
	place = ++_size;
	while (place > 1 && value < list.get(place >> 1)) {
		if (list.set(place, list.get(place >> 1)))
			return -1;
		place >>= 1;
	}
	if (list.set(place, value)) return -1;

	return 0;
}


/******************************************************
 * Gets the value of the first element, which is also
 * removed from the heap. The first element will have the
 * least value.
 * Returns value >= 0 on success, and -1 on failure.
 */
int Heap::get() {
	int out, left, right, place, temp;
	if (!this ||
	    _size < 1 ||
	    state)
		return -1;

	// Downheap:
	out = list.get(1);
	temp = list.get(_size--);
	place = 1;
	while (place <= (_size >> 1)) {

		left = list.get(place << 1);
		right = list.get((place << 1) + 1);
		if (temp <= left && temp <= right)
			break;

		if (left < right) {
			if (list.set(place, left)) {
				state = BAD;
				return -1;
			}
			place <<= 1;

		} else {
			if (list.set(place, right)) {
				state = BAD;
				return -1;
			}
			place = (place << 1) + 1;
		}
	}
	if (list.set(place, temp)) {
			state = BAD;
			return -1;
		}

	return out;
}
