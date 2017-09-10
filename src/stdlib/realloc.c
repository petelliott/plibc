/*
realloc
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
#include <stdlib.h>
#include <string.h>
#include "../memory.h"
#include "unistd.h"


void *realloc(void *ptr, size_t size) {
    struct block *mblock = ((struct block *) ptr) -1;

    if (ptr == NULL) {
        return malloc(size);
    }

    if ((((long) mblock) ^ mblock->pos_mag) != MALLOC_MAG) {
        return NULL;
    }

    if (size < mblock->len) {
        shrink_block(mblock, size);
        return ptr;
    }else if (mblock->next == NULL && mblock == base) {
        sbrk(size - mblock->len);
        mblock->len = size;
        return ptr;
    } else if (mblock->next->used == 0 && (long)mblock->next - (long)mblock + mblock->next->len >= size) {
        block_merge_next(mblock);
        return ptr;
    } else {
        void *new_ptr = malloc(size);
        memcpy(new_ptr, ptr, mblock->len);
        free(ptr);
        return new_ptr;
    }

}
