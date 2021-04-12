cmake_minimum_required(VERSION 3.6)

project (example8.6 LANGUAGES C)

add_executable(example8.6 src/example8.6.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example8.6)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_STARTUP_PROJECT example8.6)

# build using the C11 standard
set_property(TARGET example8.6 PROPERTY C_STANDARD 11)

install(TARGETS example8.6 DESTINATION bin)
