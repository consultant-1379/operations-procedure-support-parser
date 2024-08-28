//ClearCase Version Control Information
//ClearCase: @(#) syn-opsserver/server/servermain/src/VariableWatcher.H @@/main/orbix/1 2000-03-03.14:12 EHS

// ---------------------------------------------------------------------
// 
//  COPYRIGHT EHPT Sweden AB 2000.
//  All rights reserved.
//
//  The Copyright to the computer program(s) herein is the property of
//  EHPT Sweden AB.
//  The program(s) may be used and/or copied only with the written
//  permission from EHPT Sweden AB or in accordance with the terms and
//  conditions stipulated in the  agreement/contract under which the
//  program(s) have been supplied.
//
// ---------------------------------------------------------------------

#ifndef VARIABLEWATCHER_H 
#define VARIABLEWATCHER_H

#include <OZT_VarStore.H>
#include <OZT_SourceMgr.H>
#include <CHA_ModelClient.H>
#include <OPSC.H>

/**
 * This class is used to receive notifications when a variable value has changed. It then
 * notifies the GUI via the IDL interface.
 *
 * @author <2000-02-081> EHS/OX/DF Anders Ahlström
 *
 * @see OtherClass
 */
class  VariableWatcher
: public CHA_ModelClient
{

public:
      
  /**
   * Constructor
   *
   * @param smgr source manager, IN
   * @param listener listener object used for CORBA calls, IN
   */
  VariableWatcher(OZT_SourceMgr *smgr, OPS::ServerRouterListener *listener);
  
  /**
   * Destructor.
   *
   */
  ~VariableWatcher();

  void setListener(OPS::ServerRouterListener_ptr listener);
    // Description
    //     Used to set the listener pointer to the correct GUI when a GUI
    //     takes over a session previously owned by a crashed GUI.
  
private: 

  /**
   * The source manager
   */
  OZT_SourceMgr    *sourceMgr_;

  /**
   * The listener object
   */
  OPS::ServerRouterListener    *listener_;

  /**
   * This method is called when the observed model has changed.
   *
   * @param pModel The observed model, IN
   * @param pData Data passed from the observed model, IN
   */
  void updateFrom(CHA_Model* pModel, void* pData);

  /**
   * This method is called when the model no longer can update it's clients
   *
   * @param pModel The observed model, IN
   */
  void detachFrom(CHA_Model* model);
};

#endif
