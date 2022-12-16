//
// Created by sbancuz on 12/16/22.
//

#include "headers/elf_header.h"
#include "headers/macros.h"

// https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#File_header
Elf64_Ehdr read_elf_header(FILE *src) {
    Elf64_Ehdr hdr = {0};

    // magic number 7F 45 4c 46
    read_bytes(src, hdr.e_ident[EI_MAG0], 4);

    // This byte is set to either 1 or 2 to signify 32- or 64-bit format, respectively.
    read_bytes(src, hdr.e_ident[EI_CLASS], 1);

    // This byte is set to either 1 or 2 to signify little or big endianness, respectively.
    read_bytes(src, hdr.e_ident[EI_DATA], 1);

    // Set to 1 for the original and current version of ELF.
    read_bytes(src, hdr.e_ident[EI_VERSION], 1);

    // Identifies the target operating system ABI.
    read_bytes(src, hdr.e_ident[EI_OSABI], 1);

    // Further specifies the ABI version.
    read_bytes(src, hdr.e_ident[EI_ABIVERSION], 1);

    // Reserved padding bytes.
    read_bytes(src, hdr.e_ident[EI_PAD], 7);

    // Identifies object file type.
    read_bytes(src, hdr.e_type, 2);

    // Specifies target instruction set architecture.
    read_bytes(src, hdr.e_machine, 2);

    // Set to 1 for the original version of ELF.
    read_bytes(src, hdr.e_version, 4);

    // This is the memory address of the entry point from where the process starts executing.
    // If the file doesn't have an associated entry point, then this holds zero.
    read_bytes(src, hdr.e_entry, sizeof(void *));

    // Points to the start of the program header table.
    read_bytes(src, hdr.e_phoff, sizeof(void *));

    // Points to the start of the section header table.
    read_bytes(src, hdr.e_shoff, sizeof(void *));

    // Interpretation of this field depends on the target architecture.
    read_bytes(src, hdr.e_flags, 4);

    // Contains the size of this header, normally 64 Bytes for 64-bit and 52 Bytes for 32-bit format.
    read_bytes(src, hdr.e_ehsize, 2);

    // Contains the size of a program header table entry.
    read_bytes(src, hdr.e_phentsize, 2);

    // Contains the number of entries in the program header table.
    read_bytes(src, hdr.e_phnum, 2);

    // Contains the size of a section header table entry.
    read_bytes(src, hdr.e_shentsize, 2);

    // Contains the number of entries in the section header table.
    read_bytes(src, hdr.e_shnum, 2);

    // Contains index of the section header table entry that contains the section names.
    read_bytes(src, hdr.e_shstrndx, 2);

    return hdr;
}

void print_elf_header(Elf64_Ehdr *hdr) {
    printf("File Header:\n");

    printf("\tMagic number: %2x %2x %2x %2x %2x %2x %2x %2x %2x 00 00 00 00 00 00 00\n",
           hdr->e_ident[EI_MAG0], hdr->e_ident[EI_MAG1], hdr->e_ident[EI_MAG2],
           hdr->e_ident[EI_MAG3], hdr->e_ident[EI_CLASS], hdr->e_ident[EI_DATA],
           hdr->e_ident[EI_VERSION], hdr->e_ident[EI_OSABI], hdr->e_ident[EI_ABIVERSION]
    );

    printf("\tAarch:        %s-bit\n", hdr->e_ident[EI_CLASS] == 1 ? "32" : "64");
    printf("\tEndianness:   %s\n", hdr->e_ident[EI_DATA] == 1 ? "LE" : "BE");
    printf("\tELF:          %x\n", hdr->e_ident[EI_VERSION]);
    printf("\tABI:          %s\n", abi_to_string(hdr->e_ident[EI_OSABI]));
    printf("\tABI Version:  %x\n",  hdr->e_ident[EI_ABIVERSION]);
    printf("\tFile Type:    %s\n", type_to_string(hdr->e_type));
    printf("\tMachine:      %s\n", machine_to_string(hdr->e_machine));
    printf("\tVersion:      %x\n", hdr->e_version);
    printf("\tEntry:        %lx\n", hdr->e_entry);
    printf("\tPhys. Off:    %lx\n", hdr->e_phoff);
    printf("\tSection Off:  %lx\n", hdr->e_shoff);
    printf("\tFlags:        0x%x\n", hdr->e_flags);
    printf("\tHeader size:  %hd\n", hdr->e_ehsize);
    printf("\tP_head size:  %hd\n", hdr->e_phentsize);
    printf("\tP_head entry: %hx\n", hdr->e_phnum);
    printf("\tS_head size:  %hd\n", hdr->e_shentsize);
    printf("\tS_head entry: %hx\n", hdr->e_shnum);
    printf("\tS_name index: %hx\n", hdr->e_shstrndx);
}

char *abi_to_string(int abi) {
    switch (abi) {
        case 0x00:
            return "System V";
        case 0x01:
            return "HP-UX";
        case 0x02:
            return "NetBSD";
        case 0x03:
            return "Linux";
        case 0x04:
            return "GNU Hurd";
        case 0x06:
            return "Solaris";
        case 0x07:
            return "AIX (Monterey)";
        case 0x08:
            return "IRIX";
        case 0x09:
            return "FreeBSD";
        case 0x0A:
            return "Tru64";
        case 0x0B:
            return "Novell Modesto";
        case 0x0C:
            return "OpenBSD";
        case 0x0D:
            return "OpenVMS";
        case 0x0E:
            return "NonStop Kernel";
        case 0x0F:
            return "AROS";
        case 0x10:
            return "FenixOS";
        case 0x11:
            return "Nuxi CloudABI";
        case 0x12:
            return "Stratus Technologies OpenVOS";
    }

    return "Invalid";
}

