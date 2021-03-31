cmake_minimum_required(VERSION 3.0)

project (example2.1 LANGUAGES C)

add_executable(example2.1 src/example2.1.c)

# build using the C11 standard
set_property(TARGET example2.1 PROPERTY C_STANDARD 11)

install(TARGETS example2.1 DESTINATION bin)
