cmake_minimum_required(VERSION 3.0)

project (example4.3 LANGUAGES C)

add_executable(example4.3 src/example4.3.c)

# build using the C11 standard
set_property(TARGET example4.3 PROPERTY C_STANDARD 11)

install(TARGETS example4.3 DESTINATION bin)
