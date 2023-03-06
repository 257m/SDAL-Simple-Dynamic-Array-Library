all: compile_dynamic_array_library compile_example

CC = clang
override CFLAGS += -g -Wno-everything

compile_example:
	$(CC) $(CFLAGS) example.c dynamic_array.o -o example

compile_dynamic_array_library:
	$(CC) -c dynamic_array.c -o dynamic_array.o

clean:
	rm -f example

run:
	./example