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

#include <OZT_EventHandler.H>
#include <OZT_IOWin.H>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <rw/tools/regex.h>

//*****************************************************************************


// trace
#include <trace.H>
static std::string trace ="OZT_IOWin";

//*****************************************************************************

extern OZT_EventHandler *ozt_evHandlerPtr;

static const int MAX_CHOICES_PER_COL = 21;

//*****************************************************************************

// HF65265
//OZT_IOWin::OZT_IOWin(OPS::ServerRouterListener_ptr listener)
OZT_IOWin::OZT_IOWin(OPS::ServerRouterListener_ptr listener, OPS::ClientType type)
// END HF65265
: state_(IDLE),
  listener_(listener),
  // HF65265
  listenerType_(type),
  // END HF65265
  ioWinIndex(0)
{
 TRACE_IN(trace, OZT_IOWin, "");
 TRACE_OUT(trace, OZT_IOWin, "");
  timeoutTime_ = -1;
}

//***************************************************************************

OZT_IOWin::~OZT_IOWin()
{
}

//***************************************************************************


// HF95902
//***************************************************************************

void OZT_IOWin::changeListener(OPS::ServerRouterListener* listener, OPS::ClientType type)
{
  TRACE_IN(trace, changeListener, "");
  listener_ = listener;
  listenerType_ = type;
 TRACE_OUT(trace, changeListener, "");
}


//***************************************************************************
// END HF95902

//***************************************************************************

void OZT_IOWin::open()
{
 TRACE_IN(trace, open, "");

  listener_->openIOWindow();

  TRACE_OUT(trace, open, "");
}


//***************************************************************************

void OZT_IOWin::close()
{
 TRACE_IN(trace, close, "");

  listener_->closeWindows();

 TRACE_OUT(trace, close, "");
}
 
//***************************************************************************

void OZT_IOWin::clrscr()
{
 TRACE_IN(trace, clrscr, "");

// HF65265
	if (listenerType_ == OPS::GUI) {
  		listener_->clearIOWindow(); 
	}
// HF95902
//	else { 
		// clear list of drawCommands
		TRACE_FLOW(trace, clrscr, "Clearing command list");
		ioWinIndex = 0;
		// Add clear to list of draw commands
		IOWinCommand command(CLEAR);
		ioWinCommands[ioWinIndex++] = command;
//	}
// END HF95902
// END HF65265
 TRACE_OUT(trace, clrscr, "");
}

//***************************************************************************

