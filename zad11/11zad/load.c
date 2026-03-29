#include "structures.h"

int loadData(hashTablePos table) {
	FILE* f = fopen("drzave.txt", "r");
	if (!f)
		return -1;
	char country[MAX_NAME], file[MAX_NAME];
	while (fscanf(f, "%s %s", country, file) == 2) {
		insertCountryHash(table, country);
		countryPos found;
		found = findCountry(table, country);
		FILE* fc = fopen(file, "r");
		if (!fc)
			continue;
		char city[MAX_NAME];
		int pop;
		while (fscanf(fc, "%s %d", city, &pop) == 2)
			found->root = insertCityTree(found->root, city, pop);
		fclose(fc);
	}
	fclose(f);
	return 0;
}
