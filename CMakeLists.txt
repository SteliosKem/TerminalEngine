cmake_minimum_required(VERSION 3.10.0)
project(Battleships VERSION 0.1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)

add_executable(Battleships src/TerminalEngine/Windows/Application.c src/Battleships/main.c)
target_include_directories(Battleships PRIVATE src/)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_options(Battleships PRIVATE
        -finput-charset=UTF-8
        -fexec-charset=UTF-8
    )
endif()