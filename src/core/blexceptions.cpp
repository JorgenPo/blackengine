#include "blexceptions.h"

namespace black {

/* BAD PARAMETER */
BadParameterException::
BadParameterException(std::string paramName, std::string functionName)
    : m_param(paramName), m_function(functionName)
{

}

std::string BadParameterException::message() const throw()
{
    return std::string("Bad parameter '" + m_param + "' in function '" + m_function + "'!");
}
/* BAD PARAMETER ENDS */

/* INTERNAL */
std::__cxx11::string InternalException::message() const throw()
{
    return std::string("Something goes wrong. Check the code that has been thrown that exception.");
}
/* INTERNAL ENDS */

} // end of black namespace
