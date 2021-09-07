cmake_minimum_required(VERSION 3.6)

project (hanoi LANGUAGES C)

add_executable(hanoi-recursive src/hanoi-recursive.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT hanoi-recursive)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_STARTUP_PROJECT hanoi-recursive)

# build using the C11 standard
set_property(TARGET hanoi-recursive PROPERTY C_STANDARD 11)

add_executable(hanoi-nonrecursive src/hanoi-nonrecursive.c)
# build using the C11 standard
set_property(TARGET hanoi-nonrecursive PROPERTY C_STANDARD 11)






add_executable(hanoi-subroutine-linkage src/hanoi-subroutine-linkage.c)
# build using the C11 standard
set_property(TARGET hanoi-subroutine-linkage PROPERTY C_STANDARD 11)


add_executable(hanoi-no-structs src/hanoi-no-structs.c)
# build using the C11 standard
set_property(TARGET hanoi-no-structs PROPERTY C_STANDARD 11)







install(TARGETS hanoi-recursive hanoi-nonrecursive hanoi-subroutine-linkage hanoi-no-structs DESTINATION bin)
