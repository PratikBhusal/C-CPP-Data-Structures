#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// #include "compare.h"
// #include "print.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  LinkedList {{{
typedef struct Node Node;
typedef struct LinkedList LinkedList;
struct LinkedList
{
    struct Node// {{{
    {
        size_t data_size;
        void* data;
        struct Node *next;

        void (*print)   (const void *self);
        int  (*compare) (const void *self, const void *other);
    } *head;// }}}
    size_t size;

    int                (*compare)      (const void *self, const void *other);
    void               (*print)        (const void *node);

    bool               (*insert_front) (LinkedList *ll, const size_t data_size,
                                        const void* data);
    bool               (*insert_back)  (LinkedList *ll, const size_t data_size,
                                        const void* data);
    const Node *const  (*remove)       (LinkedList *ll, const void* data);
    void               (*print_list)   (const LinkedList *ll);
    bool               (*contains)     (const LinkedList *ll, const void* val);
    const Node *const  (*get)          (const LinkedList *ll, const void* val);
};// LinkedList }}}

Node* new_Node(size_t data_size, const void* data,
               int  (*compare) (const void*, const void*),
               void (*print)   (const void*) );

LinkedList* LinkedList_construct(int  (*compare) (const void*, const void*),
        void (*print)   (const void*) );
void  LinkedList_destruct(LinkedList **ll_ref);
bool  LinkedList_insert_val_back(LinkedList *ll, const size_t data_size,
                                 const void* data);
bool  LinkedList_insert_val_front(LinkedList *ll, const size_t data_size,
                                  const void* data);
const Node *const LinkedList_remove(LinkedList *ll, const void* data);
void  LinkedList_print_list(const LinkedList *ll);
bool LinkedList_contains(const LinkedList *ll, const void* data);
const Node *const LinkedList_get(const LinkedList *ll, const void* data);
//  }}}

#endif // ifndef LINKED_LIST_H
