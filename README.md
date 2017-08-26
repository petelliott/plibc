# plibc
## about
a simple work-in-progress libc using the glibc headers and available
under GPLv3.

## using
`$ gcc -nostdlib {{your files}} /path/to/plibc.a`

## list of implimented functions

#### fcntl.h

- open()

#### stdlib.h
- atoi()
- exit()
- malloc()
- free()

#### unistd.h
- brk()
- sbrk()
- close()
- read()
- write()
