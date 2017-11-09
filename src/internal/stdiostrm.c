/*
standard streams and their buffers for stdio
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
#include "../plibc_io.h"

char _stdout_buffer[4096];
char _stderr_buffer[4096];

struct plibc_file _stdout_plibc = {
    .filed = STDOUT_FILENO,
    .writebuffer = _stdout_buffer,
    .write_idx = 0
};

struct plibc_file _stderr_plibc = {
    .filed = STDERR_FILENO,
    .writebuffer = _stderr_buffer,
    .write_idx = 0
};

struct plibc_file _stdin_plibc = {
    .filed = STDIN_FILENO,
    .writebuffer = NULL,
    .write_idx = 0
};

FILE *stdout = (FILE *) &_stdout_plibc;
FILE *stderr = (FILE *) &_stderr_plibc;
FILE *stdin = (FILE *) &_stdin_plibc;
