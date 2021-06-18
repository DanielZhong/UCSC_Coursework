#include "io.h"

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

uint64_t bytes_read = 0;
uint64_t bytes_written = 0;

static uint8_t buffer_code[BLOCK];
static uint32_t buffer_idx = 0;

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int total = 0;
    int bytes = 0;
    while (total != nbytes && (bytes = read(infile, buf + total, nbytes - total)) > 0) {
        total += bytes;
    }
    bytes_read += total;
    return total;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int total = 0;
    int bytes = 0;
    while (total != nbytes && (bytes = write(outfile, buf + total, nbytes - total)) > 0) {
        total += bytes;
    }
    bytes_written += total;
    return total;
}

bool read_bit(int infile, uint8_t *bit) {
    static uint8_t buffer[BLOCK];
    static uint32_t index = 8 * BLOCK; //keep track of the end of buffer
    if (index >= 8 * BLOCK) {
        read_bytes(infile, buffer, BLOCK);
        index = 0;
    }
    *bit = (buffer[index / 8] >> index % 8) & 1; //get bit
    index++;
    return true;
}

void write_code(int outfile, Code *c) {
    uint32_t buffer_location = buffer_idx / 8;
    uint16_t buffer_position = buffer_idx % 8;
    uint32_t code_location = 0;
    uint16_t code_position = 0;
    uint8_t set_on = 0;
    //write the c->bits[0...top] to buffer_code[buffer_idx...buffer_idx+top];
    for (uint32_t i = 0; i < c->top; i++) {
        //if the buffer is full
        if (buffer_idx >= 8 * BLOCK) {
            flush_codes(outfile);
            buffer_location = 0;
            buffer_position = 0;
        }
        code_location = i / 8;
        code_position = i % 8;
        set_on = (c->bits[code_location] >> code_position) & 1; //get bit
        if (set_on) { //if i_th bit is 1
            buffer_code[buffer_location] |= (set_on << buffer_position);
        } else { //if i_bit is 0
            buffer_code[buffer_location] &= (~(set_on << buffer_position));
        }

        buffer_idx++;
        buffer_location = buffer_idx / 8;
        buffer_position = buffer_idx % 8;
    }
}

void flush_codes(int outfile) {
    write_bytes(outfile, buffer_code, buffer_idx % 8 == 0 ? buffer_idx / 8 : buffer_idx / 8 + 1);
    for (uint32_t i = 0; i < BLOCK; i++) {
        buffer_code[i] = 0;
    }
    buffer_idx = 0;
}

//all io.c inspired by sahiti section
