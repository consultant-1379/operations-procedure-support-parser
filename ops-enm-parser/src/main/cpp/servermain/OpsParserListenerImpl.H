// Using VisiBroker C++
// OPS Parser Implementation for Interface 'OPS::ParserListener'.  See 'OSP.idl'.
// Header file.

#ifndef OPS_PARSER_LISTENER_IMPL_H
#define OPS_PARSER_LISTENER_IMPL_H

#include <OPSS.H>
#include "RemoteFileImpl.H"
#include <shadow.h>
#include <crypt.h>



#include <CHA_Connection.H>
#include <CHA_EsList.H>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "OZT_SourceMgr.H"
#include "OZT_CDFDef.H"
#include "OZT_CDFFile.H"
#include "OZT_RunTimeNLS.H"
#include "OZT_FileSelector.H"
#include "OZT_FileViewer.H"
#include "OZT_IOWin.H"
#include "OZT_InputWin.H"
#include "OZT_InkeyWin.H"
#include "OZT_Prompt.H"
#include "OZT_ChildHandler.H"

// Local include files.
#include "VariableWatcher.H"
#include "RequestQueueHandler.H"

#include <strstream>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <fstream>


// Forward declaration(s)
class OZT_Indicator;

/**
 * This class implements the CORBA interface OPS::ParserListener (see OPS.idl).
 *
 * @author <2000-02-09> EHS/OX/DF Anders Ahsltr�m
 *
 */
class OpsParserListenerImpl : public POA_OPS::ParserListener,public CHA_ModelClient
{

public:
  /**
   * Constructor.
   *
   *
   */
  OpsParserListenerImpl(CORBA::ORB_var pOrb);

  /**
   * Destructor.
   *
   */
  ~OpsParserListenerImpl();

  //*************************************************************************************************
  //Moved from OPSServerImpl.H, R3
  /**
   * getFileViewer. Privide OPS client with the object tha implements the file viewr object.
   * @param OPS::FileView OUT
   */
  OPS::FileView_ptr getFileViewer() throw (CORBA::SystemException, OPS::OPS_Exception);

  //*************************************************************************************************
  // Moved from ParserImpl.H, R3

  /**
   * Returns a list of available external systems.
   *
   * @return List of external systems.
   */

  OPS::stringList* getExternalSystems()throw (CORBA::SystemException, OPS::OPS_Exception);
  /**
   * Connects to specified extenal system. Queues the request.
   *
   * @param esName Name of external system to connect to, IN
   */
  void connectToES(const char * esName,
                   CORBA::Boolean isStandby)
                   throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Wrapper around real method.
   *
   * @param instance pointer to the ParserImpl instance, IN
   * @param args argument to method, IN
   */
  //static int connectCallBack(void* instance, void *args);

  /**
   * Connects to specified extenal system. Does the actual connect.
   *
   * @param esName Name of external system to connect to, IN
   */
  void doConnectToES(const char * esName, RWBoolean isStandby)
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Cleans up allocated memory after connect is executed.
   *
   * @param args Pointer to memory to clean up, IN
   */
  static void cleanupAfterConnect(void *args);

  /**
   * Disconnect from the connected external system. Queues the request.
   *
   */
  void disconnectFromES()
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Wrapper around real method.
   *
   * @param instance pointer to the ParserImpl instance, IN
   * @param args argument to method, IN
   */
  static int disConnectCallBack(void* instance, void *args);

  /**
   * Disconnect from the connected external system. Does the actual disconnect.
   *
   */
  void doDisconnectFromES()
    /*                        throw (OPS::OPS_Exception)*/;

