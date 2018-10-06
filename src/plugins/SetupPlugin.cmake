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

    install(TARGETS ${pluginName} DESTINATION debug/plugins CONFIGURATIONS Debug)
    install(TARGETS ${pluginName} DESTINATION release/plugins CONFIGURATIONS Release)

    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)
endfunction(SetupPlugin)