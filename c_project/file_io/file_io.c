#include "file_io.h"
#include <stdlib.h>
#include <string.h>

int write_to_file(const char* filename, const char* content) {
    if (!filename || !content) return -1;
    
    FILE* file = fopen(filename, "w");
    if (!file) return -1;
    
    fprintf(file, "%s", content);
    fclose(file);
    
    return 0;
}

char* read_from_file(const char* filename) {
    if (!filename) return NULL;
    
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* content = (char*)malloc(size + 1);
    if (!content) {
        fclose(file);
        return NULL;
    }
    
    fread(content, 1, size, file);
    content[size] = '\0';
    
    fclose(file);
    return content;
}

int file_exists(const char* filename) {
    if (!filename) return 0;
    
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

long get_file_size(const char* filename) {
    if (!filename) return -1;
    
    FILE* file = fopen(filename, "r");
    if (!file) return -1;
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    
    return size;
}
