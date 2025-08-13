#include "bitsy.h" //This header includes prototypes for the proposed bit abstractions
/*Include any additional headers you require*/
#include <stdlib.h>

/*You may use any global variables/structures that you like*/

int findInArr(unsigned short*, unsigned short, int);
void shiftArr(unsigned short*, int);

/* main - czy compression implementation
 * Develop a program called czy which compresses the data stream directed 
 * at its standard input and writes the compressed stream to its standard 
 * output.
 *
 * The compression algorithm reads the input one symbol (i.e., byte) at a 
 * time and compares it with each of the 8 bytes previously seen.  It also 
 * checks to see if the following n characters are the same as the current 
 * symbol.  If the byte has been previously seen, it outputs the position of 
 * the previous byte relative to the current position, Otherwise, the symbol 
 * is output as is by prefixing it with a binary one.
 *
 * To compile czy: make czy
 * To execute: ./czy < somefile.txt > somefile.encoded
 */
int main(int argc, char *argv[]){
	
	unsigned short byte = 0;
	unsigned short* backArr = calloc(8, sizeof(unsigned short));
	int offset = -1;

	while(1){
		byte = read_byte();
		//fprintf(stderr, "read byte 0x%04x\n", byte);
		
		if(byte > 0xFF){
			break;
		}

		if((offset = findInArr(backArr, byte, 8)) >= 0){

			write_bit(0);
			for(int i = 0; i < 3; i++){
				write_bit(~((offset) >> (2 - i)) & 1);
			}
		} else{
			write_bit(1);
			write_byte(byte);
		}
		
		
		shiftArr(backArr, 8);
		backArr[7] = byte;
	}

	flush_write_buffer();
	return 0; //exit status. success=0, error=-1
}

int findInArr(unsigned short* arr, unsigned short value, int s){
	for(int i = 0; i < s; i++){
		if(arr[i] == value){
			return i;
		}
	}
	return -1;
}

void shiftArr(unsigned short* arr, int s){
	for(int i = 0; i < s - 1; i++){
		arr[i] = arr[i + 1];
	}
}