/*
memset
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
#include "../align.h"


void _byte_set(char *dest, int ch, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        dest[i] = ch;
    }
}


void *memset(void *dest, int ch, size_t n) {
    size_t align = align8(dest);

    _byte_set(dest, ch, align);
    n -= align;

    long *ldest = (long *)((char *)dest + align);
    long lch    = ch;
    lch |= lch << 8;
    lch |= lch << 16;
    lch |= lch << 32;

    size_t i;
    for (i = 0; i < n/8; ++i) {
        ldest[i] = lch;
    }
    n -= 8*i;

    _byte_set((char *)(ldest + i), ch, n);

    return dest;
}
