cmake_minimum_required(VERSION 3.0)

project (example4.7 LANGUAGES C)

add_executable(example4.7 src/example4.7.c)

# build using the C11 standard
set_property(TARGET example4.7 PROPERTY C_STANDARD 11)

install(TARGETS example4.7 DESTINATION bin)
