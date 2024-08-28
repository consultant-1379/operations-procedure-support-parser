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

#include <CHA_Pipe.H>
//#include <CHA_Trace.H>

#ifdef SunOS5
#include <sys/types.h>		// waitpid()
#endif

#include <errno.h>
#include <sys/wait.h>		// waitpid()
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <fstream>

#include <rw/cstring.h>
#include <rw/ctoken.h>


//**********************************************************************

#include <trace.H>
static std::string trace ="CHA_Pipe";


//**********************************************************************


CHA_Pipe::CHA_Pipe(const RWCString& cmdStr, RWBoolean doDetach)
: rcvStream(NULL),
  sendStream(NULL),
  pipeStatus(NO_CHILD),
  procId(-1)
{
    TRACE_IN(trace, CHA_Pipe, cmdStr);

    char** argv = argVec(cmdStr);
    initPipe(argv, doDetach);

    deleteArgVec(argv);

}


//**********************************************************************


CHA_Pipe::CHA_Pipe(char *const argv[], RWBoolean doDetach)
: rcvStream(NULL),
  sendStream(NULL),
  pipeStatus(NO_CHILD),
  procId(-1)
{
    TRACE_IN(trace, CHA_Pipe, argv[0]);

    initPipe(argv, doDetach);

}

//**********************************************************************

void CHA_Pipe::initPipe(char *const argv[], RWBoolean doDetach)
{
    TRACE_IN(trace, initPipe, "");
    // a connection (pipe) from child to parent
    pipe(childToParent);

    // a connection (pipe) from parent to child
    pipe(parentToChild);

    procId = fork();			// split process in two
    switch(procId)			// check result
    {
	case -1:			// fork failed, in PARENT
	    TRACE_FLOW(trace, initPipe, "fork failed");
	    pipeStatus = NOFORK;
	    ::close(childToParent[0]);
	    ::close(childToParent[1]);
	    ::close(parentToChild[0]);
	    ::close(parentToChild[1]);
	    break;
	
	case  0:			// in CHILD
	{
	    // detach this process, if required in the contructor
	    if(doDetach)
		setsid();

	    // close "wrong ends" of pipes
	    ::close(childToParent[0]);
	    ::close(parentToChild[1]);
	    
	    // connect to stdin and stdout
	    dup2(childToParent[1], 2); // make this pipe stderr (cerr)
	    dup2(childToParent[1], 1); // make this pipe stdout (cout)
	    dup2(parentToChild[0], 0); // make this pipe stdin (cin)

	    TRACE_FLOW(trace, initPipe, argv[0] << ": in CHILD before execvp");
            execvp(argv[0], (char* const*)argv);

	    // if this is executed, exevp failed
	    TRACE_FLOW(trace, initPipe, "Could not exec!");
	    exit(17);
	}
	
	default:			// in PARENT
	    TRACE_FLOW(trace, initPipe, "in PARENT after fork");
	    // close "wrong ends" of pipes
	    ::close(childToParent[1]);
	    ::close(parentToChild[0]);

	    // connect pipes to my streams
	    rcvStream = new std::ifstream((char *)childToParent[0]);
	    sendStream = new std::ofstream((char *)parentToChild[1]);

	    // child is running
	    pipeStatus = OKAY;
	    break;
    }
}


//*********************************************************************


CHA_Pipe::~CHA_Pipe()
{
    CHA_Pipe::closeSending();
    CHA_Pipe::closeReceiving();
}


//*********************************************************************

void CHA_Pipe::closeReceiving()
{
    TRACE_IN(trace, closeReceiving, "");

    if(rcvStream != NULL)
    {
	rcvStream->close();
	delete rcvStream;
	rcvStream = NULL;
	::close(childToParent[0]);
    }
}

//*********************************************************************


void CHA_Pipe::closeSending()
{
    TRACE_IN(trace, closeSending, "");

    if(sendStream != NULL)
    {
	sendStream->flush();
	sendStream->close();
	delete sendStream;
	sendStream = NULL;
	::close(parentToChild[1]);	// just to be on the safe side
    }

    if(pipeStatus == OKAY)
	pipeStatus = CLOSED;
}


//*********************************************************************


CHA_Pipe::PipeStatus CHA_Pipe::waitForChild()
{
    TRACE_IN(trace, waitForChild, "");
    if((pipeStatus == OKAY) || (pipeStatus == CLOSED))
    {
	int* stat_loc = NULL;
	pid_t resultPid;
	do 
	{
	    resultPid = waitpid(procId, stat_loc, 0);
	} while((resultPid == -1) && (errno == EINTR));

	if(resultPid == procId)
	    pipeStatus = TERMINATED;
    }

    TRACE_RETURN(trace, waitForChild, pipeStatus);
    return pipeStatus;
}    


//*********************************************************************


CHA_Pipe::PipeStatus CHA_Pipe::status()
{
    if((pipeStatus == OKAY) || (pipeStatus == CLOSED))
    {
	int* stat_loc = NULL;
	pid_t resultPid;
	do
	{
	    resultPid = waitpid(procId, stat_loc, WNOHANG);
	} while((resultPid == -1) && (errno == EINTR));

	if(resultPid == procId)
	    pipeStatus = TERMINATED;
    }

    TRACE_RETURN(trace, status, pipeStatus);
    return pipeStatus;
}


//*********************************************************************


pid_t CHA_Pipe::pid() const
{
    TRACE_RETURN(trace, pid, procId);
    return procId;
}


//*********************************************************************


std::istream& CHA_Pipe::receive()
{
    TRACE_RETURN(trace, receive, rcvStream);
    return *rcvStream;
}


//*********************************************************************


std::ostream& CHA_Pipe::send()
{
    TRACE_RETURN(trace, send, sendStream);

    if(sendStream != NULL)
	return *sendStream;
    else
	return std::cerr;
}


//**********************************************************************


int CHA_Pipe::getReceiveDescriptor() const
{
    TRACE_RETURN(trace, getReceiveDescriptor, childToParent[0]);
    return childToParent[0];
}

//**********************************************************************
// TORF-258985
int CHA_Pipe::getSendDescriptor() const
{
    TRACE_RETURN(trace, getReceiveDescriptor, childToParent[0]);
    return parentToChild[1];
}

//**********************************************************************


char** CHA_Pipe::argVec(const RWCString& cmdLine)
{
    // calculate the number of tokens in the command line
    int nrOfTkns = 0;
    RWCTokenizer nextTkn(cmdLine); 
    while(nextTkn().isNull() == FALSE)
    {
	nrOfTkns++;
    }

    // create an argument vector
    char** argv = new char*[nrOfTkns + 1];

    // copy each argument (token) into the vector
    RWCTokenizer nextArg(cmdLine);
    for(int i = 0; i < nrOfTkns; i++)
    {
	RWCString arg = nextArg();

	TRACE_FLOW(trace, argVec, arg);

	argv[i] = new char[arg.length() + 1];
	strcpy(argv[i], arg.data());
    }

    // terminate the vector with NULL
    argv[nrOfTkns] = NULL;

    return argv;
}


//*********************************************************************

void CHA_Pipe::deleteArgVec(char **argv)
{
    for (int i = 0; argv[i] != 0; i++)
        delete [] argv[i];

    delete [] argv;
}
