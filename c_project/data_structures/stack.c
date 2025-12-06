#include "stack.h"
#include <stdlib.h>

Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void stack_push(Stack* stack, int data) {
    if (!stack) return;
    
    StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}

int stack_pop(Stack* stack) {
    if (!stack || !stack->top) return -1;
    
    StackNode* temp = stack->top;
    int data = temp->data;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
    
    return data;
}

int stack_peek(Stack* stack) {
    if (!stack || !stack->top) return -1;
    return stack->top->data;
}

int stack_is_empty(Stack* stack) {
    return stack && stack->top == NULL;
}

int stack_size(Stack* stack) {
    return stack ? stack->size : 0;
}

void stack_destroy(Stack* stack) {
    if (!stack) return;
    
    while (stack->top) {
        StackNode* temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
    free(stack);
}
