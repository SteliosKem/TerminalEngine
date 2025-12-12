cmake_minimum_required(VERSION 3.10.0)
project(TerminalEngine VERSION 0.1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)

add_executable(TerminalEngine src/TerminalEngine/Windows/Application.c src/Game/main.c src/TerminalEngine/Windows/Input.c src/TerminalEngine/Renderer/Renderer.c)
target_include_directories(TerminalEngine PRIVATE src/)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_options(TerminalEngine PRIVATE
        -finput-charset=UTF-8
        -fexec-charset=UTF-8
    )
endif()