cmake_minimum_required(VERSION 3.6)

# Adds a new target with a given plugin
function(SetupPlugin pluginName)
    project(${pluginName})
    set(CMAKE_CXX_STANDARD 17)

    file(GLOB SOURCES "src/*.h" "src/*.cpp")
    file(GLOB SHADERS "shaders/*.glsl")

    include_directories(${BLACKENGINE_SOURCE_DIR})

    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

    add_library(${pluginName} SHARED ${SOURCES} ${ADDITIONAL_SOURCES})

    target_include_directories(${pluginName} PRIVATE ${BLACKENGINE_SOURCE_DIR})
    target_link_libraries(${pluginName} PRIVATE ${BLACKENGINE_TARGET} ${LINKLIBS_LIBRARIES})

    # Set output directory to the main library dir
    set_target_properties(${pluginName} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/plugins
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/plugins)

    set_target_properties(${pluginName} PROPERTIES PREFIX "")

    get_target_property(OUTPUT_DIR ${pluginName} RUNTIME_OUTPUT_DIRECTORY)
    message(INFO " output dir is ${OUTPUT_DIR}")

    set_target_properties(${pluginName} PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

    install(TARGETS ${pluginName} DESTINATION lib/blackengine/plugins)
    install(FILES ${SHADERS} DESTINATION ${SHADER_INSTALL_PREFIX})

    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)

    add_custom_command(TARGET ${pluginName} POST_BUILD    # Adds a post-build event to MyTest
            COMMAND ${CMAKE_COMMAND} -E copy_if_different   # which executes "cmake - E copy_if_different..."
            $<TARGET_FILE:${pluginName}>           # <--this is in-file
            "${CMAKE_BINARY_DIR}/bin")
endfunction(SetupPlugin)