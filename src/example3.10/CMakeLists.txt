cmake_minimum_required(VERSION 3.0)

project (example3.10 LANGUAGES C)

add_executable(example3.10 src/example3.10.c)

# build using the C11 standard
set_property(TARGET example3.10 PROPERTY C_STANDARD 11)

install(TARGETS example3.10 DESTINATION bin)
