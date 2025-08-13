#include <stdio.h>
#include <stdlib.h>


int func(int* p){
	return *p;
}
int main(){
	int* pointer = malloc(4);
	*pointer = 5;
	int a = func(pointer);
	printf("%d\n", a);
}

