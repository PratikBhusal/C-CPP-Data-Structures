#include "LinkedList.h"

//  Node {{{
Node* new_Node(const size_t data_size, const void *const data,
               int (*compare)(const void*, const void*),
               void (*print) (const void*) )
// {{{
{
    Node *newNode = (Node*)malloc( sizeof(Node) );

    newNode->data_size = data_size;
    newNode->data = malloc(data_size);
    memcpy(newNode->data, data, data_size);
    newNode->next = NULL;

    newNode->compare = compare;
    newNode->print   = print;

    return newNode;
}// }}}
//  }}}

//  LinkedList {{{
LinkedList* LinkedList_construct(int  (*compare) (const void*, const void*),
        void (*print)   (const void*) )
// {{{
{
    LinkedList *newList = (LinkedList*) malloc( sizeof(LinkedList) );

    newList->head = NULL;
    newList->size = 0;

    newList->compare      = compare;
    newList->contains     = LinkedList_contains;
    newList->get          = LinkedList_get;
    newList->insert_back  = LinkedList_insert_val_back;
    newList->insert_front = LinkedList_insert_val_front;
    newList->print        = print;
    newList->print_list   = LinkedList_print_list;
    newList->remove       = LinkedList_remove;

    return newList;
}// }}}

void LinkedList_destruct(LinkedList **ll_ref)// {{{
{
    Node *temp = NULL;

    while ( (*ll_ref)->head != NULL ) {
        temp = (*ll_ref)->head->next;

        // printf("Location before deletion: %p\n", (void*)(*ll_ref)->head);

        free( (*ll_ref)->head->data );
        (*ll_ref)->head->data = NULL;

        free( (*ll_ref)->head );
        (*ll_ref)->head = temp;

        // printf("Location after deletion: %p\n", (void*)(*ll_ref)->head);
    }

    free(*ll_ref);
    *ll_ref = NULL;

}// }}}

bool LinkedList_insert_val_back(LinkedList *const ll, const size_t data_size,
                                const void *const data)
// {{{
{
    if (ll->head == NULL) {
        ll->head = new_Node(data_size, data, ll->compare, ll->print);
    }
    else {
        Node *curr = ll->head;
        while (curr->next != NULL) {
            curr = curr->next;
        }

        curr->next = new_Node(data_size, data, ll->compare, ll->print);

        if (!curr->next) {
            return false;
        }
    }

    ++(ll->size);
    return true;
}// }}}

bool LinkedList_insert_val_front(LinkedList *const ll, const size_t data_size,
                                 const void *const data)
// {{{
{
    Node *newHead = new_Node(data_size, data, ll->compare, ll->print);

    if (!newHead) {
        return false;
    }

    if (ll->head == NULL) {
        ll->head = newHead;
    }
    else {
        newHead->next = ll->head;
        ll->head = newHead;
    }

    ++(ll->size);
    return true;
}// }}}

const Node *const LinkedList_remove(LinkedList *const ll, const void *const data)// {{{
{
    Node **curr_ref = &(ll->head);

    // Find Node
    while (*curr_ref && (*curr_ref)->compare( (*curr_ref)->data, data) != 0 ) {
        curr_ref = &( (*curr_ref)->next );
    }

    // If node was not found
    if (*curr_ref == NULL) {
       return NULL;
    }

    // Get the Node to Delete
    Node *deletedNode = *curr_ref;

    // Remove Node from Linked List
    *curr_ref = (*curr_ref)->next;

    // Set the deleted node's next pointer to NULL
    deletedNode->next = NULL;

    return deletedNode;
}// }}}

void LinkedList_print_list(const LinkedList *const ll)// {{{
{
    const Node *curr = ll->head;

    while (curr != NULL) {
        curr->print(curr->data);
        printf("\n");
        curr = curr->next;
    }
}// }}}

bool LinkedList_contains(const LinkedList *const ll, const void *const data)// {{{
{
    const Node *curr = ll->head;

    while (curr != NULL && curr->compare( curr->data, data) != 0) {
        curr = curr->next;
    }

    // printf("\nAddress of curr: %p\n", &(curr) );
    // printf("Value of curr: %p\n\n", curr );

    return (curr) ? true : false;
}// }}}

const Node *const LinkedList_get(const LinkedList *const ll, const void *const data)// {{{
{
    const Node *curr = ll->head;

    while (curr != NULL && curr->compare( curr->data, data) != 0) {
        curr = curr->next;
    }

    // printf("\nAddress of curr: %p\n", &(curr) );
    // printf("Value of curr: %p\n\n", curr );

    return (curr)
        ? new_Node(curr->data_size, curr->data, curr->compare, curr->print)
        : NULL;
}// }}}

//  }}}
