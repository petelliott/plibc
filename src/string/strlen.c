/*
strlen
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


size_t strlen(const char *str) {
    size_t align = 0;

    while ((unsigned long)(str+align) % sizeof(long) != 0) {
        align++;
        if (str[align] == 0) {
            return align;
        }
    }
    
    // set magic numbers for hasless based on system word size
    unsigned long highword;
    unsigned long lowword;
    if (sizeof(long) == 4) {
        highword = 0x80808080UL;
        lowword = 0x01010101UL;
    } else if (sizeof(long) == 8) {
        highword = 0x8080808080808080UL;
        lowword = 0x0101010101010101UL;
    }

    unsigned long *long_ptr = (unsigned long *) (str + align);

    // hasless: https://graphics.stanford.edu/~seander/bithacks.html#ZeroInWord
    unsigned long word;
    do {
        word = *(long_ptr++);
    } while(((word - lowword) & ~word & highword) == 0);

    // check which byte was zero
    for (size_t j = 0; j < sizeof(long); ++j) {
        if ((word & (0xff << 8*j)) == 0) {
            return (unsigned long)(long_ptr) - (unsigned long)(str) + j;
        }
    }

    // shouldn't happen
    return 0;
}
