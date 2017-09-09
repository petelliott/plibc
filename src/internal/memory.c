/*
memory management functions
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
#include "../memory.h"
#include <unistd.h>
#include "../align.h"


struct block *base = NULL;


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
    splits a given block in two if possible,
    the first one being size.
    returns 1 if split 0 if not
*/
int shrink_block(struct block *mblock, size_t size) {
    if (mblock->len - size >= MIN_SPLIT_SIZE) {
        struct block *block_new = (struct block *)((char *)(mblock+1) + size);
        block_new = (struct block *)((char *)block_new + align8(block_new));

        block_new->prev    = mblock;
        block_new->next    = mblock->next;
        block_new->pos_mag = MALLOC_MAG ^ ((long) block_new);
        block_new->len     = (uint64_t)mblock + mblock->len - (uint64_t)block_new;
        block_new->used    = 0;

        if (mblock == base) {
            base = block_new;
        }

        if (mblock->next != NULL) {
            mblock->next->prev = block_new;
        }
        mblock->next = block_new;
        mblock->len = size;
        return 1;
    }
    return 0;
}


/*
    finds a free block of at least size.
*/
struct block *get_free_block(size_t size) {
    struct block *curr = base;
    while (curr != NULL) {
        if (!curr->used && curr->len >= size) {
            shrink_block(curr, size);
            curr->used = 1;
            return curr;
        }
        curr = curr->prev;
    }
    return NULL;
}


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
