//
// Created by mrtn on 15. 03. 21.
//

#ifndef CLIPBOARD_LINKED_LIST_H
#define CLIPBOARD_LINKED_LIST_H

struct Node {
    struct Node* next;
    char* value;
} typedef Node;

struct LinkedList {
    Node* first;
    Node* last;
    int count;
    int max_size;
} typedef LinkedList;

LinkedList linked_list_new(int max_size);

#endif //CLIPBOARD_LINKED_LIST_H
