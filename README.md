# plibc
## about
a simple work-in-progress libc using the glibc headers and available
under GPLv3.

## using
`$ gcc -nostdlib {{your files}} /path/to/plibc.a`

## list of implemented functions

#### fcntl.h
- open()

#### signal.h
- kill()
- raise()

#### stdlib.h
- abort()
- atoi()
- bsearch()
- exit()
- free()
- malloc()
- realloc()


#### string.h
- memcpy()
- memset()
- strlen()

#### unistd.h
- brk()
- sbrk()
- close()
- getpid()
- read()
- write()
