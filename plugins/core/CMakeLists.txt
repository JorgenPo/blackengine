cmake_minimum_required(VERSION 3.10)
project(CorePlugin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

file(GLOB SOURCES
        src/*.h
        src/*.cpp
        )

include_directories(src)

add_library(CorePlugin SHARED ${SOURCES})

# Remove lib prefix
set_target_properties(CorePlugin PROPERTIES PREFIX "")

target_link_libraries(CorePlugin BlackEngine)

install(TARGETS CorePlugin DESTINATION ${BUILD_DIR}/plugins)

# Install plugin to examples to test examples with this plugin
install(TARGETS CorePlugin DESTINATION ${CMAKE_BINARY_DIR}/examples/SimpleApplication)
install(TARGETS CorePlugin DESTINATION ${BUILD_DIR}/examples/)