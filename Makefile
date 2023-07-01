all: compile_library

CC = clang
override CFLAGS += -g -Wno-everything


compile_example:
	$(CC) $(CFLAGS) example.c sda.o -o example

compile_library:
	$(CC) -c sda.c -o sda.o

install:
	clang -shared sda.o -o $(shell bash -c 'read -p "Install Path: " INSTALL_PATH; echo $$INSTALL_PATH')/libsda.so

clean:
	rm -f example

run:
	./example
