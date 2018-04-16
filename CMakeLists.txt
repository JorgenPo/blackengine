cmake_minimum_required(VERSION 3.10)
project(BlackEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${BUILD_DIR}/)

option(WINDOW_WITH_ALL "Include support of all window implementations" OFF)
option(WINDOW_WITH_GLFW "Include GLFW window implementation support" ON)
option(WINDOW_WITH_WX "Include wxWidgets window implementation support" OFF)

file(GLOB SOURCES
        "src/core/*.h"
        "src/ui/*.h"
        "src/plugin/*.h"

        "src/core/*.cpp"
        "src/ui/*.cpp"
        "src/plugin/*.cpp"
        )

add_library(BlackEngine SHARED ${SOURCES})

# Include directories for BlackEngine and for all subprojects
include_directories(src)

# Install headers and library
install(TARGETS BlackEngine DESTINATION ${BUILD_DIR}/)
install(DIRECTORY src/core/ DESTINATION ${BUILD_DIR}/include/BlackEngine)

# Need to build from ide
install(TARGETS BlackEngine DESTINATION ${CMAKE_BINARY_DIR}/examples/SimpleApplication/)

# Build examples
add_subdirectory(examples/SimpleApplication)

