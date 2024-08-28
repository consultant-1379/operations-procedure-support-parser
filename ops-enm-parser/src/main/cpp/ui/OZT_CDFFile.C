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
#include <strstream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include "OZT_CDFDef.H"
#include "OZT_CDFFile.H"


//*****************************************************************************

// trace
#include <trace.H>
static std::string trace ="OZT_CDFFile";


//*****************************************************************************


// file identifiers
static const char* fileId = "%File_what%";
static const char* rcsid = "@(#)rcsid:$Id: OZT_CDFFile.C,v 21.0 1996/08/23 12:46:59 ehsgrap Rel $";


//*****************************************************************************
OZT_CDFFile::OZT_CDFFile(RWCString dir_path,
                         RWCString name,
                         OZT_CDFFile** file_array,
                         int num_files)
{
    TRACE_IN(trace, OZT_CDFFile, dir_path.data() << ", " << name.data());

    char pathname[MAXPATHLEN+1];
    int done = FALSE;
    int name_number = 1;
    int i;
    RWFile* a_file;
    RWCString a_name;
    std::strstream* ss;

    filename = name;                //Use given name
    if (name.first('/') == 0)
    {
        i = name.last('/');
	directory = (i==0)? (RWCString)"/" : (RWCString)name(0, i);
        filename = name(i+1, (name.length()-i-1));
    }

    else if (dir_path != "")
        directory = dir_path;           //Use given directory

    else
    { 
        getcwd(pathname, MAXPATHLEN+1);
        if (pathname == NULL)
        {
             directory = "";
        }
        else
        {
            directory = pathname;		//Use working directory 
        }
    }

    if (name == "")
//-------------------------------------------------------------------
// Choose a filename
// look for the file
// if it exists, try again with a new name
//------------------------------------------------------------------- 
    {
        while (done == FALSE)
        {
            if ((ss = new std::strstream())==0)
            { 
               std::cerr<< "Out of Memory"<<std::endl;
               exit(-1);
            }
            *ss << UNNAMED_FILE << name_number++ << std::ends;
            a_name = ss->str();
            delete [] ss->str();
            delete ss;
            if ((a_file = new RWFile(a_name.data(), "r")) == 0)
            { 
               std::cerr<< "Out of Memory"<<std::endl;
               exit(-1);
            }
            if (a_file->isValid() == FALSE)
            {
                done = TRUE;
                for (i=0; i<num_files; i++)
                    if (file_array[i]->get_name() == a_name)
                         done = FALSE;
            }
            delete a_file;
        }
        filename = a_name;
    }

    // Clear all tags and breakpoints
    clearAllBrkPts();
    clearAllTags();

    // Set the time_stamp to really old
    time_stamp = 0;

    TRACE_OUT(trace, OZT_CDFFile, directory << "," << name);
}  


//*****************************************************************************
OZT_CDFFile::~OZT_CDFFile()
{
}  


//*****************************************************************************
int OZT_CDFFile::get_breakpoint(int first_line, int num_lines)
{
    int lastLine = (MAX_LINES < first_line + num_lines)? 
                       MAX_LINES : first_line + num_lines;

    for (int line = first_line; line < lastLine; line++)
    {
        if (breakpoint_array[line])
            return TRUE;
    }
    return FALSE;
}  


//*****************************************************************************

RWCString OZT_CDFFile::get_directory(void)
{
    TRACE_IN(trace, get_directory, "");

    TRACE_RETURN(trace, get_directory, directory.data());
    return directory;
}  

//*****************************************************************************

RWCString OZT_CDFFile::get_full_name(void)
{
  TRACE_IN(trace, get_full_name, directory << "," << filename);

    RWCString full_name;

    if (directory == "")
      full_name = filename;
    else if(directory == "/")
      full_name = directory + filename;
    else
      full_name = directory + (RWCString)"/" + filename;

    TRACE_RETURN(trace, get_full_name, full_name.data());
    return full_name;
}  

//*****************************************************************************

RWCString OZT_CDFFile::get_name(void)
{
    TRACE_IN(trace, get_name, "");
    TRACE_RETURN(trace, get_name, filename.data());
    return filename;
}  

//*****************************************************************************

int OZT_CDFFile::get_next_tag(int line_num)
{
    TRACE_IN(trace, get_next_tag, "");

    char c;
    int line = line_num;
    int done = FALSE;
    int num_lines = 0;
    RWFile f(get_full_name().data(), "r");
    
    if(f.isValid() == FALSE)
    {
	   // File did not open OK.
	   
       TRACE_RETURN(trace, get_next_tag, "-1");
       return -1;
    }
    

    while (f.Read(c) == TRUE)
        if (c == '\n')
            num_lines++;

    while ((line <= num_lines) && (done == FALSE))
    {
        if (tag_array[line] == TRUE)
            done = TRUE;
        else
            line ++;
    }
       
    if (done == TRUE)
    {
       TRACE_RETURN(trace, get_next_tag, line);
       return line;
    }
    else
    {
       TRACE_RETURN(trace, get_next_tag, "-1");
       return -1;
    }
}  