char *type_to_string(Elf64_Half type) {
    switch (type) {
        case ET_NONE:
            return "Unknown";
        case ET_REL:
            return "Relocatable file";
        case ET_EXEC:
            return "Executable file";
        case ET_DYN:
            return "Shared object";
        case ET_CORE:
            return "Core file";
        case ET_LOOS:
            return "Reserved inclusive range. Operating system specific";
        case ET_HIOS:
            return "Reserved inclusive range. Operating system specific";
        case ET_LOPROC:
            return "Reserved inclusive range. Processor specific";
        case ET_HIPROC:
            return "Reserved inclusive range. Processor specific";
    };

    return "Invalid";
}

char *machine_to_string(Elf64_Half machine) {
    // the list may be incomplete

    switch (machine) {
        case 0x00:
            return "No specific instruction set";
        case 0x01:
            return "AT&T WE 32100";
        case 0x02:
            return "SPARC";
        case 0x03:
            return "x86";
        case 0x04:
            return "Motorola 68000 (M68k)";
        case 0x05:
            return "Motorola 88000 (M88k)";
        case 0x06:
            return "Intel MCU";
        case 0x07:
            return "Intel 80860";
        case 0x08:
            return "MIPS";
        case 0x09:
            return "IBM System/370";
        case 0x0A:
            return "MIPS RS3000 Little-endian";
        case 0x0E:
            return "Hewlett-Packard PA-RISC";
        case 0x0F:
            return "Reserved for future use";
        case 0x13:
            return "Intel 80960";
        case 0x14:
            return "PowerPC";
        case 0x15:
            return "PowerPC (64-bit)";
        case 0x16:
            return "S390, including S390x";
        case 0x17:
            return "IBM SPU/SPC";
        case 0x24:
            return "NEC V800";
        case 0x25:
            return "Fujitsu FR20";
        case 0x26:
            return "TRW RH-32";
        case 0x27:
            return "Motorola RCE";
        case 0x28:
            return "Arm (up to Armv7/AArch32)";
        case 0x29:
            return "Digital Alpha";
        case 0x2A:
            return "SuperH";
        case 0x2B:
            return "SPARC Version 9";
        case 0x2C:
            return "Siemens TriCore embedded processor";
        case 0x2D:
            return "Argonaut RISC Core";
        case 0x2E:
            return "Hitachi H8/300";
        case 0x2F:
            return "Hitachi H8/300H";
        case 0x30:
            return "Hitachi H8S";
        case 0x31:
            return "Hitachi H8/500";
        case 0x32:
            return "IA-64";
        case 0x33:
            return "Stanford MIPS-X";
        case 0x34:
            return "Motorola ColdFire";
        case 0x35:
            return "Motorola M68HC12";
        case 0x36:
            return "Fujitsu MMA Multimedia Accelerator";
        case 0x37:
            return "Siemens PCP";
        case 0x38:
            return "Sony nCPU embedded RISC processor";
        case 0x39:
            return "Denso NDR1 microprocessor";
        case 0x3A:
            return "Motorola Star*Core processor";
        case 0x3B:
            return "Toyota ME16 processor";
        case 0x3C:
            return "STMicroelectronics ST100 processor";
        case 0x3D:
            return "Advanced Logic Corp. TinyJ embedded processor family";
        case 0x3E:
            return "AMD x86-64";
        case 0x3F:
            return "Sony DSP Processor";
        case 0x40:
            return "Digital Equipment Corp. PDP-10";
        case 0x41:
            return "Digital Equipment Corp. PDP-11";
        case 0x42:
            return "Siemens FX66 microcontroller";
        case 0x43:
            return "STMicroelectronics ST9+ 8/16 bit microcontroller";
        case 0x44:
            return "STMicroelectronics ST7 8-bit microcontroller";
        case 0x45:
            return "Motorola MC68HC16 Microcontroller";
        case 0x46:
            return "Motorola MC68HC11 Microcontroller";
        case 0x47:
            return "Motorola MC68HC08 Microcontroller";
        case 0x48:
            return "Motorola MC68HC05 Microcontroller";
        case 0x49:
            return "Silicon Graphics SVx";
        case 0x4A:
            return "STMicroelectronics ST19 8-bit microcontroller";
        case 0x4B:
            return "Digital VAX";
        case 0x4C:
            return "Axis Communications 32-bit embedded processor";
        case 0x4D:
            return "Infineon Technologies 32-bit embedded processor";
        case 0x4E:
            return "Element 14 64-bit DSP Processor";
        case 0x4F:
            return "LSI Logic 16-bit DSP Processor";
        case 0x8C:
            return "TMS320C6000 Family";
        case 0xAF:
            return "MCST Elbrus e2k";
        case 0xB7:
            return "Arm 64-bits (Armv8/AArch64)";
        case 0xDC:
            return "Zilog Z80";
        case 0xF3:
            return "RISC-V";
        case 0xF7:
            return "Berkeley Packet Filter";
        case 0x101:
            return "WDC 65C816";
    }

    return "Not yet assigned";
}