#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "filestats.h"

int line_count(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return -1;
    int count = 0;
    int flag_newline = 1;
    char *p = malloc(sizeof(char));
    size_t n = fread(p, sizeof(char), 1, f);

    while (n == 1) {
        if (flag_newline) {
            count++;
            flag_newline = 0;
        }
        if (*p == '\n') {
            flag_newline = 1;
        }
        n = fread(p, sizeof(char), 1, f);
    }

    free(p);
    fclose(f);
    return count;
}

int word_count(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return -1;
    int count = 0;
    int flag_space = 1;
    char *p = malloc(sizeof(char));
    size_t n = fread(p, sizeof(char), 1, f);

    while (n == 1) {
        if (isalpha(*p) && flag_space) {
            count++;
            flag_space = 0;
        }
        if (isspace(*p)) {
            flag_space = 1;
        }
        n = fread(p, sizeof(char), 1, f);
    }

    free(p);
    fclose(f);
    return count;
}
