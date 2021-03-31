cmake_minimum_required(VERSION 3.0)

project (example2.4 LANGUAGES C)

add_executable(example2.4 src/example2.4.c)

# build using the C11 standard
set_property(TARGET example2.4 PROPERTY C_STANDARD 11)

install(TARGETS example2.4 DESTINATION bin)