OZT_Result OZT_IOWin::draw(RWTValOrderedVector<OZT_Value> &spec)
{
  TRACE_IN(trace, draw, "");

  long row1, col1, row2, col2, row, col;
  RWCString cmd;
  OZT_Result result;

  while(spec.entries() != 0)
  {
    cmd = spec.first();
    cmd.toUpper();
  TRACE_FLOW(trace, draw, "cmd:" << cmd );

    if (cmd == RWCString(OZT_IOW::drawBox))   // draw BOX
    {
      (void)spec.removeFirst();  // remove the "BOX"
      if (spec.entries() < 4)
        return OZT_Result(OZT_Result::MISSING_PARAMETERS);

      //  convert the LeftX
      col1 = spec.removeFirst().toLong(result) - 1;
      if (result.code != OZT_Result::NO_PROBLEM)
        return OZT_Result(OZT_Result::INVALID_VALUE);

      //  convert the UpperY
      row1 = spec.removeFirst().toLong(result) - 1;
      if (result.code != OZT_Result::NO_PROBLEM)
        return OZT_Result(OZT_Result::INVALID_VALUE);

      //  convert the RightX
      col2 = spec.removeFirst().toLong(result) - 1;
      if (result.code != OZT_Result::NO_PROBLEM)
        return OZT_Result(OZT_Result::INVALID_VALUE);

      //  convert the LowerY
      row2 = spec.removeFirst().toLong(result) - 1;
      if (result.code != OZT_Result::NO_PROBLEM)
        return OZT_Result(OZT_Result::INVALID_VALUE);

 TRACE_FLOW(trace, draw, "drawBox:" << col1 << ", " << row1 << ", " << col2 << ", " << row2 );
// HF65265
		if (listenerType_ == OPS::GUI) 
		{
	    		try
	    		{
	        		listener_->drawBox(col1, row1, col2, row2);
	    		}	
	    		catch (const OPS::OPS_Client_Exception& ce)
	    		{
	    			
     				if (ce.id == OPS::NOT_ALLOWED_IN_CHILD_SCRIPTS) 
     				{
     					TRACE_FLOW(trace,draw,"draw, NOT_ALLOWED_IN_CHILD_SCRIPTS");
     					ozt_errHandler.setFlag();
        				return OZT_Result(OZT_Result::NOT_ALLOWED_IN_CHILD_SCRIPTS);
      				}
      				else 
      				{
     					return OZT_Result(OZT_Result::NO_UI_SUPPORTED);
				}
	    		}	 
		}
// HF95902
//		else {
			// Add drawBox to list of draw commands
			if (ioWinIndex < COMMAND_LIST_SIZE) {
				IOWinCommand command(DRAW_BOX, col1, row1, col2, row2);
				ioWinCommands[ioWinIndex++] = command;
			}
			else {
		  		TRACE_FLOW(trace, draw, "More than COMMAND_LIST_SIZE commands, skipping");
			}
//		}
// END HF95902
// END HF65265	
    }
    else if (cmd == RWCString(OZT_IOW::drawCup))   // draw CUP
    {
      (void)spec.removeFirst();  // remove the "CUP"
      if (spec.entries() < 2)
        return OZT_Result(OZT_Result::MISSING_PARAMETERS);

      //  convert the column number
      col = spec.removeFirst().toLong(result) - 1;
      if (result.code != OZT_Result::NO_PROBLEM)
        return OZT_Result(OZT_Result::INVALID_VALUE);

      //  convert the row number
      row = spec.removeFirst().toLong(result) - 1;
      if (result.code != OZT_Result::NO_PROBLEM)
        return OZT_Result(OZT_Result::INVALID_VALUE); 

 TRACE_FLOW(trace, draw, "drawCup:" << col << ", " << row );
// HF65265
		if (listenerType_ == OPS::GUI) {
	    		try
	    		{
	        		listener_->drawCup(col, row);
	    		}
	    		catch (const OPS::OPS_Client_Exception& ce)
	    		{
	    			
     				if (ce.id == OPS::NOT_ALLOWED_IN_CHILD_SCRIPTS) 
     				{
     					TRACE_FLOW(trace,draw,"draw, NOT_ALLOWED_IN_CHILD_SCRIPTS");
     					ozt_errHandler.setFlag();
        				return OZT_Result(OZT_Result::NOT_ALLOWED_IN_CHILD_SCRIPTS);
      				}
      				else 
      				{
	        			return OZT_Result(OZT_Result::NO_UI_SUPPORTED);
	        		}
	    		}
		}
// HF95902
//		else {
			// Add drawCup to list of draw commands
			if (ioWinIndex < COMMAND_LIST_SIZE) {
				IOWinCommand command(DRAW_CUP, col, row);
				ioWinCommands[ioWinIndex++] = command;
			}
			else {
				TRACE_FLOW(trace, draw, "More than COMMAND_LIST_SIZE commands, skipping");
			}
//		}
// END HF95902
// END HF65265	

      continue;
    }
    else if ((cmd == RWCString(OZT_IOW::drawHigh))    // HIGH
             || (cmd == RWCString(OZT_IOW::drawInv))  // INV
             || (cmd == RWCString(OZT_IOW::drawLow))) // LOW
    {
      //  obsolete drawing instructions
      (void)spec.removeFirst();
    }
    else
    {
      	RWBoolean toFormat;
	OZT_Value v = spec.first();

	if( v.unvisibleChars > 0 )
	  toFormat = TRUE;
	else
	  toFormat = FALSE;

	TRACE_FLOW(trace, draw, "drawString:" << v );
	//  print the expression
// HF65265
		if (listenerType_ == OPS::GUI) {
	        try
	        {
	            listener_->draw(v, toFormat);     
	        }
	        catch (const OPS::OPS_Client_Exception& ce)
	        {
	        	
     			if (ce.id == OPS::NOT_ALLOWED_IN_CHILD_SCRIPTS) 
     			{
     				TRACE_FLOW(trace,draw,"draw, NOT_ALLOWED_IN_CHILD_SCRIPTS");
     				ozt_errHandler.setFlag();
        			return OZT_Result(OZT_Result::NOT_ALLOWED_IN_CHILD_SCRIPTS);
      			}
      			else 
      			{
	            		return OZT_Result(OZT_Result::NO_UI_SUPPORTED);
	        	}
	        }
		}
// HF95902
//		else {
			// Add draw to list of draw commands
			if (ioWinIndex < COMMAND_LIST_SIZE) {
				IOWinCommand command(DRAW, v, toFormat);
				ioWinCommands[ioWinIndex++] = command;
			}
			else {
				TRACE_FLOW(trace, draw, "More than COMMAND_LIST_SIZE commands, skipping");
			}
//		}
// END HF95902
// END HF65265	

	spec.removeFirst();
    }
  }
 TRACE_OUT(trace, draw, "");
  return OZT_Result(OZT_Result::NO_PROBLEM);
}


