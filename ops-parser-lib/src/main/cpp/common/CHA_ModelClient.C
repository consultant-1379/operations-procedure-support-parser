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

#include <CHA_Model.H>
#include <CHA_ModelClient.H>


//**********************************************************************

void CHA_ModelClient::addToList(CHA_Model* m)
{
  dependList.append(m);
}

//**********************************************************************

void CHA_ModelClient::removeFromList(CHA_Model* m)
{
  if ( dependList.isEmpty() == FALSE)
    if (dependList.contains(m))
      dependList.remove(m);
}

//**********************************************************************

void CHA_ModelClient::detachFromList(CHA_Model* m)
{
  removeFromList(m);
  detachFrom(m);
}
//**********************************************************************


CHA_ModelClient::~CHA_ModelClient()
{
    CHA_Model* m;
    RWOrderedIterator next(*dependents());
    while ((m = (CHA_Model*)next())!=0) m->autoRemoveDependent(this);
}


//**********************************************************************
