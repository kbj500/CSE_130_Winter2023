#include "queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

struct queue {

    // dynamic array to store queue elements
    void **elements;

    int size;
    //int start;
    //int end;

    //front anf back of array? or just ascending order
    //

    sem_t empty;
    sem_t full;
    sem_t mutex;
};

typedef struct queue queue_t;

/** @brief Dynamically allocates and initializes a new queue with a
 *         maximum size, size
 *
 *  @param size the maximum size of the queue
 *
 *  @return a pointer to a new queue_t
 */
queue_t *queue_new(int size) {

    //int rc = 0;

    queue_t *q = malloc(sizeof(queue_t));

    q->elements = (void **) calloc(size, sizeof(void *));

    q->size = size;

    //q->start = 0;

    //q->end = 0;

    sem_init(&(q->empty), 0, 1);

    sem_init(&(q->full), 0, size);

    sem_init(&(q->mutex), 0, 1);

    return q;
}

/** @brief Delete your queue and free all of its memory.
 *
 *  @param q the queue to be deleted.  Note, you should assign the
 *  passed in pointer to NULL when returning (i.e., you should set
 *  *q = NULL after deallocation).
 *
 */
void queue_delete(queue_t **q) {

    sem_destroy(&((*q)->empty));
    sem_destroy(&((*q)->full));
    sem_destroy(&((*q)->mutex));
    free(*q);
    *q = NULL;
}

/** @brief push an element onto a queue
 *
 *  @param q the queue to push an element into.
 *
 *  @param elem th element to add to the queue
 *
 *  @return A bool indicating success or failure.  Note, the function
 *          should succeed unless the q parameter is NULL.
 */
bool queue_push(queue_t *q, void *elem) {

    sem_wait(&(q->full));
    sem_wait(&(q->mutex));

    if (q == NULL)
        return false;

    for (int i = 0; i < q->size; i++) {

        if (q->elements[i] == NULL) {

            q->elements[i] = elem;
            //printf("\nnull at %d\n", i);

            //printf("\nElem: %d\n", *(int *) elem);
            //printf("\nSuccessful push: %d, i=%d\n", *(int *) q->elements[i], i);
            // return true;
            break;
        }
    }

    //printf("\nSuccessful push: %d\n", *(int *) q->elements[0]);

    sem_post(&(q->mutex));
    sem_post(&(q->empty));

    return true;
}

/** @brief pop an element from a queue.
 *
 *  @param q the queue to pop an element from.
 *
 *  @param elem a place to assign the poped element.
 *
 *  @return A bool indicating success or failure.  Note, the function
 *          should succeed unless the q parameter is NULL.
 */
bool queue_pop(queue_t *q, void **elem) {

    sem_wait(&(q->empty));
    sem_wait(&(q->mutex));

    if (q == NULL || q->elements[0] == NULL) {
        printf("\nfalse pop\n");
        return false;
    }
    //printf("\n first element value: %d", *(int *) q->elements[0]);

    //int j = 2;
    *elem = q->elements[0];

    //printf("\n first element value: %d", *(int *) q->elements[0]);
    //printf("\n first element pointer: %p", q->elements[0]);
    //*elem = NULL;
    //want to set address pointed to by elem to value in void array

    /*int temp = *(int *) q->elements[0];

    printf("\n first element value: %d", *(int *) q->elements[0]);

    printf("\n first element pointer: %p", q->elements[0]);

    printf("\n value popped: %d", temp);

    *elem = NULL;*/

    //printf("\n elem value: %d", *(int *) elem);

    for (int i = 0; i < q->size; i++) {

        if (i == (q->size) - 1) {
            q->elements[i] = NULL;
        } else {
            q->elements[i] = q->elements[i + 1];
        }
    }

    sem_post(&(q->mutex));
    sem_post(&(q->full));

    return true;
}
