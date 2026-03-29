#include "structures.h"

countryTreePos createCountryTree(char* name) {
	countryTreePos newCountry;
	newCountry = malloc(sizeof(struct countryTree));
	if (!newCountry) 
		return NULL;
	strcpy(newCountry->name, name);
	newCountry->left = NULL;
	newCountry->right = NULL;
	newCountry->head = malloc(sizeof(struct cityList));
	if (!newCountry->head) {
		free(newCountry);
		return NULL;
	}
	newCountry->head->name[0] = '\0';
	newCountry->head->population = 0;
	newCountry->head->next = NULL;
	return newCountry;
}

countryTreePos insertCountryTree(countryTreePos root, char* name) {
	if (root == NULL)
		return createCountryTree(name);
	if (strcmp(name, root->name) < 0)
		root->left = insertCountryTree(root->left, name);
	else if (strcmp(name, root->name) > 0)
		root->right = insertCountryTree(root->right, name);
	return root;
}

countryTreePos findCountryTree(countryTreePos root, char* name) {
	if (root == NULL)
		return NULL;
	if (strcmp(name, root->name) == 0)
		return root;
	if (strcmp(name, root->name) < 0)
		return findCountryTree(root->left, name);
	return findCountryTree(root->right, name);
}

int printCountryTree(countryTreePos root) {
	if (root == NULL)
		return 0;
	printf("\n %s: ", root->name);
	printCityList(root->head);
	printCountryTree(root->left);
	printCountryTree(root->right);
	return 0;
}

int freeCountryTree(countryTreePos root) {
	if (root == NULL)
		return 0;
	freeCountryTree(root->left);
	freeCountryTree(root->right);
	freeCityList(root->head);
	free(root);
	return 0;
}
