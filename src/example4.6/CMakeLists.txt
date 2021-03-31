cmake_minimum_required(VERSION 3.0)

project (example4.6 LANGUAGES C)

add_executable(example4.6 src/example4.6.c)

# build using the C11 standard
set_property(TARGET example4.6 PROPERTY C_STANDARD 11)

install(TARGETS example4.6 DESTINATION bin)
