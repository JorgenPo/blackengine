cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME BlackEngine)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Name of the main target to use in sub projects
set(BLACKENGINE_TARGET ${PROJECT_NAME})
set(BLACKENGINE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/core)
set(BLACKENGINE_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/libs)

# Link with appropriate libraries
# LINKLIBS_LIBRARIES, LINKLIBS_SOURCES and LINKLIBS_INCLUDE_DIRS
include(Libraries)

include(Functions)

include_directories(${BLACKENGINE_SOURCE_DIR})
include_directories(${BLACKENGINE_LIBRARY_DIR}/glad/include ${BLACKENGINE_LIBRARY_DIR})
include_directories(${LINKLIBS_INCLUDE_DIRS})

include(Platform)

file(GLOB_RECURSE SOURCES "${BLACKENGINE_SOURCE_DIR}/*.h" "${BLACKENGINE_SOURCE_DIR}/*.cpp")

list(FILTER SOURCES EXCLUDE REGEX "(.*)windows(.*)")
list(FILTER SOURCES EXCLUDE REGEX "(.*)linux(.*)")
list(FILTER SOURCES EXCLUDE REGEX "(.*)macos(.*)")

set(SOURCES ${SOURCES} ${PLATFORM_SOURCES} ${LINKLIBS_SOURCES} src/core/util/ShaderManager.cpp src/core/util/ShaderManager.h src/core/components/LightComponent.cpp src/core/components/LightComponent.h src/core/RayCaster.cpp src/core/RayCaster.h)

message(INFO " Linking with libs: ${LINKLIBS_LIBRARIES}")
add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LINKLIBS_LIBRARIES})

# Examples
add_subdirectory(examples)

# Plugins
add_subdirectory(src/plugins)

# Set up main target
include(SetMainTargetSettings)

# Config
CONFIGURE_FILE(
        ${CMAKE_SOURCE_DIR}/src/config/Config.h.in
        ${BLACKENGINE_SOURCE_DIR}/Config.h
)

message(INFO " Platform is ${BLACK_PLATFORM}")
message(INFO " Installation path is: " ${CMAKE_INSTALL_PREFIX})

# Install main target
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})