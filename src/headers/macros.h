//
// Created by sbancuz on 12/16/22.
//

#ifndef ELF_PATCHER_MACROS_H
#define ELF_PATCHER_MACROS_H

#define read_bytes(f, dst, n) fread(&dst, n, 1, f)
#define htx "%c%c%c%c"

#if defined(__LP64__)
#define ElfW(type) Elf64_ ## type
#define ELFW(type) ELF64_ ## type
#define ElfWs   8
#else
#define ElfW(type) Elf32_ ## type
#define ELFW(type) ELF32_ ## type
#define ElfWs   4
#endif


#endif //ELF_PATCHER_MACROS_H
