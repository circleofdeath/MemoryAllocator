#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem_i.h"
#include "mem_t.h"

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

void readtype_command() {
    int pointer = atoi(strtok(NULL, " "));
    char* token = strtok(NULL, " ");

    if(strcmp(token, "ul") == 0)      printf("%lu", read_long_value(pointer));
    else if(strcmp(token, "ui") == 0) printf("%d",  read_int_value(pointer));
    else if(strcmp(token, "us") == 0) printf("%d",  read_short_value(pointer));
    else if(strcmp(token, "uc") == 0) printf("%d",  read_byte_value(pointer));
    else if(strcmp(token, "l") == 0)  printf("%ld", read_signed_long_value(pointer));
    else if(strcmp(token, "i") == 0)  printf("%d",  read_signed_int_value(pointer));
    else if(strcmp(token, "s") == 0)  printf("%d",  read_signed_short_value(pointer));
    else if(strcmp(token, "c") == 0)  printf("%d",  read_signed_byte_value(pointer));
    else {
        fprintf(stderr, "Invalid type\n");
    }
}

void writetype_command() {
    int pointer = atoi(strtok(NULL, " "));
    char* token = strtok(NULL, " ");
    char* value = strtok(NULL, " ");

    if(strcmp(token, "ul") == 0)      write_long_value(pointer,  strtoul(value, NULL, 10));
    else if(strcmp(token, "ui") == 0) write_int_value(pointer,   strtoul(value, NULL, 10));
    else if(strcmp(token, "us") == 0) write_short_value(pointer, strtoul(value, NULL, 10));
    else if(strcmp(token, "uc") == 0) write_byte_value(pointer,  strtoul(value, NULL, 10));
    else if(strcmp(token, "l") == 0)  write_signed_long_value(pointer,  atol(value));
    else if(strcmp(token, "i") == 0)  write_signed_int_value(pointer,   atol(value));
    else if(strcmp(token, "s") == 0)  write_signed_short_value(pointer, atol(value));
    else if(strcmp(token, "c") == 0)  write_signed_byte_value(pointer,  atol(value));
    else {
        fprintf(stderr, "Invalid type\n");
    }
}

void help_command() {
    printf("help: this command\n");
    printf("exit: exit programm\n");
    printf("phmemstatic <size>: resize bytes of physical memory to <size>\n");
    printf("phmem <size>: increase/decrease bytes of physical memory by <size>\n");
    printf("free <pointer> <size>: free memory at <pointer> by <size>\n");
    printf("read <pointer> <size>: read <size> bytes from memory at <pointer>\n");
    printf("write <pointer> <data>: write <data> to memory at <pointer>\n");
    printf("infolen: show length of physical memory\n\n");
    printf("readtype <pointer> <type>: read <type> from memory at <pointer>\n");
    printf("writetype <pointer> <type> <value>: write <type> <value> to memory at <pointer>\n\n");
    printf("types:\n");
    printf("  - ul: unsigned long\n");
    printf("  - ui: unsigned int\n");
    printf("  - us: unsigned short\n");
    printf("  - uc: unsigned char\n");
    printf("  - l:  long\n");
    printf("  - i:  int\n");
    printf("  - s:  short\n");
    printf("  - c:  char");
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
        else if(strcmp(token, "readtype") == 0)    readtype_command();
        else if(strcmp(token, "writetype") == 0)   writetype_command();
        else if(strcmp(token, "infolen") == 0) {
            printf("Length of physical memory: %d", memi_size);
        } else {
            printf("%s is not a command!", token);
        }
    }

    return 0;
}
