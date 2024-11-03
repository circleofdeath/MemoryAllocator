#ifndef MEM_I_H_
#define MEM_I_H_

#include <stdbool.h>

extern bool* memi_data;
extern int memi_size;

void initialise_memory();
void physical_resize(int size);
void malloc_i(int pointer, int size, bool data[]);
bool* mem_read_i(int pointer, int size);

#endif
