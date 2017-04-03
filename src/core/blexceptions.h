#ifndef BLEXCEPTIONS_H
#define BLEXCEPTIONS_H

#include <string>

namespace black {

/**
 * @brief The AbstractException class
 * Base class for all black::exceptions.
 * Only one pure virtual message() method.
 *
 * @author george popoff 2.04.2017
 * @version 1.0
 */
class AbstractException
{
public:
    virtual std::string message() const throw() = 0;
};

/**
 * @brief The BadParameterException class
 * This exception is saying that you are
 * trying to pass a parameter to a function that
 * has not expected here.
 *
 * @author george popoff 2.04.2017
 * @version 1.0
 */
class BadParameterException : public AbstractException
{
public:
    BadParameterException(std::string paramName, std::string functionName);

    // AbstractException interface
    virtual std::string message() const override;

private:
    std::string m_param;
    std::string m_function;
};

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
    virtual std::string message() const override;

private:
    std::string m_file;
    std::string m_desiredFormat;
};

/**
 * @brief The InternalException class
 * This exception is saying that there happened
 * an internal exception. You need to check
 * the code that has been thrown that exception.
 *
 * @author george popoff 2.04.2017
 * @version 1.0
 */
class InternalException : public AbstractException
{
public:
    // AbstractException interface
    virtual std::string message() const override;
};


} // end of black namespace

#endif // BLEXCEPTIONS_H
