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

#include "OpsParserListenerImpl.H"

// -Standard C++ include files.
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <grp.h>

// Tools.h++ (Rogue Wave) include files.
#include <rw/cstring.h>
#include <rw/rwfile.h>

#include <OZT_RunTimeNLS.H>
#include <CHA_NLSCatalog.H>

#include <OZT_ErrHandling.H>
#include <OZT_EventHandler.H>
#include <OZT_Time.H>
#include <OZT_Mail.H>
#include <OZT_Misc.H>
#include <OZT_SourceInfo.H>
#include <CHA_OZTInfo.H>
#include <CHA_PrinterList.H>
#include <CHA_PrinterPipe.H>

#include <CHA_EsList.H>

// Local include files.
#include "OPS_EventHandler.H"
#include "OpsParserOrbHandler.H"
#include <trace.H>
#include <signal.h>
#include <pthread.h>
#include <time.h>


#define SHUTDOWN_WAIT_TIMEOUT_IN_SECS  60


//*****************************************************************************
//
// Global variables for the interpreter
//
CHA_OZTInfo       ozt_info;
RWCString         ozt_applName("ops_server");  //nms_cif_opss
RWCString         ozt_schedTime("0");           // for GETSCHED()
RWCString         ozt_displayInfo("999.999.999.999:0.0");              // for TIMEEVSET()
RWCString         ozt_taskid("");               // for ELB logging
char nlsPath[512];
OZT_EventHandler* ozt_evHandlerPtr = NULL;
const int MAX_SESSION_ID = 12468;
//*****************************************************************************


 static std::string trace = "OpsParserListenerImpl";
//*****************************************************************************
OpsParserListenerImpl::OpsParserListenerImpl(CORBA::ORB_var pOrb):
  pOrb_(pOrb),
  action(NOTHING),
  serverRLRef_(NULL),
  //userId_(NULL),
  //pwd_(NULL),
  //sSessionId_(NULL),
  file_count(0),
  running_file_number(0),
  view_file_number(0),
  variableWatcher_(NULL),
  pSourceMgr(NULL),
  fileViewer_(NULL),
  fileSelector_(NULL),
  prompt_(NULL),
  inputWin_(NULL),
  inkeyWin_(NULL),
  ioWin_(NULL),
  childHandler_(NULL),
  isClientChangeAllowed_(FALSE),
  sErrorMsg_(""),
  nJobId_(-1),
  isPaused_(FALSE),
  setuidDone(TRUE),
  shuttingDown_(FALSE),
  shutDownInitiated_(FALSE),
  waitingForServerRestart_(FALSE),
  shutdownProcessing_(FALSE),
  cleanupFlag(0),
  pid(0),
  clientType_(OPS::GUI) // Added due to TR HF65265
{
    TRACE_IN(trace, OpsParserListenerImpl, "OpsParserListenerImpl STARTED");

  initDetachedThreadAttr();

  createDetachedThread(&pThreadCUId_, OpsParserListenerImpl::checkSetuidThread);

#ifdef SunOS5 || __linux__
   pthread_mutex_init( &shutDownInitiatedMutex_, 0 );
   pthread_mutex_init( &shutdownWaitMutex_, 0 );
   pthread_cond_init(&shutdownWaitObject_, 0);
#endif

#ifdef HPUX10
   pthread_mutex_init( &shutDownInitiatedMutex_, pthreadMutexAttrInit_ );
   pthread_mutex_init( &shutdownWaitMutex_, pthreadMutexAttrInit_ );
   pthread_cond_init(&shutdownWaitObject_, pthreadCondAttrInit_);
#endif

}

//---------------------------------------------------------------------
OpsParserListenerImpl::~OpsParserListenerImpl(){
  for (int i=(file_count-1); i>=0; i--) {
    delete file_entry[i];
  }

  pthread_cond_destroy(&shutdownWaitObject_);
  pthread_mutex_destroy(&shutdownWaitMutex_);

  pthread_mutex_destroy(&shutDownInitiatedMutex_);
  pthread_attr_destroy(&detachedThreadAttr);
}

//---------------------------------------------------------------------

//*************************************************************************************************
//Moved from OPSServerImpl.C, R3


//---------------------------------------------------------------------
OPS::FileView_ptr OpsParserListenerImpl::getFileViewer() 
  throw (CORBA::SystemException, OPS::OPS_Exception)
{

  TRACE_IN(trace, getFileViewer, "");

 PortableServer::ServantBase_var pRemoteFileServant = new RemoteFileImpl();
  try{
    PortableServer::POA_var pDefault_poa = _default_POA();
    CORBA::Object_var pRef = pDefault_poa->servant_to_reference(pRemoteFileServant);
    OPS::FileView_var pFileViewer = OPS::FileView::_narrow(pRef);
    TRACE_OUT(trace, getFileViewer, "Creating file viewer");
    return OPS::FileView::_duplicate(pFileViewer);
  }
  catch(const CORBA::Exception& e){
    TRACE_INFO(trace, getFileViewer, "Couldn't make new fileviewer:");
  }

  TRACE_INFO(trace, getFileViewer, "Error occured");
  return OPS::FileView::_nil();
}

void OpsParserListenerImpl::initDetachedThreadAttr()
{
  pthread_attr_init(&detachedThreadAttr);
  pthread_attr_setdetachstate(&detachedThreadAttr,PTHREAD_CREATE_DETACHED);
}

void OpsParserListenerImpl::createDetachedThread(pthread_t *thread, void *(*start)(void *))
{
  TRACE_IN(trace, createDetachedThread, "");
  int retval = pthread_create(thread, &detachedThreadAttr, start, (void *)this);
  if (retval)
  {
    TRACE_INFO(trace, createDetachedThread, "Error creating thread");
  }
  TRACE_OUT(trace, createDetachedThread, "pthread_create returns " << retval);
}

void OpsParserListenerImpl::shutdown()
{
  TRACE_IN(trace, shutdown, "");
  RWBoolean doShutdown = FALSE;

  pthread_mutex_lock(&shutDownInitiatedMutex_);
  if(!shutDownInitiated_)
  {
    shutDownInitiated_ = TRUE;
    doShutdown = TRUE;
    TRACE_FLOW(trace, shutdown, "Shutdown of parser initiated");
  }
  else
  {
    TRACE_FLOW(trace, shutdown, "Shutdown is already in progress, will do nothing for this request");
  }
  pthread_mutex_unlock(&shutDownInitiatedMutex_);

  if(doShutdown)
  {
    shuttingDown_ = TRUE;

    if(pSourceMgr)
    {
    doShutdownProcessing();
    }

    // Terminate the session
    TRACE_FLOW(trace, shutdown, "OPS Parser requests for removing the session: " << sSessionId_);

    // Create a thread that shutdown the orb.
    TRACE_FLOW(trace, destroy, "Create orb shutdown thread.");
    pthread_mutex_lock(&shutDownInitiatedMutex_);
    createDetachedThread(&pOrbShutdownThreadId_, OpsParserListenerImpl::OrbShutdownThread);
    pthread_mutex_unlock(&shutDownInitiatedMutex_);
  }
  TRACE_OUT(trace, shutdown, "");
}
//----------------------------------------------------------------------

void OpsParserListenerImpl::orbShutdown(){
  TRACE_IN(trace, orbShutdown, "");
  TRACE_FLOW(trace, orbShutdown, "orb shutdown");
  // Send true as parameter. The operation blocks until all ORB processing
  //(including processing of currently executing requests, object deactivation,
  //and other object adapter operations) has completed.
   pOrb_->shutdown(TRUE);
  TRACE_OUT(trace, orbShutdown, "");
}
//----------------------------------------------------------------------

void* OpsParserListenerImpl::OrbShutdownThread(void* x){
  ((OpsParserListenerImpl*)x)->orbShutdown();
  return NULL;
}
//----------------------------------------------------------------------

void* OpsParserListenerImpl::checkSetuidThread(void* x){
  ((OpsParserListenerImpl*)x)->checkSetuid();
  return NULL;
}

//----------------------------------------------------------------------

void OpsParserListenerImpl::checkSetuid(){
 TRACE_IN(trace, checkSetuid, "");
  sleep(60);

  if (issetuiddone() == FALSE) { 
    TRACE_FLOW(trace, checkSetuid, "Setuid=FALSE.");
      shutdown();
  }

  TRACE_OUT(trace, checkSetuid, "");
}

//----------------------------------------------------------------------

RWBoolean OpsParserListenerImpl::isPasswordCorrect(const char* sUser, const char* sPwd){
  TRACE_IN(trace, isPasswordCorrect, "User = " << sUser << " PWD = " << sPwd);

  RWBoolean isPwdCorrect = FALSE;

  struct spwd* pPwdEntry = getspnam(sUser);

  if(pPwdEntry == NULL){

     TRACE_FLOW(trace, isPasswordCorrect, "Pwd entry not found");

  } else {

      // When the client is started without user/pwd being specified, it sends
      // the value of the property "user.name" as user ID, and an empty
      // password. That is regarded as ok:

      if(strlen(sPwd) == 0) {
          isPwdCorrect = TRUE;
        TRACE_FLOW(trace, isPasswordCorrect, "Is trusted user: " << sUser);
      }

      // Both password and user are specified, so we must check the password:
      else if (strcmp(crypt(sPwd,pPwdEntry->sp_pwdp), pPwdEntry->sp_pwdp) == 0){
          isPwdCorrect = TRUE;
      }
  }

  TRACE_OUT(trace, isPasswordCorrect, isPwdCorrect);
  return isPwdCorrect;
}

//----------------------------------------------------------------------


//*************************************************************************************************
// Moved from ParserImpl.C, R3

//*****************************************************************************

void OpsParserListenerImpl::cleanup()
{
   cleanupFlag = 1;
  TRACE_IN(trace, cleanup, "");

  for (int i=(file_count-1); i>=0; i--) {
    if (file_entry[i] != NULL){
      delete file_entry[i];
      file_entry[i] = NULL;
    }
  }
  if (indicator_ != NULL){
    indicator_->removeDependent(this);
  }
  if(cmdRspBuf_ != NULL){
    cmdRspBuf_->removeDependent(this);
  }
  if(commentWinModel_!= NULL){
    commentWinModel_->removeDependent(this);
  }
  if(connectionObject_ != NULL){
    connectionObject_->removeDependent(this);
  }
  if(variableWatcher_ != NULL && pSourceMgr != NULL) {
    pSourceMgr->getVarStore().removeDependent(variableWatcher_);
  }
  if (variableWatcher_ != NULL){
    delete variableWatcher_;
    variableWatcher_ = NULL;
  }
  if (pSourceMgr != NULL){
    delete pSourceMgr;
    pSourceMgr = NULL;
  }
  if (fileViewer_ != NULL){
    delete fileViewer_;
    fileViewer_ = NULL;
  }
  if (fileSelector_ != NULL){
    delete fileSelector_;
    fileSelector_ = NULL;
  }
  if (prompt_ != NULL){
    delete prompt_;
    prompt_ = NULL;
  }
  if (inputWin_ != NULL){
    delete inputWin_;
    inputWin_ = NULL;
  }
  if (inkeyWin_ != NULL){
    delete inkeyWin_;
    inkeyWin_ = NULL;
  }
  if (ioWin_ != NULL){
    delete ioWin_;
    ioWin_ = NULL;
   }
  if (childHandler_ != NULL){
    delete childHandler_;
    childHandler_ = NULL;
  }
  if (ozt_evHandlerPtr != NULL){
    delete ozt_evHandlerPtr;
    ozt_evHandlerPtr = NULL;
  }
  TRACE_OUT(trace, cleanup, "");
}


//*****************************************************************************
OPS::stringList * OpsParserListenerImpl::getExternalSystems()
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  TRACE_IN(trace, getExternalSystems, "No parameters");


  /*OPS::stringList *returnList = new OPS::stringList();

  // Copy the contents of the list to the widow.
  if (esList_.entries() > 0) {
    returnList->length(esList_.entries());
    for(int i=0; i<esList_.entries(); i++)
      (*returnList)[i] = CORBA::string_dup(esList_[i].data());
  }

  TRACE_OUT(trace, getExternalSystems, "No parameters");
  return returnList;*/
}


//*****************************************************************************
void OpsParserListenerImpl::connectToES(const char *esName,
                             CORBA::Boolean isStandby)
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  TRACE_IN(trace, connectToES, esName);

  if (action == NOTHING || action == RUN) {
    doConnectToES(esName, isStandby);
  }

  TRACE_OUT(trace, connectToES, "");
}


//*****************************************************************************
/*
int OpsParserListenerImpl::connectCallBack(void* instance, void *args)
{
    ((OpsParserListenerImpl*)instance)->doConnectToES((const char *)args);

    return ozt_evHandlerPtr->notify_done();
}
*/
//*****************************************************************************
void OpsParserListenerImpl::doConnectToES(const char* esName, RWBoolean side)
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  TRACE_IN(trace, doConnectToES, esName);
  OZT_Result       result;

  indicator_->clearMsg();
  //if (pSourceMgr->getCmdSender().getConnectionObject().getConnectionStatus() != -1/* ==      EAC_CRI_CS_CONNECTED*/)
  if (pSourceMgr->getCmdSender().getConnectionObject().getConnectionStatus() == 4)
  {
    // The disconnect() also prints a message in the response
    // window.
    pSourceMgr->getCmdSender().disconnect();
  }

  TRACE_FLOW(trace, doConnectToES, "Connecting to " << esName);

  // Write information to the log file /tmp/opsserver.log

  /// TODO add standby
  /// result = pSourceMgr->getCmdSender().connect(esName, side);
  result = pSourceMgr->getCmdSender().connect(esName);

  if (result.code != OZT_Result::NO_PROBLEM)
  {
    TRACE_OUT(trace, doConnectToES, result.toMsg());
    throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, result.toMsg());
  }
  TRACE_OUT(trace, doConnectToES, "");
}

//*****************************************************************************

void OpsParserListenerImpl::cleanupAfterConnect(void *args)
{
  TRACE_IN(trace, cleanupAfterConnect, args);
  delete[] (char *)args;
  TRACE_OUT(trace, cleanupAfterConnect, args);
}