//***************************************************************************


OZT_Result OZT_IOWin::form(RWTValOrderedVector<OZT_Value> &spec,
                           RWTValOrderedVector<RWCString> &ans)
{
 TRACE_IN(trace, form, "");

  OZT_Result result;
  RWTValOrderedVector<RWCString> varnames;
  OPS::formFieldList * fields = new OPS::formFieldList;
  //OPS::responseFieldList * returnFields = new OPS::responseFieldList;
  OZT_Value col, row, length, varname, defaultValue, type, title, label;
  while (spec.entries() != 0)
  {
    type = spec.removeFirst();

    if( type == OZT_Value( "VAR" ) ) {
      col = spec.removeFirst();
      row = spec.removeFirst();
      length = spec.removeFirst();
      varname = spec.removeFirst();
      defaultValue = spec.removeFirst();
      if (!setInputField(col, 
			 row, 
			 length, 
			 varname, 
			 defaultValue,
			 fields, 
			 varnames)) {
	return OZT_Result(OZT_Result::INVALID_VALUE);
      }
    }
    else if( type == OZT_Value( "BUTTON" ) ) {
      col = spec.removeFirst();
      row = spec.removeFirst();
      title = spec.removeFirst();
      label = spec.removeFirst();

      if( !setButtonField( col,
			   row,
			   title,
			   label,
			   fields ) ) {
	return OZT_Result(OZT_Result::INVALID_VALUE);
      }
    }
    else if( type == OZT_Value( "CHECKBOX" ) ) {
      col = spec.removeFirst();
      row = spec.removeFirst();
      title = spec.removeFirst();
      varname = spec.removeFirst();
      defaultValue = spec.removeFirst();

      if( !setCheckBoxField( col,
			     row,
			     title,
			     varname,
			     defaultValue,
			     fields,
			     varnames) ) {

	return OZT_Result(OZT_Result::INVALID_VALUE);
      }
    }
    else if( type == OZT_Value( "RADIO" ) ) {
      varname = spec.removeFirst();
      defaultValue = spec.removeFirst();
     TRACE_FLOW(trace, form, "varname" << varname << ", " << "defaultValue=" << defaultValue );
      if( !setRadioButtonGroupField( varname,
				     defaultValue,
				     spec,
				     fields,
				     varnames) ) {
	return OZT_Result(OZT_Result::INVALID_VALUE);
      }
    }
    else if( type == OZT_Value( "COMBO" ) ) {
      col = spec.removeFirst();
      row = spec.removeFirst();
      varname = spec.removeFirst();
      defaultValue = spec.removeFirst();
      
      if( !setComboBoxField( col,
			     row,
			     varname,
			     defaultValue,
			     spec,
			     fields,
			     varnames) ) {
	return OZT_Result(OZT_Result::INVALID_VALUE);
      }	    
    }
    else {
      return OZT_Result(OZT_Result::INVALID_VALUE);
    }
  }
  //
  //  wait for the user input
  //
  state_ = FORM_OPENED;

  OPS::FormReturnValue *returnValue;
  std::string smoUser;
  OPS::iowCommandList *commandList = new OPS::iowCommandList;
  setIOWinCommandList(commandList);
  try
  {
    smoUser = listener_->getSmoUser();
    if(smoUser != "")
    {
      TRACE_FLOW(trace, form, "waiting for GUI to launch");
      listener_->setWaitingForUserInput();
      listenerType_ = listener_->getClientType("");

      while(listenerType_ != OPS::GUI)
      {
        listenerType_ = listener_->getClientType("");
        if(listenerType_ == OPS::GUI)
        {
          listener_->setWaitingForUserInput();
          break;
        }
        sleep(20); // checking if gui has launched at every 20 seconds 
      }
     }
      returnValue = listener_->form(*fields, timeoutTime_, *commandList);
// HF95902
      // clear list of drawCommands
//	  ioWinIndex = 0;
// END HF95902
  }
  catch (const OPS::OPS_Client_Exception& ce)
  {
    if (commandList != NULL) {
      delete commandList;
      commandList = NULL;
    }	

    if (ce.id == OPS::NOT_ALLOWED_IN_CHILD_SCRIPTS) 
    {			
      TRACE_FLOW(trace,form,"form, NOT_ALLOWED_IN_CHILD_SCRIPTS");
      ozt_errHandler.setFlag();
      return OZT_Result(OZT_Result::NOT_ALLOWED_IN_CHILD_SCRIPTS);
    }
    else 
    {
      state_ = IDLE;
      return OZT_Result(OZT_Result::NO_UI_SUPPORTED);
    }
  }

  state_ = IDLE;
  if (commandList != NULL) {
      delete commandList;
      commandList = NULL;
  }
  
  //
  //  Collect the user input
  //
  if (returnValue->ret == OPS::DIALOG_RETURNS_OK) {
    result = OZT_Result(OZT_Result::NO_PROBLEM);
    RWCString varName;
    RWCString fieldContent;
///    int fieldWidth;
    
    for (int i=0; i<fields->length(); i++) {
      if( (returnValue->answer)[i].type == OPS::VAR ){
	varName = (returnValue->answer)[i].varname;
///	fieldWidth = (int)(*fields)[i].width;
	fieldContent = (returnValue->answer)[i].value;

      // make sure that the content is not too long
///    Not necessary - client makes sure this
///	if (fieldContent.length() > fieldWidth)
///          fieldContent = fieldContent(0, fieldWidth);

	TRACE_FLOW(trace, form, varName << "=" << fieldContent);
	ans.insert( "VAR" );
	ans.insert(varName);
	ans.insert(fieldContent);
      }
      else if( (returnValue->answer)[i].type == OPS::COMBOBOX ){
	varName = (returnValue->answer)[i].varname;
	fieldContent = (returnValue->answer)[i].value;

	TRACE_FLOW( trace, form, "COMBO: " << varName << "=" << fieldContent );

	ans.insert( "COMBO" );
	ans.insert( varName );
	ans.insert( fieldContent );
      }
      else if( (returnValue->answer)[i].type == OPS::BUTTON ){
	if( (returnValue->answer)[i].action == OPS::EXECUTE ) {
	  fieldContent = (returnValue->answer)[i].value;

	TRACE_FLOW( trace, form, "BUTTON: execute at:" << "=" << fieldContent );

	  ans.insert( "BUTTON" );
	  ans.insert( fieldContent );
	}
      }
      else if( (returnValue->answer)[i].type == OPS::CHECKBOX ){
	varName = (returnValue->answer)[i].varname;
       	fieldContent = (returnValue->answer)[i].value;

	TRACE_FLOW(trace, form, "CHECKBOX: " << varName << "=" << fieldContent);
	ans.insert( "CHECKBOX" );
	ans.insert(varName);
	ans.insert(fieldContent);
      }
      else if( (returnValue->answer)[i].type == OPS::RADIO ){
	varName = (returnValue->answer)[i].varname;
       	fieldContent = (returnValue->answer)[i].value;

	TRACE_FLOW(trace, form, "RADIO: " << varName << "=" << fieldContent);
	ans.insert( "RADIO" );
	ans.insert(varName);
	ans.insert(fieldContent);
      }
      else
	return OZT_Result(OZT_Result::INVALID_VALUE);
    }
  }
  else if( returnValue->ret == OPS::DIALOG_RETURNS_TIMEOUT ) {
    ans.clear();
    result = OZT_Result(OZT_Result::DIALOG_TIMEOUT);
    
  }
  else if (returnValue->ret == OPS::DIALOG_RETURNS_INTERRUPT)
    result = OZT_Result(OZT_Result::INTERRUPTED);
  else {
    ans.clear();  // no user input returned
    result = OZT_Result(OZT_Result::STOP);
  }

    // update the session status to server
  listener_->newState(OPS::RUNNING);

 TRACE_RETURN(trace, form, result);
  return result;
}

