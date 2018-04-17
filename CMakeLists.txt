cmake_minimum_required(VERSION 3.10)
project(BlackEngine)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${BUILD_DIR}/)

#option(WINDOW_WITH_ALL "Include support of all window implementations" OFF)
#option(WINDOW_WITH_GLFW "Include GLFW window implementation support" ON)
#option(WINDOW_WITH_WX "Include wxWidgets window implementation support" OFF)

# Run initializing scripts
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

## Check platform
include(Platform)

# Load libraries
include(Libraries)

message(STATUS "Using libraries: ${Libraries_LIBRARIES}")
message(STATUS "Using libraries: ${Libraries_INCLUDE_PATH}")

# Config
CONFIGURE_FILE(
        ${CMAKE_SOURCE_DIR}/src/config/config.h.in
        ${CMAKE_SOURCE_DIR}/src/config/config.h
)

# Common sources
file(GLOB COMMON_SOURCES
        "src/core/*.h"
        "src/core/ui/*.h"

        "src/core/*.cpp"
        "src/core/ui/*.cpp"
        )

# Platform specific sources
if (BLACK_PLATFORM_WINDOWS)
    file(GLOB PLATFORM_SOURCES "src/core/os/windows/*.h" "src/core/os/windows/*.cpp")
elseif(BLACK_PLATFORM_LINUX)
    file(GLOB PLATFORM_SOURCES "src/core/os/macos/*.h" "src/core/os/macos/*.cpp")
elseif(BLACK_PLATFORM_MACOSX)
    file(GLOB PLATFORM_SOURCES "src/core/os/linux/*.h" "src/core/os/linux/*.cpp")
endif(BLACK_PLATFORM_WINDOWS)

# Join all sources
set(SOURCES ${COMMON_SOURCES} ${PLATFORM_SOURCES})
set(INCLUDE_DIRECTORIES src/ ${Libraries_INCLUDE_PATH})

add_library(BlackEngine SHARED ${SOURCES})

target_link_libraries(BlackEngine PUBLIC ${Libraries_LIBRARIES})

# Remove lib prefix
set_target_properties(BlackEngine PROPERTIES PREFIX "")

# Include directories for BlackEngine and for all subprojects
include_directories(${INCLUDE_DIRECTORIES})

# Install headers and library
install(TARGETS BlackEngine DESTINATION ${BUILD_DIR}/)
install(TARGETS BlackEngine DESTINATION ${BUILD_DIR}/examples)
install(DIRECTORY src/core/ DESTINATION ${BUILD_DIR}/include/BlackEngine
        FILES_MATCHING PATTERN "*.h")

# Need to build from ide
install(TARGETS BlackEngine DESTINATION ${CMAKE_BINARY_DIR}/examples/SimpleApplication/)

# Build examples
add_subdirectory(examples/SimpleApplication)

# Add core plugin
add_subdirectory(plugins/core)