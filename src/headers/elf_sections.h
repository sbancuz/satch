//
// Created by sbancuz on 12/22/22.
//

#ifndef ELF_PATCHER_ELF_SECTIONS_H
#define ELF_PATCHER_ELF_SECTIONS_H

#include "elf.h"

#include <stddef.h>
#include <bits/types/FILE.h>
#include "macros.h"

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
} ElfW_Sec;

ElfW_Sec get_section(FILE *src, const ElfW(Shdr) *hdr);

ElfW_Note get_section_note(FILE *src, ElfW(Off) off);

ElfW(Sym) get_section_symtab(FILE *src, ElfW(Off) off);

void free_section(ElfW_Sec *sec, const ElfW(Shdr) *hdr);

// TODO: find a way not to use 3 params but just use ElfW_Shd
void print_section(const ElfW_Sec *sec, const ElfW(Shdr) *hdr, const char *name);

void print_note(const ElfW_Note *note, const char *name);

char *symtab_bind_to_string(const unsigned char info);

char *symtab_type_to_string(const unsigned char info);

char *symtab_visibility_to_string(const ElfW(Section) vis);

char *get_shstrtab_name(FILE *src, ElfW(Off) off);

#endif //ELF_PATCHER_ELF_SECTIONS_H
