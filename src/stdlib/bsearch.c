/*
bsearch
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


void *bsearch(
    const void *key, const void *base,
    size_t nmemb, size_t size,
    int (*compar)(const void *, const void *))
{
    size_t lo = 0;
    size_t hi = nmemb;

    while(lo < hi) {
        size_t center = (lo+hi)/2;
        const void *cptr = (const void *)((const char *)base + (center*size));
        int cmp = (*compar)(cptr, key);

        if (cmp == 0) {
            return (void *)cptr;
        } else if (cmp == 1) {
            hi = center;
        } else if (cmp == -1) {
            lo = center;
        }
    }

    return NULL;
}
