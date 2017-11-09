# plibc
## about
a simple work-in-progress libc using the glibc headers and available
under GPLv3.

## using
`$ gcc -nostdlib {{your files}} /path/to/plibc.a`

## list of implemented functions

#### fcntl.h
- open()

#### math.h
- sin()

#### signal.h
- kill()
- raise()

#### stdio.h
- fclose()
- fflush()
- fopen()
- fputc()
- fread()
- fwrite()

#### stdlib.h
- abort()
- atoi()
- bsearch()
- exit()
- free()
- malloc()
- rand()
- realloc()
- srand()


#### string.h
- memcpy()
- memset()
- strlen()

#### time.h
- time()

#### unistd.h
- brk()
- sbrk()
- close()
- getpid()
- read()
- write()
