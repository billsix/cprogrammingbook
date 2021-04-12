cmake_minimum_required(VERSION 3.6)

project (example9.1 LANGUAGES C)

add_executable(example9.1 src/example9.1.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example9.1)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_STARTUP_PROJECT example9.1)

# build using the C11 standard
set_property(TARGET example9.1 PROPERTY C_STANDARD 11)

install(TARGETS example9.1 DESTINATION bin)
