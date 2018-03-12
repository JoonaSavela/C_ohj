#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filebasics.h"

int print_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) return -1;
    int res = 0;
    char ss[50];
    char *s = ss;

    while (s != NULL) {
        s = fgets(s, 50, f);
        if (s != NULL) {
            res += strlen(s);
            printf("%s", s);
        }
    }

    return res;
}

char *difference(const char* file1, const char* file2) {
    char *res = NULL;

    return res;
}

