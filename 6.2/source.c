#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "zoo.h"


int init_animal(struct animal *as, const char *p_id, const char *p_name, 
                const char *p_species, unsigned char p_age, struct date p_entrydate)
{
    as->name = malloc((strlen(p_name) + 1) * sizeof(char));
    as->species = malloc((strlen(p_species) + 1) * sizeof(char));
    if (strlen(p_id) > 6 || !as->name || !as->species) return 0;

    strcpy(as->id, p_id);
    strcpy(as->name, p_name);
    strcpy(as->species, p_species);
    as->age = p_age;
    as->entrydate = p_entrydate;

    return 1;
}

struct animal *add_record(struct animal *array, unsigned int size, struct animal newanimal)
{
    struct animal *newarray = realloc(array, (size + 1) * sizeof(struct animal));

    init_animal(newarray + size, newanimal.id, newanimal.name, newanimal.species, newanimal.age, newanimal.entrydate);

    return newarray;
}

int update_age(struct animal *array, unsigned int size, const char *p_id,
               unsigned char newage)
{
    for (size_t i = 0; i < size; i++) {
        if (strcmp(array[i].id, p_id) == 0) {
            array[i].age = newage;
            return 1;
        }
    }

    return 0;
}

int update_entrydate(struct animal *array, unsigned int size, const char *p_id,
                     struct date newdate)
{
    for (size_t i = 0; i < size; i++) {
        if (strcmp(array[i].id, p_id) == 0) {
            array[i].entrydate = newdate;
            return 1;
        }
    }

    return 0;
}

int delete_array(struct animal *array, unsigned int size)
{
    for (size_t i = 0; i < size; i++) {
        free(array[i].name);
        free(array[i].species);
    }

    free(array);

    return 1;
}

void print_animal(struct animal a) {
    printf("id: %s\n", a.id);
    printf("name: %s\n", a.name);
    printf("species: %s\n", a.species);
    printf("age: %u\n", a.age);
    printf("entrydate: (%u, %u, %d)\n", a.entrydate.day, a.entrydate.month, a.entrydate.year);
}


int main()
{
    /* Feel free to modify
     * for example function for printing the current array content is useful */

    struct animal a1;
    struct date a1date = {1, 1, 1924};
    if (init_animal(&a1, "123456", "Winnie-the-Pooh", "Bear", 94, a1date )) {
        printf("Initialization succeeded\n");
    } else {
        printf("Initialization failed\n");
    }

    print_animal(a1);
    free(a1.name);
    free(a1.species);
    
    struct animal zoo[] = {
        { "123456", "Winnie-the-Pooh", "Bear", 94, {1,1,1924} },
        { "555666", "Eeyore", "Donkey", 92, {1,1,1926} },
        { "773466", "Piglet", "Very Small Animal", 30, {31, 12, 2015} },
        { "234567", "Roo", "Kangaroo", 5, {31, 12, 2015} }
    };
    
    struct animal *array = NULL;
    unsigned int len = 0;
    for (unsigned int i = 0; i < sizeof(zoo) / sizeof(struct animal); i++) {
        struct animal *newarray = add_record(array, len, zoo[i]);
        if (!newarray) {
            delete_array(array, len);
            exit(EXIT_FAILURE);
        }
        len++;
        array = newarray;
    }

    for (size_t i = 0; i < len; i++) {
        print_animal(array[i]);
    }

    struct date day1 = {0, 0, 0};

    if (!update_age(array, len, "555666", 50))
        printf("failed '555666'\n");

    if (!update_age(array, len, "23456677", 3))
        printf("failed '234567', invalid id\n");

    if (!update_entrydate(array, len, "123456", day1))
        printf("failed '111111'\n");

    if (!update_entrydate(array, len, "999999", day1))
        printf("failed '234567', no course\n");   

    for (size_t i = 0; i < len; i++) {
        print_animal(array[i]);
    }
    
    delete_array(array, len);
}
