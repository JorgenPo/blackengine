cmake_minimum_required(3.6)
# Setting a main target (Engine) properties

# Remove 'lib' prefix on windows builds
if (WIN32)
    SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES PREFIX "")
endif(WIN32)

# Set default installation build
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    if (UNIX)
        set(CMAKE_INSTALL_PREFIX /usr/local CACHE PATH "..." FORCE)
    endif(UNIX)
endif()

include(GenerateExportHeader)

# Generate export header and place it in the source tree
set(EXPORTED_FILE_NAME "Exported.h")

generate_export_header(${PROJECT_NAME}
        EXPORT_MACRO_NAME "BLACK_EXPORTED"
        EXPORT_FILE_NAME ${EXPORTED_FILE_NAME})

file(COPY ${PROJECT_BINARY_DIR}/${EXPORTED_FILE_NAME} DESTINATION ${BLACKENGINE_SOURCE_DIR})