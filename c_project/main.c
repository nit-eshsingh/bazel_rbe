#include <stdio.h>
#include <stdlib.h>
#include "c_project/math_utils.h"
#include "c_project/string_utils/string_utils.h"
#include "c_project/data_structures/linked_list.h"
#include "c_project/data_structures/stack.h"

int main() {
    printf("=================================\n");
    printf("C Project - Integrated Demo\n");
    printf("=================================\n\n");
    
    // Math utilities
    int a = 10, b = 20;
    printf("1. Math Utilities:\n");
    printf("   %d + %d = %d\n", a, b, add(a, b));
    printf("   %d * %d = %d\n", a, b, multiply(a, b));
    
    // String utilities
    printf("\n2. String Utilities:\n");
    const char* original = "Hello Bazel";
    char* upper = string_to_upper(original);
    char* lower = string_to_lower(original);
    printf("   Original: %s\n", original);
    printf("   Uppercase: %s\n", upper);
    printf("   Lowercase: %s\n", lower);
    free(upper);
    free(lower);
    
    // Data structures - Linked List
    printf("\n3. Data Structures - Linked List:\n");
    LinkedList* list = create_list();
    list_append(list, 10);
    list_append(list, 20);
    list_append(list, 30);
    list_prepend(list, 5);
    printf("   List contents: ");
    list_print(list);
    printf("   List size: %d\n", list_size(list));
    list_destroy(list);
    
    // Data structures - Stack
    printf("\n4. Data Structures - Stack:\n");
    Stack* stack = create_stack();
    stack_push(stack, 100);
    stack_push(stack, 200);
    stack_push(stack, 300);
    printf("   Stack peek: %d\n", stack_peek(stack));
    printf("   Stack pop: %d\n", stack_pop(stack));
    printf("   Stack size: %d\n", stack_size(stack));
    stack_destroy(stack);
    
    printf("\n=================================\n");
    return 0;
}
