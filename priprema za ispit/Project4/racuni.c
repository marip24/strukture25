/*Napisati program koji èita datoteku racuni.txt u kojoj su zapisani nazivi svih datoteka koji
predstavljaju pojedini raèun.Na poèetku svake datoteke je zapisan datum u kojem vremenu je
raèun izdat u formatu YYYY - MM - DD.Svaki sljedeæi red u datoteci predstavlja artikl u formatu
naziv, kolièina, cijena.Potrebno je formirati vezanu listu raèuna sortiranu po datumu.Svaki èvor
vezane liste sadržava vezanu listu artikala sortiranu po nazivu artikla.Nakon toga potrebno je
omoguæiti upit kojim æe korisnik saznati koliko je novaca sveukupno potrošeno na specifièni
artikl u odreðenom vremenskom razdoblju i u kojoj je kolièini isti kupljen.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct artikl {
	char ime[20];
	int kolicina;
	float cijena;
	struct artikl* next;
}Artikl;

typedef struct racun {
	char datum[20];
	Artikl* lista;
	struct racun* next;
}Racun;

Racun* stvoriRacun(const char* priv);
Artikl* stvoriListu(FILE* dat);
Artikl* sortList(Artikl* nov, Artikl* headL);
Racun* sortR(Racun* head, Racun* nov);
int ispis(Racun* head);
int brisi(Racun* head);

int main() {
	Racun* head = NULL;
	const char* zad = "racuni.txt";
	FILE* fp = fopen(zad, "r");
	if (!fp) {
		printf("\ngreskapri otvaranju fp");
		return -1;
	}
	const char* priv[20];
	while (fscanf(fp, "%s", priv)==1) {
		priv[strcspn(priv, "\n")] = '\0';
		Racun* nov = stvoriRacun(priv);
		if (!nov) {
			printf("\ngreska pri alokaciji");
			return -1;
		}
		head = sortR(head, nov);
	}
	fclose(fp);
	ispis(head);
	brisi(head);
	return 0;
}

int brisi(Racun*head){
	Racun* temp;
	while (head) {
		Artikl* a = head->lista;
		while (a) {
			Artikl* curr = a;
			a = a->next;
			free(curr);
		}
		temp = head;
		head = head->next;
		free(temp);
	}
	return 0;
}

int ispis(Racun* head) {
	Racun* temp = head;
	while (temp) {
		printf("\nDATUM: %s", temp->datum);
		Artikl* a = temp->lista;
		while (a) {
			printf("\n %s %d %.2f", a->ime, a->kolicina, a->cijena);
			a = a->next;
		}
		temp = temp->next;
		printf("\n");
	}
	return 0;
}

Racun* sortR(Racun* head, Racun* nov) {
	if (!head || strcmp(nov->datum, head->datum) < 0) {
		nov->next = head;
		return nov;
	}
	Racun* temp = head;
	while (temp->next != NULL && strcmp(nov->datum, temp->next->datum) > 0) {
		temp = temp->next;
	}
	nov->next = temp->next;
	temp->next = nov;
	return head;
}

Racun* stvoriRacun(const char*priv) {
	Racun* nov = (Racun*)malloc(sizeof(Racun));
	if (!nov) {
		printf("\ngreska pri alokaciji");
		return NULL;
	}
	FILE* dat = fopen(priv, "r");
	if (!dat) {
		printf("\ngreskapri otvaranju dat");
		return NULL;
	}
	fgets(nov->datum, sizeof(nov->datum), dat);
	nov->datum[strcspn(nov->datum, "\n")] = '\0';
	nov->next = NULL;
	nov->lista = stvoriListu(dat);
	fclose(dat);
	return nov;
}

Artikl* stvoriListu(FILE* dat) {
	Artikl* headL = NULL;
	while (1) {
		Artikl* nov = (Artikl*)malloc(sizeof(Artikl));
		if (!nov) {
			printf("\ngreska pri alokaciji");
			return NULL;
		}
		if (fscanf(dat, "%s %d %f", nov->ime, &nov->kolicina, &nov->cijena) != 3) {
			free(nov);
			break;
		}
		else {
			nov->next = NULL;
			headL = sortList(nov, headL);
		}

	}
	return headL;
}

Artikl* sortList(Artikl* nov, Artikl* headL) {
	if (!headL || strcmp(nov->ime, headL->ime) < 0) {
		nov->next = headL;
		return nov;
	}
	Artikl* temp = headL;
	while (temp->next != NULL && strcmp(nov->ime, temp->next->ime) > 0) {
		temp = temp->next;
	}
	nov->next = temp->next;
	temp->next = nov;
	return headL;
}