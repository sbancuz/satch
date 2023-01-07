//
// Created by sbancuz on 12/16/22.
//

#include <stdlib.h>
#include "headers/elf_program_header.h"

#include "headers/macros.h"

// https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#Program_header
ElfW(Phdr) read_program_header(FILE *src, const ElfW(Off) off) {
    ElfW(Phdr) hdr = {0};

		fseek(src, off, SEEK_SET);

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
		char *f = pheader_flags_to_string(hdr->p_flags);
		printf("%16s  0x%016lx 0x%016lx 0x%016lx\n %16s 0x%016lx 0x%016lx %4s  0x%010lx\n",
		       segment_type_to_str(hdr->p_type), hdr->p_offset, hdr->p_vaddr,
	       hdr->p_paddr, "", hdr->p_filesz, hdr->p_memsz, f,
	       hdr->p_align);
		free(f);
}

char *segment_type_to_str(ElfW(Word) typ) {
    switch (typ) {
        case PT_NULL:
            return "NULL";
        case PT_LOAD:
            return "LOAD";
        case PT_DYNAMIC:
            return "DYNAMIC";
        case PT_INTERP:
            return "INTERP";
        case PT_NOTE:
            return "NOTE";
        case PT_SHLIB:
            return "SHLIB";
        case PT_PHDR:
            return "PHDR";
        case PT_TLS:
            return "TLS";
        case PT_LOOS:
            return "LOOS";
        case PT_HIOS:
            return "HIOS";
        case PT_LOPROC:
            return "LOPROC";
        case PT_HIPROC:
            return "HIPROC";
	    case PT_GNU_PROPERTY:
		    return "GNU_PROPERTY";
	    case PT_GNU_STACK:
		    return "GNU_STACK";
	    case PT_GNU_EH_FRAME:
		    return "GNU_EH_FRAME";
	    case PT_GNU_RELRO:
		    return "GNU_RELRO";
    }

    return "Invalid";
}

char *pheader_flags_to_string(ElfW(Xword) flags) {
		char *ret = calloc(1, 5);
		if (flags & PF_X) ret[0] = 'X'; else ret[0] = ' ';
		if (flags & PF_W) ret[1] = 'W'; else ret[1] = ' ';
		if (flags & PF_R) ret[2] = 'R'; else ret[2] = ' ';
		if (flags & PF_MASKPROC) ret[3] = 'U'; else ret[3] = ' ';

		return ret;
}
