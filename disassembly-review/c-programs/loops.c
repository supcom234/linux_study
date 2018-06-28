#include <stdio.h>


void example_while_loop(){
	int x;
	x = 5;

	while (x != 0){
		printf("%d\n", x);
		x--;
	}
}

void example_while_loop2(){
	int x;
	x = 0;
	while (x < 10){
		printf("%d\n", x);
		x = x + 2;
	}
}

void example_while_loop3(){
	int x;
	x = 10;
	while (x > 0){
		printf("%d\n", x);
		x = x - 2;
	}
}

void example_dowhile_loop(){
	int x;
	x = 5;

	do {
		printf("%d\n", x);
		x--;
	} while (x != 0);
}

void example_dowhile_loop2(){
	int x;
	x = 0;
	do {
		printf("%d\n", x);
		x = x + 2;
	} while (x < 10);
}

void example_dowhile_loop3(){
	int x;
	x = 10;
	do {
		printf("%d\n", x);
		x = x - 2;
	} while (x > 0);
}

void example_for_loop(){
	int x;
	for (x = 0; x < 10; x++){
		printf("%d\n", x);
	}
}

void example_nested_loop(){
	int x = 10;
	while (x > 0){
		printf("%d\n", x);

		for (int y = 10; y > 10; y--){
			printf("%d\n", y);			
		}

		x = x - 2;
	}
}


int main(){
	example_while_loop();
	example_while_loop2();
	example_while_loop3();
	example_dowhile_loop();
	example_dowhile_loop2();
	example_dowhile_loop3();
	example_for_loop();
	example_nested_loop();
	return 0;
}