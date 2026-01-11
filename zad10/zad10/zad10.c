/*10. Napisati program koji èita datoteku drzave.txt u kojoj su zapisani nazivi pojedinih država. Uz
ime države u datoteci se nalazi i ime dodatne datoteke u kojoj se nalaze gradovi pojedine
države. Svaka datoteka koja predstavlja državu sadrži popis gradova u formatu naziv_grada,
broj_stanovnika.
a) Potrebno je formirati sortiranu vezanu listu država po nazivu. Svaki èvor vezane liste
sadrži stablo gradova sortirano po broju stanovnika, zatim po nazivu grada.
b) Potrebno je formirati stablo država sortirano po nazivu. Svaki èvor stabla sadrži vezanu
listu gradova sortiranu po broju stanovnika, zatim po nazivu grada.
Nakon formiranja podataka potrebno je ispisati države i gradove te omoguæiti korisniku putem
tastature pretragu gradova odreðene države koji imaju broj stanovnika veæi od unosa na
tastaturi.*/

#include "structures.h"

int main() {
	countryListPos headList;
	headList = malloc(sizeof(struct countryList));
	if (!headList)
		return -1;
	headList->next = NULL;
	headList->root = NULL;
	countryTreePos rootTree;
	rootTree = NULL;
	if (loadData(headList, &rootTree) != 0) {
		printf("\ngreska pri ucitavanju podataka\n");
		return -1;
	}
	printCountryList(headList);
	printCountryTree(rootTree);
	runMenu(headList, rootTree);
	deleteAll(headList, rootTree);
	return 0;
}