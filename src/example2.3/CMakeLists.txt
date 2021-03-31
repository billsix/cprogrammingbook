cmake_minimum_required(VERSION 3.0)

project (example2.3 LANGUAGES C)

add_executable(example2.3 src/example2.3.c)

# build using the C11 standard
set_property(TARGET example2.3 PROPERTY C_STANDARD 11)

install(TARGETS example2.3 DESTINATION bin)
