/*
fwrite <stdio.h>
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
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include "../plibc_io.h"


// TODO: buffering
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
    struct plibc_file *pstream = (struct plibc_file *) stream;

    ssize_t status;
    if (size*nmemb + pstream->write_idx <= PLIBC_BUFF_SIZE) {
        memcpy(pstream->writebuffer+pstream->write_idx, ptr, size*nmemb);
        pstream-> write_idx += size*nmemb;
        status = size*nmemb;
    } else {
        status =  write(pstream->filed, pstream->writebuffer, pstream->write_idx);
        status += write(pstream->filed, ptr, size*nmemb);
        pstream->write_idx = 0;
    }

    if (status < 0) {
        // TODO: figure out ferror and feof
        return 0;
    } else {
        return status;
    }
}
