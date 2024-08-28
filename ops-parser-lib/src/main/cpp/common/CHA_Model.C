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
//#include <colme.C>

#include <CHA_Model.H>
#include <CHA_ModelClient.H>


//**********************************************************************

CHA_Model::CHA_Model()
{
}
//**********************************************************************

void CHA_Model::addDependent(CHA_ModelClient* m)
{
  dependList.append(m);
  m->addToList(this);
}
//**********************************************************************

void CHA_Model::removeDependent(CHA_ModelClient* m)
{
    if ( dependList.isEmpty() == FALSE)
    {
        if (dependList.contains(m)) {
            dependList.remove(m);
        }
        m->removeFromList(this);
    }
}
//**********************************************************************

void CHA_Model::autoRemoveDependent(CHA_ModelClient* m)
{
  if ( dependList.isEmpty() == FALSE)
    if (dependList.contains(m))
      dependList.remove(m);
}

//**********************************************************************

void CHA_Model::changed(void* pData)
{
  CHA_ModelClient* m;
  RWOrderedIterator next(dependList);
  while ((m = (CHA_ModelClient*)next())!=0) m->updateFrom(this, pData);
}
//**********************************************************************


CHA_Model::~CHA_Model()
{
    CHA_ModelClient* m;
    RWOrderedIterator next(*dependents());
    while ((m = (CHA_ModelClient*)next())!=0) m->detachFromList(this);
}


//**********************************************************************