//*****************************************************************************
void OpsParserListenerImpl::disconnectFromES()
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  TRACE_IN(trace, disconnectFromES, "");

  if (action == NOTHING || action == RUN) {
      /*
    ((OPS_EventHandler *)ozt_evHandlerPtr)->setGuiTrigger(this,
                                                          disConnectCallBack,
                                                          NULL);
      */
      doDisconnectFromES(); // MAGA
  }
  TRACE_OUT(trace, disconnectFromES, "");
}


//*****************************************************************************
/*
int OpsParserListenerImpl::disConnectCallBack(void* instance, void *args)
{
    ((OpsParserListenerImpl*)instance)->doDisconnectFromES();

    return ozt_evHandlerPtr->notify_done();
}
*/
//*****************************************************************************
void OpsParserListenerImpl::doDisconnectFromES()
//  throw (OPS::OPS_Exception)
{
  TRACE_IN(trace, doDisconnectFromES, "");
  int disconnFlag = 1;

  indicator_->clearMsg();

  TRACE_FLOW(trace,doDisconnectFromES , "Sender State: " << pSourceMgr->getCmdSender().getState());

  isPaused_ = true; // Prevent from steppin and run the next command in the script after disconnecting.

  while (disconnFlag)
    {
      if (pSourceMgr->getCmdSender().getState() != OZT_CmdSender::WAIT_IMM_RSP &&
          pSourceMgr->getCmdSender().getState() != OZT_CmdSender::WAIT_IMM_RSP_CONFIRMED)
        {
          pSourceMgr->getCmdSender().getConnectionObject().disconnect();
          disconnFlag = 0;
        }
    }

  isPaused_ = false; // Make possible to step and run the next command in the script after disconnecting.

  TRACE_OUT(trace, doDisconnectFromES, "");
}


//*****************************************************************************
void OpsParserListenerImpl::setFile(const char* filename)
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  RWCString        report;
  RWCString                fileName;
  DIR              *dir = NULL;

  TRACE_IN(trace, setFile, filename);

  // Write information to the log file /tmp/opsserver.log
  time_t td = time(0);

  if (action == NOTHING) {
    action = SET_VALUE;
    fileName = ozt_normalisePath(filename);

    // Check some file properties
    RWFile f(fileName, "r");
    if ((f.isValid() != TRUE) || (f.Exists() != TRUE)) {
      // file does not exist
      RWCString report = ozt_nlsCatalog.getMessage(OZT_NLS_THE_FILE,
                                                   "The file") +
                         " \"" + fileName + "\" " +
                         ozt_nlsCatalog.getMessage(OZT_NLS_CANNOT_BE_ACCESSED,
                                                   "cannot be accessed");
      action = NOTHING;
      TRACE_INFO(trace, setFile, report);
      throw OPS::OPS_Exception(OPS::FILE_NOT_ACCESSIBLE, report);
    }
    else if ((dir = opendir(fileName.data())) != NULL)
    {
      // It's a directory name
      closedir(dir);
      RWCString report = ozt_nlsCatalog.getMessage(OZT_NLS_FILE_OPEN_ERROR,
                                                   "Cannot open file:") +
                         " \"" + fileName + "\"" ;
      action = NOTHING;
      TRACE_INFO(trace, setFile, report);
      throw OPS::OPS_Exception(OPS::FILE_NOT_READABLE, report);
    }
    // If is not loaded, then load it
    else if (!open_a_file("", fileName) == TRUE)
    {
      // If the file is loaded, then re-load it.
      int file_num = -1;
      for (int i = 0; i<file_count; i++)  {
        if (file_entry[i]->get_full_name() == fileName)
          file_num = i;
      }

      if (file_num >= 0) {
        file_entry[file_num]->set_time_stamp();
        (void)pSourceMgr->update(file_entry[file_num]->get_full_name());
        view_file(fileName, FALSE);
      }
    }
    else {
      if (view_file_number != (file_count-1))
        view_file(file_entry[file_count-1]->get_full_name(), FALSE);
    }

    action = NOTHING;
  }
  TRACE_OUT(trace, setFile, "");
}
//*****************************************************************************
void OpsParserListenerImpl::resetWindowTimeouts() {
  ioWin_->resetTimeout();
  inkeyWin_->resetTimeout();
  inputWin_->resetTimeout();
  prompt_->resetTimeout();
}

//*****************************************************************************
void OpsParserListenerImpl::closeFile(const char* filename)
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  TRACE_IN(trace, closeFile, filename);

  if (action == NOTHING) {
    action = SET_VALUE;
    RWCString fileName = ozt_normalisePath(filename);
    // If the file is loaded, then re-load it.
    int file_num;
    for (file_num = 0; file_num<file_count; file_num++)  {
      if (file_entry[file_num]->get_full_name() == fileName)
        break;
    }

    // Reset the current position if it's contained in this file.
    if (running_file_number == file_num) {
      current_position = 0;
      running_file_number = 0;
      pSourceMgr->reset();
    }
    if (close_a_file(file_num)) {
      view_file_number = 0;


      // Always go back to the first file after deleting the current one.
      // NOT NEEDED, due to TR HF24401
      //if (file_count > 0)view_file(file_entry[0]->get_full_name(),FALSE);
    }

    action = NOTHING;
  }
  TRACE_OUT(trace, closeFile, "");
}


//*****************************************************************************
void OpsParserListenerImpl::step()
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  RWCString        report;
  OZT_Result       result;
  LineNo      line_no;
  LineNo      num_lines;
  RWCString filename;

  TRACE_IN(trace, step, "action:" << action);

  // action must be set to NOTHING instead of PENDING_INTERRUPTION to avoid the
  // problem described in HD49152
  if ( action == PENDING_INTERRUPTION ) {
     result.code = OZT_Result::INTERRUPTED;
     action = NOTHING;
  }


  if (action == NOTHING) {
    action = RUN;

    if (file_count <= 0) {
      RWCString report = ozt_formatReport(
                  "",
                  "",
                  "",
                  ozt_nlsCatalog.getMessage(OZT_NLS_NO_FILE_LOADED,
                                            "No file loaded"));
      action = NOTHING;
      TRACE_INFO(trace, step, report);
      throw OPS::OPS_Exception( OPS::FILE_NOT_LOADED, report );
    }
    filename = file_entry[running_file_number]->get_full_name();
    stopped = FALSE;

    // Can't step if the file is out of date
    if (sync_file(running_file_number, FALSE) == FALSE) {
      RWCString report = ozt_formatReport(
                  filename,
                  "",
                  "",
                  ozt_nlsCatalog.getMessage(OZT_NLS_THE_FILE, "The file")
                  + " \"" + filename + "\" "
                  + ozt_nlsCatalog.getMessage(OZT_NLS_CANNOT_BE_ACCESSED,
                                       "cannot be accessed"));
      action = NOTHING;
      TRACE_INFO(trace, step, report);
      throw OPS::OPS_Exception( OPS::FILE_NOT_LOADED, report );
    }

    if (current_position != 0)
      show_position(file_entry[running_file_number]->get_full_name(), current_position);

    indicator_->setMsg(ozt_nlsCatalog.getMessage(OZT_NLS_STEP_IN_PROGRESS,
                                                 "Step in progress..."));

    result = pSourceMgr->setCurrPos(file_entry[running_file_number]->get_full_name(),
                                    current_position);

    if (result.code == OZT_Result::NO_PROBLEM) {
      TRACE_FLOW(trace, step, "Stepping");
      result = pSourceMgr->step(file_count);
      pSourceMgr->getCurrPos(filename, line_no, num_lines);
      current_position = line_no;
      if (result.code == OZT_Result::INCLUDE_NOT_EXECUTED) {
        indicator_->clearMsg();
        action = NOTHING;
        TRACE_INFO(trace, step, "Could not include file");
        serverRLRef_->newState(OPS::FAILED);
        // HD62350
        line_no++; // getCurrPos counts the first line as line zero
        char* line_no_str = new char[30];
        sprintf(line_no_str, " (script line no. %d)", line_no);
        sErrorMsg_ = result.toMsg();
        sErrorMsg_ += line_no_str;
        delete [] line_no_str;
        sendErrorMsg();
        // END HD62350
        throw OPS::OPS_Exception(OPS::EXECUTION_ERROR,
                                 ozt_nlsCatalog.getMessage(OZT_NLS_STEP_CANT_INCLUDE,
                                  "Include command error: Max number of files reached."));
      }
    }

    if (stopped)
      indicator_->setMsg(ozt_nlsCatalog.getMessage(OZT_NLS_STEP_INTERRUPTED,
                                                   "Step: Interrupted"));
    else if (result.code != OZT_Result::INCLUDE_NOT_EXECUTED)
      indicator_->setMsg(ozt_nlsCatalog.getMessage(OZT_NLS_STEP, "Step:")
                         + " " + result.toMsg());
    else
      indicator_->clearMsg();

    // Flush any logged responses if the execution was either
    // terminated normally, or some error occurred.  However, we
    // don't want to do the flush if we just stepped a single line
    // (NO_PROBLEM) or clicked on the 'Stop' button (STOP)...
    if (result.code != OZT_Result::NO_PROBLEM && result.code != OZT_Result::STOP
        && connectionObject_->getConnectionStatus() /*== EAC_CRI_CS_CONNECTED*/) {
        pSourceMgr->getCmdSender().logOff(true);
    }

    pSourceMgr->getCurrPos(filename, line_no, num_lines);
    if (filename == "")
      filename = file_entry[running_file_number]->get_full_name();
    current_position = line_no;

    // Show the running file name, position and number of lines
    if (num_lines != 0)
      show_position(filename, current_position);

        running_file_number = view_file_number;

    // Ugly fix to display the right file. Do it once more
    if (num_lines != 0)
      show_position(filename, current_position);

    action = NOTHING;
  }

  if (!shutdownProcessing_)
  {
    // Send back status to the client.
    if(result.code == OZT_Result::NO_PROBLEM)
      serverRLRef_->newState(OPS::RUNNING);
    else if(result.code == OZT_Result::PROGRAM_TERMINATED)
      serverRLRef_->newState(OPS::FINISHED);
    else if(result.code == OZT_Result::STOP)
      serverRLRef_->newState(OPS::STOPPED);
    else if(result.code == OZT_Result::INTERRUPTED)
      serverRLRef_->newState(OPS::INTERRUPTED);
    else if(result.code == OZT_Result::QUIT)
      serverRLRef_->newState(OPS::FINISHED);
    else if(result.code == OZT_Result::NO_UI_SUPPORTED){
      serverRLRef_->newState(OPS::WAITING_FOR_INPUT);
      sErrorMsg_ = result.toMsg();
      sendErrorMsg();
    }
    else{
      serverRLRef_->newState(OPS::FAILED);
      // HD62350
      pSourceMgr->getCurrPos(filename, line_no, num_lines);
      line_no++; // getCurrPos counts the first line as line zero
      char* line_no_str = new char[30];
      sprintf(line_no_str, " (script line no. %d)", line_no);
      sErrorMsg_ = result.toMsg();
      sErrorMsg_ += line_no_str;
    delete [] line_no_str;
      sendErrorMsg();
      // END HD62350
    }
  }

  signalFinishedShutdownProcessing();
  TRACE_OUT(trace, step, result.toMsg());
}

//*****************************************************************************
void OpsParserListenerImpl::runIncludedLines(const OPS::stringList& lines)
                                  throw (OPS::OPS_Exception)
{
  TRACE_IN(trace, runIncludedLines, "");

  OZT_Result result(OZT_Result::NO_PROBLEM);
  RWTValOrderedVector<RWCString> text;

  if( action == NOTHING || action == PENDING_INTERRUPTION ) {
    action = RUN;
    serverRLRef_->newState(OPS::RUNNING);


    for(int i=0; i < lines.length(); i++){
      TRACE_FLOW(trace, runIncludedLines, lines[i]);
      text.insert(  RWCString( lines[i]) );
    }

    OZT_SourceInfo includedSource( pSourceMgr->getVarStore(), text );

    while (result.code == OZT_Result::NO_PROBLEM ){

      result = pSourceMgr->step( includedSource, file_count );

      if( result.code !=  OZT_Result::NO_PROBLEM )
        break;
    }


    // Flush any logged responses if the execution was either
    // terminaOZT_RspReceiverted normally, or some error occurred.  However, we
    // don't want to do the flush if we just stepped a single line
    // (NO_PROBLEM) or clicked on the 'Stop' button (STOP)...
    if (result.code != OZT_Result::NO_PROBLEM
        && result.code != OZT_Result::STOP
        && connectionObject_->getConnectionStatus() //== EAC_CRI_CS_CONNECTED
        && result.code !=  OZT_Result::HIT_EOF) {
        pSourceMgr->getCmdSender().logOff(true);
    }

    // HD81058: Removed this correction. The SAOSP command worked without
    //          any problems (HD61493).
    // Here we close the log files to prevent the hang fault described
    // in HD61493.
    TRACE_FLOW(trace, runIncludedLines, "close all File logs");
    //CHA_FileLogger *pFileLogger = &(pSourceMgr->getFileLogger());
    //pFileLogger->closeAllLogs();

    if( result.code != OZT_Result::HIT_EOF ){
      RWCString outputMsg = "\n" + ozt_nlsCatalog.getMessage(OZT_NLS_RUN_STOP,
                                                             "Run stopped:")
        + " " + result.toMsg() + "\n";

      TRACE_FLOW(trace, runIncludedLines, outputMsg);

      cmdRspBuf_->append(outputMsg.data());
    }

    if (!shutdownProcessing_)
    {
      // Send message to client about the state.
      if(result.code == OZT_Result::PROGRAM_TERMINATED)
        serverRLRef_->newState(OPS::FINISHED);
      else if(result.code == OZT_Result::HIT_EOF)
        serverRLRef_->newState(OPS::INTERRUPTED);
      else if(result.code == OZT_Result::STOP)
        serverRLRef_->newState(OPS::STOPPED);
      else if(result.code == OZT_Result::INTERRUPTED)
        serverRLRef_->newState(OPS::INTERRUPTED);
      else if(result.code == OZT_Result::QUIT)
        serverRLRef_->newState(OPS::FINISHED);
      else if(result.code == OZT_Result::NO_UI_SUPPORTED){
        serverRLRef_->newState(OPS::WAITING_FOR_INPUT);
        sErrorMsg_ = result.toMsg();
        sendErrorMsg();
      }
      else{
        serverRLRef_->newState(OPS::FAILED);
        // HD62350
        RWCString filename;
        LineNo line_no;
        LineNo num_lines;
        pSourceMgr->getCurrPos(filename, line_no, num_lines);
        line_no++; // getCurrPos counts the first line as line zero
        char* line_no_str = new char[30];
        sprintf(line_no_str, " (script line no. %d)", line_no);
        sErrorMsg_ = result.toMsg();
        sErrorMsg_ += line_no_str;
      delete [] line_no_str;
        sendErrorMsg();
        // END HD62350
      }
    }

    action = NOTHING;
  }

  signalFinishedShutdownProcessing();
  TRACE_OUT(trace, runIncludedLines, result);
}

