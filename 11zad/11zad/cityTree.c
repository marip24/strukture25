#include "structures.h"

cityTreePos createCityTree(char* name, int pop) {
	cityTreePos new;
	new = malloc(sizeof(struct cityTree));
	if (!new)
		return NULL;
	strcpy(new->name, name);
	new->population = pop;
	new->left = NULL;
	new->right = NULL;
	return new;
}

cityTreePos insertCityTree(cityTreePos root, char* name, int pop) {
	if (!root)
		return createCityTree(name, pop);
	if (pop < root->population)
		root->left = insertCityTree(root->left, name, pop);
	else if (pop > root->population)
		root->right = insertCityTree(root->right, name, pop);
	else {
		if (strcmp(name, root->name) < 0)
			root->left = insertCityTree(root->left, name, pop);
		else
			root->right = insertCityTree(root->right, name, pop);
	}
	return root;
}

int printCityTree(cityTreePos root, int limit) {
	if (!root)
		return 0;
	printCityTree(root->left, limit);
	if (root->population > limit)
		printf("\n  %s (%d)\n", root->name, root->population);
	printCityTree(root->right, limit);
	return 0;
}

int freeCityTree(cityTreePos root) {
	if (!root)
		return 0;
	freeCityTree(root->left);
	freeCityTree(root->right);
	free(root);
	return 0;
}