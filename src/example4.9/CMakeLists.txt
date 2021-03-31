cmake_minimum_required(VERSION 3.0)

project (example4.9 LANGUAGES C)

SET(SOURCE_FILES
  src/example4.9.c
  src/secondfile.c)

add_executable(example4.9 ${SOURCE_FILES})

# build using the C11 standard
set_property(TARGET example4.9 PROPERTY C_STANDARD 11)

install(TARGETS example4.9 DESTINATION bin)
