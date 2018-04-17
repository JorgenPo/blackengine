cmake_minimum_required(VERSION 3.10)
project(SimpleApplicationExample)

set(CMAKE_CXX_STANDARD 17)

set(SimpleApplicationExample_INSTALL_DIR ${BUILD_DIR}/examples)
include_directories(src)

file(GLOB SOURCES
        "src/*.h"
        "src/*.cpp")

add_executable(SimpleApplicationExample ${SOURCES})

# Link with blackEngine
target_link_libraries(SimpleApplicationExample BlackEngine)

install(TARGETS SimpleApplicationExample RUNTIME DESTINATION ${SimpleApplicationExample_INSTALL_DIR})