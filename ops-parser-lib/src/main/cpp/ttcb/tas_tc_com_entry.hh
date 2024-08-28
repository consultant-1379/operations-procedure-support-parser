#ifndef TAS_TC_COM_ENTRY
#define TAS_TC_COM_ENTRY
#ifndef lint
#endif

//**********************************************************************
// 
// .NAME TAS_TC_com_entry - Insert time controlled command requests.
// .LIBRARY 3C++
// .HEADER  TAS TC
// .INCLUDE tas_tc_com_entry.hh

// .SECTION COPYRIGHT
//  COPYRIGHT Ericsson Hewlett-Packard Telecommunications AB 1995
//
// The Copyright to the computer program(s) herein
// is the property of Ericsson Hewlett-Packard Telecom AB, Sweden.
// The program(s) may be used and/or copied with the
// written permission from Ericsson Hewlett-Packard Telecom AB or in
// accordance with the terms and conditions stipulated
// in the agreement/contract under which the program(s)
// have been supplied.
// 

// .SECTION DESCRIPTION 
//      TAS_TC_com_entry has functions to insert a command request to the
//      TAS_TC_time_control object.

// .SECTION ERROR HANDLING
//	No error reports are sent to PMS.
//      The return values are described in each method.

// DOCUMENT NO
//	01/19055-CAA 134 420

// AUTHOR 
// 	1990-03-28 by TX/HJL Anders Olander

// .SECTION REVISION
//	E
//	1995-05-05

// CHANGES
// 	<Revision history>
// $Log$
//	REV NO	DATE 	NAME	DESCRIPTION
//      C       1992-02-13 TM/HJG Gunni Kallander Inserted get methods to
//                                                retrieve the entered
//                                                attributes for instance when
//                                                you want to print a list.
//                                                Make it possible to use GENMAN.
//
//      D       1993-07-19 JV/PBJ Erika Biesse    New == operator.
//
//	E	1995-05-05 PBJ Gunni Kallander	  Explain of the host parameter
//

// .SECTION SEE ALSO 
// 	TAS_TC_time_control


//**********************************************************************

#include <iostream>
using namespace std;
#define MON     1
#define TUE     2
#define WED     3
#define THU     4
#define FRI     5
#define SAT     6
#define SUN     0

// Unspecified date or time parameter representation. //
#define TCANY (-1)

// Values for state:
#define TTCB_CE_OLD                     ( 2)
#define TTCB_CE_NORMAL                  ( 1)
#define TTCB_CE_OK                      ( 0)
#define TTCB_CE_EMPTY                   (-1)
#define TTCB_CE_ILLEGAL_ARGUMENT        (-2)
#define TTCB_CE_BAD_INPUT_SYNTAX        (-3)
#define TTCB_CE_OUT_OF_MEMORY           (-4)
#define TTCB_CE_PROGRAM_ERROR           (-5)

// Added by etoslu to  make ttcb compile 22-01-02
#define RA_IOSTREAM

enum interv
{
  HOURLY, DAILY, WEEKLY, MONTHLY, ANNUALLY, NONE
};
		
//Member functions, constructors, destructors, operators

class TAS_TC_com_entry {        
        friend class Local;
        friend class Remote;
        friend class CrontabFile;
        friend int ttcb_remove_request(int, const char *);

public:
      
  TAS_TC_com_entry ();

  TAS_TC_com_entry(const TAS_TC_com_entry& to_copy);

  TAS_TC_com_entry& operator=(const TAS_TC_com_entry& to_assign);

  TAS_TC_com_entry (const char *Command_line,
                    int Year,
                    int Month,
                    int Day,
                    int Hour,
                    int Minute,
                    enum interv IntervalBase = NONE,
                    int Split = 1);

  TAS_TC_com_entry (const char *Host,
                    const char *Command_line,
                    int Year,
                    int Month,
                    int Day,
                    int Hour,
                    int Minute,
                    enum interv IntervalBase = NONE,
                    int Split = 1);
 
  TAS_TC_com_entry (const char *Command_line,
                    int Year,
                    int Month,
                    int Day,
                    int Hour,
                    int Minute,
                    int Id = 0,
                    enum interv IntervalBase = NONE,
                    int Split = 1);

  TAS_TC_com_entry (const char *Host,
                    const char *Command_line,
                    int Year,
                    int Month,
                    int Day,
                    int Hour,
                    int Minute,
                    int Id = 0,
                    enum interv IntervalBase = NONE,
                    int Split = 1);

  TAS_TC_com_entry (const char *Host,
                    const char *Command_line,
                    int Year,
                    int Month,
                    int Day,
                    int Hour,
                    int Minute,
                    const char *User,
                    int Id = 0,
                    enum interv IntervalBase = NONE,
                    int Split = 1);
 
