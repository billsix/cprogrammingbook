cmake_minimum_required(VERSION 3.6)

project (example4.1 LANGUAGES C)

add_executable(example4.1 src/example4.1.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example4.1)

# build using the C11 standard
set_property(TARGET example4.1 PROPERTY C_STANDARD 11)

install(TARGETS example4.1 DESTINATION bin)
