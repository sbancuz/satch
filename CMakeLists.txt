cmake_minimum_required(VERSION 3.24)
project(elf_patcher C)

add_compile_options(-Wall -Wextra -pedantic -Wpedantic -Wshadow)

set(CMAKE_C_STANDARD 23)

add_executable(elf_patcher src/main.c src/elf_header.c src/headers/elf_header.h src/headers/macros.h src/elf_program_header.c src/headers/elf_program_header.h src/elf_file.c src/headers/elf_file.h)
