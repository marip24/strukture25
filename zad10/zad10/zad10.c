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
/*OVAKO CE IZGLEDAT ZADATAK SA STABLIMA AKO GA BUDE*/
/*
koristit vise datoteka ka i u seston, jedna glavna datoteka drzava.txt, u njoj drzava sa imenon svoje datoteke pr. Francuska francuska.txt i tako dalje svaka u 
svon redu, moze bit drzava koliko god, svaka iduca datoteka tj od drzava pr francuska.txt mora imat grad i broj stanovnika
Pariz 16
Nice 26
nek bude vise ili manje elemenata ili da bude i prazna datoteka da malo ekseprimentiramo i testiramo tj treba radit za razlicit broj pohranjenih podataka
struktura za gradove i struktura koja predstavlja drzavu
struct countries{
char name;
Position next;
treePos root;  //jer mora imat poveznicu sa city stablom
};
struct city{
char name;
treePos left;
treePos right;
int population;
};
a i b isti, razlika koje je strukture grad a koje drzava inace su isti
a)vezana lista za drzave,  Head={.name=" ", .next=NULL};, poziv funkcije citanja datoteke, fopen(drzave.txt), provjera jel otvorena datoteka, slijedi citanje
sa bufferon, tu vrijednost razbijamo na 2 vrijednosti tj 2 tokena, jedan ce bit ime drzave a drugi je putanja i onda slijedi sortirani unos, imamo uvjete prvi je
if(p->next==NULL) onda alociramo memoriju, provjeri jel alocirana, slijedi upis podataka u newEl, upisuje ime drzave newEl->name=countryName; newEl->root=NULL;
newEl->next=p->next; p->next=newEl; drugi uvjet je if(p!=NULL&&strcmp(p->next->name>countryName)) ostalo isto kao 1 alokacija, provjera, unos podataka, spajanje sa drugim 
clannovima liste treci uvjet ako je if while(p->next!=NULL&&strcmp(p->next->name<countryName)) p=p->next; pa onda isto ka i pod 1  alokacija,provjera, unos podataka, spajanje sa drugim 
clannovima liste
najbolje cin se alocira memorija za drzavu odma za nju ubacit i gradove, sad citaje  iz nove datoteke fopen(zemlja.txt, "r") spremljenu iz buffera zemlju, odo nadodat 
if od svakog od uvjeta, pohranu se podaci, onda slijedi sortirani unos gradova prvo po broju staovnika, rekurzivna funkcija jer radimo sa stablima,
sortiranje po broju stanovnika: prvo if(root==NULL) poziva funkcija za alociranje memorije tj insert funkcija tipa root=insert(root,population); drugi uvjet
if(root->population>population) root->left= insert(root->left, population); treci uvjet if(root->population<population) root->right= insert(root->right, population);
return root; to ide na kraju. 
sortiranje po nazivu grada samo koristi strcmp, uvjeti su apsolutno isti, vrijednost grada upisana veca od procitanog ubaci u livo i obrnuto za treci uvjet, toe jedina razlika
b) isto samo obrni logiku, isto triba sortirat
i sad nakon sta se sve ovo unilo sve ovo triba ispisa -ispis while(p!=NULL) printf(p->name); nakon sta se ovo ispisalo rekurzivni poziv funkcije koja ce ispisat cilo stablo
tj poziv printTree(p->root); kad se ta cila zemlja ispisala onda idemo na iducu tj p=p->next;}
printTree{if(root!=NULL) printf(root->name), printf(root->left); printf(root->right); koristimo preorder ispir, prvo odeitelj ispise pa livo pa desno dite}
za pretragu gradova- prvo unese ime drzave pa unese neku brojku, nama program treba ispisat sve gradove koji imaju vise stanovnika od broja koji je korisnik unio
na tastaturi: while(p!=NULL){potraga za drzavom, ako se nade onda triba pretrazit stablo, za njegovo pretrazivanje ope se koristi rekurzija -ispis gradova po unosu searchTree{ if(root==NULL) return NULL;
if(root->popul>popul) printf(root->name); nakon toga searchTree(root->right), searchTree(root->left); sad je obrnuto jer sva liva manju vrijednost ima a desna imaju vecu 
vrijednnost} ako nije pronadena p=p->next; ako smo dosli do kraja printf(nema te drzave)} zadnji korak je obrisat memoriju, od najmanjeg diteta pa bata pa roditelja kad
se obrise cilo stablo onda se i taj clan obrise pa onda stablo iduceg clana i taj clan pa se onda obrise i head element, oslobodi i buffer takoder
*/

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