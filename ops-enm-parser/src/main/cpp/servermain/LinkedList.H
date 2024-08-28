//ClearCase Version Control Information
//ClearCase: @(#) syn-opsserver/server/servermain/src/LinkedList.H @@/main/1 2000-03-01.17:39 EHS

//***************************************************************************
// 
// .NAME         LinkedList.H
// .HEADER       GDK
// .LIBRARY      TestClient
// .LEFT_FOOTER  EHPT AB
// .FOOTER_DATE  2000-02-24

// .COPYRIGHT
//	COPYRIGHT EHPT AB, Sweden 2000.
//	All rights reserved.
//
// 	The Copyright to the computer program(s) herein is the property of
// 	EHPT AB, Sweden.
// 	The program(s) may be used and/or copied only with the written
// 	permission from EHPT AB or in accordance with the terms and
// 	conditions stipulated in the agreement/contract under which
// 	the program(s) have been supplied.

// .DESCRIPTION
// 	This class provides a convenient way to hold a list of pointers.

// .ERROR HANDLING
//	The error handling is specified for each method.

// DOCUMENT NO
//	<XX/190 55-CXC ZZZ ZZZ>

// AUTHOR 
//	2000-02-24 by Lars Lundberg, ehslalu.

// CHANGES
//	RCS REVISION HISTORY
//
//	$Log: LinkedList.hh,v $
//
//	Revision 1.0  2000-02-24 ehslalu
//	Initial revision.
//
//
//	RELEASE REVISION HISTORY
//
//	REV NO	DATE		NAME			DESCRIPTION
//		2000-02-24	L. Lundberg (ehslalu)	RCS rev. 1.0
//
//***************************************************************************

#ifndef LINKEDLIST_H
#define LINKEDLIST_H


//***************************************************************************
// Class LinkedList declaration.
//***************************************************************************
class LinkedList
{
   public:
      LinkedList();
      // Description:
      //    Default Constructor.
      //    Constructs an emtpy list.


      virtual ~LinkedList();
      // Description:
      //    Destructor. 
      //    Destroys the list, but it does not destroy the elements.


      void  append( void* pContents );
      // Description:
      //    Appends the specified element to the list.
      //    
      // Parameters:
      //    pContents  (IN)   The element to be appended.


      void  prepend( void* pContents );
      // Description:
      //    Prepends the specified element to the list.
      //    
      // Parameters:
      //    pContents  (IN)   The element to be prepended.


      void  remove( void* pContents );
      // Description:
      //    Removes the specified element from the list.
      //    
      // Parameters:
      //    pContents  (IN)   The element to be removed.


      void* operator[]( int index );
      // Description:
      //    Returns the element pointed out by the given index.
      //    If the index is out of range it returns a NULL pointer.
      //    The valid range is between 0 and (length - 1).
      //    
      // Parameters:
      //    index  (IN)   An index pointing out the wanted element.
      //
      // Return value:
      //    The element pointed out by the index, or NULL if the index
      //    is out of range.


      int  length() { return noOfElements_; }
      // Description:
      //    Returns the length of the list, i.e. the number of elements
      //    in the list.
      //
      // Return value:
      //    The number of elements in the list.


      void clear();
      // Description:
      //    Clears the whole list but it does not destroy the elements.


   private:
      //*********************************************************************
      // Inner class Node declaration.
      //*********************************************************************
      class Node
      {
         public:
            void* pContents_;
            Node* pPrev_;
            Node* pNext_;

            Node()  { pContents_ = NULL; pPrev_ = NULL; pNext_ = NULL; }
            ~Node() { pContents_ = NULL; pPrev_ = NULL; pNext_ = NULL; }
      };

      //*********************************************************************
      // End of inner class Node declaration.
      //*********************************************************************


      Node* pHead_;
      Node* pTail_;
      int   noOfElements_;

      void* extract( int index );
      void  removeNode( Node* pNode );
};

//***************************************************************************
// End of class LinkedList declaration.
//***************************************************************************

#endif //#ifndef LINKEDLIST_H
