#include "hmalloc.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
/*You may include any other relevant headers here.*/


/*Add additional data structures and globals here as needed.*/
void *free_list = NULL;

/* traverse
 * Start at the free list head, visit and print the length of each
 * area in the free pool. Each entry should be printed on a new line.
 */
void traverse(){

	if(free_list == NULL){
		return;
	}


	void* ptr = free_list;
	int count = 0;
	while(*(int*)(ptr + 4) != 0){
		printf("Index: %d, Address: %08x, Length: %d\n", count, ptr + 8, *(int*)(ptr));
		ptr += *(int*)(ptr + 4);
		count++;
	};
	printf("Index: %d, Address: %08x, Length: %d\n", count, ptr + 8, *(int*)(ptr));
}

/* pickFreeMemory 
 * Removes a memory block from free_list and returns its address
 */

 //When I wrote this only god and I knew how it worked
 //Now only god knows!
void* pickFreeMemory(int bytes){
	if(free_list == NULL){
		return NULL;
	}

	void* ptr = free_list;
	void* previousPointer = NULL;
	while(*(int*)(ptr + 4) != 0){
		if(*(int*)(ptr) >= bytes){
			if(previousPointer == NULL){
				if(*(int*)(ptr + 4) == 0){
					free_list = NULL;	
				} else{
					free_list = ptr + *(int*)(ptr + 4);
				}
			} else{
				if(*(int*)(ptr + 4) == 0){ //unreachable
					*(int*)(previousPointer) = 0;
				} else{
					*(int*)(previousPointer + 4) += *(int*)(ptr + 4);
				}
			}			
			return ptr;
		}
		previousPointer = ptr;
		ptr += *(int*)(ptr + 4);
	}
	if(*(int*)(ptr) >= bytes){
		*(int*)(previousPointer + 4) = 0;
		return ptr;
	}

	return NULL;
}

/* hmalloc
 * Allocation implementation.
 *    -will not allocate an initial pool from the system and will not 
 *     maintain a bin structure.
 *    -permitted to extend the program break by as many as user 
 *     requested bytes (plus length information).
 *    -keeps a single free list which will be a linked list of 
 *     previously allocated and freed memory areas.
 *    -traverses the free list to see if there is a previously freed
 *     memory area that is at least as big as bytes_to_allocate. If
 *     there is one, it is removed from the free list and returned 
 *     to the user.
 */
void *hmalloc(int bytes_to_allocate){
	void* allocatedMemory;
	
	
	if((allocatedMemory = pickFreeMemory(bytes_to_allocate))){
	} else{
		allocatedMemory = sbrk(bytes_to_allocate + 8);
		*(int*)allocatedMemory = bytes_to_allocate;
	}

	*(int*)(allocatedMemory + 4) = 0;
	void* userMemory = allocatedMemory + 8;	
	return userMemory;
}

/* hcalloc
 * Performs the same function as hmalloc but also clears the allocated 
 * area by setting all bytes to 0.
 */
void *hcalloc(int bytes_to_allocate){
	void* ptr = hmalloc(bytes_to_allocate);
	for(int i = 0; i < bytes_to_allocate; i++){
		((char*)ptr)[i] = 0;
	}
   return ptr; //placeholder to be replaced by proper return value
}

/* hfree
 * Responsible for returning the area (pointed to by ptr) to the free
 * pool.
 *    -simply appends the returned area to the beginning of the single
 *     free list.
 */
void hfree(void *ptr){
	ptr = ptr - 8;
	if(free_list == NULL){
		free_list = ptr;
		return;
	}

	int difference = free_list - ptr;
	*(int*)(ptr + 4) = difference;
	free_list = ptr;
}

/* For the bonus credit implement hrealloc. You will need to add a prototype
 * to hmalloc.h for your function.*/


/*You may add additional functions as needed.*/

/* printMemoryBlock
 * Outputs the byte values of any allocated chunk of memory
 */
void printMemoryBlock(void* memory){
	printf("Memory Dump:\n");
	memory = memory - 8;
	int totalSize = *((int*)memory) + 8;
	int traversed = 0;
	for(;traversed < totalSize;){
		for(int j = 0; j < 16 && traversed < totalSize; j++){
			printf("%02x ", *(char*)memory);
			memory++;
			traversed++;
		}
		printf("\n");
	}
}