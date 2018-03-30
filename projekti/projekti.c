#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projekti.h"

Country *add_country(Country *ptr, size_t n, char *name) {
	Country *res = realloc(ptr, sizeof(Country) * (n + 1));

	Country *cur = res + n;

	strncpy(cur->name, name, 20);
	cur->name[20] = '\0';
	cur->bronze_medals = 0;
	cur->silver_medals = 0;
	cur->gold_medals = 0;

	return res;
}

void print_countries(Country *ptr, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		printf("%s %d %d %d\n", (ptr + i)->name, 
								(ptr + i)->gold_medals,
								(ptr + i)->silver_medals,
								(ptr + i)->bronze_medals);
	}
}

void update_medals(Country *ptr, size_t n, char *name, int gold, int silver, int bronze) {
	Country *cur;

	for (size_t i = 0; i < n; ++i) {
		cur = ptr + i;
		if (strcmp(name, cur->name) == 0) {
			cur->bronze_medals += bronze;
			cur->silver_medals += silver;
			cur->gold_medals += gold;

			if (cur->bronze_medals < 0) {
				cur->bronze_medals = 0;
			} else if (cur->silver_medals < 0) {
				cur->silver_medals = 0;
			} else if (cur->gold_medals < 0) {
				cur->gold_medals = 0;
			}

			return;
		}
	}
	printf("Error: no such country.\n");
}

int int_cmp(int a, int b) {
	if (a < b) {
		return 1;
	} else if (a == b) {
		return 0;
	} else {
		return -1;
	}
}

int country_compare(const void *a, const void *b) {
	const Country *country_a = a;
	const Country *country_b = b;

	int res = int_cmp(country_a->gold_medals, country_b->gold_medals);

	if (res == 0) {
		res = int_cmp(country_a->silver_medals, country_b->silver_medals);
		if (res == 0) {
			res = int_cmp(country_a->bronze_medals, country_b->bronze_medals);
		}
	}

	return res;
}

int write_file(Country *ptr, size_t n, char *filename) {
	FILE *f = fopen(filename, "w");
	if (f == NULL) {
		return -1;
	}

	for (size_t i = 0; i < n; ++i) {
		Country *cur = ptr + i;

		fprintf(f, "%s %d %d %d\n", cur->name, 
									cur->gold_medals,
									cur->silver_medals,
									cur->bronze_medals);
	}

	fclose(f);

	return 0;
}

Country *load_file(Country *ptr, size_t *p_n, char *filename) {
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		printf("Error: no such file.\n");
		return ptr;
	}	

	char name[21];
	int gold, silver, bronze;

	int ret = fscanf(f, "%s %d %d %d\n", name, &gold, &silver, &bronze);
	size_t n = 0;

	while (ret == 4) {
		++n;
		ptr = realloc(ptr, n * sizeof(Country));
		Country *cur = ptr + n - 1;

		strcpy(cur->name, name);
		cur->name[20] = '\0';
		cur->gold_medals = gold;
		cur->silver_medals = silver;
		cur->bronze_medals = bronze;

		ret = fscanf(f, "%s %d %d %d\n", name, &gold, &silver, &bronze);	
	}

	*p_n = n;

	fclose(f);

	printf("Loaded from file %s.\n", filename);

	return ptr;
}

int main(void) {

	Country *countries = NULL;

	size_t n_countries = 0;

	char buffer[81];

	while (1) {

		char *res = fgets(buffer, 80, stdin);

		if (!res || buffer[0] == 'Q') {
			printf("Exiting program.\n");
			break;
		} else if (buffer[0] == 'A') {
			char name[80];
			int ret = sscanf(buffer + 1, "%s", name);

			if (ret == 1) {
				countries = add_country(countries, n_countries, name);
				if (countries != NULL) {
					++n_countries;
					printf("Added country: ");
					print_countries(countries + n_countries - 1, 1);
				} else {
					printf("An error occured.\n");
				}
			} else {
				printf("Invalid input.\n");
			}

		} else if (buffer[0] == 'M') {
			char name[80];
			int gold, silver, bronze;
			int ret = sscanf(buffer + 1, "%s %d %d %d", name, &gold, &silver, &bronze);
			if (ret == 4) {
				update_medals(countries, n_countries, name, gold, silver, bronze);
				printf("Updated the medals of %s.\n", name);
			} else {
				printf("Invalid input.\n");
			}
		} else if (buffer[0] == 'L') {
			qsort(countries, n_countries, sizeof(Country), country_compare);
			printf("List of countries:\n");
			print_countries(countries, n_countries);
		} else if (buffer[0] == 'W') {
			char filename[80];
			int ret = sscanf(buffer + 1, "%s", filename);
			if (ret == 1) {
				int ret2 = write_file(countries, n_countries, filename);
				if (ret2 == 0) {
					printf("Wrote to file %s.\n", filename);
				} else {
					printf("An error occured.\n");
				}
			} else {
				printf("Invalid input.\n");	
			}
		} else if (buffer[0] == 'O') {
			char filename[80];
			int ret = sscanf(buffer + 1, "%s", filename);
			if (ret == 1) {
				countries = load_file(countries, &n_countries, filename);
			} else {
				printf("Invalid input.\n");
			}
		} else {
			printf("Invalid input.\n");	
		}

	}

	free(countries);

}
