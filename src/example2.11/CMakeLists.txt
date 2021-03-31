cmake_minimum_required(VERSION 3.0)

project (example2.11 LANGUAGES C)

add_executable(example2.11 src/example2.11.c)

# build using the C11 standard
set_property(TARGET example2.11 PROPERTY C_STANDARD 11)

install(TARGETS example2.11 DESTINATION bin)
