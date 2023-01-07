//
// Created by sbancuz on 12/16/22.
//
#include <stdlib.h>
#include <stdio.h>
#include "headers/elf_file.h"
#include "headers/elf_sections.h"
#include "headers/elf_section_header.h"
#include "headers/elf_program_header.h"
#include "headers/elf_header.h"

Elf_file read_elf(FILE *src) {
    Elf_file file = {
            .e_hdr = read_elf_header(src),
            .p_hdr = read_program_header(src),
    };

    file.s_hdrs = calloc(file.e_hdr.e_shnum, sizeof(ElfW_Shdr));
    for (int i = 0; i < file.e_hdr.e_shnum; i++) {
        file.s_hdrs[i] = read_section_header(src, file.e_hdr.e_shoff + file.e_hdr.e_shentsize * i);
    }

    for (int i = 0; i < file.e_hdr.e_shnum; i++) {
        file.s_hdrs[i].section = get_section(src, &file.s_hdrs[i].hdr);
    }

    return file;
}

void print_elf(Elf_file *f) {
    print_elf_header(&f->e_hdr);
    printf("\n");
    print_program_header(&f->p_hdr);
    printf("\n");

    printf("  [N°] Name              Type             Address           Offset\n");
    printf("       Size              EntSize          Flag   Link  Info  Allin\n");

    for (int i = 0; i < f->e_hdr.e_shnum; i++) {
        printf("  [%2d]", i);
        print_section_header(&f->s_hdrs[i],
                             f->s_hdrs[f->e_hdr.e_shstrndx].section.strtab + f->s_hdrs[i].hdr.sh_name);
    }
    printf("\n");

    for (int i = 0; i < f->e_hdr.e_shnum; i++) {
        print_section(f, i);
    }
}

void free_elf(Elf_file *f) {
    for (int i = 0; i < f->e_hdr.e_shnum; i++) {
        free_section(&f->s_hdrs[i].section, &f->s_hdrs[i].hdr);
    }
    free(f->s_hdrs);
}