# Adds a new target with a given example
function(SetupExample exampleName)
    project(${exampleName})

    set(CMAKE_CXX_STANDARD 17)

    file(GLOB SOURCES "src/*.h" "src/*.cpp")

    include_directories(${BLACKENGINE_SOURCE_DIR})

    add_executable(${exampleName} ${SOURCES})
    target_link_libraries(${exampleName} ${BLACKENGINE_TARGET})

    # Set output directory to the main library dir
    set_target_properties(${exampleName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

    install(TARGETS ${exampleName} DESTINATION debug CONFIGURATIONS Debug)
    install(TARGETS ${exampleName} DESTINATION release CONFIGURATIONS Release)

endfunction(SetupExample)