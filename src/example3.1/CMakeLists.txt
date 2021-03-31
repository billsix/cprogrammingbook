cmake_minimum_required(VERSION 3.0)

project (example3.1 LANGUAGES C)

add_executable(example3.1 src/example3.1.c)

# build using the C11 standard
set_property(TARGET example3.1 PROPERTY C_STANDARD 11)

install(TARGETS example3.1 DESTINATION bin)
