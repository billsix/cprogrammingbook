cmake_minimum_required(VERSION 3.6)

project (example5.17 LANGUAGES C)

add_executable(example5.17 src/example5.17.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example5.17)

# build using the C11 standard
set_property(TARGET example5.17 PROPERTY C_STANDARD 11)

install(TARGETS example5.17 DESTINATION bin)
