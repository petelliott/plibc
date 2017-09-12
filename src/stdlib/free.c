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
#include "../memory.h"


void free (void *ptr) {
    if (ptr == NULL) {
        // free is required to handle NULL pointers;
        return;
    }

    struct block *mblock = ((struct block *) ptr) -1;
    // check that ptr came from malloc()
    if (is_mem_block(mblock)) {
        mblock->used = 0;

        if (mblock->next != NULL && !mblock->next->used) {
            block_merge_next(mblock);
        }

        if (mblock->prev != NULL && !mblock->prev->used) {
            block_merge_next(mblock->prev);
        }
    }
}