//*****************************************************************************
void OZT_IOWin::resetTimeout(){
  timeoutLabel_ = "";
  timeoutTime_ = -1;
}

//*****************************************************************************

RWCString OZT_IOWin::getTimeoutLabel(){
 TRACE_RETURN(trace, getTimeoutLabel, timeoutLabel_);
  return timeoutLabel_;
}
//***************************************************************************

OZT_Result OZT_IOWin::setTimeout( const OZT_Value& label,
				  const OZT_Value& time,
				  const OZT_Value& unit ) {

 TRACE_IN(trace, setTimeout, label << "," << time << "," << unit );
  OZT_Result res;
  size_t len;
  static RWTRegex<char> rexp("^[+]?[0-9]+$");

  if( rexp.index( time, &len ) == RW_NPOS ) {
    res.code = OZT_Result::INVALID_VALUE;
    return res;
  }

  long t = atol( time.data() );
  
  if( unit == "S" || unit == "s" )
    timeoutTime_ = t;
  else if( unit == "M" || unit == "m" )
    timeoutTime_ = t*60;
  else if( unit == "H" || unit == "h" )
    timeoutTime_ = t*3600;
  else {
    res.code = OZT_Result::INVALID_VALUE;
    return res;
  }

  timeoutLabel_ = label;
  
  res.code = OZT_Result::NO_PROBLEM;
  return res;
}

