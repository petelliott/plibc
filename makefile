CC= gcc -nostdlib -Wall


bin/plibc.a: bin/crt0.o bin/syscall.o
	ar cr bin/plibc.a $?

bin/%.o: src/%.c | bin
	$(CC) -c $< -o $@

bin/%.o: src/%.s | bin
	as $< -o $@

bin:
	mkdir bin

.PHONY: clean

clean:
	rm -r bin
