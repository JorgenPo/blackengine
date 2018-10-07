//
// Created by popof on 26.09.2018.
//

#ifndef BLACKENGINE_TYPES_H
#define BLACKENGINE_TYPES_H

#include <Exported.h>
#include <Config.h>

#if defined(BLACK_PLATFORM_WINDOWS)
    #include <plugins/windows/WindowsSharedLibrary.h>
#elif defined(BLACK_PLATFORM_LINUX)
    #include <plugins/linux/LinuxSharedLibrary.h>
#endif

namespace black {
#ifdef BLACK_PLATFORM_WINDOWS
    using SharedLibrary = os::WindowsSharedLibrary;
#elif defined(BLACK_PLATFORM_LINUX)
    using SharedLibrary = os::LinuxSharedLibrary;
#elif defined(BLACK_PLATFORM_MACOSX)
    using SharedLibrary = os::MacOSSharedLibrary;
#endif

    /**
     * Black engine types
     */
    class BLACK_EXPORTED Types {
    public:
    };
}

#endif //BLACKENGINE_TYPES_H
