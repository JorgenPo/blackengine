cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME BlackEngine)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Name of the main target to use in sub projects
set(BLACKENGINE_TARGET ${PROJECT_NAME})
set(BLACKENGINE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/core)
set(BLACKENGINE_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/src/libs)

file(GLOB SOURCES "${BLACKENGINE_SOURCE_DIR}/*.h" "${BLACKENGINE_SOURCE_DIR}/*.cpp"
        "${BLACKENGINE_SOURCE_DIR}/exceptions/*.h" "${BLACKENGINE_SOURCE_DIR}/exceptions/*.cpp"
        "${BLACKENGINE_SOURCE_DIR}/log/*.h" "${BLACKENGINE_SOURCE_DIR}/log/*.cpp"
        "${BLACKENGINE_SOURCE_DIR}/plugins/*.h" "${BLACKENGINE_SOURCE_DIR}/plugins/*.cpp"
        "${BLACKENGINE_SOURCE_DIR}/application/*.h" "${BLACKENGINE_SOURCE_DIR}/application/*.cpp"
        "${BLACKENGINE_SOURCE_DIR}/util/*.h" "${BLACKENGINE_SOURCE_DIR}/util/*.cpp"
        "${BLACKENGINE_SOURCE_DIR}/shader/*.h" "${BLACKENGINE_SOURCE_DIR}/shader/*.cpp"
        "${BLACKENGINE_SOURCE_DIR}/performance/*.h" "${BLACKENGINE_SOURCE_DIR}/performance/*.cpp"
        "${BLACKENGINE_SOURCE_DIR}/render/*.h" "${BLACKENGINE_SOURCE_DIR}/render/*.cpp")

# Link with appropriate libraries
# LINKLIBS_LIBRARIES, LINKLIBS_SOURCES and LINKLIBS_INCLUDE_DIRS
include(Libraries)

include_directories(${BLACKENGINE_SOURCE_DIR})
include_directories(${BLACKENGINE_LIBRARY_DIR})
include_directories(${LINKLIBS_INCLUDE_DIRS})

include(Platform)

message(INFO " Linking with libs: ${LINKLIBS_LIBRARIES}")
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${PLATFORM_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LINKLIBS_LIBRARIES})

# Examples
add_subdirectory(src/examples)

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