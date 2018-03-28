#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdbool.h>

//  Node {{{
typedef struct Node// {{{
{
    int num;
    struct Node *next;
}Node;// }}}

Node* new_Node();
//  }}}

//  LinkedList {{{
typedef struct LinkedList// {{{
{
    struct Node *head;

    void  (*destruct)     (struct LinkedList *this);
    bool  (*insert_front) (struct LinkedList *this, const int val);
    bool  (*insert_back)  (struct LinkedList *this, const int val);
    Node* (*delete)       (struct LinkedList *this, const int val);
    void  (*print)        (const struct LinkedList *this);
    Node* (*contains)     (const struct LinkedList *this, const int val);
}LinkedList;// }}}

LinkedList* LinkedList_construct();
void  LinkedList_destruct(LinkedList *this);
bool  LinkedList_insert_val_back(LinkedList *this, int val);
bool  LinkedList_insert_val_front(LinkedList *this, int val);
Node* LinkedList_delete(LinkedList *this, int val);
void  LinkedList_print(const LinkedList *this);
Node* LinkedList_contains(const LinkedList *this, int val);
//  }}}

#endif // ifndef LINKED_LIST_H
