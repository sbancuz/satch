//
// Created by sbancuz on 12/17/22.
//

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "headers/elf_section_header.h"

void print_section_header(ElfW(Shdr) *hdr) {
    printf("Section Header:\n");

    printf("\tString off:   %x\n", hdr->sh_name);
    printf("\tType:         %s\n", section_type_to_string(hdr->sh_type));
    printf("\tFlags:        %s\n", section_flags_to_string(hdr->sh_flags));
    printf("\tMem V_addr:   %lx\n", hdr->sh_addr);
    printf("\tSection off:  %lx\n", hdr->sh_offset);
    printf("\tSection size: %lx\n", hdr->sh_size);
    printf("\tSection index:%x\n", hdr->sh_link);
    printf("\tExtra info:   %lx\n", hdr->sh_addralign);
    printf("\tFix sz size:  %lx\n", hdr->sh_entsize);
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
            return "Section header table entry unused";
        case SHT_PROGBITS:
            return "Program data";
        case SHT_SYMTAB:
            return "Symbol table";
        case SHT_STRTAB:
            return "String table";
        case SHT_RELA:
            return "Relocation entries with addends";
        case SHT_HASH:
            return "Symbol hash table";
        case SHT_DYNAMIC:
            return "Dynamic linking information";
        case SHT_NOTE:
            return "Notes";
        case SHT_NOBITS:
            return "Program space with no data (bss)";
        case SHT_REL:
            return "Relocation entries, no addends";
        case SHT_SHLIB:
            return "Reserved";
        case SHT_DYNSYM:
            return "Dynamic linker symbol table";
        case SHT_INIT_ARRAY:
            return "Array of constructors";
        case SHT_FINI_ARRAY:
            return "Array of destructors";
        case SHT_PREINIT_ARRAY:
            return "Array of pre-constructors";
        case SHT_GROUP:
            return "Section group";
        case SHT_SYMTAB_SHNDX:
            return "Extended section indices";
        case SHT_NUM:
            return "Number of defined types.";
        case SHT_LOOS:
            return "Start OS-specific.";
    }

    return "Unknown";
}

char *section_flags_to_string(ElfW(Xword) flags) {
    char str[1024] = "\0";
    if (flags & SHF_WRITE) strcat(str, "Writable, ");
    if (flags & SHF_ALLOC) strcat(str, "Occupies memory during execution, ");
    if (flags & SHF_EXECINSTR) strcat(str, "Executable, ");
    if (flags & SHF_MERGE) strcat(str, "Might be merged, ");
    if (flags & SHF_STRINGS) strcat(str, "Contains null-terminated strings, ");
    if (flags & SHF_INFO_LINK) strcat(str, "'sh_info' contains SHT index, ");
    if (flags & SHF_LINK_ORDER) strcat(str, "Preserve order after combining, ");
    if (flags & SHF_OS_NONCONFORMING) strcat(str, "Non-standard OS specific handling required, ");
    if (flags & SHF_GROUP) strcat(str, "Section is member of a group, ");
    if (flags & SHF_TLS) strcat(str, "Section hold thread-local data, ");
    if (flags & SHF_MASKOS) strcat(str, "OS-specific, ");
    if (flags & SHF_MASKPROC) strcat(str, "Processor-specific, ");
    if (flags & SHF_ORDERED) strcat(str, "Special ordering requirement (Solaris), ");
    if (flags & SHF_EXCLUDE) strcat(str, "Section is excluded unless referenced or allocated (Solaris), ");
    str[strlen(str) - 3] = '\0';

    char * ret = malloc(strlen(str));
    strcpy(ret, str);
    return ret;
}