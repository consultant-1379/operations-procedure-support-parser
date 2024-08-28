//Source Code Control System revision handling, optional
// ClearCase: @(#) syn-opsserver/opslib/ttcb/src/tas_tc_com_entry.cc @@/main/2 2000-04-03.17:56 EHS"

/*
 *--------------------------------------------------------------------------
 *
 * Name         tas_tc_com_entry.cc
 *
 * *******************************************************************
 * * COPYRIGHT (c) 1990 Ericsson Telecom AB, Sweden.                 *
 * *                   All rights reserved                           *
 * *                                                                 *
 * * The copyright to the computer program(s) herein is the property *
 * * of Ericsson Telecom AB, Sweden. The programs may be used or     *
 * * copied only with the written permission of Ericsson Telecom AB. *
 * *******************************************************************
 *
 * Product      System          TMOS
 *              Subsystem       TAP
 *              Function block  TTCB 
 *              Software unit   TTCLIB
 *              
 * Document no  02/19055-CAA 134 420
 *
 * Rev-state    D
 *
 * Original     1990-04-03 by TX/HJL Anders Olander
 *
 * Description  Command Request Entries. Described in the API.
 *		15519-CNA 114 049 Uen
 *
 * Revision     E 1993-07-19 by JV/PBJ Erika Biesse
 * Description  New operator ==
 *        
 * Revision     D 1992-02-18 by TM/HJG Gunni Kallander
 * Description  com_entry.H changed to tas_tc_com_entry.hh
 *              ComEntry changed to TAS_TC_com_entry
 *        
 * Revision     C 1992-02-04 by TM/HJM Anders Olander
 * Description  Added Get methods.
 *
 * Revision     B 1991-09-18  by TM/HJ Klas Brandt
 * Description  com_entry.YC and comentry.LC changed to com_entry.yc
 *              and com_entry.lc
 *
 *-------------------------------------------------------------------------
 */

//#include <colme.C>
//#include <colme_CXA_101_005.C>
//Anders Berglund VK/EHS/PBO 950918

#include <mystring.hh>
#include <pwd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#if !(SunOS4 || __hpux)          // SunOS5
#include <netinet/in.h>
#endif

#include <current.hh>
#include <tas_tc_com_entry.hh>

/* Variables to comunicate result from parsing.
 * yacc doesn't provide any better way to
 * return values.
 */
static char *host, *commandline, *user;
static int year, month, day, hour, minute, split, id;
static enum interv intervalbase;

//#include <com_entry.yc>
//#include <com_entry.lc>
/* Name of the intervals. The names are also defined
 * in com_entry.L, to allow parsing. Remember to change
 * both.
 */
char *IntervalName[] = {"HOURLY", "DAILY", "WEEKLY",
			"MONTHLY", "ANNUALLY", "NONE",
			(char *)0};


/*****************************************************
 * Function that checks that a date is a valid date.
 * First the date is converted to the internal time
 * format (time(3)), and then back again. If there
 * is any difference, it's an illegal date. 
 * If TCANY if given for some parameter, the date
 * has to checked for any value in that parameter.
 * That is achived by using a most restrective value,
 * that is February a non-leap year.
 * Returns 0 on success, and -1 on failure.
 */
static int check_date(int minute = 0,
		      int hour = 0,
		      int day = 1,
		      int month = 2,
		      int year = 1990) {
	struct tm check;
	if (minute == TCANY)
		minute = 0;
	if (hour == TCANY)
		hour = 0;
	if (day == TCANY)
		day = 1;
	if (month == TCANY)
		month = 2;
	if (year == TCANY)
		year = 1990;
	check.tm_sec = 1; /* Fool the optimizer */
	check.tm_sec = 0;
	check.tm_min = minute;
	check.tm_hour = hour;
	check.tm_mday = day;
	check.tm_mon = month - 1;
	check.tm_year = year - 1900;

#ifdef SunOS4
	timelocal(&check);
#else
	check.tm_isdst = -1;
	(void)mktime(&check);
#endif

	if (check.tm_min != minute ||
	    check.tm_hour != hour ||
	    check.tm_mday != day ||
	    check.tm_mon != month - 1 ||
	    check.tm_year != year - 1900)
		return -1;
	else
		return 0;
}


