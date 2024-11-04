#ifndef MEM_I_H_
#define MEM_I_H_

// Arch of this allocator is 32 bit
#include <stdbool.h>

extern bool* memi_allocated_data;
extern bool* memi_data;
extern int memi_size;

void initialise_memory();
void physical_resize(int size);
void mem_write_i(int pointer, int size, bool data[]);
bool* mem_read_i(int pointer, int size);

int mem_malloc(int size);
void mem_free(int pointer, int size);
void allocate(int pointer, int size);
void mem_move(int pointerA, int pointerB, int size);

#endif
