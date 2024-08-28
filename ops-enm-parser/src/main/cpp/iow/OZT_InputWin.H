//ClearCase Version Control Information
//ClearCase: @(#) syn-opsserver/server/iow/src/OZT_InputWin.H @@/main/orbix/1 2000-03-03.14:23 EHS

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

#ifndef OZT_INPUTWIN_H 
#define OZT_INPUTWIN_H

#include <OZT_IOW.H>
#include "OZT_RunTimeNLS.H"
#include "OPSS.H"

/**
 * Input popup for @INPUT and @INKEY
 *
 * @author <2000-01-01> EHS/OX/DF <Name>
 *
 * @see OtherClass
 */
class  OZT_InputWin : public OZT_InputPopup
{

public:

  /**
   * Constructor
   *
   * @param listener Listener object in client that will popup a dialog
   */
  OZT_InputWin (OPS::ServerRouterListener_ptr listener);

  /**
   * Destructor
   *
   */
  ~OZT_InputWin();

  /**
   * Show the popup and get the user input.
   *
   * @param promptMsg Prompt message, IN
   * @param defaultValue Default value at the input field, IN
   * @param usrInput Input entered by the use, OUT
   * @return A result object showing whether the input was successful.
   */
  OZT_Result getInput(RWCString promptMsg, 
                      RWCString defaultValue,
		      RWBoolean toFormat,
                      RWCString &usrInput);
 
  /**
   * Interrupt the user input.
   *
   */
  void interrupt();

  OZT_Result setTimeout( const OZT_Value& label,
			 const OZT_Value& time,
			 const OZT_Value& unit );

  RWCString getTimeoutLabel();

  void resetTimeout();

protected:
  enum TimeUnit { Second, Minute, Hour };
  enum State       {BUSY, IDLE};
  State            state_;

private:
  RWCString      defaultPrompt_;
  OPS::ServerRouterListener_ptr listener_;
  OPS::ClientType clientType_;
  CHA_NLSCatalog nlsFile_;
  RWCString timeoutLabel_;
  long timeoutTime_;
};


#endif
