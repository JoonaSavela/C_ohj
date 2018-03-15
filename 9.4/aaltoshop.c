#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aaltoshop.h"

int output_binary(const char* filename, Product* shop) {
    FILE *f = fopen(filename, "w");
    if(!f || !shop) return 1;

    int i = 0;

    while ((shop + i)->name[0] != 0) {
        fwrite(shop + i, sizeof(Product), 1, f);

        i++;
    }

    fclose(f);
    return 0;
}

Product* read_binary(const char* filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return NULL;
    Product *shop = malloc(sizeof(Product));
    size_t shop_size = 1;
    size_t n = fread(shop, sizeof(Product), 1, f);

    while (n == 1) {
        shop_size++;
        shop = realloc(shop, shop_size * sizeof(Product));

        n = fread(shop + shop_size - 1, sizeof(Product), 1, f);
    }

    (shop + shop_size - 1)->name[0] = 0;

    fclose(f);
    return shop;
}

int output_plaintext(const char* filename, Product* shop) {
    FILE *f = fopen(filename, "w");
    if (!f || !shop) return 1;

    int i = 0;

    while ((shop + i)->name[0] != 0) {
        fprintf(f, "%s ", (shop + i)->name);
        fprintf(f, "%f ", (shop + i)->price);
        fprintf(f, "%d\n", (shop + i)->in_stock);

        i++;
    }

    fclose(f);
    return 0;
}

Product* read_plaintext(const char* filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return NULL;
    Product *shop = malloc(sizeof(Product));
    size_t shop_size = 0;
    char name[31];
    float price;
    int in_stock;
    char *s = malloc(sizeof(char) * 100);
    char *res = fgets(s, 100, f);

    while (res != NULL) {
        sscanf(s, "%s %f %d", name, &price, &in_stock);
        shop_size++;
        shop = realloc(shop, shop_size * sizeof(Product));
        strcpy((shop + shop_size - 1)->name, name);
        (shop + shop_size - 1)->price = price;
        (shop + shop_size - 1)->in_stock = in_stock;

        res = fgets(s, 100, f);
    }

    shop_size++;
    shop = realloc(shop, shop_size * sizeof(Product));
    (shop + shop_size - 1)->name[0] = 0;

    free(s);
    fclose(f);
    return shop;
}

