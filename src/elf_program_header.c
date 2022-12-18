//
// Created by sbancuz on 12/16/22.
//

#include <stdlib.h>
#include "headers/elf_program_header.h"

#include "headers/macros.h"

// https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#Program_header
ElfW(Phdr) read_program_header(FILE *src) {
    ElfW(Phdr) hdr = {0};

    // Identifies the type of the segment.
    read_bytes(src, hdr.p_type, 4);

#if defined(__LP64__)
    // Segment-dependent flags (position for 64-bit structure).
    read_bytes(src, hdr.p_flags, 4);
#endif
    // Offset of the segment in the file image.
    read_bytes(src, hdr.p_offset, ElfWs);

    // Virtual address of the segment in memory.
    read_bytes(src, hdr.p_vaddr, ElfWs);

    // On systems where physical address is relevant, reserved for segment's physical address.
    read_bytes(src, hdr.p_paddr, ElfWs);

    // Size in bytes of the segment in the file image. May be 0.
    read_bytes(src, hdr.p_filesz, ElfWs);

    // Size in bytes of the segment in memory. May be 0.
    read_bytes(src, hdr.p_memsz, ElfWs);
#if defined(__LP32__)
    // Segment-dependent flags (position for 64-bit structure).
    read_bytes(src, hdr.p_flags, 4);
#endif

    // 0 and 1 specify no alignment.
    // Otherwise, should be a positive, integral power of 2,
    // with p_vaddr equating p_offset modulus p_align.
    read_bytes(src, hdr.p_align, ElfWs);

    return hdr;
}

void print_program_header(ElfW(Phdr) *hdr) {
    printf("Program Header: \n");
    printf("\tSegment Type: %s\n", segment_type_to_str(hdr->p_type));
    printf("\tFlags:        %x\n", hdr->p_flags);
    printf("\tOffset:       %lx\n", hdr->p_offset);
    printf("\tVirt Addr:    %lx\n", hdr->p_vaddr);
    printf("\tPhys Addr:    %lx\n", hdr->p_paddr);
    printf("\tFile Size:    %ld\n", hdr->p_filesz);
    printf("\tMemory Size:  %ld\n", hdr->p_memsz);
    printf("\tAlignment:    %lx\n", hdr->p_align);
}

char *segment_type_to_str(ElfW(Word) typ) {
    switch (typ) {
        case PT_NULL:
            return "PT_NULL     - Program header table entry unused.";
        case PT_LOAD:
            return "PT_LOAD     - Loadable segment.";
        case PT_DYNAMIC:
            return "PT_DYNAMIC  - Dynamic linking information.";
        case PT_INTERP:
            return "PT_INTERP   - Interpreter information.";
        case PT_NOTE:
            return "PT_NOTE     - Auxiliary information.";
        case PT_SHLIB:
            return "PT_SHLIB    - Reserved.";
        case PT_PHDR:
            return "PT_PHDR     - Segment containing program header table itself.";
        case PT_TLS:
            return "PT_TLS      - Thread-Local Storage template.";
        case PT_LOOS:
            return "PT_LOOS     - Reserved inclusive range. Operating system specific.";
        case PT_HIOS:
            return "PT_HIOS     - Reserved inclusive range. Operating system specific.";
        case PT_LOPROC:
            return "PT_LOPROC   - Reserved inclusive range. Processor specific.";
        case PT_HIPROC:
            return "PT_HIPROC   - Reserved inclusive range. Processor specific.";
    }

    return "Invalid";
}