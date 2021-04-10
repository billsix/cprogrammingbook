cmake_minimum_required(VERSION 3.6)

project (example7.3 LANGUAGES C)

add_executable(example7.3 src/example7.3.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example7.3)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_STARTUP_PROJECT example7.3)

# build using the C11 standard
set_property(TARGET example7.3 PROPERTY C_STANDARD 11)

install(TARGETS example7.3 DESTINATION bin)