//*****************************************************************************
void OpsParserListenerImpl::runFromBeginning(CORBA::Boolean updatePosition)
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  OZT_Result    result;
  RWCString     filename;
  LineNo        line_no;
  LineNo        num_lines;
  int           start_file_number;
  TRACE_IN(trace, runFromBeginning, updatePosition << ":" << action);
  sErrorMsg_ = "";
  if (action == NOTHING) {
    action = RUN;
    serverRLRef_->newState(OPS::RUNNING);

    if (file_count <= 0) {
      RWCString report = ozt_formatReport(
                                          "",
                                          "",
                                          "",
                                          ozt_nlsCatalog.getMessage(OZT_NLS_NO_FILE_LOADED,
                                                                    "No file loaded"));
      serverRLRef_->newState(OPS::FAILED);
      sErrorMsg_ = report;
      sendErrorMsg();
      action = NOTHING;
      TRACE_INFO(trace, runFromBeginning, report);
      throw OPS::OPS_Exception( OPS::FILE_NOT_LOADED, report );
    }
    posUpdate_ = updatePosition;
    running_file_number = view_file_number;
    start_file_number = running_file_number;
    filename = file_entry[running_file_number]->get_full_name();
    if (sync_file(running_file_number,FALSE) == FALSE) {
      RWCString report = ozt_formatReport(
                                          filename,
                                          "",
                                          "",
                                          ozt_nlsCatalog.getMessage(OZT_NLS_THE_FILE, "The file")
                                          + " \"" + filename + "\" "
                                          + ozt_nlsCatalog.getMessage(OZT_NLS_CANNOT_BE_ACCESSED,
                                                                      "cannot be accessed"));
      serverRLRef_->newState(OPS::FAILED);
      sErrorMsg_ = report;
      sendErrorMsg();
      action = NOTHING;
      TRACE_INFO(trace, runFromBeginning, report);
      throw OPS::OPS_Exception( OPS::FILE_NOT_LOADED, report );
    }
    pSourceMgr->reset();
    current_position = 0;

    indicator_->setMsg(ozt_nlsCatalog.getMessage(OZT_NLS_RUNNING_FROM_TOP,
                                                 "Running from top of file..."));

    result = pSourceMgr->setCurrPos(filename, 0);
    if (result.code !=OZT_Result::NO_PROBLEM) {
      indicator_->setMsg(result.toMsg());
      action = NOTHING;
      serverRLRef_->newState(OPS::FAILED);
      // HD62350
      pSourceMgr->getCurrPos(filename, line_no, num_lines);
      line_no++; // getCurrPos counts the first line as line zero
      char* line_no_str = new char[30];
      sprintf(line_no_str, " (script line no. %d)", line_no);
      sErrorMsg_ = result.toMsg();
      sErrorMsg_ += line_no_str;
      delete [] line_no_str;
      sendErrorMsg();
      // END HD62350
      TRACE_OUT(trace, runFromBeginning, result.toMsg());
      return;
    }
    pSourceMgr->getCurrPos(filename, line_no, num_lines);
    //Don't run if the first line has a breakpoint
    if (file_entry[view_file_number]->get_breakpoint(line_no, num_lines) == TRUE){
      result.code = OZT_Result::INTERRUPTED;
      RWCString report = ((RWCString)"\n" +
                          + ozt_nlsCatalog.getMessage(OZT_NLS_RUN_STOP_BREAKPOINT,
                                                      "Run stopped: Breakpoint") +
                          "\n");
      cmdRspBuf_->append(report);
    }
    else {
      indicator_->setMsg(result.toMsg());
      result = run_loop(filename, FALSE);
      indicator_->clearMsg();
    }
    runCommon(result, filename, line_no, num_lines, start_file_number);
  }

  if ( action == PENDING_INTERRUPTION )
  {
    result.code = OZT_Result::INTERRUPTED;
    action = NOTHING;
  }

  signalFinishedShutdownProcessing();
  TRACE_OUT(trace, runFromBeginning, result.toMsg() << ":" << action);
}


//*****************************************************************************
void OpsParserListenerImpl::runFromCurrentPosition(CORBA::Boolean updatePosition)
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  OZT_Result    result;
  RWCString     filename;
  LineNo        line_no;
  LineNo        num_lines;
  int           start_file_number;
  TRACE_IN(trace, runFromCurrentPosition, updatePosition);
  sErrorMsg_ = "";

  if (action == RUN) {
    // Make sure that the client know that we are in state "RUNNING"
    serverRLRef_->newState(OPS::RUNNING);
  } else if (action == NOTHING) {
    action = RUN;
    serverRLRef_->newState(OPS::RUNNING);

    if (file_count <= 0) {
      RWCString report = ozt_formatReport(
                  "",
                  "",
                  "",
                  ozt_nlsCatalog.getMessage(OZT_NLS_NO_FILE_LOADED,
                                            "No file loaded"));
      action = NOTHING;
      serverRLRef_->newState(OPS::FAILED);
      sErrorMsg_ = report;
      sendErrorMsg();
      TRACE_INFO(trace, runFromCurrentPosition, report);
      throw OPS::OPS_Exception( OPS::FILE_NOT_LOADED, report );
    }

    posUpdate_ = updatePosition;
    start_file_number = running_file_number;
    filename = file_entry[running_file_number]->get_full_name();

    // Can't step if the file is out of date
    if (sync_file(running_file_number,FALSE) == FALSE) {
      RWCString report = ozt_formatReport(
                  filename,
                  "",
                  "",
                  ozt_nlsCatalog.getMessage(OZT_NLS_THE_FILE, "The file")
                  + " \"" + filename + "\" "
                  + ozt_nlsCatalog.getMessage(OZT_NLS_CANNOT_BE_ACCESSED,
                                              "cannot be accessed"));
      serverRLRef_->newState(OPS::FAILED);
      sErrorMsg_ = report;
      sendErrorMsg();
      action = NOTHING;
      TRACE_INFO(trace, runFromCurrentPosition, report);
      throw OPS::OPS_Exception( OPS::FILE_NOT_LOADED, report );
    }

    indicator_->setMsg(ozt_nlsCatalog.getMessage(OZT_NLS_RUNNING, "Running..."));

    result = run_loop(filename, FALSE);
    indicator_->clearMsg();
    runCommon(result, filename, line_no, num_lines, start_file_number);
  }

  if ( action == PENDING_INTERRUPTION )
  {
    result.code = OZT_Result::INTERRUPTED;
    action = NOTHING;
  }

  signalFinishedShutdownProcessing();

  TRACE_OUT(trace, runFromCurrentPosition, result.toMsg() << ":" << action);
}

//*****************************************************************************
void OpsParserListenerImpl::runTaggedLines(CORBA::Boolean updatePosition)
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  OZT_Result    result;
  RWCString     filename;
  LineNo        line_no;
  LineNo        num_lines;
  int           start_file_number;
  TRACE_IN(trace, runTaggedLines, updatePosition);
  sErrorMsg_ = "";
  if (action == NOTHING) {
    action = RUN;
    serverRLRef_->newState(OPS::RUNNING);

    if (file_count <= 0) {
      RWCString report = ozt_formatReport(
                  "",
                  "",
                  "",
                  ozt_nlsCatalog.getMessage(OZT_NLS_NO_FILE_LOADED,
                                            "No file loaded"));
      serverRLRef_->newState(OPS::FAILED);
      sErrorMsg_ = report;
      sendErrorMsg();
      action = NOTHING;
      TRACE_INFO(trace, runTaggedLines, report);
      throw OPS::OPS_Exception( OPS::FILE_NOT_LOADED, report );
    }

    posUpdate_ = updatePosition;
    start_file_number = running_file_number;
    filename = file_entry[running_file_number]->get_full_name();

    // Can't step if the file is out of date
    if (sync_file(running_file_number,FALSE) == FALSE) {
      RWCString report = ozt_formatReport(
                  filename,
                  "",
                  "",
                  ozt_nlsCatalog.getMessage(OZT_NLS_THE_FILE, "The file")
                  + " \"" + filename + "\" "
                  + ozt_nlsCatalog.getMessage(OZT_NLS_CANNOT_BE_ACCESSED,
                                       "cannot be accessed"));
      serverRLRef_->newState(OPS::FAILED);
      sErrorMsg_ = report;
      sendErrorMsg();
      action = NOTHING;
      TRACE_INFO(trace, runTaggedLines, report);
      throw OPS::OPS_Exception( OPS::FILE_NOT_LOADED, report );
    }

    indicator_->setMsg(ozt_nlsCatalog.getMessage(OZT_NLS_RUNNING_TAGS,
                                                 "Running tags..."));

    line_no = file_entry[running_file_number]->get_next_tag(current_position);
    if ((int)line_no < 0) {
      indicator_->setMsg(ozt_nlsCatalog.getMessage(OZT_NLS_NO_TAGS,
                                                   "Can't run tags: No Tags"));
      serverRLRef_->newState(OPS::FAILED);
      action = NOTHING;
     TRACE_OUT(trace, runTaggedLines, "No tags");
      return;
    }
    current_position = line_no;
    result = run_loop(filename, TRUE);
    indicator_->clearMsg();

    runCommon(result, filename, line_no, num_lines, start_file_number);
  }

  if ( action == PENDING_INTERRUPTION )
  {
    result.code = OZT_Result::INTERRUPTED;
    action = NOTHING;
  }

  signalFinishedShutdownProcessing();
  TRACE_OUT(trace, runTaggedLines, result.toMsg());
}


//*****************************************************************************
CORBA::Long OpsParserListenerImpl::interrupt(CORBA::Boolean doReallyInterrupt)
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  TRACE_IN(trace, interrupt, doReallyInterrupt);
//  if (action == RUN) {

      doInterrupt(doReallyInterrupt);
//  }
  action = PENDING_INTERRUPTION;

  TRACE_INFO(trace, interrupt, "pending interruption");

  return 0;
}

//*****************************************************************************
void  OpsParserListenerImpl::breakResponse()
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  TRACE_IN(trace, breakResponse, "at" << action);

  if (action == RUN) {
      doInterrupt(TRUE);
  }

  TRACE_OUT(trace, breakResponse, "action=" << action);
}

//*****************************************************************************
/*
int OpsParserListenerImpl::interruptCallBack(void* instance, void *args)
{
    ((OpsParserListenerImpl*)instance)->doInterrupt();

    return ozt_evHandlerPtr->notify_done();
}
*/
//*****************************************************************************
/*
int OpsParserListenerImpl::breakResponseCallBack(void* instance, void *args)
{
    ((OpsParserListenerImpl*)instance)->doBreakResponse();

    return ozt_evHandlerPtr->notify_done();
}
*/
//*****************************************************************************
void OpsParserListenerImpl::doInterrupt(RWBoolean doReallyInterrupt)
{
  TRACE_IN(trace, doInterrupt, "");
 //  if (action == RUN) {
    // When doReallyInterrupt is set, the ongoing statement will be
    // interrupted. Otherwise it will run to completion, but the next one will
    // not be started.
    stopped = TRUE;
    if (doReallyInterrupt) {
      action = STOP;
        pSourceMgr->interrupt();
//    }
    action = NOTHING;
  }
  TRACE_OUT(trace, doInterrupt, "");
}

//*****************************************************************************
void OpsParserListenerImpl::doBreakResponse()
{
  TRACE_IN(trace, doBreakResponse, "");

  OZT_CmdSender* cmdSender = &pSourceMgr->getCmdSender();

  cmdSender->interrupt();

  TRACE_OUT(trace, doBreakResponse, "at action=" << action );
}


//*****************************************************************************
void OpsParserListenerImpl::quit()
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  TRACE_IN(trace, quit, "");
  action = QUIT;
  TRACE_OUT(trace, quit, "");
}


//*****************************************************************************
void OpsParserListenerImpl::setBreakPoints(const OPS::longList& breakpoints,
                                const char* filename)
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  int file_number;

  TRACE_IN(trace, setBreakPoints, filename);
  if (action == NOTHING) {
    action = SET_VALUE;

    RWCString fileName = ozt_normalisePath(filename);
    // Find the file to set breakpoints in
    for (file_number=0; file_number<file_count; file_number++) {
      if (file_entry[file_number]->get_full_name() == fileName) {    // found
        break;  // exit the for loop
      }
    }
    if (file_number >= file_count) {
      if (file_count >= MAX_OPEN_FILES) {
        action = NOTHING;
        TRACE_OUT(trace, setBreakPoints, "Too many files");
        throw OPS::OPS_Exception(OPS::EXECUTION_ERROR,
                                 ozt_nlsCatalog.getMessage(OZT_NLS_MAX_FILES,
                "Maximum number of files reached, cannot set tags/breakpoints on file:") +
                                 " " + filename);
      }
      if (!open_a_file("", fileName)) {
        // failed to open the file
        action = NOTHING;
        TRACE_OUT(trace, setBreakPoints, fileName);
        throw OPS::OPS_Exception(OPS::FILE_NOT_LOADED,
                                 ozt_nlsCatalog.getMessage(OZT_NLS_FILE_OPEN_ERROR,
                                                           "Cannot open file:") +
                                 " " + fileName);
      }
    }
    file_entry[file_number]->clearAllBrkPts();
    for (int i=0; i<breakpoints.length(); i++)
    file_entry[file_number]->set_breakpoint(breakpoints[i], TRUE);

    action = NOTHING;
  }
  TRACE_INFO(trace, setBreakPoints, filename);
}


