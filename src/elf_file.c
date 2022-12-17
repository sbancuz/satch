//
// Created by sbancuz on 12/16/22.
//

#include "headers/elf_file.h"

Elf_file read_elf(FILE *src) {
    Elf_file file = {
            .e_hdr = read_elf_header(src),
            .p_hdr = read_program_header(src),
    };
    file.s_hdrs = calloc(file.e_hdr.e_shnum, sizeof(ElfW(Shdr)));
    for (int i = 0; i < file.e_hdr.e_shnum; i++){
        file.s_hdrs[i] = read_section_header(src, file.e_hdr.e_shoff + file.e_hdr.e_shentsize * i);
    }

    return file;
}

void print_elf(Elf_file *f) {
    print_elf_header(&f->e_hdr);
    printf("\n");
    print_program_header(&f->p_hdr);
    printf("\n");
    for (int i = 0; i < f->e_hdr.e_shnum; i++){
        print_section_header(&f->s_hdrs[i]);
        printf("\n");
    }
    printf("\n");
}
