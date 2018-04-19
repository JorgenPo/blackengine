cmake_minimum_required(VERSION 3.10)
project(GLRenderPlugin)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        src/*.h
        src/*.cpp
        )

set(LIBRARIES BlackEngine)

include_directories(src)

add_library(GLRenderPlugin SHARED ${SOURCES})

# Remove lib prefix
set_target_properties(GLRenderPlugin PROPERTIES PREFIX "")

target_link_libraries(GLRenderPlugin ${LIBRARIES})

install(TARGETS GLRenderPlugin DESTINATION plugins/)
install(TARGETS GLRenderPlugin DESTINATION examples/)