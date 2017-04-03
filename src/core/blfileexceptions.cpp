#include "blfileexceptions.h"

namespace black {

/* WRONG FILE */
WrongFileException::
WrongFileException(std::string file, std::string desiredFormatName)
    : m_file(file), m_desiredFormat(desiredFormatName)
{

}

std::string WrongFileException::message() const throw()
{
    return std::string("File '" + m_file + "' does not seemed to be a valid '" + m_desiredFormat + "' file!");
}
/* WRONG FILE ENDS */

/* BAD FILE */
NoSuchFileException::NoSuchFileException(std::__cxx11::string file)
    : m_file(file)
{

}

std::__cxx11::string NoSuchFileException::message() const throw()
{
    return std::string("Can't open a file '" + m_file + "'. Check permissions or existense of the file.");
}
/* BAD FILE ENDS */

/* EMPTY FILE */
EmptyFileException::EmptyFileException(std::__cxx11::string file)
    : m_file(file)
{

}

std::__cxx11::string EmptyFileException::message() const throw()
{
    return std::string("'" + m_file + "'" + " seemed to be an empty file!");
}
/* EMPTY FILE ENDS */

/* PARSE */
ParseException::ParseException(std::__cxx11::string file, std::__cxx11::string reason)
    : m_file(file), m_reason(reason)
{

}

std::__cxx11::string ParseException::message() const throw()
{
    return std::string("Failed to parse '" + m_file + "': " + m_reason);
}
/* PARSE ENDS */
} // end of black namespace
