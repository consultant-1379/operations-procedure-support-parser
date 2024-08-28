//**********************************************************************
//
// NAME
//      Semaphore.H
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
// 

// REVISION
//      A

// CHANGES
//      <Revision history>
// $Log$
//      REV NO  DATE           NAME        DESCRIPTION
//      A       1999-11-18     ehslalu     1 release

//**********************************************************************

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

class Semaphore
{
   public:
      Semaphore() { mySemaphore = 0; }
      void set()  { mySemaphore++; }
      int  get()  { return mySemaphore; }
      void wait();

   private:
      int mySemaphore;
};

#endif //SEMAPHORE_H
