cmake_minimum_required(VERSION 3.0)

project (example2.8 LANGUAGES C)

add_executable(example2.8 src/example2.8.c)

# build using the C11 standard
set_property(TARGET example2.8 PROPERTY C_STANDARD 11)

install(TARGETS example2.8 DESTINATION bin)
