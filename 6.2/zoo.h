#ifndef AALTO_C_ZOO
#define AALTO_C_ZOO

// Date in numeric format
struct date {
    unsigned char day;
    unsigned char month;
    int year;
};

// Single animal entry
struct animal {
    char id[7]; // animal ID (6 characters) + terminating '\0'
    char *name; // animals name
    char *species; // animal species (string)
    unsigned char age; // animals age
    struct date entrydate;  // date of the animals arrival
};


/* Initialize animal record
 * 
 * Parameters:
 * as: Animal entry to be changed (does not need to be allocated)
 * p_id, p_name, p_species, p_age, p_entrydate: Values for different structure
 *      fields (must be copied)
 * 
 * Returns: 1 if initialization was succesful, 0 if it failed
 * If animal ID is more than 6 characters, initialization fails.
 * 
 * -- Note that structure contains enough space for animal ID, but not for
 * name or species
 * -- Remember to check that reserved space is not overwritten
 */
int init_animal(struct animal *as, const char *p_id, const char *p_name, const char *p_species,
    unsigned char p_age, struct date p_entrydate);

/* Add a new animal to a dynamic array.
 * (Resize the array as needed). All content of the new structure is copied.
 * 
 * Parameters:
 * array: start of an dynamic array (may be NULL, if array is empty)
 * length: current length of the array (number of entries)
 * newanimal: new animal to be added, all fields need to be copied.
 * 
 * Returns: pointer to the array after adding the new item
 */
struct animal *add_record(struct animal *array, unsigned int size, struct animal newanimal);

/* Update age in existing record.
 * 
 * Parameters:
 * array: beginning of array
 * size: size of array
 * p_id: animal ID to be changed
 * newage: new value for age
 * 
 * Returns: number of entries changed, i.e. either 1 or 0
 */

int update_age(struct animal *array, unsigned int size, const char *p_id,
               unsigned char newage);

/* Update entry date in existing record.
 * 
 * Parameters:
 * array: beginning of array
 * size: size of array
 * p_id: animal ID to be changed
 * newdate: new value for entry date
 * 
 * Returns: number of entries changed, i.e. either 1 or 0
 */

int update_entrydate(struct animal *array, unsigned int size, const char *p_id,
                     struct date newdate);

int delete_array(struct animal *array, unsigned int size);

#endif
