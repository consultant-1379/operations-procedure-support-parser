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

#ifndef OZT_CLOCK_H
#define OZT_CLOCK_H

#include <OPSS.H>
#include <CHA_Model.H>
#include <rw/cstring.h>
#include <iostream>
#include <OZT_ErrHandling.H>
#include <OZT_Value.H>
#include <OZT_Time.H>
#include <OZT_CmdSender.H>

class OZT_Clock: public CHA_Model {
public:
    OZT_Clock(OPS::ServerRouterListener_ptr listener, OZT_CmdSender &cmdSender);
    // Description
    //     Constructor.
    // Parameter
    //     theIndicator    IN: the indicator object for showing the
    //                         progress of the @DELAY of @DELAYSEC.

    ~OZT_Clock();
    // Description
    //     Destructor.

    void shutdown();
    // Description
    //     This function makes the delay terminates immediately and
    //     does not inform the client about time info.

    OZT_Result delay(const OZT_Value &mins);
    // Description
    //     Starts delaying for a specified number of minutes. This function
    //     does not return until the delay completes or OZT_Clock::interrupt()
    //     is called. Event dispatching is possible inside this object via
    //     OZT_EventHandler.
    // Parameter
    //     mins      IN: the number of minutes to delay.
    // Return value
    //     A result object telling whether the @delay was completed
    //     successfully.

    OZT_Result delaySec(const OZT_Value &secs);
    // Description
    //     Starts delaying for a specified number of seconds. This function
    //     does not return until the delay completes or OZT_Clock::interrupt()
    //     is called. Event dispatching is possible inside this object via
    //     OZT_EventHandler.
    // Parameter
    //     secs      IN: the number of seconds to delay.
    // Return value
    //     A result object telling whether the @DELAYSEC was completed
    //     successfully.

    void interrupt();
    // Description
    //     To be called while OZT_Clock::delay() or OZT_Clock::delaysec()
    //     is executing. (Which is possible because event dispatching
    //     happens inside the delay functions.) This function makes
    //     the delay terminates immediately.

    void setDelayInterrupt(RWBoolean state);

    static int tick(void *instance);
    // Description
    //     Not for public use. This function will be triggered periodically
    //     while a delay is progressing.

    void test();
    // Description
    //     For testing purpose only.

    void setListener(OPS::ServerRouterListener_ptr listener);
    // Description
    //     Used to set the listener pointer to the correct GUI when a GUI
    //     takes over a session previously owned by a crashed GUI.

    void setClientType(OPS::ClientType type);
    // Description
    //     Used to set the client type, GUI or NUI
    //     ShowTimeInfo will be sent only if vlient type is GUI

private:
    enum State {IDLE, BUSY};
    void       startDelay(long secs);
    void       aTick();
    State      state;

    RWBoolean  informClient;

    OZT_Time   originalStartTime;
    OZT_CmdSender &commandSender;
    long       secsForDelay;

    OPS::ServerRouterListener_ptr listener;
    OPS::ClientType  clientType;
    RWBoolean  delayInterrupted;

    // NLS stuff
    RWCString  timeToDelayMsg;
    RWCString  minsMsg;
    RWCString  secsMsg;
};

#endif
