/*
 * file: q.c
 * desc:  implementation of the queue ADT specified in q.h
 *
 * NOTES: empty function "stubs" are provided below.
 *
 */
#include "q.h"
#include <stdio.h>
#include <stdlib.h>
/*
 * Struct for nodes of linked list used to make queue
 */
struct node {
    unsigned int val;
    struct node* next;
};
typedef struct node NODE;

/* specification of q_struct here; Note that QUEUE is
 * "aliased" to this struct in q.h
 */
struct q_struct {
    struct node* head;
    struct node* tail;
    int size;
    
    // decide on the fields you want/need to encapsulate a
    // queue here.
};

/*
 * Helper function that adds new nodes to queue
 */
NODE* newNode(unsigned int n){
    NODE* temp = malloc(sizeof(NODE));
    temp->val = n;
    temp->next = NULL;
    return temp;
}

/*
 * function: q_create
 * desc:  allocates and initializes a queue. Returns it
 *   as a pointer
 *   */
QUEUE* q_create() {
    QUEUE* queue = malloc(sizeof(QUEUE));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    return queue;
    
}

/*
 * function: q_destroy
 * desc:  deallocates all dynamically allocated memory assocated
 *   with queue passed by parameter 1
 */
void q_destroy(QUEUE *q) {
    if (q == NULL){
        return;
    }
    NODE* prev = NULL;
    NODE* current = q->head;
    
    while (current != NULL){
        prev = current;
        current = current->next;
        free(prev);
        q->size--;
    }
    q->head = NULL;
    q->tail = NULL;
    free(q);
}

/*
 * function: q_is_empty
 * desc:  returns 1 if q is empty; returns 0 otherwise
 */
int q_is_empty(QUEUE *q) {
    if (q->size == 0){
        return 1;
    }
    return 0;
}


/*
 * function: q_enqueue
 * desc:  adds integer val to the "end" of queue passed as q
 * requirements:  must be a constant time operation (O(1))
 */
void q_enqueue(QUEUE *q, unsigned val) {
    NODE* temp = newNode(val);
    //if queue is empty
    if(q_is_empty(q) == 1){
        q->head = temp;
        q->tail = temp;
    }
    else{
        q->tail->next = temp;
        q->tail = temp;
    }
    q->size++;
}

/*
 * function: q_dequeue
 * desc:
 *     o if given queue is non-empty, the first element is
 *        removed and "passed back" to the caller "by pointer" via
 *        pointer pval; 1 is returned indicating "success"
 *     o if the queue IS empty, 0 is returned indicating failure.
 *        *pval has no meaning in this scenario (since there is
 *        nothing to dequeue).
 * requirements:  must be a constant time operation (O(1)).
 */
int q_dequeue(QUEUE *q, unsigned *pval) {
    if (q_is_empty(q) == 1){
        return 0;
    }
    *pval = q->head->val;
    if (q->size == 1){
        NODE* temp = q->head;
        free(temp);
        q->head = NULL;
        q->tail = NULL;
        q->size--;
    }
    else{
        NODE* temp = q->head;
        q->head = q->head->next;
        free(temp);
        q->size--;
    }
    return 1;

}

