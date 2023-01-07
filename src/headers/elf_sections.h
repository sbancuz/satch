//
// Created by sbancuz on 12/22/22.
//

#ifndef ELF_PATCHER_ELF_SECTIONS_H
#define ELF_PATCHER_ELF_SECTIONS_H

#include <stddef.h>
#include <bits/types/FILE.h>

#include "macros.h"
#include "structs.h"

ElfW_Sec get_section(FILE *src, const ElfW(Shdr) *hdr);

ElfW_Note get_section_note(FILE *src, ElfW(Off) off);

ElfW(Sym) get_section_symtab(FILE *src, ElfW(Off) off);

void print_section(const Elf_file *f, size_t i);

void free_section(ElfW_Sec *sec, const ElfW(Shdr) *hdr);

char *get_strtab_index(char *str, size_t i, size_t len);

void print_symtab(ElfW(Sym) *sym, char *name);

void print_note(const ElfW_Note *note, const char *name);

char *symtab_bind_to_string(const unsigned char info);

char *symtab_type_to_string(const unsigned char info);

char *symtab_visibility_to_string(const ElfW(Section) vis);

#endif //ELF_PATCHER_ELF_SECTIONS_H