//***************************************************************************

OZT_Result OZT_IOWin::menu(OZT_Value &selectedValue,
                           const OZT_Value &nLeftChoices,
                           const OZT_Value &nRightChoices)
{
 TRACE_IN(trace, menu, nLeftChoices << ", " << nRightChoices);

  int nChoicesLeft, nChoicesRight;
  OZT_Result result;

  //
  //  Validate and type-convert the parameters
  //
  nChoicesLeft = (int)(nLeftChoices.toLong(result));
  if ((result.code != OZT_Result::NO_PROBLEM) ||
      (nChoicesLeft < 0) || 
      (nChoicesLeft > MAX_CHOICES_PER_COL))
  {
  TRACE_RETURN(trace, menu, "Invalid Parameter");
    return OZT_Result(OZT_Result::INVALID_VALUE);
  }

  nChoicesRight = (int)(nRightChoices.toLong(result));
  if ((result.code != OZT_Result::NO_PROBLEM) ||
      (nChoicesRight < 0) || 
      (nChoicesRight > MAX_CHOICES_PER_COL))
  {
  TRACE_RETURN(trace, menu, "Invalid Parameter");
    return OZT_Result(OZT_Result::INVALID_VALUE);
  }

  if ((nChoicesLeft == 0) && (nChoicesRight == 0))
  {
    TRACE_RETURN(trace, menu, "Invalid Parameter");
    return OZT_Result(OZT_Result::INVALID_VALUE);
  }

  long menuSelectedValue;
  state_ = MENU_OPENED;


  OPS::LongReturnValue returnValue;
  std::string smoUser;
  OPS::iowCommandList *commandList = new OPS::iowCommandList;
  setIOWinCommandList(commandList);

  try
  {
    smoUser = listener_->getSmoUser();
    if(smoUser != "")
    {
      TRACE_FLOW(trace, menu, "waiting for GUI to launch");
      listener_->setWaitingForUserInput();
      listenerType_ = listener_->getClientType("");

      while(listenerType_ != OPS::GUI)
      {
        listenerType_ = listener_->getClientType("");
        if(listenerType_ == OPS::GUI)
        {
          listener_->setWaitingForUserInput();
          break;
        }
        sleep(20); // checking if gui has launched at every 20 seconds 
      }
     }
      returnValue = listener_->menu(nChoicesLeft,
                                    nChoicesRight,
                                    timeoutTime_,
                                    *commandList);
// HF95902
      // clear list of drawCommands
//	  ioWinIndex = 0;
// END HF95902
  }
  catch (const OPS::OPS_Client_Exception& ce)
  {
        if (commandList != NULL) {
                delete commandList;
                commandList = NULL;
        }
      
     	if (ce.id == OPS::NOT_ALLOWED_IN_CHILD_SCRIPTS) 
     	{			
     		TRACE_FLOW(trace,menu,"menu, NOT_ALLOWED_IN_CHILD_SCRIPTS");
     		ozt_errHandler.setFlag();
        	return OZT_Result(OZT_Result::NOT_ALLOWED_IN_CHILD_SCRIPTS);
      	}
      	else 
      	{	
      		state_ = IDLE;
      		return OZT_Result(OZT_Result::NO_UI_SUPPORTED);
      	}
  }

  state_ = IDLE;

  if (returnValue.ret == OPS::DIALOG_RETURNS_OK )
    result = OZT_Result(OZT_Result::NO_PROBLEM);
  else if( returnValue.ret == OPS::DIALOG_RETURNS_TIMEOUT )
    result = OZT_Result(OZT_Result::DIALOG_TIMEOUT);
  else if (returnValue.ret == OPS::DIALOG_RETURNS_INTERRUPT)
    result = OZT_Result(OZT_Result::INTERRUPTED);
  else
    result = OZT_Result(OZT_Result::STOP);
  selectedValue = OZT_Value(returnValue.answer);

  if (commandList != NULL) {
      delete commandList;
      commandList = NULL;
  }

    // update the session status to server
  listener_->newState(OPS::RUNNING);

  TRACE_RETURN(trace, menu, result);
  return result;
}

