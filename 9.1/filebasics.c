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

    fclose(f);

    return res;
}

char *difference(const char* file1, const char* file2) {
    char *res = malloc(150 * sizeof(char));
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");

    char ss1[50];
    char ss2[50];    
    char *s1 = ss1;
    char *s2 = ss2;

    while (s1 != NULL && s2 != NULL) {
        s1 = fgets(s1, 50, f1);
        s2 = fgets(s2, 50, f2);

        if (s1 != NULL && s2 != NULL && strcmp(s1, s2) != 0) {
            strcpy(res, "    ");
            
            strcpy(res + 4, s1);

            strcpy(res + 4 + strlen(s1), "----\n    ");

            strcpy(res + 4 + strlen(s1) + 9, s2);

            return res;
        }
    }

    fclose(f1);
    fclose(f2);
    return res;
}

