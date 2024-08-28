/*
 *--------------------------------------------------------------------------
 *
 * Name         cti.C
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
 * Document no  06/19055-CAA 134 420
 *
 * Rev-state    B
 *
 * Original     1990-04-05 by TX/HJL Anders Olander
 *
 * Description  Crontab File interface
 *
 * Revision     B 1991-07-04 by TM/HJG Peter Hertzman
 * Description  File protection for crontab changed in
 *              SunOS 4.1.1 ( comp. to SunOS 4.0.3 ) .
 *
 * Revision     C 1996-03-18 by VP Anders Berglund
 * Description  closed fd for p_error was forgotten
 *              p_error consumes all available fd's
 *
 * Revision     D 1998-06-09 by VU Valter Saaristu
 * Description  According to TR HA87548 change fork to fork1.
 *
 * Revision     <rev> <yyyy-mm-dd> by <dep> <name>
 * Description  <description-of-the-revision>
 *
 *-------------------------------------------------------------------------
 */

/* This code was modified for TMOS/HP. The reason is described in C++.0 */
#ifdef __hpux
#include <sys/unistd.h>
#endif

#ifdef SunOS4
#include <sysent.h>
#include <sys/time.h>
#include <sys/resource.h>
#else
#include <unistd.h>
#endif

#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/param.h>
#include <mystring.hh>
#include <pwd.h>
#include <sys/types.h>

#include <queuenotail.hh>
#include <tcparam.hh>

#include <CHA_Trace.H>
#include "cti.hh"

//static CAP_TRC_trace trace = CAP_TRC_DEF((char*)"cti", (char*)"C");

#ifndef MAXLINELENGTH
#define MAXLINELENGTH 1023
#endif

/* Variables to communicate result from parsing.
 * lex/yacc doesn't provide any better way to
 * return values.
 */
static int id, year;
static Ttc_Queue_no_tail *month, *day, *hour, *minute, *weekday;
static char *host, *command, collected_line[MAXLINELENGTH + 1];

static const char* TC_SHELL="/emt_ttcshr";

//#include <cti.yc>
//#include <cti.lc>

/*********************************************************
 * Constructor for crontab file interface. Tries to
 * get a lock, and then opens the file for reading and
 * starts a child process executing crontab(1) for writing.
 * Inputs: RdWr - The interface will be used to modify
 * the file. Dir - Tells which directory crontab uses. Not used,
 * after impl. of SunOS.4.1.1 .
 * User - user name, and name (without path) of the crontab
 * file.
 * Sets status.
 */