/**************************************************
 * Common constructor function. Checks the parameters, and copies
 * the char* fields.
 * No returns.
 * BADARG is used to save my fingers.
 */

#define BADARG	{state = TTCB_CE_ILLEGAL_ARGUMENT; return;}

void TAS_TC_com_entry::TAS_TC_com_entry_constructor(
			  const char *Host,
			  const char *CommandLine,
			  int Year,
			  int Month,
			  int Day,
			  int Hour,
			  int Minute,
			  const char *User,
			  enum interv IntervalBase,
			  int Split,
			  int Id) {
	if (!this) {return;}

	state = TTCB_CE_NORMAL;
        commandline = (char *)0;
        host = (char *)0;
        user = (char *)0;

	if (Host) {
		/* Since gethostbyname doesn't accept a const char *, the string
		 * has to be copied.
		 */
		char *host_copy;
		int bad_host_arg;

		if (!(host_copy = strdup2(Host)) ||
		    !gethostbyname(host_copy))
			bad_host_arg = 1;
		else
			bad_host_arg = 0;

		delete []host_copy; host_copy = (char *)0;
		if (bad_host_arg)
			BADARG
		if (!(host = strdup2(Host))) {
			state = TTCB_CE_OUT_OF_MEMORY;
			delete host; host = (char *)0;
			return;
		}
	} else {
		host = strdup2(Get_host());
	}


	if (!CommandLine)
		BADARG

	switch (IntervalBase) {
		case NONE:
			if (Split != 1)
				BADARG
			break;
		case WEEKLY:
			if (Split < SUN || Split > SAT)
				BADARG
			break;
		default:
			if (Split < 1 || Split > 12)
				BADARG
			break;
	}

	switch (IntervalBase) {
		case NONE:
			if (Year == TCANY)
				BADARG
		case ANNUALLY:
			if (Month == TCANY)
				BADARG
		case MONTHLY:
			if (Day == TCANY)
				BADARG
		case WEEKLY:
		case DAILY:
			if (Hour == TCANY)
				BADARG
		case HOURLY:
			if (Minute == TCANY)
				BADARG
			break;
		default:
			BADARG
	}

	switch (IntervalBase) {
		case HOURLY:
			if (Hour != TCANY)
				BADARG
		case DAILY:
		case WEEKLY:
			if (Day != TCANY)
				BADARG
		case MONTHLY:
			if (Month != TCANY)
				BADARG
		case ANNUALLY:
			if (Year != TCANY)
				BADARG
		case NONE:
			break;
		default:
			this->state = TTCB_CE_PROGRAM_ERROR;
			return;
	}

	if (check_date(Minute, Hour, Day, Month, Year))
		BADARG
	id = Id;
	if (old()) 
		state = TTCB_CE_OLD;
	else
		state = TTCB_CE_NORMAL;
	year = Year;
	month = Month;
	day = Day;
	hour = Hour;
	minute = Minute;
	interval = IntervalBase;
	split = Split;

	//Remove leading white space in command
	while (*CommandLine == ' ') CommandLine++; 
	if (!(commandline = strdup2(CommandLine)) ||
	    !(user = strdup2(User)) && User) {
		state = TTCB_CE_OUT_OF_MEMORY;
		delete commandline; commandline = (char *)0;
		delete host; host = (char *)0;
		delete user; user = (char *)0;
		return;
	}
	return;
}


/**********************************************************
 * Constructing with no arguments, gives an "empty" request.
 */
TAS_TC_com_entry::TAS_TC_com_entry() {
        commandline = (char *)0;
        host = (char *)0;
        user = (char *)0;
	state = TTCB_CE_EMPTY;
        id = 0;
}

/**********************************************************
 * Copy Constructor
 */
