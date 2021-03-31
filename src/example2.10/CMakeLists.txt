cmake_minimum_required(VERSION 3.0)

project (example2.10 LANGUAGES C)

add_executable(example2.10 src/example2.10.c)

# build using the C11 standard
set_property(TARGET example2.10 PROPERTY C_STANDARD 11)

install(TARGETS example2.10 DESTINATION bin)