//*****************************************************************************
void OpsParserListenerImpl::setTags(const OPS::longList& tags,
                         const char* filename)
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  int file_number;
  TRACE_IN(trace, setTags, filename);
  if (action == NOTHING) {
    action = SET_VALUE;

    RWCString fileName = ozt_normalisePath(filename);
    // Find the file to set tags in
    for (file_number=0; file_number<file_count; file_number++) {
      if (file_entry[file_number]->get_full_name() == fileName) {    // found
        break;  // exit the for loop
      }
    }
    if (file_number >= file_count) {
      if (file_count >= MAX_OPEN_FILES) {
        action = NOTHING;
       TRACE_OUT(trace, setTags, "Too many files");
        throw OPS::OPS_Exception(OPS::EXECUTION_ERROR,
                                 ozt_nlsCatalog.getMessage(OZT_NLS_MAX_FILES,
                    "Max number of files reached, cannot set tags/breakpoints on file:") +
                                 " " + filename);
      }
      if (!open_a_file("", fileName)) {
        // failed to open the file
        action = NOTHING;
        TRACE_OUT(trace, setTags, "Cannot open file: "<<fileName);
        throw OPS::OPS_Exception(OPS::FILE_NOT_LOADED,
                                 ozt_nlsCatalog.getMessage(OZT_NLS_FILE_OPEN_ERROR,
                                                           "Cannot open file:") +
                                 " " + fileName);
      }
    }
    file_entry[file_number]->clearAllTags();
    for (int i =0; i<tags.length(); i++){
      file_entry[file_number]->set_tag(tags[i], TRUE);
    }

    action = NOTHING;
  }
  TRACE_INFO(trace, setTags, filename);
}


//*****************************************************************************
void OpsParserListenerImpl::setCurrentPosition(const char* filename,
                                    CORBA::Long position)
  throw (CORBA::SystemException, OPS::OPS_Exception)
{

  TRACE_IN(trace, setCurrentPosition, position);
  LineNo lineNo;
  LineNo numLines;

  if (action == NOTHING) {
    action = SET_VALUE;

    OZT_Result result = pSourceMgr->setCurrPos( RWCString( filename ), position);
    if( result.code == OZT_Result::NO_PROBLEM ) {
      RWCString tmpStr(filename);
      pSourceMgr->getCurrPos( tmpStr, lineNo, numLines );
      if( result.code == OZT_Result::NO_PROBLEM ){
        current_position = lineNo;
        running_file_number = view_file_number;
      }
      else {
        RWCString report = result.toMsg();
        TRACE_OUT(trace, setCurrentPosition, report);
        action = NOTHING;
        throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
      }
    }
    else {
      RWCString report = result.toMsg();
      TRACE_OUT(trace, setCurrentPosition, report);
      action = NOTHING;
      throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
    }
    action = NOTHING;
  }

  TRACE_OUT(trace, setCurrentPosition, current_position);
}
//*****************************************************************************
void OpsParserListenerImpl::routeToFile(const char* filename)
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
      TRACE_IN(trace, routeToFile, filename);
      if (action == NOTHING) {
        action = SET_ROUTE;

        CHA_FileLogger *pFileLogger = &(pSourceMgr->getFileLogger());

        CHA_LogReturnCode res = pFileLogger->logAppend(RWCString(filename));

        if (!res.isOkay()){
          RWCString report =  res.toMsg();
          action = NOTHING;
          TRACE_OUT(trace, routeToFile, report);
          throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
        }

        TRACE_OUT(trace, routeToFile, res);
      }
      action = NOTHING;
}

//*****************************************************************************
char * OpsParserListenerImpl::getLogFile()
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  RWCString temp;
  temp = (&(pSourceMgr->getFileLogger()))->getLog();
  return CORBA::string_dup(temp);
}

//*****************************************************************************
void OpsParserListenerImpl::routeToMail(const char* mail)
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
     TRACE_IN(trace, routeToMail, mail);
      if (action == NOTHING) {
        action = SET_ROUTE;

        CHA_MailLogger *pMailLogger = &(pSourceMgr->getMailLogger());

        CHA_LogReturnCode res = pMailLogger->setRecipients(RWCString(mail));

        if (res.isOkay())
          res = pMailLogger->on();

        if (!res.isOkay()){
          RWCString report =  res.toMsg();
          action = NOTHING;
          TRACE_OUT(trace, routeToMail, report);
          throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
        }

        TRACE_OUT(trace, routeToMail, res);
      }

      action = NOTHING;
}

//*****************************************************************************
void OpsParserListenerImpl::routeToPrinter(const char* printer)
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
      TRACE_IN(trace, routeToPrinter, printer);
      if (action == NOTHING) {
        action = SET_ROUTE;

        CHA_PrinterLogger *pPrinterLogger = &(pSourceMgr->getPrinterLogger());

        CHA_LogReturnCode res = pPrinterLogger->setPrinter(RWCString(printer));

        if (res.isOkay())
          res = pPrinterLogger->on();

        if (!res.isOkay()){
          RWCString report =  res.toMsg();
          action = NOTHING;
          TRACE_OUT(trace, routeToPrinter, report);
          throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
        }

        TRACE_OUT(trace, routeToPrinter, res);
      }
      action = NOTHING;
}

//***************************************************************************

void OpsParserListenerImpl::setJobId(const char* jobIdString){
  nJobId_ = atol(jobIdString);
}

//***************************************************************************

void OpsParserListenerImpl::setSmoUser(const char* smoUser){
  pSourceMgr->getCmdSender().setSmoUser(smoUser);
}

//***************************************************************************

void OpsParserListenerImpl::setCurrentDisplay(const char* currentDisplay){
       TRACE_IN(trace, setCurrentDisplay, "");
  ozt_displayInfo = currentDisplay;
       TRACE_OUT(trace, setCurrentDisplay, "Display: " << ozt_displayInfo);
}

//***************************************************************************

void OpsParserListenerImpl::removeJobFromAM()
{
/* TODO - remove this
 //TRACE_IN(trace, setJobId, "setJobId()->START");

 if(nJobId_ != -1){

   CORBA::Object_var obj;

   try
     {
       CosNaming::NamingContextExt_var pNamingRoot =
         CosNaming::NamingContextExt::_narrow(pOrb_->resolve_initial_references("NameService"));

       //////TRACE_FLOW(trace,setJobId, "Namingroot created");

       RWCString CIFServicePath= "com/ericsson/nms/cif/service/AMServer";
       CosNaming::Name_var name= pNamingRoot->to_name(CIFServicePath.data());
       obj = pNamingRoot->resolve(name);
       ActivityManager::ActivityManagement_var amRef =
           ActivityManager::ActivityManagement::_narrow(obj);

       //////TRACE_FLOW(trace,setJobId, "Amserver defined");

       amRef->remove_job(nJobId_);
       nJobId_ = -1;

       //////TRACE_FLOW(trace,setJobId, ">> amRef->remove_job");

     }

   catch (const CosNaming::NamingContext::NotFound& nf)
     {
       obj = CORBA::Object::_nil();
       //////TRACE_FLOW(trace, setJobId, "No Bind done:" << nf);
     }
   catch (const CosNaming::NamingContext::CannotProceed& cnp)
     {
       //////TRACE_FLOW(trace, setJobId, "Cannot proceed:" << cnp);
     }
   catch (const CosNaming::NamingContext::InvalidName& ivn)
     {
       //////TRACE_FLOW(trace, setJobId, "Invalid name:" << ivn);
     }
   catch(const CORBA::Exception& eX)
     {
       //////TRACE_FLOW(trace, setJobId, "Exception :" << eX);
     }

   nJobId_ = -1;
 }

 //////TRACE_OUT(trace, setJobId, "setJobId:END");
*/
}





//*****************************************************************************

void OpsParserListenerImpl::setCurrentLabelPosition(const char* filename,
                                         const char* label)
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  TRACE_IN(trace, setCurrentLabelPosition, label);
  LineNo lineNo;
  LineNo numLines;
  if (action == NOTHING) {
    action = SET_VALUE;

    RWCString tmpStr(filename);
    OZT_Result result = pSourceMgr->setCurrPos( tmpStr, RWCString( label ) );
    if( result.code == OZT_Result::NO_PROBLEM ) {
      pSourceMgr->getCurrPos( tmpStr, lineNo, numLines );
      if( result.code == OZT_Result::NO_PROBLEM ){
        current_position = lineNo;
        running_file_number = view_file_number;
      }
      else {
        RWCString report = result.toMsg();
        TRACE_OUT(trace, setCurrentLabelPosition, report);
        action = NOTHING;
        throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
      }
    }
    else {
      RWCString report = result.toMsg();
      TRACE_OUT(trace, setCurrentLabelPosition, report);
      action = NOTHING;
      throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
    }
    action = NOTHING;
  }

  TRACE_OUT(trace, setCurrentPosition, current_position);
}

//*****************************************************************************
OPS::Position* OpsParserListenerImpl::getCurrentPosition()
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
 TRACE_IN(trace, getCurrentPosition, "");

  if (file_count <= 0) {
      TRACE_OUT(trace, getCurrentPosition, "No file loaded");
      throw OPS::OPS_Exception(OPS::NO_COMMAND_FILE,
                               ozt_nlsCatalog.getMessage(OZT_NLS_NO_FILE_LOADED,
                                                         "No file loaded"));
  }

  OPS::Position* posStruct = new OPS::Position;

  posStruct->pos = current_position;
  RWCString name = file_entry[running_file_number]->get_full_name();

  CORBA::String_var c = CORBA::string_dup(name.data());
  posStruct->file = c;

 TRACE_RETURN(trace, getCurrentPosition, current_position << "," << file_entry[running_file_number]->get_full_name() );

  return posStruct;
}



//*****************************************************************************

void OpsParserListenerImpl::setVariableValue(const char *variableName,
                                  const char *variableValue)
  throw (CORBA::SystemException) {
    TRACE_IN(trace, setVariableValue, variableName << " " << variableValue);
    std::string strName(variableName);
    std::string strValue(variableValue);


    if( (strName.compare("SMO_SOFTSTOP")==0) && (strValue.compare("stop")==0)){
        TRACE_INFO(trace,setVariableValue,"Received Job cancel request from SHM");
        releaseParser();
        if(!cleanupFlag){
            pSourceMgr->getVarStore().put( variableName, variableValue );
            sleep(10);
            TRACE_INFO(trace,setVariableValue,"Calling cleanup forcefully");
            cleanup();
        }
    }
    pSourceMgr->getVarStore().put( variableName, variableValue );
    TRACE_OUT(trace, setVariableValue, "");
}

//*****************************************************************************
void OpsParserListenerImpl::setDeviceFlag(CORBA::Boolean flag)
  throw (CORBA::SystemException)
{
  TRACE_IN(trace, setDeviceFlag, flag );

  if( flag ){
    pSourceMgr->getCmdSender().useStrictDeviceMode();
  }
  else {
    pSourceMgr->getCmdSender().useNonStrictDeviceMode();
  }

  TRACE_OUT(trace, setDeviceFlag, "");
}

//*****************************************************************************
char * OpsParserListenerImpl::getVariableValue(const char *variableName)
  throw (CORBA::SystemException)
{
  TRACE_IN(trace, getVariableValue, variableName);

  OZT_Value value;
  if (pSourceMgr->getVarStore().get(variableName, value)) {
   TRACE_RETURN(trace, getVariableValue, value);
    return CORBA::string_dup(value);
  }
  else {
    TRACE_RETURN(trace, getVariableValue, "NOT SET");
    return CORBA::string_dup("NOT SET");
  }
}

//*****************************************************************************
void OpsParserListenerImpl::reset()
  throw (CORBA::SystemException)
{
  TRACE_IN(trace, reset, "");
  //Don't empty the flowStack.
  RWBoolean clearSourceInfo = FALSE;
  pSourceMgr->reset(clearSourceInfo);
  resetWindowTimeouts();
  indicator_->clearMsg(); // clear the window footer as feedback
  TRACE_OUT(trace, reset, "");
}

//*****************************************************************************
void OpsParserListenerImpl::resetBufferMark()
  throw (CORBA::SystemException)
{
  TRACE_IN(trace, resetBufferMark, "");
  cmdRspBuf_->markBeginOfRsp();
  TRACE_OUT(trace, resetBufferMark, "");
}

//*****************************************************************************
OPS::stringList * OpsParserListenerImpl::getPrinters()
  throw (CORBA::SystemException)
{
  TRACE_IN(trace, getPrinters, "");

  CHA_PrinterList printerList;
  OPS::stringList *returnList = new OPS::stringList();

  printerList.update();
  if (printerList.length() > 0)
  {
    returnList->length(printerList.length());
    for (int i = 0; i<printerList.length(); i++)
      (*returnList)[i] = CORBA::string_dup(printerList[i].data());
  }
  TRACE_RETURN(trace, getPrinters, "");
  return returnList;

}

//*****************************************************************************
void OpsParserListenerImpl::printFile(const char* fileName,
                           const char *printer)
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
  TRACE_IN(trace, printFile, fileName << ", " << printer);

  RWCString filename = ozt_normalisePath(fileName);

  CHA_PrinterPipe pipe(printer);

  if (pipe.status() == CHA_PrinterPipe::OKAY)
  {
    ostream& pipe_stream = pipe.send();

    // Print the file from the file_store
    char c;
    int result;

    RWFile file(filename, "r");
    if ((file.isValid() == TRUE) && (file.Exists() == TRUE))
    {
      for (result = file.Read(c); file.Eof() == FALSE; result = file.Read(c))
      {
       TRACE_FLOW(trace, printFile, "result=" << result);
        if (result == TRUE)
          pipe_stream << c;
      }
      pipe_stream << ends;  // properly end the stream
    }
    else
    {
      RWCString report = ozt_nlsCatalog.getMessage(OZT_NLS_THE_FILE, "The file")
                  + " \"" + fileName + "\" "
                  + ozt_nlsCatalog.getMessage(OZT_NLS_CANNOT_BE_ACCESSED,
                                       "cannot be accessed");
      TRACE_INFO(trace, printFile, report);
      throw OPS::OPS_Exception(OPS::FILE_NOT_ACCESSIBLE, report);
    }
  }
  else
  {
    RWCString report = ozt_nlsCatalog.getMessage(OZT_NLS_NO_SUCH_PRINTER, "No such printer:")
                + " \"" + printer + "\"";
    TRACE_OUT(trace, printFile, report);
    throw OPS::OPS_Exception(OPS::NO_SUCH_PRINTER, report);
  }
  TRACE_OUT(trace, printFile, "");
}

