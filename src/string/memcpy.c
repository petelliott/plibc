/*
memcpy
the _plibc_syscall function that makes syscalls available in c
Copyright (C) 2017  Peter Elliott

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <string.h>

#define align8(i) ((8 - (((long) i) % 8)) % 8)


/*
    pretty much just an inefficent memcpy
    copys byte by byte
*/
void _byte_cpy(char *dest, const char *src, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        dest[i] = src[i];
    }
}


void *memcpy(void *dest, const void *src, size_t n) {
    size_t align = align8((unsigned long) dest);

    _byte_cpy(dest, src, align);
    n -= align;

    long *ldest = (long *) ((char *)dest + align);
    long *lsrc  = (long *) ((char *)src + align);

    size_t i;
    for (i = 0; i < n/8; ++i) {
        ldest[i] = lsrc[i];
    }
    n -= 8*i;

    _byte_cpy((char *)(ldest + i), (char *)(lsrc + i), n);

    return dest;
}
