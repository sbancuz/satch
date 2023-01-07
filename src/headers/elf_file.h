//
// Created by sbancuz on 12/16/22.
//

#ifndef ELF_PATCHER_ELF_FILE_H
#define ELF_PATCHER_ELF_FILE_H

#include <elf.h>
#include <bits/types/FILE.h>

#include "structs.h"

Elf_file read_elf(FILE *src);

void print_elf(Elf_file *f);

void free_elf(Elf_file *f);

#endif //ELF_PATCHER_ELF_FILE_H
