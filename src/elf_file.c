//
// Created by sbancuz on 12/16/22.
//

#include "headers/elf_file.h"

Elf_file read_elf(FILE *src) {
    Elf_file file = {
            .e_hdr = read_elf_header(src),
            .p_hdr = read_program_header(src),
    };

    return file;
}

void print_elf(Elf_file *f) {
    print_elf_header(&f->e_hdr);
    printf("\n");
    print_program_header(&f->p_hdr);
    printf("\n");
}
