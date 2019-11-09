cmake_minimum_required(VERSION 3.6)

# GL Plugin
# Author: george popoff <popoff96@live.com>

set(PROJECT_NAME glPlugin)

file(GLOB GLFW_SOURCES src/glfw/*.h src/glfw/*.cpp)
set(ADDITIONAL_SOURCES ${BLACKENGINE_LIBRARY_DIR}/glad/src/glad.c ${GLFW_SOURCES})

SetupPlugin(${PROJECT_NAME})
