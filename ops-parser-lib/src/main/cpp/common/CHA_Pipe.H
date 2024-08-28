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


#ifndef CHA_PIPE_H
#define CHA_PIPE_H

#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <rw/cstring.h>


class CHA_Pipe
{
public:

    // status codes
    enum PipeStatus { OKAY,
		      NOFORK,
		      CLOSED,
                      TERMINATED,
                      NO_CHILD};
    CHA_Pipe(){}
 
 
    CHA_Pipe(const RWCString& command, RWBoolean doDetach = FALSE);
    // Description:
    //     Constructor. Wether the constructor succeeded or not can be
    //     checked with the method status().
    // Parameters:
    //     command	The unix command to run in the child process.
    //     doDetach	Make the new process detached from this one,
    //			i.e. let it form it's own process group and
    //			become the process leader of that group.

    CHA_Pipe(char *const argv[], RWBoolean doDetach = FALSE);
    // Description:
    //     Constructor.
    // Parameters:
    //     argv         The command line argument used for starting the
    //                  new program.
    //     doDetach     If true, make the new process as group leader.

   virtual  ~CHA_Pipe();
    // Description:
    //     Destructor.

    void closeReceiving();
    // Description:
    //     Closes the pipe from the child process to the parent. It
    //     will not be possible to receive information after this.

    void closeSending();
    // Description:
    //     Closes the pipe from this process to the child process. It
    //     will not be possible to send information to the child
    //     process after this.

    PipeStatus waitForChild();
    // Description:
    //     Waits for the child process to terminate. This call blocks
    //     until the child process actually is terminated.
    // Return values:
    //     OKAY		The pipe is ok and the child process started
    //                  execution.
    //     NOFORK	The pipe is not OK because the child process
    //                  could not start.
    //     CLOSED       The sending part of the pipe is closed,
    //                  i.e. it is not possible to send information to
    //                  the sub process anymore.
    //     TERMINATED   The child has terminated.
    //     NO_CHILD     No child process exist since the pipe never
    //                  was initiated.

    virtual PipeStatus status();
    // Description:
    //     To check the status of the pipe object and it's child process.
    // Return values:
    //     OKAY		The pipe is ok and the child process started
    //                  execution.
    //     NOFORK	The pipe is not OK because the child process
    //                  could not start.
    //     CLOSED       The sending part of the pipe is closed,
    //                  i.e. it is not possible to send information to
    //                  the sub process anymore.
    //     TERMINATED   The child has terminated.
    //     NO_CHILD     No child process exist since the pipe never 
    //                  was initiated. 

    pid_t pid() const;
    // Description:
    //     To get the process ID of the child process.

    std::istream& receive();
    // Description:
    //     Provides a stream to get information (output) from the
    //     child process.

    std::ostream& send();
    // Description:
    //     Provides a stream to send information (input) to the child
    //     process. 

    int getReceiveDescriptor() const;
    //  Description:
    //     Returns the file descriptor of the incomming pipe. This is
    //     useful for setting up input functions in XView.

    int getSendDescriptor() const;
   //  Description:
   //     Returns the file descriptor of the outgoing pipe.
private:

    void initPipe(char *const argv[], RWBoolean doDetach);
    // Description:
    //     Construct a pipe.
    // Parameters:
    //     argv         IN: the command line arguments for starting the pipe.
    //     doDetach     IN: If true, make the new process as group leader.

    char** argVec(const RWCString& cmdLine);
    // Description:
    //     Creates an argument suitable for execvp from cmdLine.
    // Parameters:
    //     cmdLine	The unix command to execute.
    // Return values:
    //     The argument to pass as second argument to execvp.

    void deleteArgVec(char **argv);
    // Description:
    //     Deallocate the memory previously allocated from argVec.
    // Parameters:
    //     argv         IN: pointer to an array of arguments obtained from
    //                      CHA_Pipe::argVec().

    std::ifstream* rcvStream;		// stream from child process
    std::ofstream* sendStream;		// stream to child process

    PipeStatus pipeStatus;		// status of this object
    pid_t procId;			// child pid

    int childToParent[2];		// file descriptors
    int parentToChild[2];		// file descriptors
};

#endif
