//
// Created by sbancuz on 12/16/22.
//

#ifndef ELF_PATCHER_ELF_PROGRAM_HEADER_H
#define ELF_PATCHER_ELF_PROGRAM_HEADER_H

#include <stdio.h>
#include "macros.h"
#include "structs.h"

ElfW(Phdr) read_program_header(FILE *src, const ElfW(Off) off);

void print_program_header(ElfW(Phdr) *src);

char *segment_type_to_str(ElfW(Word) typ);

char *pheader_flags_to_string(ElfW(Xword) flags);

#endif //ELF_PATCHER_ELF_PROGRAM_HEADER_H
