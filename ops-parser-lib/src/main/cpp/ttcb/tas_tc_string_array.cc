//Source Code Control System revision handling, optional
//ClearCase: @(#) syn-opsserver/opslib/ttcb/src/tas_tc_string_array.cc @@/main/1 2000-03-10.17:23 EHS

/*
 *--------------------------------------------------------------------------
 *
 * Name         tas_tc_string_array.C
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
 * Document no  20/19055-CAA 134 420
 *
 * Rev-state    A
 *
 * Original     1990-04-02 by TX/HJL Anders Olander
 *
 * Description  Class providing a few methods for composing strings.
 *		Strings that you want to include are "add"ed. Then you
 *		can "build" or "catenate". The functionallities are
 *		described at the declarations.
 *        
 * Revision     <rev> <yyyy-mm-dd> by <dep> <name>
 * Description  <description-of-the-revision>
 *
 *-------------------------------------------------------------------------
 */

#include <string.h>

#include <tas_tc_string_array.hh>

/***********************************************
 * Linked list struct for char*.
 */
struct lchar {
	struct lchar *next;
	char *string;
};

/***********************************************/
TAS_TC_string_array::TAS_TC_string_array() {
	head = (void *)0;
	last = (void **)&head;
}

/***********************************************
 * Destructor. Release memory held by the added strings.
 * (head is used as a (struct lchar *) but declared
 *  as (void *), to avoid having to declare the lchar struct
 *  in the header file. last is used as a (struct lchar **)
 *  but declared as (void **) for the same reason.)
 */
TAS_TC_string_array::~TAS_TC_string_array() {
	struct lchar *temp;
	temp = (struct lchar *)head;
	while (temp) {
		if (temp->string) delete temp->string;
		temp = temp->next;
		delete (struct lchar *)head;
		head = (void *)temp; 
	}
}

/***************************************************
 * Insert another string in the linked list. It will
 * be placed last.
 * (head is used as a (struct lchar *) but declared
 *  as (void *), to avoid having to declare the lchar struct
 *  in the header file. last is used as a (struct lchar **)
 *  but declared as (void **) for the same reason.)
 * Returns 0 on success and -1 on failure.
 */
int TAS_TC_string_array::add(const char *String) {
	struct lchar *temp;
	if (!this || !String) return -1;
	if (!(temp = new struct lchar)) return -1; // Make a new link element.
	if (!(temp->string = new char[strlen(String) + 1])) {
		// No memory available for the string.
		delete temp;
		return -1;
	}
	strcpy(temp->string, String);
	temp->next = (struct lchar *)0;
	*((struct lchar **)last) = temp;
	last = (void **)&(temp->next);
	return 0;
}

/*****************************************************
 * Build a string array (char *[]) which is allocated 
 * as one unit, that is it can be released with a single
 * delete operation.
 * (head is used as a (struct lchar *) but declared
 *  as (void *), to avoid having to declare the lchar struct
 *  in the header file. last is used as a (struct lchar **)
 *  but declared as (void **) for the same reason.)
 * Returns non-null on success, and null on failure.
 */
char **TAS_TC_string_array::build() {
	struct lchar *temp;
	char **block, **pp, *p;
	int count, totalsize, offset;
	if (!this) return (char **)0;

	// Count the strings, and sum the sizes.
	count = totalsize = 0;
	for (temp = (struct lchar *)head; temp; temp = temp->next) {
		count++;
		if (temp->string) totalsize += strlen(temp->string);
	}

	// Build the block. Layout: First the pointers (char *), then
	// a null pointer terminating the array, then the strings, each
	// one terminated with a null character.
	offset = count + 1;		// Start index for the strings.
	if (!(block = (char **)new char[offset * sizeof(char *) +
		totalsize + count])) return (char **)0;
	pp = block;
	temp = (struct lchar *)head;	// temp will traverse the linked list
	p = (char *)(block + offset);
	while (temp) {
		*pp = strcpy(p, temp->string);
		pp++;
		p += strlen(p) + 1;
		temp = temp->next;
	}
	*pp = (char *)0;		// Null pointer terminating the array.

	return block;
}

/*******************************************************
 * Concatenate the strings, making one long string from
 * all the added strings. It will ofcourse be allocated
 * as one unit, and can be released with a single delete
 * operation.
 * (head is used as a (struct lchar *) but declared
 *  as (void *), to avoid having to declare the lchar struct
 *  in the header file. last is used as a (struct lchar **)
 *  but declared as (void **) for the same reason.)
 * Returns non-null on success, and null on failure.
 */
char *TAS_TC_string_array::catenate() {
	struct lchar *temp;
	char *block, *p;
	int count, totalsize;
	if (!this) return (char *)0;

	// Count the strings, and sum their sizes.
	count = totalsize = 0;
	for (temp = (struct lchar *)head; temp; temp = temp->next) {
		count++;
		if (temp->string) totalsize += strlen(temp->string);
	}

	// Catenate the strings. 
	if (!(block = new char[totalsize + 1]))
		return (char *)0;
	temp = (struct lchar *)head;	// temp will traverse the linked list
	p = block;
	while (temp) {
		strcpy(p, temp->string);
		p += strlen(p);
		temp = temp->next;
	}

	return block;
}
