//ClearCase Version Control Information
//ClearCase: @(#) syn-opsserver/server/iow/src/OZT_FileViewer.H @@/main/orbix/1 2000-03-03.14:19 EHS

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

#ifndef OZT_FILE_VIEWER_H
#define OZT_FILE_VIEWER_H

#include <OZT_IOW.H>
#include <OZT_Misc.H>
#include "OPSS.H"

/**
 * Input popup for @VIEWFILE
 *
 * @author <2000-02-24> EHS/OX/DF Anders Ahlström
 *
 */
class OZT_FileViewer : public OZT_FileViewerPopup
{

public:
  /**
   * Constructor
   *
   * @param listener Listener object in client that will popup a dialog
   */
  OZT_FileViewer (OPS::ServerRouterListener_ptr listener);

  /**
   * Destructor
   *
   */
  ~OZT_FileViewer();

  /**
   * Open the file viewer and let the user view the file.
   *
   * @param fileName path name of the file to view, IN
   * @return OZT_Result(NO_PROBLEM) or
   *         OZT_Result(FILE_OPEN_ERR) or
   *         OZT_Result(USER_INTERRUPTED)
   */
  OZT_Result view(RWCString fileName);

  /**
   * Interrupt the viewing and make view() returns immediately.
   *
   */
  void interrupt();

private:
  enum State   {BUSY, IDLE};
  State        state_;
  OPS::ServerRouterListener_ptr listener_;

};

#endif
