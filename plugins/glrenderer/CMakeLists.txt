cmake_minimum_required(VERSION 3.10)
project(GLRendererPlugin)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        src/*.h
        src/glsl/*.h

        src/*.cpp
        src/glsl/*.cpp

        src/glad/src/glad.c
        )

set(LIBRARIES BlackEngine)

include_directories(src src/glad/include)

add_library(GLRendererPlugin SHARED ${SOURCES})

# Remove lib prefix
set_target_properties(GLRendererPlugin PROPERTIES PREFIX "")

target_link_libraries(GLRendererPlugin ${LIBRARIES})

install(TARGETS GLRendererPlugin DESTINATION plugins/)
install(TARGETS GLRendererPlugin DESTINATION examples/)