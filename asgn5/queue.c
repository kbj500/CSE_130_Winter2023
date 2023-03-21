#include "queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct queue {

    // dynamic array to store queue elements
    char **elements;

    int size;
    int nElem;
    //int start;
    //int end;

    //front anf back of array? or just ascending order
    //
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

    q->elements = (char **) calloc(size, sizeof(char *));

    q->size = size;

    q->nElem = 0;
    //q->start = 0;

    //q->end = 0;

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
bool queue_push(queue_t *q, char *elem) {

    if (q == NULL || q->nElem == q->size) {
        fprintf(stderr, "\nfailed push\n");
        return false;
    }

    else {

        q->elements[q->nElem] = strdup(elem);
        q->nElem++;

        //printf("\nElem: %d\n", *(int *) elem);
        //printf("\nSuccessful push: %d, i=%d\n", *(int *) q->elements[i], i);
        // return true;
    }

    //printf("\nSuccessful push: %s\n", q->elements[q->nElem - 1]);
    //printf("\n N elements: %d\n", q->nElem);
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
bool queue_pop(queue_t *q, char **elem) {

    if (q == NULL || q->nElem == 0) {
        fprintf(stderr, "\nfalse pop\n");
        return false;
    }
    //printf("\n first element value: %d", *(int *) q->elements[0]);

    //int j = 2;
    *elem = q->elements[0];

    //printf("\n %s took out\n", *elem);
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

    for (int i = 0; i < q->nElem; i++) {

        if (i == (q->nElem) - 1) {
            q->elements[i] = NULL;
        } else {
            q->elements[i] = q->elements[i + 1];
        }
    }
    q->nElem--;

    //printf("\n N elements: %d\n", q->nElem);

    return true;
}

void printChar(queue_t *q) {
    if (!q->nElem) {
        fprintf(stderr, "\n queue empty\n");
        return;
    }
    for (int i = 0; i < q->size; i++) {
        printf("\n [%d] %s \n", i, q->elements[i]);
    }
}

int charFind(queue_t *q, char *elem) {

    //printf("buff: %s\n", elem);
    for (int i = 0; i < q->nElem; i++) {
        if (q->elements[i] == NULL) {
        } else if (strcmp(elem, q->elements[i]) == 0) {
            //printf("strcmp equal %s, %s\n", elem, q->elements[i]);
            return i;
        }
        //printf("strcmp not equal %s, [%d] %s\n", elem, i, q->elements[i]);
    }
    //printf("strcmp equal not equal %s\n", elem);
    return -1;
}

void reOrderChar(queue_t *q, int index) {

    for (int i = index; i < q->nElem - 1; i++) {
        char *holder = q->elements[i];
        q->elements[i] = q->elements[i + 1];
        q->elements[i + 1] = holder;
    }
}
bool qFull(queue_t *q) {
    if (q == NULL)
        return false;
    if (q->nElem == q->size)
        return true;
    return false;
}
