cmake_minimum_required(VERSION 3.0)

project (example4.12 LANGUAGES C)

add_executable(example4.12 src/example4.12.c)

# build using the C11 standard
set_property(TARGET example4.12 PROPERTY C_STANDARD 11)

install(TARGETS example4.12 DESTINATION bin)