//***************************************************************************

void OZT_IOWin::interrupt()
{
 TRACE_IN(trace, interrupt, state_);

  switch(state_) {
    case IDLE:
      break;
    case MENU_OPENED:
    case FORM_OPENED:
       ozt_evHandlerPtr->setResult(OZT_Result::INTERRUPTED);
       break;
  }


 TRACE_OUT(trace, interrupt, "");
}

//***************************************************************************

RWBoolean OZT_IOWin::setComboBoxField( const OZT_Value &col,
				       const OZT_Value &row,
				       const OZT_Value &varname,
				       const OZT_Value &defValue,
				       RWTValOrderedVector<OZT_Value> &comboOptions,
				       OPS::formFieldList * fields,
				       RWTValOrderedVector<RWCString> &varnames ) {

  OZT_Result result;

 TRACE_IN(trace,  setComboBoxField, "(" << col << "," << row << "," << varname << "," << defValue << ")" );

  int colVal, rowVal;

  colVal = (int)(col.toLong(result)) - 1;
  if (result.code != OZT_Result::NO_PROBLEM){
    return FALSE;
  }

  rowVal = (int)(row.toLong(result)) - 1;
  if (result.code != OZT_Result::NO_PROBLEM){
    return FALSE;
  }

  OPS::formField field;
  field.type = OPS::COMBOBOX;
  field.varname = (CORBA::String_var)CORBA::string_dup(varname);
  field.defValue = (CORBA::String_var)CORBA::string_dup(defValue);
  field.column = colVal;
  field.line = rowVal;

  OZT_Value optionSource = comboOptions.removeFirst();
  if( optionSource == "FILE" ){

    OZT_Value fileName = comboOptions.removeFirst();

    TRACE_FLOW(trace,  setComboBoxField, "Reading combo options from the file:" << fileName );

    ifstream optionsFile;
    
    //open the file
    optionsFile.open( ozt_normalisePath( fileName ).data() );

    //check if everything is OK
    if( optionsFile.fail()){
     TRACE_OUT(trace,setComboBoxField , 0);
      return FALSE;
    }

    RWCString option;


    //read options from the file, do not skip empty lines....
    while(  option.readLine( optionsFile, FALSE ) ){
      field.comboOptions.length( field.comboOptions.length() + 1 );
      field.comboOptions[field.comboOptions.length() - 1] = strdup(option.data());  // Minnesläcka?

      TRACE_FLOW(trace,  setComboBoxField, "Combo option:" << option );
    }

    //remove the "ENDCOMBO" mark
    comboOptions.removeFirst();
  }
  else if( optionSource == "OPTIONS" ){
  TRACE_FLOW(trace,  setComboBoxField, "Reading combo options from the array" );

    //read the options from the array: option or ENDCOMBO
    OZT_Value option = comboOptions.removeFirst();

    while( option != OZT_Value( "ENDCOMBO" ) ) {

      field.comboOptions.length( field.comboOptions.length() + 1 );
      field.comboOptions[field.comboOptions.length() - 1] = strdup(option.data());  // Minnesläcka?

      TRACE_FLOW(trace,  setComboBoxField, "Combo option:" << option );
    
      //read the options from the array: option or ENDCOMBO
      option = comboOptions.removeFirst();
    }
  }
  else {
    TRACE_OUT(trace,setComboBoxField , 0);
      
    //error argument
    return FALSE;
  }

  fields->length(fields->length()+1);
  (*fields)[fields->length()-1] = field;

  varnames.insert(varname);

 TRACE_OUT(trace,setComboBoxField , 1);

  return TRUE;
  
}
				       
//***************************************************************************

