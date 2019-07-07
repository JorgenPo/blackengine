cmake_minimum_required(3.6)

# GL Plugin
# Author: george popoff <popoff96@live.com>

set(PROJECT_NAME glPlugin)

set(ADDITIONAL_SOURCES ${BLACKENGINE_LIBRARY_DIR}/glad/src/glad.c)
SetupPlugin(${PROJECT_NAME})