//ClearCase Version Control Information
//ClearCase: @(#) syn-opsserver/server/iow/src/OZT_InkeyWin.H @@/main/orbix/1 2000-03-03.14:22 EHS

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

#ifndef OZT_INKEYWIN_H 
#define OZT_INKEYWIN_H

#include <OZT_IOW.H>
#include "OPSS.H"




/**
 * Input popup for @INKEY
 *
 * @author <2000-02-21> EHS/OX/DF Anders Ahlstr�m
 *
 */
class  OZT_InkeyWin : public OZT_InputPopup
{

public:

  /**
   * Constructor
   *
   * @param listener Listener object in client that will popup a dialog
   */
  OZT_InkeyWin (OPS::ServerRouterListener_ptr listener);

  /**
   * Destructor
   *
   */
  ~OZT_InkeyWin();

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
  enum State       {BUSY, IDLE};
  enum TimeUnit { Second, Minute, Hour };
  State            state_;

private:
    RWCString timeoutLabel_;
    long timeoutTime_;
    OPS::ClientType clientType_;
    RWCString      defaultPrompt1_;
    RWCString      defaultPrompt2_;
    OPS::ServerRouterListener_ptr listener_;
    CHA_NLSCatalog nlsFile_;
};


#endif
