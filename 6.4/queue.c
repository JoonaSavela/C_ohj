#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "queuepriv.h"

My_Queue *Q_init(void)
{
    My_Queue *q = calloc(1, sizeof(My_Queue));
    return q;
}

int Q_enqueue(My_Queue *q, const char *id, const char *species)
{
    if (strlen(id) > 6) return 0;
    struct animal *new = malloc(sizeof(struct animal));
    strcpy(new->id, id);
    new->species = malloc((strlen(species) + 1) * sizeof(char));
    strcpy(new->species, species);
    new->next = NULL;

    if (!q) {
        q = Q_init();
    }

    if (!q->first) {
        q->first = new;
    } else {
        q->last->next = new;
    }

    q->last = new;

    return 1;
}

char *Q_firstID(My_Queue *q)
{
    if (q && q->first)
        return q->first->id;
    else
        return NULL;
}

char *Q_firstSpecies(My_Queue *q)
{
    if (q && q->first)
        return q->first->species;
    else
        return NULL;
}

int Q_dequeue(My_Queue *q)
{
    if (!q || !q->first) return 0;

    struct animal *f = q->first;

    if (f == q->last) {
        q->last = NULL;
    }

    q->first = f->next;
    free(f->species);
    free(f);

    return 1;
}

int Q_drop(My_Queue *q, const char *id)
{ 
    if (strlen(id) > 6 || !q || !q->first) return 0;
    struct animal *a = q->first;
    struct animal *prev = NULL;

    while (a) {
        if (strcmp(id, a->id) == 0) {
            if (!prev) {
                q->first = a->next;
            } else {
                if (a == q->last) q->last = prev;
                prev->next = a->next;
            }
            free(a->species);
            free(a);
            return 1;
        }
        prev = a;
        a = a->next;
    }

    return 0;
}

void Q_delete(My_Queue *q)
{
    if (q) {
        while(Q_dequeue(q));
        free(q);
    }
}
