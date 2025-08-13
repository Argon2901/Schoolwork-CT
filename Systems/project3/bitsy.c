#include "bitsy.h"
#include <unistd.h>
//#include <stdio.h>

unsigned short rByte = 0;
unsigned short wByte = 0;
unsigned char wBuffer = 0;
unsigned char rBuffer = 0xFF;
unsigned char eof = 0;
//unsigned char empty = 0;

/* Add any global variables or structures you need.*/

/* read_byte
 * Abstraction to read a byte.
 * Relys on readBit.
 */
unsigned short read_byte(){ 
	/* This function should not call read() directly.
	 * If we are buffering data in read_bit, we dont want to skip over
	 * that data by calling read again. Instead, call read_bit and 
	 * construct a byte one bit at a type. This also allows us to read
	 * 8 bits that are not necessarily byte alligned. */

	//Do NOT call read here. Instead rely on read_bit.
	unsigned short byte = 0;
	unsigned short input = 0;

	//printf("reading byte\n");
	for(int i = 0; i < 8; i++){
		input = read_bit();
		
		if(input > 0xFF){
			//printf("read_byte eof signal\n");
			return input ^ byte;
		}
		byte = byte ^ (input << (7 - i));
	}
	
	//I suggest returning a unique value greater than the max byte value
	//to communicate end of file. We need this since 0 is a valid byte value
	//so we need another way to communicate eof. These functions are typed
	//as short to allow us to return a value greater than the max byte value.
	return byte; 
}

/* read_bit
 * Abstraction to read a bit.
 * */
unsigned short read_bit(){
	/* This function is responsible for reading the next bit on the
	 * input stream from stdin (fd = 0). To accomplish this, keep a 
	 * byte sized buffer. Each time read bit is called, use bitwise
	 * operations to extract the next bit and return it to the caller.
	 * Once the entire buffered byte has been read the next byte from 
	 * the file. Once eof is reached, return a unique value > 255
	 *
	 */	
	//You will need to call read here
	if(!eof && rBuffer >= 8){
		//printf("retrieving new byte: \n");
		if(!read(0, &rByte, 1)){
			//printf("Read end of file\n");
			eof = 1;
		} else{
			rBuffer = 0;
		}
		//printf("eof = %d\n", eof);
	}
	
	if(eof){
		//printf("bitsy read_bit() eof \n");
		//empty = 1;
		return 0x100;
	}
	unsigned short bit = (rByte >> (7 - rBuffer)) & 0x1 ;
	rBuffer++;
	//printf("%d", bit);
	return bit;
	//I suggest returning a unique value greater than the max byte value
	//to communicate end of file. We need this since 0 is a valid byte value
	//so we need another way to communicate eof. These functions are typed
	//as short to allow us to return a value greater than the max byte value.
}

/* write_byte
 * Abstraction to write a byte.
 */
void write_byte(unsigned char byt){
	/* Use writeBit to write each bit of byt one at a time. Using writeBit
	 * abstracts away byte boundaries in the output.*/

	for(int i = 0; i < 8; i++){
		write_bit((byt >> (7 - i)) & 1);
	}

	//Do NOT call write, instead utilize writeBit()
}

/* write_bit
 * Abstraction to write a single bit.
 */
void write_bit(unsigned char bit){
	/* Keep a byte sized buffer. Each time this function is called, insert the 
	 * new bit into the buffer. Once 8 bits are buffered, write the full byte
	 * to stdout (fd=1).
	 */

	
	wByte = wByte ^ (bit << (7 - wBuffer));

	if(wBuffer == 7){
		write(1, &wByte, 1);
		wByte = 0;
		wBuffer = 0;
		return;
	}
	wBuffer++;
}

/* flush_write_buffer
 * Helper to write out remaining contents of a buffer after padding empty bits
 * with 1s.
 */
void flush_write_buffer(){
	/* This will be utilized when finishing your encoding. It may be that some bits
	 * are still buffered and have not been written to stdout. Call this function 
	 * which should do the following: Determine if any buffered bits have yet to be 
	 * written. Pad remaining bits in the byte with 1s. Write byte to stdout
	 */
	
	//printf("flushing wbyte %02x\n", wByte);

	if(wBuffer == 0){
		return;
	}

	 for(int i = 0; i < wBuffer; i++){
		wByte = wByte ^ (1 << (7 - wBuffer - i));
	 }

	//printf("flushing wbyte post fill %02x\n", wByte);

	 write(1, &wByte, 1);
	 wBuffer = 0;

}