RWBoolean OZT_IOWin::setRadioButtonGroupField( const OZT_Value &varname,
					       const OZT_Value &defValue,
					       RWTValOrderedVector<OZT_Value> &radioButtons,
					       OPS::formFieldList * fields,
					       RWTValOrderedVector<RWCString> &varnames ) {

 TRACE_IN(trace, setRadioButtonGroupField , "(" << varname << "," << defValue << ")");
  RWBoolean validSoFar = TRUE;
  OZT_Result result;

  OPS::formField field;
  field.type = OPS::RADIO;
  field.varname = (CORBA::String_var)CORBA::string_dup(varname);
  field.defValue = (CORBA::String_var)CORBA::string_dup(defValue);

  //get the first field: column or the ENDBUTTON indication
  OZT_Value value = radioButtons.removeFirst();

  while( value != OZT_Value( "ENDRADIO" ) ) {

    int colVal, rowVal;
    
    colVal = (int)(value.toLong(result)) - 1;
    if (result.code != OZT_Result::NO_PROBLEM){
      validSoFar = FALSE;
    }
    
    //get the second field: row value
    value = radioButtons.removeFirst();
    
    rowVal = (int)(value.toLong(result)) - 1;
    if (result.code != OZT_Result::NO_PROBLEM){
      validSoFar = FALSE;
    }
      
    // get the third field: title
    value = radioButtons.removeFirst();
    
    if( validSoFar == TRUE ) {
      OPS::radioButton button;
      button.column = colVal;
      button.line = rowVal;
      button.title = (CORBA::String_var)CORBA::string_dup( value );

TRACE_FLOW(trace, setRadioButtonGroupField , "(radio button field:" << colVal << "," << rowVal << "," << value <<  ")");

      field.buttons.length( field.buttons.length() + 1 );
      field.buttons[field.buttons.length() - 1] = button;
    }
 
   //get the first field again: column or the ENDBUTTON indication
    value = radioButtons.removeFirst();
  }
  
  if( validSoFar == TRUE ){
    fields->length(fields->length()+1);
    (*fields)[fields->length()-1] = field;

    varnames.insert(varname);
  }

 TRACE_OUT(trace, setRadioButtonGroupField, validSoFar);

  return validSoFar;
}

//***************************************************************************


RWBoolean OZT_IOWin::setCheckBoxField( const OZT_Value &col,
				       const OZT_Value &row,
				       const OZT_Value &title,
				       const OZT_Value &varname,
				       const OZT_Value &defValue,
				       OPS::formFieldList * fields,
				       RWTValOrderedVector<RWCString> &varnames ) {

  OZT_Result result;

 TRACE_IN(trace, setCheckBoxField , "(" << col << "," << row << "," << title << "," << varname << ',' << defValue << ")");

  int colVal, rowVal;

  colVal = (int)(col.toLong(result)) - 1;
  if (result.code != OZT_Result::NO_PROBLEM){
    TRACE_OUT(trace, setInputField, 0);
    return FALSE;
  }
  
  rowVal = (int)(row.toLong(result)) - 1;
  if (result.code != OZT_Result::NO_PROBLEM){
    TRACE_OUT(trace, setInputField, 0);
    return FALSE;
  }

  OPS::formField field;
  field.type = OPS::CHECKBOX;
  field.column = colVal;
  field.line = rowVal;
  field.title = (CORBA::String_var)CORBA::string_dup(title);
  field.varname = (CORBA::String_var)CORBA::string_dup(varname);
  field.defValue = (CORBA::String_var)CORBA::string_dup(defValue);
  fields->length(fields->length()+1);
  (*fields)[fields->length()-1] = field;

  varnames.insert(varname);
TRACE_OUT(trace, setCheckBoxField , 1);

  return TRUE;

}

//***************************************************************************

RWBoolean OZT_IOWin::setButtonField( const OZT_Value &col,
				     const OZT_Value &row,
				     const OZT_Value &title,
 				     const OZT_Value &label,
				     OPS::formFieldList * fields ) {

  OZT_Result result;

 TRACE_IN(trace, setButtonField, "(" << col << "," << row << "," << title << "," << label << ")");

  int colVal, rowVal;

  colVal = (int)(col.toLong(result)) - 1;
  if (result.code != OZT_Result::NO_PROBLEM){
   TRACE_OUT(trace, setInputField, 0);
    return FALSE;
  }
  
  rowVal = (int)(row.toLong(result)) - 1;
  if (result.code != OZT_Result::NO_PROBLEM){
  TRACE_OUT(trace, setInputField, 0);
    return FALSE;
  }

  //create the field
  OPS::formField field;
  field.type = OPS::BUTTON;
  field.column = colVal;
  field.line = rowVal;  
  field.label = (CORBA::String_var)CORBA::string_dup(label);
  field.title = (CORBA::String_var)CORBA::string_dup(title);

  //insert the field in the field array
  fields->length(fields->length()+1);
  (*fields)[fields->length()-1] = field;

 TRACE_OUT(trace, setButtonField , 1);

  return TRUE;
}

//***************************************************************************

