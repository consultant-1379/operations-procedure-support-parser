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
    * .SECTION DESCRIPTION -> Implement of Trace macros
    * To Enable the Trace Macros Present in OPSParser Code
*/

#ifndef TRACE_H
#define TRACE_H

#include <iostream>
#include <fstream>
#include "OPSLogger.H"
#include <strstream>

namespace std {
class strstream;
class ostrstream;
}

#define TRACE_IN( trbl, method, param_list ) {                                                           \
    if (OPSLogger::isLogging) {    \
    std::ostrstream oss;         \
    oss << trbl <<": "<<" -> "<<#method<<  " (" << param_list << ")" << std::ends;  \
    char *str = oss.str();   \
    OPSLogger::getInstance().writeToLogfile(str);  \
    delete [] str;	 \
    }	\
}

#define TRACE_ERROR( trbl, method, free_text ) {                                                          \
    std::ostrstream oss;         \
    oss << trbl <<": "<<" ERR "<<#method<<  " (" << free_text << ")" << std::ends;  \
    char *str = oss.str();   \
    OPSLogger::getInstance().writeToLogfile(str);  \
    delete [] str;	 \
}

#define TRACE_FLOW( trbl, method, free_text ) {                                                   \
    if (OPSLogger::isLogging) {   \
        std::ostrstream oss;   \
        oss << trbl <<": "<<" -> "<<#method<<  " (" << free_text << ")" << std::ends;      \
        char *str = oss.str();  \
        OPSLogger::getInstance().writeToLogfile(str);\
        delete [] str;  \
    }    \
}

#define TRACE_OUT( trbl, method, out_param ) {                                                          \
    if (OPSLogger::isLogging) {    \
        std::ostrstream oss;   \
        oss << trbl <<": "<<" <- "<<#method<<  " (" << out_param << ")" << std::ends;    \    
        char *str = oss.str();               \
        OPSLogger::getInstance().writeToLogfile(str);\
        delete [] str;                                              \
    }    \
}

#define TRACE_RETURN( trbl, method, result ) {                                                          \
    if (OPSLogger::isLogging) {    \
        std::ostrstream oss;    \
        oss << trbl <<": "<<" <- "<<#method<<  " = " << result << std::ends;          \   
        char *str = oss.str();                             \
        OPSLogger::getInstance().writeToLogfile(str);\
        delete [] str;                                              \
    }    \
}

#define TRACE_INFO( trbl, method, free_text ) {                                                          \
    std::ostrstream oss;         \
    oss << trbl <<": "<<" INFO "<<#method<<  " (" << free_text << ")" << std::ends;  \
    char *str = oss.str();   \
    OPSLogger::getInstance().writeToLogfile(str);  \
    delete [] str;   \
}
#endif
