#ifndef PLIBC_IO
#define PLIBC_IO

#include <stdint.h>

#define PLIBC_BUFF_SIZE 4096

struct plibc_file {
    int filed;
    char *writebuffer;
    size_t write_idx;
};

#endif
