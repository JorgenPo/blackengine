cmake_minimum_required(3.6)

set(LINKLIBS_LIBRARIES "")
set(LINKLIBS_INCLUDE_DIRS "")

# Link core dll with a static gcc
if (WIN32)
    message(INFO " Using static linking of libstdc++ and libgcc")
    set(CMAKE_EXE_LINKER_FLAGS " -static")
    set(LINKLIBS_LIBRARIES ${LINKLIBS_LIBRARIES} -static-libgcc -static-libstdc++)
endif(WIN32)

if(UNIX)
    set(LINKLIBS_LIBRARIES ${LINKLIBS_LIBRARIES} ${CMAKE_DL_LIBS})
endif()

list(APPEND LINKLIBS_SOURCES ${BLACKENGINE_LIBRARY_DIR}/glad/src/glad.c)

set(CONAN_DISABLE_CHECK_COMPILER ON)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS)

list(APPEND LINKLIBS_LIBRARIES ${CONAN_LIBS})
