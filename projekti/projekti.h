
typedef struct {
	char name[21];
	int bronze_medals;
	int silver_medals;
	int gold_medals;
} Country;

Country *add_country(Country *ptr, size_t n, char *name);

void print_countries(Country *ptr, size_t n);

void update_medals(Country *ptr, size_t n, char *name, int gold, int silver, int bronze);

int int_cmp(int a, int b);

int country_compare(const void *a, const void *b);

int write_file(Country *ptr, size_t n, char *filename);

Country *load_file(Country *ptr, size_t *p_n, char *filename);

