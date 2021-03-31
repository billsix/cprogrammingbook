cmake_minimum_required(VERSION 3.0)

project (example1.1 LANGUAGES C)

add_executable(example1.1 src/example1.1.c)

# build using the C11 standard
set_property(TARGET example1.1 PROPERTY C_STANDARD 11)

install(TARGETS example1.1 DESTINATION bin)
