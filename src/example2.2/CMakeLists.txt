cmake_minimum_required(VERSION 3.0)

project (example2.2 LANGUAGES C)

add_executable(example2.2 src/example2.2.c)

# build using the C11 standard
set_property(TARGET example2.2 PROPERTY C_STANDARD 11)

install(TARGETS example2.2 DESTINATION bin)
