#include <stdio.h>
#include <string.h>
#include "hexread.h"


int main(void)
{
    if (dump_hex("main.c") == -1) {
         fprintf(stderr, "Could not open main.c\n");
    }
}
