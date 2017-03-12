#ifndef BLRESOURCE_H
#define BLRESOURCE_H

#include <string>
#include <memory>

using string = std::string;

namespace black {

/**
 * @brief The Resource class
 *  In game resource. All resources, classes
 * that wants to be loaded must implement it's interface.
 *
 * @author george popoff <popoff96@live.com>
 * @date 12.03.2017
 * @version 1.0 Working version
 *
 * @abstract
 */
class Resource
{
public:
    /**
     * @brief Loads resource from file with
     *  given name.
     *
     * @param file file path string
     */
    virtual void load(string file) = 0;

    virtual ~Resource() {}
};
} // end of black namespace

#endif // BLRESOURCE_H
