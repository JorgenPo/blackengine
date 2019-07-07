cmake_minimum_required(3.6)
# Detecting build system

message(INFO " Size of void is ${CMAKE_SIZEOF_VOID_P}")

if(UNIX AND APPLE)
    set(BLACK_PLATFORM_MACOSX 1)
    set(BLACK_PLATFORM "MacOS X")
elseif(WIN32)
    set(BLACK_PLATFORM_WINDOWS 1)
    set(BLACK_PLATFORM "Windows")
elseif(UNIX AND NOT APPLE)
    set(BLACK_PLATFORM_LINUX 1)
    set(BLACK_PLATFORM "Linux")
endif(UNIX AND APPLE)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(BLACK_COMPILER_CLANG 1)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if(BLACK_PLATFORM_WINDOWS)
        set(BLACK_COMPILER_MINGW 1)
    else()
        set(BLACK_COMPILER_GNU 1)
    endif(BLACK_PLATFORM_WINDOWS)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    set(BLACK_COMPILER_INTER 1)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(BLACK_COMPILER_MSVC 1)
endif()

# Set debug define for debug build type
set(CMAKE_C_FLAGS_DEBUG "-DBLACK_DEBUG")

# Platform specific sources
if (BLACK_PLATFORM_WINDOWS)
    file(GLOB PLATFORM_SOURCES "${BLACKENGINE_SOURCE_DIR}/plugins/windows/*.h" "${BLACKENGINE_SOURCE_DIR}/plugins/windows/*.cpp")
elseif(BLACK_PLATFORM_LINUX)
    file(GLOB PLATFORM_SOURCES "${BLACKENGINE_SOURCE_DIR}/plugins/linux/*.h" "${BLACKENGINE_SOURCE_DIR}/plugins/linux/*.cpp")
elseif(BLACK_PLATFORM_MACOSX)
    file(GLOB PLATFORM_SOURCES "${BLACKENGINE_SOURCE_DIR}/plugins/macos/*.h" "${BLACKENGINE_SOURCE_DIR}/plugins/macos/*.cpp")
endif(BLACK_PLATFORM_WINDOWS)