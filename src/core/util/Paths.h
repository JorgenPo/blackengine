//
// Created by popof on 31.10.2018.
//

#ifndef BLACKENGINE_PATHS_H
#define BLACKENGINE_PATHS_H

#include "Strings.h"
#include <Exported.h>
#include <string>

namespace black {

    /**
     * Helper methods for working with paths and file names
     */
    class BLACK_EXPORTED Paths {
    public:
        /**
         * Return a file extension without a dot.
         *
         * @param path Path to the file
         *
         * @return File extension
         */
        static std::string GetFileExtension(std::string path);

        /**
         * Check file existing
         *
         * @param path Path to the file
         *
         * @return Is the file exist
         */
        static bool IsFileExist(std::string path);
    };

}


#endif //BLACKENGINE_PATHS_H
