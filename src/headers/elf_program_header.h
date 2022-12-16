//
// Created by sbancuz on 12/16/22.
//

#include <elf.h>
#include <stdio.h>

#ifndef ELF_PATCHER_ELF_PROGRAM_HEADER_H
#define ELF_PATCHER_ELF_PROGRAM_HEADER_H

Elf64_Phdr read_program_header(FILE *src);

void print_program_header(Elf64_Phdr *src);

char *segment_type_to_str(Elf64_Word typ);

#endif //ELF_PATCHER_ELF_PROGRAM_HEADER_H
