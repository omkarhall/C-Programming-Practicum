//
//  sq.c
//  Project 6
//
//  Created by Omkar Halleppanavar on 11/13/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "sq.h"

struct Node {
    int val;
    struct Node* next; // Pointer to next node in DLL
    struct Node* prev; // Pointer to previous node in DLL
};
typedef struct Node NODE;

struct list_struct {
    NODE* front;
    NODE* back;
    int size;
};
typedef struct list_struct LIST;

struct service_queue {
    LIST* the_queue;
    LIST* buzzer_bucket;
    NODE** buzzer2node;
    int capacity; // capacity of buzzer2node
};

/*
 * Creates a node
 */
NODE* new_Node(int n){
    NODE* temp = malloc(sizeof(NODE));
    temp->val = n;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

/*
 * Creates a doubly linked list
 */
LIST* list_create(){
    LIST* list = malloc(sizeof(LIST));
    list->front = NULL;
    list->back = NULL;
    list->size = 0;
    return list;
}

/*
 * Helper function to double size of buzzer2node
 */
void grow(SQ* s){
    NODE** new_buzzer2node;
    int new_capacity = 2 * s->capacity;
    
    new_buzzer2node = malloc(new_capacity * sizeof(NODE*));
    for (int i = 0; i < s->capacity; i++){
        new_buzzer2node[i] = s->buzzer2node[i];
    }
    for (int i = s->capacity; i < new_capacity; i++){
        new_buzzer2node[i] = NULL;
    }
    free(s->buzzer2node);
    s->capacity = new_capacity;
    s->buzzer2node = new_buzzer2node;
}

/*
 * Helper funtion to pop node from front of linked list
 * Returns value of node that was popped
 */
int pop_front(LIST *l) {
    if(l->front == NULL) {
        return -1;
    }
    int ret = l->front->val;
    if (l->size == 1){
        NODE* temp = l->front;
        l->front = NULL;
        l->back = NULL;
        l->size = 0;
        free(temp);
    }
    if(l->front != NULL) {
        NODE* temp = l->front;
        l->front = l->front->next;
        free(temp);
        if(l->front != NULL){
            l->front->prev = NULL;
        }
        l->size--;
    }
    return ret;
}

/*
 * Helper function to push node to front of linked list
 * Returns pointer to node that was pushed
 */
NODE* push_front(LIST* l, int newElement){
    NODE* newNode = new_Node(newElement);
    newNode->next = l->front;
    if (l->front != NULL){
        l->front->prev = newNode;
    }
    if (l->front == NULL){
        l->back = newNode;
    }
    l->front = newNode;
    l->size++;
    return newNode;
}

/*
 * Helper function to push a node to the back of linked list
 * Returns pointer to node that was pushed
 */
NODE* push_back(LIST* l, int newElement) {
    NODE* newNode = new_Node(newElement);
      //newNode->val = newElement;
      //newNode->next = NULL;
      //newNode->prev = NULL;
    if(l->front == NULL) {
        l->front = newNode;
        l->back = newNode;
        l->size++;
    }
    else {
        l->back->next = newNode;
        newNode->prev = l->back;
        l->back = newNode;
        l->size++;
    }
    return newNode;
}

/*
 * Helper function to destroy linked lists
 */
void q_destroy(LIST *q) {
    if (q == NULL){
        return;
    }
    NODE* prev = NULL;
    NODE* current = q->front;
    
    while (current != NULL){
        prev = current;
        current = current->next;
        free(prev);
        q->size--;
    }
    q->front = NULL;
    q->back = NULL;
    free(q);
}

SQ* sq_create(){
    SQ* q = malloc(sizeof(SQ));
    q->the_queue = list_create();
    q->buzzer_bucket = list_create();
    q->capacity = 1;
    q->buzzer2node = malloc(sizeof(NODE*));
    q->buzzer2node[0] = NULL;
    return q;
}

void sq_free(SQ *q){
    q_destroy(q->the_queue);
    q_destroy(q->buzzer_bucket);
    free(q->buzzer2node);
    q->capacity = 0;
    free(q);
}

void sq_display(SQ *q){
    NODE* current = q->the_queue->front;
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}


int sq_length(SQ *q){
    return q->the_queue->size;
}

int sq_give_buzzer(SQ *q){
    int buzzer;
    NODE* p;
    if(q->buzzer_bucket->front != NULL) {
        buzzer = pop_front(q->buzzer_bucket);
    }
    else {
        buzzer = q->the_queue->size;
    }
    p = push_back(q->the_queue, buzzer);
    if (q->the_queue->size > q->capacity){
        grow(q);
    }
    q->buzzer2node[buzzer] = p;
    return buzzer;
}

int sq_seat(SQ *q){
    int buzzer;
    NODE* p;
    if (q->the_queue->front != NULL){
        buzzer = pop_front(q->the_queue);
        p = push_front(q->buzzer_bucket, buzzer);
        q->buzzer2node[buzzer] = p;
        return buzzer;
    }
    return -1;
}

int sq_kick_out(SQ *q, int buzzer){
    if(buzzer >= q->capacity || buzzer < 0){
       return 0;
    }
    if (q->buzzer2node[buzzer] != NULL){
        if (q->the_queue->front == q->buzzer2node[buzzer]){
            if(q->buzzer2node[buzzer]->next != NULL)
                q->buzzer2node[buzzer]->next->prev = NULL;
            q->the_queue->front = q->buzzer2node[buzzer]->next;
        }
        if (q->the_queue->back == q->buzzer2node[buzzer]){
            if(q->buzzer2node[buzzer]->next != NULL)
                q->buzzer2node[buzzer]->prev->next = NULL;
            q->the_queue->back = q->buzzer2node[buzzer]->prev;
        }
        if (q->buzzer2node[buzzer]->next != NULL){
            q->buzzer2node[buzzer]->next->prev = q->buzzer2node[buzzer]->prev;
        }
        if (q->buzzer2node[buzzer]->prev != NULL){
            q->buzzer2node[buzzer]->prev->next = q->buzzer2node[buzzer]->next;
        }
        q->the_queue->size--;
        free(q->buzzer2node[buzzer]);
        push_front(q->buzzer_bucket, buzzer);
        q->buzzer2node[buzzer] = NULL;
        return 1;
    }
    return 0;
}

int sq_take_bribe(SQ *q, int buzzer){
    if (buzzer >= q->capacity || buzzer < 0){
        return 0;
    }
    if (q->buzzer2node[buzzer] != NULL){
        if (q->the_queue->front == q->buzzer2node[buzzer]){
            q->the_queue->front = q->buzzer2node[buzzer]->next;
        }
        if (q->the_queue->back == q->buzzer2node[buzzer]){
            q->the_queue->back = q->buzzer2node[buzzer]->prev;
        }
        if (q->buzzer2node[buzzer]->next != NULL){
            q->buzzer2node[buzzer]->next->prev = q->buzzer2node[buzzer]->prev;
        }
        if (q->buzzer2node[buzzer]->prev != NULL){
            q->buzzer2node[buzzer]->prev->next = q->buzzer2node[buzzer]->next;
        }
        q->the_queue->size--;
        free(q->buzzer2node[buzzer]);
        NODE* p = push_front(q->the_queue, buzzer);
        q->buzzer2node[buzzer] = p;
        return 1;
    }
    return 0;
}
/*
#define N 1000000
#define J 500000

int main() {
    printf("N: %d\n", N);
    SQ *q = sq_create();
    for (int i = 0; i < N; i++) {
        sq_give_buzzer(q);
    }
    for (int i = J; i < N; i++) {
        sq_take_bribe(q, i);
    }
    for (int i = 0; i < J; i++) {
        sq_kick_out(q, i);
    }
    for (int i = 0; i < N; i++) {
        sq_seat(q);
    }
    sq_free(q);
    return 0;
}
*/
