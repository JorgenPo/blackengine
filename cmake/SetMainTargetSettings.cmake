# Setting a main target (Engine) properties

# Remove 'lib' prefix on windows builds
if (WIN32)
    SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES PREFIX "")
endif(WIN32)

# Set default installation build
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin CACHE PATH "..." FORCE)
endif()

include(GenerateExportHeader)

# Generate export header and place it in the source tree
set(EXPORTED_FILE_NAME "Exported.h")

generate_export_header(${PROJECT_NAME}
        EXPORT_MACRO_NAME "BLACK_EXPORTED"
        EXPORT_FILE_NAME ${EXPORTED_FILE_NAME})

file(COPY ${PROJECT_BINARY_DIR}/${EXPORTED_FILE_NAME} DESTINATION ${BLACKENGINE_SOURCE_DIR})