void CrontabFile::CrontabFile_constructor(int RdWr, const char *, const char *User) {

	////TRACE_IN(trace, CrontabFile_constructor, User);

	pidin = 0;
	pidout = 0;

	int p[2]; // Pipe fd array
	int p_in[2];
        int p_error[2];
	uid_t uid , called_uid  ;
	char a, buffer[MAXPATHLEN];
	const int ERROR_BUF_SIZE = 100;
	char error_buf[ERROR_BUF_SIZE + 1];

	// Initialize error_buf
	memset( error_buf, '\0', ERROR_BUF_SIZE + 1);

	mep = (MutualExclusion *)0;

	/* Set the user attribute. Only the superuser may
	 * have a value that is non-null. */
	uid = geteuid() ;
	if (uid) user = (char *)0 ;
	else user = strdup2(User);
	////TRACE_FLOW(trace, CrontabFile_constructor, uid);
	//TRACE_FLOW(trace, CrontabFile_constructor, user);


	if ( User != NULL ) {

		if (! ( getpwnam(User))) {
	        status = TTCB_CRT_AUTHORITY_ERROR ;
	        return ;
            }

	    called_uid = getpwnam(User)  -> pw_uid ;

	    if (uid && called_uid != uid ) {
	        status = TTCB_CRT_AUTHORITY_ERROR ;
	        return ;
            }
        }

        /* Try to lock  */
        if ((!(mep = new MutualExclusion(User)) || !*mep)) {
		status = TTCB_CRT_PROBLEMS;
		return;
	}

	/* Open the file for input */

	if ( pipe( p_in ) )
	{
		status = TTCB_CRT_PROBLEMS ;
		return ;
 	}
	if ( pipe( p_error ) )
	{
		status = TTCB_CRT_PROBLEMS ;
		return ;
 	}


#if (SunOS4 || __hpux)
	switch ( pidin = fork() )
#else
	switch ( pidin = fork() )
#endif
	{
		case  -1:
			status = TTCB_CRT_PROBLEMS ;
			return ;
		case   0:
			if ( close( p_in[0] ) || close( p_error[0] ) ||
			     close( 1 )       ||
			     ( dup( p_in[1] ) == -1 ) ||
			     close( p_in[1] ) ||
			     close(2)         ||
                             ( dup( p_error[1] ) == -1 ) ||
                             close( p_error[1])) _exit(16) ;
//                       if ( open("/dev/null",O_WRONLY) == -1)
//			     _exit(17) ;
			/* Change effective user if specified, thus reading
			   from the correct file */
			if (User) {
				struct passwd *upw =
					getpwnam(User);
				if (!upw) _exit(11);
				if (setuid(upw->pw_uid)) _exit(11);
			}
			execlp( "crontab" , "crontab", "-l", (char *) 0 );
			_exit(14);

	}

	close( p_in[1] );
        close( p_error[1] );
//<vip>	ctin.attach( p_in[0] ) ;
// Aviod dead-lock in case the crontab command produces so much output
// that the pipe is filled and the crontab command blocks.
        fcntl( p_error[0], F_SETFL, O_NONBLOCK );

        if (read (p_error [0], &error_buf, ERROR_BUF_SIZE) != 0)
        {
            if (strstr(error_buf, "authorized") != NULL)
            {
                // You are not allowed to use crontab
                status = TTCB_CRT_AUTHORITY_ERROR;
                return;
            };
        };

	//ehsanbe 960318
        //Correction fd was not closed
        close( p_error[0]);

	/* Start a new process for executing crontab(1) */
	if (RdWr) {
		if (pipe(p)) {
			status = TTCB_CRT_PROBLEMS;
			return;
		}
#if (SunOS4 || __hpux)
		switch (pidout = fork()) {
#else
		switch (pidout = fork()) {
#endif
			case -1:
				status = TTCB_CRT_PROBLEMS;
				return;
			case  0: // Child process
				if (close(0) ||
				    (dup(p[0]) == -1) ||
				    close(p[0]) ||
				    close(p[1]) ||
				    close(2)) _exit(12);
				if (open("/dev/null", O_WRONLY) == -1)
					_exit(13);

				/* Change effective user if specified, thus
				 * writing to the correct file.
				 */
				if (User) {
					struct passwd *upw =
						getpwnam(User);
					if (!upw) _exit(11);
					if (setuid(upw->pw_uid)) _exit(11);
				}

				/* Await first (wake up) character before
				 * starting the child process. If the
				 * input is closed before anything has
				 * been written, the crontab file should
				 * be removed.
				 */
				switch (read(0, &a, 1)) {
					case -1: _exit(12);
					case  0: // Remove crontab table
						/* Here the crontab file should be
						 * removed.
						 * Supplying the -r flag
						 * accomplishes that, but also
						 * gives an error message when
						 * the last two (or more) lines
						 * are removed "at the same time".
						 * Patch: Leave the file empty.
						 * This will cause the users()
						 * method to return all users that
						 * have ever used the time control
						 * facility.
						 */
						execlp("crontab", "crontab",
							/* "-r", */  (char *)0);
						_exit(14);
					case  1: // Make crontab table
						execlp("crontab", "crontab", (char *)0);
						_exit(14);
					default: // Program error
						_exit(15);
				}
		}
		close(p[0]);
	//<vip>	ctout.attach(p[1]);
	} else
		pidout = 0;
	status = TTCB_CRT_NOTHING_WRITTEN;
	return;
}


/****************************************************************
 * Destructor. If all input has not been read, read it, making
 * other (non-tc) line being copied.
 */
CrontabFile::~CrontabFile() {
	TAS_TC_com_entry temp;
	if (status == TTCB_CRT_WRITING_IN_PROGRESS)
		 while (*this >> temp && temp);

	if ( pidin ) {
//<vip>		int fdin = ctin.rdbuf()->fd();
		ctin.close();
//		close(fdin);
		/* Doesn't matter if the child process fails or not,
		 * the aplication will never know, whatever I do.
		 */
#if SunOS4
		wait4 (pidin, (union wait*)0, 0, 0);
#else
                waitpid (pidin, NULL, 0);
#endif
    	}

	if (pidout) {
//<vip>		int fd = ctout.rdbuf()->fd();
		ctout.close();
//		close(fd);
#if SunOS4
		wait4(pidout, (union wait*)0, 0, 0);
#else
                waitpid(pidout, NULL, 0);
#endif
	}
	delete mep;
	delete user;
}


/*************************************************************
 * Error test operator method. Returns non-negative if interface
 * is usable, and negative elsewhen. The negative return values
 * can be tested with constant macros defined in cti.hh
 */
int CrontabFile::operator ! () {
	if (!this) return TTCB_CRT_PROGRAM_ERROR;

	switch (status) {
		case TTCB_CRT_WRITING_IN_PROGRESS:
		case TTCB_CRT_NOTHING_WRITTEN:
			return 0;
		case TTCB_CRT_PROBLEMS:
		case TTCB_CRT_PROGRAM_ERROR:
                case TTCB_CRT_AUTHORITY_ERROR:
			return status;
		default:
			return status = TTCB_CRT_PROGRAM_ERROR;
	}
}


/*************************************************************
 * Casting method to check if an interface is usable.
 * Returns non-null when usable, and null when not.
 */
CrontabFile::operator void * () {
	return (void *)(!*this ? 0 : -1);
}


/***********************************************************
 * Output a command on a format where some characters are
 * escaped, avoiding problems when putting them in
 * crontab files. The command will also be quoted.
 * Compare decode function below.
 * returns 0 on success, and -1 on failure.
 */
static int Output_command(std::ostream& out, const char *command){
	out << "\'";
	for (; *command; command++)
		switch (*command) {
		case '\n': out << "\\n"; break;
		case '\\': out << "\\\\"; break;
		case '%' : out << "\\p"; break;
		case '\'': out << "\\q"; break;
		default: out << *command;
	}
	out << "\'\n";
	if (!out) return -1;
	return 0;
}


/**********************************************************
 * Decode a command string read from a crontab file.
 * compare output function above. The surrounding quotes
 * should be removed before this function is called.
 * Returns first argument, pointing to the now modified
 * command string.
 */
char *ttcb_crt_Decode_command(char *command) {
	char *p;
	for (p = command; *p; p++)
		if (*p == '\\')
			switch (*strshl(p)) {
			case '\\': break;
			case 'n': *p = '\n'; break;
			case 'p': *p = '%'; break;
			case 'q': *p = '\''; break;
			default: /* What?! */ break;
	}
	return command;
}


/*********************************************************
 * Output one field to crontab file.
 * Format:
 * '*' | <number> { ',' <number>}
 * Parameters: out - output stream, start - First <number>, or
 * TCANY for '*', base - tells when to do wrap-around (eg 60 for
 * minutes), offset - lowest possible value (eg 1 for day of month,
 * 0 for minute), split - how many <number>s to print.
 * The values will be distributed evenly, and first incremental step
 * will be the smallest/shortest step.
 * Returns 0 on success, and -1 on failure.
 */
static int crtf(ofstream& out, int start, int base, int offset, int split) {
	int count;
	if (start == TCANY) {
		out << " * ";
		return 0;
	}
	start -= offset; // offset will be added back a few lines later
	if (base < 1 ||
	    base > 99 ||
	    split < 1 ||
	    split > base)
		 return -1;

	out << start+offset;
	for (count = 1; count < split; count++)
		out << "," << (start + count*base/split)%base + offset;
	out << " ";
	return 0;
}


/********************************************************
 * Output one Command Request Entry to a crontab file.
 * The format has to convay the input parser (operator >>),
 * and also has to be within the crontab(5) syntax.
 * Format:
 * <minute-field> <hour-field> <day-field> <month-field>
 *	<day_of_week-field> <shell> -i <id> [-h <host>]
 *	[-y <year> [-m <month>]] -c <command>
 * <field>-syntax specified in crtf-comment
 * <month> is included to allow new year checking (see shell
 * code)
 * <command>-syntax specified in Output_command-comment.
 *
 * Compare flags with tc_shell, cti.L and cti.Y
 */
CrontabFile& CrontabFile::operator << (TAS_TC_com_entry ce) {
	if (!ce) {
		ctout.clear(ios::failbit|ctout.rdstate());
		return *this;
	}
	if (status == TTCB_CRT_NOTHING_WRITTEN)
		ctout << ' ', status = TTCB_CRT_WRITING_IN_PROGRESS; // Wake Up!
	crtf(ctout, ce.minute, 60, 0, (ce.interval == HOURLY ? ce.split : 1));
	crtf(ctout, ce.hour, 24, 0, (ce.interval == DAILY ? ce.split : 1));
	crtf(ctout, ce.day, 28, 1, (ce.interval == MONTHLY ? ce.split : 1));
	crtf(ctout, ce.month, 12, 1, (ce.interval == ANNUALLY ? ce.split : 1));
	crtf(ctout, (ce.interval == WEEKLY ? ce.split : TCANY), 7, 0, 1);
	ctout << getenv("AM_TC_SHELL_EXEC_PATH") << TC_SHELL << " -" << TTCB_CRT_ID_FLAG << " " << ce.id;
	if (ce.host)
		ctout << " -" << TTCB_CRT_HOST_FLAG << " " << ce.host;
	if (ce.interval == NONE)
		 ctout << " -" << TTCB_CRT_YEAR_FLAG << " " << ce.year <<
			  " -" << TTCB_CRT_MONTH_FLAG << " " << ce.month;
	ctout << " -" << TTCB_CRT_COMMAND_FLAG << " ";
	Output_command(ctout, ce.commandline);
	return *this;
}


/*********************************************************
 * Analyse heap values, to find (one) start value. Start value
 * is a value that can be considered non-rounded, and therefore
 * the increment to the next value, shouldn't be graeter than
 * any other incremental step. The algorithm looks for the
 * biggest gap (incremental step), also remembering its lower
 * bound value. Last it checks for wrap-around.
 * Input: heap - pointer to heap holding the values, base -
 * number of possible values. (eg 60 for minutes)
 * Returns start value on success, and -1 on failure.
static int extr(Heap *heap, int base) {
	int gap, first, out, previous, value;
	if ((out = first = previous = heap->get()) == -1)
		return -1;
	for (gap = 0; (value = heap->get()) != -1; previous = value)
		if (!gap || gap < value - previous) {
			gap = value - previous;
			out = value;
		}
	if (base + first - previous >= gap)
		out = first;
	return out;
}
 */


/**********************************************************
 * Input method. Reads one Command Request Entry from a crontab
 * file.
 * (It would be easier to use the standard TAS_TC_com_entry format, but
 * there would be a risk for inconsistence.)
 * The use of the macros is explained later.
 */
#define code(H, P) ((H ? (H->size() ? (H->size() == 1 ? 1 : 2) : 0) : 7) << 3*P)
#define icode(I, P) ((I != TCANY ? 1 : 0) << 3*P)

CrontabFile& CrontabFile::operator >> (TAS_TC_com_entry& ce) {
	int split;
	ctin.clear();

  /*ttcb_crt_yyin = &ctin;

	for (;;)
		switch (ttcb_crt_yyparse()) {
		case TTCB_CRT_OK: // Normal return

			// Fix the escape sequences
			ttcb_crt_Decode_command(command);

			/* Code the sizes of the heaps weekday ..
			 * minute and the value of year.
 			 * Code layout: 0wymdHM (octal), where
			 * w..M is: 0 - no size, 1 - single value,
			 *          2 - multiple values, 7 - error
			 * w - weekday, y - year, m - month, d - day,
			 * H - hour, M - minute.
			 * The coding uses the macros above.
			 
			switch(code(weekday, 5)|
			       icode(year, 4)|
			       code(month, 3)|
			       code(day, 2)|
			       code(hour, 1)|
			       code(minute, 0)) {
				case 0011111:
					ce = TAS_TC_com_entry(host,
						              command,
                                                              year,
						              month->get(),
						              day->get(),
					        	      hour->get(),
					         	      minute->get(),
					        	      user, NONE, 1);
					break;
				case 0002111:
				case 0001111:
					split = month->size();
					ce = TAS_TC_com_entry(host,
				 		             command,
					        	      TCANY,
					        	      month->get(),
					        	      day->get(),
					        	      hour->get(),
				         		      minute->get(),
				        		      user, ANNUALLY, split);
					break;
				case 0000211:
				case 0000111:
					split = day->size();
					ce = TAS_TC_com_entry(host,
						              command,
						              TCANY,
			        			      TCANY,
			         			      day->get(),
				        		      hour->get(),
				        		      minute->get(),
				        		      user, MONTHLY, split);
					break;
				case 0100011:
					ce = TAS_TC_com_entry(host,
						              command,
						              TCANY,
						              TCANY,
						              TCANY,
						              hour->get(),
						              minute->get(),
						              user, WEEKLY,
						              weekday->get());
					break;
				case 0000021:
				case 0000011:
					split = hour->size();
					ce = TAS_TC_com_entry(host,
						              command,
						              TCANY,
						              TCANY,
						              TCANY,
						              hour->get(),
						              minute->get(),
						              user, DAILY, split);
					break;
				case 0000002:
				case 0000001:
					split = minute->size();
					ce = TAS_TC_com_entry(host,
						              command,
						              TCANY,
						              TCANY,
						              TCANY,
						              TCANY,
						              minute->get(),
						              user, HOURLY, split);
					break;
				default:
					ce.state = TTCB_CE_BAD_INPUT_SYNTAX;
					// Dismiss the entry
					break;
			}
			*collected_line = '\0';
			ce.id = id;
			if (!ce)
				ctin.clear(ios::failbit|ctin.rdstate());
			return *this;

		case TTCB_CRT_PROBLEMS: // Error return
			if (status == TTCB_CRT_NOTHING_WRITTEN)
				 ctout << ' ',
				 status = TTCB_CRT_WRITING_IN_PROGRESS; // Wake up!
			ctout << collected_line << "\n";
			*collected_line = '\0';
			break;

		case TTCB_CRT_EOF: // End of input return
			ce.state = TTCB_CE_EMPTY;
			ctin.clear(ios::eofbit|ctin.rdstate());
			return *this;

		default:
			ce.state = TTCB_CE_PROGRAM_ERROR;
			ctin.clear(ios::badbit|ctin.rdstate());
			return *this;
	}*/
}

