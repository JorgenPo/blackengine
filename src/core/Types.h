//
// Created by popof on 26.09.2018.
//

#ifndef BLACKENGINE_TYPES_H
#define BLACKENGINE_TYPES_H

#include <Exported.h>
#include <Config.h>
#include <plugins/windows/WindowsSharedLibrary.h>

namespace black {
#ifdef BLACK_PLATFORM_WINDOWS
    using SharedLibrary = os::WindowsSharedLibrary;
#endif

    /**
     * Black engine types
     */
    class BLACK_EXPORTED Types {
    public:
    };
}

#endif //BLACKENGINE_TYPES_H
