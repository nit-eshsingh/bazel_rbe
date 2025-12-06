#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

LinkedList* create_list() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void list_append(LinkedList* list, int data) {
    if (!list) return;
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    
    if (!list->head) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
}

void list_prepend(LinkedList* list, int data) {
    if (!list) return;
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

int list_get(LinkedList* list, int index) {
    if (!list || index < 0 || index >= list->size) return -1;
    
    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

void list_remove(LinkedList* list, int index) {
    if (!list || index < 0 || index >= list->size) return;
    
    if (index == 0) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
    } else {
        Node* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node* temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    list->size--;
}

int list_size(LinkedList* list) {
    return list ? list->size : 0;
}

void list_print(LinkedList* list) {
    if (!list) return;
    
    printf("[");
    Node* current = list->head;
    while (current) {
        printf("%d", current->data);
        if (current->next) printf(", ");
        current = current->next;
    }
    printf("]\n");
}

void list_destroy(LinkedList* list) {
    if (!list) return;
    
    Node* current = list->head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}
