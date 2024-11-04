#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem_i.h"

#define INPUT_SIZE 256

void phmemstatic_command() {
    int size = atoi(strtok(NULL, " "));
    printf("Writing/Realocating %d bytes", size);
    physical_resize(size);
}

void phmem_command() {
    int size = memi_size + atoi(strtok(NULL, " "));
    printf("Expanding/Decreasing/Realocating %d bytes", size);
    physical_resize(size);
}

void free_command() {
    int pointer = atoi(strtok(NULL, " "));
    int size = atoi(strtok(NULL, " "));
    malloc_i(pointer, size, NULL);
}

void read_command() {
    int pointer = atoi(strtok(NULL, " "));
    int size = atoi(strtok(NULL, " "));
    bool* result = mem_read_i(pointer, size);
    
    for(int i = 0; i < size; i++) {
        if(result[i]) printf("1"); else printf("0");
    
        if(i % 64 == 63) {
            printf("\n");
            continue;
        }

        if(i % 32 == 31) {
            printf(" ");
        }
    }

    free(result);
}

void write_command() {
    int pointer = atoi(strtok(NULL, " "));
    char* token = strtok(NULL, " ");
    bool* data = (bool*) malloc(sizeof(bool) * strlen(token));
    
    if(data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    } 

    for(int i = 0; i < strlen(token); i++) {
        data[i] = (token[i] == '1');
    }

    malloc_i(pointer, strlen(token), data);
    free(data); 
}

void help_command() {
    printf("phmemstatic <size>: resize bytes of physical memory to <size>\n");
    printf("phmem <size>: increase/decrease bytes of physical memory by <size>\n");
    printf("free <pointer> <size>: free memory at <pointer> by <size>\n");
    printf("read <pointer> <size>: read <size> bytes from memory at <pointer>\n");
    printf("write <pointer> <data>: write <data> to memory at <pointer>\n");
    printf("infolen: show length of physical memory");
}

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
        if(strcmp(token, "exit") == 0)             return 0;
        else if(strcmp(token, "help") == 0)        help_command();
        else if(strcmp(token, "phmemstatic") == 0) phmemstatic_command();
        else if(strcmp(token, "phmem") == 0)       phmem_command();
        else if(strcmp(token, "free") == 0)        free_command();
        else if(strcmp(token, "read") == 0)        read_command();
        else if(strcmp(token, "write") == 0)       write_command();
        else if(strcmp(token, "infolen") == 0) {
            printf("Length of physical memory: %d", memi_size);
        } else {
            printf("%s is not a command!", token);
        }
    }

    return 0;
}
