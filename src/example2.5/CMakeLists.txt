cmake_minimum_required(VERSION 3.6)

project (example2.5 LANGUAGES C)

add_executable(example2.5 src/example2.5.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example2.5)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_STARTUP_PROJECT example2.5)

# build using the C11 standard
set_property(TARGET example2.5 PROPERTY C_STANDARD 11)

install(TARGETS example2.5 DESTINATION bin)
