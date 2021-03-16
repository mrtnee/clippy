//
// Created by mrtn on 15. 03. 21.
//

#ifndef CLIPBOARD_LINKED_LIST_H
#define CLIPBOARD_LINKED_LIST_H

typedef struct Node {
    struct Node* next;
    char* value;
} Node;

typedef struct LinkedList LinkedList;

LinkedList* ll_new(int max_size);
char* ll_get(LinkedList* list, int position);
Node* ll_first(LinkedList* list);
char* ll_next(Node* node);
void ll_prepend(LinkedList* list, char* value);
void ll_append(LinkedList* list, char* value);
int ll_insert(LinkedList* list, char* value, int position);
void ll_remove(LinkedList* list, char* value);
char* ll_remove_at(LinkedList* list, int position);
int ll_count(LinkedList* list);
int ll_is_empty(LinkedList* list);
void ll_empty(LinkedList* list);
void ll_print(LinkedList* list);


#endif //CLIPBOARD_LINKED_LIST_H
