#include <string.h>
#include <stdlib.h>
#include "shopfunctions.h"


int compareAlpha(const void* a, const void* b) {
    const Product *_a = a;
    const Product *_b = b;

    return strcmp(_a->name, _b->name);
}


int compareNum(const void* a, const void* b) {
    const Product *_a = a;
    const Product *_b = b;

    const int i1 = _a->in_stock;
    const int i2 = _b->in_stock;

    if (i1 == i2) {
        return compareAlpha(a, b);
    } else if (i1 < i2) {
        return 1;
    } else {
        return -1;
    }

}


Product* findProduct(Product* p_array, const char* searchkey, int (*cmp)(const void*, const void*)) {
    size_t n = 0;
    int i = 0;

    while (p_array[i].name[0] != 0) {
        n++;
        i++;
    }

    return bsearch(searchkey, p_array, n, sizeof(Product), cmp);
}


