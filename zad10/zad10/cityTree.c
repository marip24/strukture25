#include "structures.h"

cityTreePos createCityTree(char* name, int population) {
	cityTreePos newCity;
	newCity = malloc(sizeof(struct cityTree));
	if (!newCity)
		return NULL;
	strcpy(newCity->name, name);
	newCity->population = population;
	newCity->left = NULL;
	newCity->right = NULL;
	return newCity;
}

cityTreePos insertCityTree(cityTreePos root, char* name, int population) {
	if (root == NULL)
		return createCityTree(name, population);
	if (population < root->population)
		root->left = insertCityTree(root->left, name, population);
	else if (population > root->population)
		root->right = insertCityTree(root->right, name, population);
	else {
		if (strcmp(name, root->name) < 0)
			root->left = insertCityTree(root->left, name, population);
		else
			root->right = insertCityTree(root->right, name, population);
	}
	return root;
}

int printCityTree(cityTreePos root) {
	if (root == NULL)
		return 0;
	printf("\n %s (%d)\n", root->name, root->population);
	printCityTree(root->left);
	printCityTree(root->right);
	return 0;
}

int searchCityTree(cityTreePos root, int limit) {
	if (root == NULL)
		return 0;
	if (root->population > limit)
		printf("\n %s (%d)\n", root->name, root->population);
	searchCityTree(root->right, limit);
	searchCityTree(root->left, limit);
	return 0;
}

int freeCityTree(cityTreePos root) {
	if (root == NULL)
		return 0;
	freeCityTree(root->left);
	freeCityTree(root->right);
	free(root);
	return 0;
}
