/*11. Prepraviti zadatak 10 na naèin da se formira hash tablica država. Tablica ima 11 mjesta, a
funkcija za preslikavanje kljuè raèuna da se zbraja ASCII vrijednost prvih pet slova države zatim
raèuna ostatak cjelobrojnog dijeljenja te vrijednosti s velièinom tablice. Države s istim kljuèem se
pohranjuju u vezanu listu sortiranu po nazivu države. Svaki èvor vezane liste sadrži stablo
gradova sortirano po broju stanovnika, zatim po nazivu grada.*/

#include "structures.h"

int main() {
	hashTablePos table;
	table = createHashTable(HASH_SIZE);
	if (!table)
		return -1;
	if (loadData(table) != 0) {
		printf("\ngreska pri ucitavanju\n");
		return -1;
	}
	printHash(table);
	char name[MAX_NAME];
	int limit;
	printf("\nunesi drzavu: ");
	scanf(" %s", name);
	printf("\nunesi limit populacije: ");
	scanf("%d", &limit);
	countryPos found;
	found = findCountry(table, name);
	if (!found)
		printf("\ndrzava ne postoji");
	else
		printCityTree(found->root, limit);
	freeHash(table);
	return 0;
}