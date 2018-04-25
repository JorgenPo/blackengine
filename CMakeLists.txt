cmake_minimum_required(VERSION 3.10)
project(BlackEngine)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_INSTALL_PREFIX ${BUILD_DIR}/)

message(STATUS "Install Directory: ${CMAKE_INSTALL_PREFIX}")

# Run initializing scripts
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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
        "src/core/scene/*.h"
        "src/core/render/*.h"
        "src/core/events/*.h"
        "src/core/components/*.h"
        "src/core/resources/*.h"

        "src/core/*.cpp"
        "src/core/ui/*.cpp"
        "src/core/scene/*.cpp"
        "src/core/render/*.cpp"
        "src/core/events/*.cpp"
        "src/core/components/*.cpp"
        "src/core/resources/*.cpp"

        "3dparty/logging/easylogging++.cc"
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
set(INCLUDE_DIRECTORIES src/ 3dparty/ ${Libraries_INCLUDE_PATH})

add_library(BlackEngine SHARED ${SOURCES})

target_link_libraries(BlackEngine PUBLIC ${Libraries_LIBRARIES})

# Remove lib prefix
set_target_properties(BlackEngine PROPERTIES PREFIX "")

# Include directories for BlackEngine and for all subprojects
include_directories(${INCLUDE_DIRECTORIES})

# Install headers and library
install(TARGETS BlackEngine DESTINATION /)
install(TARGETS BlackEngine DESTINATION examples/)
install(DIRECTORY src/core/ DESTINATION include/BlackEngine/
        FILES_MATCHING PATTERN "*.h")

# Build examples
add_subdirectory(examples/SimpleApplication)

# PLUGINS
## Gl Renderer Plugin
add_subdirectory(plugins/glrenderer)

# Add core plugin
add_subdirectory(plugins/core)