set(LINKLIBS_LIBRARIES "")
set(LINKLIBS_INCLUDE_DIRS "")

# Link core dll with a static gcc
if (WIN32)
    message(INFO " Using static linking of libstdc++ and libgcc")
    set(CMAKE_EXE_LINKER_FLAGS " -static")
    set(LINKLIBS_LIBRARIES ${LINKLIBS_LIBRARIES} -static-libgcc -static-libstdc++)
endif(WIN32)

message(STATUS "Searching for GLFW library")

set(GLFW_ROOT "" CACHE PATH "Path to the directory containing glfw")

find_package(GLFW REQUIRED)

set(GLAD_INCLUDE_DIRS ${BLACKENGINE_LIBRARY_DIR}/glad/include)
set(GLAD_SOURCES ${BLACKENGINE_LIBRARY_DIR}/glad/src/glad.c)

set(LINKLIBS_LIBRARIES ${LINKLIBS_LIBRARIES} ${GLFW_LIBRARIES})
set(LINKLIBS_INCLUDE_DIRS ${LINKLIBS_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLAD_INCLUDE_DIRS})
set(LINKLIBS_SOURCES ${GLAD_SOURCES})