TAS_TC_com_entry::TAS_TC_com_entry (const TAS_TC_com_entry& to_copy) {
         id = to_copy.id;
         state = to_copy.state;
         year = to_copy.year;
         month = to_copy.month;
         day = to_copy.day;
         hour = to_copy.hour;
         minute = to_copy.minute;
         interval = to_copy.interval;
         split = to_copy.split;
         host = strdup2(to_copy.Get_host());
         commandline = strdup2(to_copy.commandline);
         user = strdup2(to_copy.user);
}

TAS_TC_com_entry& TAS_TC_com_entry::operator=(const TAS_TC_com_entry& to_assign) {
         delete host; host = (char *)0;
         delete commandline; commandline = (char *)0;
         delete user; user = (char *)0;

         id = to_assign.id;
         state = to_assign.state;
         year = to_assign.year;
         month = to_assign.month;
         day = to_assign.day;
         hour = to_assign.hour;
         minute = to_assign.minute;
         interval = to_assign.interval;
         split = to_assign.split;
         host = strdup2(to_assign.Get_host());
         commandline = (to_assign.commandline ? strdup2(to_assign.commandline) : 0);
         user = (to_assign.user ? strdup2(to_assign.user) : 0);

         return *this;
}

/**********************************************************
 * Constructor patterns, which call the common constructor.
 */
TAS_TC_com_entry::TAS_TC_com_entry(const char *CommandLine,
		   int Year,
		   int Month,
		   int Day,
		   int Hour,
		   int Minute,
		   enum interv IntervalBase,
		   int Split) {
	TAS_TC_com_entry_constructor((char *)0, CommandLine,
			     Year, Month, Day, Hour, Minute,
			     (char *)0, IntervalBase, Split);
}


/**********************************************************
 * Constructor patterns, which call the common constructor.
 */
TAS_TC_com_entry::TAS_TC_com_entry(const char *Host,
		   const char *CommandLine,
		   int Year,
		   int Month,
		   int Day,
		   int Hour,
		   int Minute,
		   enum interv IntervalBase,
		   int Split) {
	TAS_TC_com_entry_constructor(Host, CommandLine,
			     Year, Month, Day, Hour, Minute,
			     (char *)0, IntervalBase, Split);
}


/**********************************************************
 * Constructor patterns, which call the common constructor.
 */
TAS_TC_com_entry::TAS_TC_com_entry(const char *CommandLine,
		   int Year,
		   int Month,
		   int Day,
		   int Hour,
		   int Minute,
		   int Id,
		   enum interv IntervalBase,
		   int Split) {
	TAS_TC_com_entry_constructor((char *)0, CommandLine,
			     Year, Month, Day, Hour, Minute,
			     (char *)0, IntervalBase, Split, Id);
}


/**********************************************************
 * Constructor patterns, which call the common constructor.
 */
TAS_TC_com_entry::TAS_TC_com_entry(const char *Host,
		   const char *CommandLine,
		   int Year,
		   int Month,
		   int Day,
		   int Hour,
		   int Minute,
		   int Id,
		   enum interv IntervalBase,
		   int Split) {
	TAS_TC_com_entry_constructor(Host, CommandLine,
			     Year, Month, Day, Hour, Minute,
			     (char *)0, IntervalBase, Split, Id);
}

/**********************************************************
 * Constructor patterns, which call the common constructor.
 */
TAS_TC_com_entry::TAS_TC_com_entry(const char *Host,
		   const char *CommandLine,
		   int Year,
		   int Month,
		   int Day,
		   int Hour,
		   int Minute,
		   const char *User,
		   int Id,
		   enum interv IntervalBase,
		   int Split) {
	TAS_TC_com_entry_constructor(Host, CommandLine,
			     Year, Month, Day, Hour, Minute,
			     User, IntervalBase, Split, Id);
}


/**********************************************************
 * Constructor patterns, which call the common constructor.
 */
TAS_TC_com_entry::TAS_TC_com_entry(const char *CommandLine,
		   int Year,
		   int Month,
		   int Day,
		   int Hour,
		   int Minute,
		   const char *User,
		   enum interv IntervalBase,
		   int Split) {
	TAS_TC_com_entry_constructor((char *)0, CommandLine,
			     Year, Month, Day, Hour, Minute,
			     User, IntervalBase, Split);
}


