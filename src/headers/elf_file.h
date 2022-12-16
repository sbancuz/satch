//
// Created by sbancuz on 12/16/22.
//

#ifndef ELF_PATCHER_ELF_FILE_H
#define ELF_PATCHER_ELF_FILE_H

#include <elf.h>
#include <bits/types/FILE.h>

typedef struct elf_fil {
    Elf64_Ehdr e_hdr;
    Elf64_Phdr p_hdr;
} Elf_file;

Elf_file read_elf(FILE * src);

void print_elf(Elf_file *f);

#endif //ELF_PATCHER_ELF_FILE_H
