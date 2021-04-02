cmake_minimum_required(VERSION 3.6)

project (example1.3 LANGUAGES C)

add_executable(example1.3 src/example1.3.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example1.3)

# build using the C11 standard
set_property(TARGET example1.3 PROPERTY C_STANDARD 11)

install(TARGETS example1.3 DESTINATION bin)
