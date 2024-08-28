//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/cegrow.cc @@/main/1 2000-03-10.17:23 EHS

/*
 *--------------------------------------------------------------------------
 *
 * Name         cegrow.C
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
 * Document no  22/19055-CAA 134 420
 *
 * Rev-state    B
 *
 * Original     1990-03-27 by TX/HJL Anders Olander
 *
 * Description  Unlimited ComEntry (Command request entry) array class.
 *        
 * Revision     B by TM/HJG Gunni Kallander
 * Description  com_entry changed to tas_tc_com_entry.
 *
 *-------------------------------------------------------------------------
 */

#include <memory.h>

#include <cegrow.hh>


/*********************************************************8
 * Constructor.
 * root == 0 indicates problems.
 */
GrowCEArray::GrowCEArray(int BaseSize) {
	if (BaseSize < 1 || !(root = new TAS_TC_com_entry[size = BaseSize]))
		root = (TAS_TC_com_entry *)0;
}


/**************************************************************
 * Destructor
 */
GrowCEArray::~GrowCEArray() {
        delete [] root;
}


/*************************************************************
 * Get element with index 'index'.
 * Index mustn't be less than zero.
 */
TAS_TC_com_entry GrowCEArray::get(int index) {
	TAS_TC_com_entry default_return;
	if (!this ||
	    !root ||
	    index < 0 ||
	    index >= size)
		return default_return;

	return root[index];
}


/*********************************************************
 * Set the value of the element with index 'index' in the
 * array. If space hasn't been allocated before, it will
 * be allocated now.
 * Inputs: index (>= 0), value (any TAS_TC_com_entry)
 * Returns 0 on success, and -1 on failure
 */
int GrowCEArray::set(int index, TAS_TC_com_entry value) {
	if (!this || !root || index < 0) return -1; // Failure
	if (index >= size) {
		int newsize, i;
		TAS_TC_com_entry *newroot;

		// Double the size of the space till it's big enough.
		for (newsize = 2 * size; index >= newsize; newsize *= 2);
		if (!(newroot = new TAS_TC_com_entry[newsize])) return -1;

                 for (i = 0; i < size; i++) {
                    newroot [i] = root [i];
                }
 
		delete root;
		root = newroot;
		size = newsize;
	}
	root[index] = value;
	return 0;
}