  TAS_TC_com_entry (const char *Command_line,
                    int Year,
                    int Month,
                    int Day,
                    int Hour,
                    int Minute,
                    const char *User,
                    enum interv IntervalBase = NONE,
                    int Split = 1);

  TAS_TC_com_entry (const char *Host,
                    const char *Command_line,
                    int Year,
                    int Month,
                    int Day,
                    int Hour,
                    int Minute,
                    const char *User,
                    enum interv IntervalBase = NONE,
                    int Split = 1);
  // Description:
  //    There are basically two constructos available, the first one
  //    creating a simple request and the second one creating a repeating
  //    request. When constructing a simple request the interval parameter
  //    should be excluded. If the host parameter is excluded, the current
  //    host will execute the command. The split parameter defaults to one.
  //    On weekly repetition, the split argument is used to specify day of
  //    week.
  //    Users having root privileges may add and remove entries including 
  //    user name as an extra parameter.
  //    
  // Parameters:
  //    Host                    Host where the command should be executed.
  //                            It may be any host, reachable in the network
  //                            and where the user has the same login.
  //				Note, if the parameter is excluded the current
  //				host will execute the command.
  //    Command_line            Shell command line. Don't forget to redirect
  //                            the standard output and standard error. If
  //                            they are not redirected the output will be
  //                            mailed to the user.
  //                            Standard input may not be used.
  //    Year                    Year when the command should be executed.
  //                            Possible values: 1990 - 2099, TCANY
  //    Month                   Month when the command should be executed.
  //                            Possible values:  1 - 12, TCANY               
  //    Day                     Day when the command should be executed.
  //                            Possible values:  1 - 31, TCANY
  //    Hour                    Time when the command should be executed.
  //                            Possible values:  0 - 23, TCANY
  //    Minute                  Time when the command should be executed.
  //                            Possible values:  0 - 59
  //                            Note, the given value on minute must be at 
  //                            least 3 minutes from now. 
  //    IntervalBase            Possible values:
  //                            HOURLY     - Repetition every hour
  //                            DAILY      - Repetition every day
  //                            WEEKLY     - Repetition every week
  //                            MONTHLY    - Repetition every month
  //                            ANNUALLY   - Repetition every year
  //    Split                   For all intervalbases except WEEKLY - any integer
  //                            number 1..12. States how many times the command
  //                            should be executed in each period specified by
  //                            the IntervalBase field.. Eg IntervalBase set to
  //                            DAILY and Split set to 4, means execution 4 times
  //                            a day, that is every sixth hour. For IntervalBase
  //                            set to WEEKLY, this field tells which day of the
  //                            week, the command should be executed.
  //                            The values may be any of SUN, MON, TUE, WED, THU,
  //                            FRI, SAT (or 0..6, 0 = SUN, 1 = MON and so on).
  //    User                    System user name
  // Return value:
  //    -
  // Additional information:
  //	If the HOST parameter is excluded the current host will execute the
  //	command. This means that if the commmand should be removed it must be 
  //	done on the host where it was created. 
  //
  //    When creating repeating requests, some arguments should not be specified.
  //    On annually repetition year should not be specified, on monthly
  //    repetition neither year nor month should be specified. On weekly or
  //    daily repetition only hour and minute should be specified, and on 
  //    repetition every hour only minute.
  //
  //    A command request variable may be defined without initializing values,
  //    when you intend extracting (reading) requests from a stream.
  //
  //    To verify that a construction succeeded the error check method can be
  //    used.
  //
  //    TCANY represents an unspecified date or time argument. When TCANY is
  //    used it will be interpreted as the next possible time or date. TCANY
  //    can only be used for repeating requests.

  ~TAS_TC_com_entry ();
  // Description:
  //    Destructor
  // Parameters:
  //    -
  // Return value:
  //    -
  // Additional information:
  //    -

  int operator ! () const;
  // Description:
  // 	Checks if a command request is ok or not. 
  // Parameters: 
  //    -
  // Return value: 
  //    TTCB_CE_OK 		No error state, defined as zero.
  //    TTCB_CE_EMPTY		Error states
  //    TTCB_CE_ILLEGAL_ARGUMENT		
  //	TTCB_CE_BAD_INPUT_SYNTAX		
  //	TTCB_CE_OUT_OF_MEMORY		
  //	TTCB_CE_PROGERM_ERROR		          
  //
  // Additional information:
  //    Example:    if (!C) error (...) 
  //                where C is the command request to be checked.
  //
  //    See also the method void *() which is nearly the same.
  //
  //    The null-object terminated array returned by list () will be
  //    indicated as having an error state, which is useful when looping over
  //    the array.