//*****************************************************************************
void OpsParserListenerImpl::printText(const char* text,
                           const char *printer)
  throw (CORBA::SystemException, OPS::OPS_Exception)
{
 TRACE_IN(trace, printText, "text, " << printer);

  if (text != NULL && strlen(text) > 0) {

    CHA_PrinterPipe pipe(printer);

    if (pipe.status() == CHA_PrinterPipe::OKAY)
    {
      ostream& pipe_stream = pipe.send();
      pipe_stream << text;
    }
    else
    {
      RWCString report = ozt_nlsCatalog.getMessage(OZT_NLS_NO_SUCH_PRINTER, "No such printer:")
                  + " \"" + printer + "\"";
      TRACE_OUT(trace, printText, report);
      throw OPS::OPS_Exception(OPS::NO_SUCH_PRINTER, report);
    }
  }
  else
  {
    RWCString report = ozt_nlsCatalog.getMessage(OZT_NLS_NO_TEXT, "No text selected");
    TRACE_OUT(trace, printText, report);
    throw OPS::OPS_Exception(OPS::NO_TEXT, report);
  }
  TRACE_OUT(trace, printText, "");
}
//*****************************************************************************
RWCString OpsParserListenerImpl::getSessionId() {
  TRACE_RETURN(trace, getSessionId, sSessionId_);
  return sSessionId_;
}
//*****************************************************************************
char * OpsParserListenerImpl::getSessionID()
  throw (CORBA::SystemException, OPS::OPS_Exception){
    TRACE_IN(trace, getSessionID, "");

    RWCString id;

    id = pSourceMgr->getSessionId();

    if( id != "-1"  ){
     TRACE_OUT(trace, getSessionID, id);
      return CORBA::string_dup(id.data());
    }

 TRACE_INFO(trace, getSessionID, "OPS_EXCEPTION: Cannot read the session id from the file " );

  throw OPS::OPS_Exception(OPS::FILE_NOT_LOADED,
                             ozt_nlsCatalog.getMessage(OZT_NLS_SESSION_READ_ERROR,
                                                       "Cannot read the session id from the file:") );
}
//*****************************************************************************
char * OpsParserListenerImpl::getCentralDir()
  throw (CORBA::SystemException)
{
  TRACE_IN(trace, getCentralDir, "");
  RWCString temp;
  if(ozt_info.getCentralDir(temp) == CHA_OZTInfo::OKAY) {
    TRACE_OUT(trace, getCentralDir, temp);
    return CORBA::string_dup(temp);
  }
  else {
   TRACE_OUT(trace, getCentralDir, "");
    return CORBA::string_dup("");
  }
}

//*****************************************************************************
char * OpsParserListenerImpl::getPrivateDir()
  throw (CORBA::SystemException)
{
  TRACE_IN(trace, getPrivateDir, "");
  RWCString temp;
  if (ozt_info.getPrivateDir(temp) == CHA_OZTInfo::OKAY) {
    TRACE_OUT(trace, getPrivateDir, temp);
    if(temp.isNull() || temp.length() < 1)
        temp = "/";
    return CORBA::string_dup(temp);
  }
  else {
    TRACE_OUT(trace, getPrivateDir, "");
    return CORBA::string_dup("/");
  }
}

//*****************************************************************************
char * OpsParserListenerImpl::getResponseDir()
  throw (CORBA::SystemException)
{
  TRACE_IN(trace, getSaveDir, "");
  RWCString temp;
  if (ozt_info.getSaveDir(temp) == CHA_OZTInfo::OKAY) {
    TRACE_OUT(trace, getSaveDir, temp);
    if(temp.isNull() || temp.length() < 1)
        temp = "/";
    return CORBA::string_dup(temp);
  }
  else {
    TRACE_OUT(trace, getSaveDir, "");
    return CORBA::string_dup("/");
  }
}

//*****************************************************************************

// run_loop() - run the script. Return the result code.
OZT_Result OpsParserListenerImpl::run_loop(RWCString file, RWBoolean tags_only)
{
  RWBoolean   got_breakpoint = FALSE;
  RWCString   filename = file;
  RWCString   outputMsg;
  RWCString   runningMsg;
  OZT_Result  result;
  RWBoolean   got_file;
  RWBoolean   swapped_file;
  RWBoolean   skip_comments = TRUE;  // Don't skip comments for tags.
  LineNo      line_no;
  LineNo      num_lines;

  TRACE_IN(trace, run_loop, file << ", " << tags_only);
  stopped = FALSE;
  running = TRUE;

  result = pSourceMgr->setCurrPos(filename, current_position);
  TRACE_FLOW(trace, run_loop, "Position set to " << current_position <<
                                " result is " << result.code);

  if (result.code == OZT_Result::NO_PROBLEM)
  {
    show_position(filename, current_position);
    result = pSourceMgr->step(file_count);
    TRACE_FLOW(trace, run_loop, "(a)Step executed, line " << current_position <<
                                " result is " << result.code);
  }


  while (result.code == OZT_Result::NO_PROBLEM && !stopped)
  {
    TRACE_FLOW(trace, run_loop, "In while");
    if (isPaused_) {
      TRACE_FLOW(trace, run_loop, "isPaused");
      sleep(2);
      continue;
    } // if (isPaused_)

    pSourceMgr->getCurrPos(filename, line_no, num_lines);
    current_position = line_no;

    TRACE_FLOW(trace, run_loop, "Currpos:" << current_position);
    // See if the running file is loaded in the debugger fOZT_RspReceiveror
    // tags + breakpoints

    // Solution for HD46575:
    // The flag swapped_file is set to TRUE whenever the active file changes. In
    // case the parser processes an include-statement, the GUI must be notified,
    // even when "update pointer" is not active in the GUI.
    if (filename == file_entry[running_file_number]->get_full_name()) {
      got_file = TRUE;
      swapped_file = FALSE;
    }
    else {
      got_file = FALSE;
      swapped_file = TRUE;
      for (int i=0; i<file_count; i++) {
        if (file_entry[i]->get_full_name() == filename) {
          running_file_number = i;
          got_file = TRUE;
        }
      }
    }

    TRACE_FLOW(trace, run_loop, "handle tags");

    // Handle tags
    if (tags_only && got_file) {
      skip_comments = FALSE;
      current_position = file_entry[running_file_number]->get_next_tag(current_position);
      if (current_position < 0)
        break;
      result = pSourceMgr->setCurrPos(filename, current_position, skip_comments);
      pSourceMgr->getCurrPos(filename, line_no, num_lines);
      current_position = line_no;
    }

    //ozt_evHandlerPtr->dispatchEvents();
    TRACE_FLOW(trace, run_loop, "handle breakpoints");

    // Handle breakpoints
    if ((file_entry[running_file_number]->get_breakpoint(current_position, num_lines)
        == TRUE) && got_file) {
      got_breakpoint = TRUE;
      break;        // get out of here if there's a breakpoint
    }

    if (current_position != line_no)
      pSourceMgr->setCurrPos(filename, current_position);
    if (posUpdate_ || swapped_file)
      show_position(filename, current_position);
    result = pSourceMgr->step(file_count, skip_comments);
    TRACE_FLOW(trace, run_loop, "(b)Step executed, line " << current_position <<
                                   " result is " << result.code);
  } //while

  TRACE_FLOW(trace, run_loop, "after while");

  // Output some text to the response window to show what's happened.
  if (got_breakpoint){
    outputMsg = "\n" + ozt_nlsCatalog.getMessage(OZT_NLS_RUN_STOP_BREAKPOINT,
                                                 "Run stopped: Breakpoint") + "\n";
    result.code = OZT_Result::INTERRUPTED;
  }
  else if (stopped){
    outputMsg = "\n" + ozt_nlsCatalog.getMessage(OZT_NLS_RUN_STOP_INTERRUPT,
                                                 "Run stopped: Interrupted") + "\n";
    result.code = OZT_Result::INTERRUPTED;
  }
  else {
    if (result.code != OZT_Result::INCLUDE_NOT_EXECUTED)
    {
       outputMsg = "\n" + ozt_nlsCatalog.getMessage(OZT_NLS_RUN_STOP,
                                                    "Run stopped:")
                   + " " + result.toMsg() + "\n";
    }
  }

  TRACE_FLOW(trace, run_loop, "appending outputmsg");
  if (action != QUIT) {
    TRACE_FLOW(trace, run_loop, outputMsg);
    cmdRspBuf_->append(outputMsg.data());
  }

  if(nJobId_ != -1)
    removeJobFromAM();

  running = FALSE;

  TRACE_RETURN(trace, run_loop, result.toMsg());
  return result;
}

//*****************************************************************************
// close_a_file(): IMPORTANT - The view_file selector and the view_file_number
//                             may need to be updated after calling this.
RWBoolean OpsParserListenerImpl::close_a_file(int file_number)
{
  TRACE_IN(trace, close_a_file, "file_number = " << file_number);

  // Make sure that the file to close exists
  if ((file_number >= file_count) || (file_count == 0)) {
    TRACE_RETURN(trace, close_a_file, "FALSE");
    return FALSE;
  }

  delete file_entry[file_number];

  // Move all the other files down one to fill the gap
  file_count--;
  for (int i=file_number; i<file_count; i++) {
    file_entry[i] = file_entry[i+1];
  }

  TRACE_RETURN(trace, close_a_file, "TRUE");
  return TRUE;
}

//*****************************************************************************
RWBoolean OpsParserListenerImpl::issetuiddone()
{
  TRACE_IN(trace, issetuiddone, "");

  if (setuidDone == TRUE) {
        TRACE_FLOW(trace, issetuiddone, "setuidDone=TRUE");
  } else {
        TRACE_FLOW(trace, issetuiddone, "setuidDone=FALSE");
  }

  TRACE_RETURN(trace, issetuiddone, "");
  return setuidDone;
}

//*****************************************************************************
//open_a_file(): Open a file with the name and path given & load it into the
//               appropriate code_sw. Make the code_sw visible if running the
//               debugger.
RWBoolean OpsParserListenerImpl::open_a_file (RWCString dir_path, RWCString name)
{
  TRACE_IN(trace, open_a_file, dir_path.data() << ", " << name.data());

  RWCString fullname = "";
 // char tmp_path[MAXPATHLEN+1];
  int i;

  // Check that we haven't exceeded the maximum number of open files.
  if (file_count >= MAX_OPEN_FILES)
  {
    TRACE_RETURN(trace, open_a_file, "FALSE - too many files open");
    return FALSE;
  }

  // Check that the file isn't already open

  if (name.first('/') == 0) {
    fullname = name;
  }
  else if ((dir_path == "")&&(name != "")) {
  //  getcwd(tmp_path, MAXPATHLEN+1);
   // fullname = (RWCString)tmp_path + "/" + name;
  }
  else if (name != "")
    fullname = dir_path + "/" + name;

  if (name != "")
    fullname = ozt_normalisePath(fullname);

  for (i=0; i<file_count; i++)
    if (file_entry[i]->get_full_name() == fullname) {
       TRACE_RETURN(trace, open_a_file, "FALSE - already open");
       return FALSE;
    }

  // Open the file
  if ((file_entry[file_count] = new OZT_CDFFile("", fullname,
                                               file_entry, file_count))==0) {
    cerr<< "Out of Memory"<<endl;
    exit(-1);
  }

  file_entry[file_count]->set_time_stamp();

  file_count++;
//  if (view_file_number != (file_count-1))
//    view_file(file_entry[file_count-1]->get_full_name(), FALSE);

   TRACE_RETURN(trace, open_a_file, "TRUE");
   return TRUE;
}

//*****************************************************************************
// sync_file() : Make sure that the file hasn't been changed by
//               another editor and synchronize if it has. Return
//               TRUE if it is synchronized OK.
RWBoolean OpsParserListenerImpl::sync_file(int file_number, RWBoolean notice)
{
  TRACE_IN(trace, sync_file, "");

  RWBoolean result = FALSE;
  RWBoolean loadIt = FALSE;

  if (file_entry[file_number]->is_changed())
  {
    // The file has changed on disk.

    // If we are running (except for single-stepping) a command
    // file we silently load in the file and don't ask for
    // confirmation because we don't want to interrupt the script
    // execution by popping up a notice box.  (This is a problem
    // only of the position marker is continously updated.)

    TRACE_FLOW(trace, sync_file, "action == " << action);

    if (!notice) {
      TRACE_FLOW(trace, sync_file, "load silently");
      loadIt = TRUE;
    }
    else {
      TRACE_FLOW(trace, sync_file, "dialog box displayed");
      // Ask for confirmation before synchronizing the file.
      // This message cannot be turned off by the props window.
      RWCString notice_string;
      notice_string = file_entry[file_number]->get_full_name() + " " +
         ozt_nlsCatalog.getMessage(OZT_NLS_NOT_UPTODATE,
                                  "has been changed by another editor.\nReload it?");
      if (serverRLRef_->askForConfirmation(notice_string) == OPS::DIALOG_RETURNS_OK) {
        loadIt = TRUE;
      }
    }
  }
  else {
    result = TRUE;
  }

  if (loadIt) {
    TRACE_FLOW(trace, sync_file, "about to load the file");
    // Load the file into the code window and the source manager.
    serverRLRef_->setCurrentFile(file_entry[file_number]->get_full_name().data());

    file_entry[file_number]->set_time_stamp();
    (void)pSourceMgr->update(file_entry[file_number]->get_full_name());

    result = TRUE;
  }

  TRACE_RETURN(trace, sync_file, result);
  return result;
}

