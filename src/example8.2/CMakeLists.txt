cmake_minimum_required(VERSION 3.6)

project (example8.2 LANGUAGES C)

add_executable(example8.2 src/example8.2.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example8.2)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_STARTUP_PROJECT example8.2)

# build using the C11 standard
set_property(TARGET example8.2 PROPERTY C_STANDARD 11)

install(TARGETS example8.2 DESTINATION bin)
