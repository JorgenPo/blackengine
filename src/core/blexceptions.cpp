#include "blexceptions.h"

namespace black {

BadParameterException::
BadParameterException(std::string paramName, std::string functionName)
    : m_param(paramName), m_function(functionName)
{

}

std::string BadParameterException::message() const
{
    return std::string("Bad parameter '" + m_param + "' in function '" + m_function + "'!");
}

WrongFileException::
WrongFileException(std::string file, std::string desiredFormatName)
    : m_file(file), m_desiredFormat(desiredFormatName)
{

}

std::string WrongFileException::message() const
{
    return std::string("File '" + m_file + "' does not seemed to be a valid '" + m_desiredFormat + "' file!");
}

std::__cxx11::string InternalException::message() const
{
    return std::string("Something goes wrong. Check the code that has been thrown that exception.");
}

} // end of black namespace
