#include "mem_i.h"
#include "mem_t.h"

long read_signed_long_value(int pointer) {
    bool* data = mem_read_i(pointer, 64);
    long result = 0;

    for(int i = 0; i < 64; i++) {
        if(data[i]) result |= (1L << i); 
    } 
   
    unsigned long mask = (1UL << 63);
    return (result & ~mask) | (mask & (result < 0 ? ~0UL : 0));
};

int read_signed_int_value(int pointer) {
    bool* data = mem_read_i(pointer, 32);
    int result = 0;

    for(int i = 0; i < 32; i++) {
        if(data[i]) result |= (1 << i); 
    } 
   
    unsigned int mask = (1U << 31);
    return (result & ~mask) | (mask & (result < 0 ? ~0U : 0));
}

short read_signed_short_value(int pointer) {
    bool* data = mem_read_i(pointer, 16);
    short result = 0;

    for(int i = 0; i < 16; i++) {
        if(data[i]) result |= (1 << i); 
    } 
   
    unsigned short mask = (1U << 15);
    return (result & ~mask) | (mask & (result < 0 ? ~0U : 0));
}

char read_signed_byte_value(int pointer) {
    bool* data = mem_read_i(pointer, 8);
    char result = 0;

    for(int i = 0; i < 8; i++) {
        if(data[i]) result |= (1 << i); 
    } 
   
    unsigned char mask = (1U << 7);
    return (result & ~mask) | (mask & (result < 0 ? ~0U : 0));
}

void write_signed_long_value(int pointer, long value) {
    bool data[64];

    for(int i = 0; i < 64; i++) {
        data[i] = (value >> i) & 1;
    }

    mem_write_i(pointer, 64, data);
}

void write_signed_int_value(int pointer, int value) {
    bool data[32];

    for(int i = 0; i < 32; i++) {
        data[i] = (value >> i) & 1;
    }

    mem_write_i(pointer, 32, data);
}

void write_signed_short_value(int pointer, short value) {
    bool data[16];

    for(int i = 0; i < 16; i++) {
        data[i] = (value >> i) & 1;
    }

    mem_write_i(pointer, 16, data);
}

void write_signed_byte_value(int pointer, char value) {
    bool data[8];

    for(int i = 0; i < 8; i++) {
        data[i] = (value >> i) & 1;
    }

    mem_write_i(pointer, 8, data);
}
