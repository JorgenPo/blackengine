cmake_minimum_required(3.6)

# Model parsers plugin
# Provides some model parsers
# Author: george popoff <popoff96@live.com>

set(PROJECT_NAME modelParsersPlugin)

file(GLOB ADDITIONAL_SOURCES "src/parsers/*.h" "src/parsers/*.cpp")

SetupPlugin(${PROJECT_NAME})