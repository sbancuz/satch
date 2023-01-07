//
// Created by sbancuz on 12/17/22.
//

#ifndef ELF_PATCHER_ELF_SECTION_HEADER_H
#define ELF_PATCHER_ELF_SECTION_HEADER_H

#include <elf.h>
#include <bits/types/FILE.h>

#include "macros.h"
#include "structs.h"


void print_section_header(const ElfW_Shdr *hdr, const char *name);

ElfW_Shdr read_section_header(FILE *src, ElfW(Xword) off);

char *section_type_to_string(ElfW(Word) type);

char *section_flags_to_string(ElfW(Xword) flags);

#endif //ELF_PATCHER_ELF_SECTION_HEADER_H
