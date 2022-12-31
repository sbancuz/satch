//
// Created by sbancuz on 12/17/22.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/elf_section_header.h"

void print_section_header(const ElfW_Shdr *s_hdr) {
    char *flags = section_flags_to_string(s_hdr->hdr.sh_flags);
    printf(" %16s  %16s  %016lx  %08lx\n",
           s_hdr->name, section_type_to_string(s_hdr->hdr.sh_type), s_hdr->hdr.sh_addr, s_hdr->hdr.sh_offset);
    printf("       %016lx  %016lx  %3s %6d %6d %5ld\n",
           s_hdr->hdr.sh_size, s_hdr->hdr.sh_entsize, flags,
           s_hdr->hdr.sh_link, s_hdr->hdr.sh_info,
           s_hdr->hdr.sh_addralign);
    free(flags);
}

ElfW_Shdr read_section_header(FILE *src, ElfW(Xword) off) {
    ElfW_Shdr s_hdr = {
            .hdr = {0},
            .name = "NULL\0",
    };

    fseek(src, off, SEEK_SET);

    // An offset to a string in the .shstrtab section that represents the name of this section.
    read_bytes(src, s_hdr.hdr.sh_name, 4);

    // Identifies the type of this header.
    read_bytes(src, s_hdr.hdr.sh_type, 4);

    // Identifies the attributes of the section.
    read_bytes(src, s_hdr.hdr.sh_flags, ElfWs);

    // Virtual address of the section in memory, for sections that are loaded.
    read_bytes(src, s_hdr.hdr.sh_addr, ElfWs);

    // Offset of the section in the file image.
    read_bytes(src, s_hdr.hdr.sh_offset, ElfWs);

    // Size in bytes of the section in the file image. May be 0.
    read_bytes(src, s_hdr.hdr.sh_size, ElfWs);

    // Contains the section index of an associated section.
    read_bytes(src, s_hdr.hdr.sh_link, 4);

    // Contains extra information about the section.
    read_bytes(src, s_hdr.hdr.sh_info, 4);

    // Contains the required alignment of the section. This field must be a power of two.
    read_bytes(src, s_hdr.hdr.sh_addralign, ElfWs);

    // Contains the size, in bytes, of each entry, for sections that contain fixed-size entries.
    // Otherwise, this field contains zero.
    read_bytes(src, s_hdr.hdr.sh_entsize, ElfWs);

    return s_hdr;
}

char *section_type_to_string(ElfW(Word) type) {
    // NOTE: This may not be exhaustive

    switch (type) {
        case SHT_NULL:
            return "NULL";
        case SHT_PROGBITS:
            return "PROGBITS";
        case SHT_SYMTAB:
            return "SYMTAB";
        case SHT_STRTAB:
            return "STRTAB";
        case SHT_RELA:
            return "RELA";
        case SHT_HASH:
            return "HASH";
        case SHT_DYNAMIC:
            return "DYNAMIC";
        case SHT_NOTE:
            return "NOTE";
        case SHT_NOBITS:
            return "NOBITS";
        case SHT_REL:
            return "REL";
        case SHT_SHLIB:
            return "SHLIB";
        case SHT_DYNSYM:
            return "DYNSYM";
        case SHT_INIT_ARRAY:
            return "INIT_ARRAY";
        case SHT_FINI_ARRAY:
            return "FINI_ARRAY";
        case SHT_PREINIT_ARRAY:
            return "REINIT_ARRAY";
        case SHT_GROUP:
            return "GROUP";
        case SHT_SYMTAB_SHNDX:
            return "SYMTAB_SHNDX";
        case SHT_NUM:
            return "NUM";
        case SHT_LOOS:
            return "LOOS";
    }

    return "UNK";
}

char *section_flags_to_string(ElfW(Xword) flags) {
    char *str = calloc(20, 1);
    int i = 0;

    //@formatter:off
    if (flags & SHF_WRITE)           { str[i] = 'W'; i++; }
    if (flags & SHF_ALLOC)           { str[i] = 'A'; i++; }
    if (flags & SHF_EXECINSTR)       { str[i] = 'X'; i++; }
    if (flags & SHF_MERGE)           { str[i] = 'M'; i++; }
    if (flags & SHF_STRINGS)         { str[i] = 'S'; i++; }
    if (flags & SHF_INFO_LINK)       { str[i] = 'I'; i++; }
    if (flags & SHF_LINK_ORDER)      { str[i] = 'L'; i++; }
    if (flags & SHF_OS_NONCONFORMING){ str[i] = 'O'; i++; }
    if (flags & SHF_GROUP)           { str[i] = 'G'; i++; }
    if (flags & SHF_TLS)             { str[i] = 'T'; i++; }
    if (flags & SHF_COMPRESSED)      { str[i] = 'C'; i++; }
    if (flags & SHF_EXCLUDE)         { str[i] = 'E'; i++; }
    //@formatter:on
    str[i] = '\0';

    return str;
}