#include "bitsy.h" //This header includes prototypes for the proposed bit abstractions
/*Include any additional headers you require*/

//#include <stdio.h>
#include <stdlib.h>
/*You may use any global variables/structures that you like*/

void shiftArr(unsigned short*, int);

/* main - dzy de-compression implementation
 * This program decompresses a compressed stream directed at its standard input 
 * and writes decompressed data to its standard output.
 *
 * To compile dzy: make dzy
 * To execute: ./dzy < somefile.encoded > somefile_decoded.txt
 */
int main(int argc, char *argv[]){
	//The implementation of your decoder should go here.
	
	//It is recommeded that you implement the bit abstractions in bitsy.c and
	//utilize them to implement your decoder.
	//If so, do NOT call read/write here. Instead rely exclusively on 
	//read_bit, read_byte, write_bit, write_byte, and flush_write_buffer.
	char eof = 0;
	unsigned short indBit;
	unsigned short byte;
	unsigned short* pBytes = calloc(8, 2);
	unsigned char threeBits;
	
	while(!eof){
		byte = 0;
		threeBits = 0;

		indBit = read_bit();
		

		if(indBit > 1){
			eof = 1;
			break;
		}

		if(indBit){//byte 
			byte = read_byte();

			if(byte > 0xFF){
				break;
			}
		} else{//3 bits
			//fprintf(stderr, "offset: ");
			for(int i = 0; i < 3; i++){
				threeBits = (threeBits) ^ (read_bit() << (2 - i));
			}

			if(threeBits > 0xFF){
				break;
			}

			byte = pBytes[7 - threeBits];
		}

		if(byte > 0xFF){
			break;
		}


		write_byte(byte);
		shiftArr(pBytes, 8);
		pBytes[7] = byte;
	}


	return 0; //exit status. success=0, error=-1
}


void shiftArr(unsigned short* arr, int s){
	for(int i = 0; i < s - 1; i++){
		arr[i] = arr[i + 1];
	}
}