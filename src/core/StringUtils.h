//
// Created by popof on 24.04.2018.
//

#ifndef BLACKENGINE_STRINGUTILS_H
#define BLACKENGINE_STRINGUTILS_H

#include <string>
#include <vector>

namespace black {
    /**
     * Helper methods for working with strings
     */
    class StringUtils {
        static std::vector<std::string> split(const std::string &string, char separator);
    };
}


#endif //BLACKENGINE_STRINGUTILS_H
