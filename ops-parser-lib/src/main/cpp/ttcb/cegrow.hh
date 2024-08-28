/*
 *--------------------------------------------------------------------------
 *
 * Name         cegrow.H
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
 * Document no  21/19055-CAA 134 420
 *
 * Rev-state    B
 *
 * Original     1990-03-27 by TX/HJL Anders Olander
 *
 * Description  Unlimited ComEntry array class.
 *        
 * Revision     B by TM/HJG Gunni Kallander
 * Description  com_entry changed to tas_tc_com_entry.
 *
 *-------------------------------------------------------------------------
 */

#ifndef CEGROW_H 
#define CEGROW_H
//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/cegrow.hh @@/main/1 2000-03-10.17:23 EHS

#include <tas_tc_com_entry.hh>
 
class GrowCEArray {
	TAS_TC_com_entry *root;
	int size;
public:
	GrowCEArray(int BaseSize = 16);
	~GrowCEArray();

	TAS_TC_com_entry get(int index);
	int set(int index, TAS_TC_com_entry value);
};

#endif

