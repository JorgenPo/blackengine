cmake_minimum_required(VERSION 3.10)
project(BlackEngine2018)

set(CMAKE_CXX_STANDARD 17)

option(WINDOW_WITH_ALL "Include support of all window implementations" OFF)
option(WINDOW_WITH_GLFW "Include GLFW window implementation support" ON)
option(WINDOW_WITH_WX "Include wxWidgets window implementation support" OFF)

include_directories(src)

file(GLOB SOURCES
        "src/core/*.h"
        "src/ui/*.h"
        "src/plugin/*.h"

        "src/core/*.cpp"
        "src/ui/*.cpp"
        "src/plugin/*.cpp"
        )

add_library(BlackEngine2018 SHARED ${SOURCES})