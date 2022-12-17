#include <stdio.h>
#include "headers/elf_file.h"

int main() {
    FILE *f = NULL;
    const char *filename = "./../test";

    if (!(f = fopen(filename, "rb"))) {
        fprintf(stderr, "Failed to open the src file\n");
    }

    Elf_file e_file = read_elf(f);
    print_elf(&e_file);

    return 0;
}
