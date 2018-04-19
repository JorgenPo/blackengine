cmake_minimum_required(VERSION 3.10)
project(CorePlugin)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        src/*.h
        src/*.cpp
        )

set(LIBRARIES BlackEngine)

include_directories(src)

add_library(CorePlugin SHARED ${SOURCES})

# Remove lib prefix
set_target_properties(CorePlugin PROPERTIES PREFIX "")

target_link_libraries(CorePlugin ${LIBRARIES})

install(TARGETS CorePlugin DESTINATION plugins/)
install(TARGETS CorePlugin DESTINATION examples/)