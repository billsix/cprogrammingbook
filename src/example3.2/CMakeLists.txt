cmake_minimum_required(VERSION 3.0)

project (example3.2 LANGUAGES C)

add_executable(example3.2 src/example3.2.c)

# build using the C11 standard
set_property(TARGET example3.2 PROPERTY C_STANDARD 11)

install(TARGETS example3.2 DESTINATION bin)
