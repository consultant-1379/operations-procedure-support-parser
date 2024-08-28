/*------------------------------------------------------------------------------
 ********************************************************************************
 * COPYRIGHT Ericsson 2018
 *
 * The copyright to the computer program(s) herein is the property of
 * Ericsson Inc. The programs may be used and/or copied only with written
 * permission from Ericsson Inc. or in accordance with the terms and
 * conditions stipulated in the agreement/contract under which the
 * program(s) have been supplied.
 *******************************************************************************
 *----------------------------------------------------------------------------*/

#include <OZT_Pipe.H>
#include <OZT_EventHandler.H>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <rw/tools/regex.h>


//*****************************************************************************

// trace
#include <trace.H>
static std::string trace ="OZT_Pipe";

//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid =
		"@(#)rcsid:$Id: OZT_Pipe.C,v 21.0 1996/08/23 12:44:30 ehsgrap Rel $";

//*****************************************************************************

extern OZT_EventHandler *ozt_evHandlerPtr;

//*****************************************************************************

OZT_Pipe::OZT_Pipe(CHA_Pipe *chp,OZT_CmdRspBuf &cmdRspBuf,OZT_EventHandler *ozt_event):
myPipe(chp), outputTarget(cmdRspBuf),state(IDLE),chdToParent(-1){

ozt_evHandlerPtr= ozt_event;
}

OZT_Pipe::OZT_Pipe(OZT_CmdRspBuf &cmdRspBuf) :
	state(IDLE), outputTarget(cmdRspBuf), chdToParent(-1) {
	TRACE_IN(trace, OZT_Pipe, "");

	TRACE_OUT(trace, OZT_Pipe, "");
}

OZT_Pipe::~OZT_Pipe() {
}

int OZT_Pipe::readPipe(void *instance) {
	((OZT_Pipe *) instance)->readChdToParent();

	return ozt_evHandlerPtr->notify_done();
}

int OZT_Pipe::sigChdCatcher(void *instance, pid_t pid, int* stat_loc,
		struct rusage *rusage) {
	TRACE_IN(trace, sigChdCatcher, "");
	// arguments "pid" and "rusage" not used

	if (stat_loc != NULL) {
		int stat_val = *stat_loc;

		if (WIFEXITED(stat_val)) {
		  // normal termination
      TRACE_FLOW(trace, sigChdCatcher, "Normal exit");
      ((OZT_Pipe *) instance)->chdIsDead();
		} else {
      TRACE_FLOW(trace, sigChdCatcher, "Execution failed");
  		((OZT_Pipe *) instance)->executeFailed();
		}
	} else {
    TRACE_FLOW(trace, sigChdCatcher, "Execution failed (exit value == null)");
  	((OZT_Pipe *) instance)->executeFailed();
	}

	TRACE_OUT(trace, sigChdCatcher, "");
	return ozt_evHandlerPtr->notify_done();
}

void OZT_Pipe::readChdToParent() {
	TRACE_IN(trace, readChdToParent, "");
	char buf[256];
	int chares;
	static RWTRegex<char> shellName("/bin/.*sh:");
	// matches common shell names like
	//  - /bin/sh
	//  - /bin/posix/sh

	buf[0] = '\0'; // in case we never enter the while loop

	while ((chares = read(chdToParent, buf, sizeof(buf) - 1)) > 0) {
		buf[chares] = '\0'; // terminate the string
		RWCString response(buf); // to use regexp matching
		// Check if the shell failed, i.e. does the response start
		// with the shell name followed by a colon like in
		//   bin/sh: noprog:  not found
		if (shellName.index(response, size_t(0)) != RW_NPOS) {
			TRACE_IN(trace, readChdToParent, "shell failed");
			executeFailed();
		}
		outputTarget.append(response);
	}

	if (chares <= 0) {
		//Sleep 0.125 sec. before the response is checked again.
		usleep(125000);
	}
	TRACE_OUT(trace, readChdToParent, (char*) buf);
}

void OZT_Pipe::executeFailed() {
	TRACE_IN(trace, executeFailed, "state : " << state);

  ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::EXECUTE_ERR));
	isExecutionSuccessful = false;

	TRACE_OUT(trace, executeFailed, "");
}

void OZT_Pipe::chdIsDead() {
  TRACE_IN(trace, chdIsDead, "");

  // If the execution has failed already we do not want to overwrite the
  // previous value.
  if (isExecutionSuccessful) {
    ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::NO_PROBLEM));
  }

  TRACE_OUT(trace, chdIsDead, "");
}

OZT_Result OZT_Pipe::execute(const RWCString &execStr) {
	TRACE_IN(trace, execute, "execStr:" << execStr);

	OZT_Result result;

/*#ifdef __hpux
	myPipe = new CHA_Pipe("/bin/posix/sh"); // create the pipe
#endif
#ifdef sun
	myPipe = new CHA_Pipe("/bin/sh");
#endif*/
        myPipe = new CHA_Pipe("/bin/sh");
	//
	//  check if the child process went alright
	//
	if ((myPipe == 0) || (myPipe->status() != CHA_Pipe::OKAY)) { 
		delete myPipe;
		result = OZT_Result(OZT_Result::EXECUTE_ERR);
		TRACE_RETURN(trace, execute, result);
		return result;
	}      
	//
	//  set up a few variables related to the child process
	//
	pid = myPipe->pid(); // get the child's pid
	chdToParent = (int) (myPipe->getReceiveDescriptor()); // get the pipe
        parentToChild = (int) (myPipe->getSendDescriptor());	
	//
	//  set non-blocking to the pipe
	//
	int flags = fcntl(chdToParent, F_GETFL);
	fcntl(chdToParent, F_SETFL, flags | O_NONBLOCK);
	//
	//  set up this object to interact with the child
	//
	state = BUSY;
	ozt_evHandlerPtr->setIOTrigger((void *) this, OZT_Pipe::readPipe,
			chdToParent);
	ozt_evHandlerPtr->setSigChdTrigger((void *) this, pid, (int(*)(void *,
			pid_t, int *)) OZT_Pipe::sigChdCatcher);

	TRACE_FLOW(trace, execute, "cmdStr: '" << execStr << "'");
       char exitBuf[15] = {"exit $?\n"};
       write(parentToChild, execStr, strlen(execStr));
       write(parentToChild, "\n", 1);
       write(parentToChild,exitBuf,strlen(exitBuf));
/*	myPipe->send() << execStr << endl;
	myPipe->send() << "exit $?" << endl;*/

       isExecutionSuccessful = true;
	// Call waitResult with argumment connectionFlag = FALSE
  // to avoid connection check when running Unix command
	ozt_evHandlerPtr->waitResult(FALSE);
	state = IDLE;
	ozt_evHandlerPtr->unsetIOTrigger((void*) this, chdToParent);
	ozt_evHandlerPtr->unsetSigChdTrigger((void*) this, pid);

	readChdToParent(); // read anything left on the pipe
	myPipe->waitForChild();
	delete myPipe;

        result = ozt_evHandlerPtr->getResult();
	TRACE_RETURN(trace, execute, result);
	return result;
}

void OZT_Pipe::interrupt() {
	TRACE_IN(trace, interrupt, "");

	if (state == BUSY) {
		ozt_evHandlerPtr->setResult(OZT_Result(OZT_Result::INTERRUPTED));

		TRACE_FLOW(trace, interrupt, "killing child");

		kill(pid, SIGKILL);
	}

	TRACE_OUT(trace, interrupt, "");
}
