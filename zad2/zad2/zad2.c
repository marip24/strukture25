/*2. Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
A. dinamièki dodaje novi element na poèetak liste,
B. ispisuje listu,
C. dinamièki dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person;
typedef struct Person* Position;

typedef struct Person{
	char name[50];
	char surname[50];
	int birthYear;
	Position next;
}Person;

Person* insert();
int Print(Person*);
Person* Start(Person*, Person*);
Person* End(Person*, Person*);
Person* Find(Person*, const char*);
int sameString(const char*, const char*);
Person* deleteSurname(Person*, const char*);
Person* clean(Person*);

int main() {
	Person Head = { .name = "",.surname = "",.birthYear = 0, .next = NULL };
	printf("\nunesite 4 osobe: ");
	printf("\nosoba br 1.:");
	Person* P1 = insert();
	Head.next = P1;

	printf("\nosoba br 2.:");
	Person* P2 = insert();
	End(Head.next, P2);

	printf("\nosoba br 3.:");
	Person* P3 = insert();
	End(Head.next, P3);

	printf("\nosoba br 4.:");
	Person* P4 = insert();
	End(Head.next, P4);
	Print(Head.next);
	
	char findSurname[50];
	printf("\nUpisite prezime koje zelite naci: ");
	scanf(" %s", &findSurname);
	Person* Found = Find(Head.next, findSurname);
	if (Found)
		printf("\ntrazena osoba je: %s %s %d", Found->name, Found->surname, Found->birthYear);
	else
		printf("\nosoba nije pronadena");

	char deleSurname[50];
	printf("\nupisite prezime koje zelite izbrisati: ");
	scanf(" %s", &deleSurname);
	Head.next = deleteSurname(Head.next, deleSurname);

	Print(Head.next);

	Head.next = clean(Head.next);

	return 0;
}

Person* insert(){
	Person* new = (Person*)malloc(sizeof(Person));
	if (!new) {
		printf("\ngreska pri alokaciji memorije.");
		return NULL;
	}
	printf("\nunesi ima: ");
	scanf(" %s", new->name);
	printf("\nunesi prezime: ");
	scanf(" %s", new->surname);
	printf("\nunesi godinu rodenja: ");
	scanf("%d", &new->birthYear);
	new->next = NULL;
	return new;
}

int Print(Person* head) {
	if (head == NULL) {
		printf("\nLista je prazna.");
		return -1;
	}
	printf("\nLista osoba: ");
	Person* temp = head;
	while (temp != NULL) {
		printf("\nIme: %s\nPrezime: %s\n Godina rodenja: %d", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}
	return 0;
}
Person* Start(Person* head, Person* nP) {
	nP->next = head;
	return nP;
}
Person* End(Person* head, Person* nP) {
	Person* temp = head;
	if (head == NULL)
		return nP;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = nP;
	return head;
}
int sameString(const char* word1, const char* word2) {
	while (*word1 && *word2) {
		if (*word1 != *word2)
			return 0;
		word1++;
		word2++;
	}
	return 1;
}
Person* Find(Person* head, const char* findSurname) {
	while (head != NULL) {
		if (sameString(head->surname, findSurname))
			return head;
		head = head->next;
	}
	return NULL;
}
Person* deleteSurname(Person* head, const char* delSurname) {
	Person* temp = NULL;
	Person* anoth = head;
	while (anoth != NULL) {
		if (sameString(anoth->surname, delSurname)) {
			if (temp == NULL) {
				Person* newHead = anoth->next;
				free(anoth);
				return newHead;
			}
			else {
				temp->next = anoth->next;
				free(anoth);
				return head;
			}
		}
		temp = anoth;
		anoth = anoth->next;
	}
	printf("\nprezime %s nije pronadeno", delSurname);
	return head;
}
Person* clean(Person* head) {
	Person *temp;
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
	return NULL;
}