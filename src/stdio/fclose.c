/*
fclose <stdio.h>
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
#include <stdlib.h>

#include "../plibc_io.h"


// TODO: buffering
int fclose(FILE *stream) {
    struct plibc_file *pstream = (struct plibc_file *) stream;
    int status = close(pstream->filed);
    free(pstream->writebuffer);
    free(pstream);
    return status;
}
