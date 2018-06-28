all: bo1 esp

clean:
	rm -f *.o bo1 esp

bo1: bo1.c
	gcc -g -m32 -fno-stack-protector -z execstack -o bo1 bo1.c

esp: esp.c
	gcc -o esp esp.c