//*****************************************************************************
// show_position() - Display the name of the file, the current line
//                   number and the total number of lines.
void OpsParserListenerImpl::show_position(RWCString fullFileName, int lineNo)
  throw (OPS::OPS_Exception)
{

  RWCString pathName, fileName;

  TRACE_IN(trace, show_position, fullFileName << ", " << lineNo);
  int i = fullFileName.last('/');

  //
  // Split the path
  //
  if (i == RW_NPOS)
  {
    pathName = RWCString();
    fileName = fullFileName;
  }
  else
  {
    pathName = fullFileName(0, i);
    fileName = fullFileName(i+1, fullFileName.length()-i-1);
  }

  //
  // View the file in if it's not already being viewed.
  //
  if (fullFileName != file_entry[view_file_number]->get_full_name())
  {
    // If an already loaded file is out of sync with regards to
    // the version on disk we silently load in the file because we
    // are currently running a script and don't want to interrupt
    // the execution by popping up a notice box. See TR
    // AD19009. This is the "FALSE" parameter to view_file...
    if (view_file(fullFileName, FALSE) == FALSE)
    {
      // Load the file because it's not already loaded.
      if (!open_a_file(pathName, fileName))
      {
        // failed to open the file
        throw OPS::OPS_Exception(OPS::FILE_NOT_LOADED,
                                 ozt_nlsCatalog.getMessage(OZT_NLS_FILE_OPEN_ERROR,
                                                          "Cannot open file:") +
                                 " " + fullFileName);
      }
      if (view_file_number != (file_count-1))
        view_file(file_entry[file_count-1]->get_full_name(), FALSE);
    }
  }
  TRACE_FLOW(trace, show_position, "before setCurrentPosition" );
  OPS::Position* posStruct = new OPS::Position;
  posStruct->pos = lineNo;
  posStruct->file =  CORBA::string_dup(fullFileName.data());
  try {
        if (clientType_ == OPS::GUI) serverRLRef_->setCurrentPositionP(*posStruct);
  }
  catch (...) {
        TRACE_FLOW(trace, show_position, "setCurrentPosition failed");
  }
  delete posStruct;
  TRACE_OUT(trace, show_position, "");
}

//*****************************************************************************
//Shall not be used by client any more, phase
//description is sent to client by sourceMgr object whenever it is set and changed
 char * OpsParserListenerImpl::getPhaseDescription() {
  return strdup((const char*)pSourceMgr->getPhaseDescription());
}

//*****************************************************************************
//Shall not be used by client any more, error
//description is sent to client by sourceMgr object whenever it is changed
char * OpsParserListenerImpl::getErrorDescription(){
    return CORBA::string_dup((const char*)sErrorMsg_);
}

//*****************************************************************************
void OpsParserListenerImpl::sendErrorMsg(){
    char* str = CORBA::string_dup((const char*)sErrorMsg_);
    serverRLRef_->setErrorInfo(str);
    CORBA::string_free(str);
}
//*****************************************************************************
//Shall not be used by client any more, progress
//is sent to client by sourceMgr object whenever it is set and changed
//Geet -long OpsParserListenerImpl::getProgress(){
CORBA::Long OpsParserListenerImpl::getProgress(){
    return pSourceMgr->getProgress();
}

//*****************************************************************************
//Shall not be used by client any more, totalcount
//is sent to client by sourceMgr object whenever it is set
//Geet -long OpsParserListenerImpl::getTotalCount(){
CORBA::Long OpsParserListenerImpl::getTotalCount(){
    return pSourceMgr->getTotalCount();
}

//*****************************************************************************

//Geet long OpsParserListenerImpl::getLineNumber() {
CORBA::Long OpsParserListenerImpl::getLineNumber() {
  LineNo      line_no;
  LineNo      num_lines;
  RWCString   filename;

  TRACE_IN(trace, getLineNumber, "");
  pSourceMgr->getCurrPos(filename, line_no, num_lines);
  TRACE_OUT(trace, getLineNumber, line_no);
  return line_no;
}

//*****************************************************************************

char * OpsParserListenerImpl::getCommandFileName() {
  LineNo      line_no;
  LineNo      num_lines;
  RWCString   filename;

  TRACE_IN(trace, getCommandFileName, "");
  pSourceMgr->getCurrPos(filename, line_no, num_lines);
  TRACE_OUT(trace, getCommandFileName, filename);

  return CORBA::string_dup(filename.data());
}

//*****************************************************************************

void OpsParserListenerImpl::pause(){
  TRACE_IN(trace, pause, "");
  isPaused_ = TRUE;
  TRACE_OUT(trace, pause, "TRUE");
}

//*****************************************************************************

void OpsParserListenerImpl::cont(){
  TRACE_IN(trace, cont, "");
  isPaused_ = FALSE;
  TRACE_OUT(trace, cont, "FALSE");
}

//*****************************************************************************

void OpsParserListenerImpl::sendMail(const char* sReceiver,
                          const char* sSubject,
                          const char* sContent){

  TRACE_IN(trace, sendMail, sReceiver)

      // OZT_Mail could be used but this only requires a few lines.

  char sTmpFile[L_tmpnam];
  //tmpnam(sTmpFile);
  mkstemp(sTmpFile);
  ofstream rStream;
  FILE *pFp;

  // get smtp server (lvsrouter entry from /ericsson/tor/data/global.properties)
  RWCString smtpAddr = getenv("OPS_SMTP_SERVER");
  smtpAddr = (RWCString)" -S " + (RWCString)"smtp=" + smtpAddr + " ";

  RWCString sCmd = (RWCString)"mailx" + smtpAddr + (RWCString)"-s " + sSubject + (RWCString)" " + sReceiver + (RWCString)" < " + sTmpFile;
  TRACE_FLOW(trace, sendMail, sCmd);

  rStream.open(sTmpFile, ios::out);
  rStream << sContent << endl;
  rStream.close();

  if((pFp=popen(sCmd, "w")) == NULL)
    TRACE_FLOW(trace, sendMail, "Could not open file");
  pclose(pFp);
  unlink(sTmpFile);

  TRACE_OUT(trace, sendMail, "");
}

//*****************************************************************************
// view_file() - Display the file contents in the code text pane
//      returns TRUE if the requested file ends up on the display
//
RWBoolean OpsParserListenerImpl::view_file(RWCString filename, RWBoolean notice)
{
  TRACE_IN(trace, view_file, filename.data());

  int file_number;

  // Find the file that needs to be viewed
  file_number = -1;
  for (int i=0; i<file_count; i++)
  {
    if (file_entry[i]->get_full_name() == filename)
    {
      file_number = i;
      break;  // exit the for loop
    }
  }

  // Only do anything if it's a loaded file
  if (file_number == -1)
  {
    TRACE_RETURN(trace, view_file, "FALSE - file not loaded");
    return FALSE;
  }

  // Check that the file is up to date, but view it either way;
  (void)sync_file(file_number, notice);

  view_file_number = file_number;

  serverRLRef_->setCurrentFile(filename);

  TRACE_RETURN(trace, view_file, "TRUE");
  return TRUE;
}


//*****************************************************************************
char* OpsParserListenerImpl::ltorwcs(const long n) const
{
  ostrstream os;
  os << n << '\0';
  char* s = os.str();
  delete [] os.str();
  return s;
}

//*****************************************************************************

void* OpsParserListenerImpl::IamAliveThread(void* x){
  ((OpsParserListenerImpl*)x)->IamAlive();
  return NULL;
}

//*****************************************************************************

void OpsParserListenerImpl::IamAlive()
{
  int timeInterval = OPS::ServerRouterListener::OPS_SESSION_SUPERVISION_TIME;
  int timeIntervalAtStart = OPS::ServerRouterListener::OPS_STARTING_SUPERVISION_TIME;
  RWBoolean isStartPhase = true;
  int failedAttempts = 0;
  int MAX_NR_OF_ATTEMPTS = 5;

  TRACE_IN(trace, IamAlive, "");

  RWBoolean clientOrServerLost = false;
  while (!shuttingDown_) {
    try {
      TRACE_FLOW(trace, IamAlive, "");

      if (!shuttingDown_) {
        if (!serverRLRef_->parserAlive(sSessionId_)) {
          failedAttempts++;
          if (failedAttempts >= MAX_NR_OF_ATTEMPTS) {
            TRACE_INFO(trace, OpsParserListenerImpl, "Client not exist");
            shuttingDown_ = true;
            clientOrServerLost = true;
          }
        }
        else
        {
          isStartPhase = false;
          failedAttempts = 0;
        }
      }
    }
    catch(const CORBA::Exception& x) {
      failedAttempts++;
      if (failedAttempts >= MAX_NR_OF_ATTEMPTS) {
        TRACE_INFO(trace, OpsParserListenerImpl, "Server not exist");
        shuttingDown_ = true;
        clientOrServerLost = true;
      }
    }

    if (shuttingDown_ == false) {
      if (isStartPhase) {
        sleep(timeIntervalAtStart);
      }
      else
      {
        sleep(timeInterval);
      }
    }
  }

  // Only shut down if we exited the alive loop because our peers
  // are gone. Otherwise, we will race with the releaseParser method
  // to shut down during a controlled shutdown.
  if (!waitingForServerRestart_ && clientOrServerLost) {
    TRACE_FLOW(trace, IamAlive, "Requesting shutdown");
    shutdown();
  }
}

//*****************************************************************************

void OpsParserListenerImpl::getExternalSystem(CORBA::String_out sEs,
                                   CORBA::Boolean& isStandBy)
{
  TRACE_IN(trace, getExternalSystem, "2 parameters");

  sEs = CORBA::string_dup(connectionObject_->getEsName());
  // TODO isStandby = (connectionObject_->IsStandbySide())? 1 : 0;
  isStandBy = 0;
  TRACE_OUT(trace, getExternalSystem, "2 parameters");
}


//*****************************************************************************

void OpsParserListenerImpl::connectToSession(OPS::ServerRouterListener_ptr serverRLRef,
                                             int sessionId,
                                             OPS::ClientType listenerType,
                                             const char* userId,
                                             const char* pwd)
  throw(OPS::OPS_Exception){

  TRACE_IN(trace, connectToSession, userId);

  // TO BE DONE LATER

  makeUiWindows();

  TRACE_OUT(trace, connectToSession, "");
}

//*****************************************************************************

void OpsParserListenerImpl::makeUiWindows(){
  TRACE_IN(trace, makeUiWindows, "ClientType:" << clientType_);

  RWCString        report;

  // Create the IO window popup handler.

  // HF95902
  // ioWin_ may have a list of draw commands cached and waiting to be executed in the client
  // hence we cannot just delete and recreate it when there is a new listener.
  if(ioWin_ != NULL)
    //    delete ioWin_;
    ioWin_->changeListener(serverRLRef_, clientType_);
  else {
    // HF65265
    //  if ((ioWin_ = new OZT_IOWin(serverRLRef_)) == 0) {
    if ((ioWin_ = new OZT_IOWin(serverRLRef_, clientType_)) == 0) {
      // END HF65265
      report = ozt_formatReport("",
                                "",
                                "",
                                ozt_nlsCatalog.getMessage(OZT_NLS_OUT_OF_MEMORY,"Out of Memory, application stops"));
      TRACE_INFO(trace, OpsParserListenerImpl, report);
      throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
    }
  }
  // END HF95902



  // Recreate the inkey popup handler.

  if(inkeyWin_ != NULL)
    delete inkeyWin_;
  if ((inkeyWin_ = new OZT_InkeyWin(serverRLRef_))==0){
    report = ozt_formatReport("",
                              "",
                              "",
                              ozt_nlsCatalog.getMessage(OZT_NLS_OUT_OF_MEMORY,
                                                        "Out of Memory, application stops"));
    TRACE_INFO(trace, OpsParserListenerImpl, report);
    throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
  }


  // Recreate the input popup handler.

  if(inputWin_ != NULL)
    delete inputWin_;
  if ((inputWin_ = new OZT_InputWin(serverRLRef_))==0){
    report = ozt_formatReport("",
                              "",
                              "",
                              ozt_nlsCatalog.getMessage(OZT_NLS_OUT_OF_MEMORY,
                                                        "Out of Memory, application stops"));
    TRACE_INFO(trace, OpsParserListenerImpl, report);
    throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
  }


  // Recreate the prompt window handler.

  if(prompt_ != NULL)
    delete prompt_;
  if ((prompt_ = new OZT_Prompt(serverRLRef_))==0){
    report = ozt_formatReport("",
                              "",
                              "",
                              ozt_nlsCatalog.getMessage(OZT_NLS_OUT_OF_MEMORY,
                                                        "Out of Memory, application stops"));
    TRACE_INFO(trace, OpsParserListenerImpl, report);
    throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
  }


  // Recreate the file selector.

  if(fileSelector_ != NULL)
    delete fileSelector_;
  if ((fileSelector_ = new OZT_FileSelector(serverRLRef_))==0){
    report = ozt_formatReport("",
                              "",
                              "",
                              ozt_nlsCatalog.getMessage(OZT_NLS_OUT_OF_MEMORY,
                                                      "Out of Memory, application stops"));
    TRACE_INFO(trace, OpsParserListenerImpl, report);
    throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
  }


  // Recreate the file viewer.

  if(fileViewer_ != NULL)
    delete fileViewer_;
  if ((fileViewer_ = new OZT_FileViewer(serverRLRef_))==0){
    report = ozt_formatReport("",
                              "",
                              "",
                              ozt_nlsCatalog.getMessage(OZT_NLS_OUT_OF_MEMORY,
                                                        "Out of Memory, application stops"));
    TRACE_INFO(trace, OpsParserListenerImpl, report);
    throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
  }

  // Recreate the Variable Watcher
  if (variableWatcher_!= NULL)
  {
    delete variableWatcher_;
    if ((variableWatcher_ = new VariableWatcher(pSourceMgr, serverRLRef_))==0) {
      cleanup();
      report = ozt_formatReport("",
                                "",
                                "",
                                ozt_nlsCatalog.getMessage(OZT_NLS_OUT_OF_MEMORY,
                                                          "Out of Memory, application stops"));
      TRACE_INFO(trace, OpsParserListenerImpl, report);
      throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
    }
    pSourceMgr->getVarStore().addDependent(variableWatcher_);
  }

  // Recreate the child script handler. (not really a window...)

  if(childHandler_ != NULL)
    delete childHandler_;
  if ((childHandler_ = new OZT_ChildHandler(serverRLRef_))==0){
    report = ozt_formatReport("",
                              "",
                              "",
                              ozt_nlsCatalog.getMessage(OZT_NLS_OUT_OF_MEMORY,
                                                        "Out of Memory, application stops"));
    TRACE_INFO(trace, OpsParserListenerImpl, report);
    throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
  }


  TRACE_OUT(trace, makeUiWindows, "");
}

//*****************************************************************************

