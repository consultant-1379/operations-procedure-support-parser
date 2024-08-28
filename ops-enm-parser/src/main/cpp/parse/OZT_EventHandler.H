#ifndef OZT_EVENT_HANDLER_H
#define OZT_EVENT_HANDLER_H

#include <CHA_EventHandler.H>
#include <OZT_ErrHandling.H>
#include <rw/defs.h>
#include <rw/tpordvec.h>
#include <OZT_Time.H>
#include <sys/wait.h>
#include <unistd.h>

//*********************************************************

// types of event clients that can be registered

enum OZT_ClientType {
         OZT_IO_CLIENT,   // clients interested in file IO activity
         OZT_CHD_CLIENT,  // clients interested in SIGCHLD
         OZT_TICK_CLIENT, // clients interested to be called regularly
         OZT_TIMER_CLIENT,// clients interested to be called at specified time
         OZT_GUI_CLIENT   // events queued by the gui
     };

//*********************************************************

// generic client record type

class OZT_Client {
public:
    OZT_Client();
    // Description
    //     Constructor.

    ~OZT_Client();
    // Description
    //     Destructor.

    virtual OZT_ClientType type() const = 0;
    // Description
    //     Type of the client.

    virtual RWBoolean operator==(const OZT_Client &client) const = 0;
    // Description
    //     Equality operator.

    virtual void dispatch();
    // Description
    //     Dispatch the callback registered for this client.

    virtual void markToTrash();
    // Description
    //
    virtual RWBoolean isValid() const;
    // Description
    //     Check if this client registered is still valid.

    virtual RWBoolean toBeTrashed() const;
    // Description
    //     Mark this client record so that this record will be
    //     removed later on.

    virtual void *getInstance() const;
    // Description
    //     Get hold of the instance pointer kept inside the record.

protected:
    void          *instance;
    int          (*func)(void *);
    RWBoolean     trashed;
};

//*********************************************************

class OZT_IOClient: public OZT_Client {
public:
    OZT_IOClient(void *instance,
                 int (*func)(void*),
                 int fd);
    // Description
    //     Constructor.
    // Parameter
    //     instance   IN: a void pointer that will be passed to "func"
    //                    when the event is dispatched.
    //     func       IN: a callback that will be invoked when the
    //                    event is dispatched.
    //     fd         IN: a file descriptior that the client is interested.

    ~OZT_IOClient();
    // Description
    //     Destructor.

    RWBoolean operator==(const OZT_Client &client) const;
    // Description
    //     Equality operator.

    OZT_ClientType type() const;
    // Description
    //     Returns the type of this client which is OZT_IO_CLIENT.

    int fd;  // the file descriptor that this client is interested in
};


//*********************************************************

class OZT_TimerClient: public OZT_Client {
public:
    OZT_TimerClient(void *instance,
                    int (*func)(void *),
                    unsigned long secs);
    // Description
    //     Constructor.
    // Parameters
    //     instance     IN: a void pointer that will be passed to "func"
    //                      when the time event is dispatched.
    //     func         IN: a callback that will be invoked when the
    //                      time event is dispatched.
    //     secs         IN: number of seconds to wait before the event
    //                      should be dispatched.

    ~OZT_TimerClient();
    // Description
    //     Destructor.

    RWBoolean      isExpired() const;
    // Description
    //     Checks if the time has expired for dispatching the time event
    //     for this client.

    RWBoolean operator==(const OZT_Client &client) const;
    // Description
    //     Equality operator.

    OZT_ClientType type() const;
    // Description
    //     Returns the type of this client which is OZT_TIMER_CLIENT.

protected:
    OZT_Time timeToExpire;
};

//*********************************************************

class OZT_TickClient: public OZT_Client {
public:
    OZT_TickClient(void *instance, int (*func)(void *));
    // Description
    //     Constructor.
    // Parameters
    //     instance    IN: a void pointer that will be passed to "func"
    //                     when it is called.
    //     func        IN: the callback for this client.

    ~OZT_TickClient();
    // Description
    //     Destructor.

    RWBoolean       operator==(const OZT_Client &client) const;
    // Description
    //     Equality operator.

    OZT_ClientType  type() const;
    // Description
    //     Returns the type of this client which is OZT_TICK_CLIENT.
};

//*********************************************************

class OZT_ChdClient: public OZT_Client {
public:
    OZT_ChdClient(void *instance,
                  int (*func)(void *,pid_t,int *),
                  pid_t pid);
    // Description
    //     Constructor.
    // Paramaters
    //     instance    IN: a void pointer that will be passed to "func"
    //                     when it is called.
    //     func        IN: the callback for this client.
    //     pid         IN: the process id that the client is interested in
    //                     its death.

    ~OZT_ChdClient();
    // Description
    //     Destructor.

    OZT_ClientType type() const;
    // Description
    //     Returns the type of this client which is OZT_CHD_CLIENT.

    RWBoolean      operator==(const OZT_Client &client) const;
    // Description
    //     Equality operator.

    void dispatchSignalEvent(int *stat);
    // Description
    //     Dispatch the callback registered for this client.

