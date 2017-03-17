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
 * @version 1.0 First version
 *
 * @author george popoff <popoff96@live.com>
 * @date 17.03.2017
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
            return *logger.m_debugStream;
        } else if ( type == "error" ) {
            return *logger.m_errorStream;
        } else if ( type == "info" ) {
            return *logger.m_infoStream;
        } else {
            return *logger.m_logStream;
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
     * @brief Write error information
     */
    void test(std::string str) const;

    /**
     * @brief Write info information
     */
    void info() const;

    void setLogStream(std::ostream* stream)   {  m_logStream = stream; }
    void setDebugStream(std::ostream* stream) {  m_debugStream = stream; }
    void setErrorStream(std::ostream* stream) {  m_errorStream = stream; }
    void setInfoStream(std::ostream* stream)  {  m_logStream = stream; }

private:
    static std::ostream* m_logStream;
    static std::ostream* m_debugStream;
    static std::ostream* m_errorStream;
    static std::ostream* m_infoStream;

};

} // end of black namespace
#endif // BLLOGGER_H
