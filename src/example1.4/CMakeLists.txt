cmake_minimum_required(VERSION 3.0)

project (example1.4 LANGUAGES C)

add_executable(example1.4 src/example1.4.c)

# build using the C11 standard
set_property(TARGET example1.4 PROPERTY C_STANDARD 11)

install(TARGETS example1.4 DESTINATION bin)
