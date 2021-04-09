cmake_minimum_required(VERSION 3.6)

project (example4.8 LANGUAGES C)

add_executable(example4.8 src/example4.8.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example4.8)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_STARTUP_PROJECT example4.8)

# build using the C11 standard
set_property(TARGET example4.8 PROPERTY C_STANDARD 11)

install(TARGETS example4.8 DESTINATION bin)
