cmake_minimum_required(VERSION 3.6)

project (example3.4 LANGUAGES C)

add_executable(example3.4 src/example3.4.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example3.4)

# build using the C11 standard
set_property(TARGET example3.4 PROPERTY C_STANDARD 11)

install(TARGETS example3.4 DESTINATION bin)
