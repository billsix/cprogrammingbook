cmake_minimum_required(VERSION 3.0)

project (example2.5 LANGUAGES C)

add_executable(example2.5 src/example2.5.c)

# build using the C11 standard
set_property(TARGET example2.5 PROPERTY C_STANDARD 11)

install(TARGETS example2.5 DESTINATION bin)
