# Different util functions

macro(install_symlink filepath sympath)
    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${filepath} ${sympath})")
    install(CODE "message(\"-- Created symlink: ${sympath} -> ${filepath}\")")
endmacro(install_symlink)

macro(copy_resources_to_build_folder)
    # Copy shaders and resources to the binary dir to developing and testing
    file(GLOB SHADERS ${CMAKE_SOURCE_DIR}/src/plugins/gl/shaders/*.glsl ${CMAKE_SOURCE_DIR}/examples/simple/shaders/*.glsl)
    file(GLOB RESOURCES ${CMAKE_SOURCE_DIR}/examples/simple/models/*)

    file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/lib/resources)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib/resources)

    foreach(SHADER ${SHADERS})
        message(STATUS "Copy ${SHADER} to ${CMAKE_CURRENT_BINARY_DIR}/lib/resource/${SHADER_NAME}")
        get_filename_component(SHADER_NAME ${SHADER} NAME)
        file(GENERATE
                OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/lib/resources/${SHADER_NAME}
                INPUT ${SHADER})
    endforeach()

    file(COPY ${RESOURCES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/lib/resources)
    foreach(RESOURCE ${RESOURCES})
        get_filename_component(RESOURCE_NAME ${RESOURCE} NAME)
        message(STATUS "Copy ${RESOURCE} to ${CMAKE_CURRENT_BINARY_DIR}/lib/resource/${RESOURCE_NAME}")

        ## For some reason file(GENERATE) corrupts images
        configure_file(${RESOURCE} ${CMAKE_CURRENT_BINARY_DIR}/lib/resource/${RESOURCE_NAME} COPYONLY)
    endforeach()
endmacro()