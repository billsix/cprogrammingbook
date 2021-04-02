cmake_minimum_required(VERSION 3.6)

project (example5.3 LANGUAGES C)

add_executable(example5.3 src/example5.3.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example5.3)

# build using the C11 standard
set_property(TARGET example5.3 PROPERTY C_STANDARD 11)

install(TARGETS example5.3 DESTINATION bin)
