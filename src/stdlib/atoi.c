/*
atoi funtion that converts an ascii representation of an int to a c one
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


int atoi(const char *nptr) {
    int neg = 0;
    if (*nptr == '-') {
        neg = 1;
        ++nptr;
    }

    int res = 0;

    while (*nptr != 0) {
        res *= 10;
        res += *nptr - '0';
        ++nptr;
    }
    return (neg)? -res : res;
}