// Here, events from everything that inherits from CHA_Model is received.
void OpsParserListenerImpl::updateFrom(CHA_Model* pModel, void* value)
{
  TRACE_IN(trace, updateFrom, "CHA_Model");

  if (action == QUIT)
  {
    // Cannot do anything if the frame has been quit.
    TRACE_OUT(trace, updateFrom, "QUIT");
    return;
  }

  if ((OZT_CmdRspBuf*)pModel == cmdRspBuf_)
  {
    TRACE_FLOW(trace, updateFrom, "pModel = OZT_CmdRspBuf");
    OZT_CmdRspBuf  *pbuf = (OZT_CmdRspBuf*)pModel;
    RWCString       text;
    long mark=0;

    //check if the mark value is sent
    if( value != NULL ){
      //covert to the correct type
      mark = *((long*)value);
      TRACE_FLOW(trace, updateFrom, "pModel = OZT_CmdRspBuf, mark:" << mark);
      try {
        if (serverRLRef_ != NULL && clientType_ == OPS::GUI) serverRLRef_->updateMarkPosition( mark );
      }
      catch (...) {
        TRACE_INFO(trace, updateFrom, "updateMarkPosition failed");
      }
      TRACE_RETURN (trace, updateFrom, "");
      return;
    }
    // See if the screen needs to be cleared.
    if (pbuf->toClearScr() == TRUE)
    {
      //TBD
      // We will never get here since OZT_CmdRspBuf::clrScr() is never used.
      // If changed in the future, add a method on the listener.
      // serverRLRef_->clearResult();
    }

    // Append new printout data to the response pane
    RWBoolean toFormat = pbuf->getFormatFlag();
    text = pbuf->getUpdateText();
    TRACE_FLOW(trace, updateFrom, "buffer text : " << text);
    if (!shutdownProcessing_)
    {
      try {
      	TRACE_FLOW(trace, updateFrom, "pModel = OZT_CmdRspBuf, position:" << current_position);
        if (serverRLRef_ != NULL)serverRLRef_->showResult(text.data(), toFormat,current_position);
      }
      catch (...) {
        TRACE_INFO(trace, updateFrom, "showResult failed");
      }
    }
  }
  else if ((CHA_Connection*)pModel == connectionObject_)
  {
    TRACE_FLOW(trace, updateFrom, "pModel = CHA_Connection");
    CHA_Connection  *con = (CHA_Connection*)pModel;

    // Display the name of the connected ES
    //if (con->getConnectionStatus() != -1)
    if (con->getConnectionStatus() == 4)
    {
// TODO  standby: serverRLRef_->setExternalSystem((char*)con->GetEsName().data(), con->IsStandbySide() );
     if (serverRLRef_ != NULL) serverRLRef_->setExternalSystem((char*)con->getEsName().data(), 0 );
    }
    else
    {
      if (serverRLRef_ != NULL) serverRLRef_->setExternalSystem("", FALSE);
    }
  }
  else if((OZT_RspCatcher*)pModel == responseCatcher_ ) {

    OZT_RspCatcher::State state = responseCatcher_->getState();
    TRACE_FLOW(trace, updateFrom, "pModel = OZT_RspCatcher state:" << state );
    if( state == OZT_RspCatcher::IDLE ){
        TRACE_FLOW(trace, updateFrom, "stopWaitTimer");
        if (serverRLRef_ != NULL) serverRLRef_->stopWaitTimer();
    }
    else if( state == OZT_RspCatcher::WAITREPLY ||
             state == OZT_RspCatcher::WAITFOR ) {
        TRACE_FLOW(trace, updateFrom, "startWaitTimer");
        if (serverRLRef_ != NULL) serverRLRef_->startWaitTimer();
    }
  }
  else if ((OZT_Indicator*)pModel == indicator_)
  {
    TRACE_FLOW(trace, updateFrom, "pModel = OZT_Indicator");

    // Display the message
    if (value != NULL)
      if (serverRLRef_ != NULL) serverRLRef_->showMessage(((RWCString*)value)->data());
  }
  else if ((OZT_CommentWinModel*)pModel == commentWinModel_)
  {
    TRACE_FLOW(trace, updateFrom, "pModel = OZT_CommentWinModel");

    // Display the message
    if (value != NULL) {
        // Append new printout data to the response pane
      RWBoolean toFormat = commentWinModel_->toFormat();
      if (serverRLRef_ != NULL) serverRLRef_->showComment(((RWCString*)value)->data(), toFormat);
    }
    else {
       if (commentWinModel_->toClear())
         {
           if (serverRLRef_ != NULL) serverRLRef_->clearCommentWindow();
         }
      else if (commentWinModel_->isActive())
        // Added due to TR HD53556
        //Check if GUI or NUI
        if (clientType_ == OPS::GUI && serverRLRef_ != NULL)serverRLRef_->openCommentWindow();
      else
        if (!commentWinModel_->isActive() && serverRLRef_ != NULL)serverRLRef_->closeWindows();
    }
  }

  TRACE_OUT(trace, updateFrom, "");
}

//*****************************************************************************

void OpsParserListenerImpl::detachFrom(CHA_Model *model)
{
  TRACE_IN(trace, detachFrom, "");
  TRACE_OUT(trace, detachFrom, "");
}

//*****************************************************************************
void OpsParserListenerImpl::releaseParser()
{
   TRACE_IN(trace, releaseParser, "");

   // Check client chagend should be done in server router!
   TRACE_FLOW(trace, releaseParser, "Client quit");
   shutdown();


   TRACE_OUT(trace, releaseParser, "");
}

//*****************************************************************************

CORBA::Boolean OpsParserListenerImpl::isConnected()
{
        TRACE_IN(trace, isConnected, "");

        CORBA::Boolean result = false;
        //if (pSourceMgr->getCmdSender().getConnectionObject().getConnectionStatus() != -1 /*==        EAC_CRI_CS_CONNECTED*/) {
	if (pSourceMgr->getCmdSender().getConnectionObject().getConnectionStatus() == 4) {
                result = true;
        }

        TRACE_OUT(trace, isConnected, "");
        return result;
}

//*****************************************************************************

CORBA::Boolean OpsParserListenerImpl::isRunning()
{
        TRACE_IN(trace, isRunning, "");

        CORBA::Boolean result = false;
        if (action == RUN) {
          result = true;
        }
        TRACE_FLOW(trace, isRunning, "result = " << result);
        TRACE_OUT(trace, isRunning, result);
        return result;
}

//*****************************************************************************

/*CORBA::Boolean OpsParserListenerImpl::isRecoveryEnabled()
{
        ////TRACE_IN(trace, isRecoveryEnabled, "");

        CORBA::Boolean result = recoveryEnabled_;

        ////TRACE_OUT(trace, isRecoveryEnabled, result);
        return result;
        }*/

//*****************************************************************************

/*void OpsParserListenerImpl::setRecoveryEnabled(CORBA::Boolean enabled)
{
        ////TRACE_FLOW(trace, setRecoveryEnabled, "recovery" << enabled);
        recoveryEnabled_ = enabled;

        }*/



//*************************************************************************************************
//New Mthodes for OSS-RC R4

//----------------------------------------------------------------------
void OpsParserListenerImpl::ping(){
  TRACE_IN(trace, ping, "");
  // This method is here just to let the server to ping the parser to check
  // if the session is ok
  return;
}

//----------------------------------------------------------------------
//Geet -long OpsParserListenerImpl::getPid(){
 CORBA::Long OpsParserListenerImpl::getPid(){
  TRACE_IN(trace, getPid, pid);
  return  pid;
}

//----------------------------------------------------------------------
void OpsParserListenerImpl::serverRestarting(){
  TRACE_IN(trace, serverRestarting, "");
  // Server is restarting, stop sending I am alive and response to server
  serverRLRef_ = NULL; // No communication towards server should be done.
  waitingForServerRestart_ = TRUE;
  shuttingDown_ = TRUE;
  TRACE_FLOW(trace, serverRestarting, "********** action = " << action);
  pthread_cancel(pThreadId_);
  //Start a thread to check server, if server is not up within 5 min. terminate parser!
  createDetachedThread(&pThreadSRId_, OpsParserListenerImpl::checkServerThread);

  TRACE_OUT(trace, serverRestarting, "");
}

//----------------------------------------------------------------------
void* OpsParserListenerImpl::checkServerThread(void* x){
  ((OpsParserListenerImpl*)x)->checkServer();
  return NULL;
}

//----------------------------------------------------------------------
void OpsParserListenerImpl::checkServer(){
  TRACE_IN(trace, checkServer, "");

  OpsParserOrbHandler* orbHdlRef = OpsParserOrbHandler::getInstance();

  // wait until server is down and a new server is up,
  //otherwise you will get ref to the terminating object
  sleep(2 * OPS::ServerRouterListener::OPS_STARTING_SUPERVISION_TIME);
  TRACE_FLOW(trace, checkServer, "Try to get server router ref");
  serverRLRef_ = orbHdlRef->getServerRouterRef(1); // 1 means it's about a server restart
  if (serverRLRef_ != NULL)
  {
    TRACE_FLOW(trace, checkServer, "Ref to server router OK after server restarted");
    handleServerRestarted();
  }
  else
    shutdown();

TRACE_OUT(trace, checkServer, "");
}

//----------------------------------------------------------------------
void OpsParserListenerImpl::handleServerRestarted(){
  TRACE_IN(trace, handleServerRestarted, "");
  shuttingDown_ = FALSE;

  pthread_mutex_lock(&shutDownInitiatedMutex_);
  shutDownInitiated_ = FALSE;
  pthread_mutex_unlock(&shutDownInitiatedMutex_);

  waitingForServerRestart_ = FALSE;
  // send IamAlive shall continue
  // Create thread to tell the server that parser is ok and alive.
  createDetachedThread(&pThreadId_, OpsParserListenerImpl::IamAliveThread);

  // The new server router ref has to be sent to all objects that call methods in the server object!
  makeUiWindows();
  pSourceMgr->setListener(serverRLRef_);
  pSourceMgr->getClock().setListener(serverRLRef_);
  variableWatcher_->setListener(serverRLRef_);
  if (action != RUN)action = NOTHING;
  //serverRLRef_->newState(OPS::RUNNING);
  TRACE_OUT(trace, handleServerRestarted, "");
}

//----------------------------------------------------------------------
void OpsParserListenerImpl::clientPassive(){
  TRACE_IN(trace, clientPassive, "");
  // A client change is on going.
  // Set action to be prepared for next action initiated by the new client
  action = NOTHING;
  TRACE_OUT(trace, clientPassive, "");
}

//----------------------------------------------------------------------
void OpsParserListenerImpl::setClientType(OPS::ClientType type){
  TRACE_IN(trace, setClientType, "clientType_ = " << type);
  clientType_ = type;
  // Inform objects about the client type
  pSourceMgr->getClock().setClientType(clientType_);
  TRACE_OUT(trace, setClientType, "");
}

