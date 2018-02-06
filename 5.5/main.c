#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *delete_comments(char *input) {
    char *res = malloc((strlen(input) + 1) * sizeof(char));
    char comment = 0; // 0 - no comment, 1 - //-comment, 2 - /*-comment-*/
    int j = 0;

    for (int i = 0; i < strlen(input); i++) {
        if (comment == 1) {
            if (input[i] == '\n') {
                comment = 0;
            }
        } else if (comment == 2) {
            if (input[i] == '*' && input[i + 1] == '/') {
                comment = 0;
                i++;
            }
        } else {
            if (input[i] == '/') {
                if (input[i + 1] == '/') {
                    comment = 1;
                    i++;
                } else if (input[i + 1] == '*') {
                    comment = 2;
                    i++;
                } else {
                    res[j] = input[i];
                    j++;
                }
            } else {
                res[j] = input[i];
                j++;
            }
        }
    }

    res[j] = 0;
    free(input);
    //res = realloc(res, (j + 1) * sizeof(char));

    return res;
}


/* Read given file <filename> to dynamically allocated memory.
 * Return pointer to the allocated memory with file content, or
 * NULL on errors.
 */
char *read_file(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
        return NULL;
    
    char *buf = NULL;
    unsigned int count = 0;
    const unsigned int ReadBlock = 100;
    unsigned int n;
    do {
        buf = realloc(buf, count + ReadBlock + 1);
        n = fread(buf + count, 1, ReadBlock, f);
        count += n;
    } while (n == ReadBlock);
    
    buf[count] = 0;
    
    return buf;
}


int main(void)
{
    char *code = read_file("testifile.c");
    if (!code) {
        printf("No code read");
        return -1;
    }
    printf("-- Original:\n");
    fputs(code, stdout);

    code = delete_comments(code);
    printf("-- Comments removed:\n");
    fputs(code, stdout);
   
    free(code);
}


