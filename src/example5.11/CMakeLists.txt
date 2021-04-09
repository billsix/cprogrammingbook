cmake_minimum_required(VERSION 3.6)

project (example5.11 LANGUAGES C)

add_executable(example5.11 src/example5.11.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example5.11)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_STARTUP_PROJECT example5.11)

# build using the C11 standard
set_property(TARGET example5.11 PROPERTY C_STANDARD 11)

install(TARGETS example5.11 DESTINATION bin)
