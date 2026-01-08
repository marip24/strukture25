#include "structures.h"

int runMenu(countryListPos headList) {
	char country[MAX_NAME];
	int limit;
	printf("\nunesi drzavu: ");
	scanf(" %99s", country);
	printf("\nunesi broj stanovnika: ");
	scanf("%d", &limit);
	countryListPos found;
	found = findCountryList(headList, country);
	if (!found) {
		printf("\ndrzava ne postoji\n");
		return -1;
	}
	searchCityTree(found->root, limit);
	return 0;
}

int deleteAll(countryListPos headList, countryTreePos rootTree) {
	freeCountryList(headList);
	freeCountryTree(rootTree);
	return 0;
}