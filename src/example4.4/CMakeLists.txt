cmake_minimum_required(VERSION 3.0)

project (example4.4 LANGUAGES C)

add_executable(example4.4 src/example4.4.c)

# build using the C11 standard
set_property(TARGET example4.4 PROPERTY C_STANDARD 11)

install(TARGETS example4.4 DESTINATION bin)
