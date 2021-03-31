cmake_minimum_required(VERSION 3.0)

project (example3.5 LANGUAGES C)

add_executable(example3.5 src/example3.5.c)

# build using the C11 standard
set_property(TARGET example3.5 PROPERTY C_STANDARD 11)

install(TARGETS example3.5 DESTINATION bin)
