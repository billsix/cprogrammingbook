cmake_minimum_required(VERSION 3.6)

project (example6.14 LANGUAGES C)

add_executable(example6.14 src/example6.14.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example6.14)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_STARTUP_PROJECT example6.14)

# build using the C11 standard
set_property(TARGET example6.14 PROPERTY C_STANDARD 11)

install(TARGETS example6.14 DESTINATION bin)
