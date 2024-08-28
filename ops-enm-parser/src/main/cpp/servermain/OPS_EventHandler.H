//ClearCase Version Control Information
//ClearCase: @(#) syn-opsserver/server/servermain/src/OPS_EventHandler.H @@/main/2 2000-04-27.13:04 EHS

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

#ifndef OPS_EVENT_HANDLER_H
#define OPS_EVENT_HANDLER_H

#include <CHA_Connection.H>

#include <OZT_EventHandler.H>
#include <pthread.h>


//*********************************************************

class OPS_GuiClient: public OZT_Client {
public:
  /**
   * Constructor.
   *
   * @param instance a void pointer that will be passed to "func" when the event is
   *                 dispatched, IN
   * @param func a callback that will be invoked when the event is dispatched, IN
   * @param args arguments tp the callback, IN
   * @param cleaner a callback that will be invoked when the event is removed.
   *                Use it to clean up memory allocated for arguments, IN
   */
  OPS_GuiClient(void *instance, 
               int (*func)(void*, void*), 
               void *args,
               void (*cleaner)(void*) = NULL);

  /**
   * Destructor.
   *
   */
  ~OPS_GuiClient();

  /**
   * Returns the type of this client which is OZT_GUI_CLIENT.
   *
   */
  OZT_ClientType type() const;

  /**
   * Equality operator.
   *
   */
  RWBoolean operator==(const OZT_Client &client) const;

  /**
   * Dispatch the callback registered for this client.
   *
   */
  void dispatchGuiEvent();

  void *args;  // agrument to the function
  int  (*function)(void *,void *);
  void (*cleaner)(void *);
};


/**
 * Event handler for OPS server
 *
 * @author <2000-04-12> EHS/OX/DF Anders Ahlström
 *
 * @see OZT_EventHandler
 */
class OPS_EventHandler: public OZT_EventHandler
{
public:

  /**
   * Constructor.
   *
   */
  OPS_EventHandler();

  /**
   * Destructor.
   *
   */
  ~OPS_EventHandler();

  /**
   * Starts dispatching events until stopped by stopDispatchThread().
   *
   */
  virtual void startDispatch();

  /**
   * Starts dispatching events.
   *
   * @return a result object passed to OZT_EventHandler::setResult() for stopping
   *         the event dispatching.
   */
  virtual OZT_Result waitResult(RWBoolean checkFlag = TRUE);

  /**
   * Register a gui callback that will be called as soon as possible.
   *
   * @param instance a void pointer that will be passed to "func" when the function
   *                 is called, IN
   * @param func the callback function to be registered, IN
   * @param args arguments to the callback function, IN
   * @param cleaner the cleanup callback to be registered, IN
   */
  virtual void setGuiTrigger(void *instance,
                             int (*func)(void *, void *),
                             void *args,
                             void (*cleaner)(void *) = NULL);

  /**
   * Un-register the callback set previously by setGuiTrigger().
   *
   * @param instance the void pointer passed previously to setGuiTrigger(), IN
   */
  virtual void unsetGuiTrigger(void *instance);

  /**
   * Dispatch any events that are due to be dispatched.
   *
   */
  virtual void dispatchEvents();


  /**
   * Set pointer to the connection object, it is used before starting dispetch to check the connection.
   *
   */
   void setConnectionRef(CHA_Connection *pConnection);

  /**
   * Set status of the client, it is used before starting dispetch, dispatch will be stopped if no client exist
   *
   */
   void clientStatus(RWBoolean statusFlag);

protected:
  /**
   * Dispatch any Gui events that are due to be dispatched.
   *
   */
  virtual void dispatchGuiEvents();
  
  /**
   * Remove any client records that are no longer valid.
   *
   */
  virtual void removeTrashedClients();

  /**
   *  vectors of gui client records
   *
   */
  RWTPtrOrderedVector<OPS_GuiClient>      guiClients;

private:
  pthread_mutex_t eventMutex_;     // protect event list

  CHA_Connection *_pConnection;
  RWBoolean connCheckFlag;
  RWBoolean clientAlive;

};

#endif
