//
// Created by sbancuz on 12/16/22.
//
#ifndef ELF_PATCHER_ELF_HEADER_H
#define ELF_PATCHER_ELF_HEADER_H

#include <elf.h>
#include <stdlib.h>
#include <stdio.h>

void print_elf_header(Elf64_Ehdr *hdr);

Elf64_Ehdr read_elf_header(FILE *src);

Elf64_Phdr read_program_header(FILE *src);

char *abi_to_string(int abi);

char *type_to_string(Elf64_Half type);

char *machine_to_string(Elf64_Half machine);

#endif //ELF_PATCHER_ELF_HEADER_H
