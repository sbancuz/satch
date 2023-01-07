//
// Created by sbancuz on 1/1/23.
//

#ifndef ELF_PATCHER_STRUCTS_H
#define ELF_PATCHER_STRUCTS_H

#include <stddef.h>
#include "macros.h"
#include "elf.h"
#include "../../thirdparty/elf_commons.h"

typedef struct elfw_note {
    size_t namesz;
    size_t descsz;
    size_t type;
    char *name;
    char *desc;
} ElfW_Note;

typedef union elfw_sec {
    ElfW_Note note;
    ElfW(Sym) *sym;
    char *strtab;
} ElfW_Sec;

typedef struct elfw_shdr {
    ElfW(Shdr) hdr;
    ElfW_Sec section;
} ElfW_Shdr;

typedef struct elf_fil {
    ElfW(Ehdr) e_hdr;
    ElfW(Phdr) p_hdr;
    ElfW_Shdr *s_hdrs;
} Elf_file;

#endif //ELF_PATCHER_STRUCTS_H
