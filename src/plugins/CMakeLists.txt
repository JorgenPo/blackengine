cmake_minimum_required(VERSION 3.6)
# Plugins subproject

# Function to setup a plugin
include(SetupPlugin.cmake)

# Add examples
add_subdirectory(gl)
add_subdirectory(modelParsers)