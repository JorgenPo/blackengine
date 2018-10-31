#include <utility>

//
// Created by popof on 31.10.2018.
//

#include "Paths.h"

namespace black {

    std::string Paths::GetFileExtension(std::string path) {
        auto splitVector = Strings::Split(std::move(path), ".");

        if (splitVector.size() < 2) {
            return "";
        }

        // Return the last element as an extension
        return splitVector.back();
    }
}