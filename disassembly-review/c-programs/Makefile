CC=gcc
CFLAGS=-std=c11 -pedantic -g3
DEPS = 
objects = hello-world data-types loops function-types flow-control crack-me pipe-example pipeshell

fheaders = str-utils.h
fobjects = str-utils.o file-utils.o


.PHONY: directories clean

all: directories $(objects)

$(objects): %: %.c
	@echo $(CC) -m32 $(CFLAGS) -o i686/$@ $<
	$(CC) -m32 $(CFLAGS) -o i686/$@ $<
	@echo $(CC) -m64 $(CFLAGS) -o x86_64/$@ $<
	$(CC) -m64 $(CFLAGS) -o x86_64/$@ $<

directories: 
	mkdir -p i686/ x86_64/

clean:
	rm -rf i686/ x86_64/
