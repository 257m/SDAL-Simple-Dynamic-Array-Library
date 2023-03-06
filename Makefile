all: compile_dynamic_array_library compile_example

CC = clang
override CFLAGS += -g -Wno-everything

compile_example:
	$(CC) $(CFLAGS) example.c sda.o -o example

compile_dynamic_array_library:
	$(CC) -c sda.c -o sda.o

clean:
	rm -f example

run:
	./example