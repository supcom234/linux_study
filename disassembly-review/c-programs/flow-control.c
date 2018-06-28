#include <stdio.h>

void greaterthan(int x){

	if (x > 5){
		printf("%d\n", x);
	}
}

void greaterthanorequal(int x){

	if (x >= 5){
		printf("%d\n", x);
	} else {
		printf("else");
	}
}

void lessthan(int x){

	if (x < 5){
		printf("%d\n", x);
	}
}

void lessthanorequal(int x){

	if (x <= 5){
		printf("%d\n", x);
	} else {
		printf("else");
	}
}

void equalto(int x){

	if (x == 5){
		printf("%d\n", x);
	}
}

void notequalto(int x){

	if (x != 5){
		printf("%d\n", x);
	} else {
		printf("else");
	} 
}


void nested(int x){
	if (x > 5 && x < 10){
		printf("%d\n", x);
	} else {
		printf("else");
	}
}

int main(){
	greaterthan(6);
	greaterthanorequal(5);
	lessthan(4);
	lessthanorequal(3);
	equalto(5);
	notequalto(7);
	nested(8);
	return 0;
}
