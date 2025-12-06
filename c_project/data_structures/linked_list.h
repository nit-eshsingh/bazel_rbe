#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    int size;
} LinkedList;

// Linked list operations
LinkedList* create_list();
void list_append(LinkedList* list, int data);
void list_prepend(LinkedList* list, int data);
int list_get(LinkedList* list, int index);
void list_remove(LinkedList* list, int index);
int list_size(LinkedList* list);
void list_print(LinkedList* list);
void list_destroy(LinkedList* list);

#endif // LINKED_LIST_H
