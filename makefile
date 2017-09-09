CC= gcc -nostdlib -Wall

OBJS= bin/internal/crt0.o bin/internal/syscall.o \
      bin/unistd/write.o bin/unistd/read.o bin/unistd/brk.o bin/unistd/close.o bin/unistd/getpid.o \
	  bin/stdlib/exit.o bin/stdlib/atoi.o bin/stdlib/malloc.o bin/stdlib/abort.o \
	  bin/fcntl/open.o \
	  bin/string/memcpy.o bin/string/strlen.o bin/string/memset.o \
	  bin/signal/kill.o bin/signal/raise.o

bin/plibc.a: $(OBJS)
	ar cr bin/plibc.a $?

bin/%.o: src/%.c | bin
	$(CC) -c $< -o $@

bin/%.o: src/%.s | bin
	as $< -o $@

bin:
	mkdir -p bin/internal bin/unistd bin/stdio bin/stdlib bin/fcntl bin/string bin/signal

.PHONY: clean

clean:
	rm -r bin
