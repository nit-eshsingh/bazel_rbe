#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>

// File I/O operations
int write_to_file(const char* filename, const char* content);
char* read_from_file(const char* filename);
int file_exists(const char* filename);
long get_file_size(const char* filename);

#endif // FILE_IO_H
