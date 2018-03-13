#include <stdio.h>
#include "filestats.h"

int line_count(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return -1;
    int count = 0;



    fclose(f);
    return count;
}

int word_count(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f!) return -1;
    int count = 0;


    fclose(f);
    return count;
}