//----------------------------------------------------------------------
void OpsParserListenerImpl::setSessionData(OPS::ServerRouterListener_ptr serverRLRef,
                                           RWCString sSessionId,
                                           OPS::ClientType clientType,
                                           const char* userId,
                                           const char* pwd)
{
  TRACE_IN(trace, setSessionData, "");

  serverRLRef_ = serverRLRef;
  sSessionId_ = sSessionId;
  clientType_ = clientType;
  userId_ = userId;
  pwd_ = pwd;

//Moved from ParserImpl's constructor
  RWCString        report;

  TRACE_FLOW(trace, setSessionData, "sSessionId   = " << sSessionId_);
  TRACE_FLOW(trace, setSessionData, "listenerType = " << clientType_);
  TRACE_FLOW(trace, setSessionData, "userId       = " << userId_);
  TRACE_FLOW(trace, setSessionData, "pwd          = " << pwd_);

/*	
   // Check the user and password
   if(isPasswordCorrect(userId_, pwd_) == FALSE){
    throw OPS::OPS_Exception(OPS::INCORRECT_PWD, "Incorrect user or password");
   }

  // Get the ES list while we still have the authority to use IMH.
  // It will not work after the "setuid".

  // Read from the pdb map if the "esListSource"
  // option is used.


  RWCString source;
  CHA_OZTInfo::ReturnCode rc = ozt_info.getEsListSource(source);

  CHA_EsList::NeSource neSource_ = CHA_EsList::EA; // Default

  if(source == "EA") {
    neSource_ = CHA_EsList::EA; // Default
  }
  else if(source == "IMHAPI") {
    neSource_ = CHA_EsList::IMHAPI;
  }

  // Update the CHA External System list.
  esList_.update(neSource_);
*/
/*
    // With SSH Connection in place from ops-server,
        there is no need to set supplementary groups/UID/GID for Parser process

  // Set group to "root":
  const char *rootGroupName = "root";
  struct group  rootGroup;
  struct group *rootGroupResult;
  char memBuf[_SC_GETGR_R_SIZE_MAX];

  int err = getgrnam_r(rootGroupName, &rootGroup,
                       memBuf, (size_t)_SC_GETGR_R_SIZE_MAX,
                       &rootGroupResult);
  if (err !=0 ) {

      cerr << "Unknown group: " << rootGroupName << " (" << err << ")\n";
      report = ozt_formatReport("", "", "",
                                ozt_nlsCatalog.getMessage(OZT_NLS_CANNOT_SET_USER,
                                                          "Cannot set group (unknown) to:") +
                                " \"" + rootGroupName + "\"");
      TRACE_INFO(trace, OpsParserListenerImpl, report);
      throw OPS::OPS_Exception(OPS::AUTHORITY_PROBLEM, report);
  }

  if (err = setgid(rootGroup.gr_gid) != 0) {
      cerr << "Failed to set group: " << rootGroupName << " (" << err << ")\n";
      report = ozt_formatReport("",
                                "",
                                "",
                                ozt_nlsCatalog.getMessage(OZT_NLS_CANNOT_SET_USER,
                                                          "Cannot set group to:") +
                                " \"" + rootGroupName + "\"");
      TRACE_INFO(trace, OpsParserListenerImpl, report);
      throw OPS::OPS_Exception(OPS::AUTHORITY_PROBLEM, report);
  }

  // HG13946: Set supplementary group IDs.
  if (err = initgroups(userId_, rootGroup.gr_gid) != 0) {
        cerr << "Failed to set supplementary groups: (" << err << ")\n";
        report = ozt_formatReport("",
                                "",
                                "",
                                ozt_nlsCatalog.getMessage(OZT_NLS_CANNOT_SET_USER,
                                                          "Cannot set supplementary groups"));
        TRACE_INFO(trace, OpsParserListenerImpl, report);
        throw OPS::OPS_Exception(OPS::AUTHORITY_PROBLEM, report);
  }// HG13946

  // Set user.
  passwd *pwdStruct = getpwnam(userId_);

  int ret = (pwdStruct == NULL)? -1 : setuid(pwdStruct->pw_uid);

  if (ret != 0) {
    report = ozt_formatReport("",
                              "",
                              "",
                              ozt_nlsCatalog.getMessage(OZT_NLS_CANNOT_SET_USER,
                                                        "Cannot set user to:") +
                                " \"" + userId_ + "\"");
    TRACE_INFO(trace, OpsParserListenerImpl, report);
    throw OPS::OPS_Exception(OPS::AUTHORITY_PROBLEM, report);
  } else {
        setuidDone = true;
  }

  // HD61750: Set the environment variable USER.
  static char userIdString[32];
  if (pwdStruct->pw_name != NULL) {
      strcpy(userIdString, "USER=");
      strcat(userIdString, pwdStruct->pw_name);
      putenv(userIdString);
  }

  // HOME is set accordingly:
  static char homeDirString[32];
  if (pwdStruct->pw_dir != NULL) {
      strcpy(homeDirString, "HOME=");
      strcat(homeDirString, pwdStruct->pw_dir);
      putenv(homeDirString);
  }
*/
  passwd *pwdStruct = getpwnam(userId_);
  char* opsNlsPath = getenv( "OPS_NLSPATH" );
  if(opsNlsPath != NULL)
  {
    TRACE_FLOW(trace, OpsParserListenerImpl, "NLS path: " << opsNlsPath);
    strcpy(nlsPath,"NLSPATH=");
    strcat(nlsPath,opsNlsPath);
    if(!putenv(nlsPath))
    {
      TRACE_FLOW(trace, OpsParserListenerImpl, "Failed to putenv NLSPATH");
    }
  }
  else
  {
    TRACE_FLOW(trace, OpsParserListenerImpl, "NLS path is not defined! ");
  }
 
  // Check that home directory exists.
  int ret = chdir(pwdStruct->pw_dir);
  if (ret != 0) {
    report = ozt_formatReport("",
                              "",
                              "",
                              ozt_nlsCatalog.getMessage(OZT_NLS_CANNOT_CD,
                                                        "Cannot change to directory") +
                                " \"" + pwdStruct->pw_dir + "\"");
    TRACE_INFO(trace, OpsParserListenerImpl, report);
    throw OPS::OPS_Exception(OPS::AUTHORITY_PROBLEM, report);
  }

  // Check if CHA_RESPONSE & CHA_CMDFILE are defined.

  RWCString privDir, saveDir;
  if (((ozt_info.getPrivateDir(privDir) != CHA_OZTInfo::OKAY) ||
      (ozt_info.getSaveDir(saveDir) != CHA_OZTInfo::OKAY)) && FALSE) {

    cleanup();
    report = ozt_formatReport("",
                              "",
                              "",
                              ozt_nlsCatalog.getMessage(OZT_NLS_CHA_ENV_ERROR,
                                         "OPS environment variable/s(CHA_CMDFILE \
                                          or CHA_RESPONSE) error, application stops"));
    TRACE_OUT(trace, OpsParserListenerImpl, report);
    throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
  }

  // If privdir doesn't exist, set it to common dir or root if that
  // wasn't possible. Change directory to private dir.

  if(privDir.isNull() || privDir.length() < 1){
      RWCString temp;
      privDir = (ozt_info.getCentralDir(temp) == CHA_OZTInfo::OKAY &&
                 !temp.isNull() && access((const char*)temp, F_OK))?
          temp : (RWCString)"/";
  }
  chdir(privDir);

  // Create classes that handles graphical commands.

 // Event handler. Not much used anymore.

  if ((ozt_evHandlerPtr = new OPS_EventHandler)==0) {
    report = ozt_formatReport("",
                              "",
                              "",
                              ozt_nlsCatalog.getMessage(OZT_NLS_OUT_OF_MEMORY,
                                                      "Out of Memory, application stops"));
    TRACE_INFO(trace, OpsParserListenerImpl, report);
    throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
  }

  makeUiWindows();


  //
  //   Construct the source manager
  //

  RWCString id = getSessionId();
  pSourceMgr = new OZT_SourceMgr(pOrb_, serverRLRef_, id, ioWin_, inputWin_, inkeyWin_,
                                 fileSelector_, fileViewer_, prompt_, childHandler_);
  if ((pSourceMgr == 0) || (!pSourceMgr->constructOK()))
  {
    cleanup();
    report = ozt_formatReport("",
                              "",
                              "",
                              ozt_nlsCatalog.getMessage(OZT_NLS_FAIL_TO_INIT,
                                                        "Fail to initialise the interpreter \
                                         (probably CAP_IPC problems)"));
    TRACE_OUT(trace, OpsParserListenerImpl, report);
    throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
  }
  current_position = 0;


  //
  //   Construct the variable watcher
  //

  if ((variableWatcher_ = new VariableWatcher(pSourceMgr, serverRLRef_))==0) {
    TRACE_FLOW(trace, OpsParserListenerImpl, "cleanup() 3");
    cleanup();
    report = ozt_formatReport("",
                              "",
                              "",
                              ozt_nlsCatalog.getMessage(OZT_NLS_OUT_OF_MEMORY,
                                                      "Out of Memory, application stops"));
    TRACE_INFO(trace, OpsParserListenerImpl, report);
    throw OPS::OPS_Exception(OPS::EXECUTION_ERROR, report);
  }
  pSourceMgr->getVarStore().addDependent(variableWatcher_);


  // Add dependencies

  indicator_ = &pSourceMgr->getIndicator();
  indicator_->addDependent(this);
  cmdRspBuf_ = &pSourceMgr->getCmdRspBuf();
  cmdRspBuf_->addDependent(this);
  commentWinModel_ = &pSourceMgr->getCommentWinModel();
  commentWinModel_->addDependent(this);
  connectionObject_ = &pSourceMgr->getCmdSender().getConnectionObject();
  connectionObject_->addDependent(this);

  std::string enmUser(userId_);
  connectionObject_->setEnmId(enmUser);

  //Send Session Id to the cmdSender
  pSourceMgr->getCmdSender().setSessionId(sSessionId_);

  //Get parser process pid
  pid = pSourceMgr->getCmdSender().getPid();

  // Set client type in the clock object
  pSourceMgr->getClock().setClientType(clientType_);

  responseCatcher_ = &pSourceMgr->getRspCatcher();
  responseCatcher_->addDependent( this );


  // Added to improve handling of Imm. Rsp, check the connection before dispatching
  // provide  OZT_EventHandler with connection status
 ((OPS_EventHandler *)ozt_evHandlerPtr)->setConnectionRef(connectionObject_);

  // Create thread that tell the server that parser is ok and alive.
  createDetachedThread(&pThreadId_, OpsParserListenerImpl::IamAliveThread);

  TRACE_FLOW(trace, setSessionData, "Parser is ready with session ID: " << sSessionId_);
  TRACE_OUT(trace, setSessionData, "");
}
//----------------------------------------------------------------------

void OpsParserListenerImpl::runCommon(OZT_Result result,
                                      RWCString filename,
                                      LineNo line_no,
                                      LineNo num_lines,
                                      int start_file_number){
  //Common code shared by runFromCurrentPosition(), runFromBeginning() and runTagg
  TRACE_IN(trace, runCommon, "");

  std::string smoUser = serverRLRef_->getSmoUser();
  if(smoUser != ""){
     sErrorMsg_ = result.toMsg();
     sendErrorMsg();
  }

  if (!shutdownProcessing_) {
    // Send message to client about the state.
    if(result.code == OZT_Result::PROGRAM_TERMINATED ||
    result.code == OZT_Result::HIT_EOF)
      serverRLRef_->newState(OPS::FINISHED);
    else if(result.code == OZT_Result::STOP)
      serverRLRef_->newState(OPS::STOPPED);
    else if(result.code == OZT_Result::INTERRUPTED)
      serverRLRef_->newState(OPS::INTERRUPTED);
    else if(result.code == OZT_Result::QUIT)
      serverRLRef_->newState(OPS::FINISHED);
    else if(result.code == OZT_Result::NO_UI_SUPPORTED)
    {
      serverRLRef_->newState(OPS::WAITING_FOR_INPUT);
      sErrorMsg_ = result.toMsg();
      sendErrorMsg();
    }
    else
    {
      TRACE_FLOW(trace, runCommon, result.toMsg());

      // If the call is from SHM (smouser exists) and result has syntax error (code 2) or variable undefined error (code 5).
      if(smoUser != "" && (result.code == 2 || result.code == 5))
         serverRLRef_->newState(OPS::INTERRUPTED);
      else
         serverRLRef_->newState(OPS::FAILED);
      // HD62350
      pSourceMgr->getCurrPos(filename, line_no, num_lines);
      line_no++; // getCurrPos counts the first line as line zero
      char* line_no_str = new char[30];
      sprintf(line_no_str, " (script line no. %d)", line_no);
      sErrorMsg_ = result.toMsg();
      sErrorMsg_ += line_no_str;
      delete [] line_no_str;
      sendErrorMsg();
      // END HD62350
    }
  }

  TRACE_FLOW(trace, runCommon, "After sending back final state");

  // Flush any logged responses if the execution was either
  // terminated normally, or some error occurred.  However, we
  // don't want to do the flush if we just stepped a single line
  // (NO_PROBLEM) or clicked on the 'Stop' button (STOP)...
  if (result.code != OZT_Result::NO_PROBLEM && result.code != OZT_Result::STOP &&
  connectionObject_->getConnectionStatus() /*== EAC_CRI_CS_CONNECTED*/)
  {
      pSourceMgr->getCmdSender().logOff(true);
  }

  // HD81058: Removed this correction. The SAOSP command worked without
  //            any problems (HD61493).
  // Here we close the log files to prevent the hang fault described
  // in HD61493.
  TRACE_FLOW(trace, runFromCurrentPosition, "close all File logs");
  //CHA_FileLogger *pFileLogger = &(pSourceMgr->getFileLogger());
  //pFileLogger->closeAllLogs();
    if(pSourceMgr != NULL)
	  pSourceMgr->getCurrPos(filename, line_no, num_lines);
	  
    if (filename == "" && file_entry[running_file_number] != NULL)
      filename = file_entry[running_file_number]->get_full_name();
      current_position = line_no;

   if (num_lines != 0 && file_entry[running_file_number] != NULL)
    show_position(file_entry[running_file_number]->get_full_name(), current_position);

  running_file_number = view_file_number;
  viewCorrectFile(result, filename, line_no, num_lines, start_file_number);

  if (result.code == OZT_Result::INCLUDE_NOT_EXECUTED)
  {
    action = NOTHING;
    TRACE_OUT(trace, runCommon, result.toMsg());

    throw OPS::OPS_Exception(OPS::EXECUTION_ERROR,
                               ozt_nlsCatalog.getMessage(OZT_NLS_CANT_INCLUDE,
                        "Run stopped: Cannot include file. Max number of files reached."));
  }
    action = NOTHING;

}
//----------------------------------------------------------------------
void OpsParserListenerImpl::viewCorrectFile(OZT_Result result,
                                      RWCString filename,
                                      LineNo line_no,
                                      LineNo num_lines,
                                      int start_file_number){
  //Fix to display the right file.
  //If the last line in the first file is @INCLUDE the file might be wrong.
  
  if (result.code == OZT_Result::PROGRAM_TERMINATED ||
  result.code == OZT_Result::HIT_EOF &&
  start_file_number != running_file_number)
  {
     running_file_number = start_file_number;
     RWCString tmpStr(file_entry[running_file_number]->get_full_name());
     	 if(pSourceMgr != NULL)
         pSourceMgr->getCurrPos(tmpStr, line_no, num_lines);

	 if(file_entry[running_file_number] != NULL)
     show_position(file_entry[running_file_number]->get_full_name(), current_position);
  }
}

//----------------------------------------------------------------------

void OpsParserListenerImpl::doShutdownProcessing()
{
  TRACE_IN(trace, doShutdownProcessing, "");
  if (action != RUN)
  {
    // Added to improve handling of Imm. Rsp, check client before dispatching
    // provide  OZT_EventHandler with client status
    ozt_evHandlerPtr->stopDispatch();
    ((OPS_EventHandler *)ozt_evHandlerPtr)->clientStatus(FALSE);

    // Due to TR HF49387 and HF31139
    // Interrupt the current command
    pSourceMgr->getCmdSender().totalInterrupt();
  }
  else
  {
    shutdownProcessing_ = TRUE;

    // quit from running loop
    stopped = TRUE;
    action = QUIT;

    // terminate current command
    pSourceMgr->getCmdSender().totalInterrupt();
    pSourceMgr->getClock().shutdown();

    if (shutdownProcessing_)
    {
      waitForFinishedShutdownProcessing();
    }
  }
  TRACE_OUT(trace, doShutdownProcessing, "");
}

//----------------------------------------------------------------------

void OpsParserListenerImpl::signalFinishedShutdownProcessing()
{
  TRACE_IN(trace, signalFinishedShutdownProcessing, "");

  pthread_mutex_lock(&shutdownWaitMutex_);
  TRACE_FLOW(trace, signalFinishedShutdownProcessing, "Send broadcast signal");
  pthread_cond_broadcast(&shutdownWaitObject_);
  pthread_mutex_unlock(&shutdownWaitMutex_);

  shutdownProcessing_ = FALSE;
  TRACE_OUT(trace, signalFinishedShutdownProcessing, "");
}

//----------------------------------------------------------------------

void OpsParserListenerImpl::waitForFinishedShutdownProcessing()
{
  TRACE_IN(trace, waitForFinishedShutdownProcessing, "");
  struct timespec timeout;
  int returnCode;

  timeout.tv_sec = time(NULL) + SHUTDOWN_WAIT_TIMEOUT_IN_SECS;
  timeout.tv_nsec = 0;

  pthread_mutex_lock(&shutdownWaitMutex_);
  TRACE_FLOW(trace, waitForFinishedShutdownProcessing, "Waiting for shutdown...");

  returnCode = pthread_cond_timedwait(&shutdownWaitObject_, &shutdownWaitMutex_, &timeout);
  if (returnCode == ETIMEDOUT)
  {
    TRACE_INFO(trace, waitForFinishedShutdownProcessing,
        "Shutdown waiting timer expired");
  }
  pthread_mutex_unlock(&shutdownWaitMutex_);

  shutdownProcessing_ = FALSE;
  TRACE_OUT(trace, waitForFinishedShutdownProcessing, "");
}
