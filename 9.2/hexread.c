#include <stdio.h>
#include <stdlib.h>
#include "hexread.h"

int dump_hex(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return -1;
    int res = 0;
    unsigned char *p = malloc(sizeof(char));
    size_t n = fread(p, sizeof(unsigned char), 1, f);
    size_t count = 0;

    while (n == 1) {
        printf("%02x ", *p);
        count++;
        if (count % 16 == 0) printf("\n");
        n = fread(p, sizeof(unsigned char), 1, f);
    }

    printf("\n");

    free(p);
    fclose(f);
    return res;
}
