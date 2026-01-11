/*11. Prepraviti zadatak 10 na naèin da se formira hash tablica država. Tablica ima 11 mjesta, a
funkcija za preslikavanje kljuè raèuna da se zbraja ASCII vrijednost prvih pet slova države zatim
raèuna ostatak cjelobrojnog dijeljenja te vrijednosti s velièinom tablice. Države s istim kljuèem se
pohranjuju u vezanu listu sortiranu po nazivu države. Svaki èvor vezane liste sadrži stablo
gradova sortirano po broju stanovnika, zatim po nazivu grada.*/

/*
hash: zbroji prvih par slova te drzave, koliko je slova toliko i %taj broj ide, taj broj je prost koji je iza %, pa koji je ostatak na taj red hash tablice ide;
struct hashTable{
int size;
Position* HashList;
};

struct Country{
...
int key; //jedina izmjena iz 10tog
};
u mainu: 1) inicijalizirat hashTable, prvo alocirat, hashTable->hashList=...malloc...
for(int i=0; i<hashTable->size;i--){
hashTable->hashList[i]=NULL;
}
sad citamo podatke iz datoteke drzave.txt, otvorit je, uvest buffer, svaka linija na 2 tokena, sve ponavljanje iz desetog, onda nakon dohvatili podatke iz jedne linije,
toj drzavi triba pridodat kljuc f-ja: findKey(string cName) return (cName[0]+cName[1]+...+cName[4])%hashTable->size; kad se dobije triba se spojit sa hash tablicom
kad dobije kljuc triba vidit jel hash tablica pokazuje na null ili na sta drugo znaci: if(*(hashTable->hashList)==NULL) onda dodaj novi element tj. spojiga, u slucaju da
taj isti uvjet != NULL &&strcmp(<0) onda ope dodaj novi element tj dodaj ga na pocetak liste, else while(dok nije kraj liste) i dok strcmp>0 inkrementiraj di se nalazi 
i++; hashTable->hashList+=i; i onda ce se tu negdi smistit ta nova drzava i onda kad se smistis dodaj novi element, to je izvan whilea a unutar else; da nije bila zadan
prosti broj tablice, onda bi se napravila funkcija koja bi trazija prvi iduci prosti broj; -dodavanje: alokacija, provjera,upis imena drzave, populacije itd. kad se
kopiraju svi podaci onda se izracunti kljuc pohrani tj. country->key=findKey(cName); newEl->next=hashTable->hashList[findKey(cName)]; hashTable->hashList[findKey(cName)]=newEl;
dosta je napravit samo da ima liste za drzave i stabla za gradove netriba imat a i b dio ka u zadatku pod 10
pretrazivanje s obzirom na unos za populaciju: for(int i=-0;i<hashTable-Ysize;i+++){poziv funkcije za pretrazivanje iste drzava tipa findCountry("head", population); a taj
bi head zapravo postao hashTable->hashList[i]; }
brisanje: for(int i=0; i<hashTable->size;i++){freeList("head"), a taj head je hashTable->hashList[i]; }
za hash tabl pola koda ce bit identican jer ce u svakoj bit ova for petlja, uvik se ponavlja
*/

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