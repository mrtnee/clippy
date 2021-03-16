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
static char* _ll_remove_first_element(LinkedList* list);
static char* _ll_remove_last_element(LinkedList* list);
static char* _ll_remove(LinkedList* list, char* value);
static char* _ll_remove_at(LinkedList* list, int position);


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
//    while (node) {
//    }
//}

char* ll_remove_at(LinkedList* list, int position) {
    if (position < 0 || position >= ll_count(list))
        return NULL;

    char* value;
    if (position == 0)
        value = _ll_remove_first_element(list);
    else
        value = _ll_remove_at(list, position);

    list->count--;
    return value;
}

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

void ll_empty(LinkedList* list) {
    Node* iter = list->first;
    Node* tmp;
    while (iter) {
        free(iter->value);
        tmp = iter;
        iter = iter->next;
        free(tmp);
    }
    list->count = 0;
    list->first = NULL;
    list->last = NULL;
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

static char* _ll_remove_first_element(LinkedList* list) {
    Node* node = list->first;

    list->first = node->next;
    if (ll_count(list) == 1)
        list->last = NULL;

    char* value = node->value;
    free(node);
    return value;
}

// Assume that at least one element is before the element
// at position <position>.
static char* _ll_remove_at(LinkedList* list, int position) {
    Node* iter = list->first;
    for (int i = 0; i < position-1; i++)
        iter = iter->next;

    Node* node = iter->next;
    iter->next = node->next;
    if (position == ll_count(list) - 1)
        list->last = iter;

    char* value = node->value;
    free(node);
    return value;
}