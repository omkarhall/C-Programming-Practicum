/*
 * file: q.h
 * desc:  specification of functions implementing a queue Abstract
 *   Data Type.  Recall that a queue has a first-in-first out policy.
 *   Fundamental operations are
 *
 *      q_enqueue:  to add an element at the end of a queue
 *      q_dequque:  to remove the first element of a queue (if non-empty).
 *
 * NOTES:  the elements of the queue are unsigned integers.
 *
 */




/* Actual specification of q_struct "hidden" in q.c */
typedef struct q_struct QUEUE;

/*
 * function: q_create
 * desc:  allocates and initializes a queue. Returns it
 *   as a pointer
 *   */
extern QUEUE * q_create();

/*
 * function: q_destroy
 * desc:  deallocates all dynamically allocated memory assocated
 *   with queue passed by parameter 1
 */
extern void q_destroy(QUEUE *q);

/*
 * function: q_is_empty
 * desc:  returns 1 if q is empty; returns 0 otherwise
 */
extern int q_is_empty(QUEUE *q);


/*
 * function: q_enqueue
 * desc:  adds integer val to the "end" of queue passed as q
 * requirements:  must be a constant time operation (O(1))
 */
extern void q_enqueue(QUEUE *q, unsigned val);

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
extern int q_dequeue(QUEUE *q, unsigned *pval);

