/*------------------------------------------------------------------------------
 *******************************************************************************
 * COPYRIGHT Ericsson 2018
 *
 * The copyright to the computer program(s) herein is the property of
 * Ericsson Inc. The programs may be used and/or copied only with written
 * permission from Ericsson Inc. or in accordance with the terms and
 * conditions stipulated in the agreement/contract under which the
 * program(s) have been supplied.
 *******************************************************************************
 *----------------------------------------------------------------------------*/

#ifndef CHA_MODEL_H
#define CHA_MODEL_H


#include <rw/ordcltn.h>
#include <CHA_ModelClient.H>

class CHA_Model : public RWCollectable
{
public:
    virtual ~CHA_Model();
    // Description:
    //     Destructor. Will call CHA_ModelClient::detachFrom(this)
    //     on all it's CHA_ModelClient:s.

  CHA_Model();
  virtual void addDependent(CHA_ModelClient*);
  virtual void removeDependent(CHA_ModelClient*);
  void autoRemoveDependent(CHA_ModelClient*);

  // Allows peek at dependent list:
  const RWOrdered*      dependents() {return &dependList;}
  virtual void          changed(void* pData = 0);       // Notify all dependents
private:
  RWOrdered             dependList;
};

#endif

