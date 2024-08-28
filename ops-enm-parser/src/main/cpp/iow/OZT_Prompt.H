//ClearCase Version Control Information
//ClearCase: @(#) syn-opsserver/server/iow/src/OZT_Prompt.H @@/main/orbix/1 2000-03-03.14:24 EHS

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

#ifndef OZT_PROMPT_H
#define OZT_PROMPT_H

#include <OZT_IOW.H>
#include "OZT_RunTimeNLS.H"
#include "OPSS.H"

/**
 * Prompt object for @PROMPT
 *
 * @author <2000-01-01> EHS/OX/DF <Name>
 *
 * @see OtherClass
 */
class OZT_Prompt : public OZT_PromptNotice
{

public:

  /**
   * Constructor.
   *
   */
  OZT_Prompt(OPS::ServerRouterListener_ptr listener);

  /**
   * Destructor.
   *
   */
  ~OZT_Prompt();

  /**
   * Prompts the user for whether to continue or not.
   *
   * @return TO_CONTINUE     The user choose to continue
   *         TO_STOP         The user choose to stop
   *         TO_STOP_N_QUIT  The user choose to stop and quit
   */
  OZT_Prompt::Answer askContinue();


  OZT_Result setTimeout( const OZT_Value& label,
			 const OZT_Value& time,
			 const OZT_Value& unit );

  RWCString getTimeoutLabel();

  void resetTimeout();

private:
  enum TimeUnit { Second, Minute, Hour };
  RWCString timeoutLabel_;
  long timeoutTime_;
  OPS::ServerRouterListener_ptr listener_;
  CHA_NLSCatalog nlsFile_;
};

#endif
