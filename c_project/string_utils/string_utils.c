#include "string_utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* string_to_upper(const char* str) {
    if (!str) return NULL;
    
    size_t len = strlen(str);
    char* result = (char*)malloc(len + 1);
    
    for (size_t i = 0; i < len; i++) {
        result[i] = toupper(str[i]);
    }
    result[len] = '\0';
    
    return result;
}

char* string_to_lower(const char* str) {
    if (!str) return NULL;
    
    size_t len = strlen(str);
    char* result = (char*)malloc(len + 1);
    
    for (size_t i = 0; i < len; i++) {
        result[i] = tolower(str[i]);
    }
    result[len] = '\0';
    
    return result;
}

size_t string_length(const char* str) {
    return str ? strlen(str) : 0;
}

char* string_concat(const char* str1, const char* str2) {
    if (!str1 && !str2) return NULL;
    if (!str1) return strdup(str2);
    if (!str2) return strdup(str1);
    
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char* result = (char*)malloc(len1 + len2 + 1);
    
    strcpy(result, str1);
    strcat(result, str2);
    
    return result;
}

int string_compare(const char* str1, const char* str2) {
    if (!str1 && !str2) return 0;
    if (!str1) return -1;
    if (!str2) return 1;
    
    return strcmp(str1, str2);
}
