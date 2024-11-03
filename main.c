#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem_i.h"

#define INPUT_SIZE 256

int main() {
    initialise_memory();
    printf("Type \"exit\" to exit the program! \"help\" for help!");
    char line[INPUT_SIZE];

    while(1) {
        printf("\n~/> ");
        if(fgets(line, sizeof(line), stdin) == NULL) {
            perror("Failed to read input");
            break;
        }

        size_t len = strlen(line);
        if(len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        char* token = strtok(line, " ");
        if(strcmp(token, "exit") == 0) {
            return 0;
        } else if(strcmp(token, "help") == 0) {
            printf("phmemstatic <size>: resize bytes of physical memory to <size>\n");
            printf("phmem <size>: increase/decrease bytes of physical memory by <size>\n");
            printf("free <pointer> <size>: free memory at <pointer> by <size>\n");
            printf("read <pointer> <size>: read <size> bytes from memory at <pointer>\n");
            printf("write <pointer> <data>: write <data> to memory at <pointer>\n");
            printf("infolen: show length of physical memory");
        } else if(strcmp(token, "phmemstatic") == 0) {
            token = strtok(NULL, " ");
            printf("Writing/Relocating %s bytes", token);
            physical_resize(atoi(token));
        } else if(strcmp(token, "phmem") == 0) {
            token = strtok(NULL, " ");
            printf("Expanding/Relocating %s bytes", token);
            physical_resize(memi_size + atoi(token));
        } else if(strcmp(token, "free") == 0) {
            token = strtok(NULL, " ");
            int pointer = atoi(token);
            token = strtok(NULL, " ");
            int size = atoi(token);
            malloc_i(pointer, size, NULL);
        } else if(strcmp(token, "read") == 0) {
            token = strtok(NULL, " ");
            int pointer = atoi(token);
            token = strtok(NULL, " ");
            int size = atoi(token);
            bool* result = mem_read_i(pointer, size);
    
            for(int i = 0; i < size; i++) {
                printf("%s%s", (result[i] ? "1" : "0"), ((i % 64 == 63) ? "\n" : ""));
            }
        } else if(strcmp(token, "write") == 0) {
            token = strtok(NULL, " ");
            int pointer = atoi(token);
            token = strtok(NULL, " ");
            bool* data = (bool*) malloc(sizeof(bool) * strlen(token));
    
            for(int i = 0; i < strlen(token); i++) {
                data[i] = (token[i] == '1');
            }

            malloc_i(pointer, strlen(token), data);
        } else if(strcmp(token, "infolen") == 0) {
            printf("Length of physical memory: %d", memi_size);
        } else {
            printf("%s is not a command!", token);
        }
    }

    return 0;
}
