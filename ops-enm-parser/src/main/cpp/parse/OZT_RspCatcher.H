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

#ifndef OZT_RSP_CATCHER_H
#define OZT_RSP_CATCHER_H

#define RESPONSE_CHECK_INTERVAL 1

#include <OZT_ErrHandling.H>
#include <OZT_Value.H>
#include <OZT_CmdRspBuf.H>
#include <OZT_Indicator.H>
#include <CHA_ModelClient.H>
#include <CHA_Model.H>
#include <OZT_CmdSender.H>

class OZT_RspCatcher: public CHA_ModelClient, public CHA_Model {
public:
    enum State {IDLE, WAITFOR, WAITREPLY};

    OZT_RspCatcher(OPS::ServerRouterListener_ptr listener, OZT_CmdRspBuf &theCmdRspBuf, OZT_Indicator &theIndicator, OZT_CmdSender &theCmdSender);
    // Description
    //     Constructor
    // Parameters
    //     theCmdRspBuf    IN: reference to the command response buffer
    //     theIndicator    IN: reference to the indicator object for showing
    //                         progress.


    ~OZT_RspCatcher();
    // Description
    //     Destructor

    OZT_Result waitFor(const OZT_Value &str1,
                       const OZT_Value &str2,
                       const RWBoolean indefinite,
                       const OZT_Value &secs);
    // Description
    //     Starts to wait for some strings for a specified period.
    // Parameters
    //     str1         IN: the first string to be waited for.
    //     str2         IN: the second string to be waited for.
    //     indefinite   IN: if TRUE, the wait will not time-out
    //     secs         IN: number of seconds to wait for. Ignored if
    //                      "indefinite" is TRUE.
    // Return value
    //     A result object about the wait.


    void setOKReply(const RWCString &str);
    // Description
    //     Sets the OK string for @SETREPLY command. If the string specified
    //     can be found in the buffer from the search back point, it is
    //     considered to have received a complete response.
    // Parameters
    //     str   IN: the OK string
    

    void setFailReply(const RWCString &str);
    // Description
    //     Sets the FAIL string for @SETREPLY command. If the string specified
    //     can be found in the buffer from the search back point, it is
    //     considered to have received a fail response.
    // Parameters
    //     str   IN: the FAIL string
    

    OZT_Result waitReply(const RWBoolean indefinite,
                         const OZT_Value &secs);
    // Description
    //     Starts to wait for a complete reply.
    // Parameters
    //     indefinite   IN: if TRUE, there won't be a time-out.
    //     secs         IN: the number of seconds to wait, ignored if
    //                      "indefinite" is TRUE.


    void interrupt();
    // Description
    //     Interrupts the wait that is currently executing.
 

#if TPF >= 400  
    virtual void updateFrom(CHA_Model* pModel, void*);
#else
    virtual void updateFrom(RWModel* pModel, void*);
#endif
    // Description
    //     

    virtual void detachFrom(CHA_Model* pModel);
    // Description
    //     

  State getState();

  void setListener(OPS::ServerRouterListener_ptr listener);
  // Description
  //     Used to set the listener pointer to the correct GUI when a GUI
  //     takes over a session previously owned by a crashed GUI.
private:
    static int timeOutCallBack(void *instance);
    OZT_Result waitReplyCheck();
    void timeOut();
    void changeState(const State newState);
    RWCString printState(const State theState);

    OZT_Indicator &indicator;
    OZT_CmdRspBuf &cmdRspBuf;
    OZT_CmdSender &cmdSender;
    RWCString      okReply;
    RWCString      failReply;
    RWCString      expectedStr1;
    RWCString      expectedStr2;
    State          state;
    OPS::ServerRouterListener_ptr listener;
};

#endif
