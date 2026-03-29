#include "structures.h"

hashTablePos createHashTable(int size) {
	hashTablePos table;
	table = malloc(sizeof(struct hashTable));
	if (!table)
		return NULL;
	table->size = size;
	table->list = malloc(size * sizeof(countryPos));
	if (!table->list)
		return NULL;
	for (int i = 0; i < size; i++)
		table->list[i] = NULL;
	return table;
}

int findKey(char* name, int size) {
	int sum = 0;
	for (int i = 0; i < 5 && name[i] != '\0'; i++)
		sum += name[i];
	return sum % size;
}

int insertCountryHash(hashTablePos table, char* name) {
	int key;
	key = findKey(name, table->size);
	countryPos new;
	new = malloc(sizeof(struct country));
	if (!new)
		return -1;
	strcpy(new->name, name);
	new->key = key;
	new->root = NULL;
	new->next = NULL;
	countryPos p;
	p = table->list[key];
	if (!p || strcmp(name, p->name) < 0) {
		new->next = p;
		table->list[key] = new;
		return 0;
	}
	while (p->next && strcmp(name, p->next->name) > 0)
		p = p->next;
	new->next = p->next;
	p->next = new;
	return 0;
}

countryPos findCountry(hashTablePos table, char* name) {
	int key;
	key = findKey(name, table->size);
	countryPos p;
	p = table->list[key];
	while (p) {
		if (strcmp(p->name, name) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}

int printHash(hashTablePos table) {
	for (int i = 0; i < table->size; i++) {
		printf("\n [%d]\n", i);
		countryPos p;
		p = table->list[i];
		while (p) {
			printf("  %s\n", p->name);
			printCityTree(p->root,-1);
			p = p->next;
		}
	}
	return 0;
}

int freeHash(hashTablePos table) {
	for (int i = 0; i < table->size; i++) {
		countryPos p;
		p = table->list[i];
		while (p) {
			countryPos temp = p;
			p = p->next;
			freeCityTree(temp->root);
			free(temp);
		}
	}
	free(table->list);
	free(table);
	return 0;
}