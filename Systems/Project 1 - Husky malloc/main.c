#include "hmalloc.h"
#include <stdlib.h>
#include <stdio.h>
/*You may include any other relevant headers here.*/


/*	main()
 *	Use this function to develop tests for hmalloc. You should not 
 *	implement any of the hmalloc functionality here. That should be
 *	done in hmalloc.c
 *	This file will not be graded. When grading I will replace main 
 *	with my own implementation for testing.*/
int main(int argc, char *argv[]){
	// some calls to hmalloc
	// ...
	// some calls to hfree
	char *a, *b, *c, *d;
	a = hmalloc(20);
	b = hmalloc(10);
	c = hmalloc(30);
	d = hmalloc(5);

	/*for(int i = 0; i < 20; i++){
		a[i] = 'a' + i;
	}
	traverse();

	printf("%s\n", a);
	
	hfree(a);
	hfree(b);
	hfree(c);
	hfree(d);

	traverse();
	printf("\n");

	a = hmalloc(4);
	b = hmalloc(21);
	c = hmalloc(15);
	

	traverse();
	printf("\n");

	d = hcalloc(12);
	printMemoryBlock(d);
	*/

	free(a);
	traverse();
	a = hmalloc(15);
	traverse();


	return 1;
}
