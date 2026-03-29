#include "structures.h"

int runMenu(countryListPos headList, countryTreePos rootTree) {
	char country[MAX_NAME];
	int limit, choice;
	printf("\n1-pretraga pod a");
	printf("\n2-pretraga pod b");
	printf("\nodabir: ");
	scanf("%d", &choice);
	printf("\nunesite drzavu: ");
	scanf(" %99s", country);
	printf("\nunesite broj stanovnika: ");
	scanf("%d", &limit);
	if (choice == 1) {
		countryListPos found;
		found = findCountryList(headList, country);
		if (!found) {
			printf("\ndrzava ne postoji\n");
			return -1;
		}
		printf("\ngradovi u %s :\n", country);
		searchCityTree(found->root, limit);
	}
	else if (choice == 2) {
		countryTreePos found;
		found = findCountryTree(rootTree, country);
		if (!found) {
			printf("\ndrzava ne postoji\n");
			return -1;
		}
		printf("\gradovi u %s:\n", country);
		searchCityList(found->head, limit);
	}
	else
		printf("\npogresan unos");

	return 0;
}

int deleteAll(countryListPos headList, countryTreePos rootTree) {
	freeCountryList(headList);
	freeCountryTree(rootTree);
	return 0;
}
