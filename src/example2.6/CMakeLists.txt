cmake_minimum_required(VERSION 3.0)

project (example2.6 LANGUAGES C)

add_executable(example2.6 src/example2.6.c)

# build using the C11 standard
set_property(TARGET example2.6 PROPERTY C_STANDARD 11)

install(TARGETS example2.6 DESTINATION bin)