/**********************************************************
 * Constructor patterns, which call the common constructor.
 */
TAS_TC_com_entry::TAS_TC_com_entry(const char *Host,
		   const char *CommandLine,
		   int Year,
		   int Month,
		   int Day,
		   int Hour,
		   int Minute,
		   const char *User,
		   enum interv IntervalBase,
		   int Split) {
	TAS_TC_com_entry_constructor(Host, CommandLine,
			     Year, Month, Day, Hour, Minute,
			     User, IntervalBase, Split);
}

/**********************************************************
 * Destructor
 */
TAS_TC_com_entry::~TAS_TC_com_entry () {
      delete []commandline; commandline = (char *)0;
      delete []host; host = (char *)0;
      delete []user; user = (char *)0;
}

/******************************************************
 * Error test operator method. returns zero if the
 * request is usable, and negative elsewhen. The
 * negative returns can be tested with constant macros
 * defined in tas_tc_com_entry.hh
 */
int TAS_TC_com_entry::operator ! () const {
	if (!this) return TTCB_CE_PROGRAM_ERROR;

	switch (state) {
		case TTCB_CE_OLD:
		case TTCB_CE_NORMAL:
			return TTCB_CE_OK; // Defined as zero

		case 0:
			((TAS_TC_com_entry *)this)->state = TTCB_CE_EMPTY;
		case TTCB_CE_EMPTY:
		case TTCB_CE_ILLEGAL_ARGUMENT:
		case TTCB_CE_BAD_INPUT_SYNTAX:
		case TTCB_CE_OUT_OF_MEMORY:
		case TTCB_CE_PROGRAM_ERROR:
			return state;

		default:
			return ((TAS_TC_com_entry *)this)->state = TTCB_CE_PROGRAM_ERROR;
	}
}


/********************************************************
 * Casting method to check a request is usable. 
 * Uses operator ! defined above.
 * Returns non-null when usable, and null when not.
 */ 
TAS_TC_com_entry::operator void * () const {
	return (void *)(!*this ? 0 : -1);
}


/********************************************************
 * Comparison method to check if a request is equal to 
 * another.
 * Returns 1 at equality, and 0 when difference.
 */ 
int TAS_TC_com_entry::operator == (const TAS_TC_com_entry& to_compare) const {
	const char *h1host = this->Get_host();
	const char *h2host = to_compare.Get_host();

		if (year == to_compare.year &&
		    month == to_compare.month &&
		    day == to_compare.day &&
		    hour == to_compare.hour &&
		    minute == to_compare.minute && 
		    interval == to_compare.interval &&
		    split == to_compare.split &&
		    !strcmp(commandline, to_compare.commandline) &&
		    (h1host && h2host &&
		    !strcmp(h1host, h2host)))
				return 1;
		else return 0;
}


/******************************************************
 * Output a request to a stream. The format has to 
 * convey the input parser (operator >>), and also
 * has to be readable.
 * Format:
 * [<uname>][@<hostname>] [[[[<year>-]<month>-]<day>] <hour>:]<minute>
 *	[<interval>[/<split>]] # <command> \n
 * 
 * (<split> is day of week, when interval is WEEKLY)
 * (In <command> \n is escaped with \ and n, and \ is escaped
 * with a double \ )
 */
