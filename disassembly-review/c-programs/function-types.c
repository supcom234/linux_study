/*
stdcall – all arguments on stack, callee cleans
cdecl – all arguments on stack, caller cleans
fastcall– like stdcall, but first 2 args go into ECX and EDX
thiscall – like stdcall, but an object pointer goes into ECX (C++ style)
*/
#include <stdio.h>

#define __stdcall __attribute__((stdcall))
#define __cdecl __attribute__((cdecl))
//#define __thiscall __attribute__((thiscall)) TODO must be used on a class method in cpp program.
#define __fastcall __attribute__((fastcall))

__stdcall
int my_std_call(int x , int y, int count){
	printf("%d\n", x);
	printf("%d\n", y);
	printf("%d\n", count);
	return 1;
}

__fastcall
int my_fast_call(int x , int y, int count){
	printf("%d\n", x);
	printf("%d\n", y);
	printf("%d\n", count);	
	return 2;
}

__cdecl
int my_cdecl_call(int x , int y, int count){
	printf("%d\n", x);
	printf("%d\n", y);
	printf("%d\n", count);	
	return 3;
}

int my_normal_call(int x , int y, int count){
	printf("%d\n", x);
	printf("%d\n", y);
	printf("%d\n", count);	
}

int main(int argc, char **argv){
	my_std_call(1, 2, 3);
	my_fast_call(4, 5, 6);
	my_cdecl_call(7, 8, 9);
	my_normal_call(10, 11, 12);
	return 0;
}