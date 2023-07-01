all: compile_library

CC = clang
override CFLAGS += -g -Wno-everything

compile_example:
	$(CC) $(CFLAGS) example.c sda.o -o example

compile_library:
	$(CC) -c sda.c -o sda.o

install: sda.o
	clang -shared $< -o $(shell bash -c 'read -p "Install Directory: " INSTALL_DIR; echo $$INSTALL_DIR')/libsda.so
	cp sda.h $(shell bash -c 'read -p "Include Directory: " INCLUDE_DIR; echo $$INCLUDE_DIR')/sda.h

clean:
	rm -rf example sda.o

run:
	./example
