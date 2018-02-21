#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"

const struct zoo {
    const char *id;
    const char *species;
} animals[] = {
    {"123456", "Dog" },
    {"234567", "Bear" },
    {"777777", "Pink Fairy Armadillo" },  // this is actual species, I googled!
    {"aaaaaaaaa", "Chlamyphorus truncatus" },
    {"666666", "Mosquito" }
};

int main()
{
    /* testing exercise. Feel free to modify this function */

    My_Queue *q = Q_init();
    
    for (unsigned int i = 0; i < sizeof(animals) / sizeof(struct zoo); i++) {
        if (Q_enqueue(q, animals[i].id, animals[i].species))
            printf("i = %d, firstspecies: %s\n", i, Q_firstSpecies(q));
    }
    
    Q_drop(q, "777777");
    
    while (Q_dequeue(q)) {
        if (Q_firstSpecies(q))
            printf("dequeue, firstspecies: %s\n", Q_firstSpecies(q));
        else
            printf("My_Queue is empty\n");
    }
    
    Q_delete(q);
}
