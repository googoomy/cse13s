#include "io.h"
#include "code.h"
#include "defines.h"

#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

uint32_t bytes_read = 0;
uint32_t bytes_written = 0;
static uint8_t write_bit_buffer[BLOCK] = {0};
static uint8_t write_bit_top = 0;

int read_bytes(int infile, uint8_t *buf, int nbytes){
	if(nbytes == 0){
		return 0;
	}
	int curr_bytes_read = 0;
	int num_bytes_read = 0;
	while((read(infile, buf + bytes_read, nbytes - curr_bytes_read)) > 0){
		bytes_read += curr_bytes_read;
		num_bytes_read += 1;
		if (num_bytes_read == nbytes){
			break;
		}
	}	
}

int write_bytes(int outfile, uint8_t *buf, int nbytes){
	if(nbytes == 0){
		return 0;
	}
	int curr_bytes_written = 0;
	int num_bytes_written = 0;
	while((write(outfile, buf + bytes_written, nbytes - curr_bytes_written)) > 0){
		bytes_written += curr_bytes_written;
		num_bytes_written += 1;
		if(num_bytes_written == nbytes){
			break;
		}
	}
}

bool read_bit(int infile, uint8_t *bit){
	static uint8_t read_bit_buffer[BLOCK] = {0};
	static uint32_t read_bit_top = 0;
	static uint32_t read_bit_buffer_size = 0;
	if(read_bit_top == 0){
		read_bit_buffer_size = read_bytes(infile, read_bit_buffer, BLOCK);
		if(read_bit_buffer_size == 0){
			return false;
		}
	}
	*bit = (read_bit_buffer[read_bit_top / 8] >> (read_bit_top % 8)) & 1;
	read_bit_top += 1;
	if(read_bit_top == read_bit_buffer_size * 8){
		read_bit_top = 0;
	}
	return true;
}

void write_code(int outfile, Code *c){

}

void flush_codes(int outfile){

}
