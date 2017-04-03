#ifndef BLLOGGER_H
#define BLLOGGER_H

#include "blconstants.h"

#include <ostream>

namespace black {

/**
 * Static class for logging
 *
 * @brief The Logger class
 *
 * @version 1.1 02.04.2017
 *
 * @author george popoff <popoff96@live.com>
 */
class Logger {

private:
    Logger();
    ~Logger();

public:
    /**
     * @brief Returns appropriate stream object
     *  Enchanced singleton...
     *
     * @param type String name of desired log type
     * Defaults to debug!
     *
     * @return ostream
     */
    static std::ostream& getInstance(std::string type = "debug") {
        static Logger logger;

        if ( type == "debug" ) {
            *logger.m_debugStream << std::endl;
            return *logger.m_debugStream;
        } else if ( type == "error" ) {
            *logger.m_errorStream << std::endl;
            return *logger.m_errorStream;
        } else if ( type == "info" ) {
            return *logger.m_infoStream << std::endl;
        } else {
            return *logger.m_logStream << std::endl;
        }
    }
    /**
     * @brief Write log in a file or
     * console.
     */
    void log(std::string str) const;

    /**
     * @brief Write debug information
     */
    void debug(std::string str) const;

    /**
     * @brief Write error information
     */
    void error(std::string str) const;


    /**
     * @brief Write info information
     */
    void info(std::string str) const;

    void setLogStream(std::ostream* stream)   {  m_logStream = stream; }
    void setDebugStream(std::ostream* stream) {  m_debugStream = stream; }
    void setErrorStream(std::ostream* stream) {  m_errorStream = stream; }
    void setInfoStream(std::ostream* stream)  {  m_logStream = stream; }

private:
    std::ostream* m_logStream;
    std::ostream* m_debugStream;
    std::ostream* m_errorStream;
    std::ostream* m_infoStream;

};

} // end of black namespace
#endif // BLLOGGER_H
