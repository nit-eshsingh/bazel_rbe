#ifndef STACK_H
#define STACK_H

typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
    int size;
} Stack;

// Stack operations
Stack* create_stack();
void stack_push(Stack* stack, int data);
int stack_pop(Stack* stack);
int stack_peek(Stack* stack);
int stack_is_empty(Stack* stack);
int stack_size(Stack* stack);
void stack_destroy(Stack* stack);

#endif // STACK_H
