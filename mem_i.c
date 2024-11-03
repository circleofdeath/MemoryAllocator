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

bool* memi_data = NULL;
int memi_size = 0;
// ### endregion ###

void initialise_memory() {
    memi_data = createNewArray(0);
}

void physical_resize(int size) {
    bool* n = createNewArray(size);
    int s = (memi_size > size) ? size : memi_size;
    for(int i = 0; i < s; i++) {
        *(n + i) = memi_data[i];
    }
    free(memi_data);
    memi_data = n;
    memi_size = size;
}

void malloc_i(int pointer, int size, bool data[]) {
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
