cmake_minimum_required(VERSION 3.6)

project (example4.11 LANGUAGES C)

add_executable(example4.11 src/example4.11.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example4.11)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_STARTUP_PROJECT example4.11)

# build using the C11 standard
set_property(TARGET example4.11 PROPERTY C_STANDARD 11)

install(TARGETS example4.11 DESTINATION bin)
