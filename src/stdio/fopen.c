/*
fopen <stdio.h>
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
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../plibc_io.h"


// TODO: buffering
FILE *fopen(const char *path, const char *mode) {
    struct plibc_file *fil = malloc(sizeof(FILE));
    int unistd_mode = 0;

    if (mode[0] == 'r') {
        unistd_mode = O_RDONLY;
    } else if (mode[0] == 'w') {
        unistd_mode = O_WRONLY;
    }

    if (mode[1] == '+') {
        unistd_mode = O_RDWR;
    }

    if (mode[0] == 'a') {
        unistd_mode |= O_APPEND;
    }

    fil->filed = open(path, unistd_mode | O_CREAT, 0666);
    fil->writebuffer = malloc(PLIBC_BUFF_SIZE);
    fil->write_idx = 0;
    return (FILE *)fil;
}
