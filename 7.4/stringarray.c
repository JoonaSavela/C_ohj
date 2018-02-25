#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stringarray.h"

/* Exercise a: Initializes the string array to contain the initial
 * NULL pointer, but nothing else.
 * Returns: pointer to the array of strings that has one element
 *      (that contains NULL)
 */
char **init_string_array(void)
{
    char **new = malloc(sizeof(char *));
    *new = NULL;

    return new;
}

/* Releases the memory used by the strings.
 */
void release_string_array(char **arr)
{
    char **a = arr;
    while(*a != NULL) {
        free(*a);
        a++;
    }
    free(arr);
}

/* Exercise b: Add <string> to the end of array <array>.
 * Returns: pointer to the array after the string has been added.
 */
char **insert_string(char **arr, const char *str)
{
    char **a = arr;
    int n = 0;

    while(*a != NULL) {
        n++;
        a++;
    }

    a = realloc(arr, sizeof(char *) * (n + 2));

    *(a + n) = malloc(sizeof(char) * (1 + strlen(str)));
    strcpy(*(a + n), str);

    *(a + n + 1) = NULL;

    return a;
}


/* Exercise c: reorder strings in <array> to lexicographical order */
void sort_string_array(char **arr)
{
    char **a = arr;
    int n = 0;

    while(*a != NULL) {
        n++;
        a++;
    }

    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0 && strcmp(*(arr + j - 1), *(arr + j)) > 0) {
            char *temp = malloc(sizeof(char) * (strlen(*(arr + j)) + 1));
            strcpy(temp, *(arr + j));
            *(arr + j) = realloc(*(arr + j), sizeof(char) * (strlen(*(arr + j - 1)) + 1));
            strcpy(*(arr + j), *(arr + j - 1));
            *(arr + j - 1) = realloc(*(arr + j - 1), sizeof(char) * (strlen(temp) + 1));
            strcpy(*(arr + j - 1), temp);
            free(temp);
            
            j--;
        }
    }

}

/* You can use this function to check what your array looks like.
 */
void print_string_array(char **arr)
{
    if (!arr)
        return;
    while (*arr) {
        printf("%s  ", *arr);
        arr++;
    }
    printf("\n");
}
