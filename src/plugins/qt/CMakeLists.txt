cmake_minimum_required(VERSION 3.6)

# QT Plugin
# Author: george popoff <popoff96@live.com>

set(PROJECT_NAME qtPlugin)

SetupPlugin(${PROJECT_NAME})

find_package(Qt5Gui REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${Qt5Gui_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${Qt5Gui_INCLUDES})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${Qt5Gui_DEFINITIONS})
target_compile_options(${PROJECT_NAME} INTERFACE ${Qt5Gui_EXECUTABLE_COMPILE_FLAGS})