#include <stdlib.h>
#include <stdio.h>
#include "aaltogame.h"

Area *createArea(unsigned int xsize, unsigned int ysize)
{
    Area *new = malloc(sizeof(Area));
    new->xsize = xsize;
    new->ysize = ysize;
    new->cells = malloc(ysize * sizeof(Status *));

    for (unsigned int j = 0; j < ysize; j++) {
        new->cells[j] = malloc(xsize * sizeof(Status));
        for (unsigned int i = 0; i < xsize; i++) {
            new->cells[j][i] = DEAD;
        }
    }

    return new;
}

void releaseArea(Area *a)
{
    for (unsigned int j = 0; j < a->ysize; j++) {
        free(a->cells[j]);
    }
    free(a->cells);
    free(a);
}

void initArea(Area *a, unsigned int n)
{
    unsigned int tot = a->xsize * a->ysize;
    for (unsigned int k = 0; k < n; k++) {
        int r = rand() % tot;
        unsigned int j = r / a->xsize;
        unsigned int i = r % a->xsize;
        while (a->cells[j][i] == ALIVE) {
            r = rand() % tot;
            j = r / a->xsize;
            i = r % a->xsize;
        }
        a->cells[j][i] = ALIVE;
    }
}

void printArea(const Area *a)
{
    for (unsigned int j = 0; j < a->ysize; j++) {
        for (unsigned int i = 0; i < a->xsize; i++) {
            if (a->cells[j][i] == DEAD) {
                printf(".");
            } else {
                printf("*");
            }
        }
        printf("\n");
    }
}

void tick(Area *a)
{
    Status **new = malloc(a->ysize * sizeof(Status *));

    // create a new area
    for (unsigned int j = 0; j < a->ysize; j++) {
        new[j] = malloc(a->xsize * sizeof(Status));

        for (unsigned int i = 0; i < a->xsize; i++) {
            unsigned int n_alive = 0;
            
            for (int jj = j - 1; jj < j + 2; jj++) {
                for (int ii = i - 1; ii < i + 2; ii++) {
                    if (!(jj == j && ii == i) && jj >= 0 && ii >= 0 && jj < a->ysize && ii < a->xsize) {
                        if (a->cells[jj][ii] == ALIVE) n_alive++;
                    }
                }
            }

            if (a->cells[j][i] == ALIVE) {
                if (n_alive < 2 || n_alive > 3) {
                    new[j][i] = DEAD;
                } else {
                    new[j][i] = ALIVE;
                }
            } else {
                if (n_alive == 3) {
                    new[j][i] = ALIVE;
                } else {
                    new[j][i] = DEAD;
                }
            }
        }
    }

    // copy new area to area struct
    for (unsigned int j = 0; j < a->ysize; j++) {
        for (unsigned int i = 0; i < a->xsize; i++) {
            a->cells[j][i] = new[j][i];
        }
        free(new[j]);
    }
    free(new);
}




