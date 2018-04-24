//
// Created by popof on 24.04.2018.
//

#include "FileUtils.h"

namespace black {

    std::string FileUtils::getFileExtension(const std::string &fileName) {
        auto dotPosition = fileName.find('.');

        if (dotPosition == std::string::npos) {
            return "";
        }

        return fileName.substr(dotPosition + 1, std::string::npos);
    }

    bool FileUtils::hasTrailingSlash(const std::string &fileName) {
        return fileName.back() == '/';
    }

}
