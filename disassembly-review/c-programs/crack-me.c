/*
A very simple crack-me application for an IDA exercise.
*/

#include <stdio.h>

int main(){
	const int x = 5;

	if (x < 10){
		printf("Please provide a license to this software.\n");
	} else {
		printf("You have cracked the software!\n");
	}

	return 0;
}