cmake_minimum_required(VERSION 3.0)

project (example4.8 LANGUAGES C)

add_executable(example4.8 src/example4.8.c)

# build using the C11 standard
set_property(TARGET example4.8 PROPERTY C_STANDARD 11)

install(TARGETS example4.8 DESTINATION bin)
