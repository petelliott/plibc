/*
malloc and free 
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
#include <stdint.h>
#include <unistd.h>

#define MALLOC_MAG 0x8a05e5ad623cc4e

#define align8(i) ((8 - (((long) i) % 8)) % 8)

struct block {
    struct block *prev;
    struct block *next;
    uint64_t pos_mag; // position dependant magic number
    uint32_t len;     // length of the block
    uint32_t used;    // this could be one byte but we need to preserve 8 byte alignment
};

struct block *base = NULL; // the tail of the blocks linked list


/*
    expands the data segment and inserts a new block of size
    used when no freed block can be found
*/
struct block *push_block(size_t size) {
    void *start = sbrk(0);
    // we need to make sure that our blocks are aligned.
    // the malloc definion guarantees that the pointer is aligned for any built in type.
    // 8 bytes on 64 bit systems
    long align = align8(start);

    long alloc_size = align + sizeof(struct block) + size;
    sbrk(alloc_size);

    struct block *new_block = (struct block *)(((char *)start) + align);

    if (base != NULL) {
        base->next = new_block;
    }

    new_block->prev    = base;
    new_block->next    = NULL;
    new_block->pos_mag = MALLOC_MAG ^ ((long) new_block);
    new_block->len     = size;
    new_block->used    = 1;

    base = new_block;

    return new_block;
}


/*
    finds a free block of at least size.
    TODO: implement block splitting
*/
struct block *get_free_block(size_t size) {
    struct block *curr = base;
    while (curr != NULL) {
        if (!curr->used && curr->len >= size) {
            curr->used = 1;
            return curr;
        }
        curr = curr->prev;
    }
    return NULL;
}


void *malloc (size_t size) {
    struct block* mblock;

    if (size == 0) {
        return NULL;
    }

    if (base == NULL) {
        mblock = push_block(size);
        return mblock + 1; // skip to the useable memory
    }

    mblock = get_free_block(size);
    if (mblock == NULL) {
        mblock = push_block(size);
    }
    return mblock + 1; // skip to the useable memory
}


/*
    merges a block its next block.
    should only be called when both blocks are free
*/
void block_merge_next(struct block *mblock) {
    // accounting for padding between end of one block and the start of another
    mblock->len = (long)mblock->next - (long)mblock + mblock->next->len;
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
