cmake_minimum_required(VERSION 3.0)

project (example4.11 LANGUAGES C)

add_executable(example4.11 src/example4.11.c)

# build using the C11 standard
set_property(TARGET example4.11 PROPERTY C_STANDARD 11)

install(TARGETS example4.11 DESTINATION bin)