  /**
   * Sets the command file to be executed
   *
   * @param filename the name of the command file including the full directory path. IN
   */
  void setFile(const char* filename)
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Closes a file
   *
   * @param filename the name of the command file to close. IN
   */
  void closeFile(const char* filename)
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Takes one step in the command file, and executes the new line
   *
   */
  void step()
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Runs the command lines inserted in the command window
   */
  void runIncludedLines(const OPS::stringList& lines)
    throw (OPS::OPS_Exception);
  /**
   * Runs the command file, line by line, from the beginning
   *
   */
  void runFromBeginning(CORBA::Boolean updatePosition)
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Runs the command file, line by line, from the current position
   *
   */
  void runFromCurrentPosition(CORBA::Boolean updatePosition)
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Runs the command file, line by line, from the current position.
   * Only tagged lines are run.
   *
   * @param <para> <Parameter Description, IN/OUT>
   * @return <Value> <Description>
   */
  void runTaggedLines(CORBA::Boolean updatePosition)
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Interrupt the file execution.
   *
   * @return Current position.
   */
  CORBA::Long interrupt(CORBA::Boolean doReallyInterrupt)
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Breaks the command window responses
   *
   *
   */
  void breakResponse()
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Wrapper around real method.
   *
   * @param instance pointer to the ParserImpl instance, IN
   * @param args argument to method, IN
   */
  //static int interruptCallBack(void* instance, void *args);

  //static int breakResponseCallBack(void* instance, void *args);


  /**
   * Interrupt the file execution. Does the actual interrupt.
   *
   */
  void doInterrupt(RWBoolean doInterrupt);

  void doBreakResponse();

  /**
   * Quits from the parser server. Must be called before th client exits.
   *
   */
  void quit()
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Sets breakponts on the selected lines.
   *
   * @param breakpoints list of breakpoints, IN
   * @param filename name of file containing breakpoints, IN
   */
  void setBreakPoints(const OPS::longList& breakpoints,
                      const char* filename)
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Sets tags on the selected lines.
   *
   * @param tags list of tags, IN
   * @param filename name of file containing tags, IN
   * @return <Value> <Description>
   */
  void setTags(const OPS::longList& tags,
               const char* filename)
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Sets current position to the selected line.
   *
   * @param position new current position, IN
   * @return <Value> <Description>
   */
  //void setCurrentPosition(CORBA::Long position)
  // throw (CORBA::SystemException, OPS::OPS_Exception);

  void routeToFile(const char* filename)
    throw (CORBA::SystemException, OPS::OPS_Exception);

 char * getLogFile()
    throw (CORBA::SystemException, OPS::OPS_Exception);

  void routeToMail(const char* mail)
    throw (CORBA::SystemException, OPS::OPS_Exception);

  void setCurrentPosition(const char* filename,
			  CORBA::Long position)
    throw (CORBA::SystemException, OPS::OPS_Exception);

  void routeToPrinter(const char* printer)
    throw (CORBA::SystemException, OPS::OPS_Exception);

  void setCurrentLabelPosition(const char* filename,
			       const char* label)
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Gets current position
   *
   * @param fileName Name of file containing current position, OUT
   * @return Current position
   */
  OPS::Position* getCurrentPosition()
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Sets the variable value
   *
   * @param name Name of the variable, IN
   *        value Initial value IN
   */
  void setVariableValue(const char* name,
			const char* value)
    throw (CORBA::SystemException);

  /**
   * Sets the device flag value
   *
   * @param flag , IN
   */

  void setDeviceFlag(CORBA::Boolean flag)
    throw (CORBA::SystemException);

  /**
   * Gets value of the specified variable.
   *
   * @param variableName Name of the variable, IN
   * @return Variable value
   */
  char * getVariableValue(const char* variableName)
    throw (CORBA::SystemException);


  /**
   * Resets runtime data. The following data is reset:
   * Variable contents
   * Call stack
   * File stack
   * Function busy retry
   * Input Output window
   * @CHECK status
   * @ORDERED status
   * Printer
   * Log file
   * Error flag
   *
   */
  void reset()
    throw (CORBA::SystemException);

  void resetBufferMark()
    throw (CORBA::SystemException);

