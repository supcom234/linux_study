#include <stdio.h>
#include <stdlib.h>

/*
Disassembly notes:
The .data section is read/ write at runtime the .rodata section is readonly

The static modifier remove the public from the .data section of the variable offset from the disassembly.
*/
char * ABC = "abc"; //The ABC reference is in the .data section the value is stored in the .rodata section
char DEF[4] = "DEF"; //Both the value and reference are in the  in .data.

static char* TEST = "cool"; //value in .rodata
static char TEST2[6] = "test2"; //value in .data
const char* TEST3 = "neato";  //This is exactly the same as ABC
const char* const TEST4 = "zebra";  //Reference and value both are stored in the .rodata section. Which makes it a true constant.
int* TEST_INT = NULL; // Reference ends up in the .bss segment in memory.

void print_characters(char d, unsigned char d1, signed char d2){
	char s = 'a';
	unsigned char s1 = 'b';
	signed char s2 = 'c';
	
	printf("0x%x\n", s);
	printf("0x%x\n", s1);
	printf("0x%x\n", s2);

	printf("0x%x\n", d);
	printf("0x%x\n", d1);
	printf("0x%x\n", d2);
}

void print_shorts(short d, unsigned short d1, signed short d2){
	short s = 1;
	unsigned short s1 = 2;
	signed short s2 = 3;

	printf("0x%x\n", s);
	printf("0x%x\n", s1);
	printf("0x%x\n", s2);

	printf("0x%x\n", d);
	printf("0x%x\n", d1);
	printf("0x%x\n", d2);
}

void print_ints(int d, unsigned int d1, signed int d2){
	int* TEST_INT2 = NULL;
	int s = 1;
	unsigned int s1 = 2;
	signed int s2 = 3;
	TEST_INT2 = &s;

	printf("0x%x\n", s);
	printf("0x%x\n", s1);
	printf("0x%x\n", s2);

	printf("0x%x\n", d);
	printf("0x%x\n", d1);
	printf("0x%x\n", d2);
	TEST_INT = malloc(sizeof(int));
	*TEST_INT = 123;
	printf("%d\n", TEST_INT);
}

void print_longs(long d, unsigned long d1, signed long d2){
	long s = 1;
	unsigned long s1 = 2;
	signed long s2 = 3;

	printf("0x%x\n", s);
	printf("0x%x\n", s1);
	printf("0x%x\n", s2);

	printf("0x%x\n", d);
	printf("0x%x\n", d1);
	printf("0x%x\n", d2);
}

void print_floats(float d, double d1, long double d2){
	float s = 1.0f;
	double s1 = 2.1;
	long double s2 = 3.3;

	printf("0x%x\n", s);
	printf("0x%x\n", s1);
	printf("0x%x\n", s2);

	printf("0x%x\n", d);
	printf("0x%x\n", d1);
	printf("0x%x\n", d2);	
}


void print_char_arrays(){
	// This msg ends up in the .rodata section of the binary.
	char* msg = "This is a char*.";
	// The entire string is in the .text section of the binary.
	char msg2[18] = "This is a char[].";
	printf(msg);
	printf(msg2);
	printf(ABC);
	printf(DEF);
	printf(TEST);
	printf(TEST2);
	printf(TEST3);	
	printf(TEST4);
	printf("%d\n", TEST_INT);
}

int main(){
	print_characters('d', 'e', 'f');
	print_shorts(4, 5, 6);
	print_ints(4, 5, 6);
	print_longs(4, 5, 6);
	print_floats(4.3f, 5.0, 6.2);
	print_char_arrays();
	return 0;
}