cmake_minimum_required(VERSION 3.6)

project (example2.4 LANGUAGES C)

add_executable(example2.4 src/example2.4.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example2.4)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_STARTUP_PROJECT example2.4)

# build using the C11 standard
set_property(TARGET example2.4 PROPERTY C_STANDARD 11)

install(TARGETS example2.4 DESTINATION bin)
