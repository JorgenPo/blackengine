cmake_minimum_required(VERSION 3.12)

# Adds a new target with a given plugin
function(SetupPlugin pluginName)
    project(${pluginName})

    set(CMAKE_CXX_STANDARD 17)

    file(GLOB SOURCES "src/*.h" "src/*.cpp")

    include_directories(${BLACKENGINE_SOURCE_DIR})

    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

    add_library(${pluginName} SHARED ${SOURCES} ${ADDITIONAL_SOURCES})

    target_link_libraries(${pluginName} ${BLACKENGINE_TARGET} ${GLFW_LIBRARIES})

    # Set output directory to the main library dir
    set_target_properties(${pluginName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)
    set_target_properties(${pluginName} PROPERTIES PREFIX "")

    get_target_property(OUTPUT_DIR ${pluginName} RUNTIME_OUTPUT_DIRECTORY)
    message(INFO " output dir is ${OUTPUT_DIR}")

    # Without this on linux executable does not find black engine library
    set_target_properties(${pluginName} PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

    install(TARGETS ${pluginName} DESTINATION ${CMAKE_INSTALL_PREFIX}/blackengine/plugins)

    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)
endfunction(SetupPlugin)