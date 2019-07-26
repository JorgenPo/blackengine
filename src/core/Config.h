#pragma once

/* #undef BLACK_PLATFORM_WINDOWS */
#define BLACK_PLATFORM_LINUX
/* #undef BLACK_PLATFORM_MACOSX */
#define BLACK_PLATFORM "Linux"

#define BLACK_COMPILER_CLANG
/* #undef BLACK_COMPILER_MINGW */
/* #undef BLACK_COMPILER_GNU */
/* #undef BLACK_COMPILER_INTEL */
/* #undef BLACK_COMPILER_MSVC */

namespace black::config {
constexpr int VERSION_MAJOR = 0;
constexpr int VERSION_MINOR = 1;
constexpr int VERSION_PATCH = 0;
constexpr const char *VERSION_STRING = "0.1.0";

constexpr const char *PLUGIN_PATH = "/home/popov/libs/blackengine/lib/blackengine/plugins";
}