  /**
   * Returns a list of available printers.
   *
   * @return List of printers.
   */
  OPS::stringList *getPrinters()
    throw (CORBA::SystemException);

  /**
   * Prints a file on the selected printer.
   *
   * @param fileName Name of the file, IN
   * @param printer Name of the printer, IN
   */
  void printFile(const char* fileName,
                 const char *printer)
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Prints text on the selected printer.
   *
   * @param text Text to print, IN
   * @param printer Name of the printer, IN
   */
  void printText(const char* text,
                 const char *printer)
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Returns the central directory.
   *
   * @return central directory.
   */
  char * getCentralDir()
    throw (CORBA::SystemException);

  /**
   * Returns the session ID of the current parser session
   *
   * @Returns the session ID of the current parser session
   */
  char * getSessionID()
    throw (CORBA::SystemException, OPS::OPS_Exception);

  /**
   * Returns the private directory.
   *
   * @return private directory.
   */
  char * getPrivateDir()
    throw (CORBA::SystemException);

  /**
   * Returns the response directory.
   *
   * @return response directory.
   */
  char * getResponseDir()
    throw (CORBA::SystemException);

  //Other methods

  /**
   * Here, events from everything that inherits from CHA_Model is received.
   *
   * @param pModel The calling CHA_Model, IN
   * @param value A value sent form the CHA_Model, IN
   */
  void updateFrom(CHA_Model* pModel, void* value);

  /**
   * Called when the CHA_Model no longer can send messages.
   *
   * @param pModel The calling CHA_Model, IN
   */
  void detachFrom(CHA_Model* pModel);

  /**
   * Close a file with the name and path given.
   *
   * @param fileNumber Nuber of file in file_number, IN
   * @return TRUE if the file is closed OK, FALSE otherwise
   */
  RWBoolean close_a_file(int fileNumber);

  /**
   * Open a file with the name and path given.
   *
   * @param dir_path Path to file, IN
   * @param name Name of file, IN
   * @return TRUE if the file is opened OK, FALSE otherwise
   */
  RWBoolean open_a_file(RWCString dir_path, RWCString name);

  /**
   * Check if the parser is hanging as root or not.
   *
   * @return TRUE if setuid is done, FALSE otherwise
   */
  RWBoolean issetuiddone();

  /**
   * Make sure that the file hasn't been changed by another editor
   * and synchronize if it has.
   *
   * @param file_number File number in list of loaded files, IN
   * @param notice TBD, IN
   * @return TRUE if it is synchronized OK, FLASE otherwise
   */
  RWBoolean sync_file(int file_number, RWBoolean notice=TRUE);

  /**
   * Tell the client to show the specified line in the specified file.
   *
   * @param fullFileName Name of the file, IN
   * @param lineNo Line number in the file, IN
   */
  void show_position(RWCString fullFileName, int lineNo)
                        throw (OPS::OPS_Exception);

  /**
   * View a loaded file.
   *
   * @param fileName Name of the file, IN
   * @param notice ???, IN
   */
  RWBoolean view_file(RWCString filename, RWBoolean notice = TRUE);

  /**
   * Returns a pointer to this instance of the OPS::Parser
   * implementation class.
   * It is called from the Orbix DEREF macro (see OPS_ThreadFilter).
   */
  void* _deref() { return this; }

  /**
   * CORBA::IT_IOCallback method which is overridden by this class.
   * This method is invoked when a CORBA connection is closed.
   * A CORBA connection is closed when a client terminates or the
   * communication's level reports a break in service between the
   * server and the client.
   */
  //void OrbixFDClose( int fd );


  char * getPhaseDescription();
  /**
   * Returns a textual description of current phase. See @SETPHASE
   * and @GETPHASE.
   */

  char * getErrorDescription();
  /**
   * Returns a textual description of a possible error state.
   */

