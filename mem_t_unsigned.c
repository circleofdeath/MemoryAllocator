#include "mem_i.h"
#include "mem_t.h"

unsigned long read_long_value(int pointer) { 
    bool* data = mem_read_i(pointer, 64);
    unsigned long result = 0;

    for(int i = 0; i < 64; i++) {
        if(data[i]) result |= (1UL << i); 
    }
    
    return result;
}

unsigned int read_int_value(int pointer) { 
    bool* data = mem_read_i(pointer, 32);
    unsigned int result = 0;

    for(int i = 0; i < 32; i++) {
        if(data[i]) result |= (1U << i); 
    }
    
    return result;
}

unsigned short read_short_value(int pointer) { 
    bool* data = mem_read_i(pointer, 16);
    unsigned short result = 0;

    for(int i = 0; i < 16; i++) {
        if(data[i]) result |= (1U << i); 
    }
    
    return result;
}

unsigned char read_byte_value(int pointer) {
    bool* data = mem_read_i(pointer, 8);
    unsigned char result = 0;

    for(int i = 0; i < 8; i++) {
        if(data[i]) result |= (1U << i); 
    }
    
    return result;
}

void write_long_value(int pointer, unsigned long value) {
    bool data[64];

    for(int i = 0; i < 64; i++) {
        data[i] = (value & (1UL << i)) != 0;
    }

    mem_write_i(pointer, 64, data);
}

void write_int_value(int pointer, unsigned int value) {
    bool data[32];

    for(int i = 0; i < 32; i++) {
        data[i] = (value & (1U << i)) != 0;
    }

    mem_write_i(pointer, 32, data);
}

void write_short_value(int pointer, unsigned short value) {
    bool data[16];

    for(int i = 0; i < 16; i++) {
        data[i] = (value & (1U << i)) != 0;
    }

    mem_write_i(pointer, 16, data);
}

void write_byte_value(int pointer, unsigned char value) {
    bool data[8];

    for(int i = 0; i < 8; i++) {
        data[i] = (value & (1U << i)) != 0;
    }

    mem_write_i(pointer, 8, data);
}
