cmake_minimum_required(VERSION 3.6)

project (example4.10 LANGUAGES C)

set(SOURCE_FILES
  src/example4.10.c
  src/secondfile.c)

add_executable(example4.10 ${SOURCE_FILES})
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT example4.10)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_STARTUP_PROJECT example4.10)

# build using the C11 standard
set_property(TARGET example4.10 PROPERTY C_STANDARD 11)

install(TARGETS example4.10 DESTINATION bin)
