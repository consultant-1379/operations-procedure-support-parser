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
#include "OPSLogger.H"
#include <sys/stat.h>
#include <sys/types.h>
#include <boost/filesystem.hpp>

namespace patch {
    template < typename T > std::string to_string( const T& n ) {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

void OPSLogger::writeToLogfile(std::string str) {
        BOOST_LOG(lg) << str;
}

void OPSLogger::init_parameter() {
    std::string log_directory(log_config_directory);
    std::string log_config_file_name = log_directory+"logging.properties";
    using boost::property_tree::ptree;
    ptree pt;

    boost::property_tree::ini_parser::read_ini( log_config_file_name, pt );
    std::string str1 = pt.get<std::string>("log_enable");
    std::string str2 = pt.get<std::string>("max_file_size");
    std::string str3 = pt.get<std::string>("parser_log_directory");
    std::string str4 = pt.get<std::string>("rotation_file_size");
    str1.erase(remove(str1.begin(), str1.end(), ' '), str1.end());
    str2.erase(remove(str2.begin(), str2.end(), ' '), str2.end());
    str3.erase(remove(str3.begin(), str3.end(), ' '), str3.end());
    str4.erase(remove(str4.begin(), str4.end(), ' '), str4.end());
    if(str1=="true") {
        log_enable = true;
    }
    else if(str1=="false") {
        log_enable = false;
    }
    max_file_size  = boost::lexical_cast<unsigned long>(str2);
    rotation_file_size  = boost::lexical_cast<unsigned long>(str4);

    std::string log_path  = getenv("HOME");
    std::string log_host  = getenv("HOSTNAME");
    str3 = log_host + "_" + str3;

    parser_log_directory = log_path + "/" + str3;
    boost::filesystem::create_directory(parser_log_directory);
    chmod(parser_log_directory.c_str() , 0777);
}

void OPSLogger::init_file_collecting(boost::shared_ptr< file_sink > sink) {
    sink->locked_backend()->set_file_collector (sinks::file::make_collector (
    keywords::target = parser_log_directory,          /*< the target directory >*/
    keywords::max_size = max_file_size
    ));
}

 OPSLogger& OPSLogger::getInstance() {
    static OPSLogger myLogger;
    return myLogger;
   }

void OPSLogger::init_logging() {
    init_parameter();
    isLogging = log_enable;
    logging::core::get()->set_logging_enabled(true);

    // Creating a Thread to look into build.properties File
    //std::thread file_thread(&OPSLogger::notice,this,&log_check);
    //file_thread.detach();

    long processID = (long)getpid();
    std::string log_file = parser_log_directory+"/ops_parser"+patch::to_string(processID);

    // Create a text file sink
    boost::shared_ptr<file_sink> sink (new file_sink (
        keywords::file_name = log_file + "_%N.log",
        keywords::rotation_size = rotation_file_size
    ));

    init_file_collecting(sink);

    // Upon restart, scan the directory for files matching the file_name pattern
    sink->locked_backend()->scan_for_files();

    //Setting the logging Format.
    sink->set_formatter (
        expr::stream<< expr::attr< unsigned int>("RecordID")<<"  "<<expr::attr< boost::posix_time::ptime>("TimeStamp")<<"  "<< expr::smessage
    );
    sink->locked_backend()->auto_flush(true);

    // Add the sink to the core
    logging::core::get()->add_sink(sink);

    // And also add some attributes
    logging::core::get()->add_global_attribute("TimeStamp", boost::log::attributes::local_clock());
    logging::core::get()->add_global_attribute("RecordID", boost::log::attributes::counter< unsigned int >());
}
bool OPSLogger::isLogging = false;
