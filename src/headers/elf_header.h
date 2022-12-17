//
// Created by sbancuz on 12/16/22.
//
#ifndef ELF_PATCHER_ELF_HEADER_H
#define ELF_PATCHER_ELF_HEADER_H

#include <elf.h>
#include <stdlib.h>
#include <stdio.h>
#include "macros.h"

Elf64_Ehdr read_elf_header(FILE *src);

void print_elf_header(ElfW(Ehdr) *hdr);

char *abi_to_string(int abi);

char *type_to_string(ElfW(Half) type);

char *machine_to_string(ElfW(Half) machine);

#endif //ELF_PATCHER_ELF_HEADER_H
