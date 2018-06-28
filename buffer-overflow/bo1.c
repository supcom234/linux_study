#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int copier(char *str) {
	char buffer[100];
	strcpy(buffer, str);
	printf("Done!\n");
}

void main(int argc, char *argv[]) {
	if (argc != 2){
		printf("Please provide an argument for this program.\n");
		exit(1);
	}	
	copier(argv[1]);	
}
