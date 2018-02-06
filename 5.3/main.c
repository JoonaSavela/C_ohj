#include <stdio.h>
#include <stdlib.h>

int *dynamic_reader(unsigned int n) {

    int *dest = malloc(n * sizeof(int));
    int *origdest = dest;

    unsigned int i = 0;
    while (i < n) {
        int ret = scanf("%u", dest);
        if (ret == 1) {
            dest++;
            i++;
        }
    }

    return origdest;
}


int *insert_into_array(int *arr, unsigned int num, int newval) {

    int *new_arr = realloc(arr, (num + 1) * sizeof(int));
    *(new_arr + num) = newval;
    
    return new_arr;
}


int main() {

    unsigned int n = 4;
    int *test = dynamic_reader(n);
    for (unsigned int i = 0; i < n; i++) {
        printf("%d ", *(test + i));
    }
    printf("\n");

    for (unsigned int i = 0; i < 6; i++) {
        printf("insert %d: ", 100 - i);
        test = insert_into_array(test, n + i, 100 - i);
        for (unsigned int j = 0; j < n + i + 1; j++) {
            printf("%d ", *(test + j));
        }
        printf("\n");
    }

    free(test);
}