  operator void *() const;
  // Description:
  //    Check if a command request is ok or not.
  // Parameters:
  //    -
  // Return value:
  //    non-null                No error found in the command request
  //    null                    Error found in the command request
  //
  // Additional information:
  //    Example:    if (C) return OK
  //                where C is the command request to be checked.
  //
  //    See also the method !() which is nearly the same. 

  int operator == (const TAS_TC_com_entry& to_compare) const;
  // Description:
  // 	Checks if a command request is equal to another. 
  // Parameters: 
  //    -
  // Return value: 
  //     1                 Equal.
  //     0                 Not equal.
  //     -1                Failure
  //
  // Additional information:
  //    -

  friend std::ostream& operator << (std::ostream&, TAS_TC_com_entry);
  // Description:
  //     Writes a command request entry to an ostream.
  // Parameters:
  //     -
  // Return value:
  //     S                 Success, where S is the output stream.
  //     null              Failure
  // Additional information:
  //     Output format may be changed in future versions. The output is only
  //     intended for human reading and TAS_TC_time_control extraction.

  friend std::istream& operator >> (std::istream&, TAS_TC_com_entry&);
  // Description:
  //     Reads a command request entry from an istream. If the file is not
  //     written by the istream (see above) the result is likely to be
  //     failure.
  // Parameters:
  //     -
  // Return value:
  //     S                 Success, where S is the input stream.
  //     null              Failure
  // Additional information:
  //     Input format may be changed in future versions. Only input
  //     previously inserted (output) by the TAS_TC_time_control insertion
  //     (output) method should be used.

  const char *Get_host () const;
  // Description:
  //    Returns the name on the host where the command request is executed.
  // Parameters:
  //    -
  // Return value:
  //    host name              Success
  //    null                   Failure 
  // Additional information:
  //    -

  const char *Get_user () const;
  // Description:
  //    Return the name of the user.
  // Parameters:
  //    -
  // Return value:
  //    user name              Success
  //    null                   Failure
  // Additional information:
  //    -

  const char *Get_command_line() const;
  // Description:
  //    Returns the requested command.
  // Parameters:
  //    -
  // Return value:
  //    command line           Success
  //    null                   Failure
  // Additional information:
  //	-

  int Get_year() const;
  // Description:
  //    Returns the year when the command will be executed.
  // Paramters:
  //    -
  // Return value:
  //    1990 - 2099            Success
  //    TCANY                  Failure
  // Additional information:
  //	-

  int Get_month() const;
  // Description:
  //    Returns the month when the command will be executed.
  // Parameters:
  //    -
  // Return value:
  //    1 - 12                 Success
  //    TCANY                  Failure
  // Additional information:
  //    -

  int Get_day() const;
  // Description:
  //    Returns the day when the command will be executed.
  // Parameters:
  //    - 
  // Return value:
  //    1 - 31                 Success
  //    TCANY                  Failure
  // Additional information:
  //    -

  int Get_hour() const;
  // Description:
  //    Returns the hour when the command will be executed.
  // Parameters:
  //    -
  // Return value:
  //    0 - 23                Success
  //    TCANY                 Failure
  // Additional information:
  //    -

  int Get_minute() const;
  // Description:
  //    Returns the minute when the command will be executed.
  // Parameters:
  //    -
  // Return value:
  //    0 - 59               Success
  //    TCANY                Failure
  // Additional information:
  //    -

  enum interv Get_interval_base() const;
  // Description:
  //    Returns the interval when the command will be executed.
  // Parameters:
  //    -
  // Return value:
  //    HOURLY, DAILY, WEEKLY, MONTHLY, ANNUALLY or NONE
  // Additional information:
  //    -

  int Get_split() const;
  // Description:
  //    Returns the number of times the command will be executed in
  //    the period specified in the interval.
  // Parameters:
  //    -
  // Return value:
  //    1 - 12               Success
  //    TCANY                Failure
  // Additional information:
  //    -
 
  int Get_weekday () const;
  // Description:
  //    Returns the day of week when the command will be executed.
  // Parameters:
  //    -
  // Return value:
  //    0 - 6                Success
  //    TCANY                Failure
  // Additional information:
  //    -

  int Get_id () const;
  // Description:
  //    Returns the id-number of the job.
  // Parameters:
  //    -
  // Return value:
  //    > 0                ID number
  //    0                  No id set
  //    TCANY                Failure
  // Additional information:
  //    -

private:   		//N.B. Optional, but a good rule!
  int old(); 
  void TAS_TC_com_entry_constructor(const char *, const char *,
       int, int, int, int, int, const char *, enum interv, int, int Id = 0);
 
private:
  int id, state;
  int year, month, day, hour, minute;
  enum interv interval;
  int split;
  char *host, *commandline, *user;

};

#endif 
