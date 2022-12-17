//
// Created by sbancuz on 12/17/22.
//

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "headers/elf_section_header.h"

void print_section_header(ElfW(Shdr) *hdr) {
    printf(" %016x  %16s  %016lx  %08lx\n",
           hdr->sh_name, section_type_to_string(hdr->sh_type), hdr->sh_addr, hdr->sh_offset);
    printf("       %016lx  %016lx  %3s %6d %6d %5ld\n",
           hdr->sh_size, hdr->sh_entsize, section_flags_to_string(hdr->sh_flags), hdr->sh_link, hdr->sh_info,
           hdr->sh_addralign);
}

ElfW(Shdr) read_section_header(FILE *src, ElfW(Off) off) {
    ElfW(Shdr) hdr = {0};

    fseek(src, off, SEEK_SET);

    // An offset to a string in the .shstrtab section that represents the name of this section.
    read_bytes(src, hdr.sh_name, 4);

    // Identifies the type of this header.
    read_bytes(src, hdr.sh_type, 4);

    // Identifies the attributes of the section.
    read_bytes(src, hdr.sh_flags, ElfWs);

    // Virtual address of the section in memory, for sections that are loaded.
    read_bytes(src, hdr.sh_addr, ElfWs);

    // Offset of the section in the file image.
    read_bytes(src, hdr.sh_offset, ElfWs);

    // Size in bytes of the section in the file image. May be 0.
    read_bytes(src, hdr.sh_size, ElfWs);

    // Contains the section index of an associated section.
    read_bytes(src, hdr.sh_link, 4);

    // Contains extra information about the section.
    read_bytes(src, hdr.sh_info, 4);

    // Contains the required alignment of the section. This field must be a power of two.
    read_bytes(src, hdr.sh_addralign, ElfWs);

    // Contains the size, in bytes, of each entry, for sections that contain fixed-size entries.
    // Otherwise, this field contains zero.
    read_bytes(src, hdr.sh_entsize, ElfWs);

    return hdr;
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
    char str[11] = "\0";
    if (flags & SHF_WRITE) strcat(str, "W");
    if (flags & SHF_ALLOC) strcat(str, "A");
    if (flags & SHF_EXECINSTR) strcat(str, "X");
    if (flags & SHF_MERGE) strcat(str, "M");
    if (flags & SHF_STRINGS) strcat(str, "S");
    if (flags & SHF_INFO_LINK) strcat(str, "I");
    if (flags & SHF_LINK_ORDER) strcat(str, "L");
    if (flags & SHF_OS_NONCONFORMING) strcat(str, "O");
    if (flags & SHF_GROUP) strcat(str, "G");
    if (flags & SHF_TLS) strcat(str, "T");
    if (flags & SHF_EXCLUDE) strcat(str, "E");
    if (flags & SHF_COMPRESSED) strcat(str, "C");
    str[strlen(str) - 3] = '\0';

    char *ret = malloc(strlen(str));
    strcpy(ret, str);
    return ret;
}