  CORBA::Long getProgress();
  /**
   * Returns the progress counter. See @SETPROGRESS, @GETPROGRESS
   * and @STEPPROGRESS.
   */

  CORBA::Long getTotalCount();
  /**
   * Returns the target for the progress counter. See @SETTOTALCOUNT
   */

  //long getLineNumber();a
  CORBA::Long getLineNumber();
  /**
   * Return number of lines
   */

  char * getCommandFileName();
  /**
   * Return current filename
   */

  void pause();
  /**
   * Pause execution
   */

  void cont();
  /**
   * Continue execution
   */

  void getExternalSystem(CORBA::String_out sEs,
                         CORBA::Boolean& isStandBy);

  /**
   * Gives client possibility to tell parser, when initialisations are ready to receive
   * callbacks. This is used when a client is connecting to an already existing parser.
   */

  //void stepProgress(long interval);
  /**
   * Steps the progress counter.
   */

  /**
   * Prepares for termination. The "ping" thread is notified to stop.
   */
  void shutdown();

  /**
   * Frees allocated memory. Called before constructor throws exception.
   */
  void cleanup();

  /**
   * Sends mail.
   */
  void sendMail(const char* sReceiver,
		const char* sSubject,
		const char* sContent
                );
  /**
   * Enables the erase of the ActivityManager job using its jobId
   */
  void setJobId(const char* jobIdString);

  /**
   * Will set the SMO user name to be used to send MML commands
   */
  void setSmoUser(const char* smoUser);

  /**
   * Will set the current display (will be used by TimeEvSet).
   */
  void setCurrentDisplay(const char* currentDisplay);

  /** Connects a new client to this parser object. */
  void connectToSession(OPS::ServerRouterListener_ptr serverRLRef,
			int sessionId,
			OPS::ClientType clientType,
			const char* userId,
			const char* pwd)
    throw(OPS::OPS_Exception);

  /** Other client to take over this session, set atcion to NOTHING to prepare for
      next action initiated by the client. */
  void clientPassive();

  /** Terminates this parser if there isn't a passive listener waiting to take over */
  void releaseParser();

  /** Lets the client check that the parser is still alive */
  void pingParser();

  CORBA::Boolean isConnected();
  CORBA::Boolean isRunning();
  CORBA::Boolean isRecoveryEnabled();
  void setRecoveryEnabled(CORBA::Boolean enabled);

  //*************************************************************************************************
  // New methods
  /**
   * ping.
   *
   */
  void ping();

  /**
   * getPid, provide ops process id.
   *
   */
 // long getPid();
    CORBA::Long getPid();

  /**
   * serverRestarting.
   * Method that is used by the OPS server to indicate that server is restarting.
   *
   */
  void serverRestarting();

  /**
   * setClientType
   * Method that is used by the OPS server to indicate type of client, GUI or NUI.
   * * @param Client typet, IN
   */
  void setClientType(OPS::ClientType type);

  /**
   * setSessionData.
   * Method that is used by the main object to set session related data.
   * @param ref to the server router listener object, IN
   * @param session id, IN
   * @param Client typet, IN
   * @param User id of the client, IN
   * @param Password to the user, IN
   */
  void setSessionData(OPS::ServerRouterListener_ptr serverRLRef_,
		      RWCString sSessionId,
		      OPS::ClientType clientType,
		      const char* userId,
		      const char* pwd);



 /**
  */
  void orbShutdown();
 /**
  */


private:

  static void* OrbShutdownThread(void* x);

  //*************************************************************************************************
  /**
   *Common code shared by runFromCurrentPosition(), runFromBeginning() and runTaggedLines():
   */
  void runCommon(OZT_Result result, 
                                        RWCString filename,
                                        LineNo line_no,
                                        LineNo num_lines,
                                        int start_file_number);
  //*************************************************************************************************
  /**
   *Fix to display the right file.
   *If the last line in the first file is @INCLUDE the file might be wrong.
   */
  void viewCorrectFile(OZT_Result result, 
                                              RWCString filename,
                                              LineNo line_no,
                                              LineNo num_lines,
                                              int start_file_number);

