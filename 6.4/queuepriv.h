#ifndef MY_QUEUEPRIV_H
#define MY_QUEUEPRIV_H

#include "queue.h"

/* One animal in linked list*/
struct animal {
    char id[7];  // animal ID: 6 characters + '\0'
    char *species;  // species of animal, allocated dynamically
    struct animal *next;  // next animal in linked list
};

/* For storing the first and last item in linked list
 * If list is empty, both <first> and <last> are NULL
 * If list has one element, <first> and <last> point to the same place
 */
struct my_queue {
    struct animal *first;
    struct animal *last;
};

#endif
