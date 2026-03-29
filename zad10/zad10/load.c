#include "structures.h"

int loadData(countryListPos headList, countryTreePos* rootTree) {
	FILE* file = fopen("drzave.txt", "r");
	if (!file)
		return -1;
	char country[MAX_NAME], filename[MAX_NAME];
	while (fscanf(file, "%99s %99s", country, filename) == 2) {
		countryListPos newCountry;
		newCountry = createCountryList(country);
		if (!newCountry) {
			printf("\ndatoteka %s se ne moze otvoriti\n", filename);
			fclose(file);
			return -1;
		}
		if (insertCountryListSorted(headList, newCountry) != 0) {
			free(newCountry);
			fclose(file);
			return -1;
		}
		*rootTree = insertCountryTree(*rootTree, country);
		countryTreePos foundTree;
		foundTree = findCountryTree(*rootTree, country);
		if (!foundTree) {
			printf("\ngreska drzava nije pronadena u stablu\n");
			continue;
		}
		if (foundTree->head==NULL) {
			printf("\ngreska lista gradova za drzavu %s nije inicijalizirana\n", country);
			continue;
		}
		FILE* cityFile = fopen(filename, "r");
		if (!cityFile) {
			newCountry->root = NULL;
			continue;
		}
		char city[MAX_NAME];
		int pop;
		while (fscanf(cityFile, "%99s %d", city, &pop) == 2) {
			newCountry->root = insertCityTree(newCountry->root, city, pop);
			cityListPos newCity;
			newCity = createCityList(city, pop);
			if (!newCity)
				return -1;
			insertCityListSorted(foundTree->head, newCity);
		}
		fclose(cityFile);
	}
	fclose(file);
	return 0;
}