  //*************************************************************************************************
  // Moved from OPSServerImpl.H, R3
  pthread_t pThreadCUId_;
  const char* application_name_;
  void initDetachedThreadAttr();
  void createDetachedThread(pthread_t *thread, void *(*start)(void *));
  static void* checkSetuidThread(void* x);
  void checkSetuid();
  RWBoolean isPasswordCorrect(const char* sUser, const char* sPwd);


  //*************************************************************************************************
  // Moved from ParserImpl.H, R3
  char* ltorwcs(const long n) const;
  OZT_Result run_loop(RWCString file, RWBoolean tags_only);
  void makeUiWindows();
  RWCString getSessionId();
  void resetWindowTimeouts();
  void setErrorMessage();
  void removeJobFromAM();
  /**
   * List of External Systems
   */
  CHA_EsList esList_;
  OPS::ServerRouterListener_ptr serverRLRef_;
  RWCString            userId_;
  RWBoolean            posUpdate_;
  VariableWatcher*     variableWatcher_;
  OZT_SourceMgr*       pSourceMgr;
  OZT_Indicator*       indicator_;
  OZT_CmdRspBuf*       cmdRspBuf_;
  OZT_CommentWinModel* commentWinModel_;
  OZT_FileViewer*      fileViewer_;
  OZT_FileSelector*    fileSelector_;
  OZT_InkeyWin*        inkeyWin_;
  OZT_InputWin*        inputWin_;
  OZT_Prompt*          prompt_;
  OZT_IOWin*           ioWin_;
  RWCString            sErrorMsg_;
  RWBoolean            isPaused_;
  CHA_Connection*      connectionObject_;
  OZT_RspCatcher*      responseCatcher_;
  OZT_ChildHandler*    childHandler_;
  enum What_to_do      {NOTHING, RUN, QUIT, STOP, SET_VALUE,
			PENDING_INTERRUPTION, SET_ROUTE};
  What_to_do	action;              // Why main_loop() stopped

  int         current_position;    // Program counter, holds current line no.
  int         start_running;       // TRUE when want to start up running
  int         stopped;             // TRUE when stop or pause button pressed
  int         running;             // TRUE when a script is running.
  int         auto_quit;           // TRUE when need to quit when run stops

  OZT_CDFFile * file_entry[MAX_OPEN_FILES];
  int running_file_number;
  int view_file_number;
  int file_count;
  int cleanupFlag = 0;

  long pid;

  RWBoolean setuidDone;
  RWBoolean isClientChangeAllowed_;
  RWCString sSessionId_;
  long nJobId_;
  RWCString smoUser_;

  static void* IamAliveThread(void* x);
  pthread_t pThreadId_;
  pthread_t pOrbShutdownThreadId_;
  pthread_attr_t detachedThreadAttr;
  void IamAlive();

  CORBA::ORB_var pOrb_;

  // Added due to TR HD53556
  RWBoolean nuiIndicator_;

  int isClientOk;

  // HF65265
  OPS::ClientType clientType_;
  // END HF65265

  RWCString pwd_;
  RWBoolean shuttingDown_;
  RWBoolean shutDownInitiated_;
  pthread_mutex_t shutDownInitiatedMutex_;
  RWBoolean waitingForServerRestart_;

  static void* checkServerThread(void* x);
  pthread_t pThreadSRId_;
  void checkServer();
  void handleServerRestarted();

  void sendErrorMsg();

  RWBoolean shutdownProcessing_;
  pthread_mutex_t shutdownWaitMutex_;
  pthread_cond_t shutdownWaitObject_;
  void doShutdownProcessing();
  void signalFinishedShutdownProcessing();
  void waitForFinishedShutdownProcessing();
};

#endif //OPS_PARSER_LISTENER_IMPL_H
