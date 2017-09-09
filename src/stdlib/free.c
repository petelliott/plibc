/*
free
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
#include "../malloc.h"


/*
    merges a block its next block.
    should only be called when both blocks are free
*/
void block_merge_next(struct block *mblock) {
    // accounting for padding between end of one block and the start of another
    mblock->len = (uint64_t)mblock->next - (uint64_t)mblock + mblock->next->len;
    mblock->next = mblock->next->next;
    if (mblock->next != NULL) {
        mblock->next->prev = mblock;
    }
}



void free (void *ptr) {
    if (ptr == NULL) {
        // free is required to handle NULL pointers;
        return;
    }

    struct block *mblock = ((struct block *) ptr) -1;
    // check that ptr came from malloc()
    if ((((long) mblock) ^ mblock->pos_mag) == MALLOC_MAG) {
        mblock->used = 0;

        if (mblock->next != NULL && !mblock->next->used) {
            block_merge_next(mblock);
        }

        if (mblock->prev != NULL && !mblock->prev->used) {
            block_merge_next(mblock->prev);
        }
    }
}
