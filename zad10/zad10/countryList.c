#include "structures.h"

countryListPos createCountryList(char* name) {
	countryListPos newCountry;
	newCountry = malloc(sizeof(struct countryList));
	if (!newCountry)
		return NULL;
	strcpy(newCountry->name, name);
	newCountry->root = NULL;
	newCountry->next = NULL;
	return newCountry;
}

int insertCountryListSorted(countryListPos head, countryListPos newCountry) {
	if (!head || !newCountry)
		return -1;
	countryListPos p;
	p = head;
	while (p->next != NULL && strcmp(p->next->name, newCountry->name) < 0)
		p = p->next;
	newCountry->next = p->next;
	p->next = newCountry;
	return 0;
}

countryListPos findCountryList(countryListPos head, char* name) {
	countryListPos p;
	p = head->next;
	while (p != NULL) {
		if (strcmp(p->name, name) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}

int printCountryList(countryListPos head) {
	countryListPos p;
	p = head->next;
	while (p != NULL) {
		printf("\n %s: ", p->name);
		printCityTree(p->root);
		p = p->next;
	}
	return 0;
}

int freeCountryList(countryListPos head) {
	countryListPos temp;
	countryListPos p;
	p = head->next;
	while (p != NULL) {
		temp = p;
		p = p->next;
		freeCityTree(temp->root);
		free(temp);
	}
	head->next = NULL;
	return 0;
}
