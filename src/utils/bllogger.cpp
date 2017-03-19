#include "bllogger.h"

#include <iostream>

namespace black {

Logger::Logger()
    : m_logStream(),
    m_debugStream(),
    m_errorStream(),
    m_infoStream()
{
    m_logStream = &std::cout;
    m_debugStream = &std::cout;
    m_errorStream = &std::cout;
    m_infoStream = &std::cout;
}

Logger::~Logger()
{
    // Close streams
}

void Logger::log(std::string str) const
{
    *m_logStream << str << '\n';
}

void Logger::debug(std::string str) const
{
    if ( Constants::APPLICATION_MODE == Constants::APPLICATION_DEVELOP ||
         Constants::APPLICATION_MODE == Constants::APPLICATION_TESTING ) {
        *m_debugStream << str << '\n';
    }
}

void Logger::error(std::string str) const
{
    *m_errorStream << str << '\n';
}

void Logger::info(std::string str) const
{
    *m_infoStream << str << '\n';
}

}