//*****************************************************************************
int OZT_CDFFile::get_tag(int first_line, int num_lines)
{
    int value = FALSE;

    for (int line = first_line; line < (first_line + num_lines); line++)
    {
    if (line < MAX_LINES)
        if (tag_array[line] == TRUE)
            value = TRUE;
    }
    return value;
}  

//*****************************************************************************
int OZT_CDFFile::is_changed(void)
{
   TRACE_IN(trace, is_changed, "");

   int value;
   FILE *fp;
   struct stat  tmp_stat_rec;
   struct tm *t;
   unsigned long modify_time;

   // Return FALSE if cannot get the stats
   if (stat(get_full_name(), &tmp_stat_rec) == -1)
   {
       TRACE_RETURN(trace, set_time_stamp, "FALSE - can't stat");
       return FALSE;
   }


   // Compare the modify time with the time_stamp
   t = gmtime(&tmp_stat_rec.st_mtime);
   modify_time = (t->tm_year * 60 * 60 * 24 * 365) +
                 (t->tm_yday * 60 * 60 * 24) +
                 (t->tm_hour * 60 * 60) +
                 (t->tm_min  * 60) +
                  t->tm_sec;

   if (modify_time > time_stamp)
       value = TRUE;
   else
       value = FALSE;

   TRACE_RETURN(trace, is_changed, value << " (t=" << modify_time << ")" );

   return value;
}  

//*****************************************************************************
void OZT_CDFFile::set_breakpoint(int line_num, int is_breakpoint)
{
    if (line_num < MAX_LINES)
        breakpoint_array[line_num] = (char)is_breakpoint;
}  

//*****************************************************************************
void OZT_CDFFile::set_tag(int line_num, int is_tag)
{
    if (line_num < MAX_LINES)
        tag_array[line_num] = (char)is_tag;
}  


//*****************************************************************************
void OZT_CDFFile::set_breakpoints(const char data[MAX_LINES])
{
    memcpy((char *)breakpoint_array, (char *)data, MAX_LINES);
}

//*****************************************************************************
void OZT_CDFFile::copy_breakpoints(char data[MAX_LINES])
{
    memcpy((char *)data, (char *)breakpoint_array, MAX_LINES);
}

//*****************************************************************************
void OZT_CDFFile::copy_tags(char data[MAX_LINES])
{
    memcpy((char *)data, (char *)tag_array, MAX_LINES);
}

//*****************************************************************************
void OZT_CDFFile::set_tags(const char data[MAX_LINES])
{
    memcpy((char *)tag_array, (char *)data, MAX_LINES);
}

//*****************************************************************************
void OZT_CDFFile::clearAllBrkPts(void)
{
    memset((char*)breakpoint_array, 0, MAX_LINES);
}

//*****************************************************************************
void OZT_CDFFile::clearAllTags(void)
{
    memset((char*)tag_array, 0, MAX_LINES);
}

//*****************************************************************************
void OZT_CDFFile::set_name(RWCString name)
{
    TRACE_IN(trace, set_name, name.data());

    if (name[(unsigned)0] == '/')
    {
        int i = name.last('/');
        directory = name(0,i);
        filename = name(i+1,(name.length()-i-1));
    }
    else
    {
        char pathname[MAXPATHLEN+1];
        getcwd(pathname, MAXPATHLEN+1);
        if (pathname == NULL)
        {
            std::cerr << "CDF ERROR: could not get current directory" << std::endl;
            directory = "";
        }
        else
        {
            directory = pathname;		//Use working directory 
        }
        filename = name;
    }

    TRACE_OUT(trace, set_name, "");
}  

//*****************************************************************************
void OZT_CDFFile::set_time_stamp(void)
{

   TRACE_IN(trace, set_time_stamp, "");
   struct stat  tmp_stat_rec;
   struct tm *t;

   // Just return if cannot get the stats
   if (stat(get_full_name(), &tmp_stat_rec) == -1)
   {
       TRACE_OUT(trace, set_time_stamp, "can't stat");
       return;
   }

   t = gmtime(&tmp_stat_rec.st_mtime);
   time_stamp = (t->tm_year * 60 * 60 * 24 * 365) +
                (t->tm_yday * 60 * 60 * 24) +
                (t->tm_hour * 60 * 60) +
                (t->tm_min  * 60) +
                 t->tm_sec;

    TRACE_OUT(trace, set_time_stamp, "t=" << time_stamp);
}
