#include "bits.h"
#include <stdio.h>

void op_bit_set(unsigned char* data, int i) {
    int i1 = i / 8;
    int i2 = i % 8;
    data[i1] |= 1 << (7 - i2);
}

void op_bit_unset(unsigned char* data, int i) {
    int i1 = i / 8;
    int i2 = i % 8;
    data[i1] &= ~(1 << (7 - i2));
}

int op_bit_get(const unsigned char* data, int i) {
    int i1 = i / 8;
    int i2 = i % 8;
    return (data[i1] >> (7 - i2)) & 1;
}

void op_print_byte(unsigned char b) {
    for (int i = 7; i >= 0; i--) {
        printf("%u", (b >> i) & 1);
    }
}

unsigned char op_bit_get_sequence(const unsigned char* data, int i, int how_many) {
    unsigned char res = 0;

    int i1 = i / 8;
    int i2 = i % 8;
    
    for (int j = 0; j < how_many; j++) {
        res = res << 1;
        res |= (data[i1] >> (7 - i2)) & 1;
        i2 = (i2 + 1) % 8;
        if (i2 == 0) i1++;
    }

    return res;
}
