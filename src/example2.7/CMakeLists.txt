cmake_minimum_required(VERSION 3.0)

project (example2.7 LANGUAGES C)

add_executable(example2.7 src/example2.7.c)

# build using the C11 standard
set_property(TARGET example2.7 PROPERTY C_STANDARD 11)

install(TARGETS example2.7 DESTINATION bin)
