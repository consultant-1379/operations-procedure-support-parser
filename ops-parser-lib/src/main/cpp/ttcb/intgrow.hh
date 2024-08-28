#ifndef INTGROW_H 
#define INTGROW_H
//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/intgrow.hh @@/main/1 2000-03-10.17:23 EHS
 
/*
 *--------------------------------------------------------------------------
 *
 * Name         intgrow.H
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
 * Document no  15/19055-CAA 134 420
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

class GrowArray {
	int *root, size;
public:
	GrowArray(int BaseSize = 64);
	~GrowArray();

	int get(int index);
	int set(int index, int value);
};

#endif

