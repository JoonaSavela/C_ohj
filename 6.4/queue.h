#ifndef QUEUE_H
#define QUEUE_H

typedef struct my_queue My_Queue;

/* Allocates and initializes a new queue.
 * 
 * Returns: pointer to an empty queue
 */
My_Queue *Q_init(void);

/* Adds a new member with given animal ID <id> and species <species> to the
 * end of queue <q>.
 * 
 * Returns: 1 if addition was successful, 0 if addition failed. Addition fails,
 * for example if animal ID has more than 6 characters.
 */
int Q_enqueue(My_Queue *q, const char *id, const char *species);

/* Returns the animal ID of the first member of the queue,
 * or NULL if the queue is empty.
 */
char *Q_firstID(My_Queue *q);

/* Returns the animal species of the first member of the queue,
 * or NULL if the queue is empty.
 */
char *Q_firstSpecies(My_Queue *q);

/* Removes the first member of queue.
 * 
 * Returns: 1 if something was removed,
 * 0 if nothing was removed, i.e., the queue was already empty
 */
int Q_dequeue(My_Queue *q);

/* Drops the given animal with animal ID <id> from queue <q>.
 * Only the first instance with matching ID is dropped.
 * 
 * Returns: 1 if something was removed,
 * 0 if nothing was removed, i.e., matching animal ID was not found.
 */
int Q_drop(My_Queue *q, const char *id);

/* Delete whole queue and all memory allocated for it
 */
void Q_delete(My_Queue *q);


#endif
