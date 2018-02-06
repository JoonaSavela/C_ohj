#include <stdlib.h> // malloc, free
#include <stdio.h>  // printf

int *join_arrays(unsigned int n1, int *a1, unsigned int n2, int *a2, unsigned int n3, int *a3) {

    int *dest = malloc((n1 + n2 + n3)*sizeof(int)); 

    for (int i = 0; i < n1 + n2 + n3; i++) {
        if (i < n1) *(dest + i) = *(a1 + i);
        else if (i < n1 + n2) *(dest + i) = *(a2 + i - n1);
        else *(dest + i) = *(a3 + i - n1 - n2);
    }


    return dest;
}


int main(void)
{
    /* testing exercise. Feel free to modify */
    int a1[] = { 1, 2, 3, 4, 5 };
    int a2[] = { 10, 11, 12, 13, 14, 15, 16, 17 };
    int a3[] = { 20, 21, 22 };

    int *joined = join_arrays(5, a1, 8, a2, 3, a3);

    for (int i = 0; i < 5 + 8 + 3; i++) {
        printf("%d  ", joined[i]);
    }
    printf("\n");

    free(joined);

    return 0;
}
