CC=gcc
CFLAGS=-std=c11 -pedantic -g3
DEPS = 
HEADERS = str-utils.h
OBJECTS = str-utils.o file-utils.o


.PHONY: directories clean

all: directories file-utils

%.o: %.c $(HEADERS)	
	@echo $(CC) -m32 $(CFLAGS) -c $< -o i686/$@
	$(CC) -m32 $(CFLAGS) -c $< -o i686/$@
	@echo $(CC) -m64 $(CFLAGS) -c $< -o x86_64/$@
	$(CC) -m64 $(CFLAGS) -c $< -o x86_64/$@

file-utils: $(OBJECTS)
	@echo $(CC) -m32 $(CFLAGS) -o i686/$@ $(OBJECTS)
	cd i686/; $(CC) -m32 $(CFLAGS) -o $@ $(OBJECTS)
	@echo $(CC) -m64 $(CFLAGS) -o i686/$@ $(OBJECTS)
	cd x86_64/; $(CC) -m64 $(CFLAGS) -o $@ $(OBJECTS)

directories: 
	mkdir -p i686/ x86_64/

clean:
	rm -rf i686/ x86_64/
