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
/**
 *  OPSLogger Class to integrate the Opsparser code to Boost Framework
*/
#ifndef OPSLOGGER_H
#define OPSLOGGER_H

#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/inotify.h>
#include <thread>
#include <stddef.h> 
#include <unistd.h>
#include <stdio.h>      
#include <stdlib.h>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/log/core.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#define MAX_EVENTS 1024   /*Max. number of events to process at one go*/
#define LEN_NAME 16      /*Assuming that the length of the filename won't exceed 16 bytes*/
#define EVENT_SIZE (sizeof (struct inotify_event))    /*size of one event*/
#define BUF_LEN (MAX_EVENTS*(EVENT_SIZE + LEN_NAME)) /*buffer to store the data of events*/

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

typedef sinks::synchronous_sink< sinks::text_file_backend > file_sink;
static const char* log_config_directory = "/opt/ops/ops_parser/etc/";

class OPSLogger {
public:
 
/**
   * To Initializing the logging.
*/
    void init_logging();
	
/**
    * For writing in the Log Files.
*/
    void writeToLogfile(std::string str);

/**
    * OPSLogger Destructor.
*/
    ~OPSLogger(){};

    static bool isLogging;

    static OPSLogger& getInstance();

    OPSLogger(OPSLogger const&)       = delete;

    void operator=(OPSLogger const&)  = delete;

	
private:
    logging::sources::logger lg;
    unsigned long max_file_size;
    unsigned long rotation_file_size;
    bool log_enable;
    std::string parser_log_directory;
    OPSLogger(){};

/**
    * For Initializing the Logging Parameter
    * @param sink
        Object of text_file_backend to collect the properties related to log file.
*/
    void init_file_collecting(boost::shared_ptr< file_sink > sink);

/**
    * To Initializing the Parameter related to logging.
*/
    void init_parameter();

};
#endif