ostream& operator << (ostream& out, TAS_TC_com_entry ce) {
        static Current current;
	char oldfill;
	const char *temp;
	long oldadj;

	if (!ce) {
		out.clear(ios::failbit|out.rdstate());
		return out;
	}

	oldfill = out.fill(' ');
	oldadj = out.setf(ios::right, ios::adjustfield);
	out.width(8 /* Width of <uname> */);
	if (ce.user) {
		out << ce.user;
	} else {
		out << "";
	}

	out.setf(ios::left, ios::adjustfield);
	out.width(10 /* Width of <id> */);
	if (ce.Get_id()) {
		out << ce.Get_id();
	} else {
		out << "";
	}
	out << " ";

	out.setf(ios::left, ios::adjustfield);
//	if (strcmp(ce.Get_host(), current.host ()) != 0)
	if (ce.Get_host()) 
		out << "@";
	else
		out << " ";
	out.width(10 /* Width of <host> */);
//	if (strcmp(ce.Get_host(), current.host ()) != 0) {
	if (ce.Get_host()) {
		out << ce.Get_host();
	} else {
		out << "";
	}
	out << " ";

	out.setf(ios::right, ios::adjustfield);
	out.width(4 /* Width of <year> */);
	if (ce.interval > ANNUALLY && ce.year != TCANY) {
		out.fill('0');
		out << ce.year << "-";
	} else {
		out.fill(' ');
		out << ""      << " ";
	}

	out.width(2 /* Width of <month> */);
	if (ce.interval > MONTHLY && ce.month != TCANY) {
		out.fill('0');
		out << ce.month << "-";
	} else {
		out.fill(' ');
		out << ""       << " ";
	}

	out.width(2 /* Width of <day> */);
	if (ce.interval > DAILY && ce.day != TCANY) {
		out.fill('0');
		out << ce.day << " ";
	} else {
		out.fill(' ');
		out << ""     << " ";
	}

	out.width(2 /* Width of <hour> */);
	if (ce.interval > HOURLY && ce.hour != TCANY) {
		out.fill('0');
		out << ce.hour << ":";
	} else {
		out.fill(' ');
		out << ""      << " ";
	}

	out.width(2 /* Width of <minute> */);
	if (ce.minute != TCANY) {
		out.fill('0');
		out << ce.minute << "  ";
	} else {
		out.fill(' ');
		out << ""        << "  ";
	}

	out.fill(' ');
	out.width(8 /* Width of <interval> */);
	if (ce.interval != NONE) {
		out << IntervalName[(int)ce.interval];
	} else {
		out << "";
	}

	out.setf(ios::left, ios::adjustfield);
	if (ce.interval == WEEKLY) {
		switch (ce.split) {
			case MON: out << "/MON"; break;
			case TUE: out << "/TUE"; break;
			case WED: out << "/WED"; break;
			case THU: out << "/THU"; break;
			case FRI: out << "/FRI"; break;
			case SAT: out << "/SAT"; break;
			case SUN: out << "/SUN"; break;
			default:  out << "    "; break; // Error
		}
	} else if (ce.split > 1) {
		out << "/";
		out.width(3);
		out << ce.split;
	} else {
		out << "    "; // 3 spaces
	}

	/* Output command. Escape sequence coding coresponds to decoding
	 * in Decode_ce_command below.
	 */
	out << " # ";
	if (ce.commandline) 
	    for (temp = ce.commandline; *temp; temp++)
		switch (*temp) {
		case '\n': out << "\\n"; break;
		case '\\': out << "\\\\"; break;
		default: out << *temp;
	    }
	out << "\n";
	return out;
}


/****************************************************************
 * Decode a command string read from a istream, compare output
 * coding above.
 * Returns first argument, pointing to the now modified command
 * string.
 */
static char *Decode_ce_command(char *command) {
	char *p;
	for (p = command; *p; p++)
		if (*p == '\\')
			switch (*strshl(p)) {
			case '\\': break;
			case 'n' : *p = '\n';
			default  : /* What?! */ break;
		}
	return command;
}


/****************************************************************
 * Input a request from a stream. Same format as in operator <<.
 * The actual parsing is described in com_entry.L (lex++ input)
 * and com_entry.Y (yacc++ input). 
 */
