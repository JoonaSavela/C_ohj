#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "aaltogame.h"

int main(void)
{
    /* Feel free to modify this function to test different things */

    // re-seed random number generator
    srand((unsigned)time(NULL));

    Area *a = createArea(75,30);
    initArea(a, 300);

    // how many iterations we want
    int rounds = 120;

    // loop iterations, cancel with ctrl-c
    for(int i=0; i<rounds; i++) {
        printf("\nGeneration: %d\n", i+1);
        printArea(a);
        // slow down iterations
        usleep(500000);
        tick(a);
    }
    releaseArea(a);
}
