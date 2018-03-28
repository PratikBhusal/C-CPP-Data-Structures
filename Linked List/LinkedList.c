#include "LinkedList.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//  Node {{{
Node* new_Node()// {{{
{
    Node *newNode = (Node*)malloc( sizeof(Node) );
    newNode->num = 0;
    newNode->next = NULL;
    return newNode;
}// }}}
//  }}}

//  LinkedList {{{
LinkedList* LinkedList_construct()// {{{
{
    LinkedList *newList = (LinkedList*)malloc( sizeof(LinkedList) );
    newList->head = NULL;

    newList->destruct     = LinkedList_destruct;
    newList->insert_back  = LinkedList_insert_val_back;
    newList->insert_front = LinkedList_insert_val_front;
    newList->delete       = LinkedList_delete;
    newList->print        = LinkedList_print;
    newList->contains     = LinkedList_contains;

    return newList;
}// }}}

void LinkedList_destruct(LinkedList *this)// {{{
{
    Node *temp = NULL;
    while (this->head != NULL) {
        temp = this->head->next;

        // printf("Location before deletion: %p\n", (void*)this->head);

        free(this->head);
        this->head = temp;

        // printf("Location after deletion:  %p\n", (void*)this->head);
    }
}// }}}

bool LinkedList_insert_val_back(LinkedList *this, int val)// {{{
{
    if (this->head == NULL) {
        this->head = new_Node();
        this->head->num = val;
        this->head->next = NULL;
    }
    else {
        Node *curr = this->head;
        while (curr->next != NULL) {
            curr = curr->next;
        }

        curr->next = new_Node();
        curr->next->num = val;
    }

    return true;
}// }}}

bool LinkedList_insert_val_front(LinkedList *this, int val)// {{{
{
    if (this->head == NULL) {
        this->head = new_Node();
        this->head->num = val;
    }
    else {
        Node *newHead = new_Node();
        newHead->num = val;
        newHead->next = this->head;
        this->head = newHead;
    }

    return true;
}// }}}

Node* LinkedList_delete(LinkedList *this, int val)// {{{
{
    Node **curr_ref = &(this->head);

    // Find Node
    while (*curr_ref && (*curr_ref)->num != val) {
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

void LinkedList_print(const LinkedList *this)// {{{
{
    Node *curr = this->head;

    while (curr != NULL) {
        // printf("%p: %d\n", (void*)curr, curr->num);
        printf("%d\n", curr->num);
        curr = curr->next;
    }
}// }}}

Node* LinkedList_contains(const LinkedList *this, const int val)// {{{
{
    Node *curr = this->head;

    while (curr != NULL && curr->num != val) {
        curr = curr->next;
    }

    return curr;
}// }}}
//  }}}
