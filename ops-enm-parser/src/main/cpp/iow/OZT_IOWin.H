//ClearCase Version Control Information
//ClearCase: @(#) syn-opsserver/server/iow/src/OZT_IOWin.H @@/main/orbix/1 2000-03-03.14:21 EHS

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

#ifndef OZT_XV_IOW_H
#define OZT_XV_IOW_H

#include <OZT_IOW.H>
#include "OZT_Misc.H"
#include "OPSS.H"

#define DRAW 1
#define DRAW_BOX 2
#define DRAW_CUP 3
#define CLEAR 4

#define COMMAND_LIST_SIZE 1000


/**
 * OZT_IOWin - Implementation of the IO window
 *
 * @author <2000-02-22> EHS/OX/DF Anders Ahlstr�m
 *
 * @see OtherClass
 */
  
class IOWinCommand {
	
	public:
	
		short commandType;
		int x1;
		int y1;
		int x2;
		int y2;
		
		RWCString sText;
		RWBoolean bFormat;

		IOWinCommand();
		IOWinCommand(short commandType);
		IOWinCommand(short commandType, int x1, int y1);
		IOWinCommand(short commandType, int x1, int y1,	int x2, int y2);
		IOWinCommand(short commandType, RWCString sText, RWBoolean bFormat);

		IOWinCommand(const IOWinCommand&);
		IOWinCommand& operator=(const IOWinCommand&);
		
	private:		
		
		

};
 
class OZT_IOWin : public OZT_IOW {

public:

  /**
   * Constructor
   *
   * @param listener Listener object in client that will popup a dialog
   */
  // HF65265
  // OZT_IOWin(OPS::ServerRouterListener* listener);
  OZT_IOWin(OPS::ServerRouterListener* listener, OPS::ClientType type);
  // END HF65265


  /**
   * Destructor
   *
   */
  ~OZT_IOWin();


  /**
   * Switch to a different listener
   *
   * @param listener Listener object in client that will popup a dialog
   */
  // HF95902
  void changeListener(OPS::ServerRouterListener* listener, OPS::ClientType type);
  // END HF95902

  /**
   * Open the window.
   *
  */
  void open();


  /**
   * Close the window.
   *
   */
  void close();


  /**
   * Clear the contents of the window.
   *
   */
  void clrscr();


  /**
   * Draw a number of items according to the "spec".
   *
   * @param spec a vector of OZT_Value obtained from the @DRAW command, IN
   * @return OZT_Result(NO_PROBLEM)           everything OK
   *         OZT_Result(INTERRUPTED)          dialog interrupted
   *         OZT_Result(MISSING_PARAMETERS)   e.g. BOX without coordinates
   *         OZT_Result(INVALID_VALUE)        e.g. BOX without non-numeric param.
   */
  OZT_Result draw(RWTValOrderedVector<OZT_Value> &spec);


  /**
   * Open a form for user input.
   *
   * @param spec a vector of input fields specification, IN
   * @param ans  a vector of values input by the user when the form input is done, OUT
   * @return OZT_Result(NO_PROBLEM)           everything OK
   *         OZT_Result(INTERRUPTED)          dialog interrupted
   *         OZT_Result(INVALID_VALUE)       e.g. non-numeric field width.
   */
  OZT_Result form(RWTValOrderedVector<OZT_Value> &spec,
                    RWTValOrderedVector<RWCString> &ans);


  /**
   * Open a menu for user input.
   *
   * @param selectedValue the number of the choice selected by the user, OUT
   * @param nLeftChoices  the number of choices on the left hand side, IN
   * @param rRightChoices the number of choices on the right hand side, IN
   * @return OZT_Result(NO_PROBLEM)           everything OK
   *         OZT_Result(INTERRUPTED)          dialog interrupted
   *         OZT_Result(INVALID_VALUE)        e.g. non-numeric param
   */
  OZT_Result menu(OZT_Value &selectedValue,
                  const OZT_Value &nLeftChoices, 
                  const OZT_Value &nRightChoices);
   

  /**
   * Interrupt any pending input action of this window.
   *
   */
  void interrupt();


  OZT_Result setTimeout( const OZT_Value& label,
			 const OZT_Value& time,
			 const OZT_Value& unit );

  RWCString getTimeoutLabel();

  void resetTimeout();

private:

  /**
    * Create an input field for a form.
   *
   * @param col column position of the input field, IN
   * @param row row position of the input field, IN
   * @param len length of the input field, IN
   * @param varname variable name for the input field, IN
   * @param defaultValue default value to fill in the field, IN
   * @param fields list of fields with new field appended, OUT
   * @param varnames list of variable names with name of variable
   *                 in the new filed appended, OUT
   * @return TRUE if successfull
   *         FALSE otherwise
   */
  RWBoolean setInputField(const OZT_Value &col,
                          const OZT_Value &row,
                          const OZT_Value &len,
                          const OZT_Value &varname,
                          const OZT_Value &defaultValue,
                          OPS::formFieldList * fields,
                          RWTValOrderedVector<RWCString> &varnames);

  RWBoolean setButtonField( const OZT_Value &col,
			    const OZT_Value &row,
			    const OZT_Value &title,
			    const OZT_Value &label,
			    OPS::formFieldList * fields );

  RWBoolean setCheckBoxField( const OZT_Value &col,
			      const OZT_Value &row,
			      const OZT_Value &title,
			      const OZT_Value &varname,
			      const OZT_Value &defValue,
			      OPS::formFieldList * fields,
			      RWTValOrderedVector<RWCString> &varnames );

  RWBoolean setRadioButtonGroupField( const OZT_Value &varname,
				      const OZT_Value &defValue,
				      RWTValOrderedVector<OZT_Value> &radioButtons,
				      OPS::formFieldList * fields,
				      RWTValOrderedVector<RWCString> &varnames );

  RWBoolean setComboBoxField( const OZT_Value &col,
			      const OZT_Value &row,
			      const OZT_Value &varname,
			      const OZT_Value &defValue,
			      RWTValOrderedVector<OZT_Value> &comboOptions,
			      OPS::formFieldList * fields,
			      RWTValOrderedVector<RWCString> &varnames );
			      
  RWBoolean setIOWinCommandList(OPS::iowCommandList *commandList);


  enum State {IDLE, MENU_OPENED, FORM_OPENED};
  enum TimeUnit { Second, Minute, Hour };

  State      state_;
  RWCString timeoutLabel_;
  long timeoutTime_;
  OPS::ServerRouterListener_ptr listener_;
  
  IOWinCommand ioWinCommands[COMMAND_LIST_SIZE];
  int ioWinIndex;
  
  // HF65265
  OPS::ClientType listenerType_;
  // END HF65265

};


#endif
