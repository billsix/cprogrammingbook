cmake_minimum_required(VERSION 3.0)

project (example3.7 LANGUAGES C)

add_executable(example3.7 src/example3.7.c)

# build using the C11 standard
set_property(TARGET example3.7 PROPERTY C_STANDARD 11)

install(TARGETS example3.7 DESTINATION bin)
