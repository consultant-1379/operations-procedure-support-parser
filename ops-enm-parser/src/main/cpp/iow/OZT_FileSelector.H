//ClearCase Version Control Information
//ClearCase: @(#) syn-opsserver/server/iow/src/OZT_FileSelector.H @@/main/orbix/1 2000-03-03.14:18 EHS

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

#ifndef OZT_FILE_SELECTOR_H 
#define OZT_FILE_SELECTOR_H

#include <OZT_IOW.H>
#include <OPSS.H>

/**
 * Selector object for SELFILE()
 *
 * @author <2000-02-24> EHS/OX/DF <Name>
 *
 */
class  OZT_FileSelector : public OZT_FileSelectPopup
{

public:

  /**
   * Constructor
   *
   * @param listener Listener object in client that will popup a dialog
   */
  OZT_FileSelector(OPS::ServerRouterListener_ptr listener);

  /**
   * Destructor
   *
   */
  ~OZT_FileSelector();

  /**
   * Prompts the user to select a file.
   *
   * @param mask       A mask for filtering files, IN
   * @param promptMsg  Message to be displayed when the user is prompted, IN
   * @param usrInput   Absolute path name of the user input, OUT
   * @return OZT_Result(NO_PROBLEM) or
   *         OZT_Result(USER_INTERRUPTED)
   */
  OZT_Result selFile(const RWCString &mask, 
                     const RWCString &promptMsg,
                     RWCString &usrInput);

  /**
   * Interrupts the user input
   *
   */
  void interrupt();

protected:

private:
    enum State {IDLE, BUSY};
    State state_;
    OPS::ClientType listenerType_;
    OPS::ServerRouterListener_ptr listener_;
};

#endif
