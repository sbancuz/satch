//
// Created by sbancuz on 12/16/22.
//

#ifndef ELF_PATCHER_ELF_PROGRAM_HEADER_H
#define ELF_PATCHER_ELF_PROGRAM_HEADER_H

#include <stdio.h>
#include "macros.h"
#include "structs.h"

Elf64_Phdr read_program_header(FILE *src);

void print_program_header(ElfW(Phdr) *src);

char *segment_type_to_str(ElfW(Word) typ);

#endif //ELF_PATCHER_ELF_PROGRAM_HEADER_H
