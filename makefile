CC= gcc -nostdlib -Wall

OBJS= bin/internal/crt0.o bin/internal/syscall.o \
      bin/unistd/write.o bin/unistd/read.o bin/unistd/brk.o bin/unistd/close.o \
	  bin/stdlib/exit.o bin/stdlib/atoi.o bin/stdlib/malloc.o \
	  bin/fcntl/open.o \
	  bin/string/memcpy.o bin/string/strlen.o

bin/plibc.a: $(OBJS)
	ar cr bin/plibc.a $?

bin/%.o: src/%.c | bin
	$(CC) -c $< -o $@

bin/%.o: src/%.s | bin
	as $< -o $@

bin:
	mkdir -p bin/internal bin/unistd bin/stdio bin/stdlib bin/fcntl bin/string

.PHONY: clean

clean:
	rm -r bin
