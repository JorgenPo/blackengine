#ifndef BLFILEEXCEPTIONS_H
#define BLFILEEXCEPTIONS_H

#include <blexceptions.h>

namespace black {

/**
 * @brief The WrongFileException class
 * This exception is saying that a file seemed to
 * have a wrong format.
 *
 * @author george popoff 2.04.2017
 * @version 1.0
 */
class WrongFileException : public AbstractException
{
public:
    WrongFileException(std::string file, std::string desiredFormatName);

    // AbstractException interface
    virtual std::string message() const throw() override;

private:
    std::string m_file;
    std::string m_desiredFormat;
};

/**
 * @brief The WrongFileException class
 * This exception is saying that a file does not
 * exist or haven't rigth permissions
 *
 * @author george popoff 2.04.2017
 * @version 1.0
 */
class NoSuchFileException : public AbstractException
{
public:
    NoSuchFileException(std::string file);

    // AbstractException interface
    virtual std::string message() const throw() override;

private:
    std::string m_file;
};

/**
 * @brief The WrongFileException class
 * This exception is saying that a file is empty.
 *
 * @author george popoff 2.04.2017
 * @version 1.0
 */
class EmptyFileException: public AbstractException
{
public:
    EmptyFileException(std::string file);

    // AbstractException interface
    virtual std::string message() const throw() override;

private:
    std::string m_file;
};

/**
 * @brief The ParseException class
 * This exception is saying that a file parsing
 * has been failed.
 *
 * @author george popoff 2.04.2017
 * @version 1.0
 */
class ParseException: public AbstractException
{
public:
    ParseException(std::string file, std::string reason);

    // AbstractException interface
    virtual std::string message() const throw() override;

private:
    std::string m_file;
    std::string m_reason;
};

} // end of black namespace
#endif // BLFILEEXCEPTIONS_H
