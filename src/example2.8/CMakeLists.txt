cmake_minimum_required(VERSION 3.6)

project (example2.8 LANGUAGES C)

add_executable(example2.8 src/example2.8.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example2.8)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_STARTUP_PROJECT example2.8)

# build using the C11 standard
set_property(TARGET example2.8 PROPERTY C_STANDARD 11)

install(TARGETS example2.8 DESTINATION bin)
