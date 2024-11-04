#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "mem_i.h"

// ### region private ###
bool* createNewArray(int size) {
    bool* result = (bool*) malloc(size * sizeof(bool));
    if(result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < size; i++) {
        result[i] = false;
    }

    return result;
}

bool* memi_allocated_data = NULL;
bool* memi_data = NULL;
int memi_size = 0;
// ### endregion ###

void initialise_memory() {
    memi_data = createNewArray(0);
    memi_allocated_data = createNewArray(0);
}

void physical_resize(int size) {
    bool* n = createNewArray(size);
    bool* an = createNewArray(size);
    int s = (memi_size > size) ? size : memi_size;
    for(int i = 0; i < s; i++) {
        *(n + i) = memi_data[i];
        *(an + i) = memi_allocated_data[i];
    }
    free(memi_data);
    free(memi_allocated_data);
    memi_data = n;
    memi_allocated_data = an;
    memi_size = size;
}

void mem_write_i(int pointer, int size, bool data[]) {
    for(int i = 0; i < size; i++) {
        if((i + pointer) >= memi_size) {
            // buffer overflow protection
            return;
        }

        // NULL singaniles that it's memory release
        *(memi_data + pointer + i) = (data == NULL) ? false : data[i];
    }
}

bool* mem_read_i(int pointer, int size) {
    bool* result = createNewArray(size);
    for(int i = 0; i < size; i++) {
        if((i + pointer) >= memi_size) {
            // buffer overflow protection
            return result;
        }

        *(result + i) = *(memi_data + pointer + i);
    }
    return result;
}

void mem_free(int pointer, int size) {
    for(int i = 0; i < size; i++) {
        if((i + pointer) >= memi_size) {
            // buffer overflow protection
            return;
        }

        *(memi_data + pointer + i) = false;
        *(memi_allocated_data + pointer + i) = false;
    }
}

void allocate(int pointer, int size) {
    for(int i = 0; i < size; i++) {
        if((i + pointer) >= memi_size) {
            // buffer overflow protection
            return;
        }

        *(memi_allocated_data + pointer + i) = true;
    }
}

void mem_move(int pointerA, int pointerB, int size) {
    bool* data = mem_read_i(pointerA, size);
    mem_write_i(pointerB, size, data);
    allocate(pointerB, size);
    mem_free(pointerA, size);
}

int mem_malloc(int size) {
    for(int i = 0; i < memi_size; i++) {
        if(*(memi_allocated_data + i) == false) {
            int j = i;
            
            while(i < memi_size && i < (j + size) && *(memi_allocated_data + i) == false) {
                i++;
            }

            if((i - j) >= size) {
                allocate(j, size);
                return j;
            }
        }
    }

    return -1;
}
