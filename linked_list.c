//
// Created by mrtn on 15. 03. 21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

/* Struct definitions */
typedef struct Node {
    struct Node* next;
    char* value;
} Node;

typedef struct LinkedList {
    Node* first;
    Node* last;
    int count;
    int max_size;
} LinkedList;


/* Static function declarations */
static void _ll_insert(LinkedList* list, char* value, int position);


static Node* node_new(char* value) {
    Node* node = malloc(sizeof(Node));
    // Copy value to the Node value.
    node->value = malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(node->value, value);
    node->next = NULL;
    return node;
}

LinkedList* ll_new(int max_size) {
    LinkedList* list = malloc(sizeof(LinkedList));
    list->max_size = max_size;
    list->count = 0;
    list->first = NULL;
    list->last = NULL;
    return list;
}

void ll_prepend(LinkedList* list, char* value) {
    Node* node = node_new(value);
    node->next = list->first;

    // Update first and last node.
    list->first = node;
    if (list->last == NULL)
        list->last = node;

    list->count++;
    // TODO: delete last element if there are too many elements in the list.
}

void ll_append(LinkedList* list, char* value) {
    Node* node = node_new(value);

    if (!ll_is_empty(list))
        list->last->next = node;
    else
        list->first = node;
    list->last = node;

    list->count++;
}

/**
 * Insert value at given position in list.
 * @param list List to insert the value into.
 * @param value Value ot insert.
 * @param position Position at which to insert the value.
 * @return 1 if successful, 0 otherwise.
 */
int ll_insert(LinkedList* list, char* value, int position) {
    if (position > list->count || position < 0)
        return 0;

    // Handle first and last position and finally insert if need be.
    if (position == 0)
        ll_prepend(list, value);
    else if (position == list->count)
        ll_append(list, value);
    else
        _ll_insert(list, value, position);

    return 1;
}

//void ll_remove(LinkedList* list, char* value) {
//    if (ll_count(list) == 0)
//        return;
//
//    Node* node = list->first;
//    while () {
//    }
//}

int ll_is_empty(LinkedList* list) {
    return list->count == 0;
}

void ll_print(LinkedList* list) {
    Node* node = list->first;
    while (node) {
        printf("%s\n", node->value);
        node = node->next;
    }
}

int ll_count(LinkedList* list) {
    return list->count;
}


/* Static functions */
static void _ll_insert(LinkedList* list, char* value, int position) {
    Node* iter = list->first;
    for (int i = 0; i < position-1; i++)
        iter = iter->next;

    Node* node = node_new(value);
    node->next = iter->next;
    iter->next = node;
    list->count++;
}