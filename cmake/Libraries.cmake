cmake_minimum_required(VERSION 3.12)

set(LINKLIBS_LIBRARIES "")
set(LINKLIBS_INCLUDE_DIRS "")

# Link core dll with a static gcc
if (WIN32)
    message(INFO " Using static linking of libstdc++ and libgcc")
    set(CMAKE_EXE_LINKER_FLAGS " -static")
    set(LINKLIBS_LIBRARIES ${LINKLIBS_LIBRARIES} -static-libgcc -static-libstdc++)
endif(WIN32)

message(STATUS "Searching for GLFW library")

if(WIN32)
    set(GLFW_ROOT "" CACHE PATH "Path to the directory containing glfw")
endif(WIN32)

find_package(GLFW REQUIRED)

set(GLAD_INCLUDE_DIRS ${BLACKENGINE_LIBRARY_DIR}/glad/include)
set(GLAD_SOURCES ${BLACKENGINE_LIBRARY_DIR}/glad/src/glad.c)

# Set to ON to see additional FindBoost log
set(Boost_DEBUG OFF)

if (WIN32)
    message(INFO " You must mannualy set BOOST_ROOT and BOOST_LIBRARYDIR on windows")
    set(BOOST_ROOT "" CACHE PATH "Path to the directory containing boost")
    set(BOOST_LIBRARYDIR "" CACHE PATH "Path to the directory containing boost built libraryes")
    message(INFO " BOOST_ROOT=" ${BOOST_ROOT})
    message(INFO " BOOST_LIBRARY_DIR=" ${BOOST_LIBRARYDIR})

    set(Boost_USE_STATIC_LIBS ON)
    message(INFO " Using static boost libs")
endif(WIN32)

find_package(Boost 1.67.0 REQUIRED COMPONENTS filesystem)

message(STATUS "BOOST_INCLUDES=${Boost_INCLUDE_DIR}")
message(STATUS "BOOST_LIBRARIES=${Boost_LIBRARIES}")

set(LINKLIBS_LIBRARIES ${LINKLIBS_LIBRARIES} ${GLFW_LIBRARIES} ${Boost_LIBRARIES})

if(UNIX)
    set(LINKLIBS_LIBRARIES ${LINKLIBS_LIBRARIES} ${CMAKE_DL_LIBS})
endif()

set(LINKLIBS_INCLUDE_DIRS ${LINKLIBS_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLAD_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})
set(LINKLIBS_SOURCES ${GLAD_SOURCES})