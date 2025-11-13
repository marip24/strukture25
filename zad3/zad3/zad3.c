/*3. Prethodnom zadatku dodati funkcije:
A. dinamièki dodaje novi element iza odreðenog elementa,
B. dinamièki dodaje novi element ispred odreðenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. èita listu iz datoteke.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person;
typedef struct Person* Position;

typedef struct Person {
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
Person* insertAfter(Person*, const char*);
Person* insertBefore(Person*, const char*);
Person* sortList(Person*);
int saveinFile(Person*, const char*);
Person* readFromFile(const char*);

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
	Start(Head.next, P3);

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

	char newAfter[50];
	printf("\niza kojeg prezimena zelite upisati novu osobu: ");
	scanf(" %s", &newAfter);
	Head.next=insertAfter(Head.next, newAfter);
	Print(Head.next);

	char newBefore[50];
	printf("\nispred kojeg prezimena zelite upisati novu osobu: ");
	scanf(" %s", &newBefore);
	Head.next=insertBefore(Head.next, newBefore);
	Print(Head.next);

	Head.next=sortList(Head.next);
	printf("\nsortirana lista po prezimenima je: \n");
	Print(Head.next);

	saveinFile(Head.next, "zadatak3.txt");
	Head.next = clean(Head.next);

	printf("\ncitanje liste iz datoteke: \n");
	Head.next = readFromFile("zadatak3.txt");
	Print(Head.next);

	Head.next = clean(Head.next);

	return 0;
}

Person* insert() {
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
	Person* temp;
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
	return NULL;
}
Person* insertAfter(Person* head, const char* surname) {
	Person* targeted = Find(head, surname);
	if (targeted!=NULL) {
		Person* newPerson = insert();
		newPerson->next = targeted->next;
		targeted->next = newPerson;
	}
	return head;
}
Person* insertBefore(Person* head, const char* surname) {
	Person* targeted = Find(head, surname);
	if (!targeted) {
		printf("\nosoba nije pronadena");
		return head;
	}
	Person* newPerson = insert();
	if (targeted == head) {
		newPerson->next = head;
		return newPerson;
	}
	Person* prev = head;
	while (prev->next != NULL && prev->next != targeted)
		prev = prev->next;
	newPerson->next = targeted;
	prev->next = newPerson;
	return head;
}
Person* sortList(Person*head) {
	int swap;
	Person*end = NULL;
	do {
		swap = 0;
		Person* prev = NULL;
		Person* curr = head;
		while (curr->next != end) {
			if (strcmp(curr->surname, curr->next->surname) > 0) {
				Person* temp = curr->next;
				curr->next = temp->next;
				temp->next = curr;
				if (prev == NULL)
					head = temp;
				else
					prev->next = temp;
				prev = temp;
				swap = 1;
			}
			else {
				prev = curr;
				curr = curr->next;
			}
		}
		end = curr;
	} while (swap);
	return head;
}
int saveinFile(Person*head, const char*fileName) {
	FILE* f = fopen(fileName, "w");
	if (!f) {
		printf("\ngreska pri otvaranju datoteke");
		return -1;
	}
	Person* temp = head;
	while (temp != NULL) {
		fprintf(f, "%s %s %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}
	fclose(f);
	printf("\nlista je spremljena u datoteku.");
	return 0;
}
Person* readFromFile(const char* fileName) {
	FILE* f = fopen(fileName, "r");
	if (!f) {
		printf("\ngreska pri otvaranju datoteke");
		return NULL;
	}
	Person* head = NULL;
	Person* last = NULL;
	while (1) {
		Person* newPerson = (Person*)malloc(sizeof(Person));
		if (!newPerson) {
			printf("\ngreska");
			fclose(f);
			return head;
		}
		int r = fscanf(f, " %s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear);
		if (r != 3) {
			free(newPerson);
			break;
		}
		newPerson->next = NULL;
		if (head == NULL)
			head = newPerson;
		else
			last->next = newPerson;
		last=newPerson;
	}
	fclose(f);
	printf("\nlista je ucitana iz datoteke.");
	return head;
}