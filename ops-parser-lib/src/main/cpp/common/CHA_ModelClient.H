// RCS handling
// $Id: CHA_ModelClient.H,v 22.0.1.1 1996/01/05 14:09:50 ehsphad Exp $

//**********************************************************************
// 
// .NAME    CHA_ModelClient - the view leg of a MVC architecture
// .LIBRARY CHA
// .HEADER  CHA INTERNAL API
// .INCLUDE filename.H 

// .COPYRIGHT
//      COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1994
//
//      The Copyright to the computer program(s) herein is the
//      property of Ericsson Hewlett-Packard Telecommunications AB,
//      Sweden.  The program(s) may be used and/or copied with the
//      written permission from Ericsson Hewlett-Packard
//      Telecommunications AB or in accordance with the terms and
//      conditions stipulated in the agreement/contract under which
//      the program(s) have been supplied.

// .DESCRIPTION 
//      The CHA_ModelClient class implements the view leg of a model,
//      view, controller architecture. It is an enhancement of the
//      RWModelClient class from Tools.h++.

// DOCUMENT NO
//      190 89-CAA 134 1515

// AUTHOR 
//      1994-02-28 by EHS/PXE Jan Grape (ehsgrap@ehs.ericsson.se)

// .REVISION

// CHANGES
//      RCS revision history
//
//
//      Release revision history
//	REV NO	DATE		NAME			DESCRIPTION

// .SEE ALSO 
//      CHA_Model

//**********************************************************************

#ifndef CHA_MODELCLIENT_H
#define CHA_MODELCLIENT_H

#include <rw/ordcltn.h>

class CHA_Model;

class CHA_ModelClient : public RWCollectable
{
public:

   virtual ~CHA_ModelClient();

    virtual void updateFrom(CHA_Model* model, void* pData) = 0;
    // Description:
    //     This method is called by the CHA_Model when it notifies
    //     it's clients about an event or state change.
    //
    //     This method has to be implemented by the subclasses and
    //     sould never be called explicitly.
    // Parameters:
    //     model		a pointer to the calling model object
    //     pData		a pointer to some data regarding the update

    virtual void detachFrom(CHA_Model* model) = 0;
    // Description:
    //     This method is called by the CHA_Model when it no longer
    //     can update it's clients. The most common case is that the
    //     model object is being destructed.
    //
    //     This method has to be implemented by the subclasses and
    //     sould never be called explicitly from anything other than
    //     a CHA_Model object.
    // Parameters:
    //     model		a pointer to the calling model object

  void addToList(CHA_Model* m);
  void detachFromList(CHA_Model* m);
  void removeFromList(CHA_Model* m);

  // Allows peek at dependent list:
  const RWOrdered*      dependents() {return &dependList;}

private:
  RWOrdered             dependList;

};

#endif
