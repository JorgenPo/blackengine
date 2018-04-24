//
// Created by popof on 24.04.2018.
//

#include <vector>
#include <sstream>
#include <iterator>
#include "StringUtils.h"

namespace black {

    template<typename Out>
    void splitString(const std::string &s, char separator, Out result) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, separator)) {
            *(result++) = item;
        }
    }

    std::vector<std::string> StringUtils::split(const std::string &string, char separator) {
        std::vector<std::string> parts;
        splitString(string, separator, std::back_inserter(parts));
        return parts;
    }
}