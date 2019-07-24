//
// Created by popof on 24.09.2018.
//

#ifndef BLACKENGINE_CONSTANTS_H
#define BLACKENGINE_CONSTANTS_H

#include <common/Config.h>
#include <common/Exported.h>

#include <string>

namespace black {

enum class Platform {
  WINDOWS,
  LINUX,
  MACOSX
};

class BLACK_EXPORTED Constants {
public:
#if defined(BLACK_PLATFORM_WINDOWS)
  static const Platform RuntimePlatform = Platform::WINDOWS;
#elif defined(BLACK_PLATFORM_LINUX)
  static const Platform RuntimePlatform = Platform::LINUX;
#elif defined(BLACK_PLATFORM_MACOSX)
  static const Platform RuntimePlatform = Platform::MACOSX;
#endif

  static constexpr const char *RuntimePlatformString = BLACK_PLATFORM;

  static constexpr bool IsDebug = true;
};

}

#endif //BLACKENGINE_CONSTANTS_H
