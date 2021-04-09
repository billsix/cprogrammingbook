cmake_minimum_required(VERSION 3.6)

project (example3.5 LANGUAGES C)

add_executable(example3.5 src/example3.5.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example3.5)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_STARTUP_PROJECT example3.5)

# build using the C11 standard
set_property(TARGET example3.5 PROPERTY C_STANDARD 11)

install(TARGETS example3.5 DESTINATION bin)
