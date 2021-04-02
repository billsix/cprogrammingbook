cmake_minimum_required(VERSION 3.6)

project (example4.6 LANGUAGES C)

add_executable(example4.6 src/example4.6.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example4.6)

# build using the C11 standard
set_property(TARGET example4.6 PROPERTY C_STANDARD 11)

install(TARGETS example4.6 DESTINATION bin)