    pid_t pid;   // identity of the process that this client is interested in.
    int          (*function)(void *,pid_t,int *);
};

//*********************************************************

class OZT_EventHandler: public CHA_EventHandler {

public:
    OZT_EventHandler();
    // Description
    //     Constructor.


    virtual ~OZT_EventHandler();
    // Description
    //     Destructor.


    virtual int notify_done() const;
    // Description
    //     Legacy of Xview...


    virtual void startDispatch();
    // Description
    //     Starts dispatching events.


    virtual void stopDispatch();
    // Description
    //     Stops dispatching events.


    virtual OZT_Result waitResult(RWBoolean checkFlag = TRUE);
    // Description
    //     Starts dispatching events.
    //
    // Return value
    //     A result object that is passed to OZT_EventHandler::setResult()
    //     which stops event dispatching.


    virtual void setResult(OZT_Result result);
    // Description
    //     Stops event dispatching.
    // Parameter
    //     result    IN: a result object that is to return to the caller
    //                   which starts event dispatching.

    virtual OZT_Result getResult() {return result;};
    // Description
    //     Return result.
    // Return value
    //     The result of the execution.

    virtual void setIOTrigger(void *instance, int (*func)(void *), int fd);
    // Description
    //     Register a callback for IO activity.
    // Parameter
    //     instance    IN: a void pointer that will be passed to "func"
    //                     which there is any IO activity on the file
    //                     descriptor "fd".
    //     func        IN: the callback function that will be called if
    //                     there is any activity on "fd".
    //     fd          IN: a descriptor for a file to be monitored.


    virtual void unsetIOTrigger(void *instance, int fd);
    // Description
    //     Un-register a callback set previously by setIOTrigger().
    // Parameter
    //     instance IN: the void pointer passed previously to setIOTrigger().
    //     fd       IN: the file descriptor passed previously to setIOTrigger().


    virtual void setSigChdTrigger(void *instance,
                                  pid_t pid,
                                  int (*func)(void *,pid_t,int *) = 0);
    // Description
    //     Register a callback that will be called when the process with
    //     identity "pid" is dead.
    // Parameter
    //     instance    IN: a void pointer that will be passed to "func"
    //                     when the function is called.
    //     pid         IN: when the process with identity "pid" dies, "func"
    //                     will be called.
    //     func        IN: the callback to be registered. If not provided,
    //                     the event handler will still remove the zombie
    //                     process left.


    virtual void unsetSigChdTrigger(void *instance, pid_t pid);
    // Description
    //     Unregister a callback set previously by setSigChdTrigger().
    // Parameter
    //     instance   IN: the void pointer passed previously during setting.
    //     pid        IN: the process identity that passed previously
    //                    during setting.


    virtual void setTimer(void *instance, int (*func)(void *), long secs);
    // Description
    //     Register a callback that will be called when a specified number
    //     of seconds is expired.
    // Parameter
    //     instance   IN: a void pointer that will be passed to "func"
    //                    when the function is called.
    //     func       IN: the callback function to be registered.
    //     secs       IN: the seconds to wait before dispatching the callback.


    virtual void unsetTimer(void *instance);
    // Description
    //     Un-register the callback set previously by setTimer().
    // Parameter
    //     instance   IN: the void pointer passed previously to setTimer().


    virtual void setTickTrigger(void *instance, int (*func)(void *));
    // Description
    //     Register a callback which will be called periodically.
    // Parameter
    //     instance   IN: a void pointer that will be passed to "func"
    //                    when the function is called.
    //     func       IN: the callback function to be registered.


    virtual void unsetTickTrigger(void *instance);
    // Description
    //     Un-register the callback set previously by setTickTrigger().
    // Parameter
    //     instance   IN: the void pointer passed previously to setTickTrigger()


    virtual void dispatchEvents();
    // Description
    //     Dispatch any events that are due to dispatch.

    virtual void sleepAWhile();
    // Description
    //     Sleep for a while. Safe to call even in Xview application.

protected:
    virtual void dispatchIOEvents();
    // Description
    //     Dispatch the IO callbacks that are due to be dispatched.

    virtual void dispatchTimerEvents();
    // Description
    //     Dispatch the timer callbacks that are due to be dispatched.

    virtual void dispatchTickEvents();
    // Description
    //     Dispatch any tick callbacks registered.

    virtual void dispatchChdEvents();
    // Description
    //     Dispatch any sigchld callbacks registered.

    virtual void removeTrashedClients();
    // Description
    //     Remove any client records that are no longer valid.

    //
    //  vectors of different client records
    //
    RWTPtrOrderedVector<OZT_IOClient>      ioClients;
    RWTPtrOrderedVector<OZT_ChdClient>     chdClients;
    RWTPtrOrderedVector<OZT_TimerClient>   timerClients;
    RWTPtrOrderedVector<OZT_TickClient>    tickClients;

    OZT_Result result;   // the result to be passed back to waitResult()
    RWBoolean  getOut;   // Set to TRUE to make event dispatching stops at once

private:

    static  int defaultSigChdCallBack(void *instance,pid_t,int *);
    //
    // Description:
    //     Default callback used to receive notification when a child
    //     process terminates.
};

#endif
