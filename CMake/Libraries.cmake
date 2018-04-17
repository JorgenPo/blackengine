find_package(OpenGL REQUIRED)

set(Libraries_LIBRARIES ${OPENGL_LIBRARY})
set(Libraries_INCLUDE_PATH "")

set(ENABLE_GLFW OFF CACHE BOOL "Enable suppport of GLFW")

set(GLFW_INCLUDE_PATH "" CACHE PATH "The directory that contains GL/glfw3.h" )
set(GLFW_LIBRARY "" CACHE FILEPATH "libglfw3.a or glfw3.dll" )

if (ENABLE_GLFW)
    message(STATUS "Support of GLFW enabled")
    if (GLFW_INCLUDE_PATH STREQUAL "" OR GLFW_LIBRARY STREQUAL "")
        message(FATAL_ERROR "You must set up GLFW path")
    else()
        set(Libraries_LIBRARIES ${Libraries_LIBRARIES} ${GLFW_LIBRARY})
        set(Libraries_INCLUDE_PATH ${GLFW_INCLUDE_PATH})
        add_definitions(-DGLFW_DLL)
        install(FILES ${GLFW_LIBRARY} DESTINATION ${BUILD_DIR}/examples)
        install(FILES ${GLFW_LIBRARY} DESTINATION ${BUILD_DIR}/)
        install(FILES ${GLFW_LIBRARY} DESTINATION ${CMAKE_BINARY_DIR}/examples/SimpleApplication)
    endif(GLFW_INCLUDE_PATH STREQUAL "" OR GLFW_LIBRARY STREQUAL "")
endif(ENABLE_GLFW)