cmake_minimum_required(VERSION 3.0)

project (example2.9 LANGUAGES C)

add_executable(example2.9 src/example2.9.c)

# build using the C11 standard
set_property(TARGET example2.9 PROPERTY C_STANDARD 11)

install(TARGETS example2.9 DESTINATION bin)
