CC= gcc -nostdlib -Wall -std=gnu99

OBJS= bin/internal/crt0.o bin/internal/syscall.o bin/internal/memory.o bin/internal/stdiostrm.o\
      bin/unistd/write.o bin/unistd/read.o bin/unistd/brk.o bin/unistd/close.o bin/unistd/getpid.o \
	  bin/stdlib/exit.o bin/stdlib/atoi.o bin/stdlib/malloc.o bin/stdlib/free.o \
	  bin/stdlib/abort.o bin/stdlib/bsearch.o bin/stdlib/realloc.o bin/stdlib/rand.o\
	  bin/fcntl/open.o \
	  bin/string/memcpy.o bin/string/strlen.o bin/string/memset.o \
	  bin/signal/kill.o bin/signal/raise.o \
	  bin/time/time.o \
	  bin/stdio/fopen.o bin/stdio/fwrite.o bin/stdio/fread.o bin/stdio/fclose.o bin/stdio/fputc.o bin/stdio/fflush.o\
	  bin/math/sin.o


bin/plibc.a: $(OBJS)
	ar cr bin/plibc.a $?

bin/%.o: src/%.c | bin
	$(CC) -c $< -o $@

bin/%.o: src/%.s | bin
	as $< -o $@

bin:
	dirname $(OBJS) | sort -u | xargs mkdir -p

.PHONY: clean

clean:
	rm -r bin
