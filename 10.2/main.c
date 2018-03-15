#include <string.h>
#include <stdarg.h>
#include <stdio.h>

int myprint(const char *str, ...) {
    int n = strlen(str);
    int count = 0;
    va_list args;
    va_start(args, str);

    for (int i = 0; i < n; i++) {
        if (*(str + i) != '&') {
            fputc(*(str + i), stdout);
        } else {
            printf("%d", va_arg(args, int));
            count++;
        }
    }
    va_end(args);

    return count;
}

int main(void)
{
    myprint("Hello!\n");
    myprint("Number: &\n", 5);
    myprint("Number one: &, number two: &\n", 120, 1345);
    int ret = myprint("Three numbers: & & &\n", 12, 444, 5555);
    myprint("I just printed & integers\n", ret);

    return 0;
}
