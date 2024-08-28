//**********************************************************************
//
// NAME
//      RequestQueueHandler.H
//
//  COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB, Sweden 1997.
//  All rights reserved.
//
//  The Copyright to the computer program(s) herein is the property of
//  Ericsson Hewlett-Packard Telecommunications AB, Sweden.
//  The program(s) may be used and/or copied only with the written
//  permission from Ericsson Hewlett-Packard Telecommunications AB or in
//  accordance with the terms and conditions stipulated in the
//  agreement/contract under which the program(s) have been supplied.

// DOCUMENT NO
//	

// AUTHOR 

// REVISION
//      A

// CHANGES
//      <Revision history>
// $Log$
//      REV NO  DATE           NAME        DESCRIPTION
//      A       1997-07-30     ehsfrko     1 release

//**********************************************************************

#ifndef REQUEST_QUEUE_HANDLER_H
#define REQUEST_QUEUE_HANDLER_H


#include "LinkedList.H"
#include "Semaphore.H"


class RequestQueueHandler
{
   public:
      RequestQueueHandler();
      ~RequestQueueHandler();

      void            startThread();
      void            stopThread();
      static void*    sObjectThread( void* thisPointer );
      void*           objectThread();
      void            insertAtTail( CORBA::Request* pReq );
      CORBA::Request* removeHead();


   private:
      LinkedList*     pReqList_;
      pthread_mutex_t reqMutex_;     // protect request list
      Semaphore*      reqSemaphore_; // number of pending requests
      pthread_t       threadId_;     // id of the request thread
      int             continue_;     // thread loop flag

};
#endif //#ifndef REQUEST_QUEUE_HANDLER_H
