//
// Created by popof on 24.09.2018.
//

#ifndef BLACKENGINE_CONSTANTS_H
#define BLACKENGINE_CONSTANTS_H

#include <Config.h>
#include <Exported.h>

#include <string>

namespace black {

    enum class Platform {
        WINDOWS,
        LINUX,
        MACOSX
    };

    class BLACK_EXPORTED Constants {
    public:
#ifdef BLACK_PLATFORM_WINDOWS
    static const Platform RuntimePlatform = Platform::WINDOWS;
#elif BLACK_PLATFORM_LINUX
    static const Platform RuntimePlatform = Platform::LINUX;
#elif BLACK_PLATFORM_MACOSX
    static const Platform RuntimePlatform = Platform::MACOSX;
#endif

    static constexpr const char *RuntimePlatformString = BLACK_PLATFORM;

    static const bool IsDebug = true;
    };

}

#endif //BLACKENGINE_CONSTANTS_H
