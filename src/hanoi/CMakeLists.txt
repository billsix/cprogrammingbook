cmake_minimum_required(VERSION 3.6)

project (hanoi LANGUAGES C)

add_executable(hanoi-first src/hanoi-first.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT hanoi-first)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_STARTUP_PROJECT hanoi-first)

# build using the C11 standard
set_property(TARGET hanoi-first PROPERTY C_STANDARD 11)






add_executable(hanoi-subroutine-linkage src/hanoi-subroutine-linkage.c)
# To make visual studio open with the correct project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT hanoi-subroutine-linkage)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY XCODE_STARTUP_PROJECT hanoi-subroutine-linkage)

# build using the C11 standard
set_property(TARGET hanoi-subroutine-linkage PROPERTY C_STANDARD 11)







install(TARGETS hanoi-first hanoi-subroutine-linkage DESTINATION bin)
