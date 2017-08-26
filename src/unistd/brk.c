/*
unistd.h brk syscall and sbrk function
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
#include <unistd.h>
#include "../syscall.h"

void * currbrk = 0;


int brk (void *addr) {
    // the brk syscall and function call return different things
    currbrk = (void *) _plibc_syscall(12, addr);
    if (currbrk < addr) {
        //TODO: set errno to ENOMEM
        return -1;
    }
    return 0;
}


void *sbrk (intptr_t delta) {
    if (currbrk == 0) {
        brk(NULL);
    }

    if (delta == 0) { // avoid a syscall if possible
        return currbrk;
    }

    void * oldbrk = currbrk;
    brk(currbrk+delta);
    return oldbrk;
}
