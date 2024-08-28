/*------------------------------------------------------------------------------
 ********************************************************************************
 * COPYRIGHT Ericsson 2018
 *
 * The copyright to the computer program(s) herein is the property of
 * Ericsson Inc. The programs may be used and/or copied only with written
 * permission from Ericsson Inc. or in accordance with the terms and
 * conditions stipulated in the agreement/contract under which the
 * program(s) have been supplied.
 ********************************************************************************
 *----------------------------------------------------------------------------*/

#ifndef OZT_PIPE_H
#define OZT_PIPE_H

#include <OZT_EventHandler.H>
#include <CHA_Pipe.H>
#include <OZT_ErrHandling.H>
#include <OZT_CmdRspBuf.H>
#include <sys/wait.h>



class OZT_Pipe {
public:
    enum State {IDLE, BUSY};

    OZT_Pipe(OZT_CmdRspBuf& cmdRspBuf);
    // Description
    //     Constructor
    // Parameter
    //     cmdRspBuf   IN: reference to OZT_CmdRspBuf. This is used
    //                     to deliver output from the external program
    //                     executed.
    OZT_Pipe(CHA_Pipe *cha_pipe,OZT_CmdRspBuf& cmdRspBuf,OZT_EventHandler *ozt_event);

    ~OZT_Pipe();
    // Description
    //     Destructor


    OZT_Result execute(const RWCString& execStr);
    // Description
    //     Execute the command string with a new shell.
    // Parameter
    //     execStr    IN: the string to be executed.
    // Return value
    //     A result object about whether the external program can be
    //     executed.


    void interrupt();
    // Description
    //     Interrupt the command being executed by the posix shell. Calling
    //     this will result in a SIGTERM to be sent to the posix shell.


private:

    static int sigChdCatcher(void* instance,
                             pid_t pid = 0,
                             int* stat_loc = 0,
                             struct rusage *rusage = 0);

    static int readPipe(void* instance);

    void        chdIsDead();
    void        executeFailed();
    void        readChdToParent();

    CHA_Pipe*      myPipe;
    OZT_CmdRspBuf& outputTarget;
    pid_t          pid;
    int            chdToParent;
    int		   parentToChild; 
    State          state;
    bool           isExecutionSuccessful;
};

#endif
