cmake_minimum_required(VERSION 3.5)

project(blackengine-editor LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CONAN_DISABLE_CHECK_COMPILER ON)
#include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

file(GLOB_RECURSE EDITOR_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui)

add_executable(blackengine-editor
        ${BLACKENGINE_LIBRARY_DIR}/glad/src/glad.c
        ${EDITOR_SOURCES})

target_link_libraries(blackengine-editor PRIVATE Qt5::Widgets BlackEngine)
target_include_directories(blackengine-editor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)