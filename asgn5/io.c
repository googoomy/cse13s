#include "io.h"
#include "code.h"
#include "defines.h"

#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

uint64_t bytes_read = 0;
uint64_t bytes_written = 0;
static uint8_t write_bit_buffer[BLOCK] = { 0 };
static uint8_t write_bit_top = 0;

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    if (nbytes == 0) {
        return 0;
    }
    int curr_bytes_read = 0;
    int num_bytes_read = 0;
    while ((read(infile, buf + bytes_read, nbytes - curr_bytes_read)) > 0) {
        bytes_read += curr_bytes_read;
        num_bytes_read += 1;
        if (num_bytes_read == nbytes) {
            break;
        }
    }
    return num_bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    if (nbytes == 0) {
        return 0;
    }
    int curr_bytes_written = 0;
    int num_bytes_written = 0;
    while ((write(outfile, buf + bytes_written, nbytes - curr_bytes_written)) > 0) {
        bytes_written += curr_bytes_written;
        num_bytes_written += 1;
        if (num_bytes_written == nbytes) {
            break;
        }
    }
    return num_bytes_written;
}

//This read_bit function is based on both TA Christian and Eugene's pseudocode
bool read_bit(int infile, uint8_t *bit) {
    static uint8_t read_bit_buffer[BLOCK] = { 0 };
    static uint32_t read_bit_top = 0;
    static uint32_t read_bit_buffer_size = 0;
    static int read_bit_prev = -1;
    if (read_bit_top == 0) {
        read_bit_buffer_size = read_bytes(infile, read_bit_buffer, BLOCK);
        if (read_bit_buffer_size < BLOCK) {
            read_bit_prev = read_bit_buffer_size * 8 + 1;
        }
        if (read_bit_buffer_size == 0) {
            return false;
        }
    }
    *bit = (read_bit_buffer[read_bit_top / 8] >> (read_bit_top % 8)) & 1;
    read_bit_top += 1;
    if (read_bit_top == BLOCK * 8) {
        read_bit_top = 0;
    }
    return true;
}

void write_code(int outfile, Code *c) {
    for (uint8_t i = 0; i < c->top; i += 1) {
        //uint32_t curr_bit = (c->bits[i/8] >> (i % 8)) & 1;
        //uint32_t curr_offset
        int bit = code_get_bit(c, i);
        if (bit == 1) {
            code_set_bit(c, i);
        } else {
            code_clr_bit(c, i);
        }
        write_bit_top += 1;
        int temp = BLOCK * 8;
        if (write_bit_top == temp) {
            flush_codes(outfile);
        }
    }
}

void flush_codes(int outfile) {
    if (write_bit_top > 0) {
        write_bytes(outfile, write_bit_buffer, (write_bit_top / 8) + 1);
    }
}
