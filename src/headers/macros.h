//
// Created by sbancuz on 12/16/22.
//

#ifndef ELF_PATCHER_MACROS_H
#define ELF_PATCHER_MACROS_H

#define read_bytes(f, dst, n) fread(&dst, n, 1, f)
#define htx "%c%c%c%c"

#endif //ELF_PATCHER_MACROS_H
