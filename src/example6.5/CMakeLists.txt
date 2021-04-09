cmake_minimum_required(VERSION 3.6)

project (example6.5 LANGUAGES C)

add_executable(example6.5 src/example6.5.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example6.5)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_STARTUP_PROJECT example6.5)

# build using the C11 standard
set_property(TARGET example6.5 PROPERTY C_STANDARD 11)

install(TARGETS example6.5 DESTINATION bin)
