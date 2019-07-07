cmake_minimum_required(VERSION 3.6)

# Adds a new target with a given example
function(SetupExample exampleName)
    project(${exampleName})

    set(CMAKE_CXX_STANDARD 17)

    file(GLOB SOURCES "src/*.h" "src/*.cpp")
    file(GLOB SHADERS "shaders/*.glsl")
    file(GLOB RESOURCES "models/*")

    include_directories(${BLACKENGINE_SOURCE_DIR})

    add_executable(${exampleName} ${SOURCES})
    target_link_libraries(${exampleName} ${BLACKENGINE_TARGET})

    # Set output directory to the main library dir
    set_target_properties(${exampleName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set_target_properties(${exampleName} PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

    install(TARGETS ${exampleName} DESTINATION ${EXAMPLE_INSTALL_PREFIX})
    install(FILES ${SHADERS} DESTINATION ${SHADER_INSTALL_PREFIX})
    install(FILES ${RESOURCES} DESTINATION ${RESOURCE_INSTALL_PREFIX})

    install_symlink(${SHADER_INSTALL_PREFIX} ${EXAMPLE_INSTALL_PREFIX}/shaders)
endfunction(SetupExample)