istream& operator >> (istream& in, TAS_TC_com_entry& ce) {
	in.clear();
/* <vip> ttcb_ce_yyin = &in;
	switch (ttcb_ce_yyparse()) {
		case TTCB_CE_OK: // Normal return
			ce.TAS_TC_com_entry_constructor(host,
				Decode_ce_command(commandline),
				year, month, day, hour, minute,
				user, intervalbase, split, id);
			if (!ce)
				in.clear(ios::failbit|in.rdstate());
			break;
		case TTCB_CE_BAD_INPUT_SYNTAX: // Error return
			ce.state = TTCB_CE_BAD_INPUT_SYNTAX;
			in.clear(ios::failbit|in.rdstate());
			break;
		case TTCB_CE_EMPTY: // End of input return
			ce.state = TTCB_CE_EMPTY;
			in.clear(ios::eofbit|in.rdstate());
			break;
		default:
			ce.state = TTCB_CE_PROGRAM_ERROR;
			in.clear(ios::badbit|in.rdstate());
			break;
	}
	return in;*/
}

/*****************************************************
 * This function checks if request entry will never be
 * executed in the future.
 *
 * Stub, always returning 0, that is false.
 * To be replaced.
 * Should return 1 for true, and 0 for false.
 */
int TAS_TC_com_entry::old() {
	if (!this) return 0;

	return 0; // False;
}


/*****************************************************
 * Get host name.
 * Returns: empty string on failure
 */
const char *TAS_TC_com_entry::Get_host() const {
        static Current current;

	// Error return
	if (!*this) return (char *)0;

        if (host) 
           return host;

        // Host not filled in, which means current host
        return current.host ();
}


/*****************************************************
 * Get user name.
 * Returns: (char *)0 if not set and on failure
 */
const char *TAS_TC_com_entry::Get_user() const {
	if (!*this) return (char *)0;

	return user;
}


/*****************************************************
 * Get command line string
 * Returns: (char *)0 on failure
 */
const char *TAS_TC_com_entry::Get_command_line() const {
	if (!*this) return (char *)0;

	return commandline;
}


/*****************************************************
 * Get Year value
 * Returns: TCANY on failure
 */
int TAS_TC_com_entry::Get_year() const {
	if (!*this) return TCANY;

	// Not applicable?
	if (interval <= ANNUALLY) return TCANY;

	return year;
}


/*****************************************************
 * Get Month value
 * Returns: TCANY on failure
 */
int TAS_TC_com_entry::Get_month() const {
	if (!*this) return TCANY;

	// Not applicable?
	if (interval <= MONTHLY) return TCANY;

	return month;
}


/*****************************************************
 * Get Day value
 * Returns: TCANY on failure
 */
int TAS_TC_com_entry::Get_day() const {
	if (!*this) return TCANY;

	// Not applicable?
	if (interval <= DAILY) return TCANY;

	return day;
}


/*****************************************************
 * Get Hour value
 * Returns: TCANY on failure
 */
int TAS_TC_com_entry::Get_hour() const {
	if (!*this) return TCANY;

	// Not applicable?
	if (interval <= HOURLY) return TCANY;

	return hour;
}


/*****************************************************
 * Get Minute value
 * Returns: TCANY on failure
 */
int TAS_TC_com_entry::Get_minute() const {
	if (!*this) return TCANY;

	return minute;
}


/*****************************************************
 * Get IntervalBase value
 * Return NONE (which is a legal value) on failure.
 */
enum interv TAS_TC_com_entry::Get_interval_base() const {
	if (!*this) return NONE;

	return interval;
}


/*****************************************************
 * Get Split value
 * Returns: TCANY on failure
 */
int TAS_TC_com_entry::Get_split() const {
	if (!*this) return TCANY;

	// Not applicable?
	if (interval == NONE || interval == WEEKLY) return TCANY;

	// Standard case
	return split;
}


/*****************************************************
 * Get Weekday value
 * Returns: TCANY on failure
 */
int TAS_TC_com_entry::Get_weekday() const {
	if (!*this) return TCANY;

	// Error Cases
	if (interval != WEEKLY) return TCANY;

	// Standard case
	return split;
}

/*****************************************************
 * Get Id value
 * Returns: TCANY on failure
 */
int TAS_TC_com_entry::Get_id() const {
	if (!*this) return TCANY;

	// Error Cases

	// Standard case
	return id;
}

