#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stddef.h>

// String manipulation utilities
char* string_to_upper(const char* str);
char* string_to_lower(const char* str);
size_t string_length(const char* str);
char* string_concat(const char* str1, const char* str2);
int string_compare(const char* str1, const char* str2);

#endif // STRING_UTILS_H