RWBoolean OZT_IOWin::setInputField(const OZT_Value &col,
                                   const OZT_Value &row,
                                   const OZT_Value &len,
                                   const OZT_Value &varname,
                                   const OZT_Value &defaultValue,
                                   OPS::formFieldList * fields,
                                   RWTValOrderedVector<RWCString> &varnames)
{
 TRACE_IN(trace, setInputField, "(" << col << "," << row << "," << len <<
                                   ") , (" << varname << "," << defaultValue << ")");
  int colVal, rowVal, lenVal;
  RWCString initialValue;
  OZT_Result result;

  colVal = (int)(col.toLong(result)) - 1;
  if (result.code != OZT_Result::NO_PROBLEM){
    TRACE_OUT(trace, setInputField, 0);
    return FALSE;
  }

  rowVal = (int)(row.toLong(result)) - 1;
  if (result.code != OZT_Result::NO_PROBLEM){
  TRACE_OUT(trace, setInputField, 0);
    return FALSE;
  }

  lenVal = (int)(len.toLong(result));
  if (result.code != OZT_Result::NO_PROBLEM){
 //   TRACE_OUT(trace, setInputField, 0);
    return FALSE;
  }

  if (rowVal < 0)
    rowVal = 0;

  if (colVal < 0)
    colVal = 0;

  if (lenVal < 0)
    lenVal = 0;

  if (defaultValue.length() > lenVal) {
    // Extract part of the default value (an RWCString)
    initialValue = defaultValue(0, lenVal);
  }
  else {
    initialValue = defaultValue;
  }

 TRACE_FLOW(trace, setInputField, initialValue);

  OPS::formField field;
  field.type = OPS::VAR;
  field.column = colVal;
  field.line = rowVal;
  field.width = lenVal;
  field.defValue = (CORBA::String_var)CORBA::string_dup(initialValue);
  field.varname = (CORBA::String_var)CORBA::string_dup(varname);
  fields->length(fields->length()+1);
  (*fields)[fields->length()-1] = field;
  varnames.insert(varname);

 TRACE_OUT(trace, setInputField, 1);

  return TRUE;
}



RWBoolean OZT_IOWin::setIOWinCommandList(OPS::iowCommandList *commandList)
{
  	TRACE_IN(trace, setIOWinCommandList, "");

	for (int i = 0; i < ioWinIndex; i++) {
		TRACE_FLOW(trace, setIOWinCommandList, "(command index " << i << ")");

		OPS::iowCmd command;
  		TRACE_FLOW(trace, setIOWinCommandList, "(" << ioWinCommands[i].commandType << "," << ioWinCommands[i].x1 << "," << ioWinCommands[i].y1 <<
                                   ") , (" << ioWinCommands[i].x2 << "," << ioWinCommands[i].y2 << "," << ioWinCommands[i].sText << ")");
		command.commandType = ioWinCommands[i].commandType;
		command.x1 = ioWinCommands[i].x1;
		command.y1 = ioWinCommands[i].y1;
		command.x2 = ioWinCommands[i].x2;
		command.y2 = ioWinCommands[i].y2;
		command.sText = (CORBA::String_var)CORBA::string_dup(ioWinCommands[i].sText);
		command.bFormat = ioWinCommands[i].bFormat;
		commandList->length(commandList->length()+1);
		(*commandList)[commandList->length()-1] = command; 
	}
  	TRACE_OUT(trace, setIOWinCommandList, 1);
  	return TRUE;
}



//*******************************
//
// class IOWinCommand
//
//*******************************

IOWinCommand::IOWinCommand(){}

IOWinCommand::IOWinCommand(short ct) {
	commandType = ct;
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
	sText = "";
	bFormat = false;
}

IOWinCommand::IOWinCommand(short ct, int x, int y) {
	commandType = ct;
	x1 = x;
	y1 = y;
	x2 = 0;
	y2 = 0;
	sText = "";
	bFormat = false;
}

IOWinCommand::IOWinCommand(short ct, int x, int y, int xx, int yy) {
	commandType = ct;
	x1 = x;
	y1 = y;
	x2 = xx;
	y2 = yy;
	sText = "";
	bFormat = false;
}

IOWinCommand::IOWinCommand(short ct, RWCString text, RWBoolean format) {
	commandType = ct;
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
	sText = text;
	bFormat = format;
}

IOWinCommand::IOWinCommand(const IOWinCommand& iowc) {
	commandType = iowc.commandType;
	x1 = iowc.x1;
	y1 = iowc.y1;
	x2 = iowc.x2;
	y2 = iowc.y2;
	sText = iowc.sText;
	bFormat = iowc.bFormat;
}

IOWinCommand& IOWinCommand::operator=(const IOWinCommand& iowc) {
	commandType = iowc.commandType;
	x1 = iowc.x1;
	y1 = iowc.y1;
	x2 = iowc.x2;
	y2 = iowc.y2;
	sText = iowc.sText;
	bFormat = iowc.bFormat;
			
	return *this;
}




