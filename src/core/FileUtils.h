//
// Created by popof on 24.04.2018.
//

#ifndef BLACKENGINE_FILEUTILS_H
#define BLACKENGINE_FILEUTILS_H

#include <string>

namespace black {
    /**
     * Useful helper function to handle different
     * file names and paths
     */
    class FileUtils {
    public:
        static std::string getFileExtension(const std::string &fileName);
        static bool hasTrailingSlash(const std::string &fileName);
    };
}


#endif //BLACKENGINE_FILEUTILS_H
