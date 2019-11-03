cmake_minimum_required(VERSION 3.6)
# Plugins subproject

# Function to setup a plugin
include(SetupPlugin.cmake)
include(AddPlugin.cmake)

# Set plugins here
set(PLUGINS gl modelParsers qt)

set(BlackEngine_PLUGINS ${BlackEngine_PLUGINS} ${PLUGINS} PARENT_SCOPE)

foreach(Plugin ${PLUGINS})
    AddPlugin(${Plugin})
endforeach()
